#ifndef DW4_IGTIMERDISPATCHVIEW_H
#define DW4_IGTIMERDISPATCHVIEW_H
#include "dw4/core/igObjectDispatchView.h"

/* igTimer's virtual functions as the engine and the game call them on igPsx2LongTimer
 * (igPsx2LongTimer_<Name>): slot 24 reads the elapsed nanoseconds, slot 26 stops the clock and
 * slot 29 restarts it.
 * ABI view only: never instantiated. */
class igTimerDispatchView : public igObjectDispatchView {
public:
    virtual void d21(); virtual void d22();
    virtual double GetTimeAsDouble();                                       /* slot 23 */
    virtual long long GetElapsedTime();                                     /* slot 24 */
    virtual void d25();
    virtual void Stop();                                                    /* slot 26 */
    virtual void Reset();                                                   /* slot 27 */
    virtual void d28();
    virtual void Restart();                                                 /* slot 29 */
};

#endif
