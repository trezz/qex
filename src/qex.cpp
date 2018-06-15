#include "qex.h"

#include <iostream>

namespace qex
{

Qex::Qex (char* range /* = nullptr */)
{ _user_range.parse(range); }

Qex::~Qex ()
{ }

char* Qex::index_tsv_line (char* line, size_t lineno)
{
  _range.parse(line);
  line = _range.end;

  /* next_token should point to the character preceding the query, which
   * is `\t` in a TSV file. If not then an invalid line was given as input
   * argument.
   * The query is pointed by line here.
   */
  if (*line != '\t')
  { throw std::string(std::to_string(lineno)
          + ": ill-formed line detected. Query not found"); }
  char* query = ++line;

  /* go to end of query and save its length */
  while (*line != '\n' && *line != '\r' && *line != 0)
  { ++line; }
  size_t query_size = line - query;

  /* remove endline characters and step to next line */
  while (*line == '\n' || *line == '\r')
  {
    *line = 0;
    ++line;
  }

  /* here, the entire line is parsed. If the range does not match with the
   * requested user one, do nothing more. */
  if (is_equal(_range, _user_range))
  {
    _queries_in_range[std::string_view(query, query_size)] += 1;
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
  { _popular_queries[query_num.second].push_back(query_num.first); }
}

void Qex::print_nth_most_popular_queries (size_t num) const
{
  PopularQueriesMap::const_iterator begin = _popular_queries.begin(),
                                    end = _popular_queries.end();
  while (end != begin)
  {
    --end;
    const auto& num_queries = *end;
    for (const std::string_view& query : num_queries.second)
    {
      if (num-- == 0)
      { return; }
      std::cout << query << " " << num_queries.first << std::endl;
    }
  }
}

bool Qex::is_equal(const Range& range, const Range& user_range)
{
  return
    ((user_range.year & range.year) == range.year) &&
    ((user_range.month & range.month) == range.month) &&
    ((user_range.day & range.day) == range.day) &&
    ((user_range.hour & range.hour) == range.hour) &&
    ((user_range.minute & range.minute) == range.minute) &&
    ((user_range.second & range.second) == range.second);
}

} /* namespace qex */
