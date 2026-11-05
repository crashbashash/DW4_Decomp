#include "dw4/reflected.h"
/* igObject header: the reference count at +4 is not a reflected field */
typedef struct RefCountedHeader { char pad4[4]; int references; } RefCountedHeader;
extern "C" {
int Gap__Core__igObject__vfunc_08__002ff0f0(beSvFileMakeApi *);
int igObject_Destroy(RefCountedHeader *);
void Gap__Bec__beSvFileMakeApi__vfunc_08(beSvFileMakeApi *arg0);
}

void Gap__Bec__beSvFileMakeApi__vfunc_08(beSvFileMakeApi *arg0) {
    RefCountedHeader *temp_a0;

    temp_a0 = (RefCountedHeader *)arg0->_saveWork;
    if (temp_a0 != 0) {
        if (temp_a0 != 0) {
            temp_a0->references = temp_a0->references - 1;
            if (((unsigned long long) ((long long) temp_a0->references << 0x29) >> 0x29) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        arg0->_saveWork = 0;
    }
    Gap__Core__igObject__vfunc_08__002ff0f0(arg0);
}
