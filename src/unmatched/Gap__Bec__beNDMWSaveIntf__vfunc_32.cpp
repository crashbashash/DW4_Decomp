/* reference-counted engine object header: refcount word at +4 */
extern "C" {
typedef struct RefCountedHeader { char pad4[4]; int f4; } RefCountedHeader;
#include "dw4/reflected.h"
RefCountedHeader *FUN_00236f80(int, int);
int igObject_Destroy(RefCountedHeader *);
extern int DAT_00588518[4];
void Gap__Bec__beNDMWSaveIntf__vfunc_32(beNDMWSaveIntf *arg0) {
    RefCountedHeader *temp_a0;
    RefCountedHeader *temp_v0;

    if (arg0->_padManager == 0) {
        temp_v0 = FUN_00236f80(arg0->_insight, DAT_00588518[0]);
        if (temp_v0 != 0) {
            temp_v0->f4 = (int)((int) (temp_v0->f4 + 1));
        }
        temp_a0 = (RefCountedHeader *)arg0->_padManager;
        if (temp_a0 != 0) {
            temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
            if (((unsigned long long) ((long long) temp_a0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        arg0->_padManager = (int)temp_v0;
    }
}
}
