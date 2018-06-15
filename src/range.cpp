#include "range.h"

#include <cstdlib>

namespace qex
{

Range::Range ()
  : year(-1), month(-1), day(-1),
    hour(-1), minute(-1), second(-1)
{ }

Range::Range (const char* timestamp)
{ parse(timestamp); }

void Range::parse (const char* range)
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
    else if (range == next_token)
    {
      /* invalid character found where integer conversion should occured.
       * reset current date value to -1 and stop conversion. */
      date[i] = -1;
      break;
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

} /* namespace qex */

