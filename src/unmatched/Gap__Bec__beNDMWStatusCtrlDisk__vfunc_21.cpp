/* Update state machine of the status-screen disk control (_st0 open / run / close / wait-close, _st1
 * step, _st2 sub-step). Each sub-window, list and disk reference is held by an owning reference
 * scoped to the block that uses it; one holder class per retail destructor copy. */
#include "dw4/reflected.h"
static inline int countOf(const igDataList *l) { return l->_count; }
static inline int st1Of(const beNDMWStatusCtrlDisk *w) { return w->_st1; }

extern "C" {
void *FUN_002eb010(int);
void *StringPool_Construct(void *);
const char *StringPool_Intern(void *, const char *);
void StringChunk_ReleaseHeader(int, int *);
int List_Resize(void *, int, int);
void *igObject_GetAllocator(void *);
void *Memory_GetAllocatorBySelector(int);
void igObject_Destroy(void *);
void ObjectList_AppendRetained(...);
void ObjectList_SetAtRetained_003e9160(...);
void ObjectRef_Release_003e9110(...);
void ObjectRef_Retain_003e90d0(...);
int FUN_00236f80(...);
void *FUN_002cb0d0(void *);
void *FUN_003b4410(void *);
void *FUN_003b4f50(void *);
void *FUN_003b51b0(void *);
void FUN_003f5410(...);
void FUN_0041d2c0(...);
void FUN_0041d3b0(...);
void FUN_0041d3f0(...);
void FUN_0041d490(...);
void FUN_0041d510(...);
void beMessenger_SelectGroup(...);
void beMessenger_AppendInt(...);
void beMessenger_AppendString(...);
void beMessenger_DispatchSelected(...);
void beMessenger_SendNamed(...);
int beMessenger_GetObject(int, int);
int *igProperty_GetRecordFolder(int, const void *);
int *igProperty_GetRecordByte(int, const void *);
int beNDMWItemBase_GetRecordString(...);
void beNDMWWindow_PresentModel(...);
void beNDMWWindow_PresentModelAtOrigin(...);
void beNDMWWindow_RunMessageScript(...);
void beNDMWWindow_BindContext(...);
void beNDMWWindow_ClearQueuedText(...);
void beNDMWWindow_PlayQueuedModelClose(...);
void beNDMWWindow_RequestChildrenClose(...);
int beNDMWWindow_PollCloseComplete(...);
extern void *DAT_00586f20[4];
extern int DAT_00587110[4];
extern int DAT_0058b028[4];
extern unsigned char GPR_00554c14;
extern unsigned char GPR_00554a30;
extern unsigned char GPR_00554a34;
extern int DAT_004cf700[12];
extern int DAT_004cf670[12];
extern int DAT_004cf674[4];
extern int DAT_005199e0[4];
extern int DAT_005199e8[4];
extern int DAT_00519a58[4];
extern int DAT_00519a90[4];
extern int DAT_00519b00[4];
extern int DAT_00519b08[4];
extern int DAT_00519b50[4];
extern int DAT_00519b60[4];
extern int DAT_00519b68[4];
extern int DAT_00519b90[4];
extern int DAT_00519ba0[4];
extern int DAT_00519ba8[4];
extern int DAT_00519c28[4];
extern int DAT_00519cc8[4];
extern int DAT_00519cd8[4];
extern int DAT_00519ce8[4];
extern int DAT_00519d88[4];
extern int DAT_00519d98[4];
extern int DAT_00519eb8[4];
extern int DAT_00519f28[4];
extern int DAT_00519f30[4];
extern int DAT_0051a040[4];
extern int DAT_0051a060[4];
extern int DAT_0051a080[4];
extern int DAT_0051a0a8[4];
extern int DAT_0051a150[4];
extern int DAT_0051a160[4];
extern int DAT_0051a170[4];
extern int DAT_0051a180[4];
extern int DAT_0051a190[4];
extern int DAT_0051a1a0[4];
extern int DAT_0051a1a8[4];
extern int DAT_0051a1b8[4];
extern int DAT_0051a1c8[4];
extern int DAT_0051a1d8[4];
extern int DAT_0051a1e8[4];
extern int DAT_0051a1f8[4];
extern int DAT_0051a200[4];
extern int DAT_0051a210[4];
}

typedef unsigned __int128 Q128;
struct Str3 { const char *v[3]; };
extern Str3 DAT_004cf730;
typedef igObject RefHeader;
static inline void ReleaseObject(igObject *o)
{
    if (o) {
        --o->_refCount;
        if (!(o->_refCount & 0x7fffff)) igObject_Destroy(o);
    }
}
#define WINDOW_REF(Name) \
class Name { \
public: \
    igObject *p; \
    Name(void *o) : p((igObject *)o) {} \
    ~Name() { ReleaseObject((igObject *)p); } \
}
WINDOW_REF(SelectE1Ref);
WINDOW_REF(ConfirmRef);
WINDOW_REF(QuantityRef);
WINDOW_REF(DecideListRef);
class SwapRef {
public:
    igObject *p;
    SwapRef(void *o) : p((igObject *)o) { igObject *q = p; if (q) ++q->_refCount; }
    ~SwapRef() { ReleaseObject((igObject *)p); }
};
class DeviceRef {
public:
    igObject *p;
    DeviceRef(void *o) : p((igObject *)o) { igObject *q = p; if (q) ++q->_refCount; }
    DeviceRef(const DeviceRef &r) : p(r.p) { if (p != 0) p->_refCount = p->_refCount + 1; }
    ~DeviceRef() { ReleaseObject((igObject *)p); }
};
class StringRef {
public:
    const char *p;
    StringRef(const char *s) : p(s) {}
    ~StringRef() { const char *held = p;
        if (held != 0) { int *hd = (int *)held - 2;
            int cnt = ((int *)held)[-1] - 1; ((int *)held)[-1] = cnt;
            if (cnt == 0) StringChunk_ReleaseHeader(*hd, hd); } }
};
extern "C" int StringList_AppendRetained(int, const StringRef &);
extern "C" void FUN_003f56d0(void *, void *, const char *, const DeviceRef &, void *);
struct HA { static int Add(int a, int b) { return a + b; } };

#define GET_ALLOC(v) { void *ga = igObject_GetAllocator(self); if (GPR_00554c14 != 0) { v = ga; } else { v = Memory_GetAllocatorBySelector(DAT_00587110[0]); } }
#define INTERN(slot, text) { \
    const char *tok; \
    if ((text) == 0) { tok = 0; } else { \
        if (DAT_00586f20[0] == 0) { \
            void *pool = FUN_002eb010(0x10); \
            if (pool != 0) pool = StringPool_Construct(pool); \
            DAT_00586f20[0] = pool; \
        } \
        tok = StringPool_Intern(DAT_00586f20[0], (const char *)(text)); \
    } \
    slot = tok; }
#define WSETI84(w, v) { beNDMWWindowSelect *wt = (beNDMWWindowSelect *)(w); wt->_selectMax = (v); }
#define WSETI100(w, v) { beNDMWWindowSelect *wt = (beNDMWWindowSelect *)(w); wt->_startPoint = (v); }
#define WSETPOS(w, x, y, z) { beNDMWWindowSelect *wt = (beNDMWWindowSelect *)(w); *(float *)&wt->_offsetPos[0] = (x); *(float *)&wt->_offsetPos[1] = (y); *(float *)&wt->_offsetPos[2] = (z); }
#define INTERNP(slot, ptr) { \
    const char *src = (const char *)(ptr); \
    const char *tok; \
    if (src == 0) { tok = 0; } else { \
        if (DAT_00586f20[0] == 0) { \
            void *pool = FUN_002eb010(0x10); \
            if (pool != 0) pool = StringPool_Construct(pool); \
            DAT_00586f20[0] = pool; \
        } \
        tok = StringPool_Intern(DAT_00586f20[0], src); \
    } \
    slot = tok; }
#define INTERNP_APPEND(field, ptr) { const char *tok_; INTERNP(tok_, ptr) StringList_AppendRetained(field, StringRef(tok_)); }
#define INTERN_APPEND(field, text) { const char *tok_; INTERN(tok_, text) StringList_AppendRetained(field, StringRef(tok_)); }
#define MSG_SELECT_INT(v) { beMessenger_SelectGroup(self->_messenger, DAT_00519ba0); \
    beMessenger_AppendInt(self->_messenger, v); beMessenger_DispatchSelected(self->_messenger, DAT_00519ba8); }
#define NEXT_ST0() { self->_st0 = self->_st0 + 1; self->_st3 = 0; self->_st2 = 0; self->_st1 = 0; }
#define NEXT_ST2() { self->_st2 = self->_st2 + 1; self->_st3 = 0; }
#define SYNC_COUNT() { self->_nowProcKazu = ((igObjectList *)self->_subWindow)->_count; }
#define WIN_PENDING() (((igObjectList *)self->_subWindow)->_count != self->_nowProcKazu)
#define BLIST_ADD(r, v) { int n; igDataList *dl = (igDataList *)(r).p; n = dl->_count; \
    if (n < dl->_capacity) dl->_count = n + 1; else List_Resize(dl, n + 1, 1); \
    ((unsigned char *)dl->_data)[n] = (v); }
#define LIST_ADD(decided, val) { int n_ = ((igDataList *)(decided))->_count; igDataList *l_ = (igDataList *)(decided); \
    if (n_ < l_->_capacity) l_->_count = countOf(l_) + 1; else List_Resize(l_, n_ + 1, 4); \
    ((int *)l_->_data)[n_] = (val); }
#define SEND_CLOSE() beMessenger_SendNamed(self->_messenger, DAT_00519a90, DAT_00519d88, 0, DAT_00519a58)
#define RESET_ST1() { self->_st1 = 0; self->_st3 = 0; self->_st2 = 0; }
#define MSG_STR3(a, b, c, d) { beMessenger_SelectGroup(self->_messenger, DAT_00519c28); \
    beMessenger_AppendString(self->_messenger, a); beMessenger_AppendString(self->_messenger, b); \
    beMessenger_AppendString(self->_messenger, c); beMessenger_DispatchSelected(self->_messenger, d); }
#define CLOSE_LISTS() { igObjectList *l1 = (igObjectList *)self->_modelCloseInfoNameList; \
    FUN_0041d2c0(l1, 0, l1->_count); l1->_count = 0; \
    ((igObjectList *)self->_modelCloseRamNoList)->_count = 0; \
    igObjectList *l2 = (igObjectList *)self->_modelCloseSeqNameList; \
    FUN_0041d2c0(l2, 0, l2->_count); l2->_count = 0; }

struct Q48 { Q128 q[3]; };
extern "C" void Gap__Bec__beNDMWStatusCtrlDisk__vfunc_21(beNDMWStatusCtrlDisk *self);
void Gap__Bec__beNDMWStatusCtrlDisk__vfunc_21(beNDMWStatusCtrlDisk *self)
{
    Str3 names;
    char bufC[8];
    float vecA[3];
    float vecB[3];
    float vecC[3];
    float vecD[3];
    int tq[12];
    switch (self->_st0) {
    case 0: {
        int i, j;
        if (self->_st1 == 0) self->_cursor = 0;
        MSG_SELECT_INT(self->_playerNo)
        igProperty_GetRecordFolder(beMessenger_GetObject(self->_messenger, 0), DAT_0051a150);
        beNDMWWindow_PresentModelAtOrigin(self, DAT_0051a0a8, 0, DAT_0051a160, DAT_00519a58);
        INTERN_APPEND(self->_textCloseTypeList, DAT_0051a040)
        INTERNP_APPEND(self->_textCloseNameList, DAT_004cf670[0])
        beNDMWWindow_RunMessageScript(self, DAT_00519b90, 0x48);
        for (i = 0; i < 12; i++)
            FUN_003f5410(self, DAT_0051a060, DAT_004cf670[i], DAT_00519b60, DAT_00519b68);
        for (j = 0; j < 12; j++)
            FUN_003f5410(self, DAT_0051a170, DAT_004cf670[j], DAT_00519b60, DAT_0051a080);
        FUN_003f5410(self, DAT_00519b50, DAT_004cf670[0], DAT_00519b60, DAT_00519b68);
        NEXT_ST0()
    }
    case 1:
        switch (st1Of(self)) {
        case 0: {
            void *al;
            int cnt;
            GET_ALLOC(al)
            { SelectE1Ref diskWin(FUN_003b51b0(al));
            beNDMWWindow_BindContext(diskWin.p, self, self->_insight, self->_playerNo, 0);
            ObjectList_AppendRetained(self->_subWindow, diskWin.p);
            MSG_SELECT_INT(self->_playerNo)
            igProperty_GetRecordFolder(beMessenger_GetObject(self->_messenger, 0), DAT_0051a150);
            WSETI84(diskWin.p, 10)
            WSETPOS(diskWin.p, -121.0f, 128.0f, 0.0f)
            WSETI100(diskWin.p, self->_cursor)
            INTERN_APPEND(((beNDMWWindowSelect *)diskWin.p)->_textCloseTypeList, DAT_00519b50)
            INTERN_APPEND(((beNDMWWindowSelect *)diskWin.p)->_textCloseNameList, DAT_00519d98)
            beNDMWWindow_RunMessageScript(diskWin.p, DAT_00519b90, 0x2B);
            }
            cnt = ((igObjectList *)self->_subWindow)->_count;
            self->_nowProcKazu = cnt;
            self->_st1 = 2; self->_st3 = 0; self->_st2 = 0;
            self->_st2 = self->_cursor; self->_st3 = 0;
            self->_st3 = 0x3E7;
            FUN_0041d510(self, 1, 0, cnt);
            return;
        }
        case 2:
            if (!WIN_PENDING()) {
                if (self->_retCode != -1 && (self->_st2 != self->_retCode || self->_st3 == 0x3E7)) {
                    FUN_0041d510(self, 0, 1);
                    self->_st2 = self->_retCode;
                    self->_st3 = 0;
                    return;
                }
                break;
            }
            switch (self->_retCode) {
            case -1:
                NEXT_ST0()
                return;
            default:
                self->_st1 = self->_st1 + 1; self->_st3 = 0; self->_st2 = 0;
                self->_cursor = self->_retCode;
                return;
            }
        case 3:
            switch (self->_st2) {
            case 0: {
                void *al;
                *(Q48 *)tq = *(const Q48 *)DAT_004cf700;
                vecA[0] = -121.0f; vecA[1] = 128.0f; vecA[2] = 0.0f;
                beNDMWWindow_PresentModel(self, DAT_00519d88, 0, tq[self->_cursor], 0, vecA);
                GET_ALLOC(al)
                { SelectE1Ref actionWin(FUN_003b51b0(al));
                beNDMWWindow_BindContext(actionWin.p, self, self->_insight, self->_playerNo, 0);
                ObjectList_AppendRetained(self->_subWindow, actionWin.p);
                WSETI84(actionWin.p, 2)
                WSETPOS(actionWin.p, 115.0f, 145.0f, 0.0f)
                WSETI100(actionWin.p, 0)
                beNDMWWindow_PresentModelAtOrigin(actionWin.p, DAT_0051a180, 0, DAT_00519eb8, DAT_00519a58);
                FUN_003f5410(actionWin.p, DAT_0051a190, DAT_004cf670[0], DAT_00519b60, DAT_00519b68);
                FUN_003f5410(actionWin.p, DAT_0051a190, DAT_004cf674[0], DAT_00519b60, DAT_00519b68);
                }
                SYNC_COUNT()
                NEXT_ST2()
            }
            case 1:
                beNDMWWindow_RunMessageScript(self, DAT_00519b90, 0x41);
                NEXT_ST2()
            case 2:
                if (WIN_PENDING()) {
                    switch (self->_retCode) {
                    case 0: self->_st1 = 4; self->_st3 = 0; self->_st2 = 0; return;
                    case 1: self->_st1 = 5; self->_st3 = 0; self->_st2 = 0; return;
                    default:
                        SEND_CLOSE();
                        RESET_ST1()
                        return;
                    }
                }
                break;
            }
            break;
        case 4:
            switch (self->_st2) {
            case 0: {
                void *al;
                int i;
                GET_ALLOC(al)
                { SelectE1Ref orderWin(FUN_003b51b0(al));
                beNDMWWindow_BindContext(orderWin.p, self, self->_insight, self->_playerNo, 0);
                ObjectList_AppendRetained(self->_subWindow, orderWin.p);
                MSG_SELECT_INT(self->_playerNo)
                igProperty_GetRecordFolder(beMessenger_GetObject(self->_messenger, 0), DAT_0051a150);
                WSETI84(orderWin.p, 10)
                WSETPOS(orderWin.p, -121.0f, 128.0f, 0.0f)
                WSETI100(orderWin.p, self->_cursor)
                GET_ALLOC(al)
                DecideListRef decided(FUN_002cb0d0(al));
                for (i = 0; i < 10; i++) {
                    if (i == self->_cursor) { BLIST_ADD(decided, GPR_00554a30) } else { BLIST_ADD(decided, GPR_00554a34) }
                }
                FUN_0041d490(&((beNDMWWindowSelect *)orderWin.p)->_decideList, decided.p);
                }
                SYNC_COUNT()
                NEXT_ST2()
            }
            case 1:
                NEXT_ST2()
                self->_st3 = self->_cursor;
                return;
            case 2:
                if (!WIN_PENDING()) {
                    if (self->_retCode != -1 && self->_st3 != self->_retCode) {
                        FUN_0041d510(self, 0, 1);
                        self->_st3 = self->_retCode;
                        return;
                    }
                } else {
                    if (self->_retCode != -1) {
                        igObjectList *l;
                        MSG_SELECT_INT(self->_playerNo)
                        l = (igObjectList *)igProperty_GetRecordFolder(beMessenger_GetObject(self->_messenger, 0), DAT_0051a150)[3];
                        SwapRef cursorDisk(((void **)l->_data)[self->_cursor]);
                        SwapRef targetDisk(((void **)l->_data)[self->_retCode]);
                        ObjectList_SetAtRetained_003e9160(l, self->_cursor, targetDisk.p);
                        ObjectList_SetAtRetained_003e9160(l, self->_retCode, cursorDisk.p);
                    }
                    SEND_CLOSE();
                    RESET_ST1()
                    return;
                }
                break;
            }
            break;
        case 5:
            switch (self->_st2) {
            case 0: {
                void *al;
                int i;
                beNDMWItemDisk *item;
                MSG_SELECT_INT(self->_playerNo)
                item = (beNDMWItemDisk *)((int *)((igObjectList *)igProperty_GetRecordFolder(beMessenger_GetObject(self->_messenger, 0), DAT_0051a150)[3])->_data)[self->_cursor];
                if (item->_kazu <= 0) {
                    GET_ALLOC(al)
                    { ConfirmRef emptyWin(FUN_003b4f50(al));
                    beNDMWWindow_BindContext(emptyWin.p, self, self->_insight, self->_playerNo, 0);
                    ObjectList_AppendRetained(self->_subWindow, emptyWin.p);
                    NEXT_ST2()
                    INTERN_APPEND(((beNDMWWindowSelect *)emptyWin.p)->_textCloseTypeList, DAT_00519b50)
                    INTERNP_APPEND(((beNDMWWindowSelect *)emptyWin.p)->_textCloseNameList, DAT_004cf670[0])
                    beNDMWWindow_RunMessageScript(emptyWin.p, DAT_00519b90, 0x8D);
                    }
                } else {
                    igObjectList *dk;
                    ((igObjectList *)self->_playerNoList)->_count = 0;
                    dk = (igObjectList *)self->_diskList;
                    FUN_0041d3f0(dk, 0, dk->_count);
                    FUN_0041d3b0(dk, 0, dk->_count);
                    dk->_count = 0;
                    for (i = 0; i < 4; i++) {
                        int obj;
                        MSG_SELECT_INT(i)
                        obj = beMessenger_GetObject(self->_messenger, 0);
                        if (((unsigned char *)igProperty_GetRecordByte(obj, DAT_0051a1a0))[12] != 0 && i != self->_playerNo) {
                            LIST_ADD(self->_playerNoList, i)
                            {
                            igObjectList *fl = (igObjectList *)igProperty_GetRecordFolder(obj, DAT_0051a150)[3];
                            beNDMWItemDisk *found = 0;
                            int k;
                            for (k = 0; k < fl->_count; k++) {
                                beNDMWItemDisk *e = ((beNDMWItemDisk **)fl->_data)[k];
                                if (e->_recNo == item->_recNo) { found = e; break; }
                            }
                            if (found != 0) ObjectList_AppendRetained(self->_diskList, found);
                            else ObjectList_AppendRetained(self->_diskList, 0);
                            }
                        }
                    }
                    if (((igObjectList *)self->_playerNoList)->_count <= 0) {
                        GET_ALLOC(al)
                        { ConfirmRef noPlayerWin(FUN_003b4f50(al));
                        beNDMWWindow_BindContext(noPlayerWin.p, self, self->_insight, self->_playerNo, 0);
                        ObjectList_AppendRetained(self->_subWindow, noPlayerWin.p);
                        NEXT_ST2()
                        INTERN_APPEND(((beNDMWWindowSelect *)noPlayerWin.p)->_textCloseTypeList, DAT_00519b50)
                        INTERNP_APPEND(((beNDMWWindowSelect *)noPlayerWin.p)->_textCloseNameList, DAT_004cf670[0])
                        beNDMWWindow_RunMessageScript(noPlayerWin.p, DAT_00519b90, 0x8E);
                        }
                    } else {
                        self->_st1 = 6; self->_st3 = 0; self->_st2 = 0;
                        self->_receipt = 0;
                        return;
                    }
                }
                break;
            }
            case 1:
                SYNC_COUNT()
                NEXT_ST2()
            case 2:
                if (WIN_PENDING()) {
                    SEND_CLOSE();
                    RESET_ST1()
                    return;
                }
                break;
            }
            break;
        case 6:
            switch (self->_st2) {
            case 0:
                SEND_CLOSE();
                beNDMWWindow_PlayQueuedModelClose(self);
                CLOSE_LISTS()
                beNDMWWindow_ClearQueuedText(self);
            case 1:
                NEXT_ST2()
                return;
            case 2: {
                int i;
                beNDMWItemBase *item;
                igObjectList *lsx;
                switch (((igObjectList *)self->_playerNoList)->_count) {
                case 1:
                default:
                    beNDMWWindow_PresentModelAtOrigin(self, DAT_0051a180, 0, DAT_0051a1a8, DAT_00519a58);
                    break;
                case 2:
                    beNDMWWindow_PresentModelAtOrigin(self, DAT_0051a180, 0, DAT_0051a1b8, DAT_00519a58);
                    break;
                case 3:
                    beNDMWWindow_PresentModelAtOrigin(self, DAT_0051a180, 0, DAT_0051a1c8, DAT_00519a58);
                    break;
                }
                INTERN_APPEND(self->_textCloseTypeList, DAT_0051a1d8)
                INTERN_APPEND(self->_textCloseNameList, DAT_005199e0)
                INTERN_APPEND(self->_textCloseTypeList, DAT_0051a1d8)
                INTERN_APPEND(self->_textCloseNameList, DAT_005199e8)
                beNDMWWindow_RunMessageScript(self, DAT_00519b90, 0x4A);
                MSG_SELECT_INT(self->_playerNo)
                lsx = (igObjectList *)igProperty_GetRecordFolder(beMessenger_GetObject(self->_messenger, 0), DAT_0051a150)[3];
                FUN_003f5410(self, DAT_0051a060, DAT_005199e0, beNDMWItemBase_GetRecordString(item = (beNDMWItemBase *)((int *)lsx->_data)[self->_cursor], FUN_00236f80(self->_insight, DAT_0058b028[0]), DAT_00519f28), DAT_00519b68);
                ObjectRef_Retain_003e90d0(item);
                ObjectRef_Release_003e9110(self->_sendDisk);
                self->_sendDisk = (int)item;
                names = DAT_004cf730;
                for (i = 0; i < ((igObjectList *)self->_playerNoList)->_count; i++) {
                    int pno = ((int *)((igObjectList *)self->_playerNoList)->_data)[i];
                    igObjectList *l2;
                    MSG_SELECT_INT(pno)
                    l2 = (igObjectList *)igProperty_GetRecordFolder(beMessenger_GetObject(self->_messenger, 0), DAT_0051a1e8)[3];
                    if (l2->_count > 0) {
                        DeviceRef firstDevice((void *)*(int *)l2->_data);
                        FUN_003f56d0(self, DAT_0051a060, names.v[i], DeviceRef(firstDevice), DAT_00519b68);
                    }
                    bufC[0] = ((beNDMWItemDisk *)((int *)((igObjectList *)self->_diskList)->_data)[i])->_kazu + 0x30;
                    bufC[1] = 0;
                    FUN_003f5410(self, DAT_0051a170, names.v[i], bufC, DAT_0051a1f8);
                }
                {
                    char bufA[2];
                    bufA[0] = ((beNDMWItemDisk *)self->_sendDisk)->_kazu + 0x30;
                    bufA[1] = 0;
                    FUN_003f5410(self, DAT_0051a200, DAT_005199e0, bufA, DAT_0051a1f8);
                }
                FUN_003f5410(self, DAT_0051a200, DAT_005199e8, DAT_0051a210, DAT_0051a1f8);
                NEXT_ST2()
            }
            case 3: {
                void *al;
                GET_ALLOC(al)
                { SelectE1Ref playerWin(FUN_003b51b0(al));
                beNDMWWindow_BindContext(playerWin.p, self, self->_insight, self->_playerNo, 0);
                ObjectList_AppendRetained(self->_subWindow, playerWin.p);
                WSETPOS(playerWin.p, -121.0f, 109.0f, 0.0f)
                WSETI84(playerWin.p, ((igObjectList *)self->_playerNoList)->_count)
                WSETI100(playerWin.p, self->_receipt)
                }
                SYNC_COUNT()
                NEXT_ST2()
            }
            case 4:
                if (WIN_PENDING()) {
                    if (self->_retCode == -1) {
                        self->_st1 = 7; self->_st3 = 0; self->_st2 = 0;
                        return;
                    }
                    self->_receipt = self->_retCode;
                    if (((beNDMWItemDisk *)((int *)((igObjectList *)self->_diskList)->_data)[self->_receipt])->_kazu >= 9) {
                        self->_st2 = 10; self->_st3 = 0;
                        return;
                    }
                    switch (self->_receipt) {
                    case 0:
                        vecB[0] = -121.0f; vecB[1] = 109.0f; vecB[2] = 0.0f;
                        beNDMWWindow_PresentModel(self, DAT_00519d88, 0, DAT_00519cc8, 0, vecB);
                        break;
                    case 1:
                        vecC[0] = -121.0f; vecC[1] = 109.0f; vecC[2] = 0.0f;
                        beNDMWWindow_PresentModel(self, DAT_00519d88, 0, DAT_00519cd8, 0, vecC);
                        break;
                    case 2:
                        vecD[0] = -121.0f; vecD[1] = 109.0f; vecD[2] = 0.0f;
                        beNDMWWindow_PresentModel(self, DAT_00519d88, 0, DAT_00519ce8, 0, vecD);
                        break;
                    }
                    NEXT_ST2()
                    return;
                }
                break;
            case 5: {
                void *al;
                int a1, v0;
                GET_ALLOC(al)
                { QuantityRef quantityWin(FUN_003b4410(al));
                a1 = ((beNDMWItemDisk *)self->_sendDisk)->_kazu;
                v0 = 9 - ((beNDMWItemDisk *)((int *)((igObjectList *)self->_diskList)->_data)[self->_receipt])->_kazu;
                self->_sendMax = (a1 < v0) ? a1 : v0;
                beNDMWWindow_BindContext(quantityWin.p, self, self->_insight, self->_playerNo, self->_sendMax);
                ObjectList_AppendRetained(self->_subWindow, quantityWin.p);
                WSETPOS(quantityWin.p, 68.0f, -3.0f, 0.0f)
                }
                SYNC_COUNT()
                NEXT_ST2()
                return;
            }
            case 6: {
                char bufB[2];
                bufB[0] = (self->_sendMax + 0x30) - self->_retCode;
                bufB[1] = 0;
                MSG_STR3(DAT_0051a200, DAT_005199e8, bufB, DAT_00519f30)
            }
                NEXT_ST2()
                self->_st3 = self->_retCode;
            case 7:
                if (!WIN_PENDING()) {
                    if (self->_retCode != -1 && self->_retCode != self->_st3) {
                        self->_st2 = 6; self->_st3 = 0;
                        return;
                    }
                } else {
                    int rc = self->_retCode;
                    if (rc == -1) {
                        MSG_STR3(DAT_0051a200, DAT_005199e8, DAT_0051a210, DAT_00519f30)
                        SEND_CLOSE();
                        self->_st2 = 3; self->_st3 = 0;
                        return;
                    }
                    {
                        void *al;
                        rc = self->_sendMax - rc;
                        beNDMWItemDisk *sd = (beNDMWItemDisk *)self->_sendDisk;
                        beNDMWItemDisk *tg = ((beNDMWItemDisk **)((igObjectList *)self->_diskList)->_data)[self->_receipt];
                        { unsigned q = sd->_kazu; sd->_kazu = q - rc; }
                        { unsigned q = tg->_kazu; tg->_kazu = rc + q; }
                        GET_ALLOC(al)
                        { ConfirmRef sentWin(FUN_003b4f50(al));
                        beNDMWWindow_BindContext(sentWin.p, self, self->_insight, self->_playerNo, 0);
                        ObjectList_AppendRetained(self->_subWindow, sentWin.p);
                        beNDMWWindow_RunMessageScript(self, DAT_00519b90, 0x84);
                        }
                        SYNC_COUNT()
                        NEXT_ST2()
                        return;
                    }
                }
                break;
            case 8:
                if (WIN_PENDING()) {
                    MSG_STR3(DAT_00519b50, DAT_005199e0, DAT_00519b00, DAT_00519b08)
                    MSG_STR3(DAT_0051a200, DAT_005199e8, DAT_0051a210, DAT_00519f30)
                    SEND_CLOSE();
                    self->_st1 = 7; self->_st3 = 0; self->_st2 = 0;
                    return;
                }
                break;
            case 10: {
                void *al;
                GET_ALLOC(al)
                { ConfirmRef fullWin(FUN_003b4f50(al));
                beNDMWWindow_BindContext(fullWin.p, self, self->_insight, self->_playerNo, 0);
                ObjectList_AppendRetained(self->_subWindow, fullWin.p);
                INTERN_APPEND(((beNDMWWindowSelect *)fullWin.p)->_textCloseTypeList, DAT_00519b50)
                INTERNP_APPEND(((beNDMWWindowSelect *)fullWin.p)->_textCloseNameList, DAT_004cf670[0])
                beNDMWWindow_RunMessageScript(fullWin.p, DAT_00519b90, 0x8F);
                }
                SYNC_COUNT()
                NEXT_ST2()
            }
            case 11:
                if (WIN_PENDING()) {
                    MSG_STR3(DAT_0051a200, DAT_005199e8, DAT_0051a210, DAT_00519f30)
                    SEND_CLOSE();
                    self->_st2 = 3; self->_st3 = 0;
                    return;
                }
                break;
            }
            break;
        case 7:
            switch (self->_st2) {
            case 0:
                beNDMWWindow_PlayQueuedModelClose(self);
                CLOSE_LISTS()
                beNDMWWindow_ClearQueuedText(self);
                NEXT_ST2()
            case 1:
                self->_st0 = 0; self->_st3 = 0; self->_st2 = 0; self->_st1 = 0;
                self->_st1 = 1; self->_st3 = 0; self->_st2 = 0;
                return;
            }
            break;
        }
        break;
    case 2:
        beNDMWWindow_PlayQueuedModelClose(self);
        beNDMWWindow_ClearQueuedText(self);
        beNDMWWindow_RequestChildrenClose(self);
        NEXT_ST0()
        return;
    case 3:
        if (beNDMWWindow_PollCloseComplete(self) != 0) {
            self->_isRun = 0;
        }
        break;
    }
}
