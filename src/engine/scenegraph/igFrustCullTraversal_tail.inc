void FUN_001c4590(int arg0) {
    FUN_001c4700(((int)DAT_00562760[0]), arg0);
}

void FUN_001c45a0(void) {
    *(int *)0x562760 = FUN_0019a6e0(Memory_GetAllocatorBySelector(*(int *)0x587038));
}

void FUN_001c45d0(void) {
    void *temp_a0;

    temp_a0 = *(void **)0x562760;
    if (temp_a0 != 0) {
        *(int *)((char *)temp_a0 + 4) = (int) (*(int *)((char *)temp_a0 + 4) - 1);
        if (((unsigned long long) ((long long) *(int *)((char *)temp_a0 + 4) << 0x29) >> 0x29) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
}

void Gap__Sg__igFrustCullTraversal__vfunc_31(igFrustCullTraversal *self) {
    Gap__Sg__igCommonTraversal__vfunc_31((A_1b6e20 *)self);
    self->_curMVMat = 0;
    self->_curProjectionMat = 0;
}

void Gap__Sg__igFrustCullTraversal__vfunc_09(O_1c4650 *arg0, int arg1) {
    R_1c4650 *s0;
    R_1c4650 *a0;
    Gap__Sg__igCommonTraversal__vfunc_09((igCommonTraversal *)arg0, arg1);
    if (arg1 == 0) {
        s0 = DAT_00562760[0];
        if (s0 != 0) {
            s0->references = s0->references + 1;
        }
        a0 = arg0->ref;
        if (a0 != 0) {
            a0->references = a0->references - 1;
            if (((unsigned long long)(long long)a0->references & 0x7fffffULL) == 0) {
                igObject_Destroy((void *)a0);
            }
        }
        arg0->ref = s0;
        arg0->flags = arg0->flags | 0x200;
        arg0->v->vX(0);
    }
}

void FUN_001c4700(int arg0, int arg1) {
    FUN_001b68c0((void *)arg0, (void *)arg1);
    if (FUN_002fe290(arg1, ((int)igNode_GetMetaObject())) != 0) {
        igTraversal_RegisterFunction((struct L_1e06c0 *)arg0, (struct X_1e06c0 *)arg1, (void *)&FUN_001c5030);
    }
    if (FUN_002fe290(arg1, ((int)igPlanarShadowShader_GetMetaObject())) != 0) {
        igTraversal_RegisterFunction((struct L_1e06c0 *)arg0, (struct X_1e06c0 *)arg1, (void *)&FUN_001c5130);
    }
}

void Gap__Sg__igFrustCullTraversal__vfunc_24(igCommonTraversal *self, int arg1) {
    Gap__Sg__igCommonTraversal__vfunc_24((igCommonTraversal *)self, arg1);
}

void FUN_001c47a0(void *arg0, int arg1, int arg2) {
    FUN_001904f0((char *)arg0 + 0x1DC);
    *(int *)((char *)(arg0) + 540) = arg1;
    *(int *)((char *)(arg0) + 544) = arg2;
}

int FUN_001c4ac0(CullFrustumView *o, CullBoundsView *b) {
    CullAttrState *st;
    /* matching construct: permuter — st assigned inside the first lookup, so the second reloads its fields */
    float *world = currentEntry_1c4ac0(stackOf_1c4ac0(st = o->_state, ((CullMeta * *)g_igModelViewMatrixAttr_metaObject)[0]))->_matrix;
    float *view = currentEntry_1c4ac0(stackOf_1c4ac0(st, g_igProjectionMatrixAttr_metaObject[0]))->_matrix;
    int same = o->_lastWorld == world;
    if (same) {
        same = o->_lastView == view;
    }
    if (!same) {
        FUN_001c47a0((void *)o, (int)(world), (int)(view));
    }
    return FUN_001c47f0(o->_frustum, b->_min, b->_max);
}

void FUN_001c5030(igFrustCullTraversal *arg0, igNode *arg1) {
    if (arg0->_modeMask & 0x200) {
        BoundVolume *o = (BoundVolume *)arg1->_bound;
        void *var = o;
        if (o != 0) {
            int t = g_igAABox_metaObject[0];
            if (t == o->ty()) {
                var = o;
            } else {
                igAABox *x = (igAABox *)arg0->_boundingBox;
                var = x;
                float *mn = (float *)x->_min;
                float *mx = (float *)&x->_max;
                mn[0] = mn[1] = mn[2] = 3.4028235e38f;
                mx[0] = mx[1] = mx[2] = -3.4028235e38f;
                igVolume_ExtendBy(x, o);
            }
            FUN_001c4c20(arg0, arg1, FUN_001c4ac0((CullFrustumView *)arg0, (CullBoundsView *)var));
            return;
        }
    }
    unsigned sel = arg1->_handle;
    ((void (*)(igFrustCullTraversal *, igNode *))DAT_00562640[0]->_data[sel])(arg0, arg1);
}

int FUN_001c5130(void *arg0, TraversalNodeView *arg1) {
    return ((int (*)(void *, TraversalNodeView *))((TravFunctionTable *)DAT_00562640[0])->_data[arg1->_id])(arg0, arg1);
}

int FUN_001c5160(S0_1c5160 *arg0, float fparg0) {
    if (fparg0 < arg0->f556 && !(fparg0 < 1.0f)) { arg0->f552 = fparg0; DAT_0048da28[0] = 1.0f / fparg0; return 1; } return 0;
}

void FUN_001c51b0(int arg0, int arg1, int arg2) {
    FUN_001c47f0(arg2, arg0, arg1);
}

