#ifndef _QEX_QEX_H_
#define _QEX_QEX_H_

#include <unordered_set>
#include <unordered_map>
#include <map>
#include <string_view>

#include "range.h"

namespace qex
{

/** Program main class */
class Qex
{
  public:
    typedef std::unordered_map<std::string_view, size_t> QueryMap;
      /**< queries map with their number of occurrence as values */
    typedef std::map<size_t, std::unordered_set<std::string_view>> PopularQueriesMap;
      /**< most popular queries map, ordered by number of occurence */

  public:
    /** Constructor */
    Qex (char* range = nullptr);
    /** Destructor */
    virtual ~Qex ();

    /**
     * Index a TSV line formmatted as follows:
     * <YEAR>-<MONTH>-<DAY> <HOUR>:<MIN>:<SEC>\t<QUERY>[\n|\r]
     *
     * Throws std::exception on parsing error.
     *
     * \param [in] line   Pointer on a file line formatted as described above.
     * \param [in] lineno Line numer being processed.
     *
     * \return a pointer on the next line to index, 0 if end of file is
     *         reached.
     */
    char* index_tsv_line (char* line, size_t lineno);

    /** Returns the number of distinct queries indexed */
    size_t num_distinct_queries () const;

    /** Build the most popular queries set from the indexed queries */
    void build_most_popular_queries_set ();

    /** print the `num` number of most popular queries in descending order
     * on stdout. */
    void print_nth_most_popular_queries (size_t num) const;

  private:
    Range _range;
      /**< User-defined range given as constructor's input argument */
    QueryMap _queries_in_range;
      /**< Queries in requested range */
    PopularQueriesMap _popular_queries;
      /**< Popular queries ordered by number of occurence */
};

} /* namespace qex */

#endif /* !_QEX_QEX_H_ */