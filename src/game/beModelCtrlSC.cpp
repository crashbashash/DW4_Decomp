#include "dw4/reflected.h"
#include "dw4/igTDataList.h"
#include "dw4/igSmartPointer.h"

extern "C" long long __fixsfdi(float);
extern "C" int igMatrix44f_SetIdentity(...);
extern "C" int FUN_001904f0(...);
extern "C" int igObjectPool_Grow(...);
extern "C" int igAttrStackManager_MarkStackChanged(...);
extern "C" int FUN_001b12f0(...);
extern "C" int FUN_001b13d0(...);
extern "C" int igTraversal_TraverseChildren(...);
extern "C" int FUN_001356b0(...);
extern "C" int igTimeAttr_CreateInstance(...);
extern "C" int igTraversal_RegisterFunction(int, int, void (*)(void));
extern "C" int FUN_0034fd90(...);
extern "C" void FUN_003993a0(void);
extern "C" int FUN_003908d0(...);
extern "C" int FUN_00394400(...);
extern "C" int Memory_GetAllocatorBySelector(...);
extern "C" int beMessenger_AppendInt(...);
extern "C" int beMessenger_AppendMatrix(...);
extern "C" int beMessenger_AppendObject(...);
extern "C" int beMessenger_AppendString(...);
extern "C" int beMessenger_DispatchSelected(...);
extern "C" int beMessenger_GetBoolCount(...);
extern "C" int beMessenger_SelectGroup(...);
extern "C" int beMessenger_SetRunCheck(...);
extern "C" int igObject_GetAllocator(...);
extern "C" int thunk_FUN_0018ac80(...);
extern "C" int beMessenger_AppendBool(int, unsigned char);
extern "C" int beMessenger_GetObjectCount(int);
extern "C" int beMessenger_SelectReceivers(int, int *, int, int);
extern "C" int beMessenger_SendNamed(int, int *, int, int, int *);
extern "C" int beMessenger_GetInt(int, int);
extern "C" long long beMessenger_GetLong(int, int);
extern "C" int beMessenger_AppendLong(int, long long);
extern "C" int List_RemoveWordAt(...);
extern "C" int FUN_002eb010(...);
extern "C" int ObjectList_AppendRetained(...);
extern "C" int StringChunk_ReleaseHeader(...);
extern "C" int StringPool_Construct(...);
extern "C" void * StringPool_Intern(...);
extern "C" void *FUN_0034f6f0(int);
extern "C" int Gap__Bec__beModelCtrlSCSound__vfunc_20(void);
extern "C" int Gap__Bec__beModelCtrlSCEffect__vfunc_20(void);
extern "C" int Gap__Bec__beModelCtrlSCHitBox__vfunc_20(void);
extern "C" int FUN_00398e50(igCommonTraversal *traversal, beModelCtrlNode2 *node);
extern "C" long long FUN_00398e80(beModelCtrlNode2 *arg0, long long arg1);
extern "C" igMetaObject *g_igModelViewMatrixAttr_metaObject[4];
class Ctl;
template <class T> struct AttrSlots : igTDataList<T> {
};
struct Ls { char p0[8]; int cnt; int cap; int *data; int cur; };
struct Pool { char p0[8]; int cap; char p1[4]; int *data; int cur; };
struct Tb { char p0[16]; Ls **data; };
struct Q { char p0[8]; int n; char p1[4]; int *a; char p2[8]; int (*cb)(int, int); };
struct Mgr { char p0[16]; Tb *tb; char p1[28]; int f48; char p2[16]; int *base; };
struct Mat;
class Ent { public:
 virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
 virtual void v30(char *m);
 int refc; short idx; short off; char p1[4]; long long clk; };
class Ctl { public:
 virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
 virtual long long v24();
 virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
 virtual void v30(long long t); virtual void v31();
 char p0[48]; Mgr *mgr; char p1[16]; Pool *pa; Pool *pb; };
extern "C" int FUN_00398ef0(beModelCtrlNode2 *self, Ctl *ctl);
extern "C" int DAT_00562640[4];
struct BoxF : public igObject { float mn[3]; float mx[3]; };
extern "C" igObject *beBaseInfoDataList_Create(int);
extern "C" BoxF *FUN_0018a660(int);
struct PropertyRecord { char p[16]; int f16; beModelCtrlInfoWork *q; };
extern "C" PropertyRecord * igProperty_FindByName(...);
extern "C" int emptyString[4];
extern "C" int DAT_0050f410[4];
extern "C" int DAT_0050f420[4];
extern "C" int DAT_0050f430[4];
extern "C" int DAT_0050f440[4];
extern "C" int DAT_0050f450[4];
extern "C" int DAT_0050f460[4];
extern "C" int g_propertyNameField[4];
extern "C" int g_defaultAllocatorSelector[4];
extern "C" float DAT_0058a540[4];
extern "C" unsigned char GPR_00554c14;
extern "C" char GPR_00554e54;
struct V4 { float x, y, z, w; };
struct ReleaseRefInline { static inline void go(igObject *object) {
    if (object) {
        --object->_refCount;
        if (((unsigned long long)(long long)object->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy(object);
    }
} };
/* Owning reference to the freshly created data list. */

/* Owning reference to the working box. */
struct Ref { BoxF *p; Ref(BoxF *o) : p(o) {} ~Ref() { igObject *object = (igObject *)p; if (object) { --object->_refCount; if (((unsigned long long)(long long)object->_refCount & 0x7fffffULL) == 0) igObject_Destroy(object); } } };
/* matching construct: expression temporary -- the freshly created data list is held by a temporary passed to an
   inline helper, so its frame slot (168) sorts below the box reference (172); a named local took 172 instead. */
struct DataListInit { static inline void go(beBaseInfoRam *arg1, const igSmartPointer<igObject> &tmp) {
        igObject *s0 = tmp.p;
        if (s0 != 0) {
            s0->_refCount++;
        }
        ReleaseRefInline::go((igObject *)arg1->_dataList);
        arg1->_dataList = (int)s0;
}
static inline void make(beBaseInfoRam *arg1, int a) { igSmartPointer<igObject> list(beBaseInfoDataList_Create(a)); go(arg1, list); }
};
extern "C" int Gap__Bec__beModelCtrlSCHitBox__vfunc_21(beModelCtrlSCHitBox *arg0, beBaseInfoRam *arg1);
class DW4VC_92_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual int vX(); };
extern "C" int Gap__Bec__beModelCtrlSCHitBox__vfunc_22(beModelCtrlSCHitBox *arg0);
/* BeModelCtrlSCEffect vfunc 21: asks the gene model for its ram number, then dispatches the effect
 * request (owner name, sequence, lock target, offset, rotation, position lock) to the selected
 * receivers. The ram object's data list is created on first use. */


struct PropertyEntry { char pad[20]; struct PropertyValueObj *f20; };
struct PropertyValueObj { char pad[220]; int *f220; int f224; };
struct Vec3f { float x, y, z; };
extern "C" int beMessenger_AppendVec3(int, Vec3f *);
extern "C" beBaseInfoRam *beMessenger_GetObject(int, int);
extern "C" int DAT_0050f468[4];
extern "C" int DAT_0050f478[4];
extern "C" int DAT_0050f488[4];
extern "C" int Gap__Bec__beModelCtrlSCEffect__vfunc_21(beModelCtrlSCEffect *arg0, beBaseInfoRam *arg1);
extern "C" int DAT_0050f498[4];
extern "C" void Gap__Bec__beModelCtrlSCEffect__vfunc_23(beModelCtrlSCEffect *arg0, void *arg1);
/* Asks the messenger of arg1->f16 for a long long value (group select, append string, dispatch,
 * get long); stores it into arg0->f24 when it is neither -1 nor 0 and the int result is 4. */

/* Only the messenger word at +20 of the owner object is read. */
typedef struct MessengerOwnerView { char pad[20]; int f20; } MessengerOwnerView;
/* Only the owner pointer at +16 of the context object is read. */
typedef struct OwnerContextView { char pad[16]; MessengerOwnerView *f16; } OwnerContextView;
extern "C" int DAT_0050f4a0[4];
extern "C" int DAT_0050f4a8[4];
extern "C" int Gap__Bec__beModelCtrlSCSound__vfunc_21(beModelCtrlSCSound *arg0, OwnerContextView *arg1);
extern "C" int DAT_0050f4b0[4];
extern "C" int DAT_0050f4b8[4];
/* Only the messenger word at +20 of the owner object is read. */
struct MessengerOwnerView_399d10 { char pad[20]; int msg; };
/* Only the owner pointer at +16 of the context object is read. */
struct OwnerContextView_399d10 { char pad[16]; struct MessengerOwnerView_399d10 *m; };
extern "C" void Gap__Bec__beModelCtrlSCSound__vfunc_23(beModelCtrlSCSound *arg0, struct OwnerContextView_399d10 *arg1);
class V92;
class V92 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual unsigned char vX(void *, int); };
class V96;
class V96 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual unsigned char vX(void *, int); };
extern "C" unsigned char FUN_00399d90(beModelCtrlSubComBase *arg0, beBaseInfoRam *arg1);
extern "C" void FUN_00399e20(beModelCtrlSubCom *arg0, int arg1);
extern "C" int g_beModelCtrlSCEffect_metaObject[4];
class DW4VC_88 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); };
class DW4VC_100 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int vX(int); };
struct E { char pad[56]; unsigned char f56; };
extern "C" void FUN_00399f20(beModelCtrlSubCom *arg0, int arg1);
class VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int v88(); virtual void e0(); virtual void e1(); virtual void v100(int); };
extern "C" void FUN_0039a130(beModelCtrlSubCom *arg0, int arg1, int arg2);
/* Appends an effect sub-command: builds a beModelCtrlSCEffect (pooled allocator unless the global
 * selector flag is clear), interns the model and sequence names into it (releasing whatever the
 * fresh record held), copies the offset and rotation vectors, the two flags and the start frame,
 * then appends the record to the sub-command list, which retains it. The creating reference is
 * released on scope exit. */

struct V { float x, y, z; };
extern "C" beModelCtrlSCEffect *FUN_0034f8e0(int);
extern "C" int g_stringPool[4];
extern "C" void FUN_0039a250(beModelCtrlSubCom *self, int str1, int str2, struct V *va, struct V *vb, char c1, char c2, float f);
/* Build one timed record from the request `arg1` (start time, optional duration, two vectors and a
 * kind code classified by its ten-thousands digit) and append it, retained, to the list at
 * arg0->f8. The record is owned by a stack reference until the list has taken its own reference. */

typedef struct R : public igObject { int f8; int f12; float f16; int f20; int f24; float f28; float f32; float f36; float f40; float f44; float f48; float f52; } R;
typedef struct A { char pad[8]; int f8; } A;
typedef struct S { char pad[12]; int f12; float f16; float f20; float f24; float f28; float f32; float f36; float f40; float f44; } S;
extern "C" void FUN_0039a500(A *arg0, S *arg1);
extern "C" beModelCtrlSCSound *FUN_0034f4a0(...);
extern "C" void FUN_0039a750(beModelCtrlSubCom *arg0, int arg1, float fparg0);
extern "C" int g_beModelCtrlSCSound_metaObject[4];
extern "C" int g_beModelCtrlSCEffect_metaObject[4];
extern "C" int g_beModelCtrlSCHitBox_metaObject[4];

int FUN_00398e50(igCommonTraversal *traversal, beModelCtrlNode2 *node)
{
    return FUN_00398ef0(node, (Ctl *)traversal);
}

long long FUN_00398e80(beModelCtrlNode2 *arg0, long long arg1) {
    unsigned int u = (unsigned int)(arg1 >> 0x12);
    float f = (float)u;
    long long r;
    f = f * arg0->_timeScale;
    r = __fixsfdi(f) << 0x12;
    return r + arg0->_timeBias;
}

static inline igAttrList *overrides(const beModelCtrlNode2 *n) { return (igAttrList *)n->_overrideAttrList; }

int FUN_00398ef0(beModelCtrlNode2 *self, Ctl *ctl) {
    long long t;
    short *ai;
    short *ao;
    Mgr *mgr;
    Ls *tgt;
    Ent *ea;
    Ent *eb;
    int idx;
    int s6;
    int s7;
    int i;
    int j;
    int l;
    int jo;
    int lo;
    short *bi;
    short *bo;
    int r;
    Q *q;
    Q *top;
    int k;
    int *ta;
    int x;
    int (*cb)(int, int);
    char mat[64];
    char tmp[64];

    mgr = ctl->mgr;
    idx = g_igModelViewMatrixAttr_metaObject[0]->_id;
    top = (Q *)mgr->tb->data[mgr->base[idx]];
    t = FUN_00398e80(self, ctl->v24());
    self->_time = t;
    igMatrix44f_SetIdentity(mat);
    if (top->n != 0) {
        k = top->n - 1;
        ta = top->a;
        FUN_001904f0(mat, (char *)self->_m, ta[k] + 12);
    } else {
        igMatrix44f_SetIdentity(tmp);
        FUN_001904f0(mat, (char *)self->_m, tmp);
    }
    {
        Pool *p = ctl->pa;
        if (p->cur >= p->cap) igObjectPool_Grow(p, FUN_001356b0);
        i = p->cur;
        p->cur = i + 1;
        ea = (Ent *)p->data[i];
    }
    ea->v30(mat);
    {
        Pool *p = ctl->pb;
        if (p->cur >= p->cap) igObjectPool_Grow(p, igTimeAttr_CreateInstance);
        i = p->cur;
        p->cur = i + 1;
        eb = (Ent *)p->data[i];
    }
    eb->clk = t;
    ctl->v30(t);

    ao = &ea->off;
    ai = &ea->idx;
    s6 = ea->off + mgr->base[ea->idx];
    tgt = mgr->tb->data[s6];
    ((AttrSlots<Ent *> *)tgt)->append(ea);
    igAttrStackManager_MarkStackChanged(mgr, tgt, s6);

    bi = &eb->idx;
    bo = &eb->off;
    s7 = eb->off + mgr->base[eb->idx];
    tgt = mgr->tb->data[s7];
    ((AttrSlots<Ent *> *)tgt)->append(eb);
    igAttrStackManager_MarkStackChanged(mgr, tgt, s7);

    j = 0;
    if (j < overrides(self)->_count) {
        jo = 0;
        do {
            FUN_001b12f0(mgr, *(int *)(((igAttrList *)self->_overrideAttrList)->_data + jo));
            j++;
            jo += 4;
        } while (j < ((igAttrList *)self->_overrideAttrList)->_count);
    }
    r = igTraversal_TraverseChildren(ctl, self);
    for (l = ((igAttrList *)self->_overrideAttrList)->_count - 1, lo = l * 4; l >= 0; l--) {
        FUN_001b13d0(mgr, *(int *)(((igAttrList *)self->_overrideAttrList)->_data + lo));
        lo -= 4;
    }
    {
        int pb = *bo + mgr->base[*bi];
        Q *qb = (Q *)mgr->tb->data[pb];
        int kb = qb->n - 1;
        int *tab = qb->a;
        int xb = tab[kb];
        int (*cbb)(int, int) = qb->cb;
        if (cbb != 0) cbb(xb, mgr->f48);
        qb->n = qb->n - 1;
        igAttrStackManager_MarkStackChanged(mgr, qb, pb);
    }
    {
        int pa = *ao + mgr->base[*ai];
        Q *qa = (Q *)mgr->tb->data[pa];
        int ka = qa->n - 1;
        int *taa = qa->a;
        int xa = taa[ka];
        int (*cba)(int, int) = qa->cb;
        if (cba != 0) cba(xa, mgr->f48);
        qa->n = qa->n - 1;
        igAttrStackManager_MarkStackChanged(mgr, qa, pa);
    }
    ctl->v31();
    if (r == 2) return 2;
    return 0;
}

void FUN_003993a0(void) {
    igTraversal_RegisterFunction(DAT_00562640[0], FUN_0034fd90(), (void (*)())FUN_00398e50);
}

int Gap__Bec__beModelCtrlSCHitBox__vfunc_21(beModelCtrlSCHitBox *arg0, beBaseInfoRam *arg1) {
    float c[3];
    int i;
    V4 sp80;
    igObject *s0;
    PropertyRecord *s2;
    beModelCtrlInfoWork *s1;
    beModelCtrl *m;
    beBaseInfo *info = (beBaseInfo *)arg1->_parentInfo;
    BoxF *t;
    if (arg1->_dataList == 0) {
        int alloc = igObject_GetAllocator(arg1);
        int a;
        if (GPR_00554c14 != 0) {
            a = alloc;
        } else {
            a = Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
        }
        DataListInit::make(arg1, a);
    }
    s2 = igProperty_FindByName(arg1->_dataList, g_propertyNameField[0], DAT_0050f410);
    s1 = s2->q;
    m = (beModelCtrl *)arg1->_parentManager;
    int alloc = igObject_GetAllocator(arg0);
    int a;
    if (GPR_00554c14 != 0) {
        a = alloc;
    } else {
        a = Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
    }
    Ref spAC(FUN_0018a660(a));
    goto L2;
L1:
    thunk_FUN_0018ac80(spAC.p, s2->f16 + 32);
    { t = spAC.p;
    c[0] = t->mn[0] * 0.5f + t->mx[0] * 0.5f;
    c[1] = t->mn[1] * 0.5f + t->mx[1] * 0.5f;
    c[2] = t->mn[2] * 0.5f + t->mx[2] * 0.5f; }
    goto L3;
L1b:
    if (m->_isDebugHitBox != 0 && s1 != 0) {
        int a1 = s1->_debugHitBoxNode;
        if (a1 != 0) {
            if (GPR_00554e54 == 0) {
                DAT_0058a540[0] = 0;
                DAT_0058a540[1] = 0;
                DAT_0058a540[2] = 1.0f;
                DAT_0058a540[3] = 0.5f;
                DAT_0058a540[4] = 1.0f;
                DAT_0058a540[5] = 1.0f;
                DAT_0058a540[8] = 1.0f;
                DAT_0058a540[6] = 0;
                DAT_0058a540[7] = 0.5f;
                DAT_0058a540[11] = 0.5f;
                DAT_0058a540[9] = 0;
                DAT_0058a540[10] = 0;
                GPR_00554e54 = 1;
            }
            {
                float *p = &DAT_0058a540[arg0->_bulletMode * 4];
                sp80.x = p[0]; sp80.y = p[1]; sp80.z = p[2]; sp80.w = p[3];
            }
            FUN_003908d0(m, a1, spAC.p, &sp80);
        }
    }
    switch (arg0->_bulletMode) {
    case 0:
        beMessenger_SelectGroup(m->_messenger, DAT_0050f420);
        break;
    case 1:
        beMessenger_SelectGroup(m->_messenger, DAT_0050f430);
        break;
    default:
        beMessenger_SelectGroup(m->_messenger, DAT_0050f440);
        break;
    }
    beMessenger_AppendInt(m->_messenger, arg0->_kind);
    beMessenger_AppendObject(m->_messenger, spAC.p);
    beMessenger_AppendMatrix(m->_messenger, s2->f16 + 32);
    {
        int a1 = s1->_hitParentName;
        if (a1 == 0) {
            int n = info->_name != 0 ? info->_name : (int)emptyString;
            beMessenger_AppendString(m->_messenger, n);
            beMessenger_AppendInt(m->_messenger, arg1->_ramNo);
        } else {
            beMessenger_AppendString(m->_messenger, a1);
            beMessenger_AppendInt(m->_messenger, s1->_hitParentRamNo);
        }
    }
    beMessenger_SetRunCheck(m->_messenger, 1);
    beMessenger_DispatchSelected(m->_messenger, DAT_0050f450);
    if (beMessenger_GetBoolCount(m->_messenger) != 0) {
        int a2 = s2->q->_luaBHit;
        if (a2 != 0) {
            int n = info->_name != 0 ? info->_name : (int)emptyString;
            FUN_00394400(m, arg1, a2, DAT_0050f460, n, 0, 0, 0, 0, 0);
        }
    }
    return 1;
L3:
    for (i = 0; i < 3; i++) {
        float size = arg0->_boxSize[i];
        t = spAC.p;
        t->mn[i] = c[i] - size / 2.0f;
        t = spAC.p;
        t->mx[i] = size / 2.0f + c[i];
    }
    goto L1b;
L2:
    { BoxF *t = spAC.p; t->mn[0] = t->mx[0] = arg0->_offset[0]; }
    { float v = arg0->_offset[1]; BoxF *t = spAC.p; t->mx[1] = v; t->mn[1] = v; }
    { BoxF *t = spAC.p; t->mn[2] = t->mx[2] = arg0->_offset[2]; }
    goto L1;
}

int Gap__Bec__beModelCtrlSCHitBox__vfunc_22(beModelCtrlSCHitBox *arg0) {
    if (!(arg0->_runFrame < arg0->_endFrame)) {
        return 0;
    }
    ((DW4VC_92_0 *)(((char *)(arg0) + 0)))->vX();
    return 1;
}

/* Owning stack reference to the freshly created data list; released on scope exit (reference count
 * in the low 23 bits of _refCount). */

int Gap__Bec__beModelCtrlSCEffect__vfunc_21(beModelCtrlSCEffect *arg0, beBaseInfoRam *arg1) {
    beBaseInfo *s2;
    beBaseInfoManager *s1;
    int *v;
    int *str;
    PropertyValueObj *s0;
    Vec3f sp70;
    Vec3f sp60;
    s1 = (beBaseInfoManager *)arg1->_parentManager;
    s2 = (beBaseInfo *)arg1->_parentInfo;
    beMessenger_SendNamed(s1->_messenger, &DAT_0050f468[0], arg0->_modelName, -1, &DAT_0050f478[0]);
    if (beMessenger_GetObjectCount(s1->_messenger) != 0) {
    arg0->_geneRamNo = beMessenger_GetObject(s1->_messenger, 0)->_ramNo;
    beMessenger_SelectReceivers(s1->_messenger, &DAT_0050f468[0], arg0->_modelName, arg0->_geneRamNo);
    beMessenger_AppendInt(s1->_messenger, arg1->_ramNo);
    v = (int *)s2->_name;
    if (v != 0) str = v; else str = &emptyString[0];
    beMessenger_AppendString(s1->_messenger, str);
    beMessenger_AppendString(s1->_messenger, arg0->_seqName);
    if (arg1->_dataList == 0) {
        int a = igObject_GetAllocator(arg1);
        igSmartPointer<igObject> created(beBaseInfoDataList_Create(GPR_00554c14 != 0 ? a : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0])));
        igObject *t = created.p;
        if (t != 0) t->_refCount = t->_refCount + 1;
        igObject *old = (igObject *)arg1->_dataList;
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if ((old->_refCount & 0x7fffff) == 0) igObject_Destroy(old);
        }
        arg1->_dataList = (int)t;
    }
    s0 = ((PropertyEntry *)igProperty_FindByName(arg1->_dataList, g_propertyNameField[0], &DAT_0050f410[0]))->f20;
    if (s0->f220 == 0) {
        v = (int *)s2->_name;
        if (v != 0) str = v; else str = &emptyString[0];
        beMessenger_AppendString(s1->_messenger, str);
        beMessenger_AppendInt(s1->_messenger, arg1->_ramNo);
    } else {
        beMessenger_AppendString(s1->_messenger, s0->f220);
        beMessenger_AppendInt(s1->_messenger, s0->f224);
    }
    sp70.x = ((float *)arg0->_offset)[0];
    sp70.y = ((float *)arg0->_offset)[1];
    sp70.z = ((float *)arg0->_offset)[2];
    beMessenger_AppendVec3(s1->_messenger, &sp70);
    sp60.x = ((float *)arg0->_rotation)[0];
    sp60.y = ((float *)arg0->_rotation)[1];
    sp60.z = ((float *)arg0->_rotation)[2];
    beMessenger_AppendVec3(s1->_messenger, &sp60);
    beMessenger_AppendBool(s1->_messenger, arg0->_isPositionLock);
    beMessenger_DispatchSelected(s1->_messenger, &DAT_0050f488[0]);
    } else {
        return 0;
    }
    return arg0->_isSeqDead != 0;
}

void Gap__Bec__beModelCtrlSCEffect__vfunc_23(beModelCtrlSCEffect *arg0, void *arg1) {
    int temp_a3;

    if (arg0->_isOneSet != 0) {
        temp_a3 = arg0->_geneRamNo;
        if (temp_a3 != -1) {
            beMessenger_SendNamed(*(int *)((char *)(*(int *)((char *)(arg1) + 16)) + 20), &DAT_0050f468[0], arg0->_modelName, temp_a3, &DAT_0050f498[0]);
        }
    }
}

int Gap__Bec__beModelCtrlSCSound__vfunc_21(beModelCtrlSCSound *arg0, OwnerContextView *arg1) {
    MessengerOwnerView *s1 = arg1->f16;
    long long s0;
    beMessenger_SelectGroup(s1->f20, &DAT_0050f4a0[0]);
    beMessenger_AppendString(s1->f20, arg0->_sndName);
    beMessenger_DispatchSelected(s1->f20, &DAT_0050f4a8[0]);
    s0 = beMessenger_GetLong(s1->f20, 0);
    if (s0 == -1) {
        return 0;
    }
    if (s0 == 0) {
        return 0;
    }
    if (beMessenger_GetInt(s1->f20, 0) != 4) {
        return 0;
    }
    arg0->_sndHandle = s0;
    return 1;
}

void Gap__Bec__beModelCtrlSCSound__vfunc_23(beModelCtrlSCSound *arg0, struct OwnerContextView_399d10 *arg1) {
    struct MessengerOwnerView_399d10 *m = arg1->m;
    if (arg0->_sndHandle != 0) {
        beMessenger_SelectGroup(m->msg, &DAT_0050f4a0[0]);
        beMessenger_AppendString(m->msg, &DAT_0050f4b0[0]);
        beMessenger_AppendLong(m->msg, arg0->_sndHandle);
        beMessenger_DispatchSelected(m->msg, &DAT_0050f4b8[0]);
    }
}

unsigned char FUN_00399d90(beModelCtrlSubComBase *arg0, beBaseInfoRam *arg1) {
    float temp_f1;
    unsigned char var_v0;

    temp_f1 = arg0->_runFrame + ((beSystem *)((beBaseInfoManager *)arg1->_parentManager)->_system)->_frameTimeF;
    arg0->_runFrame = temp_f1;
    var_v0 = 1;
    if (arg0->_isOneSet == 0) {
        if (!(temp_f1 < arg0->_startFrame)) {
            arg0->_isOneSet = 1;
            var_v0 = ((V92 *)arg0)->vX(arg1, 1);
        }
    } else {
        var_v0 = ((V96 *)arg0)->vX(arg1, 1);
    }
    return var_v0;
}

void FUN_00399e20(beModelCtrlSubCom *arg0, int arg1) {
    int var_s3;
    int var_s2;
    igObject *temp_a0;
    igObjectList *temp_s1;

    var_s3 = ((igObjectList *)arg0->_comList)->_count;
    var_s2 = 0;
    if (var_s3 > 0) {
        do {
            if (!(((int)FUN_00399d90((beModelCtrlSubComBase *)(((int *)((igObjectList *)arg0->_comList)->_data)[var_s2]), (beBaseInfoRam *)arg1)) & 0xFF)) {
                temp_s1 = (igObjectList *)(arg0->_comList);
                temp_a0 = (igObject *)(((int *)temp_s1->_data)[var_s2]);
                if (temp_a0 != 0) {
                    temp_a0->_refCount = temp_a0->_refCount - 1;
                    if ((temp_a0->_refCount & 0x7FFFFF) == 0) {
                        igObject_Destroy(temp_a0);
                    }
                }
                List_RemoveWordAt(temp_s1, var_s2);
                var_s2 -= 1;
                var_s3 -= 1;
                ((int *)temp_s1->_data)[temp_s1->_count] = 0;
            }
            var_s2 += 1;
        } while (var_s2 < var_s3);
    }
}

void FUN_00399f20(beModelCtrlSubCom *arg0, int arg1) {
    igObjectList *l;
    int i;
    int n2;
    int n3;
    DW4VC_88 *o;
    int j;
    int q;
    int n;
    int s1;
    igObject *p;

    n = ((igObjectList *)arg0->_comList)->_count;
    i = 0;
    if (0 < n) {
        do {
            s1 = g_beModelCtrlSCEffect_metaObject[0];
            o = ((DW4VC_88 **)((igObjectList *)arg0->_comList)->_data)[i];
            if (s1 != o->vX() || ((E *)o)->f56 != 0) {
                ((DW4VC_100 *)o)->vX(arg1);
            }
            i += 1;
        } while (i < n);
    }
    l = (igObjectList *)arg0->_comList;
    n2 = l->_count;
    j = 0;
    if (0 < n2) {
        do {
            p = ((igObject **)l->_data)[j];
            if (p != 0) {
                p->_refCount = p->_refCount - 1;
                if ((p->_refCount & 0x7FFFFF) == 0) {
                    igObject_Destroy(p);
                }
            }
            j += 1;
        } while (j < n2);
    }
    n3 = l->_count;
    for (q = 0; q < n3; q++) {
        ((int *)l->_data)[q] = 0;
    }
    l->_count = 0;
}

void FUN_0039a130(beModelCtrlSubCom *arg0, int arg1, int arg2) {
    int n; int i; VC *o; igObjectList *l; igObject *t;
    n = ((igObjectList *)arg0->_comList)->_count;
    i = 0;
    if (n > 0) {
        do {
            o = ((VC **)((igObjectList *)arg0->_comList)->_data)[i];
            if (arg2 == o->v88()) {
                o->v100(arg1);
                l = (igObjectList *)arg0->_comList;
                t = ((igObject **)l->_data)[i];
                if (t != 0) {
                    --t->_refCount;
                    if (((unsigned long long)(long long)t->_refCount & 0x7fffffULL) == 0) {
                        igObject_Destroy(t);
                    }
                }
                List_RemoveWordAt(l, i);
                i--;
                n--;
                ((int *)l->_data)[l->_count] = 0;
            }
            i++;
        } while (i < n);
    }
}

/* Owning stack reference to the new effect record, released on scope exit (reference count in the
 * low 23 bits of _refCount). */

void FUN_0039a250(beModelCtrlSubCom *self, int str1, int str2, struct V *va, struct V *vb, char c1, char c2, float f) {
    int a;
    int v;
    int *s;
    int *old;
    int *hd;
    int r;
    beModelCtrlSCEffect *e;
    a = igObject_GetAllocator();
    igSmartPointer<beModelCtrlSCEffect> effect(FUN_0034f8e0(GPR_00554c14 != 0 ? a : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0])));
    e = effect.p;
    if (g_stringPool[0] == 0) {
        v = FUN_002eb010(0x10);
        if (v != 0) {
            v = StringPool_Construct(v);
        }
        g_stringPool[0] = v;
    }
    s = (int *)StringPool_Intern(g_stringPool[0], str1);
    old = (int *)e->_modelName;
    if (old != 0) {
        hd = old - 2;
        r = old[-1] - 1;
        old[-1] = r;
        if (r == 0) {
            StringChunk_ReleaseHeader(*hd, hd);
        }
    }
    e->_modelName = (int)s;
    effect.p->_geneRamNo = -1;
    e = effect.p;
    if (g_stringPool[0] == 0) {
        v = FUN_002eb010(0x10);
        if (v != 0) {
            v = StringPool_Construct(v);
        }
        g_stringPool[0] = v;
    }
    s = (int *)StringPool_Intern(g_stringPool[0], str2);
    old = (int *)e->_seqName;
    if (old != 0) {
        hd = old - 2;
        r = old[-1] - 1;
        old[-1] = r;
        if (r == 0) {
            StringChunk_ReleaseHeader(*hd, hd);
        }
    }
    e->_seqName = (int)s;
    effect.p->_startFrame = f;
    e = effect.p;
    ((float *)e->_offset)[0] = va->x;
    ((float *)e->_offset)[1] = va->y;
    ((float *)e->_offset)[2] = va->z;
    e = effect.p;
    ((float *)e->_rotation)[0] = vb->x;
    ((float *)e->_rotation)[1] = vb->y;
    ((float *)e->_rotation)[2] = vb->z;
    effect.p->_isSeqDead = c1;
    effect.p->_isPositionLock = c2;
    ObjectList_AppendRetained(self->_comList, effect.p);
}

/* Owning stack reference to the new record, released on scope exit (reference count in the low 23
 * bits of refs). */

void FUN_0039a500(A *arg0, S *arg1) {
    int v;
    float f;
    float e;
    R *t;
    int k;

    v = igObject_GetAllocator(arg0);
    v = (GPR_00554c14 != 0) ? v : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
    igSmartPointer<R> rec((R *)FUN_0034f6f0(v));
    rec.p->f16 = arg1->f16;
    e = arg1->f20;
    if (e == -1.0f) {
        f = 100000000.0f;
    } else {
        f = arg1->f16 + e;
    }
    t = rec.p;
    t->f28 = f;
    t = rec.p;
    t->f32 = arg1->f24;
    t->f36 = arg1->f28;
    t->f40 = arg1->f32;
    t = rec.p;
    t->f44 = arg1->f36;
    t->f48 = arg1->f40;
    t->f52 = arg1->f44;
    k = arg1->f12;
    switch (k / 10000) {
    case 0:
        if (k < 1000) {
            rec.p->f24 = 0;
        } else {
            rec.p->f24 = 2;
        }
        break;
    case 6:
        rec.p->f24 = 1;
        break;
    case 7:
    case 8:
        rec.p->f24 = 2;
        break;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 9:
    default:
        rec.p->f24 = 0;
        break;
    }
    rec.p->f20 = arg1->f12;
    ObjectList_AppendRetained(arg0->f8, rec.p);
}

/* Owning stack reference to the new sound command, released on scope exit once the list holds its
 * own reference (reference count in the low 23 bits of _refCount). */

void FUN_0039a750(beModelCtrlSubCom *arg0, int arg1, float fparg0) {
    int *temp_a1;
    int temp_v0;
    int var_v0;
    int key;
    int var_v0_2;
    int *temp_v1;
    beModelCtrlSCSound *s1;

    key = arg1;
    var_v0 = igObject_GetAllocator(arg0);
    if (GPR_00554c14 != 0) {
        var_v0 = (int)var_v0;
    } else {
        var_v0 = Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
    }
    igSmartPointer<beModelCtrlSCSound> cmd(FUN_0034f4a0(var_v0));
    s1 = cmd.p;
    if (g_stringPool[0] == 0) {
        var_v0_2 = FUN_002eb010(0x10);
        if (var_v0_2 != 0) {
            var_v0_2 = StringPool_Construct(var_v0_2);
        }
        g_stringPool[0] = var_v0_2;
    }
    key = (int)StringPool_Intern(g_stringPool[0], key);
    temp_v1 = (int *)s1->_sndName;
    if (temp_v1 != 0) {
        temp_a1 = temp_v1 - 2;
        temp_v0 = temp_v1[-1] - 1;
        temp_v1[-1] = temp_v0;
        if (temp_v0 == 0) {
            StringChunk_ReleaseHeader(*temp_a1, temp_a1);
        }
    }
    s1->_sndName = key;
    cmd.p->_startFrame = fparg0;
    ObjectList_AppendRetained(arg0->_comList, cmd.p);
}

int Gap__Bec__beModelCtrlSCSound__vfunc_20(void)
{
    return g_beModelCtrlSCSound_metaObject[0];
}

int Gap__Bec__beModelCtrlSCEffect__vfunc_20(void)
{
    return g_beModelCtrlSCEffect_metaObject[0];
}

int Gap__Bec__beModelCtrlSCHitBox__vfunc_20(void)
{
    return g_beModelCtrlSCHitBox_metaObject[0];
}
