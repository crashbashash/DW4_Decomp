namespace Gap {
namespace Sg {

void igTransformSequence1_5::removeKeyFrame(int index) {
    List_RemoveAt((::igDataList *)((TransformSequenceChannelView *)this)->_timeListLong, index, 8);
    if (_drivenChannels & 1) { List_RemoveAt((::igDataList *)((TransformSequenceChannelView *)this)->_xlateList, index, 12); }
    if ((_drivenChannels & 2) || (_drivenChannels & 4)) { List_RemoveAt((::igDataList *)((TransformSequenceChannelView *)this)->_quatList, index, 16); }
    if (_drivenChannels & 8) { List_RemoveAt((::igDataList *)((TransformSequenceChannelView *)this)->_scaleList, index, 12); }
}

void igTransformSequence1_5::setKeyFrameCount(int n) {
    _timeListLong->setCount(n);
    if (_drivenChannels & 1) {
        Core::igTDataList<igVec3f> *list = (Core::igTDataList<igVec3f> *)_xlateList.p;
        list->setCount(n);
    }
    if ((_drivenChannels & 2) || (_drivenChannels & 4)) {
        Core::igTDataList<igVec4f> *list = (Core::igTDataList<igVec4f> *)_quatList.p;
        list->setCount(n);
    }
    if (_drivenChannels & 8) {
        Core::igTDataList<igVec3f> *list = (Core::igTDataList<igVec3f> *)_scaleList.p;
        list->setCount(n);
    }
}

void igTransformSequence1_5::setTimeAsLong(int arg1, long long arg2) {
    _timeListLong->set(arg1, arg2);
}

/* IgTransformSequence1_5 vfunc_40: overwrite one keyframe of the translation list (_xlateList,
 * 12-byte x/y/z entries) with the vector at `translation`. Does nothing unless bit 0 of
 * _drivenChannels is set and `index` is inside the list. Sibling accessors with the same shape:
 * vfunc_44 (quaternion list, bit 1) and vfunc_49 (scale list, bit 3). */

void igTransformSequence1_5::setTranslation(int index, const igVec3f *xlate) {
    if (_drivenChannels & 1) {
        Core::igTDataList<igVec3f> *list = (Core::igTDataList<igVec3f> *)_xlateList.p;
        list->set(index, *xlate);
    }
}

/* Overwrites rotation key `index` (a 16-byte quaternion of _quatList) with the four floats at
 * `quaternion`. Ignored unless channel bit 2 of _drivenChannels is set and the index is inside the
 * list (the sibling accessors setTranslation and setScale gate their lists the same way). */

void igTransformSequence1_5::setQuaternion(int index, const igVec4f *q) {
    if (_drivenChannels & 2) {
        Core::igTDataList<igVec4f> *list = (Core::igTDataList<igVec4f> *)_quatList.p;
        list->set(index, *q);
    }
}

void igTransformSequence1_5::setEulerRotation(int arg1, const igVec3f *euler) {
    void *arg2 = (void *)euler;
    void *temp_v1;
    if (_drivenChannels & 4) {
        float z = *(float *)((char *)(arg2) + 8);
        float y = *(float *)((char *)(arg2) + 4);
        float x = *(float *)((char *)(arg2) + 0);
        temp_v1 = (void *)((char *)_quatList->_data + (arg1 * 0x10));
        *(float *)((char *)(temp_v1) + 0) = x;
        *(float *)((char *)(temp_v1) + 4) = y;
        *(float *)((char *)(temp_v1) + 8) = z;
        *(int *)((char *)(temp_v1) + 12) = 0;
    }
}
}
}

namespace Gap {
namespace Sg {

/* Stores one scale key: when the sequence drives the scale channel it copies the three floats at
 * `scale` into key `index` of _scaleList; a missing channel or an out-of-range index is ignored. */
void igTransformSequence1_5::setScale(int index, const igVec3f *scale) {
    if (_drivenChannels & 8) {
        Core::igTDataList<igVec3f> *list = (Core::igTDataList<igVec3f> *)_scaleList.p;
        list->set(index, *scale);
    }
}
}
}
#undef TRANSFORM_CHANNEL_SCALE

namespace Gap {
namespace Sg {

long long igTransformSequence1_5::getKeyFrameTimeOffset() const {
    return _keyframeTimeOffset;
}

void igTransformSequence1_5::setDuration(long long arg1) {
    _animationDuration = arg1;
}

/* Caches the sequence length: the span from the first to the last key time, computed once while the
 * duration is still unset (-1). The first key time is read through self->_timeListLong again rather than
 * through {times} (matching construct: the second read makes the data pointer take its register before
 * the scaled index). */
void igTransformSequence1_5::userPostLoad() {
    if (_animationDuration == -1) {
        igTDataList<long long> *times = (igTDataList<long long> *)_timeListLong.p;
        int count = times->count();
        int last = count - 1;
        if (count != 0) {
            _animationDuration = times->get(last) - ((igTDataList<long long> *)_timeListLong.p)->get(0);
        } else {
            _animationDuration = 0;
        }
    }
}

/* Converts a pre-1.5 sequence: the double key times (seconds) become nanosecond longs, and the start time becomes
 * the key-frame offset. The append is written out (matching construct: the count read through a `const` view is a
 * load of its own, so `_count++` reads the count again as retail does, and `count` is numbered below the list). */
void igTransformSequence1_5::userMakeConcrete(igMetaObject *sourceObjectType) {
    if (igTransformSequence::_Meta == sourceObjectType) {
        if (_timeList) {
            for (int i = 0; i < _timeList->_count; i++) {
                long long time = (long long)(_timeList->get(i) * 1000000000LL);
                igLongList *list = _timeListLong;
                int count = ((const igLongList *)list)->_count;
                if (count < list->_capacity) {
                    list->_count++;
                } else {
                    list->resizeAndSetCount(count + 1, sizeof(long long));
                }
                ((long long *)list->_data)[count] = time;
            }
            _timeList->_count = 0;
        }
        if (_startTime >= 0) {
            setKeyFrameTimeOffset((long long)(_startTime * 1000000000LL));
        }
    }
    _interpolationMethod[0] = 1;
    _interpolationMethod[1] = 3;
    _interpolationMethod[2] = 1;
}
}
}

/* Setter for the reflected bool field _uniformTimeEnabled. */

namespace Gap {
namespace Sg {

void igTransformSequence::setUniformTimeState(bool enabled) {
    _uniformTimeEnabled = enabled;
}

void igTransformSequence::reset() {
    _lastTime = 1;
}

bool igTransformSequence::evaluateRotation(float *quaternion, long long time, int *cachedLastTimeFrame, int flags) {
    float matrix[16];
    bool result = ((igTransformSource *)this)->getMatrix(*(igMatrix44f *)matrix, time, cachedLastTimeFrame, flags);
    igMatrix44f_GetQuaternion(quaternion, matrix);
    return result;
}


void igTransform::setMatrix(const igMatrix44f *matrix)
{
    igMatrix44f_Copy(_m.m, matrix->m);
}
}
}

/* Slot 36, shared by igTransform descendants: store the igTransform::_target field (+96). */

namespace Gap {
namespace Sg {

void igPlanarShadowShader::reset()
{
    _mats->removeAll();
    _geoms->removeAll();
    _blendmats->removeAll();
    _savedBounds = 0;
    _unused = 0;
}
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

int FUN_001e35f0(igAnimationBindingList *self) {
    return self->_capacity != 0;
}

int igBitMask_GetMeta(void) {
    return ((int)g_igBitMask_metaObject);
}

int igUnsignedIntList_GetMeta(void) {
    return (int)Gap::Core::igUnsignedIntList::getClassMeta();
}

igMetaObject *igBlendMatrixSelect_GetMeta(void) {
    return g_igBlendMatrixSelect_metaObject;
}

int igBoundingBoxesMaker_GetMeta(void) {
    return ((int)g_igBoundingBoxesMaker_metaObject);
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

int igModelViewMatrixBoneSelect_GetMeta(void) {
    return ((int)g_igModelViewMatrixBoneSelect_metaObject);
}

igMetaObject *igModelViewMatrixBoneSelectListSg_GetPublishedMetaObject(void) {
    return g_igModelViewMatrixBoneSelectListSg_metaObject;
}

int igDoubleList_GetMeta(void) {
    return (int)Gap::Core::igDoubleList::getClassMeta();
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

int Gap__Bec__igModelViewMatrixBoneSelectList__vfunc_22(void)
{
    return ((int)g_igModelViewMatrixBoneSelect_metaObject);
}

int igCompiledTransformList_GetElementMeta(void) {
    return ((int)g_igCompiledTransform_metaObject);
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
