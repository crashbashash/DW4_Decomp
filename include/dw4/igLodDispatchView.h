#ifndef DW4_IGLODDISPATCHVIEW_H
#define DW4_IGLODDISPATCHVIEW_H
#include "dw4/igObjectDispatchView.h"

/* igLod's virtual functions: slot 29 forgets the range the last selection found (_lastRange,
 * _lastIndex, _lastLower, _lastUpper), which a caller does after editing _rangeList.
 * ABI view only: never instantiated. */
class igLodDispatchView : public igObjectDispatchView {
public:
    virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28();
    virtual void resetLastRange();                                          /* slot 29 */
};

#endif
