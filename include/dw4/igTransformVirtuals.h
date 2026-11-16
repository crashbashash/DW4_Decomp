#ifndef DW4_IGTRANSFORMVIRTUALS_H
#define DW4_IGTRANSFORMVIRTUALS_H

#include "dw4/igObjectVirtuals.h"

/* igTransform seen through its vtable: slot 35 stores the transform's matrix. */
class igTransformVirtuals : public igObjectVirtuals {
public:
    DW4_SLOTS_5(t) DW4_SLOTS_5(u) DW4_SLOTS_1(v0) DW4_SLOTS_1(v1) DW4_SLOTS_1(v2) DW4_SLOTS_1(v3)
    virtual void setMatrix(const float *matrix);
};

#endif
