#ifndef DW4_IGBLENDEQUATIONEXTDISPATCHVIEW_H
#define DW4_IGBLENDEQUATIONEXTDISPATCHVIEW_H
#include "dw4/core/igObjectDispatchView.h"

/* igBlendEquationExt's virtual functions as igBlendFunctionAttr calls them on the PS2 extension: slot 28 is the
 * kit's applyEquation (alchemy-kit_202309 include/igGfx/igBlendEquationExt.h), after igContextExt's slots 21-26
 * and DW4's slot 27. ABI view only: never instantiated. */
class igBlendEquationExtDispatchView : public igObjectDispatchView {
public:
    virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25();
    virtual void d26(); virtual void d27();
    virtual void applyEquation();                                             /* slot 28 */
};
#endif
