/* `retCode != -1` is spelled as a switch (default first, then case -1). */
#include "dw4/reflected.h"
extern "C" {
int FUN_002eb010(...);
int FUN_003b4410(...);
int FUN_003b4d90(...);
int FUN_003b4f50(...);
int FUN_003b51b0(...);
int FUN_003b7360(...);
int FUN_003f5410(...);
int FUN_003f5660(...);
int FUN_0042b880(...);
int FUN_0042b9d0(...);
int FUN_0042bae0(...);
void *Memory_GetAllocatorBySelector(...);
int ObjectList_AppendRetained(...);
int StringChunk_ReleaseHeader(...);
int StringPool_Construct(...);
char *StringPool_Intern(...);
int beDataBase_GetRecordInt(...);
char *beDataBase_GetRecordString(...);
int beMessenger_AppendInt(...);
int beMessenger_AppendString(...);
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
struct Item { int p[3]; int f12; int p16; int f20; };
struct Rec { int p[3]; igObjectList *f12; };
static inline int f20Of(const Item *item) { return item->f20; }
Rec *igProperty_GetRecordFolder(...);
extern char *DAT_004cf8a0[];
extern int DAT_0051b308[4];
extern int DAT_0051b398[4];
extern int DAT_0051b3b0[4];
extern int DAT_0051b3c0[4];
extern int DAT_0051b3c8[4];
extern int DAT_0051b3e8[4];
extern int DAT_0051b460[4];
extern int DAT_0051b470[4];
extern int DAT_0051b498[4];
extern int DAT_0051b4a0[4];
extern int DAT_0051b548[4];
extern int DAT_0051b558[4];
extern int DAT_0051b560[4];
extern int DAT_0051b590[4];
extern int DAT_0051b598[4];
extern int DAT_0051b5d8[4];
extern int DAT_0051b5e8[4];
extern int DAT_0051b610[4];
extern int DAT_0051b618[4];
extern int DAT_0051b620[4];
extern int DAT_0051b630[4];
extern int DAT_0051b640[4];
extern int DAT_0051b650[4];
extern int DAT_0051b660[4];
extern int DAT_0051b668[4];
extern int DAT_0051b678[4];
extern int DAT_0051b680[4];
extern int DAT_0051b690[4];
extern int DAT_0051b698[4];
extern int DAT_0051b6a8[4];
extern int DAT_0051b6b0[4];
extern int DAT_0051b6b8[4];
extern int DAT_0051b6c0[4];
extern int DAT_0051b6d0[4];
extern int DAT_00586f20[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;

void Gap__Bec__beNDMWShopCtrl50__vfunc_21(beNDMWShopCtrl50 *self);
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

/* Owning stack references to the sub-windows while their set-up runs; each releases its object on
 * scope exit (reference count in the low 23 bits of _refCount). One class per destructor copy. */
class ResultRef {
public:
    igObject *p;
    ResultRef(igObject *o) : p(o) {}
    ~ResultRef() { igObject *o = p; if (o != 0) { o->_refCount = o->_refCount - 1; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
class SelectE1Ref {
public:
    igObject *p;
    SelectE1Ref(igObject *o) : p(o) {}
    ~SelectE1Ref() { igObject *o = p; if (o != 0) { o->_refCount = o->_refCount - 1; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
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
class MenuRef {
public:
    igObject *p;
    MenuRef(igObject *o) : p(o) {}
    ~MenuRef() { igObject *o = p; if (o != 0) { o->_refCount = o->_refCount - 1; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
#define REL(o) { igObject *rr = (o); if (rr != 0) { rr->_refCount = rr->_refCount - 1; if (((unsigned long long)((long long)(int)rr->_refCount << 0x29) >> 0x29) == 0) { igObject_Destroy(rr); } } }

#define VCNT(l) ((l)->_count)
#define SUBCNT(s) (((beNDMWWindowList *)(s)->_subWindow)->_count)
#define W(p, off) (*(int *)((int)(p) + (off)))

#define CLEAR_LIST(L, lst) { \
    int n = L->_count; int k = 0; \
    if (0 < n) { int off = 0; do { \
        char **e = (char **)((int)L->_data + off); \
        if (DAT_00586f20[0] == 0) { int pool = FUN_002eb010(0x10); if (pool != 0) pool = StringPool_Construct(pool); DAT_00586f20[0] = pool; } \
        char *nw = StringPool_Intern(DAT_00586f20[0], 0); char *old = *e; \
        if (old != 0) { int *hd = (int *)old - 2; int cnt = ((int *)old)[-1] - 1; ((int *)old)[-1] = cnt; if (cnt == 0) StringChunk_ReleaseHeader(*hd, hd); } \
        k += 1; *e = nw; off += 4; \
    } while (k < n); } }

#define CLEAR1(L, lst) { \
    int n; \
    int k; \
    char **e; \
    char *nw; \
    int off; \
    char *old; \
    n = L->_count; k = 0; \
    if (0 < n) { off = 0; do { \
        e = (char **)((int)L->_data + off); \
        if (DAT_00586f20[0] == 0) { int pool = FUN_002eb010(0x10); if (pool != 0) pool = StringPool_Construct(pool); DAT_00586f20[0] = pool; } \
        nw = StringPool_Intern(DAT_00586f20[0], 0); old = *e; \
        if (old != 0) { int *hd = (int *)old - 2; int cnt = ((int *)old)[-1] - 1; ((int *)old)[-1] = cnt; if (cnt == 0) StringChunk_ReleaseHeader(*hd, hd); } \
        k += 1; *e = nw; off += 4; \
    } while (k < n); } }

void Gap__Bec__beNDMWShopCtrl50__vfunc_21(beNDMWShopCtrl50 *self) {
    int vA[3];
    int vB[3];
    const igObjectList *fa;
    void *alloc;
    int obj;
    int i;
    int cost0;
    int cost2;
    int objm;
    int found;
    int j;
    int money;
    int rec2;
    const igObjectList *fb;
    int jb;
    Item *it;
    Item *ib;
    char **fp;
    igStringRefList *la;
    igStringRefList *lb;

    switch (self->_st0) {
    case 0:
        beNDMWWindow_PlayQueuedModelClose(self);
        la = (igStringRefList *)self->_modelCloseInfoNameList;
        CLEAR1(la, 0)
        la->_count = 0;
        ((igIntList *)self->_modelCloseRamNoList)->_count = 0;
        lb = (igStringRefList *)self->_modelCloseSeqNameList;
        CLEAR_LIST(lb, 0)
        lb->_count = 0;
        beNDMWWindow_ClearQueuedText(self);
        self->_st0 = self->_st0 + 1;
        self->_st3 = 0;
        self->_st2 = 0;
        self->_st1 = 0;
        self->_st1 = 0;
        self->_st3 = 0;
        self->_st2 = 0;
    case 1:
        switch (self->_st1) {
        case 0:
            switch (self->_st2) {
            default:
                return;
            case 0:
                ALLOC(alloc, self)
                {
                ResultRef spCC((igObject *)FUN_003b4d90(alloc));
                beNDMWWindow_BindContext(spCC.p, self, self->_insight, self->_playerNo, 0x60E);
                ObjectList_AppendRetained(self->_subWindow, spCC.p);
                }
                self->_nowProcKazu = SUBCNT(self);
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
            case 1:
                if (SUBCNT(self) != self->_nowProcKazu) {
                    switch (self->_retCode) {
                    case 0:
                        self->_st1 = 1;
                        self->_st3 = 0;
                        self->_st2 = 0;
                        self->_cursor = 0;
                        return;
                    case 1:
                        self->_st1 = 4;
                        self->_st3 = 0;
                        self->_st2 = 0;
                        return;
                    case 2: default:
                        self->_st0 = self->_st0 + 1;
                        self->_st3 = 0;
                        self->_st2 = 0;
                        self->_st1 = 0;
                        return;
                    }
                }
                break;
            }
            break;
        case 1:
            switch (self->_st2) {
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
                beMessenger_SendNamed(self->_messenger, &DAT_0051b5d8[0], &DAT_0051b660[0], 0, &DAT_0051b5e8[0]);
                obj = beMessenger_GetObject(self->_messenger, 0);
                INTERN_APPEND(self->_textCloseTypeList, &DAT_0051b668[0])
                INTERN_APPEND(self->_textCloseNameList, DAT_004cf8a0[0])
                beNDMWWindow_RunMessageScript(self, &DAT_0051b3b0[0], 0x5DD);
                i = 0;
                fp = &DAT_004cf8a0[0];
                do {
                    FUN_003f5410(self, &DAT_0051b3c8[0], *fp, beDataBase_GetRecordString(obj, i, &DAT_0051b678[0]), &DAT_0051b598[0]);
                    FUN_003f5660(self, &DAT_0051b680[0], *fp, beDataBase_GetRecordInt(obj, i, &DAT_0051b690[0]), &DAT_0051b460[0]);
                    i += 1;
                    fp += 1;
                } while (i < 10);
                FUN_003f5410(self, &DAT_0051b470[0], DAT_004cf8a0[0], &DAT_0051b590[0], &DAT_0051b598[0]);
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
            case 1:
                FUN_0042bae0(self, -1);
                beMessenger_SendNamed(self->_messenger, &DAT_0051b308[0], &DAT_0051b610[0], 0, &DAT_0051b698[0]);
                ALLOC(alloc, self)
                {
                SelectE1Ref spC8((igObject *)FUN_003b51b0(alloc));
                beNDMWWindow_BindContext(spC8.p, self, self->_insight, self->_playerNo, 0);
                ObjectList_AppendRetained(self->_subWindow, spC8.p);
                { beNDMWWindowSelect *w = (beNDMWWindowSelect *)spC8.p; w->_offsetPos[0] = -121.0f; w->_offsetPos[1] = 128.0f; w->_offsetPos[2] = 0.0f; }
                ((beNDMWWindowSelect *)spC8.p)->_startPoint = self->_cursor;
                ((beNDMWWindowSelect *)spC8.p)->_selectMax = 10;
                INTERN_APPEND(((beNDMWWindow *)spC8.p)->_textCloseTypeList, &DAT_0051b470[0])
                INTERN_APPEND(((beNDMWWindow *)spC8.p)->_textCloseNameList, &DAT_0051b548[0])
                beNDMWWindow_RunMessageScript(spC8.p, &DAT_0051b3b0[0], 0x611);
                }
                self->_nowProcKazu = SUBCNT(self);
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
                self->_retCode = self->_cursor;
            case 2:
                if (self->_retCode != -1) {
                    beMessenger_SendNamed(self->_messenger, &DAT_0051b5d8[0], &DAT_0051b660[0], 0, &DAT_0051b5e8[0]);
                    obj = beMessenger_GetObject(self->_messenger, 0);
                    beMessenger_SelectGroup(self->_messenger, &DAT_0051b3c0[0]);
                    beMessenger_AppendString(self->_messenger, &DAT_0051b470[0]);
                    beMessenger_AppendString(self->_messenger, DAT_004cf8a0[0]);
                    { int ms = self->_messenger; beMessenger_AppendString(ms, beDataBase_GetRecordString(obj, self->_retCode, &DAT_0051b6a8[0])); }
                    beMessenger_DispatchSelected(self->_messenger, &DAT_0051b6b0[0]);
                    beMessenger_SelectGroup(self->_messenger, &DAT_0051b3c0[0]);
                    beMessenger_AppendString(self->_messenger, &DAT_0051b470[0]);
                    beMessenger_AppendString(self->_messenger, DAT_004cf8a0[0]);
                    beMessenger_AppendString(self->_messenger, &DAT_0051b6b8[0]);
                    beMessenger_DispatchSelected(self->_messenger, &DAT_0051b558[0]);
                }
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
                self->_st3 = self->_retCode;
            case 3:
                if (SUBCNT(self) == self->_nowProcKazu) {
                    if (self->_retCode != -1) {
                        if (self->_retCode != self->_st3) {
                            self->_st2 = 2;
                            self->_st3 = 0;
                            return;
                        }
                    }
                } else {
                    if (self->_retCode != -1) {
                        self->_cursor = self->_retCode;
                        FUN_0042bae0(self, self->_cursor);
                        self->_conItemNo = self->_retCode;
                        beMessenger_SelectGroup(self->_messenger, &DAT_0051b398[0]);
                        beMessenger_AppendInt(self->_messenger, self->_playerNo);
                        beMessenger_DispatchSelected(self->_messenger, &DAT_0051b3e8[0]);
                        fa = igProperty_GetRecordFolder(beMessenger_GetObject(self->_messenger, 0), &DAT_0051b6c0[0])->f12;
                        found = 0;
                        j = 0;
                        if (0 < VCNT(fa)) {
                            do {
                                it = ((Item **)fa->_data)[j];
                                if (it != 0 && self->_conItemNo == it->f12) {
                                    found = it->f20;
                                    break;
                                }
                                j += 1;
                            } while (j < VCNT(fa));
                        }
                        if (found == 9) {
                            self->_st1 = 5;
                            self->_st3 = 0;
                            self->_st2 = 0;
                            self->_st3 = 0x623;
                            return;
                        }
                        self->_st1 = 2;
                        self->_st3 = 0;
                        self->_st2 = 0;
                        self->_diskCnt = found;
                        return;
                    }
                    self->_st0 = 0;
                    self->_st3 = 0;
                    self->_st2 = 0;
                    self->_st1 = 0;
                    return;
                }
                break;
            }
            break;
        case 2:
            switch (self->_st2) {
            case 0:
                beMessenger_SendNamed(self->_messenger, &DAT_0051b308[0], &DAT_0051b610[0], 0, &DAT_0051b6d0[0]);
                ALLOC(alloc, self)
                {
                QuantityRef spC4((igObject *)FUN_003b4410(alloc));
                beNDMWWindow_BindContext(spC4.p, self, self->_insight, self->_playerNo, 9 - self->_diskCnt);
                ObjectList_AppendRetained(self->_subWindow, spC4.p);
                { beNDMWWindowSelect *w = (beNDMWWindowSelect *)spC4.p; w->_offsetPos[0] = 52.0f; w->_offsetPos[1] = -69.0f; w->_offsetPos[2] = 0.0f; }
                INTERN_APPEND(((beNDMWWindow *)spC4.p)->_textCloseTypeList, &DAT_0051b470[0])
                INTERN_APPEND(((beNDMWWindow *)spC4.p)->_textCloseNameList, &DAT_0051b548[0])
                beNDMWWindow_RunMessageScript(self, &DAT_0051b3b0[0], 0x624);
                beNDMWWindow_RunMessageScript(self, &DAT_0051b3b0[0], 0x5DE);
                self->_retCode = 8 - self->_diskCnt;
                FUN_0042b880(self);
                }
                self->_nowProcKazu = SUBCNT(self);
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
            case 1:
                if (SUBCNT(self) == self->_nowProcKazu) {
                    if (self->_retCode != -1) {
                        if (self->_st3 != self->_retCode) {
                            FUN_0042b880(self);
                        }
                        self->_st3 = self->_retCode;
                        return;
                    }
                } else {
                    switch (self->_retCode) {
                    default:
                        self->_st1 = 3;
                        self->_st3 = 0;
                        self->_st2 = 0;
                        self->_st3 = (9 - self->_diskCnt) - self->_retCode;
                        return;
                    case -1:
                    FUN_0042b9d0(self);
                    self->_st1 = 1;
                    self->_st3 = 0;
                    self->_st2 = 0;
                    self->_st2 = 1;
                    self->_st3 = 0;
                    }
                    return;
                }
                break;
            }
            break;
        case 3:
            switch (self->_st2) {
            case 0:
                beMessenger_SendNamed(self->_messenger, &DAT_0051b5d8[0], &DAT_0051b660[0], 0, &DAT_0051b5e8[0]);
                self->_tanka = beDataBase_GetRecordInt(beMessenger_GetObject(self->_messenger, 0), self->_conItemNo, &DAT_0051b690[0]);
                self->_kazu = self->_st3;
                cost0 = self->_tanka * self->_kazu;
                beMessenger_SelectGroup(self->_messenger, &DAT_0051b398[0]);
                beMessenger_AppendInt(self->_messenger, self->_playerNo);
                beMessenger_DispatchSelected(self->_messenger, &DAT_0051b3e8[0]);
                if (cost0 <= W(igProperty_GetRecord(beMessenger_GetObject(self->_messenger, 0), &DAT_0051b560[0]), 12)) {
                    self->_st2 = self->_st2 + 1;
                    self->_st3 = 0;
                    return;
                }
                self->_st1 = 5;
                self->_st3 = 0;
                self->_st2 = 0;
                self->_st3 = 0x622;
                return;
            case 1:
                ALLOC(alloc, self)
                {
                ConfirmRef spC0((igObject *)FUN_003b4f50(alloc));
                beNDMWWindow_BindContext(spC0.p, self, self->_insight, self->_playerNo, 0x613);
                ObjectList_AppendRetained(self->_subWindow, spC0.p);
                }
                self->_nowProcKazu = SUBCNT(self);
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
            case 2:
                if (SUBCNT(self) != self->_nowProcKazu) {
                    ALLOC(alloc, self)
                    {
                    ResultRef spBC((igObject *)FUN_003b4d90(alloc));
                    beNDMWWindow_BindContext(spBC.p, self, self->_insight, self->_playerNo, 0x614);
                    ObjectList_AppendRetained(self->_subWindow, spBC.p);
                    }
                    self->_nowProcKazu = SUBCNT(self);
                    self->_st2 = self->_st2 + 1;
                    self->_st3 = 0;
                    return;
                }
                break;
            case 3:
                if (SUBCNT(self) != self->_nowProcKazu) {
                    FUN_0042b9d0(self);
                    switch (self->_retCode) {
                    case 0:
                        cost2 = self->_tanka * self->_kazu;
                        beMessenger_SelectGroup(self->_messenger, &DAT_0051b398[0]);
                        beMessenger_AppendInt(self->_messenger, self->_playerNo);
                        beMessenger_DispatchSelected(self->_messenger, &DAT_0051b3e8[0]);
                        objm = beMessenger_GetObject(self->_messenger, 0);
                        money = W(igProperty_GetRecord(objm, &DAT_0051b560[0]), 12);
                        rec2 = igProperty_GetRecord(objm, &DAT_0051b560[0]);
                        W(rec2, 12) = money - cost2;
                        beMessenger_SelectGroup(self->_messenger, &DAT_0051b498[0]);
                        beMessenger_AppendInt(self->_messenger, self->_playerNo);
                        beMessenger_DispatchSelected(self->_messenger, &DAT_0051b4a0[0]);
                        fb = igProperty_GetRecordFolder(objm, &DAT_0051b6c0[0])->f12;
                        jb = 0;
                        if (0 < VCNT(fb)) {
                            do {
                                ib = ((Item **)fb->_data)[jb];
                                if (ib != 0 && self->_conItemNo == ib->f12) {
                                    ib->f20 = self->_kazu + f20Of(ib);
                                    break;
                                }
                                jb += 1;
                            } while (jb < VCNT(fb));
                        }
                        break;
                    case 1: default:
                        break;
                    }
                    self->_st1 = 1;
                    self->_st3 = 0;
                    self->_st2 = 0;
                    self->_st2 = 1;
                    self->_st3 = 0;
                    return;
                }
                break;
            }
            break;
        case 5:
            switch (self->_st2) {
            case 0:
                ALLOC(alloc, self)
                {
                ConfirmRef spB8((igObject *)FUN_003b4f50(alloc));
                beNDMWWindow_BindContext(spB8.p, self, self->_insight, self->_playerNo, self->_st3);
                ObjectList_AppendRetained(self->_subWindow, spB8.p);
                }
                self->_nowProcKazu = SUBCNT(self);
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
            case 1:
                if (SUBCNT(self) != self->_nowProcKazu) {
                    FUN_0042b9d0(self);
                    self->_st1 = 1;
                    self->_st3 = 0;
                    self->_st2 = 0;
                    return;
                }
                break;
            }
            break;
        case 4:
            switch (self->_st2) {
            case 0:
                ALLOC(alloc, self)
                {
                MenuRef spB4((igObject *)FUN_003b7360(alloc));
                beNDMWWindow_BindContext(spB4.p, self, self->_insight, self->_playerNo, 0);
                ObjectList_AppendRetained(self->_subWindow, spB4.p);
                }
                self->_nowProcKazu = SUBCNT(self);
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
            case 1:
                if (SUBCNT(self) != self->_nowProcKazu) {
                    self->_st1 = 0;
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
        beNDMWWindow_PlayQueuedModelClose(self);
        beNDMWWindow_ClearQueuedText(self);
        beNDMWWindow_RequestChildrenClose(self);
        self->_st0 = self->_st0 + 1;
        self->_st3 = 0;
        self->_st2 = 0;
        self->_st1 = 0;
        return;
    case 3:
        if (beNDMWWindow_PollCloseComplete(self) != 0) {
            self->_isRun = 0;
        }
        break;
    }
}
