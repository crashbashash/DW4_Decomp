#include "dw4/reflected.h"
#include "dw4/igTDataList.h"
#include "dw4/igSmartPointer.h"
#define SLOTS ((igObjectList *)self->_hdSEs)
#define ENTS ((igObjectList *)self->_lsBinObjs)
#define DEFN ((char *)emptyString)
#define LIST(a) (*(void **)((a) + 40))

extern "C" int FUN_0037b010(void *node, void *traversal);
extern "C" int igAttrStackManager_MarkStackChanged(...);
extern "C" int igTraversal_TraverseChildren(void *, void *);
extern "C" int igObjectPool_Grow(void *, void *);
extern "C" int FUN_001356b0(...);
extern "C" int igTimeAttr_CreateInstance(...);
extern "C" int igMatrix44f_SetIdentity(void *);
extern "C" int FUN_001904f0(void *, void *, void *);
extern "C" int Matrix44_Copy(void *, void *);
extern "C" int igTraversal_RegisterFunction(int, int, void (*)());
extern "C" int FUN_003680b0(...);
extern "C" void FUN_0037b460(void);
extern "C" int FUN_00367e50(...);
extern "C" void FUN_0037b760(void);
extern "C" int FUN_00306360(int, const char *, int);
extern "C" void FUN_0030b3c0(...);
extern "C" void FUN_003327c0(const char *);
extern "C" void FUN_00332810(int);
extern "C" void FUN_00332c50(int);
extern "C" void * Memory_GetAllocatorBySelector(...);
extern "C" void * igObject_GetAllocator(...);
extern "C" int strcmp(...);
extern "C" int FUN_0037b950(void);
extern "C" int FUN_00236c40(...);
extern "C" int FUN_00236f80(int, int);
extern "C" int beCriAudio_Setup(int, int);
extern "C" int igNamedObject_SetName(...);
extern "C" int beCriAudio_Release(int);
extern "C" int ObjectList_AppendRetained(...);
extern "C" int List_Reserve(...);
extern "C" int FUN_00332cf0(...);
extern "C" int beCriAudio_SetVolume(...);
extern "C" int beCriAudio_GetStatus(...);
extern "C" int beCriAudio_IsPaused(...);
extern "C" int beCriAudio_Suspend(...);
extern "C" int beCriAudio_Resume(...);
extern "C" int beCriVolume_StepAdxLevel(...);
extern "C" int beCriVolume_StepSndfLevel(...);
extern "C" int ObjectList_RemoveFirstRetained(...);
extern "C" int beCriAudio_PlayFile(...);
extern "C" int beCriAudio_Pause(...);
extern "C" int strlen(...);
extern "C" int FUN_00332d20(int);
extern "C" int FUN_00333230(int);
extern "C" void FUN_0037d270(int dummy0, int arg1, int arg2);
extern "C" int FUN_003332b0(int, int, int);
extern "C" void FUN_0037d2a0(int arg0, int arg1, int arg2);
extern "C" void FUN_00332e90(int, int);
extern "C" void FUN_0037d2f0(int p0, int p1);
extern "C" void FUN_0037d310(int arg0);
extern "C" int List_RemoveWordAt(int *, int);
extern "C" void FUN_0037d4a0(int *arg0);
extern "C" int FUN_00280f60(int *);
extern "C" int FUN_00281078(int, int);
extern "C" int FUN_002813c8(int);
extern "C" int FUN_00281cf8(...);
extern "C" int Memory_FreeBuffer(...);
extern "C" void FUN_002829f0(int, int);
extern "C" void FUN_0037dc60(int *arg0, char *arg1);
extern "C" int igAdxAudio_GetStatus(int);
extern "C" int FUN_002825e0(int, unsigned int, int);
extern "C" int igObject_IsKindOf(int, int);
extern "C" int FUN_00308860(int, int *, int);
extern "C" int igMemoryRefMetaField_SetAlignmentType(int, int *);
extern "C" int igMetaObject_FindFieldByName(int, int *);
extern "C" void FUN_0037e070(void);
extern "C" int Gap__Bec__beCri__vfunc_20(void);
typedef int (*CB)(void *, int, void *);
/* vtable view of an item: slot 30 takes the transform */
class Item { public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
    virtual void v30(void *);
};
/* vtable view of the traversal context (igCommonTraversal): slots 30/31 only */
class Trav { public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
    virtual void v30(long long);
    virtual void v31();
};
template <class T> struct AttrSlots : igTDataList<T> {
};
struct Mat { int w[16]; };
struct Src { int pad[8]; Mat m32; int pad2[4]; long long t112; };
struct Rec { int pad[8]; Mat m32; int pad2[3]; Src *src108; };
struct Dat { int pad[2]; int f8; };
extern "C" Dat *g_igModelViewMatrixAttr_metaObject[4];
extern "C" int FUN_0037b040(Rec *arg0, igCommonTraversal *arg1);
extern "C" int DAT_00562640[4];
extern "C" int FUN_0037b4a0(igCommonTraversal *traversal, void *node);
struct ItemStack : igTDataList<Item *> {
};
struct Rec_37b4d0 { int pad[8]; Mat m32; int pad2[3]; Mat *src108; };
extern "C" int FUN_0037b4d0(Rec_37b4d0 *arg0, igCommonTraversal *arg1);
extern "C" void FUN_00236be0(int, beCri *);
extern "C" igStringObj *FUN_002b9500(void *);
extern "C" int FUN_00306770(int, int, const char *, igSmartPointer<igStringObj> *, const char *, int);
struct IniRoot { char pad[56]; int ini; };
struct ErrorHooks { char pad[60]; void (*onError)(void); };
extern "C" IniRoot *g_objectSystem[4];
extern "C" ErrorHooks *g_igFile_metaObject[4];
extern "C" void (*DAT_0058a350[4])(void);
extern "C" int DAT_005873c8[4];
extern "C" int g_defaultAllocatorSelector[4];
extern "C" char *DAT_004c22f0[4];
extern "C" char DAT_0050e400[];
extern "C" char DAT_0050e410[];
extern "C" char DAT_0050e420[];
extern "C" char DAT_0050e428[];
extern "C" char DAT_0050e438[];
extern "C" char DAT_0050e440[];
extern "C" char DAT_0050e460[];
extern "C" unsigned char GPR_00554c14;
extern "C" unsigned char GPR_00554de4;
extern "C" void Gap__Bec__beCri__vfunc_21(beCri *self);
extern "C" int g_igAdxFile_metaObject[4];
extern "C" void Gap__Bec__beCri__vfunc_22(beCri *arg0);
struct RefCountedNamedObject { int w0; int rc; int w8; int f12; };
extern "C" struct RefCountedNamedObject * FUN_00366910(...);
extern "C" int g_ndmwAllocatorSelector[4];
extern "C" int g_beSystem_metaObject[4];
extern "C" int DAT_0058a360[4];
extern "C" int DAT_0058a460[4];
extern "C" void Gap__Bec__beCri__vfunc_23(beCri *arg0);
extern "C" void Gap__Bec__beCri__vfunc_24(beCri *arg0);
extern "C" int g_beCriFxInfo_metaObject[4];
class DW4VC_88_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); };
extern "C" int Gap__Bec__beCri__vfunc_25(beCri *arg0, void **arg1);
extern "C" int DAT_0050e480[4];
extern "C" void Gap__Bec__beCri__vfunc_26(beCri *arg0);
struct CriSystemState { char p0[88]; int f88; };
extern "C" void Gap__Bec__beCri__vfunc_27(beCri *arg0);
extern "C" int emptyString[4];
extern "C" void beCriVolume_StartFade(beCriVolume *, int, float, float, float);
extern "C" long long FUN_0037c2c0(beCri *self, igObjectList *table, beSoundData *ev);
extern "C" int FUN_0037c130(beCri *self, unsigned char kind, short priority);
extern "C" int beCriAudio_PlayMemory(beCriAudio *, void *, int);
extern "C" int beCriAudio_PlaySfp(beCriAudio *, int, int);
extern "C" int FUN_0030ba20(igNamedObject *);
extern "C" int FUN_0030b5c0(igNamedObject *);
extern "C" long long FUN_0037c4c0(beCri *self, igObjectList *lst, beSoundData *req);
extern "C" int beCriAudio_Stop(beCriAudio *);
extern "C" void FUN_0037caf0(void *arg0, beCriHandle *arg1);
extern "C" void FUN_0037cb80(beCri *arg0, long long arg1);
typedef struct L { char p8[8]; int n; char p12[4]; int *data; } L;
typedef struct O { char p32[32]; int f32; int f36; L *f40; } O;
extern "C" void FUN_0037cc50(O *arg0, int arg1);
extern "C" void FUN_0037cd90(beCri *arg0, int arg1);
extern "C" void FUN_0037cf30(beCri *arg0, char *arg1, float f0, float f1, float f2);
extern "C" void FUN_0037d160(beCri *arg0, long long arg1, float fparg0, float fparg1, float fparg2);
extern "C" int DAT_005875e8[4];
struct Obj : public igObject { int w8; int w12; };
typedef struct Obj_37d4a0 { int w0; unsigned refs; } Obj_37d4a0;
typedef struct Target { int w0, w4, w8, w12; int kind; } Target;
typedef struct Entry { int w0, w4, w8; Target *target; int w16, w20; long long armed; short type; } Entry;
typedef struct EntryList { int w0, w4; int count; int w12; Entry **items; } EntryList;
typedef struct Owner { char pad[40]; EntryList *list; } Owner;
extern "C" void FUN_0037d570(Owner *self, int on);
extern "C" int DAT_0058a3e0[4];
extern "C" int FUN_0037d680(beCri *arg0, beCriSfpData *arg1);
extern "C" bool FUN_0037d780(beCri *o);
extern "C" int g_beCriSfpData_metaObject[4];
extern "C" int g_beCriAcxData_metaObject[4];
/* matching construct: dummy-virtual view (20 slots) so Kind() compiles to the retail jalr; fields are read through beCriSfpData. */
struct SndKindV {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual int Kind();
};
extern "C" int FUN_0037d870(beCri *arg0, int arg1);
extern "C" bool FUN_0037daf0(beCri *arg0);
typedef struct N { int w[2]; char *name; int w3[3]; int val; } N;
typedef struct L_37dc60 { int w[2]; int cnt; int w3; N **arr; } L_37dc60;
extern "C" int DAT_0050e488[4];
extern "C" unsigned char FUN_0037dd10(beCri *arg0, int *arg1);
extern "C" void FUN_0037e020(beCri *arg0, int arg1);
extern "C" int DAT_0050e490[4];
extern "C" int DAT_0050e4a0[4];
extern "C" int g_igMemoryRefMetaField_metaObject[4];
extern "C" int g_globalContext[4];
extern "C" int g_beCri_metaObject[4];

int FUN_0037b010(void *node, void *traversal) {
    return FUN_0037b040((Rec *)traversal, (igCommonTraversal *)node);
}

/* matching construct: the reflected fields hold 4-byte handles; the casts give the typed views (no layout effect) */
int FUN_0037b040(Rec *arg0, igCommonTraversal *arg1)
{
    igAttrStackManager *b;
    int idxB;
    Mat mA;
    Mat mB;
    long long t;
    igObjectPool *p;
    igObjectPool *p2;
    Item *item;
    igTimeAttr *item2;
    int cnt;
    igAttrStack *l;
    int idx;
    int r;
    int idx2;
    igAttrStack *l2;
    CB cb;
    void *ob;
    int ix;
    void **dp;
    short *pg;
    short *pi;
    short *pg2;
    short *pi2;
    int n1;

    b = (igAttrStackManager *)arg1->_attrStack;
    ix = g_igModelViewMatrixAttr_metaObject[0]->f8;
    l = ((igAttrStack **)((igObjectList *)b->_attrStacks)->_data)[((int *)b->_attrStackIndexTable)[ix]];
    Matrix44_Copy(&arg0->m32, &arg0->src108->m32);
    t = arg0->src108->t112;
    igMatrix44f_SetIdentity(&mA);
    if (l->_count != 0) {
        n1 = l->_count - 1;
        FUN_001904f0(&mA, &arg0->m32, (char *)((void **)l->_data)[n1] + 12);
    } else {
        igMatrix44f_SetIdentity(&mB);
        FUN_001904f0(&mA, &arg0->m32, &mB);
    }
    p = (igObjectPool *)arg1->_matrixPool;
    if (p->_freeIndex >= p->_count) {
        igObjectPool_Grow(p, (void *)&FUN_001356b0);
    }
    cnt = p->_freeIndex;
    p->_freeIndex = cnt + 1;
    item = ((Item **)p->_data)[cnt];
    item->v30(&mA);
    p2 = (igObjectPool *)arg1->_timePool;
    if (p2->_freeIndex >= p2->_count) {
        igObjectPool_Grow(p2, (void *)&igTimeAttr_CreateInstance);
    }
    cnt = p2->_freeIndex;
    p2->_freeIndex = cnt + 1;
    item2 = ((igTimeAttr **)p2->_data)[cnt];
    item2->_time = t;
    ((Trav *)arg1)->v30(t);
    pg = &((igAttr *)item)->_cachedAttrIndex;
    pi = &((igAttr *)item)->_cachedUnitID;
    idx = *pi + ((int *)b->_attrStackIndexTable)[*pg];
    l = ((igAttrStack **)((igObjectList *)b->_attrStacks)->_data)[idx];
    ((AttrSlots<Item *> *)l)->append(item);
    igAttrStackManager_MarkStackChanged(b, l, idx);
    pg2 = &item2->_cachedAttrIndex;
    pi2 = &item2->_cachedUnitID;
    idxB = *pi2 + ((int *)b->_attrStackIndexTable)[*pg2];
    l = ((igAttrStack **)((igObjectList *)b->_attrStacks)->_data)[idxB];
    ((AttrSlots<igTimeAttr *> *)l)->append(item2);
    igAttrStackManager_MarkStackChanged(b, l, idxB);
    r = igTraversal_TraverseChildren(arg1, arg0);
    idx2 = *pi2 + ((int *)b->_attrStackIndexTable)[*pg2];
    l2 = ((igAttrStack **)((igObjectList *)b->_attrStacks)->_data)[idx2];
    ix = l2->_count - 1;
    cb = (CB)l2->_popProc;
    ob = ((void **)l2->_data)[ix];
    if (cb != 0) {
        cb(ob, b->_popProcData, cb);
    }
    l2->_count = l2->_count - 1;
    igAttrStackManager_MarkStackChanged(b, l2, idx2);
    idx2 = *pi + ((int *)b->_attrStackIndexTable)[*pg];
    l2 = ((igAttrStack **)((igObjectList *)b->_attrStacks)->_data)[idx2];
    ix = l2->_count - 1;
    cb = (CB)l2->_popProc;
    ob = ((void **)l2->_data)[ix];
    if (cb != 0) {
        cb(ob, b->_popProcData, cb);
    }
    l2->_count = l2->_count - 1;
    igAttrStackManager_MarkStackChanged(b, l2, idx2);
    ((Trav *)arg1)->v31();
    if (r == 2) {
        return 2;
    }
    return 0;
}

void FUN_0037b460(void) {
    igTraversal_RegisterFunction(DAT_00562640[0], FUN_003680b0(), (void (*)())FUN_0037b010);
}

int FUN_0037b4a0(igCommonTraversal *traversal, void *node)
{
    return FUN_0037b4d0((Rec_37b4d0 *)node, traversal);
}

/* matching construct: the reflected fields hold 4-byte handles (_attrStack is the igAttrStackManager, _matrixPool an igObjectPool of igAttr subclasses, _attrStacks an igObjectList of igAttrStack); the casts give the typed views (no layout effect) */
int FUN_0037b4d0(Rec_37b4d0 *arg0, igCommonTraversal *arg1)
{
    igAttrStackManager *b;
    Mat mA;
    Mat mB;
    igObjectPool *p;
    Item *item;
    int cnt;
    igAttrStack *l;
    int idx;
    int r;
    int idx2;
    igAttrStack *l2;
    CB cb;
    void *ob;
    int ix;
    void **dp;
    short *pg;
    short *pi;
    igAttrStack *l0;
    int n1;

    b = (igAttrStackManager *)arg1->_attrStack;
    ix = g_igModelViewMatrixAttr_metaObject[0]->f8;
    l0 = ((igAttrStack **)((igObjectList *)b->_attrStacks)->_data)[((int *)b->_attrStackIndexTable)[ix]];
    Matrix44_Copy(&arg0->m32, &arg0->src108->w[8]);
    igMatrix44f_SetIdentity(&mA);
    if (l0->_count != 0) {
        n1 = l0->_count - 1;
        FUN_001904f0(&mA, &arg0->m32, (char *)((void **)l0->_data)[n1] + 12);
    } else {
        igMatrix44f_SetIdentity(&mB);
        FUN_001904f0(&mA, &arg0->m32, &mB);
    }
    p = (igObjectPool *)arg1->_matrixPool;
    if (p->_freeIndex >= p->_count) {
        igObjectPool_Grow(p, (void *)&FUN_001356b0);
    }
    cnt = p->_freeIndex;
    p->_freeIndex = cnt + 1;
    item = ((Item **)p->_data)[cnt];
    item->v30(&mA);
    pg = &((igAttr *)item)->_cachedAttrIndex;
    pi = &((igAttr *)item)->_cachedUnitID;
    l = (igAttrStack *)b->_attrStacks;
    idx = *pg;
    idx = *pi + ((int *)b->_attrStackIndexTable)[idx];
    l = ((igAttrStack **)l->_data)[idx];
    ((ItemStack *)l)->append(item);
    igAttrStackManager_MarkStackChanged(b, l, idx);
    r = igTraversal_TraverseChildren(arg1, arg0);
    idx2 = *pi + ((int *)b->_attrStackIndexTable)[*pg];
    l2 = ((igAttrStack **)((igObjectList *)b->_attrStacks)->_data)[idx2];
    ix = l2->_count - 1;
    dp = (void **)l2->_data;
    cb = (CB)l2->_popProc;
    ob = dp[ix];
    if (cb != 0) {
        cb(ob, b->_popProcData, cb);
    }
    l2->_count = l2->_count - 1;
    igAttrStackManager_MarkStackChanged(b, l2, idx2);
    if (r == 2) {
        return 2;
    }
    return 0;
}

void FUN_0037b760(void) {
    igTraversal_RegisterFunction(DAT_00562640[0], FUN_00367e50(), (void (*)())FUN_0037b4a0);
}

void Gap__Bec__beCri__vfunc_21(beCri *self) {
    int section;
    int ini;
    FUN_00236be0(self->_insight, self);
    ini = g_objectSystem[0]->ini;
    if (ini == 0) return;
    section = FUN_00306360(ini, DAT_0050e400, 0);
    if (section == -1) return;
    void *alloc = igObject_GetAllocator(self);
    alloc = GPR_00554c14 ? alloc : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
    igSmartPointer<igStringObj> path(FUN_002b9500(alloc));
    if (FUN_00306770(ini, section, DAT_0050e410, &path, DAT_0050e420, 0) == 0) {
        if (strcmp(DAT_0050e428, DAT_0050e438) == 0)
            FUN_0030b3c0((igStringObj *)path, DAT_0050e440);
        else
            FUN_0030b3c0((igStringObj *)path, DAT_0050e460);
    }
    char *text = (char *)path->_buffer;
    FUN_003327c0(text == 0 ? DAT_004c22f0[0] : text);
    GPR_00554de4 = 1;
    FUN_00332810(0);
    DAT_005873c8[0] = 2;
    FUN_00332c50(1);
    ErrorHooks *hooks = g_igFile_metaObject[0];
    DAT_0058a350[0] = hooks->onError;
    hooks->onError = (void (*)(void))FUN_0037b950;
}

int FUN_0037b950(void) {
    return g_igAdxFile_metaObject[0];
}

void Gap__Bec__beCri__vfunc_22(beCri *arg0) {
    ((int * *)g_igFile_metaObject)[0][15] = (int)DAT_0058a350[0];
    FUN_00236c40(arg0->_insight, arg0);
}

void Gap__Bec__beCri__vfunc_23(beCri *arg0) {
    int var_v0;
    int var_v0_2;
    struct RefCountedNamedObject *t;
    int i;
    int *a1;
    int *a0;

    arg0->_system = FUN_00236f80(arg0->_insight, g_beSystem_metaObject[0]);
    var_v0 = ((int)igObject_GetAllocator(arg0));
    if (GPR_00554c14 != 0) {
        var_v0 = (int)var_v0;
    } else {
        var_v0 = ((int)Memory_GetAllocatorBySelector(g_ndmwAllocatorSelector[0]));
    }
    t = (struct RefCountedNamedObject *)arg0->_hdBGM;
    if (t != 0) {
        t->rc = t->rc - 1;
        if ((t->rc & 0x7FFFFF) == 0) {
            igObject_Destroy(t);
        }
    }
    arg0->_hdBGM = (int)FUN_00366910(var_v0);
    beCriAudio_Setup(((struct RefCountedNamedObject *)arg0->_hdBGM)->f12, 2);
    igNamedObject_SetName(arg0->_hdBGM, 0);
    var_v0_2 = ((int)igObject_GetAllocator(arg0));
    if (GPR_00554c14 != 0) {
        var_v0_2 = (int)var_v0_2;
    } else {
        var_v0_2 = ((int)Memory_GetAllocatorBySelector(g_ndmwAllocatorSelector[0]));
    }
    t = (struct RefCountedNamedObject *)arg0->_hdENV;
    if (t != 0) {
        t->rc = t->rc - 1;
        if ((t->rc & 0x7FFFFF) == 0) {
            igObject_Destroy(t);
        }
    }
    arg0->_hdENV = (int)FUN_00366910(var_v0_2);
    beCriAudio_Setup(((struct RefCountedNamedObject *)arg0->_hdENV)->f12, 2);
    igNamedObject_SetName(arg0->_hdENV, 0);
    FUN_0037d310((int)arg0);
    arg0->_pauseOnetime = 0;
    for (i = 0; i < 32; i++) {
        DAT_0058a360[i] = 0;
        DAT_0058a360[i + 32] = 0;
        DAT_0058a460[i] = 0;
    }
}

void Gap__Bec__beCri__vfunc_24(beCri *arg0) {
    FUN_0037cc50((O *)arg0, 5);
    beCriAudio_Release(*(int *)((char *)(arg0->_hdBGM) + 12));
    beCriAudio_Release(*(int *)((char *)(arg0->_hdENV) + 12));
    FUN_0037d4a0((int *)arg0);
}

int Gap__Bec__beCri__vfunc_25(beCri *arg0, void **arg1) {
    int temp_s0;

    temp_s0 = g_beCriFxInfo_metaObject[0];
    if (temp_s0 == ((DW4VC_88_0 *)(arg1))->vX()) {
        ObjectList_AppendRetained(arg0->_infoList, arg1);
        return 1;
    }
    return 0;
}

void Gap__Bec__beCri__vfunc_26(beCri *arg0) {
    igDataList *l;
    int n;
    int i;
    igObject *o;
    igDataList *l2;
    FUN_0037dc60((int *)arg0, (char *)(&DAT_0050e480[0]));
    l = (igDataList *)arg0->_infoList;
    n = l->_count;
    for (i = 0; i < n; i++) {
        o = ((igObject **)l->_data)[i];
        if (o != 0) {
            o->_refCount = (int)o->_refCount - 1;
            if (((unsigned long long)((long long)(int)o->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    {
        int m = l->_count;
        int j;
        for (j = 0; j < m; j++) {
            ((igObject **)l->_data)[j] = 0;
        }
    }
    l->_count = 0;
    l2 = (igDataList *)arg0->_infoList;
    if (0 < l2->_count) {
    } else {
        List_Reserve(l2, 0, 4);
    }
    FUN_0037d870(arg0, 0);
}

void Gap__Bec__beCri__vfunc_27(beCri *arg0) {
    int sp9C, sp98, sp94, sp90, sp8C, sp88;
    int i;
    int j;
    int k;
    int v;
    beCriHandle *s2;
    beCriAudio *s1;
    beCriHandle *t;
    int r;
    beCriVolume *s0;
    FUN_00332cf0(1);
    if (arg0->_execDvdErr > 0) {
        if (((CriSystemState *)arg0->_system)->f88 == 0) {
            ObjectList_AppendRetained(((igObjectList *)arg0->_hdSEs), arg0->_hdBGM);
            ObjectList_AppendRetained(((igObjectList *)arg0->_hdSEs), arg0->_hdENV);
            i = 0;
            if (0 < ((igObjectList *)arg0->_hdSEs)->_count) {
                i = 0;
                do {
                    t = ((beCriHandle **)((igObjectList *)arg0->_hdSEs)->_data)[i];
                    if (t->_playID != 0) beCriAudio_Resume((beCriAudio *)t->_audio, ((igObjectList *)arg0->_hdSEs));
                    i++;
                } while (i < ((igObjectList *)arg0->_hdSEs)->_count);
            }
            ObjectList_RemoveFirstRetained(&sp9C, ((igObjectList *)arg0->_hdSEs), arg0->_hdBGM, 0);
            ObjectList_RemoveFirstRetained(&sp98, ((igObjectList *)arg0->_hdSEs), arg0->_hdENV, 0);
            arg0->_execDvdErr = 0;
        }
    } else {
        if (((CriSystemState *)arg0->_system)->f88 > 0) {
            ObjectList_AppendRetained(((igObjectList *)arg0->_hdSEs), arg0->_hdBGM);
            ObjectList_AppendRetained(((igObjectList *)arg0->_hdSEs), arg0->_hdENV);
            j = 0;
            if (0 < ((igObjectList *)arg0->_hdSEs)->_count) {
                j = 0;
                do {
                    t = ((beCriHandle **)((igObjectList *)arg0->_hdSEs)->_data)[j];
                    if (t->_playID != 0) beCriAudio_Suspend((beCriAudio *)t->_audio, ((igObjectList *)arg0->_hdSEs));
                    j++;
                } while (j < ((igObjectList *)arg0->_hdSEs)->_count);
            }
            ObjectList_RemoveFirstRetained(&sp94, ((igObjectList *)arg0->_hdSEs), arg0->_hdBGM, 0);
            ObjectList_RemoveFirstRetained(&sp90, ((igObjectList *)arg0->_hdSEs), arg0->_hdENV, 0);
            arg0->_execDvdErr = 1;
            return;
        }
        ObjectList_AppendRetained(((igObjectList *)arg0->_hdSEs), arg0->_hdBGM);
        ObjectList_AppendRetained(((igObjectList *)arg0->_hdSEs), arg0->_hdENV);
        i = 0;
        if (0 < ((igObjectList *)arg0->_hdSEs)->_count) {
            k = 0;
            do {
                s2 = ((beCriHandle **)((igObjectList *)arg0->_hdSEs)->_data)[k];
                if (s2->_playID != 0) {
                    s1 = (beCriAudio *)s2->_audio;
                    s0 = (beCriVolume *)s2->_volume;
                    r = beCriAudio_GetStatus(s1, ((igObjectList *)arg0->_hdSEs));
                    switch (r) {
                    case 1:
                        if (beCriAudio_IsPaused(s1) == 0) {
                            switch (s0->_isExec) {
                            case 3: {
                                if (s1->_audioType == 3) {
                                    v = beCriVolume_StepSndfLevel(s0, arg0->_baseVolume);
                                } else {
                                    v = beCriVolume_StepAdxLevel(s0, arg0->_baseVolume);
                                }
                                beCriAudio_SetVolume(s1, v);
                                if (s0->_end == 0.0f) {
                                    if (s1->_audioType == 3) {
                                        if (v < 13) FUN_0037caf0(arg0, s2);
                                    } else if (v < -209) {
                                        FUN_0037caf0(arg0, s2);
                                    }
                                }
                                break;
                            }
                            }
                        }
                        break;
                    case -1:
                    case 0:
                        FUN_0037caf0(arg0, s2);
                        break;
                    }
                }
                k++;
            } while (k < ((igObjectList *)arg0->_hdSEs)->_count);
        }
        ObjectList_RemoveFirstRetained(&sp8C, ((igObjectList *)arg0->_hdSEs), arg0->_hdBGM, 0);
        ObjectList_RemoveFirstRetained(&sp88, ((igObjectList *)arg0->_hdSEs), arg0->_hdENV, 0);
    }
}

int FUN_0037c130(beCri *self, unsigned char kind, short priority) {
    beCriHandle *handle; /* matching construct: declaration-order search — the handle and its audio declared before the lists */
    beCriAudio *audio;
    beCriHandleList *handles;
    beCriHandleList *list;
    beCriHandle *candidate;
    beCriAudio *candidateAudio;
    long long bestID;
    short bestPriority;
    int best;
    int i;
    handles = (beCriHandleList *)self->_hdSEs;
    for (i = 0, list = handles; i < list->_count; i++) {
        handle = ((beCriHandle **)list->_data)[i];
        audio = (beCriAudio *)handle->_audio;
        if (!(kind == 1 && audio->_adxt == 0) && !(kind == 0 && audio->_sndf == 0)) {
            if (handle->_playID == 0) return i;
        }
        /* matching construct: hand search — the list re-read from self each iteration keeps the element address unreduced */
        list = (beCriHandleList *)self->_hdSEs;
    }
    bestID = self->_request;
    bestPriority = 0x7fff;
    for (i = 0, list = handles; i < list->_count; i++) {
        candidate = ((beCriHandle **)list->_data)[i];
        candidateAudio = (beCriAudio *)candidate->_audio;
        if (!(kind == 1 && candidateAudio->_adxt == 0) && !(kind == 0 && candidateAudio->_sndf == 0)) {
            if (candidate->_priority <= priority && candidate->_playID < bestID && candidate->_priority <= bestPriority) {
                bestID = candidate->_playID;
                bestPriority = candidate->_priority;
                best = i;
            }
        }
        list = (beCriHandleList *)self->_hdSEs; /* matching construct: hand search — re-read as in the first scan */
    }
    if (best != -1) FUN_0037caf0(self, ((beCriHandle **)handles->_data)[best]);
    return best;
}

long long FUN_0037c2c0(beCri *self, igObjectList *table, beSoundData *ev) {
    beCriHandle *slot;
    int voice;
    beCriVolume *handle;
    int *name;
    long long seq;
    if (ev->_memoryIdx != -1) return 0;
    slot = 0; voice = 0; handle = 0;
    switch (ev->_type) {
    case 4:
    case 3:
        return 0;
    case 1:
        slot = (beCriHandle *)self->_hdBGM;
        voice = slot->_audio;
        handle = (beCriVolume *)slot->_volume;
        break;
    case 2:
        slot = (beCriHandle *)self->_hdENV;
        voice = slot->_audio;
        handle = (beCriVolume *)slot->_volume;
        break;
    }
    if (beCriAudio_GetStatus(voice) == 1) {
        if (handle->_isExec == 0) beCriVolume_StartFade(handle, self->_baseVolume, 1.0f, 0.0f, 10.0f);
        return 0;
    }
    handle->_max = ev->_volume;
    name = (int *)((igNamedObject **)table->_data)[ev->_fnameIdx]->_name;
    name = name != 0 ? name : &emptyString[0];
    beCriAudio_Pause(voice, 1);
    beCriAudio_SetVolume(voice, handle->_max + self->_baseVolume);
    if (beCriAudio_PlayFile(voice, name) & 0xff) {
        if (self->_pauseOnetime != 0) self->_pauseOnetime = 0; else beCriAudio_Pause(voice, 0);
        seq = self->_request + 1;
        self->_request = seq;
        slot->_playID = seq;
        slot->_type = ev->_type;
        name = (int *)ev->_name;
        name = name != 0 ? name : &emptyString[0];
        igNamedObject_SetName(slot, name);
        return seq;
    }
    return 0;
}

long long FUN_0037c4c0(beCri *self, igObjectList *lst, beSoundData *req) {
    beCriSfpData *e0;
    beCriAudio *vc0;
    unsigned char ok;
    beCriAudio *vf;
    char *src;
    beCriHandle *slot;
    beCriVolume *df;
    int found;
    long long id;
    int i;
    beCriVolume *dc0;
    beCriAudio *vc1;
    int idx;
    int off;
    char *nm;
    char *cur;
    beCriSfpData *e;
    if (SLOTS->_count <= 0) return -1;
    switch (req->_type) {
    case 1: return 0;
    case 2: return 0;
    default: break;
    }
    ok = 0;
    slot = 0;
    if (req->_memoryIdx == -1) {
        idx = FUN_0037c130(self, 1, req->_priority);
        if (idx < 0 || idx >= SLOTS->_count) return 0;
        slot = ((beCriHandle **)SLOTS->_data)[idx];
        vf = (beCriAudio *)slot->_audio;
        df = (beCriVolume *)slot->_volume;
        df->_max = req->_volume;
        src = (char *)((igNamedObject **)lst->_data)[req->_fnameIdx]->_name;
        nm = src != 0 ? src : ((char *)emptyString);
        vf->_audioType = 1;
        beCriAudio_Pause(vf, 1);
        beCriAudio_SetVolume(vf, df->_max + self->_baseVolume);
        ok = beCriAudio_PlayFile(vf, nm);
        if (ok) {
            if (self->_pauseOnetime) self->_pauseOnetime = 0; else beCriAudio_Pause(vf, 0);
        }
    } else {
        if (ENTS->_count <= 0) return 0;
        src = (char *)((igNamedObject **)lst->_data)[req->_fnameIdx]->_name;
        nm = src != 0 ? src : ((char *)emptyString);
        igSmartPointer<igStringObj> h((igStringObj *)((beSystem *)self->_system)->_globalStrObj, kRetainReference);
        FUN_0030b3c0(h.p, nm);
        FUN_0030ba20((igNamedObject *)h.p);
        FUN_0030b5c0((igNamedObject *)h.p);
        found = -1;
        i = 0;
        if (0 < ENTS->_count) {
            off = 0;
            do {
                e = *(beCriSfpData **)((char *)ENTS->_data + off);
                src = (char *)e->_name;
                nm = src != 0 ? src : ((char *)emptyString);
                cur = (char *)h.p->_buffer;
                cur = (cur == 0) ? DAT_004c22f0[0] : cur;
                if (strcmp(cur, nm) == 0) { found = i; break; }
                i += 1;
                off += 4;
            } while (i < ENTS->_count);
        }
        if (found == -1) {
            return 0;
        }
        switch (self->_dataType) {
        case 0:
            e0 = ((beCriSfpData **)ENTS->_data)[found];
            if (e0->_dataBuffer != 0) {
                idx = FUN_0037c130(self, 1, req->_priority);
                if (idx < 0 || idx >= SLOTS->_count) {
                    return 0;
                }
                slot = ((beCriHandle **)SLOTS->_data)[idx];
                vc0 = (beCriAudio *)slot->_audio;
                dc0 = (beCriVolume *)slot->_volume;
                dc0->_max = req->_volume;
                vc0->_audioType = 2;
                beCriAudio_Pause(vc0, 1);
                beCriAudio_SetVolume(vc0, dc0->_max + self->_baseVolume);
                ok = beCriAudio_PlayMemory(vc0, (void *)e0->_dataBuffer, req->_memoryIdx);
                if (self->_pauseOnetime) self->_pauseOnetime = 0;
                beCriAudio_Pause(vc0, 0);
            } else {
                return 0;
            }
            break;
        case 1:
            if (((beCriSfpData **)ENTS->_data)[found]->_isTransfer != 0) {
                idx = FUN_0037c130(self, 0, req->_priority);
                if (idx < 0 || idx >= SLOTS->_count) {
                    return 0;
                }
                slot = ((beCriHandle **)SLOTS->_data)[idx];
                vc1 = (beCriAudio *)slot->_audio;
                ((beCriVolume *)slot->_volume)->_max = req->_volume;
                ok = beCriAudio_PlaySfp(vc1, idx, req->_memoryIdx);
                if (ok) beCriAudio_SetVolume(vc1, 127);
                if (self->_pauseOnetime) self->_pauseOnetime = 0;
            } else {
                return 0;
            }
            break;
        default:
            break;
        }
    }
    if (ok) {
        id = self->_request + 1;
        self->_request = id;
        slot->_playID = id;
        slot->_type = req->_type;
        src = (char *)req->_name;
        nm = src != 0 ? src : ((char *)emptyString);
        igNamedObject_SetName(slot, nm);
        slot->_priority = req->_priority;
        return id;
    }
    return 0;
}

void FUN_0037caf0(void *arg0, beCriHandle *arg1) {
    beCriAudio *temp_s0;
    beCriVolume *temp_v1;

    temp_s0 = (beCriAudio *)arg1->_audio;
    temp_v1 = (beCriVolume *)arg1->_volume;
    arg1->_playID = 0;
    arg1->_type = 0;
    temp_v1->_isExec = 0;
    temp_v1->_max = 0;
    temp_v1->_current = 0;
    temp_v1->_sta = 0;
    temp_v1->_end = 0;
    if (temp_s0->_audioType == 3) {
        beCriAudio_SetVolume(temp_s0, 0);
    } else {
        beCriAudio_SetVolume(temp_s0, -0x3E7);
    }
    beCriAudio_Stop(temp_s0);
    igNamedObject_SetName(arg1, 0);
}

void FUN_0037cb80(beCri *arg0, long long arg1) {
    int var_s1;
    beCriHandle *temp_a1;

    temp_a1 = (beCriHandle *)arg0->_hdBGM;
    if (arg1 == temp_a1->_playID) {
        FUN_0037caf0((void *)arg0, temp_a1);
        return;
    }
    temp_a1 = (beCriHandle *)arg0->_hdENV;
    if (arg1 == temp_a1->_playID) {
        FUN_0037caf0((void *)arg0, temp_a1);
        return;
    }
    var_s1 = 0;
    if (0 < ((igObjectList *)arg0->_hdSEs)->_count) {
        do {
            temp_a1 = ((beCriHandle **)((igObjectList *)arg0->_hdSEs)->_data)[var_s1];
            if (arg1 == temp_a1->_playID) {
                FUN_0037caf0((void *)arg0, temp_a1);
            }
            var_s1 += 1;
        } while (var_s1 < ((igObjectList *)arg0->_hdSEs)->_count);
    }
}

void FUN_0037cc50(O *arg0, int arg1) {
    int i;
    int j;

    switch (arg1) {
    case 1:
        FUN_0037caf0((void *)arg0, (beCriHandle *)arg0->f32);
        break;
    case 2:
        FUN_0037caf0((void *)arg0, (beCriHandle *)arg0->f36);
        break;
    case 3:
    case 4:
        for (i = 0; i < arg0->f40->n; i++) {
            FUN_0037caf0((void *)arg0, (beCriHandle *)(arg0->f40->data[i]));
        }
        break;
    case 5:
    default:
        FUN_0037caf0((void *)arg0, (beCriHandle *)arg0->f32);
        FUN_0037caf0((void *)arg0, (beCriHandle *)arg0->f36);
        for (j = 0; j < arg0->f40->n; j++) {
            FUN_0037caf0((void *)arg0, (beCriHandle *)(arg0->f40->data[j]));
        }
        break;
    }
}

void FUN_0037cd90(beCri *arg0, int arg1) {
    int i;
    int off;
    beCriHandle *it;
    int *p;

    p = (int *)((beCriHandle *)arg0->_hdBGM)->_name;
    p = p != 0 ? p : &emptyString[0];
    if (strcmp(p, arg1) == 0) {
        beCriAudio_Pause(((beCriHandle *)arg0->_hdBGM)->_audio, 0);
    } else {
        p = (int *)((beCriHandle *)arg0->_hdENV)->_name;
        p = p != 0 ? p : &emptyString[0];
        if (strcmp(p, arg1) == 0) {
            beCriAudio_Pause(((beCriHandle *)arg0->_hdENV)->_audio, 0);
        } else {
            i = 0;
            if (0 < ((beCriHandleList *)arg0->_hdSEs)->_count) {
                off = 0;
                do {
                    it = (beCriHandle *)((int *)(((beCriHandleList *)arg0->_hdSEs)->_data + off))[0];
                    p = it->_name != 0 ? (int *)it->_name : &emptyString[0];
                    if (p != 0) {
                        p = it->_name != 0 ? (int *)it->_name : &emptyString[0];
                        if (strlen(p) != 0) {
                            p = it->_name != 0 ? (int *)it->_name : &emptyString[0];
                            if (strcmp(p, arg1) == 0) {
                                beCriAudio_Pause(it->_audio, 0);
                            }
                        }
                    }
                    i += 1;
                    off += 4;
                } while (i < ((beCriHandleList *)arg0->_hdSEs)->_count);
            }
        }
    }
}

void FUN_0037cf30(beCri *arg0, char *arg1, float f0, float f1, float f2) {
    char *s;
    int i, off;
    beCriHandle *n;
    igObjectList *l;
    s = (char *)((beCriHandle *)arg0->_hdBGM)->_name;
    if ((s ? s : DEFN) && strcmp(s ? s : DEFN, arg1) == 0) {
        beCriVolume_StartFade((beCriVolume *)(((beCriHandle *)arg0->_hdBGM)->_volume), arg0->_baseVolume, f0, f1, f2);
    } else {
        s = (char *)((beCriHandle *)arg0->_hdENV)->_name;
        if ((s ? s : DEFN) && strcmp(s ? s : DEFN, arg1) == 0) {
            beCriVolume_StartFade((beCriVolume *)(((beCriHandle *)arg0->_hdENV)->_volume), arg0->_baseVolume, f0, f1, f2);
        } else {
            l = (igObjectList *)arg0->_hdSEs;
            for (i = 0; i < l->_count; i++) {
                n = ((beCriHandle **)l->_data)[i];
                s = (char *)n->_name;
                if (s ? s : DEFN) {
                    if (strlen(s ? s : DEFN)) {
                        if (strcmp(arg1, (char *)n->_name ? (char *)n->_name : DEFN) == 0)
                            beCriVolume_StartFade((beCriVolume *)n->_volume, arg0->_baseVolume, f0, f1, f2);
                    }
                }
                l = (igObjectList *)arg0->_hdSEs;
            }
        }
    }
}

void FUN_0037d160(beCri *arg0, long long arg1, float fparg0, float fparg1, float fparg2) {
    beCriHandle *c;
    int i;
    c = (beCriHandle *)arg0->_hdBGM;
    if (arg1 == c->_playID) {
        beCriVolume_StartFade((beCriVolume *)c->_volume, arg0->_baseVolume, fparg0, fparg1, fparg2);
        return;
    }
    c = (beCriHandle *)arg0->_hdENV;
    if (arg1 == c->_playID) {
        beCriVolume_StartFade((beCriVolume *)c->_volume, arg0->_baseVolume, fparg0, fparg1, fparg2);
        return;
    }
    for (i = 0; i < ((igObjectList *)arg0->_hdSEs)->_count; i++) {
        c = ((beCriHandle **)((igObjectList *)arg0->_hdSEs)->_data)[i];
        if (arg1 == c->_playID) {
            beCriVolume_StartFade((beCriVolume *)c->_volume, arg0->_baseVolume, fparg0, fparg1, fparg2);
        }
    }
}

void FUN_0037d270(int dummy0, int arg1, int arg2) {
    FUN_00332d20(arg1);
    FUN_00333230(arg2);
}

void FUN_0037d2a0(int arg0, int arg1, int arg2) {
    if ((arg1 < 0) || (arg1 >= DAT_005875e8[0])) {
        return;
    }
    FUN_003332b0(arg1, arg2, 0);
}

void FUN_0037d2f0(int p0, int p1)
{
    FUN_00332e90(-1, 0);
}

void FUN_0037d310(int arg0) {
    int i;
    if (*(int *)((char *)LIST(arg0) + 8) > 0) FUN_0037d4a0((int *)arg0);
    i = 0;
    do {
        {
        int a = ((int)igObject_GetAllocator(arg0));
        a = GPR_00554c14 ? a : ((int)Memory_GetAllocatorBySelector(g_ndmwAllocatorSelector[0]));
        igSmartPointer<Obj> r((Obj *)((void *)FUN_00366910(a)));
        beCriAudio_Setup(r.p->w12, 1);
        igNamedObject_SetName((Obj *)r, 0);
        ObjectList_AppendRetained(LIST(arg0), (Obj *)r);
        }
        i++;
    } while (i < 4);
    i = 0;
    do {
        {
        int a = ((int)igObject_GetAllocator(arg0));
        a = GPR_00554c14 ? a : ((int)Memory_GetAllocatorBySelector(g_ndmwAllocatorSelector[0]));
        igSmartPointer<Obj> r((Obj *)((void *)FUN_00366910(a)));
        beCriAudio_Setup(r.p->w12, -1);
        igNamedObject_SetName((Obj *)r, 0);
        ObjectList_AppendRetained(LIST(arg0), (Obj *)r);
        }
        i++;
    } while (i < 48);
}

void FUN_0037d4a0(int *arg0) {
    int *l;
    Obj_37d4a0 *o;
    FUN_0037cc50((O *)arg0, 3);
    if (*(int *)(arg0[10] + 8) > 0) {
        do {
            beCriAudio_Release(*(int *)(**(int **)(arg0[10] + 16) + 12));
            l = (int *)arg0[10];
            o = (Obj_37d4a0 *)**(int **)(l + 4);
            if (o != 0) {
                --o->refs;
                if ((o->refs & 0x7fffff) == 0) {
                    igObject_Destroy(o);
                }
            }
            List_RemoveWordAt(l, 0);
            ((int *)l[4])[l[2]] = 0;
        } while (*(int *)(arg0[10] + 8) > 0);
    }
}

void FUN_0037d570(Owner *self, int on) {
    int i;
    for (i = 0; i < self->list->count; i++) {
        Entry *e = self->list->items[i];
        if (e->armed != 0 && e->type == 4) {
            Target *t = e->target;
            if (beCriAudio_GetStatus(t) == 1) {
                if (on != 0) {
                    beCriAudio_SetVolume(t, t->kind == 3 ? 127 : 0);
                } else {
                    beCriAudio_SetVolume(t, t->kind == 3 ? 0 : -999);
                }
            }
        }
    }
}

int FUN_0037d680(beCri *arg0, beCriSfpData *arg1) {
    int temp_s2;
    int *temp_s1;
    int temp_s0;
    if (arg1->_isTransfer != 0) {
        return 1;
    }
    temp_s2 = arg1->_portNo;
    temp_s0 = temp_s2 * 4;
    temp_s1 = (int *)((char *)&DAT_0058a360[0] + temp_s0);
    if (*temp_s1 == 0) {
        if (DAT_0058a3e0[temp_s2] != 0) {
            goto block_6;
        }
    } else {
block_6:
        FUN_002813c8(temp_s2);
    }
    *temp_s1 = arg1->_tblSize;
    DAT_0058a3e0[temp_s2] = arg1->_pcmSize;
    if (FUN_00280f60(&DAT_0058a360[0]) < 0) {
        return 0;
    }
    if (FUN_00281078(temp_s2, arg1->_dataBuffer) < 0) {
        return 0;
    }
    DAT_0058a460[temp_s2] = 1;
    return 1;
}

bool FUN_0037d780(beCri *o) {
    bool ok = true;
    igObjectList *l = (igObjectList *)o->_lsBinObjs;
    if (o->_dataType == 1) {
        bool first = ok;
        int i = 0;
        if (0 < l->_count) {
            do {
                beCriSfpData *e = ((beCriSfpData **)l->_data)[i];
                if (e->_isTransfer == 0) {
                    e->_portNo = i;
                    if (first) {
                        if (FUN_0037d680((beCri *)o, (beCriSfpData *)e) == 0) ok = false;
                        first = false;
                    } else {
                        DAT_0058a460[i] = 1;
                    }
                } else {
                    DAT_0058a460[i] = 2;
                }
                i++;
            } while (i < l->_count);
        }
    }
    return ok;
}

int FUN_0037d870(beCri *arg0, int arg1) {
    int idx;
    int lo;
    beCriSfpData *e;
    int off;
    int a;
    int b;
    igObjectList *l;
    int n;
    int i;
    beCriSfpData *o;
    igObjectList *l2;
    lo = -(arg1 & 0xFF);
    idx = ((igObjectList *)arg0->_lsBinObjs)->_count - 1;
    if (lo < idx) {
        off = idx * 4;
        do {
            a = g_beCriAcxData_metaObject[0];
            e = *(beCriSfpData **)((char *)((igObjectList *)arg0->_lsBinObjs)->_data + off);
            if (a != ((SndKindV *)e)->Kind()) {
                b = g_beCriSfpData_metaObject[0];
                if (b == ((SndKindV *)e)->Kind() && e->_isTransfer != 0) {
                    int ch = e->_portNo;
                    if (DAT_0058a360[ch] != 0 || DAT_0058a360[ch + 32] != 0) {
                        FUN_002813c8(ch);
                        DAT_0058a360[ch] = 0;
                        DAT_0058a360[ch + 32] = 0;
                        DAT_0058a460[ch] = 0;
                    }
                }
            }
            idx -= 1;
            off -= 4;
        } while (lo < idx);
    }
    l = ((igObjectList *)arg0->_lsBinObjs);
    n = l->_count;
    for (i = 0; i < n; i++) {
        o = (beCriSfpData *)((int *)l->_data)[i];
        if (o != 0) {
            o->_refCount = o->_refCount - 1;
            if (((unsigned long long)((long long)(int)o->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    {
        int m = l->_count;
        int j;
        for (j = 0; j < m; j++) {
            ((int *)l->_data)[j] = 0;
        }
    }
    l->_count = 0;
    l2 = ((igObjectList *)arg0->_lsBinObjs);
    if (0 < l2->_count) {
    } else {
        List_Reserve(l2, 0, 4);
    }
    return 1;
}

bool FUN_0037daf0(beCri *arg0) {
    int st;
    beCriSfpData *nx;
    bool ok;
    int i;
    int *p;
    int off;
    beCriSfpData *e;

    ok = true;
    i = 0;
    if (0 < ((igObjectList *)arg0->_lsBinObjs)->_count) {
        off = 0;
        p = &DAT_0058a460[0];
        do {
            if (*p != 0 && *p != 2) {
                *p = FUN_00281cf8(i);
                st = *p;
                switch (st) {
                case 1:
                    return false;
                case 2:
                    e = *(beCriSfpData **)((char *)((igObjectList *)arg0->_lsBinObjs)->_data + off);
                    Memory_FreeBuffer(e->_dataBuffer);
                    e->_dataBuffer = 0;
                    e->_isTransfer = 1;
                    if (i < ((igObjectList *)arg0->_lsBinObjs)->_count - 1) {
                        nx = *(beCriSfpData **)((char *)((igObjectList *)arg0->_lsBinObjs)->_data + off + 4);
                        if (nx->_isTransfer == 0) {
                            FUN_0037d680(arg0, nx);
                        }
                    }
                    break;
                case 3:
                    ok = false;
                    break;
                default:
                    ok = false;
                    break;
                }
            }
            i += 1;
            p += 1;
            off += 4;
        } while (i < ((igObjectList *)arg0->_lsBinObjs)->_count);
    }
    return ok;
}

void FUN_0037dc60(int *arg0, char *arg1) {
    L_37dc60 *t = (L_37dc60 *)arg0[11];
    N *s0;
    if (t->cnt > 0) {
        s0 = t->arr[0];
        if (arg1 == 0) {
            arg1 = ((char *)DAT_0050e480);
        }
        if (strcmp(arg1, s0->name != 0 ? s0->name : ((char *)emptyString)) == 0) {
            FUN_002829f0(0xA4000000, s0->val);
            return;
        }
        FUN_002829f0(0xA4000000, 0x7F);
        return;
    }
    FUN_002829f0(0xA4000000, 0x7F);
}

unsigned char FUN_0037dd10(beCri *arg0, int *arg1) {
    unsigned char res1;
    int i1;
    unsigned char res2;
    int i2;
    beCriHandle *it;
    int *p;
    beCriHandle *it1;
    int h7c;
    int h78;

    if (strcmp(arg1, &DAT_0050e488[0]) == 0) {
        res1 = 1;
        ObjectList_AppendRetained(arg0->_hdSEs, arg0->_hdBGM);
        ObjectList_AppendRetained(arg0->_hdSEs, arg0->_hdENV);
        i1 = 0;
        if (0 < ((beCriHandleList *)arg0->_hdSEs)->_count) {
            do {
                it1 = ((beCriHandle **)((beCriHandleList *)arg0->_hdSEs)->_data)[i1];
                if (it1->_playID != 0 && ((beCriAudio *)it1->_audio)->_audioType == 1 && igAdxAudio_GetStatus(((beCriAudio *)it1->_audio)->_adxt) != 3) {
                    res1 = 0;
                    break;
                }
                i1 += 1;
            } while (i1 < ((beCriHandleList *)arg0->_hdSEs)->_count);
        }
        ObjectList_RemoveFirstRetained(&h7c, arg0->_hdSEs, arg0->_hdBGM, 0);
        ObjectList_RemoveFirstRetained(&h78, arg0->_hdSEs, arg0->_hdENV, 0);
        return res1;
    }
    res2 = 1;
    p = (int *)((beCriHandle *)arg0->_hdBGM)->_name;
    if ((p != 0 ? p : &emptyString[0]) != 0 && strcmp(p != 0 ? p : &emptyString[0], arg1) == 0) {
        if (igAdxAudio_GetStatus(((beCriAudio *)((beCriHandle *)arg0->_hdBGM)->_audio)->_adxt) != 3) res2 = 0;
    } else {
        p = (int *)((beCriHandle *)arg0->_hdENV)->_name;
        if ((p != 0 ? p : &emptyString[0]) != 0 && strcmp(p != 0 ? p : &emptyString[0], arg1) == 0) {
            if (igAdxAudio_GetStatus(((beCriAudio *)((beCriHandle *)arg0->_hdENV)->_audio)->_adxt) != 3) res2 = 0;
        } else {
            i2 = 0;
            if (0 < ((beCriHandleList *)arg0->_hdSEs)->_count) {
                do {
                    it = ((beCriHandle **)((beCriHandleList *)arg0->_hdSEs)->_data)[i2];
                    p = (int *)it->_name;
                    if ((p != 0 ? p : &emptyString[0]) != 0) {
                        if (strlen(p != 0 ? p : &emptyString[0]) != 0) {
                            if (strcmp(arg1, (int *)it->_name != 0 ? (int *)it->_name : &emptyString[0]) == 0 && it->_playID != 0 && igAdxAudio_GetStatus(((beCriAudio *)it->_audio)->_adxt) != 3) {
                                res2 = 0;
                                break;
                            }
                        }
                    }
                    i2 += 1;
                } while (i2 < ((beCriHandleList *)arg0->_hdSEs)->_count);
            }
        }
    }
    return res2;
}

void FUN_0037e020(beCri *arg0, int arg1) {
    if (arg0->_sndfVolume == 0) {
        if (arg1 <= 0 || arg1 > 127) arg1 = 127;
        arg0->_sndfVolume = arg1;
        FUN_002825e0(0, 0xA0010000, arg1);
    }
}

static inline int cast0(int o) { if (o != 0 && igObject_IsKindOf(o, g_igMemoryRefMetaField_metaObject[0]) != 0) { return o; } return 0; }

void FUN_0037e070(void) {
    int var_s0;

    FUN_00308860(g_globalContext[0], &DAT_0050e490[0], 0x20);
    var_s0 = igMetaObject_FindFieldByName(g_beCriSfpData_metaObject[0], &DAT_0050e4a0[0]);
    var_s0 = cast0(var_s0);
    igMemoryRefMetaField_SetAlignmentType(var_s0, &DAT_0050e490[0]);
}

int Gap__Bec__beCri__vfunc_20(void)
{
    return g_beCri_metaObject[0];
}

