#include "dw4/reflected.h"
extern "C" {
struct S_ref { char pad4[4]; int f4; };
int FUN_002cb0d0(...);
int FUN_002eb010(...);
int FUN_003b4410(...);
int FUN_003b4d90(...);
int FUN_003b4f50(...);
int FUN_003b51b0(...);
int FUN_003f5410(...);
int FUN_00435250(...);
int FUN_00437ae0(...);
int FUN_00437f50(...);
int FUN_00438050(...);
int List_Resize(...);
void *Memory_GetAllocatorBySelector(...);
int ObjectList_AppendRetained(...);
int StringChunk_ReleaseHeader(...);
int StringPool_Construct(...);
char *StringPool_Intern(...);
int beMessenger_AppendInt(...);
int beMessenger_DispatchSelected(...);
int beMessenger_GetObject(...);
int beMessenger_SelectGroup(...);
int beMessenger_SendNamed(...);
int beNDMWWindow_BindContext(...);
int beNDMWWindow_ClearQueuedText(...);
int beNDMWWindow_PlayQueuedModelClose(...);
int beNDMWWindow_PollCloseComplete(...);
int beNDMWWindow_PresentModel(...);
int beNDMWWindow_PresentModelAtOrigin(...);
int beNDMWWindow_RequestChildrenClose(...);
int beNDMWWindow_RunMessageScript(...);
int igObject_Destroy(...);
void *igObject_GetAllocator(...);
int igProperty_GetRecord(...);
struct Item { int p[5]; int f20; };
struct Rec { int p[3]; igObjectList *f12; };
Rec *igProperty_GetRecordFolder(...);
extern char *DAT_004cf8a0[];
extern int DAT_0051b308[4];
extern int DAT_0051b398[4];
extern int DAT_0051b3b0[4];
extern int DAT_0051b3c8[4];
extern int DAT_0051b3e8[4];
extern int DAT_0051b460[4];
extern int DAT_0051b470[4];
extern int DAT_0051b498[4];
extern int DAT_0051b4a0[4];
extern int DAT_0051b548[4];
extern int DAT_0051b560[4];
extern int DAT_0051b590[4];
extern int DAT_0051b598[4];
extern int DAT_0051b610[4];
extern int DAT_0051b618[4];
extern int DAT_0051b620[4];
extern int DAT_0051b630[4];
extern int DAT_0051b640[4];
extern int DAT_0051b650[4];
extern int DAT_0051b668[4];
extern int DAT_0051b680[4];
extern int DAT_0051b6c0[4];
extern int DAT_0051bd88[4];
extern int DAT_0051bd98[4];
extern int DAT_0051bda0[4];
extern int DAT_0051bdb0[4];
extern int DAT_00586f20[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554a60;
extern unsigned char GPR_00554a64;
extern unsigned char GPR_00554c14;

void Gap__Bec__beNDMWShopCtrlDiskSell__vfunc_21(beNDMWShopCtrlDiskSell *self);
}
struct U { static inline char *InternStr(char *text) {
    if (text == 0) return 0;
    if (DAT_00586f20[0] == 0) {
        int pool = FUN_002eb010(0x10);
        if (pool != 0) pool = StringPool_Construct(pool);
        DAT_00586f20[0] = pool;
    }
    return StringPool_Intern(DAT_00586f20[0], text);
} };
/* Owning stack reference to a pooled string token (count at p[-1], chunk header at p[-2]).
 * Interning for a text list yields one: the list takes its own share and the token is a temporary
 * released at the end of the statement. */
class StringRef {
public:
    char *p;
    StringRef(char *s) : p(s) {}
    ~StringRef() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); } }
};
extern "C" int StringList_AppendRetained(int, const StringRef &);
#define INTERN_APPEND(lst, text) { char *tok = U::InternStr((char *)(text)); StringList_AppendRetained(lst, StringRef(tok)); }

#define ALLOC(a, self) { \
    a = igObject_GetAllocator(self); \
    a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(DAT_00587110[0]); }

/* Owning stack references to the sub-windows and the decide list while their set-up runs; each
 * releases its object on scope exit (reference count in the low 23 bits of _refCount). One class
 * per destructor copy. */
template <class T> class igSmartPointer {
public:
    T *p;
    igSmartPointer(T *o) : p(o) {}
    ~igSmartPointer() { T *o = p; if (o != 0) { o->_refCount = o->_refCount - 1; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
class DecideListRef {
public:
    igObject *p;
    DecideListRef(igObject *o) : p(o) {}
    ~DecideListRef() { igObject *o = p; if (o != 0) { o->_refCount = o->_refCount - 1; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
class QuantityRef {
public:
    igObject *p;
    QuantityRef(igObject *o) : p(o) {}
    ~QuantityRef() { igObject *o = p; if (o != 0) { o->_refCount = o->_refCount - 1; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
class ConfirmRef {
public:
    igObject *p;
    ConfirmRef(igObject *o) : p(o) {}
    ~ConfirmRef() { igObject *o = p; if (o != 0) { o->_refCount = o->_refCount - 1; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
class ResultRef {
public:
    igObject *p;
    ResultRef(igObject *o) : p(o) {}
    ~ResultRef() { igObject *o = p; if (o != 0) { o->_refCount = o->_refCount - 1; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
#define REL(o) { igObject *rr = (o); if (rr != 0) { rr->_refCount = rr->_refCount - 1; if (((unsigned long long)((long long)(int)rr->_refCount << 0x29) >> 0x29) == 0) { igObject_Destroy(rr); } } }
#define RELEASE(p) { if ((p) != 0) { \
        ((S_ref *)(p))->f4 = ((S_ref *)(p))->f4 - 1; \
        if (((unsigned long long) ((long long) ((S_ref *)(p))->f4 << 0x29) >> 0x29) == 0) { \
            igObject_Destroy(p); \
        } \
    } }

#define W(p, off) (*(int *)((int)(p) + (off)))

void Gap__Bec__beNDMWShopCtrlDiskSell__vfunc_21(beNDMWShopCtrlDiskSell *self) {
    int vA[3];
    int vB[3];
    void *alloc;
    igObjectList *temp_s3;
    igObjectList *fa;
    Item *rc;
    int folder;
    int i;
    int j;
    int obj;
    igObjectList *fb;
    int newv;
    int cost;
    int tot;
    int rec;
    int row;
    char **fp;
    unsigned char *dst;
    unsigned char val;

    switch (self->_st0) {
    default:
        return;
    case 0:
        beNDMWWindow_PresentModelAtOrigin(self, &DAT_0051b610[0], 0, &DAT_0051b618[0], &DAT_0051b620[0]);
        vA[0] = 0xC3120000;
        vA[1] = 0x41C80000;
        vA[2] = 0;
        beNDMWWindow_PresentModel(self, &DAT_0051b630[0], 0, &DAT_0051b640[0], &DAT_0051b620[0], &vA[0]);
        vB[0] = 0x436C0000;
        vB[1] = 0x41C80000;
        vB[2] = 0;
        beNDMWWindow_PresentModel(self, &DAT_0051b650[0], 0, &DAT_0051b640[0], &DAT_0051b620[0], &vB[0]);
        INTERN_APPEND(self->_textCloseTypeList, &DAT_0051b470[0])
        INTERN_APPEND(self->_textCloseNameList, &DAT_0051b548[0])
        INTERN_APPEND(self->_textCloseTypeList, &DAT_0051b668[0])
        INTERN_APPEND(self->_textCloseNameList, DAT_004cf8a0[0])
        beNDMWWindow_RunMessageScript(self, &DAT_0051b3b0[0], 0x3E9);
        beMessenger_SelectGroup(self->_messenger, &DAT_0051b398[0]);
        beMessenger_AppendInt(self->_messenger, self->_playerNo);
        beMessenger_DispatchSelected(self->_messenger, &DAT_0051b3e8[0]);
        temp_s3 = igProperty_GetRecordFolder(beMessenger_GetObject(self->_messenger, 0), &DAT_0051b6c0[0])->f12;
        i = 0;
        if (0 < temp_s3->_count) {
            fp = &DAT_004cf8a0[0];
            do {
                FUN_003f5410(self, &DAT_0051b3c8[0], *fp, &DAT_0051b590[0], &DAT_0051b598[0]);
                FUN_003f5410(self, &DAT_0051bd88[0], *fp, &DAT_0051b590[0], &DAT_0051bd98[0]);
                FUN_003f5410(self, &DAT_0051b680[0], *fp, &DAT_0051b590[0], &DAT_0051b460[0]);
                i += 1;
                fp += 1;
            } while (i < temp_s3->_count);
        }
        self->_cursor = 0;
        self->_st0 = self->_st0 + 1;
        self->_st3 = 0;
        self->_st2 = 0;
        self->_st1 = 0;
        self->_st1 = 6;
        self->_st3 = 0;
        self->_st2 = 0;
    case 1:
        switch (self->_st1) {
        case 6:
            switch (self->_st2) {
            case 0:
                beMessenger_SendNamed(self->_messenger, &DAT_0051b308[0], &DAT_0051b610[0], 0, &DAT_0051bda0[0]);
                FUN_00435250(self->_mother, -1);
                ALLOC(alloc, self)
                {
                igSmartPointer<igObject> spBC((igObject *)FUN_003b51b0(alloc));
                self->_retCode = self->_cursor;
                beNDMWWindow_BindContext(spBC.p, self, self->_insight, self->_playerNo, 0);
                ObjectList_AppendRetained(self->_subWindow, spBC.p);
                { beNDMWStatusSelectE1 *w = (beNDMWStatusSelectE1 *)spBC.p; w->_offsetPos[0] = -121.0f; w->_offsetPos[1] = 128.0f; w->_offsetPos[2] = 0.0f; }
                ((beNDMWStatusSelectE1 *)spBC.p)->_startPoint = self->_cursor;
                FUN_003f5410(spBC.p, &DAT_0051b470[0], DAT_004cf8a0[0], &DAT_0051b590[0], &DAT_0051b598[0]);
                beMessenger_SelectGroup(self->_messenger, &DAT_0051b398[0]);
                beMessenger_AppendInt(self->_messenger, self->_playerNo);
                beMessenger_DispatchSelected(self->_messenger, &DAT_0051b3e8[0]);
                fa = igProperty_GetRecordFolder(beMessenger_GetObject(self->_messenger, 0), &DAT_0051b6c0[0])->f12;
                ((beNDMWStatusSelectE1 *)spBC.p)->_selectMax = fa->_count;
                ALLOC(alloc, self)
                DecideListRef spB8((igObject *)FUN_002cb0d0(alloc));
                j = 0;
                if (0 < fa->_count) {
                    do {
                        if (((Item **)fa->_data)[j]->f20 > 0) {
                            { int idx; igBoolList *l = (igBoolList *)spB8.p; idx = l->_count;
                            if (idx < l->_capacity) {
                                l->_count = idx + 1;
                            } else {
                                List_Resize(l, idx + 1, 1);
                            }
                            ((unsigned char *)l->_data)[idx] = GPR_00554a60; }
                        } else {
                            { int idx; igBoolList *l = (igBoolList *)spB8.p; idx = l->_count;
                            if (idx < l->_capacity) {
                                l->_count = idx + 1;
                            } else {
                                List_Resize(l, idx + 1, 1);
                            }
                            ((unsigned char *)l->_data)[idx] = GPR_00554a64; }
                        }
                        j += 1;
                    } while (j < fa->_count);
                }
                {
                    igBoolList *l2 = (igBoolList *)spB8.p;
                    beNDMWStatusSelectE1 *w = (beNDMWStatusSelectE1 *)spBC.p;
                    if (l2 != 0) {
                        l2->_refCount = l2->_refCount + 1;
                    }
                    { igObject *old = (igObject *)w->_decideList; REL(old) }
                    w->_decideList = (int)l2;
                }
                beNDMWWindow_RunMessageScript(self, &DAT_0051b3b0[0], 0x676);
                }
                self->_nowProcKazu = ((beNDMWWindowList *)self->_subWindow)->_count;
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
            case 1:
                FUN_00437ae0(self, 1, 1);
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
                return;
            case 2:
                if (((beNDMWWindowList *)self->_subWindow)->_count == self->_nowProcKazu) {
                    if (self->_retCode != -1) {
                        if (self->_st3 != self->_retCode) {
                            FUN_00437ae0(self, 0, 1);
                            self->_st3 = self->_retCode;
                            return;
                        }
                    }
                } else {
                    if (self->_retCode != -1) {
                        self->_st1 = 7;
                        self->_st3 = 0;
                        self->_st2 = 0;
                        self->_cursor = self->_retCode;
                        FUN_00435250(self->_mother, self->_cursor);
                        beMessenger_SelectGroup(self->_messenger, &DAT_0051b398[0]);
                        beMessenger_AppendInt(self->_messenger, self->_playerNo);
                        beMessenger_DispatchSelected(self->_messenger, &DAT_0051b3e8[0]);
                        self->_maxSell = ((Item **)igProperty_GetRecordFolder(beMessenger_GetObject(self->_messenger, 0), &DAT_0051b6c0[0])->f12->_data)[self->_cursor]->f20;
                        if (self->_maxSell == 0) {
                            self->_st1 = 6;
                            self->_st3 = 0;
                            self->_st2 = 0;
                            return;
                        }
                        break;
                    }
                    ((beNDMWWindow *)self->_mother)->_retCode = -1;
                    self->_st0 = self->_st0 + 1;
                    self->_st3 = 0;
                    self->_st2 = 0;
                    self->_st1 = 0;
                    return;
                }
                break;
            }
            break;
        case 7:
            switch (self->_st2) {
            case 0:
                beMessenger_SendNamed(self->_messenger, &DAT_0051b308[0], &DAT_0051b610[0], 0, &DAT_0051bdb0[0]);
                ALLOC(alloc, self)
                {
                QuantityRef spB4((igObject *)FUN_003b4410(alloc));
                beNDMWWindow_BindContext(spB4.p, self, self->_insight, self->_playerNo, self->_maxSell);
                ObjectList_AppendRetained(self->_subWindow, spB4.p);
                { beNDMWShopSelect52 *w = (beNDMWShopSelect52 *)spB4.p; w->_offsetPos[0] = 52.0f; w->_offsetPos[1] = -104.0f; w->_offsetPos[2] = 0.0f; }
                INTERN_APPEND(((beNDMWShopSelect52 *)spB4.p)->_textCloseTypeList, &DAT_0051b470[0])
                INTERN_APPEND(((beNDMWShopSelect52 *)spB4.p)->_textCloseNameList, &DAT_0051b548[0])
                beNDMWWindow_RunMessageScript(self, &DAT_0051b3b0[0], 0x624);
                beNDMWWindow_RunMessageScript(self, &DAT_0051b3b0[0], 0x5E1);
                self->_retCode = self->_maxSell - 1;
                FUN_00437f50(self);
                }
                self->_nowProcKazu = ((beNDMWWindowList *)self->_subWindow)->_count;
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
            case 1:
                if (((beNDMWWindowList *)self->_subWindow)->_count == self->_nowProcKazu) {
                    if (self->_retCode != -1) {
                        if (self->_st3 != self->_retCode) {
                            FUN_00437f50(self);
                        }
                        self->_st3 = self->_retCode;
                        return;
                    }
                } else {
                    if (self->_retCode != -1) {
                        self->_st1 = 8;
                        self->_st3 = 0;
                        self->_st2 = 0;
                        self->_kazu = self->_maxSell - self->_retCode;
                        return;
                    }
                    FUN_00438050(self);
                    self->_st1 = 6;
                    self->_st3 = 0;
                    self->_st2 = 0;
                    return;
                }
                break;
            }
            break;
        case 8:
            switch (self->_st2) {
            case 0:
                ALLOC(alloc, self)
                {
                ConfirmRef spB0((igObject *)FUN_003b4f50(alloc));
                beNDMWWindow_BindContext(spB0.p, self, self->_insight, self->_playerNo, 0x619);
                ObjectList_AppendRetained(self->_subWindow, spB0.p);
                }
                self->_nowProcKazu = ((beNDMWWindowList *)self->_subWindow)->_count;
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
            case 1:
                if (((beNDMWWindowList *)self->_subWindow)->_count != self->_nowProcKazu) {
                    ALLOC(alloc, self)
                    {
                    ResultRef spAC((igObject *)FUN_003b4d90(alloc));
                    beNDMWWindow_BindContext(spAC.p, self, self->_insight, self->_playerNo, 0x61A);
                    ObjectList_AppendRetained(self->_subWindow, spAC.p);
                    }
                    self->_nowProcKazu = ((beNDMWWindowList *)self->_subWindow)->_count;
                    self->_st2 = self->_st2 + 1;
                    self->_st3 = 0;
                    return;
                }
                break;
            case 2:
                if (((beNDMWWindowList *)self->_subWindow)->_count != self->_nowProcKazu) {
                    FUN_00438050(self);
                    switch (self->_retCode) {
                    case 0:
                        beMessenger_SelectGroup(self->_messenger, &DAT_0051b398[0]);
                        beMessenger_AppendInt(self->_messenger, self->_playerNo);
                        beMessenger_DispatchSelected(self->_messenger, &DAT_0051b3e8[0]);
                        obj = beMessenger_GetObject(self->_messenger, 0);
                        fb = igProperty_GetRecordFolder(obj, &DAT_0051b6c0[0])->f12;
                        cost = self->_tanka * self->_kazu;
                        tot = W(igProperty_GetRecord(obj, &DAT_0051b560[0]), 12);
                        tot = tot + cost;
                        if (tot > 9999999) {
                            tot = 9999999;
                        }
                        W(igProperty_GetRecord(obj, &DAT_0051b560[0]), 12) = tot;
                        beMessenger_SelectGroup(self->_messenger, &DAT_0051b498[0]);
                        beMessenger_AppendInt(self->_messenger, self->_playerNo);
                        beMessenger_DispatchSelected(self->_messenger, &DAT_0051b4a0[0]);
                        rc = ((Item **)fb->_data)[self->_cursor]; { unsigned int q = rc->f20; tot = q - self->_kazu; rc->f20 = tot; }
                        break;
                    case 1:
                        break;
                    }
                    self->_st1 = 6;
                    self->_st3 = 0;
                    self->_st2 = 0;
                    return;
                }
                break;
            }
            break;
        }
        break;
    case 2:
        beNDMWWindow_PlayQueuedModelClose();
        beNDMWWindow_ClearQueuedText(self);
        beNDMWWindow_RequestChildrenClose(self);
        self->_st0 = self->_st0 + 1;
        self->_st3 = 0;
        self->_st2 = 0;
        self->_st1 = 0;
        FUN_00435250(self->_mother, -1);
        return;
    case 3:
        if (beNDMWWindow_PollCloseComplete() != 0) {
            self->_isRun = 0;
        }
        break;
    }
}
