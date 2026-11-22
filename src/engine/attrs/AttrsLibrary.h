#ifndef DW4_ATTRS_LIBRARY_H
#define DW4_ATTRS_LIBRARY_H

#include "dw4/support/reflected.h"
#include "dw4/core/igSmartPointer.h"
#include "dw4/core/igStringRef.h"
#include "dw4/core/igTDataList.h"
#include "dw4/support/ClassRegistration.h"
#include "dw4/attrs/igAttrList.h"
#include "dw4/attrs/igBlendFunctionAttr.h"
#include "dw4/attrs/igBlendMatrixPaletteAttr.h"
#include "dw4/attrs/igBlendStateAttr.h"
#include "dw4/attrs/igClearAttr.h"
#include "dw4/attrs/igColorAttr.h"
#include "dw4/attrs/igDisplayListAttr.h"
#include "dw4/attrs/igGeometryAttr.h"
#include "dw4/attrs/igGeometryAttrList.h"
#include "dw4/attrs/igGeometrySetAttr.h"
#include "dw4/attrs/igLightAttr.h"
#include "dw4/attrs/igLightStateAttr.h"
#include "dw4/attrs/igLightingStateAttr.h"
#include "dw4/attrs/igMatrixOptStateAttr.h"
#include "dw4/attrs/igModelViewMatrixAttr.h"
#include "dw4/attrs/igParticleAttr.h"
#include "dw4/attrs/igProjectionMatrixAttr.h"
#include "dw4/attrs/igTextureAttr.h"
#include "dw4/attrs/igTextureBindAttr.h"
#include "dw4/attrs/igTextureList.h"
#include "dw4/attrs/igTextureMatrixAttr.h"
#include "dw4/attrs/igTextureStateAttr.h"
#include "dw4/attrs/igTimeAttr.h"
#include "dw4/attrs/igVertexBlendMatrixAttr.h"
#include "dw4/attrs/igVertexBlendMatrixListAttr.h"
#include "dw4/attrs/igViewportAttr.h"
#include <string.h>
#include <stdio.h>
#include "dw4/gfx/igVisualContextDispatchView.h"
#include "dw4/gfx/igCapabilityManagerDispatchView.h"
#include "dw4/gfx/igMultiTextureExtDispatchView.h"
#include "dw4/gfx/igBlendEquationExtDispatchView.h"
#include "dw4/support/softfloat.h"
#include "dw4/gfx/igVisualContext.h"
#include "dw4/gfx/igVertexArray.h"
#include "dw4/core/igResult.h"
#include "dw4/core/igRegistry.h"
#include "dw4/gfx/igPsx2BlendEquationExt.h"
#include "dw4/gfx/igPsx2VisualContext.h"
#include <math.h>
#include "dw4/core/igObjectSystem.h"
#include "dw4/core/igObjectList.h"
#include "dw4/core/igObject.h"
#include "dw4/core/igNamedObject.h"
#include "dw4/core/igMetaObject.h"
#include "dw4/core/igMemoryPoolContext.h"
#include "dw4/core/igMemoryPoolView.h"
#include "dw4/maths/igMatrix44f.h"
#include "dw4/gfx/igImage.h"
#include "dw4/core/igDataLists.h"
#include "dw4/game/beModelCtrlInfo.h"
#include "dw4/core/StringPool.h"
#include "dw4/gfx/GfxMetaEnums.h"
#include "dw4/core/igMetaObjectList.h"
#include "dw4/maths/igMathConstants.h"
#include "dw4/core/igInfo.h"
#define REL(pp) if (*(pp) != 0) { (*(pp))->refs = (*(pp))->refs - 1; if (((unsigned long long)(long long)(*(pp))->refs & 0x7fffffULL) == 0) igObject_Destroy((igObject *)(*(pp))); }
typedef void (*igMetaObjectCallback)();
#include "dw4/core/igBoolMetaField.h"
#include "dw4/core/igDoubleMetaField.h"
#include "dw4/core/igEnumMetaField.h"
#include "dw4/core/igFloatMetaField.h"
#include "dw4/core/igIntMetaField.h"
#include "dw4/core/igLongMetaField.h"
#include "dw4/maths/igMatrix44fMetaField.h"
#include "dw4/core/igMemoryRefMetaField.h"
#include "dw4/core/igMetaEnum.h"
#include "dw4/core/igObjectRefArrayMetaField.h"
#include "dw4/core/igObjectRefMetaField.h"
#include "dw4/core/igRawRefMetaField.h"
#include "dw4/core/igShortMetaField.h"
#include "dw4/core/igUnsignedCharMetaField.h"
#include "dw4/core/igUnsignedIntMetaField.h"
#include "dw4/core/igUnsignedShortMetaField.h"
#include "dw4/maths/igVec3fMetaField.h"
#include "dw4/maths/igVec4fMetaField.h"
#include "dw4/support/list-services.h"
#include "dw4/maths/igVec3fList.h"
#include "dw4/maths/igVec4f.h"
#include "dw4/core/igUnsignedIntList.h"
#include "dw4/runtime/New.h"

extern "C" void FUN_0014cd90(void);


extern "C" void AttrsLibrary_MarkRegistered(void);

typedef struct S_ref { char pad4[4]; int f4; } S_ref;


union U { int vt; char b[16]; };




union U_1304e0 { int vt; char b[48]; };
struct Obj { int *vt; char pad[12]; };
extern "C" igMetaObject *igVertexBlendMatrixListAttr_GetMetaObject(void);

extern "C" int g_igVertexBlendMatrixListAttr_vtable[4];
extern "C" int DAT_00522630[8];
union U_1309c0 { int vt; char b[160]; };
extern "C" int igVertexBlendMatrixListAttr_GetVTable(void);
extern "C" void igVertexBlendMatrixListAttr_EnsureRegistered(void);
extern "C" CallbackArray *igVertexBlendMatrixListAttr_Register(void);
extern "C" void igVertexBlendMatrixListAttr_GetMetaObjectFunction(void);
extern "C" void igVertexBlendMatrixListAttr_InitFields(void);

union U_130ca0 { int vt; int w[20]; char b[80]; };
union U_131000 { int vt; char b[32]; };
struct F { char pad[48]; int *f48; };
struct Fld { char pad[48]; int f48; };


extern "C" int FUN_00131c50(void);
/* The igMetaField members InitFields writes, through one view: the reflected igMetaField, igEnumMetaField and
 * igObjectRefMetaField are unrelated structs to the compiler, and stores through three types schedule differently. */
struct MetaFieldSetupView { char p0[38]; char _persistent; char _shallowCopyMethod; char _deepCopyMethod; char p41[3]; char _isAlikeShallowMethod; char p45[3]; void (*_invarianceFunction)(void); void (*_getMetaEnumFunction)(void); int _metaObject; };
extern "C" void FUN_00131f70(void);
struct W { int *vt; int f[27]; };
struct Ref { int pad; union { int w; struct { unsigned cnt:23; unsigned f:9; } b; } u; };
struct R { int w0; int rc; };
struct S_132230 {
    void *f0;
    char pad[8];
    struct R *f12;
    char pad2[32];
    struct R *f48;
    char pad3[4];
    struct R *f56;
    char pad4[4];
    struct R *f64;
};

struct Obj_1328f0 { int *vt; char pad[8]; char *m; char pad2[16]; };
/* Deleting destructor; the deletion flag is a signed short. */
typedef struct ObjectRefTarget { int word0; int references; } ObjectRefTarget;
typedef struct ObjectRefWord { ObjectRefTarget *value; } ObjectRefWord;
union U_132c40 { int vt; char b[80]; };

typedef struct { int *vt; int pad[7]; } Obj_133090;

union U_133240 { int vt; char b[80]; };
typedef struct S_temp_a0_1338d0 { char pad4[4]; int f4; } S_temp_a0_1338d0;
union U_133c10 { int vt; int w[4]; void *p[4]; char b[16]; };
extern "C" ObjectRefWord *FUN_00133ca0(ObjectRefWord *self,int delete_storage);
union U_133ef0 { int vt; char b[32]; };
union U_134290 { int vt; char b[80]; };
union U_134bf0 { int vt; int w[4]; void *p[4]; char b[16]; };
extern "C" igMetaObject *igParticleAttr_GetMetaObject(void);
typedef struct Q { char pad4[4]; int f4; } Q;
typedef struct { int *vt; int w[3]; Q *s; int tail[4]; } Obj_134dc0;
extern "C" int g_igParticleAttr_vtable[4];
extern "C" int igParticleAttr_GetVTable(void);
extern "C" CallbackArray *igParticleAttr_Register(void);
extern "C" void igParticleAttr_GetMetaObjectFunction(void);
extern "C" void igParticleAttr_InitFields(void);
struct Obj_1355e0 { int *vt; char pad[28]; };

extern "C" void thunk_igModelViewMatrixAttr_UserUnregister(void);
typedef struct { int *vt; int pad[7]; } Obj_1360e0;
union U_136290 { int vt; char b[32]; };
extern "C" ObjectRefWord *FUN_00136370(ObjectRefWord *self,int delete_storage);
struct Obj_136680 { int *vt; char pad[28]; };
union U_1367f0 { int vt; char b[160]; };
extern "C" igMetaEnum *igGeometrySetAttr_GetAttrFlagsMetaEnum(void);
union U_136d30 { int vt; char b[32]; };
extern "C" void **FUN_00136e10(void **arg0, int arg1);
struct F_136f30 { char p[38]; char f38; char f39; char f40; char p2[3]; char f44; char p3[7]; int f52; int f56; };
extern "C" void **FUN_00137260(void **arg0, short arg1);
extern "C" void **FUN_001372e0(struct Ref **self, short flag);
extern "C" void **FUN_00137360(void **arg0, long long arg1);
struct S1 { char pad4[4]; int f4; };
extern "C" igMetaObject *igGeometryAttr_GetPublishedMetaObject(void);

struct O_137b40 { int *vt; int p; };
typedef struct S_temp_a0_1380e0 { char pad4[4]; int f4; } S_temp_a0_1380e0;
extern "C" void **FUN_001380e0(void **arg0, short arg1);
union U_1389f0 { int vt; char b[64]; };
union U_139a70 { int vt; char b[32]; };
union U_139fb0 { int vt; char b[64]; };
struct Obj_13a400 { int *vt; char pad[28]; };
union U_13a6d0 { int vt; char b[32]; };
typedef struct S_temp_a0_13a800 { char pad4[4]; int f4; } S_temp_a0_13a800;
extern "C" void **FUN_0013a800(void **arg0, short arg1);


extern "C" void thunk_igAttrPool_UserUnregister(void);
struct Obj_13ac70 { int *vt; char pad[28]; };

struct Obj_13afa0 { int *vt; char pad[28]; };

typedef struct { int pad[3]; unsigned int a; float b; } S2;

class DW4VC_128_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual int vX(int); };
class DW4VC_132_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual int vX(float); };

extern "C" void FUN_0013b800(void);


typedef igSmartPointer<igObject> igObjectPointer;


class DW4VC_88_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); };
class DW4VC_104_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual int vX(const char *); };
class igVisualContextView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();
    virtual void vfunc_21(int capability);
};
class igBlendFunctionAttrView;








class Q_13c940 { public:
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
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void d27();
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual void d31();
    virtual void d32();
    virtual void d33();
    virtual void d34();
    virtual void d35();
    virtual void d36();
    virtual void d37();
    virtual void d38();
    virtual void d39();
    virtual void d40();
    virtual void d41();
    virtual void d42();
    virtual void d43();
    virtual void d44();
    virtual void d45();
    virtual void d46();
    virtual void d47();
    virtual int getId();
};
class P { public:
    virtual void e0();
    virtual void e1();
    virtual void e2();
    virtual void e3();
    virtual void e4();
    virtual void e5();
    virtual void e6();
    virtual void e7();
    virtual void e8();
    virtual void e9();
    virtual void e10();
    virtual void e11();
    virtual void e12();
    virtual void e13();
    virtual void e14();
    virtual void e15();
    virtual void e16();
    virtual void e17();
    virtual void e18();
    virtual void e19();
    virtual void e20();
    virtual void e21();
    virtual void touch(Q_13c940 *q);
    char pad[32];
    int f36;
};
struct X { char pad[20]; int f20; };
struct S_13c940 {
    int p0, p4, p8;
    int mode;
    X *f16;
    int f20;
    P *f24;
    int f28, f32, f36;
    int f40;
    int f44, f48;
};




struct S_13cc30;
class VC_13cc30 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void vX(int); };
struct L { char p[8]; int n; char q[4]; VC_13cc30 **a; };
struct S_13cc30 { char p[12]; L *f12; };

class C { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual void d101(); virtual void d102(); virtual void d103(); virtual void d104(); virtual void d105(); virtual void d106(); virtual void d107(); virtual void d108(); virtual void d109(); virtual void d110(); virtual void d111(); virtual void d112(); virtual void d113(); virtual void d114(); virtual void d115(); virtual void d116(); virtual void d117(); virtual void d118(); virtual void d119(); virtual void d120(); virtual void d121(); virtual void d122(); virtual void d123(); virtual void d124(); virtual void d125(); virtual void d126(); virtual void d127(); virtual void d128(); virtual void d129(); virtual void d130(); virtual void d131(); virtual void d132(); virtual void d133(); virtual void d134(); virtual void d135(); virtual void d136(); virtual void d137(); virtual void d138(); virtual void d139(); virtual void d140(); virtual void d141(); virtual void d142(); virtual void d143(); virtual void d144(); virtual void d145(); virtual void d146(); virtual void d147(); virtual void d148(); virtual void d149(); virtual void d150(); virtual void d151(); virtual void d152(); virtual void d153(); virtual void d154(); virtual void d155(); virtual void d156(); virtual void d157(); virtual void d158(); virtual void d159(); virtual void d160(); virtual void d161(); virtual void d162(); virtual void d163(); virtual void d164(); virtual void d165(); virtual void d166(); virtual void d167(); virtual void d168(); virtual void d169(); virtual void d170(); virtual void d171(); virtual void d172(); virtual void d173(); virtual void d174(); virtual void d175(); virtual void d176(); virtual void d177(); virtual void d178(); virtual void d179(); virtual void d180(); virtual void d181(); virtual void d182(); virtual void d183(); virtual void d184(); virtual void d185(); virtual void d186(); virtual void d187(); virtual void d188(); virtual void d189(); virtual void d190(); virtual void d191(); virtual void d192(); virtual void d193(); virtual void d194(); virtual void d195(); virtual void d196(); virtual void d197(); virtual void d198(); virtual void d199(); virtual void d200(); virtual void d201(); virtual void d202(); virtual void d203(); virtual void d204(); virtual void d205(); virtual void d206(); virtual void d207(); virtual void d208(); virtual void d209(); virtual void d210(); virtual void d211(); virtual void d212(); virtual void d213(); virtual void d214(); virtual void d215(); virtual void d216(); virtual void d217(); virtual void d218(); virtual void d219(); virtual void d220(); virtual void d221(); virtual void d222(); virtual void d223(); virtual void d224(); virtual void d225(); virtual void d226(); virtual void d227(); virtual void d228(); virtual void d229(); virtual void d230(); virtual void d231(); virtual void d232(); virtual void d233(); virtual void d234(); virtual void d235(); virtual void d236(); virtual void d237(); virtual void d238(); virtual void d239(); virtual void d240(); virtual void d241(); virtual float f242(); virtual void d243(); virtual int f244(); virtual void d245(); virtual void f246(float *); virtual void d247(); virtual float f248(); virtual void d249(); virtual float f250(); };

extern "C" void FUN_0013d020(void);
struct Rc { int w0; int refs; };
#include "dw4/gfx/igVertexArrayLock.h"
#include "dw4/attrs/igVertexBlendStateAttr.h"
#include "dw4/attrs/igVisualContextAttrDefaultManager.h"
#include "dw4/attrs/igTextureMatrixStateAttr.h"
#include "dw4/attrs/igTextureFunctionAttr.h"
#include "dw4/attrs/igTextureCoordSourceAttr.h"
#include "dw4/attrs/igTexGenMatrixAttr.h"
#include "dw4/attrs/igStencilFunctionAttr.h"
#include "dw4/attrs/igRenderDestinationAttr.h"
#include "dw4/attrs/igPixelPipelineModeAttr.h"
#include "dw4/attrs/igMultiPassStateAttr.h"
#include "dw4/attrs/igGeometryMaskAttr.h"
#include "dw4/attrs/igGenericAttrDefaultManager.h"
#include "dw4/attrs/igDepthStateAttr.h"
#include "dw4/attrs/igCullFaceAttr.h"
#include "dw4/attrs/igColorMaskAttr.h"
#include "dw4/attrs/igBlendMatricesAttr.h"
#include "dw4/attrs/igAttrPool.h"
#include "dw4/attrs/igAlphaStateAttr.h"
#include "dw4/attrs/igAlphaFunctionAttr.h"
#include "dw4/datapump/igMatrixObjectList.h"
#include "dw4/gfx/igBlendEquationExt.h"
#include "dw4/gfx/igParticleArray.h"
#include "dw4/gfx/igPrimLengthArray.h"
#include "dw4/gfx/igScissorExt.h"
extern "C" void FUN_00192360(const float *matrix, float *out, float *in, int count);
extern "C" void FUN_00192430(const float *matrix, float *out, float *in, unsigned int count);
extern "C" float FUN_0018b9e0(const void *ray, const float *a, const float *b, const float *c, float *hit,
                               float *normal, int mode);
extern "C" void Gap__Gfx__igVertexArray2__vfunc_24(void);

/* The source's vtable: 68 unnamed padding slots, then the getter at offset 280. */
struct Ob { virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4(); virtual void a5(); virtual void a6(); virtual void a7(); virtual void a8(); virtual void a9(); virtual void v10(); };
struct Item { virtual void b0(); virtual void b1(); virtual void b2(); virtual void b3(); virtual void b4(); virtual void b5(); virtual void b6(); virtual void b7(); virtual void b8(); virtual void b9(); virtual void b10(); virtual void b11(); virtual void b12(); virtual void b13(); virtual void b14(); virtual void b15(); virtual void b16(); virtual void b17(); virtual void b18(); virtual void b19(); virtual void b20(); virtual void b21(); virtual void v22(int); };
/* matching construct: dummy-virtual view so ->v30() dispatches through the object vtable */
struct Self { virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3(); virtual void c4(); virtual void c5(); virtual void c6(); virtual void c7(); virtual void c8(); virtual void c9(); virtual void c10(); virtual void c11(); virtual void c12(); virtual void c13(); virtual void c14(); virtual void c15(); virtual void c16(); virtual void c17(); virtual void c18(); virtual void c19(); virtual void c20(); virtual void c21(); virtual void c22(); virtual void c23(); virtual void c24(); virtual void c25(); virtual void c26(); virtual void c27(); virtual void c28(); virtual void c29(); virtual void v30(int); };

class EV { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual int vX(int); };

struct L_13e8d0 { char pad[8]; int n; char pad2[4]; EV **d; };
struct T_13e8d0 { char pad[16]; int f16; L_13e8d0 *f20; int f24; unsigned char f28; };
class DW4VC_112_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual int vX(); };
class I { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void vX(); };
class H { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual void d101(); virtual void d102(); virtual void d103(); virtual void d104(); virtual void d105(); virtual void d106(); virtual void d107(); virtual void d108(); virtual void d109(); virtual void d110(); virtual void d111(); virtual void d112(); virtual void d113(); virtual void d114(); virtual void d115(); virtual void d116(); virtual void d117(); virtual void d118(); virtual void d119(); virtual void d120(); virtual void d121(); virtual void d122(); virtual void d123(); virtual void d124(); virtual void d125(); virtual void d126(); virtual void d127(); virtual void d128(); virtual void d129(); virtual void d130(); virtual void d131(); virtual void d132(); virtual void d133(); virtual void d134(); virtual void d135(); virtual void d136(); virtual void d137(); virtual void d138(); virtual void d139(); virtual void d140(); virtual void d141(); virtual void d142(); virtual void d143(); virtual void d144(); virtual void d145(); virtual void d146(); virtual void d147(); virtual void d148(); virtual void d149(); virtual void d150(); virtual void d151(); virtual void d152(); virtual void d153(); virtual void d154(); virtual void d155(); virtual void d156(); virtual void d157(); virtual void d158(); virtual void d159(); virtual void d160(); virtual void d161(); virtual void d162(); virtual void d163(); virtual void d164(); virtual void d165(); virtual void d166(); virtual void d167(); virtual void d168(); virtual void d169(); virtual void d170(); virtual void d171(); virtual void d172(); virtual void d173(); virtual void d174(); virtual void d175(); virtual void d176(); virtual void d177(); virtual void d178(); virtual void d179(); virtual void d180(); virtual void d181(); virtual void d182(); virtual void d183(); virtual void d184(); virtual void d185(); virtual void d186(); virtual void d187(); virtual void d188(); virtual void d189(); virtual void d190(); virtual void vX(int); int references; };
struct Lst { char p[8]; int n; int p2; I **arr; };
struct A_13ea20 { char p[12]; H *f12; int f16; Lst *f20; };


extern "C" void igPsx2VisualContext_SetLightDirection(igObject *context, int light, float *direction);

extern "C" void igPsx2VisualContext_SetLightAttenuation(igObject *context, int light, float *attenuation);
class L_13ece0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void vX(int); int references; };
struct A_13ece0 { char p[16]; int f16; char p2[120]; L_13ece0 *f140; unsigned char f144; unsigned char f145; };
class O_13ef30 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void vX(); char pad[12]; int f16; };
struct S_13ef30 { char p[16]; O_13ef30 *f16; unsigned char f20; };

class DW4VC_320_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual int vX(int); };
/* Stand-in receiver: the dummy virtuals only put `vX` at the right vtable slot. */
class BoundLightVtable { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual int vX(); };


class MaterialContextView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31();
    virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39();
    virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47();
    virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55();
    virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63();
    virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71();
    virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79();
    virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87();
    virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95();
    virtual void d96(); virtual float getMaterialShininess(); virtual void d98(); virtual void d99(); virtual void d100(); virtual void getMaterialAmbient(igVec4f *color); virtual void d102(); virtual void getMaterialEmission(igVec4f *color);
    virtual void d104(); virtual void getMaterialDiffuse(igVec4f *color); virtual void d106(); virtual void getMaterialSpecular(igVec4f *color);
};
class MaterialAttrView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void setShininess(float shininess); virtual void setAmbient(const igVec4f *color);
    virtual void setEmission(const igVec4f *color); virtual void setDiffuse(const igVec4f *color); virtual void setSpecular(const igVec4f *color);
};
/* igMatrixOptStateAttr's virtual functions as synchronizeDefault calls them: slot 30 sets _enabled. */
class igMatrixOptStateAttrView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
    virtual void setState(unsigned char enabled);
};

class VA { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual void d101(); virtual void d102(); virtual void d103(); virtual void d104(); virtual void d105(); virtual void d106(); virtual void d107(); virtual void d108(); virtual void d109(); virtual void d110(); virtual void d111(); virtual void d112(); virtual void d113(); virtual void d114(); virtual void d115(); virtual void d116(); virtual void d117(); virtual void d118(); virtual void d119(); virtual void d120(); virtual void d121(); virtual void d122(); virtual void d123(); virtual void d124(); virtual void d125(); virtual void d126(); virtual void d127(); virtual void d128(); virtual void d129(); virtual void d130(); virtual void d131(); virtual void d132(); virtual void d133(); virtual void d134(); virtual void d135(); virtual void d136(); virtual void d137(); virtual void d138(); virtual void d139(); virtual void d140(); virtual void d141(); virtual void d142(); virtual void d143(); virtual void d144(); virtual void d145(); virtual void d146(); virtual void d147(); virtual void d148(); virtual void d149(); virtual void d150(); virtual void d151(); virtual void d152(); virtual void d153(); virtual void d154(); virtual void d155(); virtual void d156(); virtual void d157(); virtual void d158(); virtual void d159(); virtual void d160(); virtual void d161(); virtual void d162(); virtual void d163(); virtual void d164(); virtual void d165(); virtual void d166(); virtual void d167(); virtual void d168(); virtual void d169(); virtual void d170(); virtual void d171(); virtual void d172(); virtual void d173(); virtual void d174(); virtual void d175(); virtual void d176(); virtual void d177(); virtual void d178(); virtual void d179(); virtual void d180(); virtual void d181(); virtual void d182(); virtual void d183(); virtual void d184(); virtual void d185(); virtual void d186(); virtual void d187(); virtual void d188(); virtual void d189(); virtual void d190(); virtual void d191(); virtual void d192(); virtual void d193(); virtual void d194(); virtual void d195(); virtual void d196(); virtual void d197(); virtual void d198(); virtual void d199(); virtual void d200(); virtual void d201(); virtual void d202(); virtual void d203(); virtual void d204(); virtual void d205(); virtual int vX(int, void *); };
extern "C" void FUN_0013f800(void *arg0, int arg1);
extern "C" void FUN_001757c0(igPsx2VisualContext*, int);
class igMultiPassStateAttrView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
    virtual void vfunc_30(int passes);
};
class igPsx2VisualContextView {
public:
    virtual void d0();
    unsigned int _refCount;
    char _pad8[1444];
    int _bMultiPassNum;
};


class A_13f8a0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void vX(int, int, int *, float); };
class B_13f8a0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void vX(); };
extern "C" void igParticleAttr_apply(igParticleAttr *arg0, char *arg1);
extern "C" void igParticleAttr_SetParticleArray(igParticleAttr *self, igObject *particleArray, int particleNum, int particleOffset);
class VC37 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual float vX(); };
extern "C" int Gap__Attrs__igParticleAttr__vfunc_33(igParticleAttr *self);
extern "C" float Gap__Bec__ParticleArray__vfunc_35(ParticleArray *arg0);
extern "C" void igParticleAttr_SynchronizeDefault(void);

extern "C" void igPointSpriteExt_SetSpriteSize(igPrimLengthArray1_1 *self, float value);

class VisualContextMatrixSlots {
public:
    virtual void vfunc_2(); virtual void vfunc_3(); virtual void vfunc_4(); virtual void vfunc_5(); virtual void vfunc_6(); virtual void vfunc_7();
    virtual void vfunc_8(); virtual void vfunc_9(); virtual void vfunc_10(); virtual void vfunc_11(); virtual void vfunc_12(); virtual void vfunc_13();
    virtual void vfunc_14(); virtual void vfunc_15(); virtual void vfunc_16(); virtual void vfunc_17(); virtual void vfunc_18(); virtual void vfunc_19();
    virtual void vfunc_20(); virtual void vfunc_21(); virtual void vfunc_22(); virtual void vfunc_23(); virtual void vfunc_24(); virtual void vfunc_25();
    virtual void vfunc_26(); virtual void vfunc_27(); virtual void vfunc_28(); virtual void vfunc_29(); virtual void vfunc_30(); virtual void vfunc_31();
    virtual void vfunc_32(); virtual void vfunc_33(); virtual void vfunc_34(); virtual void vfunc_35(); virtual void vfunc_36(); virtual void vfunc_37();
    virtual void vfunc_38(); virtual void vfunc_39(); virtual void vfunc_40(); virtual void vfunc_41(); virtual void vfunc_42(); virtual void vfunc_43();
    virtual void vfunc_44(); virtual void vfunc_45(); virtual void vfunc_46(); virtual void vfunc_47(); virtual void vfunc_48(); virtual void vfunc_49();
    virtual void vfunc_50(); virtual void vfunc_51(); virtual void vfunc_52(); virtual void vfunc_53(); virtual void vfunc_54(); virtual void vfunc_55();
    virtual void vfunc_56(); virtual void vfunc_57(); virtual void vfunc_58(); virtual void vfunc_59(); virtual void vfunc_60(); virtual void vfunc_61();
    virtual void vfunc_62(); virtual void vfunc_63(); virtual void vfunc_64(); virtual void vfunc_65(); virtual void vfunc_66(); virtual void vfunc_67();
    virtual void vfunc_68(); virtual void vfunc_69(); virtual void vfunc_70(); virtual void vfunc_71(); virtual void vfunc_72(); virtual void vfunc_73();
    virtual void vfunc_74(); virtual void vfunc_75(); virtual void vfunc_76(); virtual void vfunc_77(); virtual void vfunc_78(); virtual void vfunc_79();
    virtual void vfunc_80(); virtual void vfunc_81(); virtual void vfunc_82(); virtual void vfunc_83(); virtual void vfunc_84(); virtual void vfunc_85();
    virtual void vfunc_86(); virtual void vfunc_87(); virtual void vfunc_88(); virtual void vfunc_89(); virtual void vfunc_90(); virtual void vfunc_91();
    virtual void vfunc_92(); virtual void vfunc_93(); virtual void vfunc_94(); virtual void vfunc_95(); virtual void vfunc_96(); virtual void vfunc_97();
    virtual void vfunc_98(); virtual void vfunc_99(); virtual void vfunc_100(); virtual void vfunc_101(); virtual void vfunc_102(); virtual void vfunc_103();
    virtual void vfunc_104(); virtual void vfunc_105(); virtual void vfunc_106(); virtual void vfunc_107(); virtual void vfunc_108(); virtual void vfunc_109();
    virtual void vfunc_110(); virtual void vfunc_111(); virtual void vfunc_112(); virtual void vfunc_113(); virtual void vfunc_114(); virtual void vfunc_115();
    virtual void vfunc_116(); virtual void vfunc_117(); virtual void vfunc_118(); virtual void vfunc_119(); virtual void vfunc_120(); virtual void vfunc_121();
    virtual void vfunc_122(); virtual void vfunc_123(); virtual void vfunc_124(); virtual void vfunc_125(); virtual void vfunc_126(); virtual void vfunc_127();
    virtual void vfunc_128(); virtual void vfunc_129(); virtual void vfunc_130(); virtual void vfunc_131(); virtual void vfunc_132(); virtual void vfunc_133();
    virtual void vfunc_134(); virtual void vfunc_135(); virtual void vfunc_136(); virtual void vfunc_137(); virtual void vfunc_138(); virtual void vfunc_139();
    virtual void vfunc_140(); virtual void vfunc_141(); virtual void vfunc_142(); virtual void vfunc_143(); virtual void vfunc_144(); virtual void vfunc_145();
    virtual void vfunc_146(); virtual void vfunc_147(); virtual void vfunc_148(); virtual void vfunc_149(); virtual void vfunc_150(); virtual void vfunc_151();
    virtual void vfunc_152(); virtual void vfunc_153(); virtual void vfunc_154(); virtual void vfunc_155(); virtual void vfunc_156(); virtual void vfunc_157();
    virtual void vfunc_158(); virtual void vfunc_159(); virtual void vfunc_160(); virtual void vfunc_161(); virtual void vfunc_162(); virtual void vfunc_163();
    virtual void vfunc_164(); virtual void vfunc_165(); virtual void vfunc_166(); virtual void vfunc_167(); virtual void vfunc_168(); virtual void vfunc_169();
    virtual void vfunc_170(); virtual void vfunc_171(); virtual void vfunc_172(); virtual void vfunc_173(); virtual void vfunc_174(); virtual void vfunc_175();
    virtual void vfunc_176(); virtual void vfunc_177(); virtual void vfunc_178(); virtual void vfunc_179(); virtual void vfunc_180(); virtual void vfunc_181();
    virtual void vfunc_182(); virtual void vfunc_183(); virtual void vfunc_184(); virtual void vfunc_185(); virtual void vfunc_186(); virtual void vfunc_187();
    virtual void vfunc_188(); virtual void vfunc_189(); virtual void vfunc_190(); virtual void vfunc_191(); virtual void vfunc_192(); virtual void vfunc_193();
    virtual void vfunc_194(); virtual void vfunc_195(); virtual void vfunc_196(); virtual void vfunc_197(); virtual void vfunc_198(); virtual void vfunc_199();
    virtual void vfunc_200(); virtual void vfunc_201(); virtual void vfunc_202(); virtual void vfunc_203(); virtual void vfunc_204(); virtual void vfunc_205();
    virtual void vfunc_206(); virtual void vfunc_207();
    virtual void getMatrix(int which, float *m);
};
class MatrixAttrSlots {
public:
    virtual void vfunc_2(); virtual void vfunc_3(); virtual void vfunc_4(); virtual void vfunc_5(); virtual void vfunc_6(); virtual void vfunc_7();
    virtual void vfunc_8(); virtual void vfunc_9(); virtual void vfunc_10(); virtual void vfunc_11(); virtual void vfunc_12(); virtual void vfunc_13();
    virtual void vfunc_14(); virtual void vfunc_15(); virtual void vfunc_16(); virtual void vfunc_17(); virtual void vfunc_18(); virtual void vfunc_19();
    virtual void vfunc_20(); virtual void vfunc_21(); virtual void vfunc_22(); virtual void vfunc_23(); virtual void vfunc_24(); virtual void vfunc_25();
    virtual void vfunc_26(); virtual void vfunc_27(); virtual void vfunc_28(); virtual void vfunc_29(); virtual void vfunc_30(); virtual void vfunc_31();
    virtual void setMatrix(const float *m);
};
struct OO;
class DW4VC_200_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual int vX(); };
class DW4VC_212_3 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual int vX(int, int *, int *); };
class DW4VC_216_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual int vX(int); };
class DW4VC_220_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual int vX(int); };
class DW4VC_224_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual int vX(int); };
class DW4VC_228_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual int vX(int); };
struct OO { char pad[20]; int f20; char pad2[12]; int f36; int f40; int f44; int f48; int f52; int f56; int f60; };
typedef struct R_13fea0 { int w0; int refs; } R_13fea0;
class DW4VC_188 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual int vX(int); };
struct X_13fea0 { char pad0[12]; int w12; char pad1[4]; int w20; char pad2[40]; R_13fea0 *obj; };
extern "C" int igVisualContext_GetScissorType(igVisualContext *self);
class Destination : public igObject { public: };
class Renderable { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void vX(int); };
struct Attr { char p[12]; Destination *f12; };
/* Stand-in receiver: the dummy virtuals only put `vX` at the right vtable slot. */
class BoundRenderDestinationVtable { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual int vX(); };

extern "C" void FUN_00140360(void *arg0, int arg1);

class DW4VC_136_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual int vX(int); };


extern "C" char *igTextureAttr_GetFileName(char *arg0);
typedef struct V3 { int a; int b; float c; } V3;
extern "C" char DAT_00560000[];
extern "C" void igTextureBindAttr_SetFastApply(int arg0);


class igTextureCoordSourceAttrView;
class VisualContextDispatch {
public:
    virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void slot3(); virtual void slot4(); virtual void slot5(); virtual void slot6(); virtual void slot7(); virtual void slot8(); virtual void slot9();
    virtual void slot10(); virtual void slot11(); virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15(); virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
    virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23(); virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27(); virtual void slot28(); virtual void slot29();
    virtual void slot30(); virtual void slot31(); virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35(); virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
    virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43(); virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47(); virtual void slot48(); virtual void slot49();
    virtual void slot50(); virtual void slot51(); virtual void slot52(); virtual void slot53(); virtual void slot54(); virtual void slot55(); virtual void slot56(); virtual void slot57(); virtual void slot58(); virtual void slot59();
    virtual void slot60(); virtual void slot61(); virtual void slot62(); virtual void slot63(); virtual void slot64(); virtual void slot65(); virtual void slot66(); virtual void slot67(); virtual void slot68(); virtual void slot69();
    virtual void slot70(); virtual void slot71(); virtual void slot72(); virtual void slot73(); virtual void slot74(); virtual void slot75(); virtual void slot76(); virtual void slot77(); virtual void slot78(); virtual void slot79();
    virtual void slot80(); virtual void slot81(); virtual void slot82(); virtual void slot83(); virtual void slot84(); virtual void slot85(); virtual void slot86(); virtual void slot87(); virtual void slot88(); virtual void slot89();
    virtual void slot90(); virtual void slot91(); virtual void slot92(); virtual void slot93(); virtual void slot94(); virtual void slot95(); virtual void slot96(); virtual void slot97(); virtual void slot98(); virtual void slot99();
    virtual void slot100(); virtual void slot101(); virtual void slot102(); virtual void slot103(); virtual void slot104(); virtual void slot105(); virtual void slot106(); virtual void slot107(); virtual void slot108(); virtual void slot109();
    virtual void slot110(); virtual void slot111(); virtual void slot112(); virtual void slot113(); virtual void slot114(); virtual void slot115(); virtual void slot116(); virtual void slot117(); virtual void slot118(); virtual void slot119();
    virtual void slot120(); virtual void slot121(); virtual void slot122(); virtual void slot123(); virtual void slot124(); virtual void slot125(); virtual void slot126(); virtual void slot127(); virtual void slot128(); virtual void slot129();
    virtual void slot130(); virtual void slot131(); virtual void slot132(); virtual void slot133(); virtual void slot134(); virtual void slot135(); virtual void slot136(); virtual void slot137(); virtual void slot138(); virtual void slot139();
    virtual void slot140(); virtual void slot141(); virtual void slot142(); virtual void slot143(); virtual void slot144(); virtual void slot145(); virtual void slot146(); virtual void slot147(); virtual void slot148();

    virtual void getTextureCoordSource(int unitID, int *mode, int *texCoordIndex);
};
extern "C" void igPsx2VisualContext_SetTextureSourceLevel(igObject *context, int texture, igImage *image, int level);
extern "C" void * DAT_0055ed08[4];
extern "C" void FUN_001412a0(void);
class igTextureFunctionAttrView;

class G { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual int v120(int, int, unsigned); virtual int v124(int, int, int); };
class igTextureMatrixAttrView;
typedef struct S_141630 { char p0[12]; bool b; char pad[3]; int f16; } S_141630;

class igTextureMatrixStateAttrView;

class igTextureStateAttrView;

typedef struct S_141840 { char pad[10]; short s10; char pad2[4]; int i16; } S_141840;
class igTextureUnloadAttrView;
class V128 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual int vX(int *); };
class igVertexBlendMatrixAttrView;
struct Src { char p0[8]; int n; int p12; int *d; };
struct S_141e10 { char p0[12]; unsigned char f12; unsigned char f13; char p14[2]; int f16; int f20; struct Src *f24; };
#include "dw4/datapump/igMatrixObject.h"

extern "C" void igVertexBlendMatrixListAttr_apply(struct S_141e10 *arg0, igPsx2VisualContext *arg1);
extern "C" void igVertexBlendMatrixListAttr_SynchronizeDefault(void);

extern "C" void igVertexBlendMatrixListAttr_ReleaseDefaults(igVertexBlendMatrixListAttr *self);


extern "C" igMetaObject *igVertexBlendMatrixListAttr_GetMeta(void);
typedef struct S1_142400 { char pad4[4]; int f4; } S1_142400;
typedef struct S0_142400 { char pad12[12]; int fC; } S0_142400;
typedef struct S_temp_a0_142400 { char pad4[4]; int f4; } S_temp_a0_142400;
extern "C" igMetaObject *igParticleAttr_GetMeta(void);
class DW4VC_152_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual int vX(); };
extern "C" void igParticleAttr_Reset(igParticleAttr *self);
typedef struct Obj_1429d0 { char pad[20]; int f20; int f24; } Obj_1429d0;
typedef struct Obj_142a00 { char pad[16]; int f16; int f20; } Obj_142a00;
extern "C" int igVec3fList_GetMeta(void);

extern "C" int igNamedObject_GetMeta(void);
extern "C" int igVec3fList_GetElementSize(void);

#include "dw4/attrs/igObjectList.h"
extern "C" igMetaObject *igLightStateAttrList_GetElementMeta(void);
extern "C" igMetaObject *igLightList_GetElementMeta(void);
extern "C" igMetaObject *igTextureList_GetElementMeta(void);

extern "C" int igImageMipMapList_GetElementMeta(void);
extern "C" void igVec3fList_TrimCapacity(igDataList *arg0);

#endif
