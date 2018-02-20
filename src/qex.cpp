#include "qex.h"

#include <iostream>

namespace qex
{

Qex::Qex (bool do_map_unique_queries)
  : _do_map_unique_queries(do_map_unique_queries)
{ }

Qex::~Qex ()
{ }

char* Qex::index_tsv_line (char* line)
{
  char* next_token = nullptr;
  size_t date[6];

  /* convert timestamp fields into integer */
  for (size_t i = 0; i < 6; ++i)
  {
    date[i] = strtoul(line, &next_token, 10);
    if (line == next_token || next_token == nullptr)
    {
      throw std::string("ill-formed line detected. Not a valid timestamp");
    }
    /* step over separator character such as '-', ' ', '\t' or ':' */
    line = next_token + 1;
  }

  /* next_token should point to the character preceding the query, which
   * is `\t` in a TSV file. If not then an invalid line was given as input
   * argument.
   * The query is pointed by line here.
   */
  if (*next_token != '\t')
  { throw std::string("ill-formed line detected. Query not found"); }
  char* query = line;

  /* remove endline characters and step to next line */
  while (*line != '\n' && *line != '\r' && *line != 0)
  { ++line; }
  while (*line == '\n' || *line == '\r')
  {
    *line = 0;
    ++line;
  }

  if (_do_map_unique_queries)
  { ++_num_unique_queries[query]; }

  /* date bounds checking */
  if (date[0] < QEX_FIRST_YEAR || date[0] >= (QEX_NUM_YEARS + QEX_FIRST_YEAR) ||
      date[1] >= QEX_NUM_MONTHS ||
      date[2] >= QEX_NUM_DAYS ||
      date[3] >= QEX_NUM_HOURS ||
      date[4] >= QEX_NUM_MINUTES ||
      date[5] >= QEX_NUM_SECONDS)
  { throw std::string("ill-formed line detected. Not a valid timestamp"); }

  /* reference query leaf node from timestamp-indexed buffers */
  _per_year[date[0] - QEX_FIRST_YEAR].insert(query);
  _per_month[date[1]].insert(query);
  _per_day[date[2]].insert(query);
  _per_hour[date[3]].insert(query);
  _per_minute[date[4]].insert(query);
  _per_second[date[5]].insert(query);

  /* returns null if this is the end of file */
  return *line != 0 ? line : 0;
}

} /* namespace qex */
