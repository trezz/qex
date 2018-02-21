#include "qex.h"

#include <iostream>

namespace qex
{

Qex::Qex (char* range /* = nullptr */)
  : _range(range)
{ }

Qex::~Qex ()
{ }

char* Qex::index_tsv_line (char* line, size_t lineno)
{
  Range range(line);
  line = range.end;

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
    _queries_in_range[query] += 1;
  }

  /* returns null if this is the end of file */
  return *line != 0 ? line : 0;
}

size_t Qex::num_distinct_queries () const
{
  return _queries_in_range.size();
}

void Qex::build_most_popular_queries_set ()
{
  for (auto& query_num : _queries_in_range)
  { _popular_queries[query_num.second].insert(query_num.first); }
}

void Qex::print_nth_most_popular_queries (size_t num) const
{
  PopularQueriesMap::const_iterator begin = _popular_queries.begin(),
                                    end = _popular_queries.end();
  while (--end != begin)
  {
    const auto& num_queries = *end;
    for (const std::string& query : num_queries.second)
    {
      if (num-- == 0)
      { return; }
      std::cout << query << " " << num_queries.first << std::endl;
    }
  }
}

} /* namespace qex */
