#ifndef DW4_IGCONTROLLERVIRTUALS_H
#define DW4_IGCONTROLLERVIRTUALS_H

#include "dw4/igObjectVirtuals.h"

/* A controller seen through its vtable: the pressed buttons, a joystick's axes, the controller's id
 * and whether it is plugged in. */
class igControllerVirtuals : public igObjectVirtuals {
public:
    DW4_SLOTS_5(t) DW4_SLOTS_1(u0) DW4_SLOTS_1(u1)
    virtual unsigned int getButtons();
    virtual void getStick(int stick, float *x, float *y);
    virtual unsigned short getId();
    DW4_SLOTS_1(v0)
    virtual int isConnected();
};

#endif
