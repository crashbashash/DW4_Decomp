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
#include "dw4/gfx/igPsx2BlendEquationExt.h"
#include "dw4/gfx/igPsx2VisualContext.h"
#include "dw4/gfx/igVertexArray.h"
#include "dw4/gfx/GfxMetaEnums.h"
#include <string.h>
#include <stdio.h>
#include "dw4/support/softfloat.h"
#include "dw4/gfx/igComponentEditInfo2.h"
#include "dw4/p2/p2viewport.h"
#include "dw4/p2/p2texture.h"
#include "dw4/p2/p2swap.h"
#include "dw4/p2/p2pool.h"
#include "dw4/p2/p2multipass.h"
#include "dw4/p2/p2lighting.h"
#include "dw4/core/igMemoryPoolView.h"
#include "dw4/gfx/igDecalExtDispatchView.h"
#include "dw4/gfx/Psx2BlendEquation.h"
#include "dw4/gfx/igPsx2HandlePool.h"
#include "dw4/gfx/igPsx2RenderDestination.h"
#include "dw4/gfx/igPsx2RenderList.h"
#include "dw4/gfx/igPsx2ClutRecord.h"
#include "dw4/gfx/igPsx2TextureRecord.h"
typedef igPsx2HandlePool<p2Light> igPsx2LightPool;
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
#include "dw4/core/igStringRef.h"
#include "dw4/game/ParticleArray.h"
#include <math.h>
#include "dw4/maths/igVec4fMetaField.h"
#include "dw4/core/igMemoryRefMetaField.h"
#include "dw4/maths/igMatrix44fMetaField.h"
#include "dw4/maths/igMathConstants.h"
#include "dw4/core/igIntList.h"
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
#include "dw4/maths/igVec3ucList.h"
#include "dw4/maths/igVec4fList.h"
#include "dw4/maths/igVec3uc.h"
#include "dw4/maths/igVec4uc.h"
#include "dw4/gfx/igVertexData.h"
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
#include "dw4/support/eekernel.h"
#include "dw4/newlib/newlib_mallinfo.h"

extern "C" igMetaObject *g_igScissorExt_metaObject;
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
extern "C" void GfxLibrary_MarkRegistered(void);

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

/* Deleting destructor; the deletion flag is a signed short. */
typedef struct ObjectRefTarget { int word0; int references; } ObjectRefTarget;
typedef struct ObjectRefWord { ObjectRefTarget *value; } ObjectRefWord;

typedef struct S_ref { char pad4[4]; int f4; } S_ref;
union U { int vt; char b[48]; };
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
extern "C" igSmartPointer<igObject> *FUN_0014dd40(igSmartPointer<igObject> *self, short deleteFlag);
extern "C" igMetaObject *igImage_GetPublishedMetaObject(void);
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
extern "C" void igTrackedElementMetaField_InitDefaults(igTrackedElementMetaField *self);

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
struct S_temp_a0_1506b0 { char pad4[4]; int f4; };
struct O_1506b0 { S_temp_a0_1506b0 *m; };
extern "C" void** FUN_001372e0(igObject**, short);
extern "C" void** FUN_00137360(void**, long long);

extern "C" int IG_GFX_CLEARRENDERDESTINATION_TYPE_PSX2_GetMetaEnum(void);
extern "C" int IG_GFX_CLIPPING_TYPE_PSX2_GetMetaEnum(void);
extern "C" O_1506b0 *FUN_00150f30(O_1506b0 *arg0, short arg1);
extern "C" ObjectRefWord *FUN_00150fb0(ObjectRefWord *self,int delete_storage);
extern "C" void *FUN_00151030(void *arg0);
extern "C" int *FUN_00151050(int *p);
extern "C" int *FUN_00151060(int *p);
extern "C" int *FUN_00151070(int *p);
extern "C" int *FUN_00151080(int *p);
extern "C" int FUN_00151090(int a);
extern "C" int FUN_001510a0(int arg0);
extern "C" int *FUN_00151190(int *arg0);
extern "C" void thunk_igPsx2VertexArray2_GetMetaObject_0014acf0(void);
extern "C" void igPsx2VertexArray2_InitFields_00152350(void);
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

/* matching construct: dummy virtual slots so the vX() call dispatches through the retail vtable slot */
class A { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void vX(igObject *); };

extern "C" int text_igImageDirectory[4];
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
typedef struct Obj_155c00 { int vt; int refs; int pad; int id; } Obj_155c00;
typedef struct List { int vt; int r; int count; int cap; Obj_155c00 **data; } List;

#define REL(o) if(o){ --(o)->refs; if((((unsigned long long)(long long)(o)->refs)&0x7fffffULL)==0) igObject_Destroy((::igObject *)o);}
typedef struct Rc { int w0; int refs; } Rc;
typedef struct Ls { char p0[8]; int cnt; char p1[4]; Rc **data; } Ls;
struct Entry : public igObject { char pad[12]; char *name; };
struct EntryList { int w0; int w4; int count; int capacity; Entry **data; };

struct KeyedEntry : public igObject { char *name; };
struct KeyedEntryList { int w0; int w4; int count; int capacity; KeyedEntry **data; };
struct NamedValue { const char *name; int value; };
struct C { int f0; int f4; int f8; int fc; };
struct B { char pad[16]; struct C **tab; };
extern "C" int FUN_00156ae0(int arg0, int arg1, float fparg0);
static inline igMemoryPoolView *poolOf(igObject *object, const igMemoryPoolHandle &handle) {
    igMemoryPoolView *pool = ((Gap::Core::igObject *)object)->getMemoryPool();
    return (g_useOwnerAllocator != 0) ? pool : Memory_GetAllocatorBySelector(handle);
}
static inline igMemoryPoolView *poolOf(const Gap::Core::igObject *object, const igMemoryPoolHandle &handle) {
    igMemoryPoolView *pool = object->getMemoryPool();
    return (g_useOwnerAllocator != 0) ? pool : Memory_GetAllocatorBySelector(handle);
}

struct ImageBlock16 { long long a; long long b; };
/* Copies a compressed image's 16-byte blocks into tile order (2x2 groups of blocks, the lower row's halves
 * swapped); FUN_0015a750 calls it. */
extern "C" void FUN_0015a6a0(Gap::Gfx::igImage *self, ImageBlock16 *out);
/* Copies an uncompressed image into tiles (4x4 or 8x4/8x8 pixels by depth); 32-bit pixels split into high and low
 * halves 32 bytes apart. Compressed images go through FUN_0015a6a0. */
extern "C" void FUN_0015a750(igImage *self, unsigned char *out);

/* An image loader's pixel hand-over: the image takes `pixels` as its buffer (the loader is unused). */
extern "C" void FUN_0015ad20(void *loader, igImage *image, void *pixels);
/* An image loader's size query: Gap::Gfx::igImage::estimateImageSize for `image` (the loader is unused). */
extern "C" void FUN_0015ad30(void *loader, igImage *image, int format, int width, int height, int *size,
                             int *components, int *rowBytes);
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
extern "C" void igParticleArray_UserPostLoad(igParticleArray *self);
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
struct Y { char pad0[20]; DW4VC_812 *dev; R_15cb50 *obj; char pad1[4]; unsigned char b32; char pad2[3]; int w36; };
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
    virtual void d52();
    virtual void setPointSize2(unsigned int index, igVec2f size);
    virtual void d54();
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
extern "C" void igPointSpriteExt_GetTextureCoord(igPointSpriteExt *self, int arg1, int arg2);
extern "C" void igPointSpriteExt_GetTextureCoordPointer(igPointSpriteExt *self, int arg1, int arg2);
extern "C" void igPointSpriteExt_SetUniformSize(igPointSpriteExtView *self, unsigned int index, float value);
extern "C" void igPointSpriteExt_SetRadian(igPointSpriteExtView *self);
extern "C" void igPointSpriteExt_GetRadian(igPointSpriteExtView *self);
extern "C" int FUN_0015e130(unsigned int v);
extern "C" igVertexFormat FUN_0015e160(unsigned int vtype);
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
typedef struct L { int p0,p4; int n; int p12; int *data; } L;
/* Vertex-data lookups: by component type and index, and with a user ID. */
extern "C" igVertexData *FUN_0015f4a0(igVertexDataList *list, int type, unsigned int index);
extern "C" igVertexData *FUN_0015f510(igVertexDataList *list, int type, int userID, int index);

/* compressVertexData's fixed-point conversions: `value` with `fractionBits` fraction bits, and back (integer part). */
extern "C" int igVertexArray2Helper_FloatToFixedPoint(float value, unsigned int fractionBits);
extern "C" float igVertexArray2Helper_FixedPointToFloat(int value, int fractionBits);
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
    /* the kit's static ref/release, forwarding to Gap::Core::igObject's members as the flat igObject's do */
    static inline void release(igObjectSlotView *obj) { if (obj != 0) ((const Gap::Core::igObject *)obj)->release(); }
    static inline void ref(igObjectSlotView *obj) { if (obj != 0) ((const Gap::Core::igObject *)obj)->ref(); }
};
static inline void igObject_Destroy(igObjectSlotView *object) { igObject_Destroy((igObject *)object); }
struct PropertyRoot {
    char pad0[56];
    void *properties;
};
typedef igTDataList<Gap::Gfx::igVisualContext *> LiveContextList;

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

/* "fillMode" */
struct SystemConfig { char pad[56]; void *settings; };

extern "C" float DAT_0048a470[4];
extern "C" float DAT_005607a0[4];
extern "C" float DAT_005607a8[4];
extern "C" int DAT_005607b0[4];
extern "C" float DAT_005607b8[4];
extern "C" float DAT_005607c0[4];
extern "C" float DAT_00560838[4];
struct ShaderSetup {
    char pad[56];
    void *registry;
    void *builder;
};

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
extern "C" igSmartPointer<igObject> FUN_00167130(SlotObject_166fe0 *object);
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
extern "C" int DAT_00560840;
extern "C" void *FUN_00167310(png_structp png, int size);
extern "C" void FUN_00167320(png_structp png, void *storage);
class DW4VC_108_3 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual int vX(int, int, int); };
extern "C" void FUN_00167330(png_structp png, int arg1, int arg2);
extern "C" void FUN_00167380(void);
extern "C" void FUN_00167390(void);
extern "C" void FUN_001673a0(png_structp png_ptr, png_row_infop row_info, png_bytep data);

extern "C" void p2CallDisplayList(p2DisplayList *list);


extern "C" void FUN_00203580(int x, int y, int width, int height, int layout, void *pixels, int flags);
extern "C" void FUN_00203c50(int x, int y, int width, int height, int target, void *pixels, int flags);
extern "C" void FUN_00209cf0(int a, int b, int c, int d, int e, int f, int g);
/* Makes a texture's GS buffers current for `stage`; nonzero on success. */
extern "C" int FUN_0020bb20(P2Texture **textures, int stage, int flag);

extern "C" int DAT_0048a4e0[4];
extern "C" int DAT_0048a4ec[4];
extern "C" int DAT_0048a4f0[4];
extern "C" int DAT_0048acd0[];
extern "C" void FUN_001690d0(Gap::Gfx::igPsx2VisualContext *vc);
extern "C" void FUN_00169260(Gap::Gfx::igPsx2VisualContext *vc, int keepPool);
class DW4VC_524 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual void d101(); virtual void d102(); virtual void d103(); virtual void d104(); virtual void d105(); virtual void d106(); virtual void d107(); virtual void d108(); virtual void d109(); virtual void d110(); virtual void d111(); virtual void d112(); virtual void d113(); virtual void d114(); virtual void d115(); virtual void d116(); virtual void d117(); virtual void d118(); virtual void d119(); virtual void d120(); virtual void d121(); virtual void d122(); virtual void d123(); virtual void d124(); virtual void d125(); virtual void d126(); virtual void d127(); virtual void d128(); virtual void vX(int, void *); };
extern "C" void FUN_00169be0(Gap::Gfx::igPsx2VisualContext *vc, int mode);
#define VRAM_BUFFER_RECORD_SIZE 0x30
#define MIN(a,b) ((a) < (b) ? (a) : (b))
extern "C" void FUN_0016a520(Gap::Gfx::igPsx2VisualContext *vc);
extern "C" void igPsx2ClutRecord_Reset(igPsx2ClutRecord *record);
extern "C" void FUN_0016c650(Gap::Gfx::igPsx2VisualContext *vc, int keepPool);
extern "C" void FUN_0016cc50(Gap::Gfx::igPsx2VisualContext *vc, int mode);
extern "C" void FUN_0016cc60(Gap::Gfx::igPsx2VisualContext *vc);
extern "C" void FUN_0016cd10(Gap::Gfx::igPsx2VisualContext *vc);

extern "C" void Gap__Gfx__igPsx2DisableExt__vfunc_29(igPsx2DisableExt *self, int arg1);
extern "C" int Gap__Gfx__igPsx2DisableExt__vfunc_30(void *self, unsigned int ext);
extern "C" void Gap__Gfx__igPsx2DisableExt__vfunc_31(int arg0, unsigned int arg1, char arg2);

extern "C" long long DAT_005608a0[4];
extern "C" int DAT_005608c0[4];
extern "C" int DAT_005608c4[4];
extern "C" int DAT_005608c8[4];
extern "C" void FUN_0016d910(igPsx2VisualContext *vc, unsigned int count, int first, const float *positions, const float *normals, int (*draw)(...), int (*drawIndexed)(...));
extern "C" void FUN_0016db20(igPsx2VisualContext *vc, int first);
extern "C" void FUN_0017f080(igPsx2VisualContext *vc, int primitive, unsigned int count, int vertexOffset, int primitiveOffset);

/* A statistics capture the registry's STATISTICS_CAPTURE_<n> sections configure (numCapture, startCapture,
 * stringCapture); the visual context keeps them in a list and prints each one's report when it completes. */
struct StatisticsCapture {
    int index;                    /* the n of STATISTICS_CAPTURE_<n> */
    int frameCount;               /* numCapture */
    int startCapture;             /* frames left before the capture starts, counted down past -frameCount */
    igStringObj *name;            /* stringCapture */
    unsigned char active;
    p2Statistics start;           /* +24: the counters when the capture started */
    p2Statistics end;             /* +480: the counters when it completed */
    long long f936;
    char pad944[8];
    StatisticsCapture *next;      /* +952 */
};
/* Prints a completed capture's report. */

extern "C" void FUN_0016e140(Gap::Gfx::igPsx2VertexArray1_1 *array, int sequence);
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
extern "C" void Gap__Gfx__igPsx2DecalExt__vfunc_29(igPsx2DecalExt *self, int context);

extern "C" void Gap__Gfx__igPsx2DecalExt__vfunc_30(igPsx2DecalExt *self, int arg1);
typedef struct ImagePalette {
    char pad0[12];
    int lastIndex;
    char pad10[4];
    unsigned int *colors;
    char pad18[4];
    unsigned char used;
} ImagePalette;
extern "C" void *thunk_memcpy(void *d, const void *s, unsigned int n);
extern "C" void FUN_0016fe00(void *dst, const void *src, unsigned int size);
extern "C" void FUN_0016fe20(void *dst, const void *src, unsigned int size);
extern "C" void Gap__Gfx__igPsx2MultiTextureExt__vfunc_29(igPsx2MultiTextureExt *self, int context);
extern "C" int DAT_004df5e0[];
extern "C" void Gap__Gfx__igPsx2MultiTextureExt__vfunc_30(igPsx2MultiTextureExt *self, int unit, int, int mode);
extern "C" void Gap__Gfx__igPsx2MultiTextureExt__vfunc_31(int a0, int a1, int a2, int a3);
extern "C" void Gap__Gfx__igPsx2MultiTextureExt__vfunc_32(void);
typedef struct A_16fea0 { char p[24]; unsigned int f24; unsigned char f28; char p1[3]; int f32; int f36; int f40; int f44; unsigned char f48; } A_16fea0;
extern "C" void FUN_0016fea0(A_16fea0 *arg0, int arg1, int arg2, int arg3);
extern "C" void Gap__Gfx__igPsx2ScissorExt__vfunc_29(igPsx2ScissorExt *self, int context);
class A_1700f0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void vX(int, int, int, int); };
class B_1700f0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual void d101(); virtual void d102(); virtual void d103(); virtual void d104(); virtual void d105(); virtual void d106(); virtual void d107(); virtual void d108(); virtual void d109(); virtual void d110(); virtual void d111(); virtual void d112(); virtual void d113(); virtual void d114(); virtual void d115(); virtual void d116(); virtual void d117(); virtual void d118(); virtual void d119(); virtual void d120(); virtual void d121(); virtual void d122(); virtual void d123(); virtual void d124(); virtual void d125(); virtual void d126(); virtual void d127(); virtual void d128(); virtual void d129(); virtual void d130(); virtual void d131(); virtual void d132(); virtual void d133(); virtual void d134(); virtual void d135(); virtual void d136(); virtual void d137(); virtual void d138(); virtual void d139(); virtual void d140(); virtual void d141(); virtual void d142(); virtual void d143(); virtual void d144(); virtual void d145(); virtual void d146(); virtual void d147(); virtual void d148(); virtual void d149(); virtual void d150(); virtual void d151(); virtual void d152(); virtual void d153(); virtual void d154(); virtual void d155(); virtual void d156(); virtual void d157(); virtual void d158(); virtual void d159(); virtual void d160(); virtual void d161(); virtual void d162(); virtual void d163(); virtual void d164(); virtual void d165(); virtual void d166(); virtual void d167(); virtual void d168(); virtual void d169(); virtual void d170(); virtual void d171(); virtual void d172(); virtual void d173(); virtual void d174(); virtual void d175(); virtual void d176(); virtual void d177(); virtual void d178(); virtual void d179(); virtual void d180(); virtual void d181(); virtual void d182(); virtual void d183(); virtual void vX(int *, int *, int *, int *); };
extern "C" void Gap__Gfx__igPsx2ScissorExt__vfunc_30(int *arg0, int arg1);
extern "C" unsigned char Gap__Gfx__igPsx2ScissorExt__vfunc_31(igPsx2ScissorExt *self);
extern "C" void Gap__Gfx__igPsx2ScissorExt__vfunc_32(igPsx2ScissorExt *arg0, int arg1, int arg2, int arg3, int arg4);
extern "C" void Gap__Gfx__igPsx2ScissorExt__vfunc_33(igPsx2ScissorExt *self, int *originX, int *originY, int *width, int *height);
extern "C" void igPsx2VisualContext_ResetLight(p2Light *light);
/* The lights enabled in each of the p2 light slots, as the entry's address, or -1 for a free slot. */
extern "C" int *DAT_00560858[4];
extern igMatrix44f g_gfxIdentityMatrix;
#define STR_RELEASE(s) if (s) { int *h_ = (int *)((char *)(s) - 8); if (--h_[1] == 0) StringChunk_ReleaseHeader((StringChunk *)h_[0], (StringTokenHeader *)h_); }
#define POOL() if (!g_stringPool) { StringPool *p_ = (StringPool *)StringPool_Allocate(16); if (p_) p_ = StringPool_Construct(p_); g_stringPool = p_; }

extern "C" long long DAT_00560848[4];

extern "C" int DAT_00560850[4];
extern "C" int DAT_005608cc[4];
extern "C" int DAT_005608d0[4];
extern "C" int DAT_005608d4[4];
extern "C" int DAT_005609c8[4];
extern "C" int DAT_005608dc[4];
extern "C" int DAT_005608e4[4];
extern "C" int DAT_005608e8[4];


extern "C" void igPsx2VisualContext_ResetMaterial(p2Material *material);
extern "C" int DAT_005608f8[4];
extern "C" int DAT_005608fc[4];
extern "C" int DAT_00560900[4];
extern "C" int DAT_00560904[4];
extern "C" int DAT_00560908[4];
typedef struct V4_171cd0 { float x, y, z, w; } V4_171cd0;
typedef struct St { V4_171cd0 a; V4_171cd0 b; V4_171cd0 c; V4_171cd0 d; float e; unsigned f; } St;
#define EQ4(S, FLD, Q, CTR) do { V4_171cd0 *a5; St *v1 = (S); int v0; \
    a5 = &v1->FLD; v0 = 1; if (v1->FLD.x != (Q)->x) v0 = 0; \
    if (v0 != 0) { v0 = 1; if (a5->y != (Q)->y) v0 = 0; } \
    if (v0 != 0) { v0 = 1; if (a5->z != (Q)->z) v0 = 0; } \
    if (v0 != 0) { v0 = 1; if (a5->w != (Q)->w) v0 = 0; } \
    if (v0 != 0) CTR[0] += 1; } while (0)
extern "C" int DAT_0056090c[4];
extern "C" int DAT_00560910;

extern "C" int DAT_00560914[4];

extern "C" int DAT_00560918[4];


typedef struct L_172600 { int p0; int p4; int count; int cap; char *data; } L_172600;
#define PUSH(f) do { int n; L_172600 *l; int v; l = arg0->f; v = count_of_172600(l); if (v != 0) { n = l->count; if (n < l->cap) { l->count = v + 1; } else { ((Gap::Core::igDataList *)l)->resizeAndSetCount(n + 1, 64); } igMatrix44f_Copy((float *)(l->data + (n << 6)), (const float *)(l->data + ((n - 1) << 6))); } } while (0)
typedef struct St_172b00 { char pad0[8]; int n; int cap; char *data; } St_172b00;
#define SET(l, m) { \
    St_172b00 *s = (l); \
    int n = s->n; \
    int n1; \
    if (n == 0) { \
        n1 = n + 1; \
        if (n < s->cap) s->n = n_of(s) + 1; \
        else ((Gap::Core::igDataList *)s)->resizeAndSetCount(n1, 0x40); \
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
        else ((Gap::Core::igDataList *)s)->resizeAndSetCount(n1, 0x40); \
        igMatrix44f_Copy((float *)(s->data + (n << 6)), (const float *)(m)); \
    } else { \
        igMatrix44f_Copy((float *)(s->data + ((n_of(s) - 1) << 6)), (const float *)(m)); \
    } }
extern "C" int DAT_0056091c[4];
extern "C" void FUN_00174090(Gap::Gfx::igPsx2VisualContext *vc);
struct Obj;
extern "C" int DAT_00560920[4];
extern "C" long long DAT_005608a8[4];
extern "C" int DAT_00560924[4];
extern "C" int DAT_00560928[4];
extern "C" int DAT_00560968[4];
extern "C" int DAT_00560948[8];
/* The blend-equation tables: for each source blend function, the rows of its destination blend functions. */
extern "C" Psx2BlendEquation *DAT_0048ac00[4];
extern "C" int DAT_0056098c;
extern "C" int DAT_00560998[4];
extern "C" int DAT_0056099c[4];

extern "C" int DAT_0048a500[4];
extern "C" void FUN_001747f0(Gap::Gfx::igPsx2VisualContext *vc);
extern "C" int DAT_005609a0[4];
extern "C" long long DAT_005608b8[4];
extern "C" void FUN_00174950(Gap::Gfx::igPsx2VisualContext *vc, int enable);

extern "C" long long DAT_005608b0[2];
extern "C" int DAT_0048a530[4];
extern "C" int DAT_0048a538[4];
extern "C" int DAT_005609a4[4];
extern "C" int DAT_005609a8[4];
extern "C" int DAT_005609ac[4];
extern "C" int DAT_005609b0[4];
extern "C" int DAT_005609b4[4];

extern "C" int DAT_0048a540[4];
extern "C" void FUN_00174db0(Gap::Gfx::igPsx2VisualContext *vc);
extern "C" int DAT_005609b8[4];

extern "C" int DAT_005609bc[4];

extern "C" int DAT_005609c0[4];
extern "C" int DAT_005609c4[4];
extern "C" int DAT_005609cc[4];

extern "C" int DAT_0048a560[4];
extern "C" int DAT_005609d0[4];
extern "C" int DAT_005609d4[4];

extern "C" int DAT_005609d8[4];
extern "C" int DAT_005609dc[4];
extern "C" int DAT_005609e0[4];

extern "C" int DAT_0048a520[4];
extern "C" int DAT_005609e4[4];
extern "C" int DAT_005609e8[4];

extern "C" int DAT_005609ec[4];

extern "C" int DAT_005609f0[4];
extern "C" int DAT_005609f4[4];

extern "C" int DAT_005609f8;
extern "C" int DAT_005609fc[4];

extern "C" int DAT_00560a00[4];

extern "C" int DAT_00560a04[4];
extern "C" void FUN_001757c0(igPsx2VisualContext *vc, int passCount);
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
extern "C" void Gap__Bec__ParticleArray__vfunc_27(igParticleArrayRefs *self);
extern "C" long long DAT_00560660[4];
extern "C" void Gap__Gfx__igPsx2ParticleArray__vfunc_29(PA_175ba0 *arg0);
struct PA_175c70;
struct PA_175c70 { int vt; int pad[3]; int n; };
extern "C" int Gap__Gfx__igPsx2ParticleArray__vfunc_24(PA_175c70 *arg0, int arg1);
#include "dw4/p2/psx2ParticleFormat.h"
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
extern "C" void Gap__Gfx__igPsx2ParticleArray__vfunc_35(igPsx2ParticleArray *self, float fparg0);
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
extern "C" void igPsx2PointSpriteExt_SetSpriteSize(igPsx2PointSpriteExt *self, float farg0);
extern "C" void igPsx2PointSpriteExt_BeginSprites(UCodeState *state);
extern "C" void igPsx2PointSpriteExt_EndSprites(igPsx2PointSpriteExt *self);
extern "C" void igPsx2PointSpriteExt_ConfigureVertexArray(O176a50 *arg0, V96 *arg1, int *arg2, int arg3, int arg4);
extern "C" int FUN_00176ba0(void *arg0);
extern "C" void igPsx2PointSpriteExt_SetPosition(igPsx2PointSpriteExt *self, int arg1, void *arg2);
extern "C" void igPsx2PointSpriteExt_GetPosition(igPsx2PointSpriteExt *self, int arg1, void *arg2);
extern "C" void igPsx2PointSpriteExt_SetColorPacked(igPsx2PointSpriteExt *self, int arg1, int arg2);
extern "C" void igPsx2PointSpriteExt_SetColor(igPsx2PointSpriteExt *self, int arg1, int arg2);
extern "C" void igPsx2PointSpriteExt_GetColorPacked(igPsx2PointSpriteExt *self, unsigned int arg1);
extern "C" void igPsx2PointSpriteExt_GetColor(igPsx2PointSpriteExt *self, unsigned int arg1);
extern "C" void igPsx2PointSpriteExt_SetTextureCoord(W_1767c0 *arg0, int arg1, int arg2, float *arg3);
extern "C" void igPsx2PointSpriteExt_GetTextureCoord(igPsx2PointSpriteExt *self, int arg1, int arg2);
extern "C" void igPsx2PointSpriteExt_GetTextureCoordPointer(igPsx2PointSpriteExt *self, int arg1, int arg2);
extern "C" void igPsx2PointSpriteExt_SetRadian(igPsx2PointSpriteExt *self);
extern "C" void igPsx2PointSpriteExt_GetRadian(igPsx2PointSpriteExt *self);
extern "C" int FUN_00177010(igPsx2VisualContext *vc, int *arg1, int *arg2, int arg3, int arg4);
extern "C" int FUN_001774c0(igPsx2VisualContext *vc, Gap::Gfx::igPsx2VertexStream *stream, bool *useTexture);

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

extern "C" int DAT_0048ac40[];
extern "C" int DAT_0048acb0[];
extern "C" int DAT_0048ac70[4];
extern "C" int DAT_0048acf0[];
extern "C" int DAT_00560a5c[8];
extern "C" void igPsx2TextureRecord_Reset(igPsx2TextureRecord *record);
extern "C" void igPsx2TextureRecord_ReleaseImages(igPsx2TextureRecord *record);
extern "C" int igPsx2TextureFormat_GetP2Format(int format);
extern "C" int DAT_00560a08[8];
extern "C" unsigned int DAT_0048aca0[];
extern "C" int DAT_0048acc0[];
extern "C" bool igPsx2VisualContext_ApplyTextureState(Gap::Gfx::igPsx2VisualContext *vc, igPsx2TextureRecord *record, int stage, igPsx2ClutRecord *clut, int clutHandle);
class TextureImageView260 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual int vX(int, int, int, int); };
extern "C" int DAT_00560a28[4];
extern "C" int DAT_00560a2c[4];
extern "C" int DAT_00560a34[4];
extern "C" int DAT_00560a38[4];
extern "C" int DAT_00560a3c[4];
extern "C" int DAT_00560a7c[8];
extern "C" int DAT_00560a9c[8];
extern "C" int igPsx2VisualContext_CreateSharedClut(Gap::Gfx::igPsx2VisualContext *vc, int intensityBits, int alphaBits, int *palette);
struct R_17cef0 { int w0; int refs; };
class M_17cef0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void *meta(); };
struct O_17cef0 { char pad[20]; M_17cef0 *m; R_17cef0 *b; R_17cef0 *a; };
extern "C" void Gap__Gfx__igPsx2UserUCodeExt__vfunc_29(O_17cef0 *arg0, M_17cef0 *arg1);
extern "C" bool FUN_0017e590(igPsx2VisualContext *vc, igVertexDataList *vertexData, int firstVertex, int *spriteSizes, int *texCoords);

extern "C" void FUN_0017e980(igPsx2VisualContext *h, igVertexDataList *vertexData, int firstVertex);
extern "C" bool FUN_0017df40(igPsx2VisualContext *vc, igVertexDataList *vertexData, int firstVertex, int *positions, int *normals, int *colors, int *texCoords);
extern "C" void FUN_0017eb90(igPsx2VisualContext *vc, igVertexDataList *vertexData, int primitive, int count, int firstVertex, int stripOffset, bool useTexture);
struct Rc_17f2b0 : public igObject { };
extern "C" void FUN_0017fd80(Gap::Core::igUnsignedIntList **colors, Gap::Core::igUnsignedIntList **converted, int alphaRange);
extern "C" void FUN_00180060(igPsx2VisualContext *vc);
extern "C" void FUN_00180ab0(igPsx2VisualContext *vc, igVertexData *srcPositions, igVertexData *outPositions, igVertexData *srcNormals, igVertexData *outNormals, igVertexData *weights, igVertexData *indices, int weightCount);
extern "C" void FUN_001805a0(igPsx2VisualContext *vc, Gap::Gfx::igPsx2VertexStream *stream, int count);
extern "C" int igPsx2UserUCodeExt_GetMeta(void);
extern "C" int igContextExt_UpdateFrameRateDisplay(void);
extern "C" int igPsx2PointSpriteExt_GetMeta(void);
extern "C" int igPsx2ParticleArray_GetMeta(void);
extern "C" float Gap__Bec__ParticleArray__vfunc_31(ParticleArray *arg0);
extern "C" float Gap__Bec__ParticleArray__vfunc_34(ParticleArray *arg0);
extern "C" int igPsx2ScissorExt_GetMeta(void);
extern "C" igMetaObject *igPsx2MultiTextureExt_GetMeta(void);
extern "C" int igPsx2DecalExt_GetMeta(void);
extern "C" igMetaObject *igPsx2BlendEquationExt_GetMeta(void);
extern "C" igMetaObject *igPsx2DisableExt_GetMeta(void);
extern "C" int igVisualContextCapabilityManager_GetMeta(void);
extern "C" int igPointSpriteExt_GetMeta(void);
extern "C" int FUN_00180f10(void);
extern "C" int igParticleArray_GetMeta(void);
extern "C" void Gap__Bec__ParticleArray__vfunc_32(ParticleArray *arg0, float arg1);
extern "C" void Gap__Bec__ParticleArray__vfunc_33(ParticleArray *arg0, float arg1);
extern "C" int igGenericCapabilityManager_GetMeta(void);
extern "C" void FUN_00180fa0(igParticleFormat *self);
extern "C" igMetaObject *FUN_00180fd0(void);
extern "C" int igPsx2LongList_GetMeta(void);
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
extern "C" void ParticleArray_EvaluateLinearVec4(float *dst, void *arg1, void *arg2, float fparg0);
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
struct A_1830b0 { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void v144(unsigned, void *); virtual void d35(); virtual void v152(unsigned, int); };
struct B_1830b0 { virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4(); virtual void a5(); virtual void a6(); virtual void a7(); virtual void a8(); virtual void a9(); virtual void a10(); virtual void a11(); virtual void a12(); virtual void a13(); virtual void a14(); virtual void a15(); virtual void a16(); virtual void a17(); virtual void a18(); virtual void a19(); virtual void a20(); virtual void a21(); virtual void a22(); virtual void a23(); virtual void a24(); virtual void a25(); virtual void a26(); virtual void v116(unsigned, void *); virtual void b0(); virtual void b1(); virtual void b2(); virtual void b3(); virtual void b4(); virtual void b5(); virtual void b6(); virtual void b7(); virtual void b8(); virtual void b9(); virtual void b10(); virtual void v164(unsigned, int); virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3(); virtual void c4(); virtual void c5(); virtual void c6(); virtual void c7(); virtual void c8(); virtual void c9(); virtual void c10(); virtual void v212(unsigned, float); };
extern "C" void FUN_001830b0(int arg0, unsigned arg1, int arg2, int arg3, igObject *arg4, A_1830b0 *arg5, float fparg0);
struct A_1836f0 { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void v144(unsigned, void *); virtual void d35(); virtual void v152(unsigned, int); char pad[20]; igObject *f24; };
struct B_1836f0 { virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4(); virtual void a5(); virtual void a6(); virtual void a7(); virtual void a8(); virtual void a9(); virtual void a10(); virtual void a11(); virtual void a12(); virtual void a13(); virtual void a14(); virtual void a15(); virtual void a16(); virtual void a17(); virtual void a18(); virtual void a19(); virtual void a20(); virtual void a21(); virtual void a22(); virtual void a23(); virtual void a24(); virtual void a25(); virtual void a26(); virtual void v116(unsigned, void *); virtual void b0(); virtual void b1(); virtual void b2(); virtual void b3(); virtual void b4(); virtual void b5(); virtual void b6(); virtual void b7(); virtual void b8(); virtual void b9(); virtual void b10(); virtual void v164(unsigned, int); virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3(); virtual void c4(); virtual void c5(); virtual void c6(); virtual void c7(); virtual void c8(); virtual void c9(); virtual void c10(); virtual void v212(unsigned, float); };
extern "C" void FUN_001836f0(int arg0, unsigned arg1, int arg2, int arg3, igObject *arg4, A_1836f0 *arg5, float fparg0);
class MeshTarget { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual int v116(unsigned, igVec3f *); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual int v144(unsigned, igVec3f *); virtual void d35(); virtual int v152(unsigned, int); virtual void d37(); virtual void d38(); virtual int v164(unsigned, int); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual int v220(unsigned, igVec2f);
 int f4; char pad8[16]; MeshTarget *f24; };
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
struct A_184cc0 { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void v144(unsigned, void *); virtual void d35(); virtual void v152(unsigned, int); char pad[20]; igObject *f24; };
struct B_184cc0 { virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4(); virtual void a5(); virtual void a6(); virtual void a7(); virtual void a8(); virtual void a9(); virtual void a10(); virtual void a11(); virtual void a12(); virtual void a13(); virtual void a14(); virtual void a15(); virtual void a16(); virtual void a17(); virtual void a18(); virtual void a19(); virtual void a20(); virtual void a21(); virtual void a22(); virtual void a23(); virtual void a24(); virtual void a25(); virtual void a26(); virtual void v116(unsigned, void *); virtual void b0(); virtual void b1(); virtual void b2(); virtual void b3(); virtual void b4(); virtual void b5(); virtual void b6(); virtual void b7(); virtual void b8(); virtual void b9(); virtual void b10(); virtual void v164(unsigned, int); virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3(); virtual void c4(); virtual void c5(); virtual void c6(); virtual void c7(); virtual void c8(); virtual void c9(); virtual void c10(); virtual void v212(unsigned, float); };
extern "C" void FUN_00184cc0(int arg0, unsigned arg1, int arg2, int arg3, igObject *arg4, A_184cc0 *arg5, float fparg0);
class B_185340 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual int v116(unsigned, int *); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual int v144(unsigned, int *); virtual void d35(); virtual int v152(unsigned, int); virtual void d37(); virtual void d38(); virtual int v164(unsigned, int); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual int v212(unsigned, float);
 int f4; char pad8[16]; B_185340 *f24; };
extern "C" void FUN_00185340(int arg0, unsigned arg1, int arg2, int arg3, B_185340 *arg4, B_185340 *arg5, float fparg0);
class B_185670 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual int v116(unsigned, igVec3f *); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual int v144(unsigned, igVec3f *); virtual void d35(); virtual int v152(unsigned, int); virtual void d37(); virtual void d38(); virtual int v164(unsigned, int); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual int v220(unsigned, igVec2f);
 int f4; char pad8[16]; B_185670 *f24; };
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
struct A_185c80 { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void v144(unsigned, void *); virtual void d35(); virtual void v152(unsigned, int); char pad[20]; igObject *f24; };
struct B_185c80 { virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4(); virtual void a5(); virtual void a6(); virtual void a7(); virtual void a8(); virtual void a9(); virtual void a10(); virtual void a11(); virtual void a12(); virtual void a13(); virtual void a14(); virtual void a15(); virtual void a16(); virtual void a17(); virtual void a18(); virtual void a19(); virtual void a20(); virtual void a21(); virtual void a22(); virtual void a23(); virtual void a24(); virtual void a25(); virtual void a26(); virtual void v116(unsigned, void *); virtual void b0(); virtual void b1(); virtual void b2(); virtual void b3(); virtual void b4(); virtual void b5(); virtual void b6(); virtual void b7(); virtual void b8(); virtual void b9(); virtual void b10(); virtual void v164(unsigned, int); virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3(); virtual void c4(); virtual void c5(); virtual void c6(); virtual void c7(); virtual void c8(); virtual void c9(); virtual void c10(); virtual void v212(unsigned, float); };
extern "C" void FUN_00185c80(int arg0, unsigned arg1, int arg2, int arg3, igObject *arg4, A_185c80 *arg5, float fparg0);
class VertexSink { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual int v116(unsigned, float *); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual int v144(unsigned, float *); virtual void d35(); virtual int v152(unsigned, int); virtual void d37(); virtual void d38(); virtual int v164(unsigned, int); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual int v212(unsigned, float); virtual void d52(); virtual int v220(unsigned, igVec2f);
 int f4; char pad8[16]; VertexSink *f24; };
extern "C" void FUN_00185fb0(int arg0, unsigned arg1, int arg2, int arg3, VertexSink *arg4, VertexSink *arg5, float fparg0);
/* matching construct: dummy virtual slots so the vN() calls dispatch through the retail vtable offsets (receiver classes of A_186300 and B_186300 are not established) */
struct A_186300 { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void v144(unsigned, void *); virtual void d35(); virtual void v152(unsigned, int); char pad[20]; igObject *f24; };
struct B_186300 { virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4(); virtual void a5(); virtual void a6(); virtual void a7(); virtual void a8(); virtual void a9(); virtual void a10(); virtual void a11(); virtual void a12(); virtual void a13(); virtual void a14(); virtual void a15(); virtual void a16(); virtual void a17(); virtual void a18(); virtual void a19(); virtual void a20(); virtual void a21(); virtual void a22(); virtual void a23(); virtual void a24(); virtual void a25(); virtual void a26(); virtual void v116(unsigned, void *); virtual void b0(); virtual void b1(); virtual void b2(); virtual void b3(); virtual void b4(); virtual void b5(); virtual void b6(); virtual void b7(); virtual void b8(); virtual void b9(); virtual void b10(); virtual void v164(unsigned, int); virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3(); virtual void c4(); virtual void c5(); virtual void c6(); virtual void c7(); virtual void c8(); virtual void c9(); virtual void c10(); virtual void v212(unsigned, float); };
extern "C" void FUN_00186300(int arg0, unsigned arg1, int arg2, int arg3, igObject *arg4, A_186300 *arg5, float fparg0);
struct PackedVertexWriter { virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4(); virtual void a5(); virtual void a6(); virtual void a7(); virtual void a8(); virtual void a9(); virtual void a10(); virtual void a11(); virtual void a12(); virtual void a13(); virtual void a14(); virtual void a15(); virtual void a16(); virtual void a17(); virtual void a18(); virtual void a19(); virtual void a20(); virtual void a21(); virtual void a22(); virtual void a23(); virtual void a24(); virtual void a25(); virtual void a26();  virtual void v116(unsigned, int *); virtual void b0(); virtual void b1(); virtual void b2(); virtual void b3(); virtual void b4(); virtual void b5(); virtual void b6(); virtual void b7(); virtual void b8(); virtual void b9(); virtual void b10();  virtual void v164(unsigned, int); virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3(); virtual void c4(); virtual void c5(); virtual void c6(); virtual void c7(); virtual void c8(); virtual void c9(); virtual void c10(); virtual void c11(); virtual void c12();  virtual void v220(unsigned, igVec2f); int refs; };
struct VertexArrayWriter { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33();  virtual void v144(unsigned, int *); virtual void d35(); virtual void v152(unsigned, int); int pad[5]; PackedVertexWriter *f24; };
extern "C" void FUN_00186660(int arg0, unsigned int arg1, int arg2, int arg3, PackedVertexWriter *arg4, VertexArrayWriter *arg5, float fparg0);
extern "C" LiveContextList *DAT_00560758;

#endif
