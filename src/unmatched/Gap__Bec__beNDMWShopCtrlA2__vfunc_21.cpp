#include "dw4/reflected.h"
extern "C" {
void *FUN_00236f80(int, int);
int FUN_002eb010(int);
void *FUN_003b4950(void *);
void *FUN_003b4b10(void *);
int FUN_003f5410(void *, void *, void *, void *, void *);
void *Memory_GetAllocatorBySelector(int);
int ObjectList_AppendRetained(int, void *);
void StringChunk_ReleaseHeader(int, void *);
int StringPool_Construct(int);
int StringPool_Intern(int, int);
int beDataBase_GetRecordCount(int);
int beDataBase_GetRecordInt(int, int, void *);
void *beDataBase_GetRecordString(int, int, void *);
int beMessenger_AppendInt(int, int);
int beMessenger_AppendString(int, void *);
int beMessenger_AppendVec3(int, void *);
int beMessenger_DispatchSelected(int, void *);
int beMessenger_GetObject(int, int);
int beMessenger_SelectGroup(int, void *);
int beMessenger_SendNamed(int, void *, void *, int, void *);
int beNDMWWindow_BindContext(void *, void *, int, int, int);
int beNDMWWindow_ClearQueuedText(void *);
int beNDMWWindow_PlayQueuedModelClose(void *);
int beNDMWWindow_PollCloseComplete(void *);
int beNDMWWindow_PresentModelAtOrigin(void *, void *, int, void *, void *);
int beNDMWWindow_RequestChildrenClose(void *);
void igObject_Destroy(void *);
void *igObject_GetAllocator(void *);
struct Item { int p[3]; int f12; int p16; int f20; };
struct Rec { int p[3]; igDataList *f12; };
struct FRec { int p[3]; igDataList *f12; };
FRec *igProperty_GetRecordFolder(int, void *);
Rec *igProperty_GetRecordArray(int, void *);
struct VObj {
#define V4(a) virtual int a##0(); virtual int a##1(); virtual int a##2(); virtual int a##3();
V4(a) V4(b) V4(c) V4(d) V4(e) virtual int g0(); virtual int g1();
    virtual unsigned f24();
};
struct P3 { void *p[3]; };
extern P3 DAT_004cfa00;
extern P3 DAT_004cfa10;
extern P3 DAT_004cfa20;
extern int DAT_0051b398[4];
extern int DAT_0051b3c0[4];
extern int DAT_0051b3d8[4];
extern int DAT_0051b3e8[4];
extern int DAT_0051b598[4];
extern int DAT_0051b5d8[4];
extern int DAT_0051b5e8[4];
extern int DAT_0051b620[4];
extern int DAT_0051b678[4];
extern int DAT_0051b6c0[4];
extern int DAT_0051b708[4];
extern int DAT_0051b718[4];
extern int DAT_0051b728[4];
extern int DAT_0051b738[4];
extern int DAT_0051b748[4];
extern int DAT_0051b758[4];
extern int DAT_0051b768[4];
extern int DAT_0051b778[4];
extern int DAT_0051b788[4];
extern int DAT_0051b908[4];
extern int DAT_0051b918[4];
extern int DAT_0051b920[4];
extern int DAT_0051b9c0[4];
extern int DAT_0051b9d0[4];
extern int DAT_0051b9e0[4];
extern int DAT_0051b9e8[4];
extern int DAT_0051b9f8[4];
extern int DAT_00586f20[4];
extern int DAT_00587110[4];
extern int DAT_0058b028[4];
extern unsigned char GPR_00554a4c;
extern unsigned char GPR_00554c14;
void Gap__Bec__beNDMWShopCtrlA2__vfunc_21(beNDMWShopCtrlA2 *arg0);
}
struct Rc { int w0; int references; };
/* Owning stack reference to a shop select window while it is set up; released on scope exit
 * (reference count in the low 23 bits of references). */
class WindowRef {
public:
    Rc *p;
    WindowRef(Rc *w) : p(w) {}
    /* matching construct: an argument read through the conversion is evaluated before the call
     * arguments that follow it (retail keeps the window in a saved register across them) */
    operator Rc *() const { return p; }
    ~WindowRef() { Rc *w = p; if (w != 0) { --w->references; if ((w->references & 0x7fffff) == 0) igObject_Destroy(w); } }
};
/* Same role for the result sub-window. */
class SubWindowRef {
public:
    Rc *p;
    SubWindowRef(Rc *w) : p(w) {}
    operator Rc *() const { return p; }
    ~SubWindowRef() { Rc *w = p; if (w != 0) { --w->references; if ((w->references & 0x7fffff) == 0) igObject_Destroy(w); } }
};
#define REL(o) { Rc *rr = (o); if (rr != 0) { rr->references = rr->references - 1; if (((unsigned long long)((long long)rr->references << 0x29) >> 0x29) == 0) { igObject_Destroy(rr); } } }
#define CLEAR(L) { igStringRefList *l = (igStringRefList *)(L); int n = l->_count; int i; int *slot; int nw; for (i = 0; i < n; i++) { slot = (int *)l->_data + i; if (DAT_00586f20[0] == 0) { int v = FUN_002eb010(16); if (v != 0) v = StringPool_Construct(v); DAT_00586f20[0] = v; } nw = StringPool_Intern(DAT_00586f20[0], 0); { int *old = (int *)*slot; if (old != 0) { int *hdr = old - 2; int c = hdr[1] - 1; hdr[1] = c; if (c == 0) StringChunk_ReleaseHeader(hdr[0], hdr); } } *slot = nw; } l->_count = 0; }
void Gap__Bec__beNDMWShopCtrlA2__vfunc_21(beNDMWShopCtrlA2 *arg0) {
    void *alloc;
    void *a3;
    unsigned times[3];
    P3 names1;
    P3 names2;
    P3 names3;
    float vec[3];
    int obj;
    beNDMWStatus *ctx;
    int maxv;
    int i;
    switch (arg0->_st0) {
    case 0:
        /* matching construct: volatile read reloads the state word after the dispatch. */
        arg0->_st0 = ((volatile beNDMWShopCtrlA2 *)arg0)->_st0 + 1;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        arg0->_st1 = 0;
        arg0->_st1 = 7;
        arg0->_st3 = 0;
        arg0->_st2 = 0;
        return;
    case 1:
        switch (arg0->_st1) {
        case 7:
            switch (arg0->_st2) {
            case 0:
                switch ((unsigned)arg0->_entCode) {
                case 1: a3 = DAT_0051b708; break;
                case 2: a3 = DAT_0051b718; break;
                case 3: a3 = DAT_0051b728; break;
                case 4: a3 = DAT_0051b738; break;
                case 5: a3 = DAT_0051b748; break;
                case 6: a3 = DAT_0051b758; break;
                case 7: a3 = DAT_0051b768; break;
                case 8: a3 = DAT_0051b778; break;
                case 9: a3 = DAT_0051b788; break;
                }
                beNDMWWindow_PresentModelAtOrigin(arg0, DAT_0051b9c0, 0, a3, DAT_0051b620);
                alloc = igObject_GetAllocator(arg0);
                alloc = GPR_00554c14 ? alloc : Memory_GetAllocatorBySelector(DAT_00587110[0]);
                {
                    WindowRef win((Rc *)FUN_003b4950(alloc));
                    beNDMWWindow_BindContext(win, arg0, arg0->_insight, arg0->_playerNo, 0x7DD);
                    ObjectList_AppendRetained(arg0->_subWindow, win);
                }
                arg0->_nowProcKazu = ((igDataList *)arg0->_subWindow)->_count;
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;
            case 1:
                if (((igDataList *)arg0->_subWindow)->_count != arg0->_nowProcKazu) {
                    arg0->_st2 = arg0->_st2 + 1;
                    arg0->_st3 = 0;
                }
                break;
            case 2:
                alloc = igObject_GetAllocator(arg0);
                alloc = GPR_00554c14 ? alloc : Memory_GetAllocatorBySelector(DAT_00587110[0]);
                {
                    SubWindowRef win((Rc *)FUN_003b4b10(alloc));
                    beNDMWWindow_BindContext(win, arg0, arg0->_insight, arg0->_playerNo, 0x7D8);
                    ObjectList_AppendRetained(arg0->_subWindow, win);
                }
                arg0->_nowProcKazu = ((igDataList *)arg0->_subWindow)->_count;
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;
            case 3:
                if (((igDataList *)arg0->_subWindow)->_count != arg0->_nowProcKazu) {
                    switch (arg0->_retCode) {
                    case 0:
                        beNDMWWindow_PlayQueuedModelClose(arg0);
                        CLEAR(arg0->_modelCloseInfoNameList)
                        ((igIntList *)arg0->_modelCloseRamNoList)->_count = 0;
                        CLEAR(arg0->_modelCloseSeqNameList)
                        arg0->_st1 = 8;
                        arg0->_st3 = 0;
                        arg0->_st2 = 0;
                        return;
                    case 1:
                        ((beNDMWWindow *)arg0->_mother)->_retCode = 6;
                        arg0->_st0 = arg0->_st0 + 1;
                        arg0->_st3 = 0;
                        arg0->_st2 = 0;
                        arg0->_st1 = 0;
                        return;
                    default:
                        ((beNDMWWindow *)arg0->_mother)->_retCode = 4;
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
        case 8:
            switch (arg0->_st2) {
            case 0:
                alloc = igObject_GetAllocator(arg0);
                alloc = GPR_00554c14 ? alloc : Memory_GetAllocatorBySelector(DAT_00587110[0]);
                {
                WindowRef win((Rc *)FUN_003b4950(alloc));
                beNDMWWindow_BindContext(win, arg0, arg0->_insight, arg0->_playerNo, 0);
                ObjectList_AppendRetained(arg0->_subWindow, win);
                beMessenger_SelectGroup(arg0->_messenger, DAT_0051b398);
                beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
                beMessenger_DispatchSelected(arg0->_messenger, DAT_0051b3e8);
                obj = beMessenger_GetObject(arg0->_messenger, 0);
                {
                    igDataList *a = igProperty_GetRecordFolder(obj, DAT_0051b6c0)->f12;
                    int j = 0;
                    /* matching construct: volatile count keeps the retail per-iteration reload of the list size (no loop-invariant hoist). */
                    while (j < *(volatile int *)&a->_count) {
                        Item *it = ((Item **)a->_data)[j];
                        if (it != 0 && it->f12 == 10) {
                            if (it->f20 > 0) it->f20 = it->f20 - 1;
                            break;
                        }
                        j++;
                    }
                }
                beMessenger_SendNamed(arg0->_messenger, DAT_0051b5d8, DAT_0051b918, 0, DAT_0051b5e8);
                {
                int db = beMessenger_GetObject(arg0->_messenger, 0);
                ctx = (beNDMWStatus *)FUN_00236f80(arg0->_insight, DAT_0058b028[0]);
                maxv = 0;
                names1 = DAT_004cfa00;
                names2 = DAT_004cfa10;
                for (i = 0; i < 3; i++) {
                    unsigned char found;
                    int acc;
                    int idx;
                    int cnt;
                    times[i] = (((VObj *)((beSystem *)ctx->_system)->_random)->f24() % 1000U) * 1000;
                    found = 0;
                    acc = 0;
                    idx = 0;
                    cnt = beDataBase_GetRecordCount(db);
                    for (; idx < cnt; idx++) {
                        acc += beDataBase_GetRecordInt(db, idx, DAT_0051b9d0) * 1000;
                        if (times[i] < (unsigned)acc) { found = 1; break; }
                    }
                    if (found == 0) idx = cnt - 1;
                    {
                        igDataList *ar = igProperty_GetRecordArray(obj, DAT_0051b908)->f12;
                        if (ar->_count != 0 && idx >= 0 && idx < ar->_count) ((char *)ar->_data)[idx] = GPR_00554a4c;
                    }
                    if (maxv < beDataBase_GetRecordInt(db, idx, DAT_0051b9e0)) maxv = beDataBase_GetRecordInt(db, idx, DAT_0051b9e0);
                    FUN_003f5410(win, DAT_0051b9e8, names1.p[i], beDataBase_GetRecordString(db, idx, DAT_0051b678), DAT_0051b598);
                    beNDMWWindow_PresentModelAtOrigin(win.p, beDataBase_GetRecordString(db, idx, DAT_0051b920), i, names2.p[i], DAT_0051b620);
                    {
                        float x, y, z;
                        switch (beDataBase_GetRecordInt(db, idx, DAT_0051b9e0)) {
                        case 2: x = 0.0f; y = 1.0f; z = 0.0f; break;
                        case 1: x = 1.0f; y = 1.0f; z = 0.0f; break;
                        default: x = 1.0f; y = 1.0f; z = 1.0f; break;
                        }
                        beMessenger_SelectGroup(arg0->_messenger, DAT_0051b3c0);
                        beMessenger_AppendString(arg0->_messenger, DAT_0051b9e8);
                        beMessenger_AppendString(arg0->_messenger, names1.p[i]);
                        vec[0] = x; vec[1] = y; vec[2] = z;
                        beMessenger_AppendVec3(arg0->_messenger, vec);
                        beMessenger_DispatchSelected(arg0->_messenger, DAT_0051b9f8);
                    }
                }
                }
                switch (maxv) {
                case 2: ((beNDMWShopSelect03 *)(Rc *)win)->_entCode = 0x7DA; break;
                case 1: ((beNDMWShopSelect03 *)(Rc *)win)->_entCode = 0x7DB; break;
                default: ((beNDMWShopSelect03 *)(Rc *)win)->_entCode = 0x7DC; break;
                }
                }
                arg0->_nowProcKazu = ((igDataList *)arg0->_subWindow)->_count;
                arg0->_st2 = arg0->_st2 + 1;
                arg0->_st3 = 0;
            case 1:
                if (((igDataList *)arg0->_subWindow)->_count != arg0->_nowProcKazu) {
                    int k;
                    names3 = DAT_004cfa20;
                    for (k = 0; k < 3; k++) {
                        beMessenger_SelectGroup(arg0->_messenger, DAT_0051b3c0);
                        beMessenger_AppendString(arg0->_messenger, DAT_0051b9e8);
                        beMessenger_AppendString(arg0->_messenger, names3.p[k]);
                        beMessenger_DispatchSelected(arg0->_messenger, DAT_0051b3d8);
                    }
                    ((beNDMWWindow *)arg0->_mother)->_retCode = 4;
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
