#include "gtest/gtest.h"

#include "range.h"
#include "qex.h"

using namespace qex;

TEST(Range, toint)
{
  ASSERT_EQ(12, toint("12", NULL));
  ASSERT_EQ(0, toint("toto", NULL));
  ASSERT_EQ(4, toint("4", NULL));
  ASSERT_EQ(123456789, toint("123456789", NULL));
  ASSERT_EQ(2017, toint("2017-40", NULL));

  /* I know this is bad but since this test never actually modifies the string
   * it does no harm. */
  char* s = (char*) "1987-06-12";

  ASSERT_EQ(1987, toint(s, &s));
  ASSERT_EQ('-', *s);
  ++s;
  ASSERT_EQ(6, toint(s, &s));
  ASSERT_EQ('-', *s);
  ++s;
  ASSERT_EQ(12, toint(s, &s));
  ASSERT_EQ(0, toint(s, &s));
}

TEST(Range, valid)
{
  Range r;

  /* valid complete range */
  ASSERT_NO_THROW(r.parse("1987-06-12 9:30:00"));
  ASSERT_EQ(r.year, 1987); ASSERT_EQ(r.month,   6);   ASSERT_EQ(r.day,   12);
  ASSERT_EQ(r.hour, 9);    ASSERT_EQ(r.minute,  30);  ASSERT_EQ(r.second, 0);

  /* valid incomplete range (date only) */
  ASSERT_NO_THROW(r.parse("1-2-3"));
  ASSERT_EQ(r.year, 1); ASSERT_EQ(r.month, 2); ASSERT_EQ(r.day, 3);
  ASSERT_EQ(r.hour, -1); ASSERT_EQ(r.minute, -1); ASSERT_EQ(r.second, -1);

  /* valid incomplete range (year only) */
  ASSERT_NO_THROW(r.parse("2017"));
  ASSERT_EQ(r.year, 2017); ASSERT_EQ(r.month, -1); ASSERT_EQ(r.day, -1);
  ASSERT_EQ(r.hour, -1); ASSERT_EQ(r.minute, -1); ASSERT_EQ(r.second, -1);

  /* valid with wildcard range */
  ASSERT_NO_THROW(r.parse("*-03-* 23:*:12"));
  ASSERT_EQ(r.year, -1); ASSERT_EQ(r.month, 3); ASSERT_EQ(r.day, -1);
  ASSERT_EQ(r.hour, 23); ASSERT_EQ(r.minute, -1); ASSERT_EQ(r.second, 12);
}

TEST(Range, invalid)
{
  Range r;

  /* null range */
  ASSERT_NO_THROW(r.parse(nullptr));
  ASSERT_EQ(r.year, -1); ASSERT_EQ(r.month, -1); ASSERT_EQ(r.day, -1);
  ASSERT_EQ(r.hour, -1); ASSERT_EQ(r.minute, -1); ASSERT_EQ(r.second, -1);

  /* empty range */
  ASSERT_NO_THROW(r.parse(""));
  ASSERT_EQ(r.year, -1); ASSERT_EQ(r.month, -1); ASSERT_EQ(r.day, -1);
  ASSERT_EQ(r.hour, -1); ASSERT_EQ(r.minute, -1); ASSERT_EQ(r.second, -1);

  /* invalid: not a number */
  ASSERT_NO_THROW(r.parse("Vincent"));
  ASSERT_EQ(r.year, -1); ASSERT_EQ(r.month, -1); ASSERT_EQ(r.day, -1);
  ASSERT_EQ(r.hour, -1); ASSERT_EQ(r.minute, -1); ASSERT_EQ(r.second, -1);

  /* invalid: To much fields -> expected the first values to be taken into
   * account */
  ASSERT_NO_THROW(r.parse("1-2-3-4 5:6:7:8"));
  ASSERT_EQ(r.year, 1); ASSERT_EQ(r.month, 2); ASSERT_EQ(r.day, 3);
  ASSERT_EQ(r.hour, 4); ASSERT_EQ(r.minute, 5); ASSERT_EQ(r.second, 6);

  /* invalid separators */
  ASSERT_NO_THROW(r.parse("1-2-3  4::5"));
  ASSERT_EQ(r.year, 1); ASSERT_EQ(r.month, 2); ASSERT_EQ(r.day, 3);
  ASSERT_EQ(r.hour, 4); ASSERT_EQ(r.minute, -1); ASSERT_EQ(r.second, -1);
}

TEST(Range, equality)
{
  Qex q;
  ASSERT_TRUE(q.is_equal(Range(""), Range("")));
  ASSERT_TRUE(q.is_equal(Range("1"), Range("")));
  ASSERT_TRUE(q.is_equal(Range("1-2-3 4:5:6"), Range("1-*-3 4:5:*")));
  ASSERT_TRUE(!q.is_equal(Range("1-2-3"), Range("1-*-2234")));
}
