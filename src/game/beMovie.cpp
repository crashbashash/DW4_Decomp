#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"
#include "dw4/igTDataList.h"

extern "C" igObject * beBaseInfoDataList_Create(...);
extern "C" int FUN_00331fb0(...);
extern "C" int FUN_003320d0(...);
extern "C" void *FUN_003350f0(...);
extern "C" void *FUN_00367490(...);
extern "C" int Memory_GetAllocatorBySelector(...);
extern "C" void igObject_Destroy(void *);
extern "C" int igObject_GetAllocator(...);
extern "C" int FUN_00332290(int, int);
extern "C" int FUN_00332340(int);
extern "C" void FUN_00332430(int, int);
extern "C" int FUN_00281bb8(int, unsigned char, int);
extern "C" unsigned int FUN_00332490(void *, bool);
extern "C" void FUN_00332370(int, int);
extern "C" int FUN_003323a0(int);
extern "C" int FUN_00332460(int, int, bool);
extern "C" void FUN_003a73b0(void *arg0, int arg1);
extern "C" void FUN_003a7580(void *, int, void *);
extern "C" float FUN_003a7810(float *arg0);
extern "C" long long __fixsfdi(float);
extern "C" void *FUN_0036a510(...);
extern "C" int ObjectList_AppendRetained(...);
extern "C" int igNamedObject_SetName(...);
extern "C" float __floatdisf(long long);
extern "C" void List_RemoveWordAt(...);
extern "C" int List_Reserve(...);
extern "C" void * FUN_00236f80(...);
extern "C" void beMessenger_RegisterReceiver(int, int, char *, int, int);
extern "C" int Gap__Bec__beMovie__vfunc_30(void);
extern "C" int Gap__Bec__beMovie__vfunc_20(void);
extern "C" int *bePadManager_GetPadForPlayer(int, int);
extern "C" int igObject_IsKindOf(void *, int);
extern "C" int beLua__RunNamedChunk(int, int, int);
extern "C" int strcmp(int *, int *);
extern "C" int FUN_002eb010(int);
extern "C" int StringPool_Construct(int);
extern "C" int StringPool_Intern(int, int);
extern "C" void StringChunk_ReleaseHeader(int, void *);
extern "C" int FUN_00100610(void *);
extern "C" int g_ndmwAllocatorSelector[4];
extern "C" unsigned char GPR_00554c14;
struct Obj { int w0; unsigned refs; Obj *w8; Obj *w12; int w16; int w20; };
struct Rel {
    static inline void go(Obj *p) {
        if (p != 0) {
            p->refs = p->refs - 1;
            if ((p->refs & 0x7fffff) == 0) igObject_Destroy(p);
        }
    }
};
extern "C" int FUN_003a6950(Obj *o, int mode);
typedef struct S1 { char pad4[4]; int f4; } S1;
typedef struct O { char pad8[8]; S1 *a; S1 *b; } O;
extern "C" int FUN_003323d0(S1 *);
extern "C" void FUN_003a6b50(O *arg0);
struct S { char pad[8]; int f8; char pad2[4]; int f16; };
extern "C" int FUN_003a6c00(S *arg0, int arg1);
struct DispatchTarget;
extern "C" int FUN_00332160(DispatchTarget *, int, int);
extern "C" int FUN_003a6c80(beCriAudio *self, int arg1, int arg2);
extern "C" int DAT_00510060[4];
extern "C" int DAT_00510080[4];
extern "C" int DAT_005100a0[4];
extern "C" char DAT_005100c0[], DAT_005100e0[], DAT_00510100[];
extern "C" int FUN_003a6ce0(beCriAudio *o, int id, long long value);
extern "C" void FUN_003a6e00(beCriAudio *s);
extern "C" int FUN_003a7300(void *arg0);
extern "C" void FUN_003a74b0(void *arg0);

extern "C" char DAT_00510120[];
extern "C" char DAT_00510140[];
extern "C" char DAT_00510170[];
/* The beCriAudio::_sndf target, a CRI sound-file handle; its +8 word is declared locally. */
struct Q { int p0, p4; int f8; };
/* matching construct: static bool helper members (the retail shape) over the reflected receiver */
struct H {
    static bool A(beCriAudio *s) { return s->_sndf != 0 && s->_audioType == 3; }
    static bool B(beCriAudio *s) { return s->_adxt != 0 && s->_audioType == 1; }
    static bool C(beCriAudio *s) { return s->_adxt != 0 && s->_audioType == 2; }
};
extern "C" void FUN_003a6f70(beCriAudio *s, int a1);
extern "C" int DAT_00510190[4];
extern "C" int DAT_005101b0[4];
/* matching construct: predicate helpers as static members, as in the sibling FUN_003a7260 */
struct Pred {
    static bool A(beCriAudio *s) { return s->_sndf != 0 && s->_audioType == 3; }
    static bool B(beCriAudio *s) { return s->_adxt != 0 && s->_audioType == 1; }
    static bool C(beCriAudio *s) { return s->_adxt != 0 && s->_audioType == 2; }
};
extern "C" int FUN_003a70c0(beCriAudio *s);
struct S_3a7260 {
    static bool A(beCriAudio *s) { return s->_sndf != 0 && s->_audioType == 3; }
    static bool B(beCriAudio *s) { return s->_adxt != 0 && s->_audioType == 1; }
    static bool C(beCriAudio *s) { return s->_adxt != 0 && s->_audioType == 2; }
};
extern "C" void FUN_003a7260(beCriAudio *s, unsigned char a1);
/* matching construct: inline bool predicates as members of a view over the reflected beCriAudio (_adxt, _sndf, _audioType, _errVolume) */
struct O_3a73b0 : beCriAudio {
    bool A() { return _sndf != 0 && _audioType == 3; }
    bool B() { return _adxt != 0 && _audioType == 1; }
    bool C() { return _adxt != 0 && _audioType == 2; }
};
extern "C" float DAT_004c8fc0[];
extern "C" float DAT_004c90b0[];
typedef struct Ramp {
    char pad0[8];
    int mode;
    int base;
    float cur;
    float from;
    float to;
    float step;
} Ramp;
typedef union FBits { float f; struct { unsigned m : 31; unsigned s : 1; } b; } FBits;
extern "C" int FUN_003a7590(Ramp *self, int add, float from, float to, float div);
/* The sign bit of the two scaled
 * sample values is cleared through a byte bit-field union. */
typedef union U { float f; struct { unsigned char p0, p1, p2; unsigned char lo : 7; unsigned char sign : 1; } b; } U;
typedef struct A { char p0[8]; int w8; int w12; float f16; float f20; float f24; } A;
extern "C" int FUN_003a7890(A *arg0, int arg1);
extern "C" int FUN_003a79a0(beCriVolume *arg0);
extern "C" int g_propertyNameField[4];
extern "C" int g_defaultAllocatorSelector[4];
typedef igObject Obj_3a7a20;
struct Rel_3a7a20 {
    static inline void go(Obj_3a7a20 *p) {
        if (p != 0) {
            p->_refCount = p->_refCount - 1;
            if ((p->_refCount & 0x7fffff) == 0) igObject_Destroy(p);
        }
    }
};
struct RefB {
    Obj_3a7a20 *p;
    RefB(void *x) { p = (Obj_3a7a20 *)x; }
    ~RefB() { Obj_3a7a20 *x = p; if (x) { --x->_refCount; if ((x->_refCount & 0x7fffff) == 0) igObject_Destroy(x); } }
};
typedef beBaseInfoRamTimer Lst;
typedef beAction2InfoRam Act;
struct ActOps {
    static inline void Ensure(Act *o) {
        if (o->_dataList == 0) {
            int a = igObject_GetAllocator(o);
            a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
            igSmartPointer<igObject> r((igObject *)((void *)beBaseInfoDataList_Create(a)));
            Obj_3a7a20 *s2 = r.p;
            if (s2 != 0) s2->_refCount = s2->_refCount + 1;
            Rel_3a7a20::go((Obj_3a7a20 *)o->_dataList);
            o->_dataList = (int)s2;
        }
    }
};
extern "C" void FUN_003a7a20(Act *arg0, int arg1, long long arg2);
extern "C" igObject * beBaseInfoDataList_Create(...);
extern "C" int FUN_003a7d80(beBaseInfoRam *arg0, int arg1);
/* The timer record returned by igProperty_FindByName; +32 is the int64 duration. */

struct P { char pad[32]; long long f32; };
extern "C" int FUN_003a7e90(beAction2InfoRam *arg0, int arg1);
extern "C" beBaseInfoRamTimer * igProperty_FindByName(...);
extern "C" long long FUN_003a7fd0(beBaseInfoRam *arg0, int arg1);
struct Prop { char pad40[40]; long long f40; long long f48; float f56; };
typedef igObject Rc;
typedef beAction2InfoRam A_3a8140;
extern "C" float FUN_003a8140(A_3a8140 *arg0, int arg1);
extern "C" void FUN_003a82f0(beBaseInfoRam *arg0, int arg1, float fparg0);
extern "C" int emptyString[4];
extern "C" int g_beBaseInfoRamTimer_metaObject[4];
class E {
public:
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual int v20();
};
extern "C" void FUN_003a84a0(beBaseInfoRam *t, float f);
extern "C" void FUN_003a8580(beBaseInfoRam *self, char *name);
struct Rc_3a8760 { int vt; int rc; };
class DW4VC_88_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); };
extern "C" void FUN_003a8760(beBaseInfoRam *arg0);
typedef struct RefObj { char p0[4]; int f4; } RefObj;
extern "C" int g_igMovieManager_metaObject[4];
extern "C" void Gap__Bec__beMovie__vfunc_32(beMovie *arg0);
extern "C" char DAT_00510200[];
extern "C" void Gap__Bec__beMovie__vfunc_29(beMovie * p0, int p1, char * p2, int p3, int p4);
extern "C" int g_beMovieInfo_metaObject[4];
extern "C" int g_beMovie_metaObject[4];
/* matching construct: dummy-virtual class supplies the retail vtable slot offsets for the virtual calls */
class MovieVirtual {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual int v30(int *);
};
struct ItemPtrList { int pad0[2]; int count; int pad1; int **items; };
struct InfoHolder { int pad0[5]; ItemPtrList *list; };
struct MovieInfoArg { int pad0[3]; InfoHolder *inner; };
extern "C" int g_stringPool[4];
extern "C" int g_bePadManager_metaObject[4];
extern "C" int g_beMovieInfoData_metaObject[4];
extern "C" int g_beLua_metaObject[4];
extern "C" void Gap__Bec__beMovie__vfunc_31(beMovie *self, MovieInfoArg *arg1);
struct S_temp_a0 { char pad4[4]; int f4; };
struct O_3a9190 { S_temp_a0 *m; };
extern "C" O_3a9190 *FUN_003a9190(O_3a9190 *arg0, short arg1);

int FUN_003a6950(Obj *o, int mode) {
    if (mode < 0) {
        int a = igObject_GetAllocator(o);
        a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(g_ndmwAllocatorSelector[0]);
        Rel::go(o->w12);
        o->w12 = (Obj *)FUN_00367490(a);
        Rel::go(o->w8);
        o->w8 = 0;
        o->w16 = 3;
    } else {
        int a = igObject_GetAllocator(o);
        a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(g_ndmwAllocatorSelector[0]);
        Rel::go(o->w8);
        o->w8 = (Obj *)FUN_003350f0(a);
        Rel::go(o->w12);
        o->w12 = 0;
        o->w16 = 1;
        int rate = (mode == 2) ? 0xBB80 : 0x5DC0;
        if (FUN_00331fb0(o->w8, mode, 1, 2, rate) == 0) return 0;
        if (FUN_003320d0(o->w8, mode, 1, 2, rate, 0) == 0) return 0;
    }
    o->w20 = -999;
    return 1;
}

void FUN_003a6b50(O *arg0) {
    S1 *t0;
    S1 *t1;
    S1 *t2;
    t0 = arg0->b;
    if (t0 != 0) {
        t0->f4 = (int)((int) (t0->f4 - 1));
        if (((unsigned long long) ((long long) t0->f4 << 0x29) >> 0x29) == 0) {
            igObject_Destroy((void *)t0);
        }
    }
    arg0->b = 0;
    t1 = arg0->a;
    if (t1 != 0) {
        FUN_003323d0(t1);
    }
    t2 = arg0->a;
    if (t2 != 0) {
        t2->f4 = (int)((int) (t2->f4 - 1));
        if (((unsigned long long) ((long long) t2->f4 << 0x29) >> 0x29) == 0) {
            igObject_Destroy((void *)t2);
        }
    }
    arg0->a = 0;
}

int FUN_003a6c00(S *arg0, int arg1) {
    unsigned char b = 0;
    int t = arg0->f8;
    if (t != 0) {
        if (arg0->f16 == 1) b = 1;
    }
    if (b) { FUN_00332340(t); return FUN_00332290(arg0->f8, arg1); }
    return 0;
}

int FUN_003a6c80(beCriAudio *self, int arg1, int arg2) {
    bool ready = false;
    DispatchTarget *t = (DispatchTarget *)self->_adxt;
    if (t != 0) {
        if (self->_audioType == 2) ready = true;
    }
    if (ready) {
        int r = FUN_00332160(t, arg1, arg2);
        return r;
    }
    return 0;
}

int FUN_003a6ce0(beCriAudio *o, int id, long long value) {
    int ok = o->_sndf != 0;
    if (ok) ok = o->_audioType == 3;
    if (ok) {
        if (id < 1 || id > 255) { FUN_003a7580(o, id, DAT_00510060); return 0; }
        if (FUN_00281bb8(1, id, (int)value)) { FUN_003a7580(o, id, DAT_00510080); return 0; }
        if (FUN_00281bb8(2, id, 0)) { FUN_003a7580(o, id, DAT_005100a0); return 0; }
        ((beCriSndf *)o->_sndf)->_req = id;
        ((beCriSndf *)o->_sndf)->_seq = value;
        ((beCriSndf *)o->_sndf)->_isPlaying = 0;
        return 1;
    }
    return 0;
}

void FUN_003a6e00(beCriAudio *s) {
    if (H::A(s)) {
        int n = ((beCriSndf *)s->_sndf)->_req;
        if (n != 0) {
            if (n <= 0 || n > 255) {
                FUN_003a7580(s, n, DAT_005100c0);
            } else {
                int r = FUN_00281bb8(7, n & 0xFF, 0);
                if (r < 0) {
                    FUN_003a7580(s, r, DAT_005100e0);
                    return;
                }
                if (r > 0) {
                    r = FUN_00281bb8(3, ((beCriSndf *)s->_sndf)->_req & 0xFF, 0);
                    if (r < 0) FUN_003a7580(s, r, DAT_00510100);
                }
                ((beCriSndf *)s->_sndf)->_req = 0;
                ((beCriSndf *)s->_sndf)->_seq = 0;
            }
        }
    } else {
        bool b = H::B(s);
        if (b || H::C(s)) {
            FUN_00332430(s->_adxt, -999);
            FUN_00332370(s->_adxt, 1);
            FUN_00332340(s->_adxt);
        }
    }
}

void FUN_003a6f70(beCriAudio *s, int a1) {
    if (H::A(s)) {
        int n = ((Q *)s->_sndf)->f8;
        if (n != 0) {
            if (n <= 0 || n > 255) {
                FUN_003a7580(s, n, DAT_00510120);
            } else {
                int r = FUN_00281bb8(7, n & 0xFF, 0);
                if (r < 0) {
                    FUN_003a7580(s, r, DAT_00510140);
                    return;
                }
                r = FUN_00281bb8(4, ((Q *)s->_sndf)->f8 & 0xFF, a1);
                if (r < 0) FUN_003a7580(s, r, DAT_00510170);
            }
        }
    } else {
        bool b = H::B(s);
        if (b || H::C(s)) FUN_00332430(s->_adxt, a1);
    }
}

int FUN_003a70c0(beCriAudio *s) {
    if (Pred::A(s)) {
        int n = ((beCriSndf *)s->_sndf)->_req;
        if (n == 0) return 0;
        if (n < 1 || n > 255) {
            FUN_003a7580(s, n, (void *)(&DAT_00510190[0]));
            return -1;
        }
        int r = FUN_00281bb8(7, n & 0xff, 0);
        if (r < 0) {
            FUN_003a7580(s, r, (void *)(&DAT_005101b0[0]));
            return -1;
        }
        switch (r) {
        case 1: case 2:
            ((beCriSndf *)s->_sndf)->_isPlaying = 1;
            return 1;
        default:
            return ((beCriSndf *)s->_sndf)->_isPlaying == 0;
        }
    }
    bool b = Pred::B(s);
    if (b || Pred::C(s)) {
        switch (FUN_00332490((void *)s->_adxt, b)) {
        case 0: return 0;
        case 1: case 2: case 3: case 4: return 1;
        case 5: return 0;
        case 6: default: return -1;
        }
    }
    return -1;
}

void FUN_003a7260(beCriAudio *s, unsigned char a1) {
    if (!S_3a7260::A(s)) {
        bool b = S_3a7260::B(s);
        if (b || S_3a7260::C(s)) FUN_00332370(s->_adxt, a1);
    }
}

int FUN_003a7300(void *arg0) {
    O_3a73b0 *o = (O_3a73b0 *)arg0;
    bool b;
    if (o->A()) {
        return 0;
    }
    b = o->B();
    if (b || o->C()) {
        return FUN_003323a0(o->_adxt);
    }
    return 0;
}

void FUN_003a73b0(void *arg0, int arg1) {
    O_3a73b0 *o = (O_3a73b0 *)arg0;
    bool b;
    int r;
    int t;
    if (o->A()) {
        o->_errVolume = 127;
        return;
    }
    t = arg1;
    b = false;
    if (o->_adxt != 0) {
        t = o->_audioType;
        if (t == 1) {
            b = true;
        }
    }
    if (b || o->C()) {
        r = FUN_00332460(o->_adxt, t, b);
        if (r != -999) {
            if (FUN_003323a0(o->_adxt) == 0) {
                o->_errVolume = r;
                FUN_00332430(o->_adxt, -999);
                FUN_00332370(o->_adxt, 1);
            }
        } else {
            o->_errVolume = -999;
        }
    }
}

void FUN_003a74b0(void *arg0) {
    O_3a73b0 *o = (O_3a73b0 *)arg0;
    bool b;
    if (o->A()) {
        o->_errVolume = -999;
        return;
    }
    b = o->B();
    if (b || o->C()) {
        if (o->_errVolume != -999) {
            FUN_00332430(o->_adxt, o->_errVolume);
            FUN_00332370(o->_adxt, 0);
            o->_errVolume = -999;
        }
    }
}

void FUN_003a7580(void *, int, void *)
{
}

int FUN_003a7590(Ramp *self, int add, float from, float to, float div) {
    FBits u;
    int lo, hi, i, j, lo2, hi2, m, k;
    self->mode = 3;
    self->from = from;
    self->to = to;
    if (from < to) {
        lo = -1; hi = -1;
        for (i = 0; i < 60; i++) {
            if (from <= DAT_004c8fc0[i]) { lo = i; break; }
        }
        for (j = 59; j > -1; j--) {
            if (to >= DAT_004c8fc0[j]) { hi = j; break; }
        }
        self->cur = (float)lo;
        self->step = (float)(hi - lo) / div;
        u.f = -210.0f * DAT_004c8fc0[(int)self->cur];
        u.b.s = 0;
        return add + ((int)u.f - 210 + self->base);
    }
    lo2 = -1; hi2 = -1;
    for (m = 0; m < 60; m++) {
        if (from >= DAT_004c90b0[m]) { lo2 = m; break; }
    }
    for (k = 59; k > -1; k--) {
        if (to <= DAT_004c90b0[k]) { hi2 = k; break; }
    }
    self->cur = (float)lo2;
    self->step = (float)(hi2 - lo2) / div;
    u.f = -210.0f * DAT_004c90b0[(int)self->cur];
    u.b.s = 0;
    return add + ((int)u.f - 210 + self->base);
}

float FUN_003a7810(float *arg0) {
    float t;
    if (arg0[5] < arg0[6]) {
        t = arg0[4] + arg0[7];
        arg0[4] = t;
        return DAT_004c8fc0[(int)t];
    }
    t = arg0[4] + arg0[7];
    arg0[4] = t;
    return DAT_004c90b0[(int)t];
}

int FUN_003a7890(A *arg0, int arg1) {
    float f21 = arg0->f20;
    float f20 = arg0->f24;
    U ua, ub;
    int v0, v1;
    ua.f = -210.0f * FUN_003a7810((float *)arg0);
    ua.b.sign = 0;
    v0 = arg1 + ((int)ua.f - 210 + *(int *)&arg0->w12);
    ub.f = -210.0f * f20;
    ub.b.sign = 0;
    v1 = arg1 + ((int)ub.f - 210 + arg0->w12);
    if (!(f21 <= f20)) {
        if (v0 <= v1) {
            arg0->w8 = 0;
            if (f20 == 0.0f) {
                return -999;
            }
        }
    } else {
        if (v0 >= v1) {
            arg0->w8 = 0;
        }
    }
    return v0;
}

int FUN_003a79a0(beCriVolume *arg0) {
    float temp_f20;
    int var_v0;

    temp_f20 = arg0->_end;
    var_v0 = (int)((int) (127.0f * FUN_003a7810((float *)((float *)arg0))));
    if (var_v0 <= (int) (127.0f * temp_f20)) {
        arg0->_isExec = 0;
        if (temp_f20 == 0.0f) {
            var_v0 = 0;
        }
    }
    return var_v0;
}

void FUN_003a7a20(Act *arg0, int arg1, long long arg2) {
    Lst *var_s2;
    long long t;
    unsigned v;
    float f;

    ActOps::Ensure(arg0);
    var_s2 = (Lst *)((void *)igProperty_FindByName((Obj_3a7a20 *)arg0->_dataList, g_propertyNameField[0], arg1));
    if (var_s2 == 0) {
        int a = igObject_GetAllocator(arg0);
        a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
        RefB sp5C(FUN_0036a510(a));
        igNamedObject_SetName(sp5C.p, arg1);
        if (arg0->_dataList == 0) {
            int b = igObject_GetAllocator(arg0);
            b = GPR_00554c14 ? b : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
            igSmartPointer<igObject> sp58((igObject *)((void *)beBaseInfoDataList_Create(b)));
            Obj_3a7a20 *s2 = sp58.p;
            if (s2 != 0) s2->_refCount = s2->_refCount + 1;
            Rel_3a7a20::go((Obj_3a7a20 *)arg0->_dataList);
            arg0->_dataList = (int)s2;
        }
        ObjectList_AppendRetained((Obj_3a7a20 *)arg0->_dataList, sp5C.p);
        var_s2 = (Lst *)sp5C.p;
    }
    t = ((igInsightCore *)((beAction2 *)arg0->_parentManager)->_insight)->_worldTime;
    v = (unsigned)(t >> 0x12);
    f = (float)v;
    f = f * var_s2->_timeScale;
    var_s2->_timeBias = -(__fixsfdi(f) << 0x12);
    var_s2->_svWorldTime = t;
    var_s2->_keikaFrame = 1.0f;
    var_s2->_endTime = arg2;
}

/* Owning stack reference to the freshly created data list (reference count in the low 23 bits of
 * _refCount); released on scope exit. */

int FUN_003a7d80(beBaseInfoRam *arg0, int arg1) {
    int t;
    int var_v0;
    igObject *p;
    igObject *old;

    if (arg0->_dataList == 0) {
        t = igObject_GetAllocator(); /* matching construct: a0 still holds arg0, retail passes it without a move */
        if (GPR_00554c14 != 0) {
            var_v0 = t;
        } else {
            var_v0 = Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
        }
        {
            igSmartPointer<igObject> r(beBaseInfoDataList_Create(var_v0));
            p = r.p;
            if (p != 0) {
                p->_refCount = p->_refCount + 1;
            }
            old = (igObject *)arg0->_dataList;
            if (old != 0) {
                old->_refCount = old->_refCount - 1;
                if ((old->_refCount & 0x7FFFFF) == 0) {
                    igObject_Destroy(old);
                    ;
                }
            }
            arg0->_dataList = (int)p;
        }
    }
    return ((int)igProperty_FindByName(arg0->_dataList, g_propertyNameField[0], arg1)) != 0;
}

/* Owning stack reference to the freshly created property list; released on scope exit once the ram
 * holds its own reference (reference count in the low 23 bits of _refCount). */

/* matching construct: the (igObject *)/(int) casts on _dataList stand in for a 4-byte reference field */
int FUN_003a7e90(beAction2InfoRam *arg0, int arg1) {
    if (arg0->_dataList == 0) {
        int al;
        igObject *o;
        al = igObject_GetAllocator(arg0);
        al = GPR_00554c14 != 0 ? al : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
        igSmartPointer<igObject> created(beBaseInfoDataList_Create(al));
        igObject *s0 = created.p;
        if (s0 != 0) {
            s0->_refCount = s0->_refCount + 1;
        }
        o = (igObject *)arg0->_dataList;
        if (o != 0) {
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        arg0->_dataList = (int)s0;
    }
    {
        P *p = ((P *)igProperty_FindByName((igObject *)arg0->_dataList, g_propertyNameField[0], arg1));
        if (p == 0) {
            return 1;
        }
        long long t = p->f32;
        return t < FUN_003a7fd0((beBaseInfoRam *)arg0, arg1);
    }
}

long long FUN_003a7fd0(beBaseInfoRam *arg0, int arg1) {
    beBaseInfoRamTimer *temp_s0;
    if (arg0->_dataList == 0) {
        int base = igObject_GetAllocator();
        int var_v0;
        if (GPR_00554c14 != 0) {
            var_v0 = base;
        } else {
            var_v0 = Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
        }
        igSmartPointer<igObject> sp4C((igObject *)((void *)beBaseInfoDataList_Create(var_v0)));
        igObject *o = sp4C.p;
        if (o != 0) {
            o->_refCount = (int)o->_refCount + 1;
        }
        igObject *temp_a0 = (igObject *)arg0->_dataList;
        if (temp_a0 != 0) {
            temp_a0->_refCount = (int)temp_a0->_refCount - 1;
            if (((unsigned long long)((long long)(int)temp_a0->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        arg0->_dataList = (int)o;
    }
    temp_s0 = igProperty_FindByName(arg0->_dataList, g_propertyNameField[0], arg1);
    int temp_v0 = (int)(((igInsightCore *)((beBaseInfoManager *)arg0->_parentManager)->_insight)->_worldTime >> 0x12);
    float var_f12 = (float)(unsigned int)temp_v0;
    var_f12 = var_f12 * temp_s0->_timeScale;
    long long sh = __fixsfdi(var_f12);
    return (sh << 0x12) + temp_s0->_timeBias;
}

float FUN_003a8140(A_3a8140 *arg0, int arg1) {
    Prop *temp_v0;
    long long temp_s0;
    long long temp_v0_2;
    float var_f0;
    if (arg0->_dataList == 0) {
        int base = igObject_GetAllocator();
        int var_v0;
        if (GPR_00554c14 != 0) {
            var_v0 = base;
        } else {
            var_v0 = Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
        }
        igSmartPointer<igObject> sp5C((Rc *)((void *)beBaseInfoDataList_Create(var_v0)));
        Rc *o = sp5C.p;
        if (o != 0) {
            o->_refCount = o->_refCount + 1;
        }
        Rc *temp_a0 = (Rc *)arg0->_dataList;
        if (temp_a0 != 0) {
            temp_a0->_refCount = temp_a0->_refCount - 1;
            if (((unsigned long long)((long long)(int)temp_a0->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        arg0->_dataList = (int)o;
    }
    temp_v0 = ((Prop *)igProperty_FindByName(arg0->_dataList, g_propertyNameField[0], arg1));
    temp_s0 = ((igInsightCore *)((beAction2 *)arg0->_parentManager)->_insight)->_worldTime;
    if (temp_s0 != temp_v0->f40) {
        temp_v0_2 = FUN_003a7fd0((beBaseInfoRam *)arg0, arg1);
        long long d = temp_v0_2 - temp_v0->f48;
        if (d != 0) {
            var_f0 = __floatdisf(d) / 1.6666667e7f;
            if (!(var_f0 <= 3.0f)) {
                var_f0 = 3.0f;
            }
            temp_v0->f56 = var_f0;
            temp_v0->f48 = temp_v0_2;
        } else {
            temp_v0->f56 = 0.0f;
        }
        temp_v0->f40 = temp_s0;
    }
    return temp_v0->f56;
}

/* Owning stack reference to the freshly created data list; released on scope exit (reference count
 * in the low 23 bits of _refCount). */

void FUN_003a82f0(beBaseInfoRam *arg0, int arg1, float fparg0) {
    beBaseInfoRamTimer *prop;
    float scale;
    float cur;
    long long b;
    long long r;

    if (arg0->_dataList == 0) {
        int a = igObject_GetAllocator(arg0);
        igSmartPointer<igObject> created(beBaseInfoDataList_Create(GPR_00554c14 != 0 ? a : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0])));
        igObject *p = created.p;
        if (p != 0) {
            p->_refCount = p->_refCount + 1;
        }
        igObject *old = (igObject *)arg0->_dataList;
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if ((old->_refCount & 0x7fffff) == 0) {
                igObject_Destroy(old);
            }
        }
        arg0->_dataList = (int)p;
    }
    prop = igProperty_FindByName(arg0->_dataList, g_propertyNameField[0], arg1);
    cur = prop->_timeScale;
    if (fparg0 != cur) {
        scale = (float)(unsigned int)(int)(((igInsightCore *)((beBaseInfoManager *)arg0->_parentManager)->_insight)->_worldTime >> 0x12);
        r = __fixsfdi(scale * cur);
        r <<= 0x12;
        r += prop->_timeBias;
        b = r;
        b -= __fixsfdi(scale * fparg0) << 0x12;
        prop->_timeBias = b;
        prop->_timeScale = fparg0;
        prop->_keikaFrame = 0.0f;
    }
}

void FUN_003a84a0(beBaseInfoRam *t, float f) {
    int n;
    int i;
    int s1;
    int *a1;
    E *e;
    if (t->_dataList != 0) {
        n = ((beBaseInfoDataList *)t->_dataList)->_count;
        i = 0;
        if (0 < n) {
            do {
                s1 = g_beBaseInfoRamTimer_metaObject[0];
                e = ((E **)((beBaseInfoDataList *)t->_dataList)->_data)[i];
                if (s1 == e->v20()) {
                    a1 = (int *)((beBaseInfoData *)e)->_name;
                    a1 = a1 != 0 ? a1 : &emptyString[0];
                    FUN_003a82f0((beBaseInfoRam *)t, (int)a1, f);
                }
                i++;
            } while (i < n);
        }
    }
}

void FUN_003a8580(beBaseInfoRam *self, char *name) {
    igTDataList<igObject *> *l1;
    int idx;
    igObject *found;
    igObject *obj;
    igObject *cur;
    igObject *old;
    void *alloc;
    if (self->_dataList != 0) {
        if (self->_dataList == 0) {
            alloc = ((void *)igObject_GetAllocator(self));
            alloc = GPR_00554c14 ? alloc : ((void *)Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]));
            igSmartPointer<igObject> h(beBaseInfoDataList_Create(alloc));
            cur = h.p;
            if (cur != 0) cur->_refCount = cur->_refCount + 1;
            old = (igObject *)self->_dataList;
            if (old != 0) { old->_refCount = old->_refCount - 1; if ((old->_refCount & 0x7fffff) == 0) igObject_Destroy(old); }
            self->_dataList = (int)cur;
        }
        found = ((igObject *)igProperty_FindByName((void *)self->_dataList, g_propertyNameField[0], name));
        if (found != 0) {
            l1 = (igTDataList<igObject *> *)self->_dataList;
            idx = l1->find(found);
            l1 = (igTDataList<igObject *> *)self->_dataList;
            obj = l1->_data[idx];
            if (obj != 0) { obj->_refCount = obj->_refCount - 1; if ((obj->_refCount & 0x7fffff) == 0) igObject_Destroy(obj); }
            List_RemoveWordAt(l1, idx);
            l1->_data[l1->_count] = 0;
        }
    }
}

static inline int countOf(const igObjectList *l) { return l->_count; }

void FUN_003a8760(beBaseInfoRam *arg0) {
    int temp_s1;
    int var_s3;
    int var_s2;
    igObjectList *temp_s1_2;
    int temp_s0;
    int temp_a1;
    void **temp_a0;
    Rc_3a8760 *temp_a0_2;
    igObjectList *temp_a0_3;
    igObjectList *temp_v1;

    temp_v1 = ((igObjectList *)arg0->_dataList);
    if (temp_v1 != 0) {
        var_s3 = temp_v1->_count;
        var_s2 = 0;
        if (var_s3 > 0) {
            do {
                temp_s0 = var_s2 * 4;
                temp_a0 = (void **)(*(int *)(((igObjectList *)arg0->_dataList)->_data + temp_s0));
                temp_s1 = g_beBaseInfoRamTimer_metaObject[0];
                if (temp_s1 == ((DW4VC_88_0 *)(temp_a0))->vX()) {
                    temp_s1_2 = ((igObjectList *)arg0->_dataList);
                    temp_a0_2 = (Rc_3a8760 *)*(int *)(temp_s1_2->_data + temp_s0);
                    if (temp_a0_2 != 0) {
                        temp_a0_2->rc = temp_a0_2->rc - 1;
                        if ((temp_a0_2->rc & 0x7FFFFF) == 0) {
                            igObject_Destroy(temp_a0_2);
                        }
                    }
                    List_RemoveWordAt(temp_s1_2, var_s2);
                    var_s3 -= 1;
                    var_s2 -= 1;
                    *(int *)(temp_s1_2->_data + (temp_s1_2->_count * 4)) = 0;
                }
                var_s2 += 1;
            } while (var_s2 < var_s3);
        }
        temp_a0_3 = ((igObjectList *)arg0->_dataList);
        temp_a1 = temp_a0_3->_count;
        if (temp_a1 >= countOf(temp_a0_3)) {
            List_Reserve(temp_a0_3, temp_a1, 4);
        }
    }
}

void Gap__Bec__beMovie__vfunc_32(beMovie *arg0) {
    RefObj *temp_a0;
    RefObj *temp_v0;

    temp_v0 = (RefObj *)(FUN_00236f80(arg0->_insight, g_igMovieManager_metaObject[0]));
    if (temp_v0 != 0) {
        temp_v0->f4 = (int)((int) (temp_v0->f4 + 1));
    }
    temp_a0 = (RefObj *)(arg0->_movie);
    if (temp_a0 != 0) {
        temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
        if (((unsigned long long) ((long long) temp_a0->f4 << 0x29) >> 0x29) == 0) {
            igObject_Destroy((void *)temp_a0);
        }
    }
    arg0->_movie = (int)(temp_v0);
}

void Gap__Bec__beMovie__vfunc_29(beMovie * p0, int p1, char * p2, int p3, int p4)
{
    beMessenger_RegisterReceiver(p0->_messenger, p1, DAT_00510200, 0, -1);
}

int Gap__Bec__beMovie__vfunc_30(void)
{
    return g_beMovieInfo_metaObject[0];
}

void Gap__Bec__beMovie__vfunc_31(beMovie *self, MovieInfoArg *arg1) {
    int *pad; int flags; MovieVirtual *o; bool ok; int h; ItemPtrList *l; int i; beMovieInfoData *it; int *name;
    int *t; int ref; int *hdr; int cnt; int off;
    if ((int *)self->_playingName != 0) {
        pad = bePadManager_GetPadForPlayer(((int)FUN_00236f80(self->_insight, g_bePadManager_metaObject[0])), 0);
        flags = pad[18];
        if ((flags & 8) || (flags & 0x4000)) {
            o = (MovieVirtual *)self->_movie;
            if (o != 0) o->v26();
        }
        o = (MovieVirtual *)self->_movie;
        ok = false;
        if (o != 0) {
            if (o->v30((int *)self->_playingName) == 2) ok = true;
        } else ok = true;
        if (ok) {
            h = ((int)FUN_00236f80(self->_insight, g_beLua_metaObject[0]));
            l = arg1->inner->list;
            for (i = 0; i < l->count; i++) {
                it = (beMovieInfoData *)l->items[i];
                if (it != 0 && igObject_IsKindOf(it, g_beMovieInfoData_metaObject[0]) != 0) { it = (beMovieInfoData *)it; } else it = 0;
                if (it == 0) goto done;
                name = (int *)it->_name;
                if (name != 0) { name = (int *)name; } else name = emptyString;
                if (strcmp((int *)self->_playingName, name) == 0) {
                    beLua__RunNamedChunk(h, it->_callLuaName, 0);
                    break;
                }
            }
block25: /* matching construct: unreferenced label kept from the matching draft */
            if (g_stringPool[0] == 0) {
                ref = FUN_002eb010(16);
                if (ref) ref = StringPool_Construct(ref);
                g_stringPool[0] = ref;
            }
            ref = StringPool_Intern(g_stringPool[0], 0);
            t = (int *)self->_playingName;
            if (t) {
                hdr = t - 2;
                cnt = t[-1] - 1;
                t[-1] = cnt;
                if (cnt == 0) StringChunk_ReleaseHeader(*hdr, hdr);
            }
            self->_playingName = ref;
        }
    }
done:;
}

O_3a9190 *FUN_003a9190(O_3a9190 *arg0, short arg1) {
    if (arg0) {
        S_temp_a0 *t = arg0->m;
        if (t) { t->f4 -= 1; if ((t->f4 & 0x7fffff) == 0) igObject_Destroy(t); }
        if (arg1 > 0) FUN_00100610(arg0);
    }
    return arg0;
}

int Gap__Bec__beMovie__vfunc_20(void)
{
    return g_beMovie_metaObject[0];
}
