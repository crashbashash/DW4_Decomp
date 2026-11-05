/* 0x0041acf0 Gap__Bec__beNDMWStatusCtrlDisk__vfunc_21: update state machine of the status-screen
 * disk sub-menu. */
#include "dw4/reflected.h"

extern "C" {
void *FUN_002eb010(int);
void *StringPool_Construct(void *);
const char *StringPool_Intern(void *, const char *);
void StringChunk_ReleaseHeader(int, int *);
int StringList_AppendRetained(int, const char **);
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
void FUN_003f56d0(...);
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
struct RP { RefHeader *p; ~RP() {} };
struct HA { static int Add(int a, int b) { return a + b; } };

#define RETAIN_REF(q) { RefHeader *rr = (RefHeader *)(q); if (rr) ++rr->_refCount; }
#define RELEASE_REF(q) { RefHeader *rr = (RefHeader *)(q); \
    if (rr) { --rr->_refCount; if (!(rr->_refCount & 0x7fffff)) igObject_Destroy(rr); } }
#define RETAIN_DIRECT(r) { if ((r).p != 0) (r).p->_refCount = (r).p->_refCount + 1; }
#define RELEASE_DIRECT(r) { if ((r).p != 0) { (r).p->_refCount = (r).p->_refCount - 1; if (!((r).p->_refCount & 0x7fffff)) igObject_Destroy((r).p); } }
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
#define RELEASE_STR(slot) { const char *held = slot; \
    if (held != 0) { int *hd = (int *)held - 2; \
        int cnt = ((int *)held)[-1] - 1; ((int *)held)[-1] = cnt; \
        if (cnt == 0) StringChunk_ReleaseHeader(*hd, hd); } }
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
#define INTERNP_APPEND(slot, field, ptr) { INTERNP(slot, ptr) StringList_AppendRetained(field, &slot); RELEASE_STR(slot) }
#define INTERN_APPEND(slot, field, text) { INTERN(slot, text) StringList_AppendRetained(field, &slot); RELEASE_STR(slot) }
#define MSG_SELECT_INT(v) { beMessenger_SelectGroup(self->_messenger, DAT_00519ba0); \
    beMessenger_AppendInt(self->_messenger, v); beMessenger_DispatchSelected(self->_messenger, DAT_00519ba8); }
#define NEXT_ST0() { self->_st0 = self->_st0 + 1; self->_st3 = 0; self->_st2 = 0; self->_st1 = 0; }
#define NEXT_ST2() { self->_st2 = self->_st2 + 1; self->_st3 = 0; }
#define SYNC_COUNT() { self->_nowProcKazu = ((igObjectList *)self->_subWindow)->_count; }
#define WIN_PENDING() (((igObjectList *)self->_subWindow)->_count != self->_nowProcKazu)
#define BLIST_ADD(r, v) { int n; igDataList *dl = (igDataList *)(r).p; n = dl->_count; \
    if (n < dl->_capacity) dl->_count = n + 1; else List_Resize(dl, n + 1, 1); \
    ((unsigned char *)dl->_data)[n] = (v); }
#define LIST_ADD(lst, val) { int n_ = ((igDataList *)(lst))->_count; igDataList *l_ = (igDataList *)(lst); \
    if (n_ < l_->_capacity) l_->_count = *(volatile int *)&l_->_count + 1; else List_Resize(l_, n_ + 1, 4); \
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

extern "C" void Gap__Bec__beNDMWStatusCtrlDisk__vfunc_21(beNDMWStatusCtrlDisk *self);
void Gap__Bec__beNDMWStatusCtrlDisk__vfunc_21(beNDMWStatusCtrlDisk *self)
{
    RP wA;
    RP wB;
    RP wC;
    RP lst;
    RP rA;
    RP rB;
    RP wD;
    RP wE;
    RP rC;
    char bufA[2];
    RP wF;
    RP wG;
    char bufB[2];
    RP wH;
    RP wI;
    const char *tk0, *tk1, *tk2, *tk3, *tk4, *tk5, *tk6, *tk7, *tk8, *tk9, *tk10, *tk11;
    RP rD;
    const char *tk12, *tk13;
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
        INTERN_APPEND(tk0, self->_textCloseTypeList, DAT_0051a040)
        INTERNP_APPEND(tk1, self->_textCloseNameList, DAT_004cf670[0])
        beNDMWWindow_RunMessageScript(self, DAT_00519b90, 0x48);
        for (i = 0; i < 12; i++)
            FUN_003f5410(self, DAT_0051a060, DAT_004cf670[i], DAT_00519b60, DAT_00519b68);
        for (j = 0; j < 12; j++)
            FUN_003f5410(self, DAT_0051a170, DAT_004cf670[j], DAT_00519b60, DAT_0051a080);
        FUN_003f5410(self, DAT_00519b50, DAT_004cf670[0], DAT_00519b60, DAT_00519b68);
        NEXT_ST0()
    }
    case 1:
        switch (*(volatile int *)&self->_st1) {
        case 0: {
            void *al;
            int cnt;
            GET_ALLOC(al)
            wA.p = (RefHeader *)FUN_003b51b0(al);
            beNDMWWindow_BindContext(wA.p, self, self->_insight, self->_playerNo, 0);
            ObjectList_AppendRetained(self->_subWindow, wA.p);
            MSG_SELECT_INT(self->_playerNo)
            igProperty_GetRecordFolder(beMessenger_GetObject(self->_messenger, 0), DAT_0051a150);
            WSETI84(wA.p, 10)
            WSETPOS(wA.p, -121.0f, 128.0f, 0.0f)
            WSETI100(wA.p, self->_cursor)
            INTERN_APPEND(tk2, ((beNDMWWindowSelect *)wA.p)->_textCloseTypeList, DAT_00519b50)
            INTERN_APPEND(tk3, ((beNDMWWindowSelect *)wA.p)->_textCloseNameList, DAT_00519d98)
            beNDMWWindow_RunMessageScript(wA.p, DAT_00519b90, 0x2B);
            RELEASE_REF(wA.p)
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
                const Q128 *qs = (const Q128 *)DAT_004cf700;
                Q128 *qd = (Q128 *)tq;
                Q128 q0 = *qs++; Q128 q1 = *qs++; Q128 q2 = *qs;
                qd[0] = q0; qd[1] = q1; qd[2] = q2;
                vecA[0] = -121.0f; vecA[1] = 128.0f; vecA[2] = 0.0f;
                beNDMWWindow_PresentModel(self, DAT_00519d88, 0, tq[self->_cursor], 0, vecA);
                GET_ALLOC(al)
                wB.p = (RefHeader *)FUN_003b51b0(al);
                beNDMWWindow_BindContext(wB.p, self, self->_insight, self->_playerNo, 0);
                ObjectList_AppendRetained(self->_subWindow, wB.p);
                WSETI84(wB.p, 2)
                WSETPOS(wB.p, 115.0f, 145.0f, 0.0f)
                WSETI100(wB.p, 0)
                beNDMWWindow_PresentModelAtOrigin(wB.p, DAT_0051a180, 0, DAT_00519eb8, DAT_00519a58);
                FUN_003f5410(wB.p, DAT_0051a190, DAT_004cf670[0], DAT_00519b60, DAT_00519b68);
                FUN_003f5410(wB.p, DAT_0051a190, DAT_004cf674[0], DAT_00519b60, DAT_00519b68);
                RELEASE_REF(wB.p)
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
                wC.p = (RefHeader *)FUN_003b51b0(al);
                beNDMWWindow_BindContext(wC.p, self, self->_insight, self->_playerNo, 0);
                ObjectList_AppendRetained(self->_subWindow, wC.p);
                MSG_SELECT_INT(self->_playerNo)
                igProperty_GetRecordFolder(beMessenger_GetObject(self->_messenger, 0), DAT_0051a150);
                WSETI84(wC.p, 10)
                WSETPOS(wC.p, -121.0f, 128.0f, 0.0f)
                WSETI100(wC.p, self->_cursor)
                GET_ALLOC(al)
                lst.p = (RefHeader *)FUN_002cb0d0(al);
                for (i = 0; i < 10; i++) {
                    if (i == self->_cursor) { BLIST_ADD(lst, GPR_00554a30) } else { BLIST_ADD(lst, GPR_00554a34) }
                }
                FUN_0041d490(&((beNDMWWindowSelect *)wC.p)->_decideList, lst.p);
                RELEASE_REF(lst.p)
                RELEASE_REF(wC.p)
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
                        rA.p = (RefHeader *)((int *)l->_data)[self->_cursor];
                        RETAIN_REF(rA.p)
                        rB.p = (RefHeader *)((int *)l->_data)[self->_retCode];
                        RETAIN_REF(rB.p)
                        ObjectList_SetAtRetained_003e9160(l, self->_cursor, rB.p);
                        ObjectList_SetAtRetained_003e9160(l, self->_retCode, rA.p);
                        RELEASE_REF(rB.p)
                        RELEASE_REF(rA.p)
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
                    wD.p = (RefHeader *)FUN_003b4f50(al);
                    beNDMWWindow_BindContext(wD.p, self, self->_insight, self->_playerNo, 0);
                    ObjectList_AppendRetained(self->_subWindow, wD.p);
                    NEXT_ST2()
                    INTERN_APPEND(tk4, ((beNDMWWindowSelect *)wD.p)->_textCloseTypeList, DAT_00519b50)
                    INTERNP_APPEND(tk5, ((beNDMWWindowSelect *)wD.p)->_textCloseNameList, DAT_004cf670[0])
                    beNDMWWindow_RunMessageScript(wD.p, DAT_00519b90, 0x8D);
                    RELEASE_REF(wD.p)
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
                        wE.p = (RefHeader *)FUN_003b4f50(al);
                        beNDMWWindow_BindContext(wE.p, self, self->_insight, self->_playerNo, 0);
                        ObjectList_AppendRetained(self->_subWindow, wE.p);
                        NEXT_ST2()
                        INTERN_APPEND(tk6, ((beNDMWWindowSelect *)wE.p)->_textCloseTypeList, DAT_00519b50)
                        INTERNP_APPEND(tk7, ((beNDMWWindowSelect *)wE.p)->_textCloseNameList, DAT_004cf670[0])
                        beNDMWWindow_RunMessageScript(wE.p, DAT_00519b90, 0x8E);
                        RELEASE_REF(wE.p)
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
                INTERN_APPEND(tk8, self->_textCloseTypeList, DAT_0051a1d8)
                INTERN_APPEND(tk9, self->_textCloseNameList, DAT_005199e0)
                INTERN_APPEND(tk10, self->_textCloseTypeList, DAT_0051a1d8)
                INTERN_APPEND(tk11, self->_textCloseNameList, DAT_005199e8)
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
                        rC.p = (RefHeader *)*(int *)l2->_data;
                        RETAIN_REF(rC.p)
                        rD.p = rC.p;
                        RETAIN_DIRECT(rD)
                        FUN_003f56d0(self, DAT_0051a060, names.v[i], &rD, DAT_00519b68);
                        RELEASE_DIRECT(rD)
                        RELEASE_REF(rC.p)
                    }
                    bufC[0] = ((beNDMWItemDisk *)((int *)((igObjectList *)self->_diskList)->_data)[i])->_kazu + 0x30;
                    bufC[1] = 0;
                    FUN_003f5410(self, DAT_0051a170, names.v[i], bufC, DAT_0051a1f8);
                }
                bufA[0] = ((beNDMWItemDisk *)self->_sendDisk)->_kazu + 0x30;
                bufA[1] = 0;
                FUN_003f5410(self, DAT_0051a200, DAT_005199e0, bufA, DAT_0051a1f8);
                FUN_003f5410(self, DAT_0051a200, DAT_005199e8, DAT_0051a210, DAT_0051a1f8);
                NEXT_ST2()
            }
            case 3: {
                void *al;
                GET_ALLOC(al)
                wF.p = (RefHeader *)FUN_003b51b0(al);
                beNDMWWindow_BindContext(wF.p, self, self->_insight, self->_playerNo, 0);
                ObjectList_AppendRetained(self->_subWindow, wF.p);
                WSETPOS(wF.p, -121.0f, 109.0f, 0.0f)
                WSETI84(wF.p, ((igObjectList *)self->_playerNoList)->_count)
                WSETI100(wF.p, self->_receipt)
                RELEASE_REF(wF.p)
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
                wG.p = (RefHeader *)FUN_003b4410(al);
                a1 = ((beNDMWItemDisk *)self->_sendDisk)->_kazu;
                v0 = 9 - ((beNDMWItemDisk *)((int *)((igObjectList *)self->_diskList)->_data)[self->_receipt])->_kazu;
                self->_sendMax = (a1 < v0) ? a1 : v0;
                beNDMWWindow_BindContext(wG.p, self, self->_insight, self->_playerNo, self->_sendMax);
                ObjectList_AppendRetained(self->_subWindow, wG.p);
                WSETPOS(wG.p, 68.0f, -3.0f, 0.0f)
                RELEASE_REF(wG.p)
                SYNC_COUNT()
                NEXT_ST2()
                return;
            }
            case 6:
                bufB[0] = (self->_sendMax + 0x30) - self->_retCode;
                bufB[1] = 0;
                MSG_STR3(DAT_0051a200, DAT_005199e8, bufB, DAT_00519f30)
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
                        igObjectList &dl = *(igObjectList *)self->_diskList;
                        int rcpt;
                        int mx = *(volatile int *)&self->_sendMax;
                        rcpt = self->_receipt;
                        beNDMWItemDisk &sd = *(beNDMWItemDisk *)self->_sendDisk;
                        const int &d = mx - rc;
                        beNDMWItemDisk &tg = *((beNDMWItemDisk **)dl._data)[rcpt];
                        sd._kazu = sd._kazu - d;
                        tg._kazu = HA::Add(d, tg._kazu);
                        GET_ALLOC(al)
                        wH.p = (RefHeader *)FUN_003b4f50(al);
                        beNDMWWindow_BindContext(wH.p, self, self->_insight, self->_playerNo, 0);
                        ObjectList_AppendRetained(self->_subWindow, wH.p);
                        beNDMWWindow_RunMessageScript(self, DAT_00519b90, 0x84);
                        RELEASE_REF(wH.p)
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
                wI.p = (RefHeader *)FUN_003b4f50(al);
                beNDMWWindow_BindContext(wI.p, self, self->_insight, self->_playerNo, 0);
                ObjectList_AppendRetained(self->_subWindow, wI.p);
                INTERN_APPEND(tk12, ((beNDMWWindowSelect *)wI.p)->_textCloseTypeList, DAT_00519b50)
                INTERNP_APPEND(tk13, ((beNDMWWindowSelect *)wI.p)->_textCloseNameList, DAT_004cf670[0])
                beNDMWWindow_RunMessageScript(wI.p, DAT_00519b90, 0x8F);
                RELEASE_REF(wI.p)
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
