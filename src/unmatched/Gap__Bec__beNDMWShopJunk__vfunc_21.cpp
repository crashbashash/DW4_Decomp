#include "dw4/reflected.h"
extern "C" {
void *FUN_003b4d90(void *);
void *FUN_003b4f50(void *);
void *FUN_003b6bc0(void *);
void *FUN_003b7520(void *);
void *FUN_002cb0d0(void *);
void *FUN_00236f80(int, int);
int beLua__RunNamedChunk(void *, int *, int *);
void *Memory_GetAllocatorBySelector(int);
int ObjectList_AppendRetained(unsigned, void *);
int beNDMWWindow_BindContext(void *, void *, int, int, int);
int beNDMWWindow_ClearQueuedText(void *);
int beNDMWWindow_PlayQueuedModelClose(void *);
int beNDMWWindow_PollCloseComplete(void *);
int beNDMWWindow_RequestChildrenClose(void *);
void igObject_Destroy(void *);
void *igObject_GetAllocator(void *);
int List_Resize(void *, int, int);
typedef igObject Rc;
struct Rec { int pad[3]; int f12; };
struct P { int pad[3]; igIntList *f12; };
int beMessenger_SelectGroup(int, int *);
int beMessenger_AppendInt(int, int);
int beMessenger_AppendString(int, const char *);
int beMessenger_DispatchSelected(int, int *);
int beMessenger_GetObjectCount(int);
Rc *beMessenger_GetObject(int, int);
int beMessenger_GetInt(int, int);
int beMessenger_SendGroup(int, int *, int *);
P *FUN_003a9250(void *, int *);
Rec *igProperty_GetRecord(void *, int *);
extern int DAT_00587110[4];
extern int DAT_0051b398[4];
extern int DAT_0051b3c0[4];
extern int DAT_0051b3d8[4];
extern int DAT_0051b3e8[4];
extern int DAT_0051b470[4];
extern int DAT_0051b498[4];
extern int DAT_0051b4a0[4];
extern int DAT_0051b560[4];
extern int DAT_0051b7f0[4];
extern int DAT_0051b800[4];
extern int DAT_0051b810[4];
extern int DAT_0051b820[4];
extern int DAT_0051b828[4];
extern int DAT_0051b838[4];
extern const char *DAT_004cf8a0[];
struct Tbl { int v[10]; };
extern Tbl DAT_004cf9c0;
extern int DAT_00589208[4];
extern unsigned char GPR_00554c14;
extern unsigned char GPR_00554a38;
extern unsigned char GPR_00554a3c;
extern unsigned char GPR_00554a40;
extern unsigned char GPR_00554a44;
extern unsigned char GPR_00554a48;
}
struct Lst { int pad[2]; int cnt; };
/* Scope holder for a freshly built window or list: its destructor releases the reference. One
 * class per kind (0..4), so each gets its own out-of-line destructor. */
template <int kind> struct RP {
    Rc *p;
    RP(Rc *x) { p = x; }
    ~RP() { Rc *o = p; if (o != 0) { o->_refCount = o->_refCount - 1; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
    operator Rc *() { return p; }
};
#define REL(o) { Rc *rr = (o); if (rr != 0) { rr->_refCount = (int)rr->_refCount - 1; if (((unsigned long long)((long long)(int)rr->_refCount << 0x29) >> 0x29) == 0) { igObject_Destroy(rr); } } }
#define PUSHB(lp, v) { igBoolList *L = (igBoolList *)(lp); int n = L->_count; if (n < L->_capacity) L->_count = n + 1; else List_Resize(L, n + 1, 1); n[(unsigned char *)L->_data] = (v); }
extern "C" void Gap__Bec__beNDMWShopJunk__vfunc_21(beNDMWShopJunk *arg0) {
    void *alloc;
    Tbl sp50;
    switch (arg0->_st0) {
    case 0:
        beMessenger_SelectGroup(arg0->_messenger, DAT_0051b498);
        beMessenger_AppendInt(arg0->_messenger, 9);
        beMessenger_DispatchSelected(arg0->_messenger, DAT_0051b7f0);
        if (beMessenger_GetObjectCount(arg0->_messenger) > 0) {
            Rc *o = beMessenger_GetObject(arg0->_messenger, 0);
            if (o != 0) o->_refCount = (int)o->_refCount + 1;
            { Rc *t = (Rc *)arg0->_junkItemList; REL(t) }
            arg0->_junkItemList = (int)o;
            arg0->_totalGift = beMessenger_GetInt(arg0->_messenger, 1);
        }
        arg0->_st0 = ((volatile beNDMWShopJunk *)arg0)->_st0 + 1;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        arg0->_st1 = 0;
        arg0->_st1 = 0;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
    case 1:
        switch (arg0->_st1) {
        case 0:
            switch (arg0->_st2) {
            case 0:
                alloc = igObject_GetAllocator(arg0);
                alloc = GPR_00554c14 ? alloc : Memory_GetAllocatorBySelector(DAT_00587110[0]);
                {
                RP<0> sp8C((Rc *)FUN_003b4d90(alloc));
                beNDMWWindow_BindContext(sp8C, arg0, arg0->_insight, arg0->_playerNo, 0x79e);
                ObjectList_AppendRetained((unsigned)arg0->_subWindow, sp8C);
                ((beNDMWShopSelect01 *)sp8C.p)->_startPoint = arg0->_junkMenu;
                alloc = igObject_GetAllocator(arg0);
                alloc = GPR_00554c14 ? alloc : Memory_GetAllocatorBySelector(DAT_00587110[0]);
                RP<1> sp88((Rc *)FUN_002cb0d0(alloc));

                if (arg0->_totalGift >= 3956000) {
                    PUSHB(sp88.p, GPR_00554a38)
                } else {
                    PUSHB(sp88.p, GPR_00554a3c)
                }
                if (((igObjectList *)arg0->_junkItemList)->_count <= 0) {
                    PUSHB(sp88.p, GPR_00554a40)
                } else {
                    PUSHB(sp88.p, GPR_00554a44)
                }
                PUSHB(sp88.p, GPR_00554a48)
                int i;
                Rc *src;
                {
                    for (i = 0; (src = sp88.p, i < ((igBoolList *)src)->_count); i++) {
                        beMessenger_SelectGroup(arg0->_messenger, DAT_0051b3c0);
                        beMessenger_AppendString(arg0->_messenger, (const char *)DAT_0051b470);
                        beMessenger_AppendString(arg0->_messenger, DAT_004cf8a0[i]);
                        if (*(unsigned char *)(((igBoolList *)sp88.p)->_data + i) != 0) {
                            beMessenger_DispatchSelected(arg0->_messenger, DAT_0051b3d8);
                        } else {
                            beMessenger_DispatchSelected(arg0->_messenger, DAT_0051b800);
                        }
                    }
                }
                {
                    beNDMWShopSelect01 *dst = (beNDMWShopSelect01 *)sp8C.p;
                    if (src != 0) src->_refCount = (int)src->_refCount + 1;
                    { Rc *t = (Rc *)dst->_decideList; REL(t) }
                    dst->_decideList = (int)src;
                }
                }
                arg0->_nowProcKazu = ((beNDMWWindowList *)arg0->_subWindow)->_count;
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;
            case 1:
                if (((beNDMWWindowList *)arg0->_subWindow)->_count != arg0->_nowProcKazu) {
                    {
                        int i = 0;
                        const char **q = DAT_004cf8a0;
                        do {
                            beMessenger_SelectGroup(arg0->_messenger, DAT_0051b3c0);
                            beMessenger_AppendString(arg0->_messenger, (const char *)DAT_0051b470);
                            beMessenger_AppendString(arg0->_messenger, DAT_004cf8a0[i]);
                            beMessenger_DispatchSelected(arg0->_messenger, DAT_0051b3d8);
                            i++;
                            q++;
                        } while (i < 3);
                    }
                    switch (arg0->_retCode) {
                    case 0:
                        arg0->_junkMenu = 0;
                        arg0->_st1 = 1;
                        arg0->_st3 = 0;
                        arg0->_st2 = 0;
                        return;
                    case 1:
                        arg0->_junkMenu = 1;
                        arg0->_st1 = 2;
                        arg0->_st3 = 0;
                        arg0->_st2 = 0;
                        return;
                    default:
                    case 2:
                        arg0->_st0 = arg0->_st0 + 1;
                        arg0->_st3 = 0;
                        arg0->_st2 = 0;
                        arg0->_st1 = 0;
                        return;
                    }
                }
                break;
            }
            break;
        case 1:
            switch (arg0->_st2) {
            case 0:
                alloc = igObject_GetAllocator(arg0);
                alloc = GPR_00554c14 ? alloc : Memory_GetAllocatorBySelector(DAT_00587110[0]);
                {
                RP<2> sp84((Rc *)FUN_003b7520(alloc));
                beNDMWWindow_BindContext(sp84, arg0, arg0->_insight, arg0->_playerNo, 2);
                ObjectList_AppendRetained((unsigned)arg0->_subWindow, sp84);
                }
                arg0->_nowProcKazu = ((beNDMWWindowList *)arg0->_subWindow)->_count;
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;
            case 1:
                if (((beNDMWWindowList *)arg0->_subWindow)->_count != arg0->_nowProcKazu) {
                    if (arg0->_retCode != -1) {
                        igIntList *l;
                        beMessenger_SendGroup(arg0->_messenger, DAT_0051b398, DAT_0051b810);
                        l = FUN_003a9250(beMessenger_GetObject(arg0->_messenger, 0), DAT_0051b820)->f12;
                        {
                            int c = l->_count;
                            int *p = &((int *)l->_data)[1];
                            int v = *p + (int)arg0->_retCode;
                            if (c != 0 && c > 1) *p = v;
                        }
                        beMessenger_SelectGroup(arg0->_messenger, DAT_0051b398);
                        beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
                        beMessenger_DispatchSelected(arg0->_messenger, DAT_0051b3e8);
                        {
                            Rc *o = beMessenger_GetObject(arg0->_messenger, 0);
                            int s = igProperty_GetRecord(o, DAT_0051b560)->f12 - arg0->_retCode;
                            igProperty_GetRecord(o, DAT_0051b560)->f12 = s;
                        }
                        beMessenger_SelectGroup(arg0->_messenger, DAT_0051b498);
                        beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
                        beMessenger_DispatchSelected(arg0->_messenger, DAT_0051b4a0);
                        arg0->_st1 = 0;
                        arg0->_st3 = 0;
                        arg0->_st2 = 0;
                        {
                            int *p;
                            sp50 = DAT_004cf9c0;
                            p = sp50.v;
                            if (*p != -1) {
                                do {
                                    if (arg0->_totalGift < *p && !(((int *)l->_data)[1] < *p)) {
                                        beLua__RunNamedChunk(FUN_00236f80(arg0->_insight, DAT_00589208[0]), DAT_0051b828, DAT_0051b838);
                                        arg0->_st1 = 3;
                                        arg0->_st3 = 0;
                                        arg0->_st2 = 0;
                                        return;
                                    }
                                    p++;
                                } while (*p != -1);
                            }
                        }
                    } else {
                        arg0->_st1 = 0;
                        arg0->_st3 = 0;
                        arg0->_st2 = 0;
                        return;
                    }
                }
                break;
            }
            break;
        case 2:
            switch (arg0->_st2) {
            case 0:
                alloc = igObject_GetAllocator(arg0);
                alloc = GPR_00554c14 ? alloc : Memory_GetAllocatorBySelector(DAT_00587110[0]);
                {
                RP<3> sp80((Rc *)FUN_003b6bc0(alloc));
                beNDMWWindow_BindContext(sp80, arg0, arg0->_insight, arg0->_playerNo, 9);
                ObjectList_AppendRetained((unsigned)arg0->_subWindow, sp80);
                }
                arg0->_nowProcKazu = ((beNDMWWindowList *)arg0->_subWindow)->_count;
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;
            case 1:
                if (((beNDMWWindowList *)arg0->_subWindow)->_count != arg0->_nowProcKazu) {
                    arg0->_st1 = 0;
                    arg0->_st3 = 0;
                    arg0->_st2 = 0;
                    return;
                }
                break;
            }
            break;
        case 3:
            switch (arg0->_st2) {
            case 0:
                alloc = igObject_GetAllocator(arg0);
                alloc = GPR_00554c14 ? alloc : Memory_GetAllocatorBySelector(DAT_00587110[0]);
                {
                RP<4> sp7C((Rc *)FUN_003b4f50(alloc));
                beNDMWWindow_BindContext(sp7C, arg0, arg0->_insight, arg0->_playerNo, 0x7b2);
                ObjectList_AppendRetained((unsigned)arg0->_subWindow, sp7C);
                }
                arg0->_nowProcKazu = ((beNDMWWindowList *)arg0->_subWindow)->_count;
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;
            case 1:
                if (((beNDMWWindowList *)arg0->_subWindow)->_count != arg0->_nowProcKazu) {
                    arg0->_st0 = arg0->_st0 + 1;
                    arg0->_st3 = 0;
                    arg0->_st2 = 0;
                    arg0->_st1 = 0;
                    return;
                }
                break;
            }
            break;
        }
        break;
    case 2:
        beNDMWWindow_PlayQueuedModelClose(arg0);
        beNDMWWindow_ClearQueuedText(arg0);
        beNDMWWindow_RequestChildrenClose(arg0);
        arg0->_st0 = arg0->_st0 + 1;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        arg0->_st1 = 0;
        return;
    case 3:
        if (beNDMWWindow_PollCloseComplete(arg0) != 0) {
            arg0->_isRun = 0;
        }
        break;
    }
}
