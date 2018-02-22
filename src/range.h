#ifndef _QEX_RANGE_H_
#define _QEX_RANGE_H_

namespace qex
{

/**
 * Declaration of the Range class with represents a timestamp formatted as
 * follows:
 *  <YEAR>-<MONTH>-<DAY> <HOUR>:<MIN>:<SEC>
 * 
 * This class also handles wildcard character '*' in place of any numerical
 * value. The special value '-1' is set in that case in the corresponding
 * attribute.
 * 
 * Note that in case an invalid range is given as input, all dates are accepted
 * in range (all values to -1).
 */
struct Range
{
  /** Constructor with a timestamp character string as argument. 
   * It fills its integer attributes by converting the input string values. */
  Range (const char* range);

  /* Comparison operators */
  bool operator == (const Range& other) const;
  bool operator != (const Range& other) const;

  /* First part of the timestamp as integer value. */
  int year, month, day;
  /* Second part of the timestamp */
  int hour, minute, second;

  char* end;
    /**< Pointer on the character following the parsed range */
};

} /* namespace qex */

#endif /* !_QEX_RANGE_H_ */
