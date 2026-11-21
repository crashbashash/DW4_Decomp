#ifndef DW4_SCENE_GRAPH_LIBRARY_H
#define DW4_SCENE_GRAPH_LIBRARY_H

#include "dw4/support/reflected.h"
#include "dw4/core/igSmartPointer.h"
#include "dw4/core/igTDataList.h"
#include "dw4/core/igMemoryPoolView.h"
#include "dw4/gfx/igVertexArrayLock.h"
#include "dw4/maths/igVec3f.h"
#include "dw4/core/igobject_release.h"
#include "dw4/support/ClassRegistration.h"
#include "dw4/scenegraph/AnimationPools.h"
#include "dw4/scenegraph/igActor.h"
#include "dw4/enbaya/Enbaya.h"
#include "dw4/scenegraph/igActorInfo.h"
#include "dw4/scenegraph/igActorList.h"
#include "dw4/scenegraph/igAnimationDatabase.h"
#include "dw4/scenegraph/igAppearanceList.h"
#include "dw4/scenegraph/igAttrSet.h"
#include "dw4/scenegraph/igBoundingBoxesMaker.h"
#include "dw4/scenegraph/igCamera.h"
#include "dw4/scenegraph/igEnbayaTransformSource.h"
#include "dw4/scenegraph/igFrustCullTraversal.h"
#include "dw4/scenegraph/igGeometry.h"
#include "dw4/scenegraph/igGeometryList.h"
#include "dw4/scenegraph/igGraphPath.h"
#include "dw4/scenegraph/igGroup.h"
#include "dw4/scenegraph/igIntersectTraversal.h"
#include "dw4/scenegraph/igLightSet.h"
#include "dw4/scenegraph/igLightStateSet.h"
#include "dw4/scenegraph/igLod.h"
#include "dw4/scenegraph/igModelViewMatrixBoneSelect.h"
#include "dw4/scenegraph/igNode.h"
#include "dw4/scenegraph/igNodeList.h"
#include "dw4/scenegraph/igPlanarShadowShader.h"
#include "dw4/scenegraph/igProbe.h"
#include "dw4/scenegraph/igProjectiveShadowShader.h"
#include "dw4/scenegraph/igSceneInfo.h"
#include "dw4/scenegraph/igSegment.h"
#include "dw4/scenegraph/igSwitch.h"
#include "dw4/scenegraph/igTransform.h"
#include "dw4/scenegraph/igTransformList.h"
#include "dw4/scenegraph/igTransformRecorder.h"
#include "dw4/scenegraph/igAnimationCombiner.h"
#include "dw4/scenegraph/igAnimationState.h"
#include "dw4/scenegraph/igAppearance.h"
#include "dw4/scenegraph/igAttrStackManager.h"
#include "dw4/scenegraph/igBitMask.h"
#include "dw4/scenegraph/igEnbayaAnimationSource.h"
#include "dw4/scenegraph/igObjectPool.h"
#include "dw4/scenegraph/igTransformSource.h"
#include "dw4/scenegraph/igTraversal.h"
#include "dw4/gfx/igVertexArray2.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "dw4/support/softfloat.h"
#include "dw4/gfx/igVisualContext.h"
#include "dw4/attrs/igVertexBlendMatrixListAttr.h"
#include "dw4/attrs/igVertexBlendMatrixAttr.h"
#include "dw4/attrs/igTimeAttr.h"
#include "dw4/attrs/igTextureStateAttr.h"
#include "dw4/attrs/igTextureMatrixAttr.h"
#include "dw4/attrs/igTextureList.h"
#include "dw4/attrs/igTextureBindAttr.h"
#include "dw4/attrs/igTextureAttr.h"
#include "dw4/core/igStringObj.h"
#include "dw4/core/igResult.h"
#include "dw4/core/igRegistry.h"
#include "dw4/attrs/igProjectionMatrixAttr.h"
#include "dw4/core/igObjectSystem.h"
#include "dw4/core/igObjectList.h"
#include "dw4/attrs/igObjectList.h"
#include "dw4/core/igObject.h"
#include "dw4/datapump/igNonRefCountedObjectStack.h"
#include "dw4/core/igNamedObject.h"
#include "dw4/attrs/igModelViewMatrixAttr.h"
#include "dw4/core/igMetaObject.h"
#include "dw4/core/igMetaField.h"
#include "dw4/core/igMemoryPoolContext.h"
#include "dw4/attrs/igMatrixOptStateAttr.h"
#include "dw4/maths/igMatrix44f.h"
#include "dw4/attrs/igLightingStateAttr.h"
#include "dw4/attrs/igLightStateAttr.h"
#include "dw4/attrs/igLightAttr.h"
#include "dw4/gfx/igImage.h"
#include "dw4/gfx/GfxMetaEnums.h"
#include "dw4/attrs/igGeometrySetAttr.h"
#include "dw4/attrs/igGeometryAttr.h"
#include "dw4/attrs/igDisplayListAttr.h"
#include "dw4/core/igDataLists.h"
#include "dw4/support/list-services.h"
#include "dw4/core/igStringRef.h"
#include "dw4/attrs/igColorAttr.h"
#include "dw4/attrs/igClearAttr.h"
#include "dw4/attrs/igBlendStateAttr.h"
#include "dw4/attrs/igBlendMatrixPaletteAttr.h"
#include "dw4/attrs/igBlendFunctionAttr.h"
#include "dw4/attrs/igAttrList.h"
#include "dw4/cri/sndf.h"
#include "dw4/cri/cri_adxt.h"
#include "dw4/game/beModelCtrlInfo.h"
#include "dw4/game/beHitLandModelTraversal.h"
#include "dw4/core/StringPool.h"
#include "dw4/game/ParticleTimer.h"
#include "dw4/game/ParticleInfo.h"
#include "dw4/core/igUnsignedIntList.h"
#include "dw4/core/igObjectRefMetaField.h"
#include "dw4/core/igMetaObjectList.h"
#include "dw4/maths/igMathConstants.h"
#include "dw4/core/igIntList.h"
#include "dw4/core/igInfo.h"
#include "dw4/maths/igAABox.h"
#include "dw4/core/igBoolMetaField.h"
#include "dw4/core/igCharArrayMetaField.h"
#include "dw4/core/igCharMetaField.h"
#include "dw4/scenegraph/igCommonTraversal.h"
#include "dw4/core/igDirectory.h"
#include "dw4/core/igDoubleList.h"
#include "dw4/core/igDoubleMetaField.h"
#include "dw4/core/igDriverDatabase.h"
#include "dw4/core/igEnumMetaField.h"
#include "dw4/core/igFile.h"
#include "dw4/core/igFloatList.h"
#include "dw4/core/igFloatMetaField.h"
#include "dw4/core/igIntMetaField.h"
#include "dw4/core/igLongList.h"
#include "dw4/core/igLongMetaField.h"
#include "dw4/core/igMemory.h"
#include "dw4/core/igMemoryPool.h"
#include "dw4/core/igMetaEnum.h"
#include "dw4/core/igNamedObjectList.h"
#include "dw4/core/igObjectDirEntry.h"
#include "dw4/core/igObjectStringMap.h"
#include "dw4/core/igPointerList.h"
#include "dw4/core/igPointerListList.h"
#include "dw4/core/igRawRefMetaField.h"
#include "dw4/maths/igRay.h"
#include "dw4/maths/igRayList.h"
#include "dw4/core/igResource.h"
#include "dw4/core/igStringMetaField.h"
#include "dw4/core/igStringObjList.h"
#include "dw4/core/igStringRefList.h"
#include "dw4/core/igUnsignedCharArrayMetaField.h"
#include "dw4/core/igUnsignedCharList.h"
#include "dw4/core/igUnsignedCharMetaField.h"
#include "dw4/core/igUnsignedLongMetaField.h"
#include "dw4/core/igUnsignedShortList.h"
#include "dw4/maths/igVec3fList.h"
#include "dw4/maths/igVec3fMetaField.h"
#include "dw4/maths/igVec4f.h"
#include "dw4/attrs/igVertexBlendStateAttr.h"
#include "dw4/maths/igVolume.h"
#include "dw4/core/internalNonRefCountedObjectList.h"

class ForwardTarget { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual int vX(void *); };
struct TraversalNodeView { char pad[24]; int _id; };
typedef void (*igMetaObjectCallback)();

extern "C" void FUN_0019fdd0(void);




#include "dw4/maths/igMatrix44fMetaField.h"
#include "dw4/maths/igMathOperatorTables.h"
#include "dw4/core/igMemoryRefMetaField.h"
#include "dw4/core/igUnsignedIntMetaField.h"
#include "dw4/maths/igVec4fMetaField.h"
#include "dw4/support/emptyString.h"
#include "dw4/attrs/igAlphaFunctionAttr.h"
#include "dw4/attrs/igAlphaStateAttr.h"
#include "dw4/attrs/igBlendMatricesAttr.h"
#include "dw4/attrs/igColorMaskAttr.h"
#include "dw4/attrs/igCullFaceAttr.h"
#include "dw4/attrs/igDepthStateAttr.h"
#include "dw4/attrs/igGenericAttrDefaultManager.h"
#include "dw4/attrs/igGeometryMaskAttr.h"
#include "dw4/attrs/igMultiPassStateAttr.h"
#include "dw4/attrs/igPixelPipelineModeAttr.h"
#include "dw4/attrs/igRenderDestinationAttr.h"
#include "dw4/attrs/igStencilFunctionAttr.h"
#include "dw4/attrs/igTexGenMatrixAttr.h"
#include "dw4/attrs/igTextureCoordSourceAttr.h"
#include "dw4/attrs/igTextureFunctionAttr.h"
#include "dw4/attrs/igTextureMatrixStateAttr.h"
#include "dw4/attrs/igVisualContextAttrDefaultManager.h"
#include "dw4/attrs/igAttrDefaultManager.h"
#include "dw4/attrs/igAttrListList.h"
#include "dw4/attrs/igBlendMatrixPaletteAttrList.h"
#include "dw4/attrs/igClippingStateAttr.h"
#include "dw4/attrs/igCopyRenderDestinationAttr.h"
#include "dw4/attrs/igDepthWriteStateAttr.h"
#include "dw4/attrs/igLightList.h"
#include "dw4/attrs/igLightStateAttrList.h"
#include "dw4/attrs/igModelViewMatrixAttrList.h"
#include "dw4/attrs/igNormalizeNormalsStateAttr.h"
#include "dw4/attrs/igRenderListAttr.h"
#include "dw4/attrs/igSetRenderDestinationAttr.h"
#include "dw4/attrs/igStencilStateAttr.h"
#include "dw4/attrs/igTextureCubeAttr.h"
#include "dw4/attrs/igTextureUnloadAttr.h"
#include "dw4/attrs/igViewportAttr.h"
#include "dw4/datapump/igDataPumpInfo.h"
#include "dw4/datapump/igLongStack.h"
#include "dw4/datapump/igBoolObject.h"
#include "dw4/datapump/igFloatObject.h"
#include "dw4/datapump/igIntObject.h"
#include "dw4/datapump/igMatrixObject.h"
#include "dw4/datapump/igMatrixStack.h"
#include "dw4/datapump/igNonRefCountedMatrixObjectList.h"
#include "dw4/gfx/igCapabilityManager.h"
#include "dw4/maths/igVolumeList.h"
#include "dw4/scenegraph/igQuaternionfList.h"
#include "dw4/gfx/igGenericCapabilityManager.h"
#include "dw4/gfx/igVisualContextCapabilityManager.h"
#include "dw4/datapump/igCompressVec.h"
extern igMetaObject *g_igActorInfo_metaObject;
extern igMetaObject *g_igActorList_metaObject;
extern igMetaObject *g_igAnimation_metaObject;
extern igMetaObject *g_igAnimationBinding_metaObject;
extern igMetaObject *g_igAnimationBindingList_metaObject;
extern igMetaObject *g_igAnimationCombiner_metaObject;
extern igMetaObject *g_igAnimationCombinerBoneInfo_metaObject;
extern igMetaObject *g_igAnimationCombinerBoneInfoList_metaObject;
extern igMetaObject *g_igAnimationCombinerBoneInfoListList_metaObject;
extern igMetaObject *g_igAnimationCombinerBoneInfoPool_metaObject;
extern igMetaObject *g_igAnimationCombinerList_metaObject;
extern igMetaObject *g_igAnimationHierarchy_metaObject;
extern igMetaObject *g_igAnimationList_metaObject;
extern igMetaObject *g_igAnimationModifier_metaObject;
extern igMetaObject *g_igAnimationModifierList_metaObject;
extern igMetaObject *g_igAnimationSequence_metaObject;
extern igMetaObject *g_igAnimationState_metaObject;
extern igMetaObject *g_igAnimationStateList_metaObject;
extern igMetaObject *g_igAnimationStatePool_metaObject;
extern igMetaObject *g_igAnimationSystem_metaObject;
extern igMetaObject *g_igAnimationTrack_metaObject;
extern igMetaObject *g_igAnimationTrackList_metaObject;
extern igMetaObject *g_igAnimationTransitionDefinition_metaObject;
extern igMetaObject *g_igAnimationTransitionDefinitionList_metaObject;
extern igMetaObject *g_igAnimationTransitionParams_metaObject;
extern igMetaObject *g_igAnimationTransitionPoint_metaObject;
extern igMetaObject *g_igAnimationTransitionPointList_metaObject;
extern igMetaObject *g_igAppearance_metaObject;
extern igMetaObject *g_igAttrStack_metaObject;
extern igMetaObject *g_igAttrStackList_metaObject;
extern igMetaObject *g_igAttrStackManager_metaObject;
extern igMetaObject *g_igBillboard_metaObject;
extern igMetaObject *g_igBitMask_metaObject;
extern igMetaObject *g_igBlendListRecord_metaObject;
extern igMetaObject *g_igBlendMatricesAttrPool_metaObject;
extern igMetaObject *g_igBlendMatrixSelect_metaObject;
extern igMetaObject *g_igBoundingBoxesMaker_metaObject;
extern igMetaObject *g_igCompileTraversal_metaObject;
extern igMetaObject *g_igCompiledTransform_metaObject;
extern igMetaObject *g_igCompiledTransformList_metaObject;
extern igMetaObject *g_igCompressedAnimationSequenceQS_metaObject;
extern igMetaObject *g_igCompressedTransformSequence1_5Data_metaObject;
extern igMetaObject *g_igEnbayaAnimationSource_metaObject;
extern igMetaObject *g_igEnbayaAnimationState_metaObject;
extern igMetaObject *g_igEnbayaContextPool_metaObject;
extern igMetaObject *g_igEnvironmentMapShader2_metaObject;
extern igMetaObject *g_igEnvironmentMapShader2List_metaObject;
extern igMetaObject *g_igFrustCullTraversal_metaObject;
extern igMetaObject *g_igGeometryList_metaObject;
extern igMetaObject *g_igGraphPath_metaObject;
extern igMetaObject *g_igGraphPathList_metaObject;
extern igMetaObject *g_igIniShaderFactory_metaObject;
extern igMetaObject *g_igInterpretedShaderData_metaObject;
extern igMetaObject *g_igLightStateAttrPool_metaObject;
extern igMetaObject *g_igMatrixObjectPool_metaObject;
extern igMetaObject *g_igModelViewMatrixAttrPool_metaObject;
extern igMetaObject *g_igModelViewMatrixBoneSelect_metaObject;
extern igMetaObject *g_igModelViewMatrixBoneSelectListSg_metaObject;
extern igMetaObject *g_igNode_metaObject;
extern igMetaObject *g_igNodeList_metaObject;
extern igMetaObject *g_igNodeListList_metaObject;
extern igMetaObject *g_igNonRefCountedAttrStackManagerList_metaObject;
extern igMetaObject *g_igNonRefCountedNodeList_metaObject;
extern igMetaObject *g_igNonRefCountedTransformList_metaObject;
extern igMetaObject *g_igObjectPool_metaObject;
extern igMetaObject *g_igOverrideAttrSet_metaObject;
extern igMetaObject *g_igPlanarShadowShader_metaObject;
extern igMetaObject *g_igProbe_metaObject;
extern igMetaObject *g_igProjectionMatrixAttrPool_metaObject;
extern igMetaObject *g_igProjectiveShadowShader_metaObject;
extern igMetaObject *g_igPsx2EnvironmentMapShader_metaObject;
extern igMetaObject *g_igRenderPackage_metaObject;
extern igMetaObject *g_igRenderPackageList_metaObject;
extern igMetaObject *g_igRenderPackagePool_metaObject;
extern igMetaObject *g_igSegment_metaObject;
extern igMetaObject *g_igShaderData_metaObject;
extern igMetaObject *g_igShaderFactory_metaObject;
extern igMetaObject *g_igShaderFactoryList_metaObject;
extern igMetaObject *g_igShaderInfo_metaObject;
extern igMetaObject *g_igShaderProcessor_metaObject;
extern igMetaObject *g_igSkeleton_metaObject;
extern igMetaObject *g_igSkeletonBoneInfo_metaObject;
extern igMetaObject *g_igSkeletonBoneInfoList_metaObject;
extern igMetaObject *g_igSkeletonList_metaObject;
extern igMetaObject *g_igSkin_metaObject;
extern igMetaObject *g_igSkinList_metaObject;
extern igMetaObject *g_igSorter_metaObject;
extern igMetaObject *g_igSwitch_metaObject;
extern igMetaObject *g_igTextureMatrixAttrPool_metaObject;
extern igMetaObject *g_igTimeAttrPool_metaObject;
extern igMetaObject *g_igTransformList_metaObject;
extern igMetaObject *g_igTransformRecorder_metaObject;
extern igMetaObject *g_igTransformSequence_metaObject;
extern igMetaObject *g_igTransformSequence1_5_metaObject;
extern igMetaObject *g_igTransformSource_metaObject;
extern igMetaObject *g_igTransformStack_metaObject;
extern igMetaObject *g_igTransientShaderData_metaObject;
extern igMetaObject *g_igTraversal_metaObject;
extern igMetaObject *g_igTraversalFunctionList_metaObject;
extern igMetaObject *g_igVertexBlendMatrixAttrPool_metaObject;
extern igMetaObject *g_igVertexBlendMatrixListAttrPool_metaObject;

extern "C" int g_igTraversal_vtable[4];

struct R { int vt; unsigned int rc; };
struct Obj { int *vt; char pad[24]; struct R *p; char pad2[0]; };

struct S {
    void *f0;
    char pad[24];
    void *f1c;
};


struct Obj_194720 { int *vt; int f4; int f8; int fC; int f10; int f14; int f18; int f1C; };
extern "C" int g_igTransientShaderData_vtable[4];
extern "C" void** FUN_0013a800(void**, short);
extern "C" int g_igShaderData_vtable[4];
struct Ref { int pad; union { int w; struct { unsigned cnt:23; unsigned f:9; } b; } u; };
struct T { int word0; int references; };
struct Obj_194930 {
    int *vt; char p4[4]; T *m8; T *m12; T *m16; T *m20;
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
extern "C" igMetaObject *igShaderData_GetPublishedMetaObject(void);

struct M { char pad[40]; int f40; };
struct T_194b40 { int word0; int references; char pad8[20]; int f28; char pad32[6]; char f38; char pad39[13]; char f52; char pad53[3]; int f56; };
class DW4VC_84_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual int vX(int); };

struct Obj_194f40 { int *vt; int w[27]; };
extern "C" int g_igTransformSequence1_5_vtable[4];
extern "C" int DAT_005283e0[4];
struct Obj_195030 {
    int *vt; char p4[4]; T *m8; T *m12; T *m16; T *m20;
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
struct S_temp_a0 { char pad4[4]; int f4; };
struct O { S_temp_a0 *m; };
/* Deleting destructor; the deletion flag is a signed short. */
typedef struct ObjectRefTarget { int word0; int references; } ObjectRefTarget;
typedef struct ObjectRefWord { ObjectRefTarget *value; } ObjectRefWord;
extern "C" igMetaObject *igTransformSequence_GetPublishedMetaObject(void);
extern "C" void igTransformSequence1_5_InitFields(void);
extern "C" igMetaObject *igTransformSource_GetPublishedMetaObject(void);
struct Fld { char p0[38]; char f38; char p39[13]; char f52; char p53[3]; int f56; int f60; };
struct Obj_195860 { int *vt; int f4; int f8; int f12; int f16; int f20; int f24; int f28; char sub1[64]; char sub2[64]; };

extern "C" int g_igTransformRecorder_vtable[4];
typedef struct S_temp_a0_1958f0 { char pad4[4]; int f4; } S_temp_a0_1958f0;

extern "C" int g_igNode_vtable[4];
struct Rc { int vt; int rc; };
extern "C" int g_igNonRefCountedTransformList_vtable[4];
union U { int vt; char b[32]; };

extern "C" int g_igTransformList_vtable[4];

struct Obj_196080 { int *vt; char pad[28]; };
extern "C" int g_igTransformStack_vtable[4];

struct W { int *vt; int f[27]; };
struct S_1962d0 {
    void *f0;
    char pad0[96];
    void *f64;
    void *f68;
};
struct V { int x; int y; int z; int w; };

struct Obj_196780 { int *vt; char pad[28]; };
extern "C" int g_igObjectPool_vtable[4];
extern "C" int g_igSwitch_vtable[4];
union U_1969d0 { int vt; char b[48]; };
union U_196c10 { int vt; char b[144]; };

extern int g_igSorter_vtable[4];
extern int DAT_00528620[8];

extern "C" void** FUN_001380e0(void**, short);

struct Obj_197860 { int *vt; char pad[28]; };
extern "C" int g_igRenderPackageList_vtable[4];
struct Obj_1979d0 { int *vt; char pad[28]; };
extern "C" int g_igRenderPackagePool_vtable[4];
extern "C" igMetaObject *igObjectPool_GetPublishedMetaObject(void);
typedef struct S_ref { char pad4[4]; int f4; } S_ref;
extern "C" int g_igRenderPackage_vtable[4];
extern "C" int g_igSkinList_vtable[4];
extern "C" int g_igSkin_vtable[4];
union U_198070 { int vt; int w[8]; char b[32]; };

struct Obj_198480 { int *vt; char pad[28]; };
extern "C" int g_igSkeletonList_vtable[4];
extern "C" int g_igSkeleton_vtable[4];
extern "C" igMetaObject *igAnimationHierarchy_GetPublishedMetaObject(void);
struct Obj_198890 { int *vt; char pad[28]; };
extern "C" int g_igSkeletonBoneInfoList_vtable[4];
extern "C" int g_igSkeletonBoneInfo_vtable[4];
extern "C" void thunk_igSkeletonBoneInfo_GetMetaObject_00198ac0(void);
struct Obj_198bf0 { int *vt; char pad[4]; };
extern "C" int g_igShaderProcessor_vtable[4];
union U_198d50 { int vt; int w[8]; void *p[8]; char b[32]; };
extern "C" int g_igShaderInfo_vtable[4];

extern "C" void FUN_001d8ab0(void);
struct Obj_199040 { int *vt; char pad[28]; };
extern "C" int g_igShaderFactoryList_vtable[4];
extern "C" int g_igShaderFactory_vtable[4];
struct T_199330 { int *vt; int w4; char *f8; struct Rc *f12; struct Rc *f16; };
struct Obj_1996b0 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; };
struct Obj_199a90 { int *vt; char pad[28]; };
extern "C" int g_igBlendMatricesAttrPool_vtable[4];
struct Obj_199c00 { int *vt; char pad[28]; };
extern "C" int g_igTextureMatrixAttrPool_vtable[4];
extern "C" int g_igMatrixObjectPool_vtable[4];
extern "C" int g_igVertexBlendMatrixListAttrPool_vtable[4];
struct Obj_19a050 { int *vt; char pad[28]; };
extern "C" int g_igVertexBlendMatrixAttrPool_vtable[4];
struct Obj_19a1c0 { int *vt; char pad[28]; };
extern "C" int g_igProjectionMatrixAttrPool_vtable[4];
extern "C" int g_igTimeAttrPool_vtable[4];
extern "C" int g_igModelViewMatrixAttrPool_vtable[4];
struct Obj_19a610 { int *vt; char pad[28]; };
extern "C" int g_igLightStateAttrPool_vtable[4];
struct Obj_19a7c0 { int *vt; char pad[28]; };
extern "C" int g_igTraversalFunctionList_vtable[4];

struct Obj_19ada0 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; };
extern "C" int g_igSegment_vtable[4];
struct Obj_19af80 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; int w12; int w13; int w14; int w15; };
extern "C" int g_igSceneInfo_vtable[4];

typedef struct S_temp_a0_19b1f0 { char pad4[4]; int f4; } S_temp_a0_19b1f0;
struct V3 { int x; int y; int z; };

struct S_19b4e0 { int *vt; char pad[236]; };
extern "C" void** FUN_001321b0(void**, long long);
extern "C" int* FUN_00132410(int*);
extern "C" ObjectRefWord* FUN_00133ca0(ObjectRefWord*, int);
extern "C" ObjectRefWord* FUN_00136370(ObjectRefWord*, int);
extern "C" int g_igProjectiveShadowShader_vtable[4];


struct Fld_19b8a0 { char p0[38]; char f38; char p39[13]; char f52; char p53[3]; int f56; };
extern "C" int FUN_00151090(int);
extern "C" int g_igPlanarShadowShader_vtable[4];
extern "C" int D_005289f0[4];
union U_19bf50 { int vt; char b[112]; };
extern "C" int g_igAttrSet_vtable[4];
struct S_19c0e0 {
    void *f0;
    char pad[28];
    void *f20;
};
extern "C" igMetaObject *igAttrSet_GetPublishedMetaObject(void);

typedef struct { float x, y, z, w; } V4;
struct F { int *vt; int w[11]; };
extern "C" int g_igOverrideAttrSet_vtable[4];
struct Obj_19c960 { int *vt; char pad[28]; };
extern "C" int g_igNonRefCountedNodeList_vtable[4];
typedef struct { int *vt; int pad[7]; } Obj_19cad0;
extern "C" int g_igNodeListList_vtable[4];
struct Obj_19cc80 { int *vt; char pad[28]; };
extern "C" int g_igNodeList_vtable[4];
extern "C" int g_igGeometry_vtable[4];
extern "C" int DAT_0052aab0[4];
extern "C" int g_igModelViewMatrixBoneSelect_vtable[4];
union U_19d480 { int vt; int w[12]; void *p[12]; char b[48]; };
struct W_19d660 { int *vt; int f[19]; };
extern "C" int g_igLod_vtable[4];
struct Obj_19d960 { int *vt; int w[11]; };
extern "C" int g_igLightStateSet_vtable[4];
extern "C" int g_igLightSet_vtable[4];
struct Obj_19dc50 { int *vt; int f4; int f8; int f12; int f16; int f20; int f24; int f28; };
extern "C" igMetaObject *igNode_GetPublishedMetaObject(void);
struct Obj_19e070 { int *vt; int w[15]; };
extern "C" ObjectRefWord* FUN_00150fb0(ObjectRefWord*, int);
extern "C" int FUN_0018fa00(int *, int);
extern "C" int g_igIntersectTraversal_vtable[4];
struct S1 { char pad4[4]; int f4; };
typedef struct S_temp_a0_19e340 { char pad4[4]; int f4; } S_temp_a0_19e340;
typedef struct S_temp_a0_19e3c0 { char pad4[4]; int f4; } S_temp_a0_19e3c0;
extern "C" igMetaObject *igTraversal_GetPublishedMetaObject(void);
extern "C" int g_igProbe_vtable[4];
struct Obj_19eaa0 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; };
extern "C" igSmartPointer<igObject> *FUN_0014dd40(igSmartPointer<igObject> *self, short deleteFlag);
extern "C" int g_igInterpretedShaderData_vtable[4];
extern "C" igMetaObject *igTransientShaderData_GetPublishedMetaObject(void);
struct Obj_19ed70 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; int w12; int w13; int w14; int w15; };
extern "C" int g_igIniShaderFactory_vtable[4];
extern "C" igMetaObject *igShaderFactory_GetPublishedMetaObject(void);

struct Obj_19f2b0 { int *vt; int f4; int f8; int fC; int f10; int f14; int f18; int f1C; };
extern "C" int g_igGraphPathList_vtable[4];
typedef struct { int *vt; int p1[1]; int *ref; int pad[5]; } Obj_19f710;
extern "C" int g_igGraphPath_vtable[4];
extern "C" int g_igGeometryList_vtable[4];
struct Obj_19fb80 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; };
struct S_19fde0 { int *vt; char pad[468]; int a; char b[72]; int c; };
struct T_19fde0 { int w0; int refs; };
struct T1a0910 { int word0; int references; };
struct Obj_19fde0;
extern "C" int FUN_001510a0(int);
extern "C" int g_igFrustCullTraversal_vtable[4];
extern "C" int g_igCommonTraversal_vtable[4];
struct Obj_19fde0 {
    int *vt;
    char p4[24];
    T1a0910 *m28;
    T1a0910 *m32;
    T1a0910 *m36;
    char p40[12];
    T1a0910 *m52;
    T1a0910 *m56;
    T1a0910 *m60;
    T1a0910 *m64;
    T1a0910 *m68;
    T1a0910 *m72;
    T1a0910 *m76;
    T1a0910 *m80;
    T1a0910 *m84;
    T1a0910 *m88;
    T1a0910 *m92;
    T1a0910 *m96;
    char p100[132];
    T1a0910 *m232;
    T1a0910 *m236;
    T1a0910 *m240;
    T1a0910 *m244;
    T1a0910 *m248;
    T1a0910 *m252;
    T1a0910 *m256;
    T1a0910 *m260;
    T1a0910 *m264;
    T1a0910 *m268;
    char p272[64];
    T1a0910 *m336;
    inline void rel(T1a0910 **self) {
        if (self) {
            T1a0910 *object = *self;
            if (object) {
                --object->references;
                if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
                    igObject_Destroy((igObject *)object);
            }
        }
    }
};
struct Obj_1a1480 { int *vt; char pad[28]; };
extern "C" int g_igEnvironmentMapShader2List_vtable[4];

typedef struct { int *vt; int p1[2]; int *ref; int pad[0]; } Obj_1a1900;
extern "C" int g_igEnbayaTransformSource_vtable[4];
extern "C" int g_igEnbayaContextPool_vtable[4];
extern "C" int g_igEnbayaAnimationState_vtable[4];
extern "C" int g_igAnimationState_vtable[4];
union U_1a1e80 { int vt; char b[176]; };
extern "C" igMetaObject *igAnimationState_GetPublishedMetaObject(void);
extern "C" int g_igEnbayaAnimationSource_vtable[4];
union U_1a22b0 { int vt; int w[12]; void *p[12]; char b[48]; };
struct Obj_1a2590 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; };
extern "C" ObjectRefWord* FUN_00164870(ObjectRefWord*, int);
extern "C" int g_igCompressedTransformSequence1_5Data_vtable[4];
extern "C" int g_igCompressedAnimationSequenceQS_vtable[4];
union U_1a2810 { int vt; char b[64]; };
extern "C" igMetaObject *igAnimationSequence_GetPublishedMetaObject(void);
struct Fld_1a29e0 { char p0[38]; char f38; char p39[13]; int f52; int f56; };
extern "C" int g_igBlendListRecord_vtable[4];
union U_1a2d00 { int vt; int w[4]; void *p[4]; char b[16]; };
extern "C" int g_igCompileTraversal_vtable[4];
extern "C" int DAT_00529320[8];
union U_1a2f80 { int vt; char b[528]; };
extern "C" igMetaObject *igCommonTraversal_GetPublishedMetaObject(void);
struct Obj_1a34c0 { int *vt; char pad[28]; };
extern "C" int g_igCompiledTransformList_vtable[4];
union U_1a3620 { int vt; int w[12]; void *p[12]; char b[48]; };
extern "C" int g_igCompiledTransform_vtable[4];
struct Fld_1a37a0 { char p0[38]; char f38; char p39[13]; char f52; char p53[3]; int f56; };
struct O_1a38e0 { int vt; char b[468]; };

extern "C" int D_005293c0[4];
typedef struct { int *vt; int w[15]; } Obj_1a4600;
extern "C" int g_igCamera_vtable[4];
struct Obj_1a48c0 { int *vt; int w[11]; };
extern "C" int g_igBoundingBoxesMaker_vtable[4];

struct Obj_1a4ba0 { int *vt; int f4; int f8; int f12; int f16; int f20; int f24; int f28; int f32; int f36; int f40; char sub1[64]; char sub2[64]; char pad[4]; };
extern "C" int g_igBlendMatrixSelect_vtable[4];
struct Obj_1a4e30 { int *vt; char pad[28]; };
extern "C" int g_igBitMask_vtable[4];

extern "C" int g_igBillboard_vtable[4];
union U_1a4fd0 { int vt; int w[16]; void *p[16]; char b[64]; };
struct Obj_1a5260 { int *vt; char pad[28]; };
extern "C" int g_igNonRefCountedAttrStackManagerList_vtable[4];
struct Obj_1a53d0 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; int w12; int w13; int w14; int w15; int w16; int w17; int w18; int w19; };
extern "C" int g_igAttrStackManager_vtable[4];
struct Obj_1a59a0 { int *vt; char pad[28]; };
extern "C" int g_igAttrStackList_vtable[4];
extern "C" int g_igAttrStack_vtable[4];
union U_1a5b00 { int vt; int w[16]; void *p[16]; char b[64]; };
typedef struct { int *vt; int w[7]; int s; } Obj_1a5e10;
struct Obj_1a6080 { int *vt; char pad[28]; };
extern "C" int g_igAppearanceList_vtable[4];
struct Obj_1a61f0 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; };
extern "C" int g_igAppearance_vtable[4];
extern "C" int g_igAnimationStatePool_vtable[4];
extern "C" int g_igAnimationStateList_vtable[4];
union U_1a6c90 { int vt; int w[37]; char b[148]; };
struct Obj_1a7370 { int *vt; char pad[28]; };
extern "C" int g_igAnimationModifierList_vtable[4];
struct Obj_1a74f0 { int *vt; char pad[8]; char *m; char pad2[16]; };
extern "C" int g_igAnimationModifier_vtable[4];
struct W_1a7820 { int *vt; int f[11]; };
extern "C" int g_igAnimationDatabase_vtable[4];
typedef struct S_temp_a0_1a7980 { char pad4[4]; int f4; } S_temp_a0_1a7980;
struct Obj_1a7d50 { int *vt; char pad[28]; };
extern "C" int g_igAnimationCombinerBoneInfoPool_vtable[4];
struct Obj_1a7ec0 { int *vt; char pad[28]; };
extern "C" int g_igAnimationCombinerBoneInfoListList_vtable[4];
struct Obj_1a7fe0 { int *vt; char pad[28]; };
extern "C" int g_igAnimationCombinerBoneInfoList_vtable[4];
struct Obj_1a8140 { int *vt; char p4[8]; int *m12; int *m16; char pe[44]; };
extern "C" int g_igAnimationCombinerBoneInfo_vtable[4];
struct Obj_1a8450 { int *vt; char pad[28]; };
extern "C" int g_igAnimationCombinerList_vtable[4];
struct Obj_1a8570 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; int w12; int w13; int w14; int w15; int w16; int w17; int w18; int w19; int w20; int w21; int w22; int w23; };
extern "C" int g_igAnimationCombiner_vtable[4];
extern "C" int DAT_00529c40[4];
struct S_1a8620 {
    void *f0;
    char pad0[4];
    void *f8;
    igObject *fc;
};
extern "C" igMetaObject *igAnimationSystem_GetPublishedMetaObject(void);
struct Fld_1a88b0 { char p0[38]; char f38; char p39[13]; char f52; char f53; char p54[2]; int f56; int f60; char f64; char f65; };
struct Obj_1a8b60 { int *vt; char pad[28]; };
extern "C" int g_igAnimationBindingList_vtable[4];
extern "C" int g_igAnimationBinding_vtable[4];
struct Obj_1a9020 { int *vt; char pad[28]; };
extern "C" int g_igAnimationList_vtable[4];
extern "C" int g_igAnimation_vtable[4];
union U_1a91d0 { int vt; char b[64]; };
extern "C" int g_igAnimationTransitionDefinitionList_vtable[4];
extern "C" int g_igAnimationTransitionDefinition_vtable[4];
struct Obj_1a98d0 { int *vt; char pad[28]; };
extern "C" int g_igAnimationTransitionPointList_vtable[4];
typedef struct Q { char pad4[4]; int f4; } Q;
typedef struct { int *vt; int w[3]; Q *s; } Obj_1a99f0;
extern "C" int g_igAnimationTransitionPoint_vtable[4];
struct Obj_1a9c50 { int *vt; char pad[28]; };
extern "C" int g_igAnimationTransitionParams_vtable[4];
struct Obj_1a9e30 { int *vt; char pad[28]; };
extern "C" int g_igAnimationTrackList_vtable[4];
extern "C" int g_igAnimationTrack_vtable[4];
union U_1a9f50 { int vt; char b[48]; };
struct Obj_1aa1b0 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; };
extern "C" int g_igActorInfo_vtable[4];
struct Obj_1aa660 { int *vt; char pad[28]; };
extern "C" int g_igActorList_vtable[4];
extern "C" int g_igActor_vtable[4];
struct igObjectView { int *vtable; unsigned int refCount; igObjectView(); };
struct igMatrix44fView { float m[16]; igMatrix44fView(); };
struct igActorVtable { igActorVtable(int **slot) { *slot = g_igActor_vtable; } };
struct igNodeView : igObjectView {
    int name, bound, parentList, flags, handle, childList;
    igNodeView() { name = 0; bound = 0; parentList = 0; childList = 0; }
    ~igNodeView();
};
struct ActorAnimSystemField { int *p; ActorAnimSystemField() { p = 0; } ~ActorAnimSystemField(); };
struct ActorAppearanceField { int *p; ActorAppearanceField() { p = 0; } ~ActorAppearanceField(); };
struct ActorDatabaseField { int *p; ActorDatabaseField() { p = 0; } ~ActorDatabaseField(); };
struct ActorModifierField { int *p; ActorModifierField() { p = 0; } ~ActorModifierField(); };
struct igActorView : igNodeView, igActorVtable {
    ActorAnimSystemField animationSystem;
    int boneCache, blendCache;
    ActorAppearanceField appearance;
    ActorDatabaseField database;
    ActorModifierField modifierList;
    igMatrix44fView transform;
    char cacheFlags[4];
    igMatrix44fView mvm;
    igMatrix44fView inverseView;
    char tail[4];
    igActorView() : igActorVtable(&vtable) { }
    ~igActorView() { vtable = g_igActor_vtable; }
};
extern "C" int g_igPsx2EnvironmentMapShader_vtable[4];
union U_1aae40 { int *vt; char b[128]; };
extern "C" int DAT_00528fa0[4];
struct Obj_1aaf80 {
    int *vt;
    char p4[28];
    T *m32;
    T *m36;
    char p40[12];
    T *m52;
    char p56[8];
    T *m64;
    T *m68;
    char p72[4];
    T *m76;
    T *m80;
    T *m84;
    T *m88;
    T *m92;
    T *m96;
    T *m100;
    T *m104;
    T *m108;
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
typedef struct S_temp_a0_1ab380 { char pad4[4]; int f4; } S_temp_a0_1ab380;
extern "C" igMetaObject *igEnvironmentMapShader2_GetPublishedMetaObject(void);

struct E { char pad[8]; int *f8; };
struct L { char pad[8]; int count; char pad1[4]; E **data; };
struct S_1ab6c0 { char pad[20]; L *f20; };
typedef struct S1_1ab770 { char pad4[4]; int f4; } S1_1ab770;

class DW4VC_96_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual int vX(); };
class DW4VC_104_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual int vX(int); };
typedef struct { int p[2]; int cnt; int p2; void **arr; } I;
typedef struct { int p[4]; I * list; } H;
typedef struct { int p[2]; int id; int p2[3]; unsigned busy; } T_1ab920;
typedef struct S_temp_a0_1ab990 { char pad4[4]; int f4; } S_temp_a0_1ab990;
typedef struct S0 { char pad16[16]; S_temp_a0_1ab990 *f10; char pad20[52]; unsigned char f48; } S0;
typedef struct R_1aba30 { char pad4[4]; int f4; } R_1aba30;
typedef struct S_1aba30 { char pad8[8]; R_1aba30 *ref; char pad12[60]; unsigned char flags; } S_1aba30;
struct Rc_1abb50 { int w0; int refs; };
class A { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual int vX(); int f4; };
struct S_1abb50 { char p0[8]; Rc_1abb50 *f8; void *f12; };

typedef struct AnimationPoolObject { int w0; int references; char pad[20]; char f28; } AnimationPoolObject;

struct R_1abdf0 { char pad[4]; int f4; };
struct Ent { int p[2]; int key; };
struct Rec2 { char p[24]; igObjectList *tbl; };
struct X { int p[2]; Rec2 *r; };
struct Own { int p[2]; int key; };
struct Item { int p[3]; Own *owner; char q[32]; int w; };
class V_1abed0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual int vN(); };
class VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual int v96(); };
class igSceneMgrView {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual long long slot24();
};
struct igTimeView { char pad[16]; long long t; };
struct CombinerStateList { char pad[8]; int _count; int _capacity; igAnimationState **_data; };

class DW4VC_96_4 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual int vX(int, int, int, int); };
class igCompressedSeqView {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20();
    virtual int slot21();
};
/* matching construct: dummy-virtual class supplies the retail vtable slot offsets for the virtual calls */
struct TimeSourceVirtual { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();  virtual long long v24(); };
extern TimeSourceVirtual *DAT_005871d8[4];
/* matching construct: dummy-virtual class supplies the retail vtable slot offsets for the virtual calls */
struct TraversalVirtual { virtual void t0(); int pad[3]; long long val; unsigned char flag; };
class igAnimationHierarchyOps {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21();
    virtual int getBoneCount();
    virtual int getBlendCount();
    char pad4[8];
    float *_translations;
};
struct BoneInfoRow { char pad[8]; int _count; int _capacity; igAnimationCombinerBoneInfo **_data; };
struct BoneInfoRows { char pad[16]; BoneInfoRow **_data; };
struct CombinerView {
    char pad0[12];
    igAnimationHierarchyOps *_animHierarchy;
    char pad16[32];
    BoneInfoRows *_boneInfoListList;
    char pad52[32];
    float *_boneMatrixArray;
    float *_blendMatrixArray;
};

typedef struct IL { int p0, p1; int count; int cap; int *data; } IL;
typedef struct X_1ad5c0 { char p0[12]; int w12; } X_1ad5c0;
typedef struct It { int p0; int refs; char p8[4]; X_1ad5c0 *x; char p16[32]; int prio; } It;
typedef struct Ls { int p0, p1; int count; int cap; It **data; } Ls;
typedef struct LL { int p0, p1; int count; int cap; Ls **data; } LL;
typedef struct A_1ad5c0 { char p0[48]; LL *ll; IL *il; char p56[24]; char b80; } A_1ad5c0;

struct Retained {
    It *p;
    Retained(It *object) : p(object) {
        It *o = p;
        if (o != 0) {
            o->refs += 1;
        }
    }
};
class V_1ad860 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual int vX(); };
class igPoolObject {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20();
    virtual void slot21();
    virtual int reset();
    unsigned int _refCount;
};
struct CombinerBoneInfo { char pad[8]; int _lastKeyframe; igAnimationState *_animationState; int _transformSource; float _q[4]; float _t[3]; int _priority; unsigned char _useTranslation; char pad53[3]; int _reflect; };
struct CombinerBoneRow { char pad[8]; int _count; int _capacity; CombinerBoneInfo **_data; };
struct CombinerBoneRows { char pad[16]; CombinerBoneRow **_data; };
struct CombinerIntList { char pad[8]; int _count; int _capacity; int *_data; };
struct CombinerStateList_1ad990 { char pad[8]; int _count; int _capacity; igPoolObject **_data; };
struct CombinerStateRec { int _vtable; unsigned int _refCount; int pad8; int _combineMode; char pad16[108]; unsigned char _isCycleMatchTarget; };
struct CombinerHierarchyRec;
struct CombinerBlendView {
    char pad0[12];
    igPoolObject *_animHierarchy;
    char pad16[32];
    CombinerBoneRows *_boneInfoListList;
    CombinerIntList *_boneInfoListBase;
    CombinerStateList_1ad990 *_animationStateList;
    char pad60[20];
    unsigned char _cacheValid;
};

struct CombinerPool { char pad[8]; int _capacity; int pad12; igPoolObject **_data; int _used; };
struct CombinerBoneState { igPoolObject _base; igPoolObject *_animation; int _combineMode; int _transitionMode; int _status; int _baseState; unsigned char _new; char pad29[43]; long long _blendStartTime; char pad80[72]; long long _timeRequested; };
struct CombinerBitMask { char pad[16]; unsigned int *_data; };
struct CombinerTrack { igPoolObject _base; int _name; igPoolObject *_source; float _q[4]; float _t[3]; };
struct CombinerTrackList { char pad[16]; CombinerTrack **_data; };
struct CombinerAnimation { igPoolObject _base; int _name; int _priority; int _bindingList; CombinerTrackList *_trackList; char pad24[32]; CombinerBitMask *_useTrans; };
struct CombinerBinding { char pad[12]; int *_boneMap; };
struct CombinerHierarchyTrans { char pad[12]; float *_translations; };
class igPoolObject_1adf70 {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21();
    virtual int reset();
    unsigned int _refCount;
};
struct PoolObjectList { char pad[8]; int _count; int _capacity; igPoolObject_1adf70 **_data; };
struct BoneInfoSlot { char pad[8]; int _lastKeyframe; int _animationState; int _transformSource; float _q[4]; float _t[3]; int _priority; unsigned char _useTranslation; char pad53[3]; int _reflect; };
struct BoneInfoSlotList { char pad[8]; int _count; int _capacity; BoneInfoSlot **_data; };
struct BoneInfoRows_1adf70 { char pad[16]; BoneInfoSlotList **_data; };
struct CombinerResetView {
    char pad0[12];
    igPoolObject_1adf70 *_animHierarchy;
    char pad16[32];
    BoneInfoRows_1adf70 *_boneInfoListList;
    int pad52;
    PoolObjectList *_animationStateList;
    char pad60[20];
    unsigned char _cacheValid;
};
struct CombinerStateList_1ae2d0 { char pad[8]; int _count; int _capacity; igPoolObject **_data; };
struct CombinerStateView {
    char pad0[12];
    igPoolObject *_animHierarchy;
    char pad16[32];
    CombinerBoneRows *_boneInfoListList;
    CombinerIntList *_boneInfoListBase;
    CombinerStateList_1ae2d0 *_animationStateList;
    char pad60[20];
    unsigned char _cacheValid;
};
extern "C" int FUN_001adec0(CombinerBlendView *c, CombinerAnimation *anim, int combineMode, int transitionMode, int status, int *priorities, bool perBone);
struct L_1ae660 { char p0[8]; int count; char p1[4]; int items; };
struct E_1ae660 { char p0[72]; long long f72; float f80; float f84; long long f88; long long f96; };

class DW4VC_92_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual int vX(); };
struct CombinerStateList_1ae780 { char pad[8]; int _count; int _capacity; igPoolObject **_data; };
struct CombinerStateView_1ae780 {
    char pad0[12];
    igPoolObject *_animHierarchy;
    char pad16[32];
    CombinerBoneRows *_boneInfoListList;
    CombinerIntList *_boneInfoListBase;
    CombinerStateList_1ae780 *_animationStateList;
    char pad60[20];
    unsigned char _cacheValid;
};
struct CombinerNewState { igPoolObject _base; igPoolObject *_animation; int _combineMode; int _transitionMode; int _status; int _baseState; unsigned char _new; char pad29[43]; long long _blendStartTime; };
struct CombinerQuat { float x, y, z, w; };
typedef struct R_1aea60 : public igObject { int f8; int f12; int *f16; } R_1aea60;
typedef struct O_1aea60 { char pad[8]; char *f8; char pad2[8]; void *f20; void *f24; void *f28; void *f32; void *f36; } O_1aea60;
extern "C" int *DAT_00562560[4];

struct AnimDbRecord { int vtable; unsigned int references; const char *name; };

struct RecordRef {
    AnimDbRecord *p;
    RecordRef(AnimDbRecord *object) : p(object) {
        if (p != 0) {
            p->references = p->references + 1;
        }
    }
    ~RecordRef() {
        AnimDbRecord *object = p;
        if (object != 0) {
            object->references = object->references - 1;
            if ((object->references & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)object);
            }
        }
    }
};
struct AnimDbObject : public igObject { int _name; int _source; int _f16; int _f20; };
struct AnimDbList { char pad[8]; int _count; int _capacity; AnimDbObject **_data; };
struct AnimDbDirectory { char pad[8]; int _count; };
struct AnimDbField { char pad[8]; int _offset; };
struct AnimDbRec { char pad[8]; int _name; AnimDbDirectory *_directory; char pad16[4]; AnimDbList *_skeletonList; AnimDbList *_animationList; AnimDbList *_skinList; AnimDbList *_appearanceList; AnimDbList *_combinerList; };
extern int DAT_00586730;
extern AnimDbField *DAT_00562568;

extern long long DAT_0048d8c0;
extern float DAT_0048d8c8;
extern long long DAT_00562570;

struct AppearanceNameEntry { char pad[8]; int _string; };
struct AppearanceNameList { char pad[8]; int _count; int _capacity; AppearanceNameEntry **_data; };
struct AppearanceWordList { char pad[8]; int _count; int _capacity; int *_data; };
struct igAppearanceView {
    char pad[12];
    int _skin;
    AppearanceWordList *_attachedSkins;
    AppearanceWordList *_attachedGraphs;
    AppearanceNameList *_segmentOverrideNameList;
    AppearanceWordList *_segmentOverrideGraphList;
};
class V112 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void vX(); };
struct L_1af7e0 { char pad8[8]; unsigned int cnt; char pad12[4]; V112 **arr; };
struct S_1af7e0 { char pad32[32]; L_1af7e0 *l; };
struct A_1af890 { int p0; int p1; int p2; int p3; int *arr; };
struct B { int p0; int p1; int f8; int p3; int p4; int f20; };
struct O_1af890 { int p0; int p1; int p2; int n; struct A_1af890 *l16; int p5; struct B *b24; struct B *b28; char pad[12]; struct B *b44; char pad2[16]; struct B *b64; };
struct L_1af920 { char pad8[8]; int n; int cap; int *data; };
struct Z { char pad56[56]; int f56; };

extern "C" struct L_1af920 *DAT_00562580[4];

struct K { void *p; K(void *x) { p = x; } ~K() { } static void operator delete(void *q) { Memory_FreeBufferAliasB(q); } };
struct AttrStackList {
    int w0; int rc; int n; int w12; void **data;
};
struct Finder {
    static int Find(AttrStackList *l, K &key) {
        int cnt = l->n;
        int i = 0;
        for (; i < cnt; i++) {
            if (key.p == l->data[i]) {
                return i;
            }
        }
        return -1;
    }
};
typedef struct R_1afb00 { char pad4[4]; int f4; } R_1afb00;
extern "C" R_1afb00 *DAT_00562578[4];
struct RefObj { int w0; int references; int count; int capacity; void **data; };

struct Finder_1afb60 {
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
struct AttrObj : igObject { int _id; };
struct AttrStackRec;
class AttrDefaultManager {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20();
    virtual igSmartPointer<AttrObj> getDefault(void *meta, int unit);
};
class AttrCaps {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24();
    virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28();
    virtual int unitCount(void *capabilities);
    virtual void s30();
    virtual void onDefault(int v);
};
struct AttrStackRec : igObject { int _count; int _capacity; int _data; AttrObj *_default; int _cachedOverride; int _popProc; int pad32; AttrObj *_lastIncrementalFlushedAttr; };
struct AttrList { char pad[8]; int _count; int _capacity; igObject **_data; };
struct AttrManagerRec : public igObject {
     int pad8;
    int _numAttrStacks;
    AttrList *_attrStacks;
    AttrList *_attrDefaults;
    char pad24[28];
    int _capabilityManager;
    AttrDefaultManager *_defaultManager;
    char pad60[8];
    int *_attrStackIndexTable;
    int _attrStackIndexTableSize;
};

struct AttrStackRefView { int w0; int references; };
struct List { int pad0[2]; int count; int pad1; AttrStackRefView **data; };
struct AttrStackManagerView {
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
    virtual void v21();
    int pad4[2];
    int f12;
    List *f16;
    List *f20;
    char pad2[28];
    AttrStackRefView *f52;
    AttrStackRefView *f56;
};
typedef struct PendingIntList { char p0[8]; int cnt; int cap; int *data; } PendingIntList;
typedef struct TrackedIntStack { char p0[8]; int cnt; int cap; int *data; int f20; int f24; int f28; char f32; char q[3]; int f36; } TrackedIntStack;
typedef struct TrackedIntTable { char p0[16]; TrackedIntStack **data; } TrackedIntTable;
typedef struct PendingValueCollector { char p0[16]; TrackedIntTable *f16; char q0[4]; PendingIntList *f24; char p1[16]; PendingIntList *f44; char p2[12]; unsigned char f60; } PendingValueCollector;
struct Rc_1b0450 : public igObject { int n; int cap; int *data; };
struct E_1b0450 { int p0; int p4; int n; int p12; int *data; int def; int idx; int p28; int p32; int p36; char flag; };
struct B_1b0450 { int p0; int p4; int p8; int p12; struct E_1b0450 **data; };
struct A_1b0450 { int p0; int p4; char f8; int p12; struct B_1b0450 *f16; int p20; int p24; igSmartPointer<Rc_1b0450> f28; igSmartPointer<Rc_1b0450> f32; };
typedef struct R_1b0dc0 { char pad4[4]; int f4; } R_1b0dc0;
typedef struct E2 { char pad16[16]; R_1b0dc0 *f10; } E2;
typedef struct E1 { char pad20[20]; E2 *f14; } E1;
typedef struct L_1b0dc0 { char pad16[16]; E1 **arr; } L_1b0dc0;
typedef struct C { char pad8[8]; int n; } C;
typedef struct G { char pad8[8]; int idx; } G;
typedef struct O_1b0dc0 { char pad16[16]; L_1b0dc0 *l; char pad20[16]; C *c24; C *c28; char pad2c[24]; int *base; } O_1b0dc0;

/* An igAttrStack seen as its object stack. The pushes follow the stack classes' layering: the
 * override push marks where the overrides start, the object stack's push hands the object to the
 * data stack by reference, and the data stack stores it at the old count. */
struct AttrObjectStack : igTDataList<igObject *> {
    int _default;
    int _cachedOverride;
    void (*_popProc)(igObject *, int);
    int pushItem(igObject *const &item) {
        const int count = getCount();
        if (count < _capacity) {
            _count++;
        } else {
            ((Gap::Core::igDataList *)this)->resizeAndSetCount(count + 1, sizeof(igObject *));
        }
        _data[count] = item;
        return count;
    }
    int push(const igObject *object) { return pushItem((igObject *const &)object); }
    void pushOverride(const igObject *override) {
        if (_cachedOverride < 0) {
            _cachedOverride = _count;
        }
        push(override);
    }
};
struct Q_1b1100 { char p[8]; int n; char r[4]; int *a; char s[8]; int (*cb)(int, int); };
struct X_1b1100 { char p[16]; struct Q_1b1100 **q; };
struct A_1b1100 { char p[16]; struct X_1b1100 *f16; char q[28]; int f48; char r[16]; int *f68; };
struct B_1b1100 { char p[8]; short idx; short off; };
struct Q_1b11b0 { char p[8]; int n; char r[4]; int *a; char s[8]; int (*cb)(int, int); };
struct X_1b11b0 { char p[16]; struct Q_1b11b0 **q; };
struct A_1b11b0 { char p[16]; struct X_1b11b0 *f16; char q[28]; int f48; char r[16]; int *f68; };
struct B_1b11b0 { char p[8]; int idx; };
struct Q_1b1250 { char p[8]; int n; char r[4]; int *a; char s[8]; int (*cb)(int, int); };
struct X_1b1250 { char p[16]; struct Q_1b1250 **q; };
struct A_1b1250 { char p[16]; struct X_1b1250 *f16; char q[28]; int f48; char r[16]; int *f68; };
struct B_1b1250 { char p[8]; int idx; };
struct Q_1b13d0 { char p[8]; int n; char r[4]; int *a; char s[4]; int f24; int (*cb)(int, int); };
struct X_1b13d0 { char p[16]; struct Q_1b13d0 **q; };
struct A_1b13d0 { char p[16]; struct X_1b13d0 *f16; char q[28]; int f48; char r[16]; int *f68; };
struct B_1b13d0 { char p[8]; short idx; short off; };
struct L_1b1490 { char pad[8]; int n; int cap; int *arr; };

struct igBitMaskWords { char pad8[8]; int _count; int _capacity; unsigned int *_data; unsigned int _bitCount;
    inline void setCount(int n);
    inline void setWord(int i, const unsigned int &v);
    inline unsigned int getWord(unsigned int i) { return _data[i]; }
};
extern unsigned int DAT_0048d8d0;
struct A_1b21d0 { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual unsigned v34(); char pad[28]; unsigned f32; };
class VC_100_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int *vX(); };
struct X_1b23e0 : public igObject { igVec3f a; igVec3f b; };
struct Y { char pad[12]; VC_100_0 *f12; };
extern "C" void FUN_001b1fa0(igGeometryAttr *geometry, igVec3f *min, igVec3f *max);
struct BoundsObject : public igObject { igVec3f min; igVec3f max; };
extern "C" int DAT_0055f158[4];

class Elem { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); };
struct List_1b2600 { int pad0[2]; int count; int pad1; Elem **data; };
struct Owner { char pad[32]; List_1b2600 *list; };
class DW4VC_156_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual int vX(int); };
class V_1b2750 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void vX(void *, int); };
/* An igAABox seen as its header and the min/max corners as six floats. */
struct AABoxFields { int vt; int rc; float f8, f12, f16, f20, f24, f28; };
/* Its destructor is compiled out of line as `__dt__10Ref_1b2750Fv` (a stripped row of the unit), so the name stays. */
struct Ref_1b2750 {
    AABoxFields *o;
    Ref_1b2750(AABoxFields *p) : o(p) {}
    ~Ref_1b2750() {
        AABoxFields *object = o;
        if (object) {
            --object->rc;
            if (((unsigned long long)(long long)object->rc & 0x7fffffULL) == 0)
                igObject_Destroy((igObject *)object);
        }
    }
};
/* An igTransform's _transformInput: the key matrices a sequence can produce. */
class TransformInputView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32();
    virtual void get(unsigned, void *);
    virtual void e1(); virtual void e2(); virtual void e3();
    virtual unsigned count();
};
struct B_1b2750 { float f0, f4, f8, f12, f16, f20, f24, f28; };
struct O_1b2750 { int f0, f4; long long f8; unsigned char b16, b17; short pad; struct B_1b2750 *f20; };
extern "C" unsigned char igNode_ComputeBound(igAABox *, igAABox *, int, int, unsigned char, unsigned char, long long);
struct TravObject { int _vtable; unsigned int _refCount; int _id; };
struct TravObjectList { char pad[8]; int _count; int _capacity; TravObject **_data; };
struct TravFlattenView { char pad[40]; TravObjectList *_a; TravObjectList *_b; };
struct NodeProcEntry { int meta; int proc; };
struct NodeProcTable { NodeProcEntry e[34]; } __attribute__((aligned(16)));
class igTimerSourceView {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual long long getTime();
};
class H_1b2fa0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void vX(int, int); char p0[180]; igBitMask *f184; };
class DW4VC_132_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual int vX(int); };
class VC_1b2fa0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual int vX(int, int); };
class C_1b2fa0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void vX(int); };
typedef struct A0 { char p0[32]; int f32; char p1[124]; int f160; char p2[12]; int f176; int f180; } A0;
typedef struct A1 { char p0[52]; int f52; char p1[12]; int f68; } A1;
typedef struct { char pad[64]; unsigned char flags; } T_1b2fa0;
struct Rc_1b2fa0 { int vt; int rc; int w8; int w12; int f16; };
struct M4130 { char pad[12]; int f12; };
struct A4130 { char pad[8]; int f8; };
struct O4130 { char pad0[32]; struct M4130 *f32; char pad1[20]; struct A4130 *f56; char pad2[100]; struct Rc_1b2fa0 *f160; };
struct Q_1b2fa0 { char p0[8]; int count; char pc[4]; int *data; };
struct A4220 { char p0[144]; struct Q_1b2fa0 *f144; };
struct B4220 { char p0[52]; int f52; };
struct S4500 { char p0[12]; int k; char p1[100]; float firstX,firstY,firstZ,secondX,secondY,secondZ; };
struct O4500 { char p0[56]; float x,y,z; int w; char p1[64]; struct S4500 *s; };
extern const NodeProcTable DAT_0048d8f0;

extern "C" int g_igTimeTransform_metaObject[4];
extern "C" int g_igTimeSwitch_metaObject;
extern "C" int g_igShader2_metaObject;
extern "C" int g_igShader_metaObject[4];
extern "C" int g_igSelfShadowShader_metaObject;
extern "C" int g_igMultiTextureShader_metaObject[4];
extern "C" int g_igMultiResolutionMeshInstance_metaObject;
extern "C" int g_igMorphInstance2_metaObject;
extern "C" int g_igMorphInstance_metaObject;
extern "C" int g_igInverseKinematicsSolver_metaObject;
extern "C" int g_igInverseKinematicsJoint_metaObject;
extern "C" int g_igInverseKinematicsHandle_metaObject;
extern "C" int g_igDOFShader_metaObject[4];
extern "C" int g_igCompiledGraph_metaObject[4];
extern "C" int g_igCartoonShader_metaObject[4];
extern "C" int g_igBumpMapShader_metaObject[4];
extern "C" int DAT_00562598[4];
extern "C" int DAT_005625a0[4];
extern "C" int DAT_005625a8[4];
extern "C" int DAT_005625b0[4];
extern "C" int DAT_005625b8[4];
extern "C" int DAT_005625c0[4];
extern "C" int DAT_005625c8[4];
extern "C" int DAT_005625d0[4];
extern "C" int DAT_005625d8[4];
extern "C" int DAT_005625e0[4];
extern "C" int DAT_005625e8[4];
extern "C" void *DAT_005625f0;
extern "C" VC_1b2fa0 *DAT_00562638[4];

extern "C" void FUN_001b3030(igProjectiveShadowShader *shader, igCommonTraversal *traversal);
extern "C" void FUN_001dc610(igSorter *sorter);

class igTraversalStackView {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20();
    virtual int slot21(void *other);
};
struct igCommonTraversalView {
    char pad0[52];
    void *f52;
    char pad1[12];
    igTraversalStackView *f68;
};

class C_1b6e20 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void v92(); virtual void v96(); char pad[124]; unsigned char f128; };
struct S20 { char p[20]; int f20; };
struct S8 { char p[8]; int f8; };
struct A_1b6e20 { char p[48]; char f48; char p1[3]; C_1b6e20 *f52; char p2[12]; C_1b6e20 *f68; S20 *f72; S20 *f76; S20 *f80; S20 *f84; S20 *f88; S20 *f92; S20 *f96; char p3[148]; S8 *f248; S8 *f252; char p4[12]; S20 *f268; };

typedef struct R_1b6f30 { int w0; int refs; } R_1b6f30;
typedef struct A_1b6f30 { char pad[32]; R_1b6f30 *f32; R_1b6f30 *f36; char pad40[12]; int f52; } A_1b6f30;
typedef struct R_1b7010 : public igObject { struct R_1b7010 *f8; } R_1b7010;
typedef struct O_1b7010 { char pad[32]; R_1b7010 *f32; R_1b7010 *f36; char pad2[20]; R_1b7010 *f60; } O_1b7010;

class V128 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual int vX(int); };
struct List_1b7330 { char p0[8]; int cap; char p1[4]; V128 **items; int count; };
struct O_1b7330 { char p0[52]; int f52; char p1[16]; List_1b7330 *list; };
struct S_1b73d0 { char pad[52]; int x; };
typedef igTDataList<igClearAttr *> AttrSlotList;
class igAttrStackOps {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual void push(int attr);
};
struct AttrStackView { char pad[20]; igAttrStackOps *_ops; };
struct AttrStackListView { char pad[16]; AttrStackView **_data; };
struct AttrManagerView { char pad[16]; AttrStackListView *_attrStacks; char pad2[48]; int *_firstUnit; };
class igCommonTraversalOps {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual long long getTime();
    virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
    virtual void setTime(long long t);
    char head[12];
    long long _timeLong;
    unsigned char _userTimeState;
    char pad25[27];
    AttrManagerView *_attrStack;
    char pad56[4];
    int _vc;
    char pad64[36];
    float _viewMat[16];
    char pad164[172];
    igClearAttr *_defaultTimeAttr;
};

struct L_1b75b0 { int p0; int p1; int size; int cap; long long *data; };
struct Ent_1b7630 { int pad[2]; int count; int pad2; int *items; int pad3[2]; void (*fn)(int, int); };
struct Tab { int pad[4]; Ent_1b7630 **ents; };
struct Mgr { int pad[4]; Tab *tab; int pad2[7]; int arg; int pad3[4]; int *idx; };
/* matching construct: dummy-virtual view so ->f31() dispatches through vtable slot 31 of the traversal */
struct TravView { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void f31(); };

struct SegmentOverrideRef { igObject *p; inline void retain() { if (p != 0) p->_refCount = p->_refCount + 1; } inline void set(igObject *o) { p = o; retain(); } };
struct SegmentStackList { char pad8[8]; int _count; int _capacity; igObject **_data; int count() const { return _count; } };

struct igGroupMaskView { char p[28]; igNodeList *_childList; igBitMask *_mask; };
class DW4VC_104_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual int vX(); };
class C_1b7ce0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual long long vX(); char pad4[48]; int f52; char pad56[180]; int f236; };
struct A_1b7ce0 { char pad20[20]; unsigned int f20; };

struct V_1b7d70 { float x, y, z, w; };
struct ActorMatrixEntry { char _pad0[12]; float _matrix[16]; };
struct ActorMatrixStack { int _pad0[2]; int _count; int _pad0c; ActorMatrixEntry **_data; };
struct ActorStackList { int _pad0[4]; ActorMatrixStack **_data; };
struct ActorAttrState { char _pad0[16]; ActorStackList *_stacks; char _pad14[48]; int *_slotOfIndex; };
struct ActorMeta { int _pad0[2]; int _offset; };
struct ActorCountedList { int _pad0[2]; int _count; };
struct ActorTraversal { char _pad0[52]; ActorAttrState *_state; char _pad38[108]; float _view[16]; };
class ActorAnimationHolder {
public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual void updateNodes(void *t, void *actor, int status, float *bones, float *blend, void *list);
};
class ActorAnimationStateSlots {
public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual void slot21();
    virtual int update(void *t, void *actor);
    virtual int isReady();
    virtual void setReady(int v);
    virtual float *bones();
    virtual void slot26();
    virtual float *blends();
};
struct ActorAnimationState : ActorAnimationStateSlots { int _pad4[2]; ActorAnimationHolder *_holder; };
struct ActorChildren { char _pad[8]; };
struct ActorView {
    char _pad0[32]; ActorAnimationState *_animationState; float *_bones; float *_blends; ActorChildren _children; ActorCountedList *_nodes;
    char _pad38[64]; unsigned char _forced; unsigned char _useCached; char _pad7a[2]; float _world[16]; float _view[16];     unsigned char _animate; unsigned char _traverse;
};
struct List_1b8a20 { int pad[2]; int count; int cap; int *items; int getCount() const { return count; } };
class Sub { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22();  virtual int g100(); };
class Dev_1b8a20 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24();  virtual int g108(); virtual void x112(); virtual int g116(); };
struct Mid { char pad[12]; Sub *f12; };
struct Src { char pad[32]; Dev_1b8a20 *f32; int f36; int f40; char pad2[77]; unsigned char f121; };
struct Dst { char pad[248]; List_1b8a20 *l248; List_1b8a20 *l252; List_1b8a20 *l256; };
class DW4VC_104_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual int vX(int, int); };
extern "C" void *DAT_00561928[4];
extern "C" int DAT_00561918[4];
class VC_104a { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();  virtual int vX(); };
class VC_156b { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36();  virtual int vX(int); };
class V140 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void vX(); };
class V128_1b8de0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void vY(int); };
struct LA { char p0[8]; int count; int p1; int *data; };
struct LB { char p0[8]; int cap; int p1; V128_1b8de0 **data; int count; };
struct G_1b8de0 { char p0[8]; int f8; };
struct Src_1b8de0 : V140 { char p0[24]; LA *list; };
struct Dst_1b8de0 { char p0[52]; int f52; char p1[16]; LB *l72; };
extern "C" void FUN_001b1aa0(igBillboard *billboard, float *matrix, const float *modelView, const float *view);
/* Builds the billboard rotation in `matrix` from its up vector and the direction to the viewer. */
extern "C" void FUN_001b1590(float *matrix, const float *up, const float *direction);

typedef struct RC { int p0; unsigned refs; } RC;
typedef struct G_1b8f20 { char p[8]; int f8; } G_1b8f20;
typedef struct Arr { char p[8]; int count; int p12; int *data; } Arr;
typedef struct LB_1b8f20 { char p[8]; int cap; int p12; RC **data; int count; } LB_1b8f20;
typedef struct X_1b8f20 { char p[16]; Arr *a16; char q[48]; int *a68; } X_1b8f20;
typedef struct C_1b8f20 { char p[52]; X_1b8f20 *x; char q[16]; LB_1b8f20 *l72; char r[24]; char v100[64]; char v164[16]; } C_1b8f20;
typedef struct D { char p[60]; RC *f60; } D;
struct TransformAttrView { char _pad0[12]; char _matrix[64]; };
struct TransformStackView { int _pad0[2]; int _count; int _pad0c; TransformAttrView **_data; TransformAttrView *_default; int _base; };
struct TransformStackList { int _pad0[4]; TransformStackView **_data; };
struct TransformStateView { char _pad0[16]; TransformStackList *_stacks; char _pad14[48]; int *_slotOfIndex; };
struct AttrClassView { int _pad0[2]; int _stackIndex; };
struct RefList { int _pad0[2]; int _count; int _pad0c; void **_data; };
struct AttrSetList { int _pad0[2]; int _count; int _pad0c; RefList **_data; };
class ModelViewAttrView {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29();
    virtual void setMatrix(void *);
};
struct SwitchGroupView { char _pad0[28]; RefList *_children; AttrSetList *_attrSets; int _pad24; unsigned char _nested; char _pad29[15]; int _mode; };
struct TraversalStateHolder { char _pad0[52]; TransformStateView *_state; };
struct DrawTraversalView { char _pad0[52]; TransformStateView *_state; char _pad38[176]; void *_baseAttr; };
typedef struct CullMatrixEntry { char _pad0[12]; float _matrix[16]; } CullMatrixEntry;
typedef struct CullMatrixStack { int _pad0[2]; int _count; int _pad0c; CullMatrixEntry **_data; CullMatrixEntry *_default; int _current; } CullMatrixStack;
typedef struct CullStackList { int _pad0[4]; CullMatrixStack **_data; } CullStackList;
typedef struct CullAttrState { char _pad0[16]; CullStackList *_stacks; char _pad14[48]; int *_slotOfIndex; } CullAttrState;
typedef struct CullMeta { int _pad0[2]; int _index; } CullMeta;
typedef struct { float x, y, z; } LightVec3;
typedef struct LightView { char _pad0[12]; int _type; char _pad10[100]; LightVec3 _worldPosition; LightVec3 _worldDirection; } LightView;
typedef struct LightListView { int _pad0[2]; int _count; int _pad0c; LightView **_data; } LightListView;
typedef struct LightSceneView { char _pad0[28]; LightListView *_lights; } LightSceneView;
typedef struct LightFieldMeta { int _pad0[2]; int _offset; } LightFieldMeta;
typedef struct LightTraversalView { char _pad0[52]; CullAttrState *_state; char _pad38[12]; int _collector; char _pad48[92]; float _view[16]; } LightTraversalView;
extern "C" LightFieldMeta *DAT_0055f0a0[4];

extern "C" int FUN_001be190(igAttrSet *set, igCompileTraversal *traversal);
struct L_1b9fc0 { char p8[8]; int n; char p12[4]; int *data; };
struct B_1b9fc0 { char p32[32]; struct L_1b9fc0 *f32; };
struct A_1b9fc0 { char p52[52]; int f52; };
typedef struct { float x, y, z; } CullVec3;
typedef struct CullTraversalView { char _pad0[52]; CullAttrState *_state; } CullTraversalView;
typedef struct CullNodeView { char _pad0[52]; CullVec3 _center; } CullNodeView;
typedef struct S_1ba1a0 { char pad52[52]; int f52; char pad56[176]; int f232; } S_1ba1a0;
struct igCartoonShader;
extern "C" void igCommonTraversal_DrawCartoonShader(igCartoonShader *self, igCommonTraversal *traversal);
typedef struct { char pad[52]; int f34; char pad2[176]; int fe8; } T_1ba200;
typedef struct S_1ba650 { char p[52]; int f52; char q[176]; int f232; } S_1ba650;
class VC1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual int vX(int); };
class VC0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void vX(int *); };
struct RecorderFrame { char _pad0[16]; long long _time; };
struct RecorderFramePool { int _pad0[2]; int _capacity; int _pad0c; RecorderFrame **_data; int _used; };
class TransformRecorderVisitor {
public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual void slot21();
    virtual void slot22();
    virtual void slot23();
    virtual void slot24();
    virtual void slot25();
    virtual void slot26();
    virtual void slot27();
    virtual void slot28();
    virtual void slot29();
    virtual void slot30();
    virtual void slot31();
    virtual void slot32();
    virtual void slot33();
    virtual void slot34();
    virtual void slot35();
    virtual void slot36();
    virtual void slot37();
    virtual void slot38();
    virtual long long sample(int a);
};
class TransformRecorderTraversal {
public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual void slot4();
    virtual void slot5();
    virtual void slot6();
    virtual void slot7();
    virtual void slot8();
    virtual void slot9();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual void slot21();
    virtual void slot22();
    virtual void slot23();
    virtual int channel();
    virtual void slot25();
    virtual void slot26();
    virtual void slot27();
    virtual void slot28();
    virtual void slot29();
    virtual void begin(long long t);
    virtual void end();
};
struct RecorderTraversalView : TransformRecorderTraversal {
    char _pad4[48]; int _state; char _pad38[20]; RecorderFramePool *_frames;
};

class DW4VC_148_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual int vX(); };
class DW4VC_152_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual int vX(int); };
class DW4VC_160_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual int vX(int); };
class DW4VC_164_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual unsigned char vX(); };
class DW4VC_172_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual int vX(); };
class DW4VC_176_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual int vX(int); };
class DW4VC_184_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual int vX(int); };
class PooledDrawItem { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void v(char *); };
struct DrawItemPool { int p0; int p4; int cap; int pc; PooledDrawItem **data; int idx; };
struct BaseTable { int p0; int p4; int count; int pc; int *data; };
struct DrawItemSource { char pad[52]; int f52; char pad2[16]; DrawItemPool *f72; char pad3[172]; BaseTable *f248; };
struct DrawItemIndex { char pad[32]; int f32; };
typedef struct MatrixFrame { char _pad0[12]; char *_matrices; unsigned int _count; unsigned int _capacity; } MatrixFrame;
typedef struct MatrixFramePool { int _pad0[2]; int _capacity; int _pad0c; MatrixFrame **_data; int _used; } MatrixFramePool;
typedef struct MatrixArrayList { int _pad0[2]; int _count; int _pad0c; char **_data; } MatrixArrayList;
typedef struct BoneIndexList { int _pad0[2]; int _count; int _pad0c; int *_data; } BoneIndexList;
typedef struct BlendNodeView { char _pad0[40]; BoneIndexList *_boneIndices; } BlendNodeView;
typedef struct CompileTraversalHead { char _pad0[52]; int _state; char _pad38[196]; MatrixArrayList *_palettes; char _pad100[12]; MatrixFramePool *_frames; } CompileTraversalHead;

struct S_1bafb0 { char pad[8]; int *f8; };
extern "C" Q *DAT_00562648[4];
typedef struct C_1bb280 { char pad[28]; Q *f28; } C_1bb280;
typedef struct RefCountedEntry { int w0; int ref; } RefCountedEntry;
typedef struct RefCountedEntryList { char pad0[8]; int cnt; int pad12; RefCountedEntry **data; } RefCountedEntryList;
class igCompileTraversalVSlots { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual int slot31(); };
extern "C" int igCompileTraversal_TraverseGeometry(igCompileTraversal *self, igGeometry *geometry);
struct T_1bb880 : public igVirtualObject { virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual int setMatrix(int); int f8; T_1bb880 *f12; char p[16]; int f32; };
struct E_1bb880 { char p[20]; void *f20; };
struct L1 { char p[16]; E_1bb880 **f16; };
struct L0 { char p[16]; L1 *f16; char q[48]; int *f68; };
struct G_1bb880 { char p[8]; int f8; };

class VC104 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual int vX(int, int); };
class VC128L { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual int vX(long long); };
class DW4VC_132_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual int vX(); };
extern "C" int FUN_001bbb30(int, int);
extern "C" igMetaField *g_igVertexBlendMatrixAttr_mField[4];
extern "C" igMetaField *g_unlinkedTransformClass_sourceField[4];
typedef struct X_1bce40 { char pad[4]; int f4; int f8; } X_1bce40;
struct Obj_1bcf70 { int w0; unsigned refs; int p8; int f12; int *f16; int f20; unsigned f24; };
struct SL { char p[8]; int count; char p2[4]; int *data; };
struct B_1bcf70 { char p[40]; SL *f40; };
struct A_1bcf70 { char p[52]; int f52; char q[440]; char f496; char r[7]; int f504; };
class DW4VC_124_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual int vX(); };

struct Arr_1bd170 { char p[8]; int n; int cap; int *data; };
struct B_1bd170 { char p[12]; struct Arr_1bd170 *list; };
struct A_1bd170 { char p[32]; struct Arr_1bd170 *out; };
struct Shape { char pad[472]; igTDataList<void *> *list; };
struct Links {
    char pad[32];
    igTDataList<void *> *targets;
    igTDataList<int> *indices;
    igTDataList<void **> *slots;
};
typedef igTDataList<void *> RemapIndexList;
struct RemapObject {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual igMetaObject *getMeta();
    unsigned int _refCount;
    char _pad8[16];
    RemapIndexList *_indices;
};
struct RemapObjectList { int _vtable; unsigned int _refCount; int _count; int _capacity; RemapObject **_data; };
struct RemapTable { int _vtable; unsigned int _refCount; int _pad8; void *_storage; int *_data; int _count; unsigned int _capacity; };
struct RemapEntry { int _vtable; unsigned int _refCount; void *_target; RemapObject **_slot; };
struct RemapContext { char _pad0[480]; RemapIndexList *_pool; };
struct RemapOwner { char _pad0[32]; RemapObjectList *_items; char _pad24[12]; RemapObjectList *_entries; char _pad34[32]; RemapObject *_fallback; };

typedef struct QSUShortList { int _pad0[4]; unsigned short *_data; } QSUShortList;
typedef struct QSView {
    int _pad0[2];
    QSUShortList *_compressedTranslationList;
    QSUShortList *_compressedQuaternionList;
    int _pad10;
    float _translationBase;
    float _translationRangeOverMaxUShort;
    float _quaternionBase;
    float _quaternionRangeOverMaxUShort;
} QSView;
struct QSDataList { int _vtable; int _refCount; int _count; int _capacity; int *_data; };
class QSSequenceSlots {
public:
    virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void slot3(); virtual void slot4(); virtual void slot5(); virtual void slot6(); virtual void slot7(); virtual void slot8(); virtual void slot9();
    virtual void slot10(); virtual void slot11(); virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15(); virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
    virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23(); virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27(); virtual void slot28(); virtual void slot29();
    virtual void slot30(); virtual void slot31(); virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35(); virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
    virtual long long keyTime(int i);
};
struct QSSequenceView : QSSequenceSlots {
    int _refCount;
    QSDataList *_compressedTranslationList;
    QSDataList *_compressedQuaternionList;
    QSDataList *_compressedTimeList;
    float _translationBase;
    float _translationRangeOverMaxUShort;
    float _quaternionBase;
    float _quaternionRangeOverMaxUShort;
    int _pad36;
    unsigned long long _animationDuration;
    int _playMode;
    int _lastTime;
    unsigned char _channels;
    unsigned char _interpolationMethod[7];
};
struct QSSourceSequence { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual int v156(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void *v172(); virtual void d42(); virtual void d43(); virtual void *v184(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual long long v224(int); virtual void d55(); virtual void d56(); virtual int v236(int); virtual int v240(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual long long v260(); char pad[32]; int f36; };
extern "C" void Gap__Sg__igCompressedAnimationSequenceQS__vfunc_44(QSSequenceView *arg0, QSSourceSequence *arg1);
struct M_1bfa60 { int pad[2]; int count; };
struct O_1bfa60 { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31(); virtual void v32(); virtual int v33(); virtual void v34(); virtual void v35(); virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39(); virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43(); virtual void v44(int,int*); virtual void v45(int*,int,int,float); virtual void v46(int*,int,int,float);
 int p0[3]; M_1bfa60 *m; int p1[8]; int idx; unsigned char flags; };
extern "C" void FUN_001bf7d0(QSSequenceView *o, unsigned char *before, unsigned char *after, int *key0, int *key1, float *t0, float *t1, long long time);

struct M_1bfc70 { int pad[2]; int count; };
struct O_1bfc70 { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35(); virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39(); virtual long long v40(int);
 int p0[3]; M_1bfc70 *m; int p1[8]; int cur; };
extern "C" void FUN_00192ab0(float *, float, void *, void *);
struct S_1bfe90 { char pad[58]; unsigned char f58; };
class DW4VC_184_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual int vX(int, int *); };
class V192 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual int vX(int, int, int, float); };
struct L_1c0010 { char pad8[8]; int cnt; };
struct S_1c0010 { V192 *vt; char pad4[12]; L_1c0010 *f16; };
struct L_1c00e0 { char pad8[8]; int n; };
class VC_1c00e0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual int v140(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual int v184(int, int); virtual void v188(int, int, int, float); virtual void v192(int, int, int, float); };
struct O_1c00e0 : VC_1c00e0 { char pad4[12]; L_1c00e0 *f16; };
struct Obj_1c03a0 { char p0[16]; float a[4]; char p1[16]; double f48; char p2[4]; int f60; float f64; };
struct Cls { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual int v148(int); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual void d101(); virtual void d102(); virtual void d103(); virtual void d104(); virtual void d105(); virtual void d106(); virtual void d107(); virtual void d108(); virtual void d109(); virtual void d110(); virtual void d111(); virtual void d112(); virtual void d113(); virtual void d114(); virtual void d115(); virtual void d116(); virtual void d117(); virtual void d118(); virtual void d119(); virtual void d120(); virtual void d121(); virtual void d122(); virtual void d123(); virtual void d124(); virtual void d125(); virtual void d126(); virtual void d127(); virtual void d128(); virtual void d129(); virtual void d130(); virtual void d131(); virtual void d132(); virtual void d133(); virtual void d134(); virtual void d135(); virtual void d136(); virtual void d137(); virtual void d138(); virtual void d139(); virtual void d140(); virtual void d141(); virtual void d142(); virtual void d143(); virtual void d144(); virtual void d145(); virtual void d146(); virtual void d147(); virtual void d148(); virtual void d149(); virtual void d150(); virtual void d151(); virtual void d152(); virtual void d153(); virtual void d154(); virtual void d155(); virtual void d156(); virtual void d157(); virtual void d158(); virtual void d159(); virtual void d160(); virtual void d161(); virtual void d162(); virtual void d163(); virtual void d164(); virtual void d165(); virtual void d166(); virtual void d167(); virtual void d168(); virtual void d169(); virtual void d170(); virtual void d171(); virtual void d172(); virtual void d173(); virtual void d174(); virtual void d175(); virtual void d176(); virtual void v716(float *); virtual void d178(); virtual void d179(); virtual float v728(); };
struct A1_1c03a0 { char p0[32]; int f32; char p1[16]; int f52; char p2[4]; Cls *f60; char p3[4]; int f68; };
/* The depth-of-field group node: its children are drawn in a far pass and a near pass, each under its own
 * projection. */
struct DepthOfFieldNode {
    char _pad0[28];
    igDataList *_childList;
    unsigned char _enabled;
    char _pad33[3];
    float _blurPercent;
    float _focusDistance;
    float _fovX;
    float _fovY;
    float _nearPlane;
    float _farPlane;
    float _aspect;
    unsigned char _projectionDirty;
};
extern "C" void DepthOfField_UpdateProjections(DepthOfFieldNode *);
extern "C" void FUN_001db720(igSorter *sorter, igGeometry *geometry, igAttrStackManager *attrStack);

extern "C" Obj_1c03a0 *DAT_00562660[4];
extern "C" void *DAT_00562668[4];
extern "C" void *DAT_00562670[4];
extern "C" void *DAT_00562680[4];
extern "C" void *DAT_00562688[4];
extern "C" void *DAT_00562690[4];
extern "C" void *DAT_00562698[4];
extern "C" void *DAT_005626a0[4];
extern "C" void *DAT_005626a8[4];
extern "C" void *DAT_005626c0[4];
extern "C" void *DAT_005626c8[4];
extern "C" void *DAT_005626d0[4];
extern "C" void *DAT_005626d8[4];
extern "C" int DAT_00562678[4];
extern "C" unsigned char GPR_00554984;
extern "C" unsigned char GPR_00554b8c;
class DW4VC_108_4 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual int vX(int, int, int, int); };
class EnbayaSourceSlots24 {
public:
    virtual void pad0();
    virtual void pad1();
    virtual void pad2();
    virtual void pad3();
    virtual void pad4();
    virtual void pad5();
    virtual void pad6();
    virtual void pad7();
    virtual void pad8();
    virtual void pad9();
    virtual void pad10();
    virtual void pad11();
    virtual void pad12();
    virtual void pad13();
    virtual void pad14();
    virtual void pad15();
    virtual void pad16();
    virtual void pad17();
    virtual void pad18();
    virtual void pad19();
    virtual void pad20();
    virtual int f(int a, int b, int e);
};
class EnbayaSourceSlots26 {
public:
    virtual void pad0();
    virtual void pad1();
    virtual void pad2();
    virtual void pad3();
    virtual void pad4();
    virtual void pad5();
    virtual void pad6();
    virtual void pad7();
    virtual void pad8();
    virtual void pad9();
    virtual void pad10();
    virtual void pad11();
    virtual void pad12();
    virtual void pad13();
    virtual void pad14();
    virtual void pad15();
    virtual void pad16();
    virtual void pad17();
    virtual void pad18();
    virtual void pad19();
    virtual void pad20();
    virtual void pad21();
    virtual void pad22();
    virtual int f(int a, int b, int e);
};
class EnbayaSourceSlots28 {
public:
    virtual void pad0();
    virtual void pad1();
    virtual void pad2();
    virtual void pad3();
    virtual void pad4();
    virtual void pad5();
    virtual void pad6();
    virtual void pad7();
    virtual void pad8();
    virtual void pad9();
    virtual void pad10();
    virtual void pad11();
    virtual void pad12();
    virtual void pad13();
    virtual void pad14();
    virtual void pad15();
    virtual void pad16();
    virtual void pad17();
    virtual void pad18();
    virtual void pad19();
    virtual void pad20();
    virtual void pad21();
    virtual void pad22();
    virtual void pad23();
    virtual void pad24();
    virtual int f(int a, int b, int c, int g);
};
class EnbayaStreamSlots {
public:
    virtual void slot0();
    virtual void slot1();
    virtual void slot2();
    virtual void slot3();
    virtual float duration();
};
struct EnbayaSourceView {
    int _vtable; int _refCount; unsigned char _interpolationMethod[3]; unsigned char _drivenChannels; int _playMode;
    float _lastUpdateTimef; int _pad14; long long _lastUpdateTime; EnbayaStreamSlots *_enbayaAnimationStream;
};
struct EnbayaDecoderView { char _pad0[36]; float _interval; };
struct EnbayaKeyView { float _quaternion[4]; float _translation[4]; };
extern int DAT_00562720[4];
extern "C" float DAT_005626e8[4];
extern "C" float DAT_005626f0[4];
extern "C" int DAT_005626f8[4];
extern "C" float DAT_00562700[4];
extern "C" int FUN_002808f0(int);
typedef struct Obj_1c0e70 { char pad[32]; int f32; } Obj_1c0e70;
struct List_1c0f00 {
    char p0[8]; int count; char p12[4]; Ref **data;
    int getCount() const { return count; }
    void clear() {
        int n = count;
        for (int i = 0; i < n; i++) {
            Ref *r = data[i];
            if (r != 0) {
                r->u.w = r->u.w - 1;
                if (r->u.b.cnt == 0) igObject_Destroy((igObject *)r);
            }
        }
        int n2 = count;
        for (int i = 0; i < n2; i++) data[i] = 0;
        count = 0;
    }
};
struct Meta { char p0[60]; void *f60; };
extern void *DAT_00562728[4];
extern char DAT_00560000[];
/* Returns a decoding context to the pool's free list. */
extern "C" void FUN_001c16a0(igEnbayaContextPool *pool, void *context, int boneCount);

class Alloc { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void vX(void *); };
extern "C" int DAT_0048da00[4];
struct L_1c1450 { int pad0[2]; int count; int pad1; int *data; };
struct Obj_1c1450 { int vt; int p4; L_1c1450 *outer; int p12; L_1c1450 *dst; };
typedef struct L_1c1560 { char p0[8]; int n; int p1; int *d; } L_1c1560;
typedef struct O_1c1560 { char p0[8]; int c; int p1; int *d; } O_1c1560;
typedef struct T_1c1560 { char p0[8]; L_1c1560 *f8; L_1c1560 *f12; L_1c1560 *f16; } T_1c1560;
typedef struct PoolObject { int _vtable; int _refCount; } PoolObject;
typedef struct EnbayaIntList { int _pad0[2]; int _count; int _capacity; int *_data; int count() const { return _count; } } EnbayaIntList;
typedef struct EnbayaContextPoolView { int _pad0[2]; int _poolList; EnbayaIntList *_boneCountList; EnbayaIntList *_freeIndexList; } EnbayaContextPoolView;
extern "C" int DAT_0048da08[4];
struct PoolListHolder { PoolObject *p; ~PoolListHolder() {} };
typedef struct L_1c1a80 { char p0[8]; int n; int p1; int *d; } L_1c1a80;
typedef struct T_1c1a80 { char p0[8]; L_1c1a80 *f8; L_1c1a80 *f12; } T_1c1a80;
extern "C" void FUN_001c1950(T_1c1a80 *pool, igTDataList<void *> *list, int boneCount, int count);
extern "C" int FUN_0027ede0(int boneCount);
class DW4VC_92_0_1c1b50 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual int vX(int, int, int); };
struct S_1c1b50 { char pad[8]; int f8; DW4VC_92_0_1c1b50 *obj; };
struct EB;
class VA { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual int vX(int, int, int, int, int); };
struct EB { int pad[2]; int f8; VA *obj; };
class EnbayaSourceSlots {
public:
    virtual void pad0();
    virtual void pad1();
    virtual void pad2();
    virtual void pad3();
    virtual void pad4();
    virtual void pad5();
    virtual void pad6();
    virtual void pad7();
    virtual void pad8();
    virtual void pad9();
    virtual void pad10();
    virtual void pad11();
    virtual void pad12();
    virtual void pad13();
    virtual void pad14();
    virtual void pad15();
    virtual void pad16();
    virtual void pad17();
    virtual void pad18();
    virtual void pad19();
    virtual void pad20();
    virtual void pad21();
    virtual void pad22();
    virtual int f(int a, int b, int t);
};
struct EnbayaTransformSourceView {
    void *vtable;
    int _pad4;
    int _trackId;
    EnbayaSourceSlots *_enbayaAnimationSource;
};
class EnbayaSourceSlots_1c1bd0 {
public:
    virtual void pad0();
    virtual void pad1();
    virtual void pad2();
    virtual void pad3();
    virtual void pad4();
    virtual void pad5();
    virtual void pad6();
    virtual void pad7();
    virtual void pad8();
    virtual void pad9();
    virtual void pad10();
    virtual void pad11();
    virtual void pad12();
    virtual void pad13();
    virtual void pad14();
    virtual void pad15();
    virtual void pad16();
    virtual void pad17();
    virtual void pad18();
    virtual void pad19();
    virtual void pad20();
    virtual void pad21();
    virtual void pad22();
    virtual void pad23();
    virtual int f(int a, int b, int c, int d, int t);
};
struct EnbayaTransformSourceView_1c1bd0 {
    void *vtable;
    int _pad4;
    int _trackId;
    EnbayaSourceSlots_1c1bd0 *_enbayaAnimationSource;
};
class EnbayaSourceSlots_1c1bf0 {
public:
    virtual void pad0();
    virtual void pad1();
    virtual void pad2();
    virtual void pad3();
    virtual void pad4();
    virtual void pad5();
    virtual void pad6();
    virtual void pad7();
    virtual void pad8();
    virtual void pad9();
    virtual void pad10();
    virtual void pad11();
    virtual void pad12();
    virtual void pad13();
    virtual void pad14();
    virtual void pad15();
    virtual void pad16();
    virtual void pad17();
    virtual void pad18();
    virtual void pad19();
    virtual void pad20();
    virtual void pad21();
    virtual void pad22();
    virtual void pad23();
    virtual void pad24();
    virtual int f(int a, int b, int c, int t);
};
struct EnbayaTransformSourceView_1c1bf0 {
    void *vtable;
    int _pad4;
    int _trackId;
    EnbayaSourceSlots_1c1bf0 *_enbayaAnimationSource;
};
class EnbayaSourceSlots_1c1c10 {
public:
    virtual void pad0();
    virtual void pad1();
    virtual void pad2();
    virtual void pad3();
    virtual void pad4();
    virtual void pad5();
    virtual void pad6();
    virtual void pad7();
    virtual void pad8();
    virtual void pad9();
    virtual void pad10();
    virtual void pad11();
    virtual void pad12();
    virtual void pad13();
    virtual void pad14();
    virtual void pad15();
    virtual void pad16();
    virtual void pad17();
    virtual void pad18();
    virtual void pad19();
    virtual void pad20();
    virtual void pad21();
    virtual void pad22();
    virtual void pad23();
    virtual void pad24();
    virtual void pad25();
    virtual int f(int a, int b, int c, int d, int e, int t);
};
struct EnbayaTransformSourceView_1c1c10 {
    void *vtable;
    int _pad4;
    int _trackId;
    EnbayaSourceSlots_1c1c10 *_enbayaAnimationSource;
};
extern "C" unsigned long long FUN_001c0ea0(EnbayaSourceView *o);

struct Ref_1c1c60 { int w0; int rc; };
struct List_1c1c60 { int w0; int w4; int count; int cap; Ref_1c1c60 **data; };
class T_1c1c60 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();  virtual int vA(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47();  virtual void vB();
    char pad[60]; List_1c1c60 *f64; List_1c1c60 *f68; };

extern "C" void * *DAT_00562740[4];
struct T_1c1e10 { int w0; int refs; };
class DW4VC_100_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int vX(int); };
class DW4VC_128_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual int vX(int); };
class Obj_1c20b0;
struct PropertySet { char pad[56]; int props; };


class Obj_1c20b0 : public igVirtualObject {
public:
  virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22();
  virtual void configure(int);        /* +100 */
  virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
  virtual void setKind(int);          /* +128 */
  virtual void setValue(int);         /* +132 */
  
  int field8;
  int field12;
};
struct Controller {
  char pad0[32];
  int a32;
  Obj_1c20b0 *p36;
  int a40;
  char pad44[4];
  unsigned char flag48;
  char pad49[3];
  int a52;
  int a56;
  char pad60[13];
  unsigned char enabled;   /* +73 */
  char pad74[2];
  Obj_1c20b0 *f76, *f80, *f84, *f88, *f92, *f96, *f100, *f104, *f108;
};
typedef struct R_1c2880 { int w0; int refs; } R_1c2880;
typedef struct OL { char p[8]; int count; int cap; R_1c2880 **data; } OL;
typedef struct S_1c2880 { char pad[64]; OL *l64; OL *l68; char b72; char pad73[3]; R_1c2880 *f76; R_1c2880 *f80; R_1c2880 *f84; R_1c2880 *f88; R_1c2880 *f92; R_1c2880 *f96; R_1c2880 *f100; R_1c2880 *f104; R_1c2880 *f108; } S_1c2880;
struct E_1c2eb0 { char pad[96]; int f96; };
struct S0_1c2eb0 { char pad32[32]; E_1c2eb0 *f32; char pad36[24]; char f60; };
extern "C" void FUN_001c31e0(igTextureAttr *reflection);
struct Obj_1c3090 { int w0; unsigned refs; };
struct X_1c3090 { char pad[96]; int f96; };
class V_1c3090 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void a(int); virtual void d48(); virtual void b(int); virtual void c(); char pad[28]; X_1c3090 *f32; char pad2[24]; unsigned char f60; char pad3[3]; int f64; int f68; char pad4[1]; unsigned char f73; char pad5[2]; int f76; int f80; int f84; };
class SphereMapAllocator {
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
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void v39();
    virtual void v40();
    virtual void v41();
    virtual void v42();
    virtual void v43();
    virtual void v44();
    virtual void v45();
    virtual void v46();
    virtual void v47();
    virtual void v48();
    virtual void v49();
    virtual void v50();
    virtual void v51();
    virtual unsigned char *alloc(int);
    virtual void w53();
    virtual void w54();
    virtual void w55();
    virtual void w56();
    virtual void w57();
    virtual void w58();
    virtual void w59();
    virtual void w60();
    virtual void w61();
    virtual void w62();
    virtual void w63();
    virtual void release(void *);
};
extern "C" void FUN_001c4140(float *dir, igImage *image, int *face, unsigned char *dst);
struct R_1c4650 { int word0; int references; };
extern "C" R_1c4650 *DAT_00562760[4];
class V128_1c4650 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void vX(int); };
struct O_1c4650 { char p0[28]; R_1c4650 *ref; char p1[196]; unsigned int flags; char p2[316]; V128_1c4650 *v; };
/* matching construct: dummy virtual slots so the type-test call dispatches through the retail vtable offset 88 */
struct BoundVolume { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int ty(); };
extern "C" int FUN_001c4c20(igFrustCullTraversal *self, igNode *node, int result);
typedef int (*CullTravProc)(igFrustCullTraversal *, igNode *);
extern "C" void igFrustCullTraversal_TraverseNode(igFrustCullTraversal *arg0, igNode *arg1);
typedef struct CullFrustumView { char _pad0[52]; CullAttrState *_state; char _pad38[420]; float _frustum[16]; float *_lastWorld; float *_lastView; } CullFrustumView;
typedef struct CullBoundsView { char _pad0[8]; float _min[3]; float _max[3]; } CullBoundsView;

extern "C" int FUN_001c47f0(const float *matrix, const float *boxMin, const float *boxMax);
extern "C" float DAT_0048da28[4];
typedef struct ObjectRefFieldView { int _vtable; int _refCount; char _pad8[30]; unsigned char _flag38; char _pad27[13]; unsigned char _flag52; char _pad35[3]; int _metaObject; } ObjectRefFieldView;


extern "C" void *DAT_00562768[4];

struct FieldHolder { ObjectRefFieldView *p; ~FieldHolder() {} };
/* matching construct: dummy-virtual class so ->v100() / ->v132() dispatch through the attribute object's vtable */
class AttributeVtable { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int *v100(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void v132(int); };
struct AttributeObjView { int vt; int p4; int p8; AttributeVtable *f12; };
class ParticleAttributeObj;
struct FieldOffsetHolder { char pad[8]; int f8; };
/* matching construct: dummy-virtual class so ->vX() dispatches through the attribute object's vtable */
class ParticleAttributeObj { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void vX(); };
class V_1c5660;
class V_1c5660 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void vX(int); char pad4[16]; int f20; };
struct Item_1c5660 { char pad[12]; V_1c5660 *f12; };
struct Lst { char pad[8]; unsigned int cnt; int pad2; Item_1c5660 **items; };
struct Z_1c5660 { char pad[32]; Lst *f32; };
struct T_1c5740 { char p[8]; void **f; };
struct U_1c5740 { char p[8]; int f; };
class DW4VC_72_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual int vX(); };
struct List_1c5790 { char p[8]; int n; char q[4]; T **arr; };
typedef struct { char pad[4]; int f4; } R_1c58c0;
typedef struct { char pad[8]; int f8; char pad2[4]; int *f10; } L_1c58c0;
typedef struct { char pad[8]; L_1c58c0 *f8; } T_1c58c0;
struct OO;
class DW4VC_88_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); };
class DW4VC_156_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void vX(long long); };
class DW4VC_164_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual long long vX(long long); };
struct LL_1c59f0 { char pad[16]; char **items; };
struct OO { char pad[8]; LL_1c59f0 *list; };
struct EE { char pad[96]; int f96; };
typedef struct SgChildList { int _pad0[2]; int _count; int _pad0c; struct SgLinkNode **_data; } SgChildList;
struct SgLinkNode {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29(); virtual void v30();
    virtual void attach(SgLinkNode *); virtual void detach(SgLinkNode *);
    char _pad4[12];
    SgChildList *_parents;
    char _pad14[8];
    SgChildList *_children;
};
class DW4VC_140_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual int vX(int, int); };
class O_1c5d70 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual int vX(void *); int f4; char pad[12]; int f20; };
struct T_1c5d70 { char pad[28]; int f28; };
struct R_1c5d70 { O_1c5d70 *p; };
class X_1c5e20 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void vX(void *); };
struct L_1c5e20 { char pad8[8]; unsigned int f8; char pad12[4]; X_1c5e20 **f16; };
struct T_1c5e20 { char pad28[28]; L_1c5e20 *f28; };
struct S_1c5eb0;
struct Obj_1c5eb0 {
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31();
    virtual void vX(S_1c5eb0 *);
    int refs; int p8; int p12; int p16; int f20;
};
struct List_1c5eb0 { int p0, p4; int n; int p12; Obj_1c5eb0 **data; };
struct S_1c5eb0 { char pad[28]; List_1c5eb0 * list; List_1c5eb0 *getList() const { return list; } };
extern "C" int DAT_0048da58[4];
class VO { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual int v92(); virtual void * v96(int); virtual void d23(); virtual void d24(); virtual void d25(); virtual void v112(int, int); virtual void d27(); virtual int v120(); };
struct It_1c6110 { int w[5]; int f20; };
struct Lst_1c6110 { int w[2]; int cnt; int pad; It_1c6110 **arr; };
struct O_1c6110 : VO { int f4[6]; Lst_1c6110 *f28; };
struct S_1c6230 { char pad[20]; int f; };
class Elem_1c6260 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual int vX(); };
struct List_1c6260 { int pad0[2]; unsigned int count; int pad1; Elem_1c6260 **data; };
class Obj_1c6260 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual int vX(); char pad[24]; List_1c6260 *list; };
class Obj_1c6340 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void vX(int); };
struct Q_1c6340 { int p0; int p1; unsigned int count; int p3; Obj_1c6340 **data; };

typedef struct Ob { int w0; unsigned refs; int w2; } Ob;
typedef struct O_1c6520 { int w[6]; int f24; Ob *f28; Ob *f32; int f36; int f40; } O_1c6520;
/* Resolve the scene-node handle (+32) of a named child. With force == 0 and a cached handle (+32) it
 * returns 1 at once. Otherwise it refreshes the parent, drops the old handle, resets the interned
 * label (+36, +40), looks up the child index, reads two attributes of the child (a string and an
 * object-name string) into the stack holders, resolves both and, when their text differs, builds a
 * fresh handle, else it reuses the parent. The handle's own child index goes to +40 and the resolved
 * string to +36. Every return path releases the four stack holders.
 * Matching constructs: sp40/sp44 are RP holders (empty-destructor stack objects stay in memory, so
 * the `sp44 = 0; if (sp44) ++refs` pair is a store then a reload); sp3C/sp38/sp34 are the
 * address-taken out-parameter temporaries, released through their own memory slot (REL_TMP, re-read
 * after the decrement); a smart-pointer assignment holds the new value in a local (`n`) between the
 * retain and the store; sp40's pointer is read into `o40` before the `a = ...f8` test so the load
 * fills the branch delay slot. */
struct Obj_1c66c0 {
    int vt;
    union {
        int w;
        struct { unsigned cnt : 23; unsigned f : 9; } b;
    } u;
    const char *f8;
};
struct RP { Obj_1c66c0 *p; ~RP() {} };
struct Node {
    char pad0[24];
    char *f24;
    Obj_1c66c0 *f28;       /* parent handle */
    Obj_1c66c0 *f32;       /* resolved handle (reference counted) */
    char *f36;      /* interned label string */
    int f40;
};

typedef struct IniSectionNode { char _pad0[28]; int _parent; } IniSectionNode;

struct ShaderObject : public igObject { };
struct Factory { char pad32[32]; int f32; int f36; int f40; };
struct ShaderObject_1ca6c0 : public igObject {};
struct ShaderNameList : public igObject { int count; int capacity; char **data; };
struct ShaderMetaView;
struct DataPumpInfo : public igObject {};
struct ShaderProcessorTypes { char pad0[16]; igSmartPointer<DataPumpInfo> dataPumpInfo; char pad20[8]; void *types; };
struct ShaderProcessorView { char pad0[24]; int kind; int ini; char pad1[12]; int allocatorKey; ShaderProcessorTypes *info; };
struct ShaderCacheView;

extern "C" int FUN_001c7680(ShaderProcessorView *, int, char *, ShaderObject_1ca6c0 *, void *, unsigned char *);
struct L_1cafc0 { char p0[8]; int n; char pc[4]; int *items; };
struct IniValueObject : public igObject { union { int i; float f; unsigned char b; char *s; } value; };
struct IniValueList;
struct IniValueTarget;

struct IniSectionObject { int pad0; int _refCount; char *name; };
struct IniTypeTable { char pad0[60]; void *meta; };
struct IniShaderFactoryView;
static inline void releaseSection(IniSectionObject *object) {
    if (object != 0) {
        object->_refCount = object->_refCount - 1;
        if ((object->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy((igObject *)object);
        }
    }
}
struct SectionRef {
    IniSectionObject *p;
    SectionRef() {}
    SectionRef(IniSectionObject *object) : p(object) {
        if (p != 0) {
            p->_refCount = p->_refCount + 1;
        }
    }
    SectionRef(const SectionRef &other) : p(other.p) {
        if (p != 0) {
            p->_refCount = p->_refCount + 1;
        }
    }
    ~SectionRef() {
        releaseSection(p);
    }
    SectionRef &operator=(const SectionRef &other) {
        IniSectionObject *next = other.p;
        if (next != 0) {
            next->_refCount = next->_refCount + 1;
        }
        release();
        p = next;
        return *this;
    }
    void release() {
        releaseSection(p);
    }
    IniSectionObject *get() const { return p; }
};
extern "C" SectionRef FUN_001cd9f0(IniShaderFactoryView *self, char *name);
class DW4VC_96_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual int vX(int); };
struct IniObjectRef { int pad0; int _refCount; };
struct IniStringValue { char pad0[8]; char *text; };
struct IniEntry { char *name; IniStringValue *value; };
struct IniEntryList { char pad0[8]; int count; char pad1[4]; IniEntry **data; };
struct IniNodeList;
struct IniNode { int type; char pad0[4]; IniEntryList *entries; char pad1[4]; IniNodeList *children; };
struct IniNodeList { char pad0[8]; int count; char pad1[4]; IniNode **data; };
struct IniShaderFactoryView;
struct IniDocument { int pad0; int _refCount; char *text; };
struct IniCacheTable { int pad0; int _refCount; };
struct IniSourceList { char pad0[20]; void *entries; };
struct IniFieldEntry { char pad0[56]; IniCacheTable *cache; };
struct IniFactoryState { char pad0[20]; int mode; char pad1[32]; IniCacheTable *cache; };
extern "C" int text_system[4];
struct IniSectionText : public igObject { char *text; };
struct IniNamedObject : public igObject {};
struct IniFieldEntry_1cdbb0 { char pad0[56]; IniNamedObject *cache; };
struct IniFactoryView { char pad0[20]; int mode; char pad1[32]; IniNamedObject *cache; };
class IniFileHandle : public igVirtualObject {
public:
        virtual void d1();    virtual void d2();    virtual void d3();    virtual void d4();    virtual void d5();    virtual void d6();    virtual void d7();    virtual void d8();    virtual void d9();    virtual void d10();    virtual void d11();    virtual void d12();    virtual void d13();    virtual void d14();    virtual void d15();    virtual void d16();    virtual void d17();    virtual void d18();    virtual void d19();    virtual void d20();    virtual void d21();    virtual void d22();
    virtual int open(char *, const char *);
    virtual void close();
    virtual void read(char *, int, int);
    virtual void d26();    virtual void d27();    virtual void d28();    virtual void d29();    virtual void d30();    virtual void d31();    virtual void d32();    virtual void d33();    virtual void d34();    virtual void d35();
    virtual void seek(int, int);
    virtual int tell();
};
struct IniStringObject : public igObject { char *text; };
static inline void drop(IniStringObject *object) {
    if (object != 0) {
        object->_refCount = object->_refCount - 1;
        if ((object->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(object);
        }
    }
}
class IniStringRef {
public:
    IniStringObject *p;
    IniStringRef() {}
    IniStringRef(const IniStringRef &o);
    ~IniStringRef() { drop(p); }
};
class IniPathResolver {
public:
    virtual void d0();    virtual void d1();    virtual void d2();    virtual void d3();    virtual void d4();    virtual void d5();    virtual void d6();    virtual void d7();    virtual void d8();    virtual void d9();    virtual void d10();    virtual void d11();    virtual void d12();    virtual void d13();    virtual void d14();    virtual void d15();    virtual void d16();    virtual void d17();    virtual void d18();    virtual void d19();    virtual void d20();
    virtual IniStringRef resolve(char *);
};
class IniFileObject : public igVirtualObject {
public:
    virtual void d1();    virtual void d2();    virtual void d3();    virtual void d4();    virtual void d5();    virtual void d6();    virtual void d7();    virtual void d8();    virtual void d9();    virtual void d10();    virtual void d11();    virtual void d12();    virtual void d13();    virtual void d14();    virtual void d15();    virtual void d16();    virtual void d17();    virtual void d18();    virtual void d19();    virtual void d20();    virtual void d21();    virtual void d22();
    virtual int open(char *, const char *);
    virtual void close();
    
    char pad0[4];
    int handle;
};

static inline void retain_1ce400(IniStringObject *object) {
    if (object != 0) {
        object->_refCount = object->_refCount + 1;
    }
}
static inline void release_1ce400(IniStringObject *object) {
    if (object != 0) {
        object->_refCount = object->_refCount - 1;
        if ((object->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(object);
        }
    }
}
struct StringObjectRef {
    IniStringObject *p;
    StringObjectRef(IniStringObject *object) : p(object) { retain_1ce400(p); }
    ~StringObjectRef() { release_1ce400(p); }
};
extern "C" igObject *DAT_00562790[4];

extern "C" igSmartPointer<igVolumeList> FUN_0018f760(igMemoryPoolView *allocator);
typedef struct MatrixStackEntry { float f[16]; } MatrixStackEntry;
typedef struct ReleasableList { int pad0, pad4; int n; int cap; int *data; } ReleasableList;
typedef struct MatrixStackList { int pad0, pad4; int n; int cap; MatrixStackEntry *data; } MatrixStackList;
typedef struct CountedObject { int vt; int rc; } CountedObject;
typedef struct TraversalMatrixState { int p[8]; MatrixStackList *mats; ReleasableList *objs; } TraversalMatrixState;

struct HitMetaView { char pad0[8]; int index; };
struct HitMatrix { float m[16]; };
class HitBound {
public:
    virtual void d0();    virtual void d1();    virtual void d2();    virtual void d3();    virtual void d4();    virtual void d5();    virtual void d6();    virtual void d7();    virtual void d8();    virtual void d9();    virtual void d10();    virtual void d11();    virtual void d12();    virtual void d13();    virtual void d14();    virtual void d15();    virtual void d16();    virtual void d17();    virtual void d18();    virtual void d19();
    virtual HitMetaView *getMeta();
};
struct HitBoundList { char pad0[16]; HitBound **data; };
struct HitMatrixStack { char pad0[8]; int count; char pad1[4]; HitMatrix *data; };
struct HitSegment { char pad0[8]; float x, y, z; };
struct HitSegmentList { char pad0[8]; unsigned int count; char pad1[4]; HitSegment **data; };
struct HitPointerList { char pad0[16]; void **data; };
struct HitQuery { char pad0[8]; void *volume; HitSegmentList *segments; HitPointerList *aux; };
struct HitAttr;
struct HitAttrList { char pad0[8]; unsigned int count; char pad1[4]; HitAttr **data; };
struct HitNode { char pad0[12]; HitBound *bound; char pad1[16]; HitAttrList *attrs; };
struct HitReport {
    int type;
    HitQuery *query;
    int context;
    HitMatrix *matrix;
    void *object;
    float distance;
    igVec3f local;
    igVec3f point;
    igVec3f normal;
    int index;
    int first;
    int second;
    int pad0;
};
struct HitTraversal;
typedef int (*HitCallback)(HitTraversal *, HitNode *, HitReport *);
struct HitTraversal {
    char pad0[32];
    HitMatrixStack *matrices;
    int context;
    HitQuery *query;
    unsigned int flags;
    HitCallback callback;
    HitBoundList *cache;
    HitBound *scratch;
};
extern "C" int FUN_0018ffa0(void**, void**);
extern "C" int FUN_00190010(void**, int);
extern "C" void FUN_001901b0(HitBound *, HitMatrix *);
extern "C" int FUN_001cef70(HitTraversal *, HitAttr *, HitBound *, igVec3f *, igVec3f *, int *, int *, void *, long long);
typedef struct S_1cf990 { char pad4[4]; int f4; } S_1cf990;
typedef struct Ls_1cf990 { char pad8[8]; int n; char pad12[4]; S_1cf990 **data; } Ls_1cf990;
typedef struct A_1cf990 { char pad36[36]; Ls_1cf990 *f36; } A_1cf990;
typedef struct B_1cf990 { char pad28[28]; Ls_1cf990 *f28; } B_1cf990;
class TraversalNode {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual int getMeta();
    virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36();
    virtual void setContext(int);
    char pad0[28];
    float transform[16];
};
struct TraversalMatrix { float m[16]; };
struct MatrixStack { char pad0[8]; int count; char pad1[4]; TraversalMatrix *data; };
struct NodeRefObject { int pad0; int _refCount; };
struct NodeStack { char pad0[8]; int count; char pad1[4]; NodeRefObject **data; };
class ModelTraversal;
typedef int (*TraversalCallback)(ModelTraversal *, TraversalNode *);
class ModelTraversal {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual int context();
    int pad0;
    unsigned char enabled;
    TraversalCallback callback;
    char pad1[16];
    MatrixStack *matrices;
    NodeStack *nodes;
};
struct SceneMatrix { float m[16]; };
class SceneDrawItem {
public:
    virtual void d0();    virtual void d1();    virtual void d2();    virtual void d3();    virtual void d4();    virtual void d5();    virtual void d6();    virtual void d7();    virtual void d8();    virtual void d9();    virtual void d10();    virtual void d11();    virtual void d12();    virtual void d13();    virtual void d14();    virtual void d15();    virtual void d16();    virtual void d17();    virtual void d18();    virtual void d19();    virtual void d20();    virtual void d21();    virtual void d22();    virtual void d23();    virtual void d24();    virtual void d25();    virtual void d26();    virtual void d27();    virtual void d28();    virtual void d29();
    virtual void setMatrix(SceneMatrix *);
};
struct SceneDrawItemPool { char pad0[8]; int capacity; char pad1[4]; SceneDrawItem **data; int used; };
struct SceneRenderer { char pad0[52]; void *state; char pad1[16]; SceneDrawItemPool *pool; };
class SceneTransformNode;
struct SceneChildList { char pad0[8]; int count; char pad1[4]; SceneTransformNode **data; };
class SceneTransformNode {
public:
    virtual void d0();    virtual void d1();    virtual void d2();    virtual void d3();    virtual void d4();    virtual void d5();    virtual void d6();    virtual void d7();    virtual void d8();    virtual void d9();    virtual void d10();    virtual void d11();    virtual void d12();    virtual void d13();    virtual void d14();    virtual void d15();    virtual void d16();    virtual void d17();    virtual void d18();    virtual void d19();
    virtual int getMeta();
    virtual void d21();    virtual void d22();    virtual void d23();    virtual void d24();    virtual void d25();    virtual void d26();    virtual void d27();    virtual void d28();    virtual void d29();    virtual void d30();    virtual void d31();    virtual void d32();    virtual void d33();    virtual void d34();    virtual void d35();    virtual void d36();
    virtual void setContext(int);
    char pad0[24];
    SceneChildList *children;
    SceneMatrix local;
    char pad1[12];
    SceneMatrix bind;
    char *block;
};
class DW4VC_112_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual int vX(int, int); };
class VC_1d0330 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void vX(); };
struct L_1d0330 { int pad[2]; unsigned int n; int pad2; VC_1d0330 **a; };
struct O_1d0330 { char pad[28]; L_1d0330 *l; };
struct L_1d03b0 { char pad0[8]; unsigned int n; char pad1[4]; char **data; };
struct S_1d03b0 { char pad[28]; L_1d03b0 *list; };
struct D_1d03b0 { char pad[8]; int off; };
class LS { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual int vA(void *); virtual int vB(void *); };
class igLightStateEntry {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25();
    virtual void apply();
};
struct igLightStateList {
    char pad0[8];
    unsigned int count;
    char pad1[4];
    igLightStateEntry **data;
};
struct igLightStateSetView {
    char pad0[32];
    igLightStateList *lights;
};
struct RangeRefObject { int pad0; int _refCount; };
struct RangeFloatList { char pad0[8]; int count; char pad1[4]; float *data; };
struct RangeRefList { char pad0[8]; int count; char pad1[4]; RangeRefObject **data; };
struct RangeLookup {
    char pad0[28];
    RangeRefList *refs;
    RangeFloatList *times;
    RangeRefObject *current;
    int index;
    float start;
    float end;
    char pad1[12];
    RangeFloatList *blends;
};
extern "C" float DAT_0048da38[4];
extern "C" float DAT_0048da40[4];
extern "C" unsigned char GPR_00554988;
struct Src_1d08d0 { char pad[20]; int f20; };
struct Self { char pad[44]; Src_1d08d0 *f44; igFloatList *f48; igFloatList *f52; igUnsignedCharList *f56; };
struct ByteListRef {
    igUnsignedCharList *p;
    ByteListRef(igUnsignedCharList *object) : p(object) {}
    ~ByteListRef() {
        if (p != 0) {
            p->_refCount = p->_refCount - 1;
            if ((p->_refCount & 0x7FFFFF) == 0) igObject_Destroy(p);
        }
    }
};
extern "C" int FUN_001d0c90(void *);
struct KeyFloatList { char pad0[8]; unsigned int count; char pad1[4]; float *data; };
struct KeyIndexList { char pad0[8]; int count; int capacity; int *data; int getCount() const { return count; } };
typedef union KeyFloatBits { float f; struct { unsigned char p0, p1, p2; unsigned char lo : 7; unsigned char sign : 1; } b; } KeyFloatBits;
class KeyChannel {
public:
    virtual void d0();    virtual void d1();    virtual void d2();    virtual void d3();    virtual void d4();    virtual void d5();    virtual void d6();    virtual void d7();    virtual void d8();    virtual void d9();    virtual void d10();    virtual void d11();    virtual void d12();    virtual void d13();    virtual void d14();    virtual void d15();    virtual void d16();    virtual void d17();    virtual void d18();    virtual void d19();    virtual void d20();    virtual void d21();
    virtual void setKeyCount(int);
    virtual void d23();
    virtual void setKeyValue(int, float);
    virtual void d25();
    virtual void setKeyIndex(int, int);
};
struct KeyChannelList { char pad0[8]; int count; char pad1[4]; KeyChannel **data; };
struct KeyChannelOwner { char pad0[16]; KeyChannelList *channels; };
struct KeyReducer { char pad0[44]; KeyFloatList *values; KeyIndexList *kept; char pad1[4]; KeyChannelOwner *owner; };
struct igFloatListView {
    char pad0[8];
    int count;
    char pad1[4];
    float *data;
};
struct KeyTrackHeader {
    char pad0[16];
    igFloatListView *keys;
};
struct KeyTrackListView {
    char pad0[16];
    KeyTrackHeader **data;
};
struct KeyTrackOwner {
    char pad0[32];
    int count;
    KeyTrackListView *tracks;
};
typedef struct K_1d18a0 { char pad[16]; unsigned *keys; } K_1d18a0;
typedef struct S_1d18a0 { char pad[24]; int f24; char pad2[28]; unsigned f56; } S_1d18a0;
struct KeyAnimTrack { char pad0[8]; int keyCount; K_1d18a0 *keyTimes; igFloatListView *values; igFloatListView *tangents; };
struct KeyAnimTrackList { char pad0[16]; KeyAnimTrack **data; };
struct KeyAnim { char pad0[8]; int keyCount; K_1d18a0 *keyTimes; char pad16[8]; int playMode; int interpolation; int trackCount; KeyAnimTrackList *tracks; char pad40[8]; long long startTime; unsigned int duration; };
extern "C" void FUN_001d1a90(KeyAnim *self, igFloatListView *out, long long time);
static inline float keyLerp(float a, float b, float t) { return a + t * (b - a); }
struct MorphWordList { char pad0[8]; int count; char pad1[4]; unsigned int *data; };
struct MorphShortList { char pad0[16]; unsigned short *data; };
struct MorphParentTable { char pad0[16]; unsigned short *data; };
struct MorphBaseIndices { char pad0[12]; unsigned short *data; };
struct MorphTables {
    char pad0[12];
    MorphBaseIndices *base;
    MorphParentTable *parents;
    MorphShortList *steps;
    unsigned int firstFrame;
    unsigned int lastFrame;
    unsigned short leafCount;
};
class MorphIndexBuffer {
public:
    virtual void d0();    virtual void d1();    virtual void d2();    virtual void d3();    virtual void d4();    virtual void d5();    virtual void d6();    virtual void d7();    virtual void d8();    virtual void d9();    virtual void d10();    virtual void d11();    virtual void d12();    virtual void d13();    virtual void d14();    virtual void d15();    virtual void d16();    virtual void d17();    virtual void d18();    virtual void d19();    virtual void d20();    virtual void d21();    virtual void d22();
    virtual unsigned short *lock(int, int, int);
    virtual void d24();
    virtual void unlock(unsigned short *, int, int, int);
};
class MorphTarget {
public:
    virtual void d0();    virtual void d1();    virtual void d2();    virtual void d3();    virtual void d4();    virtual void d5();    virtual void d6();    virtual void d7();    virtual void d8();    virtual void d9();    virtual void d10();    virtual void d11();    virtual void d12();    virtual void d13();    virtual void d14();    virtual void d15();    virtual void d16();    virtual void d17();    virtual void d18();    virtual void d19();    virtual void d20();    virtual void d21();    virtual void d22();    virtual void d23();    virtual void d24();    virtual void d25();    virtual void d26();    virtual void d27();    virtual void d28();    virtual void d29();    virtual void d30();    virtual void d31();    virtual void d32();    virtual void d33();    virtual void d34();    virtual void d35();    virtual void d36();
    virtual void setRange(int, unsigned int, int);
};
struct MorphTargetList { char pad0[16]; MorphTarget **data; };
struct MorphLevelState {
    char pad0[32];
    MorphTargetList *targets;
    char pad1[8];
    MorphTables *tables;
    MorphIndexBuffer *indices;
    char pad2[4];
    MorphWordList *changed;
    unsigned int shownFrame;
    unsigned int frame;
    unsigned short shownLevel;
    unsigned short level;
};

struct S_1d2230 { int p[3]; int t; };
class O_1d2230 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void v128(int); virtual void v132(int);
  int p[4]; int f20; };
struct L1d { int a; int b; int count; int cap; int *data; };

struct ObjectListOwner { char pad[16]; igTDataList<igObject *> *_list; };
struct S_1d32f0;
class V_1d32f0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual int c(); virtual S_1d32f0 *g(int); };
struct S_1d32f0 : V_1d32f0 { char p[16]; int f20; };
class DW4VC_120_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual int vX(); };
struct NodeParentListView { int _vtable; unsigned int _refCount; int _count; int _capacity; void **_data; };
class NodeSlots {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20();
    virtual int getChildCount();
    virtual class GroupChild *getChild(int);
    virtual void s23(); virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
    virtual void s32();
    virtual void replaceChild(int index, void *with);
    int _refCount;
};
class GroupChild : public NodeSlots { public: char pad[20]; NodeParentListView *_parents; };

extern "C" void * *DAT_00562798[4];
extern "C" void * *DAT_005627a0[4];
extern "C" void * *DAT_005627a8[4];
extern "C" void * *DAT_005627b0[4];
extern "C" void * *DAT_005627b8[4];
extern "C" void *DAT_005627c0[4];
extern "C" void * *DAT_005627c8[4];
extern "C" void * *DAT_005627d0[4];
extern "C" void * *DAT_005627d8[4];
class DW4VC_136_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual int vX(int); };
class DW4VC_140_3 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual int vX(int, int, int); };
struct Obj_1d39b0 { int w0; int references; };
struct T_1d39b0 {
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
    virtual int vX();
};
class VA_1d3e20 {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
    virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
    virtual void v30(void *);
};
class VB {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
    virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
    virtual void v30(int);
};
extern "C" void FUN_001d3c60(igPlanarShadowShader *shader, igCommonTraversal *traversal);
extern "C" int DAT_005627e0[4];
extern "C" int DAT_005627e8[4];
extern "C" int DAT_005627f0[4];
extern "C" int DAT_005627f8[4];
extern "C" int DAT_00562800[4];
extern "C" int DAT_00562808[4];
extern "C" int DAT_00562810[4];
extern "C" int DAT_00562818[4];
extern "C" int DAT_00562820[4];
extern "C" int DAT_00562828[4];
extern "C" int DAT_00562830[4];
extern "C" int DAT_00562838[4];
extern "C" int DAT_00562840[4];
extern "C" int DAT_00562848[4];
extern "C" int DAT_00562850[4];
extern "C" int DAT_00562858[4];
extern "C" int DAT_00562860[4];
extern "C" int DAT_00562870[4];
extern "C" int DAT_00562878[4];
extern "C" int DAT_00562880[4];
extern "C" int DAT_005628d0[4];
extern "C" int DAT_005628d8[4];
class ShadowRefObj { public: virtual void s0(); int refCount; };
class ShadowSetupObj : public ShadowRefObj { public: virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(int); virtual void s24(); virtual void s25(); virtual void s26(int); virtual void s27(int); virtual void s28(int); virtual void s29(); virtual void s30(int); virtual void s31(int); virtual void s32(int); virtual void s33(int); char pad8[44]; unsigned char *pixels; };
class ShadowFogObj { public: virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(int); virtual void s24(); virtual void s25(); virtual void s26(int); virtual void s27(int); virtual void s28(int); virtual void s29(); virtual void s30(int); virtual void s31(float); virtual void s32(int); virtual void s33(int); };
struct ShadowColor { float r, g, b, a; };
struct ShadowColorObj { char pad0[12]; int enabled; ShadowColor color; char pad32[28]; int packed;
    void setColor(ShadowColor &c) { color = c; packed = igVec4f_PackColor((float *)&c, 1); }
};
struct ShadowModeObj { char pad0[12]; int mode; };

struct ShadowRef {
    ShadowSetupObj *p;
    ~ShadowRef() {
        ShadowSetupObj *object = p;
        if (object) {
            --object->refCount;
            if (((unsigned long long)(long long)object->refCount & 0x7fffffULL) == 0)
                igObject_Destroy((igObject *)object);
        }
    }
};
typedef struct R_1d5430 { char pad[4]; int f4; } R_1d5430;
struct V4_1d5a70 { float x, y, z, w; };
class Ob_1d5a70 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void v30(V4_1d5a70 *); };
struct P { char p0[68]; float f68; char p72[16]; int w88; int w92; char p96[20]; Ob_1d5a70 *o116; char p120[32]; int w152; int w156; char p160[4]; int w164; char p168[24]; int w192; int w196; char p200[37]; unsigned char b237; };
struct Q_1d5a70 { char p0[52]; int w52; char p56[12]; int w68; };
typedef struct A0_1d5c40 { char pad144[144]; int f90; unsigned char f94; } A0_1d5c40;
typedef struct A1_1d5c40 { char pad52[52]; int f34; char pad56[12]; int f44; char pad72[160]; int fe8; } A1_1d5c40;
typedef struct S1_1d5e00 { char pad52[52]; int f34; char pad68[12]; int f44; } S1_1d5e00;
struct L_1d5e60 { char pad[8]; int count; char pad2[4]; int *data; };
struct A_1d5e60 { char pad[28]; struct L_1d5e60 *f28; };
struct L_1d5ef0 { char pad[8]; int count; char pad1[4]; int *data; };
struct S60 { char pad[60]; struct L_1d5ef0 *f60; };
typedef struct A_1d5f70 { char pad[208]; unsigned char f208; } A_1d5f70;
extern "C" int FUN_00191860(void *, float, float, float, float, float, float);
struct Mx { float m[16]; };
class V_1d6060 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void vX(Mx *); };
struct O_1d6060 { char p0[32]; float f32, f36, f40, f44, f48, f52, f56; char p60[28]; V_1d6060 *f88; V_1d6060 *f92; char p96[28]; float f124, f128; char p132[12]; V_1d6060 *f144; char p148[60]; unsigned char f208; char p209[3]; float f212, f216, f220, f224; };
struct Src_1d6190 { char p[96]; float f96; char p1[16]; float f116; float f120; float f124; float f128; float f132; float f136; };
struct S_1d6190 { char p0[32]; float f32; float f36; float f40; float f44; float f48; float f52; float f56; char p1[44]; int f104; char p2[92]; struct Src_1d6190 *src; };
struct R_1d6240 { int w0; int rc; };
struct L_1d6240 { char pad[8]; int cnt; int cap; int *data; };
struct S_1d6240 { char pad[64]; struct L_1d6240 *f64; };
class DW4VC_112_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual int vX(); };


typedef struct NodeList { char p0[8]; unsigned count; char p1[4]; int *data; } NodeList;
typedef struct TraversedNode { char p0[28]; NodeList *children; } TraversedNode;
typedef struct PathEntry : public igObject { } PathEntry;
struct O_1d65e0 { char pad[20]; int f20; int f24; igObject *f28; };
struct ChildOwner { char pad[20]; int f20; };
struct ChildObject : public igObject { };
struct EE_1d6790;
struct OO_1d6790;
struct AA;
class DW4VC_124_0_1d6790 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual long long vX(); };
class DW4VC_128_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual long long vX(); };
class DW4VC_260_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual long long vX(); };
struct OO_1d6790 { char pad[32]; long long f32; long long f40; };
struct AA { char pad[8]; unsigned int n; };
struct EE_1d6790 { char pad[24]; void *f24; };
struct VertexFormat { int flags; };
struct VertexArray {
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26();
    virtual int setPosition(int index, float *position);
};
struct Primitive : public igVirtualObject {
    virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
    virtual int configure(VertexFormat *format, int vertices, int a, int b);
    virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36();
    virtual int setPrimitives(int type, int count, int offset);
    
    int f8;
    VertexArray *vertices;
};

/* Configure the stage render-state objects (viewport/camera/clear/light setup). A straight run of
 * configuration writes: object fields (+12 mode words, +20/+24/+36 flags), the virtual setters at
 * vtable offsets +100 (select) and +128 (value) on the objects held in the globals
 * 0x5628f0..0x5629f0, a unit-colour vector copied into one object (0x562940), then the scene list
 * (0x5629a0, +32) is cleared and refilled with the object FUN_001d6900 returns, and the
 * projection/view helpers FUN_00191860 / igMatrix44f_MakeLookAt get their literal arguments. Names are role
 * hypotheses; evidence: asm/FUN_001d6a70.s. Matching constructs: dummy virtual slots give the
 * retail vtable offsets (offset = 8 + 4 * index); the stack vectors are declared in the order eye,
 * origin, up, white, forward so the frame offsets match, and the Vec4 is copied with float
 * loads/stores. Build: local/mwcps2/combat/mwccps2.exe (sha256
 * acf1088553362dddef7eee2d269848b03208e29fd26caa441848e57b6299786a), -O3 -Iinclude. */
struct Vec4 { float x, y, z, w; };
class Gfx;
class Lens;
class GfxQuad;
class GfxScene;
class GfxVec;
/* Generic render-state object: select() is +100, set() +128. */
class Gfx {
public:
  virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22();
  virtual void select(int);           /* +100 */
  virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
  virtual void set(int);              /* +128 */
  virtual void set2(int);             /* +132 */
  virtual void set3(int);             /* +136 */
  int refs;                           /* +4 */
  int w8;
  int mode;                           /* +12 */
  int w16;
  int w20;
  unsigned char flag24;
  char pad25[3];
  int w28, w32;
  int w36;
};
class GfxQuad {
public:
  virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22();
  virtual void select(int);
  virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
  virtual void set(int, int, int, int);
};
class GfxVec {
public:
  virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22();
  virtual void select(int);
  virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
  virtual void set(const Vec4 *);
};
struct SceneList { int vtbl, refs, count, capacity; int *data; };
class GfxScene { public: int vtbl, refs, w8, mode; int w16, w20, w24, w28; SceneList *items; };
struct Ref_1d6a70 { int vtbl; int refs; };
struct Lens {
  int vtbl, refs, w8, mode;
  Vec4 color;                             /* +16 */
  int w32, w36, w40, w44;
  long long w48;
  int w56, w60, w64;
};
extern "C" Gfx *DAT_005628f0[4];
extern "C" Gfx *DAT_005628f8[4];
extern "C" Lens *DAT_00562900[4];
extern "C" Gfx *DAT_00562908[4];
extern "C" Gfx *DAT_00562910[4];
extern "C" Gfx *DAT_00562918[4];
extern "C" Gfx *DAT_00562920[4];
extern "C" Gfx *DAT_00562928[4];
extern "C" Gfx *DAT_00562930[4];
extern "C" Gfx *DAT_00562938[4];
extern "C" Lens *DAT_00562940[4];
extern "C" Gfx *DAT_00562948[4];
extern "C" Gfx *DAT_00562950[4];
extern "C" Gfx *DAT_00562958[4];
extern "C" Gfx *DAT_00562960[4];
extern "C" Gfx *DAT_00562968[4];
extern "C" Gfx *DAT_00562970[4];
extern "C" Gfx *DAT_00562978[4];
extern "C" GfxQuad *DAT_00562980[4];
extern "C" GfxQuad *DAT_00562988[4];
extern "C" GfxQuad *DAT_00562990[4];
extern "C" Gfx *DAT_00562998[4];
extern "C" GfxScene *DAT_005629a0[4];
extern "C" Gfx *DAT_005629a8[4];
extern "C" Gfx *DAT_005629b0[4];
extern "C" Gfx *DAT_005629b8[4];
extern "C" Gfx *DAT_005629c0[4];
extern "C" GfxVec *DAT_005629c8[4];
extern "C" Gfx *DAT_005629d0[4];
extern "C" Gfx *DAT_005629d8[4];
extern "C" Gfx *DAT_005629e0[4];
extern "C" Gfx *DAT_005629e8[4];
extern "C" Gfx *DAT_005629f0[4];

extern "C" int DAT_004e4820[];
class ShadowStateObj : public ShadowRefObj { public: virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22(int); virtual void s23(int); virtual void s24(); virtual void s25(); virtual void s26(int); virtual void s27(int); virtual void s28(int); virtual void s29(); virtual void s30(int); virtual void s31(int); virtual void s32(int); virtual void s33(int); };
class ShadowViewportObj { public: virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29(); virtual void s30(int, int, int, int, float, float); };
static inline void addRef(ShadowRefObj *o) { if (o) { o->refCount++; } }
static inline void releaseRef(ShadowRefObj *o) {
    if (o) {
        --o->refCount;
        if (((unsigned long long)(long long)o->refCount & 0x7fffffULL) == 0)
            igObject_Destroy((igObject *)o);
    }
}
struct ShadowRef_1d7120 {
    ShadowRefObj *p;
    ShadowRef_1d7120(ShadowRefObj *x) : p(x) { addRef(p); }
    ~ShadowRef_1d7120() {
        ShadowRefObj *object = p;
        if (object) {
            --object->refCount;
            if (((unsigned long long)(long long)object->refCount & 0x7fffffULL) == 0)
                igObject_Destroy((igObject *)object);
        }
    }
};
struct ShadowTexState {
    char pad0[12]; int mode; ShadowRefObj *image; ShadowRefObj *source; ShadowRefObj *target;
    int f28; int f32; int f36; int f40; int width; int height;
    void set_image(ShadowRefObj *v) { addRef(v); releaseRef(image); image = v; }
    void set_source(ShadowRefObj *v) { addRef(v); releaseRef(source); source = v; }
    void set_target(ShadowRefObj *v) { addRef(v); releaseRef(target); target = v; }
};
struct ShadowTarget : public ShadowRefObj {
    char pad8[4]; int f12; int f16; int f20; unsigned char f24; char pad25[7]; ShadowRefObj *texture; int f36; int width; int height;
    int f48; int f52; int f56; int f60;
    void setSize(int w, int h) { width = w; height = h; }
    void set_texture(ShadowRefObj *v) { addRef(v); releaseRef(texture); texture = v; }
};
struct ShadowHolder { char pad0[12]; ShadowRefObj *target;
    void set_target(ShadowRefObj *v) { addRef(v); releaseRef(target); target = v; }
};
struct ShadowFlagObj { char pad0[82]; unsigned char enabled; };
struct ProjectiveShadowView {
    char pad0[100];
    ShadowStateObj *f100;
    ShadowStateObj *f104;
    int pad108;
    char f112[16];
    int width;
    int height;
    int format;
    char pad140[4];
    ShadowTarget *target;
    ShadowHolder *holder;
    ShadowStateObj *texture;
    ShadowStateObj *f156;
    ShadowStateObj *f160;
    ShadowStateObj *f164;
    ShadowTexState *texState;
    ShadowStateObj *image;
    ShadowViewportObj *f176;
    char pad180[4];
    ShadowStateObj *f184;
    char pad188[40];
    ShadowViewportObj *f228;
};
extern "C" float DAT_004e0f30[16];
struct G_1d7630 { int pad[2]; int f8; };
extern "C" G_1d7630 *DAT_0055ee30[4];
class Ob_1d7630 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();  virtual void vX(float *); };
struct Src_1d7630 { char p0[96]; float f96; char p1[16]; float f116, f120, f124, f128, f132, f136; };
struct T_1d7630 {
    char p0[36]; float p[3]; float q[3]; float f60; float f64; float f68; float f72[5];
    Ob_1d7630 *f92; Ob_1d7630 *f96; int f100; float f104; float f108; char p2[80]; Src_1d7630 *f192; int f196; int f200; char f204[4]; unsigned char f208; char p3[3];
    float f212, f216, f220, f224;
};
typedef struct ShaderTraversalPair { void *_meta; void *_function; } ShaderTraversalPair;
typedef struct ShaderTraversalPairs { ShaderTraversalPair _pairs[4]; } ShaderTraversalPairs;
extern "C" ShaderTraversalPairs DAT_0048dac0;
extern "C" igTDataList<igTraversalFunctionPtr> *DAT_005628e0[4];
extern "C" igTDataList<igTraversalFunctionPtr> *DAT_005628e8[4];
class DW4VCSR_128_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual int vX(float *); };
typedef struct L_1d7b70 { char p[8]; int n; char q[4]; int *arr; } L_1d7b70;
typedef struct S0_1d7b70 {
    char p0[28]; L_1d7b70 *f28; unsigned char b32; char p1[51]; L_1d7b70 *f84; char p2[4]; int f92; int f96; int f100;
    char p3[36]; unsigned char b140; char p4[7]; int f148; char p5[4]; int f156; char p6[16]; int f176;
    char p7[16]; int f196; int f200; int f204; char p8[20]; int f228;
} S0_1d7b70;
typedef struct S1_1d7b70 { char p[52]; int f52; char p1[12]; int f68; } S1_1d7b70;
extern "C" int DAT_0048dae0[4];

typedef struct ShaderDataEntry { int _vtable; int references; } ShaderDataEntry;
typedef struct ShaderDataList { int pad0[2]; int count; int pad1; ShaderDataEntry **data; } ShaderDataList;
/* igShaderData with its lists typed. */
struct ShaderDataView { char pad[8]; ShaderDataList *_attrPushLists; ShaderDataList *_attrPopLists; ShaderDataEntry *_dataPumps; ShaderDataList *_childLists; };
struct S_1d86f0 { char pad0[8]; igObjectList *f8; };
struct A_1d8870 { char pad[20]; igObjectList *f20; };
struct Attr : public igObject { };
class VO_1d8980 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void v96(Attr *, Attr *, int); virtual void v100(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); };
class VA_1d8980 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void v124(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual void d101(); virtual void d102(); virtual void d103(); virtual void d104(); virtual void d105(); virtual void d106(); virtual void d107(); virtual void d108(); virtual void d109(); virtual void d110(); virtual void d111(); virtual void d112(); virtual void d113(); virtual void d114(); virtual void d115(); virtual void d116(); virtual void d117(); virtual void d118(); virtual void d119(); virtual void d120(); virtual void d121(); virtual void d122(); virtual void d123(); virtual void d124(); };
struct P_1d8980 { char pad[36]; VO_1d8980 *f36; };
class V_1d8a60 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual int vX(); };
struct T_1d8a60 { char pad[20]; int f20; };

struct ShaderFieldRecord { char pad[8]; int *name; char pad2[8]; int kind; };
struct ShaderFieldTable { char pad[20]; igTDataList<ShaderFieldRecord *> *list; };
struct S1d { int w[5]; int f20; };
typedef struct SkeletonBitListView { int _vtable; unsigned int _refCount; int _count; int _capacity; unsigned int *_data; int _bitCount; } SkeletonBitListView;
typedef struct SkeletonBitOwnerView { char pad[44]; SkeletonBitListView *_bits; } SkeletonBitOwnerView;
extern "C" void FUN_00190470(void *, void *, void *);
struct SkeletonMatrix { float m[16]; };
struct SkeletonBoneInfoView { int _vtable; unsigned int _refCount; int _name; int _parentIdx; int _bmIdx; };
struct SkeletonBoneListView { int _vtable; unsigned int _refCount; int _count; int _capacity; SkeletonBoneInfoView **_data; };
class SkeletonSlots {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21();
    virtual int getBoneCount();
    virtual void s23();
    virtual int getTime();
    virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
    virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35(); virtual void s36();
    virtual void update(int t);
};
struct SkeletonSourceView : SkeletonSlots { char pad[28]; SkeletonMatrix _matrix; };
struct SkeletonOverrideView { int _vtable; unsigned int _refCount; int _bone; SkeletonSourceView *_source; int _mode; };
struct SkeletonOverrideListView { int _vtable; unsigned int _refCount; int _count; int _capacity; SkeletonOverrideView **_data; };
struct SkeletonView : SkeletonSlots { unsigned int _refCount; int _name; int _boneTranslationArray; SkeletonBoneListView *_boneInfoList; SkeletonMatrix *_invJointArray; };
typedef struct E_1d9500 { char pad8[8]; int *f8; } E_1d9500;
typedef struct L_1d9500 { char pad8[8]; int cnt; char pad12[4]; E_1d9500 **arr; } L_1d9500;
typedef struct S_1d9500 { char pad16[16]; L_1d9500 *l; } S_1d9500;
class VC_1d95a0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual int vX(); };
struct E_1d95a0 { int pad[3]; int f12; };
struct B_1d95a0 { int pad[4]; E_1d95a0 **arr; };
struct O_1d95a0 { int vt; int pad[3]; B_1d95a0 *b; };
class V116 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual int vX(int, int *); };
class VC_1d96d0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual int vX(int, int *); };
typedef struct S_temp_a0_1d9770 { char pad4[4]; int f4; } S_temp_a0_1d9770;
/* igObject header: the reference count at +4 is not a reflected field */
typedef struct RefCountedHeader { char pad4[4]; int references; } RefCountedHeader;
typedef struct SortItemView { char pad[24]; float key; } SortItemView;
typedef struct SortListView { int _vtable; unsigned int _refCount; int _count; int _capacity; SortItemView **_data; } SortListView;
extern "C" void *DAT_005629f8[4];
typedef struct SortItemView_1d9a30 { char pad[20]; char *pos; float key; } SortItemView_1d9a30;
typedef struct SortListView_1d9a30 { int _vtable; unsigned int _refCount; int _count; int _capacity; SortItemView_1d9a30 **_data; } SortListView_1d9a30;
typedef struct R_1d9ac0 { int w0; int refs; } R_1d9ac0;
typedef struct L_1d9ac0 { char pad[8]; int cnt; char pad2[4]; R_1d9ac0 **arr; } L_1d9ac0;
struct B_1d9ac0 { char pad[32]; L_1d9ac0 *list; };
struct A_1d9ac0 { char pad[100]; struct B_1d9ac0 *b; };
extern "C" int FUN_001da220(void *, int, int);
struct Obj_1da6e0 { char pad[20]; unsigned key; };
struct Tbl { char pad[16]; struct Obj_1da6e0 **arr; };
struct Pair { int a; int b; };
typedef struct SorterPackageView { char pad[20]; unsigned int key; } SorterPackageView;
typedef struct SorterPackageListView { int _vtable; unsigned int _refCount; int _count; int _capacity; SorterPackageView **_data; } SorterPackageListView;
typedef struct SorterIndexListView { int _vtable; unsigned int _refCount; int _count; int _capacity; int *_data; } SorterIndexListView;
typedef struct SorterOpaqueView { char pad[60]; SorterIndexListView *_opaquePackageIndices; } SorterOpaqueView;
extern "C" int DAT_0048dae8[4];
struct SorterDevice {
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
    virtual void f30(int);
    virtual void f31(int);
};
struct SorterList { int pad[2]; int count; int cap; int *items; int getCount() const { return count; } };
struct SorterState { char pad[64]; SorterDevice *a; SorterDevice *b; SorterDevice *c; int pad2; SorterList *l80; SorterList *l84; SorterList *l88; };
typedef struct L_1db500 { char pad[8]; int count; int cap; int *data; } L_1db500;
typedef struct B_1db500 { char pad[12]; L_1db500 *f12; } B_1db500;
typedef struct A_1db500 { char pad[8]; B_1db500 *f8; char pad12[24]; int f36; int f40; } A_1db500;
struct Sorter;
struct List_1db5d0 { char pad8[8]; int f8; int f12; int *f16; };
struct Ent_1db5d0 { char pad28[28]; List_1db5d0 *f28; };
struct EL { char pad8[8]; int f8; char pad16[4]; Ent_1db5d0 **f16; int f20; };
struct Sorter {
  char pad8[8]; DW4VC_112_0 *f8; char pad12[4]; EL *f16; char pad20[4]; List_1db5d0 *f24; List_1db5d0 *f28; List_1db5d0 *f32; DW4VC_112_0 *f36; DW4VC_112_0 *f40; DW4VC_112_0 *f44; DW4VC_112_0 *f48; char pad52[40]; DW4VC_112_0 *f92; DW4VC_112_0 *f96; char pad100[4]; List_1db5d0 *f104; List_1db5d0 *f108; unsigned char f112; char pad113[11]; int f124; unsigned char f128;
};
struct L_1dc400 { char p0[8]; int cnt; int cap; int *data; };
struct LA_1dc400 { char p0[12]; struct L_1dc400 *l; };
typedef struct L2 { char pad[8]; int f8; int f12; } L2;
typedef struct X_1dc500 { char pad[4]; int f4; int f8; int f12; char pad2[12]; L2 *f28; } X_1dc500;
typedef struct L_1dc500 { char pad[8]; int f8; char pad2[4]; X_1dc500 **f16; int f20; } L_1dc500;
typedef struct A_1dc500 { char pad[16]; L_1dc500 *f16; char pad2[92]; unsigned char f112; char f113; char f114; char pad3; X_1dc500 *f116; int f120; } A_1dc500;
typedef struct P_1dc940 { char pad8[8]; int f8; } P_1dc940;
typedef struct S_1dc940 { char pad28[28]; P_1dc940 *f28; int f32; } S_1dc940;
typedef struct Obj_1dca40 Obj_1dca40;
struct Obj_1dca40 { int w0; int references; };
typedef struct List_1dca40 List_1dca40;
struct List_1dca40 { int pad0[2]; int count; int pad1; Obj_1dca40 **data; int f20; int f24; };
struct ObjectPool : igTDataList<igObject *> {
    int _activeCount;
    int _pad24;
    unsigned char _resetOnRelease;
};

typedef struct KeyTimeListView { int _vtable; unsigned int _refCount; int _count; int _capacity; double *_data; } KeyTimeListView;
typedef struct KeyValueListView { int _vtable; unsigned int _refCount; int _count; int _capacity; int *_data; } KeyValueListView;
typedef struct KeyTrackView { char pad[28]; KeyValueListView *_values; KeyTimeListView *_times; double _startTime; int _mode; } KeyTrackView;
struct S_1dce70 { char pad[8]; int f8; char pad2[4]; double *f16; };
class DW4VC_116_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual int vX(); };
class VC_1dd010 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void vX(int); };
extern "C" float FUN_00192290(float const*);
typedef struct TransformSampleVec3ListView { int _vtable; unsigned int _refCount; int _count; int _capacity; float (*_data)[3]; } TransformSampleVec3ListView;
typedef struct TransformSampleQuatListView { int _vtable; unsigned int _refCount; int _count; int _capacity; float (*_data)[4]; } TransformSampleQuatListView;
typedef struct TransformSampleView { int _vtable; unsigned int _refCount; TransformSampleVec3ListView *_xlateList; TransformSampleQuatListView *_quatList; TransformSampleVec3ListView *_scaleList; } TransformSampleView;
typedef struct B_1dd250 { char pad[16]; char *data; } B_1dd250;
typedef struct A_1dd250 { char pad[8]; B_1dd250 *b8; B_1dd250 *b12; B_1dd250 *b16; char pad2[24]; float f44; float f48; float f52; } A_1dd250;

extern "C" float DAT_004e105c[4];
extern "C" float DAT_004e1060[4];
class V_1dd3e0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void vSet(int, int *); virtual void vGet(int, int *); virtual void e0(); virtual void e1(); virtual void e2(); virtual int vCount(); };
struct F_1dd3e0 { char p[44]; float a; float b; float c; };

extern "C" long long DAT_00562a18[4];
extern "C" long long DAT_00562a20[4];
extern "C" int DAT_00562a28[4];
extern "C" long long DAT_00562a30[4];
class VC_1dd570 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual int v156(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual float *v180(int); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual unsigned char v240(); };
extern "C" void FUN_00192990(void *, float *, float *, float *);
typedef struct KeyVec3ListView { int _vtable; unsigned int _refCount; int _count; int _capacity; igVec3f *_data; } KeyVec3ListView;
typedef struct KeyQuatView { float x, y, z, w; } KeyQuatView;
typedef struct KeyQuatListView { int _vtable; unsigned int _refCount; int _count; int _capacity; KeyQuatView *_data; } KeyQuatListView;
typedef struct KeySequenceView { int _vtable; unsigned int _refCount; KeyVec3ListView *_xlateList; KeyQuatListView *_quatList; KeyVec3ListView *_scaleList; char pad[52]; unsigned char _drivenChannels; } KeySequenceView;
typedef struct KeyMatrixView { float r[3][4]; float tx, ty, tz, tw; } KeyMatrixView;
struct V4_1dda90 { float x, y, z, w; };
struct SeqData {
    char pad0[4];
    int refCount;
    int count;
    int capacity;
};
struct SeqTempRef {
    SeqData *p;
    SeqTempRef(SeqData *x) : p(x) {}
    ~SeqTempRef() {
        if (p) {
            --p->refCount;
            if (((unsigned long long)(long long)p->refCount & 0x7fffffULL) == 0)
                igObject_Destroy((igObject *)p);
        }
    }
};
struct TransformSequenceView {
    char pad0[8];
    SeqData *translationKeys;
    SeqData *rotationKeys;
    SeqData *scaleKeys;
    char pad20[36];
    SeqData *keys;
    SeqData *translations;
    SeqData *rotations;
    SeqData *scales;
    unsigned char channels;
    unsigned char translationMode;
    unsigned char rotationMode;
    unsigned char scaleMode;
};
typedef struct L_1de9c0 { int pad[2]; int count; int cap; igVec3f *data; } L_1de9c0;
typedef struct LL_1de9c0 { int pad[2]; int count; } LL_1de9c0;
typedef struct T_1de9c0 { char pad[56]; LL_1de9c0 *tl; L_1de9c0 *a; L_1de9c0 *b; L_1de9c0 *c; unsigned char flags; } T_1de9c0;
struct Set { static inline void put(L_1de9c0 *l, int i, igVec3f *p) {
    igVec3f *e;
    if (l->count != 0 && i >= 0 && i < l->count) {
        e = l->data + i; e->vec[0] = p->vec[0]; e->vec[1] = p->vec[1]; e->vec[2] = p->vec[2];
    }
} };
/* The rates are read as unsigned, so the unsigned-int to float conversion yields the srl/andi/or
 * fixup. */
typedef struct SequenceTimeList { char pad[16]; long long *_data; } SequenceTimeList;
/* igTransformSequence1_5 down to its key time list (_timeListLong, +56). */
typedef struct SequenceKeyTimes { char pad[56]; SequenceTimeList *_timeListLong; } SequenceKeyTimes;
struct O_1df6e0 {
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
    virtual int a();
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
    virtual long long b(int);
    char pad[76];
    long long f80;
};
class V_1df740 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual long long vB(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual int vA();
  char pad[72]; long long f80; long long f88; };
struct IgForwardTarget {
virtual void slot0();
virtual void slot1();
virtual void slot2();
virtual void slot3();
virtual void slot4();
virtual void slot5();
virtual void slot6();
virtual void slot7();
virtual void slot8();
virtual void slot9();
virtual void slot10();
virtual void slot11();
virtual void slot12();
virtual void slot13();
virtual void slot14();
virtual void slot15();
virtual void slot16();
virtual void slot17();
virtual void slot18();
virtual void slot19();
virtual void slot20();
virtual void slot21();
virtual void slot22();
virtual void slot23();
virtual void slot24();
virtual void slot25();
virtual void slot26(int a, int b, int c, void *d, int e);
};
struct IgForwardTarget_1dfd60 {
virtual void slot0();
virtual void slot1();
virtual void slot2();
virtual void slot3();
virtual void slot4();
virtual void slot5();
virtual void slot6();
virtual void slot7();
virtual void slot8();
virtual void slot9();
virtual void slot10();
virtual void slot11();
virtual void slot12();
virtual void slot13();
virtual void slot14();
virtual void slot15();
virtual void slot16();
virtual void slot17();
virtual void slot18();
virtual void slot19();
virtual void slot20();
virtual void slot21();
virtual void slot22();
virtual void slot23();
virtual void slot24(int a, int b, void *d, int e);
};
typedef struct T_1e0380 { int w0; int refs; } T_1e0380;
extern "C" T_1e0380 *DAT_00562a38[4];
typedef struct A_1e0380 { char pad[28]; T_1e0380 *f1c; } A_1e0380;
struct S_1e04c0;
struct V_1e04c0;
class V_1e04c0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); };
struct L_1e04c0 { char p[16]; int (**tab)(S_1e04c0 *, V_1e04c0 *); };
struct S_1e04c0 { char p[8]; unsigned char f8; char q[3]; int (*f12)(...); char r[12]; L_1e04c0 *f28; };
struct W_1e04c0 : V_1e04c0 { char p[20]; int f24; };
struct L_1e07a0 { char p[8]; int n; char q[4]; int *arr; };
struct S_1e07a0 { char p[28]; L_1e07a0 *f28; };
class DW4VC_200_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual int vX(); };
struct T_1e08b0 { int word0; int references; int f8; int f12; };
struct Rel { static inline void go(T_1e08b0 *object) {
    if (object) {
        --object->references;
        if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
            igObject_Destroy((igObject *)object);
    }
} };
class DW4VC_128_4 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual int vX(int, int, int, int); };
typedef struct Rc_1e1210 { int w0; int refs; } Rc_1e1210;
class A_1e1210 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void v28(int); virtual void d29(); char p[40]; int f44; };
class B_1e1210 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void v30(int); virtual void v31(int); };
typedef struct S_1e1210 { char p0[32]; int f32; char p1[16]; int f52; char p2[17]; unsigned char f73; char p3[6]; B_1e1210 *f80; char p4[28]; B_1e1210 *f112; Rc_1e1210 *f116; Rc_1e1210 *f120; } S_1e1210;
typedef struct R_1e1400 { int w0; int refs; } R_1e1400;
typedef struct S_1e1400 { char pad[112]; R_1e1400 *a; R_1e1400 *b; R_1e1400 *c; } S_1e1400;
struct EnvMapSource { char pad[0xA4]; float matrix[16]; };
extern "C" float DAT_004e48a0[4];
extern "C" float DAT_004e48a4[4];
extern "C" float DAT_004e48a8[4];
extern "C" float DAT_004e48ac[4];
extern "C" char GPR_00554bb0;
class A1_1e1580 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual int vX(int); };
class S_1e1580 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void v47(A1_1e1580*); virtual void d48(); virtual void v49(A1_1e1580*); virtual void v50(); char p[28]; int f32; char p2[12]; unsigned char f48; char p3[3]; int f52; char p4[4]; char f60; char p5[11]; char f72; };
struct EnvMapAttr { char pad[4]; int f4; };
extern "C" EnvMapAttr *DAT_00562730[4];
extern "C" EnvMapAttr *DAT_00562738[4];
struct EnvMapAttrState { char pad[12]; int f12; };
class EnvMapAttrOps { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(int); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void vX(int); virtual void vY(int); };
struct EnvMapAlphaAttr { char pad[28]; unsigned char b28; };
struct EnvMapShaderView {
    char pad0[36]; EnvMapAttrState *f36; char pad1[4]; float f44; char pad2[16]; int f64; int f68;
    int pad3; int f76; int f80; EnvMapAttrState *f84; EnvMapAttrOps *f88; EnvMapAttrOps *f92; int f96; char pad5[12]; EnvMapAttrOps *f112; int f116; EnvMapAttrOps *f120;
};
struct EnvMapRef {
    EnvMapAttr *p;
    ~EnvMapRef() {
        EnvMapAttr *object = p;
        if (object) {
            --object->f4;
            if (((unsigned long long)(long long)object->f4 & 0x7fffffULL) == 0)
                igObject_Destroy((igObject *)object);
        }
    }
};
struct X_1e1ac0 { char pad[4]; int f4; };
struct E_1e1ac0 { char pad[12]; int f12; };
class VD { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void vX(int); char pad[0]; };
struct W112 { char pad[28]; unsigned char b28; };
struct S_1e1ac0 {
    char pad0[36]; int f36; char pad1[4]; float f44; char pad2[16]; int f64; int f68;
    int pad3; int f76; int f80; E_1e1ac0 *f84; int f88; int f92; int f96; char pad5[12]; VD *f112; int f116;
};
struct Ref_1e1ac0 {
    X_1e1ac0 *p;
    ~Ref_1e1ac0() {
        X_1e1ac0 *object = p;
        if (object) {
            --object->f4;
            if (((unsigned long long)(long long)object->f4 & 0x7fffffULL) == 0)
                igObject_Destroy((igObject *)object);
        }
    }
};
struct EnvMapShaderView_1e1e70 {
    char pad0[36]; EnvMapAttrState *f36; char pad1[4]; float f44; char pad2[16]; int f64; int f68;
    int pad3; int f76; int f80; EnvMapAttrState *f84; int f88; int f92; int f96; int f100; int f104; char pad5[4]; EnvMapAttrOps *f112; int f116; EnvMapAttrOps *f120;
};
struct EnvMapShaderView_1e22c0 {
    char pad0[36]; EnvMapAttrState *f36; char pad1[4]; float f44; char pad2[8]; int f56; char pad3[4]; int f64; int f68;
    int pad4; int f76; int f80; EnvMapAttrState *f84; EnvMapAttrOps *f88; EnvMapAttrOps *f92; int f96; EnvMapAttrOps *f100; EnvMapAttrOps *f104; EnvMapAttrOps *f108; EnvMapAttrOps *f112; int f116; EnvMapAttrOps *f120;
};
struct EnvMapTempRef {
    EnvMapAttr *p;
    EnvMapTempRef(EnvMapAttr *x) : p(x) {}
    ~EnvMapTempRef() {
        if (p) {
            --p->f4;
            if (((unsigned long long)(long long)p->f4 & 0x7fffffULL) == 0)
                igObject_Destroy((igObject *)p);
        }
    }
};
struct IgForwardTarget_1e28b0 {
virtual void slot0();
virtual void slot1();
virtual void slot2();
virtual void slot3();
virtual void slot4();
virtual void slot5();
virtual void slot6();
virtual void slot7();
virtual void slot8();
virtual void slot9();
virtual void slot10();
virtual void slot11();
virtual void slot12();
virtual void slot13();
virtual void slot14();
virtual void slot15();
virtual void slot16();
virtual void slot17();
virtual void slot18();
virtual void slot19();
virtual void slot20();
virtual void slot21();
virtual void slot22();
virtual void slot23();
};
struct IgForwardTarget_1e28c0 {
virtual void slot0();
virtual void slot1();
virtual void slot2();
virtual void slot3();
virtual void slot4();
virtual void slot5();
virtual void slot6();
virtual void slot7();
virtual void slot8();
virtual void slot9();
virtual void slot10();
virtual void slot11();
virtual void slot12();
virtual void slot13();
virtual void slot14();
virtual void slot15();
virtual void slot16();
virtual void slot17();
virtual void slot18();
virtual void slot19();
virtual void slot20();
virtual void slot21();
virtual void slot22();
virtual void slot23();
virtual void slot24();
virtual void slot25();
};
typedef struct TransformSequenceChannelView { char pad[8]; int _xlateList; int _quatList; int _scaleList; char pad2[36]; int _timeListLong; char pad3[12]; unsigned char _drivenChannels; } TransformSequenceChannelView;
struct L_1e2970 { int pad[2]; int count; int cap; };
struct T_1e2970 { char pad[8]; struct L_1e2970 *a; struct L_1e2970 *b; struct L_1e2970 *c; char pad2[36]; struct L_1e2970 *d; char pad3[12]; unsigned char flags; };
struct IgForwardTarget_1e2cd0 {
virtual void slot0();
virtual void slot1();
virtual void slot2();
virtual void slot3();
virtual void slot4();
virtual void slot5();
virtual void slot6();
virtual void slot7();
virtual void slot8();
virtual void slot9();
virtual void slot10();
virtual void slot11();
virtual void slot12();
virtual void slot13();
virtual void slot14();
virtual void slot15();
virtual void slot16();
virtual void slot17();
virtual void slot18();
virtual void slot19();
virtual void slot20();
virtual void slot21();
};
struct IgForwardTarget_1e2d60 {
virtual void slot0();
virtual void slot1();
virtual void slot2();
virtual void slot3();
virtual void slot4();
virtual void slot5();
virtual void slot6();
virtual void slot7();
virtual void slot8();
virtual void slot9();
virtual void slot10();
virtual void slot11();
virtual void slot12();
virtual void slot13();
virtual void slot14();
virtual void slot15();
virtual void slot16();
virtual void slot17();
virtual void slot18();
virtual void slot19();
virtual void slot20();
virtual void slot21();
virtual void slot22();
virtual void slot23();
};
struct IgForwardTarget_1e2d70 {
virtual void slot0();
virtual void slot1();
virtual void slot2();
virtual void slot3();
virtual void slot4();
virtual void slot5();
virtual void slot6();
virtual void slot7();
virtual void slot8();
virtual void slot9();
virtual void slot10();
virtual void slot11();
virtual void slot12();
virtual void slot13();
virtual void slot14();
virtual void slot15();
virtual void slot16();
virtual void slot17();
virtual void slot18();
virtual void slot19();
virtual void slot20();
virtual void slot21();
virtual void slot22();
virtual void slot23();
virtual void slot24();
virtual void slot25();
};
struct RO { int vt; union { int w; struct { unsigned cnt:23; unsigned f:9; } b; } u; };
struct Rel_1e2ec0 { static inline void go(RO *o) { RO *t = o; if (t != 0) { t->u.w = t->u.w - 1; if (t->u.b.cnt == 0) igObject_Destroy((igObject *)t); } } };
struct List_1e2ec0 {
    char pad[8]; int n; char pad2[4]; RO **data;
    void clear() {
        int cnt = n;
        int i;
        for (i = 0; i < cnt; i++) {
            Rel_1e2ec0::go(data[i]);
        }
        int cnt2 = n;
        int j;
        for (j = 0; j < cnt2; j++) data[j] = 0;
        n = 0;
    }
};
struct Shader { char pad[80]; List_1e2ec0 *f80; List_1e2ec0 *f84; List_1e2ec0 *f88; RO *f92; RO *f96; };

typedef struct S1_1e31f0 { char pad4[4]; int f4; } S1_1e31f0;
typedef struct S0_1e31f0 { char pad68[68]; int f44; } S0_1e31f0;
typedef struct S_temp_a0_1e31f0 { char pad4[4]; int f4; } S_temp_a0_1e31f0;
typedef struct { char p[8]; int n; char q[4]; char *arr; } T_1e3270;
struct S_1e3300 { char pad0[8]; struct R *p8; char pad1[44]; unsigned char f56; };

extern "C" void SceneGraphLibrary_MarkRegistered(void);
extern "C" igMetaObject *igGroup_GetPublishedMetaObject(void);
extern "C" igMetaObject *igTraversal_GetMetaObject(void);
extern "C" int igTraversal_GetVTable(void);
extern "C" void *FUN_00194490(struct S *arg0, short arg1);
extern "C" void igTraversal_EnsureRegistered(void);
extern "C" CallbackArray *igTraversal_Register(void);
extern "C" void igTraversal_GetMetaObjectFunction(void);
extern "C" void igTraversal_InitFields(void);
extern "C" void FUN_00194690(void);
extern "C" void thunk_FUN_001e0470(void);
extern "C" igMetaObject *igTransientShaderData_GetMetaObject(void);
extern "C" int igTransientShaderData_GetVTable(void);
extern "C" int **FUN_00194790(int **arg0, long long arg1);
extern "C" void **igSmartPointer_igNodeListList_Destruct(struct Ref **self, short flag);
extern "C" void **igSmartPointer_igDataPumpInfo_Destruct(void **arg0, long long arg1);
extern "C" Obj_194930 *FUN_00194930(Obj_194930 *arg0, short arg1);
extern "C" void igTransientShaderData_EnsureRegistered(void);
extern "C" CallbackArray *igTransientShaderData_Register(void);
extern "C" void igTransientShaderData_GetMetaObjectFunction(void);
extern "C" igMetaObject *igShaderData_GetPublishedMetaObject(void);
extern "C" void igTransientShaderData_InitFields(void);
extern "C" igMetaObject *igTransformSource_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igTransformSource_GetMetaObject(void);
extern "C" void igTransformSource_EnsureRegistered(void);
extern "C" CallbackArray *igTransformSource_Register(void);
extern "C" void igTransformSource_GetMetaObjectFunction(void);
extern "C" igMetaObject *igTransformSequence1_5_GetMetaObject(void);
extern "C" int igTransformSequence1_5_GetVTable(void);
extern "C" Obj_195030 *FUN_00195030(Obj_195030 *arg0, short arg1);
extern "C" ObjectRefWord *igSmartPointer_igCompressedTransformSequence1_5Data_Destruct(ObjectRefWord *self,int delete_storage);
extern "C" CallbackArray *igTransformSequence1_5_Register(void);
extern "C" void igTransformSequence1_5_GetMetaObjectFunction(void);
extern "C" igMetaObject *FUN_00195330(void);
extern "C" void thunk_FUN_001ddfd0(void);
extern "C" igMetaObject *igTransformSequence_GetMetaObject(void);
extern "C" void igTransformSequence_EnsureRegistered(void);
extern "C" CallbackArray *igTransformSequence_Register(void);
extern "C" void igTransformSequence_GetMetaObjectFunction(void);
extern "C" igMetaObject *igTransformSource_GetPublishedMetaObject(void);
extern "C" void igTransformSequence_InitFields(void);
extern "C" igMetaObject *igTransformRecorder_GetMetaObject(void);
extern "C" int igTransformRecorder_GetVTable(void);
extern "C" CallbackArray *igTransformRecorder_Register(void);
extern "C" void igTransformRecorder_GetMetaObjectFunction(void);
extern "C" void igTransformRecorder_InitFields(void);
extern "C" igMetaObject *igNonRefCountedTransformList_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igNonRefCountedTransformList_GetMetaObject(void);
extern "C" int igNonRefCountedTransformList_GetVTable(void);
extern "C" void igNonRefCountedTransformList_EnsureRegistered(void);
extern "C" CallbackArray *igNonRefCountedTransformList_Register(void);
extern "C" void igNonRefCountedTransformList_GetMetaObjectFunction(void);
extern "C" igMetaObject *igTransformList_GetMetaObject(void);
extern "C" int igTransformList_GetVTable(void);
extern "C" CallbackArray *igTransformList_Register(void);
extern "C" void igTransformList_GetMetaObjectFunction(void);
extern "C" igMetaObject *igTransformStack_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igTransformStack_GetMetaObject(void);
extern "C" int igTransformStack_GetVTable(void);
extern "C" void igTransformStack_EnsureRegistered(void);
extern "C" CallbackArray *igTransformStack_Register(void);
extern "C" void igTransformStack_GetMetaObjectFunction(void);
extern "C" igMetaObject *igTransform_GetMetaObject(void);
extern "C" int igTransform_GetVTable(void);
extern "C" void *FUN_001962d0(struct S_1962d0 *arg0, short arg1);
extern "C" ObjectRefWord *igSmartPointer_igVisualAttribute_Destruct(ObjectRefWord *self,int delete_storage);
extern "C" void **igSmartPointer_igTransformSource_Destruct(void **arg0, short arg1);
extern "C" void igTransform_GetMetaObjectFunction(void);
extern "C" void igTransform_InitFields(void);
extern "C" igSmartPointer<igObject> *igSmartPointer_igTextureMatrixAttr_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
extern "C" igMetaObject *igObjectPool_GetMetaObject(void);
extern "C" int igObjectPool_GetVTable(void);
extern "C" void igObjectPool_EnsureRegistered(void);
extern "C" CallbackArray *igObjectPool_Register(void);
extern "C" void igObjectPool_GetMetaObjectFunction(void);
extern "C" void igObjectPool_InitFields(void);
extern "C" igMetaObject *igSwitch_GetMetaObject(void);
extern "C" int igSwitch_GetVTable(void);
extern "C" CallbackArray *igSwitch_Register(void);
extern "C" void igSwitch_GetMetaObjectFunction(void);
extern "C" void igSwitch_InitFields(void);
extern "C" igMetaObject *FUN_00196c10(void);
extern "C" igMetaObject *igSorter_GetMetaObject(void);
extern "C" int igSorter_GetVTable(void);
extern "C" igSmartPointer<igObject> *igSmartPointer_igRenderPackagePool_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
extern "C" igSmartPointer<igObject> *igSmartPointer_igDepthWriteStateAttr_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
extern "C" igSmartPointer<igObject> *igSmartPointer_igRenderPackageList_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
extern "C" igSmartPointer<igObject> *igSmartPointer_igRenderPackage_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
extern "C" int *igSmartPointer_igGeometry_Construct(int *p);
extern "C" int *igSmartPointer_igRenderPackage_Construct(int *p);
extern "C" int *igSmartPointer_igDepthWriteStateAttr_Construct(int *p);
extern "C" int *igSmartPointer_igRenderPackageList_Construct(int *p);
extern "C" int *igSmartPointer_igNonRefCountedAttrList_Construct(int *p);
extern "C" int *igSmartPointer_igRenderPackagePool_Construct(int *p);
extern "C" void igSorter_EnsureRegistered(void);
extern "C" CallbackArray *igSorter_Register(void);
extern "C" void igSorter_GetMetaObjectFunction(void);
extern "C" void igSorter_InitFields(void);
extern "C" igMetaObject *igRenderPackageList_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igRenderPackageList_GetMetaObject(void);
extern "C" int igRenderPackageList_GetVTable(void);
extern "C" void igRenderPackageList_EnsureRegistered(void);
extern "C" CallbackArray *igRenderPackageList_Register(void);
extern "C" void igRenderPackageList_GetMetaObjectFunction(void);
extern "C" igMetaObject *igRenderPackagePool_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igRenderPackagePool_GetMetaObject(void);
extern "C" int igRenderPackagePool_GetVTable(void);
extern "C" void igRenderPackagePool_EnsureRegistered(void);
extern "C" CallbackArray *igRenderPackagePool_Register(void);
extern "C" void igRenderPackagePool_GetMetaObjectFunction(void);
extern "C" igMetaObject *igObjectPool_GetPublishedMetaObject(void);
extern "C" void FUN_00197ab0(int arg0);
extern "C" igMetaObject *igRenderPackage_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igRenderPackage_GetMetaObject(void);
extern "C" int igRenderPackage_GetVTable(void);
extern "C" void igRenderPackage_EnsureRegistered(void);
extern "C" CallbackArray *igRenderPackage_Register(void);
extern "C" void igRenderPackage_GetMetaObjectFunction(void);
extern "C" void igRenderPackage_InitFields(void);
extern "C" igMetaObject *igSkinList_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igSkinList_GetMetaObject(void);
extern "C" int igSkinList_GetVTable(void);
extern "C" CallbackArray *igSkinList_Register(void);
extern "C" void igSkinList_GetMetaObjectFunction(void);
extern "C" igMetaObject *igSkin_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igSkin_GetMetaObject(void);
extern "C" int igSkin_GetVTable(void);
extern "C" CallbackArray *igSkin_Register(void);
extern "C" void igSkin_GetMetaObjectFunction(void);
extern "C" void igSkin_InitFields(void);
extern "C" igMetaObject *igSkeletonList_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igSkeletonList_GetMetaObject(void);
extern "C" int igSkeletonList_GetVTable(void);
extern "C" CallbackArray *igSkeletonList_Register(void);
extern "C" void igSkeletonList_GetMetaObjectFunction(void);
extern "C" igMetaObject *igSkeleton_GetMetaObject(void);
extern "C" int igSkeleton_GetVTable(void);
extern "C" CallbackArray *igSkeleton_Register(void);
extern "C" void igSkeleton_GetMetaObjectFunction(void);
extern "C" igMetaObject *igAnimationHierarchy_GetPublishedMetaObject(void);
extern "C" void igSkeleton_InitFields(void);
extern "C" igMetaObject *igSkeletonBoneInfoList_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igSkeletonBoneInfoList_GetMetaObject(void);
extern "C" int igSkeletonBoneInfoList_GetVTable(void);
extern "C" CallbackArray *igSkeletonBoneInfoList_Register(void);
extern "C" void igSkeletonBoneInfoList_GetMetaObjectFunction(void);
extern "C" igMetaObject *igSkeletonBoneInfo_GetMetaObject(void);
extern "C" int igSkeletonBoneInfo_GetVTable(void);
extern "C" CallbackArray *igSkeletonBoneInfo_Register(void);
extern "C" void igSkeletonBoneInfo_GetMetaObjectFunction(void);
extern "C" void igSkeletonBoneInfo_InitFields(void);
extern "C" int FUN_00198b60(int arg0);
extern "C" igMetaObject *igShaderProcessor_GetMetaObject(void);
extern "C" int igShaderProcessor_GetVTable(void);
extern "C" void igShaderProcessor_EnsureRegistered(void);
extern "C" CallbackArray *igShaderProcessor_Register(void);
extern "C" void igShaderProcessor_GetMetaObjectFunction(void);
extern "C" int FUN_00198cc0(int arg0);
extern "C" igMetaObject *igShaderInfo_GetMetaObject(void);
extern "C" int igShaderInfo_GetVTable(void);
extern "C" CallbackArray *igShaderInfo_Register(void);
extern "C" void igShaderInfo_GetMetaObjectFunction(void);
extern "C" void igShaderInfo_InitFields(void);
extern "C" void thunk_FUN_001d8ab0(void);
extern "C" void thunk_FUN_001d8b90(void);
extern "C" igMetaObject *igShaderFactoryList_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igShaderFactoryList_GetMetaObject(void);
extern "C" int igShaderFactoryList_GetVTable(void);
extern "C" CallbackArray *igShaderFactoryList_Register(void);
extern "C" void igShaderFactoryList_GetMetaObjectFunction(void);
extern "C" igMetaEnum *FUN_00199110(void);
extern "C" igMetaObject *igShaderFactory_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igShaderFactory_GetMetaObject(void);
extern "C" int igShaderFactory_GetVTable(void);
extern "C" void *FUN_00199330(struct T_199330 *arg0, long long arg1);
extern "C" void igShaderFactory_EnsureRegistered(void);
extern "C" CallbackArray *igShaderFactory_Register(void);
extern "C" void igShaderFactory_GetMetaObjectFunction(void);
extern "C" void igShaderFactory_InitFields(void);
extern "C" igMetaObject *igShaderData_GetMetaObject(void);
extern "C" int igShaderData_GetVTable(void);
extern "C" void igShaderData_EnsureRegistered(void);
extern "C" CallbackArray *igShaderData_Register(void);
extern "C" void igShaderData_GetMetaObjectFunction(void);
extern "C" void igShaderData_InitFields(void);
extern "C" struct R **igSmartPointer_igModelViewMatrixAttrList_Destruct(struct R **arg0, short arg1);
extern "C" igMetaObject *igBlendMatricesAttrPool_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igBlendMatricesAttrPool_GetMetaObject(void);
extern "C" int igBlendMatricesAttrPool_GetVTable(void);
extern "C" void igBlendMatricesAttrPool_EnsureRegistered(void);
extern "C" CallbackArray *igBlendMatricesAttrPool_Register(void);
extern "C" void igBlendMatricesAttrPool_GetMetaObjectFunction(void);
extern "C" igMetaObject *igTextureMatrixAttrPool_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igTextureMatrixAttrPool_GetMetaObject(void);
extern "C" int igTextureMatrixAttrPool_GetVTable(void);
extern "C" void igTextureMatrixAttrPool_EnsureRegistered(void);
extern "C" CallbackArray *igTextureMatrixAttrPool_Register(void);
extern "C" void igTextureMatrixAttrPool_GetMetaObjectFunction(void);
extern "C" igMetaObject *igMatrixObjectPool_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igMatrixObjectPool_GetMetaObject(void);
extern "C" int igMatrixObjectPool_GetVTable(void);
extern "C" void igMatrixObjectPool_EnsureRegistered(void);
extern "C" CallbackArray *igMatrixObjectPool_Register(void);
extern "C" void igMatrixObjectPool_GetMetaObjectFunction(void);
extern "C" igMetaObject *igVertexBlendMatrixListAttrPool_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igVertexBlendMatrixListAttrPool_GetMetaObject(void);
extern "C" int igVertexBlendMatrixListAttrPool_GetVTable(void);
extern "C" void igVertexBlendMatrixListAttrPool_EnsureRegistered(void);
extern "C" CallbackArray *igVertexBlendMatrixListAttrPool_Register(void);
extern "C" void igVertexBlendMatrixListAttrPool_GetMetaObjectFunction(void);
extern "C" igMetaObject *igVertexBlendMatrixAttrPool_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igVertexBlendMatrixAttrPool_GetMetaObject(void);
extern "C" int igVertexBlendMatrixAttrPool_GetVTable(void);
extern "C" void igVertexBlendMatrixAttrPool_EnsureRegistered(void);
extern "C" CallbackArray *igVertexBlendMatrixAttrPool_Register(void);
extern "C" void igVertexBlendMatrixAttrPool_GetMetaObjectFunction(void);
extern "C" igMetaObject *igProjectionMatrixAttrPool_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igProjectionMatrixAttrPool_GetMetaObject(void);
extern "C" int igProjectionMatrixAttrPool_GetVTable(void);
extern "C" void igProjectionMatrixAttrPool_EnsureRegistered(void);
extern "C" CallbackArray *igProjectionMatrixAttrPool_Register(void);
extern "C" void igProjectionMatrixAttrPool_GetMetaObjectFunction(void);
extern "C" igMetaObject *igTimeAttrPool_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igTimeAttrPool_GetMetaObject(void);
extern "C" int igTimeAttrPool_GetVTable(void);
extern "C" void igTimeAttrPool_EnsureRegistered(void);
extern "C" CallbackArray *igTimeAttrPool_Register(void);
extern "C" void igTimeAttrPool_GetMetaObjectFunction(void);
extern "C" igMetaObject *igModelViewMatrixAttrPool_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igModelViewMatrixAttrPool_GetMetaObject(void);
extern "C" int igModelViewMatrixAttrPool_GetVTable(void);
extern "C" void igModelViewMatrixAttrPool_EnsureRegistered(void);
extern "C" CallbackArray *igModelViewMatrixAttrPool_Register(void);
extern "C" void igModelViewMatrixAttrPool_GetMetaObjectFunction(void);
extern "C" igMetaObject *igLightStateAttrPool_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igLightStateAttrPool_GetMetaObject(void);
extern "C" int igLightStateAttrPool_GetVTable(void);
extern "C" void igLightStateAttrPool_EnsureRegistered(void);
extern "C" CallbackArray *igLightStateAttrPool_Register(void);
extern "C" void igLightStateAttrPool_GetMetaObjectFunction(void);
extern "C" int igTraversalFunctionList_CreateInstance(int arg0);
extern "C" igMetaObject *igTraversalFunctionList_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igTraversalFunctionList_GetMetaObject(void);
extern "C" int igTraversalFunctionList_GetVTable(void);
extern "C" CallbackArray *igTraversalFunctionList_Register(void);
extern "C" void igTraversalFunctionList_GetMetaObjectFunction(void);
extern "C" igSmartPointer<igObject> *igSmartPointer_igProjectionMatrixAttr_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
extern "C" igSmartPointer<igObject> *igSmartPointer_igSetRenderDestinationAttr_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
extern "C" igSmartPointer<igObject> *igSmartPointer_igCopyRenderDestinationAttr_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
extern "C" igSmartPointer<igObject> *igSmartPointer_igTexGenMatrixAttr_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
extern "C" int *igSmartPointer_igColorAttr_Construct(int *p);
extern "C" int *igSmartPointer_igTexGenMatrixAttr_Construct(int *p);
extern "C" int *igSmartPointer_igViewportAttr_Construct(int *p);
extern "C" int *igSmartPointer_igCopyRenderDestinationAttr_Construct(int *p);
extern "C" int *igSmartPointer_igTextureBindAttr_Construct(int *p);
extern "C" int *igSmartPointer_igTextureAttr_Construct(int *p);
extern "C" int *igSmartPointer_igSetRenderDestinationAttr_Construct(int *p);
extern "C" int *igSmartPointer_igRenderDestinationAttr_Construct(int *p);
extern "C" int *igSmartPointer_igTextureMatrixAttr_Construct(int *p);
extern "C" int *igSmartPointer_igProjectionMatrixAttr_Construct(int *p);
extern "C" int *igSmartPointer_igModelViewMatrixAttr_Construct(int *p);
extern "C" int *igSmartPointer_igNodeList_Construct(int *p);
extern "C" int FUN_0019ace0(int a0);
extern "C" void *FUN_0019acf0(igGroup *arg0);
extern "C" int igSegment_GetVTable(void);
extern "C" void igSegment_EnsureRegistered(void);
extern "C" CallbackArray *igSegment_Register(void);
extern "C" void igSegment_GetMetaObjectFunction(void);
extern "C" int igSceneInfo_GetVTable(void);
extern "C" void igSceneInfo_GetMetaObjectFunction(void);
extern "C" void igSceneInfo_InitFields(void);
extern "C" igMetaObject *igProjectiveShadowShader_GetMetaObject(void);
extern "C" int igProjectiveShadowShader_GetVTable(void);
extern "C" int *igSmartPointer_igTextureUnloadAttr_Construct(int *p);
extern "C" int *igSmartPointer_igGeometryAttr_Construct(int *p);
extern "C" CallbackArray *igProjectiveShadowShader_Register(void);
extern "C" void igProjectiveShadowShader_GetMetaObjectFunction(void);
extern "C" void igProjectiveShadowShader_InitFields(void);
extern "C" igMetaObject *igPlanarShadowShader_GetMetaObject(void);
extern "C" int igPlanarShadowShader_GetVTable(void);
extern "C" void *FUN_0019c0e0(struct S_19c0e0 *arg0, short arg1);
extern "C" ObjectRefWord *igSmartPointer_igStencilStateAttr_Destruct(ObjectRefWord *self,int delete_storage);
extern "C" int *igSmartPointer_igStencilStateAttr_Construct(int *p);
extern "C" int *igSmartPointer_igVolume_Construct(int *p);
extern "C" int *igSmartPointer_igAttrList_Construct(int *p);
extern "C" int *igSmartPointer_igGeometryList_Construct(int *p);
extern "C" int *igSmartPointer_igModelViewMatrixAttrList_Construct(int *p);
extern "C" void *FUN_0019c380(void *arg0);
extern "C" void igPlanarShadowShader_EnsureRegistered(void);
extern "C" CallbackArray *igPlanarShadowShader_Register(void);
extern "C" void igPlanarShadowShader_GetMetaObjectFunction(void);
extern "C" igMetaObject *igAttrSet_GetPublishedMetaObject(void);
extern "C" void igPlanarShadowShader_InitFields(void);
extern "C" igMetaObject *igOverrideAttrSet_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igOverrideAttrSet_GetMetaObject(void);
extern "C" int igOverrideAttrSet_GetVTable(void);
extern "C" void igOverrideAttrSet_EnsureRegistered(void);
extern "C" CallbackArray *igOverrideAttrSet_Register(void);
extern "C" void igOverrideAttrSet_GetMetaObjectFunction(void);
extern "C" igMetaObject *igNonRefCountedNodeList_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igNonRefCountedNodeList_GetMetaObject(void);
extern "C" int igNonRefCountedNodeList_GetVTable(void);
extern "C" CallbackArray *igNonRefCountedNodeList_Register(void);
extern "C" void igNonRefCountedNodeList_GetMetaObjectFunction(void);
extern "C" igMetaObject *igNodeListList_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igNodeListList_GetMetaObject(void);
extern "C" int igNodeListList_GetVTable(void);
extern "C" void igNodeListList_EnsureRegistered(void);
extern "C" CallbackArray *igNodeListList_Register(void);
extern "C" void igNodeListList_GetMetaObjectFunction(void);
extern "C" int FUN_0019cba0(int arg0);
extern "C" igMetaObject *igNodeList_GetMetaObject(void);
extern "C" int igNodeList_GetVTable(void);
extern "C" CallbackArray *igNodeList_Register(void);
extern "C" void igNodeList_GetMetaObjectFunction(void);
extern "C" igMetaObject *igNode_GetMetaObject(void);
extern "C" int igNode_GetVTable(void);
extern "C" CallbackArray *igNode_Register(void);
extern "C" void igNode_GetMetaObjectFunction(void);
extern "C" void igNode_InitFields(void);
extern "C" void **igSmartPointer_igRenderListAttr_Destruct(void **arg0, long long arg1);
extern "C" igMetaObject *igGeometry_GetPublishedMetaObject(void);
extern "C" int *igSmartPointer_igFloatList_Construct(int *p);
extern "C" igMetaObject *igModelViewMatrixBoneSelectListSg_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igModelViewMatrixBoneSelectListSg_GetMetaObject(void);
extern "C" int igModelViewMatrixBoneSelectListSg_GetVTable(void);
extern "C" CallbackArray *igModelViewMatrixBoneSelectListSg_Register(void);
extern "C" void igModelViewMatrixBoneSelectListSg_GetMetaObjectFunction(void);
extern "C" igMetaObject *igModelViewMatrixBoneSelect_GetMetaObject(void);
extern "C" int igModelViewMatrixBoneSelect_GetVTable(void);
extern "C" CallbackArray *igModelViewMatrixBoneSelect_Register(void);
extern "C" void igModelViewMatrixBoneSelect_GetMetaObjectFunction(void);
extern "C" void igModelViewMatrixBoneSelect_InitFields(void);
extern "C" igMetaObject *igLod_GetMetaObject(void);
extern "C" int igLod_GetVTable(void);
extern "C" CallbackArray *igLod_Register(void);
extern "C" void igLod_GetMetaObjectFunction(void);
extern "C" void igLod_InitFields(void);
extern "C" igMetaObject *igLightStateSet_GetMetaObject(void);
extern "C" int igLightStateSet_GetVTable(void);
extern "C" CallbackArray *igLightStateSet_Register(void);
extern "C" void igLightStateSet_GetMetaObjectFunction(void);
extern "C" void igLightStateSet_InitFields(void);
extern "C" igMetaObject *igLightSet_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igLightSet_GetMetaObject(void);
extern "C" int igLightSet_GetVTable(void);
extern "C" CallbackArray *igLightSet_Register(void);
extern "C" void igLightSet_GetMetaObjectFunction(void);
extern "C" igMetaObject *igNode_GetPublishedMetaObject(void);
extern "C" void igLightSet_InitFields(void);
extern "C" igMetaObject *igTransform_GetPublishedMetaObject(void);
extern "C" igMetaObject *igAnimationSequence_GetPublishedMetaObject(void);
extern "C" igSmartPointer<igObject> *igSmartPointer_igAnimationTransitionDefinitionList_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
extern "C" igSmartPointer<igObject> *igSmartPointer_igAnimationTrackList_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
extern "C" igSmartPointer<igObject> *igSmartPointer_igAnimationBindingList_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
extern "C" igMetaObject *igIntersectTraversal_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igIntersectTraversal_GetMetaObject(void);
extern "C" int igIntersectTraversal_GetVTable(void);
extern "C" void **igSmartPointer_igProbe_Destruct(void **arg0, short arg1);
extern "C" void FUN_0019e440(void);
extern "C" void igIntersectTraversal_GetMetaObjectFunction(void);
extern "C" igMetaObject *igTraversal_GetPublishedMetaObject(void);
extern "C" void igIntersectTraversal_InitFields(void);
extern "C" void FUN_0019e640(void);
extern "C" void thunk_igIntersectTraversal_UserUnregister(void);
extern "C" igMetaObject *igProbe_GetMetaObject(void);
extern "C" int igProbe_GetVTable(void);
extern "C" CallbackArray *igProbe_Register(void);
extern "C" void igProbe_GetMetaObjectFunction(void);
extern "C" void igProbe_InitFields(void);
extern "C" igMetaObject *igInterpretedShaderData_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igInterpretedShaderData_GetMetaObject(void);
extern "C" int igInterpretedShaderData_GetVTable(void);
extern "C" ObjectRefWord *igSmartPointer_igShaderFactory_Destruct(ObjectRefWord *self,int delete_storage);
extern "C" void igInterpretedShaderData_EnsureRegistered(void);
extern "C" CallbackArray *igInterpretedShaderData_Register(void);
extern "C" void igInterpretedShaderData_GetMetaObjectFunction(void);
extern "C" int FUN_0019ec60(void);
extern "C" void igInterpretedShaderData_InitFields(void);
extern "C" igMetaObject *igIniShaderFactory_GetMetaObject(void);
extern "C" int igIniShaderFactory_GetVTable(void);
extern "C" ObjectRefWord *igSmartPointer_igInterpretedShaderData_Destruct(ObjectRefWord *self,int delete_storage);
extern "C" CallbackArray *igIniShaderFactory_Register(void);
extern "C" void igIniShaderFactory_GetMetaObjectFunction(void);
extern "C" igMetaObject *igShaderFactory_GetPublishedMetaObject(void);
extern "C" void igIniShaderFactory_InitFields(void);

extern "C" igMetaObject *igGroup_GetMetaObject(void);
extern "C" int igGroup_GetVTable(void);
extern "C" void igGroup_GetMetaObjectFunction(void);
extern "C" void igGroup_InitFields(void);
extern "C" int FUN_0019f480(int arg0);
extern "C" igMetaObject *igGraphPathList_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igGraphPathList_GetMetaObject(void);
extern "C" int igGraphPathList_GetVTable(void);
extern "C" CallbackArray *igGraphPathList_Register(void);
extern "C" void igGraphPathList_GetMetaObjectFunction(void);
extern "C" igMetaObject *igGraphPath_GetMetaObject(void);
extern "C" int igGraphPath_GetVTable(void);
extern "C" CallbackArray *igGraphPath_Register(void);
extern "C" void igGraphPath_GetMetaObjectFunction(void);
extern "C" void igGraphPath_InitFields(void);
extern "C" igMetaObject *igGeometryList_GetMetaObject(void);
extern "C" int igGeometryList_GetVTable(void);
extern "C" CallbackArray *igGeometryList_Register(void);
extern "C" void igGeometryList_GetMetaObjectFunction(void);
extern "C" igMetaObject *igGeometry_GetMetaObject(void);
extern "C" int igGeometry_GetVTable(void);
extern "C" void igGeometry_GetMetaObjectFunction(void);
extern "C" void FUN_0019fca0(void);
extern "C" void thunk_FUN_001c51d0(void);
extern "C" igMetaObject *igFrustCullTraversal_GetMetaObject(void);
extern "C" int igFrustCullTraversal_GetVTable(void);
extern "C" struct R **igSmartPointer_igCapabilityManager_Destruct(struct R **arg0, short arg1);
extern "C" struct T_19fde0 **igSmartPointer_igAttrDefaultManager_Destruct(struct T_19fde0 **arg0, short arg1);
extern "C" void **igSmartPointer_igAttrStackManager_Destruct(void **arg0, int arg1);
extern "C" void **igSmartPointer_igTransformStack_Destruct(void **arg0, short arg1);
extern "C" void **igSmartPointer_igSorter_Destruct(struct Ref **self, short flag);
extern "C" void **igSmartPointer_igModelViewMatrixAttrPool_Destruct(void **arg0, long long arg1);
extern "C" O *igSmartPointer_igTimeAttrPool_Destruct(O *arg0, short arg1);
extern "C" void **igSmartPointer_igVertexBlendMatrixAttrPool_Destruct(void **arg0, short arg1);
extern "C" void **igSmartPointer_igTextureMatrixAttrPool_Destruct(void **arg0, short arg1);
extern "C" ObjectRefWord *igSmartPointer_igVertexBlendMatrixListAttrPool_Destruct(ObjectRefWord *self,int delete_storage);
extern "C" void **igSmartPointer_igMatrixObjectPool_Destruct(void **arg0, short arg1);
extern "C" ObjectRefWord *igSmartPointer_igProjectionMatrixAttrPool_Destruct(ObjectRefWord *self,int delete_storage);
extern "C" struct R **igSmartPointer_igMatrixOptStateAttr_Destruct(struct R **arg0, short arg1);
extern "C" ObjectRefWord *igSmartPointer_igNormalizeNormalsStateAttr_Destruct(ObjectRefWord *self,int delete_storage);
extern "C" void **igSmartPointer_igLongStack_Destruct(void **arg0, int arg1);
extern "C" void **igSmartPointer_igNonRefCountedMatrixObjectList_Destruct(void **arg0, short arg1);
extern "C" void **igSmartPointer_igNonRefCountedTransformList_Destruct(struct Ref **self, short flag);
extern "C" O *igSmartPointer_igBlendMatricesAttrPool_Destruct(O *arg0, short arg1);
extern "C" ObjectRefWord *igSmartPointer_igTimeAttr_Destruct(ObjectRefWord *self,int delete_storage);
extern "C" Obj_19fde0 *FUN_001a0910(Obj_19fde0 *arg0, short arg1);
extern "C" void **igSmartPointer_igClippingStateAttr_Destruct(void **arg0, short arg1);
extern "C" int *FUN_001a1080(int *p);
extern "C" int *igSmartPointer_igAABox_Construct(int *p);
extern "C" void *FUN_001a10a0(igCommonTraversal *arg0);
extern "C" void igFrustCullTraversal_EnsureRegistered(void);
extern "C" CallbackArray *igFrustCullTraversal_Register(void);
extern "C" void igFrustCullTraversal_GetMetaObjectFunction(void);
extern "C" igMetaObject *igCommonTraversal_GetPublishedMetaObject(void);
extern "C" void igFrustCullTraversal_InitFields(void);
extern "C" void FUN_001a13a0(void);
extern "C" void thunk_FUN_001c45d0(void);
extern "C" igMetaObject *igEnvironmentMapShader2List_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igEnvironmentMapShader2List_GetMetaObject(void);
extern "C" int igEnvironmentMapShader2List_GetVTable(void);
extern "C" void igEnvironmentMapShader2List_EnsureRegistered(void);
extern "C" CallbackArray *igEnvironmentMapShader2List_Register(void);
extern "C" void igEnvironmentMapShader2List_GetMetaObjectFunction(void);
extern "C" igMetaObject *igEnvironmentMapShader2_GetMetaObject(void);
extern "C" void igEnvironmentMapShader2_EnsureRegistered(void);
extern "C" CallbackArray *igEnvironmentMapShader2_Register(void);
extern "C" void igEnvironmentMapShader2_GetMetaObjectFunction(void);
extern "C" void igEnvironmentMapShader2_InitFields(void);
extern "C" void igPsx2EnvironmentMapShader_GetMetaObjectFunction(void);
extern "C" igMetaObject *igEnbayaTransformSource_GetMetaObject(void);
extern "C" int igEnbayaTransformSource_GetVTable(void);
extern "C" CallbackArray *igEnbayaTransformSource_Register(void);
extern "C" void igEnbayaTransformSource_GetMetaObjectFunction(void);
extern "C" void igEnbayaTransformSource_InitFields(void);
extern "C" igMetaObject *igEnbayaContextPool_GetMetaObject(void);
extern "C" int igEnbayaContextPool_GetVTable(void);
extern "C" CallbackArray *igEnbayaContextPool_Register(void);
extern "C" void thunk_igEnbayaContextPool_GetMetaObject(void);
extern "C" void igEnbayaContextPool_InitFields(void);
extern "C" igMetaObject *igEnbayaAnimationState_GetMetaObject(void);
extern "C" int igEnbayaAnimationState_GetVTable(void);
extern "C" CallbackArray *igEnbayaAnimationState_Register(void);
extern "C" void igEnbayaAnimationState_GetMetaObjectFunction(void);
extern "C" igMetaObject *igAnimationState_GetPublishedMetaObject(void);
extern "C" void igEnbayaAnimationState_InitFields(void);
extern "C" void FUN_001a2190(void);
extern "C" void FUN_001a21a0(void);
extern "C" igMetaEnum *FUN_001a21b0(void);
extern "C" igMetaObject *igEnbayaAnimationSource_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igEnbayaAnimationSource_GetMetaObject(void);
extern "C" int igEnbayaAnimationSource_GetVTable(void);
extern "C" CallbackArray *igEnbayaAnimationSource_Register(void);
extern "C" void igEnbayaAnimationSource_GetMetaObjectFunction(void);
extern "C" void igEnbayaAnimationSource_InitFields(void);
extern "C" void FUN_001a24d0(void);
extern "C" void FUN_001a24e0(void);
extern "C" igMetaObject *igCompressedTransformSequence1_5Data_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igCompressedTransformSequence1_5Data_GetMetaObject(void);
extern "C" int igCompressedTransformSequence1_5Data_GetVTable(void);
extern "C" void igCompressedTransformSequence1_5Data_EnsureRegistered(void);
extern "C" CallbackArray *igCompressedTransformSequence1_5Data_Register(void);
extern "C" void igCompressedTransformSequence1_5Data_GetMetaObjectFunction(void);
extern "C" void igCompressedTransformSequence1_5Data_InitFields(void);
extern "C" igMetaObject *igCompressedAnimationSequenceQS_GetMetaObject(void);
extern "C" int igCompressedAnimationSequenceQS_GetVTable(void);
extern "C" CallbackArray *igCompressedAnimationSequenceQS_Register(void);
extern "C" void igCompressedAnimationSequenceQS_GetMetaObjectFunction(void);
extern "C" void igCompressedAnimationSequenceQS_InitFields(void);
extern "C" void **igSmartPointer_igCompiledTransformList_Destruct(void **arg0, short arg1);
extern "C" ObjectRefWord *igSmartPointer_igEnvironmentMapShader2List_Destruct(ObjectRefWord *self,int delete_storage);
extern "C" int *igSmartPointer_igEnvironmentMapShader2List_Construct(int *p);
extern "C" int *FUN_001a2c50(int *p);
extern "C" int *igSmartPointer_igCompiledTransformList_Construct(int *p);
extern "C" int FUN_001a2c70(int arg0);
extern "C" igMetaObject *igBlendListRecord_GetMetaObject(void);
extern "C" int igBlendListRecord_GetVTable(void);
extern "C" void igBlendListRecord_EnsureRegistered(void);
extern "C" CallbackArray *igBlendListRecord_Register(void);
extern "C" void igBlendListRecord_GetMetaObjectFunction(void);
extern "C" void igBlendListRecord_InitFields(void);
extern "C" void *FUN_001a2ef0(int allocator);
extern "C" igMetaObject *igCompileTraversal_GetMetaObject(void);
extern "C" int igCompileTraversal_GetVTable(void);
extern "C" struct R **igSmartPointer_igBlendMatrixPaletteAttrList_Destruct(struct R **arg0, short arg1);
extern "C" int *igSmartPointer_igBlendMatrixPaletteAttrList_Construct(int *p);
extern "C" int *igSmartPointer_igNonRefCountedTransformList_Construct(int *p);
extern "C" int *igSmartPointer_igNonRefCountedMatrixObjectList_Construct(int *p);
extern "C" void igCompileTraversal_EnsureRegistered(void);
extern "C" CallbackArray *igCompileTraversal_Register(void);
extern "C" void igCompileTraversal_GetMetaObjectFunction(void);
extern "C" void igCompileTraversal_InitFields(void);
extern "C" void FUN_001a33e0(void);
extern "C" void thunk_FUN_001bb230(void);
extern "C" igMetaObject *igCompiledTransformList_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igCompiledTransformList_GetMetaObject(void);
extern "C" int igCompiledTransformList_GetVTable(void);
extern "C" void igCompiledTransformList_EnsureRegistered(void);
extern "C" CallbackArray *igCompiledTransformList_Register(void);
extern "C" void igCompiledTransformList_GetMetaObjectFunction(void);
extern "C" int FUN_001a3590(int arg0);
extern "C" igMetaObject *igCompiledTransform_GetMetaObject(void);
extern "C" int igCompiledTransform_GetVTable(void);
extern "C" void igCompiledTransform_EnsureRegistered(void);
extern "C" CallbackArray *igCompiledTransform_Register(void);
extern "C" void igCompiledTransform_GetMetaObjectFunction(void);
extern "C" void igCompiledTransform_InitFields(void);
extern "C" igMetaObject *FUN_001a38e0(void);
extern "C" igMetaObject *igCommonTraversal_GetMetaObject(void);
extern "C" int igCommonTraversal_GetVTable(void);
extern "C" int *FUN_001a3c60(void *p);
extern "C" int *FUN_001a3c70(void *p);
extern "C" int *FUN_001a3c80(void *p);
extern "C" int *FUN_001a3c90(void *p);
extern "C" int *FUN_001a3ca0(void *p);
extern "C" int *FUN_001a3cb0(void *p);
extern "C" int *igSmartPointer_igProjectionMatrixAttrPool_Construct(void *p);
extern "C" int *igSmartPointer_igMatrixObjectPool_Construct(void *p);
extern "C" int *igSmartPointer_igVertexBlendMatrixListAttrPool_Construct(void *p);
extern "C" int *igSmartPointer_igTextureMatrixAttrPool_Construct(void *p);
extern "C" int *igSmartPointer_igVertexBlendMatrixAttrPool_Construct(void *p);
extern "C" int *igSmartPointer_igTimeAttrPool_Construct(void *p);
extern "C" int *igSmartPointer_igModelViewMatrixAttrPool_Construct(void *p);
extern "C" int *igSmartPointer_igSorter_Construct(void *p);
extern "C" int *igSmartPointer_igVisualContext_Construct(void *p);
extern "C" int *igSmartPointer_igTransformStack_Construct(void *p);
extern "C" int *igSmartPointer_igAttrStackManager_Construct(void *p);
extern "C" int *igSmartPointer_igAttrDefaultManager_Construct(void *p);
extern "C" int *igSmartPointer_igCapabilityManager_Construct(void *p);
extern "C" void *FUN_001a3d90(igTraversal *arg0);
extern "C" CallbackArray *igCommonTraversal_Register(void);
extern "C" void igCommonTraversal_GetMetaObjectFunction(void);
extern "C" void igCommonTraversal_InitFields(void);
extern "C" void FUN_001a44d0(void);
extern "C" void thunk_igCommonTraversal_UserUnregister(void);
extern "C" igMetaObject *igCamera_GetMetaObject(void);
extern "C" int igCamera_GetVTable(void);
extern "C" CallbackArray *igCamera_Register(void);
extern "C" void igCamera_GetMetaObjectFunction(void);
extern "C" void igCamera_InitFields(void);
extern "C" igMetaEnum *FUN_001a47d0(void);
extern "C" igMetaObject *igBoundingBoxesMaker_GetMetaObject(void);
extern "C" int igBoundingBoxesMaker_GetVTable(void);
extern "C" void igBoundingBoxesMaker_EnsureRegistered(void);
extern "C" CallbackArray *igBoundingBoxesMaker_Register(void);
extern "C" void igBoundingBoxesMaker_GetMetaObjectFunction(void);
extern "C" void igBoundingBoxesMaker_InitFields(void);
extern "C" igMetaObject *igBlendMatrixSelect_GetMetaObject(void);
extern "C" int igBlendMatrixSelect_GetVTable(void);
extern "C" CallbackArray *igBlendMatrixSelect_Register(void);
extern "C" void igBlendMatrixSelect_GetMetaObjectFunction(void);
extern "C" void igBlendMatrixSelect_InitFields(void);
extern "C" igMetaObject *igBitMask_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igBitMask_GetMetaObject(void);
extern "C" int igBitMask_GetVTable(void);
extern "C" CallbackArray *igBitMask_Register(void);
extern "C" void igBitMask_GetMetaObjectFunction(void);
extern "C" int FUN_001a4f00(void);
extern "C" void igBitMask_InitFields(void);
extern "C" igMetaObject *igBillboard_GetMetaObject(void);
extern "C" int igBillboard_GetVTable(void);
extern "C" CallbackArray *igBillboard_Register(void);
extern "C" void igBillboard_GetMetaObjectFunction(void);
extern "C" void igBillboard_InitFields(void);
extern "C" int FUN_001a51d0(int arg0);
extern "C" igMetaObject *igNonRefCountedAttrStackManagerList_GetMetaObject(void);
extern "C" int igNonRefCountedAttrStackManagerList_GetVTable(void);
extern "C" void igNonRefCountedAttrStackManagerList_EnsureRegistered(void);
extern "C" CallbackArray *igNonRefCountedAttrStackManagerList_Register(void);
extern "C" void igNonRefCountedAttrStackManagerList_GetMetaObjectFunction(void);
extern "C" igMetaObject *igAttrStackManager_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igAttrStackManager_GetMetaObject(void);
extern "C" int igAttrStackManager_GetVTable(void);
extern "C" void **igSmartPointer_igAttrStackList_Destruct(void **arg0, long long arg1);
extern "C" void **igSmartPointer_igLightStateAttrPool_Destruct(void **arg0, int arg1);
extern "C" void igAttrStackManager_EnsureRegistered(void);
extern "C" CallbackArray *igAttrStackManager_Register(void);
extern "C" void igAttrStackManager_GetMetaObjectFunction(void);
extern "C" void igAttrStackManager_InitFields(void);
extern "C" void FUN_001a58e0(void);
extern "C" void thunk_igAttrStackManager_UserUnregister(void);
extern "C" igMetaObject *igAttrStackList_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igAttrStackList_GetMetaObject(void);
extern "C" int igAttrStackList_GetVTable(void);
extern "C" void igAttrStackList_EnsureRegistered(void);
extern "C" CallbackArray *igAttrStackList_Register(void);
extern "C" void igAttrStackList_GetMetaObjectFunction(void);
extern "C" int FUN_001a5a70(int arg0);
extern "C" igMetaObject *igAttrStack_GetMetaObject(void);
extern "C" int igAttrStack_GetVTable(void);
extern "C" void igAttrStack_EnsureRegistered(void);
extern "C" CallbackArray *igAttrStack_Register(void);
extern "C" void igAttrStack_GetMetaObjectFunction(void);
extern "C" void igAttrStack_InitFields(void);
extern "C" igMetaObject *igAttrSet_GetMetaObject(void);
extern "C" int igAttrSet_GetVTable(void);
extern "C" CallbackArray *igAttrSet_Register(void);
extern "C" void igAttrSet_GetMetaObjectFunction(void);
extern "C" void igAttrSet_InitFields(void);
extern "C" igMetaObject *igAppearanceList_GetMetaObject(void);
extern "C" int igAppearanceList_GetVTable(void);
extern "C" CallbackArray *igAppearanceList_Register(void);
extern "C" void igAppearanceList_GetMetaObjectFunction(void);
extern "C" igMetaObject *igAppearance_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igAppearance_GetMetaObject(void);
extern "C" int igAppearance_GetVTable(void);
extern "C" void **igSmartPointer_igSkin_Destruct(void **arg0, short arg1);
extern "C" void **igSmartPointer_igSkinList_Destruct(struct Ref **self, short flag);
extern "C" void **igSmartPointer_igModelViewMatrixBoneSelectList_Destruct(void **arg0, long long arg1);
extern "C" CallbackArray *igAppearance_Register(void);
extern "C" void igAppearance_GetMetaObjectFunction(void);
extern "C" void igAppearance_InitFields(void);
extern "C" igMetaObject *igAnimationSystem_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igAnimationSystem_GetMetaObject(void);
extern "C" void igAnimationSystem_EnsureRegistered(void);
extern "C" CallbackArray *igAnimationSystem_Register(void);
extern "C" void igAnimationSystem_GetMetaObjectFunction(void);
extern "C" void igAnimationSystem_InitFields(void);
extern "C" igMetaObject *igAnimationStatePool_GetMetaObject(void);
extern "C" int igAnimationStatePool_GetVTable(void);
extern "C" CallbackArray *igAnimationStatePool_Register(void);
extern "C" void thunk_igAnimationStatePool_GetMetaObject(void);
extern "C" igMetaObject *igAnimationStateList_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igAnimationStateList_GetMetaObject(void);
extern "C" int igAnimationStateList_GetVTable(void);
extern "C" CallbackArray *igAnimationStateList_Register(void);
extern "C" void igAnimationStateList_GetMetaObjectFunction(void);
extern "C" igMetaEnum *FUN_001a6a90(void);
extern "C" igMetaEnum *FUN_001a6af0(void);
extern "C" igMetaEnum *FUN_001a6b50(void);
extern "C" void FUN_001a6bb0(int arg0);
extern "C" igMetaObject *igAnimationState_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igAnimationState_GetMetaObject(void);
extern "C" int igAnimationState_GetVTable(void);
extern "C" void igAnimationState_EnsureRegistered(void);
extern "C" CallbackArray *igAnimationState_Register(void);
extern "C" void igAnimationState_GetMetaObjectFunction(void);
extern "C" void igAnimationState_InitFields(void);
extern "C" igMetaObject *igAnimationSequence_GetMetaObject(void);
extern "C" void igAnimationSequence_EnsureRegistered(void);
extern "C" CallbackArray *igAnimationSequence_Register(void);
extern "C" void igAnimationSequence_GetMetaObjectFunction(void);
extern "C" igMetaObject *igAnimationHierarchy_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igAnimationHierarchy_GetMetaObject(void);
extern "C" void igAnimationHierarchy_EnsureRegistered(void);
extern "C" CallbackArray *igAnimationHierarchy_Register(void);
extern "C" void igAnimationHierarchy_GetMetaObjectFunction(void);
extern "C" void igAnimationHierarchy_InitFields(void);
extern "C" igMetaObject *igAnimationModifierList_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igAnimationModifierList_GetMetaObject(void);
extern "C" int igAnimationModifierList_GetVTable(void);
extern "C" CallbackArray *igAnimationModifierList_Register(void);
extern "C" void igAnimationModifierList_GetMetaObjectFunction(void);
extern "C" igMetaEnum *FUN_001a7440(void);
extern "C" igMetaObject *igAnimationModifier_GetMetaObject(void);
extern "C" int igAnimationModifier_GetVTable(void);
extern "C" void igAnimationModifier_EnsureRegistered(void);
extern "C" CallbackArray *igAnimationModifier_Register(void);
extern "C" void igAnimationModifier_GetMetaObjectFunction(void);
extern "C" void igAnimationModifier_InitFields(void);
extern "C" igMetaObject *igAnimationDatabase_GetMetaObject(void);
extern "C" int igAnimationDatabase_GetVTable(void);
extern "C" ObjectRefWord *igSmartPointer_igSkeletonList_Destruct(ObjectRefWord *self,int delete_storage);
extern "C" void **igSmartPointer_igAnimationList_Destruct(void **arg0, short arg1);
extern "C" void **igSmartPointer_igAnimationCombinerList_Destruct(void **arg0, short arg1);
extern "C" CallbackArray *igAnimationDatabase_Register(void);
extern "C" void igAnimationDatabase_GetMetaObjectFunction(void);
extern "C" void igAnimationDatabase_InitFields(void);
extern "C" igMetaObject *igAnimationCombinerBoneInfoPool_GetMetaObject(void);
extern "C" int igAnimationCombinerBoneInfoPool_GetVTable(void);
extern "C" CallbackArray *igAnimationCombinerBoneInfoPool_Register(void);
extern "C" void thunk_igAnimationCombinerBoneInfoPool_GetMetaObject(void);
extern "C" igMetaObject *igAnimationCombinerBoneInfoListList_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igAnimationCombinerBoneInfoListList_GetMetaObject(void);
extern "C" int igAnimationCombinerBoneInfoListList_GetVTable(void);
extern "C" CallbackArray *igAnimationCombinerBoneInfoListList_Register(void);
extern "C" void igAnimationCombinerBoneInfoListList_GetMetaObjectFunction(void);
extern "C" igMetaObject *igAnimationCombinerBoneInfoList_GetMetaObject(void);
extern "C" int igAnimationCombinerBoneInfoList_GetVTable(void);
extern "C" CallbackArray *igAnimationCombinerBoneInfoList_Register(void);
extern "C" void igAnimationCombinerBoneInfoList_GetMetaObjectFunction(void);
extern "C" void igAnimationCombinerBoneInfo_Create(int arg0);
extern "C" igMetaObject *igAnimationCombinerBoneInfo_GetMetaObject(void);
extern "C" int igAnimationCombinerBoneInfo_GetVTable(void);
extern "C" void igAnimationCombinerBoneInfo_EnsureRegistered(void);
extern "C" CallbackArray *igAnimationCombinerBoneInfo_Register(void);
extern "C" void igAnimationCombinerBoneInfo_GetMetaObjectFunction(void);
extern "C" void igAnimationCombinerBoneInfo_InitFields(void);
extern "C" igMetaObject *igAnimationCombinerList_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igAnimationCombinerList_GetMetaObject(void);
extern "C" int igAnimationCombinerList_GetVTable(void);
extern "C" CallbackArray *igAnimationCombinerList_Register(void);
extern "C" void igAnimationCombinerList_GetMetaObjectFunction(void);
extern "C" igMetaObject *igAnimationCombiner_GetMetaObject(void);
extern "C" int igAnimationCombiner_GetVTable(void);
extern "C" void *FUN_001a8620(struct S_1a8620 *arg0, short arg1);
extern "C" ObjectRefWord *igSmartPointer_igAnimationCombinerBoneInfoListList_Destruct(ObjectRefWord *self,int delete_storage);
extern "C" struct R **igSmartPointer_igAnimationStateList_Destruct(struct R **arg0, short arg1);
extern "C" CallbackArray *igAnimationCombiner_Register(void);
extern "C" void igAnimationCombiner_GetMetaObjectFunction(void);
extern "C" igMetaObject *igAnimationSystem_GetPublishedMetaObject(void);
extern "C" void igAnimationCombiner_InitFields(void);
extern "C" void thunk_FUN_001abca0(void);
extern "C" void thunk_FUN_001abdf0(void);
extern "C" igMetaObject *igAnimationBindingList_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igAnimationBindingList_GetMetaObject(void);
extern "C" int igAnimationBindingList_GetVTable(void);
extern "C" CallbackArray *igAnimationBindingList_Register(void);
extern "C" void igAnimationBindingList_GetMetaObjectFunction(void);
extern "C" int FUN_001a8c30(int arg0);
extern "C" igMetaObject *igAnimationBinding_GetMetaObject(void);
extern "C" int igAnimationBinding_GetVTable(void);
extern "C" CallbackArray *igAnimationBinding_Register(void);
extern "C" void igAnimationBinding_GetMetaObjectFunction(void);
extern "C" void igAnimationBinding_InitFields(void);
extern "C" igMetaObject *igAnimationList_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igAnimationList_GetMetaObject(void);
extern "C" int igAnimationList_GetVTable(void);
extern "C" CallbackArray *igAnimationList_Register(void);
extern "C" void igAnimationList_GetMetaObjectFunction(void);
extern "C" int FUN_001a90f0(int arg0);
extern "C" igMetaObject *igAnimation_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igAnimation_GetMetaObject(void);
extern "C" int igAnimation_GetVTable(void);
extern "C" CallbackArray *igAnimation_Register(void);
extern "C" void igAnimation_GetMetaObjectFunction(void);
extern "C" void igAnimation_InitFields(void);
extern "C" igMetaObject *igAnimationTransitionDefinitionList_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igAnimationTransitionDefinitionList_GetMetaObject(void);
extern "C" int igAnimationTransitionDefinitionList_GetVTable(void);
extern "C" CallbackArray *igAnimationTransitionDefinitionList_Register(void);
extern "C" void igAnimationTransitionDefinitionList_GetMetaObjectFunction(void);
extern "C" igMetaObject *igAnimationTransitionDefinition_GetMetaObject(void);
extern "C" int igAnimationTransitionDefinition_GetVTable(void);
extern "C" void igAnimationTransitionDefinition_EnsureRegistered(void);
extern "C" CallbackArray *igAnimationTransitionDefinition_Register(void);
extern "C" void igAnimationTransitionDefinition_GetMetaObjectFunction(void);
extern "C" void igAnimationTransitionDefinition_InitFields(void);
extern "C" igMetaObject *igAnimationTransitionPointList_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igAnimationTransitionPointList_GetMetaObject(void);
extern "C" int igAnimationTransitionPointList_GetVTable(void);
extern "C" void igAnimationTransitionPointList_EnsureRegistered(void);
extern "C" CallbackArray *igAnimationTransitionPointList_Register(void);
extern "C" void igAnimationTransitionPointList_GetMetaObjectFunction(void);
extern "C" igMetaObject *igAnimationTransitionPoint_GetMetaObject(void);
extern "C" int igAnimationTransitionPoint_GetVTable(void);
extern "C" void igAnimationTransitionPoint_EnsureRegistered(void);
extern "C" CallbackArray *igAnimationTransitionPoint_Register(void);
extern "C" void igAnimationTransitionPoint_GetMetaObjectFunction(void);
extern "C" void igAnimationTransitionPoint_InitFields(void);
extern "C" igMetaObject *igAnimationTransitionParams_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igAnimationTransitionParams_GetMetaObject(void);
extern "C" int igAnimationTransitionParams_GetVTable(void);
extern "C" void igAnimationTransitionParams_EnsureRegistered(void);
extern "C" CallbackArray *igAnimationTransitionParams_Register(void);
extern "C" void igAnimationTransitionParams_GetMetaObjectFunction(void);
extern "C" void igAnimationTransitionParams_InitFields(void);
extern "C" igMetaObject *igAnimationTrackList_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igAnimationTrackList_GetMetaObject(void);
extern "C" int igAnimationTrackList_GetVTable(void);
extern "C" CallbackArray *igAnimationTrackList_Register(void);
extern "C" void igAnimationTrackList_GetMetaObjectFunction(void);
extern "C" igMetaObject *igAnimationTrack_GetMetaObject(void);
extern "C" int igAnimationTrack_GetVTable(void);
extern "C" CallbackArray *igAnimationTrack_Register(void);
extern "C" void igAnimationTrack_GetMetaObjectFunction(void);
extern "C" void igAnimationTrack_InitFields(void);
extern "C" int igActorInfo_GetVTable(void);
extern "C" void **igSmartPointer_igActor_Destruct(void **arg0, long long arg1);
extern "C" void igActorInfo_EnsureRegistered(void);
extern "C" CallbackArray *igActorInfo_Register(void);
extern "C" void igActorInfo_GetMetaObjectFunction(void);
extern "C" void igActorInfo_InitFields(void);
extern "C" igMetaObject *igActorList_GetMetaObject(void);
extern "C" int igActorList_GetVTable(void);
extern "C" CallbackArray *igActorList_Register(void);
extern "C" void igActorList_GetMetaObjectFunction(void);
extern "C" igMetaObject *igActor_GetOrCreateMetaObject(void);
extern "C" igMetaObject *igActor_GetMetaObject(void);
extern "C" int igActor_GetVTable(void);
extern "C" void **igSmartPointer_igAnimationSystem_Destruct(struct Ref **self, short flag);
extern "C" void **igSmartPointer_igAppearance_Destruct(void **arg0, long long arg1);
extern "C" O *igSmartPointer_igAnimationModifierList_Destruct(O *arg0, short arg1);
extern "C" CallbackArray *igActor_Register(void);
extern "C" void igActor_GetMetaObjectFunction(void);
extern "C" void igActor_InitFields(void);
extern "C" igMetaObject *igPsx2EnvironmentMapShader_GetMetaObject(void);
extern "C" int igPsx2EnvironmentMapShader_GetVTable(void);
extern "C" Obj_1aaf80 *FUN_001aaf80(Obj_1aaf80 *arg0, short arg1);
extern "C" ObjectRefWord *igSmartPointer_igMultiPassStateAttr_Destruct(ObjectRefWord *self,int delete_storage);
extern "C" int *igSmartPointer_igMultiPassStateAttr_Construct(int *p);
extern "C" int *igSmartPointer_igBlendFunctionAttr_Construct(int *p);
extern "C" void *FUN_001ab4a0(igEnvironmentMapShader2 *arg0);
extern "C" void igPsx2EnvironmentMapShader_EnsureRegistered(void);
extern "C" CallbackArray *igPsx2EnvironmentMapShader_Register(void);
extern "C" igMetaObject *igEnvironmentMapShader2_GetPublishedMetaObject(void);
extern "C" void igPsx2EnvironmentMapShader_InitFields(void);
extern "C" int FUN_001ab6c0(S_1ab6c0 *arg0, int arg1);
extern "C" int FUN_001ab770(void *arg0, void **arg1, void **arg2);
extern "C" int FUN_001ab8b0(int arg0, int arg1, void **arg2);
extern "C" int FUN_001ab920(const H *a, int id, T_1ab920 **out);
extern "C" void Gap__Sg__igTransformSequence1_5__vfunc_68(S0 *arg0);
extern "C" int Gap__Sg__igTransformSequence1_5__vfunc_50(igTransformSequence1_5 *self, int index);
extern "C" void Gap__Sg__igTransformSequence1_5__vfunc_67(S_1aba30 *arg0);
extern "C" long long Gap__Sg__igTransformSequence1_5__vfunc_65(igTransformSequence1_5 *self);
extern "C" long long Gap__Sg__igTransformSequence1_5__vfunc_56(igTransformSequence1_5 *arg0, int arg1);
extern "C" int Gap__Sg__igTransformSequence1_5__vfunc_42(igTransformSequence1_5 *self, int index);
extern "C" int Gap__Sg__igTransformSequence1_5__vfunc_41(igTransformSequence1_5 *arg0);
extern "C" int Gap__Sg__igTransformSequence1_5__vfunc_69(igTransformSequence1_5 *self);
extern "C" unsigned char Gap__Sg__igTransformSequence1_5__vfunc_60(igTransformSequence1_5 *self);
extern "C" int FUN_001abb50(S_1abb50 *arg0, A *arg1);
extern "C" int FUN_001abc20(int *arg0, int arg1);
extern "C" void FUN_001abca0(void);
extern "C" void FUN_001abdf0(void);
extern "C" void *FUN_001abed0(igCollisionGrid *a0, X *a1, void **out);
extern "C" void FUN_001ac040(igAnimationCombiner *arg0, igAnimationState *arg1);
extern "C" long long FUN_001acb10(igTimeView *a);
extern "C" void FUN_001acb50(igAnimationCombiner *c);
extern char g_cleanCombinerStates;
/* Slot 24 of a time source returns its current time. */
class TimeSourceView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4();
    virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
    virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14();
    virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual long long getTime();
};
/* Slot 22 of the animation hierarchy returns its bone count. */
class HierarchyCountView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4();
    virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
    virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14();
    virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual void d20(); virtual void d21();
    virtual int getBoneCount();
};
class CombinerSelfView;
extern "C" float *Gap__Sg__igAnimationCombiner__vfunc_24(CombinerSelfView *self, TimeSourceView *timeSource);
extern "C" void igAnimationCombiner_SetHierarchyUpdated(igAnimationCombiner *self, char arg1);
extern "C" int igCompressedAnimationSequenceQS_evaluateRotationAndTranslation(void **arg0, int arg1, int arg2, int arg3, int arg4, int arg5);
extern "C" int Gap__Sg__igCompressedAnimationSequenceQS__vfunc_24(igCompressedSeqView *self);
extern "C" long long Gap__Bec__beHitLandModelTraversal__vfunc_24(TraversalVirtual *t);
extern "C" void igAnimationCombiner_UserPostLoad(CombinerView *c);
extern "C" void FUN_001ad5c0(A_1ad5c0 *arg0, It *arg1, int arg2);
extern "C" void FUN_001ad770(igAnimationCombiner *a);
extern "C" int FUN_001ad860(igAnimationCombiner *arg0, igAnimationState *arg1);
extern "C" int FUN_001ad990(CombinerBlendView *c, CombinerAnimation *anim, int combineMode, int transitionMode, int status, int *priorities, bool perBone, CombinerBinding *binding);
extern "C" void FUN_001ae1b0(void *arg0, float fparg0, float fparg1, float fparg2, float fparg3);
extern "C" void **FUN_001ae1d0(void **arg0, void *arg1);
extern "C" void **FUN_001ae250(void **arg0, igObject *arg1);
extern "C" int FUN_001ae2d0(CombinerStateView *c, igPoolObject *state);
extern "C" void igAnimationCombiner_userDestruct(void **arg0);
extern "C" int igAnimationCombiner_Configured(igAnimationCombiner *self);
extern "C" void *Gap__Sg__igAnimationDatabase__vfunc_24(O_1aea60 *arg0, char *arg1);
extern "C" int FUN_001aedd0(void *self, igTDataList<AnimDbRecord *> *list, int file, AnimDbRecord *object);
extern "C" bool igAnimationDatabase_FindObjectReference(AnimDbRec *db, int file, AnimDbObject *obj);
extern "C" void Gap__Sg__igAnimationState__vfunc_23(void);
extern "C" void Gap__Sg__igAnimationState__vfunc_24(void);
extern "C" void Gap__Sg__igAnimationState__vfunc_25(void);
extern "C" void Gap__Sg__igAnimationState__vfunc_26(void);
extern "C" int FUN_001af620(igAppearanceView *a, void *t);
extern "C" void igAttrSet_Reset(S_1af7e0 *arg0);
extern "C" void FUN_001af860(igAttrStack *arg0);
extern "C" void Gap__Sg__igAttrStackManager__vfunc_23(struct O_1af890 *arg0);
extern "C" void igAttrStackManager_userConstruct(unsigned char *arg0, int arg1);
extern "C" void igAttrStackManager_userDestruct(int arg0);
extern "C" void igAttrStackManager_UserUnregister(void);
extern "C" void igAttrStackManager_RegisterClass(char *arg0);
extern "C" void igAttrStackManager_RegisterAttribute(AttrManagerRec *m, AttrObj *meta);
extern "C" void FUN_001b0250(PendingValueCollector *arg0, PendingIntList *arg1);
extern "C" void FUN_001b0440(int a0, int a1);
extern "C" void FUN_001b0450(A_1b0450 *arg0, Rc_1b0450 *arg1);
extern "C" void FUN_001b0dc0(O_1b0dc0 *arg0);
extern "C" void FUN_001b1030(igAttrStackManager *self, igAttr *attr);
extern "C" void FUN_001b1100(struct A_1b1100 *arg0, struct B_1b1100 *arg1);
extern "C" void FUN_001b11b0(struct A_1b11b0 *arg0, struct B_1b11b0 *arg1);
extern "C" void FUN_001b1250(struct A_1b1250 *arg0, struct B_1b1250 *arg1, int arg2);
extern "C" void FUN_001b21d0(A_1b21d0 *arg0, igVec3f *arg1, igVec3f *arg2);
extern "C" void FUN_001b23b0(int *arg0, int *arg1);
extern "C" int FUN_001b23e0(int arg0, Y *arg1);
extern "C" int FUN_001b24d0(int arg0, int arg1);
extern "C" bool igGeometry_ExtendBound(int arg0, void *arg1);
extern "C" int igTransform_ExtendBound(int arg0, void *arg1, long long time);
extern "C" void Gap__Core__igObject__vfunc_37(void *self, int arg1);
extern "C" int igTransformSequence_ExtendBound(AABoxFields *arg0, TransformInputView *arg1);
extern "C" void FUN_001b2f30(struct O_1b2750 *arg0, int arg1, struct B_1b2750 *arg2);
extern "C" long long Gap__Sg__igCommonTraversal__vfunc_26(igCommonTraversal *t);
extern "C" int FUN_001b3ad0(igCommonTraversal *arg0, int arg1);
extern "C" void FUN_001b3c90(A0 *arg0, A1 *arg1);
extern "C" void FUN_001b3ff0(void *arg0, int arg1);
extern "C" void FUN_001b4090(T_1b2fa0 *arg0, int arg1, int arg2);
extern "C" int FUN_001b40f0(void *arg0, int arg1);
extern "C" int FUN_001b4120(int *p);
extern "C" int FUN_001b4130(struct O4130 *arg0);
extern "C" void FUN_001b4220(struct A4220 *arg0, struct B4220 *arg1);
extern "C" void FUN_001b42c0(TravFlattenView *self, int root);
extern "C" void FUN_001b4500(struct O4500 *o, struct S4500 *s, int b);
extern "C" int FUN_001b4bb0(igCommonTraversal *arg0, int arg1);
struct LightingTexGenView;
extern "C" void FUN_001b4570(LightingTexGenView *self, igCommonTraversal *traversal);
extern "C" void igCommonTraversal_RegisterClass(int arg0);
extern "C" void igCommonTraversal_RegisterClassFunction(void *self, void *meta);
extern "C" void igCommonTraversal_userConstruct(igCommonTraversal *arg0, int arg1);
extern "C" void igCommonTraversal_UserRegister(void);
extern "C" void igCommonTraversal_UserUnregister(void);
extern "C" void igCommonTraversal_userDestruct(igObject *self);
extern "C" int Gap__Sg__igCommonTraversal__vfunc_30(igCommonTraversalView *self);
extern "C" void FUN_001b6cd0(int a0, float, float, float, float, float, float);
extern "C" void igCommonTraversal_SetPerspective(void *arg0, float fparg0, float fparg1, float fparg2, float fparg3, float fparg4);
extern "C" void Gap__Sg__igCommonTraversal__vfunc_31(A_1b6e20 *arg0);
extern "C" void igCommonTraversal_SetViewMatrix(int arg0, int *arg1);
extern "C" void igCommonTraversal_Setup(A_1b6f30 *arg0, R_1b6f30 *arg1, R_1b6f30 *arg2);
extern "C" void igCommonTraversal_SetVisualContext(O_1b7010 *arg0, R_1b7010 *arg1);
extern "C" V128 *FUN_001b7330(O_1b7330 *arg0, float *arg1);
extern "C" void FUN_001b73d0(struct S_1b73d0 *arg0);
extern "C" void Gap__Sg__igCommonTraversal__vfunc_23(igCommonTraversalOps *t, int root);
extern "C" void Gap__Sg__igCommonTraversal__vfunc_32(igCommonTraversal *self, long long arg1);
extern "C" void Gap__Sg__igCommonTraversal__vfunc_24(igCommonTraversal *t, int arg1);
extern "C" void Gap__Sg__igCommonTraversal__vfunc_33(igCommonTraversal *self);
extern "C" int FUN_001b7740(void **arg0, void **arg1);
extern "C" void FUN_001b7770(igCommonTraversal *self, int name, int value);
extern "C" igObject *FUN_001b7920(igCommonTraversal *self, int name);
extern "C" int FUN_001b7af0(void *arg0, int arg1);
extern "C" int igCommonTraversal_TraverseSwitch(void *t, void *arg);
extern "C" int FUN_001b7c70(void **arg0, void *arg1);
extern "C" int FUN_001b7ce0(C_1b7ce0 *arg0, A_1b7ce0 *arg1);
extern "C" int FUN_001b7d70(void *arg0, void *arg1);
extern "C" int Gap__Sg__igActor__vfunc_37(ActorView *o0, ActorTraversal *t0);
extern "C" void FUN_001b89b0(void *arg0, igCommonTraversal *arg1);
extern "C" int FUN_001b8a00(int *p);
extern "C" int FUN_001b8a10(int *p);
extern "C" void FUN_001b8a20(Src *arg0, Dst *arg1);
extern "C" int igCommonTraversal_TraverseJointTransform(igCommonTraversal *self, int arg1);
extern "C" void FUN_001b8c80(void *self, int arg1);
extern "C" void FUN_001b8cf0(igCommonTraversal *arg0, char *arg1);
extern "C" int FUN_001b8de0(Dst_1b8de0 *arg0, Src_1b8de0 *arg1);
extern "C" int igCommonTraversal_TraverseBillboard(C_1b8f20 *arg0, D *arg1);
extern "C" int FUN_001b99d0(DrawTraversalView *o, SwitchGroupView *g);
extern "C" void igCommonTraversal_TraverseTransform(int arg0, int arg1);
extern "C" int igCommonTraversal_TraverseLightSet(LightTraversalView *o, LightSceneView *scene);
extern "C" int FUN_001b9f00(igCompileTraversal *arg0, igAttrSet *arg1);
extern "C" int igCommonTraversal_TraverseLightStateSet(struct A_1b9fc0 *arg0, struct B_1b9fc0 *arg1);
extern "C" int igCommonTraversal_TraverseLod(CullTraversalView *o, CullNodeView *node);
extern "C" int igCommonTraversal_TraverseBumpMapShader(int a0, int arg1);
extern "C" int igCommonTraversal_TraverseCartoonShader(int arg0_, int arg1);
extern "C" int igCommonTraversal_TraversePlanarShadowShader(int a0, int arg1);
extern "C" int igCommonTraversal_TraverseTransformRecorder(igCommonTraversal *arg0, VC1 *arg1);
extern "C" void Gap__Sg__igTransformRecorder__vfunc_38(igTransformRecorder *self, const float *matrix);
extern "C" void Gap__Sg__igTransformRecorder__vfunc_37(igTransformRecorder *self, const float *matrix);
extern "C" int FUN_001baa10(RecorderTraversalView *o, TransformRecorderVisitor *v);
extern "C" int FUN_001bab30(int a0, void **arg1);
extern "C" int igCommonTraversal_TraverseEnvironmentMapShader2(int arg0, void **arg1);
extern "C" int FUN_001bac90(int arg0, void **arg1);
extern "C" int igCommonTraversal_TraverseModelViewMatrixBoneSelect(DrawItemSource *arg0, DrawItemIndex *arg1);
extern "C" int igCommonTraversal_TraverseBlendMatrixSelect(CompileTraversalHead *o, BlendNodeView *node);
extern "C" int igCommonTraversal_TraverseSegment(int arg0, struct S_1bafb0 *arg1);
class DW4VC_104_3 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual long long vX(); };
struct KeyTrackValue : public igObject { };
extern "C" int FUN_001bb090(S_1e04c0 *self, KeyTrackView *track);
extern "C" void FUN_001bb1f0(int arg0);
extern "C" void FUN_001bb200(void);
extern "C" void FUN_001bb230(void);
extern "C" void igCompileTraversal_userConstruct(C_1bb280 *arg0, int arg1);
extern "C" void Gap__Sg__igCompileTraversal__vfunc_31(char *p);
extern "C" void igCompileTraversal_userDestruct(void **self);
extern "C" void igCompileTraversal_RegisterClassFunction(int arg0, int arg1);
extern "C" void Gap__Sg__igCompileTraversal__vfunc_23(igCompileTraversal *self, int arg1);
extern "C" void Gap__Sg__igCompileTraversal__vfunc_24(igCompileTraversal *arg0, int arg1);
extern "C" int igCompileTraversal_TraverseTransform(int arg0, int arg1);
extern "C" float *FUN_001bcd60(float *v, int i);
extern "C" float FUN_001bcd70(const float *v, int i);
extern "C" int igCompileTraversal_TraverseProjectiveShadowShader(igCompileTraversal *self);
extern "C" int FUN_001bcd90(void *arg0);
extern "C" int FUN_001bcda0(void *arg0);
extern "C" int FUN_001bcdb0(void *arg0);
extern "C" int FUN_001bcdc0(void *arg0);
extern "C" int igCompileTraversal_TraversePlanarShadowShader(igCompileTraversal *self);
extern "C" int FUN_001bcde0(void *arg0);
extern "C" int igCompileTraversal_TraverseEnvironmentMapShader2(igCompileTraversal *self, void **arg1);
extern "C" int igCompileTraversal_TraverseModelViewMatrixBoneSelect(igCompileTraversal *self, int *arg1);
extern "C" int igCompileTraversal_TraverseBlendMatrixSelect(A_1bcf70 *arg0, B_1bcf70 *arg1);
extern "C" int FUN_001bd0e0(int arg0, void *arg1);
extern "C" int igCompileTraversal_TraverseActor(void);
extern "C" int igCompileTraversal_TraverseSegment(void);
extern "C" void FUN_001bd170(struct A_1bd170 *arg0, struct B_1bd170 *arg1);
extern "C" void FUN_001bd6b0(Links *links, Shape *shape);
extern "C" int FUN_001bd890(RemapOwner *o, RemapContext *ctx);
extern "C" void FUN_001bf020(void);
extern "C" int FUN_001bf3d0(igTransformSequence1_5 *self);
extern "C" int Gap__Sg__igTransformSequence1_5__vfunc_43(igTransformSequence1_5 *self);
extern "C" int Gap__Sg__igTransformSequence1_5__vfunc_39(igTransformSequence1_5 *self);
extern "C" void FUN_001bf400(int arg0, int arg1, long long arg2);
extern "C" void FUN_001bf560(QSView *o, int index, float *out);
extern "C" void Gap__Sg__igCompressedAnimationSequenceQS__vfunc_46(QSView *o, int index, float *out);
extern "C" long long Gap__Sg__igCompressedAnimationSequenceQS__vfunc_42(igCompressedAnimationSequenceQS *self, int arg1);
extern "C" int Gap__Sg__igCompressedAnimationSequenceQS__vfunc_23(O_1bfa60 *a0, int a1, long long a2);
extern "C" int Gap__Sg__igCompressedAnimationSequenceQS__vfunc_35(igCompressedAnimationSequenceQS *self);
extern "C" void FUN_001bfc70(O_1bfc70 *o, long long t, int *a2, int *a3, float *a4, float *a5);
extern "C" void Gap__Sg__igCompressedAnimationSequenceQS__vfunc_48(struct S_1bfe90 *arg0, int *arg1, void *arg2, int *arg3, float fparg0);
extern "C" void Gap__Sg__igCompressedAnimationSequenceQS__vfunc_47(igCompressedAnimationSequenceQS *self, int *arg1, int arg2, int arg3, float fparg0);
extern "C" int Gap__Sg__igCompressedAnimationSequenceQS__vfunc_25(S_1c0010 *arg0, int arg1, long long arg2);
extern "C" int Gap__Sg__igCompressedAnimationSequenceQS__vfunc_27(O_1c00e0 *arg0, int arg1, int arg2, long long arg3);
extern "C" int FUN_001c0240(igTransformSequence1_5 *self);
extern "C" int FUN_001c0390(void *, int);
extern "C" void FUN_001c03a0(DepthOfFieldNode *arg0, A1_1c03a0 *arg1);
extern "C" void FUN_001c07d0(void);
extern "C" void FUN_001c07e0(void);
extern "C" void igEnbayaAnimationSource_resetFields(igEnbayaAnimationSource *self);
extern "C" int Gap__Sg__igEnbayaAnimationSource__vfunc_23(void **arg0, int arg1, int arg2, int arg3);
extern "C" int Gap__Sg__igEnbayaAnimationSource__vfunc_24(EnbayaSourceSlots24 *o, int a, int b, int c, int d, int e);
extern "C" int Gap__Sg__igEnbayaAnimationSource__vfunc_25(EnbayaSourceView *o, float *out, long long time, int track);
extern "C" int Gap__Sg__igEnbayaAnimationSource__vfunc_26(EnbayaSourceSlots26 *o, int a, int b, int c, int d, int e);
extern "C" int Gap__Sg__igEnbayaAnimationSource__vfunc_27(EnbayaSourceView *o, float *out, float *pos, long long time, int track);
extern "C" int Gap__Sg__igEnbayaAnimationSource__vfunc_28(EnbayaSourceSlots28 *o, int a, int b, int c, int d, int e, int g);
extern "C" void igEnbayaAnimationSource_UserPostLoad(Obj_1c0e70 *arg0);
extern "C" void FUN_001c0f00(int mode);
extern "C" igMetaObject *igEnbayaAnimationState_GetPublishedMetaObject(void);
extern "C" void FUN_001c10f0(void);
extern "C" void FUN_001c1100(void);
extern "C" void igEnbayaAnimationState_UserPostLoad(void **arg0);
extern "C" void Gap__Sg__igEnbayaAnimationState__vfunc_23(igEnbayaAnimationState *arg0);
extern "C" void Gap__Sg__igEnbayaAnimationState__vfunc_24(igEnbayaAnimationState *self);
extern "C" void Gap__Sg__igEnbayaAnimationState__vfunc_25(igEnbayaAnimationState *self);
extern "C" void Gap__Sg__igEnbayaAnimationState__vfunc_26(igEnbayaAnimationState *self);
extern "C" void igEnbayaContextPool_resetFields(int arg0, int flags);
extern "C" void igEnbayaContextPool_destructFields(Obj_1c1450 *arg0);
extern "C" int FUN_001c1560(T_1c1560 *arg0, int arg1);
extern "C" void FUN_001c17e0(EnbayaContextPoolView *o, int boneCount);
extern "C" void FUN_001c1a80(T_1c1a80 *arg0, int arg1, int arg2);
extern "C" int Gap__Sg__igEnbayaTransformSource__vfunc_23(S_1c1b50 *arg0, int arg1, int arg2);
extern "C" int Gap__Sg__igEnbayaTransformSource__vfunc_24(void *arg0, int a1, int a2, int a3, int a4);
extern "C" int Gap__Sg__igEnbayaTransformSource__vfunc_25(EnbayaTransformSourceView *o, int a, int b);
extern "C" int igEnbayaTransformSource_evaluateRotation(EnbayaTransformSourceView_1c1bd0 *o, int a, int b, int c, int d);
extern "C" int Gap__Sg__igEnbayaTransformSource__vfunc_27(EnbayaTransformSourceView_1c1bf0 *o, int a, int b, int c);
extern "C" int igEnbayaTransformSource_evaluateRotationAndTranslation(EnbayaTransformSourceView_1c1c10 *o, int a, int b, int c, int d, int e);
extern "C" int Gap__Sg__igEnbayaTransformSource__vfunc_31(void);
extern "C" void Gap__Sg__igEnbayaTransformSource__vfunc_32(int a0);
extern "C" void FUN_001c1c50(void **self, int flag);
extern "C" void FUN_001c1c60(T_1c1c60 *arg0);
extern "C" int FUN_001c1e00(void);
extern "C" void FUN_001c1e10(void);
extern "C" void FUN_001c1f90(int);
extern "C" void FUN_001c20b0(Controller *self);
extern "C" void FUN_001c2880(S_1c2880 *arg0);
struct EnvAttr { char _pad0[8]; short _attrIndex; short _unitOffset; };
struct EnvAttrList { char _pad0[8]; int _count; int _capacity; EnvAttr **_data; };
struct EnvSlot : igTDataList<EnvAttr *> { char _pad14[4]; int _mark; void (*_onPop)(EnvAttr *, int); };
struct EnvSlotTable { char _pad0[16]; EnvSlot **_data; };
struct EnvAttrStack { char _pad0[16]; EnvSlotTable *_slots; char _pad14[28]; int _popArg; char _pad34[16]; int *_unitOfAttr; };
struct EnvListList { char _pad0[8]; int _count; int _capacity; EnvAttrList **_data; };
struct EnvTraversalView { char _pad0[32]; int _arg32; char _pad24[16]; EnvAttrStack *_attrStack; char _pad38[12]; A_1dc500 *_context; };
class EnvPassShaderView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
    virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
    virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39();
    virtual void d40(); virtual void d41(); virtual void d42();
    virtual void prepare(EnvTraversalView *);
    virtual void d44(); virtual void d45();
    virtual void configure(int);
    char _pad4[44];
    unsigned char _unit;
    char _pad31[11];
    unsigned char _configured;
    char _pad3d[3];
    EnvListList *_pushLists;
    EnvListList *_popLists;
    unsigned char _useContext;
};
static inline void pushEnvAttr(EnvAttrStack *s, EnvAttr *a) {
    int idx = a->_unitOffset + s->_unitOfAttr[a->_attrIndex];
    EnvSlot *l = s->_slots->_data[idx];
    if (l->_mark < 0) l->_mark = l->_count;
    l->append(a);
    igAttrStackManager_MarkStackChanged((igAttrStackManager *)s, (igAttrStack *)l, idx);
}
static inline void popEnvAttr(EnvAttrStack *s, EnvAttr *a) {
    int idx = a->_unitOffset + s->_unitOfAttr[a->_attrIndex];
    EnvSlot *l = s->_slots->_data[idx];
    int last = l->_count - 1;
    EnvAttr **d = l->_data;
    EnvAttr *top = d[last];
    void (*cb)(EnvAttr *, int) = l->_onPop;
    if (cb != 0 && top == a) cb(top, s->_popArg);
    l->_count = l->_count - 1;
    if (l->_count == l->_mark) l->_mark = -1;
    igAttrStackManager_MarkStackChanged((igAttrStackManager *)s, (igAttrStack *)l, idx);
}
extern "C" void FUN_001c2be0(EnvPassShaderView *self, EnvTraversalView *t);
extern "C" void igPsx2EnvironmentMapShader_SetEnvironmentMapTexture(S0_1c2eb0 *arg0, Rc *arg1);
extern "C" void igPsx2EnvironmentMapShader_SetDiffuseTexture(igPsx2EnvironmentMapShader *self, igObject *value);
extern "C" void igPsx2EnvironmentMapShader_SetDiffuseTextureCoordIndex(igPsx2EnvironmentMapShader *self, int coordIndex);
extern "C" void igPsx2EnvironmentMapShader_SetGlossMapTexture(igPsx2EnvironmentMapShader *self, igObject *value);
extern "C" void igPsx2EnvironmentMapShader_SetGlossTextureCoordIndex(igPsx2EnvironmentMapShader *self, int coordIndex);
extern "C" void igPsx2EnvironmentMapShader_SetReflectionAmount(igPsx2EnvironmentMapShader *self, float reflectionAmount);
extern "C" void igPsx2EnvironmentMapShader_SetTransparencyState(igPsx2EnvironmentMapShader *self, char isTransparent);
extern "C" void FUN_001c3090(V_1c3090 *arg0, int arg1);
extern "C" void FUN_001c31d0(void);
extern "C" void FUN_001c3ab0(int width, int height, int bpp, void *face1, void *face0, void *face3, void *face2, void *face5, void *face4, unsigned char *out);
extern "C" int FUN_001c3fd0(float *v);
extern "C" void FUN_001c4590(int arg0);
extern "C" void FUN_001c45a0(void);
extern "C" void FUN_001c45d0(void);
extern "C" void Gap__Sg__igFrustCullTraversal__vfunc_31(igFrustCullTraversal *self);
extern "C" void igFrustCullTraversal_userConstruct(O_1c4650 *arg0, int arg1);
extern "C" void igFrustCullTraversal_RegisterClassFunction(int arg0, int arg1);
extern "C" void Gap__Sg__igFrustCullTraversal__vfunc_24(igCommonTraversal *self, int arg1);
extern "C" void FUN_001c47a0(void *arg0, int arg1, int arg2);
extern "C" int FUN_001c4ac0(CullFrustumView *o, CullBoundsView *b);
extern "C" void FUN_001c51d0(void);
extern "C" void igGeometry_UserPostLoad(ParticleTimer *arg0);
extern "C" void igGeometry_SetFlags(ParticleTimer *arg0, int arg1);
extern "C" void igGeometry_EnableFlags(ParticleTimer *arg0, int arg1, int arg2);
extern "C" void igGeometry_Transform(ParticleTimer *arg0, int arg1);
extern "C" void igGeometry_Reset(ParticleAttributeObj *arg0);
extern "C" void FUN_001c5660(Z_1c5660 *arg0, int arg1, int arg2);
extern "C" void FUN_001c5730(int *p, igObject *object);
extern "C" void FUN_001c5740(U_1c5740 *arg0, T_1c5740 *arg1);
extern "C" void FUN_001c5870(void *arg0, int arg1);
extern "C" int FUN_001c58c0(T_1c58c0 *arg0);
extern "C" int FUN_001c59b0(void *self);
extern "C" void FUN_001c59f0(OO *arg0, int arg1, int arg2, long long arg3);
extern "C" int igNode_GetMeta(void);
extern "C" void igGroup_UserPostLoad(SgLinkNode *o);
extern unsigned char DAT_00554980;
#define g_compileKeepBound DAT_00554980
class CompiledGraphView;
extern "C" int FUN_001bdc80(CompiledGraphView *self, igObject *scene);
extern "C" int igGroup_InsertChild(T_1c5d70 *self, int a1, O_1c5d70 *a2);
extern "C" void igGroup_userDestruct(T_1c5e20 *arg0);
extern "C" void FUN_001c6110(O_1c6110 *arg0, int arg1);
extern "C" void igNode_EnableFlags(struct S_1c6230 *arg0, int arg1, int arg2);
extern "C" int igGroup_IsTransformable(void *arg0);
extern "C" int igNode_IsTransformable(void **arg0);
extern "C" void igGroup_Transform(int *arg0, int arg1);
extern "C" void igNode_Transform(void);
extern "C" void FUN_001c63e0(int arg0, int arg1);
struct IniStrRef {
    char *p;
    IniStrRef() {}
    IniStrRef(char *text) : p(text) {}
    IniStrRef(const igStringRef &s) : p(s.p) { if (p != 0) ((int *)p)[-1] = ((int *)p)[-1] + 1; }
    IniStrRef(const IniStrRef &o) : p(o.p) { if (p != 0) ((int *)p)[-1] = ((int *)p)[-1] + 1; }
    static inline void Release(char *s) {
        int *x = (int *)s;
        if (x != 0) { int *hd = x - 2; int c = x[-1] - 1; x[-1] = c; if (c == 0) StringChunk_ReleaseHeader((StringChunk *)*hd, (StringTokenHeader *)hd); }
    }
    ~IniStrRef() { Release(p); }
    /* The holder as the list services take it: a pointer to the string word. */
    char *const *ref() const { return &p; }
};
extern "C" IniStrRef FUN_001c6fa0(IniSectionNode *node);
extern "C" int FUN_001c6520(O_1c6520 *arg0, int arg1);
extern "C" int FUN_001c66c0(Node *self, int force);
extern "C" igSmartPointer<ShaderObject> igIniShaderFactory_GetInterfaceParameterString(Factory *self, const char *name);
extern "C" int FUN_001ca6b0(int *p, int);
extern "C" igSmartPointer<ShaderObject_1ca6c0> FUN_001ca6c0(ShaderProcessorView *self, char *name, unsigned char flag);
extern "C" igMetaObject *igShaderProcessor_GetMeta(void);
class IniFieldTarget {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
    virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual void *getMeta();
};
struct IniItemList { char pad0[8]; int count; char pad1[4]; void **data; };
struct IniFieldView { char pad0[56]; void *refMeta; };
static inline IniFieldView *asObjectRefField(IniFieldView *f) {
    if (f != 0 && ((Gap::Core::igObject *)f)->isOfType(Gap::Core::igObjectRefMetaField::getClassMeta()) != 0) {
        return f;
    }
    return 0;
}
static inline void *itemAt(IniItemList *l, int i) { return l->data[i]; }
extern "C" void FUN_001cade0(void *self, IniFieldTarget *target, IniItemList *items, void *names, void *lookup, void *fieldNames);
extern "C" void FUN_001cb010(void *self, IniValueTarget *target, IniValueList *list);
extern "C" void FUN_001cb1f0(void *self, char *name, int ini, int section, DW4VC_96_1 *target, IniValueList *values);
extern "C" void FUN_001cb2d0(void *self, void *types, const char *key, void *target);
class ShaderPassList {
public:
    virtual void d0();    virtual void d1();    virtual void d2();    virtual void d3();    virtual void d4();    virtual void d5();    virtual void d6();    virtual void d7();    virtual void d8();    virtual void d9();    virtual void d10();    virtual void d11();    virtual void d12();    virtual void d13();    virtual void d14();    virtual void d15();    virtual void d16();    virtual void d17();    virtual void d18();    virtual void d19();    virtual void d20();
    virtual void setCount(int);
    virtual void d22();
    virtual void prepare();
};
class ShaderTarget {
public:
    virtual void d0();    virtual void d1();    virtual void d2();    virtual void d3();    virtual void d4();    virtual void d5();    virtual void d6();    virtual void d7();    virtual void d8();    virtual void d9();    virtual void d10();    virtual void d11();    virtual void d12();    virtual void d13();    virtual void d14();    virtual void d15();    virtual void d16();    virtual void d17();    virtual void d18();    virtual void d19();    virtual void d20();    virtual void d21();    virtual void d22();    virtual void d23();    virtual void d24();    virtual void d25();    virtual void d26();    virtual void d27();    virtual void d28();
    virtual void clear();
    virtual void d30();    virtual void d31();    virtual void d32();    virtual void d33();    virtual void d34();    virtual void d35();    virtual void d36();    virtual void d37();    virtual void d38();    virtual void d39();
    virtual void setFlag(unsigned char);
    virtual void d41();    virtual void d42();
    virtual void setInfo(ShaderObject_1ca6c0 *);
    char pad0[32];
    ShaderPassList *passes;
};
struct ShaderStringObject : public igObject { char *text; int length; };
extern "C" int FUN_001cb340(ShaderProcessorView *self, ShaderTarget *target, int arg);
extern "C" igSmartPointer<igObject> FUN_001c8c80(ShaderProcessorView *self, int section, const char *key, void *meta, ShaderNameList *shared);

extern "C" IniStrRef FUN_001ccb20(igStringRefList *list);
extern "C" void igIniShaderFactory_ResetFileCache(int a0);
extern "C" void FUN_001ccd10(IniShaderFactoryView *self, IniNodeList *list);
struct IniShaderFactoryFields { char pad0[20]; int f20; char pad1[4]; int f28; };
struct IniFactoryEntry { char pad0[12]; IniSectionObject *f12; char *f16; };
extern "C" void igIniShaderFactory_PreloadFileCache(IniShaderFactoryFields *self);
extern "C" void igIniShaderFactory_UserPostLoad(igIniShaderFactory *self);
extern "C" void igIniShaderFactory_TrimCapacity(igIniShaderFactory *self);
extern "C" int FUN_001cd150(IniDocument **out, IniFactoryState *self, char *name);
extern "C" igSmartPointer<IniSectionText> FUN_001cdbb0(IniFactoryView *self, char *name);
struct IniHeldObject { int vt; int refs; };
struct IniFactoryBinding { char pad[44]; IniHeldObject *r44; IniHeldObject *r48; };
extern "C" bool igIniShaderFactory_ConfigureShader(IniFactoryBinding *self, int a1, IniHeldObject *a2, int a3);
extern "C" void igFolder_ListDirectories(void **arg0);
extern "C" int FUN_001ce400(IniStringObject **out, char *path);
extern "C" int FUN_001ce640(void *arg0, int arg1);
extern "C" void FUN_001ce660(int arg0);
extern "C" void igIntersectTraversal_userConstruct(beHitLandModelTraversal *arg0, int arg1);
extern "C" void igIntersectTraversal_userDestruct(igObject *self);
extern "C" void igNode_userDestruct(igObject *self);
extern "C" void Gap__Core__igObject__vfunc_36(igTransform *self, int target);
extern "C" void FUN_001ce710(void);
extern "C" void igIntersectTraversal_UserUnregister(void);
extern "C" void igIntersectTraversal_RegisterClassFunction(int arg0, int arg1);
extern "C" void igIntersectTraversal_resetFields(beHitLandModelTraversal *arg0, int flags);
extern "C" void Gap__Bec__beHitLandModelTraversal__vfunc_21(void *self, int arg1);
extern "C" void Gap__Bec__beHitLandModelTraversal__vfunc_22(void *self, int arg1);
extern "C" int FUN_001ceab0(HitTraversal *self, HitNode *node);
extern "C" void FUN_001cf950(int **arg0, int *arg1);
extern "C" int igIntersectTraversal_TraverseGroup(A_1cf990 *arg0, B_1cf990 *arg1);
extern "C" int igIntersectTraversal_TraverseTransform(ModelTraversal *self, TraversalNode *node);
extern "C" int igIntersectTraversal_TraverseGeometry(ModelTraversal *self, TraversalNode *node);
extern "C" igMetaObject *igTransform_GetMeta(void);
extern "C" int igGeometry_GetMeta(void);
extern "C" void FUN_001d0130(SceneTransformNode *self, SceneRenderer *renderer, SceneMatrix *parent, int context);
extern "C" int igLightSet_GetInherantFlags(void);
extern "C" void igLightSet_userConstruct(void **arg0, int arg1);
extern "C" void igLightSet_Reset(O_1d0330 *arg0);
extern "C" void igLightSet_Transform(S_1d03b0 *arg0, int arg1);
extern "C" void igLightStateSet_userConstruct(void **self, int flag);
extern "C" void igLightStateSet_Reset(igLightStateSetView *self);
extern "C" RangeRefObject *FUN_001d0520(RangeLookup *self, float t);
extern "C" void igLod_Reset(igLod *self);
extern "C" void igLod_UserPostLoad(void **arg0);
extern "C" void igLod_Transform(igLod *self, float *matrix);
extern "C" bool FUN_001d08d0(Self *arg0, int arg1);
extern "C" void FUN_001d1550(void *arg0, long long arg1);
extern "C" void FUN_001d15a0(KeyReducer *self);
extern "C" void FUN_001d1760(void *arg0, long long arg1);
extern "C" void FUN_001d17a0(KeyTrackOwner *self, igFloatListView *out, int last);
extern "C" void FUN_001d18a0(S_1d18a0 *arg0, int *arg1, int *arg2, float *arg3, K_1d18a0 *arg4, int arg5, unsigned arg6);
extern "C" void FUN_001d1a80(int a0, int a1, long long time);
extern "C" void FUN_001d1da0(MorphLevelState *self, float t);
extern "C" int FUN_001d2230(int a0, S_1d2230 *src, S_1d2230 *dst, O_1d2230 *obj, int flag);
extern "C" int igNode_GetParentCount(igNode *self);
extern "C" int igNode_GetParent(void *arg0, int arg1);
extern "C" int igNode_AddParent(igNode *self, int arg1);
extern "C" int igNode_RemoveParent(ObjectListOwner *self, igObject *object);
extern "C" void FUN_001d32f0(S_1d32f0 *arg0, int arg1);
extern "C" void igNode_userConstruct(void **arg0, int arg1);
extern "C" int igNode_GetInherantFlags(void);
extern "C" void igNode_InsertGroupAbove(NodeSlots *o, void *with);
extern "C" void igPlanarShadowShader_userConstruct(void **arg0, int arg1);
extern "C" int igPlanarShadowShader_GetMeta(void);
extern "C" void igPlanarShadowShader_userDestruct(T_1d39b0 *arg0);
extern "C" void Gap__Sg__igPlanarShadowShader__vfunc_39(igPlanarShadowShader *arg0, int geom, int arg2, int arg3);
extern "C" void FUN_001d3e20(igPlanarShadowShader *arg0, igCommonTraversal *arg1);
extern "C" void FUN_001d4180(void);
extern "C" void igProjectiveShadowShader_userConstruct(void **arg0, int arg1);
extern "C" igMetaObject *igProjectiveShadowShader_GetMeta(void);
extern "C" void FUN_001d5430(void);
extern "C" void igProjectiveShadowShader_userDestruct(void **arg0);
extern "C" int FUN_001d5a70(P *arg0, Q_1d5a70 *arg1);
extern "C" void FUN_001d5c40(A0_1d5c40 *arg0, A1_1d5c40 *arg1);
extern "C" void FUN_001d5e00(void *arg0, S1_1d5e00 *arg1);
extern "C" void FUN_001d5e60(struct A_1d5e60 *arg0, int arg1);
extern "C" void FUN_001d5ef0(struct S60 *arg0, int arg1);
extern "C" void FUN_001d5f70(A_1d5f70 *arg0, int arg1, int *arg2, int *arg3, int *arg4);
extern "C" void FUN_001d6060(O_1d6060 *arg0, char *arg1);
extern "C" void FUN_001d6190(struct S_1d6190 *arg0, char *arg1);
extern "C" void igProjectiveShadowShader_UserPostLoad(struct S_1d6240 *arg0);
extern "C" void igProjectiveShadowShader_Reset(igProjectiveShadowShader *self);
extern "C" int Gap__Bec__ParticleInfo__vfunc_22(ParticleInfo *self, int name);
extern "C" void FUN_001d6410(TraversedNode *collector, TraversedNode *node, void *path);
extern "C" void FUN_001d6790(OO_1d6790 *arg0, AA *arg1);
extern "C" int FUN_001d68e0(void);
extern "C" int FUN_001d68f0(void);
extern "C" int FUN_001d6900(Primitive **out);
extern "C" void FUN_001d6a70(void);
extern "C" void FUN_001d7120(ProjectiveShadowView *s);
extern "C" void FUN_001d7630(void *arg0, float *arg1);
extern "C" void FUN_001d7910(void);
extern "C" void FUN_001d7b10(void *arg0, void *arg1);
extern "C" void FUN_001d7b70(S0_1d7b70 *arg0, S1_1d7b70 *arg1);
extern "C" int getSgMaxLightStateCount(void);
extern "C" int FUN_001d8270(int arg0);
extern "C" int FUN_001d82c0(void *arg0, int arg1, int arg2);
extern "C" int FUN_001d82f0(void *arg0, int arg1);
extern "C" int FUN_001d8310(void *arg0, int arg1);
extern "C" int FUN_001d8330(void *arg0, unsigned int arg1);
extern "C" void igShaderData_AppendPass(igShaderData *self, int item, int arg2, int arg3);
extern "C" void igShaderData_RemoveAll(struct ShaderDataView *arg0);
extern "C" void FUN_001d86f0(struct S_1d86f0 *arg0, int arg1, igObject *arg2);
extern "C" void FUN_001d87b0(igTransformSequence *arg0, int arg1, igObject *arg2);
extern "C" void FUN_001d8870(struct A_1d8870 *arg0, int arg1, igObject *arg2);
extern "C" void igShaderData_UserPostLoad(igShaderData *self);
extern "C" int igShaderFactory_ConfigureShader(void *dummy, VA_1d8980 *arg1, void *, int);
extern "C" void igShaderFactory_GetInterfaceParameterString(void **arg0);
extern "C" void igShaderFactory_SetFileCachingMode(T_1d8a60 *arg0, int arg1);
extern "C" void igShaderFactory_ResetFileCache(void);
extern "C" void FUN_001d8b90(void);
extern "C" int igShaderInfo_FindObjectReference(ShaderFieldTable *self, int arg1, ShaderFieldRecord *key);
extern "C" int Gap__Sg__igShaderInfo__vfunc_24(struct S1d *arg0, int *arg1);
extern "C" int igShaderProcessor_Configure(void *arg0, void *arg1);
extern "C" void igShaderProcessor_Update(void);
extern "C" void FUN_001d9090(SkeletonBitOwnerView *o, int index, int value);
extern "C" void igSkeleton_Update(SkeletonView *o, SkeletonSlots *clock, int unused, SkeletonMatrix *local, SkeletonMatrix *global, SkeletonMatrix *out, SkeletonOverrideListView *overrides);
extern "C" int igSkeleton_GetBoneCount(igSkeleton *self);
extern "C" int igSkeleton_FindBoneIndex(S_1d9500 *arg0, int arg1);
extern "C" int igSkeleton_GetChild(O_1d95a0 *arg0, int arg1, int *arg2);
extern "C" int igSkeleton_GetSpecifiedChild(void **arg0, int arg1, int arg2);
extern "C" int igSkeleton_GetChildCount(VC_1d96d0 *arg0, int arg1);
extern "C" int FUN_001d9740(void *arg0, int arg1);
extern "C" void **igSmartPointer_igModelViewMatrixBoneSelect_Destruct(void **arg0, short arg1);
extern "C" void **FUN_001d9870(void **arg0, short arg1);
extern "C" void Gap__Bec__ParticleTimer__vfunc_35(ParticleTimer *arg0, RefCountedHeader *arg1);
extern "C" int FUN_001d9970(int *a, int *b);
extern "C" int FUN_001d99d0(int *arg0, int *arg1);
extern "C" int FUN_001d9a30(int *a, int *b);
extern "C" void FUN_001d9ac0(struct A_1d9ac0 *arg0, int arg1, int arg2);
extern "C" void FUN_001d9bb0(void *arg0, int arg1);
extern "C" void FUN_001da6e0(igSorter *arg0);
extern "C" void FUN_001da790(SorterOpaqueView *o);
extern "C" void igSorter_userConstruct(SorterState *o, int arg1);
extern "C" void FUN_001db500(A_1db500 *arg0);
extern "C" void Gap__Sg__igSorter__vfunc_24(Sorter *arg0);
extern "C" void FUN_001dc400(igSorter *arg0, igGroup *arg1, igAttrStackManager *arg2);
extern "C" void FUN_001dc500(A_1dc500 *arg0, unsigned char arg1, int arg2);
extern "C" void FUN_001d23a0(void *shader);
struct MultiPassShaderView;
extern "C" int FUN_001ba260(igCommonTraversal *self, MultiPassShaderView *shader);
/* Slot 23 of the capability manager answers a capability query. */
class CapabilityQueryView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4();
    virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
    virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14();
    virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual void d20();
    virtual int query(int capability);
};
extern "C" int igSwitch_InsertChild(S_1dc940 *arg0, int arg1, void *arg2);
extern "C" void FUN_001dcb80(ObjectPool *pool, igObject *object);
extern "C" int FUN_001dcc80(KeyTrackView *o, double t);
extern "C" int FUN_001dce70(struct S_1dce70 *arg0, double arg1);
extern "C" void igTransform_userConstruct(igTransform *self, int flag);
extern "C" int igTransform_IsTransformable(igTransform *arg0);
extern "C" int Gap__Sg__igTransformSource__vfunc_29(void);
extern "C" void igTransform_Transform(void *arg0, int arg1);
extern "C" void Gap__Sg__igTransformSource__vfunc_30(void);
extern "C" int igTransform_GetInherantFlags(void);
extern "C" void igTransform_Reset(igTransform *self);
extern "C" void Gap__Sg__igTransformSource__vfunc_33(void);
extern "C" void FUN_001dd0e0(TransformSampleView *o, int index, float (*m)[4]);
extern "C" void FUN_001dd250(A_1dd250 *arg0, int arg1, char *arg2);
extern "C" int FUN_001dd370(void *arg0);
extern "C" void FUN_001dd3e0(void *arg0, int arg1);
extern "C" void Gap__Sg__igTransformSequence1_5__vfunc_66(VC_1dd570 *arg0);
extern "C" int Gap__Sg__igTransformSequence1_5__vfunc_45(igTransformSequence1_5 *self, int index);
extern "C" void Gap__Sg__igTransformSequence1_5__vfunc_35(igTransformSequence1_5 *self, int index, float *matrix);
extern "C" void Gap__Sg__igTransformSequence1_5__vfunc_62(igTransformSequence1_5 *self, long long arg1);
extern "C" void Gap__Sg__igTransformSequence1_5__vfunc_34(KeySequenceView *o, int index, KeyMatrixView *m);
extern "C" void Gap__Sg__igTransformSequence1_5__vfunc_37(igTransformSequence1_5 *t, int idx);
extern "C" void FUN_001ddfd0(void);
extern "C" void Gap__Sg__igTransformSequence1_5__vfunc_57(TransformSequenceView *s, int channel, unsigned int mode);
extern "C" int Gap__Sg__igTransformSequence1_5__vfunc_59(igTransformSequence1_5 *arg0, int arg1);
extern "C" void Gap__Sg__igTransformSequence1_5__vfunc_58(TransformSequenceView *s, unsigned char channels);
extern "C" void Gap__Sg__igTransformSequence1_5__vfunc_61(T_1de9c0 *t, int idx, int ch, igVec3f *p, igVec3f *q);
extern "C" int Gap__Sg__igTransformSequence1_5__vfunc_48(igTransformSequence1_5 *self, int index);
extern "C" void igTransformSequence1_5_InterpolateTranslation(igTransformSequence1_5 *self, float *out, int from, int to, float t);
extern "C" void igTransformSequence1_5_InterpolateRotation(igTransformSequence1_5 *self, float *out, int from, int to, float t);
extern "C" void FUN_001930f0(float *out, float *p1, float *p2, float *p3, float *p4, float t);
extern "C" void igTransformSequence1_5_FindKeys(igTransformSequence1_5 *self, long long time, int *key0, int *key1, float *t, int *lastKey);
extern "C" void igTransformSequence1_5_UserPostLoad(igTransformSequence1_5 *self);
extern "C" void igTransformSequence1_5_FindUniformKeys(SequenceKeyTimes *arg0, long long arg1, int *arg2, int *arg3, float *arg4);
extern "C" long long Gap__Sg__igTransformSequence1_5__vfunc_31(O_1df6e0 *o);
extern "C" long long Gap__Sg__igTransformSequence1_5__vfunc_32(V_1df740 *arg0);
extern "C" void Gap__Sg__igTransformSequence1_5__vfunc_27(IgForwardTarget *o, int a, int b, int c);
extern "C" void Gap__Sg__igTransformSequence1_5__vfunc_25(IgForwardTarget_1dfd60 *o, int a, int b);
extern "C" bool Gap__Sg__igTransformSequence1_5__vfunc_29(igTransformSequence1_5 *o);
extern "C" void igTraversal_RegisterClass(int arg0);
extern "C" void igTraversal_RegisterClassFunction(int arg0, int arg1);
extern "C" void igTraversal_userConstruct(A_1e0380 *arg0, int arg1);
extern "C" void FUN_001e0410(void);
extern "C" void FUN_001e0470(void);
extern "C" int DAT_00562a40;
extern "C" long long DAT_00562a48;
extern "C" V_1e04c0 *DAT_00562a50;
/* The igTraversal virtuals around a node's traversal (vfunc_N sits at vtable offset 4N). */
class TraversalHooksView {
public:
    virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12();
    virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22();
    virtual void preTraverse(V_1e04c0 *node);    /* vfunc_23 */
    virtual void postTraverse(V_1e04c0 *node);   /* vfunc_24 */
};
extern "C" void Gap__Bec__beHitLandModelTraversal__vfunc_23(TraversalHooksView *self, V_1e04c0 *node);
extern "C" void Gap__Sg__igTraversal__vfunc_23(void *, int);
extern "C" void Gap__Sg__igTraversal__vfunc_24(void *, int);
extern "C" void thunk_FUN_001c1c50(void **self, int flag);
extern "C" void igPsx2EnvironmentMapShader_userDestruct(void **arg0);
extern "C" int igPsx2EnvironmentMapShader_GetMeta(void);
extern "C" void Gap__Sg__igPsx2EnvironmentMapShader__vfunc_49(void);
extern "C" void Gap__Sg__igPsx2EnvironmentMapShader__vfunc_50(int arg0);
extern "C" void Gap__Sg__igPsx2EnvironmentMapShader__vfunc_51(S_1e1210 *self);
extern "C" void Gap__Sg__igPsx2EnvironmentMapShader__vfunc_52(S_1e1400 *arg0);
extern "C" void Gap__Sg__igPsx2EnvironmentMapShader__vfunc_45(igPsx2EnvironmentMapShader *arg0, EnvMapSource *arg1);
extern "C" void Gap__Sg__igPsx2EnvironmentMapShader__vfunc_48(S_1e1580 *self, A1_1e1580 *arg1);
extern "C" void FUN_001e16a0(EnvMapShaderView *arg0, void *);
extern "C" void FUN_001e1ac0(S_1e1ac0 *arg0, void *);
extern "C" void FUN_001e1e70(EnvMapShaderView_1e1e70 *arg0, void *);
extern "C" void FUN_001e22c0(EnvMapShaderView_1e22c0 *arg0, void *);
extern "C" void Gap__Sg__igPsx2EnvironmentMapShader__vfunc_46(void);
extern "C" int FUN_001e2810(void);
extern "C" void igPsx2EnvironmentMapShader_Reset(igPsx2EnvironmentMapShader *self);
extern "C" int igPsx2EnvironmentMapShader_IsTransformable(void);
extern "C" int igGroup_HasChildren(igGroup *self);
extern "C" int igGroup_IsChildrenOrdered(void);
extern "C" void igNode_SetFlags(int a0, int a1);
extern "C" int igTraversal_GetMeta(void);
extern "C" void Gap__Bec__beHitLandModelTraversal__vfunc_25(beHitLandModelTraversal *arg0, long long arg1);
extern "C" igMetaObject *igTransformSequence1_5_GetMeta(void);
extern "C" void Gap__Sg__igTransformSequence1_5__vfunc_53(IgForwardTarget_1e28b0 *o);
extern "C" void Gap__Sg__igTransformSequence1_5__vfunc_54(IgForwardTarget_1e28c0 *o);
extern "C" void Gap__Sg__igTransformSequence1_5__vfunc_36(TransformSequenceChannelView *o, int index);
extern "C" void Gap__Sg__igTransformSequence1_5__vfunc_38(struct T_1e2970 *t, int n);
extern "C" void Gap__Sg__igTransformSequence1_5__vfunc_55(igTransformSequence1_5 *arg0, int arg1, long long arg2);
extern "C" void Gap__Sg__igTransformSequence1_5__vfunc_40(igTransformSequence1_5 *self, int index, float *translation);
extern "C" void Gap__Sg__igTransformSequence1_5__vfunc_44(igTransformSequence1_5 *self, int index, void *quaternion);
extern "C" void Gap__Sg__igTransformSequence1_5__vfunc_47(igTransformSequence1_5 *arg0, int arg1, void *arg2);
extern "C" void Gap__Sg__igTransformSequence1_5__vfunc_49(igTransformSequence1_5 *self, int index, void *scale);
extern "C" long long Gap__Sg__igTransformSequence1_5__vfunc_63(igTransformSequence1_5 *self);
extern "C" void Gap__Sg__igTransformSequence1_5__vfunc_64(igTransformSequence1_5 *self, long long arg1);
extern "C" void FUN_001e2cd0(IgForwardTarget_1e2cd0 *o);
extern "C" void FUN_001e2ce0(igTransformSequence1_5 *self, char enabled);
extern "C" void FUN_001e2cf0(void *arg0);
extern "C" igMetaObject *FUN_001e2d00(void);
extern "C" int FUN_001e2d10(void **arg0, int arg1);
extern "C" void FUN_001e2d60(IgForwardTarget_1e2d60 *o);
extern "C" void FUN_001e2d70(IgForwardTarget_1e2d70 *o);
extern "C" void igTransform_SetMatrix(igTransform *self, const float *matrix);
extern "C" void igNode_Reset(void);
extern "C" int igShaderProcessor_ConfigureRequired(void);
extern "C" int igSwitch_GetMeta(void);
extern "C" int igSwitch_IsChildrenOrdered(void);
extern "C" int igSorter_GetMeta(void);
extern "C" igMetaObject *igSkeleton_GetMeta(void);
extern "C" int igSkeleton_GetJointCount(igSkeleton *self);
extern "C" int *igSkeleton_GetBoneName(igSkeleton *self, int arg1);
extern "C" int igSkeleton_GetParent(igSkeleton *self, int arg1);
extern "C" igMetaObject *igShaderInfo_GetMeta(void);
extern "C" igMetaObject *igShaderFactory_GetMeta(void);
extern "C" void igShaderFactory_PreloadFileCache(void);
extern "C" igMetaObject *igShaderData_GetMeta(void);
extern "C" igMetaObject *igSceneInfo_GetMeta(void);
extern "C" void igPlanarShadowShader_Reset(Shader *arg0);
extern "C" void Gap__Bec__ParticleTimer__vfunc_36(ParticleTimer *a0, int a1);
extern "C" int igGeometry_IsChildrenOrdered(void);
extern "C" int igNode_HasChildren(void);
extern "C" igMetaObject *igLod_GetMeta(void);
extern "C" int igLod_IsChildrenOrdered(void);
extern "C" int Gap__Sg__igLod__vfunc_37(igLod *arg0);
extern "C" int igLightStateSet_GetMeta(void);
extern "C" int igLightSet_GetMeta(void);
extern "C" igMetaObject *igIntersectTraversal_GetMeta(void);
extern "C" igMetaObject *igIniShaderFactory_GetMeta(void);
extern "C" igMetaObject *igGroup_GetMeta(void);
extern "C" int igFrustCullTraversal_GetMeta(void);
extern "C" void Gap__Sg__igCommonTraversal__vfunc_29(S0_1e31f0 *arg0, S1_1e31f0 *arg1);
extern "C" void Gap__Sg__igCommonTraversal__vfunc_27(igCommonTraversal *self, long long arg1);
extern "C" igMetaObject *igEnbayaTransformSource_GetMeta(void);
extern "C" igMetaObject *igEnbayaContextPool_GetMeta(void);
extern "C" igMetaObject *igEnbayaAnimationState_GetMeta(void);
extern "C" igMetaObject *igEnbayaAnimationSource_GetMeta(void);
extern "C" unsigned char Gap__Sg__igCompressedAnimationSequenceQS__vfunc_34(igCompressedAnimationSequenceQS *self);
extern "C" void Gap__Sg__igCompressedAnimationSequenceQS__vfunc_37(struct S_1e3300 *arg0);
extern "C" int Gap__Sg__igCompressedAnimationSequenceQS__vfunc_38(void);
extern "C" int Gap__Sg__igCompressedAnimationSequenceQS__vfunc_39(void);
extern "C" void Gap__Sg__igCompressedAnimationSequenceQS__vfunc_40(void);
extern "C" int Gap__Sg__igCompressedAnimationSequenceQS__vfunc_41(void);
extern "C" long long Gap__Sg__igCompressedAnimationSequenceQS__vfunc_43(igCompressedAnimationSequenceQS *self);
extern "C" void Gap__Sg__igCompressedAnimationSequenceQS__vfunc_45(igCompressedAnimationSequenceQS *self, long long animationDuration);
extern "C" int igCompressedAnimationSequenceQS_evaluateRotation(void **arg0, int arg1);
extern "C" igMetaObject *igCompressedAnimationSequenceQS_GetMeta(void);
extern "C" int igCompileTraversal_GetMeta(void);
extern "C" igMetaObject *igCommonTraversal_GetMeta(void);
extern "C" int igCamera_IsTransformable(void);
extern "C" igMetaObject *igAttrStackManager_GetMeta(void);
extern "C" igMetaObject *igAttrSet_GetMeta(void);
extern "C" int igAnimationState_GetMeta(void);
extern "C" igMetaObject *igAnimationDatabase_GetMeta(void);
extern "C" igMetaObject *igAnimationCombiner_GetMeta(void);
extern "C" unsigned char igAnimationCombiner_GetHierarchyUpdated(igAnimationCombiner *self);
extern "C" int igAnimationCombiner_GetBoneMatrixArray(igAnimationCombiner *self);
extern "C" int igAnimationCombiner_GetBoneMatrix(igAnimationCombiner *self, int arg1);
extern "C" int igAnimationCombiner_GetBlendMatrixArray(igAnimationCombiner *self);
extern "C" int igAnimationCombiner_GetBlendMatrix(igAnimationCombiner *self, int arg1);
extern "C" int igActor_GetMeta(void);
extern "C" int igActor_IsTransformable(void);
extern "C" int igActorList_GetMeta(void);
extern "C" igMetaObject *igActorInfo_GetMeta(void);
extern "C" igMetaObject *igAnimationTrack_GetMeta(void);
extern "C" igMetaObject *igAnimationTrackList_GetMeta(void);
extern "C" igMetaObject *igAnimationTransitionParams_GetMeta(void);
extern "C" igMetaObject *igAnimationTransitionPoint_GetMeta(void);
extern "C" igMetaObject *igAnimationTransitionPointList_GetMeta(void);
extern "C" igMetaObject *igAnimationTransitionDefinition_GetMeta(void);
extern "C" igMetaObject *igAnimationTransitionDefinitionList_GetMeta(void);
extern "C" igMetaObject *igAnimationList_GetMeta(void);
extern "C" igMetaObject *igAnimationBinding_GetMeta(void);
extern "C" igMetaObject *igAnimationBindingList_GetMeta(void);
extern "C" int FUN_001e35e0(void);
extern "C" int FUN_001e35f0(igAnimationBindingList *self);
extern "C" int igAnimationCombinerList_GetMeta(void);
extern "C" igMetaObject *igAnimationCombinerBoneInfo_GetMeta(void);
extern "C" igMetaObject *igAnimationCombinerBoneInfoList_GetMeta(void);
extern "C" igMetaObject *igAnimationCombinerBoneInfoListList_GetMeta(void);
extern "C" igMetaObject *igAnimationCombinerBoneInfoPool_GetMeta(void);
extern "C" igMetaObject *igObjectPool_GetMeta(void);
extern "C" igMetaObject *igAnimationModifier_GetMeta(void);
extern "C" igMetaObject *igAnimationModifierList_GetMeta(void);
extern "C" igMetaObject *igAnimationStateList_GetMeta(void);
extern "C" igMetaObject *igAnimationStatePool_GetMeta(void);
extern "C" igMetaObject *igAppearance_GetMeta(void);
extern "C" igMetaObject *igAppearanceList_GetMeta(void);
extern "C" igMetaObject *igAttrStack_GetMeta(void);
extern "C" igMetaObject *igAttrStackList_GetMeta(void);
extern "C" igMetaObject *igNonRefCountedAttrStackManagerList_GetMeta(void);
extern "C" igMetaObject *igBillboard_GetMeta(void);
extern "C" int igBillboard_IsTransformable(void);
extern "C" int igBitMask_GetMeta(void);
extern "C" int igUnsignedIntList_GetMeta(void);
extern "C" igMetaObject *igBlendMatrixSelect_GetMeta(void);
extern "C" int igBoundingBoxesMaker_GetMeta(void);
extern "C" igMetaObject *igCamera_GetMeta(void);
extern "C" void igCamera_Activate(void);
extern "C" void igCamera_Deactivate(void);
extern "C" int igCompiledTransform_GetMeta(void);
extern "C" igMetaObject *igCompiledTransformList_GetMeta(void);
extern "C" igMetaObject *igBlendListRecord_GetMeta(void);
extern "C" igMetaObject *igCompressedTransformSequence1_5Data_GetMeta(void);
extern "C" igMetaObject *igEnvironmentMapShader2List_GetMeta(void);
extern "C" igMetaObject *igGeometryList_GetMeta(void);
extern "C" igMetaObject *igGraphPath_GetMeta(void);
extern "C" igMetaObject *igGraphPathList_GetMeta(void);
extern "C" igMetaObject *igInterpretedShaderData_GetMeta(void);
extern "C" igMetaObject *igProbe_GetMeta(void);
extern "C" igMetaObject *igAnimation_GetMeta(void);
extern "C" int igModelViewMatrixBoneSelect_GetMeta(void);
extern "C" igMetaObject *igModelViewMatrixBoneSelectListSg_GetPublishedMetaObject(void);
extern "C" igMetaObject *igNodeList_GetMeta(void);
extern "C" igMetaObject *igNodeListList_GetMeta(void);
extern "C" igMetaObject *igNonRefCountedNodeList_GetMeta(void);
extern "C" igMetaObject *igOverrideAttrSet_GetMeta(void);
extern "C" int igSegment_GetMeta(void);
extern "C" int igSegment_IsTransformable(void);
extern "C" int igTraversalFunctionList_GetMeta(void);
extern "C" igMetaObject *igLightStateAttrPool_GetMeta(void);
extern "C" igMetaObject *igModelViewMatrixAttrPool_GetMeta(void);
extern "C" igMetaObject *igTimeAttrPool_GetMeta(void);
extern "C" igMetaObject *igProjectionMatrixAttrPool_GetMeta(void);
extern "C" igMetaObject *igVertexBlendMatrixAttrPool_GetMeta(void);
extern "C" igMetaObject *igVertexBlendMatrixListAttrPool_GetMeta(void);
extern "C" igMetaObject *igMatrixObjectPool_GetMeta(void);
extern "C" igMetaObject *igTextureMatrixAttrPool_GetMeta(void);
extern "C" igMetaObject *igBlendMatricesAttrPool_GetMeta(void);
extern "C" igMetaObject *igShaderFactoryList_GetMeta(void);
extern "C" igMetaObject *igSkeletonBoneInfo_GetMeta(void);
extern "C" igMetaObject *igSkeletonBoneInfoList_GetMeta(void);
extern "C" igMetaObject *igSkeletonList_GetMeta(void);
extern "C" igMetaObject *igSkin_GetMeta(void);
extern "C" igMetaObject *igSkinList_GetMeta(void);
extern "C" igMetaObject *igRenderPackage_GetMeta(void);
extern "C" igMetaObject *igRenderPackagePool_GetMeta(void);
extern "C" igMetaObject *igRenderPackageList_GetMeta(void);
extern "C" int igDoubleList_GetMeta(void);
extern "C" igMetaObject *igTransformStack_GetMeta(void);
extern "C" igMetaObject *igTransformList_GetMeta(void);
extern "C" igMetaObject *igNonRefCountedTransformList_GetMeta(void);
extern "C" igMetaObject *igTransformRecorder_GetMeta(void);
extern "C" int igTransientShaderData_GetMeta(void);
extern "C" igMetaObject *igRenderPackageList_GetElementMeta(void);
extern "C" igMetaObject *igNonRefCountedAttrStackManagerList_GetElementMeta(void);
extern "C" igMetaObject *igNonRefCountedTransformList_GetElementMeta(void);
extern "C" igMetaObject *igNonRefCountedNodeList_GetElementMeta(void);
extern "C" int igTraversalFunctionList_GetElementSize(igTraversalFunctionList *self);
extern "C" int igDoubleList_GetElementSize(void);
extern "C" int igUnsignedIntList_GetElementSize(void);
extern "C" int FUN_001e3ab0(igIntList *list, int *value);
extern "C" int igActorList_GetElementMeta(void);
extern "C" igMetaObject *igAnimationCombinerList_GetElementMeta(void);
extern "C" igMetaObject *igAppearanceList_GetElementMeta(void);
extern "C" igMetaObject *igAnimationStateList_GetElementMeta(void);
extern "C" igMetaObject *igAnimationCombinerBoneInfoListList_GetElementMeta(void);
extern "C" igMetaObject *igAnimationCombinerBoneInfoList_GetElementMeta(void);
extern "C" igMetaObject *igEnvironmentMapShader2List_GetElementMeta(void);
extern "C" igMetaObject *igGraphPathList_GetElementMeta(void);
extern "C" igMetaObject *igAnimationList_GetElementMeta(void);
extern "C" igMetaObject *igAnimationTransitionDefinitionList_GetElementMeta(void);
extern "C" igMetaObject *igAnimationTransitionPointList_GetElementMeta(void);
extern "C" igMetaObject *igAnimationTrackList_GetElementMeta(void);
extern "C" igMetaObject *igAnimationBindingList_GetElementMeta(void);
extern "C" int Gap__Bec__igModelViewMatrixBoneSelectList__vfunc_22(void);
extern "C" igMetaObject *igShaderFactoryList_GetElementMeta(void);
extern "C" igMetaObject *igSkeletonList_GetElementMeta(void);
extern "C" igMetaObject *igSkeletonBoneInfoList_GetElementMeta(void);
extern "C" igMetaObject *igAnimationModifierList_GetElementMeta(void);
extern "C" igMetaObject *igSkinList_GetElementMeta(void);
extern "C" int igCompiledTransformList_GetElementMeta(void);
extern "C" igMetaObject *igGeometryList_GetElementMeta(void);
extern "C" igMetaObject *igAttrStackList_GetElementMeta(void);
extern "C" igMetaObject *igTransformList_GetElementMeta(void);
extern "C" igMetaObject *igNodeListList_GetElementMeta(void);
extern "C" igMetaObject *igNodeList_GetElementMeta(void);
extern "C" void igUnsignedIntList_TrimCapacity(igUnsignedIntList *self);
extern "C" void igDoubleList_TrimCapacity(igDataList *arg0);
extern "C" void igTraversalFunctionList_TrimCapacity(igTraversalFunctionList *self);
extern "C" int igCommonTraversal_TraverseActor(void *arg0, ForwardTarget *arg1);
extern "C" int igCommonTraversal_TraverseProjectiveShadowShader(char *arg0, struct S_1d6190 *arg1);
extern "C" int FUN_001ba850(A1_1c03a0 *arg0, DepthOfFieldNode *arg1);
extern "C" int igFrustCullTraversal_TraversePlanarShadowShader(void *arg0, TraversalNodeView *arg1);
extern "C" int igIntersectTraversal_TraverseNode(void);
extern "C" int igTraversal_TraverseLeaf(void);
static int FUN_001c0ae0(float *arg0, float fparg0, float fparg1);
static inline void insertRetained(Ls *list, int index, It *object) {
    Retained retained(object);
    List_InsertWords((igDataList *)list, index, 1, &retained.p);
}
static inline void releaseWord(igPoolObject *o) {
    if (o != 0) {
        o->_refCount = o->_refCount - 1;
        if (((unsigned long long)((long long)(int)o->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy((igObject *)o);
        }
    }
}
static inline void clearBoneInfo(CombinerBoneInfo *b) {
    FUN_001ae250((void * *)&b->_animationState, 0);
    FUN_001ae1d0((void * *)&b->_transformSource, 0);
    FUN_001ae1b0(b->_q, 0.0f, 0.0f, 0.0f, 0.0f);
    Vec3f_Set((igVec3f *)b->_t, 0.0f, 0.0f, 0.0f);
    b->_priority = 0;
    b->_useTranslation = 0;
    b->_lastKeyframe = 1;
    b->_reflect = -1;
}
static inline igPoolObject *poolTake(CombinerPool *pool, void *ctor) {
    int i;
    if (pool->_used >= pool->_capacity) {
        igObjectPool_Grow((igObjectPool *)pool, (igObject *(*)(int))ctor);
    }
    i = pool->_used;
    pool->_used = i + 1;
    return pool->_data[i];
}
static inline int useTranslation(CombinerAnimation *a, unsigned int i) {
    CombinerBitMask *m = a->_useTrans;
    if (m != 0) {
        return ((1 << (i & 31)) & m->_data[i >> 5]) != 0;
    }
    return 0;
}
static inline void retain(igPoolObject *o) {
    if (o != 0) {
        o->_refCount = o->_refCount + 1;
    }
}
static inline void setState(CombinerBoneInfo *b, igPoolObject *s) {
    retain(s);
    releaseWord((igPoolObject *)b->_animationState);
    b->_animationState = (igAnimationState *)s;
}
static inline void setBase(CombinerStateView *c, int bone, int value) {
    CombinerIntList *s = c->_boneInfoListBase;
    int n = s->_count;
    if (n != 0 && bone >= 0 && bone < n) {
        s->_data[bone] = value;
    }
    c->_cacheValid = 0;
}
static inline AnimDbRecord *castToNamed(AnimDbRecord *object) {
    if (object != 0 && ((Gap::Core::igObject *)object)->isOfType(Gap::Core::igNamedObject::getClassMeta()) != 0) {
        return object;
    }
    return 0;
}
static inline const char *nameOf(AnimDbRecord *object) {
    const char *name = object->name;
    if (name != 0) {
        return name;
    }
    return ((char *)emptyString);
}
#define CAST_INLINE(NAME, META) static inline AnimDbObject *NAME(AnimDbObject *o) { if (o != 0 && ((Gap::Core::igObject *)o)->isOfType(META) != 0) { return o; } return 0; }
CAST_INLINE(castSkeleton, ((igMetaObject *)g_igTransformSource_metaObject))
CAST_INLINE(castField, ((igMetaObject *)g_igObjectRefMetaField_metaObject))
CAST_INLINE(castBoolList, ((igMetaObject *)g_igAnimationTrackList_metaObject))
static inline const char *nameOf(int name) {
    const char *n = (const char *)name;
    if (n != 0) {
        return n;
    }
    return ((char *)emptyString);
}
#undef CAST_INLINE
static inline int overrideName(igAppearanceView *a, int i) {
    int s = a->_segmentOverrideNameList->_data[i]->_string;
    s = s == 0 ? ((int)g_stringObjEmptyText) : s;
    return s;
}
static inline int n_of(const struct L_1af920 *list) { return list->n; }
static inline void attrRelease(igObject *o) {
    if (o != 0) {
        o->_refCount = o->_refCount - 1;
        if ((o->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(o);
        }
    }
}
static inline void attrRetain(igObject *o) {
    if (o != 0) {
        o->_refCount = o->_refCount + 1;
    }
}
static inline void attrListSet(AttrList *l, int i, igObject *o) {
    attrRetain(o);
    attrRelease(l->_data[i]);
    {
        int n = l->_count;
        if (n != 0 && i >= 0 && i < n) {
            l->_data[i] = o;
        }
    }
}
static inline void attrFieldSet(AttrObj **slot, AttrObj *v) {
    attrRetain(v);
    attrRelease(*slot);
    *slot = v;
}
static inline int n_of_1b1490(const struct L_1b1490 *list) { return list->n; }
inline void igBitMaskWords::setCount(int n) {
    if (n >= 0) {
        if (!(n > _capacity)) {
            _count = n;
        } else {
            ((Gap::Core::igDataList *)this)->resizeAndSetCount(n, 4);
        }
    }
}
inline void igBitMaskWords::setWord(int i, const unsigned int &v) {
    int n = _count;
    if (n != 0 && i >= 0 && i < n) {
        _data[i] = v;
    }
}
static inline void clearRetained(TravObjectList *l) {
    int n = l->_count;
    int i;
    for (i = 0; i < n; i++) {
        TravObject *o = l->_data[i];
        if (o != 0) {
            o->_refCount = o->_refCount - 1;
            if (((unsigned long long)((long long)(int)o->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)o);
            }
        }
    }
    {
        int total = l->_count;
        for (i = 0; i < total; i++) {
            l->_data[i] = 0;
        }
    }
    l->_count = 0;
}
static inline void retain_1b7010(R_1b7010 *object) {
    if (object != 0) {
        object->_refCount = object->_refCount + 1;
    }
}
static inline void release(R_1b7010 *object) {
    if (object != 0) {
        object->_refCount = object->_refCount - 1;
        if ((object->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(object);
        }
    }
}
static inline void pushAttr(AttrManagerView *m, igMetaObject *meta, int attr) {
    m->_attrStacks->_data[m->_firstUnit[meta->_id]]->_ops->push(attr);
}
static inline int size_of(const struct L_1b75b0 *list) { return list->size; }
static inline void removeRetained(SegmentStackList *list, int i) {
    igObject *o = list->_data[i];
    if (o != 0) {
        o->_refCount = o->_refCount - 1;
        if (((unsigned long long)((long long)(int)o->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy((igObject *)o);
        }
    }
    List_RemoveWordAt((igDataList *)list, i);
    list->_data[list->_count] = 0;
}
static inline ActorMatrixEntry *entryAt(ActorMatrixStack *s, int i) { return s->_data[i]; }
static inline ActorMatrixEntry *lastEntry(ActorMatrixStack *s) {
    int n = s->_count;
    if (n == 0) return 0;
    return entryAt(s, n - 1);
}
static inline float *bonesOf(ActorView *o) {
    if (o->_useCached) return o->_bones;
    return o->_animationState->bones();
}
static inline float *blendsOf(ActorView *o) {
    if (o->_useCached) return o->_blends;
    return o->_animationState->blends();
}
static inline TransformAttrView *attrAt(TransformStackView *s, int i) { return s->_data[i]; }
static inline TransformAttrView *topOf(TransformStackView *s) {
    if (s->_base >= 0) {
        return attrAt(s, s->_base);
    }
    if (s->_count != 0) {
        return attrAt(s, s->_count - 1);
    }
    return s->_default;
}
static inline TransformStackView *stackOf(TransformStateView *st) {
    return st->_stacks->_data[st->_slotOfIndex[((AttrClassView *)Gap::Attrs::igModelViewMatrixAttr::getClassMeta())->_stackIndex]];
}
static inline CullMatrixEntry *entryAt_1b9d90(CullMatrixStack *s, int i) { return s->_data[i]; }
static inline CullMatrixEntry *currentEntry(CullMatrixStack *s) {
    int cur = s->_current;
    int n;
    if (cur >= 0) return entryAt_1b9d90(s, cur);
    n = s->_count;
    if (n != 0) return entryAt_1b9d90(s, n - 1);
    return s->_default;
}
static inline CullMatrixStack *stackOf_1b9d90(CullAttrState *st, CullMeta *meta) {
    return st->_stacks->_data[st->_slotOfIndex[meta->_index]];
}
static inline CullMatrixEntry *entryAt_1ba080(CullMatrixStack *s, int i) { return s->_data[i]; }
static inline CullMatrixEntry *currentEntry_1ba080(CullMatrixStack *s) {
    int cur = s->_current;
    int n;
    if (cur >= 0) return entryAt_1ba080(s, cur);
    n = s->_count;
    if (n != 0) return entryAt_1ba080(s, n - 1);
    return s->_default;
}
static inline char *paletteAt(MatrixArrayList *l, int i) { return l->_data[i]; }
static inline void clearEntries(RefCountedEntryList *l) {
    int n;
    int m;
    int i;
    int j;
    n = l->cnt;
    for (i = 0; i < n; i++) {
        RefCountedEntry *o = l->data[i];
        if (o) {
            o->ref = o->ref - 1;
            if (((unsigned long long)((long long)o->ref << 0x29) >> 0x29) == 0) igObject_Destroy((igObject *)o);
        }
    }
    m = l->cnt;
    for (j = 0; j < m; j++) l->data[j] = 0;
    l->cnt = 0;
}
static inline int n_of_1bd170(const struct Arr_1bd170 *list) { return list->n; }
template <class T> static inline void releaseRefCounted(T *p) {
    p->_refCount = (int)p->_refCount - 1;
    if (((unsigned long long)((long long)(int)p->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy((igObject *)p);
    }
}
template <class T> static inline void retainRefCounted(T *p) {
    if (p != 0) {
        p->_refCount = p->_refCount + 1;
    }
}
static inline void setTarget(RemapEntry *e, void *t) {
    unsigned int *old;
    retainRefCounted((RemapObject *)t);
    old = (unsigned int *)e->_target;
    if (old != 0) {
        releaseRefCounted((RemapObject *)old);
    }
    e->_target = t;
}
static inline void setAt(RemapObjectList *l, int i, RemapObject *v) {
    if (l->_count != 0 && i >= 0 && i < l->_count) {
        l->_data[i] = v;
    }
}
static inline void setCount_1bd890(RemapTable *t, unsigned int n) {
    if (t->_capacity < n) {
        if (t->_storage != 0) {
            ((Gap::Core::igObject *)t)->free(t->_storage);
        }
        if (t->_data != 0) {
            ((Gap::Core::igObject *)t)->free(t->_data);
        }
        t->_data = ((int *)((Gap::Core::igObject *)t)->malloc(n * 4));
        t->_capacity = n;
    }
    t->_count = n;
}
static inline int findIndex(EnbayaIntList *l0, int n0, int boneCount, int &i) {
    for (i = 0; i < n0; i++) {
        if (boneCount == l0->_data[i]) return i;
    }
    i = -1;
    return -1;
}
static inline void release_1c20b0(Obj_1c20b0 *o) {
  if (o != 0) {
    o->_refCount = o->_refCount - 1;
    if ((o->_refCount & 0x7FFFFF) == 0) igObject_Destroy(o);
  }
}
static inline void assign(Obj_1c20b0 *&field, Obj_1c20b0 *value) {
  if (value) value->_refCount = value->_refCount + 1;
  release_1c20b0(field);
  field = value;
}
static inline CullMatrixEntry *entryAt_1c4ac0(CullMatrixStack *s, int i) { return s->_data[i]; }
static inline CullMatrixEntry *currentEntry_1c4ac0(CullMatrixStack *s) {
    int cur = s->_current;
    int n;
    if (cur >= 0) return entryAt_1c4ac0(s, cur);
    n = s->_count;
    if (n != 0) return entryAt_1c4ac0(s, n - 1);
    return s->_default;
}
static inline CullMatrixStack *stackOf_1c4ac0(CullAttrState *st, CullMeta *meta) {
    return st->_stacks->_data[st->_slotOfIndex[meta->_index]];
}
static inline char *internText(const char *text) {
    int pool;
    if (text == 0) return 0;
    if (g_stringPool == 0) {
        pool = (int)StringPool_Allocate(16);
        if (pool != 0) {
            pool = (int)StringPool_Construct((StringPool *)pool);
        }
        g_stringPool = (StringPool *)pool;
    }
    return ((char *)StringPool_Intern(g_stringPool, text));
}
static inline int f8_of(const L_1c58c0 *list) { return list->f8; }
static inline char *releaseText(char *s) {
    if (s != 0) {
        int *header = (int *)s - 2;
        int count = ((int *)s)[-1] - 1;
        ((int *)s)[-1] = count;
        if (count == 0) {
            StringChunk_ReleaseHeader((StringChunk *)*header, (StringTokenHeader *)header);
        }
    }
    return 0;
}
static inline void releaseString(char *s) {
    if (s != 0) {
        int *h = (int *)s - 2;
        int c = ((int *)s)[-1] - 1;
        ((int *)s)[-1] = c;
        if (c == 0) {
            StringChunk_ReleaseHeader((StringChunk *)*h, (StringTokenHeader *)h);
        }
    }
}
static inline int n_of_1ce970(const MatrixStackList *list) { return list->n; }
static inline HitMatrix *topMatrix(HitTraversal *self) {
    HitMatrixStack *s = self->matrices;
    return &s->data[s->count - 1];
}
static inline int passStop(int r) {
    if (r == 2) {
        return 2;
    }
    return 0;
}
static inline TraversalMatrix popMatrix(MatrixStack *s) {
    s->count = s->count - 1;
    return s->data[s->count];
}
static inline void dropCurrent(RangeLookup *self) {
    RangeRefObject *o = self->current;
    if (o != 0) {
        o->_refCount = o->_refCount - 1;
        if (((unsigned long long)((long long)(int)o->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy((igObject *)o);
        }
    }
}
static inline void setFloats(igFloatList *&field, const igSmartPointer<igFloatList> &value) {
    igFloatList *held = value.p;
    igFloatList *old;
    if (held) held->_refCount = held->_refCount + 1;
    old = field;
    if (old) {
        old->_refCount = old->_refCount - 1;
        if ((old->_refCount & 0x7FFFFF) == 0) igObject_Destroy(old);
    }
    field = held;
}
static inline void setBytes(igUnsignedCharList *&field, const igSmartPointer<igUnsignedCharList> &value) {
    igUnsignedCharList *held = value.p;
    igUnsignedCharList *old;
    if (held) held->_refCount = held->_refCount + 1;
    old = field;
    if (old) {
        old->_refCount = old->_refCount - 1;
        if ((old->_refCount & 0x7FFFFF) == 0) igObject_Destroy(old);
    }
    field = held;
}
static inline void appendIndex(KeyIndexList *l, int v) {
    int n = l->count;
    if (l->capacity > n) {
        l->count = l->count + 1;
    } else {
        ((Gap::Core::igDataList *)l)->resizeAndSetCount(n + 1, 4);
    }
    l->data[n] = v;
}
static inline void setValue(igFloatListView *l, int i, const float *v) {
    int n = l->count;
    if (n != 0 && i >= 0 && i < n) {
        l->data[i] = *v;
    }
}
static inline int count_of(const struct L1d *list) { return list->count; }
static inline int findParent(NodeParentListView *l, int *x) {
    int n = l->_count;
    for (int i = 0; i < n; i++) {
        if (x[0] == (int)l->_data[i]) { return i; }
    }
    return -1;
}
static inline void retain_1d3410(int *slot) {
    NodeSlots *x = (NodeSlots *)*slot;
    if (x != 0) { x->_refCount = x->_refCount + 1; }
}
static inline void release_1d3410(int *slot) {
    if (*slot != 0) {
        ((NodeSlots *)*slot)->_refCount = ((NodeSlots *)*slot)->_refCount - 1;
        if ((((NodeSlots *)*slot)->_refCount & 0x7fffff) == 0) { igObject_Destroy((igObject *)*slot); }
    }
}
static inline void clearBytes(char *p, unsigned int n) {
    if (p != 0) {
        do {
            *p = 0;
            n--;
            p++;
        } while (n != 0);
    }
}
static inline void setBit(SkeletonBitListView *l, int i) {
    unsigned int mask = 1 << (i & 31);
    int w = (unsigned int)i >> 5;
    unsigned int *p = &l->_data[w];
    int c = l->_count;
    unsigned int v = mask | *p;
    if (c != 0 && w >= 0 && c > w) { *p = v; }
}
static inline void clearBit(SkeletonBitListView *l, int i) {
    unsigned int mask = ~(1 << (i & 31));
    int w = (unsigned int)i >> 5;
    unsigned int *p = &l->_data[w];
    int c = l->_count;
    unsigned int v = mask & *p;
    if (c != 0 && w >= 0 && c > w) { *p = v; }
}
static inline int count_of_1da6e0(const igDataList *list) { return list->_count; }
static inline int a_of(const struct Pair *pair) { return pair->a; }
static inline void setRef(SorterList *l, int i, const int &v) {
    if (l->count != 0 && i >= 0 && i < l->count) { l->items[i] = v; }
}
static inline int count_of_1db500(const L_1db500 *list) { return list->count; }
static inline int cnt_of(const struct L_1dc400 *list) { return list->cnt; }
static inline int count_of_1dca40(const List_1dca40 *list) { return list->count; }
static inline void releaseRef_1de040(SeqData *old) {
    if (old) {
        --old->refCount;
        if (((unsigned long long)(long long)old->refCount & 0x7fffffULL) == 0)
            igObject_Destroy((igObject *)old);
    }
}
static inline void assignRef(SeqData *&field, const SeqTempRef &r) {
    SeqData *o = r.p;
    if (o) { o->refCount++; }
    releaseRef_1de040(field);
    field = o;
}
static inline void setCount_1de040(SeqData *list, int n, int size) {
    if (n >= 0) {
        if (n <= list->capacity) { list->count = n; } else { ((Gap::Core::igDataList *)list)->resizeAndSetCount(n, size); }
    }
}
static inline void releaseRef_1de4e0(SeqData *old) {
    if (old) {
        --old->refCount;
        if (((unsigned long long)(long long)old->refCount & 0x7fffffULL) == 0)
            igObject_Destroy((igObject *)old);
    }
}
static inline void assignRef_1de4e0(SeqData *&field, const SeqTempRef &r) {
    SeqData *o = r.p;
    if (o) { o->refCount++; }
    releaseRef_1de4e0(field);
    field = o;
}
static inline void setCount_1de4e0(SeqData *list, int n, int size) {
    if (n >= 0) {
        if (n <= list->capacity) { list->count = n; } else { ((Gap::Core::igDataList *)list)->resizeAndSetCount(n, size); }
    }
}
static inline void assignRef_1e22c0(EnvMapAttrOps *&field, const EnvMapTempRef &r) {
    EnvMapAttr *o = r.p;
    if (o) { o->f4++; }
    EnvMapAttr *old = (EnvMapAttr *)field;
    if (old) {
        --old->f4;
        if (((unsigned long long)(long long)old->f4 & 0x7fffffULL) == 0)
            igObject_Destroy((igObject *)old);
    }
    field = (EnvMapAttrOps *)o;
}
static inline int n_of_1e3270(const T_1e3270 *list) { return list->n; }

extern "C" igMetaField *g_igTextureMatrixAttr_mField[4];

typedef igTDataList<AttrObjectStack *> AttrObjectStackList;
static inline AttrObjectStack *getAttrStack(igAttrStackManager *manager, int attrHandle) {
    return ((AttrObjectStackList *)manager->_attrStacks)->get(attrHandle);
}
static inline void fastPushAttr(igAttrStackManager *manager, const igObject *attribute, int attrHandle) {
    AttrObjectStack *attrStack = getAttrStack(manager, attrHandle);
    attrStack->push(attribute);
    igAttrStackManager_MarkStackChanged(manager, (igAttrStack *)attrStack, attrHandle);
}
static inline void fastPushOverride(igAttrStackManager *manager, const igObject *override, int attrHandle) {
    AttrObjectStack *attrStack = getAttrStack(manager, attrHandle);
    attrStack->pushOverride(override);
    igAttrStackManager_MarkStackChanged(manager, (igAttrStack *)attrStack, attrHandle);
}
/* The manager's light addresses, an igNonRefCountedAttrList kept sorted by address. Its typed
 * sortedAdd passes the light on as an igObject, and the data list's sortedAdd takes that by
 * reference. */
struct LightAttrAddrList : igTDataList<igObject *> {
    int binaryInsert(igObject *const &item) const { return FUN_00142bb0((igObjectList *)this, &item); }
    void insert(int index, igObject *const &item) { List_InsertWords((igDataList *)this, index, 1, &item); }
    int sortedAddItem(igObject *const &item) {
        const int index = binaryInsert(item);
        insert(index, item);
        return index;
    }
    int sortedAddObject(igObject *object) { return sortedAddItem(object); }
    int sortedAdd(igLightAttr *light) { return sortedAddObject((igObject *)light); }
};
static inline igObject *topAttr(AttrObjectStack *stack) {
    int n = stack->_count;
    if (n == 0) {
        return 0;
    }
    return stack->get(n - 1);
}
static inline igObject *takePooled(igObjectPool *pool, void *create) {
    int i;
    if (pool->_freeIndex >= pool->_count) {
        igObjectPool_Grow((igObjectPool *)pool, (igObject *(*)(int))create);
    }
    i = pool->_freeIndex;
    pool->_freeIndex = i + 1;
    return ((igObject **)pool->_data)[i];
}
class LightStateAttrView {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24();
    virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
    virtual void setEnabled(bool enabled);
    unsigned int _refCount;
    short _cachedAttrIndex;
    short _cachedUnitID;
    igObject *_internal;
    igLightAttr *_light;
    bool _enabled;
    igLightAttr *getLight() const { return _light; }
};
class MatrixAttrView {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22();
    virtual void setUnitID(int unit);
    virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28();
    virtual void s29();
    virtual void setMatrix(float *m);
    unsigned int _refCount;
    short _cachedAttrIndex;
    short _cachedUnitID;
    float _m[16];
};
struct TextureMatrixAttrView : MatrixAttrView {
    int _unitID;
    short _outputElementCount;
    unsigned char _isProjective;
};
class TransformView {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24();
    virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
    virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34();
    virtual void s35(); virtual void s36();
    virtual void update(int time);
    unsigned int _refCount;
    char _pad8[24];
    float _m[16];
    int _target;
    MatrixAttrView *_mvm;
};
class CommonTraversalView {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual int getTime();
    unsigned int _refCount;
    char _pad8[44];
    igAttrStackManager *_attrStack;
    char _pad56[16];
    igObjectPool *_matrixPool;
    igObjectPool *_timePool;
    igObjectPool *_blendMatrixPool;
    igObjectPool *_texMatPool;
};
extern "C" int igAttrStackManager_IsLightEnabled(igAttrStackManager *self, igLightAttr *light);
extern "C" float *igTransform_PushMatrix(TransformView *self, CommonTraversalView *traversal);
extern "C" int igTransform_TraverseChildrenAndPopMatrix(float *matrix, igTransform *self, igCommonTraversal *traversal);
extern "C" int igCommonTraversal_TraverseOverrideAttrSet(igCommonTraversal *self, igOverrideAttrSet *set);
extern "C" int igCommonTraversal_TraverseAttrSet(igCommonTraversal *self, igAttrSet *set);
extern "C" int igCommonTraversal_TraverseSelfShadowShader(igCommonTraversal *self, igProjectiveShadowShader *shader);
extern "C" int igTransform_CompileChildrenAndPopMatrix(float *matrix, igTransform *self, igCompileTraversal *traversal);
extern "C" int igCompileTraversal_TraverseJointTransform(igTraversal *traversal, igTransform *node);

#endif
