#ifndef DW4_SCENE_GRAPH_LIBRARY_H
#define DW4_SCENE_GRAPH_LIBRARY_H

#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"
#include "dw4/igTDataList.h"
#include "dw4/igVec3f.h"
#include "dw4/igobject_release.h"

class ForwardTarget { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual int vX(void *); };
struct TraversalNodeView { char pad[24]; int _id; };
extern "C" unsigned char g_SceneGraphLibrary_registered;
extern "C" igMetaObject *g_igGroup_metaObject[4];
extern igMetaObject *g_igTraversal_metaObject[4];
extern "C" int igObject_InitHeader(...);
extern "C" int DAT_00528250[4];
extern "C" void *g_objectSystem[4];
struct R { int vt; unsigned int rc; };
struct Obj { int *vt; char pad[24]; struct R *p; char pad2[0]; };
extern "C" int thunk_FUN_002ed460__002ff810(...);
struct S {
    void *f0;
    char pad[24];
    void *f1c;
};
extern "C" char igObject_GetMetaObject_ParentAccessor[];
extern "C" char igObject_Register[];
extern "C" char g_igTraversal_callbackList[];
extern "C" char igTraversal_className[];
extern "C" int igMetaObject_RegisterClass(...);
extern "C" int FUN_002ebc00(...);
extern "C" int FUN_002fe480(...);
extern "C" int igMetaObject_CreateFields(...);
extern "C" int igMetaObject_GetFieldAt(...);
extern "C" int igMetaObject_GetFieldCount(...);
extern "C" int igMetaObject_NameFields(...);
extern "C" int g_igTraversal_ctorTable[4];
extern "C" int g_igTraversal_fieldTable[4];
extern "C" int DAT_0048af50[4];
extern "C" int DAT_0048af70[4];
extern "C" int FUN_002fe490(...);
extern "C" igMetaObject *g_igTransientShaderData_metaObject[4];
struct Obj_194720 { int *vt; int f4; int f8; int fC; int f10; int f14; int f18; int f1C; };
extern "C" int DAT_0052b870[4];
extern "C" int FUN_0013a800(...);
extern "C" int DAT_00528870[4];
struct Ref { int pad; union { int w; struct { unsigned cnt:23; unsigned f:9; } b; } u; };
extern "C" int __dl__FPv(...);
struct T { int word0; int references; };
struct Obj_194930 {
    int *vt; char p4[4]; T *m8; T *m12; T *m16; T *m20;
    inline void rel(T **self) {
        if (self) {
            T *object = *self;
            if (object) {
                --object->references;
                if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
                    igObject_Destroy(object);
            }
        }
    }
};
extern "C" char igShaderData_GetPublishedMetaObject[];
extern "C" char g_igTransientShaderData_callbackList[];
extern "C" char igTransientShaderData_className[];
extern "C" igMetaObject *g_igShaderData_metaObject[4];
extern "C" int FUN_0013abd0(...);
extern "C" int FUN_001e5690(...);
extern "C" int FUN_00303460(...);
extern "C" int ObjectPointerList_FindIndex(...);
extern "C" int igMetaObject_FinalizeAndReplaceField(...);
extern "C" int igMetaObject_FindFieldByName(...);
extern "C" int text_attrPushLists[4];
extern "C" int text_attrPopLists[4];
extern "C" int text_dataPumps[4];
extern "C" int text_childLists[4];
extern "C" int DAT_005611b0[4];
extern "C" int DAT_005611b8[4];
extern "C" int DAT_005611c0[4];
extern "C" int DAT_005611c8[4];
struct M { char pad[40]; int f40; };
struct T_194b40 { int word0; int references; char pad8[20]; int f28; char pad32[6]; char f38; char pad39[13]; char f52; char pad53[3]; int f56; };
class DW4VC_84_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual int vX(int); };
extern "C" igMetaObject *igMetaObject_Create(int);
extern "C" int Memory_GetAllocatorBySelector(...);
extern "C" igMetaObject *g_igTransformSource_metaObject[4];
extern "C" int kIGMemoryPoolHandleMetaData[4];
extern "C" char igTransformSource_className[];
extern igMetaObject *g_igTransformSequence1_5_metaObject[4];
struct Obj_194f40 { int *vt; int w[27]; };
extern "C" int FUN_001374b0(int *, int);
extern "C" int DAT_005282c0[4];
extern "C" int DAT_005283e0[4];
struct Obj_195030 {
    int *vt; char p4[4]; T *m8; T *m12; T *m16; T *m20;
    inline void rel(T **self) {
        if (self) {
            T *object = *self;
            if (object) {
                --object->references;
                if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
                    igObject_Destroy(object);
            }
        }
    }
};
struct S_temp_a0 { char pad4[4]; int f4; };
struct O { S_temp_a0 *m; };
/* Deleting destructor; the deletion flag is a signed short. */
typedef struct ObjectRefTarget { int word0; int references; } ObjectRefTarget;
typedef struct ObjectRefWord { ObjectRefTarget *value; } ObjectRefWord;
extern "C" char igTransformSequence_GetPublishedMetaObject[];
extern "C" char g_igTransformSequence1_5_callbackList[];
extern "C" char igTransformSequence1_5_className[];
extern "C" void igTransformSequence1_5_InitFields(void);
extern "C" int FUN_002ca680(...);
extern "C" int g_igTransformSequence1_5_ctorTable[4];
extern "C" int g_igTransformSequence1_5_fieldTable[4];
extern "C" int DAT_0048b010[4];
extern "C" int DAT_0048b040[4];
extern "C" int text_timeList[4];
extern "C" int DAT_005611e8[4];
extern "C" igMetaObject *g_igTransformSequence_metaObject[4];
extern "C" char igTransformSource_GetPublishedMetaObject[];
extern "C" char g_igTransformSequence_callbackList[];
extern "C" char igTransformSequence_className[];
extern "C" int FUN_00189c10(...);
extern "C" int FUN_0018a0a0(...);
extern "C" int FUN_0018e470(...);
extern "C" int FUN_002c93a0(...);
extern "C" int FUN_002d9500(...);
extern "C" int FUN_002dc7a0(...);
extern "C" int FUN_002ea4b0(...);
extern "C" int g_igTransformSequence_ctorTable[4];
extern "C" int g_igTransformSequence_fieldTable[4];
extern "C" int DAT_0048b0e0[4];
extern "C" int DAT_0048b110[4];
extern "C" int DAT_0048b138[4];
extern "C" int FUN_002d1870(...);
struct Fld { char p0[38]; char f38; char p39[13]; char f52; char p53[3]; int f56; int f60; };
extern "C" igMetaObject *g_igTransformRecorder_metaObject[4];
struct Obj_195860 { int *vt; int f4; int f8; int f12; int f16; int f20; int f24; int f28; char sub1[64]; char sub2[64]; };
extern "C" int igMatrix44f_SetIdentity(...);
extern "C" int DAT_0052b7d0[4];
typedef struct S_temp_a0_1958f0 { char pad4[4]; int f4; } S_temp_a0_1958f0;
extern "C" int StringChunk_ReleaseHeader(...);
extern "C" int g_igNamedObject_vtable[4];
extern "C" int DAT_00528a90[4];
struct Rc { int vt; int rc; };
struct T_195970 { int *vt; int w4; char *f8; struct Rc *f12; struct Rc *f16; };
extern "C" int DAT_00528dd0[4];
struct T_195a90 { int *vt; int w4; char *f8; struct Rc *f12; struct Rc *f16; int w20; int w24; struct Rc *f28; };
extern "C" char igGroup_GetPublishedMetaObject[];
extern "C" char igTransformRecorder_className[];
extern "C" int g_igTransformRecorder_ctorTable[4];
extern "C" int g_igTransformRecorder_fieldTable[4];
extern "C" int DAT_0048b150[4];
extern "C" int DAT_0048b158[4];
extern "C" igMetaObject *g_igNonRefCountedTransformList_metaObject[4];
extern "C" int DAT_0052b760[4];
union U { int vt; char b[32]; };
extern "C" char igNonRefCountedObjectList_GetPublishedMetaObject[];
extern "C" char igNonRefCountedObjectList_Register[];
extern "C" char g_igNonRefCountedTransformList_callbackList[];
extern "C" char igNonRefCountedTransformList_className[];
extern "C" igMetaObject *g_igTransformList_metaObject[4];
extern "C" int DAT_0052b6f0[4];
extern "C" char igObjectList_GetPublishedMetaObject[];
extern "C" char igObjectList_Register[];
extern "C" char g_igTransformList_callbackList[];
extern "C" char igTransformList_className[];
extern "C" igMetaObject *g_igTransformStack_metaObject[4];
struct Obj_196080 { int *vt; char pad[28]; };
extern "C" int DAT_0052b690[4];
extern "C" char igNonRefCountedObjectStack_GetPublishedMetaObject[];
extern "C" char igNonRefCountedObjectStack_Register[];
extern "C" char g_igTransformStack_callbackList[];
extern "C" char igTransformStack_className[];
extern "C" int igMetaObject_CreateInstance(...);
extern "C" igMetaObject *g_igTransform_metaObject[4];
struct W { int *vt; int f[27]; };
extern "C" int DAT_005284f0[4];
struct S_1962d0 {
    void *f0;
    char pad0[96];
    void *f64;
    void *f68;
};
extern "C" char g_igTransform_callbackList[];
extern "C" char igTransform_className[];
struct V { int x; int y; int z; int w; };
struct M_196570 { int m[16]; };
extern "C" int FUN_00130310(...);
extern "C" int FUN_00130e90(...);
extern "C" int FUN_0018c640(...);
extern "C" int g_igTransform_ctorTable[4];
extern "C" int g_igTransform_fieldTable[4];
extern "C" int DAT_0048b1b0[4];
extern "C" int DAT_0048b1c0[4];
extern igMetaObject *g_igObjectPool_metaObject[4];
struct Obj_196780 { int *vt; char pad[28]; };
extern "C" int DAT_0052b5c0[4];
extern "C" char igObjectPool_className[];
extern "C" int FUN_002d3890(...);
extern "C" int g_igObjectPool_ctorTable[4];
extern "C" int g_igObjectPool_fieldTable[4];
extern "C" int DAT_0048b1f0[4];
extern "C" int DAT_0048b200[4];
extern "C" igMetaObject *g_igSwitch_metaObject[4];
extern "C" int DAT_00528590[4];
union U_1969d0 { int vt; char b[48]; };
extern "C" char g_igSwitch_callbackList[];
extern "C" char igSwitch_className[];
extern "C" int g_igSwitch_ctorTable[4];
extern "C" int g_igSwitch_fieldTable[4];
extern "C" int DAT_0048b228[4];
extern "C" int DAT_0048b230[4];
union U_196c10 { int vt; char b[144]; };
extern igMetaObject *g_igSorter_metaObject[4];
extern int kIGMemoryPoolHandleMetaData[4];
extern int DAT_00528630[4];
extern int DAT_00528620[8];
extern void *g_objectSystem[4];
extern int g_igSorter_ctorTable[4];
extern int g_igSorter_fieldTable[4];
extern int DAT_0048b390[4];
extern int DAT_0048b420[4];
extern char g_igSorter_callbackList[];
extern char igSorter_className[];
extern "C" void igMetaObject_RunStaticInit(...);
extern "C" int FUN_001380e0(...);
extern "C" int FUN_001510d0(...);
extern "C" int ObjectRef_Destruct_00150eb0(...);
extern "C" int FUN_00137fb0(...);
extern "C" int FUN_001382a0(...);
extern "C" int FUN_001386d0(...);
extern "C" int FUN_0013ad40(...);
extern "C" int igIntList_GetOrCreateMetaObject(...);
extern "C" igMetaObject *g_igRenderPackageList_metaObject[4];
struct Obj_197860 { int *vt; char pad[28]; };
extern "C" int DAT_0052b550[4];
extern "C" char g_igRenderPackageList_callbackList[];
extern "C" char igRenderPackageList_className[];
extern "C" igMetaObject *g_igRenderPackagePool_metaObject[4];
struct Obj_1979d0 { int *vt; char pad[28]; };
extern "C" int DAT_0052b4e0[4];
extern "C" char igObjectPool_GetPublishedMetaObject[];
extern "C" char g_igRenderPackagePool_callbackList[];
extern "C" char igRenderPackagePool_className[];
extern "C" igMetaObject *g_igRenderPackage_metaObject[4];
typedef struct S_ref { char pad4[4]; int f4; } S_ref;
extern "C" int DAT_0052b480[4];
extern "C" char g_igRenderPackage_callbackList[];
extern "C" char igRenderPackage_className[];
extern "C" int g_igRenderPackage_ctorTable[4];
extern "C" int g_igRenderPackage_fieldTable[4];
extern "C" int DAT_0048b510[4];
extern "C" int DAT_0048b530[4];
extern "C" igMetaObject *g_igSkinList_metaObject[4];
extern "C" int DAT_0052b410[4];
extern "C" char g_igSkinList_callbackList[];
extern "C" char igSkinList_className[];
extern "C" igMetaObject *g_igSkin_metaObject[4];
extern "C" int DAT_0052b3b0[4];
union U_198070 { int vt; int w[8]; char b[32]; };
typedef struct S_temp_a0_198190 { char pad4[4]; int f4; } S_temp_a0_198190;
extern "C" char igNamedObject_GetPublishedMetaObject[];
extern "C" char igNamedObject_Register[];
extern "C" char g_igSkin_callbackList[];
extern "C" char igSkin_className[];
extern "C" int FUN_0018a6a0(...);
extern "C" int g_igSkin_ctorTable[4];
extern "C" int g_igSkin_fieldTable[4];
extern "C" int DAT_0048b570[4];
extern "C" int DAT_0048b578[4];
extern "C" igMetaObject *g_igSkeletonList_metaObject[4];
struct Obj_198480 { int *vt; char pad[28]; };
extern "C" int DAT_0052b340[4];
extern "C" char g_igSkeletonList_callbackList[];
extern "C" char igSkeletonList_className[];
extern igMetaObject *g_igSkeleton_metaObject[4];
extern "C" int DAT_005286a0[4];
extern "C" char igAnimationHierarchy_GetPublishedMetaObject[];
extern "C" char g_igSkeleton_callbackList[];
extern "C" char igSkeleton_className[];
extern "C" igMetaObject *g_igAnimationHierarchy_metaObject[4];
extern "C" int FUN_001888e0(...);
extern "C" int g_igSkeleton_ctorTable[4];
extern "C" int g_igSkeleton_fieldTable[4];
extern "C" int DAT_0048b5b0[4];
extern "C" int DAT_0048b5c0[4];
extern "C" igMetaObject *g_igSkeletonBoneInfoList_metaObject[4];
struct Obj_198890 { int *vt; char pad[28]; };
extern "C" int DAT_0052b2d0[4];
extern "C" char g_igSkeletonBoneInfoList_callbackList[];
extern "C" char igSkeletonBoneInfoList_className[];
extern igMetaObject *g_igSkeletonBoneInfo_metaObject[4];
extern "C" int DAT_0052b270[4];
extern "C" char thunk_igSkeletonBoneInfo_GetMetaObject_00198ac0[];
extern "C" char igSkeletonBoneInfo_className[];
extern "C" int g_igSkeletonBoneInfo_ctorTable[4];
extern "C" int g_igSkeletonBoneInfo_fieldTable[4];
extern "C" int DAT_0048b5f8[4];
extern "C" int DAT_0048b608[4];
extern igMetaObject *g_igShaderProcessor_metaObject[4];
struct Obj_198bf0 { int *vt; char pad[4]; };
extern "C" int DAT_00528720[4];
extern "C" char igShaderProcessor_className[];
extern igMetaObject *g_igShaderInfo_metaObject[4];
union U_198d50 { int vt; int w[8]; void *p[8]; char b[32]; };
extern "C" int DAT_00528790[4];
extern "C" char igInfo_GetPublishedMetaObject[];
extern "C" char igInfo_Register[];
extern "C" char g_igShaderInfo_callbackList[];
extern "C" char igShaderInfo_className[];
extern "C" int g_igShaderInfo_ctorTable[4];
extern "C" int g_igShaderInfo_fieldTable[4];
extern "C" int DAT_0048b630[4];
extern "C" int DAT_0048b638[4];
extern "C" void FUN_001d8ab0(void);
extern "C" igMetaObject *g_igShaderFactoryList_metaObject[4];
struct Obj_199040 { int *vt; char pad[28]; };
extern "C" int DAT_0052b200[4];
extern "C" char g_igShaderFactoryList_callbackList[];
extern "C" char igShaderFactoryList_className[];
extern "C" int igMetaEnum_Create(...);
extern "C" int DAT_0048b650[4];
extern "C" int DAT_0048b660[4];
extern "C" int FILE_CACHING_MODE[4];
extern "C" int DAT_00561520[4];
extern "C" igMetaObject *g_igShaderFactory_metaObject[4];
extern "C" int DAT_00528800[4];
struct T_199330 { int *vt; int w4; char *f8; struct Rc *f12; struct Rc *f16; };
extern "C" char g_igShaderFactory_callbackList[];
extern "C" char igShaderFactory_className[];
extern "C" int FUN_002be100(...);
extern "C" int g_igShaderFactory_ctorTable[4];
extern "C" int g_igShaderFactory_fieldTable[4];
extern "C" int DAT_0048b698[4];
extern "C" int DAT_0048b6a8[4];
extern "C" int DAT_0048b6b8[4];
struct Obj_1996b0 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; };
extern "C" char g_igShaderData_callbackList[];
extern "C" char igShaderData_className[];
extern "C" int g_igShaderData_ctorTable[4];
extern "C" int g_igShaderData_fieldTable[4];
extern "C" int DAT_0048b6f0[4];
extern "C" int DAT_0048b700[4];
extern "C" igMetaObject *g_igBlendMatricesAttrPool_metaObject[4];
struct Obj_199a90 { int *vt; char pad[28]; };
extern "C" int DAT_0052b190[4];
extern "C" char g_igBlendMatricesAttrPool_callbackList[];
extern "C" char igBlendMatricesAttrPool_className[];
extern "C" igMetaObject *g_igTextureMatrixAttrPool_metaObject[4];
struct Obj_199c00 { int *vt; char pad[28]; };
extern "C" int DAT_0052b120[4];
extern "C" char g_igTextureMatrixAttrPool_callbackList[];
extern "C" char igTextureMatrixAttrPool_className[];
extern "C" igMetaObject *g_igMatrixObjectPool_metaObject[4];
extern "C" int DAT_0052b0b0[4];
extern "C" char g_igMatrixObjectPool_callbackList[];
extern "C" char igMatrixObjectPool_className[];
extern "C" igMetaObject *g_igVertexBlendMatrixListAttrPool_metaObject[4];
extern "C" int DAT_0052b040[4];
extern "C" char g_igVertexBlendMatrixListAttrPool_callbackList[];
extern "C" char igVertexBlendMatrixListAttrPool_className[];
extern "C" igMetaObject *g_igVertexBlendMatrixAttrPool_metaObject[4];
struct Obj_19a050 { int *vt; char pad[28]; };
extern "C" int DAT_0052afd0[4];
extern "C" char g_igVertexBlendMatrixAttrPool_callbackList[];
extern "C" char igVertexBlendMatrixAttrPool_className[];
extern "C" igMetaObject *g_igProjectionMatrixAttrPool_metaObject[4];
struct Obj_19a1c0 { int *vt; char pad[28]; };
extern "C" int DAT_0052af60[4];
extern "C" char g_igProjectionMatrixAttrPool_callbackList[];
extern "C" char igProjectionMatrixAttrPool_className[];
extern "C" igMetaObject *g_igTimeAttrPool_metaObject[4];
extern "C" int DAT_0052aef0[4];
extern "C" char g_igTimeAttrPool_callbackList[];
extern "C" char igTimeAttrPool_className[];
extern "C" igMetaObject *g_igModelViewMatrixAttrPool_metaObject[4];
extern "C" int DAT_0052ae80[4];
extern "C" char g_igModelViewMatrixAttrPool_callbackList[];
extern "C" char igModelViewMatrixAttrPool_className[];
extern "C" igMetaObject *g_igLightStateAttrPool_metaObject[4];
struct Obj_19a610 { int *vt; char pad[28]; };
extern "C" int DAT_0052ae10[4];
extern "C" char g_igLightStateAttrPool_callbackList[];
extern "C" char igLightStateAttrPool_className[];
extern "C" igMetaObject *g_igTraversalFunctionList_metaObject[4];
struct Obj_19a7c0 { int *vt; char pad[28]; };
extern "C" int DAT_0052adb0[4];
extern "C" char igDataList_GetPublishedMetaObject[];
extern "C" char igDataList_Register[];
extern "C" char igTraversalFunctionList_className[];
extern igMetaObject *g_igSegment_metaObject[4];
struct Obj_19ada0 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; };
extern "C" int DAT_0052ad10[4];
extern "C" char igSegment_className[];
extern "C" igMetaObject *g_igSceneInfo_metaObject[4];
struct Obj_19af80 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; int w12; int w13; int w14; int w15; };
extern "C" int FUN_00131aa0(...);
extern "C" int FUN_00131b20(...);
extern "C" int DAT_005288e0[4];
extern "C" int DAT_0052fde0[4];
typedef struct S_temp_a0_19b1f0 { char pad4[4]; int f4; } S_temp_a0_19b1f0;
extern "C" char g_igSceneInfo_callbackList[];
extern "C" char igSceneInfo_className[];
struct V3 { int x; int y; int z; };
extern "C" int FUN_0013a360(...);
extern "C" int g_igSceneInfo_ctorTable[4];
extern "C" int g_igSceneInfo_fieldTable[4];
extern "C" int DAT_0048b7c0[4];
extern "C" int DAT_0048b7e0[4];
extern "C" igMetaObject *g_igProjectiveShadowShader_metaObject[4];
struct S_19b4e0 { int *vt; char pad[236]; };
extern "C" int FUN_001321b0(...);
extern "C" int FUN_00132390(...);
extern "C" int FUN_00132410(...);
extern "C" int FUN_00132980(...);
extern "C" int FUN_00133ca0(...);
extern "C" int FUN_001353b0(...);
extern "C" int FUN_00136370(...);
extern "C" int FUN_00142d10(...);
extern "C" int DAT_00528950[4];
extern "C" char g_igProjectiveShadowShader_callbackList[];
extern "C" char igProjectiveShadowShader_className[];
extern "C" int FUN_00130440(...);
extern "C" int FUN_00131160(...);
extern "C" int FUN_00131800(...);
extern "C" int FUN_00132850(...);
extern "C" int FUN_00132ba0(...);
extern "C" int FUN_00133b70(...);
extern "C" int FUN_001341f0(...);
extern "C" int FUN_001346d0(...);
extern "C" int FUN_001356f0(...);
extern "C" int FUN_00136750(...);
extern "C" int FUN_00137850(...);
extern "C" int FUN_00138950(...);
extern "C" int FUN_00138f20(...);
extern "C" int FUN_0014dfb0(...);
extern "C" int FUN_002e3810(void *, float);
extern "C" int g_igProjectiveShadowShader_ctorTable[4];
extern "C" int g_igProjectiveShadowShader_fieldTable[4];
extern "C" int DAT_0048b9d0[4];
extern "C" int DAT_0048ba90[4];
struct Fld_19b8a0 { char p0[38]; char f38; char p39[13]; char f52; char p53[3]; int f56; };
extern igMetaObject *g_igPlanarShadowShader_metaObject[4];
extern "C" int FUN_0013bfe0(...);
extern "C" int FUN_00151090(...);
extern "C" int FUN_0018f980(...);
extern "C" int DAT_005289f0[4];
extern "C" int D_005289f0[4];
union U_19bf50 { int vt; char b[112]; };
extern "C" int DAT_005294b0[4];
struct S_19c0e0 {
    void *f0;
    char pad[28];
    void *f20;
};
extern "C" char igAttrSet_GetPublishedMetaObject[];
extern "C" char g_igPlanarShadowShader_callbackList[];
extern "C" char igPlanarShadowShader_className[];
extern "C" igMetaObject *g_igAttrSet_metaObject[4];
extern "C" int FUN_00133430(...);
extern "C" int FUN_00135540(...);
extern "C" int FUN_001365e0(...);
extern "C" int FUN_0013af00(...);
extern "C" int FUN_00186a80(...);
extern "C" int FUN_0018e670(void *, void *);
typedef struct { float x, y, z, w; } V4;
extern "C" int g_igPlanarShadowShader_ctorTable[4];
extern "C" int g_igPlanarShadowShader_fieldTable[4];
extern "C" int DAT_0048bbf0[4];
extern "C" int DAT_0048bc30[4];
extern "C" igMetaObject *g_igOverrideAttrSet_metaObject[4];
struct F { int *vt; int w[11]; };
extern "C" int DAT_0052ac70[4];
extern "C" char igOverrideAttrSet_className[];
extern "C" igMetaObject *g_igNonRefCountedNodeList_metaObject[4];
struct Obj_19c960 { int *vt; char pad[28]; };
extern "C" int DAT_0052ac00[4];
extern "C" char g_igNonRefCountedNodeList_callbackList[];
extern "C" char igNonRefCountedNodeList_className[];
extern "C" igMetaObject *g_igNodeListList_metaObject[4];
typedef struct { int *vt; int pad[7]; } Obj_19cad0;
extern "C" int DAT_0052ab90[4];
extern "C" char g_igNodeListList_callbackList[];
extern "C" char igNodeListList_className[];
extern "C" igMetaObject *g_igNodeList_metaObject[4];
struct Obj_19cc80 { int *vt; char pad[28]; };
extern "C" int DAT_0052ab20[4];
extern "C" char g_igNodeList_callbackList[];
extern "C" char igNodeList_className[];
extern "C" igMetaObject *g_igNode_metaObject[4];
extern "C" char g_igNode_callbackList[];
extern "C" char igNode_className[];
extern "C" int g_igNode_ctorTable[4];
extern "C" int g_igNode_fieldTable[4];
extern "C" int DAT_0048bcb0[4];
extern "C" int DAT_0048bcc0[4];
extern "C" int DAT_00528e70[4];
struct S_19d120 {
    void *f0;
    char pad[36];
    void *f28;
};
extern "C" igMetaObject *g_igGeometry_metaObject[4];
extern "C" igMetaObject *g_igModelViewMatrixBoneSelectList_metaObject_00561880[4];
extern "C" int DAT_0052aab0[4];
extern "C" char g_igModelViewMatrixBoneSelectList_561880_callbackList[];
extern "C" char igModelViewMatrixBoneSelectList_className[];
extern igMetaObject *g_igModelViewMatrixBoneSelect_metaObject[4];
extern "C" int DAT_0052aa10[4];
union U_19d480 { int vt; int w[12]; void *p[12]; char b[48]; };
extern "C" char igModelViewMatrixBoneSelect_className[];
extern "C" int g_igModelViewMatrixBoneSelect_ctorTable[4];
extern "C" int g_igModelViewMatrixBoneSelect_fieldTable[4];
extern "C" int DAT_0048bce8[4];
extern "C" int DAT_0048bcf0[4];
extern igMetaObject *g_igLod_metaObject[4];
struct W_19d660 { int *vt; int f[19]; };
extern "C" int FUN_001354b0(...);
extern "C" int DAT_00528b20[4];
extern "C" char g_igLod_callbackList[];
extern "C" char igLod_className[];
extern "C" int FUN_002c9780(void);
extern "C" int g_igLod_ctorTable[4];
extern "C" int g_igLod_fieldTable[4];
extern "C" int DAT_0048bd50[4];
extern "C" int DAT_0048bd70[4];
extern igMetaObject *g_igLightStateSet_metaObject[4];
struct Obj_19d960 { int *vt; int w[11]; };
extern "C" int DAT_00528bc0[4];
extern "C" char g_igLightStateSet_callbackList[];
extern "C" char igLightStateSet_className[];
extern "C" int FUN_00136040(...);
extern "C" int g_igLightStateSet_ctorTable[4];
extern "C" int g_igLightStateSet_fieldTable[4];
extern "C" int DAT_0048bda8[4];
extern "C" int DAT_0048bdb0[4];
extern "C" igMetaObject *g_igLightSet_metaObject[4];
extern "C" int DAT_00528c60[4];
struct Obj_19dc50 { int *vt; int f4; int f8; int f12; int f16; int f20; int f24; int f28; };
extern "C" char igNode_GetPublishedMetaObject[];
extern "C" char g_igLightSet_callbackList[];
extern "C" char igLightSet_className[];
extern "C" int g_igLightSet_ctorTable[4];
extern "C" int g_igLightSet_fieldTable[4];
extern "C" int DAT_0048bdd0[4];
extern "C" int DAT_0048bdd8[4];
extern "C" igMetaObject *g_igAnimationSequence_metaObject[4];
extern "C" igMetaObject *g_igIntersectTraversal_metaObject[4];
struct Obj_19e070 { int *vt; int w[15]; };
extern "C" int FUN_00150fb0(int *, int);
extern "C" int FUN_0018fa00(int *, int);
extern "C" int DAT_00528cf0[4];
struct S1 { char pad4[4]; int f4; };
struct O_19e150 { int *vt; char pad4[24]; S1 *m28; S1 *m32; S1 *m36; S1 *m40; char pad44[8]; S1 *m52; S1 *m56; };
typedef struct S_temp_a0_19e340 { char pad4[4]; int f4; } S_temp_a0_19e340;
typedef struct S_temp_a0_19e3c0 { char pad4[4]; int f4; } S_temp_a0_19e3c0;
extern "C" char igTraversal_GetPublishedMetaObject[];
extern "C" char g_igIntersectTraversal_callbackList[];
extern "C" char igIntersectTraversal_className[];
extern "C" int FUN_00186c40(...);
extern "C" int FUN_00188260(...);
extern "C" int FUN_001e4740(...);
extern "C" int g_igIntersectTraversal_ctorTable[4];
extern "C" int g_igIntersectTraversal_fieldTable[4];
extern "C" int DAT_0048be40[4];
extern "C" int DAT_0048be60[4];
extern "C" igMetaObject *g_igProbe_metaObject[4];
extern "C" int DAT_0052a950[4];
extern "C" char g_igProbe_callbackList[];
extern "C" char igProbe_className[];
extern "C" int FUN_001880b0(...);
extern "C" int g_igProbe_ctorTable[4];
extern "C" int g_igProbe_fieldTable[4];
extern "C" int DAT_0048beb0[4];
extern "C" int DAT_0048bec0[4];
extern "C" igMetaObject *g_igInterpretedShaderData_metaObject[4];
struct Obj_19eaa0 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; };
extern "C" int FUN_0014dd40(...);
extern "C" int DAT_0052a8e0[4];
extern "C" char igTransientShaderData_GetPublishedMetaObject[];
extern "C" char g_igInterpretedShaderData_callbackList[];
extern "C" char igInterpretedShaderData_className[];
extern "C" int FUN_002bcbb0(...);
extern "C" int g_igInterpretedShaderData_ctorTable[4];
extern "C" int g_igInterpretedShaderData_fieldTable[4];
extern "C" int DAT_0048bef0[4];
extern "C" int DAT_0048bef8[4];
extern igMetaObject *g_igIniShaderFactory_metaObject[4];
struct Obj_19ed70 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; int w12; int w13; int w14; int w15; };
extern "C" int FUN_001509f0(...);
extern "C" int StringRef_Destruct_00130720(...);
extern "C" int DAT_00528d60[4];
extern "C" char igShaderFactory_GetPublishedMetaObject[];
extern "C" char g_igIniShaderFactory_callbackList[];
extern "C" char igIniShaderFactory_className[];
extern "C" int FUN_002bb030(...);
extern "C" int igMemoryPool_GetOrCreateMetaObject(...);
extern "C" int igStringMetaField_SetDefaultText(...);
extern "C" int g_igIniShaderFactory_ctorTable[4];
extern "C" int g_igIniShaderFactory_fieldTable[4];
extern "C" int DAT_0048bf80[4];
extern "C" int DAT_0048bfb0[4];
struct Obj_19f2b0 { int *vt; int f4; int f8; int fC; int f10; int f14; int f18; int f1C; };
extern "C" char g_igGroup_callbackList[];
extern "C" char igGroup_className[];
extern "C" int g_igGroup_ctorTable[4];
extern "C" int g_igGroup_fieldTable[4];
extern "C" int DAT_0048bff0[4];
extern "C" int DAT_0048bff8[4];
extern "C" igMetaObject *g_igGraphPathList_metaObject[4];
extern "C" int DAT_0052a870[4];
extern "C" char g_igGraphPathList_callbackList[];
extern "C" char igGraphPathList_className[];
extern "C" igMetaObject *g_igGraphPath_metaObject[4];
typedef struct { int *vt; int p1[1]; int *ref; int pad[5]; } Obj_19f710;
extern "C" int DAT_0052a810[4];
extern "C" char g_igGraphPath_callbackList[];
extern "C" char igGraphPath_className[];
extern "C" int g_igGraphPath_ctorTable[4];
extern "C" int g_igGraphPath_fieldTable[4];
extern "C" int DAT_0048c030[4];
extern "C" int DAT_0048c040[4];
extern "C" igMetaObject *g_igGeometryList_metaObject[4];
extern "C" int DAT_0052a7a0[4];
extern "C" char g_igGeometryList_callbackList[];
extern "C" char igGeometryList_className[];
struct Obj_19fb80 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; };
extern "C" char g_igGeometry_callbackList[];
extern "C" char igGeometry_className[];
extern "C" int igGeometry_InitFields_0019fca0[4];
extern "C" int igGeometry_PostInit_0019fdd0[4];
extern "C" int FUN_00133e50(...);
extern "C" int g_igGeometry_ctorTable[4];
extern "C" int g_igGeometry_fieldTable[4];
extern "C" int DAT_0048c070[4];
extern "C" int DAT_0048c078[4];
extern "C" int text_trigger[4];
extern "C" int DAT_00561a40[4];
struct S_19fde0 { int *vt; char pad[468]; int a; char b[72]; int c; };
struct T_19fde0 { int w0; int refs; };
struct T1a0910 { int word0; int references; };
struct Obj_19fde0;
struct M_19fde0 { int m[16]; };
extern igMetaObject *g_igFrustCullTraversal_metaObject[4];
extern "C" int FUN_001510a0(...);
extern "C" int FUN_00139170(...);
extern "C" int DAT_00528f10[4];
extern "C" int DAT_005293c0[4];
extern "C" igMetaObject *g_igCommonTraversal_metaObject[4];
extern "C" int g_igFrustCullTraversal_ctorTable[4];
extern "C" int g_igFrustCullTraversal_fieldTable[4];
extern "C" int DAT_0048c0d0[4];
extern "C" int DAT_0048c0f0[4];
extern "C" char g_igFrustCullTraversal_callbackList[];
extern "C" char igFrustCullTraversal_className[];
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
                    igObject_Destroy(object);
            }
        }
    }
};
extern "C" igMetaObject *g_igEnvironmentMapShader2List_metaObject[4];
struct Obj_1a1480 { int *vt; char pad[28]; };
extern "C" int DAT_0052a730[4];
extern "C" char g_igEnvironmentMapShader2List_callbackList[];
extern "C" char igEnvironmentMapShader2List_className[];
extern igMetaObject *g_igEnvironmentMapShader2_metaObject[4];
extern "C" char g_igEnvironmentMapShader2_callbackList[];
extern "C" char igEnvironmentMapShader2_className[];
extern "C" int FUN_00131ca0(...);
extern "C" int FUN_00131fe0(...);
extern "C" int FUN_001325e0(...);
extern "C" int FUN_00139640(...);
extern "C" int g_igEnvironmentMapShader2_ctorTable[4];
extern "C" int g_igEnvironmentMapShader2_fieldTable[4];
extern "C" int DAT_0048c210[4];
extern "C" int DAT_0048c270[4];
extern int g_igEnbayaTransformSource_metaObject[4];
typedef struct { int *vt; int p1[2]; int *ref; int pad[0]; } Obj_1a1900;
extern "C" int DAT_00529080[4];
extern "C" char g_igEnbayaTransformSource_callbackList[];
extern "C" char igEnbayaTransformSource_className[];
extern "C" int g_igEnbayaTransformSource_metaObject[4];
extern "C" int g_igEnbayaTransformSource_ctorTable[4];
extern "C" int g_igEnbayaTransformSource_fieldTable[4];
extern "C" int DAT_0048c2e0[4];
extern "C" int DAT_0048c2e8[4];
extern "C" int g_igEnbayaContextPool_metaObject[4];
extern "C" int DAT_00529110[4];
extern "C" char g_igEnbayaContextPool_callbackList[];
extern "C" char igEnbayaContextPool_className[];
extern "C" int FUN_002c8fc0(...);
extern "C" int FUN_002ca450(...);
extern "C" int g_igEnbayaContextPool_ctorTable[4];
extern "C" int g_igEnbayaContextPool_fieldTable[4];
extern "C" int DAT_0048c320[4];
extern "C" int DAT_0048c330[4];
extern "C" int g_igEnbayaContextPool_metaObject[4];
extern igMetaObject *g_igEnbayaAnimationState_metaObject[4];
extern "C" int DAT_00529170[4];
extern "C" int DAT_00529550[4];
union U_1a1e80 { int vt; char b[176]; };
extern "C" char igAnimationState_GetPublishedMetaObject[];
extern "C" char igEnbayaAnimationState_className[];
extern "C" igMetaObject *g_igAnimationState_metaObject[4];
extern "C" int g_igEnbayaAnimationState_ctorTable[4];
extern "C" int g_igEnbayaAnimationState_fieldTable[4];
extern "C" int DAT_0048c350[4];
extern "C" int DAT_0048c358[4];
extern "C" int DAT_0048c360[4];
extern "C" int DAT_0048c380[4];
extern "C" int PLAY_MODE[4];
extern "C" int DAT_00561b98[4];
extern "C" igMetaObject *g_igEnbayaAnimationSource_metaObject[4];
extern "C" int DAT_005291e0[4];
union U_1a22b0 { int vt; int w[12]; void *p[12]; char b[48]; };
extern "C" char igEnbayaAnimationSource_className[];
extern "C" int FUN_002cc2c0(...);
extern "C" int FUN_0030e750(...);
extern "C" int g_igEnbayaAnimationSource_ctorTable[4];
extern "C" int g_igEnbayaAnimationSource_fieldTable[4];
extern "C" int DAT_0048c3e0[4];
extern "C" int DAT_0048c400[4];
extern "C" igMetaObject *g_igCompressedTransformSequence1_5Data_metaObject[4];
struct Obj_1a2590 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; };
extern "C" int FUN_00164870(...);
extern "C" int DAT_0052a6d0[4];
extern "C" char g_igCompressedTransformSequence1_5Data_callbackList[];
extern "C" char igCompressedTransformSequence1_5Data_className[];
extern "C" int FUN_002ca030(...);
extern "C" int g_igCompressedTransformSequence1_5Data_ctorTable[4];
extern "C" int g_igCompressedTransformSequence1_5Data_fieldTable[4];
extern "C" int DAT_0048c480[4];
extern "C" int DAT_0048c4b0[4];
extern "C" igMetaObject *g_igCompressedAnimationSequenceQS_metaObject[4];
extern "C" int DAT_00529260[4];
union U_1a2810 { int vt; char b[64]; };
extern "C" char igAnimationSequence_GetPublishedMetaObject[];
extern "C" char g_igCompressedAnimationSequenceQS_callbackList[];
extern "C" char igCompressedAnimationSequenceQS_className[];
extern "C" int FUN_0030ec10(...);
extern "C" int g_igCompressedAnimationSequenceQS_ctorTable[4];
extern "C" int g_igCompressedAnimationSequenceQS_fieldTable[4];
extern "C" int DAT_0048c540[4];
extern "C" int DAT_0048c570[4];
extern "C" int DAT_0048c5a0[4];
struct Fld_1a29e0 { char p0[38]; char f38; char p39[13]; int f52; int f56; };
extern igMetaObject *g_igBlendListRecord_metaObject[4];
extern "C" int DAT_0052a670[4];
union U_1a2d00 { int vt; int w[4]; void *p[4]; char b[16]; };
extern "C" char g_igBlendListRecord_callbackList[];
extern "C" char igBlendListRecord_className[];
extern "C" int FUN_001399d0(...);
extern "C" int FUN_0013b070(...);
extern "C" int g_igBlendListRecord_ctorTable[4];
extern "C" int g_igBlendListRecord_fieldTable[4];
extern "C" int DAT_0048c5c8[4];
extern "C" int DAT_0048c5d0[4];
extern igMetaObject *g_igCompileTraversal_metaObject[4];
extern "C" int DAT_00529330[4];
extern "C" int DAT_00529320[8];
union U_1a2f80 { int vt; char b[528]; };
extern "C" char igCommonTraversal_GetPublishedMetaObject[];
extern "C" char g_igCompileTraversal_callbackList[];
extern "C" char igCompileTraversal_className[];
extern "C" int FUN_00139820(...);
extern "C" int FUN_001e4970(...);
extern "C" int g_igCompileTraversal_ctorTable[4];
extern "C" int g_igCompileTraversal_fieldTable[4];
extern "C" int DAT_0048c660[4];
extern "C" int DAT_0048c690[4];
extern "C" igMetaObject *g_igCompiledTransformList_metaObject[4];
struct Obj_1a34c0 { int *vt; char pad[28]; };
extern "C" int DAT_0052a600[4];
extern "C" char g_igCompiledTransformList_callbackList[];
extern "C" char igCompiledTransformList_className[];
extern igMetaObject *g_igCompiledTransform_metaObject[4];
union U_1a3620 { int vt; int w[12]; void *p[12]; char b[48]; };
extern "C" int DAT_0052a5a0[4];
extern "C" char g_igCompiledTransform_callbackList[];
extern "C" char igCompiledTransform_className[];
struct Fld_1a37a0 { char p0[38]; char f38; char p39[13]; char f52; char p53[3]; int f56; };
extern "C" int FUN_002b9540(...);
extern "C" int g_igCompiledTransform_ctorTable[4];
extern "C" int g_igCompiledTransform_fieldTable[4];
extern "C" int DAT_0048c720[4];
extern "C" int DAT_0048c740[4];
struct O_1a38e0 { int vt; char b[468]; };
struct M_1a38e0 { int m[16]; };
extern "C" int FUN_00130140(...);
extern "C" int FUN_00150eb0(...);
extern "C" int FUN_00130f60(...);
extern "C" int FUN_00134fb0(...);
extern "C" int FUN_001359e0(...);
extern "C" int FUN_0013aab0(...);
extern "C" int FUN_0014a040(...);
extern "C" int FUN_0014fd40(...);
extern "C" int FUN_001e4010(...);
extern "C" int FUN_002b9390(...);
extern "C" int D_005293c0[4];
extern "C" int g_igCommonTraversal_ctorTable[4];
extern "C" int g_igCommonTraversal_fieldTable[4];
extern "C" int DAT_0048c8f0[4];
extern "C" int DAT_0048c980[4];
extern "C" char g_igCommonTraversal_callbackList[];
extern "C" char igCommonTraversal_className[];
extern "C" igMetaObject *g_igCamera_metaObject[4];
typedef struct { int *vt; int w[15]; } Obj_1a4600;
extern "C" int DAT_0052a500[4];
extern "C" char igCamera_className[];
extern "C" int g_igCamera_ctorTable[4];
extern "C" int g_igCamera_fieldTable[4];
extern "C" int DAT_0048ca50[4];
extern "C" int DAT_0048ca70[4];
extern "C" int DAT_0048ca90[4];
extern "C" int DAT_0048ca98[4];
extern "C" int DAT_0048caa0[4];
extern "C" int text_CameraType[4];
extern "C" int DAT_00561ee0[4];
extern igMetaObject *g_igBoundingBoxesMaker_metaObject[4];
struct Obj_1a48c0 { int *vt; int w[11]; };
extern "C" int FUN_0013a880(...);
extern "C" int FUN_001489a0(...);
extern "C" int DAT_0052a4a0[4];
extern "C" char g_igBoundingBoxesMaker_callbackList[];
extern "C" char igBoundingBoxesMaker_className[];
extern "C" int FUN_002c8e50(...);
extern "C" int g_igBoundingBoxesMaker_ctorTable[4];
extern "C" int g_igBoundingBoxesMaker_fieldTable[4];
extern "C" int DAT_0048cb10[4];
extern "C" int DAT_0048cb30[4];
extern igMetaObject *g_igBlendMatrixSelect_metaObject[4];
struct Obj_1a4ba0 { int *vt; int f4; int f8; int f12; int f16; int f20; int f24; int f28; int f32; int f36; int f40; char sub1[64]; char sub2[64]; char pad[4]; };
extern "C" int DAT_0052a400[4];
extern "C" char g_igBlendMatrixSelect_callbackList[];
extern "C" char igBlendMatrixSelect_className[];
extern "C" int g_igBlendMatrixSelect_ctorTable[4];
extern "C" int g_igBlendMatrixSelect_fieldTable[4];
extern "C" int DAT_0048cb78[4];
extern "C" int DAT_0048cb88[4];
extern "C" igMetaObject *g_igBitMask_metaObject[4];
struct Obj_1a4e30 { int *vt; char pad[28]; };
extern "C" int DAT_0052a340[4];
extern "C" char igUnsignedIntList_GetPublishedMetaObject[];
extern "C" char igUnsignedIntList_Register[];
extern "C" char igBitMask_className[];
extern "C" int g_igUnsignedIntList_metaObject[4];
extern "C" int g_igBitMask_ctorTable[4];
extern "C" int g_igBitMask_fieldTable[4];
extern "C" int DAT_0048cba8[4];
extern "C" int DAT_0048cbb0[4];
extern igMetaObject *g_igBillboard_metaObject[4];
extern "C" int DAT_0052a2a0[4];
union U_1a4fd0 { int vt; int w[16]; void *p[16]; char b[64]; };
extern "C" char g_igBillboard_callbackList[];
extern "C" char igBillboard_className[];
extern "C" int g_igBillboard_ctorTable[4];
extern "C" int g_igBillboard_fieldTable[4];
extern "C" int DAT_0048cbe0[4];
extern "C" int DAT_0048cbf0[4];
extern igMetaObject *g_igNonRefCountedAttrStackManagerList_metaObject[4];
struct Obj_1a5260 { int *vt; char pad[28]; };
extern "C" int DAT_0052a230[4];
extern "C" char g_igNonRefCountedAttrStackManagerList_callbackList[];
extern "C" char igNonRefCountedAttrStackManagerList_className[];
extern "C" igMetaObject *g_igAttrStackManager_metaObject[4];
struct Obj_1a53d0 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; int w12; int w13; int w14; int w15; int w16; int w17; int w18; int w19; };
extern "C" int DAT_00529450[4];
extern "C" char g_igAttrStackManager_callbackList[];
extern "C" char igAttrStackManager_className[];
extern "C" int igIntMetaField_GetDefaultDescriptor(...);
extern "C" int g_igAttrStackManager_ctorTable[4];
extern "C" int g_igAttrStackManager_fieldTable[4];
extern "C" int DAT_0048cce0[4];
extern "C" int DAT_0048cd30[4];
extern "C" igMetaObject *g_igAttrStackList_metaObject[4];
struct Obj_1a59a0 { int *vt; char pad[28]; };
extern "C" int DAT_0052a1c0[4];
extern "C" char g_igAttrStackList_callbackList[];
extern "C" char igAttrStackList_className[];
extern igMetaObject *g_igAttrStack_metaObject[4];
extern "C" int DAT_0052a160[4];
union U_1a5b00 { int vt; int w[16]; void *p[16]; char b[64]; };
extern "C" char g_igAttrStack_callbackList[];
extern "C" char igAttrStack_className[];
extern "C" int g_igAttrStack_ctorTable[4];
extern "C" int g_igAttrStack_fieldTable[4];
extern "C" int DAT_0048cdd0[4];
extern "C" int DAT_0048cdf0[4];
typedef struct { int *vt; int w[7]; int s; } Obj_1a5e10;
extern "C" char g_igAttrSet_callbackList[];
extern "C" char igAttrSet_className[];
extern "C" int g_igAttrSet_ctorTable[4];
extern "C" int g_igAttrSet_fieldTable[4];
extern "C" int DAT_0048ce28[4];
extern "C" int DAT_0048ce30[4];
extern "C" igMetaObject *g_igAppearanceList_metaObject[4];
struct Obj_1a6080 { int *vt; char pad[28]; };
extern "C" int DAT_0052a0f0[4];
extern "C" char g_igAppearanceList_callbackList[];
extern "C" char igAppearanceList_className[];
extern "C" igMetaObject *g_igAppearance_metaObject[4];
struct Obj_1a61f0 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; };
extern "C" int FUN_00131bc0(...);
extern "C" int DAT_0052a090[4];
extern "C" char g_igAppearance_callbackList[];
extern "C" char igAppearance_className[];
extern "C" int g_igAppearance_ctorTable[4];
extern "C" int g_igAppearance_fieldTable[4];
extern "C" int DAT_0048cea0[4];
extern "C" int DAT_0048cec0[4];
extern "C" igMetaObject *g_igAnimationSystem_metaObject[4];
extern "C" char g_igAnimationSystem_callbackList[];
extern "C" char igAnimationSystem_className[];
extern "C" int g_igAnimationSystem_ctorTable[4];
extern "C" int g_igAnimationSystem_fieldTable[4];
extern "C" int DAT_0048cef0[4];
extern "C" int DAT_0048cef8[4];
extern "C" int g_igAnimationStatePool_metaObject[4];
extern "C" int DAT_0052a020[4];
extern "C" char g_igAnimationStatePool_callbackList[];
extern "C" char igAnimationStatePool_className[];
extern "C" igMetaObject *g_igAnimationStateList_metaObject[4];
extern "C" int DAT_00529fb0[4];
extern "C" char g_igAnimationStateList_callbackList[];
extern "C" char igAnimationStateList_className[];
extern "C" int DAT_0048cf10[4];
extern "C" int DAT_0048cf20[4];
extern "C" int text_Status[4];
extern "C" int DAT_005620e8[4];
extern "C" int DAT_0048cf30[4];
extern "C" int DAT_0048cf50[4];
extern "C" int text_TransitionMode[4];
extern "C" int DAT_005620f0[4];
extern "C" int DAT_0048cf68[4];
extern "C" int DAT_0048cf78[4];
extern "C" int text_CombineMode[4];
extern "C" int DAT_005620f8[4];
union U_1a6c90 { int vt; int w[37]; char b[148]; };
extern "C" char g_igAnimationState_callbackList[];
extern "C" char igAnimationState_className[];
extern "C" int g_igAnimationState_ctorTable[4];
extern "C" int g_igAnimationState_fieldTable[4];
extern "C" int DAT_0048d070[4];
extern "C" int DAT_0048d0e0[4];
extern "C" int DAT_0048d148[4];
extern "C" int DAT_0048d150[4];
extern "C" int DAT_0048d158[4];
extern "C" char igAnimationSequence_className[];
extern "C" char igAnimationHierarchy_className[];
extern "C" int FUN_00187b10(...);
extern "C" int g_igAnimationHierarchy_ctorTable[4];
extern "C" int g_igAnimationHierarchy_fieldTable[4];
extern "C" int DAT_0048d170[4];
extern "C" int DAT_0048d178[4];
extern "C" igMetaObject *g_igAnimationModifierList_metaObject[4];
struct Obj_1a7370 { int *vt; char pad[28]; };
extern "C" int DAT_00529f40[4];
extern "C" char g_igAnimationModifierList_callbackList[];
extern "C" char igAnimationModifierList_className[];
extern "C" int DAT_0048d190[4];
extern "C" int DAT_0048d1a0[4];
extern "C" int text_ModifierType[4];
extern "C" int DAT_005621f8[4];
extern igMetaObject *g_igAnimationModifier_metaObject[4];
struct Obj_1a74f0 { int *vt; char pad[8]; char *m; char pad2[16]; };
extern "C" int DAT_00529ee0[4];
extern "C" char g_igAnimationModifier_callbackList[];
extern "C" char igAnimationModifier_className[];
extern "C" int g_igAnimationModifier_ctorTable[4];
extern "C" int g_igAnimationModifier_fieldTable[4];
extern "C" int DAT_0048d1d8[4];
extern "C" int DAT_0048d1e8[4];
extern "C" int DAT_0048d1f8[4];
extern "C" igMetaObject *g_igAnimationDatabase_metaObject[4];
struct W_1a7820 { int *vt; int f[11]; };
extern "C" int DAT_005295c0[4];
typedef struct S_temp_a0_1a7980 { char pad4[4]; int f4; } S_temp_a0_1a7980;
extern "C" char g_igAnimationDatabase_callbackList[];
extern "C" char igAnimationDatabase_className[];
extern "C" int g_igAnimationDatabase_ctorTable[4];
extern "C" int g_igAnimationDatabase_fieldTable[4];
extern "C" int DAT_0048d260[4];
extern "C" int DAT_0048d280[4];
extern "C" int g_igAnimationCombinerBoneInfoPool_metaObject[4];
struct Obj_1a7d50 { int *vt; char pad[28]; };
extern "C" int DAT_00529e70[4];
extern "C" char g_igAnimationCombinerBoneInfoPool_callbackList[];
extern "C" char igAnimationCombinerBoneInfoPool_className[];
extern "C" igMetaObject *g_igAnimationCombinerBoneInfoListList_metaObject[4];
struct Obj_1a7ec0 { int *vt; char pad[28]; };
extern "C" int DAT_00529e00[4];
extern "C" char g_igAnimationCombinerBoneInfoListList_callbackList[];
extern "C" char igAnimationCombinerBoneInfoListList_className[];
extern igMetaObject *g_igAnimationCombinerBoneInfoList_metaObject[4];
struct Obj_1a7fe0 { int *vt; char pad[28]; };
extern "C" int DAT_00529d90[4];
extern "C" char g_igAnimationCombinerBoneInfoList_callbackList[];
extern "C" char igAnimationCombinerBoneInfoList_className[];
extern "C" igMetaObject *g_igAnimationCombinerBoneInfo_metaObject[4];
struct Obj_1a8140 { int *vt; char p4[8]; int *m12; int *m16; char pe[44]; };
extern "C" int DAT_00529d30[4];
extern "C" char g_igAnimationCombinerBoneInfo_callbackList[];
extern "C" char igAnimationCombinerBoneInfo_className[];
extern "C" int g_igAnimationCombinerBoneInfo_ctorTable[4];
extern "C" int g_igAnimationCombinerBoneInfo_fieldTable[4];
extern "C" int DAT_0048d300[4];
extern "C" int DAT_0048d320[4];
extern "C" igMetaObject *g_igAnimationCombinerList_metaObject[4];
struct Obj_1a8450 { int *vt; char pad[28]; };
extern "C" int DAT_00529cc0[4];
extern "C" char g_igAnimationCombinerList_callbackList[];
extern "C" char igAnimationCombinerList_className[];
extern int g_igAnimationCombiner_metaObject[4];
struct Obj_1a8570 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; int w12; int w13; int w14; int w15; int w16; int w17; int w18; int w19; int w20; int w21; int w22; int w23; };
extern "C" int DAT_00529630[4];
extern "C" int DAT_00529c40[4];
struct S_1a8620 {
    void *f0;
    char pad0[4];
    void *f8;
    igObject *fc;
};
extern "C" char igAnimationSystem_GetPublishedMetaObject[];
extern "C" char g_igAnimationCombiner_callbackList[];
extern "C" char igAnimationCombiner_className[];
extern "C" int g_igAnimationCombiner_metaObject[4];
extern "C" int FUN_00187520(...);
extern "C" int g_igAnimationCombiner_ctorTable[4];
extern "C" int g_igAnimationCombiner_fieldTable[4];
extern "C" int DAT_0048d3e0[4];
extern "C" int DAT_0048d420[4];
struct Fld_1a88b0 { char p0[38]; char f38; char p39[13]; char f52; char f53; char p54[2]; int f56; int f60; char f64; char f65; };
extern "C" igMetaObject *g_igAnimationBindingList_metaObject[4];
struct Obj_1a8b60 { int *vt; char pad[28]; };
extern "C" int DAT_00529bd0[4];
extern "C" char g_igAnimationBindingList_callbackList[];
extern "C" char igAnimationBindingList_className[];
extern igMetaObject *g_igAnimationBinding_metaObject[4];
extern "C" int DAT_00529b70[4];
extern "C" char g_igAnimationBinding_callbackList[];
extern "C" char igAnimationBinding_className[];
extern "C" int g_igAnimationBinding_ctorTable[4];
extern "C" int g_igAnimationBinding_fieldTable[4];
extern "C" int DAT_0048d4b0[4];
extern "C" int DAT_0048d4d0[4];
extern "C" igMetaObject *g_igAnimationList_metaObject[4];
struct Obj_1a9020 { int *vt; char pad[28]; };
extern "C" int DAT_00529b00[4];
extern "C" char g_igAnimationList_callbackList[];
extern "C" char igAnimationList_className[];
extern "C" igMetaObject *g_igAnimation_metaObject[4];
extern "C" int DAT_0052a9b0[4];
union U_1a91d0 { int vt; char b[64]; };
extern "C" char g_igAnimation_callbackList[];
extern "C" char igAnimation_className[];
extern "C" int g_igAnimation_ctorTable[4];
extern "C" int g_igAnimation_fieldTable[4];
extern "C" int DAT_0048d550[4];
extern "C" int DAT_0048d570[4];
extern "C" igMetaObject *g_igAnimationTransitionDefinitionList_metaObject[4];
extern "C" int DAT_00529a90[4];
extern "C" char g_igAnimationTransitionDefinitionList_callbackList[];
extern "C" char igAnimationTransitionDefinitionList_className[];
extern igMetaObject *g_igAnimationTransitionDefinition_metaObject[4];
extern "C" int DAT_00529a30[4];
extern "C" char g_igAnimationTransitionDefinition_callbackList[];
extern "C" char igAnimationTransitionDefinition_className[];
extern "C" int g_igAnimationTransitionDefinition_ctorTable[4];
extern "C" int g_igAnimationTransitionDefinition_fieldTable[4];
extern "C" int DAT_0048d5d0[4];
extern "C" int DAT_0048d5e0[4];
extern "C" igMetaObject *g_igAnimationTransitionPointList_metaObject[4];
struct Obj_1a98d0 { int *vt; char pad[28]; };
extern "C" int DAT_005299c0[4];
extern "C" char g_igAnimationTransitionPointList_callbackList[];
extern "C" char igAnimationTransitionPointList_className[];
extern igMetaObject *g_igAnimationTransitionPoint_metaObject[4];
typedef struct Q { char pad4[4]; int f4; } Q;
typedef struct { int *vt; int w[3]; Q *s; } Obj_1a99f0;
extern "C" int DAT_00529960[4];
extern "C" char g_igAnimationTransitionPoint_callbackList[];
extern "C" char igAnimationTransitionPoint_className[];
extern "C" int g_igAnimationTransitionPoint_ctorTable[4];
extern "C" int g_igAnimationTransitionPoint_fieldTable[4];
extern "C" int DAT_0048d610[4];
extern "C" int DAT_0048d618[4];
extern "C" igMetaObject *g_igAnimationTransitionParams_metaObject[4];
struct Obj_1a9c50 { int *vt; char pad[28]; };
extern "C" int DAT_00529900[4];
extern "C" char igAnimationTransitionParams_className[];
extern "C" int g_igAnimationTransitionParams_ctorTable[4];
extern "C" int g_igAnimationTransitionParams_fieldTable[4];
extern "C" int DAT_0048d640[4];
extern "C" int DAT_0048d650[4];
extern "C" igMetaObject *g_igAnimationTrackList_metaObject[4];
struct Obj_1a9e30 { int *vt; char pad[28]; };
extern "C" int DAT_00529890[4];
extern "C" char g_igAnimationTrackList_callbackList[];
extern "C" char igAnimationTrackList_className[];
extern igMetaObject *g_igAnimationTrack_metaObject[4];
extern "C" int DAT_00529830[4];
union U_1a9f50 { int vt; char b[48]; };
extern "C" char g_igAnimationTrack_callbackList[];
extern "C" char igAnimationTrack_className[];
extern "C" int g_igAnimationTrack_ctorTable[4];
extern "C" int g_igAnimationTrack_fieldTable[4];
extern "C" int DAT_0048d690[4];
extern "C" int DAT_0048d6a0[4];
extern igMetaObject *g_igActorInfo_metaObject[4];
struct Obj_1aa1b0 { int *vt; int w1; int w2; int w3; int w4; int w5; int w6; int w7; int w8; int w9; int w10; int w11; };
extern "C" int DAT_005297c0[4];
extern "C" char g_igActorInfo_callbackList[];
extern "C" char igActorInfo_className[];
extern "C" int g_igActorInfo_ctorTable[4];
extern "C" int g_igActorInfo_fieldTable[4];
extern "C" int DAT_0048d710[4];
extern "C" int DAT_0048d730[4];
extern "C" igMetaObject *g_igActorList_metaObject[4];
struct Obj_1aa660 { int *vt; char pad[28]; };
extern "C" int DAT_00529750[4];
extern "C" char g_igActorList_callbackList[];
extern "C" char igActorList_className[];
extern "C" igMetaObject *g_igActor_metaObject[4];
extern "C" int DAT_005296b0[4];
struct igObjectView { int *vtable; unsigned int refCount; igObjectView(); };
struct igMatrix44fView { float m[16]; igMatrix44fView(); };
struct igActorVtable { igActorVtable(int **slot) { *slot = DAT_005296b0; } };
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
    ~igActorView() { vtable = DAT_005296b0; }
};
extern "C" char g_igActor_callbackList[];
extern "C" char igActor_className[];
struct ActorVectorWords { int x; int y; int z; int w; };
struct ActorMatrixWords { int m[16]; };
extern "C" int g_igActor_ctorTable[4];
extern "C" int g_igActor_fieldTable[4];
extern "C" int DAT_0048d7f0[4];
extern "C" int DAT_0048d830[4];
extern igMetaObject *g_igPsx2EnvironmentMapShader_metaObject[4];
extern "C" int DAT_00528170[4];
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
                    igObject_Destroy(object);
            }
        }
    }
};
typedef struct S_temp_a0_1ab380 { char pad4[4]; int f4; } S_temp_a0_1ab380;
extern "C" char igEnvironmentMapShader2_GetPublishedMetaObject[];
extern "C" char g_igPsx2EnvironmentMapShader_callbackList[];
extern "C" char igPsx2EnvironmentMapShader_className[];
extern "C" int FUN_001331a0(...);
extern "C" int FUN_001351d0(...);
extern "C" int FUN_00139f10(...);
extern "C" int g_igPsx2EnvironmentMapShader_ctorTable[4];
extern "C" int g_igPsx2EnvironmentMapShader_fieldTable[4];
extern "C" int DAT_0048d8a0[4];
extern "C" int DAT_0048d8b0[4];
extern "C" int strcmp(...);
extern "C" int emptyString[4];
struct E { char pad[8]; int *f8; };
struct L { char pad[8]; int count; char pad1[4]; E **data; };
struct S_1ab6c0 { char pad[20]; L *f20; };
typedef struct S1_1ab770 { char pad4[4]; int f4; } S1_1ab770;
extern "C" int ObjectList_AppendRetained(...);
extern "C" int igObject_GetAllocator(...);
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
extern "C" void *igObject_AllocateStorage(...);
typedef struct AnimationPoolObject { int w0; int references; char pad[20]; char f28; } AnimationPoolObject;
extern "C" int FUN_00306e50(...);
extern "C" int text_cleanCombinerStates[4];
extern "C" int kIGMemoryPoolHandleSystem[4];
extern "C" char GPR_00554b84;
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
extern "C" int igMatrix44f_GetQuaternion(...);
extern "C" int igMatrix44f_GetTranslation(...);
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
extern "C" int Gap__Core__igObject__vfunc_15(...);
extern "C" void igMetaField_AllocateArray(int *, int, CombinerView *, int, int);
extern "C" int DAT_00562300;
extern "C" int DAT_00562308;
typedef struct IL { int p0, p1; int count; int cap; int *data; } IL;
typedef struct X_1ad5c0 { char p0[12]; int w12; } X_1ad5c0;
typedef struct It { int p0; int refs; char p8[4]; X_1ad5c0 *x; char p16[32]; int prio; } It;
typedef struct Ls { int p0, p1; int count; int cap; It **data; } Ls;
typedef struct LL { int p0, p1; int count; int cap; Ls **data; } LL;
typedef struct A_1ad5c0 { char p0[48]; LL *ll; IL *il; char p56[24]; char b80; } A_1ad5c0;
extern "C" int List_InsertWords(...);
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
extern "C" int List_RemoveWordAt(...);
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
extern "C" int Gap__Core__igObject__userDestruct(...);
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
extern "C" char text_trackList[];
extern "C" char DAT_004e44f8[];
extern "C" char DAT_004e4500[];
extern "C" int *DAT_00562560[4];
extern "C" int g_igObjectRefMetaField_metaObject[4];
extern "C" int g_propertyNameField[4];
extern "C" int sscanf(...);
extern "C" int strlen(...);
extern "C" int strncmp(char *, char *, int);
extern "C" int igObject_IsKindOf(...);
extern "C" int igProperty_FindByName(...);
struct AnimDbRecord { int vtable; unsigned int references; const char *name; };
extern igMetaObject *g_igNamedObject_metaObject;
extern "C" int FUN_002e2d30(...);
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
                igObject_Destroy(object);
            }
        }
    }
};
struct AnimDbObject : public igObject { int _name; int _source; int _f16; int _f20; };
struct AnimDbList { char pad[8]; int _count; int _capacity; AnimDbObject **_data; };
struct AnimDbDirectory { char pad[8]; int _count; };
struct AnimDbField { char pad[8]; int _offset; };
struct AnimDbRec { char pad[8]; int _name; AnimDbDirectory *_directory; char pad16[4]; AnimDbList *_skeletonList; AnimDbList *_animationList; AnimDbList *_skinList; AnimDbList *_appearanceList; AnimDbList *_combinerList; };
extern char text_s_s_d[];
extern int DAT_00586730;
extern AnimDbField *DAT_00562568;
extern "C" int FUN_002d86b0(AnimDbDirectory *, int, AnimDbObject *);
extern "C" int sprintf(char *, const char *, ...);
extern long long DAT_0048d8c0;
extern float DAT_0048d8c8;
extern long long DAT_00562570;
extern "C" long long __fixsfdi(float);
extern char *g_stringObjEmptyText[4];
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
extern "C" int ObjectList_RemoveAllRetained(...);
class V112 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void vX(); };
struct L_1af7e0 { char pad8[8]; unsigned int cnt; char pad12[4]; V112 **arr; };
struct S_1af7e0 { char pad32[32]; L_1af7e0 *l; };
struct A_1af890 { int p0; int p1; int p2; int p3; int *arr; };
struct B { int p0; int p1; int f8; int p3; int p4; int f20; };
struct O_1af890 { int p0; int p1; int p2; int n; struct A_1af890 *l16; int p5; struct B *b24; struct B *b28; char pad[12]; struct B *b44; char pad2[16]; struct B *b64; };
struct L_1af920 { char pad8[8]; int n; int cap; int *data; };
struct Z { char pad56[56]; int f56; };
extern "C" int Gap__Core__igObject__userConstruct(...);
extern "C" int text_simpleLightManagementState[4];
extern "C" struct L_1af920 *DAT_00562580[4];
extern "C" int kIGMemoryPoolHandleAttribute[4];
extern "C" unsigned char g_useOwnerAllocator;
extern "C" void FUN_002ed5c0(void *);
struct K { void *p; K(void *x) { p = x; } ~K() { } static void operator delete(void *q) { FUN_002ed5c0(q); } };
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
extern "C" RefObj *FUN_002c8e10(void *);
extern "C" void *igAttr_GetMetaObject(...);
extern "C" int FUN_002fe290(...);
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
extern "C" int *FUN_00300e50(void *, int *, int);
extern "C" int ObjectList_ResizeRetained(...);
struct Obj_1b0000 { int w0; int references; };
struct List { int pad0[2]; int count; int pad1; Obj_1b0000 **data; };
struct T_1b0000 {
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
    Obj_1b0000 *f52;
    Obj_1b0000 *f56;
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
extern "C" G *g_igLightStateAttr_metaObject[4];
struct AttrObjectStack : igTDataList<igObject *> {
    int _default;
    int _cachedOverride;
    void (*_popProc)(igObject *, int);
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
struct A_1b1490 { char pad[8]; char f8; char pad2[15]; struct L_1b1490 *f24; struct L_1b1490 *f28; };
struct B_1b1490 { char pad[32]; unsigned char f32; char pad2[7]; unsigned char f40; };
extern "C" int memset(...);
struct igBitMaskWords { char pad8[8]; int _count; int _capacity; unsigned int *_data; unsigned int _bitCount;
    inline void setCount(int n);
    inline void setWord(int i, const unsigned int &v);
    inline unsigned int getWord(unsigned int i) { return _data[i]; }
};
extern unsigned int DAT_0048d8d0;
struct V3_1b21d0 { float x, y, z; };
struct A_1b21d0 { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual unsigned v34(); char pad[28]; unsigned f32; };
extern "C" int igVertexArray2__FindVertexData(...);
extern "C" int g_igVec3fList_metaObject[4];
class VC_100_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int *vX(); };
struct V3_1b23e0 { float x, y, z; };
struct X_1b23e0 : public igObject { V3_1b23e0 a; V3_1b23e0 b; };
struct Y { char pad[12]; VC_100_0 *f12; };
extern "C" void *igAABox_CreateInstance(...);
extern "C" int igVolume_ExtendBy(...);
extern "C" int FUN_001b1fa0(...);
struct V3_1b24d0 { float x, y, z; };
struct BoundsObject : public igObject { V3_1b24d0 min; V3_1b24d0 max; };
extern "C" int DAT_0055f158[4];
extern "C" int g_igGeometryAttr_metaObject[4];
class Elem { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); };
struct List_1b2600 { int pad0[2]; int count; int pad1; Elem **data; };
struct Owner { char pad[32]; List_1b2600 *list; };
extern "C" int igAABox_Transform(...);
class DW4VC_156_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual int vX(int); };
class V_1b2750 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void vX(void *, int); };
extern "C" void *FUN_00301000(void *);
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
                igObject_Destroy(object);
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
struct TravFunctionTable { char pad[16]; int *_data; };
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
extern "C" igMetaObject *g_igModelViewMatrixAttr_metaObject[4];
extern "C" int DAT_005612d8[4];
extern "C" int DAT_005612e0;
extern "C" int DAT_00561570;
extern "C" int DAT_00561578[4];
extern "C" int DAT_005615d0;
extern "C" int DAT_00561860[4];
extern "C" int DAT_00561868;
extern "C" int DAT_00561870;
extern "C" int DAT_00561878;
extern "C" int g_unlinkedTransformClass_metaObject[4];
extern "C" int DAT_00561908;
extern "C" int DAT_00561910;
extern "C" int DAT_00561920;
extern "C" int DAT_00561bd8[4];
extern "C" int DAT_00561ca0[4];
extern "C" int DAT_00561e98[4];
extern "C" int DAT_00561ee8[4];
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
extern "C" TravFunctionTable *DAT_00562640[4];
extern "C" int FUN_00130830(...);
extern "C" int FUN_00130a70(...);
extern "C" int FUN_00130cf0(...);
extern "C" int FUN_001318f0(...);
extern "C" int FUN_00132a00(...);
extern "C" int FUN_001357e0(...);
extern "C" int FUN_0013b110(...);
extern "C" int FUN_00140c00(...);
extern "C" int FUN_00157200(...);
extern "C" int FUN_001b3030(...);
extern "C" int FUN_001dc610(...);
extern "C" void *FUN_002fe300(...);
extern "C" int igMetaObject_CountTree(...);
extern "C" igMetaObject *igTextureBindAttr_GetMetaObject(...);
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
extern "C" int FUN_00191910(...);
extern "C" float atanf(float);
extern "C" float tanf(float);
class C_1b6e20 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void v92(); virtual void v96(); char pad[124]; unsigned char f128; };
struct S20 { char p[20]; int f20; };
struct S8 { char p[8]; int f8; };
struct A_1b6e20 { char p[48]; char f48; char p1[3]; C_1b6e20 *f52; char p2[12]; C_1b6e20 *f68; S20 *f72; S20 *f76; S20 *f80; S20 *f84; S20 *f88; S20 *f92; S20 *f96; char p3[148]; S8 *f248; S8 *f252; char p4[12]; S20 *f268; };
extern "C" int igMatrix44f_Copy(...);
extern "C" int igMatrix44f_Invert(...);
extern "C" int g_igAttr_metaObject[4];
typedef struct R_1b6f30 { int w0; int refs; } R_1b6f30;
typedef struct A_1b6f30 { char pad[32]; R_1b6f30 *f32; R_1b6f30 *f36; char pad40[12]; int f52; } A_1b6f30;
typedef struct R_1b7010 : public igObject { struct R_1b7010 *f8; } R_1b7010;
typedef struct O_1b7010 { char pad[32]; R_1b7010 *f32; R_1b7010 *f36; char pad2[20]; R_1b7010 *f60; } O_1b7010;
extern "C" R_1b7010 *FUN_00130020(void *);
extern "C" R_1b7010 *FUN_00137ab0(void *);
extern "C" R_1b7010 *FUN_00149c30(void *);
extern "C" R_1b7010 *FUN_0014f2c0(void *);
extern "C" int FUN_001356b0(...);
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
extern "C" igMetaObject *igClearAttr_GetMetaObject(void);
extern "C" igMetaObject *igProjectionMatrixAttr_GetMetaObject(void);
struct L_1b75b0 { int p0; int p1; int size; int cap; long long *data; };
struct Ent_1b7630 { int pad[2]; int count; int pad2; int *items; int pad3[2]; void (*fn)(int, int); };
struct Tab { int pad[4]; Ent_1b7630 **ents; };
struct Mgr { int pad[4]; Tab *tab; int pad2[7]; int arg; int pad3[4]; int *idx; };
/* matching construct: dummy-virtual view so ->f31() dispatches through vtable slot 31 of the traversal */
struct TravView { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void f31(); };
extern "C" void *igStringObj_Create(...);
extern "C" int igStringObj_Set(...);
extern "C" int igStringObj_ToLower(igObject *);
extern "C" int List_BinarySearchWords(int, void *, void *);
extern "C" int FUN_002d6e60(int, void *, void *);
extern "C" int kIGMemoryPoolHandleTemporary[4];
struct SegmentOverrideRef { igObject *p; inline void retain() { if (p != 0) p->_refCount = p->_refCount + 1; } inline void set(igObject *o) { p = o; retain(); } };
struct SegmentStackList { char pad8[8]; int _count; int _capacity; igObject **_data; int count() const { return _count; } };
extern "C" int FUN_0030bfa0(...);
extern "C" int strcasecmp(...);
struct igGroupMaskView { char p[28]; igNodeList *_childList; igBitMask *_mask; };
extern "C" int FUN_001b9530(...);
class DW4VC_104_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual int vX(); };
class C_1b7ce0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual int vX(); char pad4[48]; int f52; char pad56[180]; int f236; };
struct A_1b7ce0 { char pad20[20]; unsigned int f20; };
extern "C" float sqrtf(float);
struct V_1b7d70 { float x, y, z, w; };
extern "C" int Vec3f_TransformProjective(...);
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
extern ActorMeta *g_igActor_transformMetaField[4];
extern "C" int FUN_001904f0(...);
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
extern "C" int FUN_001b1aa0(...);
extern "C" int DAT_004e0ef0[4];
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
extern "C" LightFieldMeta *g_igLightAttr_directionMetaField[4];
extern "C" int Vec3f_TransformDirection(...);
extern "C" int FUN_001be190(...);
extern "C" int List_AppendWords(...);
struct L_1b9fc0 { char p8[8]; int n; char p12[4]; int *data; };
struct B_1b9fc0 { char p32[32]; struct L_1b9fc0 *f32; };
struct A_1b9fc0 { char p52[52]; int f52; };
extern "C" int FUN_001b06f0(...);
typedef struct { float x, y, z; } CullVec3;
typedef struct CullTraversalView { char _pad0[52]; CullAttrState *_state; } CullTraversalView;
typedef struct CullNodeView { char _pad0[52]; CullVec3 _center; } CullNodeView;
typedef struct S_1ba1a0 { char pad52[52]; int f52; char pad56[176]; int f232; } S_1ba1a0;
extern "C" int FUN_001b4c40(...);
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
extern "C" void igTimeAttr_CreateInstance(...);
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
extern "C" void FUN_00139c10(void);
extern "C" int FUN_00300f50(...);
extern "C" char *FUN_00300db0(MatrixFrame *, int, int);
struct S_1bafb0 { char pad[8]; int *f8; };
extern "C" Q *DAT_00562648[4];
typedef struct C_1bb280 { char pad[28]; Q *f28; } C_1bb280;
typedef struct RefCountedEntry { int w0; int ref; } RefCountedEntry;
typedef struct RefCountedEntryList { char pad0[8]; int cnt; int pad12; RefCountedEntry **data; } RefCountedEntryList;
class igCompileTraversalVSlots { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual int slot31(); };
extern "C" void FUN_001bc1e0(void);
struct T_1bb880 : public igVirtualObject { virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual int setMatrix(int); int f8; T_1bb880 *f12; char p[16]; int f32; };
struct E_1bb880 { char p[20]; void *f20; };
struct L1 { char p[16]; E_1bb880 **f16; };
struct L0 { char p[16]; L1 *f16; char q[48]; int *f68; };
struct G_1bb880 { char p[8]; int f8; };
extern "C" G_1bb880 *g_igClearAttr_metaObject[4];
class VC104 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual int vX(int, int); };
class VC128L { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual int vX(long long); };
class DW4VC_132_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual int vX(); };
extern "C" int FUN_001bbb30(int, int);
typedef struct X_1bce40 { char pad[4]; int f4; int f8; } X_1bce40;
typedef struct A_1bce40 { char pad[52]; int f52; char pad2[416]; int f472; int f476; } A_1bce40;
struct Obj_1bcf70 { int w0; unsigned refs; int p8; int f12; int *f16; int f20; unsigned f24; };
extern "C" void *FUN_00139990(...);
struct SL { char p[8]; int count; char p2[4]; int *data; };
struct B_1bcf70 { char p[40]; SL *f40; };
struct A_1bcf70 { char p[52]; int f52; char q[440]; char f496; char r[7]; int f504; };
class DW4VC_124_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual int vX(); };
extern "C" int g_igDisplayListAttr_metaObject[4];
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
    virtual int getMeta();
    unsigned int _refCount;
    char _pad8[16];
    RemapIndexList *_indices;
};
struct RemapObjectList { int _vtable; unsigned int _refCount; int _count; int _capacity; RemapObject **_data; };
struct RemapTable { int _vtable; unsigned int _refCount; int _pad8; void *_storage; int *_data; int _count; unsigned int _capacity; };
struct RemapEntry { int _vtable; unsigned int _refCount; void *_target; RemapObject **_slot; };
struct RemapContext { char _pad0[480]; RemapIndexList *_pool; };
struct RemapOwner { char _pad0[32]; RemapObjectList *_items; char _pad24[12]; RemapObjectList *_entries; char _pad34[32]; RemapObject *_fallback; };
extern int g_igVertexBlendMatrixListAttr_metaObject[4];
extern int g_igBlendMatrixPaletteAttr_metaObject[4];
extern int g_igMatrixOptStateAttr_metaObject[4];
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
extern "C" QSDataList *FUN_002c9ff0(int);
extern "C" int FUN_001e5f00(void *, int *, float *, float *);
extern "C" int FUN_001e6130(void *, int *, float *, float *);
extern "C" void Gap__Sg__igCompressedAnimationSequenceQS__vfunc_44(QSSequenceView *arg0, QSSourceSequence *arg1);
struct M_1bfa60 { int pad[2]; int count; };
struct O_1bfa60 { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31(); virtual void v32(); virtual int v33(); virtual void v34(); virtual void v35(); virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39(); virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43(); virtual void v44(int,int*); virtual void v45(int*,int,int,float); virtual void v46(int*,int,int,float);
 int p0[3]; M_1bfa60 *m; int p1[8]; int idx; unsigned char flags; };
extern "C" void FUN_001bf7d0(QSSequenceView *o, unsigned char *before, unsigned char *after, int *key0, int *key1, float *t0, float *t1, long long time);
extern "C" int FUN_00192810(...);
extern "C" int igMatrix44f_SetTranslation(...);
struct M_1bfc70 { int pad[2]; int count; };
struct O_1bfc70 { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35(); virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39(); virtual long long v40(int);
 int p0[3]; M_1bfc70 *m; int p1[8]; int cur; };
extern "C" void FUN_00192ab0(float *, float, void *, void *);
extern "C" void Quaternion_Lerp(float *, float, void *, void *);
struct S_1bfe90 { char pad[58]; unsigned char f58; };
extern "C" void Vec3_Lerp(float *, float, void *, void *);
class DW4VC_184_2 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual int vX(int, int *); };
class V192 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual int vX(int, int, int, float); };
struct L_1c0010 { char pad8[8]; int cnt; };
struct S_1c0010 { V192 *vt; char pad4[12]; L_1c0010 *f16; };
struct L_1c00e0 { char pad8[8]; int n; };
class VC_1c00e0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual int v140(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual int v184(int, int); virtual void v188(int, int, int, float); virtual void v192(int, int, int, float); };
struct O_1c00e0 : VC_1c00e0 { char pad4[12]; L_1c00e0 *f16; };
struct Obj_1c03a0 { char p0[16]; float a[4]; char p1[16]; long long f48; char p2[4]; int f60; float f64; };
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
extern "C" int FUN_001931b0(...);
extern "C" void DepthOfField_UpdateProjections(DepthOfFieldNode *);
extern "C" int FUN_001db720(...);
extern "C" long long fptodp(float);
extern "C" Obj_1c03a0 *DAT_00562660[4];
extern "C" void *DAT_00562668[4];
extern "C" void *DAT_00562670[4];
extern "C" void *DAT_00562680[4];
extern "C" void *DAT_00562688[4];
extern "C" void *DAT_00562690[4];
extern "C" void *DAT_00562698[4];
extern "C" void *DAT_005626a0[4];
extern "C" void *DAT_005626a8[4];
extern "C" void *g_depthOfFieldNearProjectionAttr[4];
extern "C" void *g_depthOfFieldFarProjectionAttr[4];
extern "C" void *DAT_005626c0[4];
extern "C" void *DAT_005626c8[4];
extern "C" void *DAT_005626d0[4];
extern "C" void *DAT_005626d8[4];
extern "C" int DAT_00562678[4];
extern "C" unsigned char GPR_00554984;
extern "C" unsigned char GPR_00554b8c;
extern "C" int thunk_FUN_00280a00(...);
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
extern float g_enbayaPlayOnceEndOffset[4];
extern "C" void FUN_0027fa60(EnbayaDecoderView *, float, int, EnbayaKeyView * *, EnbayaKeyView * *);
extern "C" float DAT_005626e8[4];
extern "C" float DAT_005626f0[4];
extern "C" int DAT_005626f8[4];
extern "C" float DAT_00562700[4];
extern "C" int FUN_002808f0(...);
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
                if (r->u.b.cnt == 0) igObject_Destroy(r);
            }
        }
        int n2 = count;
        for (int i = 0; i < n2; i++) data[i] = 0;
        count = 0;
    }
};
struct Meta { char p0[60]; void *f60; };
extern void *DAT_00562728[4];
extern unsigned char GPR_00554b90;
extern char DAT_00560000[];
extern "C" int FUN_0027ef50(int, int, unsigned char);
extern "C" unsigned char GPR_00554b94;
extern "C" int FUN_001c16a0(...);
extern "C" int FUN_002800d0(...);
extern "C" int FUN_003064b0(...);
extern "C" int igRegistry_GetKeyName(...);
extern "C" int FUN_003065f0(...);
extern "C" int Gap__Core__igObject__resetFields(...);
extern "C" int text_enbayaContextPool_d[4];
extern "C" int Gap__Core__igObject__destructFields(void *);
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
extern "C" PoolObject *FUN_002c9130(int);
extern "C" int DAT_0048da08[4];
struct PoolListHolder { PoolObject *p; ~PoolListHolder() {} };
typedef struct L_1c1a80 { char p0[8]; int n; int p1; int *d; } L_1c1a80;
typedef struct T_1c1a80 { char p0[8]; L_1c1a80 *f8; L_1c1a80 *f12; } T_1c1a80;
extern "C" int FUN_001c1950(T_1c1a80 *, int, int, int);
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
extern "C" int igMetaObject_CountInstances(...);
struct Ref_1c1c60 { int w0; int rc; };
struct List_1c1c60 { int w0; int w4; int count; int cap; Ref_1c1c60 **data; };
class T_1c1c60 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();  virtual int vA(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47();  virtual void vB();
    char pad[60]; List_1c1c60 *f64; List_1c1c60 *f68; };
extern "C" int igTextureStateAttr_CreateInstance(...);
extern "C" int igBlendStateAttr_CreateInstance(...);
extern "C" int FUN_0013b270(...);
extern "C" void * *DAT_00562740[4];
struct T_1c1e10 { int w0; int refs; };
class DW4VC_100_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int vX(int); };
class DW4VC_128_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual int vX(int); };
class Obj_1c20b0;
struct PropertySet { char pad[56]; int props; };
extern "C" int FUN_00132810(...);
extern "C" int FUN_001325a0(...);
extern "C" int FUN_00131c60(int);
extern "C" int thunk_FUN_00306e50(int, int, char *, unsigned char *, int, int);
extern "C" char text_envMapDiscardUnusedImages[];
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
extern "C" int FUN_001c31e0(...);
struct Obj_1c3090 { int w0; unsigned refs; };
struct X_1c3090 { char pad[96]; int f96; };
extern "C" void *FUN_0013aec0(...);
extern "C" int FUN_00141190(...);
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
extern "C" void FUN_001c4140(float *, void *, int *, unsigned char *);
extern "C" int kIGMemoryPoolHandleCurrent[4];
struct R_1c4650 { int word0; int references; };
extern "C" R_1c4650 *DAT_00562760[4];
class V128_1c4650 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void vX(int); };
struct O_1c4650 { char p0[28]; R_1c4650 *ref; char p1[196]; unsigned int flags; char p2[316]; V128_1c4650 *v; };
/* matching construct: dummy virtual slots so the type-test call dispatches through the retail vtable offset 88 */
struct BoundVolume { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int ty(); };
extern "C" int g_igAABox_metaObject[4];
extern "C" int FUN_001c4c20(igFrustCullTraversal *, igNode *, int);
extern "C" void FUN_001c5030(igFrustCullTraversal *arg0, igNode *arg1);
typedef struct CullFrustumView { char _pad0[52]; CullAttrState *_state; char _pad38[420]; char _frustum[64]; float *_lastWorld; float *_lastView; } CullFrustumView;
typedef struct CullBoundsView { char _pad0[8]; float _min[3]; float _max[3]; } CullBoundsView;
extern "C" CullMeta *g_igProjectionMatrixAttr_metaObject[4];
extern "C" int FUN_001c47f0(...);
extern "C" float DAT_0048da28[4];
typedef struct S0_1c5160 { char pad552[552]; float f552; float f556; } S0_1c5160;
typedef struct ObjectRefFieldView { int _vtable; int _refCount; char _pad8[30]; unsigned char _flag38; char _pad27[13]; unsigned char _flag52; char _pad35[3]; int _metaObject; } ObjectRefFieldView;
extern "C" int StringPool_Allocate(int);
extern "C" int FUN_002fe570(igMetaObject *, ObjectRefFieldView *);
extern "C" int StringPool_Construct(int);
extern "C" int StringPool_Intern(...);
extern "C" int igGeometrySetAttr_GetMetaObject(void);
extern "C" void igMetaField_SetFieldName(ObjectRefFieldView *, char * *);
extern "C" ObjectRefFieldView *igObjectRefMetaField_Create(int);
extern "C" char text_geoSet[16];
extern "C" void *DAT_00562768[4];
extern "C" int g_stringPool[4];
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
extern "C" int FUN_00300c00(...);
class DW4VC_72_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual int vX(); };
extern "C" int ObjectList_AppendRetainedList(...);
struct List_1c5790 { char p[8]; int n; char q[4]; T **arr; };
struct Obj_1c5790 { char p[8]; List_1c5790 *list; };
typedef struct { char pad[4]; int f4; } R_1c58c0;
typedef struct { char pad[8]; int f8; char pad2[4]; int *f10; } L_1c58c0;
typedef struct { char pad[8]; L_1c58c0 *f8; } T_1c58c0;
extern "C" int FUN_001906d0(...);
struct OO;
class DW4VC_88_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); };
class DW4VC_164_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual int vX(int); };
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
extern "C" void FUN_001d3590(SgLinkNode *);
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
static inline void releaseNode(Obj_1c5eb0 *o) {
    if (o) {
        --o->refs;
        if (((unsigned long long)(long long)o->refs & 0x7fffffULL) == 0) igObject_Destroy(o);
    }
}
struct Ref_1c5eb0 {
    Obj_1c5eb0 *p;
    Ref_1c5eb0() { p = 0; }
    Ref_1c5eb0(Obj_1c5eb0 *o) { p = o; if (p) p->refs++; }
    Ref_1c5eb0(const Ref_1c5eb0 &r) { p = r.p; if (p) p->refs++; }
    ~Ref_1c5eb0() { releaseNode(p); }
};
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
extern "C" int text_invarianceFunction[4];
extern "C" void *DAT_00562770[4];
extern "C" int g_igMetaField_metaObject[4];
extern "C" char GPR_00554b98;
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
extern "C" int FUN_00306360(...);
extern "C" unsigned char FUN_00306910(...);
extern "C" int thunk_strcasecmp(const char *, const char *);
extern "C" int DAT_004e4660[4];
extern "C" int text_Interface[4];
extern "C" int text_fileName[4];
extern "C" int text_section[4];
typedef struct IniSectionNode { char _pad0[28]; int _parent; } IniSectionNode;
extern "C" int text_configuration[4];
extern "C" bool FUN_00306770(int, int, const char *, void *, int *, int);
struct ShaderObject : public igObject { };
struct Factory { char pad32[32]; int f32; int f36; int f40; };
extern "C" int StringList_Resize(...);
struct ShaderObject_1ca6c0 : public igObject {};
struct ShaderNameList : public igObject { int count; int capacity; char **data; };
struct ShaderMetaView;
struct ShaderProcessorTypes { char pad0[28]; void *types; };
struct ShaderProcessorView { char pad0[24]; int kind; int ini; char pad1[12]; int allocatorKey; ShaderProcessorTypes *info; };
struct ShaderCacheView;
extern "C" ShaderMetaView *FUN_002fe460(char *);
extern "C" igSmartPointer<ShaderObject_1ca6c0> FUN_002fd6e0(ShaderMetaView *, int);
extern "C" ShaderNameList *igStringRefList_Create(void *);
extern "C" unsigned char FUN_00306aa0(int, int, void *, ShaderNameList *, int);
extern "C" void *FUN_002fdf20(ShaderMetaView *, char *);
extern "C" int FUN_001c7680(ShaderProcessorView *, int, char *, ShaderObject_1ca6c0 *, void *, unsigned char *);
extern "C" void *FUN_00303d70(...);
extern "C" int FUN_00300920(ShaderObject_1ca6c0 *, ShaderObject_1ca6c0 *);
extern "C" int FUN_00303cd0(...);
extern "C" int text_type[2];
extern "C" int text_fields[2];
extern "C" int text_const[2];
struct L_1cafc0 { char p0[8]; int n; char pc[4]; int *items; };
struct IniValueObject : public igObject { union { int i; float f; unsigned char b; char *s; } value; };
struct IniValueList;
struct IniValueTarget;
extern "C" int FUN_00303e50(IniValueList *);
extern "C" IniValueObject *FUN_00303e60(IniValueList *, int);
extern "C" int FUN_00303e80(IniValueList *, int);
extern "C" void *FUN_001e4e30(...);
extern "C" void *FUN_001e4fc0(...);
extern "C" void *FUN_001e5c50(...);
extern "C" void FUN_0030b720(IniValueObject *, int, void *);
extern "C" void FUN_0030b730(IniValueObject *, void *, float);
extern "C" void FUN_0030b770(IniValueObject *, unsigned char, int);
extern "C" void FUN_002d9740(IniValueTarget *, int, int, char *);
extern "C" int DAT_004e4710[2];
extern "C" int DAT_004e4718[2];
struct IniSectionObject { int pad0; int _refCount; char *name; };
struct IniTypeTable { char pad0[60]; void *meta; };
struct IniShaderFactoryView;
static inline void releaseSection(IniSectionObject *object) {
    if (object != 0) {
        object->_refCount = object->_refCount - 1;
        if ((object->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(object);
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
extern "C" IniSectionObject *FUN_002c6750(void *);
extern "C" void FUN_003006a0(IniSectionObject *, void *);
extern "C" int FUN_002da710(IniSectionObject *, char *, char *);
extern "C" SectionRef FUN_001cd9f0(IniShaderFactoryView *self, char *name);
extern "C" int FUN_002da990(...);
class DW4VC_96_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual int vX(int); };
extern "C" int FUN_00303dc0(...);
extern "C" int FUN_00304030(...);
extern "C" int FUN_00303ed0(...);
struct IniObjectRef { int pad0; int _refCount; };
struct IniStringValue { char pad0[8]; char *text; };
struct IniEntry { char *name; IniStringValue *value; };
struct IniEntryList { char pad0[8]; int count; char pad1[4]; IniEntry **data; };
struct IniNodeList;
struct IniNode { int type; char pad0[4]; IniEntryList *entries; char pad1[4]; IniNodeList *children; };
struct IniNodeList { char pad0[8]; int count; char pad1[4]; IniNode **data; };
struct IniShaderFactoryView;
extern "C" int FUN_0030ba90(char *, void *);
extern "C" int text_file[4];
struct IniDocument { int pad0; int _refCount; char *text; };
struct IniCacheTable { int pad0; int _refCount; };
struct IniSourceList { char pad0[20]; void *entries; };
struct IniFieldEntry { char pad0[56]; IniCacheTable *cache; };
struct IniFactoryState { char pad0[20]; int mode; char pad1[32]; IniCacheTable *cache; };
extern "C" void *FUN_00309a60(void *, void *, void *, int);
extern "C" void *FUN_003022c0(void *, void *, char *);
extern "C" IniDocument *FUN_002baff0(void *);
extern "C" int FUN_00305d30(IniDocument *, char *, void *);
extern "C" void FUN_003061c0(IniDocument *, IniDocument *, int);
extern "C" int g_globalContext[4];
extern "C" int text_system[4];
extern "C" void *DAT_005619b0[4];
extern "C" void *g_igRegistry_metaObject[4];
struct IniSectionText : public igObject { char *text; };
struct IniNamedObject : public igObject {};
struct IniFieldEntry_1cdbb0 { char pad0[56]; IniNamedObject *cache; };
struct IniFactoryView { char pad0[20]; int mode; char pad1[32]; IniNamedObject *cache; };
class IniFileHandle : public igVirtualObject {
public:
        virtual void d1();    virtual void d2();    virtual void d3();    virtual void d4();    virtual void d5();    virtual void d6();    virtual void d7();    virtual void d8();    virtual void d9();    virtual void d10();    virtual void d11();    virtual void d12();    virtual void d13();    virtual void d14();    virtual void d15();    virtual void d16();    virtual void d17();    virtual void d18();    virtual void d19();    virtual void d20();    virtual void d21();    virtual void d22();
    virtual int open(char *, void *);
    virtual void close();
    virtual void read(char *, int, int);
    virtual void d26();    virtual void d27();    virtual void d28();    virtual void d29();    virtual void d30();    virtual void d31();    virtual void d32();    virtual void d33();    virtual void d34();    virtual void d35();
    virtual void seek(int, int);
    virtual int tell();
};
extern "C" void *igFile_Create(void *);
extern "C" char *FUN_00300d70(IniFactoryView *, int);
extern "C" void *g_igStringObj_metaObject[4];
extern "C" int DAT_004e47a8[2];
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
    virtual int open(char *, void *);
    virtual void close();
    
    char pad0[4];
    int handle;
};
extern "C" int DAT_004e47b0[4];
extern "C" int kIGMemoryPoolHandleString[4];
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
extern "C" int g_beModelCtrlInfo_metaObject[4];
extern "C" int FUN_001cfc70(...);
extern "C" int FUN_0018f760(...);
typedef struct MatrixStackEntry { float f[16]; } MatrixStackEntry;
typedef struct ReleasableList { int pad0, pad4; int n; int cap; int *data; } ReleasableList;
typedef struct MatrixStackList { int pad0, pad4; int n; int cap; MatrixStackEntry *data; } MatrixStackList;
typedef struct CountedObject { int vt; int rc; } CountedObject;
typedef struct TraversalMatrixState { int p[8]; MatrixStackList *mats; ReleasableList *objs; } TraversalMatrixState;
extern "C" int g_beHitLandModelTraversal_metaObject[4];
struct HitMetaView { char pad0[8]; int index; };
struct HitMatrix { float m[16]; };
struct HitVector { float x, y, z; };
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
    HitVector local;
    HitVector point;
    HitVector normal;
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
extern "C" void igRay_Transform(HitBound *, HitMatrix *);
extern "C" int FUN_0018ffa0(void *, HitBound *);
extern "C" int FUN_00190010(HitBound *, HitSegment *);
extern "C" void FUN_001901b0(HitBound *, HitMatrix *);
extern "C" int FUN_001cef70(HitTraversal *, HitAttr *, HitBound *, HitVector *, HitVector *, int *, int *, void *, long long);
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
extern "C" void FUN_001e68e0(MatrixStack *, float *);
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
struct SceneFieldInfo { char pad0[8]; int offset; };
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
extern "C" SceneFieldInfo *DAT_00562bc8;
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
extern "C" void *FUN_002c9740(void *);
extern "C" void *FUN_002c99b0(void *);
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
extern "C" void FUN_002d6790(KeyIndexList *, int, int);
extern "C" int FUN_001d1a90(...);
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
extern "C" void memcpy(void *, void *, int);
struct S_1d2230 { int p[3]; int t; };
class O_1d2230 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void v128(int); virtual void v132(int);
  int p[4]; int f20; };
struct L1d { int a; int b; int count; int cap; int *data; };
extern "C" int g_resultSuccess[4];
extern "C" int g_resultFailure[4];
struct ObjectListOwner { char pad[16]; igTDataList<igObject *> *_list; };
struct S_1d32f0;
class V_1d32f0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual int c(); virtual S_1d32f0 *g(int); };
struct S_1d32f0 : V_1d32f0 { char p[16]; int f20; };
class DW4VC_120_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual int vX(); };
extern "C" unsigned int igGroup_RemoveChild(S_1c5eb0 *host, Obj_1c5eb0 *child);
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
extern "C" void * *FUN_00133610(...);
extern "C" int igLightingStateAttr_CreateInstance(...);
extern "C" void *FUN_00137070(...);
extern "C" void * *FUN_00138690(...);
extern "C" int FUN_00139ed0(...);
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
extern "C" int FUN_001908f0(...);
extern "C" int FUN_001d3c60(...);
extern "C" int FUN_00134690(...);
extern "C" int FUN_001315d0(...);
extern "C" int FUN_001341b0(int);
extern "C" int FUN_001384a0(int);
extern "C" int FUN_00139370(int);
extern "C" int FUN_0013b490(int);
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
extern "C" int g_shadowTextureFunctionAttr0[4];
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
    void setColor(ShadowColor &c) { color = c; packed = FUN_001931b0(&c, 1); }
};
struct ShadowModeObj { char pad0[12]; int mode; };
extern "C" int FUN_002f88e0(...);
extern "C" ShadowSetupObj *FUN_00132b60(...);
extern "C" ShadowSetupObj *FUN_0014df70(...);
extern "C" void FUN_00140ad0(void *, void *, int);
struct ShadowRef {
    ShadowSetupObj *p;
    ~ShadowRef() {
        ShadowSetupObj *object = p;
        if (object) {
            --object->refCount;
            if (((unsigned long long)(long long)object->refCount & 0x7fffffULL) == 0)
                igObject_Destroy(object);
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
extern "C" int FUN_00190c60(...);
typedef struct A_1d5f70 { char pad[208]; unsigned char f208; } A_1d5f70;
extern "C" int FUN_00191860(void *, float, float, float, float, float, float);
extern "C" int igMatrix44f_MakePerspective(void *, float, float, float, float, float);
extern "C" int igMatrix44f_MakeLookAt(...);
struct Mx { float m[16]; };
class V_1d6060 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void vX(Mx *); };
struct O_1d6060 { char p0[32]; float f32, f36, f40, f44, f48, f52, f56; char p60[28]; V_1d6060 *f88; V_1d6060 *f92; char p96[28]; float f124, f128; char p132[12]; V_1d6060 *f144; char p148[60]; unsigned char f208; char p209[3]; float f212, f216, f220, f224; };
extern "C" int igProjectiveShadowShader_Initialize(...);
struct Src_1d6190 { char p[96]; float f96; char p1[16]; float f116; float f120; float f124; float f128; float f132; float f136; };
struct S_1d6190 { char p0[32]; float f32; float f36; float f40; float f44; float f48; float f52; float f56; char p1[44]; int f104; char p2[92]; struct Src_1d6190 *src; };
struct R_1d6240 { int w0; int rc; };
struct L_1d6240 { char pad[8]; int cnt; int cap; int *data; };
struct S_1d6240 { char pad[64]; struct L_1d6240 *f64; };
class DW4VC_112_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual int vX(); };
typedef struct S1_1d6340 { char pad4[4]; int f4; } S1_1d6340;
typedef struct S0_1d6340 { char pad20[20]; int f14; } S0_1d6340;
typedef struct S_temp_a0_1d6340 { char pad4[4]; int f4; } S_temp_a0_1d6340;
extern "C" int g_ParticleInfo_metaObject[4];
extern "C" int igObject_GetFieldValueByName(void *, int);
extern "C" int Gap__Bec__ParticleInfo__vfunc_20(void);
extern "C" void Gap__Bec__ParticleInfo__vfunc_11(ParticleInfo *, int);
typedef struct NodeList { char p0[8]; unsigned count; char p1[4]; int *data; } NodeList;
typedef struct TraversedNode { char p0[28]; NodeList *children; } TraversedNode;
typedef struct PathEntry : public igObject { } PathEntry;
struct O_1d65e0 { char pad[20]; int f20; int f24; igObject *f28; };
struct ChildOwner { char pad[20]; int f20; };
struct ChildObject : public igObject { };
extern "C" ChildObject *FUN_002c72c0(...);
extern "C" int FUN_002d8620(...);
struct EE_1d6790;
extern "C" EE_1d6790 *FUN_002d7e90(...);
extern "C" int g_igObjectDirEntry_metaObject[4];
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
extern "C" Primitive *igGeometryAttr_Create(int);
extern "C" int FUN_002f8a20(void);
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
struct Vec3x { float x, y, z; };
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
extern "C" int FUN_00166d40(void);
extern "C" int DAT_004e4820[];
class ShadowStateObj : public ShadowRefObj { public: virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22(int); virtual void s23(int); virtual void s24(); virtual void s25(); virtual void s26(int); virtual void s27(int); virtual void s28(int); virtual void s29(); virtual void s30(int); virtual void s31(int); virtual void s32(int); virtual void s33(int); };
class ShadowViewportObj { public: virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29(); virtual void s30(int, int, int, int, float, float); };
static inline void addRef(ShadowRefObj *o) { if (o) { o->refCount++; } }
static inline void releaseRef(ShadowRefObj *o) {
    if (o) {
        --o->refCount;
        if (((unsigned long long)(long long)o->refCount & 0x7fffffULL) == 0)
            igObject_Destroy((void *)o);
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
                igObject_Destroy(object);
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
extern "C" void FUN_00190a10(float *, float *);
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
extern "C" TravFunctionTable *DAT_005628e0[4];
extern "C" TravFunctionTable *DAT_005628e8[4];
class DW4VCSR_128_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual int vX(float *); };
typedef struct L_1d7b70 { char p[8]; int n; char q[4]; int *arr; } L_1d7b70;
typedef struct S0_1d7b70 {
    char p0[28]; L_1d7b70 *f28; unsigned char b32; char p1[51]; L_1d7b70 *f84; char p2[4]; int f92; int f96; int f100;
    char p3[36]; unsigned char b140; char p4[7]; int f148; char p5[4]; int f156; char p6[16]; int f176;
    char p7[16]; int f196; int f200; int f204; char p8[20]; int f228;
} S0_1d7b70;
typedef struct S1_1d7b70 { char p[52]; int f52; char p1[12]; int f68; } S1_1d7b70;
extern "C" int DAT_0048dae0[4];
extern "C" int text_maxLightStateCount[4];
extern "C" int text_disableBumpDotProduct[4];
extern "C" char GPR_00554b9c;
extern "C" int g_igLightAttr_metaObject[4];
typedef struct ShaderDataEntry { int _vtable; int references; } ShaderDataEntry;
typedef struct ShaderDataList { int pad0[2]; int count; int pad1; ShaderDataEntry **data; } ShaderDataList;
/* igShaderData with its lists typed. */
struct ShaderDataView { char pad[8]; ShaderDataList *_attrPushLists; ShaderDataList *_attrPopLists; ShaderDataEntry *_dataPumps; ShaderDataList *_childLists; };
struct S_1d86f0 { char pad0[8]; igObjectList *f8; };
struct A_1d8870 { char pad[20]; igObjectList *f20; };
typedef struct S0_1d8930 { char pad20[20]; int f14; } S0_1d8930;
extern "C" int ObjectList_ClearRetainedPreserveCount(...);
struct Attr : public igObject { };
class VO_1d8980 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void v96(Attr *, Attr *, int); virtual void v100(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); };
class VA_1d8980 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void v124(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual void d90(); virtual void d91(); virtual void d92(); virtual void d93(); virtual void d94(); virtual void d95(); virtual void d96(); virtual void d97(); virtual void d98(); virtual void d99(); virtual void d100(); virtual void d101(); virtual void d102(); virtual void d103(); virtual void d104(); virtual void d105(); virtual void d106(); virtual void d107(); virtual void d108(); virtual void d109(); virtual void d110(); virtual void d111(); virtual void d112(); virtual void d113(); virtual void d114(); virtual void d115(); virtual void d116(); virtual void d117(); virtual void d118(); virtual void d119(); virtual void d120(); virtual void d121(); virtual void d122(); virtual void d123(); virtual void d124(); };
struct P_1d8980 { char pad[36]; VO_1d8980 *f36; };
class V_1d8a60 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual int vX(); };
struct T_1d8a60 { char pad[20]; int f20; };
extern "C" int FUN_002d81f0(...);
extern "C" igSmartPointer<igObject> FUN_003087a0(int directory, const char *name);
extern "C" void igNamedObject_SetName(igObject *object, int *name);
extern "C" void FUN_002d8310(igObject *list, igObject *object);
extern "C" int text_shaderInfo[4];
struct ShaderFieldRecord { char pad[8]; int *name; char pad2[8]; int kind; };
struct ShaderFieldTable { char pad[20]; igTDataList<ShaderFieldRecord *> *list; };
extern "C" int text_empty[4];
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
extern "C" int igObject_ResetFields(igObject *);
struct ObjectPool : igTDataList<igObject *> {
    int _activeCount;
    int _pad24;
    unsigned char _resetOnRelease;
};
extern "C" int _dpflt(double, double);
extern "C" double dpsub(double, double);
extern "C" double floor(double);
extern "C" int dptoli(double);
typedef struct KeyTimeListView { int _vtable; unsigned int _refCount; int _count; int _capacity; double *_data; } KeyTimeListView;
typedef struct KeyValueListView { int _vtable; unsigned int _refCount; int _count; int _capacity; int *_data; } KeyValueListView;
typedef struct KeyTrackView { char pad[28]; KeyValueListView *_values; KeyTimeListView *_times; double _startTime; int _mode; } KeyTrackView;
struct S_1dce70 { char pad[8]; int f8; char pad2[4]; double *f16; };
class DW4VC_116_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual int vX(); };
class VC_1dd010 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void vX(int); };
extern "C" float FUN_00192290(void *);
extern "C" int FUN_00190cb0(...);
typedef struct TransformSampleVec3ListView { int _vtable; unsigned int _refCount; int _count; int _capacity; float (*_data)[3]; } TransformSampleVec3ListView;
typedef struct TransformSampleQuatListView { int _vtable; unsigned int _refCount; int _count; int _capacity; float (*_data)[4]; } TransformSampleQuatListView;
typedef struct TransformSampleView { int _vtable; unsigned int _refCount; TransformSampleVec3ListView *_xlateList; TransformSampleQuatListView *_quatList; TransformSampleVec3ListView *_scaleList; } TransformSampleView;
typedef struct V3_1dd250 { float x, y, z; } V3_1dd250;
typedef struct B_1dd250 { char pad[16]; char *data; } B_1dd250;
typedef struct A_1dd250 { char pad[8]; B_1dd250 *b8; B_1dd250 *b12; B_1dd250 *b16; char pad2[24]; float f44; float f48; float f52; } A_1dd250;
extern "C" float g_vec3Zero[4];
extern "C" float DAT_004e105c[4];
extern "C" float DAT_004e1060[4];
class V_1dd3e0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void vSet(int, int *); virtual void vGet(int, int *); virtual void e0(); virtual void e1(); virtual void e2(); virtual int vCount(); };
struct F_1dd3e0 { char p[44]; float a; float b; float c; };
extern "C" long long __udivdi3(...);
extern "C" long long __muldi3(...);
extern "C" long long DAT_00562a18[4];
extern "C" long long DAT_00562a20[4];
extern "C" int DAT_00562a28[4];
extern "C" long long DAT_00562a30[4];
class VC_1dd570 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual int v156(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual float *v180(int); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual unsigned char v240(); };
extern "C" void FUN_00192990(void *, float *, float *, float *);
typedef struct KeyVec3View { float x, y, z; } KeyVec3View;
typedef struct KeyVec3ListView { int _vtable; unsigned int _refCount; int _count; int _capacity; KeyVec3View *_data; } KeyVec3ListView;
typedef struct KeyQuatView { float x, y, z, w; } KeyQuatView;
typedef struct KeyQuatListView { int _vtable; unsigned int _refCount; int _count; int _capacity; KeyQuatView *_data; } KeyQuatListView;
typedef struct KeySequenceView { int _vtable; unsigned int _refCount; KeyVec3ListView *_xlateList; KeyQuatListView *_quatList; KeyVec3ListView *_scaleList; char pad[52]; unsigned char _drivenChannels; } KeySequenceView;
typedef struct KeyMatrixView { float r[3][4]; float tx, ty, tz, tw; } KeyMatrixView;
struct V3_1dda90 { float x, y, z; };
struct V4_1dda90 { float x, y, z, w; };
extern "C" int List_InsertBytes(...);
extern "C" int FUN_002d4c20(int, int, int);
extern "C" int text_interpolationMethod[4];
struct SeqData {
    char pad0[4];
    int refCount;
    int count;
    int capacity;
};
extern "C" SeqData *FUN_0018a060(...);
struct SeqTempRef {
    SeqData *p;
    SeqTempRef(SeqData *x) : p(x) {}
    ~SeqTempRef() {
        if (p) {
            --p->refCount;
            if (((unsigned long long)(long long)p->refCount & 0x7fffffULL) == 0)
                igObject_Destroy(p);
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
extern "C" SeqData *FUN_00189bd0(...);
typedef struct V_1de9c0 { float x, y, z; } V_1de9c0;
typedef struct L_1de9c0 { int pad[2]; int count; int cap; V_1de9c0 *data; } L_1de9c0;
typedef struct LL_1de9c0 { int pad[2]; int count; } LL_1de9c0;
typedef struct T_1de9c0 { char pad[56]; LL_1de9c0 *tl; L_1de9c0 *a; L_1de9c0 *b; L_1de9c0 *c; unsigned char flags; } T_1de9c0;
struct Set { static inline void put(L_1de9c0 *l, int i, V_1de9c0 *p) {
    V_1de9c0 *e;
    if (l->count != 0 && i >= 0 && i < l->count) {
        e = l->data + i; e->x = p->x; e->y = p->y; e->z = p->z;
    }
} };
/* The rates are read as unsigned, so the unsigned-int to float conversion yields the srl/andi/or
 * fixup. */
typedef struct SequenceTimeList { char pad[16]; long long *_data; } SequenceTimeList;
/* igTransformSequence1_5 down to its key time list (_timeListLong, +56). */
typedef struct SequenceKeyTimes { char pad[56]; SequenceTimeList *_timeListLong; } SequenceKeyTimes;
extern "C" float fmodf(float, float);
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
extern "C" char text_useScratchPadForTraversal[];
extern "C" unsigned char GPR_00554bac;
struct S_1e04c0;
struct V_1e04c0;
class V_1e04c0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); };
struct L_1e04c0 { char p[16]; int (**tab)(S_1e04c0 *, V_1e04c0 *); };
struct S_1e04c0 { char p[8]; unsigned char f8; char q[3]; int (*f12)(...); char r[12]; L_1e04c0 *f28; };
struct W_1e04c0 : V_1e04c0 { char p[20]; int f24; };
struct L_1e06c0 { char pad[8]; int n; int cap; void **arr; };
struct X_1e06c0 { char pad[8]; int f8; };
struct L_1e07a0 { char p[8]; int n; char q[4]; int *arr; };
struct S_1e07a0 { char p[28]; L_1e07a0 *f28; };
class DW4VC_200_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual int vX(); };
struct T_1e08b0 { int word0; int references; int f8; int f12; };
extern "C" T_1e08b0 *FUN_00134b60(...);
extern "C" T_1e08b0 *FUN_001359a0(...);
extern "C" T_1e08b0 *FUN_00138cb0(...);
struct Rel { static inline void go(T_1e08b0 *object) {
    if (object) {
        --object->references;
        if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
            igObject_Destroy(object);
    }
} };
class DW4VC_128_4 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual int vX(int, int, int, int); };
typedef struct Rc_1e1210 { int w0; int refs; } Rc_1e1210;
class A_1e1210 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void v28(int); virtual void d29(); char p[40]; int f44; };
class B_1e1210 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void v30(int); virtual void v31(int); };
typedef struct S_1e1210 { char p0[32]; int f32; char p1[16]; int f52; char p2[17]; unsigned char f73; char p3[6]; B_1e1210 *f80; char p4[28]; B_1e1210 *f112; Rc_1e1210 *f116; Rc_1e1210 *f120; } S_1e1210;
extern "C" Rc_1e1210 *FUN_00133160(int);
extern "C" Rc_1e1210 *FUN_00135190(int);
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
                igObject_Destroy(object);
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
                igObject_Destroy(object);
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
                igObject_Destroy(p);
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
extern "C" void List_RemoveAt(int, int, int);
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
struct Rel_1e2ec0 { static inline void go(RO *o) { RO *t = o; if (t != 0) { t->u.w = t->u.w - 1; if (t->u.b.cnt == 0) igObject_Destroy(t); } } };
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
extern "C" int g_ParticleTimer_metaObject[4];
typedef struct S1_1e31f0 { char pad4[4]; int f4; } S1_1e31f0;
typedef struct S0_1e31f0 { char pad68[68]; int f44; } S0_1e31f0;
typedef struct S_temp_a0_1e31f0 { char pad4[4]; int f4; } S_temp_a0_1e31f0;
typedef struct { char p[8]; int n; char q[4]; char *arr; } T_1e3270;
struct S_1e3300 { char pad0[8]; struct R *p8; char pad1[44]; unsigned char f56; };
extern "C" int List_Reserve(...);
struct L_1e3500 { char pad[8]; int cnt; int pad2; int *items; };
extern "C" int g_igAnimationCombinerBoneInfoPool_metaObject[4];
extern "C" int g_igAnimationStatePool_metaObject[4];
extern "C" int g_igDoubleList_metaObject[4];
extern "C" void SceneGraphLibrary_MarkRegistered(void);
extern "C" igMetaObject *FUN_001943a0(void);
extern "C" igMetaObject *igTraversal_GetMetaObject(void);
extern "C" int igTraversal_GetVTable(void);
extern "C" void *FUN_00194490(struct S *arg0, short arg1);
extern "C" void FUN_00194530(void);
extern "C" void igTraversal_Register(void);
extern "C" void thunk_igTraversal_GetMetaObject(void);
extern "C" void igTraversal_InitFields(void);
extern "C" void FUN_00194690(void);
extern "C" void thunk_FUN_001e0470(void);
extern "C" igMetaObject *igTransientShaderData_GetMetaObject(void);
extern "C" int igTransientShaderData_GetVTable(void);
extern "C" int **FUN_00194790(int **arg0, long long arg1);
extern "C" void **FUN_00194830(struct Ref **self, short flag);
extern "C" void **FUN_001948b0(void **arg0, long long arg1);
extern "C" Obj_194930 *FUN_00194930(Obj_194930 *arg0, short arg1);
extern "C" void FUN_00194a90(void);
extern "C" void igTransientShaderData_Register(void);
extern "C" void thunk_igTransientShaderData_GetMetaObject(void);
extern "C" igMetaObject *FUN_00194b30(void);
extern "C" void igTransientShaderData_InitFields(void);
extern "C" igMetaObject *FUN_00194dd0(void);
extern "C" igMetaObject *igTransformSource_GetMetaObject(void);
extern "C" void FUN_00194e70(void);
extern "C" void igTransformSource_Register(void);
extern "C" void thunk_igTransformSource_GetMetaObject(void);
extern "C" igMetaObject *FUN_00194ef0(void);
extern "C" int igTransformSequence1_5_GetVTable(void);
extern "C" Obj_195030 *FUN_00195030(Obj_195030 *arg0, short arg1);
extern "C" O *FUN_00195190(O *arg0, short arg1);
extern "C" ObjectRefWord *FUN_00195210(ObjectRefWord *self,int delete_storage);
extern "C" void FUN_00195290(void);
extern "C" void igTransformSequence1_5_Register(void);
extern "C" void thunk_FUN_00194ef0(void);
extern "C" igMetaObject *FUN_00195330(void);
extern "C" void thunk_FUN_001ddfd0(void);
extern "C" igMetaObject *igTransformSequence_GetMetaObject(void);
extern "C" void FUN_00195580(void);
extern "C" void igTransformSequence_Register(void);
extern "C" void thunk_igTransformSequence_GetMetaObject(void);
extern "C" igMetaObject *FUN_00195610(void);
extern "C" void igTransformSequence_InitFields(void);
extern "C" igMetaObject *FUN_001957c0(void);
extern "C" igMetaObject *igTransformRecorder_GetMetaObject(void);
extern "C" int igTransformRecorder_GetVTable(void);
extern "C" void **FUN_001958f0(void **arg0, short arg1);
extern "C" void *FUN_00195970(struct T_195970 *arg0, long long arg1);
extern "C" void *FUN_00195a90(struct T_195a90 *arg0, long long arg1);
extern "C" void FUN_00195c00(void);
extern "C" void igTransformRecorder_Register(void);
extern "C" void thunk_igTransformRecorder_GetMetaObject(void);
extern "C" void igTransformRecorder_InitFields(void);
extern "C" igMetaObject *FUN_00195d00(void);
extern "C" igMetaObject *igNonRefCountedTransformList_GetMetaObject(void);
extern "C" int igNonRefCountedTransformList_GetVTable(void);
extern "C" void FUN_00195de0(void);
extern "C" void igNonRefCountedTransformList_Register(void);
extern "C" void thunk_igNonRefCountedTransformList_GetMetaObject(void);
extern "C" igMetaObject *FUN_00195e70(void);
extern "C" igMetaObject *igTransformList_GetMetaObject(void);
extern "C" int igTransformList_GetVTable(void);
extern "C" void FUN_00195f50(void);
extern "C" void igTransformList_Register(void);
extern "C" void thunk_igTransformList_GetMetaObject(void);
extern "C" igMetaObject *FUN_00195fe0(void);
extern "C" igMetaObject *igTransformStack_GetMetaObject(void);
extern "C" int igTransformStack_GetVTable(void);
extern "C" void FUN_001960c0(void);
extern "C" void igTransformStack_Register(void);
extern "C" void thunk_igTransformStack_GetMetaObject(void);
extern "C" void FUN_00196150(int arg0);
extern "C" igMetaObject *FUN_00196190(void);
extern "C" igMetaObject *igTransform_GetMetaObject(void);
extern "C" int igTransform_GetVTable(void);
extern "C" void *FUN_001962d0(struct S_1962d0 *arg0, short arg1);
extern "C" ObjectRefWord *FUN_001963d0(ObjectRefWord *self,int delete_storage);
extern "C" void **FUN_00196450(void **arg0, short arg1);
extern "C" void FUN_001964d0(void);
extern "C" void igTransform_Register(void);
extern "C" void thunk_igTransform_GetMetaObject(void);
extern "C" void igTransform_InitFields(void);
extern "C" ObjectRefWord *FUN_001966b0(ObjectRefWord *self,int delete_storage);
extern "C" igMetaObject *igObjectPool_GetMetaObject(void);
extern "C" int igObjectPool_GetVTable(void);
extern "C" void FUN_001967c0(void);
extern "C" void igObjectPool_Register(void);
extern "C" void thunk_igObjectPool_GetMetaObject(void);
extern "C" void igObjectPool_InitFields(void);
extern "C" void igSwitch_CreateInstance(int arg0);
extern "C" igMetaObject *FUN_00196930(void);
extern "C" igMetaObject *igSwitch_GetMetaObject(void);
extern "C" int igSwitch_GetVTable(void);
extern "C" struct R **FUN_00196a50(struct R **arg0, short arg1);
extern "C" void FUN_00196ad0(void);
extern "C" void igSwitch_Register(void);
extern "C" void thunk_igSwitch_GetMetaObject(void);
extern "C" void igSwitch_InitFields(void);
extern "C" igMetaObject *FUN_00196c10(void);
extern "C" igMetaObject *igSorter_GetMetaObject(void);
extern "C" int igSorter_GetVTable(void);
extern "C" void **FUN_00196f60(void **arg0, long long arg1);
extern "C" void **FUN_00196fe0(void **arg0, int arg1);
extern "C" void **FUN_00197060(void **arg0, short arg1);
extern "C" void **FUN_001970e0(struct Ref **self, short flag);
extern "C" void **FUN_00197160(void **arg0, long long arg1);
extern "C" O *FUN_001971e0(O *arg0, short arg1);
extern "C" void **FUN_00197260(void **arg0, long long arg1);
extern "C" int *FUN_001972e0(int *p);
extern "C" int *FUN_001972f0(int *p);
extern "C" int *FUN_00197300(int *p);
extern "C" int *FUN_00197310(int *p);
extern "C" int *FUN_00197320(int *p);
extern "C" int *FUN_00197330(int *p);
extern "C" int *FUN_00197340(int *p);
extern "C" int *FUN_00197350(int *p);
extern "C" void FUN_00197360(void);
extern "C" void igSorter_Register(void);
extern "C" void thunk_igSorter_GetMetaObject(void);
extern "C" void igSorter_InitFields(void);
extern "C" igMetaObject *FUN_001977c0(void);
extern "C" igMetaObject *igRenderPackageList_GetMetaObject(void);
extern "C" int igRenderPackageList_GetVTable(void);
extern "C" void FUN_001978a0(void);
extern "C" void igRenderPackageList_Register(void);
extern "C" void thunk_igRenderPackageList_GetMetaObject(void);
extern "C" igMetaObject *FUN_00197930(void);
extern "C" igMetaObject *igRenderPackagePool_GetMetaObject(void);
extern "C" int igRenderPackagePool_GetVTable(void);
extern "C" void FUN_00197a10(void);
extern "C" void igRenderPackagePool_Register(void);
extern "C" void thunk_igRenderPackagePool_GetMetaObject(void);
extern "C" igMetaObject *FUN_00197aa0(void);
extern "C" void FUN_00197ab0(int arg0);
extern "C" igMetaObject *FUN_00197af0(void);
extern "C" igMetaObject *igRenderPackage_GetMetaObject(void);
extern "C" int igRenderPackage_GetVTable(void);
extern "C" void FUN_00197cc0(void);
extern "C" void igRenderPackage_Register(void);
extern "C" void thunk_igRenderPackage_GetMetaObject(void);
extern "C" void igRenderPackage_InitFields(void);
extern "C" igMetaObject *FUN_00197e60(void);
extern "C" igMetaObject *igSkinList_GetMetaObject(void);
extern "C" int igSkinList_GetVTable(void);
extern "C" void FUN_00197f40(void);
extern "C" void igSkinList_Register(void);
extern "C" void thunk_igSkinList_GetMetaObject(void);
extern "C" igMetaObject *FUN_00197fd0(void);
extern "C" igMetaObject *igSkin_GetMetaObject(void);
extern "C" int igSkin_GetVTable(void);
extern "C" void **FUN_00198190(void **arg0, short arg1);
extern "C" ObjectRefWord *FUN_00198210(ObjectRefWord *self,int delete_storage);
extern "C" void FUN_00198290(void);
extern "C" void igSkin_Register(void);
extern "C" void thunk_igSkin_GetMetaObject(void);
extern "C" void igSkin_InitFields(void);
extern "C" igMetaObject *FUN_001983e0(void);
extern "C" igMetaObject *igSkeletonList_GetMetaObject(void);
extern "C" int igSkeletonList_GetVTable(void);
extern "C" void FUN_001984c0(void);
extern "C" void igSkeletonList_Register(void);
extern "C" void thunk_igSkeletonList_GetMetaObject(void);
extern "C" igMetaObject *FUN_00198550(void);
extern "C" int igSkeleton_GetVTable(void);
extern "C" void FUN_00198680(void);
extern "C" void igSkeleton_Register(void);
extern "C" void thunk_FUN_00198550(void);
extern "C" igMetaObject *FUN_00198720(void);
extern "C" void igSkeleton_InitFields(void);
extern "C" igMetaObject *FUN_001987f0(void);
extern "C" igMetaObject *igSkeletonBoneInfoList_GetMetaObject(void);
extern "C" int igSkeletonBoneInfoList_GetVTable(void);
extern "C" void FUN_001988d0(void);
extern "C" void igSkeletonBoneInfoList_Register(void);
extern "C" void thunk_igSkeletonBoneInfoList_GetMetaObject(void);
extern "C" igMetaObject *FUN_00198960(void);
extern "C" int igSkeletonBoneInfo_GetVTable(void);
extern "C" void FUN_00198a40(void);
extern "C" void igSkeletonBoneInfo_Register(void);
extern "C" void thunk_FUN_00198960(void);
extern "C" void igSkeletonBoneInfo_InitFields(void);
extern "C" int FUN_00198b60(int arg0);
extern "C" igMetaObject *igShaderProcessor_GetMetaObject(void);
extern "C" int igShaderProcessor_GetVTable(void);
extern "C" void FUN_00198c30(void);
extern "C" void igShaderProcessor_Register(void);
extern "C" void thunk_igShaderProcessor_GetMetaObject(void);
extern "C" int FUN_00198cc0(int arg0);
extern "C" igMetaObject *igShaderInfo_GetMetaObject(void);
extern "C" int igShaderInfo_GetVTable(void);
extern "C" void FUN_00198e30(void);
extern "C" void igShaderInfo_Register(void);
extern "C" void thunk_igShaderInfo_GetMetaObject(void);
extern "C" void igShaderInfo_InitFields(void);
extern "C" void thunk_FUN_001d8ab0(void);
extern "C" void thunk_FUN_001d8b90(void);
extern "C" igMetaObject *FUN_00198fa0(void);
extern "C" igMetaObject *igShaderFactoryList_GetMetaObject(void);
extern "C" int igShaderFactoryList_GetVTable(void);
extern "C" void FUN_00199080(void);
extern "C" void igShaderFactoryList_Register(void);
extern "C" void thunk_igShaderFactoryList_GetMetaObject(void);
extern "C" int FUN_00199110(void);
extern "C" igMetaObject *FUN_00199170(void);
extern "C" igMetaObject *igShaderFactory_GetMetaObject(void);
extern "C" int igShaderFactory_GetVTable(void);
extern "C" void *FUN_00199330(struct T_199330 *arg0, long long arg1);
extern "C" void **FUN_00199450(void **arg0, short arg1);
extern "C" void FUN_001994d0(void);
extern "C" void igShaderFactory_Register(void);
extern "C" void thunk_igShaderFactory_GetMetaObject(void);
extern "C" void igShaderFactory_InitFields(void);
extern "C" igMetaObject *igShaderData_GetMetaObject(void);
extern "C" int igShaderData_GetVTable(void);
extern "C" void FUN_00199760(void);
extern "C" void igShaderData_Register(void);
extern "C" void thunk_igShaderData_GetMetaObject(void);
extern "C" void igShaderData_InitFields(void);
extern "C" ObjectRefWord *FUN_001998f0(ObjectRefWord *self,int delete_storage);
extern "C" struct R **FUN_00199970(struct R **arg0, short arg1);
extern "C" igMetaObject *FUN_001999f0(void);
extern "C" igMetaObject *igBlendMatricesAttrPool_GetMetaObject(void);
extern "C" int igBlendMatricesAttrPool_GetVTable(void);
extern "C" void FUN_00199ad0(void);
extern "C" void igBlendMatricesAttrPool_Register(void);
extern "C" void thunk_igBlendMatricesAttrPool_GetMetaObject(void);
extern "C" igMetaObject *FUN_00199b60(void);
extern "C" igMetaObject *igTextureMatrixAttrPool_GetMetaObject(void);
extern "C" int igTextureMatrixAttrPool_GetVTable(void);
extern "C" void FUN_00199c40(void);
extern "C" void igTextureMatrixAttrPool_Register(void);
extern "C" void thunk_igTextureMatrixAttrPool_GetMetaObject(void);
extern "C" igMetaObject *FUN_00199cd0(void);
extern "C" igMetaObject *igMatrixObjectPool_GetMetaObject(void);
extern "C" int igMatrixObjectPool_GetVTable(void);
extern "C" void FUN_00199db0(void);
extern "C" void igMatrixObjectPool_Register(void);
extern "C" void thunk_igMatrixObjectPool_GetMetaObject(void);
extern "C" igMetaObject *FUN_00199e40(void);
extern "C" igMetaObject *igVertexBlendMatrixListAttrPool_GetMetaObject(void);
extern "C" int igVertexBlendMatrixListAttrPool_GetVTable(void);
extern "C" void FUN_00199f20(void);
extern "C" void igVertexBlendMatrixListAttrPool_Register(void);
extern "C" void thunk_igVertexBlendMatrixListAttrPool_GetMetaObject(void);
extern "C" igMetaObject *FUN_00199fb0(void);
extern "C" igMetaObject *igVertexBlendMatrixAttrPool_GetMetaObject(void);
extern "C" int igVertexBlendMatrixAttrPool_GetVTable(void);
extern "C" void FUN_0019a090(void);
extern "C" void igVertexBlendMatrixAttrPool_Register(void);
extern "C" void thunk_igVertexBlendMatrixAttrPool_GetMetaObject(void);
extern "C" igMetaObject *FUN_0019a120(void);
extern "C" igMetaObject *igProjectionMatrixAttrPool_GetMetaObject(void);
extern "C" int igProjectionMatrixAttrPool_GetVTable(void);
extern "C" void FUN_0019a200(void);
extern "C" void igProjectionMatrixAttrPool_Register(void);
extern "C" void thunk_igProjectionMatrixAttrPool_GetMetaObject(void);
extern "C" igMetaObject *FUN_0019a290(void);
extern "C" igMetaObject *igTimeAttrPool_GetMetaObject(void);
extern "C" int igTimeAttrPool_GetVTable(void);
extern "C" void FUN_0019a370(void);
extern "C" void igTimeAttrPool_Register(void);
extern "C" void thunk_igTimeAttrPool_GetMetaObject(void);
extern "C" igMetaObject *FUN_0019a400(void);
extern "C" igMetaObject *igModelViewMatrixAttrPool_GetMetaObject(void);
extern "C" int igModelViewMatrixAttrPool_GetVTable(void);
extern "C" void FUN_0019a4e0(void);
extern "C" void igModelViewMatrixAttrPool_Register(void);
extern "C" void thunk_igModelViewMatrixAttrPool_GetMetaObject(void);
extern "C" igMetaObject *FUN_0019a570(void);
extern "C" igMetaObject *igLightStateAttrPool_GetMetaObject(void);
extern "C" int igLightStateAttrPool_GetVTable(void);
extern "C" void FUN_0019a650(void);
extern "C" void igLightStateAttrPool_Register(void);
extern "C" void thunk_igLightStateAttrPool_GetMetaObject(void);
extern "C" int FUN_0019a6e0(int arg0);
extern "C" igMetaObject *FUN_0019a720(void);
extern "C" igMetaObject *igTraversalFunctionList_GetMetaObject(void);
extern "C" int igTraversalFunctionList_GetVTable(void);
extern "C" void FUN_0019a800(void);
extern "C" void igTraversalFunctionList_Register(void);
extern "C" void thunk_igTraversalFunctionList_GetMetaObject(void);
extern "C" ObjectRefWord *FUN_0019a890(ObjectRefWord *self,int delete_storage);
extern "C" void **FUN_0019a910(void **arg0, int arg1);
extern "C" void **FUN_0019a990(void **arg0, short arg1);
extern "C" void **FUN_0019aa10(struct Ref **self, short flag);
extern "C" void **FUN_0019aa90(void **arg0, long long arg1);
extern "C" O *FUN_0019ab10(O *arg0, short arg1);
extern "C" ObjectRefWord *FUN_0019ab90(ObjectRefWord *self,int delete_storage);
extern "C" int *FUN_0019ac10(int *p);
extern "C" int *FUN_0019ac20(int *p);
extern "C" int *FUN_0019ac30(int *p);
extern "C" int *FUN_0019ac40(int *p);
extern "C" int *FUN_0019ac50(int *p);
extern "C" int *FUN_0019ac60(int *p);
extern "C" int *FUN_0019ac70(int *p);
extern "C" int *FUN_0019ac80(int *p);
extern "C" int *FUN_0019ac90(int *p);
extern "C" int *FUN_0019aca0(int *p);
extern "C" int *FUN_0019acb0(int *p);
extern "C" int *FUN_0019acc0(int *p);
extern "C" int *FUN_0019acd0(int *p);
extern "C" int FUN_0019ace0(int a0);
extern "C" void *FUN_0019acf0(igGroup *arg0);
extern "C" igMetaObject *igSegment_GetMetaObject(void);
extern "C" int igSegment_GetVTable(void);
extern "C" void FUN_0019ae10(void);
extern "C" void igSegment_Register(void);
extern "C" void thunk_igSegment_GetMetaObject(void);
extern "C" void FUN_0019aea0(int arg0);
extern "C" igMetaObject *FUN_0019aee0(void);
extern "C" igMetaObject *igSceneInfo_GetMetaObject(void);
extern "C" int igSceneInfo_GetVTable(void);
extern "C" void *FUN_0019b040(igSceneInfo *arg0, short arg1);
extern "C" void **FUN_0019b1f0(void **arg0, short arg1);
extern "C" void FUN_0019b270(void);
extern "C" void igSceneInfo_Register(void);
extern "C" void thunk_igSceneInfo_GetMetaObject(void);
extern "C" void igSceneInfo_InitFields(void);
extern "C" igMetaObject *FUN_0019b440(void);
extern "C" igMetaObject *igProjectiveShadowShader_GetMetaObject(void);
extern "C" int igProjectiveShadowShader_GetVTable(void);
extern "C" int *FUN_0019b7e0(int *p);
extern "C" int *FUN_0019b7f0(int *p);
extern "C" void FUN_0019b800(void);
extern "C" void igProjectiveShadowShader_Register(void);
extern "C" void thunk_igProjectiveShadowShader_GetMetaObject(void);
extern "C" void igProjectiveShadowShader_InitFields(void);
extern "C" igMetaObject *igPlanarShadowShader_GetMetaObject(void);
extern "C" int igPlanarShadowShader_GetVTable(void);
extern "C" void *FUN_0019c0e0(struct S_19c0e0 *arg0, short arg1);
extern "C" ObjectRefWord *FUN_0019c1a0(ObjectRefWord *self,int delete_storage);
extern "C" void **FUN_0019c220(void **arg0, short arg1);
extern "C" ObjectRefWord *FUN_0019c2a0(ObjectRefWord *self,int delete_storage);
extern "C" int *FUN_0019c320(int *p);
extern "C" int *FUN_0019c330(int *p);
extern "C" int *FUN_0019c340(int *p);
extern "C" int *FUN_0019c350(int *p);
extern "C" int *FUN_0019c360(int *p);
extern "C" int *FUN_0019c370(int *p);
extern "C" void *FUN_0019c380(void *arg0);
extern "C" void FUN_0019c3f0(void);
extern "C" void igPlanarShadowShader_Register(void);
extern "C" void thunk_igPlanarShadowShader_GetMetaObject(void);
extern "C" igMetaObject *FUN_0019c490(void);
extern "C" void igPlanarShadowShader_InitFields(void);
extern "C" igMetaObject *FUN_0019c6a0(void);
extern "C" igMetaObject *igOverrideAttrSet_GetMetaObject(void);
extern "C" int igOverrideAttrSet_GetVTable(void);
extern "C" void FUN_0019c7b0(void);
extern "C" void igOverrideAttrSet_Register(void);
extern "C" void thunk_igOverrideAttrSet_GetMetaObject(void);
extern "C" struct R **FUN_0019c840(struct R **arg0, short arg1);
extern "C" igMetaObject *FUN_0019c8c0(void);
extern "C" igMetaObject *igNonRefCountedNodeList_GetMetaObject(void);
extern "C" int igNonRefCountedNodeList_GetVTable(void);
extern "C" void FUN_0019c9a0(void);
extern "C" void igNonRefCountedNodeList_Register(void);
extern "C" void thunk_igNonRefCountedNodeList_GetMetaObject(void);
extern "C" igMetaObject *FUN_0019ca30(void);
extern "C" igMetaObject *igNodeListList_GetMetaObject(void);
extern "C" int igNodeListList_GetVTable(void);
extern "C" void FUN_0019cb10(void);
extern "C" void igNodeListList_Register(void);
extern "C" void thunk_igNodeListList_GetMetaObject(void);
extern "C" int FUN_0019cba0(int arg0);
extern "C" igMetaObject *FUN_0019cbe0(void);
extern "C" igMetaObject *igNodeList_GetMetaObject(void);
extern "C" int igNodeList_GetVTable(void);
extern "C" void FUN_0019ccc0(void);
extern "C" void igNodeList_Register(void);
extern "C" void thunk_igNodeList_GetMetaObject(void);
extern "C" igMetaObject *FUN_0019cd50(void);
extern "C" igMetaObject *igNode_GetMetaObject(void);
extern "C" int igNode_GetVTable(void);
extern "C" void FUN_0019cf10(void);
extern "C" void igNode_Register(void);
extern "C" void thunk_igNode_GetMetaObject(void);
extern "C" void igNode_InitFields(void);
extern "C" void **FUN_0019d0a0(void **arg0, long long arg1);
extern "C" void *FUN_0019d120(struct S_19d120 *arg0, short arg1);
extern "C" igMetaObject *FUN_0019d1e0(void);
extern "C" int *FUN_0019d1f0(int *p);
extern "C" void **FUN_0019d200(void **arg0, int arg1);
extern "C" igMetaObject *FUN_0019d280(void);
extern "C" igMetaObject *igModelViewMatrixBoneSelectList_561880_GetMetaObject(void);
extern "C" int igModelViewMatrixBoneSelectList_561880_GetVTable(void);
extern "C" void FUN_0019d360(void);
extern "C" void igModelViewMatrixBoneSelectList_561880_Register(void);
extern "C" void thunk_igModelViewMatrixBoneSelectList_561880_GetMetaObject(void);
extern "C" void FUN_0019d3f0(int arg0);
extern "C" igMetaObject *igModelViewMatrixBoneSelect_GetMetaObject(void);
extern "C" int igModelViewMatrixBoneSelect_GetVTable(void);
extern "C" void FUN_0019d4f0(void);
extern "C" void igModelViewMatrixBoneSelect_Register(void);
extern "C" void thunk_igModelViewMatrixBoneSelect_GetMetaObject(void);
extern "C" void igModelViewMatrixBoneSelect_InitFields(void);
extern "C" igMetaObject *igLod_GetMetaObject(void);
extern "C" int igLod_GetVTable(void);
extern "C" void FUN_0019d710(void);
extern "C" void igLod_Register(void);
extern "C" void thunk_igLod_GetMetaObject(void);
extern "C" void igLod_InitFields(void);
extern "C" igMetaObject *igLightStateSet_GetMetaObject(void);
extern "C" int igLightStateSet_GetVTable(void);
extern "C" void **FUN_0019d9e0(void **arg0, short arg1);
extern "C" void FUN_0019da60(void);
extern "C" void igLightStateSet_Register(void);
extern "C" void thunk_igLightStateSet_GetMetaObject(void);
extern "C" void igLightStateSet_InitFields(void);
extern "C" igMetaObject *FUN_0019dbb0(void);
extern "C" igMetaObject *igLightSet_GetMetaObject(void);
extern "C" int igLightSet_GetVTable(void);
extern "C" void FUN_0019dcd0(void);
extern "C" void igLightSet_Register(void);
extern "C" void thunk_igLightSet_GetMetaObject(void);
extern "C" igMetaObject *FUN_0019dd70(void);
extern "C" void igLightSet_InitFields(void);
extern "C" igMetaObject *FUN_0019de30(void);
extern "C" igMetaObject *FUN_0019de40(void);
extern "C" void **FUN_0019de50(struct Ref **self, short flag);
extern "C" void **FUN_0019ded0(void **arg0, long long arg1);
extern "C" O *FUN_0019df50(O *arg0, short arg1);
extern "C" igMetaObject *FUN_0019dfd0(void);
extern "C" igMetaObject *igIntersectTraversal_GetMetaObject(void);
extern "C" int igIntersectTraversal_GetVTable(void);
extern "C" O_19e150 *FUN_0019e150(O_19e150 *arg0, short arg1);
extern "C" void **FUN_0019e340(void **arg0, short arg1);
extern "C" void **FUN_0019e3c0(void **arg0, short arg1);
extern "C" void FUN_0019e440(void);
extern "C" void igIntersectTraversal_Register(void);
extern "C" void thunk_igIntersectTraversal_GetMetaObject(void);
extern "C" igMetaObject *FUN_0019e4e0(void);
extern "C" void igIntersectTraversal_InitFields(void);
extern "C" void FUN_0019e640(void);
extern "C" void thunk_FUN_001ce740(void);
extern "C" void igProbe_Create(int arg0);
extern "C" igMetaObject *FUN_0019e6c0(void);
extern "C" igMetaObject *igProbe_GetMetaObject(void);
extern "C" int igProbe_GetVTable(void);
extern "C" void FUN_0019e890(void);
extern "C" void igProbe_Register(void);
extern "C" void thunk_igProbe_GetMetaObject(void);
extern "C" void igProbe_InitFields(void);
extern "C" igMetaObject *FUN_0019ea00(void);
extern "C" igMetaObject *igInterpretedShaderData_GetMetaObject(void);
extern "C" int igInterpretedShaderData_GetVTable(void);
extern "C" ObjectRefWord *FUN_0019eb40(ObjectRefWord *self,int delete_storage);
extern "C" void FUN_0019ebc0(void);
extern "C" void igInterpretedShaderData_Register(void);
extern "C" void thunk_igInterpretedShaderData_GetMetaObject(void);
extern "C" int FUN_0019ec60(void);
extern "C" void igInterpretedShaderData_InitFields(void);
extern "C" igMetaObject *igIniShaderFactory_GetMetaObject(void);
extern "C" int igIniShaderFactory_GetVTable(void);
extern "C" void **FUN_0019eeb0(void **arg0, short arg1);
extern "C" ObjectRefWord *FUN_0019ef30(ObjectRefWord *self,int delete_storage);
extern "C" void FUN_0019efb0(void);
extern "C" void igIniShaderFactory_Register(void);
extern "C" void thunk_igIniShaderFactory_GetMetaObject(void);
extern "C" igMetaObject *FUN_0019f050(void);
extern "C" void igIniShaderFactory_InitFields(void);
extern "C" void igGroup_CreateInstance(int arg0);
extern "C" igMetaObject *FUN_0019f210(void);
extern "C" igMetaObject *igGroup_GetMetaObject(void);
extern "C" int igGroup_GetVTable(void);
extern "C" void FUN_0019f330(void);
extern "C" void igGroup_Register(void);
extern "C" void thunk_igGroup_GetMetaObject(void);
extern "C" void igGroup_InitFields(void);
extern "C" int FUN_0019f480(int arg0);
extern "C" igMetaObject *FUN_0019f4c0(void);
extern "C" igMetaObject *igGraphPathList_GetMetaObject(void);
extern "C" int igGraphPathList_GetVTable(void);
extern "C" void FUN_0019f5a0(void);
extern "C" void igGraphPathList_Register(void);
extern "C" void thunk_igGraphPathList_GetMetaObject(void);
extern "C" int igGraphPath_Create(int arg0);
extern "C" igMetaObject *FUN_0019f670(void);
extern "C" igMetaObject *igGraphPath_GetMetaObject(void);
extern "C" int igGraphPath_GetVTable(void);
extern "C" void FUN_0019f7a0(void);
extern "C" void igGraphPath_Register(void);
extern "C" void thunk_igGraphPath_GetMetaObject(void);
extern "C" void igGraphPath_InitFields(void);
extern "C" igMetaObject *FUN_0019f930(void);
extern "C" igMetaObject *igGeometryList_GetMetaObject(void);
extern "C" int igGeometryList_GetVTable(void);
extern "C" void FUN_0019fa10(void);
extern "C" void igGeometryList_Register(void);
extern "C" void thunk_igGeometryList_GetMetaObject(void);
extern "C" void FUN_0019faa0(int arg0);
extern "C" igMetaObject *FUN_0019fae0(void);
extern "C" igMetaObject *igGeometry_GetMetaObject(void);
extern "C" int igGeometry_GetVTable(void);
extern "C" void FUN_0019fc00(void);
extern "C" void igGeometry_Register(void);
extern "C" void thunk_igGeometry_GetMetaObject(void);
extern "C" void FUN_0019fca0(void);
extern "C" void thunk_FUN_001c51d0(void);
extern "C" void FUN_0019fde0(int arg0);
extern "C" igMetaObject *igFrustCullTraversal_GetMetaObject(void);
extern "C" int igFrustCullTraversal_GetVTable(void);
extern "C" struct R **FUN_0019ff10(struct R **arg0, short arg1);
extern "C" struct T_19fde0 **FUN_0019ff90(struct T_19fde0 **arg0, short arg1);
extern "C" void **FUN_001a0010(void **arg0, int arg1);
extern "C" void **FUN_001a0090(void **arg0, short arg1);
extern "C" void **FUN_001a0110(struct Ref **self, short flag);
extern "C" void **FUN_001a0190(void **arg0, long long arg1);
extern "C" O *FUN_001a0210(O *arg0, short arg1);
extern "C" void **FUN_001a0290(void **arg0, short arg1);
extern "C" void **FUN_001a0310(void **arg0, short arg1);
extern "C" ObjectRefWord *FUN_001a0390(ObjectRefWord *self,int delete_storage);
extern "C" void **FUN_001a0410(void **arg0, short arg1);
extern "C" ObjectRefWord *FUN_001a0490(ObjectRefWord *self,int delete_storage);
extern "C" struct R **FUN_001a0510(struct R **arg0, short arg1);
extern "C" ObjectRefWord *FUN_001a0590(ObjectRefWord *self,int delete_storage);
extern "C" void **FUN_001a0610(void **arg0, int arg1);
extern "C" void **FUN_001a0690(void **arg0, short arg1);
extern "C" void **FUN_001a0710(struct Ref **self, short flag);
extern "C" void **FUN_001a0790(void **arg0, long long arg1);
extern "C" O *FUN_001a0810(O *arg0, short arg1);
extern "C" ObjectRefWord *FUN_001a0890(ObjectRefWord *self,int delete_storage);
extern "C" Obj_19fde0 *FUN_001a0910(Obj_19fde0 *arg0, short arg1);
extern "C" void **FUN_001a1000(void **arg0, short arg1);
extern "C" int *FUN_001a1080(int *p);
extern "C" int *FUN_001a1090(int *p);
extern "C" void *FUN_001a10a0(igCommonTraversal *arg0);
extern "C" void FUN_001a1170(void);
extern "C" void igFrustCullTraversal_Register(void);
extern "C" void thunk_igFrustCullTraversal_GetMetaObject(void);
extern "C" igMetaObject *FUN_001a1210(void);
extern "C" void igFrustCullTraversal_InitFields(void);
extern "C" void FUN_001a13a0(void);
extern "C" void thunk_FUN_001c45d0(void);
extern "C" igMetaObject *FUN_001a13e0(void);
extern "C" igMetaObject *igEnvironmentMapShader2List_GetMetaObject(void);
extern "C" int igEnvironmentMapShader2List_GetVTable(void);
extern "C" void FUN_001a14c0(void);
extern "C" void igEnvironmentMapShader2List_Register(void);
extern "C" void thunk_igEnvironmentMapShader2List_GetMetaObject(void);
extern "C" igMetaObject *igEnvironmentMapShader2_GetMetaObject(void);
extern "C" void FUN_001a15a0(void);
extern "C" void igEnvironmentMapShader2_Register(void);
extern "C" void thunk_igEnvironmentMapShader2_GetMetaObject(void);
extern "C" void igEnvironmentMapShader2_InitFields(void);
extern "C" void thunk_igPsx2EnvironmentMapShader_GetMetaObject(void);
extern "C" igMetaObject *FUN_001a18b0(void);
extern "C" int igEnbayaTransformSource_GetVTable(void);
extern "C" void FUN_001a1990(void);
extern "C" void igEnbayaTransformSource_Register(void);
extern "C" void thunk_FUN_001a18b0(void);
extern "C" void igEnbayaTransformSource_InitFields(void);
extern "C" int igEnbayaContextPool_Create(int allocator);
extern "C" igMetaObject *igEnbayaContextPool_GetMetaObject(void);
extern "C" int igEnbayaContextPool_GetVTable(void);
extern "C" void igEnbayaContextPool_RunStaticInit(void);
extern "C" void igEnbayaContextPool_Register(void);
extern "C" void thunk_igEnbayaContextPool_GetMetaObject(void);
extern "C" void igEnbayaContextPool_InitFields(void);
extern "C" igMetaObject *igEnbayaAnimationState_GetMetaObject(void);
extern "C" int igEnbayaAnimationState_GetVTable(void);
extern "C" void FUN_001a2030(void);
extern "C" void igEnbayaAnimationState_Register(void);
extern "C" void thunk_igEnbayaAnimationState_GetMetaObject(void);
extern "C" igMetaObject *FUN_001a20d0(void);
extern "C" void igEnbayaAnimationState_InitFields(void);
extern "C" void FUN_001a2190(void);
extern "C" void FUN_001a21a0(void);
extern "C" int FUN_001a21b0(void);
extern "C" igMetaObject *FUN_001a2210(void);
extern "C" igMetaObject *igEnbayaAnimationSource_GetMetaObject(void);
extern "C" int igEnbayaAnimationSource_GetVTable(void);
extern "C" void FUN_001a22f0(void);
extern "C" void igEnbayaAnimationSource_Register(void);
extern "C" void thunk_igEnbayaAnimationSource_GetMetaObject(void);
extern "C" void igEnbayaAnimationSource_InitFields(void);
extern "C" void FUN_001a24d0(void);
extern "C" void FUN_001a24e0(void);
extern "C" igMetaObject *FUN_001a24f0(void);
extern "C" igMetaObject *igCompressedTransformSequence1_5Data_GetMetaObject(void);
extern "C" int igCompressedTransformSequence1_5Data_GetVTable(void);
extern "C" void FUN_001a2640(void);
extern "C" void igCompressedTransformSequence1_5Data_Register(void);
extern "C" void thunk_igCompressedTransformSequence1_5Data_GetMetaObject(void);
extern "C" void igCompressedTransformSequence1_5Data_InitFields(void);
extern "C" igMetaObject *igCompressedAnimationSequenceQS_GetMetaObject(void);
extern "C" int igCompressedAnimationSequenceQS_GetVTable(void);
extern "C" void FUN_001a2940(void);
extern "C" void igCompressedAnimationSequenceQS_Register(void);
extern "C" void thunk_igCompressedAnimationSequenceQS_GetMetaObject(void);
extern "C" void igCompressedAnimationSequenceQS_InitFields(void);
extern "C" void **FUN_001a2b40(void **arg0, short arg1);
extern "C" ObjectRefWord *FUN_001a2bc0(ObjectRefWord *self,int delete_storage);
extern "C" int *FUN_001a2c40(int *p);
extern "C" int *FUN_001a2c50(int *p);
extern "C" int *FUN_001a2c60(int *p);
extern "C" int FUN_001a2c70(int arg0);
extern "C" igMetaObject *igBlendListRecord_GetMetaObject(void);
extern "C" int igBlendListRecord_GetVTable(void);
extern "C" void FUN_001a2d90(void);
extern "C" void igBlendListRecord_Register(void);
extern "C" void thunk_igBlendListRecord_GetMetaObject(void);
extern "C" void igBlendListRecord_InitFields(void);
extern "C" void FUN_001a2ef0(int arg0);
extern "C" igMetaObject *igCompileTraversal_GetMetaObject(void);
extern "C" int igCompileTraversal_GetVTable(void);
extern "C" struct R **FUN_001a30c0(struct R **arg0, short arg1);
extern "C" int *FUN_001a3140(int *p);
extern "C" int *FUN_001a3150(int *p);
extern "C" int *FUN_001a3160(int *p);
extern "C" void FUN_001a3170(void);
extern "C" void igCompileTraversal_Register(void);
extern "C" void thunk_igCompileTraversal_GetMetaObject(void);
extern "C" void igCompileTraversal_InitFields(void);
extern "C" void FUN_001a33e0(void);
extern "C" void thunk_FUN_001bb230(void);
extern "C" igMetaObject *FUN_001a3420(void);
extern "C" igMetaObject *igCompiledTransformList_GetMetaObject(void);
extern "C" int igCompiledTransformList_GetVTable(void);
extern "C" void FUN_001a3500(void);
extern "C" void igCompiledTransformList_Register(void);
extern "C" void thunk_igCompiledTransformList_GetMetaObject(void);
extern "C" int FUN_001a3590(int arg0);
extern "C" igMetaObject *igCompiledTransform_GetMetaObject(void);
extern "C" int igCompiledTransform_GetVTable(void);
extern "C" void FUN_001a3700(void);
extern "C" void igCompiledTransform_Register(void);
extern "C" void thunk_igCompiledTransform_GetMetaObject(void);
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
extern "C" int *FUN_001a3cc0(void *p);
extern "C" int *FUN_001a3cd0(void *p);
extern "C" int *FUN_001a3ce0(void *p);
extern "C" int *FUN_001a3cf0(void *p);
extern "C" int *FUN_001a3d00(void *p);
extern "C" int *FUN_001a3d10(void *p);
extern "C" int *FUN_001a3d20(void *p);
extern "C" int *FUN_001a3d30(void *p);
extern "C" int *FUN_001a3d40(void *p);
extern "C" int *FUN_001a3d50(void *p);
extern "C" int *FUN_001a3d60(void *p);
extern "C" int *FUN_001a3d70(void *p);
extern "C" int *FUN_001a3d80(void *p);
extern "C" void *FUN_001a3d90(igTraversal *arg0);
extern "C" void FUN_001a3dd0(void);
extern "C" void igCommonTraversal_Register(void);
extern "C" void thunk_igCommonTraversal_GetMetaObject(void);
extern "C" void igCommonTraversal_InitFields(void);
extern "C" void FUN_001a44d0(void);
extern "C" void thunk_FUN_001b6c50(void);
extern "C" int *FUN_001a4510(int *p);
extern "C" void FUN_001a4520(int arg0);
extern "C" igMetaObject *FUN_001a4560(void);
extern "C" igMetaObject *igCamera_GetMetaObject(void);
extern "C" int igCamera_GetVTable(void);
extern "C" void FUN_001a4670(void);
extern "C" void igCamera_Register(void);
extern "C" void thunk_igCamera_GetMetaObject(void);
extern "C" void igCamera_InitFields(void);
extern "C" int FUN_001a47d0(void);
extern "C" void FUN_001a4830(int arg0);
extern "C" igMetaObject *igBoundingBoxesMaker_GetMetaObject(void);
extern "C" int igBoundingBoxesMaker_GetVTable(void);
extern "C" void FUN_001a4970(void);
extern "C" void igBoundingBoxesMaker_Register(void);
extern "C" void thunk_igBoundingBoxesMaker_GetMetaObject(void);
extern "C" void igBoundingBoxesMaker_InitFields(void);
extern "C" igMetaObject *igBlendMatrixSelect_GetMetaObject(void);
extern "C" int igBlendMatrixSelect_GetVTable(void);
extern "C" void FUN_001a4c50(void);
extern "C" void igBlendMatrixSelect_Register(void);
extern "C" void thunk_igBlendMatrixSelect_GetMetaObject(void);
extern "C" void igBlendMatrixSelect_InitFields(void);
extern "C" igMetaObject *FUN_001a4d90(void);
extern "C" igMetaObject *igBitMask_GetMetaObject(void);
extern "C" int igBitMask_GetVTable(void);
extern "C" void FUN_001a4e70(void);
extern "C" void igBitMask_Register(void);
extern "C" void thunk_igBitMask_GetMetaObject(void);
extern "C" int FUN_001a4f00(void);
extern "C" void igBitMask_InitFields(void);
extern "C" igMetaObject *igBillboard_GetMetaObject(void);
extern "C" int igBillboard_GetVTable(void);
extern "C" void FUN_001a5050(void);
extern "C" void igBillboard_Register(void);
extern "C" void thunk_igBillboard_GetMetaObject(void);
extern "C" void igBillboard_InitFields(void);
extern "C" int FUN_001a51d0(int arg0);
extern "C" igMetaObject *igNonRefCountedAttrStackManagerList_GetMetaObject(void);
extern "C" int igNonRefCountedAttrStackManagerList_GetVTable(void);
extern "C" void FUN_001a52a0(void);
extern "C" void igNonRefCountedAttrStackManagerList_Register(void);
extern "C" void thunk_igNonRefCountedAttrStackManagerList_GetMetaObject(void);
extern "C" igMetaObject *FUN_001a5330(void);
extern "C" igMetaObject *igAttrStackManager_GetMetaObject(void);
extern "C" int igAttrStackManager_GetVTable(void);
extern "C" void **FUN_001a5540(void **arg0, long long arg1);
extern "C" void **FUN_001a55c0(void **arg0, int arg1);
extern "C" void FUN_001a5640(void);
extern "C" void igAttrStackManager_Register(void);
extern "C" void thunk_igAttrStackManager_GetMetaObject(void);
extern "C" void igAttrStackManager_InitFields(void);
extern "C" void FUN_001a58e0(void);
extern "C" void thunk_FUN_001afb00(void);
extern "C" igMetaObject *FUN_001a5900(void);
extern "C" igMetaObject *igAttrStackList_GetMetaObject(void);
extern "C" int igAttrStackList_GetVTable(void);
extern "C" void FUN_001a59e0(void);
extern "C" void igAttrStackList_Register(void);
extern "C" void thunk_igAttrStackList_GetMetaObject(void);
extern "C" int FUN_001a5a70(int arg0);
extern "C" igMetaObject *igAttrStack_GetMetaObject(void);
extern "C" int igAttrStack_GetVTable(void);
extern "C" void FUN_001a5b90(void);
extern "C" void igAttrStack_Register(void);
extern "C" void thunk_igAttrStack_GetMetaObject(void);
extern "C" void igAttrStack_InitFields(void);
extern "C" void FUN_001a5d30(int arg0);
extern "C" igMetaObject *FUN_001a5d70(void);
extern "C" igMetaObject *igAttrSet_GetMetaObject(void);
extern "C" int igAttrSet_GetVTable(void);
extern "C" void FUN_001a5e90(void);
extern "C" void igAttrSet_Register(void);
extern "C" void thunk_igAttrSet_GetMetaObject(void);
extern "C" void igAttrSet_InitFields(void);
extern "C" igMetaObject *FUN_001a5fe0(void);
extern "C" igMetaObject *igAppearanceList_GetMetaObject(void);
extern "C" int igAppearanceList_GetVTable(void);
extern "C" void FUN_001a60c0(void);
extern "C" void igAppearanceList_Register(void);
extern "C" void thunk_igAppearanceList_GetMetaObject(void);
extern "C" igMetaObject *FUN_001a6150(void);
extern "C" igMetaObject *igAppearance_GetMetaObject(void);
extern "C" int igAppearance_GetVTable(void);
extern "C" void **FUN_001a62d0(void **arg0, short arg1);
extern "C" void **FUN_001a6350(struct Ref **self, short flag);
extern "C" void **FUN_001a63d0(void **arg0, long long arg1);
extern "C" void FUN_001a6450(void);
extern "C" void igAppearance_Register(void);
extern "C" void thunk_igAppearance_GetMetaObject(void);
extern "C" void igAppearance_InitFields(void);
extern "C" igMetaObject *FUN_001a6600(void);
extern "C" igMetaObject *igAnimationSystem_GetMetaObject(void);
extern "C" void FUN_001a66a0(void);
extern "C" void igAnimationSystem_Register(void);
extern "C" void thunk_igAnimationSystem_GetMetaObject(void);
extern "C" void igAnimationSystem_InitFields(void);
extern "C" int igAnimationStatePool_Create(int allocator);
extern "C" igMetaObject *igAnimationStatePool_GetMetaObject(void);
extern "C" int igAnimationStatePool_GetVTable(void);
extern "C" void igAnimationStatePool_RunStaticInit(void);
extern "C" void igAnimationStatePool_Register(void);
extern "C" void thunk_igAnimationStatePool_GetMetaObject(void);
extern "C" igMetaObject *FUN_001a6920(void);
extern "C" igMetaObject *igAnimationStateList_GetMetaObject(void);
extern "C" int igAnimationStateList_GetVTable(void);
extern "C" void FUN_001a6a00(void);
extern "C" void igAnimationStateList_Register(void);
extern "C" void thunk_igAnimationStateList_GetMetaObject(void);
extern "C" int FUN_001a6a90(void);
extern "C" int FUN_001a6af0(void);
extern "C" int FUN_001a6b50(void);
extern "C" void FUN_001a6bb0(int arg0);
extern "C" igMetaObject *FUN_001a6bf0(void);
extern "C" igMetaObject *igAnimationState_GetMetaObject(void);
extern "C" int igAnimationState_GetVTable(void);
extern "C" void FUN_001a6dc0(void);
extern "C" void igAnimationState_Register(void);
extern "C" void thunk_igAnimationState_GetMetaObject(void);
extern "C" void igAnimationState_InitFields(void);
extern "C" igMetaObject *igAnimationSequence_GetMetaObject(void);
extern "C" void FUN_001a7080(void);
extern "C" void igAnimationSequence_Register(void);
extern "C" void thunk_igAnimationSequence_GetMetaObject(void);
extern "C" igMetaObject *FUN_001a7100(void);
extern "C" igMetaObject *igAnimationHierarchy_GetMetaObject(void);
extern "C" void FUN_001a71a0(void);
extern "C" void igAnimationHierarchy_Register(void);
extern "C" void thunk_igAnimationHierarchy_GetMetaObject(void);
extern "C" void igAnimationHierarchy_InitFields(void);
extern "C" igMetaObject *FUN_001a72d0(void);
extern "C" igMetaObject *igAnimationModifierList_GetMetaObject(void);
extern "C" int igAnimationModifierList_GetVTable(void);
extern "C" void FUN_001a73b0(void);
extern "C" void igAnimationModifierList_Register(void);
extern "C" void thunk_igAnimationModifierList_GetMetaObject(void);
extern "C" int FUN_001a7440(void);
extern "C" igMetaObject *igAnimationModifier_GetMetaObject(void);
extern "C" int igAnimationModifier_GetVTable(void);
extern "C" O *FUN_001a7580(O *arg0, short arg1);
extern "C" void FUN_001a7600(void);
extern "C" void igAnimationModifier_Register(void);
extern "C" void thunk_igAnimationModifier_GetMetaObject(void);
extern "C" void igAnimationModifier_InitFields(void);
extern "C" igMetaObject *FUN_001a7780(void);
extern "C" igMetaObject *igAnimationDatabase_GetMetaObject(void);
extern "C" int igAnimationDatabase_GetVTable(void);
extern "C" ObjectRefWord *FUN_001a7900(ObjectRefWord *self,int delete_storage);
extern "C" void **FUN_001a7980(void **arg0, short arg1);
extern "C" ObjectRefWord *FUN_001a7a00(ObjectRefWord *self,int delete_storage);
extern "C" void **FUN_001a7a80(void **arg0, short arg1);
extern "C" void FUN_001a7b00(void);
extern "C" void igAnimationDatabase_Register(void);
extern "C" void thunk_igAnimationDatabase_GetMetaObject(void);
extern "C" void igAnimationDatabase_InitFields(void);
extern "C" int igAnimationCombinerBoneInfoPool_Create(int allocator);
extern "C" igMetaObject *igAnimationCombinerBoneInfoPool_GetMetaObject(void);
extern "C" int igAnimationCombinerBoneInfoPool_GetVTable(void);
extern "C" void igAnimationCombinerBoneInfoPool_RunStaticInit(void);
extern "C" void igAnimationCombinerBoneInfoPool_Register(void);
extern "C" void thunk_igAnimationCombinerBoneInfoPool_GetMetaObject(void);
extern "C" igMetaObject *FUN_001a7e20(void);
extern "C" igMetaObject *igAnimationCombinerBoneInfoListList_GetMetaObject(void);
extern "C" int igAnimationCombinerBoneInfoListList_GetVTable(void);
extern "C" void FUN_001a7f00(void);
extern "C" void igAnimationCombinerBoneInfoListList_Register(void);
extern "C" void thunk_igAnimationCombinerBoneInfoListList_GetMetaObject(void);
extern "C" igMetaObject *igAnimationCombinerBoneInfoList_GetMetaObject(void);
extern "C" int igAnimationCombinerBoneInfoList_GetVTable(void);
extern "C" void FUN_001a8020(void);
extern "C" void igAnimationCombinerBoneInfoList_Register(void);
extern "C" void thunk_igAnimationCombinerBoneInfoList_GetMetaObject(void);
extern "C" void FUN_001a80b0(int arg0);
extern "C" igMetaObject *igAnimationCombinerBoneInfo_GetMetaObject(void);
extern "C" int igAnimationCombinerBoneInfo_GetVTable(void);
extern "C" void FUN_001a8220(void);
extern "C" void igAnimationCombinerBoneInfo_Register(void);
extern "C" void thunk_igAnimationCombinerBoneInfo_GetMetaObject(void);
extern "C" void igAnimationCombinerBoneInfo_InitFields(void);
extern "C" igMetaObject *FUN_001a83b0(void);
extern "C" igMetaObject *igAnimationCombinerList_GetMetaObject(void);
extern "C" int igAnimationCombinerList_GetVTable(void);
extern "C" void FUN_001a8490(void);
extern "C" void igAnimationCombinerList_Register(void);
extern "C" void thunk_igAnimationCombinerList_GetMetaObject(void);
extern "C" igMetaObject *FUN_001a8520(void);
extern "C" int igAnimationCombiner_GetVTable(void);
extern "C" void *FUN_001a8620(struct S_1a8620 *arg0, short arg1);
extern "C" ObjectRefWord *FUN_001a8700(ObjectRefWord *self,int delete_storage);
extern "C" struct R **FUN_001a8780(struct R **arg0, short arg1);
extern "C" void FUN_001a8800(void);
extern "C" void igAnimationCombiner_Register(void);
extern "C" void thunk_FUN_001a8520(void);
extern "C" igMetaObject *FUN_001a88a0(void);
extern "C" void igAnimationCombiner_InitFields(void);
extern "C" void thunk_FUN_001abca0(void);
extern "C" void thunk_FUN_001abdf0(void);
extern "C" igMetaObject *FUN_001a8ac0(void);
extern "C" igMetaObject *igAnimationBindingList_GetMetaObject(void);
extern "C" int igAnimationBindingList_GetVTable(void);
extern "C" void FUN_001a8ba0(void);
extern "C" void igAnimationBindingList_Register(void);
extern "C" void thunk_igAnimationBindingList_GetMetaObject(void);
extern "C" int FUN_001a8c30(int arg0);
extern "C" igMetaObject *igAnimationBinding_GetMetaObject(void);
extern "C" int igAnimationBinding_GetVTable(void);
extern "C" void FUN_001a8df0(void);
extern "C" void igAnimationBinding_Register(void);
extern "C" void thunk_igAnimationBinding_GetMetaObject(void);
extern "C" void igAnimationBinding_InitFields(void);
extern "C" igMetaObject *FUN_001a8f80(void);
extern "C" igMetaObject *igAnimationList_GetMetaObject(void);
extern "C" int igAnimationList_GetVTable(void);
extern "C" void FUN_001a9060(void);
extern "C" void igAnimationList_Register(void);
extern "C" void thunk_igAnimationList_GetMetaObject(void);
extern "C" int FUN_001a90f0(int arg0);
extern "C" igMetaObject *FUN_001a9130(void);
extern "C" igMetaObject *igAnimation_GetMetaObject(void);
extern "C" int igAnimation_GetVTable(void);
extern "C" void FUN_001a9290(void);
extern "C" void igAnimation_Register(void);
extern "C" void thunk_igAnimation_GetMetaObject(void);
extern "C" void igAnimation_InitFields(void);
extern "C" igMetaObject *FUN_001a9420(void);
extern "C" igMetaObject *igAnimationTransitionDefinitionList_GetMetaObject(void);
extern "C" int igAnimationTransitionDefinitionList_GetVTable(void);
extern "C" void FUN_001a9500(void);
extern "C" void igAnimationTransitionDefinitionList_Register(void);
extern "C" void thunk_igAnimationTransitionDefinitionList_GetMetaObject(void);
extern "C" igMetaObject *igAnimationTransitionDefinition_GetMetaObject(void);
extern "C" int igAnimationTransitionDefinition_GetVTable(void);
extern "C" void FUN_001a96c0(void);
extern "C" void igAnimationTransitionDefinition_Register(void);
extern "C" void thunk_igAnimationTransitionDefinition_GetMetaObject(void);
extern "C" void igAnimationTransitionDefinition_InitFields(void);
extern "C" igMetaObject *FUN_001a9830(void);
extern "C" igMetaObject *igAnimationTransitionPointList_GetMetaObject(void);
extern "C" int igAnimationTransitionPointList_GetVTable(void);
extern "C" void FUN_001a9910(void);
extern "C" void igAnimationTransitionPointList_Register(void);
extern "C" void thunk_igAnimationTransitionPointList_GetMetaObject(void);
extern "C" igMetaObject *igAnimationTransitionPoint_GetMetaObject(void);
extern "C" int igAnimationTransitionPoint_GetVTable(void);
extern "C" void FUN_001a9a80(void);
extern "C" void igAnimationTransitionPoint_Register(void);
extern "C" void thunk_igAnimationTransitionPoint_GetMetaObject(void);
extern "C" void igAnimationTransitionPoint_InitFields(void);
extern "C" igMetaObject *FUN_001a9bb0(void);
extern "C" igMetaObject *igAnimationTransitionParams_GetMetaObject(void);
extern "C" int igAnimationTransitionParams_GetVTable(void);
extern "C" void FUN_001a9c90(void);
extern "C" void igAnimationTransitionParams_Register(void);
extern "C" void thunk_igAnimationTransitionParams_GetMetaObject(void);
extern "C" void igAnimationTransitionParams_InitFields(void);
extern "C" igMetaObject *FUN_001a9d90(void);
extern "C" igMetaObject *igAnimationTrackList_GetMetaObject(void);
extern "C" int igAnimationTrackList_GetVTable(void);
extern "C" void FUN_001a9e70(void);
extern "C" void igAnimationTrackList_Register(void);
extern "C" void thunk_igAnimationTrackList_GetMetaObject(void);
extern "C" igMetaObject *igAnimationTrack_GetMetaObject(void);
extern "C" int igAnimationTrack_GetVTable(void);
extern "C" void FUN_001aa030(void);
extern "C" void igAnimationTrack_Register(void);
extern "C" void thunk_igAnimationTrack_GetMetaObject(void);
extern "C" void igAnimationTrack_InitFields(void);
extern "C" igMetaObject *igActorInfo_GetMetaObject(void);
extern "C" int igActorInfo_GetVTable(void);
extern "C" void **FUN_001aa290(void **arg0, long long arg1);
extern "C" void **FUN_001aa310(void **arg0, int arg1);
extern "C" void **FUN_001aa390(void **arg0, short arg1);
extern "C" void FUN_001aa410(void);
extern "C" void igActorInfo_Register(void);
extern "C" void thunk_igActorInfo_GetMetaObject(void);
extern "C" void igActorInfo_InitFields(void);
extern "C" igMetaObject *FUN_001aa5c0(void);
extern "C" igMetaObject *igActorList_GetMetaObject(void);
extern "C" int igActorList_GetVTable(void);
extern "C" void FUN_001aa6a0(void);
extern "C" void igActorList_Register(void);
extern "C" void thunk_igActorList_GetMetaObject(void);
extern "C" igMetaObject *FUN_001aa730(void);
extern "C" igMetaObject *igActor_GetMetaObject(void);
extern "C" int igActor_GetVTable(void);
extern "C" void **FUN_001aa8d0(struct Ref **self, short flag);
extern "C" void **FUN_001aa950(void **arg0, long long arg1);
extern "C" O *FUN_001aa9d0(O *arg0, short arg1);
extern "C" void FUN_001aaa50(void);
extern "C" void igActor_Register(void);
extern "C" void thunk_igActor_GetMetaObject(void);
extern "C" void igActor_InitFields(void);
extern "C" igMetaObject *igPsx2EnvironmentMapShader_GetMetaObject(void);
extern "C" int igPsx2EnvironmentMapShader_GetVTable(void);
extern "C" void **FUN_001aaf00(void **arg0, long long arg1);
extern "C" Obj_1aaf80 *FUN_001aaf80(Obj_1aaf80 *arg0, short arg1);
extern "C" void **FUN_001ab380(void **arg0, short arg1);
extern "C" ObjectRefWord *FUN_001ab400(ObjectRefWord *self,int delete_storage);
extern "C" int *FUN_001ab480(int *p);
extern "C" int *FUN_001ab490(int *p);
extern "C" void *FUN_001ab4a0(igEnvironmentMapShader2 *arg0);
extern "C" void FUN_001ab540(void);
extern "C" void igPsx2EnvironmentMapShader_Register(void);
extern "C" igMetaObject *FUN_001ab5d0(void);
extern "C" void igPsx2EnvironmentMapShader_InitFields(void);
extern "C" int FUN_001ab6c0(S_1ab6c0 *arg0, int arg1);
extern "C" int FUN_001ab770(void *arg0, void **arg1, void **arg2);
extern "C" int FUN_001ab8b0(int arg0, int arg1, void **arg2);
extern "C" int FUN_001ab920(const H *a, int id, T_1ab920 **out);
extern "C" void Gap__Sg__igTransformSequence1_5__vfunc_68(S0 *arg0);
extern "C" int Gap__Sg__igTransformSequence1_5__vfunc_50(igTransformSequence1_5 *self, int index);
extern "C" void Gap__Sg__igTransformSequence1_5__vfunc_67(S_1aba30 *arg0);
extern "C" long long Gap__Sg__igTransformSequence1_5__vfunc_65(void *arg0);
extern "C" long long Gap__Sg__igTransformSequence1_5__vfunc_56(igTransformSequence1_5 *arg0, int arg1);
extern "C" int Gap__Sg__igTransformSequence1_5__vfunc_42(igTransformSequence1_5 *self, int index);
extern "C" int Gap__Sg__igTransformSequence1_5__vfunc_41(igTransformSequence1_5 *arg0);
extern "C" int Gap__Sg__igTransformSequence1_5__vfunc_69(void *arg0);
extern "C" unsigned char Gap__Sg__igTransformSequence1_5__vfunc_60(igTransformSequence1_5 *self);
extern "C" int FUN_001abb50(S_1abb50 *arg0, A *arg1);
extern "C" int FUN_001abc20(int *arg0, int arg1);
extern "C" void FUN_001abca0(void);
extern "C" void FUN_001abdf0(void);
extern "C" void *FUN_001abed0(igCollisionGrid *a0, X *a1, void **out);
extern "C" void FUN_001ac040(igAnimationCombiner *arg0, igAnimationState *arg1);
extern "C" long long FUN_001acb10(igTimeView *a);
extern "C" void FUN_001acb50(igAnimationCombiner *c);
extern "C" void Gap__Sg__igAnimationCombiner__vfunc_26(void *arg0, char arg1);
extern "C" int FUN_001ad310(void **arg0, int arg1, int arg2, int arg3, int arg4, int arg5);
extern "C" int Gap__Sg__igCompressedAnimationSequenceQS__vfunc_24(igCompressedSeqView *self);
extern "C" long long Gap__Bec__beHitLandModelTraversal__vfunc_24(TraversalVirtual *t);
extern "C" void Gap__Sg__igAnimationCombiner__vfunc_17(CombinerView *c);
extern "C" void FUN_001ad5c0(A_1ad5c0 *arg0, It *arg1, int arg2);
extern "C" void FUN_001ad770(igAnimationCombiner *a);
extern "C" int FUN_001ad860(igAnimationCombiner *arg0, igAnimationState *arg1);
extern "C" int FUN_001ad990(CombinerBlendView *c, CombinerAnimation *anim, int combineMode, int transitionMode, int status, int *priorities, bool perBone, CombinerBinding *binding);
extern "C" int igAnimationCombiner_RemoveAllStates(CombinerResetView *c);
extern "C" void Vec3f_Set(void *arg0, float fparg0, float fparg1, float fparg2);
extern "C" void FUN_001ae1b0(void *arg0, float fparg0, float fparg1, float fparg2, float fparg3);
extern "C" void **FUN_001ae1d0(void **arg0, void *arg1);
extern "C" void **FUN_001ae250(void **arg0, igObject *arg1);
extern "C" int FUN_001ae2d0(CombinerStateView *c, igPoolObject *state);
extern "C" int igAnimationCombiner_AddAnimationBlend(CombinerBlendView *c, CombinerAnimation *anim, int combineMode, int transitionMode, int status, int *priorities, bool perBone, long long arg7, float fparg0, float fparg1, long long arg_sp0);
extern "C" void Gap__Sg__igAnimationCombiner__vfunc_10(void **arg0);
extern "C" int Gap__Sg__igAnimationCombiner__vfunc_23(void *arg0);
extern "C" void igAnimationCombiner_AddAnimation(CombinerBlendView *c, CombinerAnimation *anim, int combineMode, int transitionMode, int status);
extern "C" int igAnimationCombiner_ResetToPose(CombinerStateView_1ae780 *c, CombinerStateView_1ae780 *from);
extern "C" void *Gap__Sg__igAnimationDatabase__vfunc_24(O_1aea60 *arg0, char *arg1);
extern "C" int FUN_001aedd0(void *self, igTDataList<AnimDbRecord *> *list, int file, AnimDbRecord *object);
extern "C" int Gap__Sg__igAnimationDatabase__vfunc_23(AnimDbRec *db, int file, AnimDbObject *obj);
extern "C" void igAnimationState_UpdateLocalTime(igAnimationState *s, long long t);
extern "C" void Gap__Sg__igAnimationState__vfunc_23(void);
extern "C" void Gap__Sg__igAnimationState__vfunc_24(void);
extern "C" void Gap__Sg__igAnimationState__vfunc_25(void);
extern "C" void Gap__Sg__igAnimationState__vfunc_26(void);
extern "C" int FUN_001af620(igAppearanceView *a, void *t);
extern "C" int FUN_001af7a0(int *p);
extern "C" int FUN_001af7b0(void *arg0, int arg1);
extern "C" void Gap__Sg__igAttrSet__vfunc_31(S_1af7e0 *arg0);
extern "C" void FUN_001af860(igAttrStack *arg0);
extern "C" void Gap__Sg__igAttrStackManager__vfunc_23(struct O_1af890 *arg0);
extern "C" void Gap__Sg__igAttrStackManager__vfunc_09(unsigned char *arg0, int arg1);
extern "C" void Gap__Sg__igAttrStackManager__vfunc_10(int arg0);
extern "C" void FUN_001afb00(void);
extern "C" void FUN_001afb60(char *arg0);
extern "C" void FUN_001afc90(AttrManagerRec *m, AttrObj *meta);
extern "C" void FUN_001b0000(T_1b0000 *arg0, int arg1, Obj_1b0000 *arg2, Obj_1b0000 *arg3);
extern "C" void FUN_001b0250(PendingValueCollector *arg0, PendingIntList *arg1);
extern "C" void FUN_001b0440(int a0, int a1);
extern "C" void FUN_001b0450(A_1b0450 *arg0, Rc_1b0450 *arg1);
extern "C" void FUN_001b0dc0(O_1b0dc0 *arg0);
extern "C" void FUN_001b1030(igAttrStackManager *self, igAttr *attr);
extern "C" void FUN_001b1100(struct A_1b1100 *arg0, struct B_1b1100 *arg1);
extern "C" void FUN_001b11b0(struct A_1b11b0 *arg0, struct B_1b11b0 *arg1);
extern "C" void FUN_001b1250(struct A_1b1250 *arg0, struct B_1b1250 *arg1, int arg2);
extern "C" void igAttrStackManager_PushOverrideAttr(igAttrStackManager *self, igAttr *attr);
extern "C" void igAttrStackManager_PopOverrideAttr(struct A_1b13d0 *arg0, struct B_1b13d0 *arg1);
extern "C" void igAttrStackManager_MarkStackChanged(struct A_1b1490 *arg0, struct B_1b1490 *arg1, int arg2);
extern "C" void igBitMask_SetAll(igDataList *arg0);
extern "C" void igBitMask_ClearAll(igDataList *arg0);
extern "C" void igBitMask_SetBitCount(void *arg, unsigned int bits);
extern "C" void FUN_001b21d0(A_1b21d0 *arg0, V3_1b21d0 *arg1, V3_1b21d0 *arg2);
extern "C" void FUN_001b23b0(int *arg0, int *arg1);
extern "C" int FUN_001b23e0(int arg0, Y *arg1);
extern "C" int FUN_001b24d0(int arg0, int arg1);
extern "C" bool igGeometry_ExtendBound(int arg0, void *arg1);
extern "C" int igTransform_ExtendBound(int arg0, void *arg1, long long time);
extern "C" void Gap__Core__igObject__vfunc_37(void *self, int arg1);
extern "C" int igTransformSequence_ExtendBound(AABoxFields *arg0, TransformInputView *arg1);
extern "C" int FUN_001b2ed0(int arg0, int arg1);
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
extern "C" void FUN_001b68b0(int arg0);
extern "C" void FUN_001b68c0(void *self, void *meta);
extern "C" void Gap__Sg__igCommonTraversal__vfunc_09(igCommonTraversal *arg0, int arg1);
extern "C" void FUN_001b6be0(void);
extern "C" void FUN_001b6c50(void);
extern "C" int Gap__Core__igObject__vfunc_08();
extern "C" int Gap__Sg__igCommonTraversal__vfunc_30(igCommonTraversalView *self);
extern "C" void FUN_001b6cd0(int a0, float, float, float, float, float, float);
extern "C" void FUN_001b6ce0(void *arg0, float fparg0, float fparg1, float fparg2, float fparg3, float fparg4);
extern "C" void Gap__Sg__igCommonTraversal__vfunc_31(A_1b6e20 *arg0);
extern "C" void FUN_001b6ee0(int arg0, int *arg1);
extern "C" void FUN_001b6f30(A_1b6f30 *arg0, R_1b6f30 *arg1, R_1b6f30 *arg2);
extern "C" void Gap__Sg__igCommonTraversal__vfunc_28(O_1b7010 *arg0, R_1b7010 *arg1);
extern "C" V128 *FUN_001b7330(O_1b7330 *arg0, float *arg1);
extern "C" void FUN_001b73d0(struct S_1b73d0 *arg0);
extern "C" void Gap__Sg__igCommonTraversal__vfunc_23(igCommonTraversalOps *t, int root);
extern "C" void Gap__Sg__igCommonTraversal__vfunc_32(void *arg0, long long arg1);
extern "C" void Gap__Sg__igCommonTraversal__vfunc_24(igCommonTraversal *t, int arg1);
extern "C" void Gap__Sg__igCommonTraversal__vfunc_33(void *arg0);
extern "C" void FUN_001b7740(void **arg0, void **arg1);
extern "C" void FUN_001b7770(igCommonTraversal *self, int name, int value);
extern "C" igObject *FUN_001b7920(igCommonTraversal *self, int name);
extern "C" int FUN_001b7af0(void *arg0, int arg1);
extern "C" int FUN_001b7b90(void *t, void *arg);
extern "C" int FUN_001b7c70(void **arg0, void *arg1);
extern "C" int FUN_001b7ce0(C_1b7ce0 *arg0, A_1b7ce0 *arg1);
extern "C" int FUN_001b7d70(void *arg0, void *arg1);
extern "C" int Gap__Sg__igActor__vfunc_37(ActorView *o0, ActorTraversal *t0);
extern "C" void FUN_001b89b0(void *arg0, igCommonTraversal *arg1);
extern "C" int FUN_001b8a00(int *p);
extern "C" int FUN_001b8a10(int *p);
extern "C" void FUN_001b8a20(Src *arg0, Dst *arg1);
extern "C" int FUN_001b8ba0(void *arg0, int arg1);
extern "C" void FUN_001b8c80(void *self, int arg1);
extern "C" void FUN_001b8cf0(igCommonTraversal *arg0, char *arg1);
extern "C" int FUN_001b8de0(Dst_1b8de0 *arg0, Src_1b8de0 *arg1);
extern "C" int FUN_001b8f20(C_1b8f20 *arg0, D *arg1);
extern "C" int FUN_001b99d0(DrawTraversalView *o, SwitchGroupView *g);
extern "C" void FUN_001b9d40(int arg0, int arg1);
extern "C" int FUN_001b9d90(LightTraversalView *o, LightSceneView *scene);
extern "C" int FUN_001b9f00(igCompileTraversal *arg0, igAttrSet *arg1);
extern "C" int FUN_001b9fc0(struct A_1b9fc0 *arg0, struct B_1b9fc0 *arg1);
extern "C" int FUN_001ba080(CullTraversalView *o, CullNodeView *node);
extern "C" int FUN_001ba1a0(int a0, int arg1);
extern "C" int FUN_001ba200(int arg0_, int arg1);
extern "C" int FUN_001ba650(int a0, int arg1);
extern "C" int FUN_001ba880(igCommonTraversal *arg0, VC1 *arg1);
extern "C" void Gap__Sg__igTransformRecorder__vfunc_38(int a0);
extern "C" void Gap__Sg__igTransformRecorder__vfunc_37(void *arg0);
extern "C" int FUN_001baa10(RecorderTraversalView *o, TransformRecorderVisitor *v);
extern "C" int FUN_001bab30(int a0, void **arg1);
extern "C" int FUN_001bac30(int arg0, void **arg1);
extern "C" int FUN_001bac90(int arg0, void **arg1);
extern "C" int FUN_001bacf0(DrawItemSource *arg0, DrawItemIndex *arg1);
extern "C" int FUN_001bae20(CompileTraversalHead *o, BlendNodeView *node);
extern "C" int FUN_001bafb0(int arg0, struct S_1bafb0 *arg1);
class DW4VC_104_3 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual long long vX(); };
struct KeyTrackValue : public igObject { };
extern "C" int FUN_001bb090(S_1e04c0 *self, KeyTrackView *track);
extern "C" void FUN_001bb1f0(int arg0);
extern "C" void FUN_001bb200(void);
extern "C" void FUN_001bb230(void);
extern "C" void Gap__Sg__igCompileTraversal__vfunc_09(C_1bb280 *arg0, int arg1);
extern "C" void Gap__Sg__igCompileTraversal__vfunc_31(char *p);
extern "C" void Gap__Sg__igCompileTraversal__vfunc_10(void **self);
extern "C" void FUN_001bb550(int arg0, int arg1);
extern "C" void Gap__Sg__igCompileTraversal__vfunc_23(igCompileTraversal *self, int arg1);
extern "C" void Gap__Sg__igCompileTraversal__vfunc_24(igCompileTraversal *arg0, int arg1);
extern "C" int FUN_001bbae0(int arg0, int arg1);
extern "C" int FUN_001bcd60(int arg0, int arg1);
extern "C" float FUN_001bcd70(float *arg0, int arg1);
extern "C" int FUN_001bcd80(void *arg0);
extern "C" int FUN_001bcd90(void *arg0);
extern "C" int FUN_001bcda0(void *arg0);
extern "C" int FUN_001bcdb0(void *arg0);
extern "C" int FUN_001bcdc0(void *arg0);
extern "C" int FUN_001bcdd0(void *arg0);
extern "C" int FUN_001bcde0(void *arg0);
extern "C" int FUN_001bcdf0(void *arg0, void **arg1);
extern "C" int FUN_001bce40(A_1bce40 *arg0, int *arg1);
extern "C" int FUN_001bcf70(A_1bcf70 *arg0, B_1bcf70 *arg1);
extern "C" int FUN_001bd0e0(int arg0, void *arg1);
extern "C" int FUN_001bd150(void);
extern "C" int FUN_001bd160(void);
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
extern "C" long long Gap__Sg__igCompressedAnimationSequenceQS__vfunc_42(int *arg0, int arg1);
extern "C" int Gap__Sg__igCompressedAnimationSequenceQS__vfunc_23(O_1bfa60 *a0, int a1, long long a2);
extern "C" int Gap__Sg__igCompressedAnimationSequenceQS__vfunc_35(igCompressedAnimationSequenceQS *self);
extern "C" void FUN_001bfc70(O_1bfc70 *o, long long t, int *a2, int *a3, float *a4, float *a5);
extern "C" void Gap__Sg__igCompressedAnimationSequenceQS__vfunc_48(struct S_1bfe90 *arg0, int *arg1, void *arg2, int *arg3, float fparg0);
extern "C" void Gap__Sg__igCompressedAnimationSequenceQS__vfunc_47(void *arg0, int *arg1, int arg2, int arg3, float fparg0);
extern "C" int Gap__Sg__igCompressedAnimationSequenceQS__vfunc_25(S_1c0010 *arg0, int arg1, long long arg2);
extern "C" int Gap__Sg__igCompressedAnimationSequenceQS__vfunc_27(O_1c00e0 *arg0, int arg1, int arg2, long long arg3);
extern "C" int FUN_001c0240(igTransformSequence1_5 *self);
extern "C" int FUN_001c0390(void *, int);
extern "C" void FUN_001c03a0(DepthOfFieldNode *arg0, A1_1c03a0 *arg1);
extern "C" void FUN_001c07d0(void);
extern "C" void FUN_001c07e0(void);
extern "C" void Gap__Sg__igEnbayaAnimationSource__vfunc_13(void *arg0);
extern "C" int Gap__Sg__igEnbayaAnimationSource__vfunc_23(void **arg0, int arg1, int arg2, int arg3);
extern "C" int Gap__Sg__igEnbayaAnimationSource__vfunc_24(EnbayaSourceSlots24 *o, int a, int b, int c, int d, int e);
extern "C" int Gap__Sg__igEnbayaAnimationSource__vfunc_25(EnbayaSourceView *o, float *out, long long time, int track);
extern "C" int Gap__Sg__igEnbayaAnimationSource__vfunc_26(EnbayaSourceSlots26 *o, int a, int b, int c, int d, int e);
extern "C" int Gap__Sg__igEnbayaAnimationSource__vfunc_27(EnbayaSourceView *o, float *out, float *pos, long long time, int track);
extern "C" int Gap__Sg__igEnbayaAnimationSource__vfunc_28(EnbayaSourceSlots28 *o, int a, int b, int c, int d, int e, int g);
extern "C" void Gap__Sg__igEnbayaAnimationSource__vfunc_17(Obj_1c0e70 *arg0);
extern "C" void FUN_001c0f00(int mode);
extern "C" igMetaObject *FUN_001c10e0(void);
extern "C" void FUN_001c10f0(void);
extern "C" void FUN_001c1100(void);
extern "C" void Gap__Sg__igEnbayaAnimationState__vfunc_17(void **arg0);
extern "C" void Gap__Sg__igEnbayaAnimationState__vfunc_23(igEnbayaAnimationState *arg0);
extern "C" void Gap__Sg__igEnbayaAnimationState__vfunc_24(void *arg0);
extern "C" void Gap__Sg__igEnbayaAnimationState__vfunc_25(void *arg0);
extern "C" void Gap__Sg__igEnbayaAnimationState__vfunc_26(void *arg0);
extern "C" void Gap__Sg__igEnbayaContextPool__vfunc_13(int arg0);
extern "C" void Gap__Sg__igEnbayaContextPool__vfunc_04(Obj_1c1450 *arg0);
extern "C" int FUN_001c1560(T_1c1560 *arg0, int arg1);
extern "C" void FUN_001c17e0(EnbayaContextPoolView *o, int boneCount);
extern "C" void FUN_001c1a80(T_1c1a80 *arg0, int arg1, int arg2);
extern "C" int Gap__Sg__igEnbayaTransformSource__vfunc_23(S_1c1b50 *arg0, int arg1, int arg2);
extern "C" int Gap__Sg__igEnbayaTransformSource__vfunc_24(void *arg0, int a1, int a2, int a3, int a4);
extern "C" int Gap__Sg__igEnbayaTransformSource__vfunc_25(EnbayaTransformSourceView *o, int a, int b);
extern "C" int Gap__Sg__igEnbayaTransformSource__vfunc_26(EnbayaTransformSourceView_1c1bd0 *o, int a, int b, int c, int d);
extern "C" int Gap__Sg__igEnbayaTransformSource__vfunc_27(EnbayaTransformSourceView_1c1bf0 *o, int a, int b, int c);
extern "C" int Gap__Sg__igEnbayaTransformSource__vfunc_28(EnbayaTransformSourceView_1c1c10 *o, int a, int b, int c, int d, int e);
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
    igAttrStackManager_MarkStackChanged((A_1b1490 *)s, (B_1b1490 *)l, idx);
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
    igAttrStackManager_MarkStackChanged((A_1b1490 *)s, (B_1b1490 *)l, idx);
}
extern "C" void FUN_001c2be0(EnvPassShaderView *self, EnvTraversalView *t);
extern "C" void FUN_001c2eb0(S0_1c2eb0 *arg0, Rc *arg1);
extern "C" void FUN_001c2f50(igPsx2EnvironmentMapShader *self, igObject *value);
extern "C" void FUN_001c2fd0(igPsx2EnvironmentMapShader *self, int coordIndex);
extern "C" void FUN_001c2fe0(igPsx2EnvironmentMapShader *self, igObject *value);
extern "C" void FUN_001c3060(igPsx2EnvironmentMapShader *self, int coordIndex);
extern "C" void FUN_001c3070(igPsx2EnvironmentMapShader *self, float reflectionAmount);
extern "C" void FUN_001c3080(igPsx2EnvironmentMapShader *self, char isTransparent);
extern "C" void FUN_001c3090(V_1c3090 *arg0, int arg1);
extern "C" void FUN_001c31d0(void);
extern "C" void FUN_001c3ab0(int width, int height, int bpp, void *face1, void *face0, void *face3, void *face2, void *face5, void *face4, unsigned char *out);
extern "C" int FUN_001c3fd0(float *v);
extern "C" void FUN_001c4590(int arg0);
extern "C" void FUN_001c45a0(void);
extern "C" void FUN_001c45d0(void);
extern "C" void Gap__Sg__igFrustCullTraversal__vfunc_31(igFrustCullTraversal *self);
extern "C" void Gap__Sg__igFrustCullTraversal__vfunc_09(O_1c4650 *arg0, int arg1);
extern "C" void FUN_001c4700(int arg0, int arg1);
extern "C" void Gap__Sg__igFrustCullTraversal__vfunc_24(igCommonTraversal *self, int arg1);
extern "C" void FUN_001c47a0(void *arg0, int arg1, int arg2);
extern "C" int FUN_001c4ac0(CullFrustumView *o, CullBoundsView *b);
extern "C" int FUN_001c5160(S0_1c5160 *arg0, float fparg0);
extern "C" void FUN_001c51b0(int arg0, int arg1, int arg2);
extern "C" void FUN_001c51d0(void);
extern "C" void Gap__Bec__ParticleTimer__vfunc_15(ParticleTimer *arg0);
extern "C" void Gap__Bec__ParticleTimer__vfunc_27(ParticleTimer *arg0, int arg1);
extern "C" void Gap__Bec__ParticleTimer__vfunc_26(ParticleTimer *arg0, int arg1, int arg2);
extern "C" void Gap__Bec__ParticleTimer__vfunc_25(ParticleTimer *arg0, int arg1);
extern "C" void Gap__Bec__ParticleTimer__vfunc_29(ParticleAttributeObj *arg0);
extern "C" void FUN_001c5660(Z_1c5660 *arg0, int arg1, int arg2);
extern "C" int FUN_001c5730(int *p, int);
extern "C" void FUN_001c5740(U_1c5740 *arg0, T_1c5740 *arg1);
extern "C" void igGraphPath_SetNodes(Obj_1c5790 *arg0, int arg1);
extern "C" void FUN_001c5870(void *arg0, int arg1);
extern "C" int FUN_001c58c0(T_1c58c0 *arg0);
extern "C" int igGraphPath_GetTail(void *arg0);
extern "C" int FUN_001c59b0(void *self);
extern "C" int FUN_001c59e0(void *arg0);
extern "C" void FUN_001c59f0(OO *arg0, int arg1, int arg2, int arg3);
extern "C" int Gap__Sg__igNode__vfunc_22(void);
extern "C" void igGraphPath_GetTransform(int arg0, int arg1, int arg2);
extern "C" void FUN_001c5b80(SgLinkNode *o);
extern "C" int igGroup_AppendChild(void *arg0, int arg1);
extern "C" int FUN_001c5d70(T_1c5d70 *self, int a1, O_1c5d70 *a2);
extern "C" void FUN_001c5e20(T_1c5e20 *arg0);
extern "C" Ref_1c5eb0 igGroup_RemoveChildAt(S_1c5eb0 *host, int idx);
extern "C" void FUN_001c6110(O_1c6110 *arg0, int arg1);
extern "C" void FUN_001c6230(struct S_1c6230 *arg0, int arg1, int arg2);
extern "C" int Gap__Sg__igGroup__vfunc_26(void *arg0);
extern "C" int Gap__Sg__igNode__vfunc_26(void **arg0);
extern "C" void FUN_001c6340(int *arg0, int arg1);
extern "C" void Gap__Sg__igNode__vfunc_27(void);
extern "C" void FUN_001c63e0(int arg0, int arg1);
extern "C" void **ObjectRef_Destruct_001c6460(void **arg0, short arg1);
/* A string handed out with a reference already taken; whoever receives it releases it. */
struct RetainedString {
    char *p;
    RetainedString(char *text) : p(text) { if (p != 0) ((int *)p)[-1] = ((int *)p)[-1] + 1; }
};
struct IniStrRef {
    char *p;
    IniStrRef() {}
    IniStrRef(char *text) : p(text) {}
    IniStrRef(const RetainedString &s) : p(s.p) { if (p != 0) ((int *)p)[-1] = ((int *)p)[-1] + 1; }
    IniStrRef(const IniStrRef &o) : p(o.p) { if (p != 0) ((int *)p)[-1] = ((int *)p)[-1] + 1; }
    static inline void Release(char *s) {
        int *x = (int *)s;
        if (x != 0) { int *hd = x - 2; int c = x[-1] - 1; x[-1] = c; if (c == 0) StringChunk_ReleaseHeader(*hd, hd); }
    }
    ~IniStrRef() { Release(p); }
};
extern "C" RetainedString StringList_CopyRetained(igStringRefList *list, int index);
extern "C" IniStrRef FUN_001c6fa0(IniSectionNode *node);
extern "C" void StringList_AppendRetained(igStringRefList *list, const IniStrRef &value);
extern "C" int FUN_001c6520(O_1c6520 *arg0, int arg1);
extern "C" int FUN_001c66c0(Node *self, int force);
extern "C" igSmartPointer<ShaderObject> Gap__Sg__igIniShaderFactory__vfunc_24(Factory *self, const char *name);
extern "C" ObjectRefWord *FUN_001c7600(ObjectRefWord *self,int delete_storage);
extern "C" void igStringMetaField_AssignRetainedToken(igStringMetaField *arg0, int arg1, void **arg2);
extern "C" int FUN_001ca6b0(int *p, int);
extern "C" igSmartPointer<ShaderObject_1ca6c0> FUN_001ca6c0(ShaderProcessorView *self, char *name, unsigned char flag);
extern "C" igMetaObject *Gap__Sg__igShaderProcessor__vfunc_22(void);
class IniFieldTarget {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
    virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual void *getMeta();
};
struct IniItemList { char pad0[8]; int count; char pad1[4]; void **data; };
struct IniFieldView { char pad0[56]; void *refMeta; };
extern "C" void igObjectRefMetaField_Assign(IniFieldView *, IniFieldTarget *, void *);
static inline IniFieldView *asObjectRefField(IniFieldView *f) {
    if (f != 0 && igObject_IsKindOf(f, g_igObjectRefMetaField_metaObject[0]) != 0) {
        return f;
    }
    return 0;
}
static inline void *itemAt(IniItemList *l, int i) { return l->data[i]; }
extern "C" int FUN_001cafc0(struct L_1cafc0 *arg0, IniStrRef name, int arg2);
extern "C" void FUN_001cade0(void *self, IniFieldTarget *target, IniItemList *items, void *names, void *lookup, void *fieldNames);
extern "C" void FUN_001cb010(void *self, IniValueTarget *target, IniValueList *list);
extern "C" void FUN_001cb1f0(void *self, char *name, int ini, int section, DW4VC_96_1 *target, IniValueList *values);
extern "C" void FUN_001cb2d0(void *self, void *types, void *key, void *target);
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
extern "C" igSmartPointer<igObject> FUN_001c8c80(ShaderProcessorView *self, int section, void *key, void *meta, ShaderNameList *shared);
extern "C" void igStringObj_Insert(ShaderStringObject *, void *, int, int);
extern "C" int text_attrs[2];
extern "C" int text_value[4];
extern "C" int text_function[4];
extern "C" int text_shader_childList[4];
extern "C" int text_implementation[4];
extern "C" int text_passes[2];
extern "C" int text_processor[4];
extern "C" int text_useRenderPackage[4];
extern "C" int text_pushAttrs[4];
extern "C" int text_popAttrs[4];
extern "C" int text_childNodes[4];
extern "C" void *g_igAttrList_metaObject[4];
extern "C" IniStrRef FUN_001ccb20(igStringRefList *list);
extern "C" void Gap__Sg__igIniShaderFactory__vfunc_26(int a0);
extern "C" void FUN_001ccd10(IniShaderFactoryView *self, IniNodeList *list);
struct IniShaderFactoryFields { char pad0[20]; int f20; char pad1[4]; int f28; };
struct IniFactoryEntry { char pad0[12]; IniSectionObject *f12; char *f16; };
extern "C" IniNodeList *FUN_002da780(IniSectionObject *);
extern "C" int FUN_002da850(IniSectionObject *, IniNodeList *);
extern "C" IniFactoryEntry *FUN_00307630(int, int);
extern "C" int FUN_00307650(int);
extern "C" void Gap__Sg__igIniShaderFactory__vfunc_27(IniShaderFactoryFields *self);
extern "C" void Gap__Sg__igIniShaderFactory__vfunc_17(void *arg0);
extern "C" void Gap__Sg__igIniShaderFactory__vfunc_18(void *arg0);
extern "C" int FUN_001cd150(IniDocument **out, IniFactoryState *self, char *name);
extern "C" igSmartPointer<IniSectionText> FUN_001cdbb0(IniFactoryView *self, char *name);
struct IniHeldObject { int vt; int refs; };
struct IniFactoryBinding { char pad[44]; IniHeldObject *r44; IniHeldObject *r48; };
extern "C" bool Gap__Sg__igIniShaderFactory__vfunc_23(IniFactoryBinding *self, int a1, IniHeldObject *a2, int a3);
extern "C" void Gap__Core__igFolder__vfunc_25(void **arg0);
extern "C" int FUN_001ce400(IniStringObject **out, char *path);
extern "C" int FUN_001ce640(void *arg0, int arg1);
extern "C" void FUN_001ce660(int arg0);
extern "C" void Gap__Bec__beHitLandModelTraversal__vfunc_07(beHitLandModelTraversal *arg0, int arg1);
extern "C" int Gap__Core__igObject__vfunc_08__001ce700();
extern "C" int Gap__Core__igObject__vfunc_08__001d3390(void *);
extern "C" void Gap__Core__igObject__vfunc_36(igTransform *self, int target);
extern "C" void FUN_001ce710(void);
extern "C" void FUN_001ce740(void);
extern "C" void FUN_001ce790(int arg0, int arg1);
extern "C" void Gap__Bec__beHitLandModelTraversal__vfunc_11(beHitLandModelTraversal *arg0);
extern "C" void igIntersectTraversal_ResetStacks(TraversalMatrixState *self);
extern "C" void Gap__Bec__beHitLandModelTraversal__vfunc_21(void *self, int arg1);
extern "C" void Gap__Bec__beHitLandModelTraversal__vfunc_22(void *self, int arg1);
extern "C" int FUN_001ceab0(HitTraversal *self, HitNode *node);
extern "C" void FUN_001cf950(int **arg0, int *arg1);
extern "C" int FUN_001cf990(A_1cf990 *arg0, B_1cf990 *arg1);
extern "C" int FUN_001cfaa0(ModelTraversal *self, TraversalNode *node);
extern "C" igMetaObject *FUN_001cfc60(void);
extern "C" int Gap__Sg__igGeometry__vfunc_22(void);
extern "C" void FUN_001d0130(SceneTransformNode *self, SceneRenderer *renderer, SceneMatrix *parent, int context);
extern "C" int Gap__Sg__igLightSet__vfunc_30(void);
extern "C" void Gap__Sg__igLightSet__vfunc_09(void **arg0, int arg1);
extern "C" void Gap__Sg__igLightSet__vfunc_31(O_1d0330 *arg0);
extern "C" void Gap__Sg__igLightSet__vfunc_27(S_1d03b0 *arg0, int arg1);
extern "C" void thunk_Gap__Sg__igNode__vfunc_09(void **self, int flag);
extern "C" void Gap__Sg__igLightStateSet__vfunc_31(igLightStateSetView *self);
extern "C" RangeRefObject *FUN_001d0520(RangeLookup *self, float t);
extern "C" void Gap__Sg__igLod__vfunc_31(igLod *self);
extern "C" void Gap__Sg__igLod__vfunc_17(void **arg0);
extern "C" void Gap__Sg__igLod__vfunc_27(igLod *self, float *matrix);
extern "C" bool FUN_001d08d0(Self *arg0, int arg1);
extern "C" void FUN_001d1550(void *arg0, int arg1);
extern "C" void FUN_001d15a0(KeyReducer *self);
extern "C" void FUN_001d1760(void *arg0, int arg1);
extern "C" void FUN_001d17a0(KeyTrackOwner *self, igFloatListView *out, int last);
extern "C" void FUN_001d18a0(S_1d18a0 *arg0, int *arg1, int *arg2, float *arg3, K_1d18a0 *arg4, int arg5, unsigned arg6);
extern "C" void FUN_001d1a80(int a0, int a1, int);
extern "C" void FUN_001d1da0(MorphLevelState *self, float t);
extern "C" int FUN_001d2230(int a0, S_1d2230 *src, S_1d2230 *dst, O_1d2230 *obj, int flag);
extern "C" int FUN_001d3190(void *arg0);
extern "C" int FUN_001d31b0(void *arg0, int arg1);
extern "C" int FUN_001d31d0(void *arg0, int arg1);
extern "C" int Gap__Core__igObject__vfunc_32(ObjectListOwner *self, igObject *object);
extern "C" void FUN_001d32f0(S_1d32f0 *arg0, int arg1);
extern "C" void Gap__Sg__igNode__vfunc_09(void **arg0, int arg1);
extern "C" int FUN_001d3400(void);
extern "C" void FUN_001d3410(NodeSlots *o, void *with);
extern "C" void FUN_001d3550(void *arg0);
extern "C" void Gap__Sg__igNode__vfunc_17(void *arg0);
extern "C" void **FUN_001d35d0(struct Ref **self, short flag);
extern "C" void **FUN_001d3650(void **arg0, long long arg1);
extern "C" O *FUN_001d36d0(O *arg0, short arg1);
extern "C" void Gap__Sg__igPlanarShadowShader__vfunc_09(void **arg0, int arg1);
extern "C" int Gap__Sg__igPlanarShadowShader__vfunc_22(void);
extern "C" void Gap__Sg__igPlanarShadowShader__vfunc_10(T_1d39b0 *arg0);
extern "C" void Gap__Sg__igPlanarShadowShader__vfunc_39(igPlanarShadowShader *arg0, int dummy1, int arg2, int arg3);
extern "C" void FUN_001d3e20(igPlanarShadowShader *arg0, igCommonTraversal *arg1);
extern "C" void FUN_001d4180(void);
extern "C" void Gap__Sg__igProjectiveShadowShader__vfunc_09(void **arg0, int arg1);
extern "C" igMetaObject *Gap__Sg__igProjectiveShadowShader__vfunc_22(void);
extern "C" void igProjectiveShadowShader_ConfigureSharedAttrs(void);
extern "C" void FUN_001d5430(void);
extern "C" void Gap__Sg__igProjectiveShadowShader__vfunc_10(void **arg0);
extern "C" int FUN_001d5a70(P *arg0, Q_1d5a70 *arg1);
extern "C" void FUN_001d5c40(A0_1d5c40 *arg0, A1_1d5c40 *arg1);
extern "C" void FUN_001d5e00(void *arg0, S1_1d5e00 *arg1);
extern "C" void FUN_001d5e60(struct A_1d5e60 *arg0, int arg1);
extern "C" void FUN_001d5ef0(struct S60 *arg0, int arg1);
extern "C" void FUN_001d5f70(A_1d5f70 *arg0, int arg1, int *arg2, int *arg3, int *arg4);
extern "C" void FUN_001d6060(O_1d6060 *arg0, char *arg1);
extern "C" void FUN_001d6190(struct S_1d6190 *arg0, char *arg1);
extern "C" void Gap__Sg__igProjectiveShadowShader__vfunc_17(struct S_1d6240 *arg0);
extern "C" void Gap__Sg__igProjectiveShadowShader__vfunc_31(void *arg0);
extern "C" void FUN_001d6340(S0_1d6340 *arg0, S1_1d6340 *arg1);
extern "C" int Gap__Bec__ParticleInfo__vfunc_22(ParticleInfo *self, int name);
extern "C" void FUN_001d6410(TraversedNode *collector, TraversedNode *node, void *path);
extern "C" ObjectRefWord *FUN_001d6560(ObjectRefWord *self,int delete_storage);
extern "C" void igSceneInfo_CollectCameras(O_1d65e0 *self);
extern "C" void igSceneInfo_ComputeAnimationRange(ChildOwner *self);
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
extern "C" int FUN_001d81e0(void);
extern "C" int FUN_001d8270(int arg0);
extern "C" int FUN_001d82c0(void *arg0, int arg1, int arg2);
extern "C" int FUN_001d82f0(void *arg0, int arg1);
extern "C" int FUN_001d8310(void *arg0, int arg1);
extern "C" int FUN_001d8330(void *arg0, unsigned int arg1);
extern "C" void Gap__Sg__igShaderData__vfunc_24(void *arg0, int dummy1, int arg2, int arg3);
extern "C" void Gap__Sg__igShaderData__vfunc_25(struct ShaderDataView *arg0);
extern "C" void FUN_001d86f0(struct S_1d86f0 *arg0, int arg1, igObject *arg2);
extern "C" void FUN_001d87b0(igTransformSequence *arg0, int arg1, igObject *arg2);
extern "C" void FUN_001d8870(struct A_1d8870 *arg0, int arg1, igObject *arg2);
extern "C" void Gap__Sg__igShaderData__vfunc_17(S0_1d8930 *arg0);
extern "C" int Gap__Sg__igShaderFactory__vfunc_23(void *dummy, VA_1d8980 *arg1, void *, int);
extern "C" void Gap__Sg__igShaderFactory__vfunc_24(void **arg0);
extern "C" void Gap__Sg__igShaderFactory__vfunc_25(T_1d8a60 *arg0, int arg1);
extern "C" void Gap__Sg__igShaderFactory__vfunc_26(void);
extern "C" void FUN_001d8b90(void);
extern "C" int Gap__Sg__igShaderInfo__vfunc_23(ShaderFieldTable *self, int arg1, ShaderFieldRecord *key);
extern "C" int Gap__Sg__igShaderInfo__vfunc_24(struct S1d *arg0, int *arg1);
extern "C" int Gap__Sg__igShaderProcessor__vfunc_24(void *arg0, void *arg1);
extern "C" void Gap__Sg__igShaderProcessor__vfunc_25(void);
extern "C" void FUN_001d9090(SkeletonBitOwnerView *o, int index, int value);
extern "C" void Gap__Sg__igSkeleton__vfunc_23(SkeletonView *o, SkeletonSlots *clock, int unused, SkeletonMatrix *local, SkeletonMatrix *global, SkeletonMatrix *out, SkeletonOverrideListView *overrides);
extern "C" int Gap__Sg__igSkeleton__vfunc_24(void *arg0);
extern "C" int Gap__Sg__igSkeleton__vfunc_27(S_1d9500 *arg0, int arg1);
extern "C" int Gap__Sg__igSkeleton__vfunc_29(O_1d95a0 *arg0, int arg1, int *arg2);
extern "C" int Gap__Sg__igSkeleton__vfunc_31(void **arg0, int arg1, int arg2);
extern "C" int Gap__Sg__igSkeleton__vfunc_30(VC_1d96d0 *arg0, int arg1);
extern "C" int FUN_001d9740(void *arg0, int arg1);
extern "C" void **FUN_001d9770(void **arg0, short arg1);
extern "C" ObjectRefWord *FUN_001d97f0(ObjectRefWord *self,int delete_storage);
extern "C" void **FUN_001d9870(void **arg0, short arg1);
extern "C" void Gap__Bec__ParticleTimer__vfunc_35(ParticleTimer *arg0, RefCountedHeader *arg1);
extern "C" int FUN_001d9970(int *a, int *b);
extern "C" int FUN_001d99d0(int *arg0, int *arg1);
extern "C" int FUN_001d9a30(int *a, int *b);
extern "C" void FUN_001d9ac0(struct A_1d9ac0 *arg0, int arg1, int arg2);
extern "C" void FUN_001d9bb0(void *arg0, int arg1);
extern "C" void FUN_001da6e0(igSorter *arg0);
extern "C" void FUN_001da790(SorterOpaqueView *o);
extern "C" void Gap__Sg__igSorter__vfunc_09(SorterState *o, int arg1);
extern "C" void FUN_001db500(A_1db500 *arg0);
extern "C" void Gap__Sg__igSorter__vfunc_24(Sorter *arg0);
extern "C" void FUN_001dc400(igSorter *arg0, igGroup *arg1, igAttrStackManager *arg2);
extern "C" void FUN_001dc500(A_1dc500 *arg0, unsigned char arg1, int arg2);
extern "C" void igSwitch_EnableChild(void *arg0, unsigned int arg1);
extern "C" void igSwitch_EnableAllChildren(int *p);
extern "C" void igSwitch_DisableChild(void *arg0, unsigned int arg1);
extern "C" void igSwitch_DisableAllChildren(int *p);
extern "C" int igSwitch_AppendChild(void *arg0, int arg1);
extern "C" int Gap__Sg__igSwitch__vfunc_35(S_1dc940 *arg0, int arg1, void *arg2);
extern "C" Obj_1c5eb0 *igSwitch_RemoveChildAt(S_1dc940 *arg0, int arg1);
extern "C" void igObjectPool_Grow(List_1dca40 *arg0, Obj_1dca40 *(*arg1)(int));
extern "C" void FUN_001dcb80(ObjectPool *pool, igObject *object);
extern "C" int FUN_001dcc80(KeyTrackView *o, double t);
extern "C" int FUN_001dce70(struct S_1dce70 *arg0, double arg1);
extern "C" void Gap__Sg__igTransform__vfunc_7(igTransform *self, int flag);
extern "C" int Gap__Sg__igTransform__vfunc_24(igTransform *arg0);
extern "C" int Gap__Sg__igTransformSource__vfunc_29(void);
extern "C" void Gap__Sg__igTransform__vfunc_25(void *arg0, int arg1);
extern "C" void Gap__Sg__igTransformSource__vfunc_30(void);
extern "C" int Gap__Sg__igTransform__vfunc_28(void);
extern "C" void Gap__Sg__igTransform__vfunc_29(igTransform *self);
extern "C" void Gap__Sg__igTransformSource__vfunc_33(void);
extern "C" void FUN_001dd0e0(TransformSampleView *o, int index, float (*m)[4]);
extern "C" void FUN_001dd250(A_1dd250 *arg0, int arg1, char *arg2);
extern "C" int FUN_001dd370(void *arg0);
extern "C" void FUN_001dd3e0(void *arg0, int arg1);
extern "C" int UnsignedDivMod64_Cached(long long arg0, long long arg1, long long *arg2);
extern "C" void Gap__Sg__igTransformSequence1_5__vfunc_66(VC_1dd570 *arg0);
extern "C" int Gap__Sg__igTransformSequence1_5__vfunc_45(igTransformSequence1_5 *self, int index);
extern "C" void Gap__Sg__igTransformSequence1_5__vfunc_62(void *arg0, long long arg1);
extern "C" void Gap__Sg__igTransformSequence1_5__vfunc_34(KeySequenceView *o, int index, KeyMatrixView *m);
extern "C" void Gap__Sg__igTransformSequence1_5__vfunc_37(igTransformSequence1_5 *t, int idx);
extern "C" void FUN_001ddfd0(void);
extern "C" void Gap__Sg__igTransformSequence1_5__vfunc_57(TransformSequenceView *s, int channel, unsigned int mode);
extern "C" int Gap__Sg__igTransformSequence1_5__vfunc_59(igTransformSequence1_5 *arg0, int arg1);
extern "C" void Gap__Sg__igTransformSequence1_5__vfunc_58(TransformSequenceView *s, unsigned char channels);
extern "C" void Gap__Sg__igTransformSequence1_5__vfunc_61(T_1de9c0 *t, int idx, int ch, V_1de9c0 *p, V_1de9c0 *q);
extern "C" int Gap__Sg__igTransformSequence1_5__vfunc_48(igTransformSequence1_5 *self, int index);
extern "C" void igTransformSequence1_5_InterpolateTranslation(igTransformSequence1_5 *self, float *out, int from, int to, float t);
extern "C" void igTransformSequence1_5_InterpolateRotation(igTransformSequence1_5 *self, float *out, int from, int to, float t);
extern "C" void FUN_001930f0(float *out, float *p1, float *p2, float *p3, float *p4, float t);
extern "C" void igTransformSequence1_5_FindUniformKeys(SequenceKeyTimes *arg0, long long arg1, int *arg2, int *arg3, float *arg4);
extern "C" long long Gap__Sg__igTransformSequence1_5__vfunc_31(O_1df6e0 *o);
extern "C" long long Gap__Sg__igTransformSequence1_5__vfunc_32(V_1df740 *arg0);
extern "C" void Gap__Sg__igTransformSequence1_5__vfunc_27(IgForwardTarget *o, int a, int b, int c);
extern "C" void Gap__Sg__igTransformSequence1_5__vfunc_25(IgForwardTarget_1dfd60 *o, int a, int b);
extern "C" bool Gap__Sg__igTransformSequence1_5__vfunc_29(igTransformSequence1_5 *o);
extern "C" void FUN_001e02e0(int arg0);
extern "C" void FUN_001e02f0(int arg0, int arg1);
extern "C" void Gap__Sg__igTraversal__vfunc_09(A_1e0380 *arg0, int arg1);
extern "C" void FUN_001e0410(void);
extern "C" void FUN_001e0470(void);
extern "C" int FUN_001e04c0(S_1e04c0 *arg0, V_1e04c0 *arg1);
extern "C" void Gap__Sg__igTraversal__vfunc_23(void *, int);
extern "C" void Gap__Sg__igTraversal__vfunc_24(void *, int);
extern "C" void igTraversal_RegisterFunction(struct L_1e06c0 *arg0, struct X_1e06c0 *arg1, void *arg2);
extern "C" int igTraversal_TraverseChildren(int arg0, S_1e07a0 *arg1);
extern "C" void thunk_FUN_001c1c50(void **self, int flag);
extern "C" void Gap__Sg__igPsx2EnvironmentMapShader__vfunc_10(void **arg0);
extern "C" int Gap__Sg__igPsx2EnvironmentMapShader__vfunc_22(void);
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
extern "C" void FUN_001e2820(void *arg0);
extern "C" int FUN_001e2830(void);
extern "C" int FUN_001e2840(void *arg0);
extern "C" int FUN_001e2860(void);
extern "C" void FUN_001e2870(int a0, int a1);
extern "C" int Gap__Sg__igTraversal__vfunc_22(void);
extern "C" void Gap__Bec__beHitLandModelTraversal__vfunc_25(beHitLandModelTraversal *arg0, long long arg1);
extern "C" igMetaObject *Gap__Sg__igTransformSequence1_5__vfunc_22(void);
extern "C" void Gap__Sg__igTransformSequence1_5__vfunc_53(IgForwardTarget_1e28b0 *o);
extern "C" void Gap__Sg__igTransformSequence1_5__vfunc_54(IgForwardTarget_1e28c0 *o);
extern "C" void Gap__Sg__igTransformSequence1_5__vfunc_36(TransformSequenceChannelView *o, int index);
extern "C" void Gap__Sg__igTransformSequence1_5__vfunc_38(struct T_1e2970 *t, int n);
extern "C" void Gap__Sg__igTransformSequence1_5__vfunc_55(igTransformSequence1_5 *arg0, int arg1, long long arg2);
extern "C" void Gap__Sg__igTransformSequence1_5__vfunc_40(igTransformSequence1_5 *self, int index, float *translation);
extern "C" void Gap__Sg__igTransformSequence1_5__vfunc_44(igTransformSequence1_5 *self, int index, void *quaternion);
extern "C" void Gap__Sg__igTransformSequence1_5__vfunc_47(igTransformSequence1_5 *arg0, int arg1, void *arg2);
extern "C" void Gap__Sg__igTransformSequence1_5__vfunc_49(igTransformSequence1_5 *self, int index, void *scale);
extern "C" long long Gap__Sg__igTransformSequence1_5__vfunc_63(void *arg0);
extern "C" void Gap__Sg__igTransformSequence1_5__vfunc_64(void *arg0, long long arg1);
extern "C" void FUN_001e2cd0(IgForwardTarget_1e2cd0 *o);
extern "C" void FUN_001e2ce0(igTransformSequence1_5 *self, char enabled);
extern "C" void FUN_001e2cf0(void *arg0);
extern "C" igMetaObject *FUN_001e2d00(void);
extern "C" int FUN_001e2d10(void **arg0, int arg1);
extern "C" void FUN_001e2d60(IgForwardTarget_1e2d60 *o);
extern "C" void FUN_001e2d70(IgForwardTarget_1e2d70 *o);
extern "C" void Gap__Core__igObject__vfunc_35(int a0);
extern "C" void Gap__Sg__igNode__vfunc_31(void);
extern "C" int Gap__Sg__igShaderProcessor__vfunc_23(void);
extern "C" int Gap__Sg__igSwitch__vfunc_22(void);
extern "C" int Gap__Sg__igSwitch__vfunc_36(void);
extern "C" int Gap__Sg__igSorter__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igSkeleton__vfunc_22(void);
extern "C" int Gap__Sg__igSkeleton__vfunc_25(void *arg0);
extern "C" int *Gap__Sg__igSkeleton__vfunc_26(void *arg0, int arg1);
extern "C" int Gap__Sg__igSkeleton__vfunc_28(void *arg0, int arg1);
extern "C" igMetaObject *Gap__Sg__igShaderInfo__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igShaderFactory__vfunc_22(void);
extern "C" void Gap__Sg__igShaderFactory__vfunc_27(void);
extern "C" igMetaObject *Gap__Sg__igShaderData__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igSceneInfo__vfunc_22(void);
extern "C" void Gap__Sg__igPlanarShadowShader__vfunc_31(Shader *arg0);
extern "C" void Gap__Bec__ParticleTimer__vfunc_36(ParticleTimer *a0, int a1);
extern "C" int Gap__Bec__ParticleTimer__vfunc_34(void);
extern "C" int Gap__Sg__igNode__vfunc_25(void);
extern "C" igMetaObject *Gap__Sg__igLod__vfunc_22(void);
extern "C" int Gap__Sg__igLod__vfunc_36(void);
extern "C" int Gap__Sg__igLod__vfunc_37(igLod *arg0);
extern "C" int Gap__Sg__igLightStateSet__vfunc_22(void);
extern "C" int Gap__Sg__igLightSet__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igIntersectTraversal__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igIniShaderFactory__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igGroup__vfunc_22(void);
extern "C" int Gap__Sg__igFrustCullTraversal__vfunc_22(void);
extern "C" void Gap__Sg__igCommonTraversal__vfunc_29(S0_1e31f0 *arg0, S1_1e31f0 *arg1);
extern "C" void Gap__Sg__igCommonTraversal__vfunc_27(void *arg0, long long arg1);
extern "C" int Gap__Sg__igEnbayaTransformSource__vfunc_22(void);
extern "C" int Gap__Sg__igEnbayaContextPool__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igEnbayaAnimationState__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igEnbayaAnimationSource__vfunc_22(void);
extern "C" unsigned char Gap__Sg__igCompressedAnimationSequenceQS__vfunc_34(igCompressedAnimationSequenceQS *self);
extern "C" void Gap__Sg__igCompressedAnimationSequenceQS__vfunc_37(struct S_1e3300 *arg0);
extern "C" int Gap__Sg__igCompressedAnimationSequenceQS__vfunc_38(void);
extern "C" int Gap__Sg__igCompressedAnimationSequenceQS__vfunc_39(void);
extern "C" void Gap__Sg__igCompressedAnimationSequenceQS__vfunc_40(void);
extern "C" int Gap__Sg__igCompressedAnimationSequenceQS__vfunc_41(void);
extern "C" long long Gap__Sg__igCompressedAnimationSequenceQS__vfunc_43(igCompressedAnimationSequenceQS *self);
extern "C" void Gap__Sg__igCompressedAnimationSequenceQS__vfunc_45(igCompressedAnimationSequenceQS *self, long long animationDuration);
extern "C" int Gap__Sg__igCompressedAnimationSequenceQS__vfunc_26(void **arg0, int arg1);
extern "C" igMetaObject *Gap__Sg__igCompressedAnimationSequenceQS__vfunc_22(void);
extern "C" int Gap__Sg__igCompileTraversal__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igCommonTraversal__vfunc_22(void);
extern "C" int Gap__Sg__igCamera__vfunc_26(void);
extern "C" igMetaObject *Gap__Sg__igAttrStackManager__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igAttrSet__vfunc_22(void);
extern "C" int Gap__Sg__igAnimationState__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igAnimationDatabase__vfunc_22(void);
extern "C" int Gap__Sg__igAnimationCombiner__vfunc_22(void);
extern "C" unsigned char Gap__Sg__igAnimationCombiner__vfunc_25(void *arg0);
extern "C" int Gap__Sg__igAnimationCombiner__vfunc_27(void *arg0);
extern "C" int Gap__Sg__igAnimationCombiner__vfunc_28(void *arg0, int arg1);
extern "C" int Gap__Sg__igAnimationCombiner__vfunc_29(void *arg0);
extern "C" int Gap__Sg__igAnimationCombiner__vfunc_30(void *arg0, int arg1);
extern "C" int Gap__Sg__igActor__vfunc_22(void);
extern "C" int Gap__Sg__igActor__vfunc_26(void);
extern "C" int Gap__Sg__igActorList__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igActorInfo__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igAnimationTrack__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igAnimationTrackList__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igAnimationTransitionParams__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igAnimationTransitionPoint__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igAnimationTransitionPointList__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igAnimationTransitionDefinition__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igAnimationTransitionDefinitionList__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igAnimationList__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igAnimationBinding__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igAnimationBindingList__vfunc_22(void);
extern "C" int FUN_001e35e0(void);
extern "C" int FUN_001e35f0(igAnimationBindingList *self);
extern "C" int Gap__Sg__igAnimationCombinerList__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igAnimationCombinerBoneInfo__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igAnimationCombinerBoneInfoList__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igAnimationCombinerBoneInfoListList__vfunc_22(void);
extern "C" int Gap__Sg__igAnimationCombinerBoneInfoPool__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igObjectPool__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igAnimationModifier__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igAnimationModifierList__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igAnimationStateList__vfunc_22(void);
extern "C" int Gap__Sg__igAnimationStatePool__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igAppearance__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igAppearanceList__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igAttrStack__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igAttrStackList__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igNonRefCountedAttrStackManagerList__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igBillboard__vfunc_22(void);
extern "C" int Gap__Sg__igBillboard__vfunc_26(void);
extern "C" int Gap__Sg__igBitMask__vfunc_22(void);
extern "C" int Gap__Core__igUnsignedIntList__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igBlendMatrixSelect__vfunc_22(void);
extern "C" int Gap__Sg__igBoundingBoxesMaker__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igCamera__vfunc_22(void);
extern "C" void Gap__Sg__igCamera__vfunc_35(void);
extern "C" void Gap__Sg__igCamera__vfunc_36(void);
extern "C" int Gap__Sg__igCompiledTransform__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igCompiledTransformList__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igBlendListRecord__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igCompressedTransformSequence1_5Data__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igEnvironmentMapShader2List__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igGeometryList__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igGraphPath__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igGraphPathList__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igInterpretedShaderData__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igProbe__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igAnimation__vfunc_22(void);
extern "C" int Gap__Sg__igModelViewMatrixBoneSelect__vfunc_22(void);
extern "C" igMetaObject *FUN_001e3840(void);
extern "C" igMetaObject *Gap__Sg__igNodeList__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igNodeListList__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igNonRefCountedNodeList__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igOverrideAttrSet__vfunc_22(void);
extern "C" int Gap__Sg__igSegment__vfunc_22(void);
extern "C" int Gap__Sg__igSegment__vfunc_26(void);
extern "C" int Gap__Sg__igTraversalFunctionList__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igLightStateAttrPool__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igModelViewMatrixAttrPool__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igTimeAttrPool__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igProjectionMatrixAttrPool__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igVertexBlendMatrixAttrPool__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igVertexBlendMatrixListAttrPool__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igMatrixObjectPool__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igTextureMatrixAttrPool__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igBlendMatricesAttrPool__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igShaderFactoryList__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igSkeletonBoneInfo__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igSkeletonBoneInfoList__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igSkeletonList__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igSkin__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igSkinList__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igRenderPackage__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igRenderPackagePool__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igRenderPackageList__vfunc_22(void);
extern "C" int Gap__Core__igDoubleList__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igTransformStack__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igTransformList__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igNonRefCountedTransformList__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igTransformRecorder__vfunc_22(void);
extern "C" int Gap__Sg__igTransientShaderData__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igRenderPackageList__vfunc_24(void);
extern "C" igMetaObject *Gap__Sg__igNonRefCountedAttrStackManagerList__vfunc_24(void);
extern "C" igMetaObject *Gap__Sg__igNonRefCountedTransformList__vfunc_24(void);
extern "C" igMetaObject *Gap__Sg__igNonRefCountedNodeList__vfunc_24(void);
extern "C" int Gap__Sg__igTraversalFunctionList__vfunc_23(igTraversalFunctionList *self);
extern "C" int Gap__Core__igDoubleList__vfunc_23(void);
extern "C" int Gap__Core__igUnsignedIntList__vfunc_23(void);
extern "C" int FUN_001e3ab0(struct L_1e3500 *arg0, int *arg1);
extern "C" int Gap__Sg__igActorList__vfunc_24(void);
extern "C" int Gap__Sg__igAnimationCombinerList__vfunc_24(void);
extern "C" igMetaObject *Gap__Sg__igAppearanceList__vfunc_24(void);
extern "C" igMetaObject *Gap__Sg__igAnimationStateList__vfunc_24(void);
extern "C" igMetaObject *Gap__Sg__igAnimationCombinerBoneInfoListList__vfunc_24(void);
extern "C" igMetaObject *Gap__Sg__igAnimationCombinerBoneInfoList__vfunc_24(void);
extern "C" igMetaObject *Gap__Sg__igEnvironmentMapShader2List__vfunc_24(void);
extern "C" igMetaObject *Gap__Sg__igGraphPathList__vfunc_24(void);
extern "C" igMetaObject *Gap__Sg__igAnimationList__vfunc_24(void);
extern "C" igMetaObject *Gap__Sg__igAnimationTransitionDefinitionList__vfunc_24(void);
extern "C" igMetaObject *Gap__Sg__igAnimationTransitionPointList__vfunc_24(void);
extern "C" igMetaObject *Gap__Sg__igAnimationTrackList__vfunc_24(void);
extern "C" igMetaObject *Gap__Sg__igAnimationBindingList__vfunc_24(void);
extern "C" int Gap__Bec__igModelViewMatrixBoneSelectList__vfunc_22(void);
extern "C" igMetaObject *Gap__Sg__igShaderFactoryList__vfunc_24(void);
extern "C" igMetaObject *Gap__Sg__igSkeletonList__vfunc_24(void);
extern "C" igMetaObject *Gap__Sg__igSkeletonBoneInfoList__vfunc_24(void);
extern "C" igMetaObject *Gap__Sg__igAnimationModifierList__vfunc_24(void);
extern "C" igMetaObject *Gap__Sg__igSkinList__vfunc_24(void);
extern "C" int Gap__Sg__igCompiledTransformList__vfunc_24(void);
extern "C" igMetaObject *Gap__Sg__igGeometryList__vfunc_24(void);
extern "C" igMetaObject *Gap__Sg__igAttrStackList__vfunc_24(void);
extern "C" igMetaObject *Gap__Sg__igTransformList__vfunc_24(void);
extern "C" igMetaObject *Gap__Sg__igNodeListList__vfunc_24(void);
extern "C" igMetaObject *Gap__Sg__igNodeList__vfunc_24(void);
extern "C" void Gap__Core__igUnsignedIntList__vfunc_18(void *arg0);
extern "C" void Gap__Core__igDoubleList__vfunc_18(igDataList *arg0);
extern "C" void Gap__Sg__igTraversalFunctionList__vfunc_18(void *arg0);
extern "C" int FUN_001b8720(void *arg0, ForwardTarget *arg1);
extern "C" int FUN_001ba6b0(char *arg0, struct S_1d6190 *arg1);
extern "C" int FUN_001ba850(A1_1c03a0 *arg0, DepthOfFieldNode *arg1);
extern "C" int FUN_001c5130(void *arg0, TraversalNodeView *arg1);
extern "C" int FUN_001cf980(void);
extern "C" int FUN_001e0790(void);
static int FUN_001c0ae0(float *arg0, float fparg0, float fparg1);
static inline void insertRetained(Ls *list, int index, It *object) {
    Retained retained(object);
    List_InsertWords(list, index, 1, &retained.p);
}
static inline void releaseWord(igPoolObject *o) {
    if (o != 0) {
        o->_refCount = o->_refCount - 1;
        if (((unsigned long long)((long long)(int)o->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(o);
        }
    }
}
static inline void clearBoneInfo(CombinerBoneInfo *b) {
    FUN_001ae250((void * *)&b->_animationState, 0);
    FUN_001ae1d0((void * *)&b->_transformSource, 0);
    FUN_001ae1b0(b->_q, 0.0f, 0.0f, 0.0f, 0.0f);
    Vec3f_Set(b->_t, 0.0f, 0.0f, 0.0f);
    b->_priority = 0;
    b->_useTranslation = 0;
    b->_lastKeyframe = 1;
    b->_reflect = -1;
}
static inline igPoolObject *poolTake(CombinerPool *pool, void *ctor) {
    int i;
    if (pool->_used >= pool->_capacity) {
        igObjectPool_Grow((List_1dca40 *)pool, (Obj_1dca40 * (*)(int))ctor);
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
    if (object != 0 && igObject_IsKindOf(object, g_igNamedObject_metaObject) != 0) {
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
#define CAST_INLINE(NAME, META) static inline AnimDbObject *NAME(AnimDbObject *o) { if (o != 0 && igObject_IsKindOf(o, META) != 0) { return o; } return 0; }
CAST_INLINE(castSkeleton, ((igMetaObject *)g_igTransformSource_metaObject[0]))
CAST_INLINE(castField, ((igMetaObject *)g_igObjectRefMetaField_metaObject[0]))
CAST_INLINE(castBoolList, ((igMetaObject *)g_igAnimationTrackList_metaObject[0]))
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
    s = s == 0 ? ((int)g_stringObjEmptyText[0]) : s;
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
            List_Resize((void *)this, n, 4);
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
                igObject_Destroy((void *)o);
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
            igObject_Destroy((void *)o);
        }
    }
    List_RemoveWordAt(list, i);
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
    return st->_stacks->_data[st->_slotOfIndex[((AttrClassView *)g_igModelViewMatrixAttr_metaObject[0])->_stackIndex]];
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
            if (((unsigned long long)((long long)o->ref << 0x29) >> 0x29) == 0) igObject_Destroy((void *)o);
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
        igObject_Destroy(p);
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
            FUN_00300f50(t, t->_storage);
        }
        if (t->_data != 0) {
            FUN_00300f50(t, t->_data);
        }
        t->_data = ((int *)igObject_AllocateStorage(t, n * 4));
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
    if (g_stringPool[0] == 0) {
        pool = StringPool_Allocate(16);
        if (pool != 0) {
            pool = StringPool_Construct(pool);
        }
        g_stringPool[0] = pool;
    }
    return ((char *)StringPool_Intern(g_stringPool[0], text));
}
static inline int f8_of(const L_1c58c0 *list) { return list->f8; }
static inline char *releaseText(char *s) {
    if (s != 0) {
        int *header = (int *)s - 2;
        int count = ((int *)s)[-1] - 1;
        ((int *)s)[-1] = count;
        if (count == 0) {
            StringChunk_ReleaseHeader(*header, header);
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
            StringChunk_ReleaseHeader(*h, h);
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
            igObject_Destroy(o);
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
        FUN_002d6790(l, n + 1, 4);
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
        if ((((NodeSlots *)*slot)->_refCount & 0x7fffff) == 0) { igObject_Destroy((NodeSlots *)*slot); }
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
            igObject_Destroy((void *)old);
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
        if (n <= list->capacity) { list->count = n; } else { List_Resize((void *)list, n, size); }
    }
}
static inline void releaseRef_1de4e0(SeqData *old) {
    if (old) {
        --old->refCount;
        if (((unsigned long long)(long long)old->refCount & 0x7fffffULL) == 0)
            igObject_Destroy((void *)old);
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
        if (n <= list->capacity) { list->count = n; } else { List_Resize((void *)list, n, size); }
    }
}
static inline void assignRef_1e22c0(EnvMapAttrOps *&field, const EnvMapTempRef &r) {
    EnvMapAttr *o = r.p;
    if (o) { o->f4++; }
    EnvMapAttr *old = (EnvMapAttr *)field;
    if (old) {
        --old->f4;
        if (((unsigned long long)(long long)old->f4 & 0x7fffffULL) == 0)
            igObject_Destroy((void *)old);
    }
    field = (EnvMapAttrOps *)o;
}
static inline int n_of_1e3270(const T_1e3270 *list) { return list->n; }

extern "C" igMetaObject *g_igTextureMatrixAttr_metaObject[4];
extern "C" igMetaObject *g_igVertexBlendMatrixAttr_metaObject[4];
extern "C" igMetaField *g_igTextureMatrixAttr_mField[4];
extern "C" igMetaField *g_igVertexBlendMatrixAttr_mField[4];
extern "C" igMetaObject *igLightStateAttr_GetMetaObject(void);
extern "C" void FUN_00130c10(int allocator);
extern "C" void FUN_001317c0(int allocator);
extern "C" void FUN_001361b0(int allocator);
typedef igTDataList<AttrObjectStack *> AttrObjectStackList;
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
        igObjectPool_Grow((List_1dca40 *)pool, (Obj_1dca40 * (*)(int))create);
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
extern "C" void igAttrStackManager_PopLightStateAttr(igAttrStackManager *self, LightStateAttrView *attr, int isOverride);
extern "C" int igAttrStackManager_IsLightEnabled(igAttrStackManager *self, igLightAttr *light);
extern "C" float *igTransform_PushMatrix(TransformView *self, CommonTraversalView *traversal);
extern "C" int igTransform_TraverseChildrenAndPopMatrix(float *matrix, igTransform *self, igCommonTraversal *traversal);
extern "C" int igCommonTraversal_TraverseOverrideAttrSet(igCommonTraversal *self, igOverrideAttrSet *set);
extern "C" int igCommonTraversal_TraverseAttrSet(igCommonTraversal *self, igAttrSet *set);
extern "C" int igCommonTraversal_TraverseProjectiveShadowShader(igCommonTraversal *self, igProjectiveShadowShader *shader);
extern "C" int igTransform_CompileChildrenAndPopMatrix(float *matrix, igTransform *self, igCompileTraversal *traversal);
extern "C" int igCompileTraversal_TraverseJointTransform(igTraversal *traversal, igTransform *node);

#endif
