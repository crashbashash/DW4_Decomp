#include "dw4/reflected.h"
extern "C" {
typedef struct RefCountedObject { char pad4[4]; int f4; } RefCountedObject;
int FUN_00462dc0(int);
int igObject_Destroy(RefCountedObject *);
void Gap__Bec__beCameraCtrl__vfunc_32(beCameraCtrl *arg0);
}

void Gap__Bec__beCameraCtrl__vfunc_32(beCameraCtrl *arg0) {
    RefCountedObject *t;

    arg0->_cameraNow = 0;
    arg0->_cameraOld = 0;
    if (arg0->_viewerMang != 0) {
        FUN_00462dc0(arg0->_viewerMang);
    }
    t = (RefCountedObject *)arg0->_cameraMode;
    if (t != 0) {
        t->f4 -= 1;
        if ((t->f4 & 0x7fffff) == 0) {
            igObject_Destroy(t);
        }
    }
    arg0->_cameraMode = 0;
}
