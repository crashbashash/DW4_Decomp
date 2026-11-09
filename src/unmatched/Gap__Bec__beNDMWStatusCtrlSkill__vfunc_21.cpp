/* Matching constructs:
 *  - class VC with 22 dummy virtuals then v22/v23/v24: virtual calls through slots at +96/+100/+104 (lw t9)
 *  - Ref smart pointer with destructor for the two window objects (stack slot, reload per use);
 *    ObjectList_AppendRetained takes the object as a pointer argument (an (int) cast flips the delay slot)
 *  - StringPool_Intern takes a pointer argument (an int argument makes the constant a hoisted loop invariant)
 *  - ternary chain in Scale (delay slot filled from the branch target); `> 1` / `> 8` compares give slti at
 *  - bool ok (daddiu s1,zero,1); cast-self-assign empty then arm; unsigned reload of the record count
 *  - switch (_nowPage) / switch (_skillMenu) with default first: case alignment nops
 *  - Clr::ClearList loops: ref = Intern(pool, 0) before old = *slot */
#include "dw4/reflected.h"

extern "C" {
int igObject_GetAllocator(void *);
int Memory_GetAllocatorBySelector(int);
int FUN_003b5530(int);
int FUN_003b51b0(int);
void beNDMWWindow_BindContext(int, void *, int, int, int);
void ObjectList_AppendRetained(int, void *);
void FUN_003f5410(void *, void *, int, void *, void *);
void igObject_Destroy(void *);
void FUN_00443110(int, int, int);
int FUN_002eb010(int);
int StringPool_Construct(int);
int StringPool_Intern(int, void *);
void StringList_AppendRetained(int, int *);
void StringChunk_ReleaseHeader(int, int *);
void FUN_00420230(void *, int, int);
void beMessenger_SelectGroup(int, void *);
void beMessenger_AppendInt(int, int);
void beMessenger_AppendString(int, void *);
void beMessenger_AppendVec3(int, void *);
void beMessenger_DispatchSelected(int, void *);
int beMessenger_GetObject(int, int);
int FUN_003a9250(int, void *);
int igProperty_GetRecord(int, void *);
int igProperty_GetRecordFolder(int, void *);
void sprintf(void *, void *, int);
int FUN_00236f80(int, int);
int beNDMWItemBase_GetRecordString(int, int, void *);
int igObject_IsKindOf(int, int);
int beNDMWWindowSelect_CanRequestFO2TOP(int);
void beNDMWWindow_PresentModelAtOrigin(void *, void *, int, void *, void *);
void beNDMWWindow_RunMessageScript(void *, void *, int);
void beNDMWWindow_ClearQueuedText(void *);
void beNDMWWindow_PlayQueuedModelClose(void *);
void beNDMWWindow_RequestChildrenClose(void *);
void beNDMWWindow_SendModelSequence(void *, void *, int, void *);
int beNDMWWindow_PollCloseComplete(void *);
extern unsigned char GPR_00554c14;
extern int DAT_00586f20[4];
extern int DAT_00587110[4];
extern int DAT_0058b028[4];
extern int DAT_0058abd8[4];
extern int DAT_004cf670[];
extern int DAT_004cf674[4];
extern int DAT_00519a58[4], DAT_00519ad0[4], DAT_00519b00[4], DAT_00519b08[4], DAT_00519b50[4], DAT_00519b60[4], DAT_00519b68[4];
extern int DAT_00519b80[4], DAT_00519b90[4], DAT_00519ba0[4], DAT_00519ba8[4], DAT_00519c28[4], DAT_00519c30[4], DAT_00519f28[4];
extern int DAT_00519f38[4], DAT_00519f90[4], DAT_00519ff8[4], DAT_0051a040[4], DAT_0051a060[4], DAT_0051a080[4], DAT_0051a0a8[4];
extern int DAT_0051a1f8[4], DAT_0051a2d0[4], DAT_0051a340[4], DAT_0051a350[4], DAT_0051a360[4], DAT_0051a370[4], DAT_0051a380[4];
extern int DAT_0051a390[4], DAT_0051a3a0[4], DAT_0051a3b0[4];
void Gap__Bec__beNDMWStatusCtrlSkill__vfunc_21(beNDMWStatusCtrlSkill *);
}

struct VC { virtual void d0();virtual void d1();virtual void d2();virtual void d3();virtual void d4();virtual void d5();virtual void d6();virtual void d7();virtual void d8();virtual void d9();virtual void d10();virtual void d11();virtual void d12();virtual void d13();virtual void d14();virtual void d15();virtual void d16();virtual void d17();virtual void d18();virtual void d19();virtual void d20();virtual void d21(); virtual void v22(void *, void *); virtual int v23(); virtual int v24(); };
/* igSmartPointer<igObject> holds the menu window and RefB the detail window; each is its own class so it gets its own
 * destructor copy. */
template <class T> struct igSmartPointer {
    T *p;
    igSmartPointer(int x) { p = (T *)x; }
    ~igSmartPointer() { T *o; if ((o = p) != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
struct RefB {
    igObject *p;
    RefB(int x) { p = (igObject *)x; }
    ~RefB() { igObject *o; if ((o = p) != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
/* Interned-string reference (count at p[-1], header at p[-2]). */
struct StringRef {
    int p;
    StringRef(int x) { p = x; }
    ~StringRef() {
        if (p) {
            int *header = (int *)(p - 8);
            int count = *(int *)(p - 4) - 1;
            *(int *)(p - 4) = count;
            if (!count) StringChunk_ReleaseHeader(*header, header);
        }
    }
};
#define APPSTR_C(LIST, TEXT) { StringRef slot_(H::intern((int *)(TEXT))); StringList_AppendRetained((LIST), &slot_.p); }
#define APPSTR_V(LIST, TEXT) { StringRef slot_(H::intern((int *)(TEXT))); StringList_AppendRetained((LIST), &slot_.p); }
struct H {
static inline int intern(int *s)
{
    int ref;
    int pool;
    if (s == 0) {
        ref = 0;
    } else {
        if (DAT_00586f20[0] == 0) {
            pool = FUN_002eb010(16);
            if (pool)
                pool = StringPool_Construct(pool);
            DAT_00586f20[0] = pool;
        }
        ref = StringPool_Intern(DAT_00586f20[0], s);
    }
    return ref;
}
static inline void release(int ref)
{
    int *header;
    int count;
    if (ref) {
        header = (int *)(ref - 8);
        count = *(int *)(ref - 4) - 1;
        *(int *)(ref - 4) = count;
        if (!count)
            StringChunk_ReleaseHeader(*header, header);
    }
}
static inline void ClearStrList(int listHandle)
{
    igStringRefList *l = (igStringRefList *)listHandle;
    int n = l->_count;
    int i;
    int **slot; int *ref; int *old; int pool; int *a1; int c;
    for (i = 0; i < n; i++) {
        slot = &((int **)l->_data)[i];
        if (DAT_00586f20[0] == 0) {
            pool = FUN_002eb010(16);
            if (pool) pool = StringPool_Construct(pool);
            DAT_00586f20[0] = pool;
        }
        ref = (int *)StringPool_Intern(DAT_00586f20[0], 0);
        old = *slot;
        if (old) { a1 = old - 2; c = old[-1] - 1; old[-1] = c; if (c == 0) StringChunk_ReleaseHeader(*a1, a1); }
        *slot = ref;
    }
    l->_count = 0;
}

static inline int PickAllocator(void *obj)
{
    int a = igObject_GetAllocator(obj);
    return GPR_00554c14 != 0 ? a : Memory_GetAllocatorBySelector(DAT_00587110[0]);
}

static inline int Scale(int v)
{
    int r = v < 37 ? v * 30 : v < 108 ? v * 20 + 360 : v < 228 ? v * 10 + 1430 : v * 8 + 1884;
    return r;
}

};
#define SWV(h) ((igObjectList *)*(int *)&(h))
#define SW(h) ((igObjectList *)(h))

void Gap__Bec__beNDMWStatusCtrlSkill__vfunc_21(beNDMWStatusCtrlSkill *self)
{
    int st0 = self->_st0;
    switch (st0) {
    case 0:
        beNDMWWindow_PresentModelAtOrigin(self, DAT_00519b80, 0, DAT_00519ad0, 0);
        beNDMWWindow_RunMessageScript(self, DAT_00519b90, 90);
        self->_skillMenu = 0;
        self->_st0 = self->_st0 + 1;
        self->_st3 = 0;
        self->_st2 = 0;
        self->_st1 = 0;
    case 1:
        switch (self->_st1) {
        case 0: {
            igSmartPointer<igObject> wr(FUN_003b5530(H::PickAllocator(self)));
            beNDMWWindow_BindContext((int)wr.p, self, self->_insight, self->_playerNo, 91);
            ObjectList_AppendRetained(self->_subWindow, wr.p);
            ((int *)wr.p)[25] = self->_skillMenu;
            FUN_003f5410(wr.p, DAT_00519b50, DAT_004cf670[0], DAT_00519b60, DAT_00519b68);
            
            }
            self->_nowProcKazu = SW(self->_subWindow)->_count;
            self->_st1 = self->_st1 + 1;
            self->_st3 = 0;
            self->_st2 = 0;
        case 1:
            if (self->_retCode != -1)
                beNDMWWindow_RunMessageScript(self, DAT_00519b90, self->_retCode + 98);
            self->_st1 = self->_st1 + 1;
            self->_st3 = 0;
            self->_st2 = 0;
            self->_st3 = self->_retCode;
        case 2:
            if (SW(self->_subWindow)->_count == self->_nowProcKazu) {
                if (self->_retCode != -1 && self->_st3 != self->_retCode) {
                    self->_st1 = 1;
                    self->_st3 = 0;
                    self->_st2 = 0;
                }
            } else
            switch (self->_retCode) {
            case 0:
                FUN_00443110(self->_shinkaCtrl, self->_insight, self->_playerNo);
                if (SW(((beNDMWShinkaCtrl *)self->_shinkaCtrl)->_list)->_count > 8)
                    self->_maxPage = 2;
                else
                    self->_maxPage = 1;
                self->_nowPage = 0;
                self->_cursor = 0;
            case 1:
            case 2:
                self->_skillMenu = self->_retCode;
                self->_st1 = 3;
                self->_st3 = 0;
                self->_st2 = 0;
                break;
            default:
                self->_st0 = self->_st0 + 1;
                self->_st3 = 0;
                self->_st2 = 0;
                self->_st1 = 0;
                break;
            }
            break;
        case 3:
            switch (self->_st2) {
            case 0: {
                void *model;
                switch (self->_skillMenu) {
                default: {
                    int b[3];
                    int a[3];
                    if (self->_maxPage > 1)
                        model = DAT_0051a340;
                    else
                        model = DAT_0051a350;
                    a[0] = 0x42FE0000;
                    a[1] = 0x42820000;
                    a[2] = 0;
                    b[0] = 0xC3120000;
                    b[1] = 0x42820000;
                    b[2] = 0;
                    ((VC *)self)->v22(b, a);
                    break;
                }
                case 1:
                    model = DAT_0051a350;
                    break;
                case 2:
                    model = DAT_0051a360;
                    break;
                }
                beNDMWWindow_PresentModelAtOrigin(self, DAT_0051a0a8, 0, model, DAT_00519a58);
                RefB wr(FUN_003b51b0(H::PickAllocator(self)));
                beNDMWWindow_BindContext((int)wr.p, self, self->_insight, self->_playerNo, 0);
                ObjectList_AppendRetained(self->_subWindow, wr.p);
                { int *t = (int *)wr.p; t[22] = 0xC2F20000;
                t[23] = 0x43000000;
                t[24] = 0; }
                ((int *)wr.p)[25] = 0;
                APPSTR_C(self->_textCloseTypeList, DAT_0051a040);
                APPSTR_V(self->_textCloseNameList, DAT_004cf670[0]);
                beNDMWWindow_RunMessageScript(self, DAT_00519b90, self->_skillMenu + 95);
                switch (self->_skillMenu) {
                case 0: {
                    int n;
                    int i;
                    igObjectList *sl = SW(((beNDMWShinkaCtrl *)self->_shinkaCtrl)->_list);
                    if (self->_maxPage > 1) {
                        n = 8;
                        FUN_003f5410(self, DAT_0051a370, DAT_004cf670[0], DAT_00519b60, DAT_0051a1f8);
                        FUN_003f5410(self, DAT_0051a370, DAT_004cf674[0], DAT_00519b60, DAT_0051a1f8);
                    } else {
                        if (sl->_count == 0) n = 2; else n = sl->_count;
                    }
                    for (i = 0; i < n; i++) {
                        FUN_003f5410(self, DAT_0051a060, DAT_004cf670[i], DAT_00519b60, DAT_00519b68);
                        FUN_003f5410(self, DAT_0051a380, DAT_004cf670[i], DAT_00519b60, DAT_00519b68);
                        FUN_003f5410(self, DAT_0051a390, DAT_004cf670[i], DAT_00519b60, DAT_0051a080);
                    }
                    FUN_00420230(self, 1, 0);
                    ((int *)wr.p)[21] = n;
                    break;
                }
                case 1: {
                    int obj;
                    igObjectList *recs;
                    int level;
                    int limit;
                    int i;
                    char buf[24];
                    beMessenger_SelectGroup(self->_messenger, DAT_00519ba0);
                    beMessenger_AppendInt(self->_messenger, self->_playerNo);
                    beMessenger_DispatchSelected(self->_messenger, DAT_00519ba8);
                    obj = beMessenger_GetObject(self->_messenger, 0);
                    recs = (igObjectList *)*(int *)(FUN_003a9250(obj, DAT_00519f90) + 12);
                    level = *(int *)(igProperty_GetRecord(obj, DAT_00519ff8) + 12);
                    limit = H::Scale(level);
                    for (i = 0; i < recs->_count; i++) {
                        APPSTR_C(self->_textCloseTypeList, DAT_0051a060);
                        APPSTR_V(self->_textCloseNameList, DAT_004cf670[i]);
                        sprintf(buf, DAT_0051a2d0, ((int *)recs->_data)[i]);
                        FUN_003f5410(self, DAT_0051a390, DAT_004cf670[i], buf, DAT_0051a080);
                        beMessenger_SelectGroup(self->_messenger, DAT_00519c28);
                        beMessenger_AppendString(self->_messenger, DAT_0051a060);
                        beMessenger_AppendString(self->_messenger, (void *)DAT_004cf670[i]);
                        if (((int *)recs->_data)[i] >= limit) {
                            float col[3];
                            col[0] = 0.9f;
                            col[1] = 0.4f;
                            col[2] = 0.2f;
                            beMessenger_AppendVec3(self->_messenger, col);
                            beMessenger_DispatchSelected(self->_messenger, DAT_00519f38);
                        } else {
                            beMessenger_DispatchSelected(self->_messenger, DAT_00519c30);
                        }
                    }
                    beNDMWWindow_RunMessageScript(self, DAT_00519b90, 101);
                    ((int *)wr.p)[21] = recs->_count;
                    break;
                }
                case 2: {
                    igObjectList *recs;
                    int ctx;
                    int i;
                    int n;
                    beMessenger_SelectGroup(self->_messenger, DAT_00519ba0);
                    beMessenger_AppendInt(self->_messenger, self->_playerNo);
                    beMessenger_DispatchSelected(self->_messenger, DAT_00519ba8);
                    recs = (igObjectList *)*(int *)(igProperty_GetRecordFolder(beMessenger_GetObject(self->_messenger, 0), DAT_0051a3a0) + 12);
                    ctx = FUN_00236f80(self->_insight, DAT_0058b028[0]);
                    for (i = 0; i < recs->_count; i++) {
                        FUN_003f5410(self, DAT_0051a060, DAT_004cf670[i],
                                     (void *)beNDMWItemBase_GetRecordString(((int *)recs->_data)[i], ctx, DAT_00519f28),
                                     DAT_00519b68);
                    }
                    n = *(unsigned *)&recs->_count;
                    if (n == 0)
                        ((int *)wr.p)[21] = 1;
                    else
                        ((int *)wr.p)[21] = n;
                    break;
                }
                }
                FUN_003f5410(self, DAT_00519b50, DAT_004cf670[0], DAT_00519b60, DAT_00519b68);
                
                }
                self->_nowProcKazu = SW(self->_subWindow)->_count;
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
                self->_retCode = 0;
            case 1:
                if (self->_retCode != -1)
                    FUN_00420230(self, 0, 1);
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
                self->_st3 = self->_retCode;
            case 2: {
                int n = SW(self->_subWindow)->_count;
                if (n == self->_nowProcKazu) {
                    if (self->_retCode != -1) {
                    if (self->_st3 != self->_retCode) {
                        self->_st2 = 1;
                        self->_st3 = 0;
                    } else
                    if (self->_skillMenu == 0) {
                        int found = 0;
                        int i;
                        for (i = 0; i < SW(self->_subWindow)->_count; i++) {
                            found = ((int *)SWV(self->_subWindow)->_data)[i];
                            if (found && igObject_IsKindOf(found, DAT_0058abd8[0])) {
                                found = (int)(int *)found;
                            } else
                                found = 0;
                            if (found)
                                break;
                        }
                        if (found) {
                            bool ok = false;
                            if (beNDMWWindowSelect_CanRequestFO2TOP(found)) {
                                if (((VC *)self)->v23())
                                    ok = true;
                                else if (((VC *)self)->v24())
                                    ok = true;
                            }
                            if (ok) {
                                int *f = (int *)found;
                                f[7] = 4;
                                f[10] = 0;
                                f[9] = 0;
                                f[8] = 0;
                                switch (self->_nowPage) {
                                default:
                                    f[21] = 8;
                                    break;
                                case 1:
                                    f[21] = SW(((beNDMWShinkaCtrl *)self->_shinkaCtrl)->_list)->_count - 8;
                                    break;
                                }
                                self->_st2 = 1;
                                self->_st3 = 0;
                                self->_retCode = 0;
                                FUN_00420230(self, 1, 0);
                            }
                        }
                    }
                    }
                } else {
                    if (self->_skillMenu == 1) {
                        int i;
                        for (i = 0; i < 9; i++) {
                            beMessenger_SelectGroup(self->_messenger, DAT_00519c28);
                            beMessenger_AppendString(self->_messenger, DAT_0051a060);
                            beMessenger_AppendString(self->_messenger, (void *)DAT_004cf670[i]);
                            beMessenger_DispatchSelected(self->_messenger, DAT_00519c30);
                        }
                    }
                    beNDMWWindow_PlayQueuedModelClose(self);
                    H::ClearStrList(self->_modelCloseInfoNameList);
                    SW(self->_modelCloseRamNoList)->_count = 0;
                    H::ClearStrList(self->_modelCloseSeqNameList);
                    beNDMWWindow_ClearQueuedText(self);
                    self->_retCode = self->_skillMenu;
                    self->_st1 = 0;
                    self->_st3 = 0;
                    self->_st2 = 0;
                }
                break;
            }
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
        beNDMWWindow_SendModelSequence(self, DAT_00519b80, 0, DAT_00519a58);
        beMessenger_SelectGroup(self->_messenger, DAT_00519c28);
        beMessenger_AppendString(self->_messenger, DAT_0051a3b0);
        beMessenger_AppendString(self->_messenger, (void *)DAT_004cf670[0]);
        beMessenger_AppendString(self->_messenger, DAT_00519b00);
        beMessenger_DispatchSelected(self->_messenger, DAT_00519b08);
        return;
    case 3:
        if (beNDMWWindow_PollCloseComplete(self))
            self->_isRun = 0;
        break;
    }
}
