#ifndef DW4_IGMODELVIEWMATRIXATTRDISPATCHVIEW_H
#define DW4_IGMODELVIEWMATRIXATTRDISPATCHVIEW_H
#include "dw4/core/igObjectDispatchView.h"

/* igModelViewMatrixAttr's virtual functions: slot 30 copies a matrix into the attribute.
 * ABI view only: never instantiated. */
class igModelViewMatrixAttrDispatchView : public igObjectDispatchView {
public:
    virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
    virtual void setMatrix(const float *matrix);                            /* slot 30 */
};

#endif
