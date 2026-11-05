#include "dw4/reflected.h"
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
int FUN_00236f80(int, int);
int FUN_004432a0(beNDMWShinkaCtrl *);
int beMessenger_AppendInt(int, int);
int beMessenger_DispatchSelected(int, int *);
int *beMessenger_GetObject(int, int);
int beMessenger_SelectGroup(int, int *);
int beMessenger_SendNamed(int, int *, int *, int, int *);
int igObject_Destroy(igObject *);
extern int DAT_0051d1a8[4];
extern int DAT_0051d1b8[4];
extern int DAT_0051d1c0[4];
extern int DAT_0051d1d0[4];
extern int DAT_0051d1d8[4];
extern int DAT_00588f38[4];
extern int DAT_0058c0a0[4];
void FUN_00443110(beNDMWShinkaCtrl *arg0, int arg1, int arg2) {
    igObject *t;
    igObject *a0;
    arg0->_playerNo = arg2;
    arg0->_messenger = FUN_00236f80(arg1, DAT_00588f38[0]);
    arg0->_gameRam = FUN_00236f80(arg1, DAT_0058c0a0[0]);
    beMessenger_SendNamed(arg0->_messenger, DAT_0051d1a8, DAT_0051d1b8, 0, DAT_0051d1c0);
    t = (igObject *)beMessenger_GetObject(arg0->_messenger, 0);
    if (t != 0) {
        t->_refCount = t->_refCount + 1;
    }
    a0 = (igObject *)arg0->_dBShinka;
    if (a0 != 0) {
        a0->_refCount = a0->_refCount - 1;
        if ((a0->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(a0);
        }
    }
    arg0->_dBShinka = (int)t;
    beMessenger_SelectGroup(arg0->_messenger, DAT_0051d1d0);
    beMessenger_AppendInt(arg0->_messenger, arg2);
    beMessenger_DispatchSelected(arg0->_messenger, DAT_0051d1d8);
    t = (igObject *)beMessenger_GetObject(arg0->_messenger, 0);
    if (t != 0) {
        t->_refCount = t->_refCount + 1;
    }
    a0 = (igObject *)arg0->_playerParameter;
    if (a0 != 0) {
        a0->_refCount = a0->_refCount - 1;
        if ((a0->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(a0);
        }
    }
    arg0->_playerParameter = (int)t;
    FUN_004432a0(arg0);
}
} /* extern "C" */
