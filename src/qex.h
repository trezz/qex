/**
 *
 */
#ifndef _QEX_QEX_H_
#define _QEX_QEX_H_

#include <unordered_set>
#include <unordered_map>
#include <map>
#include <string>

/* Year at index 0 */
#define QEX_FIRST_YEAR  1970
/* Will work until 2070 */
#define QEX_NUM_YEARS   100

/* Obvious named date values */
#define QEX_NUM_MONTHS  12
#define QEX_NUM_DAYS    31
#define QEX_NUM_HOURS   24
#define QEX_NUM_MINUTES 60
#define QEX_NUM_SECONDS 60

namespace qex
{

struct Range
{
  Range (char* range);
  bool operator == (const Range& other) const;
  bool operator != (const Range& other) const;

  int year;
  int month;
  int day;
  int hour;
  int minute;
  int second;

  char* end;
    /**< Pointer on the character following the parsed range */
};

/** Program main class */
class Qex
{
  public:
    typedef std::unordered_map<std::string, size_t> QueryMap;
      /**< queries map with their number of occurrence as values */
    typedef std::map<size_t, std::unordered_set<std::string>> PopularQueriesMap;

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

    size_t num_distinct_queries () const;

    void build_most_popular_queries_set ();
    void print_nth_most_popular_queries (size_t num) const;

  private:
    Range _range;

    /* Queries in requested range */
    QueryMap _queries_in_range;

    PopularQueriesMap _popular_queries;
};

} /* namespace qex */

#endif /* !_QEX_QEX_H_ */
