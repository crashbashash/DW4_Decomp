/* Update state machine of the status-screen sub-menu (_st0 open / run / close / wait-close, _st1
 * menu choice 0..3, _st2 step, _st3 argument). Each sub-window, list and item reference is held by an
 * owning reference scoped to the block that uses it; one holder class per retail destructor copy.
 * Keep `case 1: default:` first in the player-count presentation switch. */
#include "dw4/reflected.h"

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

void *ObjectList_GetAt_003e9260(...);
void ObjectRef_Release_003e9110(...);
void ObjectRef_Retain_003e90d0(...);
void FUN_00406f20(...);
int FUN_00236f80(...);
void *FUN_003b4f50(void *);
void *FUN_003b51b0(void *);
void *FUN_003b5370(void *);
void *FUN_003c90f0(void *);


void FUN_003f5410(...);

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
struct ModelNames { int v[12]; };
extern ModelNames DAT_004cf760;
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

struct Str3 { const char *v[3]; };
extern Str3 DAT_004cf790;

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
WINDOW_REF(SelectE0Ref);
class ItemListRef {
public:
    igObject *p;
    ItemListRef(void *fresh) : p((igObject *)fresh) {}
    ItemListRef(igObjectList *shared) : p((igObject *)shared) { if (p != 0) p->_refCount = p->_refCount + 1; }
    ~ItemListRef() { ReleaseObject((igObject *)p); }
};
class DeviceRef {
public:
    igObject *p;
    DeviceRef(void *o) : p((igObject *)o) { igObject *q = p; if (q) ++q->_refCount; }
    DeviceRef(const DeviceRef &r) : p(r.p) { if (p != 0) p->_refCount = p->_refCount + 1; }
    ~DeviceRef() { ReleaseObject((igObject *)p); }
};
class MovedItemRef {
public:
    igObject *p;
    MovedItemRef(void *o) : p((igObject *)o) { igObject *q = p; if (q) ++q->_refCount; }
    ~MovedItemRef() { ReleaseObject((igObject *)p); }
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
#define INTERNP_APPEND(field, ptr) { const char *tok_; INTERNP(tok_, ptr) StringList_AppendRetained(field, StringRef(tok_)); }
#define INTERN_APPEND(field, text) { const char *tok_; INTERN(tok_, text) StringList_AppendRetained(field, StringRef(tok_)); }
static inline int count(const igDataList *list) { return list->_count; }
#define LIST_ADD(lst, val) { int n_ = ((igDataList *)(lst))->_count; igDataList *l_ = (igDataList *)(lst); \
    if (n_ < l_->_capacity) l_->_count = count(l_) + 1; else List_Resize(l_, n_ + 1, 4); \
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
static inline void AppendBoth(ItemListRef &dst, igObjectList *a, igObjectList *b)
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

struct RemovedSlot { int index; };
extern "C" RemovedSlot ObjectList_RemoveFirstRetained(void *, int, int);
class ItemListRef; class DeviceRef; class StringRef;
extern "C" int StringList_AppendRetained(int, const StringRef &);
extern "C" void FUN_00422c00(void *, const ItemListRef &);
extern "C" void FUN_00423000(void *, const ItemListRef &);
extern "C" void FUN_003f56d0(void *, void *, const char *, const DeviceRef &, void *);
extern "C" void Gap__Bec__beNDMWStatusSubMenu__vfunc_21(beNDMWStatusSubMenu *self);
void Gap__Bec__beNDMWStatusSubMenu__vfunc_21(beNDMWStatusSubMenu *self)
{
    ModelNames tq;
    float vec[3];
    Str3 names;
    float v0[3];
    float vecb[3];
    float vF[3];
    float v100[3];
    float v110[3];
    switch (self->_st0) {
    case 0: {
        void *al;
        tq = DAT_004cf760;

        v0[0] = -121.0f; v0[1] = 128.0f; v0[2] = 0.0f;
        beNDMWWindow_PresentModel(self, DAT_00519d88, 0, tq.v[self->_entCode % 12], DAT_00519a58, v0);
        beNDMWWindow_PresentModelAtOrigin(self, DAT_0051a180, 0, DAT_00519ec8, DAT_00519a58);
        INTERN_APPEND(self->_textCloseTypeList, DAT_0051a190)
        INTERNP_APPEND(self->_textCloseNameList, DAT_004cf670[0])
        INTERN_APPEND(self->_textCloseTypeList, DAT_0051a190)
        INTERNP_APPEND(self->_textCloseNameList, DAT_004cf674[0])
        INTERN_APPEND(self->_textCloseTypeList, DAT_0051a190)
        INTERNP_APPEND(self->_textCloseNameList, DAT_004cf678[0])
        beNDMWWindow_RunMessageScript(self, DAT_00519b90, 0x43);
        GET_ALLOC(al)
        { SelectE1Ref menuWin(FUN_003b51b0(al));
        beNDMWWindow_BindContext(menuWin.p, self, self->_insight, self->_playerNo, 0);
        ObjectList_AppendRetained(self->_subWindow, menuWin.p);
        WSETI84(beNDMWStatusSelectE1, menuWin.p, 3)
        WSETPOS(beNDMWStatusSelectE1, menuWin.p, 115.0f, 145.0f, 0.0f)
        WSETI100(beNDMWStatusSelectE1, menuWin.p, 0)
        }
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
                { ConfirmRef messageWin(FUN_003b4f50(al));
                beNDMWWindow_BindContext(messageWin.p, self, self->_insight, self->_playerNo, 0);
                ObjectList_AppendRetained(self->_subWindow, messageWin.p);
                INTERN_APPEND(((beNDMWShopSelect00 *)messageWin.p)->_textCloseTypeList, DAT_00519b50)
                INTERN_APPEND(((beNDMWShopSelect00 *)messageWin.p)->_textCloseNameList, DAT_005199e0)
                MSG_SELECT_INT(self->_playerNo)
                rec = igProperty_GetRecordFolder(beMessenger_GetObject(self->_messenger, 0), DAT_00519c00);
                item = (beNDMWItemBase *)((int *)((igObjectList *)rec[3])->_data)[self->_selectDevice];
                ctx = FUN_00236f80(self->_insight, DAT_0058b028[0]);
                if (item->_isEquip != 0) {
                    beNDMWWindow_RunMessageScript(messageWin.p, DAT_00519b90, 0x90);
                    self->_st2 = 0xA; self->_st3 = 0;
                } else if ((item->_kindNo == 0) == 1 && !(beNDMWItemBase_GetRecordBool(item, ctx, DAT_0051a3e0) & 0xFF)) {
                    beNDMWWindow_RunMessageScript(messageWin.p, DAT_00519b90, 0x91);
                    self->_st2 = 0xA; self->_st3 = 0;
                } else {
                    beNDMWWindow_RunMessageScript(messageWin.p, DAT_00519b90, 0x4E);
                    NEXT_ST2()
                }
                }
                SYNC_COUNT()
            }
            case 1:
                if (WIN_PENDING()) {
                    void *al;

                    GET_ALLOC(al)
                    { SelectE0Ref yesNoWin(FUN_003b5370(al));
                    beNDMWWindow_BindContext(yesNoWin.p, self, self->_insight, self->_playerNo, 0x4F);
                    ObjectList_AppendRetained(self->_subWindow, yesNoWin.p);
                    WSETI84(beNDMWStatusSelectE0, yesNoWin.p, 2)
                    }
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
            { ItemListRef keptItems(FUN_003c90f0(al));
            a7 = (igObjectList *)igProperty_GetRecordFolder(obj, DAT_00519bb8)[3];
            a8 = (igObjectList *)igProperty_GetRecordFolder(obj, DAT_00519bc8)[3];
            aA = (igObjectList *)igProperty_GetRecordFolder(obj, DAT_00519bd8)[3];
            a5 = (igObjectList *)igProperty_GetRecordFolder(obj, DAT_00519be0)[3];
            a6 = (igObjectList *)igProperty_GetRecordFolder(obj, DAT_00519bf0)[3];
            FUN_00423000(self, ItemListRef(L));
            Helpers::AppendBoth(keptItems, a7, a5);
            Helpers::AppendBoth(keptItems, a8, a6);
            for (k = 0; k < aA->_count; k++) {
                int *e = (int *)((int *)aA->_data)[k];
                if (e != 0) ObjectList_AppendRetained(keptItems.p, e);
            }
            for (i = 0; i < ((igObjectList *)keptItems.p)->_count; i++)
                ObjectList_RemoveFirstRetained(L, ((int *)((igObjectList *)keptItems.p)->_data)[i], 0);
            GET_ALLOC(al) ItemListRef kind0Items(FUN_003c90f0(al));
            GET_ALLOC(al) ItemListRef kind1Items(FUN_003c90f0(al));
            GET_ALLOC(al) ItemListRef kind2Items(FUN_003c90f0(al));
            GET_ALLOC(al) ItemListRef kind3Items(FUN_003c90f0(al));
            if (L->_count > 0) do {
                beNDMWItemBase *e = (beNDMWItemBase *)((int *)L->_data)[0];
                int t = e->_kindNo;
                if (t == 0) ObjectList_AppendRetained(kind0Items.p, e);
                else if (t == 1) ObjectList_AppendRetained(kind1Items.p, e);
                else if (t == 2) ObjectList_AppendRetained(kind2Items.p, e);
                else if (t == 3) ObjectList_AppendRetained(kind3Items.p, e);
                else FUN_00236f80(self->_insight, DAT_0058b028[0]);
                LIST_REMOVE(L, 0)
            } while (L->_count > 0);
            FUN_00422c00(self, ItemListRef((igObjectList *)kind0Items.p));
            FUN_00422c00(self, ItemListRef((igObjectList *)kind1Items.p));
            FUN_00422c00(self, ItemListRef((igObjectList *)kind2Items.p));
            FUN_00423000(self, ItemListRef((igObjectList *)kind3Items.p));
            while (((igObjectList *)keptItems.p)->_count > 0) { ObjectList_AppendRetained(L, ((int *)((igObjectList *)keptItems.p)->_data)[0]); LIST_REMOVE(keptItems.p, 0) }
            while (((igObjectList *)kind0Items.p)->_count > 0) { ObjectList_AppendRetained(L, ((int *)((igObjectList *)kind0Items.p)->_data)[0]); LIST_REMOVE(kind0Items.p, 0) }
            while (((igObjectList *)kind1Items.p)->_count > 0) { ObjectList_AppendRetained(L, ((int *)((igObjectList *)kind1Items.p)->_data)[0]); LIST_REMOVE(kind1Items.p, 0) }
            while (((igObjectList *)kind2Items.p)->_count > 0) { ObjectList_AppendRetained(L, ((int *)((igObjectList *)kind2Items.p)->_data)[0]); LIST_REMOVE(kind2Items.p, 0) }
            while (((igObjectList *)kind3Items.p)->_count > 0) { ObjectList_AppendRetained(L, ((int *)((igObjectList *)kind3Items.p)->_data)[0]); LIST_REMOVE(kind3Items.p, 0) }
            }
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
                        if (nN < lL->_capacity) lL->_count = count(lL) + 1; else List_Resize(lL, nN + 1, 4);
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
                    { ConfirmRef refusalWin(FUN_003b4f50(al));
                    beNDMWWindow_BindContext(refusalWin.p, self, self->_insight, self->_playerNo, 0);
                    ObjectList_AppendRetained(self->_subWindow, refusalWin.p);
                    beNDMWWindow_RunMessageScript(refusalWin.p, DAT_00519b90, self->_st3);
                    SYNC_COUNT()
                    self->_st2 = 4;
                    self->_st3 = 0;
                    }
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
                    INTERN_APPEND(self->_textCloseTypeList, DAT_0051a1d8)
                    INTERN_APPEND(self->_textCloseNameList, DAT_005199e0)
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
                            DeviceRef firstDevice((void *)*(int *)lst->_data);
                            FUN_003f56d0(self, DAT_0051a060, names.v[i], DeviceRef(firstDevice), DAT_00519b68);
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
                { SelectE1Ref playerWin(FUN_003b51b0(al));
                beNDMWWindow_BindContext(playerWin.p, self, self->_insight, self->_playerNo, 0);
                ObjectList_AppendRetained(self->_subWindow, playerWin.p);
                WSETPOS(beNDMWStatusSelectE1, playerWin.p, -121.0f, 109.0f, 0.0f)
                WSETI84(beNDMWStatusSelectE1, playerWin.p, ((igObjectList *)self->_playerNoList)->_count)
                WSETI100(beNDMWStatusSelectE1, playerWin.p, self->_receipt)
                }
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
                    { ConfirmRef resultWin(FUN_003b4f50(al));
                    beNDMWWindow_BindContext(resultWin.p, self, self->_insight, self->_playerNo, 0);
                    ObjectList_AppendRetained(self->_subWindow, resultWin.p);
                    SYNC_COUNT()
                    NEXT_ST2()
                    self->_st3 = -1;
                    INTERN_APPEND(((beNDMWShopSelect00 *)resultWin.p)->_textCloseTypeList, DAT_00519b50)
                    INTERNP_APPEND(((beNDMWShopSelect00 *)resultWin.p)->_textCloseNameList, DAT_004cf670[0])
                    self->_receipt = self->_retCode;
                    if (((int *)((igObjectList *)self->_playerDeviceCnt)->_data)[self->_receipt] >= 0x24) {
                        beNDMWWindow_RunMessageScript(resultWin.p, DAT_00519b90, 0x95);
                    } else {
                        int *rec;
                        igObjectList *l;

                        int idx, val;
                        beNDMWWindow_RunMessageScript(resultWin.p, DAT_00519b90, 0x83);
                        MSG_SELECT_INT(self->_playerNo)
                        l = (igObjectList *)igProperty_GetRecordFolder(beMessenger_GetObject(self->_messenger, 0), DAT_00519c00)[3];
                        MovedItemRef movedItem((void *)((int *)l->_data)[self->_selectDevice]);
                        idx = self->_selectDevice;
                        LIST_REMOVE(l, idx)
                        val = ((int *)((igObjectList *)self->_playerNoList)->_data)[self->_receipt];
                        MSG_SELECT_INT(val)
                        ObjectList_AppendRetained(igProperty_GetRecordFolder(beMessenger_GetObject(self->_messenger, 0), DAT_00519c00)[3], movedItem.p);
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
                    }
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
