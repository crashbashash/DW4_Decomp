#include "dw4/reflected.h"
extern "C" {
typedef struct RefCountedObject { char pad4[4]; int f4; } RefCountedObject;
int igObject_Destroy(RefCountedObject *);

void Gap__Bec__beNDMWStatus__vfunc_32(beNDMWStatus *arg0) {
    RefCountedObject *temp_a0;

    temp_a0 = (RefCountedObject *)arg0->_windowPro;
    if (temp_a0 != 0) {
        temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
        if (((unsigned long long) ((long long) temp_a0->f4 << 0x29) >> 0x29) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    arg0->_windowPro = 0;
}
}
