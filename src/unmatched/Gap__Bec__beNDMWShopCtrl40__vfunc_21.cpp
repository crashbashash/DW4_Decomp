/* Gap__Bec__beNDMWShopCtrl40__vfunc_21: the ShopCtrl40 (mode 4, "CNOS") update. Four-level state
 * machine on _st0 (open / run / close / wait-close), _st1 (sub-state), _st2 (step) and _st3
 * (timer); _subWindow is the child-window list, _nowProcKazu the child count that a freshly
 * spawned child must exceed before the step advances. Build requirements (same as
 * beNDMWShopDevice::vfunc_21, 0x0043cc20): the alternate compiler with "-O3,p -Cpp_exceptions
 * off"; the window and string holders' destructors are duplicates of the retail bodies the
 * exception table names. Codegen projections, not recovered declarations: Rc/Rec/Fld/Item/V are
 * partial views of objects whose reflected structs are not tied to these call sites; the
 * WindowRef/StringRef holders release their object in the destructor; the window search guard
 * reads _subWindow through the beNDMWShopCtrl30 view so it is not merged with the loop-body loads
 * (retail reloads the list pointer for the guard, body and latch separately). */
#include "dw4/reflected.h"
extern "C" {
int FUN_003f5410(void *, int *, int *, int *, int *);
void *FUN_003baf10(void *);
void *FUN_003b4f50(void *);
void *FUN_003b4d90(void *);
int igObject_IsKindOf(void *, int);
void *Memory_GetAllocatorBySelector(int);
int ObjectList_AppendRetained(void *, void *);
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
int beMessenger_SendNamed(int, int *, char *, int, int *);
void *beMessenger_GetObject(int, int);
struct Rec;
Rec *igProperty_GetRecord(void *, int *);
struct Fld;
Fld *igProperty_GetRecordFolder(void *, int *);
int beDataBase_GetRecordInt(void *, int, int *);
void *FUN_002eb010(int);
void *StringPool_Construct(void *);
char *StringPool_Intern(void *, int *);
void StringChunk_ReleaseHeader(int, int *);
struct P1;
P1 *FUN_00236f80(int, int);
extern int DAT_0051b398[4], DAT_0051b3b0[4], DAT_0051b3c0[4], DAT_0051b3e8[4], DAT_0051b470[4], DAT_0051b498[4],
    DAT_0051b4a0[4], DAT_0051b528[4], DAT_0051b548[4], DAT_0051b550[4], DAT_0051b558[4], DAT_0051b560[4],
    DAT_0051b590[4], DAT_0051b598[4], DAT_0051b5a0[4], DAT_0051b5a8[4], DAT_0051b5b8[4], DAT_0051b5c8[4],
    DAT_0051b5d8[4], DAT_0051b5e8[4], DAT_0051b5f8[4], DAT_0051b600[4], DAT_0051b608[4], DAT_00586f20[4],
    DAT_00587110[4], DAT_0058af98[4], DAT_0058b028[4];
extern unsigned char GPR_00554c14;
}
struct Rc;
struct Rc { int w0; int references; char pad[101]; char f109; char p110; char f111; };
/* owning references to freshly created windows: the destructor drops one reference and destroys at zero.  The three window
 * kinds are separate classes (separate out-of-line destructors in retail: 0x414420, 0x411080, 0x428710). */
template <int K> struct WindowRef { Rc *p; WindowRef(Rc *o) : p(o) {} ~WindowRef() { igObject *o = (igObject *)p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } } operator Rc *() { return p; } };
/* owning reference to an interned string token (reference count at p[-1], chunk header at p[-2]); retail destructor 0x130720 */
struct StringRef { char *p; StringRef(char *s) : p(s) {} ~StringRef() { char *rs = p; if (rs != 0) { int *hd = (int *)rs - 2; int rc = hd[1] - 1; hd[1] = rc; if (rc == 0) { StringChunk_ReleaseHeader(hd[0], hd); } } } };
struct Lst { int pad[2]; int cnt; int p12; int *data; };
struct Rec { int pad[3]; int f12; };
struct Fld { int pad[3]; Lst *f12; };
struct Item { int pad[2]; int f8; int f12; };
class V { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual unsigned v22(); };
struct P2 { int pad[12]; V *f48; };
struct P1 { int pad[4]; P2 *f16; };
#define LCNT(l) (((igObjectList *)(l))->_count)
#define LDAT(l) ((int *)((igObjectList *)(l))->_data)
#define RELS(o) { char *rs = (o); if (rs != 0) { int *hd = (int *)rs - 2; int rc = hd[1] - 1; hd[1] = rc; if (rc == 0) { StringChunk_ReleaseHeader(hd[0], hd); } } }
#define FINDWIN(w, i) { w = 0; i = 0; if (0 < LCNT(((beNDMWShopCtrl30 *)arg0)->_subWindow)) { do { beNDMWWindow *c = (beNDMWWindow *)LDAT(arg0->_subWindow)[i]; if (c != 0 && igObject_IsKindOf(c, DAT_0058af98[0]) != 0) { w = c; } else { w = 0; } if (w != 0) break; i++; } while (i < LCNT(arg0->_subWindow)); } }
extern "C" void Gap__Bec__beNDMWShopCtrl40__vfunc_21(beNDMWShopCtrl40 *arg0) {
    void *alloc;
    beNDMWWindow *wa;
    int ia;
    beNDMWWindow *wb;
    int ib;
    beNDMWWindow *wc;
    int ic;
    switch (arg0->_st0) {
    case 0:
        FUN_003f5410(arg0, &DAT_0051b470[0], &DAT_0051b548[0], &DAT_0051b590[0], &DAT_0051b598[0]);
        arg0->_st0 = arg0->_st0 + 1;
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
                    WindowRef<1> spBC((Rc *)FUN_003baf10(alloc));
                    beNDMWWindow_BindContext(spBC, arg0, arg0->_insight, arg0->_playerNo, 0);
                    ObjectList_AppendRetained((void *)arg0->_subWindow, spBC);
                    spBC.p->f111 = 0;
                    spBC.p->f109 = 1;
                }
                beNDMWWindow_RunMessageScript(arg0, &DAT_0051b3b0[0], 0x5AA);
                arg0->_nowProcKazu = LCNT(arg0->_subWindow);
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;
                return;
            case 1:
                FINDWIN(wa, ia)
                if (wa != 0) {
                    if (arg0->_retCode == -1) {
                        arg0->_st1 = 3;
                        arg0->_st3 = 0;
                        arg0->_st2 = 0;
                        return;
                    }
                    if (wa->_st0 == 1 && wa->_st1 == 2) {
                        arg0->_selectCursor = arg0->_retCode;
                        beMessenger_SelectGroup(arg0->_messenger, &DAT_0051b398[0]);
                        beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
                        beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051b3e8[0]);
                        if (igProperty_GetRecord(beMessenger_GetObject(arg0->_messenger, 0), &DAT_0051b560[0])->f12 < 300) {
                            arg0->_st1 = 2;
                            arg0->_st3 = 0;
                            arg0->_st2 = 0;
                        } else {
                            arg0->_st1 = 1;
                            arg0->_st3 = 0;
                            arg0->_st2 = 0;
                        }
                        beMessenger_SelectGroup(arg0->_messenger, &DAT_0051b3c0[0]);
                        beMessenger_AppendString(arg0->_messenger, &DAT_0051b470[0]);
                        beMessenger_AppendString(arg0->_messenger, &DAT_0051b548[0]);
                        beMessenger_AppendString(arg0->_messenger, &DAT_0051b550[0]);
                        beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051b558[0]);
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
                    WindowRef<2> spB8((Rc *)FUN_003b4f50(alloc));
                    beNDMWWindow_BindContext(spB8, arg0, arg0->_insight, arg0->_playerNo, 0x5AC);
                    ObjectList_AppendRetained((void *)arg0->_subWindow, spB8);
                }
                arg0->_nowProcKazu = LCNT(arg0->_subWindow);
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;
            case 1:
                if (LCNT(arg0->_subWindow) != arg0->_nowProcKazu) {
                    alloc = igObject_GetAllocator(arg0);
                    alloc = GPR_00554c14 ? alloc : Memory_GetAllocatorBySelector(DAT_00587110[0]);
                    {
                        WindowRef<3> spB4((Rc *)FUN_003b4d90(alloc));
                        beNDMWWindow_BindContext(spB4, arg0, arg0->_insight, arg0->_playerNo, 0x5AD);
                        ObjectList_AppendRetained((void *)arg0->_subWindow, spB4);
                    }
                    arg0->_nowProcKazu = LCNT(arg0->_subWindow);
                    arg0->_st2 = arg0->_st2 + 1;
                    arg0->_st3 = 0;
            case 2:
                    if (LCNT(arg0->_subWindow) != arg0->_nowProcKazu) {
                        if (arg0->_retCode == 0) {
                            int base;
                            void *db;
                            int lvl;
                            int lim;
                            int tier;
                            int sum;
                            int cnt;
                            int j;
                            void *pl;
                            Item *it;
                            int id;
                            beMessenger_SelectGroup(arg0->_messenger, &DAT_0051b398[0]);
                            beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
                            beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051b3e8[0]);
                            pl = beMessenger_GetObject(arg0->_messenger, 0);
                            { int cur = igProperty_GetRecord(pl, &DAT_0051b560[0])->f12;
                              Rec *r = igProperty_GetRecord(pl, &DAT_0051b560[0]);
                              r->f12 = cur - 300; }
                            beMessenger_SelectGroup(arg0->_messenger, &DAT_0051b498[0]);
                            beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
                            beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051b4a0[0]);
                            it = (Item *)igProperty_GetRecordFolder(pl, &DAT_0051b528[0])->f12->data[arg0->_selectCursor];
                            lvl = igProperty_GetRecord(pl, &DAT_0051b5a0[0])->f12;
                            if (lvl < 0x29) tier = 1;
                            else if (lvl < 0x65) tier = 2;
                            else if (lvl < 0xC9) tier = 3;
                            else if (lvl < 0x12D) tier = 4;
                            else if (lvl < 0x191) tier = 5;
                            else tier = 6;
                            StringRef spB0(0);
                            if (it->f8 == 0) {
                                if (DAT_00586f20[0] == 0) {
                                    void *o = FUN_002eb010(0x10);
                                    if (o != 0) o = StringPool_Construct(o);
                                    DAT_00586f20[0] = (int)o;
                                }
                                { char *ns = StringPool_Intern((void *)DAT_00586f20[0], &DAT_0051b5a8[0]);
                                  { char *os = spB0.p; RELS(os) }
                                  spB0.p = ns; }
                            } else if (it->f8 == 1) {
                                if (DAT_00586f20[0] == 0) {
                                    void *o = FUN_002eb010(0x10);
                                    if (o != 0) o = StringPool_Construct(o);
                                    DAT_00586f20[0] = (int)o;
                                }
                                { char *ns = StringPool_Intern((void *)DAT_00586f20[0], &DAT_0051b5b8[0]);
                                  { char *os = spB0.p; RELS(os) }
                                  spB0.p = ns; }
                            } else if (it->f8 == 2) {
                                if (DAT_00586f20[0] == 0) {
                                    void *o = FUN_002eb010(0x10);
                                    if (o != 0) o = StringPool_Construct(o);
                                    DAT_00586f20[0] = (int)o;
                                }
                                { char *ns = StringPool_Intern((void *)DAT_00586f20[0], &DAT_0051b5c8[0]);
                                  { char *os = spB0.p; RELS(os) }
                                  spB0.p = ns; }
                            }
                            beMessenger_SendNamed(arg0->_messenger, &DAT_0051b5d8[0], spB0.p, 0, &DAT_0051b5e8[0]);
                            db = beMessenger_GetObject(arg0->_messenger, 0);
                            base = tier * 100;
                            cnt = beDataBase_GetRecordInt(db, base, &DAT_0051b5f8[0]);
                            lim = (int)(FUN_00236f80(arg0->_insight, DAT_0058b028[0])->f16->f48->v22() % 10000U);
                            sum = 0;
                            j = 1;
                            if (cnt > 0) {
                                do {
                                    id = base + j;
                                    sum += beDataBase_GetRecordInt(db, id, &DAT_0051b600[0]);
                                    if (sum >= lim) {
                                        int v = beDataBase_GetRecordInt(db, id, &DAT_0051b5f8[0]);
                                        beDataBase_GetRecordInt(db, id, &DAT_0051b608[0]);
                                        it->f12 = v;
                                        break;
                                    }
                                    j++;
                                } while (cnt >= j);
                            }
                        }
                        arg0->_retCode = arg0->_selectCursor;
                        FINDWIN(wb, ib)
                        if (wb != 0) {
                            arg0->_st1 = 0;
                            arg0->_st3 = 0;
                            arg0->_st2 = 0;
                            arg0->_st2 = 1;
                            arg0->_st3 = 0;
                            wb->_st2 = 1;
                            wb->_st3 = 0;
                            beMessenger_SelectGroup(arg0->_messenger, &DAT_0051b3c0[0]);
                            beMessenger_AppendString(arg0->_messenger, &DAT_0051b470[0]);
                            beMessenger_AppendString(arg0->_messenger, &DAT_0051b548[0]);
                            beMessenger_AppendString(arg0->_messenger, &DAT_0051b550[0]);
                            beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051b558[0]);
                            return;
                        }
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
                    WindowRef<2> spAC((Rc *)FUN_003b4f50(alloc));
                    beNDMWWindow_BindContext(spAC, arg0, arg0->_insight, arg0->_playerNo, 0x5AB);
                    ObjectList_AppendRetained((void *)arg0->_subWindow, spAC);
                }
                arg0->_nowProcKazu = LCNT(arg0->_subWindow);
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;
            case 1:
                if (LCNT(arg0->_subWindow) != arg0->_nowProcKazu) {
                    arg0->_st1 = 3;
                    arg0->_st3 = 0;
                    arg0->_st2 = 0;
                    return;
                }
                break;
            }
            break;
        case 3:
            FINDWIN(wc, ic)
            switch (arg0->_st2) {
            case 0:
                if (wc != 0) {
                    wc->_st0 = 2;
                    wc->_st3 = 0;
                    wc->_st2 = 0;
                    wc->_st1 = 0;
                }
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;
                return;
            case 1:
                if (wc == 0) {
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
