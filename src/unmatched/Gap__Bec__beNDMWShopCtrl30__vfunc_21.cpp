/* Bank deposit/withdraw update: four-level state machine on _st0 (open / run / close / wait-
 * close), _st1 (sub-state 0..6), _st2 (step) and _st3 (timer); _bankMenu is the deposit/withdraw
 * mode (0/1), _retCode the child window's result. The st0 increment of case 0 reads _st0 through a
 * volatile lvalue (else the switch scrutinee register is reused); the window-search body reads
 * _subWindow through a volatile lvalue in st1 2/3 step 3 (else the list pointer is shared with the
 * count test); the folder list pointers are loaded after the second folder lookup; function-level
 * locals pl/x/y are declared in the order amt, pl, x, y to fix the saved-register order. _refCount
 * is read as a signed int (lwu otherwise). Rec/Fld stay local views of the igProperty records. */
#include "dw4/reflected.h"
extern "C" {
int igObject_IsKindOf(void *, int);
void *FUN_003baf10(void *);
void *FUN_003b4f50(void *);
void *FUN_003b4d90(void *);
void *FUN_003b7520(void *);
int FUN_00418ac0(void *, int, int);
void *Memory_GetAllocatorBySelector(int);
int ObjectList_AppendRetained(void *, void *);
int ObjectList_RemoveFirstRetained(int *, void *, void *, int);
int beNDMWWindow_BindContext(void *, void *, int, int, int);
int beNDMWWindow_RunMessageScript(void *, int *, int);
int beNDMWWindow_ClearQueuedText(void *);
int beNDMWWindow_PlayQueuedModelClose(void *);
int beNDMWWindow_PollCloseComplete(void *);
int beNDMWWindow_RequestChildrenClose(void *);
void igObject_Destroy(void *);
void *igObject_GetAllocator(void *);
int beMessenger_SelectGroup(int, int *);
int beMessenger_AppendInt(int, int);
int beMessenger_AppendString(int, int *);
int beMessenger_DispatchSelected(int, int *);
void *beMessenger_GetObject(int, int);
struct Rec;
Rec *igProperty_GetRecord(void *, int *);
struct Fld;
Fld *igProperty_GetRecordFolder(void *, int *);
extern int DAT_0051b398[4], DAT_0051b3b0[4], DAT_0051b3c0[4], DAT_0051b3e8[4], DAT_0051b470[4], DAT_0051b498[4],
    DAT_0051b4a0[4], DAT_0051b528[4], DAT_0051b538[4], DAT_0051b548[4], DAT_0051b550[4], DAT_0051b558[4],
    DAT_0051b560[4], DAT_0051b568[4], DAT_00587110[4], DAT_0058af98[4];
extern unsigned char GPR_00554c14;
}
/* Owning stack reference to a freshly created sub-window of one class (kind 0 the select window, 3
 * the status window, 4 the item window, 5 the window); released on scope exit. */
template <int kind> struct WindowRef {
    igObject *p;
    WindowRef(igObject *w) : p(w) {}
    ~WindowRef() { igObject *w = p; if (w != 0) { --w->_refCount; if ((w->_refCount & 0x7fffff) == 0) igObject_Destroy(w); } }
    operator igObject *() { return p; }
};
struct Rec { int pad[3]; int f12; };
struct Fld { int pad[3]; igObjectList *f12; };
#define LCNT(l) (((igObjectList *)(l))->_count)
#define LDAT(l) ((int *)((igObjectList *)(l))->_data)
#define REL(o) { igObject *rr = (o); if (rr != 0) { *(int *)&rr->_refCount = *(int *)&rr->_refCount - 1; if (((unsigned long long)((long long)*(int *)&rr->_refCount << 0x29) >> 0x29) == 0) { igObject_Destroy(rr); } } }
#define FINDWINV(w, i) { w = 0; i = 0; if (0 < LCNT(arg0->_subWindow)) { do { beNDMWStatusCtrlD0 *c = (beNDMWStatusCtrlD0 *)((int *)((igObjectList *)*(volatile int *)&arg0->_subWindow)->_data)[i]; if (c != 0 && igObject_IsKindOf(c, DAT_0058af98[0]) != 0) { w = c; } else { w = 0; } if (w != 0) break; i++; } while (i < LCNT(arg0->_subWindow)); } }
#define FINDWIN(w, i) { w = 0; i = 0; if (0 < LCNT(((beNDMWShopCtrl30 *)arg0)->_subWindow)) { do { beNDMWStatusCtrlD0 *c = (beNDMWStatusCtrlD0 *)LDAT(arg0->_subWindow)[i]; if (c != 0 && igObject_IsKindOf(c, DAT_0058af98[0]) != 0) { w = c; } else { w = 0; } if (w != 0) break; i++; } while (i < LCNT(arg0->_subWindow)); } }
/* matching construct: the move between the two folder lists is an inline function; its address-taken out-count local is then allocated after the window references (stack 100/96 in retail), as written in the function body it would take the top slots */
struct Transfer {
    static inline void Move(igObjectList *to, igObjectList *from, beNDMWItemBase *it) {
        int removed;
        ObjectList_AppendRetained(to, it);
        ObjectList_RemoveFirstRetained(&removed, from, it, 0);
    }
};
extern "C" void Gap__Bec__beNDMWShopCtrl30__vfunc_21(beNDMWShopCtrl30 *arg0) {
    void *alloc;
    beNDMWStatusCtrlD0 *wa; int ia;
    beNDMWStatusCtrlD0 *wb; int ib;
    beNDMWStatusCtrlD0 *wc; int ic;
    int amt;
    void *pl;
    int x;
    int y;
    switch (arg0->_st0) {
    case 0:
        arg0->_st0 = *(volatile int *)&arg0->_st0 + 1;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        arg0->_st1 = 0;
    case 1:
        switch (arg0->_st1) {
        case 0:
            switch (arg0->_st2) {
            case 0:
                alloc = igObject_GetAllocator(arg0);
                alloc = GPR_00554c14 ? alloc : Memory_GetAllocatorBySelector(DAT_00587110[0]);
                {
                WindowRef<0> win((igObject *)FUN_003b4d90(alloc));
                beNDMWWindow_BindContext(win, arg0, arg0->_insight, arg0->_playerNo, 0x546);
                ObjectList_AppendRetained((void *)arg0->_subWindow, win);
                ((beNDMWShopSelect01 *)win.p)->_startPoint = arg0->_bankMenu;
                }
                arg0->_nowProcKazu = LCNT(arg0->_subWindow);
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;
            case 1:
                if (LCNT(arg0->_subWindow) != arg0->_nowProcKazu) {
                    switch (arg0->_retCode) {
                    case 0:
                    case 1:
                        arg0->_bankMenu = arg0->_retCode;
                        arg0->_st1 = 1;
                        arg0->_st3 = 0;
                        arg0->_st2 = 0;
                        return;
                    case 2:
                    default:
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
                WindowRef<0> win((igObject *)FUN_003b4d90(alloc));
                beNDMWWindow_BindContext(win, arg0, arg0->_insight, arg0->_playerNo, 0x54B);
                ObjectList_AppendRetained((void *)arg0->_subWindow, win);
                }
                arg0->_nowProcKazu = LCNT(arg0->_subWindow);
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;
            case 1:
                if (LCNT(arg0->_subWindow) != arg0->_nowProcKazu) {
                    switch (arg0->_retCode) {
                    case 0: {
                        void *pl;
                        igObjectList *l;
                        beMessenger_SelectGroup(arg0->_messenger, &DAT_0051b398[0]);
                        beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
                        beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051b3e8[0]);
                        pl = beMessenger_GetObject(arg0->_messenger, 0);
                        igProperty_GetRecordFolder(pl, &DAT_0051b528[0]);
                        l = igProperty_GetRecordFolder(pl, &DAT_0051b538[0])->f12;
                        if (arg0->_bankMenu == 0) {
                            arg0->_st1 = 2;
                            arg0->_st3 = 0;
                            arg0->_st2 = 0;
                            return;
                        }
                        if (l->_count <= 0) {
                            arg0->_st1 = 6;
                            arg0->_st3 = 0;
                            arg0->_st2 = 0;
                            arg0->_st3 = 0x55E;
                            return;
                        }
                        arg0->_st1 = 3;
                        arg0->_st3 = 0;
                        arg0->_st2 = 0;
                        return;
                    }
                    case 1:
                        if (arg0->_bankMenu == 0) {
                            arg0->_st1 = 4;
                            arg0->_st3 = 0;
                            arg0->_st2 = 0;
                            return;
                        }
                        arg0->_st1 = 5;
                        arg0->_st3 = 0;
                        arg0->_st2 = 0;
                        return;
                    default:
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
        case 3:
            switch (arg0->_st2) {
            case 0:
                alloc = igObject_GetAllocator(arg0);
                alloc = GPR_00554c14 ? alloc : Memory_GetAllocatorBySelector(DAT_00587110[0]);
                {
                WindowRef<3> win((igObject *)FUN_003baf10(alloc));
                beNDMWWindow_BindContext(win, arg0, arg0->_insight, arg0->_playerNo, 0);
                ObjectList_AppendRetained((void *)arg0->_subWindow, win);
                ((beNDMWStatusCtrlD0 *)win.p)->_isAutoClose = 0;
                ((beNDMWStatusCtrlD0 *)win.p)->_isEquipDisable = 1;
                if (arg0->_st1 == 3) ((beNDMWStatusCtrlD0 *)win.p)->_isBankFolder = 1;
                }
                switch (arg0->_st1) {
                case 2:
                    beNDMWWindow_RunMessageScript(arg0, &DAT_0051b3b0[0], 0x54D);
                    break;
                case 3:
                    beNDMWWindow_RunMessageScript(arg0, &DAT_0051b3b0[0], 0x554);
                    break;
                }
                arg0->_nowProcKazu = LCNT(arg0->_subWindow);
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;
                return;
            case 1:
                FINDWIN(wa, ia)
                if (wa != 0) {
                    if (arg0->_retCode == -1) {
                        wa->_st0 = wa->_st0 + 1;
                        wa->_st3 = 0;
                        wa->_st2 = 0;
                        wa->_st1 = 0;
                        arg0->_st2 = 5;
                        arg0->_st3 = 0;
                        beMessenger_SelectGroup(arg0->_messenger, &DAT_0051b3c0[0]);
                        beMessenger_AppendString(arg0->_messenger, &DAT_0051b470[0]);
                        beMessenger_AppendString(arg0->_messenger, &DAT_0051b548[0]);
                        beMessenger_AppendString(arg0->_messenger, &DAT_0051b550[0]);
                        beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051b558[0]);
                        return;
                    }
                    if (wa->_st0 == 1 && wa->_st1 == 2) {
                        void *pl;
                        igObjectList *la;
                        igObjectList *lb;
                        beNDMWItemBase *it;
                        int sw, rc;
                        Fld *fb;
                        beMessenger_SelectGroup(arg0->_messenger, &DAT_0051b398[0]);
                        beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
                        beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051b3e8[0]);
                        pl = beMessenger_GetObject(arg0->_messenger, 0);
                        la = igProperty_GetRecordFolder(pl, &DAT_0051b528[0])->f12;
                        fb = igProperty_GetRecordFolder(pl, &DAT_0051b538[0]);
                        sw = arg0->_st1;
                        lb = fb->f12;
                        rc = arg0->_retCode;
                        switch (sw) {
                        case 2:
                            it = (beNDMWItemBase *)((int *)la->_data)[rc];
                            if (lb->_count >= 0x60) {
                                arg0->_st2 = 2;
                                arg0->_st3 = 0;
                                arg0->_st3 = 0x54E;
                                return;
                            }
                            if (it->_isEquip == 0) {
                                Transfer::Move(lb, la, it);
                            }
                            wa->_st2 = 1;
                            wa->_st3 = 0;
                            return;
                        case 3:
                            it = (beNDMWItemBase *)((int *)lb->_data)[rc];
                            if (la->_count >= 0x24) {
                                arg0->_st2 = 2;
                                arg0->_st3 = 0;
                                arg0->_st3 = 0x555;
                                return;
                            }
                            Transfer::Move(la, lb, it);
                            if (lb->_count <= 0) {
                                arg0->_st2 = 2;
                                arg0->_st3 = 0;
                                arg0->_st3 = 0x55E;
                                FUN_00418ac0(wa, 1, 0);
                                return;
                            }
                            wa->_st2 = 1;
                            wa->_st3 = 0;
                            return;
                        }
                    }
                }
                break;
            case 2:
                beMessenger_SelectGroup(arg0->_messenger, &DAT_0051b3c0[0]);
                beMessenger_AppendString(arg0->_messenger, &DAT_0051b470[0]);
                beMessenger_AppendString(arg0->_messenger, &DAT_0051b548[0]);
                beMessenger_AppendString(arg0->_messenger, &DAT_0051b550[0]);
                beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051b558[0]);
                alloc = igObject_GetAllocator(arg0);
                alloc = GPR_00554c14 ? alloc : Memory_GetAllocatorBySelector(DAT_00587110[0]);
                {
                WindowRef<4> win((igObject *)FUN_003b4f50(alloc));
                beNDMWWindow_BindContext(win, arg0, arg0->_insight, arg0->_playerNo, arg0->_st3);
                ObjectList_AppendRetained((void *)arg0->_subWindow, win);
                }
                arg0->_nowProcKazu = LCNT(arg0->_subWindow);
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;
            case 3:
                if (LCNT(arg0->_subWindow) != arg0->_nowProcKazu) {
                    FINDWINV(wb, ib)
                    if (wb != 0) {
                        wb->_st0 = wb->_st0 + 1;
                        wb->_st3 = 0;
                        wb->_st2 = 0;
                        wb->_st1 = 0;
                        arg0->_st2 = 5;
                        arg0->_st3 = 0;
                        return;
                    }
                }
                break;
            case 5:
                FINDWIN(wc, ic)
                if (wc == 0) {
                    arg0->_st1 = 0;
                    arg0->_st3 = 0;
                    arg0->_st2 = 0;
                    return;
                }
                break;
            }
            break;
        case 4:
        case 5:
            switch (arg0->_st2) {
            case 0:
                alloc = igObject_GetAllocator(arg0);
                alloc = GPR_00554c14 ? alloc : Memory_GetAllocatorBySelector(DAT_00587110[0]);
                {
                WindowRef<5> win((igObject *)FUN_003b7520(alloc));
                beNDMWWindow_BindContext(win, arg0, arg0->_insight, arg0->_playerNo, arg0->_bankMenu);
                ObjectList_AppendRetained((void *)arg0->_subWindow, win);
                }
                arg0->_nowProcKazu = LCNT(arg0->_subWindow);
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;
            case 1:
                if (LCNT(arg0->_subWindow) != arg0->_nowProcKazu) {
                    if (arg0->_retCode != -1) {
                        beMessenger_SelectGroup(arg0->_messenger, &DAT_0051b398[0]);
                        beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
                        beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051b3e8[0]);
                        pl = beMessenger_GetObject(arg0->_messenger, 0);
                        amt = arg0->_retCode;
                        if (arg0->_bankMenu == 0) {
                            x = igProperty_GetRecord(pl, &DAT_0051b560[0])->f12;
                            y = igProperty_GetRecord(pl, &DAT_0051b568[0])->f12;
                            x = x - amt;
                            y = y + amt;
                            igProperty_GetRecord(pl, &DAT_0051b560[0])->f12 = x;
                            igProperty_GetRecord(pl, &DAT_0051b568[0])->f12 = y;
                        } else {
                            x = igProperty_GetRecord(pl, &DAT_0051b560[0])->f12;
                            y = igProperty_GetRecord(pl, &DAT_0051b568[0])->f12;
                            x = x + amt;
                            y = y - amt;
                            igProperty_GetRecord(pl, &DAT_0051b560[0])->f12 = x;
                            igProperty_GetRecord(pl, &DAT_0051b568[0])->f12 = y;
                        }
                        beMessenger_SelectGroup(arg0->_messenger, &DAT_0051b498[0]);
                        beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
                        beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051b4a0[0]);
                    }
                    arg0->_st1 = 0;
                    arg0->_st3 = 0;
                    arg0->_st2 = 0;
                    return;
                }
                break;
            }
            break;
        case 6:
            switch (arg0->_st2) {
            case 0:
                alloc = igObject_GetAllocator(arg0);
                alloc = GPR_00554c14 ? alloc : Memory_GetAllocatorBySelector(DAT_00587110[0]);
                {
                WindowRef<4> win((igObject *)FUN_003b4f50(alloc));
                beNDMWWindow_BindContext(win, arg0, arg0->_insight, arg0->_playerNo, arg0->_st3);
                ObjectList_AppendRetained((void *)arg0->_subWindow, win);
                }
                arg0->_nowProcKazu = LCNT(arg0->_subWindow);
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;
            case 1:
                if (LCNT(arg0->_subWindow) != arg0->_nowProcKazu) {
                    arg0->_st1 = 0;
                    arg0->_st3 = 0;
                    arg0->_st2 = 0;
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
