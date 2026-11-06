/* Gap__Bec__beNDMWStatusCtrlEquip__vfunc_21 (0x0040ee60, 1852 B): update state machine of the
 * status-screen equip page: state 0 opens the equip select window for the entry code, state 1
 * drives the equip menu (slot select, then the per-slot windows: power socket with three kinds,
 * FUN_003ba760, FUN_003ba260) and state 2/3 close it. Matches under the unit profile (combat
 * -O3,p, exceptions on) with config/SLUS-20836/unit-objects.json 0x0040ee60: emitted
 * {__dt__4RefAFv: 0x0040f6a0, __dt__4RefCFv: 0x0040f620, __dt__4RefDFv: 0x0040f5a0}, duplicates
 * {__dt__4RefBFv: 0x0040ece0}, externals {__dl__FPv: 0x00100610} and the retail exceptions record;
 * the provisional -Cpp_exceptions off override is not needed. Each Ref owns the new window until
 * it has been bound and listed. Levers: the two-way splits on _entCode are SWITCHES (`case 0:
 * default:` first, `case 1:` second), not if/else: the case labels block delay-slot hoisting from
 * the next block and force the `move a0,s0` in the jal slot. Four distinct holder classes (one per
 * stack slot 60/56/52/48, declared A,B,C,D; the compiler emits the destructors in reverse
 * declaration order); B's destructor is the retail copy kept from the previous unit. */
#include "dw4/reflected.h"
extern "C" {
int igObject_GetAllocator(beNDMWStatusCtrlEquip *);
int Memory_GetAllocatorBySelector(int);
igObject *FUN_003b3530(int);
igObject *FUN_003b3900(int);
igObject *FUN_003b5530(int);
igObject *FUN_003ba900(int);
igObject *FUN_003ba760(int);
igObject *FUN_003ba260(int);
void FUN_003f5410(igObject *, const char *, int, const char *, const char *);
void igObject_Destroy(void *);
void beNDMWWindow_BindContext(igObject *, beNDMWStatusCtrlEquip *, int, int, int);
void ObjectList_AppendRetained(beNDMWWindowList *, igObject *);
void beMessenger_SelectReceivers(int, const char *, const char *, int);
void beMessenger_AppendString(int, const char *);
void beMessenger_DispatchSelected(int, const char *);
int beMessenger_GetBool(int, int);
void beNDMWWindow_RunMessageScript(beNDMWStatusCtrlEquip *, const char *, int);
void beNDMWWindow_PlayQueuedModelClose(void);
void beNDMWWindow_ClearQueuedText(beNDMWStatusCtrlEquip *);
void beNDMWWindow_RequestChildrenClose(beNDMWStatusCtrlEquip *);
int beNDMWWindow_PollCloseComplete(void);
extern char DAT_00519a90[], DAT_00519ad0[], DAT_00519ad8[], DAT_00519b30[], DAT_00519b40[], DAT_00519b50[], DAT_00519b60[], DAT_00519b68[], DAT_00519b80[], DAT_00519b90[];
extern int DAT_004cf670[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
}

#define RELEASE_OBJ(o) { \
    if (o) { \
        --(o)->_refCount; \
        if (((unsigned long long)(long long)(int)(o)->_refCount & 0x7fffffULL) == 0) \
            igObject_Destroy(o); \
    } }
#define DEFREF(N) struct N { igObject *p; N(igObject *q) : p(q) {} ~N() { igObject *o = p; RELEASE_OBJ(o) } };
DEFREF(RefA)
DEFREF(RefB)
DEFREF(RefC)
DEFREF(RefD)
#define SELALLOC(fb) (GPR_00554c14 ? (fb) : Memory_GetAllocatorBySelector(DAT_00587110[0]))

extern "C" void Gap__Bec__beNDMWStatusCtrlEquip__vfunc_21(beNDMWStatusCtrlEquip *self)
{
    switch (self->_st0) {
    case 0:
        switch (self->_entCode) {
        case 0:
        default: {
            int a = igObject_GetAllocator(self);
            RefA h(FUN_003b3530(SELALLOC(a)));
            beNDMWWindow_BindContext(h.p, self, self->_insight, self->_playerNo, 30);
            ObjectList_AppendRetained((beNDMWWindowList *)self->_subWindow, h.p);
            break;
        }
        case 1: {
            int a = igObject_GetAllocator(self);
            RefB h(FUN_003b3900(SELALLOC(a)));
            beNDMWWindow_BindContext(h.p, self, self->_insight, self->_playerNo, 0);
            ObjectList_AppendRetained((beNDMWWindowList *)self->_subWindow, h.p);
            break;
        }
        }
        self->_equipMenu = 0;
        self->_st0 = self->_st0 + 1;
        self->_st3 = 0;
        self->_st2 = 0;
        self->_st1 = 0;
        return;
    case 1:
        switch (self->_st1) {
        case 0:
            switch (self->_st2) {
            case 0: {
                const char *a2;
                const char *s1;
                switch (self->_entCode) {
                default:
                    a2 = DAT_00519b80;
                    s1 = DAT_00519ad0;
                    break;
                case 1:
                    a2 = DAT_00519b30;
                    s1 = DAT_00519b40;
                    break;
                }
                beMessenger_SelectReceivers(self->_messenger, DAT_00519a90, a2, 0);
                beMessenger_AppendString(self->_messenger, s1);
                beMessenger_DispatchSelected(self->_messenger, DAT_00519ad8);
                if ((beMessenger_GetBool(self->_messenger, 0) & 0xff) == 1) return;
                {
                int a = igObject_GetAllocator(self);
                RefC h(FUN_003b5530(SELALLOC(a)));
                beNDMWWindow_BindContext(h.p, self, self->_insight, self->_playerNo, 31);
                ObjectList_AppendRetained((beNDMWWindowList *)self->_subWindow, h.p);
                ((beNDMWStatusSelect01 *)h.p)->_startPoint = self->_equipMenu;
                FUN_003f5410(h.p, DAT_00519b50, DAT_004cf670[0], DAT_00519b60, DAT_00519b68);
                }
                self->_nowProcKazu = ((beNDMWWindowList *)self->_subWindow)->_count;
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
            }
            case 1:
                if (self->_retCode != -1)
                    beNDMWWindow_RunMessageScript(self, DAT_00519b90, self->_retCode + 35);
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
                self->_st3 = self->_retCode;
            case 2:
                if (((beNDMWWindowList *)self->_subWindow)->_count == self->_nowProcKazu) {
                    if (self->_retCode == -1) return;
                    if (self->_st3 == self->_retCode) return;
                    self->_st2 = 1;
                    self->_st3 = 0;
                    return;
                }
                if (self->_retCode != -1) self->_equipMenu = self->_retCode;
                switch (self->_retCode) {
                case 0:
                    self->_st1 = 1; self->_st3 = 0; self->_st2 = 0; return;
                case 1:
                    self->_st1 = 2; self->_st3 = 0; self->_st2 = 0; return;
                case 2:
                    self->_st1 = 3; self->_st3 = 0; self->_st2 = 0; return;
                default:
                    self->_st0 = self->_st0 + 1; self->_st3 = 0; self->_st2 = 0; self->_st1 = 0; return;
                }
            }
            break;
        case 1:
        case 2:
        case 3:
            switch (self->_st2) {
            case 0: {
                {
                RefD r(0);
                switch (self->_st1) {
                case 1: {
                    int a = igObject_GetAllocator(self);
                    int al = SELALLOC(a);
                    { igObject *o = r.p; RELEASE_OBJ(o) }
                    r.p = FUN_003ba900(al);
                    ((beNDMWStatusPowerSocket *)r.p)->_kindListMax = 3;
                    break;
                }
                case 2: {
                    int a = igObject_GetAllocator(self);
                    int al = SELALLOC(a);
                    { igObject *o = r.p; RELEASE_OBJ(o) }
                    r.p = FUN_003ba760(al);
                    break;
                }
                case 3: {
                    int a = igObject_GetAllocator(self);
                    int al = SELALLOC(a);
                    { igObject *o = r.p; RELEASE_OBJ(o) }
                    r.p = FUN_003ba260(al);
                    break;
                }
                }
                beNDMWWindow_BindContext(r.p, self, self->_insight, self->_playerNo, 0);
                ObjectList_AppendRetained((beNDMWWindowList *)self->_subWindow, r.p);
                }
                self->_nowProcKazu = ((beNDMWWindowList *)self->_subWindow)->_count;
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
            }
            case 1:
                if (((beNDMWWindowList *)self->_subWindow)->_count != self->_nowProcKazu) {
                    self->_retCode = self->_equipMenu;
                    self->_st1 = 0; self->_st3 = 0; self->_st2 = 0;
                    return;
                }
                break;
            }
            break;
        }
        break;
    case 2:
        beNDMWWindow_PlayQueuedModelClose();
        beNDMWWindow_ClearQueuedText(self);
        beNDMWWindow_RequestChildrenClose(self);
        self->_st0 = self->_st0 + 1;
        self->_st3 = 0; self->_st2 = 0; self->_st1 = 0;
        return;
    case 3:
        if (beNDMWWindow_PollCloseComplete() != 0) self->_isRun = 0;
        break;
    }
}
