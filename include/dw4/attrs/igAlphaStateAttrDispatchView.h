#ifndef DW4_IGALPHASTATEATTRDISPATCHVIEW_H
#define DW4_IGALPHASTATEATTRDISPATCHVIEW_H
#include "dw4/core/igObjectDispatchView.h"

/* igAlphaStateAttr's virtual functions: slot 30 switches the alpha test on or off (Gap::Attrs::igAlphaStateAttr::setState).
 * ABI view only: never instantiated. */
class igAlphaStateAttrDispatchView : public igObjectDispatchView {
public:
    virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
    virtual void SetState(int enabled);                                     /* slot 30 */
};

#endif
