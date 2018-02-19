/**
 *
 */
#ifndef _QEX_QEX_H_
#define _QEX_QEX_H_

#include <unordered_set>

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

class Trie;

class Qex
{
  public:
    typedef std::unordered_set<const Trie*> TrieSet;
      /**< Set of constrant pointers to Trie leaf nodes */

  public:
    /** Constructor */
    Qex ();
    /** Destructor */
    virtual ~Qex ();

    /**
     * Index a TSV line formmatted as follows:
     * <YEAR>-<MONTH>-<DAY> <HOUR>:<MIN>:<SEC>\t<QUERY>[\n|\r|\0]
     *
     * Returns true on success or false if something when wrong.
     */
    bool index_tsv_line (const char* line);

  private:
    Trie* _root;
      /**< Root Trie data structure holding all indexed queries */

    /* Leafs nodes indexed per year, month, day etc... */
    TrieSet _per_year[QEX_NUM_YEARS];
    TrieSet _per_month[QEX_NUM_MONTHS];
    TrieSet _per_day[QEX_NUM_DAYS];
    TrieSet _per_hour[QEX_NUM_HOURS];
    TrieSet _per_minute[QEX_NUM_MINUTES];
    TrieSet _per_second[QEX_NUM_SECONDS];
};

} /* namespace qex */

#endif /* !_QEX_QEX_H_ */
