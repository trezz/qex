#include "gtest/gtest.h"

#include "range.h"

using namespace qex;

TEST(Range, create)
{
  Range* r = nullptr;

  /* valid complete range */
  ASSERT_NO_THROW(r = new Range("1987-06-12 9:30:00"));
  ASSERT_EQ(r->year, 1987); ASSERT_EQ(r->month,   6);   ASSERT_EQ(r->day,   12);
  ASSERT_EQ(r->hour, 9);    ASSERT_EQ(r->minute,  30);  ASSERT_EQ(r->second, 0);
  ASSERT_NO_THROW(delete r);

  /* valid incomplete range (date only) */
  ASSERT_NO_THROW(r = new Range("1-2-3"));
  ASSERT_EQ(r->year, 1); ASSERT_EQ(r->month, 2); ASSERT_EQ(r->day, 3);
  ASSERT_EQ(r->hour, -1); ASSERT_EQ(r->minute, -1); ASSERT_EQ(r->second, -1);
  ASSERT_NO_THROW(delete r);

  /* valid incomplete range (year only) */
  ASSERT_NO_THROW(r = new Range("2017"));
  ASSERT_EQ(r->year, 2017); ASSERT_EQ(r->month, -1); ASSERT_EQ(r->day, -1);
  ASSERT_EQ(r->hour, -1); ASSERT_EQ(r->minute, -1); ASSERT_EQ(r->second, -1);
  ASSERT_NO_THROW(delete r);

  /* valid with wildcard range */
  ASSERT_NO_THROW(r = new Range("*-03-* 23:*:12"));
  ASSERT_EQ(r->year, -1); ASSERT_EQ(r->month, 3); ASSERT_EQ(r->day, -1);
  ASSERT_EQ(r->hour, 23); ASSERT_EQ(r->minute, -1); ASSERT_EQ(r->second, 12);
  ASSERT_NO_THROW(delete r);

  /* null range */
  ASSERT_NO_THROW(r = new Range(nullptr));
  ASSERT_EQ(r->year, -1); ASSERT_EQ(r->month, -1); ASSERT_EQ(r->day, -1);
  ASSERT_EQ(r->hour, -1); ASSERT_EQ(r->minute, -1); ASSERT_EQ(r->second, -1);
  ASSERT_NO_THROW(delete r);

  /* empty range */
  ASSERT_NO_THROW(r = new Range(""));
  ASSERT_EQ(r->year, -1); ASSERT_EQ(r->month, -1); ASSERT_EQ(r->day, -1);
  ASSERT_EQ(r->hour, -1); ASSERT_EQ(r->minute, -1); ASSERT_EQ(r->second, -1);
  ASSERT_NO_THROW(delete r);

  /* invalid: not a number */
  ASSERT_NO_THROW(r = new Range("Vincent"));
  ASSERT_EQ(r->year, -1); ASSERT_EQ(r->month, -1); ASSERT_EQ(r->day, -1);
  ASSERT_EQ(r->hour, -1); ASSERT_EQ(r->minute, -1); ASSERT_EQ(r->second, -1);
  ASSERT_NO_THROW(delete r);

  /* invalid: To much fields -> expected the first values to be taken into
   * account */
  ASSERT_NO_THROW(r = new Range("1-2-3-4 5:6:7:8"));
  ASSERT_EQ(r->year, 1); ASSERT_EQ(r->month, 2); ASSERT_EQ(r->day, 3);
  ASSERT_EQ(r->hour, 4); ASSERT_EQ(r->minute, 5); ASSERT_EQ(r->second, 6);
  ASSERT_NO_THROW(delete r);

  /* invalid separators */
  ASSERT_NO_THROW(r = new Range("1-2-3  4::5"));
  ASSERT_EQ(r->year, 1); ASSERT_EQ(r->month, 2); ASSERT_EQ(r->day, 3);
  ASSERT_EQ(r->hour, 4); ASSERT_EQ(r->minute, -1); ASSERT_EQ(r->second, -1);
  ASSERT_NO_THROW(delete r);
}
