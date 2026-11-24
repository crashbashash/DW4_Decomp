#include "dw4/maths/igVec3f.h"

namespace Gap {
namespace Sg {

const igVec3f *igCompressedAnimationSequenceQS::getTranslation(int index) const
{
    static igVec3f translation;
    const unsigned short *p = _compressedTranslationList->getArray() + index * 3;
    float *out = translation.vec;
    *out++ = _translationBase + (float)(unsigned int)*p++ * _translationRangeOverMaxUShort;
    *out++ = _translationBase + (float)(unsigned int)*p++ * _translationRangeOverMaxUShort;
    *out++ = _translationBase + (float)(unsigned int)*p++ * _translationRangeOverMaxUShort;
    return &translation;
}
}
}

void FUN_001bf560(QSView *o, int index, float *out) {
    unsigned short *p = o->_compressedQuaternionList->_data + index * 4;
    *out++ = o->_quaternionBase + (float)(unsigned int)*p++ * o->_quaternionRangeOverMaxUShort;
    *out++ = o->_quaternionBase + (float)(unsigned int)*p++ * o->_quaternionRangeOverMaxUShort;
    *out++ = o->_quaternionBase + (float)(unsigned int)*p++ * o->_quaternionRangeOverMaxUShort;
    *out++ = o->_quaternionBase + (float)(unsigned int)*p++ * o->_quaternionRangeOverMaxUShort;
}

namespace Gap {
namespace Sg {

void igCompressedAnimationSequenceQS::getTranslation(int index, igVec3f &vec) const
{
    float *out = vec.vec;
    const unsigned short *p = _compressedTranslationList->getArray() + index * 3;
    *out++ = _translationBase + (float)(unsigned int)*p++ * _translationRangeOverMaxUShort;
    *out++ = _translationBase + (float)(unsigned int)*p++ * _translationRangeOverMaxUShort;
    *out++ = _translationBase + (float)(unsigned int)*p++ * _translationRangeOverMaxUShort;
}

/* Decodes a 16-bit sign-magnitude sample (bit 15 = sign, 15-bit magnitude) into a 64-bit fixed-
 * point value (magnitude << 23). One 64-bit variable is widened, masked, shifted and negated in
 * place. */
long long igCompressedAnimationSequenceQS::getTimeAsLong(int index) const
{
    const unsigned short *d = _compressedTimeList->getArray();
    long long v = d[index];
    if (v & 0x8000) { v &= 0x7FFF; v <<= 0x17; v = -v; } else v <<= 0x17;
    return v;
}
}
}

void FUN_001bf7d0(QSSequenceView *o, unsigned char *before, unsigned char *after, int *key0, int *key1, float *t0, float *t1, long long time) {
    long long rem;
    long long end;
    long long first;
    long long last;
    *before = 0;
    *after = 0;
    first = o->keyTime(0);
    last = o->keyTime(o->_compressedTimeList->_count - 1);
    end = first + (long long)o->_animationDuration;
    if (end < time) {
        switch (o->_playMode) {
        case 1: *after = 1; return;
        case 3: case 0: UnsignedDivMod64_Cached(time - first, o->_animationDuration, &rem); time = first + rem; if (o->_lastTime != 1 && time < o->keyTime(o->_lastTime - 1)) { o->_lastTime = 1; } break;
        case 2: { unsigned long long cycle = (unsigned long long)(unsigned int)UnsignedDivMod64_Cached(time - first, o->_animationDuration, &rem); if ((int)cycle & 1) { time = end - rem; } else { time = first + rem; } } break;
        default: *before = 1; return;
        }
    } else if (time < first) {
        *before = 1;
        return;
    }
    if (last < time) {
        if (o->_playMode == 3) {
            int d;
            d = (int)((time - last) >> 18);
            *key0 = o->_compressedTimeList->_count - 1;
            *key1 = 0;
            *t0 = (float)(unsigned int)d;
            d = (int)((end - last) >> 18);
            *t1 = (float)(unsigned int)d;
            return;
        }
        *after = 1;
        return;
    }
    FUN_001bfc70((O_1bfc70 *)o, time, key0, key1, t0, t1);
}

namespace Gap {
namespace Sg {

bool igCompressedAnimationSequenceQS::getMatrix(igMatrix44f &matrix, long long time)
{
    unsigned char s6f; unsigned char s6e; int s68; int s64; float s60; float s5c; int s50[3]; int s40[4];
    float f;
    FUN_001bf7d0((QSSequenceView *)this, &s6f, &s6e, &s68, &s64, &s60, &s5c, time);
    igMatrix44f_SetIdentity((float *)&matrix);
    if (s6f) {
        if (_channels & 2) { FUN_001bf560((QSView *)this, 0, (float *)s40); FUN_00192810((const float *)s40, (float *)&matrix); }
        if (_channels & 1) { getTranslation(0, *(igVec3f *)s50); igMatrix44f_SetTranslation((float *)&matrix, (float *)s50); }
    } else if (s6e) {
        if (_channels & 2) { FUN_001bf560((QSView *)this, ((QSSequenceView *)this)->_compressedTimeList->_count - 1, (float *)s40); FUN_00192810((const float *)s40, (float *)&matrix); }
        if (_channels & 1) { getTranslation(getTimeCount() - 1, *(igVec3f *)s50); igMatrix44f_SetTranslation((float *)&matrix, (float *)s50); }
    } else {
        if (s5c < 9.99999997e-07f) f = 0.0f; else f = s60 / s5c;
        if (_channels & 2) { constructInterpolatedQuaternion(*(igVec4f *)s40, s68, s64, f); FUN_00192810((const float *)s40, (float *)&matrix); }
        if (_channels & 1) { constructInterpolatedTranslation(*(igVec3f *)s50, s68, s64, f); igMatrix44f_SetTranslation((float *)&matrix, (float *)s50); }
    }
    return 1;
}

/* IgCompressedAnimationSequenceQS virtual getter 35. Returns the element count of the
 * `_compressedTimeList` (reflected object ref, +16): the word at +8 of an igDataList-style list is
 * `_count`. The list is read through the generic igDataList layout. */

int igCompressedAnimationSequenceQS::getTimeCount() const
{
    return ((QSSequenceView *)this)->_compressedTimeList->_count;
}
}
}

void FUN_001bfc70(O_1bfc70 *o, long long t, int *a2, int *a3, float *a4, float *a5) {
    int i = o->cur;
    if (o->v40(i) < t) {
        do { i++; } while (o->v40(i) < t && i < o->m->count);
    } else if (t < o->v40(i - 1)) {
        do { i--; } while (t < o->v40(i - 1) && i > 0);
    }
    int c = o->m->count;
    if (i >= c) i = c - 1; else if (i <= 0) i = 1;
    o->cur = i;
    *a3 = i;
    *a2 = i - 1;
    if (*a2 < 0) *a2 = 0;
    *a4 = (float)(unsigned int)(int)((t - o->v40(*a2)) >> 18);
    long long s = o->v40(*a2);
    *a5 = (float)(unsigned int)(int)((o->v40(*a3) - s) >> 18);
}

namespace Gap {
namespace Sg {

void igCompressedAnimationSequenceQS::constructInterpolatedQuaternion(igVec4f &interpolatedQuaternion, int lowerBound, int upperBound, float ratio) const
{
    int slerpFrom[4]; int slerpTo[4]; int lerpFrom[4]; int lerpTo[4];
    unsigned char t;
    t = _interpolationMethod[1];
    if (t == 0) {
        FUN_001bf560((QSView *)this, lowerBound, (float *)&interpolatedQuaternion);
        return;
    }
    if (t == 3) {
        FUN_001bf560((QSView *)this, lowerBound, (float *)slerpFrom);
        FUN_001bf560((QSView *)this, upperBound, (float *)slerpTo);
        FUN_00192ab0((float *)&interpolatedQuaternion, ratio, (void *)slerpFrom, (void *)slerpTo);
        return;
    }
    FUN_001bf560((QSView *)this, lowerBound, (float *)lerpFrom);
    FUN_001bf560((QSView *)this, upperBound, (float *)lerpTo);
    Quaternion_Lerp((float *)&interpolatedQuaternion, ratio, (const float *)lerpFrom, (const float *)lerpTo);
}

void igCompressedAnimationSequenceQS::constructInterpolatedTranslation(igVec3f &translation, int lowerBound, int upperBound, float ratio) const
{
    int vecFrom[4];
    int vecTo[4];

    if (_interpolationMethod[0] == 0) {
        getTranslation(lowerBound, translation);
        return;
    }
    getTranslation(lowerBound, *(igVec3f *)&vecFrom[0]);
    getTranslation(upperBound, *(igVec3f *)&vecTo[0]);
    Vec3_Lerp(translation.vec, ratio, (const float *)((void *)&vecFrom[0]), (const float *)((void *)&vecTo[0]));
}

bool igCompressedAnimationSequenceQS::evaluateRotation(float *quaternion, long long time)
{
    unsigned char beforeStart;
    unsigned char afterEnd;
    int key0;
    int key1;
    float elapsed;
    float duration;

    FUN_001bf7d0((QSSequenceView *)this, &beforeStart, &afterEnd, &key0, &key1, &elapsed, &duration, time);
    if (beforeStart != 0) {
        FUN_001bf560((QSView *)this, 0, quaternion);
    } else if (afterEnd != 0) {
        FUN_001bf560((QSView *)this, ((QSSequenceView *)this)->_compressedTimeList->_count - 1, quaternion);
    } else {
        constructInterpolatedQuaternion(*(igVec4f *)quaternion, key0, key1, elapsed / duration);
    }
    return 1;
}

bool igCompressedAnimationSequenceQS::evaluateRotationAndTranslation(float *quaternion, float *translation, long long time)
{
    unsigned char beforeStart; unsigned char afterEnd; int key0; int key1; float elapsed; float duration; float f20;
    FUN_001bf7d0((QSSequenceView *)this, &beforeStart, &afterEnd, &key0, &key1, &elapsed, &duration, time);
    if (beforeStart != 0) {
        FUN_001bf560((QSView *)this, 0, quaternion);
        getTranslation(0, *(igVec3f *)translation);
    } else if (afterEnd != 0) {
        FUN_001bf560((QSView *)this, ((QSSequenceView *)this)->_compressedTimeList->_count - 1, quaternion);
        getTranslation(getTimeCount() - 1, *(igVec3f *)translation);
    } else {
        if (duration < 9.99999997e-07f) {
            f20 = 0.0f;
        } else {
            f20 = elapsed / duration;
        }
        constructInterpolatedQuaternion(*(igVec4f *)quaternion, key0, key1, f20);
        constructInterpolatedTranslation(*(igVec3f *)translation, key0, key1, f20);
    }
    return 1;
}
}
}

/* Getter: the scale keyframe list (`_scaleList`). */

namespace Gap {
namespace Sg {

igVec3fList *igTransformSequence::getScaleList() {
    return _scaleList;
}
}
}

class ProjectionMatrixAttrView {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29();
    virtual void setMatrix(igMatrix44fView *);
};
static inline float aspectOf(const DepthOfFieldNode &dof) { return dof._fovX / dof._fovY; }
static inline float degToRad(const float degrees) { return 0.0174532924f * degrees; }
/* The far edge of the in-focus region: the focus distance pushed out by _blurPercent of its distance from the near
 * plane. */
static inline float nearRegionFar(const DepthOfFieldNode &dof) { return dof._focusDistance + dof._blurPercent * (0.01f * (dof._focusDistance - dof._nearPlane)); }
extern "C" void DepthOfField_UpdateProjections(DepthOfFieldNode *dof);

void *g_depthOfFieldNearProjectionAttr;

void *g_depthOfFieldFarProjectionAttr;

/* Completes the field of view from the aspect ratio and rebuilds the near-pass and far-pass projections. */
void DepthOfField_UpdateProjections(DepthOfFieldNode *dof) {
    if (dof->_fovX == -1.0f) {
        dof->_fovX = dof->_fovY * dof->_aspect;
    } else if (dof->_fovY == -1.0f) {
        dof->_fovY = dof->_fovX / dof->_aspect;
    }
    igMatrix44fView nearProjection;
    igMatrix44f_MakePerspective((float *)&nearProjection, degToRad(dof->_fovX), degToRad(dof->_fovY), aspectOf(*dof),
                 dof->_nearPlane, nearRegionFar(*dof));
    ((ProjectionMatrixAttrView *)g_depthOfFieldNearProjectionAttr)->setMatrix(&nearProjection);
    igMatrix44fView farProjection;
    igMatrix44f_MakePerspective((float *)&farProjection, degToRad(dof->_fovX), degToRad(dof->_fovY), aspectOf(*dof),
                 dof->_focusDistance, dof->_farPlane);
    ((ProjectionMatrixAttrView *)g_depthOfFieldFarProjectionAttr)->setMatrix(&farProjection);
}

int FUN_001c0390(void *, int) {
    return 0;
}

void FUN_001c03a0(DepthOfFieldNode *arg0, A1_1c03a0 *arg1) {
    float color[4];
    float f20;
    Cls *s1;
    int s0;
    Obj_1c03a0 *s4;
    int v1;
    if (arg0->_childList != 0) v1 = arg0->_childList->_count; else v1 = 0;
    if (v1 != 0) {
        if (arg0->_enabled != 0 && !(arg0->_blurPercent <= 1.0f)) {
            s1 = arg1->f60;
            if (GPR_00554984 != 0) {
                if ((FUN_001c0390((void *)arg0, arg1->f32) & 0xFF) == 1) GPR_00554b8c = 1; else GPR_00554b8c = 0;
                GPR_00554984 = 0;
            }
            if (GPR_00554b8c != 0) {
                s0 = arg1->f52;
                if (arg0->_projectionDirty != 0) {
                    DepthOfField_UpdateProjections(arg0);
                    arg0->_projectionDirty = 0;
                }
                s1->v716(color);
                f20 = s1->v728();
                s4 = DAT_00562660[0];
                s4->a[0] = color[0];
                s4->a[1] = color[1];
                s4->a[2] = color[2];
                s4->a[3] = color[3];
                s4->f60 = igVec4f_PackColor(color, 1);
                s4 = DAT_00562660[0];
                s4->f48 = fptodp(f20);
                s4->f64 = f20;
                FUN_001dc500((A_1dc500 *)arg1->f68, 0, 0);
                ((Gap::Sg::igAttrStackManager *)s0)->pushOverride((Gap::Attrs::igAttr *)DAT_00562668[0]);
                ((Gap::Sg::igAttrStackManager *)s0)->pushOverride((Gap::Attrs::igAttr *)DAT_00562670[0]);
                FUN_001d9bb0((void *)arg1->f68, s0);
                ((Gap::Sg::igAttrStackManager *)s0)->pushOverride((Gap::Attrs::igAttr *)DAT_00562660[0]);
                ((Gap::Sg::igAttrStackManager *)s0)->pushOverride((Gap::Attrs::igAttr *)g_depthOfFieldFarProjectionAttr);
                igTraversal_TraverseChildren((igTraversal *)(arg1), (igNode *)arg0);
                ((Gap::Sg::igAttrStackManager *)s0)->popOverride((Gap::Attrs::igAttr *)g_depthOfFieldFarProjectionAttr);
                ((Gap::Sg::igAttrStackManager *)s0)->popOverride((Gap::Attrs::igAttr *)DAT_00562660[0]);
                ((Gap::Sg::igAttrStackManager *)s0)->popOverride((Gap::Attrs::igAttr *)DAT_00562670[0]);
                ((Gap::Sg::igAttrStackManager *)s0)->popOverride((Gap::Attrs::igAttr *)DAT_00562668[0]);
                FUN_001d9bb0((void *)arg1->f68, s0);
                ((Gap::Sg::igAttrStackManager *)s0)->pushOverride((Gap::Attrs::igAttr *)DAT_005626c8[0]);
                ((Gap::Sg::igAttrStackManager *)s0)->pushOverride((Gap::Attrs::igAttr *)DAT_005626a8[0]);
                ((Gap::Sg::igAttrStackManager *)s0)->pushOverride((Gap::Attrs::igAttr *)DAT_005626d0[0]);
                FUN_001d9bb0((void *)arg1->f68, s0);
                ((Gap::Sg::igAttrStackManager *)s0)->pushOverride((Gap::Attrs::igAttr *)DAT_00562680[0]);
                ((Gap::Sg::igAttrStackManager *)s0)->pushOverride((Gap::Attrs::igAttr *)DAT_00562688[0]);
                if (s1->v148(16) != 0) {
                    ((Gap::Sg::igAttrStackManager *)s0)->pushOverride((Gap::Attrs::igAttr *)DAT_005626a0[0]);
                } else {
                    ((Gap::Sg::igAttrStackManager *)s0)->pushOverride((Gap::Attrs::igAttr *)DAT_00562698[0]);
                }
                ((Gap::Sg::igAttrStackManager *)s0)->pushOverride((Gap::Attrs::igAttr *)DAT_00562690[0]);
                ((Gap::Sg::igAttrStackManager *)s0)->pushOverride((Gap::Attrs::igAttr *)DAT_005626c0[0]);
                ((Gap::Sg::igAttrStackManager *)s0)->pushOverride((Gap::Attrs::igAttr *)DAT_005626d8[0]);
                FUN_001db720((igSorter *)arg1->f68, (igGeometry *)DAT_00562678[0], (igAttrStackManager *)s0);
                ((Gap::Sg::igAttrStackManager *)s0)->popOverride((Gap::Attrs::igAttr *)DAT_005626d8[0]);
                ((Gap::Sg::igAttrStackManager *)s0)->popOverride((Gap::Attrs::igAttr *)DAT_005626c0[0]);
                ((Gap::Sg::igAttrStackManager *)s0)->popOverride((Gap::Attrs::igAttr *)DAT_00562690[0]);
                if (s1->v148(16) != 0) {
                    ((Gap::Sg::igAttrStackManager *)s0)->popOverride((Gap::Attrs::igAttr *)DAT_005626a0[0]);
                } else {
                    ((Gap::Sg::igAttrStackManager *)s0)->popOverride((Gap::Attrs::igAttr *)DAT_00562698[0]);
                }
                ((Gap::Sg::igAttrStackManager *)s0)->popOverride((Gap::Attrs::igAttr *)DAT_00562688[0]);
                ((Gap::Sg::igAttrStackManager *)s0)->popOverride((Gap::Attrs::igAttr *)DAT_00562680[0]);
                ((Gap::Sg::igAttrStackManager *)s0)->popOverride((Gap::Attrs::igAttr *)DAT_005626d0[0]);
                ((Gap::Sg::igAttrStackManager *)s0)->popOverride((Gap::Attrs::igAttr *)DAT_005626a8[0]);
                ((Gap::Sg::igAttrStackManager *)s0)->popOverride((Gap::Attrs::igAttr *)DAT_005626c8[0]);
                FUN_001d9bb0((void *)arg1->f68, s0);
                ((Gap::Sg::igAttrStackManager *)s0)->pushOverride((Gap::Attrs::igAttr *)g_depthOfFieldNearProjectionAttr);
                igTraversal_TraverseChildren((igTraversal *)(arg1), (igNode *)arg0);
                ((Gap::Sg::igAttrStackManager *)s0)->popOverride((Gap::Attrs::igAttr *)g_depthOfFieldNearProjectionAttr);
                FUN_001d9bb0((void *)arg1->f68, s0);
                FUN_001dc610((igSorter *)arg1->f68);
                return;
            }
        }
        FUN_001dc500((A_1dc500 *)arg1->f68, 0, 0);
        igTraversal_TraverseChildren((igTraversal *)(arg1), (igNode *)arg0);
        FUN_001dc610((igSorter *)arg1->f68);
    }
}

