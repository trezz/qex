#include "range.h"

#include <cstdlib>

namespace qex
{

Range::Range (char* range)
{
  /* fill a table of 6 dates with the string range. This loop accepts wildcards
   * characters (*) */
  int date[6] = {-1, -1, -1, -1, -1, -1};
  char* next_token = nullptr;

  for (size_t i = 0; range && i < 6; ++i)
  {
    date[i] = strtoul(range, &next_token, 10);
    if (range == next_token && *range == '*')
    {
      /* skipping wildcard character '*' + '-' */
      date[i] = -1;
      range++;
      if (*range != 0)
        range++;
    }
    else if (*next_token == 0)
    {
      break;
    }
    else
    {
      /* eventually step over separator character such as '-', ' ', '\t' or ':' */
      range = next_token + 1;
    }
  }

  /* fill attributes */
  end = next_token;
  year = date[0];
  month = date[1];
  day = date[2];
  hour = date[3];
  minute = date[4];
  second = date[5];
}

bool Range::operator == (const Range& other) const
{
  return
    (year == -1   || other.year == -1   || year == other.year     ) &&
    (month == -1  || other.month == -1  || month == other.month   ) &&
    (day == -1    || other.day == -1    || day == other.day       ) &&
    (hour == -1   || other.hour == -1   || hour == other.hour     ) &&
    (minute == -1 || other.minute == -1 || minute == other.minute ) &&
    (second == -1 || other.second == -1 || second == other.second );
}

bool Range::operator != (const Range& other) const
{ return ! (*this == other); }

} /* namespace qex */

