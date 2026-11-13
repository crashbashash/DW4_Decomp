int Gap__Sg__igTraversal__vfunc_22(void) {
    return ((int *)g_igTraversal_metaObject)[0];
}

void Gap__Bec__beHitLandModelTraversal__vfunc_25(beHitLandModelTraversal *arg0, long long arg1) {
    arg0->_timeLong = arg1;
}

igMetaObject *Gap__Sg__igTransformSequence1_5__vfunc_22(void) {
    return g_igTransformSequence1_5_metaObject[0];
}

void Gap__Sg__igTransformSequence1_5__vfunc_53(IgForwardTarget_1e28b0 *o) { o->slot23(); }

void Gap__Sg__igTransformSequence1_5__vfunc_54(IgForwardTarget_1e28c0 *o) { o->slot25(); }

void Gap__Sg__igTransformSequence1_5__vfunc_36(TransformSequenceChannelView *o, int index) {
    List_RemoveAt(o->_timeListLong, index, 8);
    if (o->_drivenChannels & 1) { List_RemoveAt(o->_xlateList, index, 12); }
    if ((o->_drivenChannels & 2) || (o->_drivenChannels & 4)) { List_RemoveAt(o->_quatList, index, 16); }
    if (o->_drivenChannels & 8) { List_RemoveAt(o->_scaleList, index, 12); }
}

void Gap__Sg__igTransformSequence1_5__vfunc_38(struct T_1e2970 *t, int n) {
    struct L_1e2970 *l;
    l = t->d;
    if (n >= 0) {
        if (n <= l->cap) {
            l->count = n;
        } else {
            List_Resize((void *)l, n, 8);
        }
    }
    if (t->flags & 1) {
        l = t->a;
        if (n >= 0) {
            if (n <= l->cap) {
                l->count = n;
            } else {
                List_Resize((void *)l, n, 12);
            }
        }
    }
    if ((t->flags & 2) || (t->flags & 4)) {
        l = t->b;
        if (n >= 0) {
            if (n <= l->cap) {
                l->count = n;
            } else {
                List_Resize((void *)l, n, 16);
            }
        }
    }
    if (t->flags & 8) {
        l = t->c;
        if (n >= 0) {
            if (n <= l->cap) {
                l->count = n;
            } else {
                List_Resize((void *)l, n, 12);
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

long long Gap__Sg__igTransformSequence1_5__vfunc_63(void *arg0) {
    return *(long long *)((char *)arg0 + 80);
}

void Gap__Sg__igTransformSequence1_5__vfunc_64(void *arg0, long long arg1) {
    *(long long *)((char *)arg0 + 88) = arg1;
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
    return g_igTransformSequence_metaObject[0];
}

int FUN_001e2d10(void **arg0, int arg1) {
    char sp30[64];
    int temp_s0;

    temp_s0 = ((DW4VC_96_1 *)(arg0))->vX((int)(&sp30[0])) & 0xFF;
    Matrix44_GetQuaternion(arg1, &sp30[0]);
    return temp_s0;
}

void FUN_001e2d60(IgForwardTarget_1e2d60 *o) { o->slot23(); }

void FUN_001e2d70(IgForwardTarget_1e2d70 *o) { o->slot25(); }

void Gap__Core__igObject__vfunc_35(int a0) {
    Matrix44_Copy((char *)a0 + 32);
}

/* Slot 36, shared by igTransform descendants: store the igTransform::_target field (+96). */
void Gap__Core__igObject__vfunc_36(igTransform *self, int target)
{
    self->_target = target;
}

void Gap__Sg__igNode__vfunc_31(void)
{
}

int Gap__Sg__igShaderProcessor__vfunc_23(void) {
    return 0;
}

int Gap__Sg__igSwitch__vfunc_22(void) {
    return ((int *)g_igSwitch_metaObject)[0];
}

int Gap__Sg__igSwitch__vfunc_36(void) {
    return 1;
}

int Gap__Sg__igSorter__vfunc_22(void) {
    return ((int *)g_igSorter_metaObject)[0];
}

igMetaObject *Gap__Sg__igSkeleton__vfunc_22(void) {
    return g_igSkeleton_metaObject[0];
}

int Gap__Sg__igSkeleton__vfunc_25(void *arg0) {
    return *(int *)((char *)(arg0) + 24);
}

int *Gap__Sg__igSkeleton__vfunc_26(void *arg0, int arg1) {
    int *temp_v0;

    temp_v0 = (int *)(*(int *)((char *)((*(int *)(*(int *)((char *)(*(int *)((char *)(arg0) + 16)) + 16) + (arg1 * 4)))) + 8));
    if (temp_v0 != 0) {
        return temp_v0;
    }
    return &emptyString[0];
}

int Gap__Sg__igSkeleton__vfunc_28(void *arg0, int arg1) {
    return *(int *)((char *)((*(int *)(*(int *)((char *)(*(int *)((char *)(arg0) + 16)) + 16) + (arg1 * 4)))) + 12);
}

igMetaObject *Gap__Sg__igShaderInfo__vfunc_22(void) {
    return g_igShaderInfo_metaObject[0];
}

igMetaObject *Gap__Sg__igShaderFactory__vfunc_22(void) {
    return g_igShaderFactory_metaObject[0];
}

void Gap__Sg__igShaderFactory__vfunc_27(void) {

}

igMetaObject *Gap__Sg__igShaderData__vfunc_22(void) {
    return g_igShaderData_metaObject[0];
}

igMetaObject *Gap__Sg__igSceneInfo__vfunc_22(void) {
    return g_igSceneInfo_metaObject[0];
}

void Gap__Sg__igPlanarShadowShader__vfunc_31(Shader *arg0) {
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

int Gap__Sg__igNode__vfunc_25(void) {
    return 0;
}

int Gap__Bec__ParticleTimer__vfunc_34(void)
{
    return 1;
}

igMetaObject *Gap__Sg__igLod__vfunc_22(void) {
    return g_igLod_metaObject[0];
}

int Gap__Sg__igLod__vfunc_36(void) {
    return 1;
}

int Gap__Sg__igLod__vfunc_37(igLod *arg0) {
    if (arg0->_lastRange == 0) {
        return -1;
    }
    return arg0->_lastIndex;
}

int Gap__Sg__igLightStateSet__vfunc_22(void) {
    return ((int *)g_igLightStateSet_metaObject)[0];
}

int Gap__Sg__igLightSet__vfunc_22(void) {
    return ((int *)g_igLightSet_metaObject)[0];
}

igMetaObject *Gap__Sg__igIntersectTraversal__vfunc_22(void) {
    return g_igIntersectTraversal_metaObject[0];
}

igMetaObject *Gap__Sg__igIniShaderFactory__vfunc_22(void) {
    return g_igIniShaderFactory_metaObject[0];
}

igMetaObject *Gap__Sg__igGroup__vfunc_22(void) {
    return g_igGroup_metaObject[0];
}

int Gap__Sg__igFrustCullTraversal__vfunc_22(void) {
    return ((int *)g_igFrustCullTraversal_metaObject)[0];
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
            igObject_Destroy((void *)temp_a0);
        }
    }
    arg0->f44 = (int)(arg1);
}

void Gap__Sg__igCommonTraversal__vfunc_27(void *arg0, long long arg1) {
    T_1e3270 *t;

    t = *(T_1e3270 **)((char *)(arg0) + 240);
    if (n_of_1e3270(t) == 0) {
        *(char *)((char *)(arg0) + 48) = 0;
        *(long long *)((char *)(arg0) + 16) = arg1;
    } else {
        *(long long *)(t->arr + t->n * 8 - 8) = arg1;
    }
}

int Gap__Sg__igEnbayaTransformSource__vfunc_22(void) {
    return g_igEnbayaTransformSource_metaObject[0];
}

int Gap__Sg__igEnbayaContextPool__vfunc_22(void) {
    return g_igEnbayaContextPool_metaObject[0];
}

igMetaObject *Gap__Sg__igEnbayaAnimationState__vfunc_22(void) {
    return g_igEnbayaAnimationState_metaObject[0];
}

igMetaObject *Gap__Sg__igEnbayaAnimationSource__vfunc_22(void) {
    return g_igEnbayaAnimationSource_metaObject[0];
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
            igObject_Destroy((void *)temp_a0);
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

int Gap__Sg__igCompressedAnimationSequenceQS__vfunc_26(void **arg0, int arg1) {
    int sp30[16];
    int temp_s0;

    temp_s0 = ((DW4VC_96_1 *)(arg0))->vX((int)(sp30)) & 0xFF;
    Matrix44_GetQuaternion(arg1, sp30);
    return temp_s0;
}

igMetaObject *Gap__Sg__igCompressedAnimationSequenceQS__vfunc_22(void) {
    return g_igCompressedAnimationSequenceQS_metaObject[0];
}

int Gap__Sg__igCompileTraversal__vfunc_22(void) {
    return ((int *)g_igCompileTraversal_metaObject)[0];
}

igMetaObject *Gap__Sg__igCommonTraversal__vfunc_22(void) {
    return g_igCommonTraversal_metaObject[0];
}

int Gap__Sg__igCamera__vfunc_26(void) {
    return 0;
}

igMetaObject *Gap__Sg__igAttrStackManager__vfunc_22(void) {
    return g_igAttrStackManager_metaObject[0];
}

igMetaObject *Gap__Sg__igAttrSet__vfunc_22(void) {
    return g_igAttrSet_metaObject[0];
}

int Gap__Sg__igAnimationState__vfunc_22(void) {
    return ((int *)g_igAnimationState_metaObject)[0];
}

igMetaObject *Gap__Sg__igAnimationDatabase__vfunc_22(void) {
    return g_igAnimationDatabase_metaObject[0];
}

int Gap__Sg__igAnimationCombiner__vfunc_22(void) {
    return g_igAnimationCombiner_metaObject[0];
}

unsigned char Gap__Sg__igAnimationCombiner__vfunc_25(void *arg0) {
    return *(int *)((char *)(arg0) + 81);
}

int Gap__Sg__igAnimationCombiner__vfunc_27(void *arg0) {
    return *(int *)((char *)(arg0) + 84);
}

int Gap__Sg__igAnimationCombiner__vfunc_28(void *arg0, int arg1) {
    return *(int *)((char *)(arg0) + 84) + (arg1 << 6);
}

int Gap__Sg__igAnimationCombiner__vfunc_29(void *arg0) {
    return *(int *)((char *)(arg0) + 88);
}

int Gap__Sg__igAnimationCombiner__vfunc_30(void *arg0, int arg1) {
    return *(int *)((char *)(arg0) + 88) + (arg1 << 6);
}

int Gap__Sg__igActor__vfunc_22(void) {
    return ((int *)g_igActor_metaObject)[0];
}

int Gap__Sg__igActor__vfunc_26(void) {
    return 0;
}

int Gap__Sg__igActorList__vfunc_22(void) {
    return ((int *)g_igActorList_metaObject)[0];
}

igMetaObject *Gap__Sg__igActorInfo__vfunc_22(void) {
    return g_igActorInfo_metaObject[0];
}

igMetaObject *Gap__Sg__igAnimationTrack__vfunc_22(void) {
    return g_igAnimationTrack_metaObject[0];
}

igMetaObject *Gap__Sg__igAnimationTrackList__vfunc_22(void) {
    return g_igAnimationTrackList_metaObject[0];
}

igMetaObject *Gap__Sg__igAnimationTransitionParams__vfunc_22(void) {
    return g_igAnimationTransitionParams_metaObject[0];
}

igMetaObject *Gap__Sg__igAnimationTransitionPoint__vfunc_22(void) {
    return g_igAnimationTransitionPoint_metaObject[0];
}

igMetaObject *Gap__Sg__igAnimationTransitionPointList__vfunc_22(void) {
    return g_igAnimationTransitionPointList_metaObject[0];
}

igMetaObject *Gap__Sg__igAnimationTransitionDefinition__vfunc_22(void) {
    return g_igAnimationTransitionDefinition_metaObject[0];
}

igMetaObject *Gap__Sg__igAnimationTransitionDefinitionList__vfunc_22(void) {
    return g_igAnimationTransitionDefinitionList_metaObject[0];
}

igMetaObject *Gap__Sg__igAnimationList__vfunc_22(void) {
    return g_igAnimationList_metaObject[0];
}

igMetaObject *Gap__Sg__igAnimationBinding__vfunc_22(void) {
    return g_igAnimationBinding_metaObject[0];
}

igMetaObject *Gap__Sg__igAnimationBindingList__vfunc_22(void) {
    return g_igAnimationBindingList_metaObject[0];
}

/* Returns the metaobject slot of igAnimationSystem, not of the binding list. */
int FUN_001e35e0(void) {
    return ((int *)g_igAnimationSystem_metaObject)[0];
}

int FUN_001e35f0(igAnimationBindingList *self) {
    return self->_capacity != 0;
}

int Gap__Sg__igAnimationCombinerList__vfunc_22(void) {
    return ((int *)g_igAnimationCombinerList_metaObject)[0];
}

igMetaObject *Gap__Sg__igAnimationCombinerBoneInfo__vfunc_22(void) {
    return g_igAnimationCombinerBoneInfo_metaObject[0];
}

igMetaObject *Gap__Sg__igAnimationCombinerBoneInfoList__vfunc_22(void) {
    return g_igAnimationCombinerBoneInfoList_metaObject[0];
}

igMetaObject *Gap__Sg__igAnimationCombinerBoneInfoListList__vfunc_22(void) {
    return g_igAnimationCombinerBoneInfoListList_metaObject[0];
}

int Gap__Sg__igAnimationCombinerBoneInfoPool__vfunc_22(void) {
    return g_igAnimationCombinerBoneInfoPool_metaObject[0];
}

igMetaObject *Gap__Sg__igObjectPool__vfunc_22(void) {
    return g_igObjectPool_metaObject[0];
}

igMetaObject *Gap__Sg__igAnimationModifier__vfunc_22(void) {
    return g_igAnimationModifier_metaObject[0];
}

igMetaObject *Gap__Sg__igAnimationModifierList__vfunc_22(void) {
    return g_igAnimationModifierList_metaObject[0];
}

igMetaObject *Gap__Sg__igAnimationStateList__vfunc_22(void) {
    return g_igAnimationStateList_metaObject[0];
}

int Gap__Sg__igAnimationStatePool__vfunc_22(void) {
    return g_igAnimationStatePool_metaObject[0];
}

igMetaObject *Gap__Sg__igAppearance__vfunc_22(void) {
    return g_igAppearance_metaObject[0];
}

igMetaObject *Gap__Sg__igAppearanceList__vfunc_22(void) {
    return g_igAppearanceList_metaObject[0];
}

igMetaObject *Gap__Sg__igAttrStack__vfunc_22(void) {
    return g_igAttrStack_metaObject[0];
}

igMetaObject *Gap__Sg__igAttrStackList__vfunc_22(void) {
    return g_igAttrStackList_metaObject[0];
}

igMetaObject *Gap__Sg__igNonRefCountedAttrStackManagerList__vfunc_22(void) {
    return g_igNonRefCountedAttrStackManagerList_metaObject[0];
}

igMetaObject *Gap__Sg__igBillboard__vfunc_22(void) {
    return g_igBillboard_metaObject[0];
}

int Gap__Sg__igBillboard__vfunc_26(void) {
    return 0;
}

int Gap__Sg__igBitMask__vfunc_22(void) {
    return ((int *)g_igBitMask_metaObject)[0];
}

int Gap__Core__igUnsignedIntList__vfunc_22(void) {
    return g_igUnsignedIntList_metaObject[0];
}

igMetaObject *Gap__Sg__igBlendMatrixSelect__vfunc_22(void) {
    return g_igBlendMatrixSelect_metaObject[0];
}

int Gap__Sg__igBoundingBoxesMaker__vfunc_22(void) {
    return ((int *)g_igBoundingBoxesMaker_metaObject)[0];
}

igMetaObject *Gap__Sg__igCamera__vfunc_22(void) {
    return g_igCamera_metaObject[0];
}

void Gap__Sg__igCamera__vfunc_35(void) {

}

void Gap__Sg__igCamera__vfunc_36(void) {

}

int Gap__Sg__igCompiledTransform__vfunc_22(void) {
    return ((int *)g_igCompiledTransform_metaObject)[0];
}

igMetaObject *Gap__Sg__igCompiledTransformList__vfunc_22(void) {
    return g_igCompiledTransformList_metaObject[0];
}

igMetaObject *Gap__Sg__igBlendListRecord__vfunc_22(void) {
    return g_igBlendListRecord_metaObject[0];
}

igMetaObject *Gap__Sg__igCompressedTransformSequence1_5Data__vfunc_22(void) {
    return g_igCompressedTransformSequence1_5Data_metaObject[0];
}

igMetaObject *Gap__Sg__igEnvironmentMapShader2List__vfunc_22(void) {
    return g_igEnvironmentMapShader2List_metaObject[0];
}

igMetaObject *Gap__Sg__igGeometryList__vfunc_22(void) {
    return g_igGeometryList_metaObject[0];
}

igMetaObject *Gap__Sg__igGraphPath__vfunc_22(void) {
    return g_igGraphPath_metaObject[0];
}

igMetaObject *Gap__Sg__igGraphPathList__vfunc_22(void) {
    return g_igGraphPathList_metaObject[0];
}

igMetaObject *Gap__Sg__igInterpretedShaderData__vfunc_22(void) {
    return g_igInterpretedShaderData_metaObject[0];
}

igMetaObject *Gap__Sg__igProbe__vfunc_22(void) {
    return g_igProbe_metaObject[0];
}

igMetaObject *Gap__Sg__igAnimation__vfunc_22(void) {
    return g_igAnimation_metaObject[0];
}

int Gap__Sg__igModelViewMatrixBoneSelect__vfunc_22(void) {
    return ((int *)g_igModelViewMatrixBoneSelect_metaObject)[0];
}

igMetaObject *FUN_001e3840(void) {
    return g_igModelViewMatrixBoneSelectList_metaObject_00561880[0];
}

igMetaObject *Gap__Sg__igNodeList__vfunc_22(void) {
    return g_igNodeList_metaObject[0];
}

igMetaObject *Gap__Sg__igNodeListList__vfunc_22(void) {
    return g_igNodeListList_metaObject[0];
}

igMetaObject *Gap__Sg__igNonRefCountedNodeList__vfunc_22(void) {
    return g_igNonRefCountedNodeList_metaObject[0];
}

igMetaObject *Gap__Sg__igOverrideAttrSet__vfunc_22(void) {
    return g_igOverrideAttrSet_metaObject[0];
}

int Gap__Sg__igSegment__vfunc_22(void) {
    return ((int *)g_igSegment_metaObject)[0];
}

int Gap__Sg__igSegment__vfunc_26(void) {
    return 0;
}

int Gap__Sg__igTraversalFunctionList__vfunc_22(void) {
    return ((int *)g_igTraversalFunctionList_metaObject)[0];
}

igMetaObject *Gap__Sg__igLightStateAttrPool__vfunc_22(void) {
    return g_igLightStateAttrPool_metaObject[0];
}

igMetaObject *Gap__Sg__igModelViewMatrixAttrPool__vfunc_22(void) {
    return g_igModelViewMatrixAttrPool_metaObject[0];
}

igMetaObject *Gap__Sg__igTimeAttrPool__vfunc_22(void) {
    return g_igTimeAttrPool_metaObject[0];
}

igMetaObject *Gap__Sg__igProjectionMatrixAttrPool__vfunc_22(void) {
    return g_igProjectionMatrixAttrPool_metaObject[0];
}

igMetaObject *Gap__Sg__igVertexBlendMatrixAttrPool__vfunc_22(void) {
    return g_igVertexBlendMatrixAttrPool_metaObject[0];
}

igMetaObject *Gap__Sg__igVertexBlendMatrixListAttrPool__vfunc_22(void) {
    return g_igVertexBlendMatrixListAttrPool_metaObject[0];
}

igMetaObject *Gap__Sg__igMatrixObjectPool__vfunc_22(void) {
    return g_igMatrixObjectPool_metaObject[0];
}

igMetaObject *Gap__Sg__igTextureMatrixAttrPool__vfunc_22(void) {
    return g_igTextureMatrixAttrPool_metaObject[0];
}

igMetaObject *Gap__Sg__igBlendMatricesAttrPool__vfunc_22(void) {
    return g_igBlendMatricesAttrPool_metaObject[0];
}

igMetaObject *Gap__Sg__igShaderFactoryList__vfunc_22(void) {
    return g_igShaderFactoryList_metaObject[0];
}

igMetaObject *Gap__Sg__igSkeletonBoneInfo__vfunc_22(void) {
    return g_igSkeletonBoneInfo_metaObject[0];
}

igMetaObject *Gap__Sg__igSkeletonBoneInfoList__vfunc_22(void) {
    return g_igSkeletonBoneInfoList_metaObject[0];
}

igMetaObject *Gap__Sg__igSkeletonList__vfunc_22(void) {
    return g_igSkeletonList_metaObject[0];
}

igMetaObject *Gap__Sg__igSkin__vfunc_22(void) {
    return g_igSkin_metaObject[0];
}

igMetaObject *Gap__Sg__igSkinList__vfunc_22(void) {
    return g_igSkinList_metaObject[0];
}

igMetaObject *Gap__Sg__igRenderPackage__vfunc_22(void) {
    return g_igRenderPackage_metaObject[0];
}

igMetaObject *Gap__Sg__igRenderPackagePool__vfunc_22(void) {
    return g_igRenderPackagePool_metaObject[0];
}

igMetaObject *Gap__Sg__igRenderPackageList__vfunc_22(void) {
    return g_igRenderPackageList_metaObject[0];
}

int Gap__Core__igDoubleList__vfunc_22(void) {
    return g_igDoubleList_metaObject[0];
}

igMetaObject *Gap__Sg__igTransformStack__vfunc_22(void) {
    return g_igTransformStack_metaObject[0];
}

igMetaObject *Gap__Sg__igTransformList__vfunc_22(void) {
    return g_igTransformList_metaObject[0];
}

igMetaObject *Gap__Sg__igNonRefCountedTransformList__vfunc_22(void) {
    return g_igNonRefCountedTransformList_metaObject[0];
}

igMetaObject *Gap__Sg__igTransformRecorder__vfunc_22(void) {
    return g_igTransformRecorder_metaObject[0];
}

int Gap__Sg__igTransientShaderData__vfunc_22(void) {
    return ((int *)g_igTransientShaderData_metaObject)[0];
}

igMetaObject *Gap__Sg__igRenderPackageList__vfunc_24(void) {
    return g_igRenderPackage_metaObject[0];
}

igMetaObject *Gap__Sg__igNonRefCountedAttrStackManagerList__vfunc_24(void) {
    return g_igAttrStackManager_metaObject[0];
}

igMetaObject *Gap__Sg__igNonRefCountedTransformList__vfunc_24(void) {
    return g_igTransform_metaObject[0];
}

igMetaObject *Gap__Sg__igNonRefCountedNodeList__vfunc_24(void) {
    return g_igNode_metaObject[0];
}

int Gap__Sg__igTraversalFunctionList__vfunc_23(igTraversalFunctionList *self) {
    return 4;
}

int Gap__Core__igDoubleList__vfunc_23(void) {
    return 8;
}

int Gap__Core__igUnsignedIntList__vfunc_23(void) {
    return 4;
}

int FUN_001e3ab0(struct L_1e3500 *arg0, int *arg1) {
    int lo;
    int hi;
    int mid;
    int b;
    int cnt;
    int a;
    cnt = arg0->cnt;
    hi = cnt - 1;
    lo = 0;
    while (lo < hi) {
        b = *arg1;
        mid = (lo + hi) >> 1;
        a = arg0->items[mid];
        if (a < b) {
            lo = mid + 1;
        } else if (b < a) {
            hi = mid - 1;
        } else {
            return mid;
        }
    }
    if (!cnt) {
        return 0;
    }
    return arg0->items[lo] < *arg1 ? 1 + lo : lo;
}

/* Returns the metaobject slot of the element class igActor, not of the list. */
int Gap__Sg__igActorList__vfunc_24(void) {
    return ((int *)g_igActor_metaObject)[0];
}

/* Returns the metaobject slot of the element class igAnimationCombiner, not of the list. */
int Gap__Sg__igAnimationCombinerList__vfunc_24(void) {
    return g_igAnimationCombiner_metaObject[0];
}

igMetaObject *Gap__Sg__igAppearanceList__vfunc_24(void) {
    return g_igAppearance_metaObject[0];
}

igMetaObject *Gap__Sg__igAnimationStateList__vfunc_24(void) {
    return g_igAnimationState_metaObject[0];
}

igMetaObject *Gap__Sg__igAnimationCombinerBoneInfoListList__vfunc_24(void) {
    return g_igAnimationCombinerBoneInfoList_metaObject[0];
}

igMetaObject *Gap__Sg__igAnimationCombinerBoneInfoList__vfunc_24(void) {
    return g_igAnimationCombinerBoneInfo_metaObject[0];
}

igMetaObject *Gap__Sg__igEnvironmentMapShader2List__vfunc_24(void) {
    return g_igEnvironmentMapShader2_metaObject[0];
}

igMetaObject *Gap__Sg__igGraphPathList__vfunc_24(void) {
    return g_igGraphPath_metaObject[0];
}

igMetaObject *Gap__Sg__igAnimationList__vfunc_24(void) {
    return g_igAnimation_metaObject[0];
}

igMetaObject *Gap__Sg__igAnimationTransitionDefinitionList__vfunc_24(void) {
    return g_igAnimationTransitionDefinition_metaObject[0];
}

igMetaObject *Gap__Sg__igAnimationTransitionPointList__vfunc_24(void) {
    return g_igAnimationTransitionPoint_metaObject[0];
}

igMetaObject *Gap__Sg__igAnimationTrackList__vfunc_24(void) {
    return g_igAnimationTrack_metaObject[0];
}

igMetaObject *Gap__Sg__igAnimationBindingList__vfunc_24(void) {
    return g_igAnimationBinding_metaObject[0];
}

int Gap__Bec__igModelViewMatrixBoneSelectList__vfunc_22(void)
{
    return ((int *)g_igModelViewMatrixBoneSelect_metaObject)[0];
}

igMetaObject *Gap__Sg__igShaderFactoryList__vfunc_24(void) {
    return g_igShaderFactory_metaObject[0];
}

igMetaObject *Gap__Sg__igSkeletonList__vfunc_24(void) {
    return g_igSkeleton_metaObject[0];
}

igMetaObject *Gap__Sg__igSkeletonBoneInfoList__vfunc_24(void) {
    return g_igSkeletonBoneInfo_metaObject[0];
}

igMetaObject *Gap__Sg__igAnimationModifierList__vfunc_24(void) {
    return g_igAnimationModifier_metaObject[0];
}

igMetaObject *Gap__Sg__igSkinList__vfunc_24(void) {
    return g_igSkin_metaObject[0];
}

int Gap__Sg__igCompiledTransformList__vfunc_24(void) {
    return ((int *)g_igCompiledTransform_metaObject)[0];
}

igMetaObject *Gap__Sg__igGeometryList__vfunc_24(void) {
    return g_igGeometry_metaObject[0];
}

igMetaObject *Gap__Sg__igAttrStackList__vfunc_24(void) {
    return g_igAttrStack_metaObject[0];
}

igMetaObject *Gap__Sg__igTransformList__vfunc_24(void) {
    return g_igTransform_metaObject[0];
}

igMetaObject *Gap__Sg__igNodeListList__vfunc_24(void) {
    return g_igNodeList_metaObject[0];
}

igMetaObject *Gap__Sg__igNodeList__vfunc_24(void) {
    return g_igNode_metaObject[0];
}

void Gap__Core__igUnsignedIntList__vfunc_18(void *arg0) {
    int temp_a1;

    temp_a1 = *(int *)((char *)arg0 + 8);
    if (temp_a1 < *(int *)((char *)arg0 + 12)) {
        List_Reserve(arg0, temp_a1, 4);
    }
}

void Gap__Core__igDoubleList__vfunc_18(igDataList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        List_Reserve(arg0, temp_a1, 8);
    }
}

void Gap__Sg__igTraversalFunctionList__vfunc_18(void *arg0) {
    int temp_a1;

    temp_a1 = *(int *)((char *)arg0 + 8);
    if (temp_a1 < *(int *)((char *)arg0 + 12)) {
        List_Reserve(arg0, temp_a1, 4);
    }
}

/* Deleting destructor; the deletion flag is a signed short. */
ObjectRefWord *FUN_001e3d70(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy(object);
        }
        if((short)delete_storage>0) FUN_00100610(self);
    }
    return self;
}

struct R **FUN_001e3df0(struct R **arg0, short arg1) {
    struct R *temp_a0;

    if (arg0 != 0) {
        temp_a0 = *arg0;
        if (temp_a0 != 0) {
            temp_a0->rc = temp_a0->rc - 1;
            if ((temp_a0->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

/* Deleting destructor; the deletion flag is a signed short. */
ObjectRefWord *FUN_001e3e70(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy(object);
        }
        if((short)delete_storage>0) FUN_00100610(self);
    }
    return self;
}

void **FUN_001e3ef0(void **arg0, int arg1) {
    int *o;

    if (arg0 != 0) {
        o = (int *)(*arg0);
        if (o != 0) {
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if ((short)arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

void **FUN_001e3f70(void **arg0, short arg1) {
    int *o;

    if (arg0 != 0) {
        o = (int *)*arg0;
        if (o != 0) {
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

