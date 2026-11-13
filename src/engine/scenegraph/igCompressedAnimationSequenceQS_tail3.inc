#include "dw4/igVec3f.h"
extern "C" igVec3f *Gap__Sg__igCompressedAnimationSequenceQS__getTranslationKey(QSView *o, int index);

igVec3f *Gap__Sg__igCompressedAnimationSequenceQS__getTranslationKey(QSView *o, int index) {
    static igVec3f translation;
    unsigned short *p = o->_compressedTranslationList->_data + index * 3;
    float *out = &translation.x;
    *out++ = o->_translationBase + (float)(unsigned int)*p++ * o->_translationRangeOverMaxUShort;
    *out++ = o->_translationBase + (float)(unsigned int)*p++ * o->_translationRangeOverMaxUShort;
    *out++ = o->_translationBase + (float)(unsigned int)*p++ * o->_translationRangeOverMaxUShort;
    return &translation;
}

void FUN_001bf560(QSView *o, int index, float *out) {
    unsigned short *p = o->_compressedQuaternionList->_data + index * 4;
    *out++ = o->_quaternionBase + (float)(unsigned int)*p++ * o->_quaternionRangeOverMaxUShort;
    *out++ = o->_quaternionBase + (float)(unsigned int)*p++ * o->_quaternionRangeOverMaxUShort;
    *out++ = o->_quaternionBase + (float)(unsigned int)*p++ * o->_quaternionRangeOverMaxUShort;
    *out++ = o->_quaternionBase + (float)(unsigned int)*p++ * o->_quaternionRangeOverMaxUShort;
}

void Gap__Sg__igCompressedAnimationSequenceQS__vfunc_46(QSView *o, int index, float *out) {
    unsigned short *p = o->_compressedTranslationList->_data + index * 3;
    *out++ = o->_translationBase + (float)(unsigned int)*p++ * o->_translationRangeOverMaxUShort;
    *out++ = o->_translationBase + (float)(unsigned int)*p++ * o->_translationRangeOverMaxUShort;
    *out++ = o->_translationBase + (float)(unsigned int)*p++ * o->_translationRangeOverMaxUShort;
}

/* Decodes a 16-bit sign-magnitude sample (bit 15 = sign, 15-bit magnitude) into a 64-bit fixed-
 * point value (magnitude << 23). One 64-bit variable is widened, masked, shifted and negated in
 * place. */
long long Gap__Sg__igCompressedAnimationSequenceQS__vfunc_42(int *arg0, int arg1) {
    unsigned short *d = *(unsigned short **)(arg0[4] + 16);
    long long v = d[arg1];
    if (v & 0x8000) { v &= 0x7FFF; v <<= 0x17; v = -v; } else v <<= 0x17;
    return v;
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

int Gap__Sg__igCompressedAnimationSequenceQS__vfunc_23(O_1bfa60 *a0, int a1, long long a2) {
    unsigned char s6f; unsigned char s6e; int s68; int s64; float s60; float s5c; int s50[3]; int s40[4];
    float f;
    FUN_001bf7d0((QSSequenceView *)a0, &s6f, &s6e, &s68, &s64, &s60, &s5c, a2);
    igMatrix44f_SetIdentity(a1);
    if (s6f) {
        if (a0->flags & 2) { FUN_001bf560((QSView *)a0, 0, (float *)s40); FUN_00192810(s40, a1); }
        if (a0->flags & 1) { a0->v44(0, s50); igMatrix44f_SetTranslation(a1, s50); }
    } else if (s6e) {
        if (a0->flags & 2) { FUN_001bf560((QSView *)a0, a0->m->count - 1, (float *)s40); FUN_00192810(s40, a1); }
        if (a0->flags & 1) { a0->v44(a0->v33() - 1, s50); igMatrix44f_SetTranslation(a1, s50); }
    } else {
        if (s5c < 9.99999997e-07f) f = 0.0f; else f = s60 / s5c;
        if (a0->flags & 2) { a0->v46(s40, s68, s64, f); FUN_00192810(s40, a1); }
        if (a0->flags & 1) { a0->v45(s50, s68, s64, f); igMatrix44f_SetTranslation(a1, s50); }
    }
    return 1;
}

/* IgCompressedAnimationSequenceQS virtual getter 35. Returns the element count of the
 * `_compressedTimeList` (reflected object ref, +16): the word at +8 of an igDataList-style list is
 * `_count`. The list is read through the generic igDataList layout. */

int Gap__Sg__igCompressedAnimationSequenceQS__vfunc_35(igCompressedAnimationSequenceQS *self) {
    return ((igDataList *)self->_compressedTimeList)->_count;
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

void Gap__Sg__igCompressedAnimationSequenceQS__vfunc_48(struct S_1bfe90 *arg0, int *arg1, void *arg2, int *arg3, float fparg0) {
    int sp80[4]; int sp70[4]; int sp60[4]; int sp50[4];
    unsigned char t;
    t = arg0->f58;
    if (t == 0) {
        FUN_001bf560((QSView *)arg0, (int)(arg2), (float *)arg1);
        return;
    }
    if (t == 3) {
        FUN_001bf560((QSView *)arg0, (int)(arg2), (float *)sp80);
        FUN_001bf560((QSView *)arg0, (int)(arg3), (float *)sp70);
        FUN_00192ab0((float *)arg1, fparg0, (void *)sp80, (void *)sp70);
        return;
    }
    FUN_001bf560((QSView *)arg0, (int)(arg2), (float *)sp60);
    FUN_001bf560((QSView *)arg0, (int)(arg3), (float *)sp50);
    Quaternion_Lerp((float *)arg1, fparg0, (void *)sp60, (void *)sp50);
}

void Gap__Sg__igCompressedAnimationSequenceQS__vfunc_47(void *arg0, int *arg1, int arg2, int arg3, float fparg0) {
    int sp60[4];
    int sp50[4];

    if (*(unsigned char *)((char *)(arg0) + 57) == 0) {
        ((DW4VC_184_2 *)(((char *)(arg0) + 0)))->vX(arg2, arg1);
        return;
    }
    ((DW4VC_184_2 *)(((char *)(arg0) + 0)))->vX(arg2, &sp60[0]);
    ((DW4VC_184_2 *)(((char *)(arg0) + 0)))->vX(arg3, &sp50[0]);
    Vec3_Lerp((float *)arg1, fparg0, (void *)&sp60[0], (void *)&sp50[0]);
}

int Gap__Sg__igCompressedAnimationSequenceQS__vfunc_25(S_1c0010 *arg0, int arg1, long long arg2) {
    unsigned char sp4F;
    unsigned char sp4E;
    int sp48;
    int sp44;
    float sp40;
    float sp3C;

    FUN_001bf7d0((QSSequenceView *)arg0, &sp4F, &sp4E, &sp48, &sp44, &sp40, &sp3C, arg2);
    if (sp4F != 0) {
        FUN_001bf560((QSView *)arg0, 0, (float *)arg1);
    } else if (sp4E != 0) {
        FUN_001bf560((QSView *)arg0, arg0->f16->cnt - 1, (float *)arg1);
    } else {
        ((V192 *)arg0)->vX(arg1, sp48, sp44, sp40 / sp3C);
    }
    return 1;
}

int Gap__Sg__igCompressedAnimationSequenceQS__vfunc_27(O_1c00e0 *arg0, int arg1, int arg2, long long arg3) {
    unsigned char sp6F; unsigned char sp6E; int sp68; int sp64; float sp60; float sp5C; float f20;
    FUN_001bf7d0((QSSequenceView *)arg0, &sp6F, &sp6E, &sp68, &sp64, &sp60, &sp5C, arg3);
    if (sp6F != 0) {
        FUN_001bf560((QSView *)arg0, 0, (float *)arg1);
        arg0->v184(0, arg2);
    } else if (sp6E != 0) {
        FUN_001bf560((QSView *)arg0, arg0->f16->n - 1, (float *)arg1);
        arg0->v184(arg0->v140() - 1, arg2);
    } else {
        if (sp5C < 9.99999997e-07f) {
            f20 = 0.0f;
        } else {
            f20 = sp60 / sp5C;
        }
        arg0->v192(arg1, sp68, sp64, f20);
        arg0->v188(arg2, sp68, sp64, f20);
    }
    return 1;
}

/* Getter: the scale keyframe list (`_scaleList`). */

int FUN_001c0240(igTransformSequence1_5 *self) {
    return self->_scaleList;
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

/* Completes the field of view from the aspect ratio and rebuilds the near-pass and far-pass projections. */
void DepthOfField_UpdateProjections(DepthOfFieldNode *dof) {
    if (dof->_fovX == -1.0f) {
        dof->_fovX = dof->_fovY * dof->_aspect;
    } else if (dof->_fovY == -1.0f) {
        dof->_fovY = dof->_fovX / dof->_aspect;
    }
    igMatrix44fView nearProjection;
    igMatrix44f_MakePerspective(&nearProjection, degToRad(dof->_fovX), degToRad(dof->_fovY), aspectOf(*dof),
                 dof->_nearPlane, nearRegionFar(*dof));
    ((ProjectionMatrixAttrView *)g_depthOfFieldNearProjectionAttr[0])->setMatrix(&nearProjection);
    igMatrix44fView farProjection;
    igMatrix44f_MakePerspective(&farProjection, degToRad(dof->_fovX), degToRad(dof->_fovY), aspectOf(*dof),
                 dof->_focusDistance, dof->_farPlane);
    ((ProjectionMatrixAttrView *)g_depthOfFieldFarProjectionAttr[0])->setMatrix(&farProjection);
}

int FUN_001c0390(void *, int) {
    return 0;
}

void FUN_001c03a0(DepthOfFieldNode *arg0, A1_1c03a0 *arg1) {
    float sp70[4];
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
                s1->v716(sp70);
                f20 = s1->v728();
                s4 = DAT_00562660[0];
                s4->a[0] = sp70[0];
                s4->a[1] = sp70[1];
                s4->a[2] = sp70[2];
                s4->a[3] = sp70[3];
                s4->f60 = FUN_001931b0(sp70, 1);
                s4 = DAT_00562660[0];
                s4->f48 = fptodp(f20);
                s4->f64 = f20;
                FUN_001dc500((A_1dc500 *)arg1->f68, 0, 0);
                igAttrStackManager_PushOverrideAttr((igAttrStackManager *)s0, (igAttr *)DAT_00562668[0]);
                igAttrStackManager_PushOverrideAttr((igAttrStackManager *)s0, (igAttr *)DAT_00562670[0]);
                FUN_001d9bb0((void *)arg1->f68, s0);
                igAttrStackManager_PushOverrideAttr((igAttrStackManager *)s0, (igAttr *)DAT_00562660[0]);
                igAttrStackManager_PushOverrideAttr((igAttrStackManager *)s0, (igAttr *)g_depthOfFieldFarProjectionAttr[0]);
                igTraversal_TraverseChildren((int)(arg1), (S_1e07a0 *)arg0);
                igAttrStackManager_PopOverrideAttr((struct A_1b13d0 *)s0, (struct B_1b13d0 *)g_depthOfFieldFarProjectionAttr[0]);
                igAttrStackManager_PopOverrideAttr((struct A_1b13d0 *)s0, (struct B_1b13d0 *)DAT_00562660[0]);
                igAttrStackManager_PopOverrideAttr((struct A_1b13d0 *)s0, (struct B_1b13d0 *)DAT_00562670[0]);
                igAttrStackManager_PopOverrideAttr((struct A_1b13d0 *)s0, (struct B_1b13d0 *)DAT_00562668[0]);
                FUN_001d9bb0((void *)arg1->f68, s0);
                igAttrStackManager_PushOverrideAttr((igAttrStackManager *)s0, (igAttr *)DAT_005626c8[0]);
                igAttrStackManager_PushOverrideAttr((igAttrStackManager *)s0, (igAttr *)DAT_005626a8[0]);
                igAttrStackManager_PushOverrideAttr((igAttrStackManager *)s0, (igAttr *)DAT_005626d0[0]);
                FUN_001d9bb0((void *)arg1->f68, s0);
                igAttrStackManager_PushOverrideAttr((igAttrStackManager *)s0, (igAttr *)DAT_00562680[0]);
                igAttrStackManager_PushOverrideAttr((igAttrStackManager *)s0, (igAttr *)DAT_00562688[0]);
                if (s1->v148(16) != 0) {
                    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)s0, (igAttr *)DAT_005626a0[0]);
                } else {
                    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)s0, (igAttr *)DAT_00562698[0]);
                }
                igAttrStackManager_PushOverrideAttr((igAttrStackManager *)s0, (igAttr *)DAT_00562690[0]);
                igAttrStackManager_PushOverrideAttr((igAttrStackManager *)s0, (igAttr *)DAT_005626c0[0]);
                igAttrStackManager_PushOverrideAttr((igAttrStackManager *)s0, (igAttr *)DAT_005626d8[0]);
                FUN_001db720(arg1->f68, DAT_00562678[0], s0);
                igAttrStackManager_PopOverrideAttr((struct A_1b13d0 *)s0, (struct B_1b13d0 *)DAT_005626d8[0]);
                igAttrStackManager_PopOverrideAttr((struct A_1b13d0 *)s0, (struct B_1b13d0 *)DAT_005626c0[0]);
                igAttrStackManager_PopOverrideAttr((struct A_1b13d0 *)s0, (struct B_1b13d0 *)DAT_00562690[0]);
                if (s1->v148(16) != 0) {
                    igAttrStackManager_PopOverrideAttr((struct A_1b13d0 *)s0, (struct B_1b13d0 *)DAT_005626a0[0]);
                } else {
                    igAttrStackManager_PopOverrideAttr((struct A_1b13d0 *)s0, (struct B_1b13d0 *)DAT_00562698[0]);
                }
                igAttrStackManager_PopOverrideAttr((struct A_1b13d0 *)s0, (struct B_1b13d0 *)DAT_00562688[0]);
                igAttrStackManager_PopOverrideAttr((struct A_1b13d0 *)s0, (struct B_1b13d0 *)DAT_00562680[0]);
                igAttrStackManager_PopOverrideAttr((struct A_1b13d0 *)s0, (struct B_1b13d0 *)DAT_005626d0[0]);
                igAttrStackManager_PopOverrideAttr((struct A_1b13d0 *)s0, (struct B_1b13d0 *)DAT_005626a8[0]);
                igAttrStackManager_PopOverrideAttr((struct A_1b13d0 *)s0, (struct B_1b13d0 *)DAT_005626c8[0]);
                FUN_001d9bb0((void *)arg1->f68, s0);
                igAttrStackManager_PushOverrideAttr((igAttrStackManager *)s0, (igAttr *)g_depthOfFieldNearProjectionAttr[0]);
                igTraversal_TraverseChildren((int)(arg1), (S_1e07a0 *)arg0);
                igAttrStackManager_PopOverrideAttr((struct A_1b13d0 *)s0, (struct B_1b13d0 *)g_depthOfFieldNearProjectionAttr[0]);
                FUN_001d9bb0((void *)arg1->f68, s0);
                FUN_001dc610(arg1->f68);
                return;
            }
        }
        FUN_001dc500((A_1dc500 *)arg1->f68, 0, 0);
        igTraversal_TraverseChildren((int)(arg1), (S_1e07a0 *)arg0);
        FUN_001dc610(arg1->f68);
    }
}

