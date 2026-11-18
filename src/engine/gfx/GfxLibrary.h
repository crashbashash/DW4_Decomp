#ifndef DW4_GFX_LIBRARY_H
#define DW4_GFX_LIBRARY_H

#include "dw4/support/reflected.h"
#include "dw4/core/igSmartPointer.h"
#include "dw4/support/typecast.h"
#include "dw4/core/igobject_release.h"
#include "dw4/core/igTDataList.h"
#include "dw4/maths/igMatrix44f.h"
#include "dw4/maths/igVec3f.h"
#include "dw4/support/ClassRegistration.h"
#include "dw4/gfx/igVisualContext.h"
#include "dw4/core/igDirEntry.h"
#include "dw4/gfx/png.h"
#include "dw4/gfx/igImage.h"
#include "dw4/gfx/igParticleArray.h"
#include "dw4/gfx/igPsx2VisualContext.h"
#include "dw4/gfx/igVertexArray.h"
#include "dw4/gfx/igVertexArray2.h"
#include "dw4/gfx/GfxMetaEnums.h"
#include <string.h>
#include <stdio.h>
#include "dw4/support/softfloat.h"
#include "dw4/p2/p2viewport.h"
#include "dw4/p2/p2texture.h"
#include "dw4/p2/p2swap.h"
#include "dw4/p2/p2pool.h"
#include "dw4/p2/p2multipass.h"
#include "dw4/p2/p2lighting.h"
#include "dw4/p2/p2gs.h"
#include "dw4/p2/p2draw.h"
#include "dw4/p2/p2core.h"
#include "dw4/core/igTimer.h"
#include "dw4/core/igTimerDispatchView.h"
#include "dw4/core/igStringObj.h"
#include "dw4/core/igResult.h"
#include "dw4/core/igRegistry.h"
#include "dw4/core/igObjectSystem.h"
#include "dw4/core/igObjectList.h"
#include "dw4/core/igObject.h"
#include "dw4/core/igNamedObject.h"
#include "dw4/core/igMetaObject.h"
#include "dw4/core/igMetaField.h"
#include "dw4/core/igMemoryPoolContext.h"
#include "dw4/core/igMemory.h"
#include "dw4/core/igDataLists.h"
#include "dw4/p2/dmaChannel.h"
#include "dw4/cri/sndf.h"
#include "dw4/cri/cri_adxt.h"
#include "dw4/core/StringPool.h"
#include "dw4/game/ParticleArray.h"
#include <math.h>
#include "dw4/maths/igVec4fMetaField.h"
#include "dw4/core/igNonRefCountedObjectList.h"
#include "dw4/core/igMemoryRefMetaField.h"
#include "dw4/maths/igMatrix44fMetaField.h"
#include "dw4/maths/igMathConstants.h"
#include "dw4/core/igIntList.h"
#include "dw4/core/igExternalDirEntry.h"
#include "dw4/core/igContext.h"
#include "dw4/core/igCompoundMetaField.h"
#include "dw4/maths/igVec3f.h"

struct Rc_17f2b0;

typedef void (*igMetaObjectCallback)();
#include "dw4/core/igBoolArrayMetaField.h"
#include "dw4/core/igBoolMetaField.h"
#include "dw4/core/igCharMetaField.h"
#include "dw4/core/igEnumArrayMetaField.h"
#include "dw4/core/igEnumMetaField.h"
#include "dw4/core/igFloatMetaField.h"
#include "dw4/core/igIntArrayMetaField.h"
#include "dw4/core/igIntMetaField.h"
#include "dw4/core/igLongMetaField.h"
#include "dw4/core/igMetaEnum.h"
#include "dw4/core/igObjectRefArrayMetaField.h"
#include "dw4/core/igObjectRefMetaField.h"
#include "dw4/core/igRawRefMetaField.h"
#include "dw4/core/igStringMetaField.h"
#include "dw4/core/igStructMetaField.h"
#include "dw4/core/igUnsignedCharMetaField.h"
#include "dw4/core/igUnsignedIntArrayMetaField.h"
#include "dw4/core/igUnsignedIntMetaField.h"
#include "dw4/core/igUnsignedLongMetaField.h"
#include "dw4/support/emptyString.h"
#include "dw4/core/internalNonRefCountedObjectList.h"
#include "dw4/support/list-services.h"
#include "dw4/maths/igVec4f.h"
#include "dw4/core/igCharList.h"
#include "dw4/core/igContextExt.h"
#include "dw4/core/igFile.h"
#include "dw4/core/igFloatList.h"
#include "dw4/core/igResource.h"
#include "dw4/core/igShortList.h"
#include "dw4/core/igUnsignedCharList.h"
#include "dw4/core/igUnsignedIntList.h"
#include "dw4/core/igUnsignedShortList.h"
#include "dw4/maths/igVec2fList.h"
#include "dw4/maths/igVec3fList.h"
#include "dw4/maths/igVec4ucList.h"
#include "dw4/gfx/igVertexArrayLock.h"
#include "dw4/gfx/igPointSpriteExt.h"
#include "dw4/core/igMemoryPool.h"
#include "dw4/core/igPointerList.h"
#include "dw4/core/igReport.h"
#include "dw4/core/igContextList.h"
#include "dw4/core/igDriverDatabase.h"
#include "dw4/runtime/New.h"
#include "dw4/datapump/igMatrixStack.h"
#include "dw4/p2/p2textureCalls.h"
#include "dw4/gfx/igGenericCapabilityManager.h"
#include "dw4/gfx/igVisualContextCapabilityManager.h"
#include "dw4/gfx/igPrimLengthArray.h"

extern "C" igMetaObject *g_igVertexArray_metaObject;
extern "C" igMetaObject *g_igScissorExt_metaObject;
extern "C" igMetaObject *g_igPrimLengthArray_metaObject;
extern "C" igMetaObject *g_igImageUtils_metaObject;
extern "C" igMetaObject *g_igDisableExt_metaObject;
extern "C" igMetaObject *g_igCapabilityManager_metaObject;
extern "C" igMetaObject *g_igPsx2LongList_metaObject;


struct StringRef {
    char *p;
    StringRef();
    StringRef(char *s) : p(s) {}
    ~StringRef() {
        if (p != 0) {
            int *header = (int *)p - 2;
            int count = header[1] - 1;
            header[1] = count;
            if (count == 0) {
                StringChunk_ReleaseHeader((StringChunk *)header[0], (StringTokenHeader *)header);
            }
        }
    }
};
extern "C" int IG_GFX_INDEX_DATA_SIZE_GetMetaEnum(void);
extern "C" int IG_GFX_SCISSOR_TYPE_GetMetaEnum(void);
extern "C" int IG_GFX_STENCIL_OPERATION_GetMetaEnum(void);
extern "C" int IG_GFX_STENCIL_FUNCTION_GetMetaEnum(void);
extern "C" int IG_GFX_FOG_MODE_GetMetaEnum(void);
extern "C" int IG_GFX_RENDER_MODE_GetMetaEnum(void);
extern "C" int IG_GFX_CULL_FACE_MODE_GetMetaEnum(void);
extern "C" int IG_GFX_SHADING_MODE_GetMetaEnum(void);
extern "C" int IG_GFX_ALPHA_FUNCTION_GetMetaEnum(void);
extern "C" int IG_GFX_BLENDING_FUNCTION_GetMetaEnum(void);
extern "C" int IG_GFX_TEXTURE_COORD_SOURCE_GetMetaEnum(void);
extern "C" int IG_GFX_PIXEL_PIPELINE_MODE_GetMetaEnum(void);
extern "C" int IG_GFX_TEXTURE_MODE_GetMetaEnum(void);
extern "C" int IG_GFX_TEXTURE_SOURCE_GetMetaEnum(void);
extern "C" int IG_GFX_TEXTURE_WRAP_GetMetaEnum(void);
extern "C" int IG_GFX_LIGHT_TYPE_GetMetaEnum(void);
extern "C" int IG_GFX_DRAW_GetMetaEnum(void);
extern "C" int IG_GFX_RENDERDESTINATION_TYPE_GetMetaEnum(void);
extern "C" int IG_GFX_STATISTIC_GetMetaEnum(void);
extern "C" void FUN_00149bc0(void);

extern "C" igMetaObject *igVisualContextCapabilityManager_GetMetaObject(void);
struct T { int word0; int references; };
extern "C" int g_igVisualContextCapabilityManager_vtable[4];

struct Obj {
    int *vt; int w0[1]; T *ref; int w1[1]; 
    inline void release() {
        T **self = &ref;
        if (self) {
            T *object = *self;
            if (object) {
                --object->references;
                if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
                    igObject_Destroy((igObject *)object);
            }
        }
    }
};

extern "C" int igVisualContextCapabilityManager_GetVTable(void);
extern "C" void igVisualContextCapabilityManager_EnsureRegistered(void);
extern "C" igMetaObject *igCapabilityManager_GetPublishedMetaObject(void);

extern "C" CallbackArray *igVisualContextCapabilityManager_Register(void);
extern "C" void igVisualContextCapabilityManager_GetMetaObjectFunction(void);
extern "C" igMetaObject *igCapabilityManager_GetPublishedMetaObject(void);

extern "C" void igVisualContextCapabilityManager_InitFields(void);
extern "C" int igVisualContextList_Create(int arg0);
extern "C" igMetaObject *igVisualContextList_GetMetaObject(void);
typedef struct { int *vt; int pad[7]; } Obj_149f30;
extern "C" int g_igVisualContextList_vtable[4];
extern "C" int igVisualContextList_GetVTable(void);
extern "C" void igVisualContextList_EnsureRegistered(void);

extern "C" CallbackArray *igVisualContextList_Register(void);
extern "C" void igVisualContextList_GetMetaObjectFunction(void);

extern "C" igMetaObject *igVisualContext_GetMetaObject(void);

extern "C" CallbackArray *igVisualContext_Register(void);
extern "C" void igVisualContext_GetMetaObjectFunction(void);
extern "C" int FUN_0014a170(void);
extern "C" int FUN_001888e0(...);
extern "C" void igVisualContext_InitFields(void);
extern "C" void igPsx2VisualContext_GetMetaObjectFunction(void);
extern "C" class igVertexArray2HelperAccess *igVertexArray2Helper_Create(int arg0);
extern "C" igMetaObject *igVertexArray2Helper_GetMetaObject(void);

extern "C" int g_igVertexArray2Helper_vtable[4];
struct Obj_14a560 {
    int *vt; char p4[4]; char *m8; T *m12; 
    inline void rel8() {
        char **self = &m8;
        if (self) {
            char *o = *self;
            if (o) {
                int *a1 = (int *)(o - 8);
                int v0 = *(int *)(o - 4) - 1;
                *(int *)(o - 4) = v0;
                if (v0 == 0) {
                    StringChunk_ReleaseHeader((StringChunk *)*a1, (StringTokenHeader *)a1);
                }
            }
        }
    }
    inline void rel12() {
        T **self = &m12;
        if (self) {
            T *object = *self;
            if (object) {
                --object->references;
                if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
                    igObject_Destroy((igObject *)object);
            }
        }
    }
};
extern "C" int igVertexArray2Helper_GetVTable(void);
extern "C" void igVertexArray2Helper_EnsureRegistered(void);

extern "C" CallbackArray *igVertexArray2Helper_Register(void);
extern "C" void igVertexArray2Helper_GetMetaObjectFunction(void);

extern "C" int FUN_0014a6e0(void);
extern "C" void igVertexArray2Helper_InitFields(void);
extern "C" int igVertexArray2_Create(int arg0);
extern "C" igMetaObject *igVertexArray2_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igVertexArray2_GetMetaObject(void);
struct Obj_14a860 { int *vt; int w[7]; };
extern "C" int g_igVertexArray2_vtable[4];
extern "C" int igVertexArray2_GetVTable(void);

struct Obj_14a910 {
    int *vt; char p4[4]; char *m8; T *m12; T *m16; T *m20;
    inline void rel(T **self) {
        if (self) {
            T *object = *self;
            if (object) {
                --object->references;
                if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
                    igObject_Destroy((igObject *)object);
            }
        }
    }
    inline void relS(char **self) {
        if (self) {
            char *o = *self;
            if (o) {
                int *a1 = (int *)(o - 8);
                int v0 = *(int *)(o - 4) - 1;
                *(int *)(o - 4) = v0;
                if (v0 == 0) {
                    StringChunk_ReleaseHeader((StringChunk *)*a1, (StringTokenHeader *)a1);
                }
            }
        }
    }
};
extern "C" Obj_14a910 *FUN_0014a910(Obj_14a910 *arg0, short arg1);
typedef struct S_temp_a0 { char pad4[4]; int f4; } S_temp_a0;
/* Deleting destructor; the deletion flag is a signed short. */
typedef struct ObjectRefTarget { int word0; int references; } ObjectRefTarget;
typedef struct ObjectRefWord { ObjectRefTarget *value; } ObjectRefWord;
extern "C" ObjectRefWord *FUN_0014aaf0(ObjectRefWord *self,int delete_storage);
extern "C" void igVertexArray2_EnsureRegistered(void);
extern "C" CallbackArray *igVertexArray2_Register(void);
extern "C" void igVertexArray2_GetMetaObjectFunction(void);

extern "C" void igVertexArray2_InitFields(void);
extern "C" void igPsx2VertexArray2_GetMetaObjectFunction(void);
extern "C" int IG_VERTEX_STREAM_COMPILE_MODE_GetMetaEnum(void);
extern "C" int IG_VERTEX_ACCESS_MODE_GetMetaEnum(void);
extern "C" int igVertexStream_Create(int arg0);
extern "C" igMetaObject *igVertexStream_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igVertexStream_GetMetaObject(void);
typedef struct S_ref { char pad4[4]; int f4; } S_ref;
union U { int vt; char b[48]; };
extern "C" int g_igVertexStream_vtable[4];
extern "C" int igVertexStream_GetVTable(void);
extern "C" void igVertexStream_EnsureRegistered(void);
extern "C" CallbackArray *igVertexStream_Register(void);
extern "C" void igVertexStream_GetMetaObjectFunction(void);
extern "C" void igVertexStream_InitFields(void);
extern "C" void igPsx2VertexStream_GetMetaObjectFunction(void);
extern "C" int igVertexDataList_Create(int arg0);
extern "C" igMetaObject *igVertexDataList_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igVertexDataList_GetMetaObject(void);
extern "C" int g_igVertexDataList_vtable[4];
union U_14b260 { int vt; char b[32]; };
extern "C" int igVertexDataList_GetVTable(void);
extern "C" void igVertexDataList_EnsureRegistered(void);

extern "C" CallbackArray *igVertexDataList_Register(void);
extern "C" void igVertexDataList_GetMetaObjectFunction(void);
extern "C" int IG_VERTEX_COMPONENT_TYPE_GetMetaEnum(void);
extern "C" int igVertexData_Create(int arg0);
extern "C" igMetaObject *igVertexData_GetMetaObject(void);
extern "C" int g_igVertexData_vtable[4];
extern "C" int igVertexData_GetVTable(void);
extern "C" void igVertexData_EnsureRegistered(void);
extern "C" CallbackArray *igVertexData_Register(void);
extern "C" void igVertexData_GetMetaObjectFunction(void);
extern "C" void igVertexData_InitFields(void);
extern "C" int igVertexArray1_1_Create(int arg0);
extern "C" igMetaObject *igVertexArray1_1_GetMetaObject(void);
extern "C" igMetaObject *igVertexArray_GetPublishedMetaObject(void);
extern "C" CallbackArray *igVertexArray1_1_Register(void);
extern "C" void igVertexArray1_1_GetMetaObjectFunction(void);
extern "C" igMetaObject *igVertexArray_GetPublishedMetaObject(void);
struct F { char p[20]; short f20; char p1[14]; char f36; char p2; char f38; char f39; char f40; char p3[12]; char f53; char p4[2]; int f56; int f60; char f64; char f65; };
extern "C" void igVertexArray1_1_InitFields(void);
extern "C" void igPsx2VertexArray1_1_GetMetaObjectFunction(void);
extern "C" void thunk_FUN_0015e010(void);
extern "C" igMetaObject *igVertexArray_GetMetaObject(void);

extern "C" CallbackArray *igVertexArray_Register(void);
extern "C" void igVertexArray_GetMetaObjectFunction(void);
extern "C" void igVertexArray_InitFields(void);
extern "C" igMetaObject *igUserUCodeExt_GetMetaObject(void);
extern "C" void igUserUCodeExt_EnsureRegistered(void);
extern "C" igMetaObject *igContextExt_GetPublishedMetaObject(void);
extern "C" CallbackArray *igUserUCodeExt_Register(void);
extern "C" void igUserUCodeExt_GetMetaObjectFunction(void);
extern "C" int FUN_0014bc40(void);
extern "C" void FUN_0014bc50(void);
extern "C" void igPsx2UserUCodeExt_GetMetaObjectFunction(void);
extern "C" igMetaObject *igScissorExt_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igScissorExt_GetMetaObject(void);
extern "C" void igScissorExt_EnsureRegistered(void);
extern "C" void igScissorExt_InitFields_0014bdb0(void);
extern "C" CallbackArray *igScissorExt_Register(void);
extern "C" void igScissorExt_GetMetaObjectFunction(void);
extern "C" void FUN_0014bdb0(void);
extern "C" void igPsx2ScissorExt_GetMetaObjectFunction(void);
extern "C" igMetaObject *igPrimLengthArray1_1_GetMetaObject(void);
struct Obj_14be30 { int *vt; char pad[28]; };
extern "C" int g_igPrimLengthArray1_1_vtable[4];
extern "C" int igPrimLengthArray1_1_GetVTable(void);
extern "C" igMetaObject *igPrimLengthArray_GetPublishedMetaObject(void);
extern "C" CallbackArray *igPrimLengthArray1_1_Register(void);
extern "C" void igPrimLengthArray1_1_GetMetaObjectFunction(void);
extern "C" igMetaObject *igPrimLengthArray_GetPublishedMetaObject(void);

struct T_14bf10 { int vt; int ref; char pad8[20]; int f28; char pad32[21]; char f53; char pad54[2]; int f56; int f60; char f64; char f65; };
class DW4VC_84_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual T_14bf10 *vX(int); };
extern "C" void igPrimLengthArray1_1_InitFields(void);
extern "C" igMetaObject *igPrimLengthArray_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igPrimLengthArray_GetMetaObject(void);
extern "C" void igPrimLengthArray_EnsureRegistered(void);
extern "C" CallbackArray *igPrimLengthArray_Register(void);
extern "C" void igPrimLengthArray_GetMetaObjectFunction(void);
extern "C" void igPrimLengthArray_InitFields(void);
extern "C" int IG_GFX_SPRITE_TYPE_GetMetaEnum(void);
extern "C" int IG_GFX_SPRITE_SIZE_SPACE_GetMetaEnum(void);
extern "C" igMetaObject *igPointSpriteExt_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igPointSpriteExt_GetMetaObject(void);
extern "C" int g_igPointSpriteExt_vtable[4];
struct PointSpriteExtInstance { int *vt; int f4; int f8; int f12; int f16; int f20; int f24; int f28; char t[368]; };
extern "C" int igPointSpriteExt_GetVTable(void);
extern "C" int DAT_00527020[4];
extern "C" int DAT_00530a10[4];
struct S1 { char pad4[4]; int f4; };
struct O { int *vt; char pad4[4]; S1 *m8; char pad12[4]; S1 *m16; char pad20[4]; S1 *m24; };
extern "C" O *FUN_0014c440(O *arg0, short arg1);
struct O_14c580 { int *vt; char pad4[4]; S1 *m8; char pad12[4]; S1 *m16; };
extern "C" O_14c580 *FUN_0014c580(O_14c580 *arg0, short arg1);
extern "C" void igPointSpriteExt_EnsureRegistered(void);
extern "C" CallbackArray *igPointSpriteExt_Register(void);
extern "C" void igPointSpriteExt_GetMetaObjectFunction(void);
extern "C" void igPointSpriteExt_InitFields(void);
extern "C" void igPsx2PointSpriteExt_GetMetaObjectFunction(void);
extern "C" int IG_GFX_PARTICLE_ARRAY_LIFE_CONTROL_GetMetaEnum(void);
extern "C" igMetaObject *igParticleArray_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igParticleArray_GetMetaObject(void);
struct Obj_14ca20 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; int w12; int w13; int w14; int w15; int w16; int w17; int w18; int w19; int w20; int w21; int w22; int w23; };
extern "C" void** FUN_00137260(void**, short);
extern "C" int g_igParticleArray_vtable[4];
extern "C" int igParticleArray_GetVTable(void);
extern "C" void **FUN_0014cc90(void **arg0, short arg1);
extern "C" ObjectRefWord *FUN_0014cd10(ObjectRefWord *self,int delete_storage);
extern "C" void FUN_0014cd90(void);
extern "C" void igParticleArray_GetMetaObjectFunction(void);
extern "C" void igParticleArray_InitFields(void);
extern "C" void igPsx2ParticleArray_GetMetaObjectFunction(void);
extern "C" int IG_GFX_PARTICLE_COORD_GetMetaEnum(void);
extern "C" int igParticleFormat_Create(int arg0);
extern "C" igMetaObject *igParticleFormat_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igParticleFormat_GetMetaObject(void);
extern "C" int g_igParticleFormat_vtable[4];
struct Obj_14d150 { int *vt; char pad[44]; };
extern "C" int igParticleFormat_GetVTable(void);
extern "C" CallbackArray *igParticleFormat_Register(void);
extern "C" void igParticleFormat_GetMetaObjectFunction(void);
extern "C" int X0_0014d010[4];
extern "C" int X1_0014d010[4];
extern "C" int X2_0014d010[4];
extern "C" int X3_0014d010[4];
extern "C" int X4_0014d010[4];
extern "C" int X5_0014d010[4];
extern "C" int X6_0014d010[4];
extern "C" int DAT_0014d010[4];
extern "C" void igParticleFormat_InitFields(void);
extern "C" int TEXTURE_ARGUMENT_GetMetaEnum(void);
extern "C" int TEXTURE_STAGE_TYPE_GetMetaEnum(void);
extern "C" int TEXTURE_FUNCTION_TYPE_GetMetaEnum(void);
extern "C" igMetaObject *igMultiTextureExt_GetMetaObject(void);
extern "C" void igMultiTextureExt_EnsureRegistered(void);
extern "C" void igMultiTextureExt_InitFields_0014d650(void);
extern "C" CallbackArray *igMultiTextureExt_Register(void);
extern "C" void igMultiTextureExt_GetMetaObjectFunction(void);
extern "C" void FUN_0014d650(void);
extern "C" void igPsx2MultiTextureExt_GetMetaObjectFunction(void);
extern "C" igMetaObject *igLineWidthExt_GetMetaObject(void);
extern "C" void igLineWidthExt_EnsureRegistered(void);
extern "C" void thunk_igLineWidthExt_GetMetaObject_0014d750(void);
extern "C" CallbackArray *igLineWidthExt_Register(void);
extern "C" void igLineWidthExt_GetMetaObjectFunction(void);
extern "C" void igLineWidthExt_InitFields(void);
extern "C" igMetaObject *igIndexArray_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igIndexArray_GetMetaObject(void);
extern "C" CallbackArray *igIndexArray_Register(void);
extern "C" void igIndexArray_GetMetaObjectFunction(void);
extern "C" void igIndexArray_InitFields(void);
extern "C" void igPsx2IndexArray_GetMetaObjectFunction(void);
extern "C" igMetaObject *igImageLoader_GetMetaObject(void);
extern "C" void igImageLoader_EnsureRegistered(void);
extern "C" igMetaObject *igImageUtils_GetPublishedMetaObject(void);
extern "C" CallbackArray *igImageLoader_Register(void);
extern "C" void igImageLoader_GetMetaObjectFunction(void);
extern "C" igMetaObject *igImageUtils_GetPublishedMetaObject(void);
extern "C" int igImageConvert_Create(int arg0);
extern "C" igMetaObject *igImageConvert_GetMetaObject(void);
extern "C" void igImageConvert_EnsureRegistered(void);
extern "C" void igImageConvert_SetAbstractProxy_0014dc40(void);
extern "C" CallbackArray *igImageConvert_Register(void);
extern "C" void igImageConvert_GetMetaObjectFunction(void);
extern "C" void FUN_0014dc40(void);
extern "C" void igPsx2ImageConvert_GetMetaObjectFunction(void);
extern "C" igMetaObject *igImageUtils_GetMetaObject(void);
extern "C" void igImageUtils_EnsureRegistered(void);
extern "C" CallbackArray *igImageUtils_Register(void);
extern "C" void igImageUtils_GetMetaObjectFunction(void);
struct R { int vt; unsigned int rc; };
extern "C" struct R **FUN_0014dd40(struct R **arg0, short arg1);
extern "C" igMetaObject *igMemoryImage_GetMetaObject(void);
extern "C" void igMemoryImage_EnsureRegistered(void);
extern "C" igMetaObject *igImage_GetPublishedMetaObject(void);
extern "C" CallbackArray *igMemoryImage_Register(void);
extern "C" void igMemoryImage_GetMetaObjectFunction(void);
extern "C" igMetaObject *FUN_0014de90(void);
extern "C" igMetaObject *igFileImage_GetMetaObject(void);
extern "C" void igFileImage_EnsureRegistered(void);
extern "C" CallbackArray *igFileImage_Register(void);
extern "C" void igFileImage_GetMetaObjectFunction(void);
extern "C" igMetaObject *igImage_GetMetaObject(void);
extern "C" CallbackArray *igImage_Register(void);
extern "C" void igImage_GetMetaObjectFunction(void);
extern "C" void igImage_InitFields(void);
extern "C" void igPsx2Image_GetMetaObjectFunction(void);
extern "C" void thunk_FUN_00156300(void);
extern "C" int CONTEXT_TRACKABLE_GetMetaEnum(void);
extern "C" igMetaObject *igTrackedElementMetaField_GetMetaObject(void);

extern "C" int g_igTrackedElementMetaField_vtable[4];

union U_14e350 { int vt; char b[64]; };
extern "C" int igTrackedElementMetaField_GetVTable(void);

extern "C" CallbackArray *igTrackedElementMetaField_Register(void);
extern "C" void igTrackedElementMetaField_GetMetaObjectFunction(void);
extern "C" int FUN_0014e530(void);
typedef struct Q { char pad4[4]; int f4; char pad12[10]; short f18; } Q;
typedef struct R_14e540 { char pad[12]; int f12; } R_14e540;


extern "C" void FUN_0014e540(void);
extern "C" int Gap__Gfx__igTrackedElementMetaField__vfunc_25(void);
extern "C" void igTrackedElementMetaField_InitDefaults(void *arg0);

extern "C" void FUN_0014e630(int arg0);
extern "C" int igCustomStateFieldList_Create(int arg0);
extern "C" igMetaObject *igCustomStateFieldList_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igCustomStateFieldList_GetMetaObject(void);
struct Obj_14ea10 { int *vt; char pad[28]; };
extern "C" int g_igCustomStateFieldList_vtable[4];
extern "C" int igCustomStateFieldList_GetVTable(void);
extern "C" void igCustomStateFieldList_EnsureRegistered(void);
extern "C" CallbackArray *igCustomStateFieldList_Register(void);
extern "C" void igCustomStateFieldList_GetMetaObjectFunction(void);
extern "C" struct igCustomStateFieldView *igCustomStateField_Create(int arg0);
extern "C" igMetaObject *igCustomStateField_GetMetaObject(void);
extern "C" int g_igCustomStateField_vtable[4];
union U_14eb70 { int vt; char b[32]; };
extern "C" int igCustomStateField_GetVTable(void);
extern "C" void igCustomStateField_EnsureRegistered(void);
extern "C" CallbackArray *igCustomStateField_Register(void);
extern "C" void igCustomStateField_GetMetaObjectFunction(void);
extern "C" void igCustomStateField_InitFields(void);
extern "C" int igCustomStateCollectionList_Create(int arg0);
extern "C" igMetaObject *igCustomStateCollectionList_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igCustomStateCollectionList_GetMetaObject(void);
struct Obj_14eee0 { int *vt; char pad[28]; };
extern "C" int g_igCustomStateCollectionList_vtable[4];
extern "C" int igCustomStateCollectionList_GetVTable(void);
extern "C" void igCustomStateCollectionList_EnsureRegistered(void);
extern "C" CallbackArray *igCustomStateCollectionList_Register(void);
extern "C" void igCustomStateCollectionList_GetMetaObjectFunction(void);
extern "C" struct igCustomStateCollectionView *igCustomStateCollection_Create(int arg0);
extern "C" igMetaObject *igCustomStateCollection_GetMetaObject(void);
struct W { int *vt; int f[7]; };
extern "C" int g_igCustomStateCollection_vtable[4];
extern "C" int igCustomStateCollection_GetVTable(void);
extern "C" void igCustomStateCollection_EnsureRegistered(void);
extern "C" CallbackArray *igCustomStateCollection_Register(void);
extern "C" void igCustomStateCollection_GetMetaObjectFunction(void);
extern "C" void igCustomStateCollection_InitFields(void);
extern "C" igMetaObject *igCustomState_GetMetaObject(void);
extern "C" void igCustomState_EnsureRegistered(void);
extern "C" CallbackArray *igCustomState_Register(void);
extern "C" void igCustomState_GetMetaObjectFunction(void);
extern "C" igMetaObject *igGenericCapabilityManager_GetMetaObject(void);
struct Obj_14f350 { int *vt; char pad[4]; };
extern "C" int g_igGenericCapabilityManager_vtable[4];
extern "C" int igGenericCapabilityManager_GetVTable(void);
extern "C" void igGenericCapabilityManager_EnsureRegistered(void);
extern "C" CallbackArray *igGenericCapabilityManager_Register(void);
extern "C" void igGenericCapabilityManager_GetMetaObjectFunction(void);
extern "C" igMetaObject *igExternalImageEntry_GetMetaObject(void);
struct W_14f470 { int *vt; int f[11]; };
extern "C" int g_igExternalImageEntry_vtable[4];
extern "C" int igExternalImageEntry_GetVTable(void);
extern "C" int g_igDirEntry_vtable[4];

struct Str { int *p;
    ~Str() { if (p != 0) { int *h = p - 2; int r = p[-1] - 1; p[-1] = r; if (r == 0) StringChunk_ReleaseHeader((StringChunk *)*h, (StringTokenHeader *)h); } }
};
struct W_14f580 { int *vt; Str s4; Str s8; char pad[16]; Str s28; Str s32; char pad2[4]; Str s40; };
extern "C" W_14f580 *FUN_0014f580(W_14f580 *t, short flag);
extern "C" void thunk_igExternalImageEntry_GetMetaObject_0014f750(void);
extern "C" igMetaObject *igExternalDirEntry_GetPublishedMetaObject(void);
extern "C" CallbackArray *igExternalImageEntry_Register(void);
extern "C" void igExternalImageEntry_GetMetaObjectFunction(void);
extern "C" int FUN_0014f760(void);
extern "C" igMetaObject *igDisableExt_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igDisableExt_GetMetaObject(void);
extern "C" void igDisableExt_EnsureRegistered(void);
extern "C" void igDisableExt_SetAbstractProxy_0014f8a0(void);
extern "C" CallbackArray *igDisableExt_Register(void);
extern "C" void igDisableExt_GetMetaObjectFunction(void);
extern "C" void FUN_0014f8a0(void);
extern "C" void igPsx2DisableExt_GetMetaObjectFunction(void);
extern "C" igMetaObject *igDecalExt_GetMetaObject(void);
extern "C" void igDecalExt_EnsureRegistered(void);
extern "C" CallbackArray *igDecalExt_Register(void);
extern "C" void igDecalExt_GetMetaObjectFunction(void);
extern "C" void igDecalExt_InitFields(void);
extern "C" void igPsx2DecalExt_GetMetaObjectFunction(void);
extern "C" int igClut_Create(int arg0);
extern "C" igMetaObject *igClut_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igClut_GetMetaObject(void);
struct Obj_14fb30 { int *vt; char pad[28]; };
extern "C" int g_igClut_vtable[4];
extern "C" int igClut_GetVTable(void);
extern "C" CallbackArray *igClut_Register(void);
extern "C" void igClut_GetMetaObjectFunction(void);
extern "C" void igClut_InitFields(void);
extern "C" void igPsx2Clut_GetMetaObjectFunction(void);
extern "C" igMetaObject *igCapabilityManager_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igCapabilityManager_GetMetaObject(void);
extern "C" void igCapabilityManager_EnsureRegistered(void);
extern "C" CallbackArray *igCapabilityManager_Register(void);
extern "C" void igCapabilityManager_GetMetaObjectFunction(void);
extern "C" igMetaObject *igBlendEquationExt_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igBlendEquationExt_GetMetaObject(void);
extern "C" void igBlendEquationExt_EnsureRegistered(void);
extern "C" CallbackArray *igBlendEquationExt_Register(void);
extern "C" void igBlendEquationExt_GetMetaObjectFunction(void);
extern "C" void igBlendEquationExt_InitFields(void);
extern "C" void igPsx2BlendEquationExt_GetMetaObjectFunction(void);
extern "C" int igTgaLoader_Create(int arg0);
extern "C" igMetaObject *igTgaLoader_GetMetaObject(void);
typedef struct { int *vt; int p1[1]; int *ref; int pad[9]; } Obj_1500f0;
extern "C" int g_igTgaLoader_vtable[4];
extern "C" int igTgaLoader_GetVTable(void);
extern "C" void igTgaLoader_EnsureRegistered(void);
extern "C" igMetaObject *igImageLoader_GetPublishedMetaObject(void);
extern "C" CallbackArray *igTgaLoader_Register(void);
extern "C" void igTgaLoader_GetMetaObjectFunction(void);
extern "C" igMetaObject *igImageLoader_GetPublishedMetaObject(void);
extern "C" void igTgaLoader_InitFields(void);
extern "C" int igFileImagePng_Create(int arg0);
extern "C" igMetaObject *igFileImagePng_GetMetaObject(void);
extern "C" int g_igFileImagePng_vtable[4];
union U_150420 { int vt; char b[96]; };
extern "C" int igFileImagePng_GetVTable(void);
extern "C" int DAT_00526800[4];
extern "C" int DAT_00526c50[4];
struct S_150490 {
    void *f0;
    char pad0[64];
    void *f44;
    char pad1[16];
    void *f58;
};
extern "C" void *FUN_00150490(struct S_150490 *arg0, short arg1);
extern "C" void igFileImagePng_EnsureRegistered(void);
extern "C" igMetaObject *igFileImage_GetPublishedMetaObject(void);
extern "C" CallbackArray *igFileImagePng_Register(void);
extern "C" void igFileImagePng_GetMetaObjectFunction(void);
extern "C" igMetaObject *igFileImage_GetPublishedMetaObject(void);
extern "C" void igFileImagePng_InitFields(void);
struct VTableProbe { int *vt; char pad[1564]; };
struct Ref { int pad; union { int w; struct { unsigned cnt:23; unsigned f:9; } b; } u; };
struct S_temp_a0_1506b0 { char pad4[4]; int f4; };
struct O_1506b0 { S_temp_a0_1506b0 *m; };
extern "C" void** FUN_001372e0(igObject**, short);
extern "C" void** FUN_00137360(void**, long long);


extern "C" int g_igPsx2VisualContext_vtable[4];
extern "C" int DAT_00525e50[4];
struct Obj_1506b0 {
    int *vt; T *m4; T *m8; T *m12; T *m16; T *m20; T *m24; T *m28; T *m32; T *m36; T *m40; T *m44; T *m48; T *m52; T *m56;
    char p60[244]; T *m304; T *m308;
    inline void rel(T **self) {
        if (self) {
            T *object = *self;
            if (object) {
                --object->references;
                if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
                    igObject_Destroy((igObject *)object);
            }
        }
    }
};
extern "C" int IG_GFX_CLEARRENDERDESTINATION_TYPE_PSX2_GetMetaEnum(void);
extern "C" int IG_GFX_CLIPPING_TYPE_PSX2_GetMetaEnum(void);
extern "C" igMetaObject *igPsx2VisualContext_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igPsx2VisualContext_GetMetaObject(void);
extern "C" int igPsx2VisualContext_GetVTable(void);
extern "C" Obj_1506b0 *FUN_00150af0(Obj_1506b0 *arg0, short arg1);
extern "C" O_1506b0 *FUN_00150f30(O_1506b0 *arg0, short arg1);
extern "C" ObjectRefWord *FUN_00150fb0(ObjectRefWord *self,int delete_storage);
extern "C" void *FUN_00151030(void *arg0);
extern "C" int *FUN_00151050(int *p);
extern "C" int *FUN_00151060(int *p);
extern "C" int *FUN_00151070(int *p);
extern "C" int *FUN_00151080(int *p);
extern "C" int FUN_00151090(int a);
extern "C" int FUN_001510a0(int arg0);
extern "C" void *FUN_001510e0(igVisualContext *arg0);
extern "C" int *FUN_00151190(int *arg0);
extern "C" void igPsx2VisualContext_EnsureRegistered(void);
extern "C" CallbackArray *igPsx2VisualContext_Register(void);
extern "C" igMetaObject *igVisualContext_GetPublishedMetaObject(void);
extern "C" void igPsx2VisualContext_InitFields(void);
extern "C" igMetaObject *igPsx2VertexStream_GetMetaObject(void);
extern "C" int g_igPsx2VertexStream_vtable[4];
union U_151f70 { int vt; char b[140]; };
extern "C" int igPsx2VertexStream_GetVTable(void);
extern "C" void igPsx2VertexStream_EnsureRegistered(void);
extern "C" igMetaObject *igVertexStream_GetPublishedMetaObject(void);
extern "C" CallbackArray *igPsx2VertexStream_Register(void);
extern "C" igMetaObject *igVertexStream_GetPublishedMetaObject(void);
extern "C" void igPsx2VertexStream_InitFields(void);
extern "C" void thunk_FUN_0017f5a0(void);
extern "C" igMetaObject *igPsx2VertexArray2_GetMetaObject(void);
extern "C" int g_igPsx2VertexArray2_vtable[4];
union U_152250 { int vt; char b[32]; };
extern "C" int igPsx2VertexArray2_GetVTable(void);
extern "C" void igPsx2VertexArray2_EnsureRegistered(void);
extern "C" void thunk_igPsx2VertexArray2_GetMetaObject_0014acf0(void);
extern "C" igMetaObject *igVertexArray2_GetPublishedMetaObject(void);
extern "C" void igPsx2VertexArray2_InitFields_00152350(void);
extern "C" CallbackArray *igPsx2VertexArray2_Register(void);
extern "C" igMetaObject *igVertexArray2_GetPublishedMetaObject(void);
extern "C" void FUN_00152350(void);
extern "C" igMetaObject *igPsx2VertexArray1_1_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igPsx2VertexArray1_1_GetMetaObject(void);
struct Obj_152410 { int *vt; int w[35]; };
extern "C" int g_igPsx2VertexArray1_1_vtable[4];
extern "C" int igPsx2VertexArray1_1_GetVTable(void);
extern "C" int DAT_00526480[4];
struct S_1524c0 {
    void *f0;
    char pad[20];
    void *f18;
};
extern "C" void *FUN_001524c0(struct S_1524c0 *arg0, short arg1);
extern "C" void **FUN_00152560(void **arg0, short arg1);
extern "C" void igPsx2VertexArray1_1_EnsureRegistered(void);
extern "C" igMetaObject *igVertexArray1_1_GetPublishedMetaObject(void);
extern "C" CallbackArray *igPsx2VertexArray1_1_Register(void);
extern "C" igMetaObject *igVertexArray1_1_GetPublishedMetaObject(void);
extern "C" void igPsx2VertexArray1_1_InitFields(void);
extern "C" int igPsx2LongList_Create(int arg0);
extern "C" int igPsx2LongList_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igPsx2LongList_GetMetaObject(void);
struct Obj_1528a0 { int *vt; char pad[28]; };
extern "C" int g_igPsx2LongList_vtable[4];
extern "C" int igPsx2LongList_GetVTable(void);
extern "C" void igPsx2LongList_EnsureRegistered(void);

extern "C" void igPsx2LongList_InitFields_00152970(void);
extern "C" CallbackArray *igPsx2LongList_Register(void);
extern "C" void igPsx2LongList_GetMetaObjectFunction(void);
class DW4VC_84_1_152970 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual int vX(int); };
extern "C" void FUN_00152970(void);
extern "C" igMetaObject *igPsx2UserUCodeExt_GetMetaObject(void);
struct Obj_152a80 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; };
extern "C" int g_igPsx2UserUCodeExt_vtable[4];
extern "C" int igPsx2UserUCodeExt_GetVTable(void);
extern "C" int DAT_00526b70[4];
struct S_152b10 {
    void *f0;
    char pad0[4];
    void *f8;
    void *fC;
    void *f10;
};
extern "C" void *FUN_00152b10(struct S_152b10 *arg0, short arg1);
extern "C" ObjectRefWord *FUN_00152c10(ObjectRefWord *self,int delete_storage);
extern "C" void **FUN_00152c90(void **arg0, short arg1);
extern "C" void igPsx2UserUCodeExt_EnsureRegistered(void);
extern "C" igMetaObject *igUserUCodeExt_GetPublishedMetaObject(void);
extern "C" CallbackArray *igPsx2UserUCodeExt_Register(void);
extern "C" igMetaObject *FUN_00152da0(void);
extern "C" void igPsx2UserUCodeExt_InitFields(void);
extern "C" igMetaObject *igPsx2ScissorExt_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igPsx2ScissorExt_GetMetaObject(void);
extern "C" int g_igPsx2ScissorExt_vtable[4];
extern "C" int igPsx2ScissorExt_GetVTable(void);
extern "C" void igPsx2ScissorExt_EnsureRegistered(void);
extern "C" igMetaObject *igScissorExt_GetPublishedMetaObject(void);
extern "C" CallbackArray *igPsx2ScissorExt_Register(void);
extern "C" igMetaObject *igScissorExt_GetPublishedMetaObject(void);
extern "C" void igPsx2ScissorExt_InitFields(void);
extern "C" igMetaObject *igPsx2PointSpriteExt_GetMetaObject(void);
extern "C" int g_igPsx2PointSpriteExt_vtable[4];
struct O_1531c0 { int vt; int f4; int f8; int f12; int f16; int f20; int f24; int f28; char t[368]; };
extern "C" int igPsx2PointSpriteExt_GetVTable(void);
extern "C" void igPsx2PointSpriteExt_EnsureRegistered(void);
extern "C" igMetaObject *igPointSpriteExt_GetPublishedMetaObject(void);
extern "C" CallbackArray *igPsx2PointSpriteExt_Register(void);
extern "C" igMetaObject *igPointSpriteExt_GetPublishedMetaObject(void);
extern "C" void igPsx2PointSpriteExt_InitFields(void);
extern "C" igMetaObject *igPsx2ParticleArray_GetMetaObject(void);
extern "C" int g_igPsx2ParticleArray_vtable[4];
union U_1533f0 { int vt; char b[128]; };
extern "C" int igPsx2ParticleArray_GetVTable(void);
extern "C" void igPsx2ParticleArray_EnsureRegistered(void);
extern "C" CallbackArray *igPsx2ParticleArray_Register(void);
extern "C" igMetaObject *igParticleArray_GetPublishedMetaObject(void);
extern "C" void igPsx2ParticleArray_InitFields(void);
extern "C" int BLENDING_FUNCTION_ALPHA_PSX2_GetMetaEnum(void);
extern "C" int BLENDING_FUNCTION_COLOR_PSX2_GetMetaEnum(void);
extern "C" int TEXTURE_FUNCTION_PSX2_GetMetaEnum(void);
extern "C" igMetaObject *igPsx2MultiTextureExt_GetMetaObject(void);
extern "C" int g_igPsx2MultiTextureExt_vtable[4];
struct Obj_153740 {
    int *vt; int w0; T *r1; int w1; T *r2; int t[8];
    inline void rel(T **self) {
        if (self) {
            T *object = *self;
            if (object) {
                --object->references;
                if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
                    igObject_Destroy((igObject *)object);
            }
        }
    }
};
extern "C" int igPsx2MultiTextureExt_GetVTable(void);
extern "C" void igPsx2MultiTextureExt_EnsureRegistered(void);
extern "C" igMetaObject *igMultiTextureExt_GetPublishedMetaObject(void);
extern "C" CallbackArray *igPsx2MultiTextureExt_Register(void);
extern "C" int FUN_001538b0(void);
extern "C" void igPsx2MultiTextureExt_InitFields(void);
extern "C" igMetaObject *igPsx2IndexArray_GetMetaObject(void);
extern "C" int g_igPsx2IndexArray_vtable[4];
extern "C" int DAT_00526760[4];
struct Obj_153aa0 {
    int *vt; int w0[1]; T *ref; char pad[16];
    inline void releaseRef() {
        T **self = &ref;
        if (self) {
            T *object = *self;
            if (object) {
                --object->references;
                if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
                    igObject_Destroy((igObject *)object);
            }
        }
    }
};
extern "C" int igPsx2IndexArray_GetVTable(void);
extern "C" void igPsx2IndexArray_EnsureRegistered(void);
extern "C" igMetaObject *igIndexArray_GetPublishedMetaObject(void);
extern "C" void igPsx2IndexArray_InitFields_00153bd0(void);
extern "C" CallbackArray *igPsx2IndexArray_Register(void);
extern "C" igMetaObject *FUN_00153bc0(void);
extern "C" void FUN_00153bd0(void);
extern "C" igMetaObject *igPsx2ImageConvert_GetMetaObject(void);
struct Obj_153c40 { int *vt; char pad[4]; };
extern "C" int g_igPsx2ImageConvert_vtable[4];
extern "C" int igPsx2ImageConvert_GetVTable(void);
extern "C" void igPsx2ImageConvert_EnsureRegistered(void);
extern "C" igMetaObject *igImageConvert_GetPublishedMetaObject(void);
extern "C" void igPsx2ImageConvert_InitFields_00153d10(void);
extern "C" CallbackArray *igPsx2ImageConvert_Register(void);
extern "C" int FUN_00153d00(void);
extern "C" void FUN_00153d10(void);
extern "C" igMetaObject *igPsx2Image_GetMetaObject(void);
extern "C" int g_igPsx2Image_vtable[4];
union U_153d80 { int vt; char b[96]; };
extern "C" int igPsx2Image_GetVTable(void);
extern "C" void igPsx2Image_EnsureRegistered(void);
extern "C" igMetaObject *igMemoryImage_GetPublishedMetaObject(void);
extern "C" void igPsx2Image_InitFields_00153ef0(void);
extern "C" CallbackArray *igPsx2Image_Register(void);
extern "C" igMetaObject *igMemoryImage_GetPublishedMetaObject(void);
extern "C" void FUN_00153ef0(void);
extern "C" igMetaObject *igPsx2DisableExt_GetMetaObject(void);
extern "C" int g_igPsx2DisableExt_vtable[4];
union U_153f60 { int vt; char b[32]; };
extern "C" int igPsx2DisableExt_GetVTable(void);
extern "C" void igPsx2DisableExt_EnsureRegistered(void);
extern "C" igMetaObject *igDisableExt_GetPublishedMetaObject(void);
extern "C" CallbackArray *igPsx2DisableExt_Register(void);
extern "C" igMetaObject *igDisableExt_GetPublishedMetaObject(void);
extern "C" void igPsx2DisableExt_InitFields(void);
extern "C" igMetaObject *igPsx2DecalExt_GetMetaObject(void);
extern "C" int g_igPsx2DecalExt_vtable[4];
union U_1541d0 { int vt; int w[5]; char b[20]; };
extern "C" int igPsx2DecalExt_GetVTable(void);
extern "C" void igPsx2DecalExt_EnsureRegistered(void);
extern "C" igMetaObject *igDecalExt_GetPublishedMetaObject(void);
extern "C" CallbackArray *igPsx2DecalExt_Register(void);
extern "C" int FUN_00154340(void);
extern "C" void igPsx2DecalExt_InitFields(void);
extern "C" igMetaObject *igPsx2Clut_GetMetaObject(void);
struct Obj_154450 { int *vt; char pad[44]; };
extern "C" int g_igPsx2Clut_vtable[4];
extern "C" int igPsx2Clut_GetVTable(void);
extern "C" void igPsx2Clut_EnsureRegistered(void);
extern "C" igMetaObject *igClut_GetPublishedMetaObject(void);
extern "C" CallbackArray *igPsx2Clut_Register(void);
extern "C" igMetaObject *igClut_GetPublishedMetaObject(void);
extern "C" void igPsx2Clut_InitFields(void);
extern "C" igMetaObject *igPsx2BlendEquationExt_GetMetaObject(void);
extern "C" int g_igPsx2BlendEquationExt_vtable[4];
union U_154630 { int vt; int w[9]; char b[36]; };
extern "C" int igPsx2BlendEquationExt_GetVTable(void);
extern "C" void igPsx2BlendEquationExt_EnsureRegistered(void);
extern "C" igMetaObject *igBlendEquationExt_GetPublishedMetaObject(void);
extern "C" CallbackArray *igPsx2BlendEquationExt_Register(void);
extern "C" igMetaObject *igBlendEquationExt_GetPublishedMetaObject(void);
extern "C" void igPsx2BlendEquationExt_InitFields(void);

class V { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual int vX(int); };
extern "C" void Gap__Gfx__igCapabilityManager__vfunc_24(V *arg0, int arg1);
struct S_154980 { char pad[8]; int f8; int f12; int f16; int f20; int f24; };

extern "C" int Gap__Gfx__igClut__vfunc_25(struct S_154980 *arg0, int arg1, int arg2, int arg3);
class DW4VC_100_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int vX(); };
extern "C" int Gap__Gfx__igClut__vfunc_24(void **arg0);
extern "C" unsigned char igClut_UnscaleAlpha(igClut *clut);
typedef struct Obj_154b40 { char pad[29]; unsigned char f29; } Obj_154b40;
extern "C" int FUN_00154b40(Obj_154b40 *arg0);
extern "C" int FUN_00154b80(int arg0, int arg1, int *arg2, int *arg3);
extern "C" void FUN_00154c90(igClut *arg0, igClut *arg1, int arg2);
typedef struct Obj_154d40 { char pad[29]; unsigned char f29; } Obj_154d40;
extern "C" int FUN_00154d40(Obj_154d40 *arg0);
extern "C" unsigned char FUN_00154d90(igClut *clut);
typedef struct S0 { char pad20[20]; int f14; } S0;
extern "C" void igClut_ReleaseDefaults(S0 *arg0);
typedef struct S0_154e40 { char pad12[12]; int fC; int f10; int f14; int f18; } S0_154e40;

extern "C" void FUN_00154e40(S0_154e40 *arg0, int arg1);
extern "C" int Gap__Gfx__igClut__vfunc_23(int arg0, int arg1);
struct Arr { char pad[8]; int a8; int a12; int a16; void *a20; int a24; };

class DW4VC_100_2 : public igVirtualObject { public: virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int vX(int, int); virtual int v24(); virtual int v25(int,int,int);
  };
extern "C" int FUN_00154f30(Arr *self, int arg1);
/* matching construct: dummy virtual slots so the vX() call dispatches through the retail vtable slot */
class A { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void vX(igObject *); };
extern "C" int igExternalImageEntry_LoadExternalFile(A *arg0);
class V_1551f0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual int vX(char *); };
struct S_1551f0 { char pad0[32]; char *f32; char pad1[4]; char *f40; };

extern "C" int FUN_001551f0(S_1551f0 *arg0, V_1551f0 *arg1);
extern "C" int text_igImageDirectory[4];
extern "C" void igExternalImageEntry_InitDefaults(int arg0);
extern "C" int Gap__Gfx__igGenericCapabilityManager__vfunc_23(void);
class FieldTypeSource {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int getMetaObject();
};
struct FieldTypeEntry : igObject {
    char pad8[8];
    FieldTypeSource *source;
};
struct FieldTypeList {
    int _pad0[2];
    int _count;
    int _capacity;
    FieldTypeEntry **_data;
};
struct FieldTypeTable {
    char pad0[308];
    FieldTypeList *extraTypes;
};

extern "C" int FUN_00155340(FieldTypeTable *table, unsigned int type);

extern "C" int FUN_00155490(void);
struct Ref_1554a0 : public igObject { char *str; int len; };

extern "C" StringRef FUN_001554a0(int arg1);
extern "C" void *igObject_GetMetaObject_Virtual(void);
/* An object whose vtable slot 20 answers its igMetaObject (igMetaField and every igObject). */
class igMetaObjectSource : public igVirtualObject {
public:
    virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6();
    virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12();
    virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18();
    virtual void s19(); virtual int getMetaObject();
};
struct igMetaFieldView : public igMetaObjectSource {
    int _offset;
    int _fieldName;
};
/* igObjectList operations that the custom-state registry inlines. */
struct igObjectRefList : public igObject {
    int _count;
    int _capacity;
    igObject **_data;
    int find(igObject *v) const {
        int i;
        int n = _count;
        for (i = 0; i < n; i++) {
            igObject *const *p = &v;
            if (*p == _data[i]) return i;
        }
        return -1;
    }
    void set(int index, igObject *v) {
        if (v != 0) v->_refCount = v->_refCount + 1;
        igRelease(_data[index]);
        if (_count != 0 && index >= 0 && index < _count) _data[index] = v;
    }
};
struct igCustomStateCollectionView : public igObject {
    int _count;
    int _capacity;
    igObject **_data;
    char *_name;
    unsigned int _flags;
};
struct igCustomStateFieldView : public igObject {
    char *_name;
    int _stateCollectionHandle;
    igSmartPointer<igMetaFieldView> _stateField;
};
/* igVisualContext's custom-state registry: the collections and the fields that name their members. */
struct igCustomStateOwner {
    char _pad0[304];
    igSmartPointer<igObjectRefList> _customStates;
    igSmartPointer<igObjectRefList> _customFields;
};
extern "C" int FUN_001555e0(igCustomStateOwner *self, igMetaObjectSource **states, unsigned int count, int name);
typedef struct Obj_155c00 { int vt; int refs; int pad; int id; } Obj_155c00;
typedef struct List { int vt; int r; int count; int cap; Obj_155c00 **data; } List;
typedef struct Owner { char pad[304]; List *a; List *b; } Owner;

#define REL(o) if(o){ --(o)->refs; if((((unsigned long long)(long long)(o)->refs)&0x7fffffULL)==0) igObject_Destroy((igObject *)o);}
extern "C" void FUN_00155c00(igResult *out, Owner *owner, int id);
typedef struct Rc { int w0; int refs; } Rc;
typedef struct Ls { char p0[8]; int cnt; char p1[4]; Rc **data; } Ls;
typedef struct O_155db0 { char p0[304]; Ls *f304; Ls *f308; } O_155db0;
extern "C" void FUN_00155db0(O_155db0 *arg0);
struct Entry : public igObject { char pad[12]; char *name; };
struct EntryList { int w0; int w4; int count; int capacity; Entry **data; };
struct Table { char pad[304]; EntryList *entries; };

extern "C" int FUN_00155f10(Table *table, int key);
struct KeyedEntry : public igObject { char *name; };
struct KeyedEntryList { int w0; int w4; int count; int capacity; KeyedEntry **data; };
struct KeyedEntryOwner { char pad[308]; KeyedEntryList *entries; };
struct NamedValue { const char *name; int value; };
extern "C" int FUN_001560b0(KeyedEntryOwner *table, int key);
extern "C" int FUN_001562b0(void);
extern "C" int FUN_001562c0(void);
struct C { int f0; int f4; int f8; int fc; };
struct B { char pad[16]; struct C **tab; };
struct A_1562d0 { char pad[308]; struct B *b; };
extern "C" int FUN_001562d0(struct A_1562d0 *arg0, int arg1);
extern "C" void FUN_00156300(void);
typedef struct S0_156340 { char pad88[88]; int f58; } S0_156340;
extern "C" void FUN_00156340(S0_156340 *arg0, void **arg1);
struct T_1566c0 : public igObject { };
extern "C" int FUN_00157200(...);
/* An igImage pixel format's storage for width x height: image size, components, and row bytes (aligned by the
 * image's slot 43); returns the image size, -1 for 0x8000. */
extern "C" int FUN_00159320(void *self, int format, unsigned int width, unsigned int height, int *imageSize, int *components, int *bytesPerRow);
class V92a { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void vX(void *, int); };
class VA { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void *vX(int, int); };
struct S_1566c0 { char p0[8]; unsigned int f8, f12; int f16, f20, f24, f28, f32, f36, f40, f44, f48; int f52; char p56[4]; char f60; char p61[3]; int f64; T_1566c0 *f68; int f72, f76; char p80[4]; int f84; };
extern "C" void FUN_001566c0(S_1566c0 *arg0, S_1566c0 *arg1, int arg2, int arg3, int arg4, int arg5);
extern "C" int FUN_00156ae0(int arg0, int arg1, float fparg0);
typedef struct S1_156b20 { char pad4[4]; int f4; } S1_156b20;
typedef struct S0_156b20 { char pad68[68]; int f44; } S0_156b20;
extern "C" void FUN_00156b20(S0_156b20 *arg0, S1_156b20 *arg1);
/* igImage slot 25: resamples the pixels to width x height (nearest neighbour), from `source` or from the image
 * itself; converts packed formats to a plain one and back around the copy. */
extern "C" void FUN_00156ba0(igImage *self, int width, int height, igImage *source);
typedef void (*igImageRowConvert)(void *dst, void *src, int count, int flags);
class igImageConvertRows : public igVirtualObject {
public:
    virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8();
    virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14();
    virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();
    virtual void d21(); virtual void d22();
    virtual igImageRowConvert v23(int order, int format, int toPlain);
    /* The row converter from `fromFormat` to `toFormat` for a width x height image, or 0. */
    virtual igImageRowConvert findConverter(int order, int fromFormat, int toFormat, int width, int height);
};
class igImageCopy : public igVirtualObject {
public:
    virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8();
    virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14();
    virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();
    virtual void d21(); virtual void d22();
    virtual void v23(igImage *source, int deep);
    virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
    virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35();
    virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41();
    /* A subclass's own conversion to `format` (vtable +168); true when it handled it. */
    virtual bool convertCustom(int format, igImage *source);
};
/* igMemoryPool: aligned allocation (slot 55) and free (slot 66). */
class igMemoryPoolView : public igVirtualObject {
public:
    virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8();
    virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14();
    virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();
    virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26();
    virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32();
    virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38();
    virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44();
    virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50();
    virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54();
    virtual void *allocateAligned(int size, int alignment);
    virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61();
    virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65();
    virtual void free(void *block);
};
static inline igMemoryPoolView *poolOf(igObject *object, const igMemoryPoolHandle &handle) {
    igMemoryPoolView *pool = igObject_GetAllocator(object);
    return (g_useOwnerAllocator != 0) ? pool : Memory_GetAllocatorBySelector(handle);
}
class V_157140 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21();  virtual int vm(int, int, int, int, int); };
struct P { char pad[12]; int f12; };
struct O_157140 { char pad[8]; int f8; int f12; char pad2[8]; int f24; char pad3[16]; int f44; char pad4[20]; P *f68; };
extern "C" bool FUN_00157140(O_157140 *arg0, int arg1, igSmartPointer<igImageConvertRows> converter);
extern "C" int FUN_00157980(void);
typedef struct S_arg0 { char p0[8]; unsigned int f8; unsigned int f12; int f16; char p1[8]; int f28; int f32; int f36; int f40; int f44; char p2[16]; int f64; char p3[4]; int f72; char p4[8]; int f84; } S_arg0;
/* The bit depths of an igImage pixel format: intensity, index, red, green, blue, alpha, depth. */
extern "C" void FUN_00159a80(int format, int *bitsInt, int *bitsIdx, int *bitsRed, int *bitsGrn, int *bitsBlu, int *bitsAlpha, int *bitsDepth);
extern "C" void FUN_00157990(S_arg0 *arg0, int arg1);
class DW4VC_152_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual int vX(int, int); };
extern "C" void FUN_00157a50(void **arg0, void **arg1);
/* igImage slot 36 (FUN_00157a50 calls it with pointSample set for indexed formats). */
extern "C" void FUN_00157ad0(igImage *self, igImage *source, int pointSample);
typedef struct S0_158400 { char pad48[48]; int f30; int f34; char pad60[4]; unsigned char f3C; } S0_158400;

extern "C" void FUN_00158400(S0_158400 *arg0, int arg1, int arg2);
extern "C" void igImage_SetDefaultOrder(void *arg0);
extern "C" void igImage_UpdateFormatInfo(igImage *arg0);
struct S_1585d0 { char p0[48]; int f30; int f34; char p38[4]; unsigned char f3c; };
class DW4VC_220_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual int vX(int, int); };
extern "C" void FUN_001585d0(S_1585d0 *arg0);
typedef struct ImageView {
    char pad0[28];
    int rBits;
    int gBits;
    int bBits;
    int aBits;
    char pad44[8];
    unsigned char *pixels;
    char pad56[8];
    int f64;
    char pad68[4];
    int f72;
    int stride;
    char pad80[4];
    int f84;
} ImageView;
extern "C" void FUN_00158670(ImageView *img, int x, int y, const void *src);
struct S_158cc0 { char p0[8]; int f8, f12, f16, f20, f24, f28, f32, f36, f40, f44, f48; void *f52; char p56[4]; char f60; char p61[3]; int f64; char p68[4]; int f72, f76; char p80[4]; int f84; };
class VStream { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual int v24(); virtual int v25(void *, int, int); };
class VObj { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual int v38(); };
class VAlloc { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void *v53(int, int); };
extern "C" int FUN_00158cc0(S_158cc0 *arg0, void **arg1);
extern "C" int FUN_00158ab0(igImage *self, VStream *file);
/* igImageConvert's in-place pixel conversions (vtable slots 25-34): pixels, a count, and the image's _order. */
class igImageConvertView : public igVirtualObject {
public:
    virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8();
    virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14();
    virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();
    virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24();
    virtual void v25(void *pixels, int count, unsigned int *order);
    virtual void v26(void *pixels, int count, unsigned int *order);
    virtual void v27(void *pixels, int count, unsigned int *order);
    virtual void v28(void *pixels, int count, unsigned int *order);
    virtual void v29(void *pixels, int count, unsigned int *order);
    virtual void v30(void *pixels, int count, unsigned int *order);
    virtual void v31(void *pixels, int count, unsigned int *order);
    virtual void v32(void *pixels, int count, unsigned int *order);
    virtual void v33(void *pixels, int count, unsigned int *order);
    virtual void v34(void *pixels, int count, unsigned int *order);
};
/* igImage's virtual slot 45, a yes/no answer about the converted image. */
class igImageVirtuals : public igVirtualObject {
public:
    virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8();
    virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14();
    virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();
    virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26();
    virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32();
    virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38();
    virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42();
    virtual void v43(int *bytesPerRow);
    virtual void d44();
    virtual bool v45();
};
extern "C" bool FUN_001586d0(igImage *self);
extern "C" int FUN_00158f40(void);
class VStream_158f50 : public igVirtualObject { public: virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int v23(int, const char *); virtual void v24(); virtual int v25(void *, int, int); };
class S_158f50 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual int v37(int); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual int v42(void *);  char pad4[12]; int f16; char pad20[8]; int f28, f32, f36, f40, f44; char pad48[4]; int f52; char pad56[4]; unsigned char f60; char pad61[3]; int f64; char pad68[4]; int f72; char pad76[8]; int f84; };
struct ImageName {
    int text;
    ImageName(int name) {
        int interned;
        if (name == 0) {
            interned = 0;
        } else {
            if (g_stringPool == 0) {
                StringPool *v = (StringPool *)StringPool_Allocate(16);
                if (v != 0) v = StringPool_Construct(v);
                g_stringPool = v;
            }
            interned = (int)StringPool_Intern(g_stringPool, (const char *)name);
        }
        text = interned;
    }
    ~ImageName() {
        if (text != 0) {
            int *hd = (int *)text - 2;
            int c = ((int *)text)[-1] - 1;
            ((int *)text)[-1] = c;
            if (c == 0) StringChunk_ReleaseHeader((StringChunk *)*hd, (StringTokenHeader *)hd);
        }
    }
};
extern "C" int FUN_00158f50(S_158f50 *arg0, int arg1);
extern "C" int FUN_001592a0(void);
extern "C" int FUN_001592b0(void);
/* igPsx2LongList vfunc 36: release the list's storage. Frees the storage block at +0x38 through
 * its object allocator, then frees the +0x34 buffer, but only when the list owns it (flag at
 * +0x3C). Those members lie past the reflected igPsx2LongList, so they are reached through the
 * local view below. */
typedef struct LongListStorageView {
    char pad52[52];
    int buffer;                 /* +0x34: block returned to Memory_FreeBuffer */
    int storage;                /* +0x38: block released with igObject_FreeMemory */
    unsigned char ownsBuffer;   /* +0x3C: nonzero when buffer must be freed */
} LongListStorageView;
extern "C" void FUN_001592c0(LongListStorageView *self);
extern "C" void FUN_00159a70(void);
extern "C" int FUN_00159f00(int a);
extern "C" int FUN_00159f70(int arg0);
extern "C" bool FUN_00159f80(int arg0);
extern "C" int FUN_0015a010(int arg0);

struct A_15a030 { char pad[56]; int f56; char pad2[28]; int *f88; };
extern "C" void igImage_UserPostLoad(struct A_15a030 *arg0);
extern "C" void igImage_UserPostRead(void);
struct S_15a100 { char p0[12]; unsigned f12; char p1[32]; int f48; unsigned char *f52; char p2[20]; int f76; };
class A_15a100 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual unsigned char *vX(int, int); };
extern "C" void FUN_0015a100(S_15a100 *arg0);
extern "C" unsigned char FUN_0015a220(int arg0);
extern "C" int FUN_0015a270(int arg0);
extern "C" void FUN_0015a280(unsigned char *arg0, int arg1, int arg2);
typedef unsigned char u8;
extern "C" void FUN_0015a300(u8 *p, int n, int k);
typedef struct S_15a380 { char pad0[8]; int f8; int f12; char pad16[28]; int f44; char pad48[4]; int f52; char pad56[12]; int f68; } S_15a380;
extern "C" int FUN_0015a380(S_15a380 *arg0);
class B_15a420 {
public:
 virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); 
 virtual void v26(int); virtual void v27(int); virtual void v28(int); virtual void v29(); virtual void v30(int);
};
class C_15a420 : public B_15a420 {
public:
 int p[11];
 unsigned int f48; int f52; char pad[4]; char f60;
};
extern "C" void FUN_0015a420(C_15a420 *o, int a1, int a2, int a3, int a4, int a5);
extern "C" void FUN_0015a500(void *arg0, int arg1);
extern "C" void FUN_0015a510(void *arg0, int arg1);
extern "C" void FUN_0015a520(void *arg0, int arg1);
typedef struct { char pad[8]; int f8; int fc; char pad2[28]; int f2c; char pad3[4]; int f34; char pad4[12]; int f44; } T_15a600;
extern "C" int FUN_0015a600(T_15a600 *arg0);
typedef struct E { long long a; long long b; } E;
typedef struct Img { char pad[8]; int w; int h; char pad2[36]; E *data; } Img;
extern "C" void FUN_0015a6a0(Img *arg0, E *out);
/* Copies an uncompressed image into tiles (4x4 or 8x4/8x8 pixels by depth); 32-bit pixels split into high and low
 * halves 32 bytes apart. Compressed images go through FUN_0015a6a0. */
extern "C" void FUN_0015a750(igImage *self, unsigned char *out);
extern "C" void FUN_0015aaf0(unsigned char *dst, unsigned char *src, int count);

extern "C" void FUN_0015ab50(void *dst, const void *src, unsigned int size);
extern "C" void FUN_0015ab70(void *dst, const void *src, unsigned int size);
extern "C" void FUN_0015ab90(unsigned char *dst, unsigned char *src, int count);
extern "C" int FUN_0015ac10(int x);
/* An image loader's pixel hand-over: the image takes `pixels` as its buffer (the loader is unused). */
extern "C" void FUN_0015ad20(void *loader, igImage *image, void *pixels);
/* An image loader's size query: FUN_00159320 for `image` (the loader is unused). */
extern "C" void FUN_0015ad30(void *loader, igImage *image, int format, int width, int height, int *size,
                             int *components, int *rowBytes);
extern "C" int FUN_0015ad50(char *arg0);
struct Rc_15adb0 { int vt; int rc; };
class V_15adb0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51();  virtual int vX(int); };
struct S0_15adb0 { char pad8[8]; V_15adb0 *f8; int f12; int f16; int f20; int f24; };
extern "C" int FUN_0015adb0(S0_15adb0 *arg0, int arg1, int arg2, int arg3);
class O_15aea0 { public:
 virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();
 virtual int v21(unsigned int, int, int, int);
 virtual void e22(); virtual void e23(); virtual void e24(); virtual void e25(); virtual void e26(); virtual void e27(); virtual void e28(); virtual void e29(); virtual void e30(); virtual void e31(); virtual void e32();
 virtual void v33();
 virtual void v34();
 char pad[8]; void *f0c; unsigned int f10;
};
extern "C" int FUN_0015aea0(O_15aea0 *arg0, unsigned int arg1, int arg2, int arg3, int arg4);
extern "C" void FUN_0015b050(void);
extern "C" void FUN_0015b060(void *arg0, int arg1, int arg2);
extern "C" void FUN_0015b080(void *arg0, int arg1, int arg2);
class VC_116 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26();  virtual void vX(int, int); };
class VC_120 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27();  virtual void vX(); };
struct O_15b0a0 { int *vt; char pad[16]; int f14; };
extern "C" void FUN_0015b0a0(void *a0, int arg1, int arg2);
extern "C" unsigned short FUN_0015b100(void *arg0, int arg1);
extern "C" int FUN_0015b120(void *arg0, int arg1);
/* Dummy class: slot at vtable byte offset 128 (30 slots precede it). */
class IndexArrayNarrowReadSlot {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4();
    virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
    virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14();
    virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24();
    virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
    virtual int ReadNarrow(int index);
};
/* Dummy class: slot at vtable byte offset 132 (31 slots precede it). */
class IndexArrayWideReadSlot {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4();
    virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
    virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14();
    virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24();
    virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
    virtual void d30();
    virtual int ReadWide(int index);
};
extern "C" int FUN_0015b140(igPsx2IndexArray *self, int index);
extern "C" int FUN_0015b1a0(int arg0, int arg1, int arg2);
extern "C" int FUN_0015b1b0(int arg0, int arg1, int arg2);
extern "C" void FUN_0015b1c0(void);
extern "C" void FUN_0015b1d0(void);
extern "C" void FUN_0015b1e0(void *arg0);
class DW4VC_100_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int vX(int, int); };
extern "C" int Gap__Bec__ParticleArray__vfunc_22(ParticleArray *arg0, int arg1);
extern "C" void Gap__Bec__ParticleArray__vfunc_23(ParticleArray *arg0, char *arg1, unsigned int arg2);
extern "C" void *FUN_0015b7d0(void *arg0, void *arg1);
extern "C" void *FUN_0015b7f0(void *arg0, void *arg1);
extern "C" void *FUN_0015b820(void *arg0, void *arg1);
extern "C" int Gap__Bec__ParticleArray__vfunc_24(ParticleArray *arg0, unsigned int arg1);
extern "C" void Gap__Bec__ParticleArray__vfunc_25(ParticleArray *arg0);
struct B_15bb50 { char pad[44]; int f44; };
struct A_15bb50 { char p0[8]; B_15bb50 *b; char p1[8]; float f20; float f24; float f28; char p2[48]; unsigned f80; };
struct V_15bb50 { float x; float y; };
extern "C" bool FUN_0015bb50(A_15bb50 *arg0, V_15bb50 *arg1, float *arg2);
struct HI { char pad[32]; int f32; int f36; char pad2[4]; int f44; };
class O48 {
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
    virtual int v136(int);
    int refs;
};
class O44 {
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
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual O48 *v104(const char *);
    int refs;
};
class O40 {
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
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual int v108(igVertexArrayLock *, int);
    virtual int v112(igVertexArrayLock *, int);
};
class PA {
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
    virtual void d20();
    virtual int v92(int, int, O44 *, float, float);
    int pad4;
    HI *f8;
    int f12;
    char pad16[4];
    float f20;
    float f24;
    float f28;
    int f32;
    int f36;
    O40 *f40;
    O44 *f44;
    O48 *f48;
    int f52;
    int f56;
    char pad60[12];
    unsigned char f72;
    unsigned char f73;
    char pad74[2];
    int (*f76)(float, int, int, int, int, O40 *, O48 *);
    char pad80[4];
    float f84;
    int f88;
};
extern "C" long long DAT_00560668[4];

typedef struct RefCountedHeader { char pad4[4]; int f4; } RefCountedHeader;
extern "C" void Gap__Bec__ParticleArray__vfunc_28(ParticleArray *arg0, RefCountedHeader *arg1, int arg2, int arg3);

extern "C" int Gap__Bec__ParticleArray__vfunc_30(ParticleArray *p);
extern "C" int Gap__Bec__ParticleArray__vfunc_29(ParticleArray *p);
extern "C" void Gap__Bec__ParticleArray__vfunc_37(ParticleArray *a0, int a1);
/* matching construct: f24_of reads at const so the compare and the release each reload it, as retail does */
typedef struct PointSpriteInterfaceView { char pad[24]; igObject * f24; } PointSpriteInterfaceView;
extern "C" void igParticleArray_ReleaseDefaults(ParticleArray *arg0);
/* matching construct: dummy-virtual receiver; vX is the retail vtable call at slot 21 */
class DW4VC_92_5 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual int vX(int, int, int, float, float); };
extern "C" void igParticleArray_UserPostLoad(void *arg0);
/* matching construct: dummy-virtual class so vX() dispatches through vtable slot 57 of the vertex-array object */
class DW4VC_236 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void vX(); };
struct PointSpriteView { char pad[24]; igObject *f24; igObject *getF24() const { return f24; } };
extern "C" void Gap__Bec__ParticleArray__vfunc_36(ParticleArray *arg0);
struct OO;
struct S4d0;
extern "C" int FUN_00190d80(void*,float*,int);
extern "C" int FUN_00191860(void*,float,float,float,float,float,float);
extern "C" int FUN_00192510(void*,float*,float*,float*,float*,float*,float*);

union Ref_15cb50 { int w; struct { unsigned cnt:23; unsigned f:9; } b; };
struct Rc_15cb50 { int vt; Ref_15cb50 u; };
struct V2 { int a; int b; };
struct Inner { char p0[60]; int f60; int f64; char p1[8]; int f76; };
class Obj2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual int v96(int *, int, int, int); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual int v200(int, int, V2 *); Ref_15cb50 u; Inner *f8;};
class Al { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual int v216(int); };
struct A1 { int vt; Ref_15cb50 u; char p0[16]; Al *f24; };
class O_15cb50 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual int v168(int, int, V2 *); char p0[20]; Obj2 *f24;};
class DW4VC_244_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual int vX(); };
class DW4VC_812_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual void d101(); virtual void d102(); virtual void d103(); virtual void d104(); virtual void d105(); virtual void d106(); virtual void d107(); virtual void d108(); virtual void d109(); virtual void d110(); virtual void d111(); virtual void d112(); virtual void d113(); virtual void d114(); virtual void d115(); virtual void d116(); virtual void d117(); virtual void d118(); virtual void d119(); virtual void d120(); virtual void d121(); virtual void d122(); virtual void d123(); virtual void d124(); virtual void d125(); virtual void d126(); virtual void d127(); virtual void d128(); virtual void d129(); virtual void d130(); virtual void d131(); virtual void d132(); virtual void d133(); virtual void d134(); virtual void d135(); virtual void d136(); virtual void d137(); virtual void d138(); virtual void d139(); virtual void d140(); virtual void d141(); virtual void d142(); virtual void d143(); virtual void d144(); virtual void d145(); virtual void d146(); virtual void d147(); virtual void d148(); virtual void d149(); virtual void d150(); virtual void d151(); virtual void d152(); virtual void d153(); virtual void d154(); virtual void d155(); virtual void d156(); virtual void d157(); virtual void d158(); virtual void d159(); virtual void d160(); virtual void d161(); virtual void d162(); virtual void d163(); virtual void d164(); virtual void d165(); virtual void d166(); virtual void d167(); virtual void d168(); virtual void d169(); virtual void d170(); virtual void d171(); virtual void d172(); virtual void d173(); virtual void d174(); virtual void d175(); virtual void d176(); virtual void d177(); virtual void d178(); virtual void d179(); virtual void d180(); virtual void d181(); virtual void d182(); virtual void d183(); virtual void d184(); virtual void d185(); virtual void d186(); virtual void d187(); virtual void d188(); virtual void d189(); virtual void d190(); virtual void d191(); virtual void d192(); virtual void d193(); virtual void d194(); virtual void d195(); virtual void d196(); virtual void d197(); virtual void d198(); virtual void d199(); virtual void d200(); virtual int vX(int, char *); };
class DW4VC_832_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual void d101(); virtual void d102(); virtual void d103(); virtual void d104(); virtual void d105(); virtual void d106(); virtual void d107(); virtual void d108(); virtual void d109(); virtual void d110(); virtual void d111(); virtual void d112(); virtual void d113(); virtual void d114(); virtual void d115(); virtual void d116(); virtual void d117(); virtual void d118(); virtual void d119(); virtual void d120(); virtual void d121(); virtual void d122(); virtual void d123(); virtual void d124(); virtual void d125(); virtual void d126(); virtual void d127(); virtual void d128(); virtual void d129(); virtual void d130(); virtual void d131(); virtual void d132(); virtual void d133(); virtual void d134(); virtual void d135(); virtual void d136(); virtual void d137(); virtual void d138(); virtual void d139(); virtual void d140(); virtual void d141(); virtual void d142(); virtual void d143(); virtual void d144(); virtual void d145(); virtual void d146(); virtual void d147(); virtual void d148(); virtual void d149(); virtual void d150(); virtual void d151(); virtual void d152(); virtual void d153(); virtual void d154(); virtual void d155(); virtual void d156(); virtual void d157(); virtual void d158(); virtual void d159(); virtual void d160(); virtual void d161(); virtual void d162(); virtual void d163(); virtual void d164(); virtual void d165(); virtual void d166(); virtual void d167(); virtual void d168(); virtual void d169(); virtual void d170(); virtual void d171(); virtual void d172(); virtual void d173(); virtual void d174(); virtual void d175(); virtual void d176(); virtual void d177(); virtual void d178(); virtual void d179(); virtual void d180(); virtual void d181(); virtual void d182(); virtual void d183(); virtual void d184(); virtual void d185(); virtual void d186(); virtual void d187(); virtual void d188(); virtual void d189(); virtual void d190(); virtual void d191(); virtual void d192(); virtual void d193(); virtual void d194(); virtual void d195(); virtual void d196(); virtual void d197(); virtual void d198(); virtual void d199(); virtual void d200(); virtual void d201(); virtual void d202(); virtual void d203(); virtual void d204(); virtual void d205(); virtual int vX(int, char *); };
struct RR { int w0; int rc; };
struct OO { char pad[20]; void *f20; RR *f24; int pad3; char f32; char pad2[3]; int f36; char buf[512]; };
typedef struct R_15cb50 { int w0; int refs; } R_15cb50;
class DW4VC_812 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual void d101(); virtual void d102(); virtual void d103(); virtual void d104(); virtual void d105(); virtual void d106(); virtual void d107(); virtual void d108(); virtual void d109(); virtual void d110(); virtual void d111(); virtual void d112(); virtual void d113(); virtual void d114(); virtual void d115(); virtual void d116(); virtual void d117(); virtual void d118(); virtual void d119(); virtual void d120(); virtual void d121(); virtual void d122(); virtual void d123(); virtual void d124(); virtual void d125(); virtual void d126(); virtual void d127(); virtual void d128(); virtual void d129(); virtual void d130(); virtual void d131(); virtual void d132(); virtual void d133(); virtual void d134(); virtual void d135(); virtual void d136(); virtual void d137(); virtual void d138(); virtual void d139(); virtual void d140(); virtual void d141(); virtual void d142(); virtual void d143(); virtual void d144(); virtual void d145(); virtual void d146(); virtual void d147(); virtual void d148(); virtual void d149(); virtual void d150(); virtual void d151(); virtual void d152(); virtual void d153(); virtual void d154(); virtual void d155(); virtual void d156(); virtual void d157(); virtual void d158(); virtual void d159(); virtual void d160(); virtual void d161(); virtual void d162(); virtual void d163(); virtual void d164(); virtual void d165(); virtual void d166(); virtual void d167(); virtual void d168(); virtual void d169(); virtual void d170(); virtual void d171(); virtual void d172(); virtual void d173(); virtual void d174(); virtual void d175(); virtual void d176(); virtual void d177(); virtual void d178(); virtual void d179(); virtual void d180(); virtual void d181(); virtual void d182(); virtual void d183(); virtual void d184(); virtual void d185(); virtual void d186(); virtual void d187(); virtual void d188(); virtual void d189(); virtual void d190(); virtual void d191(); virtual void d192(); virtual void d193(); virtual void d194(); virtual void d195(); virtual void d196(); virtual void d197(); virtual void d198(); virtual void d199(); virtual void d200(); virtual int vX(int, char *); };
struct X { char pad0[20]; DW4VC_812 *dev; R_15cb50 *obj; int w28; };
struct Y { char pad0[20]; DW4VC_812 *dev; R_15cb50 *obj; char pad1[4]; unsigned char b32; char pad2[3]; int w36; };
struct Cam { virtual void d0(); };
struct V_15cb50 {
  virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
  virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
  virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
  virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39();
  virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47();
  virtual int v48();
  virtual void d49(); virtual void d50();
  virtual void v51(int, int *, int *);
};
struct S4d0 {
  char p0[20]; V_15cb50 *o;
  char p1[272];
  float m[16];
  int w, h;
  float nl, nr, nb, nt, nn, nf;
};
class V164 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual int vX(int, int); };
struct S740 { char pad24[24]; V164 *f24; };
class V168 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual int vX(int, int); };
struct S7c0 { char pad24[24]; V168 *f24; };
class igPointSpriteVertexArrayView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31();
    virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39();
    virtual void d40();
    virtual void vfunc_41(unsigned int index);
    virtual void vfunc_42(unsigned int index);
    virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50();
    virtual void vfunc_51(unsigned int index, float value);
    virtual void d52(); virtual void d53(); virtual void d54();
    virtual void vfunc_55();
    virtual void vfunc_56();
};
class igPointSpriteExtView {
public:
    int _vtable;
    unsigned int _refCount;
    char _pad8[16];
    igPointSpriteVertexArrayView *_vertexArray;
};
class T_15cb50 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual int m200(int, int, ...); virtual int m204(int, int, ...); };
struct O880 { char pad24[24]; T_15cb50 *p; };
class DW4VC_204_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual int vX(int, int); };
class DW4VC_208_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual int vX(int, int); };
struct V2f { float x, y; };
class VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void vX(int, void *); };
struct Sdb00 { char pad[24]; VC *o; };
extern "C" void igPointSpriteExt_SetContext(int a0, int a1);
extern "C" int igPointSpriteExt_ConfigureVertexArray(O_15cb50 *arg0, A1 *arg1, int *arg2, unsigned int arg3, int arg4);
extern "C" void igPointSpriteExt_BeginSprites(OO *arg0);
extern "C" void igPointSpriteExt_EndSprites(Y *arg0);
extern "C" void FUN_0015d050(void *arg0, int dummy1, void *arg2);
extern "C" void FUN_0015d070(igPointSpriteExt *arg0, int arg1, void *arg2);
extern "C" void FUN_0015d0a0(igPointSpriteExt *arg0, int arg1, void *arg2);
extern "C" void FUN_0015d4d0(S4d0 *s);
extern "C" void igPointSpriteExt_SetPosition(void *arg0, int arg1, void *arg2);
extern "C" void igPointSpriteExt_GetPosition(igPsx2PointSpriteExt *arg0, int arg1, void *arg2);
extern "C" void igPointSpriteExt_SetColorPacked(S740 *arg0, int arg1, int arg2);
extern "C" void igPointSpriteExt_SetColor(S7c0 *arg0, int arg1, int arg2);
extern "C" void igPointSpriteExt_GetColorPacked(igPointSpriteExtView *self, unsigned int index);
extern "C" void igPointSpriteExt_GetColor(igPointSpriteExtView *self, unsigned int index);
extern "C" void igPointSpriteExt_SetTextureCoord(O880 *arg0, int arg1, int arg2, float *arg3);
extern "C" void igPointSpriteExt_GetTextureCoord(void *arg0, int arg1, int arg2);
extern "C" void igPointSpriteExt_GetTextureCoordPointer(void *arg0, int arg1, int arg2);
extern "C" void igPointSpriteExt_SetUniformSize(igPointSpriteExtView *self, unsigned int index, float value);
extern "C" void igPointSpriteExt_SetRadian(igPointSpriteExtView *self);
extern "C" void igPointSpriteExt_GetRadian(igPointSpriteExtView *self);
extern "C" void igPrimLengthArray1_1_UserMakeConcrete(igPrimLengthArray1_1 *self);
typedef struct S0_15df80 { char pad24[24]; int f18; } S0_15df80;
typedef struct S_temp_v0 { char pad4[4]; int f4; } S_temp_v0;

extern "C" void igPsx2VertexArray1_1_resetFields(S0_15df80 *arg0, int flags);
extern "C" void FUN_0015e010(void);
struct S_arg0_15e050 { char pad0[8]; int f8; char padC[12]; int f24; };
struct S_temp_v0_2 { char pad0[4]; int f4; };

extern "C" void FUN_0015e050(struct S_arg0_15e050 *arg0);
extern "C" int FUN_0015e130(unsigned int v);
extern "C" void FUN_0015e160(unsigned int *arg0, unsigned int arg1);
class DW4VC_96_4 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual int vX(int *, int, int, int); };
extern "C" void igVertexArray1_1_ConfigureFromFlags(void **arg0, int arg1, int arg2, int arg3, int arg4);
class Alloc { public:
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
  virtual void d48();
  virtual void d49();
  virtual void d50();
  virtual void d51();
  virtual void d52();
  virtual void *v53(int, int);
};
extern "C" void FUN_0015e2b0(igVertexArray1_1 *arg0, int arg1);
extern "C" void igVertexArray1_1_Cache(void);
class Alloc_15e4e0 { public:
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
  virtual void d48();
  virtual void d49();
  virtual void d50();
  virtual void d51();
  virtual int v52(int);
  virtual int v53(int, int);
};
class VA_15e4e0 { public:
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
  virtual unsigned int *v23();
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
  virtual void d48();
  virtual void d49();
  virtual void d50();
  virtual void d51();
  virtual void d52();
  virtual void d53();
  virtual void d54();
  virtual void d55();
  virtual void d56();
  virtual void d57();
  virtual void d58();
  virtual void d59();
  virtual void d60();
  virtual void d61();
  virtual int v62();
  virtual int v63();
  char pad4[4]; int f8; int f12; char pad16[8]; Alloc_15e4e0 *f24; char pad28[4]; int f32; int f36;
};
extern "C" int FUN_0015e4e0(VA_15e4e0 *arg0);
extern "C" int igVertexArray1_1_GetVertexFormat(int arg0);
struct VertexFormatInfo { unsigned flags; };
class VertexBufferOwner { public:virtual void d0();virtual void d1();virtual void d2();virtual void d3();virtual void d4();virtual void d5();virtual void d6();virtual void d7();virtual void d8();virtual void d9();virtual void d10();virtual void d11();virtual void d12();virtual void d13();virtual void d14();virtual void d15();virtual void d16();virtual void d17();virtual void d18();virtual void d19();virtual void d20();virtual void d21();virtual void d22();virtual VertexFormatInfo *getInfo();virtual void d24();virtual void d25();virtual void d26();virtual void d27();virtual void d28();virtual void d29();virtual void d30();virtual void d31();virtual void d32();virtual void d33();virtual void d34();virtual void d35();virtual void d36();virtual void d37();virtual void d38();virtual void d39();virtual void d40();virtual void d41();virtual void d42();virtual void d43();virtual void d44();virtual void d45();virtual void d46();virtual void d47();virtual void d48();virtual void d49();virtual void d50();virtual void d51();virtual void d52();virtual void d53();virtual void d54();virtual void d55();virtual void d56();virtual void d57();virtual void d58();virtual void d59();virtual void f60();virtual void f61();
int pad1[1]; int *arr; int pad2[5]; int f32; int f36;
};
extern "C" void FUN_0015e7b0(VertexBufferOwner *o);
struct S_15e940;
class VC_15e940 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual unsigned int * vX(); };
struct S_15e940 : VC_15e940 { char p[28]; float *f32; };
extern "C" void igVertexArray1_1_SetWeight(S_15e940 *arg0, int arg1, int arg2, float fparg0);
struct S_15e9c0;
class VC_15e9c0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual unsigned int * vX(); };
struct S_15e9c0 : VC_15e9c0 { char p[28]; float *f32; };
extern "C" float igVertexArray1_1_GetWeight(S_15e9c0 *arg0, int arg1, int arg2);
class VC_15ea30 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int * vX(); };
extern "C" void igVertexArray1_1_ValidateBlendWeights(int *arg0);
class VC_15eaf0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int * vX(); };
extern "C" void igVertexArray1_1_SetBlendMatrixIndex(int *arg0, int arg1, int arg2, char arg3);
class VC_15eb60 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int * vX(); };
extern "C" unsigned char igVertexArray1_1_GetBlendMatrixIndex(int *arg0, int arg1, int arg2);
extern "C" void igVertexArray1_1_SetPointSpriteSize(igPsx2VertexArray1_1 *arg0, int arg1, float fparg0);
extern "C" float igVertexArray1_1_GetPointSpriteSize(igPsx2VertexArray1_1 *arg0, int arg1);
typedef struct A_15ec30 { char p[8]; struct B_15ec30 *b; } A_15ec30;
typedef struct B_15ec30 { char p[60]; char *data; } B_15ec30;
extern "C" void igVertexArray1_1_SetPointSpriteSize2(A_15ec30 *arg0, int arg1, float *arg2);
extern "C" void igVertexArray1_1_GetPointSpriteSize2(igPsx2VertexArray1_1 *arg0, int arg1, float *arg2);
extern "C" void FUN_0015ecc0(void *arg0, int arg1, float fparg0);
extern "C" float FUN_0015ece0(void *arg0, int arg1);
/* Packed vertex format word: which arrays a vertex array holds, and how many of the counted ones.
 * Bits 0, 1, 2: positions, normals, colours; bits 4-7 the blend weights per vertex (the last weight is one less
 * the others); bits 8-11 the blend matrix indices; bits 16-19 the texture coordinate sets; bits 20-21 the
 * point-sprite size components (2 with a height, 1 with a width only); bits 22, 23 two more vector arrays;
 * bit 24 a rotating sprite. */
struct igVertexFormat {
    unsigned int bits;
    unsigned char getWeightCount() const { return (unsigned char)((bits & 0xf0) >> 4); }
    unsigned char getBlendIndexCount() const { return (unsigned char)((bits & 0xf00) >> 8); }
    unsigned char getTextureCoordCount() const { return (unsigned char)((bits & 0xf0000) >> 16); }
    unsigned char getPointSpriteSizeCount() const { return (unsigned char)((bits & 0x300000) >> 20); }
    bool getPointSpriteRotation() const { return (bits & 0x1000000) != 0; }
    void setWeightCount(unsigned char n) {
        bits &= ~0xf0;
        bits |= (unsigned int)n << 4;
    }
    void setBlendIndexCount(unsigned char n) {
        bits &= ~0xf00;
        bits |= (unsigned int)n << 8;
    }
    void setTextureCoordCount(unsigned char n) {
        bits &= ~0xf0000;
        bits |= (unsigned int)n << 16;
    }
};
extern "C" void FUN_00164e90(igVertexFormat *out, const igVertexFormat *a, const igVertexFormat *b);
/* igVertexArray's per-vertex accessors (vtable slots 29-56): each array has a setter and, one slot later, a getter. */
class igVertexArrayAccess : public igVirtualObject {
public:
    virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8();
    virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14();
    virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();
    virtual void d21(); virtual void d22(); virtual void d23();
    /* Allocates the arrays `format` names for `vertexCount` vertices from `pool`. */
    virtual void configure(igVertexFormat *format, unsigned int vertexCount, unsigned int count2, int pool);
    virtual void d25(); virtual void d26();
    virtual void d27(); virtual void d28();
    virtual void setPosition(unsigned int index, igVec3f *position);
    virtual void getPosition(unsigned int index, igVec3f *position);
    virtual void d31();
    virtual void setNormal(unsigned int index, igVec3f *normal);
    virtual void getNormal(unsigned int index, igVec3f *normal);
    virtual void d34();
    virtual void v35(unsigned int index, igVec4f *value);
    virtual void v36(unsigned int index, igVec4f *value);
    virtual void d37();
    virtual void v38(unsigned int index, igVec4f *value);
    virtual void v39(unsigned int index, igVec4f *value);
    virtual void d40();
    virtual void setColor(unsigned int index, unsigned int color);
    virtual void d42();
    virtual unsigned int getColor(unsigned int index);
    virtual void d44();
    virtual void setWeight(unsigned int weight, unsigned int index, float value);
    virtual float getWeight(unsigned int weight, unsigned int index);
    virtual void d47();
    virtual void setBlendIndex(unsigned int blend, unsigned int index, unsigned char value);
    virtual int getBlendIndex(unsigned int blend, unsigned int index);
    virtual void setTextureCoord(unsigned int set, unsigned int index, igVec2f *coord);
    virtual void getTextureCoord(unsigned int set, unsigned int index, igVec2f *coord);
    virtual void d52();
    virtual void setPointSize(unsigned int index, float size);
    virtual float getPointSize(unsigned int index);
    virtual void setPointSize2(unsigned int index, igVec2f size);
    virtual void getPointSize2(unsigned int index, igVec2f *size);
};
/* igVertexArray2 as its internal-buffer conversion uses it: slot 23 (+100) answers the vertex count. */
class igVertexArray2View : public igVirtualObject {
public:
    virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6();
    virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12();
    virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18();
    virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22();
    virtual unsigned int getVertexCount(int stream);
    char *_name;
    igSmartPointer<igVertexArrayAccess> _internalBuffer;
};
/* igVertexArray2Helper's per-vertex getters (each returns the value, or a pointer to it). */
class igVertexArray2HelperAccess : public igVirtualObject {
public:
    virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6();
    virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12();
    virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18();
    virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24();
    virtual unsigned int getVertexCount();
    virtual void s26(); virtual void s27();
    virtual igVec3f *getPosition(unsigned int index);
    virtual void s29(); virtual void s30();
    virtual igVec3f *getNormal(unsigned int index);
    virtual void s32(); virtual void s33();
    virtual igVec4f *getVector22(unsigned int index);
    virtual void s35(); virtual void s36();
    virtual igVec4f *getVector23(unsigned int index);
    virtual void s38(); virtual void s39();
    virtual unsigned int getColor(unsigned int index);
    virtual void s41(); virtual void s42();
    virtual float getWeight(unsigned int weight, unsigned int index);
    virtual void s44();
    virtual unsigned char getBlendIndex(unsigned int blend, unsigned int index);
    virtual void s46(); virtual void s47();
    virtual igVec2f *getTextureCoord(unsigned int set, unsigned int index);
    virtual void s49();
    virtual float getPointSize(unsigned int index);
    virtual void s51();
    virtual void getPointSize2(unsigned int index, igVec2f *size);
    virtual void s53(); virtual void s54(); virtual void s55();
    virtual void getFormat(igVertexFormat *format);
    char *_name;
    igVertexArray2View *_vertexArray;
    void setVertexArray(igVertexArray2View *array) {
        if (array != 0) array->_refCount = array->_refCount + 1;
        igRelease(_vertexArray);
        _vertexArray = array;
    }
};
extern "C" int Gap__Gfx__igVertexArray2__vfunc_23(igVertexArray2View *self, int a1, int a2, int a3, int pool);
/* Copies vertex `srcIndex` of `src` to vertex `dstIndex` of `dst`, for the arrays `format` names. */
extern "C" void FUN_0015dbc0(igVertexArrayAccess *dst, unsigned int dstIndex, igVertexArrayAccess *src, unsigned int srcIndex, const igVertexFormat *format);
/* What igParticleArray stores in _updateFunction and igParticleArray_Update calls: two counters, the particle
 * array and its record size, the internal vertex array, the point-sprite interface, and the time. */
typedef void (*igParticleUpdateFunction)(int n, unsigned int i, int particles, int particleSize, void *vertexArray, void *pointSprite, float time);
extern "C" void FUN_00181140(int n, unsigned int i, int particles, int particleSize, void *vertexArray, void *pointSprite, float time);
extern "C" void FUN_00181350(int n, unsigned int i, int particles, int particleSize, void *vertexArray, void *pointSprite, float time);
extern "C" void FUN_0015c950(ParticleArray *self, const igVertexFormat *format);
/* igParticleArray's context (slot 26 looks an extension up by name), point-sprite interface (slots 34, 35) and
 * internal vertex array (slot 24). */
class ParticleContextView : public igVirtualObject {
public:
    virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8();
    virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14();
    virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();
    virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25();
    virtual igObject *v26(const char *name);
    virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32();
    virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38();
    virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44();
    virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50();
    virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56();
    virtual void d57(); virtual void d58();
    virtual void v59(igObject *vertexArray);
    virtual void d60(); virtual void d61(); virtual void d62();
    virtual void v63(igObject *primLengthArray);
    virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69();
    virtual void d70();
    virtual void v71(int primType, int count, int offset);
    virtual void d72(); virtual void d73();
    virtual void v74(int primType, int primLengthCount, int offset, int primLengthOffset);
};
class PointSpriteExtView : public igVirtualObject {
public:
    virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8();
    virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14();
    virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();
    virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26();
    virtual void d27(); virtual void d28(); virtual void d29();
    virtual void v30();
    virtual void v31();
    virtual void v32(unsigned int count, unsigned int offset);
    virtual void d33();
    virtual void v34(int spriteSpace);
    virtual int v35(igObject *vertexArray, igVertexFormat *format, int count, int usage);
    virtual void d36(); virtual void d37();
    virtual void v38(unsigned int index, int color);
    virtual void d39(); virtual void d40(); virtual void d41();
    virtual void v42(int set, unsigned int index, void *textureCoord);
    virtual void d43(); virtual void d44();
    virtual void v45(unsigned int index, float rotation);
    char _pad8[16];
    igSmartPointer<igObject> _vertexArray;
};
class ParticleVertexArrayView : public igVirtualObject {
public:
    virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8();
    virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14();
    virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();
    virtual void d21(); virtual void d22(); virtual void d23();
    virtual int v24(igVertexFormat *format, int count, int usage, int flags);
    virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30();
    virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36();
    virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40();
    virtual void v41(unsigned int index, int color);
    virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47();
    virtual void d48(); virtual void d49();
    virtual void v50(int set, unsigned int index, void *textureCoord);
};
/* Home at landing: include/dw4/core/igObject.h (core declaration slice). */
/* igParticleArray's fields with the types their meta fields give them (reflected.h holds the references as words). */
struct igParticleArrayRefs : public igObject {
    igSmartPointer<igParticleFormat> _particleFormat;
    unsigned int _maxNum;
    unsigned int _arrayIndex;
    float _particleLifeStart;
    float _particleLifeEnd;
    float _currentTime;
    unsigned int _particleDataSize;
    void *_particleArray;
    igSmartPointer<igObject> _internalVertexArray;
    igSmartPointer<igObject> _context;
    igSmartPointer<igObject> _pointSpriteInterface;
    unsigned int _particleOffset;
    unsigned int _particleNum;
    int _primLengthArrayNum;
    int _primLengthArrayOffset;
    igSmartPointer<igObject> _primLengthArray;
    unsigned char _setConstant;
    unsigned char _configured;
    igParticleUpdateFunction _updateFunction;
    int _timeControlState;
    float _particleLifetimeEndOffset;
    unsigned int _aliveParticleNum;
};
extern "C" int Gap__Bec__ParticleArray__vfunc_21(igParticleArrayRefs *self, igObject *format, int maxNum, igObject *context, float lifeStart, float lifeEnd);
/* Writes the live particles' colour, texture coordinates, size and rotation into the internal vertex array or,
 * for sprites, the point-sprite interface. */
extern "C" void FUN_0015b880(igParticleArrayRefs *self);
extern "C" void FUN_0015bc20(igParticleArrayRefs *self, int checkLife, int level);
struct RcRef {
    igObject *p;
    RcRef &operator=(const RcRef &other) {
        igObject *next = other.p;
        igObject *o;
        if (next != 0) next->_refCount = next->_refCount + 1;
        if ((o = p) != 0) {
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o);
        }
        p = next;
        return *this;
    }
};
class V_15ed00 : public igVirtualObject { public:
 virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual int v17(int); virtual int v18(int); virtual void d19(); virtual void d20(); virtual void d21(); virtual int v22(int, unsigned int, int, int); virtual int v23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual int v45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual int v59();
 int f8; unsigned int f12; char p16[8]; RcRef f24; int f28; int f32; int f36; int f40;
};
extern "C" int igVertexArray1_1_Reconfigure(V_15ed00 *arg0, int arg1, unsigned int arg2, int arg3, int arg4);
#define VERTEX_FORMAT_POSITIONS 0x400000   /* bit 22 of _vertexFormat */
#define VDATA_POSITION_STREAM 68           /* _vdata + 68: pointer to the position stream */
#define POSITION_STRIDE 0xC                /* 3 floats per vertex */
extern "C" void igVertexArray1_1_SetBinormal(igPsx2VertexArray1_1 *self, int index, float *in);
extern "C" void igVertexArray1_1_GetBinormal(igPsx2VertexArray1_1 *self, int index, float *out);
extern "C" int igVertexArray1_1_GetBinormalPointer(igPsx2VertexArray1_1 *arg0, int arg1);
#define VERTEX_FORMAT_NORMALS 0x800000     /* bit 23 of _vertexFormat */
#define VDATA_NORMAL_STREAM 72             /* _vdata + 72: pointer to the normal stream */
#define NORMAL_STRIDE 0xC                  /* 3 floats per vertex */
extern "C" void igVertexArray1_1_SetTangent(igPsx2VertexArray1_1 *self, int index, float *in);
extern "C" void igVertexArray1_1_GetTangent(igPsx2VertexArray1_1 *self, int index, float *out);
extern "C" int igVertexArray1_1_GetTangentPointer(igPsx2VertexArray1_1 *arg0, int arg1);
extern "C" void igVertexArray1_1_FreePointSpriteMemory(void *arg0);
struct Alloc_15f200 {
    virtual void a0();
    virtual void a1();
    virtual void a2();
    virtual void a3();
    virtual void a4();
    virtual void a5();
    virtual void a6();
    virtual void a7();
    virtual void a8();
    virtual void a9();
    virtual void a10();
    virtual void a11();
    virtual void a12();
    virtual void a13();
    virtual void a14();
    virtual void a15();
    virtual void a16();
    virtual void a17();
    virtual void a18();
    virtual void a19();
    virtual void a20();
    virtual void a21();
    virtual void a22();
    virtual void a23();
    virtual void a24();
    virtual void a25();
    virtual void a26();
    virtual void a27();
    virtual void a28();
    virtual void a29();
    virtual void a30();
    virtual void a31();
    virtual void a32();
    virtual void a33();
    virtual void a34();
    virtual void a35();
    virtual void a36();
    virtual void a37();
    virtual void a38();
    virtual void a39();
    virtual void a40();
    virtual void a41();
    virtual void a42();
    virtual void a43();
    virtual void a44();
    virtual void a45();
    virtual void a46();
    virtual void a47();
    virtual void a48();
    virtual void a49();
    virtual void a50();
    virtual void a51();
    virtual void *alloc(int);
};
struct B_15f200 { char p[60]; void *f60; int f64; char q[8]; void *f76; };
struct A_15f200 {
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
    virtual int *getFlags();
    int pad;
    B_15f200 *f8;
    int f12;
    char q[8];
    Alloc_15f200 *f24;
};
extern "C" int igVertexArray1_1_AllocatePointSpriteMemory(A_15f200 *arg0);
extern "C" void igVertexArray1_1_FreeAbstractBiNormalsAndTangentsMemory(void *arg0);
struct ArraySizeOwner;
class ArraySizeOwnerBase { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual unsigned int * vX(); };
class ArraySizeAllocator { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual int vX(int); };
struct ArraySizeOwner : ArraySizeOwnerBase { char p[4]; char *f8; int f12; char q[8]; ArraySizeAllocator *f24; };
extern "C" int igVertexArray1_1_AllocateAbstractBiNormalsAndTangentsMemory(ArraySizeOwner *arg0);
struct S_15f430 { char p0[8]; int count; char p12[4]; int **items; };
typedef struct L { int p0,p4; int n; int p12; int *data; } L;
typedef struct VL { char p[8]; int n; int pad; int *data; } VL;
typedef struct O_15f430 { char p[16]; int k0; int k1; } O_15f430;
extern "C" int *FUN_0015f4a0(struct S_15f430 *s, int a1, int a2);
extern "C" void *FUN_0015f510(L *l, int a1, int a2, int a3);

extern "C" void FUN_0015f660(igVertexArray2 *arg0, igSmartPointer<Rc_17f2b0> list);
struct C_15f730 { virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4(); virtual void a5(); virtual void a6(); virtual void a7(); virtual void a8(); virtual void a9(); virtual void a10(); virtual void a11(); virtual void a12(); virtual void a13(); virtual void a14(); virtual void a15(); virtual void a16(); virtual void a17(); virtual void a18(); virtual void a19(); virtual int v20();  };
extern "C" int DAT_005610a8[];
extern "C" int Gap__Gfx__igVertexArray2__vfunc_25(int arg0, int arg1);
#define REF_COUNT_MASK 0x7FFFFF
extern "C" void Gap__Gfx__igVertexStream__vfunc_27(igVertexStream *self);
class A162b50;
struct VertexArrayFormat;
extern "C" void *FUN_00189e40(...);
extern "C" void* FUN_0018a060(...);
extern "C" void *FUN_0018a2d0(...);
extern "C" int DAT_005610b0[4];
/* Builds the stream objects of a new vertex array. When the helper has no igVertexArray2 yet (+12
 * == 0) it creates one and, for every stream kind requested in the layout word *arg1, creates a
 * data list of `arg2` elements and wraps it in a stream record (kind in +16) appended to the
 * array's stream list (+16): bit 0 / bit 1 / bit 2 give kinds 1 / 3 / 2 (12 / 12 / 4 byte
 * elements); bits 16..19 (count) kind 4, one record per index (8 byte elements, index in +20);
 * bits 4..7 (count) kind 5, arg2 * count 4-byte elements, count in +24; bits 8..11 (count) kind 6,
 * arg2 * count 1-byte elements, count in +24; bits 20..21 (mode) kind 9, mode 1 = 4-byte list,
 * mode 2 = 8-byte list; bit 22 / bit 23 kinds 7 / 8 (12 byte elements). */

/* reference-counted engine object header: refcount (low 23 bits) at +4 */
struct RC { int vt; int rc; };
/* data list header: element count at +8, capacity at +12 */
struct DataList { int vt; int rc; int count; int cap; };
/* stream record: list at +12, kind at +16, index/count at +20/+24 */
struct StreamRec { int vt; int rc; int pad8; DataList *list; int kind; int index; int count; };
/* matching construct: stack smart-pointer slot (empty destructor) */
struct RP { RC *p; ~RP() {} };
#define REL_15ff10(x) { RC *q_ = (x); if (q_ != 0) { q_->rc = q_->rc - 1; if (((unsigned long long)((long long)q_->rc << 0x29) >> 0x29) == 0) igObject_Destroy((igObject *)q_); } }
#define SIZE_LIST(lst, n, esz) { DataList *dl_ = (lst); if ((n) >= 0) { if ((n) <= dl_->cap) { dl_->count = (n); } else { List_Resize(dl_, (n), (esz)); } } }
#define ATTACH(rec, lst) { RC *l_ = (RC *)(lst); StreamRec *r_ = (rec); if (l_ != 0) l_->rc = l_->rc + 1; REL_15ff10((RC *)r_->list) r_->list = (DataList *)l_; }
extern "C" int Gap__Gfx__igVertexArray2Helper__vfunc_23(igVertexArray2Helper *arg0, unsigned int *arg1, int arg2);
struct VertexArrayFormat : igObject {
    char pad8[16];
    int primitiveMode;
};
struct VertexFormatOwner : igObject {
    char pad8[12];
    VertexArrayFormat *format;

    void setFormat(const igSmartPointer<VertexArrayFormat> &next) {
        VertexArrayFormat *object = next.p;
        VertexArrayFormat *previous;

        if (object != 0) {
            object->_refCount = object->_refCount + 1;
        }
        previous = format;
        if (previous != 0) {
            previous->_refCount = previous->_refCount - 1;
            if ((previous->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(previous);
            }
        }
        format = object;
    }
};
extern "C" void Gap__Gfx__igVertexArray2Helper__vfunc_26(igVertexArray2Helper *helper, unsigned int flags);
extern "C" int Gap__Gfx__igVertexArray2Helper__vfunc_27(igVertexArray2Helper *self);
struct V_15ff10 { float x, y, z; };
struct A28 {
    char pad[8]; int f8; char pad2[4]; V_15ff10 *f16;
    static inline A28 *Cast(A28 *p) {
        if (p != 0 && igObject_IsKindOf((igObject *)p, g_igVec3fList_metaObject) != 0) {
            return p;
        }
        return 0;
    }
};
struct H { char pad[12]; void *f12; };
extern "C" void Gap__Gfx__igVertexArray2Helper__vfunc_28(H *arg0, int arg1, V_15ff10 *arg2);
extern "C" void Gap__Gfx__igVertexArray2Helper__vfunc_29(igVertexArray2Helper *arg0, int arg1, float *arg2);
struct A30 { int a,b,c,d; };
struct B_15ff10 { int a,b,c,d,e; };
extern "C" int Gap__Gfx__igVertexArray2Helper__vfunc_30(struct A30 *arg0, int arg1);
struct A_15ff10 { char pad[12]; int f12; };
struct M { char pad[8]; int cnt; char p2[4]; char *data; };
struct H31 { char pad[12]; struct A_15ff10 *a; };
extern "C" void Gap__Gfx__igVertexArray2Helper__vfunc_31(struct H31 *arg0, int arg1, float *arg2);
typedef struct O_15ff10 { char pad[12]; void *f12; } O_15ff10;
typedef struct Q_15ff10 { char pad[16]; V_15ff10 *f16; } Q_15ff10;
extern "C" void Gap__Gfx__igVertexArray2Helper__vfunc_32(A_15ff10 *arg0, int arg1, V_15ff10 *arg2);
extern "C" int Gap__Gfx__igVertexArray2Helper__vfunc_33(igVertexArray2Helper *arg0, int arg1);
typedef struct Q34 { char pad[8]; int f8; char pad2[4]; V_15ff10 *f16; } Q34;
extern "C" void Gap__Gfx__igVertexArray2Helper__vfunc_34(A_15ff10 *arg0, int arg1, V_15ff10 *arg2);
extern "C" void Gap__Gfx__igVertexArray2Helper__vfunc_35(igVertexArray2Helper *arg0, int arg1, float *arg2);
extern "C" V_15ff10 *Gap__Gfx__igVertexArray2Helper__vfunc_36(A_15ff10 *arg0, int arg1);
extern "C" void Gap__Gfx__igVertexArray2Helper__vfunc_37(igVertexArray2Helper *arg0, int arg1, void *arg2);
extern "C" void Gap__Gfx__igVertexArray2Helper__vfunc_38(igVertexArray2Helper *arg0, int arg1, void *arg2);
extern "C" V_15ff10 *Gap__Gfx__igVertexArray2Helper__vfunc_39(A_15ff10 *arg0, int arg1);
struct B4 { unsigned char b[4]; };
union U_15ff10 { int i; B4 b; };
class VC_15ff10 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); };
struct T_15ff10 : VC_15ff10 { int f4; int f8; int f12; int *f16; };
struct S_15ff10 { char pad[12]; T_15ff10 *f12; };
extern "C" void Gap__Gfx__igVertexArray2Helper__vfunc_40(igVertexArray2Helper *arg0, int arg1, U_15ff10 arg2);
extern "C" void Gap__Gfx__igVertexArray2Helper__vfunc_41(igVertexArray2Helper *arg0, int arg1, int arg2);
class Y_15ff10 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); char pad[12]; int *f16; };
struct X_15ff10 { char pad[12]; Y_15ff10 *f12; };
extern "C" int Gap__Gfx__igVertexArray2Helper__vfunc_42(A_15ff10 *arg0, int arg1);
struct T43 { char pad[16]; int *f16; };
struct S43 { char pad[12]; T43 *f12; };
class DW4VC_88_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); };
extern "C" void Gap__Gfx__igVertexArray2Helper__vfunc_43(igVertexArray2Helper *arg0, int arg1, int arg2);
struct T44 : VC_15ff10 { int f4; int f8; int f12; float *f16; };
struct S44 { char pad[12]; T44 *f12; int f16; int f20; int f24; };
struct V2_15ff10 { float f[2]; V2_15ff10(){} V2_15ff10(const V2_15ff10 &o){ f[0]=o.f[0]; f[1]=o.f[1]; } V2_15ff10 &operator=(const V2_15ff10 &o){ f[0]=o.f[0]; f[1]=o.f[1]; return *this; } float &operator[](int i){ return f[i]; } };
struct V3 { float f[3]; V3(){} V3(const V3 &o){ f[0]=o.f[0]; f[1]=o.f[1]; f[2]=o.f[2]; } V3 &operator=(const V3 &o){ f[0]=o.f[0]; f[1]=o.f[1]; f[2]=o.f[2]; return *this; } float &operator[](int i){ return f[i]; } };
struct V4 { float f[4]; V4(){} V4(const V4 &o){ f[0]=o.f[0]; f[1]=o.f[1]; f[2]=o.f[2]; f[3]=o.f[3]; } V4 &operator=(const V4 &o){ f[0]=o.f[0]; f[1]=o.f[1]; f[2]=o.f[2]; f[3]=o.f[3]; return *this; } float &operator[](int i){ return f[i]; } };
extern "C" void Gap__Gfx__igVertexArray2Helper__vfunc_44(igVertexArray2Helper *arg0, int arg1, int arg2, float arg3);
extern "C" float Gap__Gfx__igVertexArray2Helper__vfunc_45(igVertexArray2Helper *arg0, int arg1, int arg2);
class ByteList {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5();
    virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11();
    virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17();
    virtual void d18(); virtual void d19();
    virtual int getMeta();
    int _refCount;
    int _count;
    int _capacity;
    int _data;
};
struct VertexData { char pad[12]; ByteList *list; int f16; int f20; int stride; };
struct Byte3 { unsigned char c[3]; Byte3() {} Byte3(const Byte3 &o) { c[0] = o.c[0]; c[1] = o.c[1]; c[2] = o.c[2]; } Byte3 &operator=(const Byte3 &o) { c[0] = o.c[0]; c[1] = o.c[1]; c[2] = o.c[2]; return *this; } unsigned char &operator[](int i) { return c[i]; } };
struct Byte4 { unsigned char c[4]; Byte4() {} Byte4(const Byte4 &o) { c[0] = o.c[0]; c[1] = o.c[1]; c[2] = o.c[2]; c[3] = o.c[3]; } Byte4 &operator=(const Byte4 &o) { c[0] = o.c[0]; c[1] = o.c[1]; c[2] = o.c[2]; c[3] = o.c[3]; return *this; } unsigned char &operator[](int i) { return c[i]; } };
extern "C" void Gap__Gfx__igVertexArray2Helper__vfunc_46(igVertexArray2Helper *helper, int component, int index, unsigned char value);
struct B3 { unsigned char b[3]; };
struct T47 : VC_15ff10 { int f4; int f8; int f12; unsigned char *f16; };
struct S47 { char pad[12]; T47 *f12; int f16; int f20; int f24; };
extern "C" unsigned char Gap__Gfx__igVertexArray2Helper__vfunc_47(igVertexArray2Helper *arg0, int arg1, int arg2);
extern "C" void Gap__Gfx__igVertexArray2Helper__vfunc_48(igVertexArray2Helper *arg0, int arg1, int arg2, void *arg3);
extern "C" void Gap__Gfx__igVertexArray2Helper__vfunc_49(igVertexArray2Helper *arg0, int arg1, int arg2, float *arg3);
extern "C" int Gap__Gfx__igVertexArray2Helper__vfunc_50(igVertexArray2Helper *arg0, int arg1, int arg2);
typedef struct Q51 { char pad[16]; float *f16; } Q51;
extern "C" void Gap__Gfx__igVertexArray2Helper__vfunc_51(A_15ff10 *arg0, int arg1, float fparg0);
extern "C" float Gap__Gfx__igVertexArray2Helper__vfunc_52(A_15ff10 *arg0, int arg1);
struct V53 { float x, y; };
struct A53 {
    char pad[8]; int f8; char pad2[4]; V53 *f16;
    static inline A53 *Cast(A53 *p) {
        if (p != 0 && igObject_IsKindOf((igObject *)p, g_igVec2fList_metaObject) != 0) {
            return p;
        }
        return 0;
    }
};
extern "C" void Gap__Gfx__igVertexArray2Helper__vfunc_53(H *arg0, int arg1, V53 *arg2);
extern "C" void Gap__Gfx__igVertexArray2Helper__vfunc_54(igVertexArray2Helper *arg0, int arg1, void *arg2);
extern "C" void Gap__Gfx__igVertexArray2Helper__vfunc_24(igVertexArray2Helper *self);
extern "C" void Gap__Gfx__igVertexArray2Helper__vfunc_25(igVertexArray2Helper *self);
class S124 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual int vX(int); };
class S136 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual int vX(int); };
class S148 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual int vX(int); };
class S160 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual int vX(int); };
class S172 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual int vX(int); };
class S184 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual float vX(int, int); };
class S196 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual int vX(int, int); };
class S216 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual float vX(int); };
class S224 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void vX(int, void *); };
class S208 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual int vX(int, int); };
class D112 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void vY(int, int); };
class D124 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void vY(int, int); };
class D136 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void vY(int, int); };
class D148 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void vY(int, int); };
class D160 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void vY(int, int); };
class D176 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void vY(int, int, float); };
class D184 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void vY(int, int, int); };
class D204 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void vY(int, float); };
class D212 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void vY(int, void *); };
class D192 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void vY(int, int, int); };
extern "C" void Gap__Gfx__igVertexArray2Helper__vfunc_56(void **arg0, int arg1, void **arg2, int arg3, int *arg4);
extern "C" int Gap__Gfx__igVertexArray2Helper__vfunc_57(void);
class H58 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual int v96(); virtual int v100(); int pad4[2]; void *f12; };
extern "C" void Gap__Gfx__igVertexArray2Helper__vfunc_58(H58 *arg0, unsigned int *arg1);
class C_15ff10 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int v88(); };
class A162b50 { public: int pad[3]; C_15ff10 *f12; int pad2[2]; int f24; };
extern "C" int FUN_00162b50(A162b50 *arg0);
struct O162ca0 { int p0; int p4; int p8; DW4VC_88_0 *obj; int p10; int p14; int f18; };
extern "C" int FUN_00162ca0(void *a0);
struct FloatList { int vt; int rc; int count; int cap; float *data; };
struct VData { char pad[12]; FloatList *list; };
extern "C" void Gap__Gfx__igVertexArray2Helper__vfunc_59(igVertexArray2Helper *self, int type, float *out, int index);
extern "C" void Gap__Gfx__igVertexArray2Helper__vfunc_60(igVertexArray2Helper *self, int type, float *out, int index);
extern "C" int FUN_00163770(float fparg0, unsigned int arg0);
extern "C" float FUN_00163800(int arg0, int arg1);
/* igVertexArray2Helper slot 61's view of one igVertexData: the list is an object reference the
 * slot swaps for the quantised one. */
struct igQuantizedVertexData {
    int _vtable;
    unsigned int _refCount;
    int _name;
    igSmartPointer<igObject> _data;
    int _componentType;
    unsigned int _componentIndex;
    unsigned int _componentSize;
    int _userID;
    unsigned int _componentFraction;
};
struct igVec2fListView { int vt; int rc; int count; int cap; igVec2f *data; };
struct igVec3fListView { int vt; int rc; int count; int cap; igVec3f *data; };
struct igVec4fListView { int vt; int rc; int count; int cap; igVec4f *data; };
/* Home at landing: igTDataList.h (CoreLibrary.h holds the same template). */
template <class T> static inline void igRelease(igTDataList<T> *o) {
    if (o != 0) {
        o->_refCount = o->_refCount - 1;
        if ((o->_refCount & 0x7FFFFF) == 0) igObject_Destroy(o);
    }
}
extern "C" float Gap__Gfx__igVertexArray2Helper__vfunc_61(igVertexArray2Helper *self, int type, int bytes,
                                                          bool useFixed, bool isSigned, int bits, int index);
extern "C" ObjectRefWord *FUN_00164870(ObjectRefWord *self,int delete_storage);
extern "C" int *FUN_001649f0(void);
extern "C" int *FUN_00164a60(void);
extern "C" int *FUN_00164aa0(void);
extern "C" int *FUN_00164b10(void);
extern "C" int *FUN_00164b80(void);
extern "C" int *FUN_00164c20(void);
extern "C" int *FUN_00164c70(void);
extern "C" int *FUN_00164ca0(void);
extern "C" int *FUN_00164cd0(void);
extern "C" int DAT_00560750[4];
extern "C" int *FUN_00164d50(void);
class VC_164d60 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int v88(); };
struct A_164d60 { char pad12[12]; VC_164d60 *f12; unsigned int f16; };
extern "C" int FUN_00164d60(int arg0, A_164d60 *arg1);
/* The shared-pool globals are declared as 4-element arrays so they stay out of small data (lui/lw
 * addressing). Each arm of the pool fill stores the slot itself (the store is duplicated). */

/* igObjectSlotView is a local view of igObject that adds the one virtual the manager calls. The 23-bit
 * reference count lives in the word at +4 (decrement, then destroy when the masked count reaches zero).
 * The 29 dummy virtuals place vfunc_29 at vtable byte +124 = +0x08 + 4*29 (MWCC puts two header words
 * ahead of the slots). */

class igObjectSlotView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28();
    virtual void vfunc_29();
    unsigned int _refCount; /* +4: 23-bit reference count, flags above it */
};
static inline void igObject_Destroy(igObjectSlotView *object) { igObject_Destroy((igObject *)object); }
/* igVisualContext as its constructFields writes it: the memory pools and the timer are smart pointers
 * there, so the assignments carry the reference counting the reflected int fields cannot express. */
struct igVisualContextFieldsView {
    int vtable;
    int _pad04[5];
    igSmartPointer<igObjectSlotView> driverDataMemoryPool;
    igSmartPointer<igObjectSlotView> vertexMemoryPool;
    igSmartPointer<igObjectSlotView> internalMemoryPool;
    igSmartPointer<igObjectSlotView> temporaryMemoryPool;
    igSmartPointer<igObjectSlotView> imageMemoryPool;
    igSmartPointer<igObjectSlotView> textureMemoryPool;
    igSmartPointer<igObjectSlotView> statisticsMemoryPool;
    igSmartPointer<igObjectSlotView> listMemoryPool;
    igSmartPointer<igObjectSlotView> timer;
    int _pad60[61];
    igObjectSlotView *customStates;
    igObjectSlotView *customFields;
};

/* The pools igVisualContext_constructFields hands a new context, set beforehand by the static setters
 * (igVisualContext_SetImageMemoryPool); a null entry takes the owner's allocator. */
extern "C" igObjectSlotView *g_igVisualContext_defaultDriverDataMemoryPool[4];
extern "C" igObjectSlotView *g_igVisualContext_defaultVertexMemoryPool[4];
extern "C" igObjectSlotView *g_igVisualContext_defaultInternalMemoryPool[4];
extern "C" igObjectSlotView *g_igVisualContext_defaultTemporaryMemoryPool[4];
extern "C" igObjectSlotView *g_igVisualContext_defaultImageMemoryPool[4];
extern "C" igObjectSlotView *g_igVisualContext_defaultTextureMemoryPool[4];
extern "C" igObjectSlotView *g_igVisualContext_defaultStatisticsMemoryPool[4];
extern "C" igObjectSlotView *g_igVisualContext_defaultListMemoryPool[4];

extern "C" void igVisualContext_constructFields(igVisualContextFieldsView *self, int flags);
struct VisualContextCapabilityManager;
struct PropertyRoot {
    char pad0[56];
    void *properties;
};
struct VisualContextCapabilityManager {
    int _vtable;
    unsigned int _refCount;
    char pad8[12];
    int index;
    char pad24[36];
    unsigned char showFrameRate;
    unsigned char commandLineFrame;
};
typedef igTDataList<VisualContextCapabilityManager *> ManagerList;

extern "C" void FUN_00165a80(VisualContextCapabilityManager *self);
/* The lookup key lives in a stack object with a destructor, so it is kept in memory and its load
 * is hoisted. */
struct RefObj { int w0; int references; int count; int capacity; void **data; };

extern "C" void FUN_002ed5c0(...);
struct K { void *p; K(void *x) { p = x; } ~K() { } static void operator delete(void *q) { FUN_002ed5c0(q); } };
struct Finder {
    static int Find(RefObj *l, K &key) {
        int n = l->count;
        int i = 0;
        for (; i < n; i++) {
            if (key.p == l->data[i]) {
                return i;
            }
        }
        return -1;
    }
};
extern "C" void FUN_00165bb0(char *arg0);
extern "C" void igVisualContext_Reset(void *arg0);
extern "C" int igVisualContext_GetDriverDataMemoryPool(int *p);
extern "C" int igVisualContext_GetVertexMemoryPool(int *p);
extern "C" int igVisualContext_GetInternalMemoryPool(int *p);
extern "C" int igVisualContext_GetImageMemoryPool(int *p);
extern "C" int igVisualContext_GetStatisticsMemoryPool(int *p);
extern "C" int igVisualContext_GetListMemoryPool(int *p);
class V1 { public: virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4(); virtual void a5(); virtual void a6(); virtual void a7(); virtual void a8(); virtual void a9(); virtual void a10(); virtual void a11(); virtual void a12(); virtual void a13(); virtual void a14(); virtual void a15(); virtual void a16(); virtual void a17(); virtual void a18(); virtual void a19(); virtual void a20(); virtual void a21(); virtual void a22(); virtual void a23(); virtual void a24(); virtual void a25(); virtual void a26(); virtual void a27(); virtual void a28(); virtual void a29(); virtual void a30(); virtual void a31(); virtual void a32(); virtual void a33(); virtual void a34(); virtual void a35(); virtual void a36(); virtual void a37(); virtual void a38(); virtual void a39(); virtual void a40(); virtual void a41(); virtual void a42(); virtual void a43(); virtual void a44(); virtual void a45(); virtual void a46(); virtual void a47(); virtual void a48(); virtual void a49(); virtual void a50(); virtual void a51(); virtual void a52(); virtual void a53(); virtual void a54(); virtual void a55(); virtual void a56(); virtual void a57(); virtual void a58(); virtual void a59(); virtual void a60(); virtual void a61(); virtual void a62(); virtual void a63(); virtual void v264(void *); };
class V2_165d30 { public: virtual void b0(); virtual void b1(); virtual void b2(); virtual void b3(); virtual void b4(); virtual void b5(); virtual void b6(); virtual void b7(); virtual void b8(); virtual void b9(); virtual void b10(); virtual void b11(); virtual void b12(); virtual void b13(); virtual void b14(); virtual void b15(); virtual void b16(); virtual void b17(); virtual void b18(); virtual void b19(); virtual void b20(); virtual void b21(); virtual void b22(); virtual void b23(); virtual void b24(); virtual void b25(); virtual void b26(); virtual void b27(); virtual void b28(); virtual void b29(); virtual void b30(); virtual void b31(); virtual void b32(); virtual void b33(); virtual void b34(); virtual void b35(); virtual void b36(); virtual void b37(); virtual void b38(); virtual void b39(); virtual void b40(); virtual void b41(); virtual void b42(); virtual void b43(); virtual void b44(); virtual void b45(); virtual void b46(); virtual void b47(); virtual void b48(); virtual void b49(); virtual void b50(); virtual void b51(); virtual void b52(); virtual void *v220(unsigned int, int); };
struct O_165d30 { char p72_[72]; unsigned int f72; int f76; void *f80; int f84; unsigned int f88; };
extern "C" int FUN_001903d0(...);

extern "C" void igVisualContext_SetBlendingMatrices(O_165d30 *arg0, unsigned int arg1, int arg2);
extern "C" int igVisualContext_GetBlendingMatricesCount(void *arg0);

struct Mat;
struct Self;
struct V_165e50;
struct Fl { int b; };
struct Obj_165e50 {
 virtual void v8();
 virtual void v12();
 virtual void v16();
 virtual void v20();
 virtual void v24();
 virtual void v28();
 virtual void v32();
 virtual void v36();
 virtual void v40();
 virtual void v44();
 virtual void v48();
 virtual void v52();
 virtual void v56();
 virtual void v60();
 virtual void v64();
 virtual void v68();
 virtual void v72();
 virtual void v76();
 virtual void v80();
 virtual void v84();
 virtual void v88();
 virtual void v92();
 virtual void v96(int *, int, int, Self *);
 virtual struct Fl *v100();
 virtual void v104();
 virtual void v108();
 virtual void v112();
 virtual void v116(int, V_165e50 *);
 virtual void v120();
 virtual V_165e50 *v124(int);
 virtual void v128(int, V_165e50 *);
 virtual void v132();
 virtual V_165e50 *v136(int);
 virtual void v140();
 virtual void v144();
 virtual void v148();
 virtual void v152();
 virtual void v156();
 virtual void v160();
 virtual void v164(int, int);
 virtual void v168();
 virtual int v172(int);
 virtual void v176();
 virtual void v180();
 virtual float v184(int, int);
 virtual void v188();
 virtual void v192();
 virtual unsigned char v196(int, int);
 virtual void v200(int, int, int);
 virtual void v204();
 virtual int v208(int, int);
 virtual void v212();
 virtual Mat *v216(int);
 virtual void v220();
 int pad[2]; int count; int pad2; int count2;
};
struct V_165e50 { float x, y, z;
 void operator=(const V_165e50 &o) { (&x)[0] = (&o.x)[0]; (&x)[1] = (&o.x)[1]; (&x)[2] = (&o.x)[2]; }
 void operator-=(const V_165e50 &o) { (&x)[0] -= (&o.x)[0]; (&x)[1] -= (&o.x)[1]; (&x)[2] -= (&o.x)[2]; }
 void operator+=(const V_165e50 &o) { (&x)[0] += (&o.x)[0]; (&x)[1] += (&o.x)[1]; (&x)[2] += (&o.x)[2]; }
 void operator*=(float s) { (&x)[0] *= s; (&x)[1] *= s; (&x)[2] *= s; }
 float dot(V_165e50 &o) { return (&x)[0] * (&o.x)[0] + (&x)[1] * (&o.x)[1] + (&x)[2] * (&o.x)[2]; }
 void normalize() { float inv = 1.0f / sqrtf(dot(*this)); *this *= inv; }
};
struct Mat { float m[16]; };
struct Self { char pad[72]; int matCount; char pad2[8]; Mat *mats; };
extern "C" void *FUN_00165e50(Self *self, Obj_165e50 *src);
/* Resets a visual context to its default render state; the flags select which state groups. Vtable
 * entries are 4 bytes starting at +8, so slot N is at offset 8 + 4*N; slots are named by index
 * because the methods are unnamed. */
struct Vec4 { float x, y, z, w; };
class igVisualContext_166400 {
public:
    virtual void vfunc_0(); virtual void vfunc_1(); virtual void vfunc_2(); virtual void vfunc_3();
    virtual void vfunc_4(); virtual void vfunc_5(); virtual void vfunc_6(); virtual void vfunc_7();
    virtual void vfunc_8(); virtual void vfunc_9(); virtual void vfunc_10(); virtual void vfunc_11();
    virtual void vfunc_12(); virtual void vfunc_13(); virtual void vfunc_14();
    virtual void vfunc_15(); virtual void vfunc_16(); virtual void vfunc_17();
    virtual void vfunc_18(); virtual void vfunc_19(); virtual void vfunc_20();
    virtual void vfunc_21(); virtual void vfunc_22(); virtual void vfunc_23();
    virtual void vfunc_24(); virtual void vfunc_25(); virtual void vfunc_26();
    virtual void vfunc_27(); virtual void vfunc_28(); virtual void vfunc_29();
    virtual void vfunc_30(); virtual void vfunc_31(); virtual void vfunc_32();
    virtual void vfunc_33(); virtual void vfunc_34(); virtual int vfunc_35(int);
    virtual void vfunc_36(); virtual void vfunc_37(); virtual void vfunc_38();
    virtual void vfunc_39(); virtual void vfunc_40(); virtual void vfunc_41();
    virtual void vfunc_42(); virtual void vfunc_43(); virtual void vfunc_44();
    virtual void vfunc_45(); virtual void vfunc_46(); virtual void vfunc_47();
    virtual void vfunc_48(); virtual void vfunc_49(); virtual void vfunc_50();
    virtual void vfunc_51(); virtual void vfunc_52(); virtual void vfunc_53();
    virtual void vfunc_54(); virtual void vfunc_55(); virtual void vfunc_56();
    virtual void vfunc_57(); virtual void vfunc_58(); virtual void vfunc_59();
    virtual void vfunc_60(); virtual void vfunc_61(); virtual void vfunc_62();
    virtual void vfunc_63(const Vec4 *); virtual void vfunc_64(); virtual void vfunc_65();
    virtual void vfunc_66(); virtual void vfunc_67(const int *); virtual void vfunc_68();
    virtual void vfunc_69(); virtual void vfunc_70(); virtual void vfunc_71();
    virtual void vfunc_72(); virtual void vfunc_73(int); virtual void vfunc_74();
    virtual void vfunc_75(); virtual void vfunc_76(); virtual void vfunc_77();
    virtual void vfunc_78(); virtual void vfunc_79(); virtual void vfunc_80();
    virtual void vfunc_81(); virtual void vfunc_82(); virtual void vfunc_83();
    virtual void vfunc_84(); virtual void vfunc_85(); virtual void vfunc_86();
    virtual void vfunc_87(); virtual void vfunc_88(); virtual void vfunc_89();
    virtual void vfunc_90(); virtual void vfunc_91(); virtual void vfunc_92();
    virtual void vfunc_93(); virtual void vfunc_94(); virtual void vfunc_95();
    virtual void vfunc_96(float); virtual void vfunc_97(); virtual void vfunc_98(int);
    virtual void vfunc_99(); virtual void vfunc_100(const Vec4 *); virtual void vfunc_101();
    virtual void vfunc_102(const Vec4 *); virtual void vfunc_103();
    virtual void vfunc_104(const Vec4 *); virtual void vfunc_105();
    virtual void vfunc_106(const Vec4 *); virtual void vfunc_107(); virtual void vfunc_108(int);
    virtual void vfunc_109(); virtual void vfunc_110(); virtual void vfunc_111(int);
    virtual void vfunc_112(); virtual void vfunc_113(const Vec4 *); virtual void vfunc_114();
    virtual void vfunc_115(int, int); virtual void vfunc_116(); virtual void vfunc_117();
    virtual void vfunc_118(); virtual void vfunc_119(); virtual void vfunc_120();
    virtual void vfunc_121(); virtual void vfunc_122(); virtual void vfunc_123();
    virtual void vfunc_124(); virtual void vfunc_125(); virtual void vfunc_126();
    virtual void vfunc_127(); virtual void vfunc_128(); virtual void vfunc_129();
    virtual void vfunc_130(); virtual void vfunc_131(); virtual void vfunc_132();
    virtual void vfunc_133(); virtual void vfunc_134(); virtual void vfunc_135();
    virtual void vfunc_136(); virtual void vfunc_137(); virtual void vfunc_138();
    virtual void vfunc_139(); virtual void vfunc_140(); virtual void vfunc_141();
    virtual void vfunc_142(); virtual void vfunc_143(int); virtual void vfunc_144();
    virtual void vfunc_145(); virtual void vfunc_146(int, int); virtual void vfunc_147();
    virtual void vfunc_148(int, int, int); virtual void vfunc_149(); virtual void vfunc_150(int);
    virtual void vfunc_151(); virtual void vfunc_152(); virtual void vfunc_153();
    virtual void vfunc_154(); virtual void vfunc_155(); virtual void vfunc_156(int, int);
    virtual void vfunc_157(int); virtual void vfunc_158(); virtual void vfunc_159(int);
    virtual void vfunc_160(); virtual void vfunc_161(int); virtual void vfunc_162();
    virtual void vfunc_163(int, int, int); virtual void vfunc_164(); virtual void vfunc_165(int);
    virtual void vfunc_166(); virtual void vfunc_167(int); virtual void vfunc_168();
    virtual void vfunc_169(); virtual void vfunc_170(); virtual void vfunc_171();
    virtual void vfunc_172(); virtual void vfunc_173(); virtual void vfunc_174();
    virtual void vfunc_175(const Vec4 *); virtual void vfunc_176(); virtual void vfunc_177();
    virtual void vfunc_178(); virtual void vfunc_179(float); virtual void vfunc_180();
    virtual void vfunc_181(int); virtual void vfunc_182(); virtual void vfunc_183();
    virtual void vfunc_184(); virtual void vfunc_185(); virtual void vfunc_186();
    virtual void vfunc_187(); virtual void vfunc_188(int); virtual void vfunc_189();
    virtual void vfunc_190(); virtual void vfunc_191(); virtual void vfunc_192();
    virtual void vfunc_193(); virtual void vfunc_194(); virtual void vfunc_195();
    virtual void vfunc_196(); virtual void vfunc_197(); virtual void vfunc_198();
    virtual void vfunc_199(); virtual void vfunc_200(); virtual void vfunc_201();
    virtual void vfunc_202(); virtual void vfunc_203(); virtual void vfunc_204();
    virtual void vfunc_205(); virtual void vfunc_206(); virtual void vfunc_207(int, int);
    virtual void vfunc_208(); virtual void vfunc_209(int); virtual void vfunc_210();
    virtual void vfunc_211(); virtual void vfunc_212(); virtual void vfunc_213();
    virtual void vfunc_214(); virtual void vfunc_215(int); virtual void vfunc_216();
    virtual void vfunc_217(int); virtual void vfunc_218(); virtual void vfunc_219(float);
    virtual void vfunc_220(); virtual void vfunc_221(int); virtual void vfunc_222();
    virtual void vfunc_223(int, int, int, int); virtual void vfunc_224();
    virtual void vfunc_225(int); virtual void vfunc_226(); virtual void vfunc_227(int);
    virtual void vfunc_228(); virtual void vfunc_229(int); virtual void vfunc_230();
    virtual void vfunc_231(int); virtual void vfunc_232(); virtual void vfunc_233(int);
    virtual void vfunc_234(); virtual void vfunc_235(int); virtual void vfunc_236();
    virtual void vfunc_237(int); virtual void vfunc_238(); virtual void vfunc_239(int);
    virtual void vfunc_240(); virtual void vfunc_241(float); virtual void vfunc_242();
    virtual void vfunc_243(int); virtual void vfunc_244(); virtual void vfunc_245(const Vec4 *);
    virtual void vfunc_246(); virtual void vfunc_247(float); virtual void vfunc_248();
    virtual void vfunc_249(float); virtual void vfunc_250(); virtual void vfunc_251();
    virtual void vfunc_252(); virtual void vfunc_253(); virtual void vfunc_254();
    virtual void vfunc_255(); virtual void vfunc_256(); virtual void vfunc_257();
    virtual void vfunc_258(); virtual void vfunc_259(int, int);
};

/* "fillMode" */
struct SystemConfig { char pad[56]; void *settings; };
extern "C" void igVisualContext_ResetToDefault(igVisualContext_166400 *ctx, int flags);
extern "C" void FUN_00166a60(void *arg0, char arg1);

extern "C" float DAT_0048a470[4];
extern "C" float DAT_005607a0[4];
extern "C" float DAT_005607a8[4];
extern "C" int DAT_005607b0[4];
extern "C" float DAT_005607b8[4];
extern "C" float DAT_005607c0[4];
extern "C" float DAT_00560838[4];
class C_166a70 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27();  virtual void vX(int, int, int *); char pad[57]; unsigned char f61; };
extern "C" void igVisualContext_UpdateFrameRateDisplay(void *arg0_, float fparg0, float fparg1);
extern "C" void igVisualContext_OutputText(void);
extern "C" void igVisualContext_UpdatePrimitiveCountDisplay(void);
class DW4VC_240_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual int vX(int); };
class DW4VC_248_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual int vX(); };
class DW4VC_284_3 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual int vX(int, int, int); };
extern "C" void igVisualContext_DrawNonIndexed(void **arg0, int arg1, int arg2, int arg3);
struct L_166d40 { char pad[8]; int count; int pad2; int *items; };
struct ShaderSetup {
    char pad[56];
    void *registry;
    void *builder;
};

extern "C" void FUN_002daab0(void *builder, void *registry, int kind, int flags);
extern "C" void igVisualContext_LoadDefaultDriverDatabase(int value);
extern "C" void FUN_00166f90(void);
extern "C" int FUN_00166fa0(void);
extern "C" void FUN_00166fb0(void);
extern "C" int FUN_00166fc0(void);
extern "C" int igVisualContext_GetLastError(void);
/* The object FUN_00166fe0 stores: slot 23 is called with four zeroes when it has nothing at +12 yet. */
class SlotObject_166fe0 : public igVirtualObject {
public:
    virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6();
    virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12();
    virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18();
    virtual void d19(); virtual void d20();
    virtual void v23(int, int, int, int);
    int f8;
    igSmartPointer<igObject> f12;
};
class SlotOwner_166fe0 {
public:
    virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5();
    virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11();
    virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17();
    virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
    virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35();
    virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41();
    virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47();
    virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53();
    virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58();
    virtual void v59(igObject *);
    char pad4[236];
    igSmartPointer<SlotObject_166fe0> slots[1];
};
extern "C" void FUN_00166fe0(SlotOwner_166fe0 *self, SlotObject_166fe0 *object, int index);
extern "C" igSmartPointer<igObject> FUN_00167130(SlotObject_166fe0 *object);
extern "C" int igVisualContext_GetVertexArray2(int arg0, int arg1);
extern "C" void igVisualContext_SetViewMatrixHint(struct MatrixInverseCache *self, const float *matrix);
extern "C" void igVisualContext_GetViewMatrixHint(char * arg0, int arg1);
typedef struct MatrixInverseCache {
    char pad0[108];
    float matrix[16];
    float inverse[16];
    unsigned char inverseDirty;
} MatrixInverseCache;
extern "C" void igVisualContext_GetViewMatrixInverse(MatrixInverseCache *self, float *out);
/* Dummy class: igVisualContext virtual at vtable byte offset 148. */
class VisualContextQuerySlot {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4();
    virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
    virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14();
    virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24();
    virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
    virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34();
    virtual int Query();
};
extern "C" int Gap__Gfx__igVisualContextCapabilityManager__vfunc_23(igVisualContextCapabilityManager *self);
typedef struct P_167240 { char pad8[8]; int f8; int fc; int f10; } P_167240;
extern "C" int Gap__Gfx__igPrimLengthArray1_1__vfunc_23(P_167240 *arg0, int arg1, int arg2);
extern "C" void Gap__Gfx__igPrimLengthArray1_1__vfunc_26(igPrimLengthArray1_1 *self, int stripIndex, int length);
extern "C" int Gap__Gfx__igPrimLengthArray1_1__vfunc_27(igPrimLengthArray1_1 *self, int stripIndex);
extern "C" int Gap__Gfx__igPrimLengthArray1_1__vfunc_24(igPrimLengthArray1_1 *arg0, int dummy1, int arg2);
extern "C" void Gap__Gfx__igPrimLengthArray1_1__vfunc_25(void);
extern "C" int DAT_00560840;
extern "C" void *FUN_00167310(png_structp png, int size);
extern "C" void FUN_00167320(png_structp png, void *storage);
class DW4VC_108_3 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual int vX(int, int, int); };
extern "C" void FUN_00167330(png_structp png, int arg1, int arg2);
extern "C" void FUN_00167380(void);
extern "C" void FUN_00167390(void);
extern "C" void FUN_001673a0(png_structp png_ptr, png_row_infop row_info, png_bytep data);
extern "C" void thunk_FUN_001592c0(LongListStorageView *self);
/* igImage copy: dimensions, format, name and bit depths from `source`; pixels and palette only when `deep`. A self
 * copy only makes borrowed pixels local. */
extern "C" void FUN_001563b0(igImage *self, igImage *source, int deep);
extern "C" void Gap__Gfx__igFileImagePng__vfunc_23(igImage *self, void **source, int deep);
extern "C" igMetaObject *FUN_00167400(void);
class Obj_167410 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual int vX(); };
struct Owner_167410 { char pad[92]; Obj_167410 *f92; };
extern "C" int FUN_00167410(Owner_167410 *arg0, png_structp arg1, png_infop arg2, png_infop arg3, void *arg4, void *arg5, int arg6, int arg7);
typedef struct PngSignificantBits {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    unsigned char gray;
    unsigned char alpha;
} PngSignificantBits;
extern "C" int FUN_00167540(void *png, int bitDepth, int colorType, PngSignificantBits *bits, int *format);
/* libpng's palette entry (png_color). */
struct PngColor {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};
/* igClut's slot 24: replaces the entries (format, count, data). */
class igClutEntries : public igVirtualObject {
public:
    virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8();
    virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14();
    virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();
    virtual void d21(); virtual void d22(); virtual void d23();
    virtual int setEntries(int format, int count, void *entries);
    /* Slot 25, the TGA loader's palette store (same arguments). */
    virtual int storeEntries(int format, int count, void *entries);
};
/* igFileImagePng: an igImage that keeps the file it reads from. */
struct igFileImagePngView : public igImage {
    igSmartPointer<VStream_158f50> _file;
};
extern "C" int Gap__Gfx__igFileImagePng__vfunc_33(igFileImagePngView *self, int name);
/* Sets libpng's read transforms for an image (16-bit stripped, small palettes and grey unpacked, tRNS to alpha). */
extern "C" int FUN_001681c0(igImage *self, png_structp png, png_infop info);
extern "C" int Gap__Gfx__igFileImagePng__vfunc_45(void);
extern "C" void igTgaLoader_ReleaseDefaults(igObject *self);
class O_1682e0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void vX(); int rc; };
struct S_1682e0 { char pad[8]; O_1682e0 *f8; int f12; int f16; int f20; int f24; int f28; };
extern "C" int FUN_001682e0(S_1682e0 *arg0, int arg1);
extern "C" int FUN_001683a0(void *arg0);
extern "C" int FUN_00168400(void *arg0);
extern "C" unsigned char FUN_00168420(void *arg0);
struct D { char pad24[24]; int f24; int f28; int f32; };
extern "C" void FUN_00168480(struct D *arg0, char *arg1);
extern "C" int FUN_00168570(int arg0, unsigned int arg1, int arg2, int *arg3, int *arg4, int *arg5, char *arg6);
/* igFile as the TGA loader drives it: open/close/read and seek (whence 0 set, 1 current). */
class igTgaFile : public igVirtualObject {
public:
    virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8();
    virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14();
    virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();
    virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24();
    virtual int open(int name, const char *mode);
    virtual void close();
    virtual int read(void *buffer, int size, int count);
    virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33();
    virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37();
    virtual int seek(int offset, int whence);
};
/* igTgaLoader: the file, palette buffers, the run-length state FUN_00168480 keeps and the read buffer. */
struct igTgaLoaderView : public igObject {
    igSmartPointer<igTgaFile> _file;
    unsigned char *_palette;
    unsigned char *_rawPalette;
    unsigned char *_buffer;
    int _runCount;
    int _runRepeat;
    int _bytesPerPixel;
    int _position;
    int _available;
    int _bufferSize;
};
/* The loader's source: the file name at +8 (0: the empty string). */
struct igTgaSource { int _vtable; unsigned int _refCount; int _name; };
extern "C" unsigned char DAT_0048a480[12][4];
extern "C" unsigned char DAT_0048a4b0[16];
extern "C" unsigned char DAT_0048a4c0[32];
extern "C" int Gap__Gfx__igTgaLoader__vfunc_23(igTgaLoaderView *self, igTgaSource *source, igImage *image);
struct VisualContextTextures;
class TextureImage;
struct O520;
struct S0_1690d0;
struct Oab80;
struct OB1d0;

extern "C" void p2CallDisplayList(p2DisplayList *list);

extern "C" void *FUN_002ed240(int, int);
extern "C" void *FUN_002ed450(void *, int, int);
extern "C" void FUN_0017a540(igPsx2VisualContext *vc, int keepLists);
extern "C" void igImage_SetPixels(TextureImage *image, void *pixels, int format, int width, int height);

extern "C" void FUN_00203580(void *source, int sourceFormat, int width, int height, int layout, void *pixels, int flags);
extern "C" void FUN_00203c50(void *source, int sourceFormat, int width, int height, int layout, void *pixels, int flags);
extern "C" void FUN_00209cf0(int a, int b, int c, int d, int e, int f, int g);
extern "C" int FUN_0020bb20(...);

extern "C" int DAT_0048a4e0[4];
extern "C" int DAT_0048a4ec[4];
extern "C" int DAT_0048a4f0[4];
extern "C" int DAT_0048acd0[];
struct P_1690d0 { unsigned short f0; unsigned short f2; unsigned short f4; char p6[2]; int *f8; short *f12; int f16; };
class Buf860 { public: virtual void b0(); virtual void b1(); virtual void b2(); virtual void b3(); virtual void b4(); virtual void b5(); virtual void b6(); virtual void b7(); virtual void b8(); virtual void b9(); virtual void b10(); virtual void b11(); virtual void b12(); virtual void b13(); virtual void b14(); virtual void b15(); virtual void b16(); virtual void b17(); virtual void b18(); virtual void b19(); virtual void b20(); virtual void b21(); virtual void b22(); virtual void b23(); virtual void b24(); virtual void b25(); virtual void b26(); virtual void b27(); virtual void b28(); virtual void b29(); virtual void b30(); virtual void b31(); virtual void b32(); virtual void b33(); virtual void b34(); virtual void b35(); virtual void b36(); virtual void b37(); virtual void b38(); virtual void b39(); virtual void b40(); virtual void b41(); virtual void b42(); virtual void b43(); virtual void b44(); virtual void b45(); virtual void b46(); virtual void b47(); virtual void b48(); virtual void b49(); virtual void b50(); virtual void b51(); virtual void b52(); virtual void b53(); virtual short *vB(int n, int sz); virtual int vA(int n, int sz, int al); };
class VM { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void* v232(void*,int); };
struct Arg0d0 { char pad[868]; P_1690d0 *f868; int f872; };
extern "C" void FUN_001690d0(Arg0d0 *arg0);
struct T260 { unsigned short f0; unsigned short f2; unsigned short f4; short pad2; int f8; unsigned short *f12; int f16;
    bool Chk(int s0) {
        int a2, a1;
        if (s0 < f0 && s0 >= 0) {
            a1 = f4;
            for (a2 = 0; a2 < a1; a2++) {
                if (s0 == f12[a2]) return false;
            }
            return true;
        }
        return false;
    }
    void Add(int s0) {
        if (s0 < f0 && s0 >= 0) {
            if (f4 >= f2) {
                VM *o = (VM *)Memory_FindBufferOwner(this);
                f2 = f2 + 8;
                f12 = (unsigned short *)o->v232(f12, f2 * 2);
            }
            f12[f4] = s0;
            f4 = f4 + 1;
        }
    }
};
extern "C" void FUN_00169260(igPsx2VisualContext *arg0, int arg1);
struct Ent46 { int f0; int f4; int f8; int f12; int f16; int f20; float f24; int f28; int f32; int f36; int f40; int f44; };
struct Pool46 { unsigned short f0; unsigned short f2; unsigned short f4; char p6[6]; unsigned short *f12; Ent46 *f16; };
class Buf46 { public: virtual void b0(); virtual void b1(); virtual void b2(); virtual void b3(); virtual void b4(); virtual void b5(); virtual void b6(); virtual void b7(); virtual void b8(); virtual void b9(); virtual void b10(); virtual void b11(); virtual void b12(); virtual void b13(); virtual void b14(); virtual void b15(); virtual void b16(); virtual void b17(); virtual void b18(); virtual void b19(); virtual void b20(); virtual void b21(); virtual void b22(); virtual void b23(); virtual void b24(); virtual void b25(); virtual void b26(); virtual void b27(); virtual void b28(); virtual void b29(); virtual void b30(); virtual void b31(); virtual void b32(); virtual void b33(); virtual void b34(); virtual void b35(); virtual void b36(); virtual void b37(); virtual void b38(); virtual void b39(); virtual void b40(); virtual void b41(); virtual void b42(); virtual void b43(); virtual void b44(); virtual void b45(); virtual void b46(); virtual void b47(); virtual void b48(); virtual void b49(); virtual void b50(); virtual void b51(); virtual void b52(); virtual void b53(); virtual void b54(); virtual void b55(); virtual unsigned short *vB(unsigned short *p, int n); };
class DW4VC_524 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual void d101(); virtual void d102(); virtual void d103(); virtual void d104(); virtual void d105(); virtual void d106(); virtual void d107(); virtual void d108(); virtual void d109(); virtual void d110(); virtual void d111(); virtual void d112(); virtual void d113(); virtual void d114(); virtual void d115(); virtual void d116(); virtual void d117(); virtual void d118(); virtual void d119(); virtual void d120(); virtual void d121(); virtual void d122(); virtual void d123(); virtual void d124(); virtual void d125(); virtual void d126(); virtual void d127(); virtual void d128(); virtual void vX(int, void *); };
class DW4VC_232 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void *vX(void *, int); };
struct Ent47 { char pad[36]; int f36; char pad2[8]; };
struct Tb { char pad[16]; Ent47 *f16; };
struct Ar { unsigned short n; unsigned short cap; unsigned short cnt; char pad[6]; void *f12; Ent47 *f16; };
extern "C" void igPsx2VisualContext_DeleteRenderDestination(igPsx2VisualContext *arg0, int arg1);
struct I { int w; int h; int p8; int f12; int p16[3]; int f28; int p32[2]; int f40; int f44; };
struct L48 { char pad[16]; I *f16; };
class V_1690d0 { public:
virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual void d101(); virtual void d102(); virtual void d103(); virtual void d104(); virtual void d105(); virtual void d106(); virtual void d107(); virtual void d108(); virtual void d109(); virtual void d110(); virtual void d111(); virtual void d112(); virtual void d113(); virtual void d114(); virtual void d115(); virtual void d116(); virtual void d117(); virtual void d118(); virtual void d119(); virtual void d120(); virtual void d121(); virtual void d122(); virtual void d123(); virtual void d124(); virtual void d125(); virtual void d126(); virtual void d127(); virtual void d128(); virtual void d129(); virtual void d130(); virtual void d131(); virtual void d132(); virtual void d133(); virtual void d134(); virtual void d135(); virtual void d136(); virtual void d137(); virtual void d138(); virtual void d139(); virtual void d140(); virtual void d141(); virtual void d142(); virtual void d143(); virtual void d144(); virtual void d145(); virtual void d146(); virtual void d147(); virtual void d148(); virtual void d149(); virtual void d150(); virtual void d151(); virtual void d152(); virtual void d153(); virtual void d154(); virtual void d155(); virtual void d156(); virtual void d157(); virtual void d158(); virtual void d159(); virtual void d160(); virtual void d161(); virtual void d162(); virtual void d163(); virtual void d164(); virtual void d165(); virtual void d166(); virtual void d167(); virtual void d168(); virtual void d169(); virtual void d170(); virtual void d171(); virtual void d172(); virtual void d173(); virtual void d174(); virtual void d175(); virtual void d176(); virtual void d177(); virtual void d178(); virtual void d179(); virtual void d180(); virtual void d181(); virtual void d182(); virtual void d183(); virtual void d184(); virtual void d185(); virtual void d186(); virtual void d187(); virtual void d188(); virtual void d189(); virtual void d190(); virtual void d191(); virtual void d192(); virtual void d193(); virtual void d194(); virtual void d195(); virtual void d196(); virtual void d197(); virtual void d198(); virtual void d199(); virtual void d200(); virtual void d201(); virtual void d202(); virtual void d203(); virtual void d204(); virtual void d205(); virtual void d206(); virtual void d207(); virtual void d208(); virtual void d209(); virtual void d210(); virtual void d211(); virtual void d212(); virtual void d213(); virtual void d214(); virtual void d215(); virtual void d216(); virtual void d217(); virtual void d218(); virtual void d219(); virtual void d220(); virtual void d221(); virtual void d222(); virtual void d223(); virtual void d224(); virtual void d225(); virtual void d226(); virtual void d227(); virtual void d228(); virtual void d229(); virtual void d230(); 
virtual void vX(int);
char pad[864]; L48 *f868; int f872; char pad2[40]; int f916; int f920; int f924; int f928; float f932; float f936; };
struct Buf49 { int width; int height; int format; int depthFormat; int f16; int p20[4]; int texIndex; int colorTex; int depthTex; };
struct BufList49 { char pad[16]; Buf49 *records; };
struct Tex49 { char pad[72]; int *handle; int depthHandle; char pad80[52]; int state; };
struct TexList49 { char pad[16]; Tex49 *records; };
class VC49 { public:
virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual void d101(); virtual void d102(); virtual void d103(); virtual void d104(); virtual void d105(); virtual void d106(); virtual void d107(); virtual void d108(); virtual void d109(); virtual void d110(); virtual void d111(); virtual void d112(); virtual void d113(); virtual void d114(); virtual void d115(); virtual void d116(); virtual void d117(); virtual void d118(); virtual void d119(); virtual void d120(); virtual void d121(); virtual void d122(); virtual void d123(); virtual void d124(); virtual void d125(); virtual void d126(); virtual void d127();
virtual void releaseTexture(int); virtual void freeTexture(int);
virtual void e130(); virtual void e131(); virtual void e132(); virtual void e133(); virtual void e134(); virtual void e135(); virtual void e136(); virtual void e137(); virtual void e138(); virtual void e139(); virtual void e140(); virtual void e141(); virtual void e142(); virtual void e143(); virtual void e144(); virtual void e145(); virtual void e146(); virtual void e147(); virtual void e148(); virtual void e149(); virtual void e150(); virtual void e151(); virtual void e152(); virtual void e153(); virtual void e154(); virtual void e155(); virtual void e156(); virtual void e157(); virtual void e158(); virtual void e159(); virtual void e160(); virtual void e161(); virtual void e162(); virtual void e163(); virtual void e164(); virtual void e165(); virtual void e166(); virtual void e167(); virtual void e168(); virtual void e169(); virtual void e170(); virtual void e171(); virtual void e172(); virtual void e173(); virtual void e174(); virtual void e175(); virtual void e176(); virtual void e177(); virtual void e178(); virtual void e179(); virtual void e180(); virtual void e181(); virtual void e182(); virtual void e183(); virtual void e184(); virtual void e185(); virtual void e186(); virtual void e187(); virtual void e188(); virtual void e189(); virtual void e190(); virtual void e191(); virtual void e192(); virtual void e193(); virtual void e194(); virtual void e195(); virtual void e196(); virtual void e197(); virtual void e198(); virtual void e199(); virtual void e200(); virtual void e201(); virtual void e202(); virtual void e203(); virtual void e204(); virtual void e205(); virtual void e206(); virtual void e207(); virtual void e208(); virtual void e209(); virtual void e210(); virtual void e211(); virtual void e212(); virtual void e213(); virtual void e214(); virtual void e215(); virtual void e216(); virtual void e217(); virtual void e218(); virtual void e219(); virtual void e220(); virtual void e221(); virtual void e222(); virtual void e223(); virtual void e224(); virtual void e225(); virtual void e226(); virtual void e227(); virtual void e228(); virtual void e229(); virtual void e230();
virtual void setDepth(int);
char pad[320]; TexList49 *texList; char pad328[540]; BufList49 *bufList; int currentBuf; char pad876[56]; float near; float far; };
extern "C" int igPsx2VisualContext_SetRenderDestinationSize(igPsx2VisualContext *self, int bufferIndex, int word0, int word1);
#define BUFFER_RECORD_SIZE 0x30  /* bytes per _pBufList record */
extern "C" int igPsx2VisualContext_GetRenderDestinationType(igPsx2VisualContext *self, int bufferIndex);
extern "C" void FUN_00169be0(void *d0, int arg1);
class TextureImage {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void d24(); virtual void d25(); virtual void setWidth(int width); virtual void setHeight(int height); virtual void setFormat(int format);
    virtual void allocateImage(); virtual void d30(); virtual void d31();
    virtual void d32(); virtual void d33(); virtual void d34(); virtual void setPixels(void *pixels, int format, int quality, int width, int height);
    char pad4[44];
    int imageSize;
    void *pixels;
    char pad56[4];
    unsigned char localImage;
};
class BufferAllocator {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31();
    virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39();
    virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47();
    virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void *allocate(int size, int align);
};
struct TextureEntry { char pad0[8]; int depth; int pad12; int indexed; char pad20[8]; int kind; char pad32[4]; int palette; int layout; char pad44[4]; };
struct TextureTable { char pad0[16]; TextureEntry *entries; };
struct PaletteEntry { int format; char pad4[132]; };
struct PaletteTable { char pad0[16]; PaletteEntry *entries; };
struct VisualContextTextures { char pad0[324]; PaletteTable *palettes; char pad328[540]; TextureTable *textures; };
extern "C" int FUN_00169e40(VisualContextTextures *self, int index, TextureImage *image, void *source, int sourceFormat, int width, int height, int flags);
extern "C" void igPsx2VisualContext_GetViewport(void *arg0, int *arg1, int *arg2, int *arg3, int *arg4);
extern "C" void igPsx2VisualContext_GetViewportWithDepth(igPsx2VisualContext *arg0, int *arg1, int *arg2, int *arg3, int *arg4, float *arg5, float *arg6);
extern "C" void igPsx2VisualContext_SetClearColor(igPsx2VisualContext *self, float *color);
extern "C" int igPsx2VisualContext_GetClearColorPacked(void *arg0);
typedef struct Obj179 { char pad[896]; int f896; } Obj179;
extern "C" void igPsx2VisualContext_GetClearColor(Obj179 *arg0, void *arg1);
typedef struct S181 { char pad[892]; float f892; char pad896[4]; unsigned f900; char pad904[376]; unsigned f1280; } S181;
extern "C" float igPsx2VisualContext_GetClearDepth(void *arg0);
extern "C" int igPsx2VisualContext_GetClearStencil(void *arg0);
#define VRAM_BUFFER_RECORD_SIZE 0x30
extern "C" float igPsx2VisualContext_GetPixelAspectRatio(igPsx2VisualContext *self, int buffer_index);
typedef struct R520 { int x; int y; } R520;
typedef struct L520 { char pad[16]; R520 *rects; } L520;
typedef struct O520 {
    char p0[104]; int f68; char p1[760]; L520 *l364; int idx;
    char p2[40]; int e394; int e398; int e39c; int e3a0;
    char p3[304]; int e4d4; int e4d8; int e4dc; int e4e0;
} O520;
#define MIN(a,b) ((a) < (b) ? (a) : (b))
struct H_1690d0 {
static inline int clampLen(int lim, int diff) {
    if (MIN(lim, diff) > 1) return MIN(lim, diff);
    return 1;
}
static inline int clampLow(int lim, int diff) {
    if (MIN(lim, diff) > 0) return MIN(lim, diff);
    return 0;
}
};
extern "C" void FUN_0016a520(O520 *o);
extern "C" void igPsx2VisualContext_SetScissor(igPsx2VisualContext *arg0, int arg1, int arg2, int arg3, int arg4);
extern "C" void igPsx2VisualContext_GetScissor(void *arg0, int *arg1, int *arg2, int *arg3, int *arg4);
extern "C" void igPsx2VisualContext_SetScissorType(int a0, int a1);
typedef struct S0_1690d0 { char pad4[4]; int f4; int f8; char pad20[8]; int f14; } S0_1690d0;
extern "C" void FUN_0016a800(S0_1690d0 *arg0);
struct Arg { char pad[328]; P_1690d0 *f328; char pad2[12]; int f344; };
extern "C" void FUN_0016a860(Arg *arg0);
struct T9f0 { unsigned short f0; short pad; unsigned short f4; short pad2; int f8; unsigned short *f12; int f16;
    bool Chk(int s0) {
        int a2, a1;
        if (s0 < f0 && s0 >= 0) {
            a1 = f4;
            for (a2 = 0; a2 < a1; a2++) {
                if (s0 == f12[a2]) return false;
            }
            return true;
        }
        return false;
    }
};
extern "C" void FUN_0016a9f0(igPsx2VisualContext *arg0, int arg1);
struct RC_1690d0 { int p0; unsigned refs; };
class VO { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55();  virtual void *v58(void *, int); };
struct E_1690d0 { int p0; RC_1690d0 *f4; int f8; int p12; int f16; int p20; };
struct Tab80 { unsigned short f0; unsigned short f2; unsigned short f4; short pad2; int f8; unsigned short *f12; E_1690d0 *f16;
    bool Chk(int s0) {
        int a2, a1;
        if (s0 < f0 && s0 >= 0) {
            a1 = f4;
            for (a2 = 0; a2 < a1; a2++) {
                if (s0 == f12[a2]) return false;
            }
            return true;
        }
        return false;
    }
};
struct Oab80 { int w[82]; Tab80 *f328; };
extern "C" void FUN_0016ab80(Oab80 *arg0, int arg1);
struct EntAd20 { int f0; int f4; int f8; int f12; int f16; int f20; };
struct PoolAd20 { unsigned short f0; unsigned short f2; unsigned short f4; char p6[6]; unsigned short *f12; EntAd20 *f16; };
struct ObjAd20 { char pad[328]; PoolAd20 *f328; };
extern "C" int FUN_0016ad20(ObjAd20 *arg0, int arg1, int arg2);
extern "C" void FUN_0016aea0(int arg0, int arg1, int *arg2, int *arg3);
struct RAf30 { char pad[4]; int f4; char pad2[12]; int f14; char pad3[4]; unsigned char f1c; };
struct EntAf30 { int f0; RAf30 *f4; int f8; int fc; int f10; int f14; };
struct Tab { char pad[16]; EntAf30 *f10; };
struct A_1690d0 { char pad[328]; Tab *f148; char pad2[1136]; unsigned char f5bc; };
class VC_220 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52();  virtual int vX(int, int); };
extern "C" void FUN_0016af30(A_1690d0 *arg0, int arg1, RAf30 *arg2);
typedef struct Q_1690d0 { char p[20]; int f20; char p2[4]; unsigned char f28; } Q_1690d0;
typedef struct RB090 { int f0; Q_1690d0 *f4; int f8; int f12; int f16; int f20; } RB090;
typedef struct A1_1690d0 { char p[16]; RB090 *f16; } A1_1690d0;
typedef struct Ob { char p[328]; A1_1690d0 *f328; } Ob;
extern "C" bool FUN_0016b090(Ob *arg0, int arg1);
struct E8 { int p0; int p4; int w8; int p12[3]; };
struct TB1d0 { unsigned short f0; short pad; unsigned short f4; short pad2; int f8; unsigned short *f12; E8 *f16;
    bool Chk(int s0) {
        int a2, a1;
        if (s0 < f0 && s0 >= 0) {
            a1 = f4;
            for (a2 = 0; a2 < a1; a2++) {
                if (s0 == f12[a2]) return false;
            }
            return true;
        }
        return false;
    }
};
struct OB1d0 { int w[82]; TB1d0 *f328; int p332[3]; int f344; };
extern "C" void FUN_0016b1d0(OB1d0 *arg0, int arg1);
extern "C" void igPsx2VisualContext_constructFields(igVisualContextFieldsView *self, int flags);
typedef struct { char pad0[80]; int f50; char pad84[238]; unsigned char f142; } S10;
extern "C" void igPsx2VisualContext_userDestruct(S10 *arg0);
struct T35 { int word0; int references; };
struct Obj35 {
    char p[940]; T35 *m940; T35 *m944; T35 *m948;
    inline void rel(T35 *&r) {
        T35 *object = r;
        if (object) {
            --object->references;
            if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
                igObject_Destroy((igObject *)object);
        }
        r = 0;
    }
};
extern "C" void igPsx2VisualContext_Reset(Obj35 *arg0);
extern "C" int igPsx2VisualContext_GetCapability(igPsx2VisualContext *context, unsigned int query);
/* The loop test is `s0 > -1` for the slti/beqz. */
class VO650 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual void d101(); virtual void d102(); virtual void d103(); virtual void d104(); virtual void d105(); virtual void d106(); virtual void d107(); virtual void d108(); virtual void d109(); virtual void d110(); virtual void d111(); virtual void d112(); virtual void d113(); virtual void d114(); virtual void d115(); virtual void d116(); virtual void d117(); virtual void d118(); virtual void d119(); virtual void d120(); virtual void d121(); virtual void d122(); virtual void d123(); virtual void d124(); virtual void d125(); virtual void d126(); virtual void d127(); virtual void d128(); virtual void d129(); virtual void d130(); virtual void d131(); virtual void d132(); virtual void d133(); virtual void d134(); virtual void d135(); virtual void d136(); virtual void d137(); virtual void d138(); virtual void d139(); virtual void d140(); virtual void d141(); virtual void d142(); virtual void d143(); virtual void d144(); virtual void d145(); virtual void d146(); virtual void d147(); virtual void d148(); virtual void d149(); virtual void d150(); virtual void d151(); virtual void d152(); virtual void d153(); virtual void d154(); virtual void d155(); virtual void d156(); virtual void d157(); virtual void d158(); virtual void d159(); virtual void d160(); virtual void d161(); virtual void d162(); virtual void d163(); virtual void d164(); virtual void d165(); virtual void d166(); virtual void d167(); virtual void d168(); virtual void d169(); virtual void d170(); virtual void d171(); virtual void d172(); virtual void d173(); virtual void d174(); virtual void d175(); virtual void d176(); virtual void d177(); virtual void d178(); virtual void d179(); virtual void d180(); virtual void d181(); virtual void d182(); virtual void d183(); virtual void d184(); virtual void d185(); virtual void d186(); virtual void d187(); virtual void d188(); virtual void d189(); virtual void d190(); virtual void v772(int); };
struct T650 { unsigned short f0; short pad; int f4; int f8; int f12; int f16; };
extern "C" void FUN_0016c650(igPsx2VisualContext *arg0, int arg1);
struct Ent192 { int *list; };
struct Nd192 { int a; int b; Nd192() { a = 0; b = 0; } static void *operator new(unsigned sz, int owner) { return FUN_002ed240(sz, owner); } };
struct T192 { unsigned short f0; unsigned short f2; unsigned short f4; short pad; int pad8; unsigned short *f12; Ent192 **f16; };
struct O192 { int w[240]; T192 *f960; char pad[4]; char f968; };
struct Rc193 { int w0; unsigned refs; int count; int cap; int *data; };
struct Ent193 { Rc193 *list; };
struct T193 { unsigned short f0; unsigned short f2; unsigned short f4; short pad; int pad8; unsigned short *f12; Ent193 **f16;
    bool Chk(int s0) {
        int a2, a1;
        if (s0 < f0 && s0 >= 0) {
            a1 = f4;
            for (a2 = 0; a2 < a1; a2++) {
                if (s0 == f12[a2]) return false;
            }
            return true;
        }
        return false;
    }
    void Add(int s0) {
        if (s0 < f0 && s0 >= 0) {
            if (f4 >= f2) {
                VM *o = (VM *)Memory_FindBufferOwner(this);
                f2 = f2 + 8;
                f12 = (unsigned short *)o->v232(f12, f2 * 2);
            }
            f12[f4] = s0;
            f4 = f4 + 1;
        }
    }
};
struct L196 { char p[8]; int n; char q[4]; int *a; };
struct T196 { char p[16]; struct L196 ***tab; };
extern "C" void FUN_0016cc50(int a0, int a1);
typedef struct IntList { int _vtable; int _refCount; int _count; int _capacity; int *_data; } IntList;
extern "C" void FUN_0016cc60(char *arg0);
extern "C" void FUN_0016cd10(void *arg0);
extern "C" void igPsx2VisualContext_DetectDriverDatabaseProperties(int dummy0, int arg1);
extern "C" void FUN_001f7db0(unsigned, int, int);

extern "C" void Gap__Gfx__igPsx2DisableExt__vfunc_29(void *arg0, int arg1);
extern "C" int Gap__Gfx__igPsx2DisableExt__vfunc_30(void *self, unsigned int ext);
extern "C" void Gap__Gfx__igPsx2DisableExt__vfunc_31(int arg0, unsigned int arg1, char arg2);
typedef struct VisualContextView { char pad956[956]; int f3bc; } VisualContextView;

extern "C" long long DAT_005608a0[4];
extern "C" void igPsx2VisualContext_SetColor(VisualContextView *arg0, void *color);
typedef struct S_16d010 { char pad[956]; unsigned int f956; } S_16d010;
extern "C" void igPsx2VisualContext_GetColor(S_16d010 *arg0, float *arg1);
extern "C" unsigned int igPsx2VisualContext_GetColorPacked(void *arg0);
extern "C" void igPsx2VisualContext_GetVertexMask(int *arg0, void *arg1);
extern "C" int DAT_005608c0[4];
class VC_16d190 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual void d101(); virtual void d102(); virtual void d103(); virtual void d104(); virtual void d105(); virtual void d106(); virtual void d107(); virtual void d108(); virtual void d109(); virtual void d110(); virtual void d111(); virtual void d112(); virtual void d113(); virtual void d114(); virtual void d115(); virtual void d116(); virtual void d117(); virtual void d118(); virtual void d119(); virtual void d120(); virtual void d121(); virtual void d122(); virtual void d123(); virtual void d124(); virtual void d125(); virtual void d126(); virtual void d127(); virtual void d128(); virtual void d129(); virtual void d130(); virtual void d131(); virtual void d132(); virtual void d133(); virtual void d134(); virtual void d135(); virtual void d136(); virtual void d137(); virtual void d138(); virtual void d139(); virtual void d140(); virtual void d141(); virtual void d142(); virtual void d143(); virtual void d144(); virtual void d145(); virtual void d146(); virtual void d147(); virtual void d148(); virtual void d149(); virtual void d150(); virtual void d151(); virtual void d152(); virtual void d153(); virtual void d154(); virtual void d155(); virtual void d156(); virtual void d157(); virtual void d158(); virtual void d159(); virtual void d160(); virtual void d161(); virtual void d162(); virtual void d163(); virtual void d164(); virtual void d165(); virtual void d166(); virtual void d167(); virtual void d168(); virtual void d169(); virtual void d170(); virtual void d171(); virtual void d172(); virtual void d173(); virtual void d174(); virtual void d175(); virtual void d176(); virtual void d177(); virtual void d178(); virtual void d179(); virtual void d180(); virtual void d181(); virtual void d182(); virtual void d183(); virtual void d184(); virtual void d185(); virtual void d186(); virtual void d187(); virtual void d188(); virtual void d189(); virtual void d190(); virtual void d191(); virtual void d192(); virtual void d193(); virtual void d194(); virtual void d195(); virtual void d196(); virtual void d197(); virtual void d198(); virtual void d199(); virtual void d200(); virtual void d201(); virtual void d202(); virtual void d203(); virtual void d204(); virtual void d205(); virtual void d206(); virtual void d207(); virtual void d208(); virtual void d209(); virtual void d210(); virtual void d211(); virtual void d212(); virtual void d213(); virtual void d214(); virtual void d215(); virtual void d216(); virtual void d217(); virtual void d218(); virtual void d219(); virtual void d220(); virtual void d221(); virtual void d222(); virtual void d223(); virtual void d224(); virtual void d225(); virtual void d226(); virtual void d227(); virtual void d228(); virtual void d229(); virtual void d230(); virtual void d231(); virtual void d232(); virtual void d233(); virtual void d234(); virtual void d235(); virtual void d236(); virtual void d237(); virtual void d238(); virtual void d239(); virtual void d240(); virtual void d241(); virtual void d242(); virtual void d243(); virtual void d244(); virtual void d245(); virtual void d246(); virtual void d247(); virtual void d248(); virtual void d249(); virtual void d250(); virtual void d251(); virtual void d252(); virtual void d253(); virtual void d254(); virtual void d255(); virtual void d256(); virtual void d257(); virtual void d258(); virtual void vX(int,int); };
extern "C" int igPsx2VisualContext_GetVertexArray(igPsx2VisualContext *self);
extern "C" int DAT_005608c4[4];
extern "C" int igPsx2VisualContext_GetPrimLengthArray(void *arg0);
extern "C" int DAT_005608c8[4];
extern "C" int igPsx2VisualContext_GetIndexArray(void *arg0);
struct Q_16d660 { char pad0[8]; int *f8; char pad1[8]; int f20; char pad2[40]; long long f64; };
extern "C" void FUN_0016d910(igPsx2VisualContext *vc, unsigned int count, int first, const float *positions, const float *normals, int (*draw)(...), int (*drawIndexed)(...));
extern "C" void FUN_0016db20(igPsx2VisualContext *vc, int first);
extern "C" int FUN_0017f080(...);
class VC_16dbe0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual long long vX(); };
struct N { char pad0[8]; int f8; char pad12[4]; unsigned char f16; char pad17[7]; char f24[912]; long long f936; char pad944[8]; N *f952; };
struct A_16dbe0 { char pad[56]; VC_16dbe0 *f56; unsigned char f60; char pad61[7]; float f68; char pad72[1480]; N *f1552; };

extern "C" int igPsx2VisualContext_BeginDraw(A_16dbe0 *arg0);
extern "C" int FUN_00178970(...);

struct N_16dca0;
class B_16dca0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual double v100(); virtual long long v104(); virtual void d25(); virtual void d26(); virtual void v116(); };
class A_16dca0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void v112(float,float); virtual void v116(float); char pad[52]; B_16dca0 *f56; unsigned char b60; char p61[3]; int f64; float f68; char pad2[1480]; N_16dca0 *f1552; };
struct N_16dca0 { char pad0[4]; int f4; int f8; char pad1[4]; unsigned char b16; char pad2[463]; char f480[456]; long long f936; char pad3[8]; N_16dca0 *f952; };
extern "C" void igPsx2VisualContext_EndDraw(A_16dca0 *arg0);

extern "C" void igPsx2VisualContext_FlushDraw(void);
extern "C" void FUN_0016e140(void *arg0, int arg1);
typedef struct Obj_16e180 { char pad[24]; int f24; } Obj_16e180;
extern "C" void Gap__Gfx__igPsx2BlendEquationExt__vfunc_29(Obj_16e180 *arg0, int arg1);

class igBlendContextView {
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
    virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual void d101(); virtual void d102(); virtual void d103();
    virtual void d104(); virtual void d105(); virtual void d106(); virtual void d107(); virtual void d108(); virtual void d109(); virtual void d110(); virtual void d111();
    virtual void d112(); virtual void d113(); virtual void d114(); virtual void d115(); virtual void d116(); virtual void d117(); virtual void d118(); virtual void d119();
    virtual void d120(); virtual void d121(); virtual void d122(); virtual void d123(); virtual void d124(); virtual void d125(); virtual void d126(); virtual void d127();
    virtual void d128(); virtual void d129(); virtual void d130(); virtual void d131(); virtual void d132(); virtual void d133(); virtual void d134(); virtual void d135();
    virtual void d136(); virtual void d137(); virtual void d138(); virtual void d139(); virtual void d140(); virtual void d141(); virtual void d142(); virtual void d143();
    virtual void d144(); virtual void d145(); virtual void d146(); virtual void d147(); virtual void d148(); virtual void d149(); virtual void d150(); virtual void d151();
    virtual void d152(); virtual int getBlendSource(); virtual void d154(); virtual int getBlendDestination();
};
extern "C" void Gap__Gfx__igPsx2BlendEquationExt__vfunc_30(igPsx2BlendEquationExt *ext);
extern "C" void FUN_0016e290(igPsx2BlendEquationExt *arg0, int arg1, int arg2, int arg3, int arg4, char arg5);
extern "C" void Gap__Gfx__igPsx2DecalExt__vfunc_29(igPsx2DecalExt *self, int context);

extern "C" void Gap__Gfx__igPsx2DecalExt__vfunc_30(int arg0, int arg1);
class DW4VC_136_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual int vX(); };
extern "C" void igPsx2Image_UserApplyWriteProxy(void *arg0);
class C_16e320 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void vX(); int pad[5]; int st; };
extern "C" void igPsx2Image_UserMakeConcrete(void *arg0);

extern "C" void igPsx2Image_InitDefaults(igObject *self);
extern "C" void thunk_FUN_001592c0__0016e390(LongListStorageView *self);
extern "C" void Gap__Gfx__igPsx2Image__vfunc_23(igImage *self, void **source, int deep);
class ImageCalls {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();
    virtual void copyFrom(igPsx2Image *source, int deep);
    virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27();
    virtual void setFormat(int format);
};
extern "C" unsigned char Gap__Gfx__igPsx2Image__vfunc_42(igPsx2Image *self, int format, igPsx2Image *source);
class G {
public:
 virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual int v21(void*,int);

};
class O0 : public igObject {
public:
 };
class O1 : public igVirtualObject {
public:
 virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual int v21(void*,void*);
  
};
class O2 : public igVirtualObject {
public:
 virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual int v31(int);
  
};
struct LoaderRef {
    O1 *p;
    LoaderRef(O1 *object) : p(object) {}
    ~LoaderRef() {
        O1 *o;
        if ((o = p) != 0) {
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7FFFFF) == 0) igObject_Destroy(o);
        }
    }
};
struct ReaderRef {
    O2 *p;
    ReaderRef(O2 *object) : p(object) {}
    ~ReaderRef() {
        O2 *o;
        if ((o = p) != 0) {
            o->_refCount = o->_refCount - 1;
            if ((o->_refCount & 0x7FFFFF) == 0) igObject_Destroy(o);
        }
    }
};
struct PathText;
struct PathText {
    int text;
    PathText(int path) {
        int a;
        if (path == 0) {
            a = 0;
        } else {
            if (g_stringPool == 0) {
                StringPool *t = (StringPool *)StringPool_Allocate(0x10);
                if (t != 0) t = StringPool_Construct(t);
                g_stringPool = t;
            }
            a = (int)StringPool_Intern(g_stringPool, (const char *)path);
        }
        text = a;
    }
    ~PathText() {
        if (text != 0) {
            int *h = (int *)text - 2;
            int t = ((int *)text)[-1] - 1;
            ((int *)text)[-1] = t;
            if (t == 0) StringChunk_ReleaseHeader((StringChunk *)*h, (StringTokenHeader *)h);
        }
    }
};
extern "C" int Gap__Gfx__igPsx2Image__vfunc_39(G *arg0, int arg1);
class Strm {
public:
    virtual void d0();virtual void d1();virtual void d2();virtual void d3();virtual void d4();virtual void d5();virtual void d6();virtual void d7();
    virtual void d8();virtual void d9();virtual void d10();virtual void d11();virtual void d12();virtual void d13();virtual void d14();virtual void d15();
    virtual void d16();virtual void d17();virtual void d18();virtual void d19();virtual void d20();virtual void d21();virtual void d22();virtual void d23();
    virtual void d24();
    virtual void Read(void *, int, int);
};
struct Img_16e8f0 {
    char p0[8];
    int f8, f12, f16, f20, f24, f28, f32, f36, f40, f44, f48, f52;
    int pad56;
    unsigned char f60;
    char p61[3];
    int f64;
    char p68[4];
    int f72;
    char p76[8];
    int f84;
};
extern "C" int Gap__Gfx__igPsx2Image__vfunc_40(Img_16e8f0 *p, Strm *s);
struct ConvertedImage : public igVirtualObject { virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void convert(void *, int); char pad[44]; void *pixels; };
struct Stream : public igVirtualObject {
    virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void close(); virtual void d25(); virtual void d26(); virtual int write(void *, int, int);
    
    void release() {
        _refCount = _refCount - 1;
        if ((_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(this);
        }
    }
};
extern "C" int Gap__Gfx__igPsx2Image__vfunc_41(igPsx2Image *image, Stream *stream);
class Strm_16ece0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void v24(); virtual int v25(void *, int, int); };
struct Img_16ece0 { char pad[8]; int f8; int f12; int f16; int f20; int f24; int f28; int f32; int f36; int f40; int f44; int f48; int f52; char pad2[4]; char f60; char pad3[3]; int f64; char pad4[4]; int f72; int f76; char pad5[4]; int f84; };
extern "C" int Gap__Gfx__igPsx2Image__vfunc_44(Img_16ece0 *arg0, Strm_16ece0 *arg1);
struct ImageBuffer { char p[48]; int size; int data; };
class DW4VC_112_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual int vX(int); };
class DW4VC_116_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual int vX(int); };
class DW4VC_120_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual int vX(int); };
class DW4VC_124_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual int vX(); };
class DW4VC_128_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual int vX(int); };
extern "C" void Gap__Gfx__igPsx2Image__vfunc_37(ImageBuffer *arg0, int arg1, int arg2, int arg3, int arg4, int arg5);
extern "C" void Gap__Gfx__igPsx2ImageConvert__vfunc_25(void);
extern "C" void Gap__Gfx__igPsx2ImageConvert__vfunc_26(void);
extern "C" void Gap__Gfx__igPsx2ImageConvert__vfunc_27(void *arg0, unsigned char *arg1, int arg2, int *arg3);
extern "C" void Gap__Gfx__igPsx2ImageConvert__vfunc_28(void *self, unsigned char *p, int n, int *mode);
extern "C" void Gap__Gfx__igPsx2ImageConvert__vfunc_29(void *arg0, unsigned char *p, int n);
extern "C" void Gap__Gfx__igPsx2ImageConvert__vfunc_30(void);
extern "C" void Gap__Gfx__igPsx2ImageConvert__vfunc_31(void);
extern "C" void Gap__Gfx__igPsx2ImageConvert__vfunc_32(void);
extern "C" void Gap__Gfx__igPsx2ImageConvert__vfunc_33(void *arg0, unsigned char *arg1, int arg2);
extern "C" void Gap__Gfx__igPsx2ImageConvert__vfunc_34(void);
struct S_16f250 { char pad[24]; int f24; };
extern "C" bool Gap__Gfx__igPsx2Image__vfunc_45(S_16f250 *p);
typedef void (*ConvertFunc)(void);
typedef struct ImagePalette {
    char pad0[12];
    int lastIndex;
    char pad10[4];
    unsigned int *colors;
    char pad18[4];
    unsigned char used;
} ImagePalette;
extern "C" void FUN_0016f7f0(...);
extern "C" ConvertFunc Gap__Gfx__igPsx2ImageConvert__vfunc_24(void *self, int srcFormat, int from, int to);
extern "C" ConvertFunc Gap__Gfx__igPsx2ImageConvert__vfunc_23(void *self, int srcFormat, int dstFormat, int flag);
extern "C" void FUN_0016f690(unsigned int *dst, unsigned char *src, int count, ImagePalette *palette);
extern "C" void FUN_0016f700(unsigned int *dst, unsigned short *src, int count);
extern "C" void FUN_0016f780(unsigned char *dst, unsigned short *src, int count);
extern "C" void FUN_0016f8a0(unsigned int *dst, unsigned char *src, int count, unsigned char *alphaSrc);
extern "C" void FUN_0016f930(unsigned short *dst, unsigned char *src, int count, unsigned char *alphaSrc);
extern "C" void FUN_0016f9b0(unsigned short *dst, unsigned char *src, int count);
extern "C" void FUN_0016fa10(unsigned char *dst, unsigned int *src, int count);
extern "C" void FUN_0016fa60(unsigned short *dst, unsigned int *src, int count);
extern "C" void FUN_0016fae0(unsigned short *dst, unsigned int *src, int count);
extern "C" void FUN_0016fb60(unsigned short *dst, unsigned char *src, int count);
extern "C" void FUN_0016fbd0(unsigned char *dst, unsigned short *src, int count);
extern "C" void FUN_0016fc20(unsigned int *dst, unsigned short *src, int count);
extern "C" void FUN_0016fc80(unsigned char *dst, unsigned short *src, int count);
extern "C" void FUN_0016fcd0(unsigned char *dst, unsigned short *src, int count);
extern "C" void *thunk_memcpy(void *d, const void *s, unsigned int n);
extern "C" void FUN_0016fd50(unsigned char *dst, unsigned char *src, int count);
extern "C" void FUN_0016fdb0(unsigned char *dst, unsigned char *src, int count);
extern "C" void FUN_0016fe00(void *dst, const void *src, unsigned int size);
extern "C" void FUN_0016fe20(void *dst, const void *src, unsigned int size);
extern "C" void Gap__Gfx__igPsx2MultiTextureExt__vfunc_29(igPsx2MultiTextureExt *self, int context);
class igVisualContextView {
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
    virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual void d101(); virtual void d102(); virtual void d103();
    virtual void d104(); virtual void d105(); virtual void d106(); virtual void d107(); virtual void d108(); virtual void d109(); virtual void d110(); virtual void d111();
    virtual void d112(); virtual void d113(); virtual void d114(); virtual void d115(); virtual void d116(); virtual void d117(); virtual void d118(); virtual void d119();
    virtual void d120(); virtual void d121(); virtual void d122(); virtual void d123(); virtual void d124(); virtual void d125(); virtual void d126(); virtual void d127();
    virtual void d128(); virtual void d129(); virtual void d130(); virtual void d131(); virtual void d132(); virtual void d133(); virtual void d134(); virtual void d135();
    virtual void d136(); virtual void d137(); virtual void d138(); virtual void d139(); virtual void d140(); virtual void d141(); virtual void d142(); virtual void d143();
    virtual void d144(); virtual void d145();
    virtual void vfunc_146(int unit, int format);
};
class igPsx2MultiTextureExtView {
public:
    int _vtable;
    unsigned int _refCount;
    char _pad8[12];
    igVisualContextView *_context;
};
extern "C" int DAT_004df5e0[];
extern "C" void Gap__Gfx__igPsx2MultiTextureExt__vfunc_30(igPsx2MultiTextureExtView *self, int unit, int, int mode);
extern "C" void Gap__Gfx__igPsx2MultiTextureExt__vfunc_31(int a0, int a1, int a2, int a3);
extern "C" void Gap__Gfx__igPsx2MultiTextureExt__vfunc_32(void);
typedef struct A_16fea0 { char p[24]; unsigned int f24; unsigned char f28; char p1[3]; int f32; int f36; int f40; int f44; unsigned char f48; } A_16fea0;
typedef struct It { char p[448]; } It;
extern "C" void FUN_0016fea0(A_16fea0 *arg0, int arg1, int arg2, int arg3);
extern "C" void Gap__Gfx__igPsx2ScissorExt__vfunc_29(igPsx2ScissorExt *self, int context);
class A_1700f0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void vX(int, int, int, int); };
class B_1700f0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual void d101(); virtual void d102(); virtual void d103(); virtual void d104(); virtual void d105(); virtual void d106(); virtual void d107(); virtual void d108(); virtual void d109(); virtual void d110(); virtual void d111(); virtual void d112(); virtual void d113(); virtual void d114(); virtual void d115(); virtual void d116(); virtual void d117(); virtual void d118(); virtual void d119(); virtual void d120(); virtual void d121(); virtual void d122(); virtual void d123(); virtual void d124(); virtual void d125(); virtual void d126(); virtual void d127(); virtual void d128(); virtual void d129(); virtual void d130(); virtual void d131(); virtual void d132(); virtual void d133(); virtual void d134(); virtual void d135(); virtual void d136(); virtual void d137(); virtual void d138(); virtual void d139(); virtual void d140(); virtual void d141(); virtual void d142(); virtual void d143(); virtual void d144(); virtual void d145(); virtual void d146(); virtual void d147(); virtual void d148(); virtual void d149(); virtual void d150(); virtual void d151(); virtual void d152(); virtual void d153(); virtual void d154(); virtual void d155(); virtual void d156(); virtual void d157(); virtual void d158(); virtual void d159(); virtual void d160(); virtual void d161(); virtual void d162(); virtual void d163(); virtual void d164(); virtual void d165(); virtual void d166(); virtual void d167(); virtual void d168(); virtual void d169(); virtual void d170(); virtual void d171(); virtual void d172(); virtual void d173(); virtual void d174(); virtual void d175(); virtual void d176(); virtual void d177(); virtual void d178(); virtual void d179(); virtual void d180(); virtual void d181(); virtual void d182(); virtual void d183(); virtual void vX(int *, int *, int *, int *); };
extern "C" void Gap__Gfx__igPsx2ScissorExt__vfunc_30(int *arg0, int arg1);
extern "C" unsigned char Gap__Gfx__igPsx2ScissorExt__vfunc_31(igPsx2ScissorExt *self);
extern "C" void Gap__Gfx__igPsx2ScissorExt__vfunc_32(igPsx2ScissorExt *arg0, int arg1, int arg2, int arg3, int arg4);
extern "C" void Gap__Gfx__igPsx2ScissorExt__vfunc_33(igPsx2ScissorExt *self, int *originX, int *originY, int *width, int *height);
extern "C" void FUN_00170210(void *arg0);
extern "C" void*DAT_00560858[4];
extern igMatrix44f g_gfxIdentityMatrix;
class LightCapsDispatch {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6();
    virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13();
    virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();
    virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27();
    virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34();
    virtual int getCapability(int capability);   /* slot 35 */
};
class PoolAllocDispatch {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6();
    virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13();
    virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();
    virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27();
    virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34();
    virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41();
    virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48();
    virtual void d49(); virtual void d50(); virtual void d51();
    virtual void *allocate(unsigned int size);   /* slot 52 */
};
extern "C" void FUN_001702c0(igPsx2VisualContext *vc);
#define STR_RELEASE(s) if (s) { int *h_ = (int *)((char *)(s) - 8); if (--h_[1] == 0) StringChunk_ReleaseHeader((StringChunk *)h_[0], (StringTokenHeader *)h_); }
#define POOL() if (!g_stringPool) { StringPool *p_ = (StringPool *)StringPool_Allocate(16); if (p_) p_ = StringPool_Construct(p_); g_stringPool = p_; }
struct T_170510 {
    unsigned short count; unsigned short pad0; unsigned short n; unsigned short pad1; char *str; unsigned short *arr; void *buf;
    bool Wanted(int idx) {
        int j;
        if (idx < count && idx >= 0) {
            for (j = 0; j < n; j++) {
                if (idx == arr[j]) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }

};
struct Obj_170510 {
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
    virtual void d48();
    virtual void d49();
    virtual void d50();
    virtual void d51();
    virtual void d52();
    virtual void d53();
    virtual void d54();
    virtual void d55();
    virtual void d56();
    virtual void d57();
    virtual void d58();
    virtual void d59();
    virtual void d60();
    virtual void d61();
    virtual void d62();
    virtual void d63();
    virtual void d64();
    virtual void d65();
    virtual void d66();
    virtual void d67();
    virtual void d68();
    virtual void d69();
    virtual void d70();
    virtual void d71();
    virtual void d72();
    virtual void d73();
    virtual void d74();
    virtual void d75();
    virtual void f76(int);
    char pad[1332]; struct T_170510 *t; int pad2; void *f1344;
};
extern "C" void FUN_00170510(Obj_170510 *o, int arg1);
typedef struct S0_1706d0 { char pad1340[1340]; unsigned char f1340; } S0_1706d0;

extern "C" long long DAT_00560848[4];
extern "C" unsigned char igPsx2VisualContext_GetLightingState(void *arg0);
class O_170750 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55();  virtual int vX(int, int); };
struct Pool { unsigned short f0; unsigned short f2; unsigned short f4; short pad6; int pad8; unsigned short *f12; char *f16; };
struct It_170750 { char pad[124]; int f124; char pad2[24]; int f152; };
struct E_1708e0 { char p[148]; unsigned char f148; char p2[11]; };
struct Lst { unsigned short f0; unsigned short f2; unsigned short f4; char p6[6]; short *f12; E_1708e0 *f16; };
class Buf { public: virtual void b0(); virtual void b1(); virtual void b2(); virtual void b3(); virtual void b4(); virtual void b5(); virtual void b6(); virtual void b7(); virtual void b8(); virtual void b9(); virtual void b10(); virtual void b11(); virtual void b12(); virtual void b13(); virtual void b14(); virtual void b15(); virtual void b16(); virtual void b17(); virtual void b18(); virtual void b19(); virtual void b20(); virtual void b21(); virtual void b22(); virtual void b23(); virtual void b24(); virtual void b25(); virtual void b26(); virtual void b27(); virtual void b28(); virtual void b29(); virtual void b30(); virtual void b31(); virtual void b32(); virtual void b33(); virtual void b34(); virtual void b35(); virtual void b36(); virtual void b37(); virtual void b38(); virtual void b39(); virtual void b40(); virtual void b41(); virtual void b42(); virtual void b43(); virtual void b44(); virtual void b45(); virtual void b46(); virtual void b47(); virtual void b48(); virtual void b49(); virtual void b50(); virtual void b51(); virtual void b52(); virtual void b53(); virtual void b54(); virtual void b55(); virtual int vB(short *p, int n); };
class Obj_1708e0 { public: virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4(); virtual void a5(); virtual void a6(); virtual void a7(); virtual void a8(); virtual void a9(); virtual void a10(); virtual void a11(); virtual void a12(); virtual void a13(); virtual void a14(); virtual void a15(); virtual void a16(); virtual void a17(); virtual void a18(); virtual void a19(); virtual void a20(); virtual void a21(); virtual void a22(); virtual void a23(); virtual void a24(); virtual void a25(); virtual void a26(); virtual void a27(); virtual void a28(); virtual void a29(); virtual void a30(); virtual void a31(); virtual void a32(); virtual void a33(); virtual void a34(); virtual void a35(); virtual void a36(); virtual void a37(); virtual void a38(); virtual void a39(); virtual void a40(); virtual void a41(); virtual void a42(); virtual void a43(); virtual void a44(); virtual void a45(); virtual void a46(); virtual void a47(); virtual void a48(); virtual void a49(); virtual void a50(); virtual void a51(); virtual void a52(); virtual void a53(); virtual void a54(); virtual void a55(); virtual void a56(); virtual void a57(); virtual void a58(); virtual void a59(); virtual void a60(); virtual void a61(); virtual void a62(); virtual void a63(); virtual void a64(); virtual void a65(); virtual void a66(); virtual void a67(); virtual void a68(); virtual void a69(); virtual void a70(); virtual void a71(); virtual void a72(); virtual void a73(); virtual void a74(); virtual void a75(); virtual void a76(); virtual void vA(int a, int b); char pad[1332]; Lst *f1336; };
extern "C" void igPsx2VisualContext_DeleteLight(Obj_1708e0 *arg0, int arg1);
typedef struct Ent { char p[144]; int f144; unsigned char f148; char q[11]; } Ent;
typedef struct Mgr { char p[16]; Ent *ents; } Mgr;
typedef struct Obj_1709d0 { char p[1336]; Mgr *f1336; } Obj_1709d0;

extern "C" int DAT_00560850[4];
extern "C" int DAT_005608cc[4];
extern "C" unsigned char igPsx2VisualContext_GetLightState(void *arg0, int arg1);
extern "C" int igPsx2VisualContext_GetLightType(void *arg0, int arg1);
extern "C" int DAT_005608d0[4];
extern "C" int DAT_005608d4[4];
typedef struct { float x; float y; float z; float w; } V4_170c30;
typedef struct { char pad[48]; V4_170c30 v; char pad2[44]; int flags; } E_170c30;
typedef struct { char pad[16]; char *f10; } Tab_170c30;
extern "C" int DAT_005609c8[4];
typedef struct E_170d80 { char p0[16]; float v0, v1, v2, v3; char p1[76]; int f108; char p2[48]; } E_170d80;
typedef struct T_170d80 { char p0[16]; E_170d80 *f16; } T_170d80;
typedef struct O_170d80 { char p0[1336]; T_170d80 *f1336; } O_170d80;
extern "C" int DAT_005608dc[4];
struct L_171100 { char pad[16]; char *base; };
class C_171100 { public:
virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual void d101(); virtual void d102(); virtual void d103(); virtual void d104(); virtual void d105(); virtual void d106(); virtual void d107(); virtual void d108(); virtual void d109(); virtual void d110(); virtual void d111(); virtual void d112(); virtual void d113(); virtual void d114(); virtual void d115(); virtual void d116(); virtual void d117(); virtual void d118(); virtual void d119(); virtual void d120(); virtual void d121(); virtual void d122(); virtual void d123(); virtual void d124(); virtual void d125(); virtual void d126(); virtual void d127(); virtual void d128(); virtual void d129(); virtual void d130(); virtual void d131(); virtual void d132(); virtual void d133(); virtual void d134(); virtual void d135(); virtual void d136(); virtual void d137(); virtual void d138(); virtual void d139(); virtual void d140(); virtual void d141(); virtual void d142(); virtual void d143(); virtual void d144(); virtual void d145(); virtual void d146(); virtual void d147(); virtual void d148(); virtual void d149(); virtual void d150(); virtual void d151(); virtual void d152(); virtual void d153(); virtual void d154(); virtual void d155(); virtual void d156(); virtual void d157(); virtual void d158(); virtual void d159(); virtual void d160(); virtual void d161(); virtual void d162(); virtual void d163(); virtual void d164(); virtual void d165(); virtual void d166(); virtual void d167(); virtual void d168(); virtual void d169(); virtual void d170(); virtual void d171(); virtual void d172(); virtual void d173(); virtual void d174(); virtual void d175(); virtual void d176(); virtual void d177(); virtual void d178(); virtual void d179(); virtual void d180(); virtual void d181(); virtual void d182(); virtual void d183(); virtual void d184(); virtual void d185(); virtual void d186(); virtual void d187(); virtual void d188(); virtual void d189(); virtual void d190(); virtual void d191(); virtual void d192(); virtual void d193(); virtual void d194(); virtual void d195(); virtual void d196(); virtual void d197(); virtual void d198(); virtual void d199(); virtual void d200(); virtual void d201(); virtual void d202(); virtual void d203(); virtual void d204(); virtual void d205(); virtual int vX(int, float *);
};
struct Ent_171100 { float x, y, z; char pad[140]; int f152; char pad2[4]; };
struct Ctx { C_171100 c; };
extern "C" int DAT_005608e4[4];
struct Item { char pad[92]; float f92; char pad2[12]; unsigned int f108; char pad3[40]; int f152; char pad4[4]; };
struct List_171220 { char pad[16]; struct Item *data; };
struct Ctx_171220 { char pad[1336]; struct List_171220 *list; };
typedef struct E_1712e0 { char pad76[76]; float f76; char pad80[80]; } E_1712e0;
typedef struct L_1712e0 { char pad16[16]; E_1712e0 *f16; } L_1712e0;
typedef struct S_1712e0 { char pad1336[1336]; L_1712e0 *f1336; } S_1712e0;
extern "C" int DAT_005608e8[4];
extern "C" void igPsx2VisualContext_GetLightDiffuse(igPsx2VisualContext *arg0, int arg1, void *arg2);
extern "C" void igPsx2VisualContext_GetLightAmbient(igPsx2VisualContext *arg0, int arg1, void *arg2);
extern "C" void igPsx2VisualContext_GetLightSpecular(igPsx2VisualContext *arg0, int arg1, float *arg2);
extern "C" void igPsx2VisualContext_GetLightPosition(igPsx2VisualContext *arg0, int arg1, float *arg2);
extern "C" void igPsx2VisualContext_GetLightDirection(igPsx2VisualContext *arg0, int arg1, float *arg2);
extern "C" float igPsx2VisualContext_GetLightFalloffRate(void);
extern "C" void igPsx2VisualContext_GetLightAttenuation(igPsx2VisualContext *arg0, int arg1, void *arg2);
extern "C" float igPsx2VisualContext_GetLightCutoffAngle(void *arg0, int arg1);

extern "C" void FUN_00171690(void *arg0, void *arg1);

extern "C" float DAT_004e1174[4];
extern "C" float DAT_004e1178[4];
extern "C" float DAT_004e117c[4];
extern "C" void FUN_001716c0(void *arg0);
typedef struct VisualColorBlock { char pad16[16]; float v[4]; } VisualColorBlock;
typedef struct VisualContextColorView { char pad1344[1344]; VisualColorBlock *f1344; } VisualContextColorView;
extern "C" int DAT_005608f8[4];
extern "C" void igPsx2VisualContext_SetMaterialDiffuse(VisualContextColorView *arg0, float *arg1);
extern "C" void igPsx2VisualContext_GetMaterialDiffuse(igPsx2VisualContext *arg0, void *arg1);
typedef struct V4_1718a0 { float x, y, z, w; } V4_1718a0;
typedef struct Sub { V4_1718a0 v; char pad[52]; unsigned flags; } Sub;
typedef struct Obj_1718a0 { char pad[1344]; struct Sub *s; } Obj_1718a0;
extern "C" int DAT_005608fc[4];
extern "C" void igPsx2VisualContext_SetMaterialAmbient(Obj_1718a0 *o, V4_1718a0 *n);
extern "C" void igPsx2VisualContext_GetMaterialAmbient(igPsx2VisualContext *arg0, void *arg1);
extern "C" int DAT_00560900[4];
struct T_171a10 { char pad[48]; float v[4]; };
struct S_171a10 { char pad[1344]; struct T_171a10 *f1344; };
extern "C" void igPsx2VisualContext_SetMaterialEmissive(struct S_171a10 *arg0, float *arg1);
extern "C" void igPsx2VisualContext_GetMaterialEmissive(igPsx2VisualContext *arg0, void *arg1);
extern "C" int DAT_00560904[4];
struct VisualContextVec4 { float x, y, z, w; };
struct VisualContextState { char pad[32]; struct VisualContextVec4 v; char pad2[20]; unsigned flags; };
struct Psx2VisualContextView { char pad[1344]; struct VisualContextState *o; };
extern "C" void igPsx2VisualContext_SetMaterialSpecular(struct Psx2VisualContextView *arg0, struct VisualContextVec4 *arg1);
extern "C" void igPsx2VisualContext_GetMaterialSpecular(igPsx2VisualContext *arg0, void *arg1);
typedef struct T_171c80 { char pad64[64]; float f64; } T_171c80;
typedef struct S0_171c80 { char pad1344[1344]; T_171c80 *f1344; } S0_171c80;
extern "C" int DAT_00560908[4];
extern "C" void igPsx2VisualContext_SetMaterialShininess(S0_171c80 *arg0, float fparg0);
extern "C" float igPsx2VisualContext_GetMaterialShininess(void *arg0);
typedef struct V4_171cd0 { float x, y, z, w; } V4_171cd0;
typedef struct St { V4_171cd0 a; V4_171cd0 b; V4_171cd0 c; V4_171cd0 d; float e; unsigned f; } St;
typedef struct O_171cd0 { char pad[1344]; St *s; } O_171cd0;
#define EQ4(S, FLD, Q, CTR) do { V4_171cd0 *a5; St *v1 = (S); int v0; \
    a5 = &v1->FLD; v0 = 1; if (v1->FLD.x != (Q)->x) v0 = 0; \
    if (v0 != 0) { v0 = 1; if (a5->y != (Q)->y) v0 = 0; } \
    if (v0 != 0) { v0 = 1; if (a5->z != (Q)->z) v0 = 0; } \
    if (v0 != 0) { v0 = 1; if (a5->w != (Q)->w) v0 = 0; } \
    if (v0 != 0) CTR[0] += 1; } while (0)
extern "C" int DAT_0056090c[4];
struct P_1720d0 { char pad[80]; int f; };
struct O_1720d0 { char pad[1344]; struct P_1720d0 *p; };
extern "C" void FUN_001720d0(struct O_1720d0 *arg0, int arg1);
extern "C" int DAT_00560910;
extern "C" void igPsx2VisualContext_SetMaterialSpecularState(igPsx2VisualContext *self, int enable);
typedef struct MaterialState { char _pad0[84]; int blendMode; } MaterialState;

extern "C" int DAT_00560914[4];
extern "C" void igPsx2VisualContext_SetMaterialColorMode(igPsx2VisualContext *self, unsigned int mode);
extern "C" int igPsx2VisualContext_GetMaterialColorMode(void *arg0);

extern "C" int DAT_00560918[4];
struct O_172230 { char p[88]; float v[4]; };
struct H_172230 { char p[1344]; struct O_172230 *o; };
extern "C" void igPsx2VisualContext_SetSceneAmbient(struct H_172230 *arg0, float *arg1);
extern "C" void igPsx2VisualContext_GetSceneAmbient(igPsx2VisualContext *arg0, void *arg1);

extern "C" void FUN_00172330(void *arg0, void *arg1);
typedef struct Stk { int a; int b; int count; int c; char *data; } Stk;
typedef struct Obj_172370 { char pad[972]; Stk *s[12]; } Obj_172370;

extern "C" void igPsx2VisualContext_SetStackSize(Obj_172370 *o, int k, int n);
struct N_172550 { char pad0[12]; int f12; };
struct S_172550 { char pad0[972]; struct N_172550 *f972; struct N_172550 *f976; struct N_172550 *f980; char pad984[4]; struct N_172550 *f988; struct N_172550 *f992; struct N_172550 *f996; struct N_172550 *f1000; };
extern "C" int igPsx2VisualContext_GetStackSize(struct S_172550 *arg0, int arg1);
typedef struct L_172600 { int p0; int p4; int count; int cap; char *data; } L_172600;
typedef struct S_172600 { char p[972]; L_172600 *l972; L_172600 *l976; L_172600 *l980; int p984; L_172600 *l988; L_172600 *l992; L_172600 *l996; L_172600 *l1000; } S_172600;
#define PUSH(f) do { int n; L_172600 *l; int v; l = arg0->f; v = count_of_172600(l); if (v != 0) { n = l->count; if (n < l->cap) { l->count = v + 1; } else { List_Resize(l, n + 1, 64); } igMatrix44f_Copy((float *)(l->data + (n << 6)), (const float *)(l->data + ((n - 1) << 6))); } } while (0)
extern "C" void igPsx2VisualContext_PushMatrix(S_172600 *arg0, int arg1);
typedef struct Mat_172910 { float m[16]; } Mat_172910;
typedef struct Obj_172910 { char pad[972]; Stk *s[8]; } Obj_172910;
extern "C" void FUN_001fbce0(...);
extern "C" void igPsx2VisualContext_PopMatrix(Obj_172910 *o, int k);
typedef struct St_172b00 { char pad0[8]; int n; int cap; char *data; } St_172b00;
#define SET(l, m) { \
    St_172b00 *s = (l); \
    int n = s->n; \
    int n1; \
    if (n == 0) { \
        n1 = n + 1; \
        if (n < s->cap) s->n = n_of(s) + 1; \
        else List_Resize(s, n1, 0x40); \
        igMatrix44f_Copy((float *)(s->data + (n << 6)), (const float *)(m)); \
    } else { \
        igMatrix44f_Copy((float *)(s->data + ((n_of(s) - 1) << 6)), (const float *)(m)); \
    } }
#define SETB(l, m) { \
    int n; \
    St_172b00 *s = (l); \
    int n1; \
    n = s->n; \
    if (n == 0) { \
        n1 = n + 1; \
        if (n < s->cap) s->n = n_of(s) + 1; \
        else List_Resize(s, n1, 0x40); \
        igMatrix44f_Copy((float *)(s->data + (n << 6)), (const float *)(m)); \
    } else { \
        igMatrix44f_Copy((float *)(s->data + ((n_of(s) - 1) << 6)), (const float *)(m)); \
    } }
extern "C" void igPsx2VisualContext_PushPreMultiply(igPsx2VisualContext *self, int arg1, char *arg2);
extern "C" void igPsx2VisualContext_PushPostMultiply(igPsx2VisualContext *self, int arg1, char *arg2);
struct Slot { int p0; int p1; int cnt; int p3; char *data; };
struct Obj_173900 {
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
    virtual void d48();
    virtual void d49();
    virtual void d50();
    virtual void d51();
    virtual void d52();
    virtual void d53();
    virtual void d54();
    virtual void d55();
    virtual void d56();
    virtual void d57();
    virtual void d58();
    virtual void d59();
    virtual void d60();
    virtual void d61();
    virtual void d62();
    virtual void d63();
    virtual void d64();
    virtual void d65();
    virtual void d66();
    virtual void d67();
    virtual void d68();
    virtual void d69();
    virtual void d70();
    virtual void d71();
    virtual void d72();
    virtual void d73();
    virtual void d74();
    virtual void d75();
    virtual void d76();
    virtual void d77();
    virtual void d78();
    virtual void d79();
    virtual void d80();
    virtual void d81();
    virtual void d82();
    virtual void d83();
    virtual void d84();
    virtual void d85();
    virtual void d86();
    virtual void d87();
    virtual void d88();
    virtual void d89();
    virtual void d90();
    virtual void d91();
    virtual void d92();
    virtual void d93();
    virtual void d94();
    virtual void d95();
    virtual void d96();
    virtual void d97();
    virtual void d98();
    virtual void d99();
    virtual void d100();
    virtual void d101();
    virtual void d102();
    virtual void d103();
    virtual void d104();
    virtual void d105();
    virtual void d106();
    virtual void d107();
    virtual void d108();
    virtual void d109();
    virtual void d110();
    virtual void d111();
    virtual void d112();
    virtual void d113();
    virtual void d114();
    virtual void d115();
    virtual void d116();
    virtual void d117();
    virtual void d118();
    virtual void d119();
    virtual void d120();
    virtual void d121();
    virtual void d122();
    virtual void d123();
    virtual void d124();
    virtual void d125();
    virtual void d126();
    virtual void d127();
    virtual void d128();
    virtual void d129();
    virtual void d130();
    virtual void d131();
    virtual void d132();
    virtual void d133();
    virtual void d134();
    virtual void d135();
    virtual void d136();
    virtual void d137();
    virtual void d138();
    virtual void d139();
    virtual void d140();
    virtual void d141();
    virtual void d142();
    virtual void d143();
    virtual void d144();
    virtual void d145();
    virtual void d146();
    virtual void d147();
    virtual void d148();
    virtual void d149();
    virtual void d150();
    virtual void d151();
    virtual void d152();
    virtual void d153();
    virtual void d154();
    virtual void d155();
    virtual void d156();
    virtual void d157();
    virtual void d158();
    virtual void d159();
    virtual void d160();
    virtual void d161();
    virtual void d162();
    virtual void d163();
    virtual void d164();
    virtual void d165();
    virtual void d166();
    virtual void d167();
    virtual void d168();
    virtual void d169();
    virtual void d170();
    virtual void d171();
    virtual void d172();
    virtual void d173();
    virtual void d174();
    virtual void d175();
    virtual void d176();
    virtual void d177();
    virtual void d178();
    virtual void d179();
    virtual void d180();
    virtual void d181();
    virtual void d182();
    virtual void d183();
    virtual void d184();
    virtual void d185();
    virtual void d186();
    virtual void d187();
    virtual void d188();
    virtual void d189();
    virtual void d190();
    virtual void d191();
    virtual void d192();
    virtual void d193();
    virtual void d194();
    virtual void d195();
    virtual void d196();
    virtual void d197();
    virtual void d198();
    virtual void d199();
    virtual void d200();
    virtual void vf(int, char *);
    char pad[968];
    Slot *s[8];
};
extern "C" void igPsx2VisualContext_PreMultiply(Obj_173900 *self, int kind, int arg);
struct L_173b30 { char p0[8]; int cnt; int cap; char *data; };
class S_173b30 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual void d101(); virtual void d102(); virtual void d103(); virtual void d104(); virtual void d105(); virtual void d106(); virtual void d107(); virtual void d108(); virtual void d109(); virtual void d110(); virtual void d111(); virtual void d112(); virtual void d113(); virtual void d114(); virtual void d115(); virtual void d116(); virtual void d117(); virtual void d118(); virtual void d119(); virtual void d120(); virtual void d121(); virtual void d122(); virtual void d123(); virtual void d124(); virtual void d125(); virtual void d126(); virtual void d127(); virtual void d128(); virtual void d129(); virtual void d130(); virtual void d131(); virtual void d132(); virtual void d133(); virtual void d134(); virtual void d135(); virtual void d136(); virtual void d137(); virtual void d138(); virtual void d139(); virtual void d140(); virtual void d141(); virtual void d142(); virtual void d143(); virtual void d144(); virtual void d145(); virtual void d146(); virtual void d147(); virtual void d148(); virtual void d149(); virtual void d150(); virtual void d151(); virtual void d152(); virtual void d153(); virtual void d154(); virtual void d155(); virtual void d156(); virtual void d157(); virtual void d158(); virtual void d159(); virtual void d160(); virtual void d161(); virtual void d162(); virtual void d163(); virtual void d164(); virtual void d165(); virtual void d166(); virtual void d167(); virtual void d168(); virtual void d169(); virtual void d170(); virtual void d171(); virtual void d172(); virtual void d173(); virtual void d174(); virtual void d175(); virtual void d176(); virtual void d177(); virtual void d178(); virtual void d179(); virtual void d180(); virtual void d181(); virtual void d182(); virtual void d183(); virtual void d184(); virtual void d185(); virtual void d186(); virtual void d187(); virtual void d188(); virtual void d189(); virtual void d190(); virtual void d191(); virtual void d192(); virtual void d193(); virtual void d194(); virtual void d195(); virtual void d196(); virtual void d197(); virtual void d198(); virtual void d199(); virtual void d200();  virtual int vX(int, char *); char pad[968]; L_173b30 *f972; L_173b30 *f976; L_173b30 *f980; L_173b30 *f984; L_173b30 *f988; L_173b30 *f992; L_173b30 *f996; L_173b30 *f1000; };
extern "C" void igPsx2VisualContext_PostMultiply(S_173b30 *self, int arg1, int arg2);
typedef struct St_173d60 { char pad0[8]; int n; char pad12[4]; char *data; } St_173d60;
typedef struct O_173d60 { char pad[972]; St_173d60 *s972; St_173d60 *s976; St_173d60 *s980; St_173d60 *s984; St_173d60 *s988; St_173d60 *s992; St_173d60 *s996; St_173d60 *s1000; } O_173d60;
extern "C" void igPsx2VisualContext_GetMatrix(O_173d60 *o, int k, int dst);
struct List_173ed0 { int pad0; int pad1; int count; int cap; char *data; int getCount() const { return count; } };
struct Obj_173ed0 {
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
    virtual void d48();
    virtual void d49();
    virtual void d50();
    virtual void d51();
    virtual void d52();
    virtual void d53();
    virtual void d54();
    virtual void d55();
    virtual void d56();
    virtual void d57();
    virtual void d58();
    virtual void d59();
    virtual void d60();
    virtual void d61();
    virtual void d62();
    virtual void d63();
    virtual void d64();
    virtual void d65();
    virtual void d66();
    virtual void d67();
    virtual void d68();
    virtual void d69();
    virtual void d70();
    virtual void d71();
    virtual void d72();
    virtual void d73();
    virtual void d74();
    virtual void d75();
    virtual void d76();
    virtual void d77();
    virtual void d78();
    virtual void d79();
    virtual void d80();
    virtual void d81();
    virtual void d82();
    virtual void d83();
    virtual void d84();
    virtual void d85();
    virtual void d86();
    virtual void d87();
    virtual void d88();
    virtual void d89();
    virtual void d90();
    virtual void d91();
    virtual void d92();
    virtual void d93();
    virtual void d94();
    virtual void d95();
    virtual void d96();
    virtual void d97();
    virtual void d98();
    virtual void d99();
    virtual void d100();
    virtual void d101();
    virtual void d102();
    virtual void d103();
    virtual void d104();
    virtual void d105();
    virtual void d106();
    virtual void d107();
    virtual void d108();
    virtual void d109();
    virtual void d110();
    virtual void d111();
    virtual void d112();
    virtual void d113();
    virtual void d114();
    virtual void d115();
    virtual void d116();
    virtual void d117();
    virtual void d118();
    virtual void d119();
    virtual void d120();
    virtual void d121();
    virtual void d122();
    virtual void d123();
    virtual void d124();
    virtual void d125();
    virtual void d126();
    virtual void d127();
    virtual void d128();
    virtual void d129();
    virtual void d130();
    virtual void d131();
    virtual void d132();
    virtual void d133();
    virtual void d134();
    virtual void d135();
    virtual void d136();
    virtual void d137();
    virtual void d138();
    virtual void d139();
    virtual void d140();
    virtual void d141();
    virtual void d142();
    virtual void d143();
    virtual void d144();
    virtual void d145();
    virtual void d146();
    virtual void d147();
    virtual void d148();
    virtual void d149();
    virtual void d150();
    virtual void d151();
    virtual void d152();
    virtual void d153();
    virtual void d154();
    virtual void d155();
    virtual void d156();
    virtual void d157();
    virtual void d158();
    virtual void d159();
    virtual void d160();
    virtual void d161();
    virtual void d162();
    virtual void d163();
    virtual void d164();
    virtual void d165();
    virtual void d166();
    virtual void d167();
    virtual void d168();
    virtual void d169();
    virtual void d170();
    virtual void d171();
    virtual void d172();
    virtual void d173();
    virtual void d174();
    virtual void d175();
    virtual void d176();
    virtual void d177();
    virtual void d178();
    virtual void d179();
    virtual void d180();
    virtual void d181();
    virtual void d182();
    virtual void d183();
    virtual void d184();
    virtual void d185();
    virtual void d186();
    virtual void d187();
    virtual void d188();
    virtual void d189();
    virtual void d190();
    virtual void d191();
    virtual void d192();
    virtual void d193();
    virtual void d194();
    virtual void d195();
    virtual void d196();
    virtual void d197();
    virtual void d198();
    virtual void d199();
    virtual void d200();
    virtual void v203(int, void *);
    char pad[980];
    List_173ed0 *list;
};
extern "C" void FUN_00173ed0(Obj_173ed0 *self, int op, void *m);
class A_173fd0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual void d101(); virtual void d102(); virtual void d103(); virtual void d104(); virtual void d105(); virtual void d106(); virtual void d107(); virtual void d108(); virtual void d109(); virtual void d110(); virtual void d111(); virtual void d112(); virtual void d113(); virtual void d114(); virtual void d115(); virtual void d116(); virtual void d117(); virtual void d118(); virtual void d119(); virtual void d120(); virtual void d121(); virtual void d122(); virtual void d123(); virtual void d124(); virtual void d125(); virtual void d126(); virtual void d127(); virtual void d128(); virtual void d129(); virtual void d130(); virtual void d131(); virtual void d132(); virtual void d133(); virtual void d134(); virtual void d135(); virtual void d136(); virtual void d137(); virtual void d138(); virtual void d139(); virtual void d140(); virtual void d141(); virtual void d142(); virtual void d143(); virtual void d144(); virtual void d145(); virtual void d146(); virtual void d147(); virtual void d148(); virtual void d149(); virtual void d150(); virtual void d151(); virtual void d152(); virtual void d153(); virtual void d154(); virtual void d155(); virtual void d156(); virtual void d157(); virtual void d158(); virtual void d159(); virtual void d160(); virtual void d161(); virtual void d162(); virtual void d163(); virtual void d164(); virtual void d165(); virtual void d166(); virtual void d167(); virtual void d168(); virtual void d169(); virtual void d170(); virtual void d171(); virtual void d172(); virtual void d173(); virtual void d174(); virtual void d175(); virtual void d176(); virtual void d177(); virtual void d178(); virtual void d179(); virtual void d180(); virtual void d181(); virtual void d182(); virtual void d183(); virtual void d184(); virtual void d185(); virtual void d186(); virtual void d187(); virtual void d188(); virtual void d189(); virtual void d190(); virtual void d191(); virtual void d192(); virtual void d193(); virtual void d194(); virtual void d195(); virtual void d196(); virtual void d197(); virtual void d198(); virtual void d199(); virtual void d200(); virtual void d201(); virtual void d202(); virtual void d203(); virtual void d204(); virtual void d205(); virtual void vX(int, int); };
extern "C" void FUN_00173fd0(int *arg0, int arg1, int arg2);
extern "C" int DAT_0056091c[4];
struct O_174030 { char pad[1448]; unsigned char f; };
class DW4VC_740_6 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual void d101(); virtual void d102(); virtual void d103(); virtual void d104(); virtual void d105(); virtual void d106(); virtual void d107(); virtual void d108(); virtual void d109(); virtual void d110(); virtual void d111(); virtual void d112(); virtual void d113(); virtual void d114(); virtual void d115(); virtual void d116(); virtual void d117(); virtual void d118(); virtual void d119(); virtual void d120(); virtual void d121(); virtual void d122(); virtual void d123(); virtual void d124(); virtual void d125(); virtual void d126(); virtual void d127(); virtual void d128(); virtual void d129(); virtual void d130(); virtual void d131(); virtual void d132(); virtual void d133(); virtual void d134(); virtual void d135(); virtual void d136(); virtual void d137(); virtual void d138(); virtual void d139(); virtual void d140(); virtual void d141(); virtual void d142(); virtual void d143(); virtual void d144(); virtual void d145(); virtual void d146(); virtual void d147(); virtual void d148(); virtual void d149(); virtual void d150(); virtual void d151(); virtual void d152(); virtual void d153(); virtual void d154(); virtual void d155(); virtual void d156(); virtual void d157(); virtual void d158(); virtual void d159(); virtual void d160(); virtual void d161(); virtual void d162(); virtual void d163(); virtual void d164(); virtual void d165(); virtual void d166(); virtual void d167(); virtual void d168(); virtual void d169(); virtual void d170(); virtual void d171(); virtual void d172(); virtual void d173(); virtual void d174(); virtual void d175(); virtual void d176(); virtual void d177(); virtual void d178(); virtual void d179(); virtual void d180(); virtual void d181(); virtual void d182(); virtual int vX(int, int, int, int, float, float); };
class DW4VC_796_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual void d101(); virtual void d102(); virtual void d103(); virtual void d104(); virtual void d105(); virtual void d106(); virtual void d107(); virtual void d108(); virtual void d109(); virtual void d110(); virtual void d111(); virtual void d112(); virtual void d113(); virtual void d114(); virtual void d115(); virtual void d116(); virtual void d117(); virtual void d118(); virtual void d119(); virtual void d120(); virtual void d121(); virtual void d122(); virtual void d123(); virtual void d124(); virtual void d125(); virtual void d126(); virtual void d127(); virtual void d128(); virtual void d129(); virtual void d130(); virtual void d131(); virtual void d132(); virtual void d133(); virtual void d134(); virtual void d135(); virtual void d136(); virtual void d137(); virtual void d138(); virtual void d139(); virtual void d140(); virtual void d141(); virtual void d142(); virtual void d143(); virtual void d144(); virtual void d145(); virtual void d146(); virtual void d147(); virtual void d148(); virtual void d149(); virtual void d150(); virtual void d151(); virtual void d152(); virtual void d153(); virtual void d154(); virtual void d155(); virtual void d156(); virtual void d157(); virtual void d158(); virtual void d159(); virtual void d160(); virtual void d161(); virtual void d162(); virtual void d163(); virtual void d164(); virtual void d165(); virtual void d166(); virtual void d167(); virtual void d168(); virtual void d169(); virtual void d170(); virtual void d171(); virtual void d172(); virtual void d173(); virtual void d174(); virtual void d175(); virtual void d176(); virtual void d177(); virtual void d178(); virtual void d179(); virtual void d180(); virtual void d181(); virtual void d182(); virtual void d183(); virtual void d184(); virtual void d185(); virtual void d186(); virtual void d187(); virtual void d188(); virtual void d189(); virtual void d190(); virtual void d191(); virtual void d192(); virtual void d193(); virtual void d194(); virtual void d195(); virtual void d196(); virtual int vX(int, int); };
class DW4VC_864_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual void d101(); virtual void d102(); virtual void d103(); virtual void d104(); virtual void d105(); virtual void d106(); virtual void d107(); virtual void d108(); virtual void d109(); virtual void d110(); virtual void d111(); virtual void d112(); virtual void d113(); virtual void d114(); virtual void d115(); virtual void d116(); virtual void d117(); virtual void d118(); virtual void d119(); virtual void d120(); virtual void d121(); virtual void d122(); virtual void d123(); virtual void d124(); virtual void d125(); virtual void d126(); virtual void d127(); virtual void d128(); virtual void d129(); virtual void d130(); virtual void d131(); virtual void d132(); virtual void d133(); virtual void d134(); virtual void d135(); virtual void d136(); virtual void d137(); virtual void d138(); virtual void d139(); virtual void d140(); virtual void d141(); virtual void d142(); virtual void d143(); virtual void d144(); virtual void d145(); virtual void d146(); virtual void d147(); virtual void d148(); virtual void d149(); virtual void d150(); virtual void d151(); virtual void d152(); virtual void d153(); virtual void d154(); virtual void d155(); virtual void d156(); virtual void d157(); virtual void d158(); virtual void d159(); virtual void d160(); virtual void d161(); virtual void d162(); virtual void d163(); virtual void d164(); virtual void d165(); virtual void d166(); virtual void d167(); virtual void d168(); virtual void d169(); virtual void d170(); virtual void d171(); virtual void d172(); virtual void d173(); virtual void d174(); virtual void d175(); virtual void d176(); virtual void d177(); virtual void d178(); virtual void d179(); virtual void d180(); virtual void d181(); virtual void d182(); virtual void d183(); virtual void d184(); virtual void d185(); virtual void d186(); virtual void d187(); virtual void d188(); virtual void d189(); virtual void d190(); virtual void d191(); virtual void d192(); virtual void d193(); virtual void d194(); virtual void d195(); virtual void d196(); virtual void d197(); virtual void d198(); virtual void d199(); virtual void d200(); virtual void d201(); virtual void d202(); virtual void d203(); virtual void d204(); virtual void d205(); virtual void d206(); virtual void d207(); virtual void d208(); virtual void d209(); virtual void d210(); virtual void d211(); virtual void d212(); virtual void d213(); virtual int vX(int); };
extern "C" void FUN_00174090(void *arg0);
class VC104 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual int vX(const char *); };
class VC120 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual int vX(int); };
class VC596 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual void d101(); virtual void d102(); virtual void d103(); virtual void d104(); virtual void d105(); virtual void d106(); virtual void d107(); virtual void d108(); virtual void d109(); virtual void d110(); virtual void d111(); virtual void d112(); virtual void d113(); virtual void d114(); virtual void d115(); virtual void d116(); virtual void d117(); virtual void d118(); virtual void d119(); virtual void d120(); virtual void d121(); virtual void d122(); virtual void d123(); virtual void d124(); virtual void d125(); virtual void d126(); virtual void d127(); virtual void d128(); virtual void d129(); virtual void d130(); virtual void d131(); virtual void d132(); virtual void d133(); virtual void d134(); virtual void d135(); virtual void d136(); virtual void d137(); virtual void d138(); virtual void d139(); virtual void d140(); virtual void d141(); virtual void d142(); virtual void d143(); virtual void d144(); virtual void d145(); virtual void d146(); virtual int vX(int); };
class VC696 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual void d101(); virtual void d102(); virtual void d103(); virtual void d104(); virtual void d105(); virtual void d106(); virtual void d107(); virtual void d108(); virtual void d109(); virtual void d110(); virtual void d111(); virtual void d112(); virtual void d113(); virtual void d114(); virtual void d115(); virtual void d116(); virtual void d117(); virtual void d118(); virtual void d119(); virtual void d120(); virtual void d121(); virtual void d122(); virtual void d123(); virtual void d124(); virtual void d125(); virtual void d126(); virtual void d127(); virtual void d128(); virtual void d129(); virtual void d130(); virtual void d131(); virtual void d132(); virtual void d133(); virtual void d134(); virtual void d135(); virtual void d136(); virtual void d137(); virtual void d138(); virtual void d139(); virtual void d140(); virtual void d141(); virtual void d142(); virtual void d143(); virtual void d144(); virtual void d145(); virtual void d146(); virtual void d147(); virtual void d148(); virtual void d149(); virtual void d150(); virtual void d151(); virtual void d152(); virtual void d153(); virtual void d154(); virtual void d155(); virtual void d156(); virtual void d157(); virtual void d158(); virtual void d159(); virtual void d160(); virtual void d161(); virtual void d162(); virtual void d163(); virtual void d164(); virtual void d165(); virtual void d166(); virtual void d167(); virtual void d168(); virtual void d169(); virtual void d170(); virtual void d171(); virtual int vX(); };
struct Obj;
extern "C" void igPsx2VisualContext_ResetToDefault(void *a0, int arg1);
typedef struct S0_174300 { char pad1372[1372]; unsigned char f55C; } S0_174300;
extern "C" int DAT_00560920[4];
extern "C" unsigned char igPsx2VisualContext_GetNormalizeNormalsState(void *arg0);
typedef struct { char pad[1020]; unsigned char f; } S_174370;
extern "C" long long DAT_005608a8[4];
extern "C" unsigned char igPsx2VisualContext_GetVertexBlendingState(void *arg0);
extern "C" int DAT_00560924[4];
struct S_1743c0 { char pad[1032]; unsigned char f1032; };
extern "C" unsigned char igPsx2VisualContext_GetBlendingState(void *arg0);
extern "C" int DAT_00560928[4];
extern "C" void igPsx2VisualContext_SetBlendingSource(int *arg0, int arg1);
extern "C" int DAT_00560968[4];
struct S174470 { char pad[1100]; int f; };
extern "C" void igPsx2VisualContext_SetBlendingDestination(struct S174470 *arg0, int arg1);
extern "C" int igPsx2VisualContext_GetBlendingSource(void *arg0);
extern "C" int igPsx2VisualContext_GetBlendingDestination(void *arg0);
typedef struct S_1744c0 { char pad0[1036]; int f1036; char pad1040[60]; int f1100; } S_1744c0;
extern "C" void igPsx2VisualContext_SetBlendingSourceDestination(S_1744c0 *arg0, int arg1, int arg2);
struct R_174510 { char pad[1036]; int a[16]; int b[16]; int c[16]; };
extern "C" int DAT_00560948[8];
extern "C" void FUN_00174510(struct R_174510 *arg0, int arg1, int arg2, int arg3, int arg4, int arg5);
extern "C" int DAT_0048ac00[4];
struct E_174640 { int a, b, c, d, e; };
extern "C" void FUN_00174640(int arg0, int arg1);
extern "C" int DAT_0056098c;
extern "C" unsigned char igPsx2VisualContext_GetAlphaTestState(void *arg0);
extern "C" int DAT_00560998[4];
extern "C" int igPsx2VisualContext_GetAlphaFunc(void *arg0);
extern "C" int DAT_0056099c[4];
struct S_1747b0 { char pad[1028]; float f; };
extern "C" float igPsx2VisualContext_GetAlphaRefValue(void *arg0);
typedef struct { char pad[1022]; unsigned char b; char pad2; int i; float f; } S_1747f0;

extern "C" int DAT_0048a500[4];
extern "C" void FUN_001747f0(S_1747f0 *s);
extern "C" int DAT_005609a0[4];
struct S174 { char pad[1373]; unsigned char f; };
extern "C" void FUN_00174850(struct S174 *arg0, int arg1);
extern "C" unsigned char FUN_001748c0(int *p);
extern "C" long long DAT_005608b8[4];
struct O_1748d0 { char pad[1228]; unsigned char v; };
extern "C" unsigned char igPsx2VisualContext_GetViewportClippingState(void *arg0);
extern "C" void FUN_00174950(void *d0, int arg1);

extern "C" void igPsx2VisualContext_GetColorMask(void *arg0, unsigned char *arg1, unsigned char *arg2, unsigned char *arg3, unsigned char *arg4);
extern "C" long long DAT_005608b0[2];
extern "C" int DAT_0048a530[4];
typedef struct { char p[1256]; int f; } S_1749f0;
extern "C" int igPsx2VisualContext_GetShadingMode(void *arg0);
/* The parameter is an int used in place; an unsigned char parameter would be normalised to a
 * masked copy. */
struct S_174a70 { char pad0[1268]; unsigned char f1268; char pad1269[3]; int f1272; };
extern "C" int DAT_0048a538[4];
extern "C" int DAT_005609a4[4];
extern "C" unsigned char igPsx2VisualContext_GetCullFaceState(void *arg0);
extern "C" int DAT_005609a8[4];
extern "C" int igPsx2VisualContext_GetCullFaceMode(void *arg0);
struct S_174bc0 { char pad[1277]; unsigned char f; };
extern "C" int DAT_005609ac[4];
extern "C" unsigned char igPsx2VisualContext_GetDepthTestState(void *arg0);
typedef struct S_174c50 { char p[892]; float f892; unsigned f896; unsigned f900; char q[376]; unsigned f1280; } S_174c50;
extern "C" int DAT_005609b0[4];
extern "C" void igPsx2VisualContext_SetDepthTestFunction(S_174c50 *arg0, unsigned arg1);
extern "C" int igPsx2VisualContext_GetDepthTestFunction(void *arg0);
struct S_174d70 { char pad[1276]; unsigned char b; };
extern "C" int DAT_005609b4[4];
extern "C" unsigned char igPsx2VisualContext_GetDepthWriteState(void *arg0);

extern "C" int DAT_0048a540[4];
extern "C" void FUN_00174db0(void *arg0);
struct S_174e20 { char p[1260]; int f1260; char q[24]; int f1288; };
extern "C" int DAT_005609b8[4];
extern "C" int igPsx2VisualContext_GetStencilState(void *arg0);

extern "C" int DAT_005609bc[4];
extern "C" int igPsx2VisualContext_GetStencilRefVal(void *arg0);

extern "C" int DAT_005609c0[4];
extern "C" int igPsx2VisualContext_GetStencilFunc(void *arg0);
extern "C" void igPsx2VisualContext_GetStencilOps(void);
extern "C" int igPsx2VisualContext_GetStencilReadMask(void);
extern "C" int igPsx2VisualContext_GetStencilWriteMask(void);
typedef struct S_175000 { char pad0[1292]; int f1292; } S_175000;
extern "C" int DAT_005609c4[4];
extern "C" int igPsx2VisualContext_GetRenderMode(void *arg0);
typedef struct S0_175090 { char pad1296[1296]; int f510; } S0_175090;
extern "C" void FUN_00175090(S0_175090 *arg0, int arg1);
struct S_1750c0 { char pad[1300]; unsigned char mode; };
extern "C" int DAT_005609cc[4];
extern "C" unsigned char igPsx2VisualContext_GetFogState(void *arg0);

extern "C" int DAT_0048a560[4];
extern "C" int DAT_005609d0[4];
struct S_175140 { char p[1304]; float f1304; int f1308; char q[16]; float f1328; float f1332; };
extern "C" float igPsx2VisualContext_GetFogDensity(void *arg0);
struct S1304 { char pad[1304]; float f1304; int f1308; char pad2[16]; float f1328; float f1332; };
extern "C" int DAT_005609d4[4];
extern "C" int igPsx2VisualContext_GetFogMode(void *arg0);

extern "C" int DAT_005609d8[4];
extern "C" void igPsx2VisualContext_GetFogColor(void *arg0, void *arg1);
struct S_175310 { char pad[1304]; float f1304; int i1308; char pad2[16]; float f1328; float f1332; };
extern "C" int DAT_005609dc[4];
extern "C" float igPsx2VisualContext_GetFogNear(void *arg0);
extern "C" int DAT_005609e0[4];
extern "C" float igPsx2VisualContext_GetFogFar(void *arg0);
struct E_1753f0 { unsigned char b0; unsigned char b1; char p[2]; int f4; int f8; float f12; int f16; int f20; };
struct S_1753f0 { char pad[322]; unsigned char b322; char pad2[1025]; unsigned char b1348; unsigned char b1349; char pad3[2]; int f1352; int f1356; float f1360; int f1364; int f1368; };
extern "C" void igPsx2VisualContext_SetVideoMode(igResult *arg0, struct S_1753f0 *arg1, struct E_1753f0 *arg2);
extern "C" void igPsx2VisualContext_GetVideoMode(igPsx2VisualContext *arg0, void *arg1);

extern "C" int DAT_0048a520[4];
extern "C" int DAT_005609e4[4];
struct S1754 { char pad[1428]; int f; char tail[1]; };
extern "C" int FUN_001754b0(struct S1754 *arg0, int arg1);
extern "C" int DAT_005609e8[4];
struct S_175510 { char p[1428]; int idx; float v[4]; };
extern "C" void FUN_00175510(struct S_175510 *arg0, float *arg1);
typedef struct S0_1755e0 { char pad1449[1449]; unsigned char f1449; } S0_1755e0;

extern "C" int DAT_005609ec[4];
extern "C" void FUN_001755e0(S0_1755e0 *arg0, int arg1);

extern "C" int DAT_005609f0[4];
struct S_175640 { char p[1536]; unsigned char v; };
extern "C" void FUN_00175640(struct S_175640 *arg0, int arg1);
extern "C" int DAT_005609f4[4];

struct O_175670 { char pad[1537]; unsigned char f; };
extern "C" void FUN_00175670(struct O_175670 *arg0, int arg1);
extern "C" int DAT_005609f8;
typedef struct S_175730 { char pad[312]; unsigned char f; } S_175730;
extern "C" int DAT_005609fc[4];
extern "C" void igPsx2VisualContext_SetDitherState(S_175730 *arg0, int arg1);
struct S_175790 { char pad[1544]; long long v; };

extern "C" int DAT_00560a00[4];
extern "C" void FUN_00175790(struct S_175790 *arg0, long long arg1);

extern "C" int DAT_00560a04[4];
extern "C" void FUN_001757c0(igPsx2VisualContext *arg0, int arg1);
class ParticleArrayCalls {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20();
    virtual void configure(float lifeStart, int format, float lifeEnd, unsigned int maxNum, void *context);
};
extern "C" int igPsx2ParticleArray_Update(igPsx2ParticleArray *self, float time, unsigned int num, unsigned int offset, int *status);
struct PA_175ba0 {
    char p0[20];
    float f20;
    float f24;
    float f28;
    char p32[20];
    int f52;
    unsigned int f56;
    char p60[24];
    float f84;
    char p88[4];
    unsigned char f92;
    char p93[7];
    int f100;
    unsigned char f104;
    char p105[7];
    long long f112;
};
extern "C" int p2DrawParticles(int, unsigned, int, float);
class igPrimLengthArrayView : public igVirtualObject {
public:
    virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8();
    virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14();
    virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();
    virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26();
    virtual int v27(int index);
};
extern "C" void Gap__Bec__ParticleArray__vfunc_27(igParticleArrayRefs *self);
extern "C" long long DAT_00560660[4];
extern "C" void Gap__Gfx__igPsx2ParticleArray__vfunc_29(PA_175ba0 *arg0);
struct PA_175c70;
struct PA_175c70 { int vt; int pad[3]; int n; };
extern "C" int Gap__Gfx__igPsx2ParticleArray__vfunc_24(PA_175c70 *arg0, int arg1);
extern "C" int FUN_001fdca0(...);
extern "C" int FUN_001fdd60(...);
extern "C" int FUN_001fdeb0(...);
extern "C" int FUN_001fe100(...);
extern "C" int FUN_001fe260(...);
extern "C" int FUN_001fe320(...);
extern "C" int g_decodedParticle_00560ac0[4];
extern "C" int g_decodedParticle_00560acc[4];
extern "C" int g_decodedParticle_00560ad8[4];
extern "C" int g_decodedParticle_00560ae4[4];
extern "C" int g_decodedParticle_00560af4[4];
extern "C" int g_decodedParticle_00560b04[4];
extern "C" int g_decodedParticle_00560b14[4];
extern "C" int g_decodedParticle_00560b1c[4];
extern "C" int g_decodedParticle_00560b24[4];
extern "C" int g_decodedParticle_00560b2c[4];
extern "C" int g_decodedParticle_00560b3c[4];
extern "C" int g_decodedParticle_00560b40[4];
extern "C" int g_decodedParticle_00560b44[4];
extern "C" int g_decodedParticle_00560b48[4];
extern "C" int g_decodedParticle_00560b4c[4];
extern "C" int *Gap__Gfx__igPsx2ParticleArray__vfunc_26(igPsx2ParticleArray *self, unsigned int index);
class DW4VC_100_2_175df0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int vX(char *, int); };
extern "C" void Gap__Gfx__igPsx2ParticleArray__vfunc_27(igPsx2ParticleArray *arg0, char *arg1);
extern "C" void *FUN_00175ed0(void *arg0, void *arg1);
extern "C" void *FUN_00175ef0(void *arg0, void *arg1);
extern "C" void *FUN_00175f20(void *arg0, void *arg1);
extern "C" void Gap__Gfx__igPsx2ParticleArray__vfunc_34(igPsx2ParticleArray *arg0, float fp);
extern "C" void Gap__Gfx__igPsx2ParticleArray__vfunc_35(int *arg0, float fparg0);
class DW4VC_136_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual int vX(float); };
class DW4VC_140_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual int vX(float); };
extern "C" void Gap__Gfx__igPsx2ParticleArray__vfunc_39(igPsx2ParticleArray *arg0, int arg1);
struct AL;
class AL { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual char *vX(int); };
class PV { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual char *vX(unsigned); };
struct PA_1765f0 { int vt; int pad1[2]; unsigned n; char pad2[16]; int stride; char *data; char pad3[52]; unsigned char flag; };
extern "C" void igPsx2ParticleArray_UserApplyWriteProxy(PA_1765f0 *arg0);
extern "C" void igPsx2ParticleArray_ReleaseDefaults(igPsx2ParticleArray *self);
struct UCodeState;
struct O176a50;
class V96;
class W_1767c0;
struct Geometry1774;
extern "C" void FUN_001f7340(int);
extern "C" int FUN_001f7360(...);
extern "C" void FUN_00193c50(igVec4f *out, igVec3f *in, float *matrix);
/* igPointSpriteExt drawn without hardware sprites: a camera-facing quad (two triangles, six vertices) per sprite. */
struct VertexArrayLock { int f0; int f4; char pad8[20]; };
class PointSpriteVertexArray : public igVirtualObject {
public:
    virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8();
    virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14();
    virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();
    virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24();
    virtual igVertexFormat *v25();
    virtual void d26();
    virtual void v27(VertexArrayLock *lock, int mode);
    virtual void v28(VertexArrayLock *lock, int mode);
    virtual void setPosition(unsigned int index, igVec3f *position);
};
class PointSpriteDraw : public igVirtualObject {
public:
    virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8();
    virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14();
    virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();
    virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26();
    virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32();
    virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36();
    virtual void getPosition(int index, igVec3f *position);
    virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43();
    virtual void d44(); virtual void d45();
    virtual float getRotation(unsigned int index);
    char pad8[12];
    ParticleContextView *_context;
    PointSpriteVertexArray *_vertexArray;
    char pad28[8];
    int _space;
    char pad40[192];
    float _matrix[16];
};
extern "C" void igPointSpriteExt_Draw(PointSpriteDraw *self, int count, int first);
extern "C" void FUN_001f7370(float);
extern "C" int DAT_004df6b0[4];

extern "C" void FUN_00180170(int, unsigned int, int, int, int *, int *, unsigned int);
class VA_1767c0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int * vX(); };
class VB { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void vX(int,int,int); };
struct UCodeAttr : igObject {
    char pad8[12];
    int flags;
};
class UCodeSource {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5();
    virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11();
    virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17();
    virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
    virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35();
    virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41();
    virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47();
    virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53();
    virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58();
    virtual UCodeAttr *currentAttr();
};
struct UCodeState {
    char pad0[24];
    UCodeAttr *attr;
    char pad28[4];
    unsigned char loaded;
    char pad33[3];
    int mode;
    char pad40[352];
    UCodeSource *source;
};
class V188 { public: virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4(); virtual void a5(); virtual void a6(); virtual void a7(); virtual void a8(); virtual void a9(); virtual void a10(); virtual void a11(); virtual void a12(); virtual void a13(); virtual void a14(); virtual void a15(); virtual void a16(); virtual void a17(); virtual void a18(); virtual void a19(); virtual void a20(); virtual void a21(); virtual void a22(); virtual void a23(); virtual void a24(); virtual void a25(); virtual void a26(); virtual void a27(); virtual void a28(); virtual void a29(); virtual void a30(); virtual void a31(); virtual void a32(); virtual void a33(); virtual void a34(); virtual void a35(); virtual void a36(); virtual void a37(); virtual void a38(); virtual void a39(); virtual void a40(); virtual void a41(); virtual void a42(); virtual void a43(); virtual void a44(); virtual int v188(int *); };
class V96 { public: virtual void b0(); virtual void b1(); virtual void b2(); virtual void b3(); virtual void b4(); virtual void b5(); virtual void b6(); virtual void b7(); virtual void b8(); virtual void b9(); virtual void b10(); virtual void b11(); virtual void b12(); virtual void b13(); virtual void b14(); virtual void b15(); virtual void b16(); virtual void b17(); virtual void b18(); virtual void b19(); virtual void b20(); virtual void b21(); virtual void v96(int *, int, int, int); };
struct O176a50 { char p0[24]; void *f24; char p28[364]; int f392; };
struct R_1767c0 { int w0; int rc; };
class DW4VC_116_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual int vX(); };
class DW4VC_120_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual int vX(); };
class DW4VC_164_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual int vX(); };
class DW4VC_168_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual int vX(); };
class DW4VC_172_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual int vX(); };
class DW4VC_176_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual int vX(); };
class O176d90 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void set(int,int,float *); virtual void get(int,int,float *); int pad[4]; unsigned flags; };
struct V2_1767c0 { float x, y; };
class W_1767c0 { public: int pad[6]; O176d90 *o; };
class DW4VC_204_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual int vX(); };
class DW4VC_208_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual int vX(); };
class DW4VC_228_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual int vX(); };
class DW4VC_232_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual int vX(); };
extern "C" void igPsx2PointSpriteExt_SetContext(void *self, int value);
extern "C" void igPsx2PointSpriteExt_Draw(int *arg0, int arg1, int arg2);
extern "C" void igPsx2PointSpriteExt_SetSpriteSize(int arg0, float farg0);
extern "C" void igPsx2PointSpriteExt_BeginSprites(UCodeState *state);
extern "C" void igPsx2PointSpriteExt_EndSprites(void *arg0);
extern "C" void igPsx2PointSpriteExt_ConfigureVertexArray(O176a50 *arg0, V96 *arg1, int *arg2, int arg3, int arg4);
extern "C" int FUN_00176ba0(void *arg0);
extern "C" void igPsx2PointSpriteExt_SetPosition(void *arg0, int arg1, void *arg2);
extern "C" void igPsx2PointSpriteExt_GetPosition(void *arg0, int arg1, void *arg2);
extern "C" void igPsx2PointSpriteExt_SetColorPacked(void *arg0, int arg1, int arg2);
extern "C" void igPsx2PointSpriteExt_SetColor(void *arg0, int arg1, int arg2);
extern "C" void igPsx2PointSpriteExt_GetColorPacked(void *arg0, unsigned int arg1);
extern "C" void igPsx2PointSpriteExt_GetColor(void *arg0, unsigned int arg1);
extern "C" void igPsx2PointSpriteExt_SetTextureCoord(W_1767c0 *arg0, int arg1, int arg2, float *arg3);
extern "C" void igPsx2PointSpriteExt_GetTextureCoord(void *arg0, int arg1, int arg2);
extern "C" void igPsx2PointSpriteExt_GetTextureCoordPointer(void *arg0, int arg1, int arg2);
extern "C" void igPsx2PointSpriteExt_SetRadian(void *arg0);
extern "C" void igPsx2PointSpriteExt_GetRadian(void *arg0);
struct VertexArray177 {
    int *vtbl;
    int pad4;
    int *f8;
    char pad12[20];
    int f32;
    int f36;
    char pad40[32];
    int f72[16];
    int f136;
};
class VertexFormat177 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int *format(); };
struct DListEntry177 { int f0; VertexArray177 *va; };
struct DLists177 { char pad[16]; DListEntry177 **entries; };
extern "C" int FUN_00177010(igPsx2VisualContext *vc, int *arg1, int *arg2, int arg3, int arg4);
class AttrValue1774 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int meta(); int pad[3]; int f16; };
struct AttrNode1774 { char p0[12]; AttrValue1774 *obj; char p16[8]; int f24; char p28[4]; int f32; };
struct Geometry1774 { char p0[20]; int attrs; char p24[24]; int f48[16]; int f112; int f116; int f120; char p124[4]; int f128; };
extern "C" int FUN_001774c0(igPsx2VisualContext *vc, Geometry1774 *geom, unsigned char *useTexture);

class StatAllocator {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51();
    virtual void *v52(int);
    virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63();
    virtual int vX(void *);
};
class igPsx2VisualContextSlots {
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
    virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual void d101(); virtual void d102(); virtual void d103();
    virtual void d104(); virtual void d105(); virtual void d106(); virtual void d107(); virtual void d108(); virtual void d109(); virtual void d110(); virtual void d111();
    virtual void d112(); virtual void d113(); virtual void d114(); virtual void d115(); virtual void d116(); virtual void d117(); virtual void d118(); virtual void d119();
    virtual void d120(); virtual void d121(); virtual void d122(); virtual void d123(); virtual void d124(); virtual void d125(); virtual void d126(); virtual void d127();
    virtual void d128(); virtual void d129(); virtual void d130(); virtual void d131(); virtual void d132(); virtual void d133(); virtual void d134(); virtual void d135();
    virtual void d136(); virtual void d137(); virtual void d138(); virtual void d139(); virtual void d140(); virtual void d141(); virtual void d142(); virtual void d143();
    virtual void d144(); virtual void d145(); virtual void d146(); virtual void d147(); virtual void d148(); virtual void d149(); virtual void d150(); virtual void d151();
    virtual void d152(); virtual void d153(); virtual void d154(); virtual void d155(); virtual void d156(); virtual void d157(); virtual void d158(); virtual void d159();
    virtual void d160(); virtual void d161(); virtual void d162(); virtual void d163(); virtual void d164(); virtual void d165(); virtual void d166(); virtual void d167();
    virtual void d168(); virtual void d169(); virtual void d170(); virtual void d171(); virtual void d172(); virtual void d173(); virtual void d174(); virtual void d175();
    virtual void d176(); virtual void d177(); virtual void d178(); virtual void d179(); virtual void d180(); virtual void d181(); virtual void d182(); virtual void d183();
    virtual void d184(); virtual void d185(); virtual void d186(); virtual void d187(); virtual void d188(); virtual void d189(); virtual void d190(); virtual void d191();
    virtual void d192(); virtual void d193(); virtual void d194(); virtual void d195(); virtual void d196(); virtual void d197(); virtual void d198(); virtual void d199();
    virtual void d200(); virtual void d201(); virtual void d202(); virtual void d203(); virtual void d204(); virtual void d205(); virtual void d206(); virtual void d207();
    virtual void d208(); virtual void d209(); virtual void d210(); virtual void d211(); virtual void d212(); virtual void d213(); virtual void d214(); virtual void d215();
    virtual void d216(); virtual void d217(); virtual void d218(); virtual void d219(); virtual void d220(); virtual void d221(); virtual void d222(); virtual void d223();
    virtual void d224(); virtual void d225(); virtual void d226(); virtual void d227(); virtual void d228(); virtual void d229(); virtual void d230(); virtual void d231();
    virtual void d232(); virtual void d233(); virtual void d234(); virtual void d235(); virtual void d236(); virtual void d237(); virtual void d238(); virtual void d239();
    virtual void d240(); virtual void d241(); virtual void d242(); virtual void d243(); virtual void d244(); virtual void d245(); virtual void d246(); virtual void d247();
    virtual void d248(); virtual void d249(); virtual void d250(); virtual void d251(); virtual void d252(); virtual void d253(); virtual void d254();
    virtual void vfunc_255();
};
extern "C" void igPsx2VisualContext_GetStatistic(igPsx2VisualContextSlots *self);
extern "C" bool igPsx2VisualContext_GetStatisticCapability(void *context, unsigned int capability);
struct StatNodeView {
    char pad0[8];
    int f8;
    char pad12[4];
    unsigned char f16;
    char pad17[935];
    StatNodeView *next;
};
class igPsx2VisualContextStats {
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
    virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual void d101(); virtual void d102(); virtual void d103();
    virtual void d104(); virtual void d105(); virtual void d106(); virtual void d107(); virtual void d108(); virtual void d109(); virtual void d110(); virtual void d111();
    virtual void d112(); virtual void d113(); virtual void d114(); virtual void d115(); virtual void d116(); virtual void d117(); virtual void d118(); virtual void d119();
    virtual void d120(); virtual void d121(); virtual void d122(); virtual void d123(); virtual void d124(); virtual void d125(); virtual void d126(); virtual void d127();
    virtual void d128(); virtual void d129(); virtual void d130(); virtual void d131(); virtual void d132(); virtual void d133(); virtual void d134(); virtual void d135();
    virtual void d136(); virtual void d137(); virtual void d138(); virtual void d139(); virtual void d140(); virtual void d141(); virtual void d142(); virtual void d143();
    virtual void d144(); virtual void d145(); virtual void d146(); virtual void d147(); virtual void d148(); virtual void d149(); virtual void d150(); virtual void d151();
    virtual void d152(); virtual void d153(); virtual void d154(); virtual void d155(); virtual void d156(); virtual void d157(); virtual void d158(); virtual void d159();
    virtual void d160(); virtual void d161(); virtual void d162(); virtual void d163(); virtual void d164(); virtual void d165(); virtual void d166(); virtual void d167();
    virtual void d168(); virtual void d169(); virtual void d170(); virtual void d171(); virtual void d172(); virtual void d173(); virtual void d174(); virtual void d175();
    virtual void d176(); virtual void d177(); virtual void d178(); virtual void d179(); virtual void d180(); virtual void d181(); virtual void d182(); virtual void d183();
    virtual void d184(); virtual void d185(); virtual void d186(); virtual void d187(); virtual void d188(); virtual void d189(); virtual void d190(); virtual void d191();
    virtual void d192(); virtual void d193(); virtual void d194(); virtual void d195(); virtual void d196(); virtual void d197(); virtual void d198(); virtual void d199();
    virtual void d200(); virtual void d201(); virtual void d202(); virtual void d203(); virtual void d204(); virtual void d205(); virtual void d206(); virtual void d207();
    virtual void d208(); virtual void d209(); virtual void d210(); virtual void d211(); virtual void d212(); virtual void d213(); virtual void d214(); virtual void d215();
    virtual void d216(); virtual void d217(); virtual void d218(); virtual void d219(); virtual void d220(); virtual void d221(); virtual void d222(); virtual void d223();
    virtual void d224(); virtual void d225(); virtual void d226(); virtual void d227(); virtual void d228(); virtual void d229(); virtual void d230(); virtual void d231();
    virtual void d232(); virtual void d233(); virtual void d234(); virtual void d235(); virtual void d236(); virtual void d237(); virtual void d238(); virtual void d239();
    virtual void d240(); virtual void d241(); virtual void d242(); virtual void d243(); virtual void d244(); virtual void d245(); virtual void d246(); virtual void d247();
    virtual void d248(); virtual void d249(); virtual void d250(); virtual void d251(); virtual void d252(); virtual void d253(); virtual void d254();  

    virtual bool supports(unsigned int capability);
    char pad4[1548];
    StatNodeView *nodes;
};
extern "C" bool igPsx2VisualContext_SetStatistic(igPsx2VisualContextStats *self, unsigned int capability, unsigned char enabled);
extern "C" int DAT_0048ac30[4];
extern "C" long long DAT_00560b58[4];
extern "C" long long DAT_00560b60[4];
extern "C" long long DAT_00560b68[4];
extern "C" long long DAT_00560b70[4];
extern "C" long long DAT_00560b78[4];
extern "C" long long DAT_00560b80[4];
extern "C" long long DAT_00560b88[4];
extern "C" long long DAT_00560b90[4];
extern "C" long long DAT_00560b98[4];
extern "C" long long DAT_00560ba0[4];
extern "C" long long DAT_00560ba8[4];
extern "C" long long DAT_00560bb0[4];
extern "C" long long DAT_00560bb8[4];
extern "C" long long DAT_00560bc0[4];
extern "C" long long DAT_00560bc8[4];
extern "C" long long DAT_00560bd0[4];
extern "C" long long DAT_00560bd8[4];
extern "C" long long DAT_00560be0[4];
extern "C" long long DAT_00560be8[4];
extern "C" long long DAT_00560bf0[4];
extern "C" long long DAT_00560bf8[4];
extern "C" long long DAT_00560c00[4];
extern "C" long long DAT_00560c08[4];
extern "C" long long DAT_00560c10[4];
extern "C" long long DAT_00560c18[4];
extern "C" long long DAT_00560c20[4];
extern "C" long long DAT_00560c28[4];
extern "C" long long DAT_00560c30[4];
extern "C" long long DAT_00560c38[4];
extern "C" long long DAT_00560c40[4];
extern "C" long long DAT_00560c48[4];
extern "C" long long DAT_00560c50[4];
extern "C" long long DAT_00560c58[4];
extern "C" long long DAT_00560c60[4];
extern "C" long long DAT_00560c68[4];
extern "C" long long DAT_00560c70[4];
extern "C" long long DAT_00560c78[4];
extern "C" long long DAT_00560c80[4];
extern "C" long long DAT_00560c88[4];
extern "C" long long DAT_00560c90[4];
extern "C" long long DAT_00560c98[4];
extern "C" long long DAT_00560ca0[4];
extern "C" long long DAT_00560ca8[4];
extern "C" long long DAT_00560cb0[4];
extern "C" long long DAT_00560cb8[4];
extern "C" long long DAT_00560cc0[4];
extern "C" long long DAT_00560cc8[4];
extern "C" long long DAT_00560cd0[4];
extern "C" long long DAT_00560cd8[4];
extern "C" long long DAT_00560ce0[4];
extern "C" long long DAT_00560ce8[4];
extern "C" long long DAT_00560cf0[4];
extern "C" long long DAT_00560cf8[4];
extern "C" long long DAT_00560d00[4];
extern "C" long long DAT_00560d08[4];
extern "C" long long DAT_00560d10[4];
extern "C" long long DAT_00560d28[4];
extern "C" long long DAT_00560d30[4];
extern "C" long long DAT_00560d38[4];
extern "C" long long DAT_00560d40[4];
extern "C" long long DAT_00560d48[4];
extern "C" long long DAT_00560d50[4];
extern "C" long long DAT_00560d58[4];
extern "C" long long DAT_00560d60[4];
extern "C" long long DAT_00560d68[4];
extern "C" long long DAT_00560d70[4];
extern "C" long long DAT_00560d78[4];
extern "C" long long DAT_00560d80[4];
extern "C" long long DAT_00560d88[4];
extern "C" long long DAT_00560d90[4];
extern "C" long long DAT_00560d98[4];
extern "C" long long DAT_00560da0[4];
extern "C" long long DAT_00560da8[4];
extern "C" long long DAT_00560db0[4];
extern "C" long long DAT_00560db8[4];
extern "C" long long DAT_00560dc0[4];
extern "C" long long DAT_00560dc8[4];
extern "C" long long DAT_00560dd0[4];
extern "C" long long DAT_00560dd8[4];
extern "C" long long DAT_00560de0[4];
extern "C" long long DAT_00560de8[4];
extern "C" long long DAT_00560df0[4];
extern "C" long long DAT_00560df8[4];
extern "C" long long DAT_00560e00[4];
extern "C" long long DAT_00560e08[4];
extern "C" long long DAT_00560e10[4];
extern "C" long long DAT_00560e18[4];
extern "C" long long DAT_00560e20[4];
extern "C" long long DAT_00560e28[4];
extern "C" long long DAT_00560e30[4];
extern "C" long long DAT_00560e38[4];
extern "C" long long DAT_00560e40[4];
extern "C" long long DAT_00560e48[4];
extern "C" long long DAT_00560e50[4];
extern "C" long long DAT_00560e58[4];
extern "C" long long DAT_00560e60[4];
extern "C" long long DAT_00560e68[4];
extern "C" long long DAT_00560e70[4];
extern "C" long long DAT_00560e78[4];
extern "C" long long DAT_00560e80[4];
extern "C" long long DAT_00560e88[4];
extern "C" long long DAT_00560e90[4];
extern "C" long long DAT_00560e98[4];
extern "C" long long DAT_00560ea0[4];
extern "C" long long DAT_00560ea8[4];
extern "C" long long DAT_00560eb0[4];
extern "C" long long DAT_00560eb8[4];
extern "C" long long DAT_00560ec0[4];
extern "C" long long DAT_00560ec8[4];
extern "C" long long DAT_00560ed0[4];
extern "C" long long DAT_00560ed8[4];
extern "C" long long DAT_00560ee0[4];
extern "C" long long DAT_00560ee8[4];
extern "C" long long DAT_00560ef0[4];
extern "C" void igPsx2VisualContext_GetStatistics(void);
/* Reads one GS/frame statistic as a per-frame rate. The game keeps the current statistics block
 * (58 long long, 0x1d0 bytes) and the block taken at the last reset. `id` selects the number:
 * elapsed = current[5] - previous[5] (frame-length counter), nothing is computed when it is not
 * positive; most ids return (current[k] - previous[k]) / elapsed, some scaled to milliseconds (x
 * 1000 / 9216000 ticks per second) or by 16; ids 44..56 return a small-integer query
 * p2GetPoolAllocated(n); ids 58, 59, 16, 17, 20, 24 consume a free-running accumulator and clear it; ids
 * 60..186 consume the per-id event counters (unsigned) and clear them; ids 42 and 43 take a fresh
 * snapshot and return one raw field of it. The result is -1.0f for an unknown id. */
typedef struct GsStatBlock { long long c[58]; } GsStatBlock;
extern "C" GsStatBlock g_gsStatCurrent;
extern "C" GsStatBlock g_gsStatPrevious;
extern "C" unsigned int g_gsEventCount[];
extern "C" long long g_gsAccumulator_005608a0[4];
extern "C" long long g_gsAccumulator_00560660[4];
extern "C" long long g_gsAccumulator_00560668[4];
extern "C" long long g_gsRawCounter[4];
#define CUR g_gsStatCurrent.c
#define PREV g_gsStatPrevious.c
#define DELTA(k) ((float)(CUR[k] - PREV[k]))
#define TICKS_PER_SECOND 9216000
extern "C" float igPsx2VisualContext_GetStatisticValue(void *unused, int id);
extern "C" void FUN_001788a0(void *arg0);
struct StatRefObject { char pad4[4]; int refs; };
struct StatNode88 { char pad12[12]; StatRefObject *f0c; char pad16[936]; StatNode88 *f3b8; };
struct StatContext88 { char pad[1552]; StatNode88 *f610; };
extern "C" void FUN_001788e0(StatContext88 *arg0, int arg1);
struct O_1778e0 { int p0; int refs; int f8; int f12; };
extern "C" struct Ref_1778e0 { O_1778e0 *p; Ref_1778e0(O_1778e0 *q) : p(q) {} ~Ref_1778e0() { O_1778e0 *q = p; if (q != 0) { q->refs = q->refs - 1; if (((unsigned long long)(long long)q->refs & 0x7fffffULL) == 0) igObject_Destroy((igObject *)q); } } operator O_1778e0 *() { return p; } O_1778e0 *operator->() { return p; } };
struct StatNode { int f0; int f4; int f8; O_1778e0 *f12; char f16; char pad[935]; StatNode *f952; };
struct StatContext { char pad[1552]; StatNode *f1552; };
struct G_1778e0 { char pad[56]; int f56; };

extern "C" void FUN_00179e00(StatContext *arg0);

extern "C" int DAT_0048ac40[];
extern "C" int DAT_0048acb0[];
extern "C" int DAT_0048ac70[4];
extern "C" int DAT_0048acf0[];
extern "C" int DAT_00560a5c[8];
typedef struct StageState { int w[112]; } StageState;
class igPsx2VisualContextSlots_17a070 {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual void d101(); virtual void d102(); virtual void d103(); virtual void d104(); virtual void d105(); virtual void d106(); virtual void d107(); virtual void d108(); virtual void d109(); virtual void d110(); virtual void d111(); virtual void d112(); virtual void d113(); virtual void d114(); virtual void d115(); virtual void d116(); virtual void d117(); virtual void d118(); virtual void d119(); virtual void d120(); virtual void d121(); virtual void d122(); virtual void d123(); virtual void d124();
    virtual void vfunc_125(int value, int option);
    virtual void d126(); virtual void d127(); virtual void d128(); virtual void d129(); virtual void d130();
    virtual void vfunc_131(int value, int index, int option);
};
extern "C" void FUN_0017a070(int *a);
typedef struct BufferEntryRef { int w0; int references; } BufferEntryRef;
typedef struct BufferSetView { char p0[48]; BufferEntryRef *f48; BufferEntryRef *f52; BufferEntryRef **f56; unsigned int f60; char p64[8]; void *f72; } BufferSetView;
extern "C" void FUN_0017a180(void *self);
extern "C" int FUN_0017a2b0(int arg0);
struct Buf_17a070;
class Owner_17a070 {
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
    virtual void d48();
    virtual void d49();
    virtual void d50();
    virtual void d51();
    virtual void d52();
    virtual void d53();
    virtual void *v224(int, int);
    virtual void *v228(int, int, int);
};
struct Buf_17a070 { short s0, s2, s4; short pad6; int f8; short *f12; void *f16; };
struct Self_17a070 { char p[324]; Buf_17a070 *f324; int pad328; T *f332; int f336, f340; char p344[220]; char a564[16]; };
extern "C" void FUN_0017a300(Self_17a070 *self);
typedef struct S0_17a070 { char pad1524[1524]; int f5F4; int f5F8; int f5FC; } S0_17a070;
extern "C" void FUN_0017a7e0(S0_17a070 *arg0);
extern "C" void FUN_0017a870(S0_17a070 *arg0, int arg1);
extern "C" int Gap__Gfx__igPsx2VisualContext__vfunc_142(void);
struct TextureStateView117 { char pad[564]; unsigned char a[16]; };
extern "C" int DAT_00560a08[8];
extern "C" unsigned char igPsx2VisualContext_GetTextureStageState(int arg0, int arg1);
struct ClutObject {
    char pad0[32];
    int handle;
    int locked;
};
class MipImage : public igVirtualObject {
public:
    virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void reduceFrom(MipImage *source);
    virtual void allocate(int size, int flags);
    virtual void setWidth(int width);
    virtual void setHeight(int height);
    virtual void setFormat(int format);
    unsigned int width;
    unsigned int height;
    char pad16[36];
    int pixels;
    char pad56[12];
    ClutObject *clut;
};
struct ClutData {
    char pad0[28];
    unsigned char dirty;
};
struct ClutEntry {
    int pad0;
    ClutData *data;
    int handle;
    char pad12[8];
    int state;
};
struct TexEntry {
    int format;
    int minFilter;
    int magFilter;
    int wrapU;
    int wrapV;
    int kind;
    unsigned int flags;
    int stage;
    int width;
    int height;
    int depth;
    char pad44[4];
    igObject *palette;
    MipImage *image;
    igSmartPointer<MipImage> *mipImages;
    unsigned int mipCount;
    char pad64[8];
    int *buffers;
    int buffer;
    char pad80;
    unsigned char reload;
    char pad82[2];
    int lodParams[4];
    int altClut;
    int clut;
    int bufferIndex;
    char pad112[24];
};
class ListAllocator {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55();
    virtual unsigned short *reallocate(unsigned short *block, int size);
};
struct TexList {
    unsigned short count;
    unsigned short freeCapacity;
    unsigned short freeCount;
    char pad6[6];
    unsigned short *freeIndices;
    TexEntry *data;
};
struct ClutList {
    int pad0[4];
    ClutEntry *data;
};
class TexContext {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual void d101(); virtual void d102(); virtual void d103(); virtual void d104(); virtual void d105(); virtual void d106(); virtual void d107(); virtual void d108(); virtual void d109(); virtual void d110(); virtual void d111(); virtual void d112(); virtual void d113(); virtual void d114(); virtual void d115(); virtual void d116(); virtual void d117(); virtual void d118(); virtual void d119(); virtual void d120(); virtual void d121(); virtual void d122(); virtual void d123(); virtual void d124(); virtual void d125(); virtual void d126(); virtual void d127();
    virtual void unloadTexture(int index);
    virtual void vfunc_131(int index);  /* unloads the texture, frees its CLUT and returns its index to the free list */
    char pad4[320];
    TexList *texList;
    ClutList *clutList;
    char pad332[4];
    int currentTex;
    char pad340[216];
    unsigned char texPageEnable;
};
extern "C" unsigned int DAT_0048aca0[];
extern "C" ListAllocator *FUN_002ed520(TexList *);
extern "C" int DAT_0048acc0[];
extern "C" bool FUN_0017b400(TexContext *context, TexEntry *entry, int stage, ClutEntry *clut, int clutIndex);
extern "C" void igPsx2VisualContext_CreateTextureOneImage(TexContext *a0, int a1, int a2, int a3, int a4, int a5, int a6);
class TexMemoryPool {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51();
    virtual int *allocate(int size);
    virtual void d53();
    virtual igSmartPointer<MipImage> *allocateArray(int elementSize, int count);
};
struct ClutContextCB80;
extern "C" int igPsx2VisualContext_CreateTexture(TexContext *context, int width, int height, int format, int kind, unsigned int flags, unsigned int levels);
extern "C" int Gap__Gfx__igPsx2VisualContext__vfunc_124(void);
extern "C" void igPsx2VisualContext_SetTextureRegion(void);
extern "C" void igPsx2VisualContext_GetTextureInfo(igPsx2VisualContext *arg0, int arg1, int *arg2, int *arg3, int *arg4, int *arg5, char *arg6);
extern "C" void igPsx2VisualContext_LoadTexture(igPsx2VisualContextSlots_17a070 *self, int value, int option);
extern "C" void FUN_0017b5f0(TexContext *context, TexEntry *entry);
extern "C" int igPsx2VisualContext_GetCurrentTexture(void *arg0);
typedef struct UCodeProgram {
    char pad0[68];
    int resident;
} UCodeProgram;
typedef struct UCodeSlot {
    char pad0[20];
    int kind;
    char pad24[28];
    UCodeProgram *program;
    char pad56[16];
    int *buffers;
    int buffer;
    char pad80[20];
    int altHandle;
    int handle;
    int bufferIndex;
    char pad112[24];
} UCodeSlot;
typedef struct UCodeSlotList {
    int _pad0[4];
    UCodeSlot *_data;
} UCodeSlotList;
typedef struct UCodeContextView {
    char pad0[324];
    UCodeSlotList *slots;
    char pad328[8];
    int current;
} UCodeContextView;
extern "C" void igPsx2VisualContext_DeleteTexture(TexContext *context, int index);
extern "C" void igPsx2VisualContext_SetTextureSource(igPsx2VisualContextSlots_17a070 *self, int value, int index, int option);
class TextureImageView260 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual int vX(int, int, int, int); };
extern "C" int igPsx2VisualContext_GetTextureImage(void *arg0, int arg1);
extern "C" int igPsx2VisualContext_SetTextureSourceFromTexture(void);
typedef struct TextureEntry138 { char pad4[4]; int f4; char pad8[72]; unsigned char f80; char pad81[55]; } TextureEntry138;
typedef struct TextureList138 { char pad16[16]; TextureEntry138 *f16; } TextureList138;
extern "C" int DAT_00560a28[4];
extern "C" int DAT_00560a2c[4];
struct TextureEntry140 { char pad[8]; int v; char pad2[68]; char flag; char pad3[55]; };
struct TextureList140 { char pad[16]; struct TextureEntry140 *arr; };
extern "C" int igPsx2VisualContext_GetTextureMinificationFilter(void *arg0, int arg1);
extern "C" int igPsx2VisualContext_GetTextureMagnificationFilter(void *arg0, int arg1);
extern "C" int DAT_00560a34[4];
extern "C" int DAT_00560a38[4];
struct TextureList136 { char pad[16]; char *e; };
extern "C" void igPsx2VisualContext_GetTextureAddressingMode(void *arg0, int arg1, int *arg2, int *arg3);
extern "C" void FUN_0017c6e0(int arg0);
extern "C" int DAT_00560a3c[4];
extern "C" void FUN_0017c710(int arg0, int arg1, int arg2);
extern "C" unsigned char FUN_0017c790(int arg0, int arg1);
typedef struct VisualContextSlots { char pad[580]; int slot[16]; } VisualContextSlots;
extern "C" void FUN_0017c880(igPsx2VisualContext *arg0, int arg1, unsigned char arg2);
extern "C" void FUN_0017c8a0(igPsx2VisualContext *context, int stage, int function, unsigned char colorComponent);
extern "C" int igPsx2VisualContext_GetTextureStageFunc(int arg0, int a1);
struct TextureStageView150 { char pad[644]; int a[16]; int b[16]; };
extern "C" int DAT_00560a7c[8];
extern "C" int DAT_00560a9c[8];
extern "C" void igPsx2VisualContext_GetTextureStageCoordSource(int arg0, int arg1, int *arg2, int *arg3);
struct ClutContextCB80 { char pad[836]; int f836; int f840; int f844; int f848; int f852; int f856; int f860; };
extern "C" int FUN_0017ccb0(struct ClutContextCB80 *, int, int, int *);
extern "C" int FUN_0017cb80(struct ClutContextCB80 *arg0, int arg1, int *arg2);
extern "C" void Gap__Gfx__igPsx2VisualContext__vfunc_122(void);
struct R_17cef0 { int w0; int refs; };
class M_17cef0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void *meta(); };
struct O_17cef0 { char pad[20]; M_17cef0 *m; R_17cef0 *b; R_17cef0 *a; };
extern "C" void Gap__Gfx__igPsx2UserUCodeExt__vfunc_29(O_17cef0 *arg0, M_17cef0 *arg1);
extern "C" igMetaObject *igPsx2VisualContext_GetMeta(void);
extern "C" void thunk_igObject_InitDefaults(igObject *self);
extern "C" void igPsx2VertexArray1_1_ReleaseDefaults(igPsx2VertexArray1_1 *self);
extern "C" void igPsx2VertexArray1_1_Reset(void);
class VC_17d0c0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual int vX(int, int); };
struct S_17d0c0 { char pad8[8]; int f8; int fc; int f10; int f14; char pad18[4]; int f1c; };
extern "C" int igPsx2VertexArray1_1_Configure(S_17d0c0 *arg0, int *arg1, int arg2, int arg3);
struct Obj_17d170 { int w0; unsigned refs; };
class V_17d170 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual unsigned *g(); char pad[44]; Obj_17d170 *f48; Obj_17d170 *f52; Obj_17d170 *f56; };
extern "C" void FUN_0017d170(V_17d170 *arg0);
struct R_17d2b0 { int w0; int rc; };
struct Lst_17d2b0 { int w0; int w4; int n; int w12; int *items; };
struct O_17d2b0 { char pad[48]; struct Lst_17d2b0 *f48; struct Lst_17d2b0 *f52; struct R_17d2b0 *f56; };
extern "C" void FUN_0017d2b0(struct O_17d2b0 *arg0);
extern "C" void igPsx2VertexArray1_1_SetPosition(int *arg0, int arg1, float *arg2);
extern "C" void igPsx2VertexArray1_1_GetPosition(igPsx2VertexArray1_1 *arg0, int arg1, float *arg2);
extern "C" int igPsx2VertexArray1_1_GetPositionPointer(int *arg0, int arg1);
extern "C" void igPsx2VertexArray1_1_SetNormal(igPsx2VertexArray1_1 *arg0, int arg1, void *arg2);
extern "C" void igPsx2VertexArray1_1_GetNormal(igVertexArray *arg0, int arg1, void *arg2);
#define VERTEX_ENTRY_SIZE 0xC  /* 3 floats per entry */
extern "C" int igPsx2VertexArray1_1_GetNormalPointer(igPsx2VertexArray1_1 *self, int vertexIndex);
extern "C" void igPsx2VertexArray1_1_SetColorPacked(igPsx2VertexArray1_1 *arg0, int arg1, unsigned int arg2);
typedef struct ColorStreamView { char pad[8]; unsigned int *f8; } ColorStreamView;
typedef struct ColorArrayView { char pad[8]; ColorStreamView *f8; } ColorArrayView;
extern "C" void igPsx2VertexArray1_1_SetColor(ColorArrayView *arg0, int arg1, float *c);
extern "C" int igPsx2VertexArray1_1_GetColorPacked(igPsx2VertexArray1_1 *arg0, int arg1);
typedef struct VertexArrayStore { char pad[8]; unsigned int *data; } VertexArrayStore;
typedef struct VertexArrayView { char pad[8]; VertexArrayStore *b; } VertexArrayView;
extern "C" void igPsx2VertexArray1_1_GetColor(VertexArrayView *arg0, int arg1, float *arg2);
extern "C" void igPsx2VertexArray1_1_SetTextureCoord(igPsx2VertexArray1_1 *self, int texCoordSet, int vertexIndex, void *uv);
extern "C" void igPsx2VertexArray1_1_GetTextureCoord(igPsx2VertexArray1_1 *self, int texCoordSet, int vertexIndex, void *uv);
extern "C" int igPsx2VertexArray1_1_GetTextureCoordPointer(igPsx2VertexArray1_1 *self, int index, int element);
typedef struct VertexDataView { char pad[76]; float *data; } VertexDataView;
typedef struct VertexArrayView_17d910 { char pad[8]; VertexDataView *b; } VertexArrayView_17d910;
extern "C" void igPsx2VertexArray1_1_SetPointSpriteRadian(VertexArrayView_17d910 *arg0, int arg1, float x);
extern "C" float igPsx2VertexArray1_1_GetPointSpriteRadian(igPsx2VertexArray1_1 *arg0, int arg1);
struct P_17da90 { int f0; int f4; int f8; int pad[12]; int f60; int pad2[1]; int f68; int f72; };
struct VA_17da90 {
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
    virtual unsigned *flags();
    int pad;
    P_17da90 *f8;
    int f12;
    int pad2;
    int f20;
    int pad3[2];
    char *f32;
    char *f36;
    int pad4[6];
    long long f64;
};
struct St_17da90 { int f0; int f4; int f8; int getF8() const { return f8; } int f12; char *f16; int f20; int f24; };
extern "C" void igPsx2VertexArray1_1_GetEditableComponent(VA_17da90 *arg0, St_17da90 *arg1);
extern "C" void igPsx2VertexArray1_1_CommitComponentEdits(void);
struct VertexColorBuffer { char p[8]; unsigned int *data; };
struct VertexArrayColorView { char p0[8]; struct VertexColorBuffer *b; unsigned int count; unsigned int f16_pad; int f20; int pad24; int f28; char pad32[32]; long long f64; };
extern "C" void igPsx2VertexArray1_1_UserApplyWriteProxy(struct VertexArrayColorView *s);
extern "C" void igPsx2VertexArray1_1_UserMakeConcrete(void *arg0, int arg1);
class Obj_17dea0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void vX(int); };
extern "C" void igPsx2VisualContext_SetVertexArray2(int *arg0, int *arg1, int arg2);
class VC_17e590 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); int pad[3]; int f16; };
struct Node { char p0[12]; VC_17e590 *obj; char p1[16]; int f32; };
struct Self_17e590 { char p[944]; int f944; };
extern "C" bool FUN_0017e590(Self_17e590 *arg0, int arg1, int arg2, int *arg3, int *arg4);

class Obj_17e980 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int meta(); int pad; int f16_; };
struct E_17e980 { char pad[12]; Obj_17e980 *obj; char pad2[16]; int f32; };
extern "C" void FUN_0017e980(igPsx2VisualContext *h, int arg1, int arg2);
typedef struct B_17eb90 { char p0[944]; struct C_17eb90 *f944; struct D_17eb90 *f948; } B_17eb90;
struct C_17eb90 { char p[12]; int f12; };
struct D_17eb90 { char p[8]; int *f8; };
extern "C" bool FUN_0017df40(B_17eb90 *, int, int, int *, int *, int *, int *);
extern "C" void FUN_0017eb90(B_17eb90 *arg0, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6);
struct Rc_17f2b0 : public igObject { };
struct Disp { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual void d101(); virtual void d102(); virtual void d103(); virtual void d104(); virtual void d105(); virtual void d106(); virtual void d107(); virtual void d108(); virtual void d109(); virtual void d110(); virtual void d111(); virtual void d112(); virtual void d113(); virtual void d114(); virtual void d115(); virtual void d116(); virtual void d117(); virtual void d118(); virtual void d119(); virtual void d120(); virtual void d121(); virtual void d122(); virtual void d123(); virtual void d124(); virtual void d125(); virtual void d126(); virtual void d127(); virtual void d128(); virtual void d129(); virtual void d130(); virtual void d131(); virtual void d132(); virtual void d133(); virtual void d134(); virtual void d135(); virtual void d136(); virtual void d137(); virtual void d138(); virtual void d139(); virtual void d140(); virtual void d141(); virtual void d142(); virtual void d143(); virtual void d144(); virtual void d145(); virtual void d146(); virtual void d147(); virtual void d148(); virtual void d149(); virtual void d150(); virtual void d151(); virtual void d152(); virtual void d153(); virtual void d154(); virtual void d155(); virtual void d156(); virtual void d157(); virtual void d158(); virtual void d159(); virtual void d160(); virtual void d161(); virtual void d162(); virtual void d163(); virtual void d164(); virtual void d165(); virtual void d166(); virtual void d167(); virtual void d168(); virtual void d169(); virtual void d170(); virtual void d171(); virtual void d172(); virtual void d173(); virtual void d174(); virtual void d175(); virtual void d176(); virtual void d177(); virtual void d178(); virtual void d179(); virtual void d180(); virtual void d181(); virtual void d182(); virtual void d183(); virtual void d184(); virtual void d185(); virtual void d186(); virtual void d187(); virtual void d188(); virtual void d189(); virtual void d190(); virtual void d191(); virtual void d192(); virtual void d193(); virtual void d194(); virtual void d195(); virtual void d196(); virtual void d197(); virtual void d198(); virtual void d199(); virtual void d200(); virtual void d201(); virtual void d202(); virtual void d203(); virtual void d204(); virtual void d205(); virtual void d206(); virtual void d207(); virtual void d208(); virtual void d209(); virtual void d210(); virtual void d211(); virtual void d212(); virtual void d213(); virtual void d214(); virtual void d215(); virtual void d216(); virtual void d217(); virtual void d218(); virtual void d219(); virtual void d220(); virtual void d221(); virtual void d222(); virtual void d223(); virtual void d224(); virtual void d225(); virtual void d226(); virtual void d227(); virtual void d228(); virtual void d229(); virtual void d230(); virtual void d231(); virtual void d232(); virtual void d233(); virtual void d234(); virtual void d235(); virtual void d236(); virtual void d237(); virtual void d238(); virtual void d239(); virtual void d240(); virtual void d241(); virtual void d242(); virtual void d243(); virtual void d244(); virtual void d245(); virtual void d246(); virtual void d247(); virtual void d248(); virtual void d249(); virtual void d250(); virtual void d251(); virtual void d252(); virtual void d253(); virtual void d254(); virtual void d255(); virtual void d256(); virtual void d257(); virtual void d258(); virtual int v1044(void *, int); };
struct Impl { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual int v104(igSmartPointer<Rc_17f2b0>, int, void *, void *); };
struct Info { char pad[12]; unsigned int f12; };
extern "C" int Gap__Gfx__igPsx2VertexArray2__vfunc_23(igVertexArray2 *array, int primitive, int arg2, Info *info, Disp *display);
class igPsx2VertexArray2View {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21();
    virtual void vfunc_22();
};
extern "C" void igPsx2VertexArray2_ReleaseDefaults(igPsx2VertexArray2View *self);
class DW4VC_108_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual int vX(); };
extern "C" void Gap__Gfx__igPsx2VertexArray2__vfunc_24(void *arg0);

extern "C" void FUN_0017f5a0(void);
typedef struct S0_17f630 { char pad16[16]; unsigned char f10; char pad24[7]; int f18; char pad128[100]; int f80; int f84; int f88; } S0_17f630;

extern "C" void igPsx2VertexStream_UserWriteFilePreProcess(S0_17f630 *arg0);
typedef struct S0_17f6c0 { char pad12[12]; int fC; char f10; char pad128[111]; int f80; int f84; int f88; } S0_17f6c0;

extern "C" void igPsx2VertexStream_UserPostLoad(S0_17f6c0 *arg0);
extern "C" int igPsx2VisualContext_GetPixelPipelineMode(void *arg0);
struct L_17fd80 { char p[8]; unsigned int n; char q[4]; unsigned int *data; 
static inline unsigned int cvt(unsigned int v, int mode) {
    unsigned int s;
    if (mode == 0x80) { return (v & 0xFFFFFF) | (((v >> 1) & 0x7F000000) + (v & 0x01000000)); }
    if (mode == 0xFF) { s = (v & 0x80000000) >> 7; return (v & 0xFFFFFF) | (s + (((v & 0xFF000000) - s) * 2)); }
    return v;
}
};
extern "C" void FUN_0017fd80(L_17fd80 **arg0, L_17fd80 **arg1, int arg2);
struct Obj_17fe50;
class Buf_17fe50 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual int v23(); int w4; int w8; int w12; int f16; };
struct Obj_17fe50 : public igObject { int w8; Buf_17fe50 *buf; int p16; int p20; int f24; };
struct Dst { int f0; int f4; int f8; int f12; int f16; int f20; int f24; };
struct Src_17fe50 { char pad[20]; int f20; int f24; };
extern "C" void Gap__Gfx__igPsx2VertexStream__vfunc_24(Src_17fe50 *self, Dst *x);
class A_17ff60 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual int vX(); int pad4[2]; int f12; unsigned char f16; char pad17[23]; long long f40; char pad48[80]; int f128; int f132; int f136; };
extern "C" void Gap__Gfx__igPsx2VertexStream__vfunc_27(A_17ff60 *arg0);
extern "C" int Gap__Gfx__igVertexStream__vfunc_23(void *arg0);
extern "C" void FUN_00180020(long long *arg0);
struct S_180030 { char pad[72]; int f72; int f76; int pad2; int f84; char pad3[1336]; char f1424; };
class V2_180060 { public: virtual void b0(); virtual void b1(); virtual void b2(); virtual void b3(); virtual void b4(); virtual void b5(); virtual void b6(); virtual void b7(); virtual void b8(); virtual void b9(); virtual void b10(); virtual void b11(); virtual void b12(); virtual void b13(); virtual void b14(); virtual void b15(); virtual void b16(); virtual void b17(); virtual void b18(); virtual void b19(); virtual void b20(); virtual void b21(); virtual void b22(); virtual void b23(); virtual void b24(); virtual void b25(); virtual void b26(); virtual void b27(); virtual void b28(); virtual void b29(); virtual void b30(); virtual void b31(); virtual void b32(); virtual void b33(); virtual void b34(); virtual void b35(); virtual void b36(); virtual void b37(); virtual void b38(); virtual void b39(); virtual void b40(); virtual void b41(); virtual void b42(); virtual void b43(); virtual void b44(); virtual void b45(); virtual void b46(); virtual void b47(); virtual void b48(); virtual void b49(); virtual void b50(); virtual void b51(); virtual void b52(); virtual void *v220(unsigned int, int); };
struct O_180060 { char p72_[72]; unsigned int f72; int f76; char *f80; char *f84; char pad88[1332]; int f1420; char f1424; };
extern "C" void FUN_00180060(O_180060 *arg0);
typedef struct BuildResource : public igObject { int w8; struct BuildResource *f12; int f16; int f20; int f24; int f28; } BuildResource;
typedef struct ResourceBuilder { char pad[644]; int f644; char pad2[692]; unsigned char f1340; char pad3[83]; unsigned char f1424; } ResourceBuilder;
typedef struct ResourceList : public igObject { int count; int cap; } ResourceList;
typedef struct ResourceSource { char pad[20]; int f20; } ResourceSource;
extern "C" void FUN_00180ab0(ResourceBuilder *builder, BuildResource *srcPositions, BuildResource *outPositions, BuildResource *srcNormals, BuildResource *outNormals, BuildResource *weights, BuildResource *indices, int weightCount);
#define RELEASE(x) { BuildResource *q = (x); if (q != 0) { q->_refCount = q->_refCount - 1; if ((q->_refCount & 0x7FFFFF) == 0) igObject_Destroy(q); } }
extern "C" void FUN_001805a0(ResourceBuilder *arg0, ResourceSource *arg1, int arg2);
extern "C" igMetaObject *igPsx2VertexStream_GetMeta(void);
extern "C" void Gap__Gfx__igVertexStream__vfunc_25(void);
extern "C" int igPsx2VertexArray2_GetMeta(void);
extern "C" igMetaObject *igPsx2VertexArray1_1_GetMeta(void);
extern "C" int igPsx2UserUCodeExt_GetMeta(void);
extern "C" int igContextExt_UpdateFrameRateDisplay(void);
extern "C" void igContext_DetectDriverDatabaseProperties(void);
extern "C" int igPsx2PointSpriteExt_GetMeta(void);
extern "C" int igPsx2ParticleArray_GetMeta(void);
extern "C" float Gap__Bec__ParticleArray__vfunc_31(ParticleArray *arg0);
extern "C" float Gap__Bec__ParticleArray__vfunc_34(ParticleArray *arg0);
extern "C" int igPsx2ScissorExt_GetMeta(void);
extern "C" igMetaObject *igPsx2MultiTextureExt_GetMeta(void);
extern "C" int igPsx2ImageConvert_GetMeta(void);
extern "C" int igPsx2Image_GetMeta(void);
extern "C" void FUN_00180ca0(void *arg0, int arg1);
extern "C" int igPsx2DecalExt_GetMeta(void);
extern "C" igMetaObject *igPsx2BlendEquationExt_GetMeta(void);
extern "C" igMetaObject *igPsx2DisableExt_GetMeta(void);
extern "C" void igPsx2VisualContext_SetNativeWindowHandle(void);
extern "C" int igPsx2VisualContext_GetNativeWindowHandle(void);
extern "C" void igPsx2VisualContext_SetNativeDeviceHandle(void);
extern "C" int igPsx2VisualContext_GetNativeDeviceHandle(void);
extern "C" void igPsx2VisualContext_SetNativeRenderContextHandle(void);
extern "C" int igPsx2VisualContext_GetNativeRenderContextHandle(void);
extern "C" void igPsx2VisualContext_SetNativeVisualInfo(void);
extern "C" int igPsx2VisualContext_GetNativeVisualInfo(igPsx2VisualContext *self);
extern "C" unsigned char igPsx2VisualContext_GetMaterialSpecularState(void *arg0);
extern "C" void Gap__Gfx__igPsx2VisualContext__vfunc_121(void);
extern "C" int igPsx2VisualContext_GetTextureMatrixState(void *arg0);
extern "C" void igVisualContext_MakeCurrent(void);
extern "C" void igVisualContext_IsCurrent(void);
extern "C" void igVisualContext_Activate(void);
extern "C" void igVisualContext_Deactivate(void);
class igPsx2VisualContextSlots_180dd0 {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31();
    virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39();
    virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47();
    virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55();
    virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63();
    virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68();
    virtual void vfunc_69();
};
extern "C" void igVisualContext_DrawIndexed(igPsx2VisualContextSlots_180dd0 *self);
extern "C" int igTgaLoader_GetMeta(void);
extern "C" igMetaObject *igFileImagePng_GetMeta(void);
extern "C" int igVisualContextCapabilityManager_GetMeta(void);
extern "C" int FUN_00180e10(void);
extern "C" int FUN_00180e20(void);
extern "C" int igVertexArray2Helper_GetMeta(void);
extern "C" void Gap__Gfx__igVertexArray2Helper__vfunc_55(igVertexArray2Helper *self);
extern "C" int igVertexStream_GetMeta(void);
extern "C" void Gap__Gfx__igVertexStream__vfunc_24(void);
extern "C" int Gap__Gfx__igVertexStream__vfunc_26(void);
extern "C" igMetaObject *igVertexArray2_GetMeta(void);
extern "C" int FUN_00180ee0(void);
extern "C" int igPrimLengthArray1_1_GetMeta(void);
extern "C" int igPointSpriteExt_GetMeta(void);
extern "C" int FUN_00180f10(void);
extern "C" int igParticleArray_GetMeta(void);
extern "C" void Gap__Bec__ParticleArray__vfunc_32(ParticleArray *arg0, float arg1);
extern "C" void Gap__Bec__ParticleArray__vfunc_33(ParticleArray *arg0, float arg1);
extern "C" igMetaObject *FUN_00180f60(void);
extern "C" int igGenericCapabilityManager_GetMeta(void);
extern "C" igMetaObject *igExternalImageEntry_GetMeta(void);
extern "C" int igClut_GetMeta(void);
extern "C" void FUN_00180fa0(igParticleFormat *self);
extern "C" int igPsx2Clut_GetMeta(void);
extern "C" int igPsx2IndexArray_GetMeta(void);
extern "C" igMetaObject *FUN_00180fd0(void);
extern "C" int igPsx2LongList_GetMeta(void);
extern "C" int FUN_00180ff0(void);
extern "C" int igCustomStateCollection_GetMeta(void);
extern "C" igMetaObject *igCustomStateCollectionList_GetMeta(void);
extern "C" igMetaObject *igCustomStateField_GetMeta(void);
extern "C" igMetaObject *igCustomStateFieldList_GetMeta(void);
extern "C" igMetaObject *igTrackedElementMetaField_GetMeta(void);
extern "C" int igTrackedElementMetaField_GetDescriptor(void);
extern "C" int igParticleFormat_GetMeta(void);
extern "C" int FUN_00181070(void);
extern "C" int igVertexData_GetMeta(void);
extern "C" igMetaObject *igVertexDataList_GetMeta(void);
extern "C" igMetaObject *igVisualContextList_GetMeta(void);
extern "C" igMetaObject *igVisualContextList_GetElementMeta(void);
extern "C" int FUN_001810c0(void);
extern "C" igMetaObject *igCustomStateFieldList_GetElementMeta(void);
extern "C" igMetaObject *igCustomStateCollectionList_GetElementMeta(void);
extern "C" int igCustomStateCollection_GetElementMeta(void);
extern "C" igMetaObject *igVertexDataList_GetElementMeta(void);
extern "C" void igDataList_TrimCapacity(igDataList *arg0);
class CountedVertexWriter {
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
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void v116(unsigned, float *);
    virtual void e0();
    virtual void e1();
    virtual void e2();
    virtual void e3();
    virtual void e4();
    virtual void e5();
    virtual void v144(unsigned, float *);
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
    virtual void f4();
    virtual void f5();
    virtual void f6();
    virtual void f7();
    virtual void f8();
    virtual void f9();
    virtual void f10();
    virtual void f11();
    virtual void f12();
    virtual void f13();
    virtual void f14();
    virtual void f15();
    virtual void f16();
    virtual void f17();
    virtual void v220(unsigned, igVec2f);
    unsigned refs;
    char pad[16];
    CountedVertexWriter *f24;
};
extern "C" void FUN_001815b0(int n, unsigned i, int base, int stride, CountedVertexWriter *a4, CountedVertexWriter *a5, float f);
extern "C" void ParticleArray_EvaluateLinearVec2(float *a, float *b, float *c, float s);
extern "C" int ParticleArray_GetSizeVelocity(int arg0);
extern "C" int ParticleArray_GetSize(int arg0);
extern "C" void ParticleArray_EvaluateLinearVec3(float *a, float *b, float *c, float s);
extern "C" int ParticleArray_GetVelocity(int arg0);
extern "C" int ParticleArray_GetPosition(int a0);
class B_1818c0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual int v116(unsigned, int *); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual int v144(unsigned, int *); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual int v212(unsigned, float);
 int f4; char pad8[16]; B_1818c0 *f24; };
extern "C" void FUN_001818c0(int arg0, unsigned arg1, int arg2, int arg3, B_1818c0 *arg4, B_1818c0 *arg5, float fparg0);
extern "C" void ParticleArray_EvaluateQuadraticFloat(float *a, float *b, float *c, float *d, float x, float y);
extern "C" int ParticleArray_GetSizeAcceleration(int arg0);
extern "C" void FUN_00181b60(int n, unsigned int i, int particles, int particleSize, CountedVertexWriter *array, CountedVertexWriter *sprite, float time);
extern "C" void ParticleArray_EvaluateQuadraticVec2(float *o, float *a, float *b, float *c, float x, float y);
struct Obj_181e30 { int vt; int ref; };
class A_181e30 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual int s0(unsigned, char *); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual int s1(unsigned, void *); };
class Hold { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual int s0(unsigned, char *); virtual void d35(); virtual int s1(unsigned, void *); int pad[5]; Obj_181e30 *obj; };
extern "C" void FUN_00181e30(int cnt, unsigned idx, int base, int stride, A_181e30 *arg4, Hold *arg5, float f);
extern "C" void ParticleArray_EvaluateLinearVec4(void *arg0, void *arg1, void *arg2, float fparg0);
extern "C" int ParticleArray_GetColorVelocity(int arg0);
extern "C" int ParticleArray_GetColor(int arg0);
class B_182110 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual int v116(unsigned, int *); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual int v144(unsigned, int *); virtual void d35(); virtual int v152(unsigned, int); virtual void d37(); virtual void d38(); virtual int v164(unsigned, int); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual int v212(unsigned, float); virtual void d52(); virtual int v220(unsigned, float *);
 int f4; char pad8[16]; B_182110 *f24; };
extern "C" void ParticleArray_EvaluateQuadraticVec4(igVec4f *out, const igVec4f *a, const igVec4f *b, const igVec4f *c, float s, float t);
extern "C" void FUN_00182110(int arg0, unsigned arg1, int arg2, int arg3, B_182110 *arg4, B_182110 *arg5, float fparg0);
extern "C" void ParticleArray_EvaluateLinearFloat(float *arg0, float *arg1, float *arg2, float fparg0);
extern "C" int ParticleArray_GetColorAcceleration(int arg0);
class B_1824d0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual int v116(unsigned, int *); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual int v144(unsigned, int *); virtual void d35(); virtual int v152(unsigned, int); virtual void d37(); virtual void d38(); virtual int v164(unsigned, int); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual int v220(unsigned, igVec2f);
 int f4; char pad8[16]; B_1824d0 *f24; };
extern "C" void FUN_001824d0(int arg0, unsigned arg1, int arg2, int arg3, B_1824d0 *arg4, B_1824d0 *arg5, float fparg0);
class Ref_182800 {
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
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void v116(unsigned, int *);
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual void d31();
    virtual void d32();
    virtual void d33();
    virtual void v144(unsigned, int *);
    virtual void d35();
    virtual void v152(unsigned, int);
    virtual void d37();
    virtual void d38();
    virtual void v164(unsigned, int);
    virtual void d40();
    virtual void d41();
    virtual void d42();
    virtual void d43();
    virtual void d44();
    virtual void d45();
    virtual void d46();
    virtual void d47();
    virtual void d48();
    virtual void d49();
    virtual void d50();
    virtual void v212(unsigned, float);
    int refs;
    char pad[16];
    Ref_182800 *f24;
};
extern "C" void FUN_00182800(int arg0, unsigned arg1, int arg2, int arg3, Ref_182800 *arg4, Ref_182800 *arg5, float fparg0);
class VertexArrayTargetEx { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual int v116(unsigned, int *); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual int v144(unsigned, int *); virtual void d35(); virtual int v152(unsigned, int); virtual void d37(); virtual void d38(); virtual int v164(unsigned, int); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual int v212(unsigned, float); virtual void d52(); virtual int v220(unsigned, igVec2f);
 int f4; char pad8[16]; VertexArrayTargetEx *f24; };
extern "C" void FUN_00182b00(int arg0, unsigned arg1, int arg2, int arg3, VertexArrayTargetEx *arg4, VertexArrayTargetEx *arg5, float fparg0);
class B_182e20 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual int v116(unsigned, int *); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual int v144(unsigned, int *); virtual void d35(); virtual int v152(unsigned, int); virtual void d37(); virtual void d38(); virtual int v164(unsigned, int);
 int f4; char pad8[16]; B_182e20 *f24; };
extern "C" void FUN_00182e20(int arg0, unsigned arg1, int arg2, int arg3, B_182e20 *arg4, B_182e20 *arg5, float fparg0);
struct V3_1830b0 { float x, y, z; };
struct V4_1830b0 { float x, y, z, w; };
struct A_1830b0 { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void v144(unsigned, void *); virtual void d35(); virtual void v152(unsigned, int); };
struct B_1830b0 { virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4(); virtual void a5(); virtual void a6(); virtual void a7(); virtual void a8(); virtual void a9(); virtual void a10(); virtual void a11(); virtual void a12(); virtual void a13(); virtual void a14(); virtual void a15(); virtual void a16(); virtual void a17(); virtual void a18(); virtual void a19(); virtual void a20(); virtual void a21(); virtual void a22(); virtual void a23(); virtual void a24(); virtual void a25(); virtual void a26(); virtual void v116(unsigned, void *); virtual void b0(); virtual void b1(); virtual void b2(); virtual void b3(); virtual void b4(); virtual void b5(); virtual void b6(); virtual void b7(); virtual void b8(); virtual void b9(); virtual void b10(); virtual void v164(unsigned, int); virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3(); virtual void c4(); virtual void c5(); virtual void c6(); virtual void c7(); virtual void c8(); virtual void c9(); virtual void c10(); virtual void v212(unsigned, float); };
extern "C" void FUN_001830b0(int arg0, unsigned arg1, int arg2, int arg3, igObject *arg4, A_1830b0 *arg5, float fparg0);
struct V3_1836f0 { float x, y, z; };
struct V4_1836f0 { float x, y, z, w; };
struct A_1836f0 { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void v144(unsigned, void *); virtual void d35(); virtual void v152(unsigned, int); char pad[20]; igObject *f24; };
struct B_1836f0 { virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4(); virtual void a5(); virtual void a6(); virtual void a7(); virtual void a8(); virtual void a9(); virtual void a10(); virtual void a11(); virtual void a12(); virtual void a13(); virtual void a14(); virtual void a15(); virtual void a16(); virtual void a17(); virtual void a18(); virtual void a19(); virtual void a20(); virtual void a21(); virtual void a22(); virtual void a23(); virtual void a24(); virtual void a25(); virtual void a26(); virtual void v116(unsigned, void *); virtual void b0(); virtual void b1(); virtual void b2(); virtual void b3(); virtual void b4(); virtual void b5(); virtual void b6(); virtual void b7(); virtual void b8(); virtual void b9(); virtual void b10(); virtual void v164(unsigned, int); virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3(); virtual void c4(); virtual void c5(); virtual void c6(); virtual void c7(); virtual void c8(); virtual void c9(); virtual void c10(); virtual void v212(unsigned, float); };
extern "C" void FUN_001836f0(int arg0, unsigned arg1, int arg2, int arg3, igObject *arg4, A_1836f0 *arg5, float fparg0);
struct MeshVec3 { float x, y, z; };
class MeshTarget { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual int v116(unsigned, MeshVec3 *); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual int v144(unsigned, MeshVec3 *); virtual void d35(); virtual int v152(unsigned, int); virtual void d37(); virtual void d38(); virtual int v164(unsigned, int); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual int v220(unsigned, igVec2f);
 int f4; char pad8[16]; MeshTarget *f24; };
struct MeshVec4 { float x, y, z, w; };
extern "C" void FUN_00183a20(int arg0, unsigned arg1, int arg2, int arg3, MeshTarget *arg4, MeshTarget *arg5, float fparg0);
extern "C" void FUN_001833c0(int n, unsigned int i, int particles, int particleSize, MeshTarget *array, MeshTarget *sprite, float time);
extern "C" void FUN_00184ff0(int n, unsigned int i, int particles, int particleSize, MeshTarget *array, MeshTarget *sprite, float time);
extern "C" void ParticleArray_EvaluateQuadraticVec3(igVec3f *out, const igVec3f *a, const igVec3f *b, const igVec3f *c, float s, float t);
class IndexedValueWriter {
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
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void v116(unsigned, int *);
    virtual void e0();
    virtual void e1();
    virtual void e2();
    virtual void e3();
    virtual void e4();
    virtual void e5();
    virtual void v144(unsigned, int *);
    unsigned refs;
    char pad[16];
    IndexedValueWriter *f24;
};
extern "C" void FUN_00183d70(int n, unsigned i, int base, int stride, IndexedValueWriter *a4, IndexedValueWriter *a5, float f);
extern "C" int ParticleArray_GetAcceleration(int arg0);
class Ref_183fd0 {
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
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void v116(unsigned, float *);
    virtual void e0();
    virtual void e1();
    virtual void e2();
    virtual void e3();
    virtual void e4();
    virtual void e5();
    virtual void v144(unsigned, float *);
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
    virtual void f4();
    virtual void f5();
    virtual void f6();
    virtual void f7();
    virtual void f8();
    virtual void f9();
    virtual void f10();
    virtual void f11();
    virtual void f12();
    virtual void f13();
    virtual void f14();
    virtual void f15();
    virtual void v212(unsigned, float);
    unsigned refs;
    char pad[16];
    Ref_183fd0 *f24;
};
extern "C" void FUN_00183fd0(int n, unsigned i, int base, int stride, Ref_183fd0 *a4, Ref_183fd0 *a5, float f);
extern "C" void FUN_00184240(int n, unsigned i, int base, int stride, CountedVertexWriter *a4, CountedVertexWriter *a5, float f);
typedef struct R_1844d0 { int w0; int refs; } R_1844d0;
class A4 {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); 
    virtual void v27(unsigned int, int *);
    virtual void w28(); virtual void w29(); virtual void w30(); virtual void w31(); virtual void w32(); virtual void w33(); virtual void w34(); virtual void w35(); virtual void w36(); virtual void w37(); virtual void w38(); virtual void w39(); virtual void w40(); virtual void w41(); virtual void w42(); virtual void w43(); virtual void w44(); virtual void w45(); virtual void w46(); virtual void w47(); virtual void w48(); virtual void w49(); virtual void w50(); 
    virtual void v51(unsigned int, float);
    int pad[5]; R_1844d0 *obj;
};
class A5 {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33(); 
    virtual void v34(unsigned int, int *);
    int pad[5]; R_1844d0 *obj;
};
extern "C" void FUN_001844d0(int arg0, unsigned int arg1, int arg2, int arg3, A4 *arg4, A5 *arg5, float fparg0);
class B_184770 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual int v116(unsigned, int *); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual int v144(unsigned, int *); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual int v220(unsigned, igVec2f);
 int f4; char pad8[16]; B_184770 *f24; };
extern "C" void FUN_00184770(int arg0, unsigned arg1, int arg2, int arg3, B_184770 *arg4, B_184770 *arg5, float fparg0);
class B_184a30 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual int v116(unsigned, int *); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual int v144(unsigned, int *); virtual void d35(); virtual int v152(unsigned, int); virtual void d37(); virtual void d38(); virtual int v164(unsigned, int); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual int v212(unsigned, float);
 int f4; char pad8[16]; B_184a30 *f24; };
extern "C" void FUN_00184a30(int arg0, unsigned arg1, int arg2, int arg3, B_184a30 *arg4, B_184a30 *arg5, float fparg0);
/* matching construct: A_184cc0 and B_184cc0 are dummy-virtual classes supplying the retail vtable slot offsets; A_184cc0::f24 is a ref-counted object held at +24 (receiver class not established) */
struct V3_184cc0 { float x, y, z; };
struct V4_184cc0 { float x, y, z, w; };
struct A_184cc0 { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void v144(unsigned, void *); virtual void d35(); virtual void v152(unsigned, int); char pad[20]; igObject *f24; };
struct B_184cc0 { virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4(); virtual void a5(); virtual void a6(); virtual void a7(); virtual void a8(); virtual void a9(); virtual void a10(); virtual void a11(); virtual void a12(); virtual void a13(); virtual void a14(); virtual void a15(); virtual void a16(); virtual void a17(); virtual void a18(); virtual void a19(); virtual void a20(); virtual void a21(); virtual void a22(); virtual void a23(); virtual void a24(); virtual void a25(); virtual void a26(); virtual void v116(unsigned, void *); virtual void b0(); virtual void b1(); virtual void b2(); virtual void b3(); virtual void b4(); virtual void b5(); virtual void b6(); virtual void b7(); virtual void b8(); virtual void b9(); virtual void b10(); virtual void v164(unsigned, int); virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3(); virtual void c4(); virtual void c5(); virtual void c6(); virtual void c7(); virtual void c8(); virtual void c9(); virtual void c10(); virtual void v212(unsigned, float); };
extern "C" void FUN_00184cc0(int arg0, unsigned arg1, int arg2, int arg3, igObject *arg4, A_184cc0 *arg5, float fparg0);
class B_185340 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual int v116(unsigned, int *); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual int v144(unsigned, int *); virtual void d35(); virtual int v152(unsigned, int); virtual void d37(); virtual void d38(); virtual int v164(unsigned, int); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual int v212(unsigned, float);
 int f4; char pad8[16]; B_185340 *f24; };
extern "C" void FUN_00185340(int arg0, unsigned arg1, int arg2, int arg3, B_185340 *arg4, B_185340 *arg5, float fparg0);
struct V3_185670 { float x, y, z; };
class B_185670 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual int v116(unsigned, V3_185670 *); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual int v144(unsigned, V3_185670 *); virtual void d35(); virtual int v152(unsigned, int); virtual void d37(); virtual void d38(); virtual int v164(unsigned, int); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual int v220(unsigned, igVec2f);
 int f4; char pad8[16]; B_185670 *f24; };
struct V4_185670 { float x, y, z, w; };
extern "C" void FUN_00185670(int arg0, unsigned arg1, int arg2, int arg3, B_185670 *arg4, B_185670 *arg5, float fparg0);
class B_1859c0 {
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
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual int v116(unsigned, float *);
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual void d31();
    virtual void d32();
    virtual void d33();
    virtual int v144(unsigned, float *);
    virtual void d35();
    virtual int v152(unsigned, int);
    virtual void d37();
    virtual void d38();
    virtual int v164(unsigned, int);
    int f4;
    char pad8[16];
    B_1859c0 *f24;
};
extern "C" void FUN_001859c0(int arg0, unsigned arg1, int arg2, int arg3, B_1859c0 *arg4, B_1859c0 *arg5, float fparg0);
struct V3_185c80 { float x, y, z; };
struct V4_185c80 { float x, y, z, w; };
struct A_185c80 { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void v144(unsigned, void *); virtual void d35(); virtual void v152(unsigned, int); char pad[20]; igObject *f24; };
struct B_185c80 { virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4(); virtual void a5(); virtual void a6(); virtual void a7(); virtual void a8(); virtual void a9(); virtual void a10(); virtual void a11(); virtual void a12(); virtual void a13(); virtual void a14(); virtual void a15(); virtual void a16(); virtual void a17(); virtual void a18(); virtual void a19(); virtual void a20(); virtual void a21(); virtual void a22(); virtual void a23(); virtual void a24(); virtual void a25(); virtual void a26(); virtual void v116(unsigned, void *); virtual void b0(); virtual void b1(); virtual void b2(); virtual void b3(); virtual void b4(); virtual void b5(); virtual void b6(); virtual void b7(); virtual void b8(); virtual void b9(); virtual void b10(); virtual void v164(unsigned, int); virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3(); virtual void c4(); virtual void c5(); virtual void c6(); virtual void c7(); virtual void c8(); virtual void c9(); virtual void c10(); virtual void v212(unsigned, float); };
extern "C" void FUN_00185c80(int arg0, unsigned arg1, int arg2, int arg3, igObject *arg4, A_185c80 *arg5, float fparg0);
class VertexSink { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual int v116(unsigned, float *); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual int v144(unsigned, float *); virtual void d35(); virtual int v152(unsigned, int); virtual void d37(); virtual void d38(); virtual int v164(unsigned, int); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual int v212(unsigned, float); virtual void d52(); virtual int v220(unsigned, igVec2f);
 int f4; char pad8[16]; VertexSink *f24; };
extern "C" void FUN_00185fb0(int arg0, unsigned arg1, int arg2, int arg3, VertexSink *arg4, VertexSink *arg5, float fparg0);
/* matching construct: dummy virtual slots so the vN() calls dispatch through the retail vtable offsets (receiver classes of A_186300 and B_186300 are not established) */
struct V3_186300 { float x, y, z; };
struct V4_186300 { float x, y, z, w; };
struct A_186300 { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void v144(unsigned, void *); virtual void d35(); virtual void v152(unsigned, int); char pad[20]; igObject *f24; };
struct B_186300 { virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4(); virtual void a5(); virtual void a6(); virtual void a7(); virtual void a8(); virtual void a9(); virtual void a10(); virtual void a11(); virtual void a12(); virtual void a13(); virtual void a14(); virtual void a15(); virtual void a16(); virtual void a17(); virtual void a18(); virtual void a19(); virtual void a20(); virtual void a21(); virtual void a22(); virtual void a23(); virtual void a24(); virtual void a25(); virtual void a26(); virtual void v116(unsigned, void *); virtual void b0(); virtual void b1(); virtual void b2(); virtual void b3(); virtual void b4(); virtual void b5(); virtual void b6(); virtual void b7(); virtual void b8(); virtual void b9(); virtual void b10(); virtual void v164(unsigned, int); virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3(); virtual void c4(); virtual void c5(); virtual void c6(); virtual void c7(); virtual void c8(); virtual void c9(); virtual void c10(); virtual void v212(unsigned, float); };
extern "C" void FUN_00186300(int arg0, unsigned arg1, int arg2, int arg3, igObject *arg4, A_186300 *arg5, float fparg0);
struct PackedVertexWriter { virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4(); virtual void a5(); virtual void a6(); virtual void a7(); virtual void a8(); virtual void a9(); virtual void a10(); virtual void a11(); virtual void a12(); virtual void a13(); virtual void a14(); virtual void a15(); virtual void a16(); virtual void a17(); virtual void a18(); virtual void a19(); virtual void a20(); virtual void a21(); virtual void a22(); virtual void a23(); virtual void a24(); virtual void a25(); virtual void a26();  virtual void v116(unsigned, int *); virtual void b0(); virtual void b1(); virtual void b2(); virtual void b3(); virtual void b4(); virtual void b5(); virtual void b6(); virtual void b7(); virtual void b8(); virtual void b9(); virtual void b10();  virtual void v164(unsigned, int); virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3(); virtual void c4(); virtual void c5(); virtual void c6(); virtual void c7(); virtual void c8(); virtual void c9(); virtual void c10(); virtual void c11(); virtual void c12();  virtual void v220(unsigned, igVec2f); int refs; };
struct VertexArrayWriter { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33();  virtual void v144(unsigned, int *); virtual void d35(); virtual void v152(unsigned, int); int pad[5]; PackedVertexWriter *f24; };
extern "C" void FUN_00186660(int arg0, unsigned int arg1, int arg2, int arg3, PackedVertexWriter *arg4, VertexArrayWriter *arg5, float fparg0);
extern "C" ManagerList *DAT_00560758;

#endif
