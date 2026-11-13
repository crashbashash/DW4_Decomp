int FUN_001abc20(int *arg0, int arg1) {
    int r;
    int *t;
    unsigned int idx;
    int *bits;

    t = (int *)arg0[6];
    idx = arg1 * 2;
    if (t == 0) {
        return -1;
    }
    bits = (int *)t[4];
    r = 0;
    if ((1 << (idx & 0x1F)) & bits[idx >> 5]) {
        r |= 1;
    }
    idx = idx + 1;
    if ((1 << (idx & 0x1F)) & bits[idx >> 5]) {
        r |= 2;
    }
    return r - 1;
}

void FUN_001abca0(void) {
    int s0;
    AnimationPoolObject *t;
    s0 = Memory_GetAllocatorBySelector(DAT_00587038[0]);
    t = DAT_00562528[0];
    if (t != 0) {
        --t->references;
        if (((unsigned long long)(long long)t->references & 0x7fffffULL) == 0) {
            igObject_Destroy((void *)t);
        }
    }
    DAT_00562528[0] = ((AnimationPoolObject *)igAnimationCombinerBoneInfoPool_Create(s0));
    DAT_00562528[0]->f28 = 0;
    s0 = Memory_GetAllocatorBySelector(DAT_00587038[0]);
    t = DAT_00562540[0];
    if (t != 0) {
        --t->references;
        if (((unsigned long long)(long long)t->references & 0x7fffffULL) == 0) {
            igObject_Destroy((void *)t);
        }
    }
    DAT_00562540[0] = ((AnimationPoolObject *)igAnimationStatePool_Create(s0));
    s0 = Memory_GetAllocatorBySelector(DAT_00587038[0]);
    t = DAT_00562558[0];
    if (t != 0) {
        --t->references;
        if (((unsigned long long)(long long)t->references & 0x7fffffULL) == 0) {
            igObject_Destroy((void *)t);
        }
    }
    DAT_00562558[0] = ((AnimationPoolObject *)FUN_001a90f0(s0));
    FUN_00306e50(*(int *)((char *)(((int * *)g_objectSystem)[0]) + 56), 7, &DAT_004e44e0[0], &GPR_00554b84, 0, 0);
}

void FUN_001abdf0(void) {
    struct R_1abdf0 *p;
    p = ((struct R_1abdf0 * *)DAT_00562528)[0];
    if (p != 0) {
        p->f4 = p->f4 - 1;
        if ((p->f4 & 0x7FFFFF) == 0) {
            igObject_Destroy((void *)p);
        }
    }
    ((struct R_1abdf0 * *)DAT_00562528)[0] = 0;
    p = ((struct R_1abdf0 * *)DAT_00562540)[0];
    if (p != 0) {
        p->f4 = p->f4 - 1;
        if ((p->f4 & 0x7FFFFF) == 0) {
            igObject_Destroy((void *)p);
        }
    }
    ((struct R_1abdf0 * *)DAT_00562540)[0] = 0;
    p = ((struct R_1abdf0 * *)DAT_00562558)[0];
    if (p != 0) {
        p->f4 = p->f4 - 1;
        if ((p->f4 & 0x7FFFFF) == 0) {
            igObject_Destroy((void *)p);
        }
    }
    ((struct R_1abdf0 * *)DAT_00562558)[0] = 0;
}

void *FUN_001abed0(igCollisionGrid *a0, X *a1, void **out) {
    int i; int j; int cnt; bool seen; Item *it; Own *best; int bestw; bool found; bool f; int k; igObjectList *tbl; int n; igObjectList *lst; int lim; Own *ow; int w; int key; int tc; Ent *e;
    n = ((V_1abed0 *)a0->_activeCells)->vN();
    best = 0;
    bestw = 0;
    found = false;
    tbl = a1->r->tbl;
    for (i = 0; i < n; i++) {
        lst = ((igObjectList **)((igObjectListList *)a0->_staticCollisions)->_data)[i];
        cnt = lst->_count;
        if (cnt > 0) {
            j = cnt - 1;
            lim = ((int *)((igIntList *)a0->_lostGroups)->_data)[i];
            seen = false;
            while (j >= lim) {
                it = ((Item **)lst->_data)[j];
                ow = it->owner;
                if (ow == (Own *)a1) { seen = true; }
                else if (seen) {
                    w = it->w;
                    if (!found || bestw < w) {
                        f = false;
                        key = ow->key;
                        tc = tbl->_count;
                        for (k = 0; k < tc; k++) {
                            e = ((Ent **)tbl->_data)[k];
                            if (key == e->key) {
                                f = true;
                                *out = e;
                                bestw = w;
                                best = ow;
                                found = f;
                                break;
                            }
                        }
                        if (f) break;
                    } else break;
                }
                j--;
            }
        }
    }
    return best;
}

/* matching construct: _animHierarchy/_boneInfoListList/_data/_animationState/_baseState are 4-byte reference fields; the casts give the typed views (no layout effect) */
void FUN_001ac040(igAnimationCombiner *arg0, igAnimationState *arg1) {
    int count = ((VC *)arg0->_animHierarchy)->v96();
    int i;
    for (i = 0; i < count; i++) {
        igAnimationCombinerBoneInfoList *l = ((igAnimationCombinerBoneInfoList **)((igAnimationCombinerBoneInfoListList *)arg0->_boneInfoListList)->_data)[i];
        int n = l->_count;
        if (n > 0) {
            int j;
            bool found = false;
            for (j = n - 1; j >= 0; j--) {
                igAnimationState *x = (igAnimationState *)((igAnimationCombinerBoneInfo **)l->_data)[j]->_animationState;
                if (x == arg1) {
                    found = true;
                } else if (found) {
                    x->_status = 3;
                }
            }
        }
    }
    arg1->_combineMode = 0;
    {
        igObject *r = (igObject *)arg1->_baseState;
        if (r != 0) {
            r->_refCount = r->_refCount - 1;
            if (((unsigned long long)((long long)*(int *)&r->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy((void *)r);
            }
        }
    }
    arg1->_baseState = 0;
    FUN_001ad770((igAnimationCombiner *)arg0);
}

long long FUN_001acb10(igTimeView *a) {
    if (a->t != -1) {
        return a->t;
    }
    return ((igSceneMgrView *)DAT_005871d8[0])->slot24();
}

void FUN_001acb50(igAnimationCombiner *c) {
    long long last = c->_lastCleanStatesTime;
    long long now = FUN_001acb10((igTimeView *)c);
    c->_lastCleanStatesTime = now;
    if (now - last >= c->_cleanStatesTimeThreshold) {
        CombinerStateList *list = (CombinerStateList *)c->_animationStateList;
        int i;
        for (i = list->_count - 1; i >= 0; i--) {
            igAnimationState *s = list->_data[i];
            float ticks = (float)(unsigned int)(int)((now - s->_timeRequested) >> 18);
            ticks = ticks * s->_timeScale;
            unsigned long long whole = (unsigned int)ticks;
            long long elapsed = whole << 18;
            long long past = elapsed - s->_blendDuration;
            if (past > c->_cleanStatesTransitionMargin) {
                int mode = s->_transitionMode;
                if (mode == 5) {
                    FUN_001ac040(c, s);
                } else if (mode == 1) {
                    if (s->_baseState != 0) {
                        s->_combineMode = 0;
                        FUN_001ad770(c);
                        ((igAnimationState *)s->_baseState)->_status = 3;
                        {
                            igAnimationState *base = (igAnimationState *)s->_baseState;
                            if (base != 0) {
                                base->_refCount = base->_refCount - 1;
                                if (((unsigned long long)((long long)(int)base->_refCount << 0x29) >> 0x29) == 0) {
                                    igObject_Destroy((void *)base);
                                }
                            }
                        }
                        s->_baseState = 0;
                    } else {
                        FUN_001ac040(c, s);
                    }
                }
            }
        }
    }
}

void Gap__Sg__igAnimationCombiner__vfunc_26(void *arg0, char arg1) {
    *(char *)((char *)arg0 + 81) = arg1;
}

int FUN_001ad310(void **arg0, int arg1, int arg2, int arg3, int arg4, int arg5) {
    int sp40[16];
    int temp_s0;

    temp_s0 = ((DW4VC_96_4 *)(arg0))->vX((int)(sp40), (int)(arg3), (int)(arg4), (int)(arg5)) & 0xFF;
    Matrix44_GetQuaternion(arg1, sp40);
    Matrix44_GetTranslation(sp40, arg2);
    return temp_s0;
}

