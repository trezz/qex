/**
 *
 */

#ifndef _QEX_RANGE_H_
#define _QEX_RANGE_H_

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

} /* namespace qex */

#endif /* !_QEX_RANGE_H_ */
