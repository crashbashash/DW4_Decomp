#include "dw4/reflected.h"
extern "C" {
void *FUN_00236f80(...);
int igObject_IsKindOf(...);
int beLua__RunNamedChunk(...);
void *FUN_003a9310(...);
void *FUN_003b31b0(...);
void *FUN_003b3370(...);
void *FUN_003b36f0(...);
void *FUN_003b4950(...);
void *FUN_003b4b10(...);
void *FUN_003b8860(...);
void *FUN_003bace0(...);
int FUN_00425e60(...);
int FUN_004329d0(...);
int FUN_00432c90(...);
int FUN_00432d30(...);
int FUN_00433120(...);
int FUN_00433290(...);
int List_Resize(...);
void *Memory_GetAllocatorBySelector(...);
int ObjectList_AppendRetained(...);
int StringChunk_ReleaseHeader(...);
int beMessenger_AppendInt(...);
int beMessenger_AppendString(...);
int beMessenger_DispatchSelected(...);
unsigned char beMessenger_GetBool(...);
int beMessenger_GetObject(...);
int beMessenger_SelectGroup(...);
int beMessenger_SelectReceivers(...);
int beMessenger_SendNamed(...);
int beNDMWWindow_BindContext(...);
int beNDMWWindow_ClearQueuedText(...);
int beNDMWWindow_PlayQueuedModelClose(...);
int beNDMWWindow_PollCloseComplete(...);
int beNDMWWindow_PresentModelAtOrigin(...);
int beNDMWWindow_RequestChildrenClose(...);
int igObject_Destroy(...);
void *igObject_GetAllocator(...);
extern int DAT_0051b308[4];
extern int DAT_0051b318[4];
extern int DAT_0051b328[4];
extern int DAT_0051b338[4];
extern int DAT_0051b348[4];
extern int DAT_0051b358[4];
extern int DAT_0051b398[4];
extern int DAT_0051b3e8[4];
extern int DAT_0051b7e0[4];
extern int DAT_0051b868[4];
extern int DAT_0051ba28[4];
extern int DAT_0051bbb0[4];
extern int DAT_0051bbc0[4];
extern int DAT_0051bbd0[4];
extern int DAT_0051bbe8[4];
extern int DAT_00587110[4];
extern int DAT_00587d08[4];
extern int DAT_00589208[4];
extern int DAT_0058ab68[4];
extern unsigned char GPR_00554c14;

void Gap__Bec__beNDMWShopCtrlDigilabo__vfunc_21(beNDMWShopCtrlDigilabo *self);
}

#define ALLOC(a, self) { a = igObject_GetAllocator(self); a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(DAT_00587110[0]); }

struct Rec12 { char p[12]; int f12; };
/* Owning reference to a freshly created window: the destructor drops one reference and destroys at
 * zero. One class per window kind, since the compiler emits one out-of-line destructor per class. */
template <int K> struct WindowRef { igObject *p; WindowRef(igObject *o) : p(o) {} ~WindowRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } } operator igObject *() { return p; } };
/* Owning reference to an interned string token (reference count at p[-1], chunk header at p[-2]). */
struct StringRef { char *p; StringRef(char *s) : p(s) {} ~StringRef() { char *s = p; if (s != 0) { int *hd = (int *)s - 2; int cnt = ((int *)s)[-1] - 1; ((int *)s)[-1] = cnt; if (cnt == 0) StringChunk_ReleaseHeader(*hd, hd); } } };
/* The copied token is returned through a hidden result pointer. */
extern "C" StringRef StringList_CopyRetained(int list, int index);

#define SUBN(self) (((igObjectList *)(self)->_subWindow)->_count)
#define PLN(self) (((igIntList *)(self)->_playerNoList)->_count)
#define PL(self, i) (((int *)((igIntList *)(self)->_playerNoList)->_data)[i])

void Gap__Bec__beNDMWShopCtrlDigilabo__vfunc_21(beNDMWShopCtrlDigilabo *self) {
    void *alloc;
    igObject *found;
    int i;
    int j;
    int idx;
    int *src;
    igIntList *l;
    igIntList *pl;

    switch (self->_st0) {
    default:
        return;
    case 0:
        self->_isDigimonChange = 0;
        self->_isWeaponChange = 0;
        FUN_004329d0(self);
        ALLOC(alloc, self)
        {
            WindowRef<1> spAC((igObject *)FUN_003b3370(alloc));
        beNDMWWindow_BindContext(spAC.p, self, self->_insight, self->_playerNo, 0);
        ObjectList_AppendRetained(self->_subWindow, spAC.p);
        }
        ALLOC(alloc, self)
        {
            WindowRef<2> spA8((igObject *)FUN_003b36f0(alloc));
        beNDMWWindow_BindContext(spA8.p, self, self->_insight, self->_playerNo, 0);
        ObjectList_AppendRetained(self->_subWindow, spA8.p);
        }
        ALLOC(alloc, self)
        {
            WindowRef<3> spA4((igObject *)FUN_003b31b0(alloc));
        beNDMWWindow_BindContext(spA4.p, self, self->_insight, self->_playerNo, self->_entCode);
        ObjectList_AppendRetained(self->_subWindow, spA4.p);
        }
        self->_st0 = self->_st0 + 1;
        self->_st3 = 0;
        self->_st2 = 0;
        self->_st1 = 0;
    case 1:
        switch (self->_st1) {
        case 0:
            switch (self->_st2) {
            case 0:
                FUN_00433290(self);
                FUN_00433120(self, self->_playerNo, 0);
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
                return;
            case 1:
                beMessenger_SelectReceivers(self->_messenger, &DAT_0051b308[0], &DAT_0051b318[0], 0);
                beMessenger_AppendString(self->_messenger, &DAT_0051b868[0]);
                beMessenger_DispatchSelected(self->_messenger, &DAT_0051b338[0]);
                if (beMessenger_GetBool(self->_messenger, 0) != 1) {
                    ALLOC(alloc, self)
                    {
                        WindowRef<4> spA0((igObject *)FUN_003b4b10(alloc));
                    beNDMWWindow_BindContext(spA0.p, self, self->_insight, self->_playerNo, PLN(self));
                    ObjectList_AppendRetained(self->_subWindow, spA0.p);
                    }
                    self->_nowProcKazu = SUBN(self);
                    self->_st2 = self->_st2 + 1;
                    self->_st3 = 0;
                }
                break;
            case 2:
                if (SUBN(self) != self->_nowProcKazu) {
                    switch (self->_retCode) {
                    case 0:
                        self->_st1 = 1;
                        self->_st3 = 0;
                        self->_st2 = 0;
                        break;
                    case 1:
                        self->_st1 = 2;
                        self->_st3 = 0;
                        self->_st2 = 0;
                        break;
                    case 2:
                        if (PLN(self) == 1) {
                            self->_st1 = 6;
                            self->_st3 = 0;
                            self->_st2 = 0;
                        } else {
                            self->_st1 = 5;
                            self->_st3 = 0;
                            self->_st2 = 0;
                        }
                        break;
                    default:
                    case 3:
                        self->_st1 = 6;
                        self->_st3 = 0;
                        self->_st2 = 0;
                        break;
                    }
                    self->_topMenu = self->_retCode;
                    return;
                }
                break;
            }
            break;
        case 1:
            switch (self->_st2) {
            case 0:
                ALLOC(alloc, self)
                {
                    WindowRef<5> sp9C((igObject *)FUN_003b8860(alloc));
                beNDMWWindow_BindContext(sp9C.p, self, self->_insight, self->_playerNo, 0);
                ObjectList_AppendRetained(self->_subWindow, sp9C.p);
                }
                self->_nowProcKazu = SUBN(self);
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
            case 1:
                if (SUBN(self) != self->_nowProcKazu) {
                    switch (self->_retCode) {
                    case 1:
                        self->_isDigimonChange = 1;
                        self->_st1 = 3;
                        self->_st3 = 0;
                        self->_st2 = 0;
                        break;
                    default:
                        self->_st1 = 0;
                        self->_st3 = 0;
                        self->_st2 = 0;
                        break;
                    }
                    FUN_00433290(self);
                    return;
                }
                break;
            }
            break;
        case 2:
            switch (self->_st2) {
            case 0:
                found = 0;
                i = 0;
                if (0 < SUBN(self)) {
                    do {
                        igObject *e = (igObject *)((int *)((igObjectList *)(*(volatile int *)&self->_subWindow) /* matching construct: forces the reload retail makes */)->_data)[i];
                        if (e != 0 && igObject_IsKindOf(e, DAT_0058ab68[0]) != 0) {
                            found = e;
                        } else {
                            found = 0;
                        }
                        if (found != 0) break;
                        i += 1;
                    } while (i < SUBN(self));
                }
                if (found != 0) {
                    ((beNDMWStatusTitle01 *)found)->_playerNo = self->_playerNo;
                    FUN_00425e60(found);
                }
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
                return;
            case 1:
                ALLOC(alloc, self)
                {
                    WindowRef<6> sp98((igObject *)FUN_003bace0(alloc));
                beNDMWWindow_BindContext(sp98.p, self, self->_insight, self->_playerNo, 1);
                ObjectList_AppendRetained(self->_subWindow, sp98.p);
                beNDMWWindow_PresentModelAtOrigin(sp98.p, &DAT_0051b318[0], 0, &DAT_0051b328[0], &DAT_0051ba28[0]);
                }
                self->_nowProcKazu = SUBN(self);
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
            case 2:
                if (SUBN(self) != self->_nowProcKazu) {
                    switch (self->_retCode) {
                    case 100:
                        self->_isWeaponChange = 1;
                        break;
                    }
                    self->_st1 = 0;
                    self->_st3 = 0;
                    self->_st2 = 0;
                    FUN_00433290(self);
                    return;
                }
                break;
            }
            break;
        case 3:
            switch (self->_st2) {
            case 0:
                beMessenger_SelectReceivers(self->_messenger, &DAT_0051b308[0], &DAT_0051b318[0], 0);
                beMessenger_AppendString(self->_messenger, &DAT_0051b868[0]);
                beMessenger_DispatchSelected(self->_messenger, &DAT_0051b338[0]);
                if (beMessenger_GetBool(self->_messenger, 0) == 1) break;
                {
                    ALLOC(alloc, self)
                    {
                        WindowRef<7> sp94((igObject *)FUN_003b4950(alloc));
                    beNDMWWindow_BindContext(sp94.p, self, self->_insight, self->_playerNo, 0x4ED);
                    ObjectList_AppendRetained(self->_subWindow, sp94.p);
                    }
                    self->_nowProcKazu = SUBN(self);
                    self->_st2 = self->_st2 + 1;
                    self->_st3 = 0;
                }
            case 1:
                if (SUBN(self) == self->_nowProcKazu) break;
                {
                    ALLOC(alloc, self)
                    {
                        WindowRef<4> sp90((igObject *)FUN_003b4b10(alloc));
                    beNDMWWindow_BindContext(sp90.p, self, self->_insight, self->_playerNo, 0x4EE);
                    ObjectList_AppendRetained(self->_subWindow, sp90.p);
                    }
                    self->_nowProcKazu = SUBN(self);
                    self->_st2 = self->_st2 + 1;
                    self->_st3 = 0;
                }
            case 2:
                if (SUBN(self) == self->_nowProcKazu) break;
                {
                    switch (self->_retCode) {
                    case 0:
                        self->_st1 = 2;
                        self->_st3 = 0;
                        self->_st2 = 0;
                        return;
                    default:
                        self->_st1 = 0;
                        self->_st3 = 0;
                        self->_st2 = 0;
                        return;
                    }
                }
                break;
            }
            break;
        case 5:
            switch (self->_st2) {
            case 0:
                if (1 < PLN(self)) {
                    ALLOC(alloc, self)
                    {
                        WindowRef<7> sp8C((igObject *)FUN_003b4950(alloc));
                    beNDMWWindow_BindContext(sp8C.p, self, self->_insight, self->_playerNo, 0x4E2);
                    ObjectList_AppendRetained(self->_subWindow, sp8C.p);
                    }
                    self->_nowProcKazu = SUBN(self);
                    self->_st2 = self->_st2 + 1;
                    self->_st3 = 0;
                    return;
                }
                self->_st1 = 0;
                self->_st3 = 0;
                self->_st2 = 0;
                return;
            case 1:
                if (SUBN(self) == self->_nowProcKazu) break;
                {
                    ALLOC(alloc, self)
                    {
                        WindowRef<4> sp88((igObject *)FUN_003b4b10(alloc));
                    beNDMWWindow_BindContext(sp88.p, self, self->_insight, self->_playerNo, -1);
                    ObjectList_AppendRetained(self->_subWindow, sp88.p);
                    pl = (igIntList *)self->_playerNoList;
                    j = 0;
                    if (0 < pl->_count) {
                        do {
                            src = &((int *)pl->_data)[j];
                            l = (igIntList *)((beNDMWShopSelect02 *)sp88.p)->_playerNoList;
                            idx = l->_count;
                            if (idx < l->_capacity) {
                                (*(volatile int *)&l->_count)++; /* matching construct: retail reloads the count */
                            } else {
                                List_Resize(l, idx + 1, 4);
                            }
                            j += 1;
                            ((int *)l->_data)[idx] = *src;
                            pl = (igIntList *)self->_playerNoList;
                        } while (j < pl->_count);
                    }
                    }
                    self->_nowProcKazu = SUBN(self);
                    self->_st2 = self->_st2 + 1;
                    self->_st3 = 0;
                }
            case 2:
                if (SUBN(self) != self->_nowProcKazu) {
                    switch (self->_retCode) {
                    default:
                        self->_playerNo = PL(self, self->_retCode);
                        self->_st1 = 0;
                        self->_st3 = 0;
                        self->_st2 = 0;
                        return;
                    case -1:
                        self->_st1 = 0;
                        self->_st3 = 0;
                        self->_st2 = 0;
                        return;
                    }
                }
                break;
            }
            break;
        case 6:
            switch (self->_st2) {
            case 0:
                if (FUN_00432d30(self) != 0) {
                    self->_st2 = 2;
                    self->_st3 = 0;
                    return;
                }
                ALLOC(alloc, self)
                {
                    WindowRef<7> sp84((igObject *)FUN_003b4950(alloc));
                beNDMWWindow_BindContext(sp84.p, self, self->_insight, self->_playerNo, 0x4FB);
                ObjectList_AppendRetained(self->_subWindow, sp84.p);
                }
                self->_nowProcKazu = SUBN(self);
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
                FUN_00432c90(self);
                int k = 0;
                if (0 < PLN(self)) {
                    do {
                        beMessenger_SelectGroup(self->_messenger, &DAT_0051b398[0]);
                        beMessenger_AppendInt(self->_messenger, PL(self, k));
                        beMessenger_DispatchSelected(self->_messenger, &DAT_0051b3e8[0]);
                        /* matching construct: the copied token is an expression temporary; a named local would take a higher stack slot than retail's */
                        beMessenger_SendNamed(self->_messenger, &DAT_0051bbc0[0], StringList_CopyRetained(((Rec12 *)FUN_003a9310(beMessenger_GetObject(self->_messenger, 0), &DAT_0051bbb0[0]))->f12, 0).p, PL(self, k), &DAT_0051b7e0[0]);
                        k += 1;
                    } while (k < PLN(self));
                }
                break;
            case 1:
                if (SUBN(self) != self->_nowProcKazu) {
                    self->_st0 = self->_st0 + 1;
                    self->_st3 = 0;
                    self->_st2 = 0;
                    self->_st1 = 0;
                }
                break;
            case 2:
                ALLOC(alloc, self)
                {
                    WindowRef<7> sp80((igObject *)FUN_003b4950(alloc));
                beNDMWWindow_BindContext(sp80.p, self, self->_insight, self->_playerNo, 0x4F3);
                ObjectList_AppendRetained(self->_subWindow, sp80.p);
                }
                self->_nowProcKazu = SUBN(self);
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
            case 3:
                if (SUBN(self) == self->_nowProcKazu) break;
                {
                    ALLOC(alloc, self)
                    {
                        WindowRef<4> sp7C((igObject *)FUN_003b4b10(alloc));
                    beNDMWWindow_BindContext(sp7C.p, self, self->_insight, self->_playerNo, 0x4F4);
                    ObjectList_AppendRetained(self->_subWindow, sp7C.p);
                    }
                    self->_nowProcKazu = SUBN(self);
                    self->_st2 = self->_st2 + 1;
                    self->_st3 = 0;
                }
            case 4:
                if (SUBN(self) != self->_nowProcKazu) {
                    switch (self->_retCode) {
                    case 0:
                        self->_st2 = self->_st2 + 1;
                        self->_st3 = 0;
                        ((beSystem *)FUN_00236f80(self->_insight, DAT_00587d08[0]))->_isSResetEnable = 0;
                        break;
                    default:
                        self->_st1 = 5;
                        self->_st3 = 0;
                        self->_st2 = 0;
                        break;
                    }
                }
                break;
            case 5:
                FUN_00432c90(self);
                self->_isDemoRun = 1;
                self->_st0 = self->_st0 + 1;
                self->_st3 = 0;
                self->_st2 = 0;
                self->_st1 = 0;
                break;
            }
            break;
        }
        break;
    case 2:
        beMessenger_SendNamed(self->_messenger, &DAT_0051b308[0], &DAT_0051b348[0], 0, &DAT_0051b358[0]);
        beNDMWWindow_PlayQueuedModelClose(self);
        beNDMWWindow_ClearQueuedText(self);
        beNDMWWindow_RequestChildrenClose(self);
        self->_st0 = self->_st0 + 1;
        self->_st3 = 0;
        self->_st2 = 0;
        self->_st1 = 0;
        if (self->_isDemoRun != 0) {
            beLua__RunNamedChunk(FUN_00236f80(self->_insight, DAT_00589208[0]), &DAT_0051bbd0[0], &DAT_0051bbe8[0]);
            return;
        }
        break;
    case 3:
        if (beNDMWWindow_PollCloseComplete() != 0) {
            self->_isRun = 0;
        }
        break;
    }
}
