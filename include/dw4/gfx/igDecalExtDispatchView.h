#ifndef DW4_IGDECALEXTDISPATCHVIEW_H
#define DW4_IGDECALEXTDISPATCHVIEW_H
#include "dw4/core/igObjectDispatchView.h"

/* igDecalExt's virtual function as igPsx2VisualContext::resetToDefault calls it on the PS2 extension: slot 28 is
 * the kit's setDecalOffset (alchemy-kit_202309 include/igGfx/igDecalExt.h), after igContextExt's slots 21-26 and
 * DW4's slot 27, as for igBlendEquationExt. ABI view only: never instantiated. */
class igDecalExtDispatchView : public igObjectDispatchView {
public:
    virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25();
    virtual void d26(); virtual void d27();
    virtual void setDecalOffset(unsigned int offset);                         /* slot 28 */
};
#endif
