#include "dw4/reflected.h"
extern "C" {
int Gap__Core__igObject__vfunc_08__002ff0f0(beSvWriteMediaApi *);
int igObject_Destroy(igObject *);
void Gap__Bec__beSvWriteMediaApi__vfunc_08(beSvWriteMediaApi *arg0);
}

void Gap__Bec__beSvWriteMediaApi__vfunc_08(beSvWriteMediaApi *arg0) {
    igObject *temp_a0;

    temp_a0 = (igObject *)arg0->_saveWork;
    if (temp_a0 != 0) {
        if (temp_a0 != 0) {
            temp_a0->_refCount = (int)temp_a0->_refCount - 1;
            if (((unsigned long long) ((long long) (int)temp_a0->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        arg0->_saveWork = 0;
    }
    Gap__Core__igObject__vfunc_08__002ff0f0(arg0);
}
