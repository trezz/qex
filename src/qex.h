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
#define QEX_NUM_HOURS   12
#define QEX_NUM_MINUTES 60
#define QEX_NUM_SECONDS 60

namespace qex
{

/** Program main class */
class Qex
{
  public:
    typedef std::unordered_set<const char*> QuerySet;
      /**< queries set */

  public:
    /** Constructor */
    Qex (bool do_map_unique_queries);
    /** Destructor */
    virtual ~Qex ();

    /**
     * Index a TSV line formmatted as follows:
     * <YEAR>-<MONTH>-<DAY> <HOUR>:<MIN>:<SEC>\t<QUERY>[\n|\r]
     *
     * Throws std::exception on parsing error.
     *
     * \param [in] line Pointer on a file line formatted as described above.
     * \return a pointer on the next line to index, 0 if end of file is
     *         reached.
     */
    char* index_tsv_line (char* line);

  private:
    bool _do_map_unique_queries;
      /**< If true, register each queries in a map with their number of
       * occurence as value. */

    std::unordered_map<std::string, size_t> _num_unique_queries;
      /**< Mapping of number of occurrence of the same query in the input
       * files. */

    /* Queries indexed per year, month, day etc... */
    QuerySet _per_year[QEX_NUM_YEARS];
    QuerySet _per_month[QEX_NUM_MONTHS];
    QuerySet _per_day[QEX_NUM_DAYS];
    QuerySet _per_hour[QEX_NUM_HOURS];
    QuerySet _per_minute[QEX_NUM_MINUTES];
    QuerySet _per_second[QEX_NUM_SECONDS];
};

} /* namespace qex */

#endif /* !_QEX_QEX_H_ */
