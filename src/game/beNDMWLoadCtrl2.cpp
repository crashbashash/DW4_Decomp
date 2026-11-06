/* src/game/beNDMWLoadCtrl2.cpp — the beNDMWLoadCtrl2 methods, one translation unit in retail
 * address order: 0x003f19e0 Gap__Bec__beNDMWLoadCtrl2__vfunc_32 lazily acquire the pad manager
 * 0x003f2450 Gap__Bec__beNDMWLoadCtrl2__vfunc_30 info-record class metaObject accessor 0x003f2460
 * Gap__Bec__beNDMWLoadCtrl2__vfunc_29 register the LOADCTRL2 message receiver 0x003f2d40
 * Gap__Bec__beNDMWLoadCtrl2__vfunc_20 class metaObject accessor The retail unit was C++ with
 * exceptions on (every framed function keeps an exception index record). The three methods that
 * used to live in beNDMWLoadCtrl2.c now compile here as C++ under that profile, which also
 * reproduces the records; the whole unit keeps C linkage. MWCC's C++ front end preserves the
 * framed call of the one-call wrapper vfunc_29 where the C front end tail-calls it. The matching
 * build splits a function back out with tools/units.py, so `make check` still verifies one
 * function at a time. */
#include "dw4/reflected.h"
extern "C" {
extern int g_beNDMWLoadCtrl2Info_metaObject[4];
extern int g_beNDMWLoadCtrl2_metaObject[4];
extern int g_bePadManager_metaObject[4];
extern int LOADCTRL2[4];
/* Looks up the insight's object list for the entry whose class metaObject is the
 * second argument (hypothesis: igInsightCore::FindObjectByMetaObject; the matched
 * body is src/unmatched/FUN_00236f80.cpp). */
int FUN_00236f80(int, int);
/* igObject reference release once the count reaches zero (docs/engine/engine-boot.md:
 * "the object-model destructor", igObject_Destroy at 0x002ff820).  Declared and called
 * without its argument: retail's a0 still holds the released object (matching construct). */
int FUN_002ff820();
int beMessenger_RegisterReceiverFromInfo(int, int, int *);
void Gap__Bec__beNDMWLoadCtrl2__vfunc_32(beNDMWLoadCtrl2 *);
int Gap__Bec__beNDMWLoadCtrl2__vfunc_30(void);
void Gap__Bec__beNDMWLoadCtrl2__vfunc_29(beNDMWLoadCtrl2 *, int);
int Gap__Bec__beNDMWLoadCtrl2__vfunc_20(void);
}

/* 0x003f19e0: lazily acquire the pad manager.  The first call finds the bePadManager
 * registered with the insight, takes a reference on it and stores it in _padManager
 * (the generated release of the previous value is the shared smart-pointer idiom of
 * the low 23 bits of _refCount are the count).  The `asm { nop }`
 * statements reproduce retail's delay-slot nops (matching constructs). */
void Gap__Bec__beNDMWLoadCtrl2__vfunc_32(beNDMWLoadCtrl2 *self) {
    igObject *found;
    igObject *previous;
    if (self->_padManager == 0) {
        found = (igObject *)FUN_00236f80(self->_insight, g_bePadManager_metaObject[0]);
        if (found != 0) {
            found->_refCount = found->_refCount + 1;
            asm { nop }
        }
        previous = (igObject *)self->_padManager;
        if (previous != 0) {
            previous->_refCount = previous->_refCount - 1;
            if ((previous->_refCount & 0x7fffff) == 0) {
                FUN_002ff820();
                asm { nop }
            }
        }
        self->_padManager = (int)found;
        asm { nop }
    }
}

/* 0x003f2450: slot 30, class metaObject accessor of the load controller's info record */
int Gap__Bec__beNDMWLoadCtrl2__vfunc_30(void)
{
    return g_beNDMWLoadCtrl2Info_metaObject[0];
}

/* 0x003f2460 — slot 29: register the load controller with its messenger as the
 * receiver named by the "LOADCTRL2" string at 0x00518290 (same
 * wrapper shape as beNDMWTitle2 slot 29). */
void Gap__Bec__beNDMWLoadCtrl2__vfunc_29(beNDMWLoadCtrl2 *self, int info)
{
    beMessenger_RegisterReceiverFromInfo(self->_messenger, info, &LOADCTRL2[0]);
}

/* 0x003f2d40: slot 20, class metaObject accessor (RTTI handle at 0x0058bef0) */
int Gap__Bec__beNDMWLoadCtrl2__vfunc_20(void)
{
    return g_beNDMWLoadCtrl2_metaObject[0];
}
