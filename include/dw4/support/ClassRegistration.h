#ifndef DW4_CLASSREGISTRATION_H
#define DW4_CLASSREGISTRATION_H

/* The class-registration entry points: each X_EnsureRegistered registers class X's meta object once,
 * X_RunStaticInit builds a pool class's meta object, and <Library>_RegisterClasses registers a
 * library's classes. Grouped by the library that defines them. */
#ifdef __cplusplus
extern "C" {
#endif

/* Core */
void igDependencyMetaField_EnsureRegistered(void);
void igFloatListList_EnsureRegistered(void);
void igMemoryDescriptorMetaField_EnsureRegistered(void);
void igNamedObjectInfo_EnsureRegistered(void);
void igNamedObjectList_EnsureRegistered(void);
void igObjectStringMap_EnsureRegistered(void);
void igPointerListList_EnsureRegistered(void);

/* Maths */
void igAABox_EnsureRegistered(void);
void igContainsFunctionList_EnsureRegistered(void);
void igContainsRayFunctionList_EnsureRegistered(void);
void igContainsVecFunctionList_EnsureRegistered(void);
void igEmptyFunctionList_EnsureRegistered(void);
void igExtendByFunctionList_EnsureRegistered(void);
void igExtendByRayFunctionList_EnsureRegistered(void);
void igExtendByVecFunctionList_EnsureRegistered(void);
void igGetCenterFunctionList_EnsureRegistered(void);
void igIntersectionFunctionList_EnsureRegistered(void);
void igIsEmptyFunctionList_EnsureRegistered(void);
void igQuaternionfList_EnsureRegistered(void);
void igRayIntersectionFunctionList_EnsureRegistered(void);
void igTransformFunctionList_EnsureRegistered(void);
void igVec3fList_EnsureRegistered(void);

/* Gfx */
void igParticleFormat_EnsureRegistered(void);
void igTrackedElementMetaField_EnsureRegistered(void);

/* Attrs */
void igParticleAttr_EnsureRegistered(void);

/* SceneGraph */
void igActorList_EnsureRegistered(void);
void igActor_EnsureRegistered(void);
void igBitMask_EnsureRegistered(void);
void igBlendMatrixSelect_EnsureRegistered(void);
void igCompressedAnimationSequenceQS_EnsureRegistered(void);
void igEnbayaAnimationSource_EnsureRegistered(void);
void igEnbayaAnimationState_EnsureRegistered(void);
void igEnbayaContextPool_RunStaticInit(void);
void igEnbayaTransformSource_EnsureRegistered(void);
void igModelViewMatrixBoneSelectListSg_EnsureRegistered(void);
void igModelViewMatrixBoneSelect_EnsureRegistered(void);

/* Libraries */
void AdxMovieLibrary_RegisterClasses(void);
void BecLibrary_RegisterClasses(void);
void CollisionLibrary_RegisterClasses(void);
void LuaAPI_RegisterClasses(void);
void NdmwLibrary_RegisterClasses(void);
void SceneSearchLibrary_RegisterClasses(void);

#ifdef __cplusplus
}
#endif

#endif
