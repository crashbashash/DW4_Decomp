#include "dw4/reflected.h"
extern "C" {
struct V4 { float x, y, z; };
float FUN_00123640(float, float);
bool FUN_0018b050(void *, int);
void igMatrix44f_SetIdentity(void *);
void FUN_00191670(void *, void *, float);
void FUN_00192f50(V4 *, void *, void *);
void *FUN_002eb010(int);
/* allocate-and-construct helpers: each stores the class handle named by its return type */
beModelCtrlNode2 *FUN_0034fd00(int);
beModelCtrlInfoRideOn4 *FUN_00351420(int);
beModelCtrlInfoRideOn3 *FUN_00351780(int);
beModelCtrlInfoRideOn2 *FUN_00351ad0(int);
beModelCtrlInfoAI *FUN_00352140(int);
beModelCtrlInfoHitBody *FUN_003523d0(int);
int FUN_00356ab0(void);
beBaseInfoDataList *beBaseInfoDataList_Create(int);
igObjectList *FUN_003908e0(beModelCtrlInfoHitBody *, beBaseInfoRam *, void *, long long);
void FUN_00392d90(void *);
int FUN_00393c80(beModelCtrl *, beBaseInfoRam *, beModelCtrlInfoWork *, const char *, const char *);
void FUN_00394400(beModelCtrl *, beBaseInfoRam *, const char *, const char *, const char *, int, int, const char *, int, int);
void FUN_00395250(beModelCtrl *, beBaseInfo *, beBaseInfoRam *, beModelCtrlInfoWork *);
void FUN_003956e0(beModelCtrl *, beBaseInfo *, beBaseInfoRam *, beModelCtrlInfoWork *, int);
int FUN_003960f0(beModelCtrl *, beModelCtrlInfoWork *);
void FUN_00396940(beModelCtrl *, beModelCtrlNode2 *, igObject *);
void FUN_00399f20(int, beBaseInfoRam *);
void FUN_0039a250(int, const char *, const char *, V4 *, V4 *, int, float, int);
void FUN_0039a750(int, const char *, float);
void FUN_003a84a0(beBaseInfoRam *, float);
void FUN_003a8760(beBaseInfoRam *);
void Matrix44_Copy(void *, void *);
void Matrix44_FromTranslation(void *, V4 *);
void Matrix44_GetTranslation(void *, V4 *);
void Matrix44_SetTranslation(void *, V4 *);
int Memory_GetAllocatorBySelector(int);
void StringChunk_ReleaseHeader(int, int *);
void *StringPool_Construct(void *);
const char *StringPool_Intern(void *, const char *);
void beMessenger_AppendBool(int, unsigned char);
void beMessenger_AppendInt(int, int);
void beMessenger_AppendMatrix(int, void *);
void beMessenger_AppendObject(int, void *);
void beMessenger_AppendString(int, const char *);
int beMessenger_GetBool(int, int);
int beMessenger_GetBoolCount(int);
float beMessenger_GetFloat(int, int);
int beMessenger_GetInt(int, int);
int beMessenger_GetIntCount(int);
void beMessenger_GetMatrix(void *, int, int);
int beMessenger_GetMatrixCount(int);
int beMessenger_GetObject(int, int);
const char *beMessenger_GetString(int, int);
int beMessenger_GetStringCount(int);
void beMessenger_GetVec3(V4 *, int, int);
int beMessenger_GetVec3Count(int);
void beMessenger_PopArgContext(int);
void beMessenger_PushArgContext(int);
unsigned beMessenger_ResolveEnumValue(int, int, const char *);
void beMessenger_SendNamed(int, const char *, const char *, int, const char *);
void igObject_Destroy(void *);
int igObject_GetAllocator(void *);
/* the property container lookup: beBaseInfoRam._dataList / beBaseInfo._dataList / a Seq record's _dataList in, one record out */
beBaseInfoData *igProperty_FindByName(int, int, const char *);
int igStrCmp(const char *, const char *);
extern float DAT_004c8fb8[4];
extern char DAT_004e0858[];
extern float DAT_004e0ef0[4];
extern float DAT_004e1058[4];
extern float DAT_004e105c[4];
extern float DAT_004e1060[4];
extern float DAT_004e1078[4];
extern float DAT_004e1088[4];
extern float DAT_004e1098[4];
extern char DAT_0050ef18[];
extern char DAT_0050ef60[];
extern char DAT_0050efd8[];
extern char DAT_0050efe0[];
extern char DAT_0050eff0[];
extern char DAT_0050eff8[];
extern char DAT_0050f1b8[];
extern char DAT_0050f1d8[];
extern char DAT_0050f1e0[];
extern char DAT_0050f1e8[];
extern char DAT_0050f1f0[];
extern char DAT_0050f200[];
extern char DAT_0050f210[];
extern char DAT_0050f220[];
extern char DAT_0050f228[];
extern char DAT_0050f230[];
extern int DAT_00561898[4];
extern int DAT_00585be0[4];
extern void *DAT_00586f20[4];
extern int DAT_00587110[4];
extern unsigned char DAT_0058a210[];
extern unsigned char GPR_00554c14;
int Gap__Bec__beModelCtrl__vfunc_33(beModelCtrl *self, beBaseInfoRam *ent, const char *msgname);
}

/* matching construct: RAII holder; its mangled destructor name pins the class name Ref */
struct Ref {
    igObject *p;
    Ref(igObject *q) : p(q) {}
    ~Ref() { igObject *x = p; if (x) { --x->_refCount; if ((x->_refCount & 0x7fffff) == 0) igObject_Destroy(x); } }
};

/* Owning stack references to the objects this handler creates before binding them: kind 0 the AI
 * info, 1 the hit-body info, 2..4 the ride-on infos of commands 25..27 and 5 their model node. */
template <int kind> struct ObjRef {
    igObject *p;
    ObjRef(igObject *q) : p(q) {}
    ~ObjRef() { igObject *x = p; if (x) { --x->_refCount; if ((x->_refCount & 0x7fffff) == 0) igObject_Destroy(x); } }
};

/* matching construct: string-handle holder; its mangled destructor name pins the class name Str */
struct Str {
    const char *p;
    ~Str() { const char *o_ = p; if (o_) { int *h_ = (int *)o_ - 2; int c_ = ((int *)o_)[-1] - 1; ((int *)o_)[-1] = c_; if (c_ == 0) StringChunk_ReleaseHeader(*h_, h_); } }
};

/* matching construct: dummy-virtual views so the calls dispatch through the retail vtable offsets (no fields) */
struct CtlV {
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4();
    virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
    virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14();
    virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24();
    virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
    virtual void d30(); virtual void d31(); virtual void d32();
    virtual int v33(beBaseInfoRam *, const char *);
    virtual void d34(); virtual void d35();
    virtual void v36(beBaseInfoRam *);
    virtual void d37(); virtual void d38(); virtual void d39();
    virtual void v40(beBaseInfoRam *);
    virtual void v41(beBaseInfoRam *);
    virtual void v42(beBaseInfoRam *);
    virtual void v43(beBaseInfoRam *);
    virtual void v44(beBaseInfoRam *);
    virtual void v45(beBaseInfoRam *);
    virtual void d46();
    virtual unsigned char v47(beBaseInfoRam *, const char *);
};
struct NodeV {
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4();
    virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
    virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14();
    virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24();
    virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
    virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34();
    virtual void v35(void *);
};
struct LodV {
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4();
    virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
    virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14();
    virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual int v20();
    virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24();
    virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28();
    virtual void v29();
};

#define REL(q) { igObject *o_ = (igObject *)(q); if (o_) { o_->_refCount = o_->_refCount - 1; if ((o_->_refCount & 0x7fffff) == 0) igObject_Destroy(o_); } }
#define RET(q) { igObject *o_ = (igObject *)(q); if (o_) o_->_refCount = o_->_refCount + 1; }
#define ALLOC(a, o) int a = igObject_GetAllocator(o); a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(DAT_00587110[0]);
#define POOL() if (DAT_00586f20[0] == 0) { void *pl_ = FUN_002eb010(0x10); if (pl_ != 0) pl_ = StringPool_Construct(pl_); DAT_00586f20[0] = pl_; }
#define SREL(old) if (old) { int *h_ = (int *)old - 2; int c_ = ((int *)old)[-1] - 1; ((int *)old)[-1] = c_; if (c_ == 0) StringChunk_ReleaseHeader(*h_, h_); }
#define SETSTR(fld, txt) { POOL() const char *tk_ = StringPool_Intern(DAT_00586f20[0], txt); const char *old_ = (const char *)d->fld; SREL(old_) d->fld = (int)tk_; }
#define NAMEOF(b) const char *b; { const char *a_ = (const char *)nm->_name; if (a_ != 0) b = a_; else b = DAT_004e0858; }
/* reflection types the vec3 fields as int words; the code reads and writes them as floats */
#define FLT(x) (*(float *)&(x))

#define M (self->_messenger)
#define CV ((CtlV *)self)
#define O3 ((beModelCtrlNode2 *)node->_node)
#define OV3 ((NodeV *)node->_node)
/* first child of the model node: an igLod (its meta is compared in case 22) */
#define LOD0(n) (((igLod **)((igObjectList *)(n)->_childList)->_data)[0])
#define MOVES(d_) ((beModelCtrlMoveObjectList *)(d_)->_moveObjectList)
#define ENSURE(ent_) Hp::Ensure(ent_, tf_);

struct Hp {
    static inline void Ensure(beBaseInfoRam *e, beModelCtrlInfoRideOn *&s) {
        if (e->_dataList == 0) {
            int a = igObject_GetAllocator(e);
            a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(DAT_00587110[0]);
            Ref r((igObject *)beBaseInfoDataList_Create(a));
            s = (beModelCtrlInfoRideOn *)r.p;
            RET(s)
            REL(e->_dataList)
            e->_dataList = (int)s;
        }
    }
};

int Gap__Bec__beModelCtrl__vfunc_33(beModelCtrl *self, beBaseInfoRam *ent, const char *msgname) {
    beBaseInfo *nm = (beBaseInfo *)ent->_parentInfo;
    V4 c0_v, c5_v, c24_p, c24_r, c6_t1, c6_t2, c26_t, c27_t, c8_258, c8_248, c8_238, c25_v, c26_v;
    float c5_m[16], c24_m[16], c6_m[16], c26_m[16], c27_m[16];
    int c6_obj;
    igObjectList *c6_lst;
    int c6_hit;
    igObject *s_;
    beModelCtrlInfoRideOn *tf_;
    ENSURE(ent)
    beModelCtrlInfoRamData *node = (beModelCtrlInfoRamData *)igProperty_FindByName(ent->_dataList, DAT_00585be0[0], DAT_0050ef60);
    beModelCtrlInfoWork *d = (beModelCtrlInfoWork *)node->_work;
    if (CV->v47(ent, msgname) == 1) return 1;
    unsigned sel = beMessenger_ResolveEnumValue(M, FUN_00356ab0(), msgname);
    switch (sel) {
    case 0: {
        Str sp30C;
        sp30C.p = 0;
        ent->_isRun = 1;
        ent->_st0 = 0; ent->_st3 = 0; ent->_st2 = 0; ent->_st1 = 0;
        if (beMessenger_GetStringCount(M) == 1) {
            const char *t = beMessenger_GetString(M, 0);
            POOL()
            const char *tk = StringPool_Intern(DAT_00586f20[0], t);
            const char *o = sp30C.p;
            SREL(o)
            sp30C.p = tk;
        } else if (beMessenger_GetStringCount(M) >= 2) {
            const char *t = beMessenger_GetString(M, 1);
            POOL()
            const char *tk = StringPool_Intern(DAT_00586f20[0], t);
            const char *o = sp30C.p;
            SREL(o)
            sp30C.p = tk;
        }
        CV->v36(ent);
        beModelCtrlInfoWork *d2 = (beModelCtrlInfoWork *)node->_work;
        beDataObjInt *y = (beDataObjInt *)d2->_mHp;
        if (y->_data == 0) {
            y->_data = 0x64;
            ((beDataObjInt *)d2->_hp)->_data = 0x64;
        }
        igObject *z = (igObject *)LOD0(O3)->_bound;
        RET(z)
        REL(d2->_baseAABox)
        d2->_baseAABox = (int)z;
        beModelCtrlNode2 *o3 = O3;
        REL(o3->_bound)
        o3->_bound = 0;
        FUN_00192f50(&c0_v, DAT_004e1098, O3->_m);
        float ang = FUN_00123640(c0_v.x, c0_v.z);
        FLT(d2->_direction[1]) = ang;
        FLT(d2->_targetDirection[1]) = ang;
        if (igProperty_FindByName(nm->_dataList, DAT_00585be0[0], DAT_0050efd8) != 0 ||
            igProperty_FindByName(nm->_dataList, DAT_00585be0[0], DAT_0050efe0) != 0) {
            ALLOC(a, self)
            ObjRef<0> r((igObject *)FUN_00352140(a));
            igObject *s = r.p;
            RET(s)
            REL(d2->_aI)
            d2->_aI = (int)s;
        }
        if (sp30C.p == 0)
            CV->v33(ent, DAT_0050eff0);
        else
            CV->v33(ent, sp30C.p);
        igObject *w = (igObject *)d2->_baseAABox;
        if (w != 0) FUN_00396940(self, O3, w);
        return 1;
    }
    case 2:
        if (ent->_isRun != 0) {
            CV->v42(ent);
            beMessenger_PushArgContext(M);
            int id = ent->_ramNo;
            NAMEOF(n)
            beMessenger_SendNamed(M, DAT_0050eff8, n, id, DAT_0050f1d8);
            if (d != 0) FUN_00399f20(d->_subCommand, ent);
            REL(node->_work)
            node->_work = 0;
            beModelCtrlNode2 *o3 = O3;
            REL(o3->_bound)
            o3->_bound = 0;
            FUN_003a8760(ent);
            ent->_isRun = 0;
            beMessenger_PopArgContext(M);
        }
        return 1;
    case 28: {
        unsigned char f = ent->_isRun;
        beMessenger_AppendBool(M, f);
        return 1;
    }
    case 29:
        if (ent->_isRun == 0) {
            beMessenger_AppendBool(M, 0);
        } else if (d == 0) {
            beMessenger_AppendBool(M, 0);
        } else if (igStrCmp((const char *)d->_seqCodeName, beMessenger_GetString(M, 0)) == 0) {
            beMessenger_AppendBool(M, 1);
        } else {
            beMessenger_AppendBool(M, 0);
        }
        return 1;
    case 8:
        if (ent->_isRun != 0 && d != 0) {
            float *p;
            if (beMessenger_GetVec3Count(M) == 2) {
                beMessenger_GetVec3(&c8_238, M, 1);
                p = &c8_238.x;
            } else {
                p = DAT_004e1058;
            }
            c8_248.x = p[0]; c8_248.y = p[1]; c8_248.z = p[2];
            int sub = d->_subCommand;
            const char *s2 = beMessenger_GetString(M, 0);
            const char *s1 = beMessenger_GetString(M, 1);
            float f20 = beMessenger_GetFloat(M, 0);
            beMessenger_GetVec3(&c8_258, M, 0);
            int b0 = beMessenger_GetBool(M, 0);
            FUN_0039a250(sub, s2, s1, &c8_258, &c8_248, b0, f20, beMessenger_GetBool(M, 1));
        }
        return 1;
    case 9:
        if (ent->_isRun != 0 && d != 0) {
            int sub = d->_subCommand;
            const char *s0 = beMessenger_GetString(M, 0);
            FUN_0039a750(sub, s0, beMessenger_GetFloat(M, 0));
        }
        return 1;
    case 32: {
        beModelCtrlInfoDataSeq *seq = (beModelCtrlInfoDataSeq *)igProperty_FindByName(nm->_dataList, DAT_00585be0[0], DAT_0050f1e0);
        igObjectList *l = (igObjectList *)seq->_dataList;
        int n = l->_count;
        beMessenger_AppendString(M, DAT_0050f1b8);
        int i;
        for (i = 0; i < n; i++) {
            beModelCtrlData *entry = (beModelCtrlData *)((void **)l->_data)[i];
            const char *b;
            const char *a_ = (const char *)entry->_name;
            if (a_ != 0) b = a_; else b = DAT_004e0858;
            beMessenger_AppendString(M, b);
        }
        return 1;
    }
    case 30:
        self->_isDebugHitBox = 1;
        return 1;
    case 31:
        self->_isDebugHitBox = 0;
        return 1;
    case 3: {
        NAMEOF(n)
        beMessenger_AppendString(M, n);
        return 1;
    }
    case 4:
        if (ent->_isRun != 0) {
            NAMEOF(n)
            beMessenger_AppendString(M, n);
        }
        return 1;
    case 5:
        if (ent->_isRun != 0 && d != 0 && beMessenger_GetMatrixCount(M) != 0) {
            beMessenger_GetMatrix(c5_m, M, 0);
            OV3->v35(c5_m);
            if (d != 0) {
                FUN_00192f50(&c5_v, DAT_004e1098, c5_m);
                float ang = FUN_00123640(c5_v.x, c5_v.z);
                FLT(d->_direction[1]) = ang;
                FLT(d->_targetDirection[1]) = ang;
            }
            igObject *a2 = (igObject *)d->_baseAABox;
            if (a2 != 0) FUN_00396940(self, O3, a2);
        }
        return 1;
    case 10:
        if (ent->_isRun == 0) return 1;
    case 11:
        beMessenger_AppendInt(M, ent->_ramNo);
        beMessenger_AppendMatrix(M, O3->_m);
        beMessenger_AppendObject(M, O3);
        return 1;
    case 12:
        if (ent->_isRun != 0 && d != 0 && d->_mutekiCount == 0.0f)
            beMessenger_AppendMatrix(M, O3->_m);
        return 1;
    case 13:
        if (ent->_isRun != 0) {
            ENSURE(ent)
            beBaseInfoData *t = igProperty_FindByName(ent->_dataList, DAT_00585be0[0], DAT_0050f1e8);
            if (t != 0) beMessenger_AppendObject(M, t);
        }
        return 1;
    case 18:
        if (ent->_isRun != 0 && d != 0) d->_isOnCtrl = 1;
        return 1;
    case 19:
        if (ent->_isRun != 0 && d != 0) {
            d->_isOnCtrl = 0;
            CV->v40(ent);
        }
        return 1;
    case 20:
        if (ent->_isRun != 0 && d != 0) {
            FUN_003a84a0(ent, 0.0f);
            int id = ent->_ramNo;
            NAMEOF(n)
            beMessenger_SendNamed(M, DAT_0050eff8, n, id, DAT_0050f1f0);
            d->_isOnFreeze = 1;
            CV->v41(ent);
        }
        return 1;
    case 21:
        if (ent->_isRun != 0 && d != 0) {
            FUN_003a84a0(ent, 1.0f);
            int id = ent->_ramNo;
            NAMEOF(n)
            beMessenger_SendNamed(M, DAT_0050eff8, n, id, DAT_0050f200);
            d->_isOnFreeze = 0;
        }
        return 1;
    case 22:
        if (ent->_isRun != 0 && d != 0 && d->_svLODHighRange == -1.0f) {
            int t = DAT_00561898[0];
            igLod *o = LOD0(O3);
            if (t == ((LodV *)o)->v20()) {
                igNodeList *yc = (igNodeList *)o->_childList;
                int cnt = 0;
                if (yc != 0) cnt = yc->_count;
                if (cnt == 3) {
                    igFloatList *yb = (igFloatList *)o->_rangeList;
                    d->_svLODHighRange = ((float *)yb->_data)[2];
                    int n = yb->_count;
                    if (n != 0 && n > 2) ((float *)yb->_data)[2] = DAT_004c8fb8[0];
                    ((LodV *)o)->v29();
                }
            }
        }
        return 1;
    case 23:
        if (ent->_isRun != 0 && d != 0) {
            float f = d->_svLODHighRange;
            if (f != -1.0f) {
                igLod *o = LOD0(O3);
                igFloatList *yb = (igFloatList *)o->_rangeList;
                int n = yb->_count;
                if (n != 0 && n > 2) ((float *)yb->_data)[2] = f;
                d->_svLODHighRange = -1.0f;
                ((LodV *)o)->v29();
            }
        }
        return 1;
    case 24:
        if (ent->_isRun != 0 && d != 0) {
            beMessenger_GetVec3(&c24_p, M, 0);
            beMessenger_GetVec3(&c24_r, M, 1);
            igMatrix44f_SetIdentity(c24_m);
            Matrix44_FromTranslation(c24_m, &c24_p);
            if (c24_r.x != 0.0f) FUN_00191670(c24_m, DAT_004e1078, 0.017453292f * c24_r.x);
            if (c24_r.y != 0.0f) FUN_00191670(c24_m, DAT_004e1088, 0.017453292f * c24_r.y);
            { float rz = c24_r.z; if (rz != 0.0f) FUN_00191670(c24_m, DAT_004e1098, 0.017453292f * rz); }
            OV3->v35(c24_m);
            FLT(d->_targetDirection[1]) = 0.017453292f * c24_r.y;
            FUN_003956e0(self, nm, ent, d, 1);
            igObject *a2 = (igObject *)d->_baseAABox;
            if (a2 != 0) FUN_00396940(self, O3, a2);
        }
        return 1;
    case 7:
        if (ent->_isRun != 0 && d != 0) {
            const char *s1 = beMessenger_GetString(M, 0);
            FUN_00393c80(self, ent, d, s1, beMessenger_GetString(M, 1));
        }
        return 1;
    case 14:
        if (ent->_isRun == 0) {
            beMessenger_AppendInt(M, 0);
        } else if (d == 0) {
            beMessenger_AppendInt(M, 0);
        } else {
            beMessenger_AppendInt(M, ((beDataObjInt *)d->_hp)->_data);
            beMessenger_AppendObject(M, (void *)d->_hp);
            beMessenger_AppendObject(M, (void *)d->_mHp);
        }
        return 1;
    case 15:
        if (ent->_isRun != 0 && d != 0) {
            int v = beMessenger_GetInt(M, 0);
            ((beDataObjInt *)d->_hp)->_data = v;
            beDataObjInt *y = (beDataObjInt *)d->_mHp;
            if (y->_data < v) y->_data = v;
        }
        return 1;
    case 16:
        if (ent->_isRun != 0 && d != 0) beMessenger_AppendInt(M, d->_recNo);
        return 1;
    case 6:
        if (d->_mutekiCount != 0.0f) {
            unsigned char ok = 0;
            NAMEOF(n)
            if (*n == 0x70 && *beMessenger_GetString(M, 0) == 0x70 && d->_hp != 0) ok = 1;
            if (!(ok & 0xFF)) return 1;
        }
        if (d->_isOnCtrl == 0 || igStrCmp((const char *)d->_seqCodeName, DAT_0050f1b8) == 0) return 1;
        {
            igObject *hitbody = (igObject *)d->_hitBody;
            if (hitbody == 0) {
                ALLOC(a, self)
                ObjRef<1> r((igObject *)FUN_003523d0(a));
                igObject *s = r.p;
                RET(s)
                REL(d->_hitBody)
                d->_hitBody = (int)s;
                hitbody = r.p;
            }
            c6_obj = beMessenger_GetObject(M, 0);
            c6_lst = FUN_003908e0((beModelCtrlInfoHitBody *)hitbody, ent, O3->_m, ((igInsightCore *)self->_insight)->_worldTime);
            unsigned char found = 0;
            int idx = 0;
            int cnt = c6_lst->_count;
            for (idx = 0; idx < cnt; idx++) {
                if (!FUN_0018b050(((void **)c6_lst->_data)[idx], c6_obj)) continue;
                {
                    c6_hit = idx;
                    found = 1;
                    break;
                }
            }
            if (found) {
                int s8 = beMessenger_GetInt(M, 0);
                beMessenger_GetMatrix(c6_m, M, 0);
                const char *s5 = beMessenger_GetString(M, 0);
                int s7 = beMessenger_GetInt(M, 1);
                int r6 = -1;
                Matrix44_GetTranslation(c6_m, &c6_t1);
                Matrix44_GetTranslation(O3->_m, &c6_t2);
                beMessenger_PushArgContext(M);
                if (*s5 != 0x70) {
                    beMessenger_SendNamed(M, DAT_0050ef18, s5, s7, DAT_0050f210);
                    if (beMessenger_GetIntCount(M) == 1)
                        r6 = beMessenger_GetInt(M, 0);
                    else
                        r6 = -9;
                }
                if (r6 != -9) {
                    NAMEOF(n)
                    FUN_00394400(self, ent, DAT_0050f220, DAT_0050f228, n, s8, c6_hit, s5, s7, r6);
                    if (DAT_0058a210[0] != 0) {
                        FLT(d->_targetDirection[1]) = FUN_00123640(c6_t1.x - c6_t2.x, c6_t1.z - c6_t2.z);
                        FUN_003956e0(self, nm, ent, d, 1);
                    }
                }
                beMessenger_PopArgContext(M);
                if (beMessenger_GetBoolCount(M) == 0) beMessenger_AppendBool(M, 1);
            }
        }
        return 1;
    case 1:
    default:
        if (ent->_isRun != 0) {
            if (igStrCmp(msgname, DAT_0050f1b8) == 0) {
                CV->v43(ent);
                POOL()
                const char *tk = StringPool_Intern(DAT_00586f20[0], DAT_0050f1b8);
                const char *old = (const char *)d->_seqCodeName;
                SREL(old)
                d->_seqCodeName = (int)tk;
            } else if (igStrCmp(msgname, DAT_0050f230) == 0) {
                beMessenger_PushArgContext(M);
                int id = ent->_ramNo;
                NAMEOF(n)
                beMessenger_SendNamed(M, DAT_0050eff8, n, id, DAT_0050f1d8);
                if (d != 0) FUN_00399f20(d->_subCommand, ent);
                beModelCtrlNode2 *o3 = O3;
                REL(o3->_bound)
                o3->_bound = 0;
                FUN_003a8760(ent);
                beMessenger_PopArgContext(M);
            } else {
                const char *tk;
                beModelCtrlInfoDataSeq *fb = (beModelCtrlInfoDataSeq *)igProperty_FindByName(nm->_dataList, DAT_00585be0[0], DAT_0050f1e0);
                beModelCtrlData *t = (beModelCtrlData *)igProperty_FindByName(fb->_dataList, DAT_00585be0[0], msgname);
                POOL()
                tk = StringPool_Intern(DAT_00586f20[0], msgname);
                const char *old = (const char *)d->_seqCodeName;
                SREL(old)
                d->_seqCodeName = (int)tk;
                RET(t)
                REL(d->_comData)
                d->_comData = (int)t;
                d->_comIndex = FUN_003960f0(self, d);
                d->_comLabelCount = 0;
                d->_ctrlSt0 = 0;
                d->_ctrlSt1 = 0;
                d->_ctrlSt1 = 0;
                ((igDataList *)d->_pdMoveDataList)->_count = 0;
                SETSTR(_wCheckName, 0)
                FUN_00399f20(d->_subCommand, ent);
                SETSTR(_luaBHit, 0)
                SETSTR(_luaWHit, 0)
                SETSTR(_luaFHit, 0)
                d->_isWallCheck = 1; d->_isFloorCheck = 1; d->_isFallCheck = 1;
                if (d->_mutekiCount < 0.0f) d->_mutekiCount = 0.0f;
                int n = MOVES(d)->_count;
                int i;
                for (i = 0; i < n; i++) {
                    beModelCtrlMoveObject *c = (beModelCtrlMoveObject *)((void **)MOVES(d)->_data)[i];
                    if (i != 3) {
                        if (c->_isSeqStop != 0) FUN_00392d90(c);
                    } else {
                        c->_isRun = 0;
                        c->_speed = 0;
                    }
                }
                FUN_00395250(self, nm, ent, d);
                CV->v44(ent);
            }
        }
        return 1;
    case 17:
        CV->v45(ent);
        return 1;
    case 25:
        if (d != 0) {
            if (beMessenger_GetInt(M, 0) != 0) {
                if (d->_rideOnData == 0) {
                    ALLOC(a, self)
                    ObjRef<2> r((igObject *)FUN_00351ad0(a));
                                        float *mt = (float *)O3->_m;
                    {
                        ALLOC(b, self)
                        ObjRef<5> r2((igObject *)FUN_0034fd00(b));
                        ((NodeV *)r2.p)->v35(mt);
                        s_ = r2.p;
                        tf_ = (beModelCtrlInfoRideOn *)r.p;
                        RET(s_)
                        REL(tf_->_modelNode)
                        tf_->_modelNode = (int)s_;
                    }
                    Matrix44_Copy(((beModelCtrlInfoRideOn2 *)r.p)->_oldMatrix, mt);
                    beMessenger_GetVec3(&c25_v, M, 0);
                    { beModelCtrlInfoRideOn2 *f2 = (beModelCtrlInfoRideOn2 *)r.p; FLT(f2->_vector) = c25_v.x; ((float *)&f2->_vector)[1] = c25_v.y; ((float *)&f2->_vector)[2] = c25_v.z; }
                    {
                        igObject *s = r.p;
                        RET(s)
                        REL(d->_rideOnData)
                        d->_rideOnData = (int)s;
                    }
                }
            } else {
                REL(d->_rideOnData)
                d->_rideOnData = 0;
            }
        }
        return 1;
    case 26:
        if (d != 0) {
            if (beMessenger_GetInt(M, 0) != 0) {
                if (d->_rideOnData == 0) {
                    ALLOC(a, self)
                    ObjRef<3> r((igObject *)FUN_00351780(a));
                                        Matrix44_GetTranslation(O3->_m, &c26_t);
                    Matrix44_Copy(c26_m, DAT_004e0ef0);
                    Matrix44_SetTranslation(c26_m, &c26_t);
                    {
                        ALLOC(b, self)
                        ObjRef<5> r2((igObject *)FUN_0034fd00(b));
                        ((NodeV *)r2.p)->v35(c26_m);
                        s_ = r2.p;
                        tf_ = (beModelCtrlInfoRideOn *)r.p;
                        RET(s_)
                        REL(tf_->_modelNode)
                        tf_->_modelNode = (int)s_;
                    }
                    Matrix44_Copy(((beModelCtrlInfoRideOn3 *)r.p)->_oldMatrix, c26_m);
                    beMessenger_GetVec3(&c26_v, M, 0);
                    { beModelCtrlInfoRideOn3 *f3 = (beModelCtrlInfoRideOn3 *)r.p; FLT(f3->_worldPosition[0]) = c26_v.x; FLT(f3->_worldPosition[1]) = c26_v.y; FLT(f3->_worldPosition[2]) = c26_v.z; }
                    ((beModelCtrlInfoRideOn3 *)r.p)->_minKyori = beMessenger_GetFloat(M, 0);
                    ((beModelCtrlInfoRideOn3 *)r.p)->_maxKyori = beMessenger_GetFloat(M, 1);
                    ((beModelCtrlInfoRideOn3 *)r.p)->_minSpeed = beMessenger_GetFloat(M, 2);
                    ((beModelCtrlInfoRideOn3 *)r.p)->_maxSpeed = beMessenger_GetFloat(M, 3);
                    {
                        igObject *s = r.p;
                        RET(s)
                        REL(d->_rideOnData)
                        d->_rideOnData = (int)s;
                    }
                }
            } else {
                REL(d->_rideOnData)
                d->_rideOnData = 0;
            }
        }
        return 1;
    case 27:
        if (d != 0) {
            if (beMessenger_GetInt(M, 0) != 0) {
                if (d->_rideOnData == 0) {
                    ALLOC(a, self)
                    ObjRef<4> r((igObject *)FUN_00351420(a));
                                        Matrix44_GetTranslation(O3->_m, &c27_t);
                    Matrix44_Copy(c27_m, DAT_004e0ef0);
                    Matrix44_SetTranslation(c27_m, &c27_t);
                    {
                        ALLOC(b, self)
                        ObjRef<5> r2((igObject *)FUN_0034fd00(b));
                        ((NodeV *)r2.p)->v35(c27_m);
                        s_ = r2.p;
                        tf_ = (beModelCtrlInfoRideOn *)r.p;
                        RET(s_)
                        REL(tf_->_modelNode)
                        tf_->_modelNode = (int)s_;
                    }
                    Matrix44_Copy(((beModelCtrlInfoRideOn4 *)r.p)->_oldMatrix, c27_m);
                    ((int *)&c27_t)[1] = 0;
                    { beModelCtrlInfoRideOn4 *f4 = (beModelCtrlInfoRideOn4 *)r.p; FLT(f4->_oldPlayerPos[0]) = c27_t.x; FLT(f4->_oldPlayerPos[1]) = c27_t.y; FLT(f4->_oldPlayerPos[2]) = c27_t.z; }
                    { beModelCtrlInfoRideOn4 *f4 = (beModelCtrlInfoRideOn4 *)r.p; FLT(f4->_vector[0]) = DAT_004e1058[0]; FLT(f4->_vector[1]) = DAT_004e105c[0]; FLT(f4->_vector[2]) = DAT_004e1060[0]; }
                    ((beModelCtrlInfoRideOn4 *)r.p)->_scalar = beMessenger_GetFloat(M, 0);
                    ((beModelCtrlInfoRideOn4 *)r.p)->_limitter = beMessenger_GetFloat(M, 1);
                    {
                        igObject *s = r.p;
                        RET(s)
                        REL(d->_rideOnData)
                        d->_rideOnData = (int)s;
                    }
                }
            } else {
                REL(d->_rideOnData)
                d->_rideOnData = 0;
            }
        }
        return 1;
    }
}
