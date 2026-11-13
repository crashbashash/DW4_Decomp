#include "dw4/igSmartPointer.h"
#include "dw4/reflected.h"
#include "dw4/DisableFeature.h"

extern "C" {

class X { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int v88(); int pad[4]; int f20; };

int igObject_IsKindOf(...);

extern int g_igTransform_metaObject[4];
extern int g_igLightSet_metaObject[4];
extern int g_igGroup_metaObject[4];
int FUN_0045f200(int arg0, X *arg1);

typedef struct T { char pad[60]; unsigned char f60; } T;
typedef struct L { char pad[8]; int f8; int pad2; int *f16; } L;
typedef struct C { char pad[192]; unsigned char f192; } C;
typedef struct A { char pad[12]; C *f12; char pad2[24]; int f40; char pad3[20]; L *f64; char pad4[12]; struct { char pad[52]; T *f52; } *f80; } A;

int FUN_001b06f0(...);

typedef struct T3 { char pad60[60]; unsigned char f3c; } T3;
typedef struct T2 { char pad52[52]; T3 *f34; } T2;
typedef struct T1 { char pad192[192]; unsigned char fc0; } T1;
typedef struct L2 { char pad8[8]; int cnt; char pad12[4]; int *arr; } L2;
typedef struct S { char pad12[12]; T1 *f0c; char pad16[24]; int f28; char pad44[20]; L2 *f40; char pad68[12]; T2 *f50; } S;

int igAttrStackManager_PopLightStateAttr(...);

struct Rc { int vt; int rc; };
class V { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int v25(int); virtual void d24(); virtual int v27(long long); virtual void d26(); virtual void d27(); virtual Rc *v30(); virtual void v31(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual void d101(); virtual void d102(); virtual void d103(); virtual void d104(); virtual void d105(); virtual void d106(); virtual void d107(); virtual void d108(); virtual void d109(); virtual void d110(); virtual void d111(); virtual void d112(); virtual void d113(); virtual void d114(); virtual void d115(); virtual void d116(); virtual void d117(); virtual void d118(); virtual void d119(); virtual void d120(); virtual void d121(); virtual void d122(); virtual void d123(); virtual void d124(); virtual void d125(); virtual void d126(); virtual void d127(); virtual void d128(); virtual void d129(); virtual void d130(); virtual void d131(); virtual void d132(); virtual void d133(); virtual void d134(); virtual void d135(); virtual void d136(); virtual void d137(); virtual void d138(); virtual void d139(); virtual void d140(); virtual void d141(); virtual void d142(); virtual void d143(); virtual void d144(); virtual void d145(); virtual void d146(); virtual void d147(); virtual void d148(); virtual void d149(); virtual void d150(); virtual void d151(); virtual void d152(); virtual void d153(); virtual void d154(); virtual void d155(); virtual void d156(); virtual void d157(); virtual void d158(); virtual void d159(); virtual void d160(); virtual void d161(); virtual void d162(); virtual void d163(); virtual void d164(); virtual void d165(); virtual void d166(); virtual void d167(); virtual void d168(); virtual void d169(); virtual void d170(); virtual void d171(); virtual void d172(); virtual void d173(); virtual void d174(); virtual void d175(); virtual void d176(); virtual void d177(); virtual void d178(); virtual void d179(); virtual void d180(); virtual void d181(); virtual void d182(); virtual void d183(); virtual void d184(); virtual void d185(); virtual void d186(); virtual void d187(); virtual void d188(); virtual void d189(); virtual void d190(); virtual void d191(); virtual void d192(); virtual void d193(); virtual void d194(); virtual void d195(); virtual void d196(); virtual void d197(); virtual void d198(); virtual void d199(); virtual void d200(); virtual int v203(int, int); virtual void d202(); virtual void d203(); virtual void d204(); virtual void d205(); virtual void d206(); virtual void d207(); virtual void d208(); virtual void d209(); virtual void d210(); virtual int v213(int); };
struct B { char pad0[12]; int f12; char pad16[28]; int f44; char pad48[60]; int f108; char pad112[64]; long long f176; };
struct Q { char pad0[8]; V *f8; B *f12; char pad16[28]; int f44; char pad48[20]; unsigned char f68; char pad69[3]; V *f72; Rc *f76; V *f80; Rc *f84; };

void igObject_Destroy(void *);

void Gap__Viewer__igViewerRenderer__vfunc_25(Q *arg0);

class V2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void *v104(void *); virtual void d25(); virtual void v112(int); };
struct Q2 { char pad8[8]; V2 *f8; char pad12[60]; V2 *f72; char pad76[4]; V2 *f80; char pad84[4]; Rc *f88; };
void igViewerRenderer_UpdateProjection(igViewerRenderer *arg0);
struct CameraLink;
void igViewerRenderer_UpdateViewMatrix(CameraLink *arg0);
struct FogOwner;
void igViewerRenderer_UpdateSorting(struct FogOwner *arg0);
struct LightOwner;
void igViewerRenderer_UpdateScene(LightOwner *arg0);
void igViewerRenderer_UpdateLighting(igViewerRenderer *arg0);
struct OptionPanelView;
void igViewerRenderer_UpdateRenderStates(OptionPanelView *arg0);
extern int text_igDisableExt[4];
void Gap__Viewer__igViewerRenderer__vfunc_23(Q2 *arg0);

int __dl__FPv(...);
void *__nw__FUi(...);
void *ViewerOptions_Construct(...);
int igModel_NotifyViews(...);
int StringChunk_ReleaseHeader(...);

extern int DAT_0058ca58[4];
extern int DAT_0058ca60[4];
extern int DAT_0058ca68[4];
extern int DAT_0058ca70[4];
extern int DAT_0058ca78[4];
extern int DAT_0058ca80[4];
extern int DAT_0058ca88[4];
extern int DAT_0058ca90[4];
extern int DAT_0058ca98[4];
extern int DAT_0058caa0[4];
extern int DAT_0058caa8[4];
extern int DAT_0058ca38[4];
extern int DAT_0058ca40[4];
extern int DAT_0058ca48[4];
extern int DAT_0058ca50[4];
typedef struct Frame {
    void *f0;
    char pad[88];
    unsigned char f92; unsigned char f93; unsigned char f94; unsigned char f95; unsigned char f96;
    char pad2[3];
    float eye[8];
    float center[8];
    unsigned char f164; unsigned char f165; unsigned char f166; unsigned char f167; unsigned char f168; unsigned char f169;
    char pad3[2];
    float range;
    char pad176[56];
    int f232;
    void *f236;
} Frame;
typedef struct Sub { char pad[8]; int f8; } Sub;
typedef struct W { char pad[184]; unsigned char f184; unsigned char f185; unsigned char f186; unsigned char f187; int f188; unsigned char f192; unsigned char f193; unsigned char f194; unsigned char f195; unsigned char f196; unsigned char f197; unsigned char f198; unsigned char f199; unsigned char f200; unsigned char f201; unsigned char f202; } W;
typedef struct Arg { char pad[12]; W *f12; char pad2[44]; Sub *f60; } Arg;
extern Frame *DAT_0056dc50[4];

struct V4 { float a, b, c, d; };
class A2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void vX(V4 *); };
class B2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void v128(int); virtual void v132(float); };
class C2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void v128(void *); virtual void v132(void *); virtual void v136(void *); virtual void d33(); virtual void v144(void *); char pad[8]; int f12; char pad2[128]; char b144; };
struct N { char pad[28]; int f28; };
struct Q3 { char pad[16]; igObject *f16; };
struct Z { char pad[8]; char b8; char pad1[3]; int f12; char pad2[8]; char b24; };
struct Y { char pad[24]; char b24; };
struct P { char pad[16]; int f16; int f20; int f24; int f28; int f32; C2 *f36; Q3 *f40; int f44; int f48; int f52; N *f56; char pad3[12]; Z *f72; int pad4; igObject *f80; };
void *igColorAttr_CreateInstance(...);
void *FUN_0013b490(...);
void *FUN_0019fde0(...);
int FUN_001c5160(void *, float);

int igGroup_AppendChild(...);

void FUN_00460e00(int *a, void *arg1);

int ObjectList_AppendRetained(...);

extern float g_vec3ZAxis[4];
extern float DAT_004e109c[4];
extern float DAT_004e10a0[4];
extern int g_vec4Zero[4];
void Gap__Viewer__igViewerRenderer__vfunc_13(P *arg0);
struct Tag { };
static inline void *createFirst() {
    Tag tag = Tag();
    return igColorAttr_CreateInstance(0);
}
static inline void *createSecond() {
    Tag tag = Tag();
    return FUN_0013b490(0);
}
static inline void *createThird() {
    Tag tag = Tag();
    return FUN_0019fde0(0, 1);
}

extern int g_igViewportAttr_metaObject[4];
int FUN_001b0000(int, int, int, int);

int FUN_001b6ce0(void *, float, float, float, float, float);

int igMatrix44f_Copy(...);

extern int DAT_0058ca20[4];

class E { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual int vX(int); };
struct CameraLink { char pad[12]; int f12; char pad1[36]; E *f52; char pad2[16]; int f72; int f76; int f80; };
int FUN_001b6ee0(int, int *);

struct FogAttr { char pad[12]; int f12; char pad2[60]; int f76; };
struct FogHolder { char pad[68]; struct FogAttr *f68; };
struct FogConfig { char pad[184]; unsigned char b184; unsigned char b185; unsigned char b186; char p; int f188; };
struct FogOwner { char pad[12]; struct FogConfig *f12; char pad2[64]; struct FogHolder *f80; };

typedef struct Obj : public igObject { } Obj;
typedef struct List { int pad0[2]; int count; int pad1; Obj **data; } List;
typedef struct Hold { char pad[28]; List *l28; } Hold;
typedef struct LightRoot { char pad[12]; int f12; } LightRoot;
class Ob { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void v128(int); int pad; int f4x; };
typedef struct Mk : public igObject { int f8; int f12; Obj *f16; } Mk;
typedef struct LightOwner { char pad[12]; LightRoot *f12; char pad2[32]; Hold *f48; char pad3[8]; List *f60; List *f64; char pad4[16]; Obj *f84; } LightOwner;
Obj *FUN_001361b0(int);
void FUN_00460790(igViewerRenderer *arg0, igGroup *arg1);
#define CLEAR(src) { \
    List *l = (src); \
    int n = l->count; \
    int i; \
    int m; \
    int j; \
    Obj *o; \
    for (i = 0; i < n; i++) { \
        o = l->data[i]; \
        if (o != 0) { \
            o->_refCount = o->_refCount - 1; \
            if ((o->_refCount & 0x7FFFFF) == 0) igObject_Destroy(o); \
        } \
    } \
    m = l->count; \
    for (j = 0; j < m; j++) { \
        l->data[j] = 0; \
    } \
    l->count = 0; }
static inline void release(Obj *object) {
    if (object != 0) {
        object->_refCount = object->_refCount - 1;
        if ((object->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(object);
        }
    }
}
struct RemovedRef {
    Obj *p;
    RemovedRef(const RemovedRef &);
    ~RemovedRef() {
        release(p);
    }
};
extern "C" RemovedRef igGroup_RemoveChildAt(Hold *, int);
struct ItemType {};
static inline Obj *createItem(ItemType) { return FUN_001361b0(0); }

int ObjectList_AppendUniqueRetained(...);

struct V3 { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29(); virtual void v30(int); virtual void v31(); virtual void v32(void*); };
void FUN_00460f20(void *arg0, int arg1, int arg2);

struct OptionPanelView;
class DW4VC_128 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual int vX(int); };
class DW4VC_132 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual int vX(int); };
struct OptionPanelConfig { char pad[195]; unsigned char b195, b196, b197, b198, b199, b200, b201, b202; };
struct OptionPanelView { char pad[12]; OptionPanelConfig *f12; DW4VC_128 *f16; DW4VC_128 *f20; DW4VC_128 *f24; DW4VC_128 *f28; };
enum PanelMode { kPanelOff, kPanelOn };

class PropertyHolder { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); };
struct PropertyList { char pad[32]; int f32; };
int igMetaObject_FindFieldByName(...);
int igProperty_FindByPointer(...);
extern int text_meta[4];
extern int g_igAttr_metaObject[4];
extern int g_igObjectRefMetaField_metaObject[4];
int FUN_00460be0(PropertyHolder *arg0, PropertyList *arg1);
static inline int castToProperty(int object) {
    if (object != 0 && igObject_IsKindOf(object, g_igObjectRefMetaField_metaObject[0]) != 0) {
        return object;
    }
    return 0;
}

struct igResult { int value; };
struct ListOwner { char pad[32]; int list; };

igSmartPointer<igObject> FUN_0013ba30(int, igSmartPointer<igObject>);
int FUN_0013c060(...);
igResult ObjectList_RemoveFirstRetained(int, int, int);

static inline void removeFromList(int list, int object) {
    ObjectList_RemoveFirstRetained(list, object, 0);
}

extern int g_igViewerRenderer_metaObject[4];

/* The ids are held in a pointer-typed local so the compare puts the call result first (beq v0,s0). */
int FUN_0045f200(int arg0, X *arg1) {
    int *s0;
    if (arg1->f20 & 1) {
        s0 = (int *)g_igTransform_metaObject[0];
        if ((int *)arg1->v88() == s0 || (s0 = (int *)g_igLightSet_metaObject[0], (int *)arg1->v88() == s0)) return 0;
        if (igObject_IsKindOf(arg1, g_igGroup_metaObject[0]) != 0) return 2;
    }
    return 1;
}

void FUN_0045f2b0(A *arg0) {
    T *t;
    int n;
    int i;

    t = arg0->f80->f52;
    FUN_001b06f0(t, arg0->f40, 0);
    if (t->f60 == 0 && arg0->f12->f192 == 0) {
        n = arg0->f64->f8;
        for (i = 0; i < n; i++) {
            FUN_001b06f0(t, arg0->f64->f16[i], 1);
        }
    }
}

void FUN_0045f370(S *arg0) {
    T3 *temp_s3; int temp_s2; int var_s1; int var_s0;

    temp_s3 = arg0->f50->f34;
    igAttrStackManager_PopLightStateAttr(temp_s3, arg0->f28, 0);
    if ((temp_s3->f3c == 0) && (arg0->f0c->fc0 == 0)) {
        temp_s2 = arg0->f40->cnt;
        var_s1 = 0;
        if (0 < temp_s2) {
            var_s0 = 0;
            do {
                igAttrStackManager_PopLightStateAttr(temp_s3, *(int *)((char *)arg0->f40->arr + var_s0), 1);
                var_s1 += 1;
                var_s0 += 4;
            } while (var_s1 < temp_s2);
        }
    }
}

void Gap__Viewer__igViewerRenderer__vfunc_25(Q *arg0) {
    Rc *t;
    Rc *n;
    arg0->f8->v203(0, (int)arg0->f12 + 44);
    arg0->f8->v213((int)arg0->f12 + 108);
    t = arg0->f76;
    if (t != 0) {
        t->rc = t->rc - 1;
        if (((unsigned long long)((long long)t->rc << 0x29) >> 0x29) == 0) {
            igObject_Destroy(t);
        }
    }
    arg0->f76 = 0;
    t = arg0->f84;
    if (t != 0) {
        t->rc = t->rc - 1;
        if (((unsigned long long)((long long)t->rc << 0x29) >> 0x29) == 0) {
            igObject_Destroy(t);
        }
    }
    arg0->f84 = 0;
    if (arg0->f12->f12 != 0) {
        if (arg0->f68 != 0) {
            arg0->f72->v31();
            arg0->f72->v27(arg0->f12->f176);
            arg0->f72->v25(arg0->f44);
            n = arg0->f72->v30();
            if (n != 0) {
                n->rc = n->rc + 1;
            }
            t = arg0->f76;
            if (t != 0) {
                t->rc = t->rc - 1;
                if (((unsigned long long)((long long)t->rc << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(t);
                }
            }
            arg0->f76 = n;
        }
        arg0->f80->v31();
        arg0->f80->v27(arg0->f12->f176);
        FUN_0045f2b0((A *)arg0);
        arg0->f80->v25(arg0->f44);
        FUN_0045f370((S *)arg0);
        n = arg0->f80->v30();
        if (n != 0) {
            n->rc = n->rc + 1;
        }
        t = arg0->f84;
        if (t != 0) {
            t->rc = t->rc - 1;
            if (((unsigned long long)((long long)t->rc << 0x29) >> 0x29) == 0) {
                igObject_Destroy(t);
            }
        }
        arg0->f84 = n;
    }
}

void Gap__Viewer__igViewerRenderer__vfunc_23(Q2 *arg0) {
    Rc *temp_v0 = (Rc *)arg0->f8->v104(&text_igDisableExt[0]);
    if (temp_v0 != 0) {
        temp_v0->rc = temp_v0->rc + 1;
    }
    Rc *temp_a0_2 = arg0->f88;
    if (temp_a0_2 != 0) {
        temp_a0_2->rc = temp_a0_2->rc - 1;
        if (((unsigned long long)((long long)temp_a0_2->rc << 0x29) >> 0x29) == 0) {
            igObject_Destroy(temp_a0_2);
        }
    }
    arg0->f88 = temp_v0;
    arg0->f72->v112((int)arg0->f8);
    arg0->f80->v112((int)arg0->f8);
    igViewerRenderer_UpdateProjection((igViewerRenderer *)arg0);
    igViewerRenderer_UpdateViewMatrix((CameraLink *)arg0);
    igViewerRenderer_UpdateSorting((FogOwner *)arg0);
    igViewerRenderer_UpdateLighting((igViewerRenderer *)arg0);
    igViewerRenderer_UpdateRenderStates((OptionPanelView *)arg0);
    igViewerRenderer_UpdateScene((LightOwner *)arg0);
}

/* The matrix setter of the visual context; IG_GFX_MATRIX_PROJECTION is the type the projection
 * matrix attribute passes. */
enum { IG_GFX_MATRIX_PROJECTION = 0 };
class VisualContextView { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual void d101(); virtual void d102(); virtual void d103(); virtual void d104(); virtual void d105(); virtual void d106(); virtual void d107(); virtual void d108(); virtual void d109(); virtual void d110(); virtual void d111(); virtual void d112(); virtual void d113(); virtual void d114(); virtual void d115(); virtual void d116(); virtual void d117(); virtual void d118(); virtual void d119(); virtual void d120(); virtual void d121(); virtual void d122(); virtual void d123(); virtual void d124(); virtual void d125(); virtual void d126(); virtual void d127(); virtual void d128(); virtual void d129(); virtual void d130(); virtual void d131(); virtual void d132(); virtual void d133(); virtual void d134(); virtual void d135(); virtual void d136(); virtual void d137(); virtual void d138(); virtual void d139(); virtual void d140(); virtual void d141(); virtual void d142(); virtual void d143(); virtual void d144(); virtual void d145(); virtual void d146(); virtual void d147(); virtual void d148(); virtual void d149(); virtual void d150(); virtual void d151(); virtual void d152(); virtual void d153(); virtual void d154(); virtual void d155(); virtual void d156(); virtual void d157(); virtual void d158(); virtual void d159(); virtual void d160(); virtual void d161(); virtual void d162(); virtual void d163(); virtual void d164(); virtual void d165(); virtual void d166(); virtual void d167(); virtual void d168(); virtual void d169(); virtual void d170(); virtual void d171(); virtual void d172(); virtual void d173(); virtual void d174(); virtual void d175(); virtual void d176(); virtual void d177(); virtual void d178(); virtual void d179(); virtual void d180(); virtual void d181(); virtual void d182(); virtual void d183(); virtual void d184(); virtual void d185(); virtual void d186(); virtual void d187(); virtual void d188(); virtual void d189(); virtual void d190(); virtual void d191(); virtual void d192(); virtual void d193(); virtual void d194(); virtual void d195(); virtual void d196(); virtual void d197(); virtual void d198(); virtual void d199(); virtual void d200(); virtual int setMatrix(int type, int matrix); };
class DisableExtView { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void setDisabled(int feature, bool disabled); };
class RenderOutputView { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void render(int visualContext); };

static inline bool BitMask_IsSet(igBitMask *mask, unsigned int bit) {
    return (((unsigned int *)mask->_data)[bit >> 5] & (1 << (bit & 0x1F))) != 0;
}

/* Draws the light and scene outputs with the projection matrix of the parameters, switching off
 * for the duration of the draw the features the parameters' disable mask selects. */
void Gap__Viewer__igViewerRenderer__Render(igViewerRenderer *self) {
    igViewerParameters *params = (igViewerParameters *)self->_parameters;
    int count = ((igBitMask *)params->_disables)->_bitCount;
    int i;
    int j;
    ((VisualContextView *)self->_visualContext)->setMatrix(IG_GFX_MATRIX_PROJECTION, (int)&params->_projectionMatrix[0]);
    if (self->_disableExtension != 0) {
        for (i = 0; i < count; i++) {
            if (g_viewerDisableFeatures[i].supported
                && BitMask_IsSet((igBitMask *)((igViewerParameters *)self->_parameters)->_disables, i)) {
                ((DisableExtView *)self->_disableExtension)->setDisabled(g_viewerDisableFeatures[i].feature, true);
            }
        }
    }
    if (self->_lightOutput != 0) {
        ((RenderOutputView *)self->_lightOutput)->render(self->_visualContext);
    }
    if (self->_sceneOutput != 0) {
        ((RenderOutputView *)self->_sceneOutput)->render(self->_visualContext);
    }
    if (self->_disableExtension != 0) {
        for (j = 0; j < count; j++) {
            if (g_viewerDisableFeatures[j].supported
                && BitMask_IsSet((igBitMask *)((igViewerParameters *)self->_parameters)->_disables, j)) {
                ((DisableExtView *)self->_disableExtension)->setDisabled(g_viewerDisableFeatures[j].feature, false);
            }
        }
    }
}

void igViewerRenderer_ApplyOptions(Arg *arg0) {
    int sp0[3];
    int sp1[3];
    int sp2[3];
    int sp3[3];
    int sp4[3];
    int sp5[3];
    int sp6[3];
    int sp7[3];
    int sp8[3];
    int sp9[3];
    int sp10[3];
    int sp11[3];
    int sp12[3];
    int sp13[3];
    int sp14[3];
    Frame *f;
    Frame *s0;
    Frame *g;
    unsigned char s1;
    int v;
    int s1i;
    void *p;
    int *h;
    int rc;
    if (DAT_0056dc50[0] == 0) {
        f = (Frame *)__nw__FUi(240);
        if (f != 0) f = (Frame *)ViewerOptions_Construct(f);
        DAT_0056dc50[0] = f;
    }
    DAT_0056dc50[0]->f232 = DAT_0056dc50[0]->f232 + 1;
    s0 = DAT_0056dc50[0];
    s1 = arg0->f60->f8 > 0;
    if (s0->f92 != 0) {
        arg0->f12->f192 = s1;
    } else {
        arg0->f12->f192 = s0->f94;
    }
    sp0[1] = 0;
    sp0[0] = 2;
    sp0[2] = DAT_0058ca58[0];
    igModel_NotifyViews(arg0->f12, sp0);
    if (s0->f93 != 0) {
        /* matching construct: respell sweep under C++ — the C int-valued !s1 */
        v = (bool)s1 ^ 1;
    } else {
        v = s0->f95;
    }
    s1i = v & 0xFF;
    arg0->f12->f193 = (s1i & ((!s0->f96) & 0xFF)) != 0;
    sp1[1] = 0;
    sp1[0] = 2;
    sp1[2] = DAT_0058ca60[0];
    igModel_NotifyViews(arg0->f12, sp1);
    arg0->f12->f194 = (s1i & s0->f96) != 0;
    sp2[1] = 0;
    sp2[0] = 2;
    sp2[2] = DAT_0058ca68[0];
    igModel_NotifyViews(arg0->f12, sp2);
    arg0->f12->f195 = s0->f168;
    sp3[1] = 0;
    sp3[0] = 2;
    sp3[2] = DAT_0058ca70[0];
    igModel_NotifyViews(arg0->f12, sp3);
    arg0->f12->f196 = s0->f169;
    sp4[1] = 0;
    sp4[0] = 2;
    sp4[2] = DAT_0058ca78[0];
    igModel_NotifyViews(arg0->f12, sp4);
    arg0->f12->f197 = s0->f166;
    sp5[1] = 0;
    sp5[0] = 2;
    sp5[2] = DAT_0058ca80[0];
    igModel_NotifyViews(arg0->f12, sp5);
    arg0->f12->f198 = s0->f167;
    sp6[1] = 0;
    sp6[0] = 2;
    sp6[2] = DAT_0058ca88[0];
    igModel_NotifyViews(arg0->f12, sp6);
    arg0->f12->f199 = s0->f164;
    sp7[1] = 0;
    sp7[0] = 2;
    sp7[2] = DAT_0058ca90[0];
    igModel_NotifyViews(arg0->f12, sp7);
    arg0->f12->f200 = s0->f165;
    sp8[1] = 0;
    sp8[0] = 2;
    sp8[2] = DAT_0058ca98[0];
    igModel_NotifyViews(arg0->f12, sp8);
    arg0->f12->f201 = 0;
    sp9[1] = 0;
    sp9[0] = 2;
    sp9[2] = DAT_0058caa0[0];
    igModel_NotifyViews(arg0->f12, sp9);
    arg0->f12->f202 = 0;
    sp10[1] = 0;
    sp10[0] = 2;
    sp10[2] = DAT_0058caa8[0];
    igModel_NotifyViews(arg0->f12, sp10);
    arg0->f12->f184 = 0;
    sp11[1] = 0;
    sp11[0] = 2;
    sp11[2] = DAT_0058ca38[0];
    igModel_NotifyViews(arg0->f12, sp11);
    arg0->f12->f185 = 1;
    sp12[1] = 0;
    sp12[0] = 2;
    sp12[2] = DAT_0058ca40[0];
    igModel_NotifyViews(arg0->f12, sp12);
    arg0->f12->f186 = 0;
    sp13[1] = 0;
    sp13[0] = 2;
    sp13[2] = DAT_0058ca48[0];
    igModel_NotifyViews(arg0->f12, sp13);
    arg0->f12->f188 = 0;
    sp14[1] = 0;
    sp14[0] = 2;
    sp14[2] = DAT_0058ca50[0];
    igModel_NotifyViews(arg0->f12, sp14);
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
                __dl__FPv(f);
            }
            DAT_0056dc50[0] = 0;
        }
    }
}

void Gap__Viewer__igViewerRenderer__vfunc_13(P *arg0) {
    V4 sp40;
    float sp58[3];
    Frame *s0;
    igObject *t;
    igSmartPointer<igObject> first((igObject *)createFirst());
    sp40.a = 1.0f; sp40.b = 1.0f; sp40.c = 1.0f; sp40.d = 1.0f;
    ((A2 *)first.p)->vX(&sp40);
    if (DAT_0056dc50[0] == 0) {
        Frame *f = (Frame *)__nw__FUi(240);
        if (f != 0) f = (Frame *)ViewerOptions_Construct(f);
        DAT_0056dc50[0] = f;
    }
    DAT_0056dc50[0]->f232 = DAT_0056dc50[0]->f232 + 1;
    s0 = DAT_0056dc50[0];
    igSmartPointer<igObject> second((igObject *)createSecond());
    ((B2 *)second.p)->v128(4);
    ((B2 *)second.p)->v132(s0->range);
    arg0->f36->v128(s0->eye);
    arg0->f36->v136(&g_vec4Zero[0]);
    arg0->f36->v132(s0->center);
    sp58[0] = -g_vec3ZAxis[0];
    sp58[1] = -DAT_004e109c[0];
    sp58[2] = -DAT_004e10a0[0];
    arg0->f36->v144(sp58);
    {
        C2 *c = arg0->f36;
        c->f12 = 0;
        c->b144 = 1;
    }
    {
        igObject *s1 = (igObject *)arg0->f36;
        Q3 *s0b = arg0->f40;
        if (s1 != 0) {
            s1->_refCount = s1->_refCount + 1;
        }
        t = s0b->f16;
        if (t) {
            t->_refCount = t->_refCount - 1;
            if ((t->_refCount & 0x7FFFFF) == 0) igObject_Destroy(t);
        }
        s0b->f16 = s1;
    }
    if (DAT_0056dc50[0] != 0) {
        if (--DAT_0056dc50[0]->f232 <= 0) {
            Frame *s0c = DAT_0056dc50[0];
            if (s0c != 0) {
                if (&s0c->f236) {
                    void *p = s0c->f236;
                    if (p != 0) {
                        int *h = (int *)((char *)(p) - 8);
                        int rc = *(int *)((char *)(p) - 4) - 1;
                        *(int *)((char *)(p) - 4) = rc;
                        if (rc == 0) {
                            StringChunk_ReleaseHeader(*h, h);
                        }
                    }
                }
                if (s0c != 0) {
                    void *p = s0c->f0;
                    if (p != 0) {
                        int *h = (int *)((char *)(p) - 8);
                        int rc = *(int *)((char *)(p) - 4) - 1;
                        *(int *)((char *)(p) - 4) = rc;
                        if (rc == 0) {
                            StringChunk_ReleaseHeader(*h, h);
                        }
                    }
                }
                __dl__FPv(s0c);
            }
            DAT_0056dc50[0] = 0;
        }
    }
    FUN_00460e00((int *)arg0, (void *)first.p);
    FUN_00460e00((int *)arg0, (void *)second.p);
    FUN_00460e00((int *)arg0, (void *)arg0->f16);
    FUN_00460e00((int *)arg0, (void *)arg0->f20);
    FUN_00460e00((int *)arg0, (void *)arg0->f24);
    FUN_00460e00((int *)arg0, (void *)arg0->f28);
    FUN_00460e00((int *)arg0, (void *)arg0->f32);
    igGroup_AppendChild(arg0->f44, arg0->f52);
    igGroup_AppendChild(arg0->f52, arg0->f56);
    ObjectList_AppendRetained(arg0->f56->f28, arg0->f36);
    igGroup_AppendChild(arg0->f44, arg0->f48);
    arg0->f72->b8 = 1;
    arg0->f72->f12 = (int)&FUN_0045f200;
    arg0->f72->b24 = 1;
    igSmartPointer<igObject> third((igObject *)createThird());
    ((Y *)third.p)->b24 = 1;
    FUN_001c5160(third.p, 1.1f);
    t = third.p;
    if (t) t->_refCount = t->_refCount + 1;
    {
        igObject *o = arg0->f80;
        if (o) {
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7FFFFF) == 0) igObject_Destroy(o);
        }
    }
    arg0->f80 = t;
}

void FUN_004601c0(void *arg0) {
    void *temp_v0;

    temp_v0 = (void *)(*(int *)((char *)(arg0) + 80));
    FUN_001b0000(*(int *)((char *)(temp_v0) + 52), g_igViewportAttr_metaObject[0], *(int *)((char *)(temp_v0) + 36), *(int *)((char *)(temp_v0) + 32));
}

void igViewerRenderer_UpdateProjection(igViewerRenderer *arg0) {
    int sp[3];
    igViewerParameters *temp_v1;
    temp_v1 = (igViewerParameters *)arg0->_parameters;
    FUN_001b6ce0((void *)arg0->_sceneTraversal, temp_v1->_hfov, -1.0f, temp_v1->_ratio, temp_v1->_nearPlane, temp_v1->_farPlane);
    igMatrix44f_Copy(&((igViewerParameters *)arg0->_parameters)->_projectionMatrix[0], (char *)arg0->_sceneTraversal + 0x110);
    sp[0] = 2;
    sp[1] = 0;
    sp[2] = DAT_0058ca20[0];
    igModel_NotifyViews((void *)arg0->_parameters, sp);
}

void igViewerRenderer_UpdateViewMatrix(CameraLink *arg0) {
    int m[16];

    igMatrix44f_Copy(m, arg0->f12 + 0x6C);
    FUN_001b6ee0(arg0->f80, m);
    FUN_001b6ee0(arg0->f72, m);
    arg0->f52->vX(arg0->f80 + 0xA4);
}

void igViewerRenderer_UpdateSorting(struct FogOwner *arg0) {
    int var_a3;
    struct FogAttr *temp_a2;
    struct FogConfig *temp_a1;

    temp_a2 = arg0->f80->f68;
    temp_a1 = arg0->f12;
    var_a3 = 0;
    if (temp_a1->b184 != 0) {
        var_a3 |= 0x20;
    }
    if (temp_a1->b185 != 0) {
        var_a3 |= 1;
    }
    if (temp_a1->b186 != 0) {
        var_a3 |= 4;
    }
    temp_a2->f12 = temp_a2->f12 & var_a3;
    temp_a2->f12 = temp_a2->f12 | var_a3;
    temp_a2->f76 = arg0->f12->f188;
}

extern "C" void igViewerRenderer_UpdateScene(LightOwner *arg0) {
    int s5;
    int n3;
    Obj *s3;
    Mk *s2;
    int s0;
    Hold *a1 = arg0->f48;
    List *v1 = a1->l28;
    int var_v1;
    if (v1 != 0) {
        var_v1 = v1->count;
    } else {
        var_v1 = 0;
    }
    if (var_v1 > 0) {
        igGroup_RemoveChildAt(a1, 0);
    }
    CLEAR(arg0->f64)
    CLEAR(arg0->f60)
    if (arg0->f12->f12 != 0) {
        igGroup_AppendChild(arg0->f48, arg0->f12->f12);
        FUN_00460790((igViewerRenderer *)arg0, (igGroup *)arg0->f12->f12);
    }
    n3 = arg0->f60->count;
    s5 = 0;
    if (0 < n3) {
        s0 = 0;
        do {
            {
            igSmartPointer<Obj> item(createItem(ItemType()));
            s3 = *(Obj **)((char *)arg0->f60->data + s0);
            s2 = (Mk *)item.p;
            if (s3 != 0) s3->_refCount = s3->_refCount + 1;
            release(s2->f16);
            s2->f16 = s3;
            ((Ob *)item.p)->v128(0);
            ObjectList_AppendRetained((int)arg0->f64, (int)item.p);
            }
            s5 += 1;
            s0 += 4;
        } while (s5 < n3);
    }
    release(arg0->f84);
    arg0->f84 = 0;
}

void FUN_00460790(igViewerRenderer *arg0, igGroup *arg1) {
    int n; int i; int off;
    if (arg1->_flags & 1) {
        if (igObject_IsKindOf(arg1, g_igGroup_metaObject[0]) != 0) {
            n = 0;
            if (arg1->_childList != 0) n = ((igNodeList *)arg1->_childList)->_count;
            i = 0;
            if (0 < n) {
                off = 0;
                do {
                    FUN_00460790(arg0, *(igGroup **)((char *)((igNodeList *)arg1->_childList)->_data + off));
                    i += 1;
                    off += 4;
                } while (i < n);
            }
        } else if (igObject_IsKindOf(arg1, g_igLightSet_metaObject[0]) != 0) {
            n = ((igObjectList *)arg1->_childList)->_count;
            i = 0;
            if (0 < n) {
                off = 0;
                do {
                    ObjectList_AppendUniqueRetained(arg0->_lightList, *(int *)((char *)((igObjectList *)arg1->_childList)->_data + off));
                    i += 1;
                    off += 4;
                } while (i < n);
            }
        }
    }
}

void igViewerRenderer_UpdateLighting(igViewerRenderer *arg0) {
    bool a1 = true;
    bool a0 = true;
    igViewerParameters *x = (igViewerParameters *)arg0->_parameters;
    if (x->_useSceneLights == 0 && x->_useHeadLight == 0) a0 = false;
    if (!a0 && x->_useHeadLightSpecular == 0) a1 = false;
    arg0->_lightingState = a1;
    x = (igViewerParameters *)arg0->_parameters;
    if (x->_useHeadLight != 0 || x->_useHeadLightSpecular != 0) {
        ((V3 *)arg0->_headlightStateAttr)->v30(1);
        if (((igViewerParameters *)arg0->_parameters)->_useHeadLightSpecular != 0) {
            if (DAT_0056dc50[0] == 0) {
                Frame *f = (Frame *)__nw__FUi(240);
                if (f != 0) f = (Frame *)ViewerOptions_Construct(f);
                DAT_0056dc50[0] = f;
            }
            DAT_0056dc50[0]->f232 = DAT_0056dc50[0]->f232 + 1;
            ((V3 *)arg0->_headlightAttr)->v32((char *)DAT_0056dc50[0] + 116);
            if (DAT_0056dc50[0] != 0) {
                if (--DAT_0056dc50[0]->f232 <= 0) {
                    Frame *s1 = DAT_0056dc50[0];
                    if (s1 != 0) {
                        if (&s1->f236) {
                            void *p = s1->f236;
                            if (p != 0) {
                                int *h = (int *)((char *)(p) - 8);
                                int rc = *(int *)((char *)(p) - 4) - 1;
                                *(int *)((char *)(p) - 4) = rc;
                                if (rc == 0) {
                                    StringChunk_ReleaseHeader(*h, h);
                                }
                            }
                        }
                        if (s1 != 0) {
                            void *p = s1->f0;
                            if (p != 0) {
                                int *h = (int *)((char *)(p) - 8);
                                int rc = *(int *)((char *)(p) - 4) - 1;
                                *(int *)((char *)(p) - 4) = rc;
                                if (rc == 0) {
                                    StringChunk_ReleaseHeader(*h, h);
                                }
                            }
                        }
                        __dl__FPv(s1);
                    }
                    DAT_0056dc50[0] = 0;
                }
            }
        } else {
            ((V3 *)arg0->_headlightAttr)->v32(&g_vec4Zero[0]);
        }
    } else {
        ((V3 *)arg0->_headlightStateAttr)->v30(0);
    }
    ((V3 *)arg0->_lightingAttr)->v30(arg0->_lightingState);
    FUN_00460e00((int *)arg0, (V3 *)arg0->_lightingAttr);
    FUN_00460f20(arg0, (int)(V3 *)arg0->_lightingAttr, ((bool)arg0->_lightingState) ^ 1);
}

void igViewerRenderer_UpdateRenderStates(OptionPanelView *arg0) {
    arg0->f20->vX(arg0->f12->b195);
    FUN_00460e00((int *)arg0, arg0->f20);
    FUN_00460f20(arg0, (int)arg0->f20, arg0->f12->b196);
    ((DW4VC_132 *)arg0->f16)->vX(arg0->f12->b197);
    FUN_00460e00((int *)arg0, arg0->f16);
    FUN_00460f20(arg0, (int)arg0->f16, arg0->f12->b198);
    arg0->f24->vX(arg0->f12->b201 ? kPanelOff : kPanelOn);
    FUN_00460e00((int *)arg0, arg0->f24);
    FUN_00460f20(arg0, (int)arg0->f24, arg0->f12->b202);
    arg0->f28->vX(arg0->f12->b199 ? kPanelOn : kPanelOff);
    FUN_00460e00((int *)arg0, arg0->f28);
    FUN_00460f20(arg0, (int)arg0->f28, arg0->f12->b200);
}

int FUN_00460be0(PropertyHolder *arg0, PropertyList *arg1) {
    int field = castToProperty(igMetaObject_FindFieldByName(g_igAttr_metaObject[0], &text_meta[0]));
    return igProperty_FindByPointer(arg1->f32, field, arg0->vX());
}

extern "C" int FUN_00460c80(igObject *object, ListOwner *owner) {
    int found = FUN_00460be0((PropertyHolder *)object, (PropertyList *)owner);
    if (found != 0) {
        removeFromList(owner->list, found);
        igSmartPointer<igObject> wrapper = FUN_0013ba30(FUN_0013c060(), igSmartPointer<igObject>(object, kRetainReference));
        ObjectList_AppendRetained(owner->list, wrapper.get());
        return 1;
    }
    return 0;
}

void FUN_00460d90(void *arg0, void *arg1, int arg2) {
    int temp_v0;

    temp_v0 = FUN_00460be0((PropertyHolder *)arg2, (PropertyList *)arg0);
    if (temp_v0 != 0) {
        ObjectList_RemoveFirstRetained(*(int *)((char *)(arg0) + 32), temp_v0, 0);
        ObjectList_AppendRetained(*(int *)((char *)(arg1) + 32), temp_v0);
    }
}

void FUN_00460e00(int *a, void *arg1) {
    if ((arg1 != 0) && !(FUN_00460c80((igObject *)arg1, (ListOwner *)a[12]) & 0xFF) && !(FUN_00460c80((igObject *)arg1, (ListOwner *)a[11]) & 0xFF)) {
        igSmartPointer<igObject> sp3C = FUN_0013ba30(FUN_0013c060(), igSmartPointer<igObject>((igObject *)arg1, kRetainReference));
        ObjectList_AppendRetained(*(int *)((char *)(a[11]) + 32), sp3C.get());
    }
}

void FUN_00460f20(void *arg0, int arg1, int arg2) {
    if (arg2 != 0) {
        FUN_00460d90((void *)*(int *)((char *)(arg0) + 44), (void *)*(int *)((char *)(arg0) + 48), arg1);
        return;
    }
    FUN_00460d90((void *)*(int *)((char *)(arg0) + 48), (void *)*(int *)((char *)(arg0) + 44), arg1);
}

int Gap__Viewer__igViewerRenderer__vfunc_22(void) {
    return g_igViewerRenderer_metaObject[0];
}

void Gap__Viewer__igViewerRenderer__vfunc_24(void) {

}

}
