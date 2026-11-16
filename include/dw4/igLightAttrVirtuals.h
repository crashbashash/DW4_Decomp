#ifndef DW4_IGLIGHTATTRVIRTUALS_H
#define DW4_IGLIGHTATTRVIRTUALS_H

#include "dw4/igObjectVirtuals.h"

/* igLightAttr seen through its vtable: the setters store a colour or the position and mark the
 * light changed. */
class igLightAttrVirtuals : public igObjectVirtuals {
public:
    DW4_SLOTS_5(t) DW4_SLOTS_1(u0) DW4_SLOTS_1(u1) DW4_SLOTS_1(u2) DW4_SLOTS_1(u3)
    virtual void setDiffuse(const float *rgba);
    virtual void setAmbient(const float *rgba);
    virtual void setSpecular(const float *rgba);
    virtual void setPosition(const float *position);
};

#endif
