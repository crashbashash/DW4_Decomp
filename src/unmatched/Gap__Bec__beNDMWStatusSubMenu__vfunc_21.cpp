/* Update state machine of the status-screen sub-menu (_st0 open / run / close / wait-close, _st1
 * menu choice 0..3, _st2 step, _st3 argument). RP slots are the memory-resident smart-pointer
 * temporaries (the empty destructor keeps them on the stack); the interned-string temporaries
 * tk0..tk11 and the Ref temporaries r1xx are address-taken locals. The branch-delay hoisting of
 * the pool-init `li a0,16` / `move a0,v0` words only turns off when the post-RA jump optimiser
 * deletes at least one jump to the next block; the player-count presentation switch provides that
 * when its default body comes first (case 1 + default share it), so the compare chain falls into
 * it without a trailing jump. Keep `case 1: default:` first. Helpers::AppendBoth is the inlined
 * two-list append used twice (same registers both times). DAT_004cf790 is the compiler's own image
 * of a local const char *[3] initialiser; declaring it as an extern Str3 object gives the ld/lwc1
 * block move. DAT_004cf760 (12 model-name pointers) is copied with three quadword loads then three
 * stores. Locals of the case-3 step 0 block are declared in the order rec, i, nN, item, lL, ctx,
 * flag; that order (not the macro form) decides the saved-register colouring of the list append. */
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
void ObjectList_RemoveFirstRetained(...);
void *ObjectList_GetAt_003e9260(...);
void ObjectRef_Release_003e9110(...);
void ObjectRef_Retain_003e90d0(...);
void FUN_00406f20(...);
int FUN_00236f80(...);
void *FUN_003b4f50(void *);
void *FUN_003b51b0(void *);
void *FUN_003b5370(void *);
void *FUN_003c90f0(void *);
void FUN_00422c00(...);
void FUN_00423000(...);
void FUN_003f5410(...);
void FUN_003f56d0(...);
void FUN_00447d00(...);
void beMessenger_SelectGroup(...);
void beMessenger_AppendInt(...);
void beMessenger_AppendString(...);
void beMessenger_AppendVec3(...);
void beMessenger_DispatchSelected(...);
void beMessenger_SendNamed(...);
int beMessenger_GetObject(int, int);
int *igProperty_GetRecordFolder(int, const void *);
int *igProperty_GetRecordByte(int, const void *);
int beNDMWItemBase_GetRecordBool(...);
int beNDMWItemBase_GetRecordString(...);
void beNDMWWindow_PresentModel(...);
void beNDMWWindow_PresentModelAtOrigin(...);
void beNDMWWindow_RunMessageScript(...);
void beNDMWWindow_BindContext(...);
void beNDMWWindow_SendModelSequence(...);
void beNDMWWindow_ClearQueuedText(...);
void beNDMWWindow_PlayQueuedModelClose(...);
void beNDMWWindow_RequestChildrenClose(...);
int beNDMWWindow_PollCloseComplete(...);
extern void *DAT_00586f20[4];
extern int DAT_00587110[4];
extern int DAT_0058b028[4];
extern unsigned char GPR_00554c14;
extern int DAT_004cf760[12];
extern int DAT_004cf670[4];
extern int DAT_004cf674[4];
extern int DAT_004cf678[4];
extern int DAT_00519d88[4];
extern int DAT_00519a58[4];
extern int DAT_0051a180[4];
extern int DAT_00519ec8[4];
extern int DAT_0051a190[4];
extern int DAT_005199e0[4];
extern int DAT_0051a060[4];
extern int DAT_00519b90[4];
extern int DAT_00519b50[4];
extern int DAT_00519ba0[4];
extern int DAT_00519ba8[4];
extern int DAT_00519c00[4];
extern int DAT_00519bb8[4];
extern int DAT_00519bc8[4];
extern int DAT_00519bd8[4];
extern int DAT_00519be0[4];
extern int DAT_00519bf0[4];
extern int DAT_0051a3e0[4];
extern int DAT_0051a3e8[4];
extern int DAT_0051a3f8[4];
extern int DAT_0051a408[4];
extern int DAT_0051a418[4];
extern int DAT_0051a1a0[4];
extern int DAT_0051a1d8[4];
extern int DAT_0051a1e8[4];
extern int DAT_00519f28[4];
extern int DAT_00519f38[4];
extern int DAT_00519b68[4];
extern int DAT_00519c28[4];
extern int DAT_00519c30[4];
extern int DAT_00519a90[4];
extern int DAT_00519cc8[4];
extern int DAT_00519cd8[4];
extern int DAT_00519ce8[4];
}

typedef unsigned __int128 Q128;
struct Str3 { const char *v[3]; };
extern Str3 DAT_004cf790;
struct RP { igObject *p; ~RP() {} };

#define RETAIN_REF(q) { igObject *rr = (igObject *)(q); if (rr) ++rr->_refCount; }
#define RELEASE_REF(q) { igObject *rr = (igObject *)(q); \
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
/* The select windows made here are beNDMWStatusSelectE1 and beNDMWStatusSelectE0; their
 * +84/+88/+100 words are _selectMax, _offsetPos (an igVec3f: two floats and a zero word, reflected
 * as int[3]) and _startPoint. */
#define WSETI84(T, w, v) { T *wt = (T *)(w); wt->_selectMax = (v); }
#define WSETI100(T, w, v) { T *wt = (T *)(w); wt->_startPoint = (v); }
#define WSETPOS(T, w, x, y, z) { T *wt = (T *)(w); *(float *)&wt->_offsetPos[0] = (x); *(float *)&wt->_offsetPos[1] = (y); wt->_offsetPos[2] = (z); }
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
#define LIST_ADD(lst, val) { int n_ = ((igDataList *)(lst))->_count; igDataList *l_ = (igDataList *)(lst); \
    if (n_ < l_->_capacity) l_->_count = *(volatile int *)&l_->_count + 1; else List_Resize(l_, n_ + 1, 4); \
    ((int *)l_->_data)[n_] = (val); }
#define LIST_REMOVE(lst, idx) { igObjectList *l_ = (igObjectList *)(lst); int ix_ = (idx); \
    ObjectRef_Release_003e9110(ObjectList_GetAt_003e9260(l_, ix_)); FUN_00406f20(l_, ix_); \
    ((int *)l_->_data)[l_->_count] = 0; }
#define MSG_SELECT_INT(v) { beMessenger_SelectGroup(self->_messenger, DAT_00519ba0); \
    beMessenger_AppendInt(self->_messenger, v); beMessenger_DispatchSelected(self->_messenger, DAT_00519ba8); }
#define NEXT_ST0() { self->_st0 = self->_st0 + 1; self->_st3 = 0; self->_st2 = 0; self->_st1 = 0; }
#define NEXT_ST2() { self->_st2 = self->_st2 + 1; self->_st3 = 0; }
#define SYNC_COUNT() { self->_nowProcKazu = ((igObjectList *)self->_subWindow)->_count; }
#define WIN_PENDING() (((igObjectList *)self->_subWindow)->_count != self->_nowProcKazu)

struct Helpers {
static inline void AppendBoth(RP &dst, igObjectList *a, igObjectList *b)
{
    int i, j;
    for (i = 0; i < a->_count; i++) {
        int *e = (int *)((int *)a->_data)[i];
        if (e != 0) ObjectList_AppendRetained(dst.p, e);
        if (i == 0) {
            for (j = 0; j < b->_count; j++) {
                int *e2 = (int *)((int *)b->_data)[j];
                if (e2 != 0) ObjectList_AppendRetained(dst.p, e2);
            }
        }
    }
}
};

extern "C" void Gap__Bec__beNDMWStatusSubMenu__vfunc_21(beNDMWStatusSubMenu *self);
void Gap__Bec__beNDMWStatusSubMenu__vfunc_21(beNDMWStatusSubMenu *self)
{
    RP w1DC;
    RP w1D8;
    RP w1D4;
    RP w1D0;
    RP l1CC;
    RP l1C8;
    RP l1C4;
    RP l1C0;
    RP w1BC;
    RP r1B8;
    RP w1B4;
    RP w1B0;
    RP k1AC;
    int tq[12];
    float vec[3];
    Str3 names;
    float v0[3];
    float vecb[3];
    float vF[3];
    float v100[3];
    float v110[3];
    const char *tk0, *tk1, *tk2, *tk3, *tk4, *tk5, *tk6, *tk7;
    RP r188;
    int sink184;
    RP r180, r17c, r178, r174;
    const char *tk8, *tk9;
    RP rb;
    const char *tk10, *tk11;
    switch (self->_st0) {
    case 0: {
        void *al;
        const Q128 *qs = (const Q128 *)DAT_004cf760;
        Q128 *qd = (Q128 *)tq;
        Q128 q0 = *qs++; Q128 q1 = *qs++; Q128 q2 = *qs;
        qd[0] = q0; qd[1] = q1; qd[2] = q2;

        v0[0] = -121.0f; v0[1] = 128.0f; v0[2] = 0.0f;
        beNDMWWindow_PresentModel(self, DAT_00519d88, 0, tq[self->_entCode % 12], DAT_00519a58, v0);
        beNDMWWindow_PresentModelAtOrigin(self, DAT_0051a180, 0, DAT_00519ec8, DAT_00519a58);
        INTERN_APPEND(tk0, self->_textCloseTypeList, DAT_0051a190)
        INTERNP_APPEND(tk1, self->_textCloseNameList, DAT_004cf670[0])
        INTERN_APPEND(tk2, self->_textCloseTypeList, DAT_0051a190)
        INTERNP_APPEND(tk3, self->_textCloseNameList, DAT_004cf674[0])
        INTERN_APPEND(tk4, self->_textCloseTypeList, DAT_0051a190)
        INTERNP_APPEND(tk5, self->_textCloseNameList, DAT_004cf678[0])
        beNDMWWindow_RunMessageScript(self, DAT_00519b90, 0x43);
        GET_ALLOC(al)
        w1DC.p = (igObject *)FUN_003b51b0(al);
        beNDMWWindow_BindContext(w1DC.p, self, self->_insight, self->_playerNo, 0);
        ObjectList_AppendRetained(self->_subWindow, w1DC.p);
        WSETI84(beNDMWStatusSelectE1, w1DC.p, 3)
        WSETPOS(beNDMWStatusSelectE1, w1DC.p, 115.0f, 145.0f, 0.0f)
        WSETI100(beNDMWStatusSelectE1, w1DC.p, 0)
        RELEASE_REF(w1DC.p)
        SYNC_COUNT()
        NEXT_ST0()
        self->_st1 = 0; self->_st3 = 0; self->_st2 = 0;
    }
    case 1:
        switch (self->_st1) {
        case 0:
            if (!WIN_PENDING()) break;
            switch (self->_retCode) {
            case 0: self->_st1 = 1; self->_st3 = 0; self->_st2 = 0; return;
            case 1: self->_st1 = 2; self->_st3 = 0; self->_st2 = 0; return;
            case 2: self->_st1 = 3; self->_st3 = 0; self->_st2 = 0; return;
            default: NEXT_ST0() return;
            }
            break;
        case 1:
            switch (self->_st2) {
            case 0: {
                void *al;

                int *rec;
                beNDMWItemBase *item;
                int ctx;
                GET_ALLOC(al)
                w1D8.p = (igObject *)FUN_003b4f50(al);
                beNDMWWindow_BindContext(w1D8.p, self, self->_insight, self->_playerNo, 0);
                ObjectList_AppendRetained(self->_subWindow, w1D8.p);
                INTERN_APPEND(tk6, ((beNDMWShopSelect00 *)w1D8.p)->_textCloseTypeList, DAT_00519b50)
                INTERN_APPEND(tk7, ((beNDMWShopSelect00 *)w1D8.p)->_textCloseNameList, DAT_005199e0)
                MSG_SELECT_INT(self->_playerNo)
                rec = igProperty_GetRecordFolder(beMessenger_GetObject(self->_messenger, 0), DAT_00519c00);
                item = (beNDMWItemBase *)((int *)((igObjectList *)rec[3])->_data)[self->_selectDevice];
                ctx = FUN_00236f80(self->_insight, DAT_0058b028[0]);
                if (item->_isEquip != 0) {
                    beNDMWWindow_RunMessageScript(w1D8.p, DAT_00519b90, 0x90);
                    self->_st2 = 0xA; self->_st3 = 0;
                } else if ((item->_kindNo == 0) == 1 && !(beNDMWItemBase_GetRecordBool(item, ctx, DAT_0051a3e0) & 0xFF)) {
                    beNDMWWindow_RunMessageScript(w1D8.p, DAT_00519b90, 0x91);
                    self->_st2 = 0xA; self->_st3 = 0;
                } else {
                    beNDMWWindow_RunMessageScript(w1D8.p, DAT_00519b90, 0x4E);
                    NEXT_ST2()
                }
                RELEASE_REF(w1D8.p)
                SYNC_COUNT()
            }
            case 1:
                if (WIN_PENDING()) {
                    void *al;

                    GET_ALLOC(al)
                    w1D4.p = (igObject *)FUN_003b5370(al);
                    beNDMWWindow_BindContext(w1D4.p, self, self->_insight, self->_playerNo, 0x4F);
                    ObjectList_AppendRetained(self->_subWindow, w1D4.p);
                    WSETI84(beNDMWStatusSelectE0, w1D4.p, 2)
                    RELEASE_REF(w1D4.p)
                    SYNC_COUNT()
                    NEXT_ST2()
                case 2:
                    if (WIN_PENDING()) {
                        if (self->_retCode == 0) {
                            int *rec;
                            MSG_SELECT_INT(self->_playerNo)
                            rec = igProperty_GetRecordFolder(beMessenger_GetObject(self->_messenger, 0), DAT_00519c00);
                            LIST_REMOVE(rec[3], self->_selectDevice)
                        }
                    default:
                        if (WIN_PENDING()) {
                            NEXT_ST0()
                            return;
                        }
                    }
                }
                break;
            }
            break;
        case 2: {
            int obj;
            igObjectList *L;
            igObjectList *a7;
            igObjectList *a8;
            igObjectList *aA;
            igObjectList *a5;
            igObjectList *a6;
            void *al;
            int i, j, k;
            MSG_SELECT_INT(self->_playerNo)
            obj = beMessenger_GetObject(self->_messenger, 0);
            L = (igObjectList *)igProperty_GetRecordFolder(obj, DAT_00519c00)[3];
            GET_ALLOC(al)
            w1D0.p = (igObject *)FUN_003c90f0(al);
            a7 = (igObjectList *)igProperty_GetRecordFolder(obj, DAT_00519bb8)[3];
            a8 = (igObjectList *)igProperty_GetRecordFolder(obj, DAT_00519bc8)[3];
            aA = (igObjectList *)igProperty_GetRecordFolder(obj, DAT_00519bd8)[3];
            a5 = (igObjectList *)igProperty_GetRecordFolder(obj, DAT_00519be0)[3];
            a6 = (igObjectList *)igProperty_GetRecordFolder(obj, DAT_00519bf0)[3];
            r188.p = (igObject *)L; RETAIN_DIRECT(r188) FUN_00423000(self, &r188); RELEASE_DIRECT(r188)
            Helpers::AppendBoth(w1D0, a7, a5);
            Helpers::AppendBoth(w1D0, a8, a6);
            for (k = 0; k < aA->_count; k++) {
                int *e = (int *)((int *)aA->_data)[k];
                if (e != 0) ObjectList_AppendRetained(w1D0.p, e);
            }
            for (i = 0; i < ((igObjectList *)w1D0.p)->_count; i++)
                ObjectList_RemoveFirstRetained(&sink184, L, ((int *)((igObjectList *)w1D0.p)->_data)[i], 0);
            GET_ALLOC(al) l1CC.p = (igObject *)FUN_003c90f0(al);
            GET_ALLOC(al) l1C8.p = (igObject *)FUN_003c90f0(al);
            GET_ALLOC(al) l1C4.p = (igObject *)FUN_003c90f0(al);
            GET_ALLOC(al) l1C0.p = (igObject *)FUN_003c90f0(al);
            if (L->_count > 0) do {
                beNDMWItemBase *e = (beNDMWItemBase *)((int *)L->_data)[0];
                int t = e->_kindNo;
                if (t == 0) ObjectList_AppendRetained(l1CC.p, e);
                else if (t == 1) ObjectList_AppendRetained(l1C8.p, e);
                else if (t == 2) ObjectList_AppendRetained(l1C4.p, e);
                else if (t == 3) ObjectList_AppendRetained(l1C0.p, e);
                else FUN_00236f80(self->_insight, DAT_0058b028[0]);
                LIST_REMOVE(L, 0)
            } while (L->_count > 0);
            r180.p = l1CC.p; RETAIN_DIRECT(r180) FUN_00422c00(self, &r180); RELEASE_DIRECT(r180)
            r17c.p = l1C8.p; RETAIN_DIRECT(r17c) FUN_00422c00(self, &r17c); RELEASE_DIRECT(r17c)
            r178.p = l1C4.p; RETAIN_DIRECT(r178) FUN_00422c00(self, &r178); RELEASE_DIRECT(r178)
            r174.p = l1C0.p; RETAIN_DIRECT(r174) FUN_00423000(self, &r174); RELEASE_DIRECT(r174)
            while (((igObjectList *)w1D0.p)->_count > 0) { ObjectList_AppendRetained(L, ((int *)((igObjectList *)w1D0.p)->_data)[0]); LIST_REMOVE(w1D0.p, 0) }
            while (((igObjectList *)l1CC.p)->_count > 0) { ObjectList_AppendRetained(L, ((int *)((igObjectList *)l1CC.p)->_data)[0]); LIST_REMOVE(l1CC.p, 0) }
            while (((igObjectList *)l1C8.p)->_count > 0) { ObjectList_AppendRetained(L, ((int *)((igObjectList *)l1C8.p)->_data)[0]); LIST_REMOVE(l1C8.p, 0) }
            while (((igObjectList *)l1C4.p)->_count > 0) { ObjectList_AppendRetained(L, ((int *)((igObjectList *)l1C4.p)->_data)[0]); LIST_REMOVE(l1C4.p, 0) }
            while (((igObjectList *)l1C0.p)->_count > 0) { ObjectList_AppendRetained(L, ((int *)((igObjectList *)l1C0.p)->_data)[0]); LIST_REMOVE(l1C0.p, 0) }
            RELEASE_REF(l1C0.p)
            RELEASE_REF(l1C4.p)
            RELEASE_REF(l1C8.p)
            RELEASE_REF(l1CC.p)
            RELEASE_REF(w1D0.p)
            NEXT_ST0()
            return;
        }
        case 3:
            switch (self->_st2) {
            case 0: {
                int *rec;
                int i;
                int nN;
                beNDMWItemBase *item;
                igDataList *lL;
                int ctx;
                bool flag;
                MSG_SELECT_INT(self->_playerNo)
                rec = igProperty_GetRecordFolder(beMessenger_GetObject(self->_messenger, 0), DAT_00519c00);
                item = (beNDMWItemBase *)((int *)((igObjectList *)rec[3])->_data)[self->_selectDevice];
                ctx = FUN_00236f80(self->_insight, DAT_0058b028[0]);
                for (i = 0; i < 4; i++) {
                    MSG_SELECT_INT(i)
                    if (((unsigned char *)igProperty_GetRecordByte(beMessenger_GetObject(self->_messenger, 0), DAT_0051a1a0))[12] != 0 && i != self->_playerNo) {
                        nN = ((igDataList *)(self->_playerNoList))->_count; lL = (igDataList *)(self->_playerNoList);
                        if (nN < lL->_capacity) lL->_count = *(volatile int *)&lL->_count + 1; else List_Resize(lL, nN + 1, 4);
                        ((int *)lL->_data)[nN] = i;
                    }
                }
                flag = false;
                if (item->_isEquip != 0) {
                    flag = true;
                    self->_st3 = 0x92;
                } else if (!(beNDMWItemBase_GetRecordBool(item, ctx, DAT_0051a3e8) & 0xFF)) {
                    flag = true;
                    self->_st3 = 0x93;
                } else if (((igObjectList *)self->_playerNoList)->_count == 0) {
                    flag = true;
                    self->_st3 = 0x94;
                }
                if (flag) {
                    void *al;

                    GET_ALLOC(al)
                    w1BC.p = (igObject *)FUN_003b4f50(al);
                    beNDMWWindow_BindContext(w1BC.p, self, self->_insight, self->_playerNo, 0);
                    ObjectList_AppendRetained(self->_subWindow, w1BC.p);
                    beNDMWWindow_RunMessageScript(w1BC.p, DAT_00519b90, self->_st3);
                    SYNC_COUNT()
                    self->_st2 = 4;
                    self->_st3 = 0;
                    RELEASE_REF(w1BC.p)
                } else {
                    beNDMWWindow *win;
                    win = (beNDMWWindow *)self->_deviceFolderList;
                    if (win != 0) {
                        win->_st0 = 2;
                        win->_st3 = 0;
                        win->_st2 = 0;
                        win->_st1 = 0;
                        beNDMWWindow_SendModelSequence(self, DAT_00519d88, 0, DAT_00519a58);
                        NEXT_ST2()
                    } else {
                        NEXT_ST0()
                    }
                    beNDMWWindow_ClearQueuedText(self);
                    return;
                }
                break;
            }
            case 1:
                if (beNDMWWindow_PollCloseComplete(self->_deviceFolderList) != 0) {
                    int cnt;
                    int *rec;
                    beNDMWItemBase *item;
                    int i;
                    ObjectRef_Retain_003e90d0(0);
                    ObjectRef_Release_003e9110(self->_deviceFolderList);
                    self->_deviceFolderList = 0;
                    cnt = ((igObjectList *)self->_playerNoList)->_count;
                    switch (cnt) {
                    case 1:
                    default:
                        beNDMWWindow_PresentModelAtOrigin(self, DAT_0051a180, 0, DAT_0051a3f8, DAT_00519a58);
                        break;
                    case 2:
                        beNDMWWindow_PresentModelAtOrigin(self, DAT_0051a180, 0, DAT_0051a408, DAT_00519a58);
                        break;
                    case 3:
                        beNDMWWindow_PresentModelAtOrigin(self, DAT_0051a180, 0, DAT_0051a418, DAT_00519a58);
                        break;
                    }
                    INTERN_APPEND(tk8, self->_textCloseTypeList, DAT_0051a1d8)
                    INTERN_APPEND(tk9, self->_textCloseNameList, DAT_005199e0)
                    beNDMWWindow_RunMessageScript(self, DAT_00519b90, 0x49);
                    MSG_SELECT_INT(self->_playerNo)
                    rec = igProperty_GetRecordFolder(beMessenger_GetObject(self->_messenger, 0), DAT_00519c00);
                    {
                        igObjectList *dl = (igObjectList *)rec[3];
                        int cx = FUN_00236f80(self->_insight, DAT_0058b028[0]);
                        item = (beNDMWItemBase *)((int *)dl->_data)[self->_selectDevice];
                        FUN_003f5410(self, DAT_0051a060, DAT_005199e0, beNDMWItemBase_GetRecordString(item, cx, DAT_00519f28), DAT_00519b68);
                    }
                    FUN_00447d00(vec, item);
                    beMessenger_SelectGroup(self->_messenger, DAT_00519c28);
                    beMessenger_AppendString(self->_messenger, DAT_0051a060);
                    beMessenger_AppendString(self->_messenger, DAT_005199e0);
                    vecb[0] = vec[0]; vecb[1] = vec[1]; vecb[2] = vec[2];
                    beMessenger_AppendVec3(self->_messenger, vecb);
                    beMessenger_DispatchSelected(self->_messenger, DAT_00519f38);
                    names = DAT_004cf790;
                    for (i = 0; i < ((igObjectList *)self->_playerNoList)->_count; i++) {
                        int pno = ((int *)((igObjectList *)self->_playerNoList)->_data)[i];
                        int obj;
                        igObjectList *folder;
                        igObjectList *lst;
                        int c;
                        MSG_SELECT_INT(pno)
                        obj = beMessenger_GetObject(self->_messenger, 0);
                        folder = (igObjectList *)igProperty_GetRecordFolder(obj, DAT_00519c00)[3];
                        lst = (igObjectList *)igProperty_GetRecordFolder(obj, DAT_0051a1e8)[3];
                        if (lst->_count > 0) {
                            r1B8.p = (igObject *)*(int *)lst->_data;
                            RETAIN_REF(r1B8.p)
                            rb.p = r1B8.p;
                            RETAIN_DIRECT(rb)
                            FUN_003f56d0(self, DAT_0051a060, names.v[i], &rb, DAT_00519b68);
                            RELEASE_DIRECT(rb)
                            RELEASE_REF(r1B8.p)
                        }
                        c = folder->_count;
                        LIST_ADD(self->_playerDeviceCnt, c)
                    }
                    NEXT_ST2()
                    return;
                }
                break;
            case 2: {
                void *al;

                GET_ALLOC(al)
                w1B4.p = (igObject *)FUN_003b51b0(al);
                beNDMWWindow_BindContext(w1B4.p, self, self->_insight, self->_playerNo, 0);
                ObjectList_AppendRetained(self->_subWindow, w1B4.p);
                WSETPOS(beNDMWStatusSelectE1, w1B4.p, -121.0f, 109.0f, 0.0f)
                WSETI84(beNDMWStatusSelectE1, w1B4.p, ((igObjectList *)self->_playerNoList)->_count)
                WSETI100(beNDMWStatusSelectE1, w1B4.p, self->_receipt)
                RELEASE_REF(w1B4.p)
                SYNC_COUNT()
                NEXT_ST2()
            }
            case 3:
                if (WIN_PENDING()) {
                    void *al;

                    if (self->_retCode == -1) {
                        NEXT_ST0()
                        return;
                    }
                    GET_ALLOC(al)
                    w1B0.p = (igObject *)FUN_003b4f50(al);
                    beNDMWWindow_BindContext(w1B0.p, self, self->_insight, self->_playerNo, 0);
                    ObjectList_AppendRetained(self->_subWindow, w1B0.p);
                    SYNC_COUNT()
                    NEXT_ST2()
                    self->_st3 = -1;
                    INTERN_APPEND(tk10, ((beNDMWShopSelect00 *)w1B0.p)->_textCloseTypeList, DAT_00519b50)
                    INTERNP_APPEND(tk11, ((beNDMWShopSelect00 *)w1B0.p)->_textCloseNameList, DAT_004cf670[0])
                    self->_receipt = self->_retCode;
                    if (((int *)((igObjectList *)self->_playerDeviceCnt)->_data)[self->_receipt] >= 0x24) {
                        beNDMWWindow_RunMessageScript(w1B0.p, DAT_00519b90, 0x95);
                    } else {
                        int *rec;
                        igObjectList *l;

                        int idx, val;
                        beNDMWWindow_RunMessageScript(w1B0.p, DAT_00519b90, 0x83);
                        MSG_SELECT_INT(self->_playerNo)
                        l = (igObjectList *)igProperty_GetRecordFolder(beMessenger_GetObject(self->_messenger, 0), DAT_00519c00)[3];
                        k1AC.p = (igObject *)((int *)l->_data)[self->_selectDevice];
                        RETAIN_REF(k1AC.p)
                        idx = self->_selectDevice;
                        LIST_REMOVE(l, idx)
                        val = ((int *)((igObjectList *)self->_playerNoList)->_data)[self->_receipt];
                        MSG_SELECT_INT(val)
                        ObjectList_AppendRetained(igProperty_GetRecordFolder(beMessenger_GetObject(self->_messenger, 0), DAT_00519c00)[3], k1AC.p);
                        RELEASE_REF(k1AC.p)
                    }
                    switch (self->_retCode) {
                    case 0: {
                        vF[0] = -121.0f; vF[1] = 109.0f; vF[2] = 0.0f;
                        beNDMWWindow_PresentModel(self, DAT_00519d88, 0, DAT_00519cc8, 0, vF);
                        break;
                    }
                    case 1: {
                        v100[0] = -121.0f; v100[1] = 109.0f; v100[2] = 0.0f;
                        beNDMWWindow_PresentModel(self, DAT_00519d88, 0, DAT_00519cd8, 0, v100);
                        break;
                    }
                    case 2: {
                        v110[0] = -121.0f; v110[1] = 109.0f; v110[2] = 0.0f;
                        beNDMWWindow_PresentModel(self, DAT_00519d88, 0, DAT_00519ce8, 0, v110);
                        break;
                    }
                    }
                    RELEASE_REF(w1B0.p)
                }
                break;
            case 4:
            default:
                if (WIN_PENDING()) {
                    int keep;
                    beMessenger_SendNamed(self->_messenger, DAT_00519a90, DAT_00519d88, 0, DAT_00519a58);
                    keep = self->_st3;
                    NEXT_ST0()
                    self->_st3 = keep;
                    return;
                }
                break;
            }
            break;
        default:
            break;
        }
        break;
    case 2:
        beNDMWWindow_PlayQueuedModelClose(self);
        beNDMWWindow_ClearQueuedText(self);
        beNDMWWindow_RequestChildrenClose(self);
        if (self->_st3 == -1) {
            beMessenger_SelectGroup(self->_messenger, DAT_00519c28);
            beMessenger_AppendString(self->_messenger, DAT_0051a060);
            beMessenger_AppendString(self->_messenger, DAT_005199e0);
            beMessenger_DispatchSelected(self->_messenger, DAT_00519c30);
        }
        NEXT_ST0()
        return;
    case 3:
        if (beNDMWWindow_PollCloseComplete(self) != 0) {
            self->_isRun = 0;
        }
        break;
    }
}
