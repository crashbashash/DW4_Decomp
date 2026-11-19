#ifndef DW4_IGLIGHTINGSTATEATTRDISPATCHVIEW_H
#define DW4_IGLIGHTINGSTATEATTRDISPATCHVIEW_H
#include "dw4/core/igObjectDispatchView.h"

/* igLightingStateAttr's virtual functions: slot 30 switches lighting on or off (igLightingStateAttr_SetState).
 * ABI view only: never instantiated. */
class igLightingStateAttrDispatchView : public igObjectDispatchView {
public:
    virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
    virtual void SetState(int enabled);                                     /* slot 30 */
};

#endif
