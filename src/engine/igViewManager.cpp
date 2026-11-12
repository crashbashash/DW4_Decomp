#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"
#include "dw4/ViewerSetup.h"

extern "C" {

int FUN_002377c0(...);
int FUN_00462ac0(...);
int FUN_002370c0(...);

int FUN_00100610(...);

extern "C" int FUN_00236b10(void *, void *);

int FUN_00236f30(...);


int FUN_00236ca0(int);
int FUN_002371f0(int);
int FUN_00237530(int);

int FUN_00236e80(int);
int FUN_00237280(int);
int FUN_002376b0(int);

struct Vobj {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
    virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35(); virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
    virtual void v40(); virtual int v41();
};
struct L4 { char pad[180]; unsigned char b180; };
struct L2 { char pad[12]; L4 *p12; };
struct L1 { char pad[44]; L2 *p44; };
struct B { char pad[16]; long long ll16; };
struct S {
    igInsightCore *a; L1 *p4; char pad8[8]; unsigned char f16; char pad17[3]; B *b20; Vobj *c24;
};
extern "C" void FUN_00237730(igInsightCore *);

int FUN_00457e90(...);

typedef struct R { int w0; int refs; } R;
typedef struct S2 { char pad[8]; R *obj; int f12; } S2;

class ViewerClock {
public:
    virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void slot3(); virtual void slot4(); virtual void slot5(); virtual void slot6(); virtual void slot7(); virtual void slot8(); virtual void slot9(); virtual void slot10(); virtual void slot11(); virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15(); virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19(); virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23(); virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
    virtual void setSeconds(float seconds);
};
struct ViewerViewManager { int _vtable; unsigned int _refCount; ViewerClock *clock; };
void FUN_00464080(ViewerViewManager *manager, long long frameTime);

int FUN_004578c0(...);

extern int DAT_0058cd80[4];

int Gap__Viewer__igViewManager__vfunc_23(void *arg0);
class DW4VC_100_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int vX(); };

int FUN_001007e0(...);
int FUN_00238110(...);
int FUN_00464170(...);
int StringChunk_ReleaseHeader(...);

extern int DAT_0058cd48[4];
extern int DAT_0058cd50[4];
extern int DAT_0058cd58[4];
typedef struct Obj { char p[80]; float f80; float f84; float f88; } Obj;
typedef struct Arg { char p[12]; Obj *o; } Arg;
typedef struct Rec { int t; int z; int v; } Rec;
typedef struct Frame {
    void *f0;
    char pad[60];
    float f64;
    unsigned char b68;
    char pad2[3];
    float f72;
    float f76;
    char pad3[133];
    unsigned char f213;
    char pad4[2];
    unsigned char f216;
    char pad5[15];
    int f232;
    void *f236;
} Frame;
extern Frame *DAT_0056dc50[4];

int Gap__Viewer__igViewManager__vfunc_24(void *arg0);
class DW4VC_104_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual int vX(); };

int Gap__Viewer__igViewManager__vfunc_25(void *arg0);
class DW4VC_108_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual int vX(); };

typedef struct ViewModelEvent {
    int type;
    int arg;
    int data;
} ViewModelEvent;
extern int DAT_0058cd40;
extern int g_igViewManager_metaObject[4];
int FUN_003082b0(...);
void igMatrix44f_SetIdentity(float *);
int FUN_00191f30(int *, float *, float *);
extern unsigned char GPR_00554e7c;
extern unsigned char GPR_00554e80;
class V { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void vX(int, int, float, float); };
struct O2 { char p[8]; V *o; };
class DW4VC_116_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual int vX(); };

igObject *FUN_00459340(int);
igObject *FUN_0045e230(int);
igObject *FUN_0045be30(int);
igObject *FUN_0045dbe0(int);
int FUN_00237020(...);
int FUN_00236ee0(...);
int FUN_00236ab0(...);
int FUN_002eb010(...);
int StringPool_Construct(...);
void *StringPool_Intern(...);
int igNamedObject_SetName(...);
extern int g_stringPool[4];

static inline void releaseString(void *p) {
    if (p != 0) {
        int *h = (int *)((char *)p - 8);
        int rc = *(int *)((char *)p - 4) - 1;
        *(int *)((char *)p - 4) = rc;
        if (rc == 0) StringChunk_ReleaseHeader(*h, h);
    }
}

static inline void *intern(const char *s) {
    if (s == 0) return 0;
    if (g_stringPool[0] == 0) {
        int pool = FUN_002eb010(16);
        if (pool != 0) pool = StringPool_Construct(pool);
        g_stringPool[0] = pool;
    }
    return StringPool_Intern(g_stringPool[0], s);
}

struct StringRef {
    void *p;
    ~StringRef() { releaseString(p); }
};

InsightCore *FUN_00232800(int);

ViewerSetup::ViewerSetup(igObject *w)
    : core(FUN_00232800(0), AdoptReference()), sceneInfo(FUN_00459340(0), AdoptReference()),
      actors(FUN_0045e230(0), AdoptReference()), dataPump(FUN_0045be30(0), AdoptReference()), showLogo(1),
      logo(FUN_0045dbe0(0), AdoptReference()), window(w, kRetainReference) {
    igObject *next = window.p;
    if (next != 0) {
        InsightCore *c = core.p;
        c->window = next;
        if (DAT_0056dc50[0] == 0) {
            Frame *f = (Frame *)FUN_001007e0(240);
            if (f != 0) f = (Frame *)FUN_00238110(f);
            DAT_0056dc50[0] = f;
        }
        DAT_0056dc50[0]->f232 = DAT_0056dc50[0]->f232 + 1;
        {
            Frame *g = DAT_0056dc50[0];
            showLogo = g->f213 != 0 && !(g->f216 != 0);
        }
        if (DAT_0056dc50[0] != 0) {
            if (--DAT_0056dc50[0]->f232 <= 0) {
                Frame *s1 = DAT_0056dc50[0];
                if (s1 != 0) {
                    if (&s1->f236) releaseString(s1->f236);
                    if (s1 != 0) releaseString(s1->f0);
                    FUN_00100610(s1);
                }
                DAT_0056dc50[0] = 0;
            }
        }
        if (showLogo) {
            StringRef scenes;
            StringRef overlays;
            scenes.p = intern("Scenes done");
            overlays.p = intern("Overlays done");
            FUN_00237020(core.p, scenes.p, logo.p);
            FUN_00237020(core.p, logo.p, overlays.p);
            FUN_00236ee0(core.p, logo.p);
        }
        FUN_00236ab0(core.p, sceneInfo.p);
        FUN_00236ab0(core.p, dataPump.p);
        igNamedObject_SetName(actors.p, "Actor manager");
        FUN_00236ab0(core.p, actors.p);
    }
}

ViewerSetup::~ViewerSetup() {
    if (window.p != 0) {
        FUN_00236b10(core.p, dataPump.p);
        FUN_00236b10(core.p, actors.p);
        FUN_00236b10(core.p, sceneInfo.p);
        if (showLogo != 0) {
            FUN_00236f30(core.p, logo.p);
        }
    }
}

void FUN_00463b30(int *arg0) {
    FUN_00237530(*arg0);
    FUN_00236ca0(*arg0);
    FUN_002371f0(*arg0);
}

void FUN_00463b70(int *arg0) {
    FUN_00237280(*arg0);
    FUN_00236e80(*arg0);
    FUN_002376b0(*arg0);
}

int FUN_00463bb0(int *p)
{
    return FUN_002377c0(*(int *)((char *)p + 0));
}

extern "C" int FUN_00463bc0(S *s) {
    FUN_00237730(s->a);
    if (s->f16) {
        igInsightCore *t = s->a;
        long long v = t->_currentTime;
        if (v > 4000000000LL) {
            FUN_00236f30(t, s->b20);
            s->f16 = 0;
        } else {
            s->b20->ll16 = v;
        }
    }
    int r = (s->p4->p44->p12->b180 != 0) ^ 1;
    if (r) {
        r = s->c24->v41() != 0;
    }
    return r;
}

int FUN_00463c70(int *p)
{
    return FUN_00462ac0(*(int *)((char *)p + 4));
}

int FUN_00463c80(int *p)
{
    return FUN_002370c0(*(int *)((char *)p + 0));
}

void FUN_00463fd0(S2 *arg0, R *arg1) {
    R *temp_a0;
    R *temp_a0_2;

    temp_a0 = arg0->obj;
    if (temp_a0 != 0) {
        FUN_00457e90(temp_a0, 0);
    }
    if (arg1 != 0) {
        arg1->refs = arg1->refs + 1;
    }
    temp_a0_2 = arg0->obj;
    if (temp_a0_2 != 0) {
        temp_a0_2->refs = temp_a0_2->refs - 1;
        if (((unsigned long long)((long long)temp_a0_2->refs << 0x29) >> 0x29) == 0) {
            igObject_Destroy(temp_a0_2);
        }
    }
    arg0->obj = arg1;
    if (arg1 != 0) {
        FUN_00457e90(arg1, arg0->f12);
    }
}

void FUN_00464080(ViewerViewManager *manager, long long frameTime) {
    int units = frameTime / 0x40000; manager->clock->setSeconds(262144.0f * (1e-9f * units));
}

void FUN_00464100(void) {

}

void FUN_00464110(void *arg0, void *arg1) {
    int buf[3];
    void *temp_v1;

    temp_v1 = (void *)(*(int *)((char *)(arg0) + 12));
    *(float *)((char *)(temp_v1) + 140) = *(float *)((char *)(arg1) + 0);
    *(float *)((char *)(temp_v1) + 144) = *(float *)((char *)(arg1) + 4);
    *(float *)((char *)(temp_v1) + 148) = *(float *)((char *)(arg1) + 8);
    buf[0] = 2;
    buf[1] = 0;
    buf[2] = DAT_0058cd80[0];
    FUN_004578c0(*(int *)((char *)(arg0) + 12), buf);
}

int Gap__Viewer__igViewManager__vfunc_23(void *arg0) {
    void **temp_a0;

    temp_a0 = (void **)(*(int *)((char *)(arg0) + 8));
    ((DW4VC_100_0 *)(temp_a0))->vX();
    return 1;
}

void FUN_00464540(Arg *arg0, int arg1) {
    int sp60[3];
    float sp6C;
    Rec r1;
    Rec r2;
    Rec r3;
    Frame *s0;
    Frame *f;
    void *p;
    int *h;
    int rc;
    FUN_00464170(arg1, sp60, &sp6C, 1, -1);
    if (DAT_0056dc50[0] == 0) {
        f = (Frame *)FUN_001007e0(240);
        if (f != 0) f = (Frame *)FUN_00238110(f);
        DAT_0056dc50[0] = f;
    }
    DAT_0056dc50[0]->f232 = DAT_0056dc50[0]->f232 + 1;
    s0 = DAT_0056dc50[0];
    if (!(sp6C <= 0.0f) && s0->b68 != 0) {
        arg0->o->f84 = sp6C / 100.0f;
        arg0->o->f88 = 3.0f * sp6C;
    } else {
        arg0->o->f84 = s0->f72;
        arg0->o->f88 = s0->f76;
    }
    r1.z = 0;
    r1.t = 2;
    r1.v = DAT_0058cd50[0];
    FUN_004578c0(arg0->o, &r1);
    r2.t = 2;
    r2.z = 0;
    r2.v = DAT_0058cd58[0];
    FUN_004578c0(arg0->o, &r2);
    arg0->o->f80 = s0->f64;
    r3.t = 2;
    r3.z = 0;
    r3.v = DAT_0058cd48[0];
    FUN_004578c0(arg0->o, &r3);
    if (DAT_0056dc50[0] != 0) {
        if (--DAT_0056dc50[0]->f232 <= 0) {
            f = DAT_0056dc50[0];
            if (f != 0) {
                if (&f->f236) {
                    p = f->f236;
                    if (p != 0) {
                        h = (int *)((char *)(p) - 8);
                        rc = *(int *)((char *)(p) - 4) - 1;
                        *(int *)((char *)(p) - 4) = rc;
                        if (rc == 0) {
                            StringChunk_ReleaseHeader(*h, h);
                        }
                    }
                }
                if (f != 0) {
                    p = f->f0;
                    if (p != 0) {
                        h = (int *)((char *)(p) - 8);
                        rc = *(int *)((char *)(p) - 4) - 1;
                        *(int *)((char *)(p) - 4) = rc;
                        if (rc == 0) {
                            StringChunk_ReleaseHeader(*h, h);
                        }
                    }
                }
                FUN_00100610(f);
            }
            DAT_0056dc50[0] = 0;
        }
    }
}

int Gap__Viewer__igViewManager__vfunc_24(void *arg0) {
    void **temp_a0;

    temp_a0 = (void **)(*(int *)((char *)(arg0) + 8));
    ((DW4VC_104_0 *)(temp_a0))->vX();
    return 1;
}

int Gap__Viewer__igViewManager__vfunc_25(void *arg0) {
    void **temp_a0;

    temp_a0 = (void **)(*(int *)((char *)(arg0) + 8));
    ((DW4VC_108_0 *)(temp_a0))->vX();
    return 1;
}

static void FUN_00464af0(float *arg0, float *arg1, float fparg0) {
    float temp_f1;
    float temp_f1_2;

    temp_f1 = *arg0;
    if (!(temp_f1 <= fparg0)) {
        *arg0 = temp_f1 - fparg0;
    } else if (temp_f1 < -fparg0) {
        *arg0 = temp_f1 + fparg0;
    } else {
        *arg0 = 0.0f;
    }
    temp_f1_2 = *arg1;
    if (!(temp_f1_2 <= fparg0)) {
        *arg1 = temp_f1_2 - fparg0;
        return;
    }
    if (temp_f1_2 < -fparg0) {
        *arg1 = temp_f1_2 + fparg0;
        return;
    }
    *arg1 = 0.0f;
}

int Gap__Viewer__igViewManager__vfunc_26(O2 *self, int x, int y, float f0, float f1) {
    float sp1C;
    float sp18;
    sp18 = f0;
    sp1C = f1;
    FUN_00464af0(&sp18, &sp1C, 0.3f);
    self->o->vX(x, y, sp18, sp1C);
    return 1;
}

int Gap__Viewer__igViewManager__vfunc_27(void *arg0) {
    void **temp_a0;

    temp_a0 = (void **)(*(int *)((char *)(arg0) + 8));
    ((DW4VC_116_0 *)(temp_a0))->vX();
    return 1;
}

int Gap__Viewer__igViewManager__vfunc_32(igViewManager *self, int width, int height)
{
    ViewModelEvent event;

    ((igViewModel *)self->_viewModel)->_ratio = (float)width / (float)height;
    event.type = 2;
    event.arg = 0;
    event.data = DAT_0058cd40;
    FUN_004578c0((igViewModel *)self->_viewModel, &event);
    return 0;
}

void FUN_00464c60(igViewManager *self) {
    float inverse[16];
    int status;
    float *m;
    int r;

    m = ((igViewModel *)self->_viewModel)->_viewMatrix;
    if (GPR_00554e7c == 0) {
        r = FUN_003082b0("current view matrix :\n%.8f,\t%.8f,\t%.8f,\t%.8f,\n%.8f,\t%.8f,\t%.8f,\t%.8f,\n%.8f,\t%.8f,\t%.8f,\t%.8f,\n%.8f,\t%.8f,\t%.8f,\t%.8f\n",
                         m[0], m[1], m[2], m[3], m[4], m[5], m[6], m[7],
                         m[8], m[9], m[10], m[11], m[12], m[13], m[14], m[15]);
        if (r != 1 && r == 2) GPR_00554e7c = 1;
    }
    igMatrix44f_SetIdentity(inverse);
    FUN_00191f30(&status, inverse, ((igViewModel *)self->_viewModel)->_viewMatrix);
    m = inverse;
    if (GPR_00554e80 == 0) {
        r = FUN_003082b0("current inverse view matrix :\n%.8f,\t%.8f,\t%.8f,\t%.8f,\n%.8f,\t%.8f,\t%.8f,\t%.8f,\n%.8f,\t%.8f,\t%.8f,\t%.8f,\n%.8f,\t%.8f,\t%.8f,\t%.8f\n",
                         m[0], m[1], m[2], m[3], m[4], m[5], m[6], m[7],
                         m[8], m[9], m[10], m[11], m[12], m[13], m[14], m[15]);
        if (r != 1 && r == 2) GPR_00554e80 = 1;
    }
}

void Gap__Viewer__igViewManager__vfunc_13(int *a) { FUN_00457e90(a[2], a[3]); }

int Gap__Viewer__igViewManager__vfunc_22(void) {
    return g_igViewManager_metaObject[0];
}

}
