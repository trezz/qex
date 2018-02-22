#include "gtest/gtest.h"

#include "range.h"

TEST(Range, create)
{
  ASSERT_NO_THROW(new qex::Range(nullptr));
}
