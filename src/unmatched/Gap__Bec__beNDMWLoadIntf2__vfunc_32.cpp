#include "dw4/reflected.h"
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
igObject *FUN_00236f80(int, int);
int igObject_Destroy(igObject *);
extern int DAT_00588518[4];
void Gap__Bec__beNDMWLoadIntf2__vfunc_32(beNDMWLoadIntf2 *arg0) {
    igObject *temp_a0;
    igObject *temp_v0;

    if (arg0->_padManager == 0) {
        temp_v0 = FUN_00236f80(arg0->_insight, DAT_00588518[0]);
        if (temp_v0 != 0) {
            temp_v0->_refCount = (int)temp_v0->_refCount + 1;
        }
        temp_a0 = (igObject *)arg0->_padManager;
        if (temp_a0 != 0) {
            temp_a0->_refCount = (int)temp_a0->_refCount - 1;
            if (((unsigned long long) ((long long) (int)temp_a0->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        arg0->_padManager = (int)temp_v0; /* matching construct: 4-byte reference field stores the object pointer */
    }
}
} /* extern "C" */
