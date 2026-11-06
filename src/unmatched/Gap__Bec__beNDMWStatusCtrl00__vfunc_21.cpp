/* The window holders are memory-resident stack objects (slots in declaration order w1..w8); each
 * releases its window in its destructor. The offset/index/count loop locals are declared in the
 * order n, i, off with c before them. */
#include "dw4/reflected.h"
typedef igObject Obj;
extern "C" {
void *FUN_003b36f0(void *);
void *FUN_003b3900(void *);
void *FUN_003b3ac0(void *);
void *FUN_003b3c80(void *);
void *FUN_003b56f0(void *);
void *FUN_003b92b0(void *);
void *FUN_003ba030(void *);
void *FUN_003bace0(void *);
int FUN_003f5410(void *, void *, int, void *, void *);
void *Memory_GetAllocatorBySelector(int);
int ObjectList_AppendRetained(int, void *);
int beMessenger_AppendString(int, void *);
int beMessenger_DispatchSelected(int, void *);
int beMessenger_GetBool(int, int);
int beMessenger_SelectGroup(int, void *);
int beMessenger_SelectReceivers(int, void *, void *, int);
int beMessenger_SendNamed(int, void *, void *, int, void *);
int beNDMWWindow_BindContext(void *, void *, int, int, int);
int beNDMWWindow_ClearQueuedText(void *);
int beNDMWWindow_PlayQueuedModelClose(void *);
int beNDMWWindow_PollCloseComplete(void *);
int beNDMWWindow_RequestChildrenClose(void *);
void igObject_Destroy(void *);
void *igObject_GetAllocator(void *);
extern int DAT_004cf670[4];
extern int DAT_00519a90[4];
extern int DAT_00519ac0[4];
extern int DAT_00519ad0[4];
extern int DAT_00519ad8[4];
extern int DAT_00519ae8[4];
extern int DAT_00519af8[4];
extern int DAT_00519b00[4];
extern int DAT_00519b08[4];
extern int DAT_00519b10[4];
extern int DAT_00519b18[4];
extern int DAT_00519b20[4];
extern int DAT_00519b28[4];
extern int DAT_00519b30[4];
extern int DAT_00519b40[4];
extern int DAT_00519b50[4];
extern int DAT_00519b60[4];
extern int DAT_00519b68[4];
extern int DAT_00519b70[4];
extern int DAT_00519b78[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
void Gap__Bec__beNDMWStatusCtrl00__vfunc_21(beNDMWStatusCtrl00 *self);
}

/* Owning reference to a freshly created window: the destructor drops one reference and destroys at
 * zero. Each window kind is its own class, so the compiler emits one destructor per kind. */
struct ObjectRef { Obj *p; ObjectRef(Obj *o) : p(o) {} ~ObjectRef() { Obj *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } } operator Obj *() { return p; } };
template <int K> struct WinRef { Obj *p; WinRef(Obj *o) : p(o) {} ~WinRef() { Obj *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } } operator Obj *() { return p; } };

#define NEWWIN(H, var, ctor, ga) { al = igObject_GetAllocator(ga);  al = GPR_00554c14 ? al : Memory_GetAllocatorBySelector(DAT_00587110[0]);  H var((Obj *)ctor(al));  beNDMWWindow_BindContext(var, self, self->_insight, self->_playerNo, 0);  lst = self->_subWindow;  ObjectList_AppendRetained(lst, var); }
#define GRP(a, b) { beMessenger_SelectGroup(self->_messenger, &DAT_00519ae8[0]);  beMessenger_AppendString(self->_messenger, &a[0]);  beMessenger_AppendString(self->_messenger, &b[0]);  beMessenger_DispatchSelected(self->_messenger, &DAT_00519b08[0]); }
#define NEXT0() { self->_st1 = self->_st1 + 1; self->_st3 = 0; self->_st2 = 0; }
#define FIN(a) { self->_st1 = a; self->_st3 = 0; self->_st2 = 0; }

void Gap__Bec__beNDMWStatusCtrl00__vfunc_21(beNDMWStatusCtrl00 *self) {
    void *al;
    int lst;
    int n;
    beNDMWStatusCtrl00 *c;
    int i;
    int off;
    if (self->_st0 != 3) {
        switch (self->_st0) {
        case 0:
            switch (self->_st1) {
            case 0:
                NEWWIN(WinRef<1>, w1, FUN_003b3c80, self);
                NEXT0();
                return;
            case 1:
                beMessenger_SelectReceivers(self->_messenger, &DAT_00519a90[0], &DAT_00519ac0[0], 0);
                beMessenger_AppendString(self->_messenger, &DAT_00519ad0[0]);
                beMessenger_DispatchSelected(self->_messenger, &DAT_00519ad8[0]);
                if ((beMessenger_GetBool(self->_messenger, 0) & 0xFF) != 1) {
                    GRP(DAT_00519af8, DAT_00519b00);
                    GRP(DAT_00519b10, DAT_00519b00);
                    GRP(DAT_00519b18, DAT_00519b00);
                    GRP(DAT_00519b20, DAT_00519b00);
                    GRP(DAT_00519b28, DAT_00519b00);
                    NEWWIN(WinRef<2>, w2, FUN_003b3ac0, self);
                    NEWWIN(WinRef<3>, w3, FUN_003b3900, self);
                    NEWWIN(ObjectRef, w4, FUN_003b36f0, self);
                    self->_statusMenu = 0;
                    NEXT0();
                    return;
                }
                break;
            case 2:
                beMessenger_SelectReceivers(self->_messenger, &DAT_00519a90[0], &DAT_00519b30[0], 0);
                beMessenger_AppendString(self->_messenger, &DAT_00519b40[0]);
                beMessenger_DispatchSelected(self->_messenger, &DAT_00519ad8[0]);
                if ((beMessenger_GetBool(self->_messenger, 0) & 0xFF) != 1) {
                    self->_st0 = self->_st0 + 1; self->_st3 = 0; self->_st2 = 0; self->_st1 = 0;
                    return;
                }
                break;
            }
            break;
        case 1:
            switch (self->_st1) {
            case 0:
                switch (self->_st2) {
                case 0:
                    {
                        al = igObject_GetAllocator(self);
                        al = GPR_00554c14 ? al : Memory_GetAllocatorBySelector(DAT_00587110[0]);
                        WinRef<4> w5((Obj *)FUN_003b56f0(al));
                        beNDMWWindow_BindContext(w5, self, self->_insight, self->_playerNo, 0);
                        lst = self->_subWindow;
                        ObjectList_AppendRetained(lst, w5);
                        ((beNDMWStatusSelect00 *)w5.p)->_startPoint = self->_statusMenu;
                        FUN_003f5410(w5, &DAT_00519b50[0], DAT_004cf670[0], &DAT_00519b60[0], &DAT_00519b68[0]);
                    }
                    self->_nowProcKazu = ((igObjectList *)self->_subWindow)->_count;
                    self->_st2 = self->_st2 + 1;
                    self->_st3 = 0;
                case 1:
                    self->_st2 = self->_st2 + 1;
                    self->_st3 = 0;
                case 2:
                    if (((igObjectList *)self->_subWindow)->_count != self->_nowProcKazu) {
                        if (self->_retCode != -1) self->_statusMenu = self->_retCode;
                        switch (self->_retCode) {
                        case 0: FIN(1); return;
                        case 1: FIN(2); return;
                        case 2: FIN(3); return;
                        default: FIN(4); return;
                        }
                    }
                    break;
                }
                break;
            case 1:
                switch (self->_st2) {
                case 0:
                    NEWWIN(WinRef<5>, w6, FUN_003bace0, self);
                    self->_nowProcKazu = ((igObjectList *)self->_subWindow)->_count;
                    self->_st2 = self->_st2 + 1; self->_st3 = 0;
                case 1:
                    if (((igObjectList *)self->_subWindow)->_count != self->_nowProcKazu) {
                        FIN(0); return;
                    }
                    break;
                }
                break;
            case 2:
                switch (self->_st2) {
                case 0:
                    NEWWIN(WinRef<6>, w7, FUN_003ba030, self);
                    self->_nowProcKazu = ((igObjectList *)self->_subWindow)->_count;
                    self->_st2 = self->_st2 + 1; self->_st3 = 0;
                case 1:
                    if (((igObjectList *)self->_subWindow)->_count != self->_nowProcKazu) {
                        FIN(0); return;
                    }
                    break;
                }
                break;
            case 3:
                switch (self->_st2) {
                case 0:
                    NEWWIN(WinRef<7>, w8, FUN_003b92b0, self);
                    self->_nowProcKazu = ((igObjectList *)self->_subWindow)->_count;
                    self->_st2 = self->_st2 + 1; self->_st3 = 0;
                case 1:
                    if (((igObjectList *)self->_subWindow)->_count != self->_nowProcKazu) {
                        FIN(0); return;
                    }
                    break;
                }
                break;
            case 4:
                switch (self->_st2) {
                case 0:
                    n = ((igObjectList *)self->_subWindow)->_count;
                    for (i = 1, off = 4; i < n; i++, off += 4) {
                        c = (beNDMWStatusCtrl00 *)((int *)((igObjectList *)self->_subWindow)->_data)[i];
                        if (c->_st0 < 2) { c->_st0 = 2; c->_st3 = 0; c->_st2 = 0; c->_st1 = 0; }
                    }
                    self->_st2 = self->_st2 + 1; self->_st3 = 0;
                    return;
                case 1:
                    beMessenger_SendNamed(self->_messenger, &DAT_00519a90[0], &DAT_00519b30[0], 0, &DAT_00519b70[0]);
                    if ((beMessenger_GetBool(self->_messenger, 0) & 0xFF) != 1) {
                        GRP(DAT_00519af8, DAT_00519b78);
                        GRP(DAT_00519b10, DAT_00519b78);
                        GRP(DAT_00519b18, DAT_00519b78);
                        GRP(DAT_00519b20, DAT_00519b78);
                        GRP(DAT_00519b28, DAT_00519b78);
                        self->_st0 = self->_st0 + 1; self->_st3 = 0; self->_st2 = 0; self->_st1 = 0;
                        return;
                    }
                    break;
                }
                break;
            }
            break;
        case 2:
            beNDMWWindow_PlayQueuedModelClose(self);
            beNDMWWindow_ClearQueuedText(self);
            beNDMWWindow_RequestChildrenClose(self);
            self->_st0 = self->_st0 + 1; self->_st3 = 0; self->_st2 = 0; self->_st1 = 0;
            return;
        }
    } else if (beNDMWWindow_PollCloseComplete(self) != 0) {
        self->_isRun = 0;
    }
}
