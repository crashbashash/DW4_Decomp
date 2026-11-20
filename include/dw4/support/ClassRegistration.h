#ifndef DW4_CLASSREGISTRATION_H
#define DW4_CLASSREGISTRATION_H

/* The class-registration entry points: each X_EnsureRegistered registers class X's meta object once,
 * X_RunStaticInit builds a pool class's meta object, and <Library>_RegisterClasses registers a
 * library's classes. Grouped by the library that defines them. */
#ifdef __cplusplus
extern "C" {
#endif

/* Core */
void igBoolArrayMetaField_EnsureRegistered(void);
void igBoolList_EnsureRegistered(void);
void igDependencyMetaField_EnsureRegistered(void);
void igDoubleArrayMetaField_EnsureRegistered(void);
void igEnumArrayMetaField_EnsureRegistered(void);
void igFloatArrayMetaField_EnsureRegistered(void);
void igFloatListList_EnsureRegistered(void);
void igFloatList_EnsureRegistered(void);
void igLongArrayMetaField_EnsureRegistered(void);
void igLongList_EnsureRegistered(void);
void igMemoryDescriptorMetaField_EnsureRegistered(void);
void igMemoryFileEntryList_EnsureRegistered(void);
void igMemoryRefArrayMetaField_EnsureRegistered(void);
void igNamedObjectInfo_EnsureRegistered(void);
void igNamedObjectList_EnsureRegistered(void);
void igObjectRefArrayMetaField_EnsureRegistered(void);
void igObjectStringMap_EnsureRegistered(void);
void igPointerListList_EnsureRegistered(void);
void igRawRefArrayMetaField_EnsureRegistered(void);
void igShortArrayMetaField_EnsureRegistered(void);
void igStringArrayMetaField_EnsureRegistered(void);
void igUnsignedCharArrayMetaField_EnsureRegistered(void);
void igUnsignedIntArrayMetaField_EnsureRegistered(void);
void igUnsignedLongArrayMetaField_EnsureRegistered(void);
void igUnsignedShortArrayMetaField_EnsureRegistered(void);
void igUnsignedShortList_EnsureRegistered(void);
void igVirtualCFuncMetaField_EnsureRegistered(void);

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
void igMatrix44fMetaField_EnsureRegistered(void);
void igQuaternionfList_EnsureRegistered(void);
void igRayIntersectionFunctionList_EnsureRegistered(void);
void igTransformFunctionList_EnsureRegistered(void);
void igVec2fMetaField_EnsureRegistered(void);
void igVec3fList_EnsureRegistered(void);
void igVec3fMetaField_EnsureRegistered(void);
void igVec4fArrayMetaField_EnsureRegistered(void);
void igVec4fMetaField_EnsureRegistered(void);
void igVec4ucMetaField_EnsureRegistered(void);

/* Gfx */
void igClut_EnsureRegistered(void);
void igExternalImageEntry_EnsureRegistered(void);
void igImage_EnsureRegistered(void);
void igIndexArray_EnsureRegistered(void);
void igParticleFormat_EnsureRegistered(void);
void igPrimLengthArray1_1_EnsureRegistered(void);
void igTrackedElementMetaField_EnsureRegistered(void);
void igVertexArray1_1_EnsureRegistered(void);

/* Attrs */
void igAlphaFunctionAttr_EnsureRegistered(void);
void igAlphaStateAttr_EnsureRegistered(void);
void igAttrListList_EnsureRegistered(void);
void igAttrList_EnsureRegistered(void);
void igAttrPool_EnsureRegistered(void);
void igBlendFunctionAttr_EnsureRegistered(void);
void igBlendStateAttr_EnsureRegistered(void);
void igClearAttr_EnsureRegistered(void);
void igColorAttr_EnsureRegistered(void);
void igColorMaskAttr_EnsureRegistered(void);
void igCopyRenderDestinationAttr_EnsureRegistered(void);
void igCullFaceAttr_EnsureRegistered(void);
void igDepthStateAttr_EnsureRegistered(void);
void igDepthWriteStateAttr_EnsureRegistered(void);
void igFogAttr_EnsureRegistered(void);
void igFogStateAttr_EnsureRegistered(void);
void igGeometryAttr1_5_EnsureRegistered(void);
void igGeometrySetAttr_EnsureRegistered(void);
void igImageMipMapList_EnsureRegistered(void);
void igLightAttr_EnsureRegistered(void);
void igLightList_EnsureRegistered(void);
void igLightStateAttrList_EnsureRegistered(void);
void igLightStateAttr_EnsureRegistered(void);
void igLightingStateAttr_EnsureRegistered(void);
void igMaterialAttr_EnsureRegistered(void);
void igModelViewMatrixAttr_EnsureRegistered(void);
void igNonRefCountedAttrList_EnsureRegistered(void);
void igNormalizeNormalsStateAttr_EnsureRegistered(void);
void igParticleAttr_EnsureRegistered(void);
void igProjectionMatrixAttr_EnsureRegistered(void);
void igRenderDestinationAttr_EnsureRegistered(void);
void igSetRenderDestinationAttr_EnsureRegistered(void);
void igShadeModelAttr_EnsureRegistered(void);
void igTextureAttr_EnsureRegistered(void);
void igTextureBindAttr_EnsureRegistered(void);
void igTextureCoordSourceAttr_EnsureRegistered(void);
void igTextureFunctionAttr_EnsureRegistered(void);
void igTextureList_EnsureRegistered(void);
void igTextureMatrixAttr_EnsureRegistered(void);
void igTextureMatrixStateAttr_EnsureRegistered(void);
void igTextureStateAttr_EnsureRegistered(void);
void igTextureUnloadAttr_EnsureRegistered(void);
void igVertexBlendStateAttr_EnsureRegistered(void);
void igViewportAttr_EnsureRegistered(void);

/* SceneGraph */
void igActorList_EnsureRegistered(void);
void igActor_EnsureRegistered(void);
void igAnimationBindingList_EnsureRegistered(void);
void igAnimationBinding_EnsureRegistered(void);
void igAnimationCombinerBoneInfoListList_EnsureRegistered(void);
void igAnimationCombinerBoneInfoList_EnsureRegistered(void);
void igAnimationCombinerBoneInfoPool_RunStaticInit(void);
void igAnimationCombinerList_EnsureRegistered(void);
void igAnimationCombiner_EnsureRegistered(void);
void igAnimationDatabase_EnsureRegistered(void);
void igAnimationList_EnsureRegistered(void);
void igAnimationModifierList_EnsureRegistered(void);
void igAnimationStateList_EnsureRegistered(void);
void igAnimationStatePool_RunStaticInit(void);
void igAnimationTrackList_EnsureRegistered(void);
void igAnimationTrack_EnsureRegistered(void);
void igAnimationTransitionDefinitionList_EnsureRegistered(void);
void igAnimation_EnsureRegistered(void);
void igAppearanceList_EnsureRegistered(void);
void igAppearance_EnsureRegistered(void);
void igAttrSet_EnsureRegistered(void);
void igBillboard_EnsureRegistered(void);
void igBitMask_EnsureRegistered(void);
void igBlendMatrixSelect_EnsureRegistered(void);
void igCamera_EnsureRegistered(void);
void igCommonTraversal_EnsureRegistered(void);
void igCompressedAnimationSequenceQS_EnsureRegistered(void);
void igEnbayaAnimationSource_EnsureRegistered(void);
void igEnbayaAnimationState_EnsureRegistered(void);
void igEnbayaContextPool_RunStaticInit(void);
void igEnbayaTransformSource_EnsureRegistered(void);
void igGeometryList_EnsureRegistered(void);
void igGeometry_EnsureRegistered(void);
void igGraphPathList_EnsureRegistered(void);
void igGraphPath_EnsureRegistered(void);
void igGroup_EnsureRegistered(void);
void igIniShaderFactory_EnsureRegistered(void);
void igLightSet_EnsureRegistered(void);
void igLightStateSet_EnsureRegistered(void);
void igLod_EnsureRegistered(void);
void igModelViewMatrixBoneSelectListSg_EnsureRegistered(void);
void igModelViewMatrixBoneSelect_EnsureRegistered(void);
void igNodeList_EnsureRegistered(void);
void igNonRefCountedNodeList_EnsureRegistered(void);
void igProjectiveShadowShader_EnsureRegistered(void);
void igSceneInfo_EnsureRegistered(void);
void igShaderFactoryList_EnsureRegistered(void);
void igShaderInfo_EnsureRegistered(void);
void igSkeletonBoneInfoList_EnsureRegistered(void);
void igSkeletonBoneInfo_EnsureRegistered(void);
void igSkeletonList_EnsureRegistered(void);
void igSkeleton_EnsureRegistered(void);
void igSkinList_EnsureRegistered(void);
void igSkin_EnsureRegistered(void);
void igSwitch_EnsureRegistered(void);
void igTransformList_EnsureRegistered(void);
void igTransformRecorder_EnsureRegistered(void);
void igTransformSequence1_5_EnsureRegistered(void);
void igTransform_EnsureRegistered(void);
void igTraversalFunctionList_EnsureRegistered(void);

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
