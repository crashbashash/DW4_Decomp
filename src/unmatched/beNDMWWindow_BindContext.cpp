#include "dw4/reflected.h"
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
int FUN_00236f80(int, int);
int igObject_Destroy(igObject *);
extern int DAT_00588518[4];
extern int DAT_00588f38[4];
/* igObject header: vtable, packed refcount */
void beNDMWWindow_BindContext(beNDMWWindow *arg0, igObject *arg1, int arg2, int arg3, int arg4) {
    igObject *t;

    if (arg1 != 0) {
        arg1->_refCount = arg1->_refCount + 1;
    }
    t = (igObject *)arg0->_mother;
    if (t != 0) {
        t->_refCount = t->_refCount - 1;
        if ((t->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(t);
        }
    }
    arg0->_mother = (int)arg1;
    arg0->_insight = arg2;
    arg0->_messenger = FUN_00236f80(arg2, DAT_00588f38[0]);
    arg0->_padManager = FUN_00236f80(arg2, DAT_00588518[0]);
    arg0->_playerNo = arg3;
    arg0->_entCode = arg4;
}
} /* extern "C" */
