#include "qex.h"

#include <string.h>

#include "trie.h"

namespace qex
{

Qex::Qex ()
{
  _root = new Trie(0, nullptr);
}

Qex::~Qex ()
{
  if (_root != nullptr)
  { delete _root; }
}

bool Qex::index_tsv_line (const char* line)
{
  char* next_token = nullptr;
  size_t date[6];

  /* convert timestamp fields into integer */
  for (size_t i = 0; i < 6; ++i)
  {
    date[i] = strtoul(line, &next_token, 10);

    if (line == next_token || next_token == nullptr)
    {
      /* ill-formed line detected, not a valid timestamp */
      return false;
    }
    /* step over separator character such as '-', ' ', '\t' or ':' */
    line = next_token + 1;
  }

  /* next_token should point to the character preceding the query, which
   * is `\t` in a TSV file. If not then an invalid line was given as input
   * argument. */
  if (*next_token != '\t')
  { return false; }

  /* remove eventual trailing newlines and save the query */
  Trie* query_leaf = _root->add_string(line);

  /* date bounds checking */
  if (date[0] < QEX_FIRST_YEAR || date[0] >= (QEX_NUM_YEARS + QEX_FIRST_YEAR) ||
      date[1] >= QEX_NUM_MONTHS ||
      date[2] >= QEX_NUM_DAYS ||
      date[3] >= QEX_NUM_HOURS ||
      date[4] >= QEX_NUM_MINUTES ||
      date[5] >= QEX_NUM_SECONDS)
  { return false; }

  /* reference query leaf node from timestamp-indexed buffers */
  _per_year[date[0] - QEX_FIRST_YEAR].insert(query_leaf);
  _per_month[date[1]].insert(query_leaf);
  _per_day[date[2]].insert(query_leaf);
  _per_hour[date[3]].insert(query_leaf);
  _per_minute[date[4]].insert(query_leaf);
  _per_second[date[5]].insert(query_leaf);

  return true;
}

} /* namespace qex */
