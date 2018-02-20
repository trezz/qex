#include "qex.h"

#include <iostream>

namespace qex
{

Range::Range (const char* range)
{
  /* fill a table of 6 dates with the string range. This loop accepts wildcards
   * characters (*) */
  std::vector<int> date(6, -1);
  char* next_token = nullptr;

  for (size_t i = 0; range && i < 6; ++i)
  {
    date[i] = strtoul(range, &next_token, 10);
    if (range == next_token && *range == '*')
    {
      /* skipping wildcard character '*' + '-' */
      range += 2;
    }
    else if (next_token == nullptr)
    { break; }
    else
    {
      /* step over separator character such as '-', ' ', '\t' or ':' */
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

/*****************************************************************************/

Qex::Qex (bool do_map_unique_queries, const char* range /* = nullptr */)
  : _do_map_unique_queries(do_map_unique_queries),
    _range(range)
{ }

Qex::~Qex ()
{ }

char* Qex::index_tsv_line (char* line, size_t lineno)
{
  Range range(line);

  /* next_token should point to the character preceding the query, which
   * is `\t` in a TSV file. If not then an invalid line was given as input
   * argument.
   * The query is pointed by line here.
   */
  if (*line != '\t')
  { throw std::string(std::to_string(lineno)
          + ": ill-formed line detected. Query not found"); }
  char* query = ++line;

  /* remove endline characters and step to next line */
  while (*line != '\n' && *line != '\r' && *line != 0)
  { ++line; }
  while (*line == '\n' || *line == '\r')
  {
    *line = 0;
    ++line;
  }

  /* here, the entire line is parsed. If the range does not match with the
   * requested user one, do nothing more. */
  if (range == _range)
  {
    if (_do_map_unique_queries)
    {
      ++_num_unique_queries[query];
    }
    else
    {
      _queries_in_range.insert(query);
    }
  }

  /* returns null if this is the end of file */
  return *line != 0 ? line : 0;
}


} /* namespace qex */
