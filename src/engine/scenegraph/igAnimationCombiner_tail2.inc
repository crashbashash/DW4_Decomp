void Gap__Sg__igAnimationCombiner__vfunc_17(CombinerView *c) {
    int result1;
    int result2;
    int bones;
    int i;
    Gap__Core__igObject__vfunc_15(c);
    bones = c->_animHierarchy->getBoneCount();
    for (i = 0; i < bones; i++) {
        BoneInfoRow *row = c->_boneInfoListList->_data[i];
        int j;
        for (j = 0; j < row->_count; j++) {
            igAnimationCombinerBoneInfo *info = row->_data[j];
            if (info->_transformSource != 0 && !info->_useAnimationTranslation) {
                float *t = c->_animHierarchy->_translations + i * 3;
                float y;
                float z;
                float x;
                z = t[2];
                y = t[1];
                x = t[0];
                info->_constantTranslation[0] = x;
                info->_constantTranslation[1] = y;
                info->_constantTranslation[2] = z;
            }
        }
    }
    if (c->_animHierarchy != 0) {
        int boneCount = c->_animHierarchy->getBoneCount();
        int blendCount = c->_animHierarchy->getBlendCount();
        if (boneCount != 0) {
            if (c->_boneMatrixArray == 0) {
                float *m;
                int k;
                igMetaField_AllocateArray(&result1, DAT_00562300, c, boneCount, igObject_GetAllocator(c));
                m = c->_boneMatrixArray;
                for (k = 0; k < boneCount; k++) {
                    igMatrix44f_SetIdentity(m);
                    m += 16;
                }
            }
            if (blendCount != 0 && c->_blendMatrixArray == 0) {
                float *m;
                int k;
                igMetaField_AllocateArray(&result2, DAT_00562308, c, blendCount, igObject_GetAllocator(c));
                m = c->_blendMatrixArray;
                for (k = 0; k < blendCount; k++) {
                    igMatrix44f_SetIdentity(m);
                    m += 16;
                }
            }
        }
    }
}

void FUN_001ad5c0(A_1ad5c0 *arg0, It *arg1, int arg2) {
    Ls *l;
    int n, i, v, nv;
    It *e;
    IL *il, *il2, *il3;
    int *p;
    l = arg0->ll->data[arg2];
    n = l->count;
    if (n == 0) {
        ObjectList_AppendRetained(l, arg1);
        il = arg0->il;
        if (il->count != 0 && arg2 >= 0 && arg2 < il->count) {
            il->data[arg2] = 0;
        }
        arg0->b80 = 0;
        return;
    }
    i = 0;
    do {
        e = l->data[i];
        if (e->prio > arg1->prio) break;
        i++;
    } while (i != n);
    if (i == n) {
        ObjectList_AppendRetained(l, arg1);
    } else {
        insertRetained(l, i, arg1);
        il2 = arg0->il;
        p = &il2->data[arg2];
        v = *p;
        nv = v + 1;
        if (i <= v) {
            if (il2->count != 0 && arg2 >= 0 && arg2 < il2->count) {
                *p = nv;
            }
            arg0->b80 = 0;
        }
    }
    if (arg1->x->w12 == 0) {
        il3 = arg0->il;
        p = &il3->data[arg2];
        if (*p < i) {
            if (il3->count != 0 && arg2 >= 0 && arg2 < il3->count) {
                *p = i;
            }
            arg0->b80 = 0;
        }
    }
}

void FUN_001ad770(igAnimationCombiner *a) {
    int n = ((igAnimationCombinerBoneInfoListList *)a->_boneInfoListList)->_count;
    int i = 0;
    goto cond;
body:
    {
        igAnimationCombinerBoneInfoList *l = ((igAnimationCombinerBoneInfoList **)((igAnimationCombinerBoneInfoListList *)a->_boneInfoListList)->_data)[i];
        int j = l->_count - 1;
        bool found = 0;
        goto jcond;
jbody:
        if (((igAnimationState *)((igAnimationCombinerBoneInfo **)l->_data)[j]->_animationState)->_combineMode == 0) {
            igIntList *s = (igIntList *)a->_boneInfoListBase;
            if (s->_count != 0 && i >= 0 && i < s->_count) ((int *)s->_data)[i] = j;
            a->_cacheValid = 0;
            found = 1;
            goto jdone;
        }
        j--;
jcond:
        if (j > 0) goto jbody;
jdone:
        if (!found) {
            igIntList *s = (igIntList *)a->_boneInfoListBase;
            if (s->_count != 0 && i >= 0 && i < s->_count) ((int *)s->_data)[i] = 0;
            a->_cacheValid = 0;
        }
        i++;
    }
cond:
    if (i < n) goto body;
}

int FUN_001ad860(igAnimationCombiner *arg0, igAnimationState *arg1) {
    int var_s4;
    igAnimationCombinerBoneInfoList *temp_s3;
    int var_s2;
    bool var_s1;
    igAnimationState *temp_s0;
    int temp_s7;
    int temp_v0;
    igAnimationState *temp_a0_2;
    temp_s7 = ((V_1ad860 *)arg0->_animHierarchy)->vX();
    var_s4 = 0;
    while (var_s4 < temp_s7) {
        temp_s3 = ((igAnimationCombinerBoneInfoList **)((igAnimationCombinerBoneInfoListList *)arg0->_boneInfoListList)->_data)[var_s4];
        temp_v0 = temp_s3->_count;
        var_s2 = temp_v0 - 1;
        if (temp_v0 > 0) {
            var_s1 = 0;
            while (var_s2 >= 0) {
                temp_s0 = (igAnimationState *)((igAnimationCombinerBoneInfo **)temp_s3->_data)[var_s2]->_animationState;
                if (temp_s0 == arg1) {
                    var_s1 = true;
                } else if (var_s1) {
                    temp_a0_2 = (igAnimationState *)temp_s0->_cycleMatchTargetState;
                    if (temp_a0_2 == arg1) {
                        if (temp_a0_2 != 0) {
                            temp_a0_2->_refCount = (int)temp_a0_2->_refCount - 1;
                            if (((unsigned long long) ((long long) (int)temp_a0_2->_refCount << 0x29) >> 0x29) == 0) {
                                igObject_Destroy((void *)temp_a0_2);
                            }
                        }
                        temp_s0->_cycleMatchTargetState = 0;
                    }
                }
                var_s2 -= 1;
            }
        }
        var_s4 += 1;
    }
    return 1;
}

int FUN_001ad990(CombinerBlendView *c, CombinerAnimation *anim, int combineMode, int transitionMode, int status, int *priorities, bool perBone, CombinerBinding *binding) {

    int i;
    CombinerTrack *track;
    int bones;
    CombinerBoneState *state;
    int pi;
    igPoolObject *source;
    CombinerBoneInfo *b;
    pi = 0;
    c->_cacheValid = 0;
    bones = c->_animHierarchy->reset();
    if (c->_animationStateList->_count == 0) {
        combineMode = 0;
    }
    state = (CombinerBoneState *)poolTake(*(CombinerPool **)((int *)DAT_00562540), (void *)FUN_001a6bb0);
    retain(&anim->_base);
    releaseWord(state->_animation);
    state->_animation = &anim->_base;
    state->_combineMode = combineMode;
    state->_transitionMode = transitionMode;
    state->_status = status;
    state->_new = 1;
    state->_base.slot21();
    state->_blendStartTime = 0;
    ObjectList_AppendRetained(c->_animationStateList, state);
    state->_timeRequested = FUN_001acb10((igTimeView *)c);
    for (i = 0; i < bones; i++) {
        int t = binding->_boneMap[i];
        track = 0;
        if (t != -1) {
            track = anim->_trackList->_data[t];
        }
        if (track != 0) {
            b = (CombinerBoneInfo *)poolTake(*(CombinerPool **)((int *)DAT_00562528), (void *)FUN_001a80b0);
            source = track->_source;
            if (source != 0) {
                int useT = useTranslation(anim, binding->_boneMap[i]);
                int priority = priorities[pi];
                int r;
                setState(b, &state->_base);
                retain(source);
                releaseWord((igPoolObject *)b->_transformSource);
                b->_transformSource = (int)source;
                b->_priority = priority;
                b->_useTranslation = useT;
                r = FUN_001abc20((int *)binding, i);
                if (r != -1) {
                    b->_reflect = r;
                }
                if (!useT) {
                    float *v = *(float **)((char *)c->_animHierarchy + 12) + i * 3;
                    float y;
                    float z;
                    float x;
                    z = v[2];
                    y = v[1];
                    x = v[0];
                    b->_t[0] = x;
                    b->_t[1] = y;
                    b->_t[2] = z;
                }
            } else {
                unsigned int idx = binding->_boneMap[i];
                float *q = track->_q;
                float *v;
                float neg[4];
                int r;
                int priority;
                if (useTranslation(anim, idx)) {
                    v = anim->_trackList->_data[idx]->_t;
                } else {
                    v = *(float **)((char *)c->_animHierarchy + 12) + i * 3;
                }
                r = FUN_001abc20((int *)binding, i);
                if (r != -1) {
                    neg[0] = q[0];
                    neg[1] = q[1];
                    neg[2] = q[2];
                    neg[3] = q[3];
                    q = neg;
                    neg[0] = -neg[0];
                    neg[1] = -neg[1];
                    neg[2] = -neg[2];
                    neg[r] = -neg[r];
                }
                priority = priorities[pi];
                setState(b, &state->_base);
                b->_q[0] = q[0];
                b->_q[1] = q[1];
                b->_q[2] = q[2];
                b->_q[3] = q[3];
                b->_t[0] = v[0];
                b->_t[1] = v[1];
                b->_t[2] = v[2];
                b->_priority = priority;
            }
            if (perBone) {
                pi++;
            }
            FUN_001ad5c0((A_1ad5c0 *)c, (It *)b, i);
        }
    }
    return 1;
}

int FUN_001adec0(CombinerBlendView *c, CombinerAnimation *anim, int combineMode, int transitionMode, int status, int *priorities, bool perBone) {
    CombinerBinding *binding;
    int result;

    FUN_001ab8b0((int)anim, *(int *)((char *)c + 12), (void **)&binding);
    result = 0;
    if (binding != 0) {
        result = FUN_001ad990(c, anim, combineMode, transitionMode, status, priorities, perBone, binding);
    }
    return result;
}

int igAnimationCombiner_RemoveAllStates(CombinerResetView *c) {
    PoolObjectList *states;
    int k;
    int count;
    int bones;
    int i;
    int n;
    states = c->_animationStateList;
    count = states->_count;
    bones = c->_animHierarchy->reset();
    if (count == 0) {
        return 0;
    }
    c->_cacheValid = 0;
    n = states->_count;
    for (i = 0; i < n; i++) {
        igPoolObject_1adf70 *s = states->_data[0];
        igPoolObject_1adf70 *o;
        s->reset();
        FUN_001dcb80((ObjectPool *)((int)DAT_00562540[0]), (igObject *)s);
        o = states->_data[0];
        if (o != 0) {
            o->_refCount = o->_refCount - 1;
            if (((unsigned long long)((long long)(int)o->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(o);
            }
        }
        List_RemoveWordAt(states, 0);
        states->_data[states->_count] = 0;
    }
    for (k = 0; k < bones; k++) {
        BoneInfoSlotList *row = c->_boneInfoListList->_data[k];
        int rowCount = row->_count;
        BoneInfoSlot *b;
        int j;
        for (j = 0; j < rowCount; j++) {
            igPoolObject_1adf70 *o;
            b = row->_data[0];
            FUN_001ae250((void * *)&b->_animationState, 0);
            FUN_001ae1d0((void * *)&b->_transformSource, 0);
            FUN_001ae1b0(b->_q, 0.0f, 0.0f, 0.0f, 0.0f);
            FUN_001ae1a0(b->_t, 0.0f, 0.0f, 0.0f);
            b->_priority = 0;
            b->_useTranslation = 0;
            b->_lastKeyframe = 1;
            b->_reflect = -1;
            FUN_001dcb80((ObjectPool *)((int)DAT_00562528[0]), (igObject *)b);
            o = (igPoolObject_1adf70 *)row->_data[0];
            if (o != 0) {
                o->_refCount = o->_refCount - 1;
                if (((unsigned long long)((long long)(int)o->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(o);
                }
            }
            List_RemoveWordAt(row, 0);
            row->_data[row->_count] = 0;
        }
    }
    return 1;
}

void FUN_001ae1a0(void *arg0, float fparg0, float fparg1, float fparg2) {
    *(float *)((char *)(arg0) + 0) = fparg0;
    *(float *)((char *)(arg0) + 4) = fparg1;
    *(float *)((char *)(arg0) + 8) = fparg2;
}

void FUN_001ae1b0(void *arg0, float fparg0, float fparg1, float fparg2, float fparg3) {
    *(float *)((char *)(arg0) + 0) = fparg0;
    *(float *)((char *)(arg0) + 4) = fparg1;
    *(float *)((char *)(arg0) + 8) = fparg2;
    *(float *)((char *)(arg0) + 12) = fparg3;
}

void **FUN_001ae1d0(void **arg0, void *arg1) {
    void *temp_a0;

    if (arg1 != 0) {
        ((igObject *)arg1)->_refCount = (int) ((int)((igObject *)arg1)->_refCount + 1);
    }
    temp_a0 = *arg0;
    if (temp_a0 != 0) {
        ((igObject *)temp_a0)->_refCount = (int) ((int)((igObject *)temp_a0)->_refCount - 1);
        if (((unsigned long long) ((long long) (int)((igObject *)temp_a0)->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    *arg0 = arg1;
    return arg0;
}

void **FUN_001ae250(void **arg0, igObject *arg1) {
    igObject *temp_a0;

    if (arg1 != 0) {
        arg1->_refCount = (int) (arg1->_refCount + 1);
    }
    temp_a0 = (igObject *)*arg0;
    if (temp_a0 != 0) {
        temp_a0->_refCount = (int) (temp_a0->_refCount - 1);
        if (((unsigned long long) ((long long) (int)temp_a0->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    *arg0 = arg1;
    return arg0;
}

int FUN_001ae2d0(CombinerStateView *c, igPoolObject *state) {
    igPoolObject *found;
    int bones;
    bool have;
    int si;
    int i;
    int count;
    CombinerStateList_1ae2d0 *states;
    states = c->_animationStateList;
    count = states->_count;
    found = 0;
    bones = c->_animHierarchy->reset();
    have = 0;
    for (si = 0; si < count; si++) {
        found = states->_data[si];
        if (found == state) {
            have = 1;
            break;
        }
    }
    if (!have) {
        return 0;
    }
    if (((CombinerStateRec *)found)->_isCycleMatchTarget) {
        FUN_001ad860((igAnimationCombiner *)c, (igAnimationState *)found);
    }
    c->_cacheValid = 0;
    for (i = 0; i < bones; i++) {
        CombinerBoneRow *row = c->_boneInfoListList->_data[i];
        int n = row->_count;
        int j;
        for (j = 0; j < n; j++) {
            CombinerBoneInfo *b = row->_data[j];
            if ((igPoolObject *)b->_animationState == state) {
                clearBoneInfo(b);
                FUN_001dcb80((ObjectPool *)((int)DAT_00562528[0]), (igObject *)b);
                releaseWord((igPoolObject *)row->_data[j]);
                List_RemoveWordAt(row, j);
                row->_data[row->_count] = 0;
                if (n - 1 > 0) {
                    bool set;
                    int k;
                    k = n - 2;
                    set = 0;
                    for (; k >= 0; k--) {
                        if (row->_data[k]->_animationState->_combineMode == 0) {
                            set = 1;
                            setBase(c, i, k);
                            break;
                        }
                    }
                    if (!set) {
                        setBase(c, i, 0);
                    }
                }
                break;
            }
        }
    }
    found->reset();
    FUN_001dcb80((ObjectPool *)((int)DAT_00562540[0]), (igObject *)found);
    releaseWord(states->_data[si]);
    List_RemoveWordAt(states, si);
    states->_data[states->_count] = 0;
    if (c->_animationStateList->_count == 1) {
        ((igAnimationState *)states->_data[0])->_combineMode = 0;
    }
    return 1;
}

int igAnimationCombiner_AddAnimationBlend(CombinerBlendView *c, CombinerAnimation *anim, int combineMode, int transitionMode, int status, int *priorities, bool perBone, long long arg7, float fparg0, float fparg1, long long arg_sp0) {
    struct L_1ae660 *l;
    struct E_1ae660 *e;
    int r;
    r = FUN_001adec0(c, anim, combineMode, transitionMode, status, priorities, perBone) & 0xFF;
    l = (struct L_1ae660 *)c->_animationStateList;
    e = (struct E_1ae660 *)*(int *)(l->items + ((l->count - 1) * 4));
    e->f96 = arg_sp0;
    e->f80 = fparg0;
    e->f84 = fparg1 - fparg0;
    e->f88 = arg7;
    e->f72 = 1;
    return r;
}

void Gap__Sg__igAnimationCombiner__vfunc_10(void **arg0) {
    if (((DW4VC_92_0 *)(arg0))->vX() != 0) {
        igAnimationCombiner_RemoveAllStates((CombinerResetView *)arg0);
        Gap__Core__igObject__vfunc_08__002ff0f0(arg0);
    }
}

int Gap__Sg__igAnimationCombiner__vfunc_23(void *arg0) {
    return *(int *)((char *)(arg0) + 64) != 0;
}

void igAnimationCombiner_AddAnimation(CombinerBlendView *c, CombinerAnimation *anim, int combineMode, int transitionMode, int status) {
    int priority;

    priority = anim->_priority;
    FUN_001adec0(c, anim, combineMode, transitionMode, status, &priority, 0);
}

int igAnimationCombiner_ResetToPose(CombinerStateView_1ae780 *c, CombinerStateView_1ae780 *from) {
    CombinerStateView_1ae780 *src;
    int need;
    int bones;
    igPoolObject *anim;
    CombinerNewState *state;
    int i;
    if (!from) {
        from = c;
    }
    { CombinerStateView_1ae780 *const pick = from; src = pick; }
    need = c->_animHierarchy->reset();
    if (need > src->_animHierarchy->reset()) {
        return 0;
    }
    igAnimationCombiner_RemoveAllStates((CombinerResetView *)c);
    c->_cacheValid = 0;
    bones = c->_animHierarchy->reset();
    state = (CombinerNewState *)poolTake(*(CombinerPool **)((int *)DAT_00562540), (void *)FUN_001a6bb0);
    anim = ((igPoolObject *)DAT_00562558[0]);
    if (anim != 0) {
        anim->_refCount = anim->_refCount + 1;
    }
    releaseWord(state->_animation);
    state->_animation = anim;
    state->_combineMode = 0;
    state->_transitionMode = 4;
    state->_status = 1;
    state->_new = 1;
    state->_base.slot21();
    state->_blendStartTime = 0;
    ObjectList_AppendRetained(c->_animationStateList, state);
    for (i = 0; i < bones; i++) {
        CombinerBoneInfo *info = (CombinerBoneInfo *)poolTake(*(CombinerPool **)((int *)DAT_00562528), (void *)FUN_001a80b0);
        float *m;
        float tx, ty, tz;
        CombinerQuat q;
        releaseWord((igPoolObject *)info->_transformSource);
        info->_transformSource = 0;
        info->_reflect = -1;
        m = (float *)(*(int *)((char *)src + 64) + (i << 6));
        tz = m[14];
        ty = m[13];
        tx = m[12];
        FUN_001925f0(&q, m);
        if (state != 0) {
            state->_base._refCount = state->_base._refCount + 1;
        }
        releaseWord((igPoolObject *)info->_animationState);
        info->_animationState = (igAnimationState *)state;
        info->_q[0] = q.x;
        info->_q[1] = q.y;
        info->_q[2] = q.z;
        info->_q[3] = q.w;
        info->_t[0] = tx;
        info->_t[1] = ty;
        info->_t[2] = tz;
        info->_priority = 0;
        FUN_001ad5c0((A_1ad5c0 *)c, (It *)info, i);
    }
    return 1;
}

