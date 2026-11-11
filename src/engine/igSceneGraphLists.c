#include "dw4/reflected.h"

int List_Reserve();
void igObject_Destroy(void *);
void FUN_00100610(void *);

typedef struct ObjectRefTarget { int word0; int references; } ObjectRefTarget;
typedef struct ObjectRefWord { ObjectRefTarget *value; } ObjectRefWord;
struct R { int vt; unsigned int rc; };
struct L { char pad[8]; int cnt; int pad2; int *items; };

/* Each metaobject handle is read through an array extern so the load stays absolute. */
extern int g_igActorList_metaObject[4];
extern int DAT_00562450[4];
extern int DAT_00562430[4];
extern int DAT_00562428[4];
extern int DAT_00562400[4];
extern int DAT_005623e8[4];
extern int DAT_005623e0[4];
extern int DAT_005623c0[4];
extern int DAT_005623b8[4];
extern int DAT_00562368[4];
extern int DAT_00562338[4];
extern int DAT_00562330[4];
extern int g_igAnimationSystem_metaObject[4];
extern int g_igAnimationCombinerList_metaObject[4];
extern int DAT_00562268[4];
extern int DAT_00562260[4];
extern int DAT_00562258[4];
extern int DAT_00562250[4];
extern int DAT_005612e8[4];
extern int DAT_00562200[4];
extern int DAT_005621f0[4];
extern int DAT_005620e0[4];
extern int DAT_005620d8[4];
extern int DAT_00562098[4];
extern int DAT_00562090[4];
extern int DAT_00562030[4];
extern int DAT_00562028[4];
extern int DAT_00561f90[4];
extern int DAT_00561f68[4];
extern int g_igBitMask_metaObject[4];
extern int DAT_00586858[4];
extern int DAT_00561f38[4];
extern int g_igBoundingBoxesMaker_metaObject[4];
extern int DAT_00561ea0[4];
extern int g_igCompiledTransform_metaObject[4];
extern int DAT_00561d28[4];
extern int DAT_00561ca8[4];
extern int DAT_00561be0[4];
extern int DAT_00561a90[4];
extern int DAT_00561a30[4];
extern int DAT_00561a10[4];
extern int DAT_00561a08[4];
extern int DAT_00561990[4];
extern int DAT_00561970[4];
extern int DAT_00562370[4];
extern int DAT_00561880[4];
extern int DAT_00561830[4];
extern int DAT_00561828[4];
extern int DAT_00561820[4];
extern int DAT_00561818[4];
extern int g_igSegment_metaObject[4];
extern int g_igTraversalFunctionList_metaObject[4];
extern int DAT_005615c0[4];
extern int DAT_005615b8[4];
extern int DAT_005615b0[4];
extern int DAT_005615a8[4];
extern int DAT_005615a0[4];
extern int DAT_00561598[4];
extern int DAT_00561590[4];
extern int DAT_00561588[4];
extern int DAT_00561580[4];
extern int DAT_00561518[4];
extern int DAT_005614d8[4];
extern int DAT_005614d0[4];
extern int DAT_005614a8[4];
extern int DAT_00561490[4];
extern int DAT_00561488[4];
extern int DAT_00561450[4];
extern int DAT_00561448[4];
extern int DAT_00561440[4];
extern int DAT_005867f0[4];
extern int DAT_005612a8[4];
extern int DAT_005612a0[4];
extern int DAT_00561298[4];
extern int DAT_00561280[4];
extern int g_igTransientShaderData_metaObject[4];
extern int DAT_00561f98[4];
extern int DAT_005612b0[4];
extern int DAT_00561838[4];
extern int g_igActor_metaObject[4];
extern int g_igAnimationCombiner_metaObject[4];
extern int DAT_00562100[4];
extern int DAT_00561a98[4];
extern int g_igModelViewMatrixBoneSelect_metaObject[4];
extern int DAT_00561528[4];
extern int DAT_005614b0[4];
extern int DAT_00561a38[4];

int Gap__Sg__igActor__vfunc_22(void) {
    return g_igActor_metaObject[0];
}

int Gap__Sg__igActor__vfunc_26(void) {
    return 0;
}

int Gap__Sg__igActorList__vfunc_22(void) {
    return g_igActorList_metaObject[0];
}

int Gap__Sg__igActorInfo__vfunc_22(void) {
    return DAT_00562450[0];
}

int Gap__Sg__igAnimationTrack__vfunc_22(void) {
    return DAT_00562430[0];
}

int Gap__Sg__igAnimationTrackList__vfunc_22(void) {
    return DAT_00562428[0];
}

int Gap__Sg__igAnimationTransitionParams__vfunc_22(void) {
    return DAT_00562400[0];
}

int Gap__Sg__igAnimationTransitionPoint__vfunc_22(void) {
    return DAT_005623e8[0];
}

int Gap__Sg__igAnimationTransitionPointList__vfunc_22(void) {
    return DAT_005623e0[0];
}

int Gap__Sg__igAnimationTransitionDefinition__vfunc_22(void) {
    return DAT_005623c0[0];
}

int Gap__Sg__igAnimationTransitionDefinitionList__vfunc_22(void) {
    return DAT_005623b8[0];
}

int Gap__Sg__igAnimationList__vfunc_22(void) {
    return DAT_00562368[0];
}

int Gap__Sg__igAnimationBinding__vfunc_22(void) {
    return DAT_00562338[0];
}

int Gap__Sg__igAnimationBindingList__vfunc_22(void) {
    return DAT_00562330[0];
}

/* Returns the metaobject slot of igAnimationSystem, not of the binding list. */
int FUN_001e35e0(void) {
    return g_igAnimationSystem_metaObject[0];
}

int FUN_001e35f0(igAnimationBindingList *self) {
    return self->_capacity != 0;
}

int Gap__Sg__igAnimationCombinerList__vfunc_22(void) {
    return g_igAnimationCombinerList_metaObject[0];
}

int Gap__Sg__igAnimationCombinerBoneInfo__vfunc_22(void) {
    return DAT_00562268[0];
}

int Gap__Sg__igAnimationCombinerBoneInfoList__vfunc_22(void) {
    return DAT_00562260[0];
}

int Gap__Sg__igAnimationCombinerBoneInfoListList__vfunc_22(void) {
    return DAT_00562258[0];
}

int Gap__Sg__igAnimationCombinerBoneInfoPool__vfunc_22(void) {
    return DAT_00562250[0];
}

int Gap__Sg__igObjectPool__vfunc_22(void) {
    return DAT_005612e8[0];
}

int Gap__Sg__igAnimationModifier__vfunc_22(void) {
    return DAT_00562200[0];
}

int Gap__Sg__igAnimationModifierList__vfunc_22(void) {
    return DAT_005621f0[0];
}

int Gap__Sg__igAnimationStateList__vfunc_22(void) {
    return DAT_005620e0[0];
}

int Gap__Sg__igAnimationStatePool__vfunc_22(void) {
    return DAT_005620d8[0];
}

int Gap__Sg__igAppearance__vfunc_22(void) {
    return DAT_00562098[0];
}

int Gap__Sg__igAppearanceList__vfunc_22(void) {
    return DAT_00562090[0];
}

int Gap__Sg__igAttrStack__vfunc_22(void) {
    return DAT_00562030[0];
}

int Gap__Sg__igAttrStackList__vfunc_22(void) {
    return DAT_00562028[0];
}

int Gap__Sg__igNonRefCountedAttrStackManagerList__vfunc_22(void) {
    return DAT_00561f90[0];
}

int Gap__Sg__igBillboard__vfunc_22(void) {
    return DAT_00561f68[0];
}

int Gap__Sg__igBillboard__vfunc_26(void) {
    return 0;
}

int Gap__Sg__igBitMask__vfunc_22(void) {
    return g_igBitMask_metaObject[0];
}

int Gap__Core__igUnsignedIntList__vfunc_22(void) {
    return DAT_00586858[0];
}

int Gap__Sg__igBlendMatrixSelect__vfunc_22(void) {
    return DAT_00561f38[0];
}

int Gap__Sg__igBoundingBoxesMaker__vfunc_22(void) {
    return g_igBoundingBoxesMaker_metaObject[0];
}

int Gap__Sg__igCamera__vfunc_22(void) {
    return DAT_00561ea0[0];
}

void Gap__Sg__igCamera__vfunc_35(void) {

}

void Gap__Sg__igCamera__vfunc_36(void) {

}

int Gap__Sg__igCompiledTransform__vfunc_22(void) {
    return g_igCompiledTransform_metaObject[0];
}

int Gap__Sg__igCompiledTransformList__vfunc_22(void) {
    return DAT_00561d28[0];
}

int Gap__Sg__igBlendListRecord__vfunc_22(void) {
    return DAT_00561ca8[0];
}

int Gap__Sg__igCompressedTransformSequence1_5Data__vfunc_22(void) {
    return DAT_00561be0[0];
}

int Gap__Sg__igEnvironmentMapShader2List__vfunc_22(void) {
    return DAT_00561a90[0];
}

int Gap__Sg__igGeometryList__vfunc_22(void) {
    return DAT_00561a30[0];
}

int Gap__Sg__igGraphPath__vfunc_22(void) {
    return DAT_00561a10[0];
}

int Gap__Sg__igGraphPathList__vfunc_22(void) {
    return DAT_00561a08[0];
}

int Gap__Sg__igInterpretedShaderData__vfunc_22(void) {
    return DAT_00561990[0];
}

int Gap__Sg__igProbe__vfunc_22(void) {
    return DAT_00561970[0];
}

int Gap__Sg__igAnimation__vfunc_22(void) {
    return DAT_00562370[0];
}

int Gap__Sg__igModelViewMatrixBoneSelect__vfunc_22(void) {
    return g_igModelViewMatrixBoneSelect_metaObject[0];
}

int FUN_001e3840(void) {
    return DAT_00561880[0];
}

int Gap__Sg__igNodeList__vfunc_22(void) {
    return DAT_00561830[0];
}

int Gap__Sg__igNodeListList__vfunc_22(void) {
    return DAT_00561828[0];
}

int Gap__Sg__igNonRefCountedNodeList__vfunc_22(void) {
    return DAT_00561820[0];
}

int Gap__Sg__igOverrideAttrSet__vfunc_22(void) {
    return DAT_00561818[0];
}

int Gap__Sg__igSegment__vfunc_22(void) {
    return g_igSegment_metaObject[0];
}

int Gap__Sg__igSegment__vfunc_26(void) {
    return 0;
}

int Gap__Sg__igTraversalFunctionList__vfunc_22(void) {
    return g_igTraversalFunctionList_metaObject[0];
}

int Gap__Sg__igLightStateAttrPool__vfunc_22(void) {
    return DAT_005615c0[0];
}

int Gap__Sg__igModelViewMatrixAttrPool__vfunc_22(void) {
    return DAT_005615b8[0];
}

int Gap__Sg__igTimeAttrPool__vfunc_22(void) {
    return DAT_005615b0[0];
}

int Gap__Sg__igProjectionMatrixAttrPool__vfunc_22(void) {
    return DAT_005615a8[0];
}

int Gap__Sg__igVertexBlendMatrixAttrPool__vfunc_22(void) {
    return DAT_005615a0[0];
}

int Gap__Sg__igVertexBlendMatrixListAttrPool__vfunc_22(void) {
    return DAT_00561598[0];
}

int Gap__Sg__igMatrixObjectPool__vfunc_22(void) {
    return DAT_00561590[0];
}

int Gap__Sg__igTextureMatrixAttrPool__vfunc_22(void) {
    return DAT_00561588[0];
}

int Gap__Sg__igBlendMatricesAttrPool__vfunc_22(void) {
    return DAT_00561580[0];
}

int Gap__Sg__igShaderFactoryList__vfunc_22(void) {
    return DAT_00561518[0];
}

int Gap__Sg__igSkeletonBoneInfo__vfunc_22(void) {
    return DAT_005614d8[0];
}

int Gap__Sg__igSkeletonBoneInfoList__vfunc_22(void) {
    return DAT_005614d0[0];
}

int Gap__Sg__igSkeletonList__vfunc_22(void) {
    return DAT_005614a8[0];
}

int Gap__Sg__igSkin__vfunc_22(void) {
    return DAT_00561490[0];
}

int Gap__Sg__igSkinList__vfunc_22(void) {
    return DAT_00561488[0];
}

int Gap__Sg__igRenderPackage__vfunc_22(void) {
    return DAT_00561450[0];
}

int Gap__Sg__igRenderPackagePool__vfunc_22(void) {
    return DAT_00561448[0];
}

int Gap__Sg__igRenderPackageList__vfunc_22(void) {
    return DAT_00561440[0];
}

int Gap__Core__igDoubleList__vfunc_22(void) {
    return DAT_005867f0[0];
}

int Gap__Sg__igTransformStack__vfunc_22(void) {
    return DAT_005612a8[0];
}

int Gap__Sg__igTransformList__vfunc_22(void) {
    return DAT_005612a0[0];
}

int Gap__Sg__igNonRefCountedTransformList__vfunc_22(void) {
    return DAT_00561298[0];
}

int Gap__Sg__igTransformRecorder__vfunc_22(void) {
    return DAT_00561280[0];
}

int Gap__Sg__igTransientShaderData__vfunc_22(void) {
    return g_igTransientShaderData_metaObject[0];
}

int Gap__Sg__igRenderPackageList__vfunc_24(void) {
    return DAT_00561450[0];
}

int Gap__Sg__igNonRefCountedAttrStackManagerList__vfunc_24(void) {
    return DAT_00561f98[0];
}

int Gap__Sg__igNonRefCountedTransformList__vfunc_24(void) {
    return DAT_005612b0[0];
}

int Gap__Sg__igNonRefCountedNodeList__vfunc_24(void) {
    return DAT_00561838[0];
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

int FUN_001e3ab0(struct L *arg0, int *arg1) {
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
    return g_igActor_metaObject[0];
}

/* Returns the metaobject slot of the element class igAnimationCombiner, not of the list. */
int Gap__Sg__igAnimationCombinerList__vfunc_24(void) {
    return g_igAnimationCombiner_metaObject[0];
}

int Gap__Sg__igAppearanceList__vfunc_24(void) {
    return DAT_00562098[0];
}

int Gap__Sg__igAnimationStateList__vfunc_24(void) {
    return DAT_00562100[0];
}

int Gap__Sg__igAnimationCombinerBoneInfoListList__vfunc_24(void) {
    return DAT_00562260[0];
}

int Gap__Sg__igAnimationCombinerBoneInfoList__vfunc_24(void) {
    return DAT_00562268[0];
}

int Gap__Sg__igEnvironmentMapShader2List__vfunc_24(void) {
    return DAT_00561a98[0];
}

int Gap__Sg__igGraphPathList__vfunc_24(void) {
    return DAT_00561a10[0];
}

int Gap__Sg__igAnimationList__vfunc_24(void) {
    return DAT_00562370[0];
}

int Gap__Sg__igAnimationTransitionDefinitionList__vfunc_24(void) {
    return DAT_005623c0[0];
}

int Gap__Sg__igAnimationTransitionPointList__vfunc_24(void) {
    return DAT_005623e8[0];
}

int Gap__Sg__igAnimationTrackList__vfunc_24(void) {
    return DAT_00562430[0];
}

int Gap__Sg__igAnimationBindingList__vfunc_24(void) {
    return DAT_00562338[0];
}

int Gap__Bec__igModelViewMatrixBoneSelectList__vfunc_22(void)
{
    return g_igModelViewMatrixBoneSelect_metaObject[0];
}

int Gap__Sg__igShaderFactoryList__vfunc_24(void) {
    return DAT_00561528[0];
}

int Gap__Sg__igSkeletonList__vfunc_24(void) {
    return DAT_005614b0[0];
}

int Gap__Sg__igSkeletonBoneInfoList__vfunc_24(void) {
    return DAT_005614d8[0];
}

int Gap__Sg__igAnimationModifierList__vfunc_24(void) {
    return DAT_00562200[0];
}

int Gap__Sg__igSkinList__vfunc_24(void) {
    return DAT_00561490[0];
}

int Gap__Sg__igCompiledTransformList__vfunc_24(void) {
    return g_igCompiledTransform_metaObject[0];
}

int Gap__Sg__igGeometryList__vfunc_24(void) {
    return DAT_00561a38[0];
}

int Gap__Sg__igAttrStackList__vfunc_24(void) {
    return DAT_00562030[0];
}

int Gap__Sg__igTransformList__vfunc_24(void) {
    return DAT_005612b0[0];
}

int Gap__Sg__igNodeListList__vfunc_24(void) {
    return DAT_00561830[0];
}

int Gap__Sg__igNodeList__vfunc_24(void) {
    return DAT_00561838[0];
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
