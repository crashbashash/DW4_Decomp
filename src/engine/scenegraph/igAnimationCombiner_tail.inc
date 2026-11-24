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

char g_cleanCombinerStates;

void FUN_001abca0(void) {
    int allocator = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem);
    g_igAnimationCombinerBoneInfoPool_instance.release();
    g_igAnimationCombinerBoneInfoPool_instance.p = (igAnimationCombinerBoneInfoPool *)igAnimationCombinerBoneInfoPool_Create(allocator);
    g_igAnimationCombinerBoneInfoPool_instance->_resetMode = 0;
    allocator = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem);
    g_igAnimationStatePool_instance.release();
    g_igAnimationStatePool_instance.p = (igAnimationStatePool *)igAnimationStatePool_Create(allocator);
    allocator = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem);
    g_igAnimation_instance.release();
    g_igAnimation_instance.p = (igAnimation *)Gap::Sg::igAnimation::_instantiateFromPool((igMemoryPoolView *)allocator);
    ((Gap::Core::igRegistry *)(*(int *)((char *)g_objectSystem + 56)))->getValue(7, "cleanCombinerStates", *(unsigned char *)&g_cleanCombinerStates, 0, 0);
}

void FUN_001abdf0(void) {
    g_igAnimationCombinerBoneInfoPool_instance.clear();
    g_igAnimationStatePool_instance.clear();
    g_igAnimation_instance.clear();
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
                igObject_Destroy((igObject *)r);
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
                            igObject::release(base);
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

void igAnimationCombiner_SetHierarchyUpdated(igAnimationCombiner *self, char arg1) {
    self->_hierarchyUpdated = arg1;
}

namespace Gap {
namespace Sg {

bool igTransformSequence::evaluateRotationAndTranslation(float *quaternion, float *translation, long long time, int *cachedLastTimeFrame, int flags) {
    float matrix[16];
    bool result = ((igTransformSource *)this)->getMatrix(*(igMatrix44f *)matrix, time, cachedLastTimeFrame, flags);
    igMatrix44f_GetQuaternion(quaternion, matrix);
    igMatrix44f_GetTranslation(matrix, translation);
    return result;
}
}
}

