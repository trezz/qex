/**
 *
 */
#ifndef _QEX_QEX_H_
#define _QEX_QEX_H_

#include <unordered_set>
#include <unordered_map>
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
    typedef std::unordered_set<std::string> QuerySet;
      /**< queries set */

  public:
    /** Constructor */
    Qex (bool do_map_unique_queries, char* range = nullptr);
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

  private:
    bool _do_map_unique_queries;
      /**< If true, register each queries in a map with their number of
       * occurence as value. */

    Range _range;

    /* Queries in requested range */
    QuerySet _queries_in_range;
};

} /* namespace qex */

#endif /* !_QEX_QEX_H_ */
