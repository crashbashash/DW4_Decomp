/* Sell-menu state machine. State 0 asks the player's inventory (DEVICEFOLDER / DISKFOLDER record
 * folders) what is sellable: with something to sell it enters branch _st1 = 0 (the ShopSelectB0
 * chooser) and _st3 picks its two-entry decide list (1 = no devices, 2 = no disks); with nothing to
 * sell it enters branch _st1 = 3 (ShopSelect00 with script 0x628). The chooser's _retCode then
 * selects branch 1 (device sell sub-window) or 2 (disk sell sub-window), which return to state 0 when
 * they end. State 2 closes the sub-windows, state 3 waits for the close to finish and clears _isRun.
 * Matching constructs: the state switch reads _st0 through a const accessor so case 0 reloads it;
 * `case 1: case 2:` in that order gives the 2-then-1 compare chain; the decide-list pointers live in
 * stack WindowRef/ListRef holders and are re-read per use; hasDevice/hasDisk are bool. */
#include "dw4/reflected.h"
#include "dw4/igobject_release.h"
extern "C" {
void *FUN_002cb0d0(...);
void *FUN_003b3f40(...);
void *FUN_003b4f50(...);
void *FUN_003b6e60(...);
void *FUN_003b70e0(...);
int List_Resize(...);
void *Memory_GetAllocatorBySelector(...);
int ObjectList_AppendRetained(...);
int beMessenger_AppendInt(...);
int beMessenger_AppendString(...);
int beMessenger_DispatchSelected(...);
int beMessenger_GetObject(...);
int beMessenger_SelectGroup(...);
int beNDMWWindow_BindContext(...);
int beNDMWWindow_ClearQueuedText(...);
int beNDMWWindow_PlayQueuedModelClose(...);
int beNDMWWindow_PollCloseComplete(...);
int beNDMWWindow_RequestChildrenClose(...);
int igObject_Destroy(...);
void *igObject_GetAllocator(...);
static inline int st0(const beNDMWShopCtrlSell *ctrl) { return ctrl->_st0; }
struct Item { int p[5]; int f20; };
struct Rec { int p[3]; igObjectList *f12; };
Rec *igProperty_GetRecordFolder(...);
extern char *DAT_004cf8a0[];
extern char *DAT_004cf8a4[];
extern int DAT_0051b398[4];
extern int DAT_0051b3c0[4];
extern int DAT_0051b3d8[4];
extern int DAT_0051b3e8[4];
extern int DAT_0051b470[4];
extern int DAT_0051b528[4];
extern int DAT_0051b6c0[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554a50;
extern unsigned char GPR_00554a54;
extern unsigned char GPR_00554a58;
extern unsigned char GPR_00554a5c;
extern unsigned char GPR_00554c14;
void Gap__Bec__beNDMWShopCtrlSell__vfunc_21(beNDMWShopCtrlSell *self);
}
/* Owning stack references: kind 0..4 one per window class created here (0 chooser, 1 device sell,
 * 2 disk sell, 4 item window), ListRef the bool decide lists. */
template <int kind> struct WindowRef {
    igObject *p;
    WindowRef(igObject *w) : p(w) {}
    ~WindowRef() { igObject *w = p; if (w != 0) { --w->_refCount; if ((w->_refCount & 0x7fffff) == 0) igObject_Destroy(w); } }
};
struct ListRef {
    igObject *p;
    ListRef(igObject *l) : p(l) {}
    ~ListRef() { igObject *l = p; if (l != 0) { --l->_refCount; if ((l->_refCount & 0x7fffff) == 0) igObject_Destroy(l); } }
};

#define ALLOC(a, self) { \
    a = igObject_GetAllocator(self); \
    a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(DAT_00587110[0]); }

#define RELEASE(p) IG_OBJECT_RELEASE((igObject *)(p));

#define PUSH_BOOL(list, value) { int idx = (list)->_count; \
    if (idx < (list)->_capacity) { (list)->_count = idx + 1; } else { List_Resize(list, idx + 1, 1); } \
    ((unsigned char *)(list)->_data)[idx] = (value); }

void Gap__Bec__beNDMWShopCtrlSell__vfunc_21(beNDMWShopCtrlSell *self) {
    void *alloc;
    igObjectList *devices;
    const igObjectList *disks;
    Item *item;
    bool hasDevice;
    bool hasDisk;
    int i;
    int rec;

    switch (st0(self)) {
    case 0:
        self->_st0 = self->_st0 + 1;
        self->_st3 = 0;
        self->_st2 = 0;
        self->_st1 = 0;
        beMessenger_SelectGroup(self->_messenger, &DAT_0051b398[0]);
        beMessenger_AppendInt(self->_messenger, self->_playerNo);
        beMessenger_DispatchSelected(self->_messenger, &DAT_0051b3e8[0]);
        rec = beMessenger_GetObject(self->_messenger, 0);
        devices = igProperty_GetRecordFolder(rec, &DAT_0051b528[0])->f12;
        disks = igProperty_GetRecordFolder(rec, &DAT_0051b6c0[0])->f12;
        hasDevice = 0;
        if (devices->_count > 0) {
            hasDevice = 1;
        }
        hasDisk = 0;
        for (i = 0; i < disks->_count; i++) {
            item = ((Item **)disks->_data)[i];
            if (item != 0 && item->f20 > 0) {
                hasDisk = 1;
                break;
            }
        }
        if (hasDevice || hasDisk) {
            self->_st1 = 0;
            self->_st3 = 0;
            self->_st2 = 0;
            if (hasDevice == 0) {
                self->_st3 = 1;
            } else if (hasDisk == 0) {
                self->_st3 = 2;
            }
        } else {
            self->_st1 = 3;
            self->_st3 = 0;
            self->_st2 = 0;
        }
    case 1:
        switch (self->_st1) {
        case 0:
            switch (self->_st2) {
            case 0:
                ALLOC(alloc, self)
                {
                WindowRef<0> sp5C((igObject *)FUN_003b3f40(alloc));
                beNDMWWindow_BindContext(sp5C.p, self, self->_insight, self->_playerNo, 0);
                ObjectList_AppendRetained(self->_subWindow, sp5C.p);
                switch (self->_st3) {
                case 1: {
                    ALLOC(alloc, self)
                    ListRef sp58((igObject *)FUN_002cb0d0(alloc));
                    { igBoolList *l = (igBoolList *)sp58.p; PUSH_BOOL(l, GPR_00554a50) }
                    { igBoolList *l = (igBoolList *)sp58.p; PUSH_BOOL(l, GPR_00554a54) }
                    {
                        igBoolList *l = (igBoolList *)sp58.p;
                        beNDMWShopSelect00 *w = (beNDMWShopSelect00 *)sp5C.p;
                        if (l != 0) {
                            l->_refCount = l->_refCount + 1;
                        }
                        {
                            igObject *old = (igObject *)w->_decideList;
                            RELEASE(old)
                        }
                        w->_decideList = (int)l;
                    }
                    break;
                }
                case 2: {
                    ALLOC(alloc, self)
                    ListRef sp54((igObject *)FUN_002cb0d0(alloc));
                    { igBoolList *l = (igBoolList *)sp54.p; PUSH_BOOL(l, GPR_00554a58) }
                    { igBoolList *l = (igBoolList *)sp54.p; PUSH_BOOL(l, GPR_00554a5c) }
                    {
                        igBoolList *l = (igBoolList *)sp54.p;
                        beNDMWShopSelect00 *w = (beNDMWShopSelect00 *)sp5C.p;
                        if (l != 0) {
                            l->_refCount = l->_refCount + 1;
                        }
                        {
                            igObject *old = (igObject *)w->_decideList;
                            RELEASE(old)
                        }
                        w->_decideList = (int)l;
                    }
                    break;
                }
                }
                }
                self->_nowProcKazu = ((beNDMWWindowList *)self->_subWindow)->_count;
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
            case 1:
                if (((beNDMWWindowList *)self->_subWindow)->_count != self->_nowProcKazu) {
                    beMessenger_SelectGroup(self->_messenger, &DAT_0051b3c0[0]);
                    beMessenger_AppendString(self->_messenger, &DAT_0051b470[0]);
                    beMessenger_AppendString(self->_messenger, DAT_004cf8a0[0]);
                    beMessenger_DispatchSelected(self->_messenger, &DAT_0051b3d8[0]);
                    beMessenger_SelectGroup(self->_messenger, &DAT_0051b3c0[0]);
                    beMessenger_AppendString(self->_messenger, &DAT_0051b470[0]);
                    beMessenger_AppendString(self->_messenger, DAT_004cf8a4[0]);
                    beMessenger_DispatchSelected(self->_messenger, &DAT_0051b3d8[0]);
                    switch (self->_retCode) {
                    case 0:
                        self->_st1 = 1;
                        self->_st3 = 0;
                        self->_st2 = 0;
                        return;
                    case 1:
                        self->_st1 = 2;
                        self->_st3 = 0;
                        self->_st2 = 0;
                        return;
                    default:
                        self->_st0 = self->_st0 + 1;
                        self->_st3 = 0;
                        self->_st2 = 0;
                        self->_st1 = 0;
                        return;
                    }
                }
                break;
            }
            break;
        case 1:
        case 2:
            switch (self->_st2) {
            case 0:
                if (self->_st1 == 1) {
                    ALLOC(alloc, self)
                    WindowRef<1> sp50((igObject *)FUN_003b70e0(alloc));
                    beNDMWWindow_BindContext(sp50.p, self, self->_insight, self->_playerNo, 0);
                    ObjectList_AppendRetained(self->_subWindow, sp50.p);
                } else {
                    ALLOC(alloc, self)
                    WindowRef<2> sp4C((igObject *)FUN_003b6e60(alloc));
                    beNDMWWindow_BindContext(sp4C.p, self, self->_insight, self->_playerNo, 0);
                    ObjectList_AppendRetained(self->_subWindow, sp4C.p);
                }
                self->_nowProcKazu = ((beNDMWWindowList *)self->_subWindow)->_count;
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
            case 1:
                if (((beNDMWWindowList *)self->_subWindow)->_count != self->_nowProcKazu) {
                    self->_st0 = 0;
                    self->_st3 = 0;
                    self->_st2 = 0;
                    self->_st1 = 0;
                    return;
                }
                break;
            }
            break;
        case 3:
            switch (self->_st2) {
            case 0:
                ALLOC(alloc, self)
                {
                WindowRef<4> sp48((igObject *)FUN_003b4f50(alloc));
                beNDMWWindow_BindContext(sp48.p, self, self->_insight, self->_playerNo, 0x628);
                ObjectList_AppendRetained(self->_subWindow, sp48.p);
                }
                self->_nowProcKazu = ((beNDMWWindowList *)self->_subWindow)->_count;
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
            case 1:
                if (((beNDMWWindowList *)self->_subWindow)->_count != self->_nowProcKazu) {
                    self->_st0 = self->_st0 + 1;
                    self->_st3 = 0;
                    self->_st2 = 0;
                    self->_st1 = 0;
                    ((beNDMWShopCtrlSell *)self->_mother)->_retCode = -1;
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
        self->_st0 = self->_st0 + 1;
        self->_st3 = 0;
        self->_st2 = 0;
        self->_st1 = 0;
        return;
    case 3:
        if (beNDMWWindow_PollCloseComplete(self) != 0) {
            self->_isRun = 0;
        }
        break;
    }
}
