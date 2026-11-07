/* The beNDMWLoadCtrl2 methods: vfunc_32 lazily acquires the pad manager, vfunc_30 is the info-
 * record class metaObject accessor, vfunc_29 registers the LOADCTRL2 message receiver and vfunc_20
 * is the class metaObject accessor. The unit is C++ with exceptions on, and the whole unit keeps C
 * linkage. The C++ front end preserves the framed call of the one-call wrapper vfunc_29 where the
 * C front end would tail-call it. */
#include "dw4/reflected.h"
extern "C" {
extern int g_beNDMWLoadCtrl2Info_metaObject[4];
extern int g_beNDMWLoadCtrl2_metaObject[4];
extern int g_bePadManager_metaObject[4];
extern int LOADCTRL2[4];
/* Looks up the insight's object list for the entry whose class metaObject is the second argument. */
int FUN_00236f80(int, int);
/* Declared and called without its argument: a0 still holds the released object (matching construct). */
int FUN_002ff820();
int beMessenger_RegisterReceiverFromInfo(int, int, int *);
void Gap__Bec__beNDMWLoadCtrl2__vfunc_32(beNDMWLoadCtrl2 *);
int Gap__Bec__beNDMWLoadCtrl2__vfunc_30(void);
void Gap__Bec__beNDMWLoadCtrl2__vfunc_29(beNDMWLoadCtrl2 *, int);
int Gap__Bec__beNDMWLoadCtrl2__vfunc_20(void);
}

void Gap__Bec__beNDMWLoadCtrl2__vfunc_32(beNDMWLoadCtrl2 *self) {
    igObject *found;
    igObject *previous;
    if (self->_padManager == 0) {
        found = (igObject *)FUN_00236f80(self->_insight, g_bePadManager_metaObject[0]);
        if (found != 0) {
            found->_refCount = found->_refCount + 1;
        }
        previous = (igObject *)self->_padManager;
        if (previous != 0) {
            previous->_refCount = previous->_refCount - 1;
            if ((previous->_refCount & 0x7fffff) == 0) {
                FUN_002ff820();
            }
        }
        self->_padManager = (int)found;
    }
}

int Gap__Bec__beNDMWLoadCtrl2__vfunc_30(void)
{
    return g_beNDMWLoadCtrl2Info_metaObject[0];
}

/* Registers the load controller with its messenger as the receiver named by the "LOADCTRL2" string
 * (same wrapper shape as beNDMWTitle2 slot 29). */
void Gap__Bec__beNDMWLoadCtrl2__vfunc_29(beNDMWLoadCtrl2 *self, int info)
{
    beMessenger_RegisterReceiverFromInfo(self->_messenger, info, &LOADCTRL2[0]);
}

int Gap__Bec__beNDMWLoadCtrl2__vfunc_20(void)
{
    return g_beNDMWLoadCtrl2_metaObject[0];
}
