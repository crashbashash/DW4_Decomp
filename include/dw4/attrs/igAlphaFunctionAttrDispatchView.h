#ifndef DW4_IGALPHAFUNCTIONATTRDISPATCHVIEW_H
#define DW4_IGALPHAFUNCTIONATTRDISPATCHVIEW_H
#include "dw4/core/igObjectDispatchView.h"

/* igAlphaFunctionAttr's virtual functions: slot 30 stores the comparison (an IG_GFX_ALPHA_FUNCTION),
 * slot 31 the reference value it compares against.
 * ABI view only: never instantiated. */
class igAlphaFunctionAttrDispatchView : public igObjectDispatchView {
public:
    virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
    virtual void SetAlphaFunc(int function);                                /* slot 30 */
    virtual void SetRefValue(float value);                                  /* slot 31 */
};

#endif
