int igTraversal_GetMeta(void) {
    return ((int)g_igTraversal_metaObject);
}

void Gap__Bec__beHitLandModelTraversal__vfunc_25(beHitLandModelTraversal *arg0, long long arg1) {
    arg0->_timeLong = arg1;
}

igMetaObject *igTransformSequence1_5_GetMeta(void) {
    return g_igTransformSequence1_5_metaObject;
}

void Gap__Sg__igTransformSequence1_5__vfunc_53(IgForwardTarget_1e28b0 *o) { o->slot23(); }

void Gap__Sg__igTransformSequence1_5__vfunc_54(IgForwardTarget_1e28c0 *o) { o->slot25(); }

void Gap__Sg__igTransformSequence1_5__vfunc_36(TransformSequenceChannelView *o, int index) {
    List_RemoveAt((igDataList *)o->_timeListLong, index, 8);
    if (o->_drivenChannels & 1) { List_RemoveAt((igDataList *)o->_xlateList, index, 12); }
    if ((o->_drivenChannels & 2) || (o->_drivenChannels & 4)) { List_RemoveAt((igDataList *)o->_quatList, index, 16); }
    if (o->_drivenChannels & 8) { List_RemoveAt((igDataList *)o->_scaleList, index, 12); }
}

void Gap__Sg__igTransformSequence1_5__vfunc_38(struct T_1e2970 *t, int n) {
    struct L_1e2970 *l;
    l = t->d;
    if (n >= 0) {
        if (n <= l->cap) {
            l->count = n;
        } else {
            ((Gap::Core::igDataList *)l)->resizeAndSetCount(n, 8);
        }
    }
    if (t->flags & 1) {
        l = t->a;
        if (n >= 0) {
            if (n <= l->cap) {
                l->count = n;
            } else {
                ((Gap::Core::igDataList *)l)->resizeAndSetCount(n, 12);
            }
        }
    }
    if ((t->flags & 2) || (t->flags & 4)) {
        l = t->b;
        if (n >= 0) {
            if (n <= l->cap) {
                l->count = n;
            } else {
                ((Gap::Core::igDataList *)l)->resizeAndSetCount(n, 16);
            }
        }
    }
    if (t->flags & 8) {
        l = t->c;
        if (n >= 0) {
            if (n <= l->cap) {
                l->count = n;
            } else {
                ((Gap::Core::igDataList *)l)->resizeAndSetCount(n, 12);
            }
        }
    }
}

void Gap__Sg__igTransformSequence1_5__vfunc_55(igTransformSequence1_5 *arg0, int arg1, long long arg2) {
    void *temp_a3;
    int temp_v1;

    temp_a3 = (void *)(arg0->_timeListLong);
    temp_v1 = *(int *)((char *)(temp_a3) + 8);
    if ((temp_v1 != 0) && (arg1 >= 0) && (arg1 < temp_v1)) {
        *(long long *)(*(int *)((char *)(temp_a3) + 16) + (arg1 * 8)) = arg2;
    }
}

/* IgTransformSequence1_5 vfunc_40: overwrite one keyframe of the translation list (_xlateList,
 * 12-byte x/y/z entries) with the vector at `translation`. Does nothing unless bit 0 of
 * _drivenChannels is set and `index` is inside the list. Sibling accessors with the same shape:
 * vfunc_44 (quaternion list, bit 1) and vfunc_49 (scale list, bit 3). */

void Gap__Sg__igTransformSequence1_5__vfunc_40(igTransformSequence1_5 *self, int index, float *translation) {
    igVec3fList *xlateList;
    int count;
    float *entry;

    if (self->_drivenChannels & 1) {
        xlateList = (igVec3fList *)(self->_xlateList);
        count = xlateList->_count;
        if ((count != 0) && (index >= 0) && (index < count)) {
            entry = (float *)(xlateList->_data + (index * 0xC));
            entry[0] = translation[0];
            entry[1] = translation[1];
            entry[2] = translation[2];
        }
    }
}

/* Overwrites rotation key `index` (a 16-byte quaternion of _quatList) with the four floats at
 * `quaternion`. Ignored unless channel bit 2 of _drivenChannels is set and the index is inside the
 * list (the sibling accessors vfunc_42/vfunc_48 gate their lists on _drivenChannels the same way). */

void Gap__Sg__igTransformSequence1_5__vfunc_44(igTransformSequence1_5 *self, int index, void *quaternion) {
    igQuaternionfList *quatList;
    int count;
    void *key;

    if (self->_drivenChannels & 2) {
        quatList = (igQuaternionfList *)(self->_quatList);
        count = quatList->_count;
        if ((count != 0) && (index >= 0) && (index < count)) {
            key = (void *)(quatList->_data + (index * 0x10));
            *(float *)((char *)(key) + 0) = (float) *(float *)((char *)(quaternion) + 0);
            *(float *)((char *)(key) + 4) = (float) *(float *)((char *)(quaternion) + 4);
            *(float *)((char *)(key) + 8) = (float) *(float *)((char *)(quaternion) + 8);
            *(float *)((char *)(key) + 12) = (float) *(float *)((char *)(quaternion) + 12);
        }
    }
}

void Gap__Sg__igTransformSequence1_5__vfunc_47(igTransformSequence1_5 *arg0, int arg1, void *arg2) {
    void *temp_v1;
    if (arg0->_drivenChannels & 4) {
        float z = *(float *)((char *)(arg2) + 8);
        float y = *(float *)((char *)(arg2) + 4);
        float x = *(float *)((char *)(arg2) + 0);
        temp_v1 = (void *)(((igDataList *)arg0->_quatList)->_data + (arg1 * 0x10));
        *(float *)((char *)(temp_v1) + 0) = x;
        *(float *)((char *)(temp_v1) + 4) = y;
        *(float *)((char *)(temp_v1) + 8) = z;
        *(int *)((char *)(temp_v1) + 12) = 0;
    }
}

#define TRANSFORM_CHANNEL_SCALE 8
/* IgTransformSequence1_5 vfunc_49: store one scale key. When the sequence drives the scale channel
 * it copies the three floats at `scale` into key `index` of _scaleList (12 bytes per key); a
 * missing channel or an out-of-range index is ignored. Counterpart of vfunc_50, which returns the
 * address of the same key (it tests the same channel bit and uses the same 12-byte stride). */

/* _drivenChannels bit for the scale channel (vfunc_50 tests it before reading _scaleList) */

void Gap__Sg__igTransformSequence1_5__vfunc_49(igTransformSequence1_5 *self, int index, void *scale) {
    igVec3fList *scaleList;
    int count;
    float *key;
    float *src;

    if (self->_drivenChannels & TRANSFORM_CHANNEL_SCALE) {
        scaleList = (igVec3fList *)(self->_scaleList);
        count = scaleList->_count;
        if ((count != 0) && (index >= 0) && (index < count)) {
            key = (float *)(scaleList->_data + (index * 0xC));
            src = (float *)scale;
            key[0] = (float) src[0];
            key[1] = (float) src[1];
            key[2] = (float) src[2];
        }
    }
}
#undef TRANSFORM_CHANNEL_SCALE

long long Gap__Sg__igTransformSequence1_5__vfunc_63(igTransformSequence1_5 *self) {
    return self->_keyframeTimeOffset;
}

void Gap__Sg__igTransformSequence1_5__vfunc_64(igTransformSequence1_5 *self, long long arg1) {
    self->_animationDuration = arg1;
}

/* Caches the sequence length: the span from the first to the last key time, computed once while the
 * duration is still unset (-1). The first key time is read through self->_timeListLong again rather than
 * through {times} (matching construct: the second read makes the data pointer take its register before
 * the scaled index). */
void igTransformSequence1_5_UserPostLoad(igTransformSequence1_5 *self) {
    if (self->_animationDuration == -1) {
        igTDataList<long long> *times = (igTDataList<long long> *)self->_timeListLong;
        int count = times->count();
        int last = count - 1;
        if (count != 0) {
            self->_animationDuration = times->get(last) - ((igTDataList<long long> *)self->_timeListLong)->get(0);
        } else {
            self->_animationDuration = 0;
        }
    }
}

void FUN_001e2cd0(IgForwardTarget_1e2cd0 *o) { o->slot21(); }

/* Setter for the reflected bool field _uniformTimeEnabled. */

void FUN_001e2ce0(igTransformSequence1_5 *self, char enabled) {
    self->_uniformTimeEnabled = enabled;
}

void FUN_001e2cf0(void *arg0) {
    *(int *)((char *)(arg0) + 40) = 1;
}

igMetaObject *FUN_001e2d00(void) {
    return g_igTransformSequence_metaObject;
}

int FUN_001e2d10(void **arg0, int arg1) {
    char sp30[64];
    int temp_s0;

    temp_s0 = ((DW4VC_96_1 *)(arg0))->vX((int)(&sp30[0])) & 0xFF;
    igMatrix44f_GetQuaternion((float *)arg1, (float *)&sp30[0]);
    return temp_s0;
}

void FUN_001e2d60(IgForwardTarget_1e2d60 *o) { o->slot23(); }

void FUN_001e2d70(IgForwardTarget_1e2d70 *o) { o->slot25(); }

void igTransform_SetMatrix(igTransform *self, const float *matrix) {
    igMatrix44f_Copy(self->_m, matrix);
}

/* Slot 36, shared by igTransform descendants: store the igTransform::_target field (+96). */
void Gap__Core__igObject__vfunc_36(igTransform *self, int target)
{
    self->_target = target;
}

void igNode_Reset(void)
{
}

int igShaderProcessor_ConfigureRequired(void) {
    return 0;
}

int igSwitch_GetMeta(void) {
    return ((int)g_igSwitch_metaObject);
}

int igSwitch_IsChildrenOrdered(void) {
    return 1;
}

int igSorter_GetMeta(void) {
    return ((int)g_igSorter_metaObject);
}

igMetaObject *igSkeleton_GetMeta(void) {
    return g_igSkeleton_metaObject;
}

int igSkeleton_GetJointCount(igSkeleton *self) {
    return self->_jointCount;
}

int *igSkeleton_GetBoneName(igSkeleton *self, int arg1) {
    int *temp_v0;

    temp_v0 = (int *)(*(int *)((char *)((*(int *)(*(int *)((char *)(self->_boneInfoList) + 16) + (arg1 * 4)))) + 8));
    if (temp_v0 != 0) {
        return temp_v0;
    }
    return (int *)emptyString;
}

int igSkeleton_GetParent(igSkeleton *self, int arg1) {
    return *(int *)((char *)((*(int *)(*(int *)((char *)(self->_boneInfoList) + 16) + (arg1 * 4)))) + 12);
}

igMetaObject *igShaderInfo_GetMeta(void) {
    return g_igShaderInfo_metaObject;
}

igMetaObject *igShaderFactory_GetMeta(void) {
    return g_igShaderFactory_metaObject;
}

void igShaderFactory_PreloadFileCache(void) {

}

igMetaObject *igShaderData_GetMeta(void) {
    return g_igShaderData_metaObject;
}

igMetaObject *igSceneInfo_GetMeta(void) {
    return g_igSceneInfo_metaObject;
}

void igPlanarShadowShader_Reset(Shader *arg0) {
    arg0->f80->clear();
    arg0->f84->clear();
    arg0->f88->clear();
    Rel_1e2ec0::go(arg0->f92);
    arg0->f92 = 0;
    Rel_1e2ec0::go(arg0->f96);
    arg0->f96 = 0;
}

void Gap__Bec__ParticleTimer__vfunc_36(ParticleTimer *a0, int a1)
{
    a0->_trigger = a1;
}

int igNode_HasChildren(void) {
    return 0;
}

int igGeometry_IsChildrenOrdered(void)
{
    return 1;
}

igMetaObject *igLod_GetMeta(void) {
    return g_igLod_metaObject;
}

int igLod_IsChildrenOrdered(void) {
    return 1;
}

int Gap__Sg__igLod__vfunc_37(igLod *arg0) {
    if (arg0->_lastRange == 0) {
        return -1;
    }
    return arg0->_lastIndex;
}

int igLightStateSet_GetMeta(void) {
    return ((int)g_igLightStateSet_metaObject);
}

int igLightSet_GetMeta(void) {
    return ((int)g_igLightSet_metaObject);
}

igMetaObject *igIntersectTraversal_GetMeta(void) {
    return g_igIntersectTraversal_metaObject;
}

igMetaObject *igIniShaderFactory_GetMeta(void) {
    return g_igIniShaderFactory_metaObject;
}

igMetaObject *igGroup_GetMeta(void) {
    return g_igGroup_metaObject;
}

int igFrustCullTraversal_GetMeta(void) {
    return ((int)g_igFrustCullTraversal_metaObject);
}

void Gap__Sg__igCommonTraversal__vfunc_29(S0_1e31f0 *arg0, S1_1e31f0 *arg1) {
    S_temp_a0_1e31f0 *temp_a0;
    if (arg1 != 0) {
        arg1->f4 = (int)((int) (arg1->f4 + 1));
    }
    temp_a0 = (S_temp_a0_1e31f0 *)(arg0->f44);
    if (temp_a0 != 0) {
        temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
        if (((unsigned long long) ((long long) temp_a0->f4 << 0x29) >> 0x29) == 0) {
            igObject_Destroy((igObject *)temp_a0);
        }
    }
    arg0->f44 = (int)(arg1);
}

void Gap__Sg__igCommonTraversal__vfunc_27(igCommonTraversal *self, long long arg1) {
    T_1e3270 *t;

    t = (T_1e3270 *)self->_timeStack;
    if (n_of_1e3270(t) == 0) {
        self->_timeBuffered = 0;
        self->_timeLong = arg1;
    } else {
        *(long long *)(t->arr + t->n * 8 - 8) = arg1;
    }
}

igMetaObject *igEnbayaTransformSource_GetMeta(void) {
    return g_igEnbayaTransformSource_metaObject;
}

igMetaObject *igEnbayaContextPool_GetMeta(void) {
    return g_igEnbayaContextPool_metaObject;
}

igMetaObject *igEnbayaAnimationState_GetMeta(void) {
    return g_igEnbayaAnimationState_metaObject;
}

igMetaObject *igEnbayaAnimationSource_GetMeta(void) {
    return g_igEnbayaAnimationSource_metaObject;
}

/* Getter for the reflected `_channels` member (igUnsignedCharMetaField at +56). */


unsigned char Gap__Sg__igCompressedAnimationSequenceQS__vfunc_34(igCompressedAnimationSequenceQS *self) {
    return self->_channels;
}

void Gap__Sg__igCompressedAnimationSequenceQS__vfunc_37(struct S_1e3300 *arg0) {
    struct R *temp_a0;

    arg0->f56 = arg0->f56 & 0xFE;
    temp_a0 = arg0->p8;
    if (temp_a0 != 0) {
        temp_a0->rc = temp_a0->rc - 1;
        if ((temp_a0->rc & 0x7FFFFF) == 0) {
            igObject_Destroy((igObject *)temp_a0);
        }
    }
    arg0->p8 = 0;
}

int Gap__Sg__igCompressedAnimationSequenceQS__vfunc_38(void) {
    return 0;
}

int Gap__Sg__igCompressedAnimationSequenceQS__vfunc_39(void) {
    return 0;
}

void Gap__Sg__igCompressedAnimationSequenceQS__vfunc_40(void) {

}

int Gap__Sg__igCompressedAnimationSequenceQS__vfunc_41(void) {
    return 0;
}

/* Accessor: the sequence's reflected _animationDuration field (igUnsignedLongMetaField, +40). */
long long Gap__Sg__igCompressedAnimationSequenceQS__vfunc_43(igCompressedAnimationSequenceQS *self) {
    return self->_animationDuration;
}

/* Setter: stores the sequence length (`_animationDuration`, an igUnsignedLongMetaField of the
 * reflected igCompressedAnimationSequenceQS). */
void Gap__Sg__igCompressedAnimationSequenceQS__vfunc_45(igCompressedAnimationSequenceQS *self, long long animationDuration) {
    self->_animationDuration = animationDuration;
}

int igCompressedAnimationSequenceQS_evaluateRotation(void **arg0, int arg1) {
    int sp30[16];
    int temp_s0;

    temp_s0 = ((DW4VC_96_1 *)(arg0))->vX((int)(sp30)) & 0xFF;
    igMatrix44f_GetQuaternion((float *)arg1, (float *)sp30);
    return temp_s0;
}

igMetaObject *igCompressedAnimationSequenceQS_GetMeta(void) {
    return g_igCompressedAnimationSequenceQS_metaObject;
}

int igCompileTraversal_GetMeta(void) {
    return ((int)g_igCompileTraversal_metaObject);
}

igMetaObject *igCommonTraversal_GetMeta(void) {
    return g_igCommonTraversal_metaObject;
}

int igCamera_IsTransformable(void) {
    return 0;
}

igMetaObject *igAttrStackManager_GetMeta(void) {
    return g_igAttrStackManager_metaObject;
}

igMetaObject *igAttrSet_GetMeta(void) {
    return g_igAttrSet_metaObject;
}

int igAnimationState_GetMeta(void) {
    return ((int)g_igAnimationState_metaObject);
}

igMetaObject *igAnimationDatabase_GetMeta(void) {
    return g_igAnimationDatabase_metaObject;
}

igMetaObject *igAnimationCombiner_GetMeta(void) {
    return g_igAnimationCombiner_metaObject;
}

unsigned char igAnimationCombiner_GetHierarchyUpdated(igAnimationCombiner *self) {
    return self->_hierarchyUpdated;
}

int igAnimationCombiner_GetBoneMatrixArray(igAnimationCombiner *self) {
    return self->_boneMatrixArray;
}

int igAnimationCombiner_GetBoneMatrix(igAnimationCombiner *self, int arg1) {
    return self->_boneMatrixArray + (arg1 << 6);
}

int igAnimationCombiner_GetBlendMatrixArray(igAnimationCombiner *self) {
    return self->_blendMatrixArray;
}

int igAnimationCombiner_GetBlendMatrix(igAnimationCombiner *self, int arg1) {
    return self->_blendMatrixArray + (arg1 << 6);
}

int igActor_GetMeta(void) {
    return ((int)g_igActor_metaObject);
}

int igActor_IsTransformable(void) {
    return 0;
}

int igActorList_GetMeta(void) {
    return ((int)g_igActorList_metaObject);
}

igMetaObject *igActorInfo_GetMeta(void) {
    return g_igActorInfo_metaObject;
}

igMetaObject *igAnimationTrack_GetMeta(void) {
    return g_igAnimationTrack_metaObject;
}

igMetaObject *igAnimationTrackList_GetMeta(void) {
    return g_igAnimationTrackList_metaObject;
}

igMetaObject *igAnimationTransitionParams_GetMeta(void) {
    return g_igAnimationTransitionParams_metaObject;
}

igMetaObject *igAnimationTransitionPoint_GetMeta(void) {
    return g_igAnimationTransitionPoint_metaObject;
}

igMetaObject *igAnimationTransitionPointList_GetMeta(void) {
    return g_igAnimationTransitionPointList_metaObject;
}

igMetaObject *igAnimationTransitionDefinition_GetMeta(void) {
    return g_igAnimationTransitionDefinition_metaObject;
}

igMetaObject *igAnimationTransitionDefinitionList_GetMeta(void) {
    return g_igAnimationTransitionDefinitionList_metaObject;
}

igMetaObject *igAnimationList_GetMeta(void) {
    return g_igAnimationList_metaObject;
}

igMetaObject *igAnimationBinding_GetMeta(void) {
    return g_igAnimationBinding_metaObject;
}

igMetaObject *igAnimationBindingList_GetMeta(void) {
    return g_igAnimationBindingList_metaObject;
}

/* Returns the metaobject slot of igAnimationSystem, not of the binding list. */
int FUN_001e35e0(void) {
    return ((int)g_igAnimationSystem_metaObject);
}

int FUN_001e35f0(igAnimationBindingList *self) {
    return self->_capacity != 0;
}

int igAnimationCombinerList_GetMeta(void) {
    return ((int)g_igAnimationCombinerList_metaObject);
}

igMetaObject *igAnimationCombinerBoneInfo_GetMeta(void) {
    return g_igAnimationCombinerBoneInfo_metaObject;
}

igMetaObject *igAnimationCombinerBoneInfoList_GetMeta(void) {
    return g_igAnimationCombinerBoneInfoList_metaObject;
}

igMetaObject *igAnimationCombinerBoneInfoListList_GetMeta(void) {
    return g_igAnimationCombinerBoneInfoListList_metaObject;
}

igMetaObject *igAnimationCombinerBoneInfoPool_GetMeta(void) {
    return g_igAnimationCombinerBoneInfoPool_metaObject;
}

igMetaObject *igObjectPool_GetMeta(void) {
    return g_igObjectPool_metaObject;
}

igMetaObject *igAnimationModifier_GetMeta(void) {
    return g_igAnimationModifier_metaObject;
}

igMetaObject *igAnimationModifierList_GetMeta(void) {
    return g_igAnimationModifierList_metaObject;
}

igMetaObject *igAnimationStateList_GetMeta(void) {
    return g_igAnimationStateList_metaObject;
}

igMetaObject *igAnimationStatePool_GetMeta(void) {
    return g_igAnimationStatePool_metaObject;
}

igMetaObject *igAppearance_GetMeta(void) {
    return g_igAppearance_metaObject;
}

igMetaObject *igAppearanceList_GetMeta(void) {
    return g_igAppearanceList_metaObject;
}

igMetaObject *igAttrStack_GetMeta(void) {
    return g_igAttrStack_metaObject;
}

igMetaObject *igAttrStackList_GetMeta(void) {
    return g_igAttrStackList_metaObject;
}

igMetaObject *igNonRefCountedAttrStackManagerList_GetMeta(void) {
    return g_igNonRefCountedAttrStackManagerList_metaObject;
}

igMetaObject *igBillboard_GetMeta(void) {
    return g_igBillboard_metaObject;
}

int igBillboard_IsTransformable(void) {
    return 0;
}

int igBitMask_GetMeta(void) {
    return ((int)g_igBitMask_metaObject);
}

int igUnsignedIntList_GetMeta(void) {
    return (int)g_igUnsignedIntList_metaObject;
}

igMetaObject *igBlendMatrixSelect_GetMeta(void) {
    return g_igBlendMatrixSelect_metaObject;
}

int igBoundingBoxesMaker_GetMeta(void) {
    return ((int)g_igBoundingBoxesMaker_metaObject);
}

igMetaObject *igCamera_GetMeta(void) {
    return g_igCamera_metaObject;
}

void igCamera_Activate(void) {

}

void igCamera_Deactivate(void) {

}

int igCompiledTransform_GetMeta(void) {
    return ((int)g_igCompiledTransform_metaObject);
}

igMetaObject *igCompiledTransformList_GetMeta(void) {
    return g_igCompiledTransformList_metaObject;
}

igMetaObject *igBlendListRecord_GetMeta(void) {
    return g_igBlendListRecord_metaObject;
}

igMetaObject *igCompressedTransformSequence1_5Data_GetMeta(void) {
    return g_igCompressedTransformSequence1_5Data_metaObject;
}

igMetaObject *igEnvironmentMapShader2List_GetMeta(void) {
    return g_igEnvironmentMapShader2List_metaObject;
}

igMetaObject *igGeometryList_GetMeta(void) {
    return g_igGeometryList_metaObject;
}

igMetaObject *igGraphPath_GetMeta(void) {
    return g_igGraphPath_metaObject;
}

igMetaObject *igGraphPathList_GetMeta(void) {
    return g_igGraphPathList_metaObject;
}

igMetaObject *igInterpretedShaderData_GetMeta(void) {
    return g_igInterpretedShaderData_metaObject;
}

igMetaObject *igProbe_GetMeta(void) {
    return g_igProbe_metaObject;
}

igMetaObject *igAnimation_GetMeta(void) {
    return g_igAnimation_metaObject;
}

int igModelViewMatrixBoneSelect_GetMeta(void) {
    return ((int)g_igModelViewMatrixBoneSelect_metaObject);
}

igMetaObject *igModelViewMatrixBoneSelectListSg_GetPublishedMetaObject(void) {
    return g_igModelViewMatrixBoneSelectListSg_metaObject;
}

igMetaObject *igNodeList_GetMeta(void) {
    return g_igNodeList_metaObject;
}

igMetaObject *igNodeListList_GetMeta(void) {
    return g_igNodeListList_metaObject;
}

igMetaObject *igNonRefCountedNodeList_GetMeta(void) {
    return g_igNonRefCountedNodeList_metaObject;
}

igMetaObject *igOverrideAttrSet_GetMeta(void) {
    return g_igOverrideAttrSet_metaObject;
}

int igSegment_GetMeta(void) {
    return ((int)g_igSegment_metaObject);
}

int igSegment_IsTransformable(void) {
    return 0;
}

int igTraversalFunctionList_GetMeta(void) {
    return ((int)g_igTraversalFunctionList_metaObject);
}

igMetaObject *igLightStateAttrPool_GetMeta(void) {
    return g_igLightStateAttrPool_metaObject;
}

igMetaObject *igModelViewMatrixAttrPool_GetMeta(void) {
    return g_igModelViewMatrixAttrPool_metaObject;
}

igMetaObject *igTimeAttrPool_GetMeta(void) {
    return g_igTimeAttrPool_metaObject;
}

igMetaObject *igProjectionMatrixAttrPool_GetMeta(void) {
    return g_igProjectionMatrixAttrPool_metaObject;
}

igMetaObject *igVertexBlendMatrixAttrPool_GetMeta(void) {
    return g_igVertexBlendMatrixAttrPool_metaObject;
}

igMetaObject *igVertexBlendMatrixListAttrPool_GetMeta(void) {
    return g_igVertexBlendMatrixListAttrPool_metaObject;
}

igMetaObject *igMatrixObjectPool_GetMeta(void) {
    return g_igMatrixObjectPool_metaObject;
}

igMetaObject *igTextureMatrixAttrPool_GetMeta(void) {
    return g_igTextureMatrixAttrPool_metaObject;
}

igMetaObject *igBlendMatricesAttrPool_GetMeta(void) {
    return g_igBlendMatricesAttrPool_metaObject;
}

igMetaObject *igShaderFactoryList_GetMeta(void) {
    return g_igShaderFactoryList_metaObject;
}

igMetaObject *igSkeletonBoneInfo_GetMeta(void) {
    return g_igSkeletonBoneInfo_metaObject;
}

igMetaObject *igSkeletonBoneInfoList_GetMeta(void) {
    return g_igSkeletonBoneInfoList_metaObject;
}

igMetaObject *igSkeletonList_GetMeta(void) {
    return g_igSkeletonList_metaObject;
}

igMetaObject *igSkin_GetMeta(void) {
    return g_igSkin_metaObject;
}

igMetaObject *igSkinList_GetMeta(void) {
    return g_igSkinList_metaObject;
}

igMetaObject *igRenderPackage_GetMeta(void) {
    return g_igRenderPackage_metaObject;
}

igMetaObject *igRenderPackagePool_GetMeta(void) {
    return g_igRenderPackagePool_metaObject;
}

igMetaObject *igRenderPackageList_GetMeta(void) {
    return g_igRenderPackageList_metaObject;
}

int igDoubleList_GetMeta(void) {
    return (int)g_igDoubleList_metaObject;
}

igMetaObject *igTransformStack_GetMeta(void) {
    return g_igTransformStack_metaObject;
}

igMetaObject *igTransformList_GetMeta(void) {
    return g_igTransformList_metaObject;
}

igMetaObject *igNonRefCountedTransformList_GetMeta(void) {
    return g_igNonRefCountedTransformList_metaObject;
}

igMetaObject *igTransformRecorder_GetMeta(void) {
    return g_igTransformRecorder_metaObject;
}

int igTransientShaderData_GetMeta(void) {
    return ((int)g_igTransientShaderData_metaObject);
}

igMetaObject *igRenderPackageList_GetElementMeta(void) {
    return g_igRenderPackage_metaObject;
}

igMetaObject *igNonRefCountedAttrStackManagerList_GetElementMeta(void) {
    return g_igAttrStackManager_metaObject;
}

igMetaObject *igNonRefCountedTransformList_GetElementMeta(void) {
    return g_igTransform_metaObject;
}

igMetaObject *igNonRefCountedNodeList_GetElementMeta(void) {
    return g_igNode_metaObject;
}

int igTraversalFunctionList_GetElementSize(igTraversalFunctionList *self) {
    return 4;
}

int igDoubleList_GetElementSize(void) {
    return 8;
}

int igUnsignedIntList_GetElementSize(void) {
    return 4;
}

int FUN_001e3ab0(igIntList *list, int *value) {
    int lo;
    int hi;
    int mid;
    int key;
    int count;
    int entry;
    count = list->_count;
    hi = count - 1;
    lo = 0;
    while (lo < hi) {
        key = *value;
        mid = (lo + hi) >> 1;
        entry = ((int *)list->_data)[mid];
        if (entry < key) {
            lo = mid + 1;
        } else if (key < entry) {
            hi = mid - 1;
        } else {
            return mid;
        }
    }
    if (!count) {
        return 0;
    }
    return ((int *)list->_data)[lo] < *value ? 1 + lo : lo;
}

/* Returns the metaobject slot of the element class igActor, not of the list. */
int igActorList_GetElementMeta(void) {
    return ((int)g_igActor_metaObject);
}

/* Returns the metaobject slot of the element class igAnimationCombiner, not of the list. */
igMetaObject *igAnimationCombinerList_GetElementMeta(void) {
    return g_igAnimationCombiner_metaObject;
}

igMetaObject *igAppearanceList_GetElementMeta(void) {
    return g_igAppearance_metaObject;
}

igMetaObject *igAnimationStateList_GetElementMeta(void) {
    return g_igAnimationState_metaObject;
}

igMetaObject *igAnimationCombinerBoneInfoListList_GetElementMeta(void) {
    return g_igAnimationCombinerBoneInfoList_metaObject;
}

igMetaObject *igAnimationCombinerBoneInfoList_GetElementMeta(void) {
    return g_igAnimationCombinerBoneInfo_metaObject;
}

igMetaObject *igEnvironmentMapShader2List_GetElementMeta(void) {
    return g_igEnvironmentMapShader2_metaObject;
}

igMetaObject *igGraphPathList_GetElementMeta(void) {
    return g_igGraphPath_metaObject;
}

igMetaObject *igAnimationList_GetElementMeta(void) {
    return g_igAnimation_metaObject;
}

igMetaObject *igAnimationTransitionDefinitionList_GetElementMeta(void) {
    return g_igAnimationTransitionDefinition_metaObject;
}

igMetaObject *igAnimationTransitionPointList_GetElementMeta(void) {
    return g_igAnimationTransitionPoint_metaObject;
}

igMetaObject *igAnimationTrackList_GetElementMeta(void) {
    return g_igAnimationTrack_metaObject;
}

igMetaObject *igAnimationBindingList_GetElementMeta(void) {
    return g_igAnimationBinding_metaObject;
}

int Gap__Bec__igModelViewMatrixBoneSelectList__vfunc_22(void)
{
    return ((int)g_igModelViewMatrixBoneSelect_metaObject);
}

igMetaObject *igShaderFactoryList_GetElementMeta(void) {
    return g_igShaderFactory_metaObject;
}

igMetaObject *igSkeletonList_GetElementMeta(void) {
    return g_igSkeleton_metaObject;
}

igMetaObject *igSkeletonBoneInfoList_GetElementMeta(void) {
    return g_igSkeletonBoneInfo_metaObject;
}

igMetaObject *igAnimationModifierList_GetElementMeta(void) {
    return g_igAnimationModifier_metaObject;
}

igMetaObject *igSkinList_GetElementMeta(void) {
    return g_igSkin_metaObject;
}

int igCompiledTransformList_GetElementMeta(void) {
    return ((int)g_igCompiledTransform_metaObject);
}

igMetaObject *igGeometryList_GetElementMeta(void) {
    return g_igGeometry_metaObject;
}

igMetaObject *igAttrStackList_GetElementMeta(void) {
    return g_igAttrStack_metaObject;
}

igMetaObject *igTransformList_GetElementMeta(void) {
    return g_igTransform_metaObject;
}

igMetaObject *igNodeListList_GetElementMeta(void) {
    return g_igNodeList_metaObject;
}

igMetaObject *igNodeList_GetElementMeta(void) {
    return g_igNode_metaObject;
}

void igUnsignedIntList_TrimCapacity(igUnsignedIntList *self) {
    int temp_a1;

    temp_a1 = self->_count;
    if (temp_a1 < self->_capacity) {
        ((Gap::Core::igDataList *)self)->setCapacity(temp_a1, 4);
    }
}

void igDoubleList_TrimCapacity(igDataList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        ((Gap::Core::igDataList *)arg0)->setCapacity(temp_a1, 8);
    }
}

void igTraversalFunctionList_TrimCapacity(igTraversalFunctionList *self) {
    int temp_a1;

    temp_a1 = self->_count;
    if (temp_a1 < self->_capacity) {
        ((Gap::Core::igDataList *)self)->setCapacity(temp_a1, 4);
    }
}

/* Deleting destructor; the deletion flag is a signed short. */
/* Deleting destructor; the deletion flag is a signed short. */
