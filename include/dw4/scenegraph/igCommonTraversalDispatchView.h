#ifndef DW4_IGCOMMONTRAVERSALDISPATCHVIEW_H
#define DW4_IGCOMMONTRAVERSALDISPATCHVIEW_H
#include "dw4/core/igObjectDispatchView.h"

/* igCommonTraversal's virtual functions: slot 24 reads the traversal's time (the top of _timeStack,
 * else the buffered clock), slot 29 resets the per-frame state (the attribute stack, the sorter,
 * the object pools and the palette lists), slot 30 pushes the time a subtree runs at onto
 * _timeStack and slot 31 pops it again.
 * ABI view only: never instantiated. */
class igCommonTraversalDispatchView : public igObjectDispatchView {
public:
    virtual void d21(); virtual void d22(); virtual void d23();
    virtual long long getTime();                                            /* slot 24 */
    virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28();
    virtual void reset();                                                   /* slot 29 */
    virtual void pushTime(long long time);                                  /* slot 30 */
    virtual void popTime();                                                 /* slot 31 */
};

#endif
