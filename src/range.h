#ifndef _QEX_RANGE_H_
#define _QEX_RANGE_H_

namespace qex
{

/** Convert a string into an int. Convert as many character as possible and
 * returns a pointer on the next non-integer character in s via the next
 * pointer.
 *
 * Note that leading spaces are trimmed. */
int toint(const char* s, char** next);

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
  /** Constructor which define the range as wildcard ('*') for all timestamp
   * fields. */
  Range ();
  /** Constructor with an input string timestamp as argument */
  Range (const char* timestamp);
  

  /** Resilient timestamp parser which convert a string timestamp into a
   * Range object. On parsing error on one of the timestamp fields, the
   * erroneous field is considered to be '*', as for all the following fields.
   * The previous valid fields are preserved. */
  void parse (const char* range);

  /* First part of the timestamp as integer value. */
  int year, month, day;
  /* Second part of the timestamp */
  int hour, minute, second;

  char* end;
    /**< Pointer on the character following the parsed range */
};

} /* namespace qex */

#endif /* !_QEX_RANGE_H_ */
