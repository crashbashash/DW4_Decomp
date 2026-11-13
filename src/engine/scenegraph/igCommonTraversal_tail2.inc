long long Gap__Sg__igCommonTraversal__vfunc_26(igCommonTraversal *t) {
    int top; igLongStack *stack = (igLongStack *)t->_timeStack; int n = stack->_count; top = n - 1;
    if (n == 0) {
        if (!t->_timeBuffered) {
            if (t->_userTimeState) {
                t->_timeLongBuf = t->_timeLong;
            } else {
                t->_timeLongBuf = ((igTimerSourceView *)DAT_005871d8[0])->getTime();
            }
            t->_timeBuffered = 1;
        }
        return t->_timeLongBuf;
    }
    return ((long long *)stack->_data)[top];
}

int FUN_001b3ad0(igCommonTraversal *arg0, int arg1) {
    igAttrStackManager *p;
    igMetaObject *mo;
    igAttrStack *a0;
    igAttrStack *l;
    int a2;
    int km;
    int k;
    unsigned s2;
    bool flag;
    igBitMask *b;
    igBitMask *b2;
    unsigned idx;
    int n;
    unsigned *d;
    unsigned w;
    unsigned idx2;
    unsigned w2;

    p = (igAttrStackManager *)arg0->_attrStack;
    a0 = ((igAttrStack **)((igAttrStackList *)p->_attrStacks)->_data)[((int *)p->_attrStackIndexTable)[g_igModelViewMatrixAttr_metaObject[0]->_id]];
    k = a0->_count;
    km = k - 1;
    if (k == 0) {
        a2 = 0;
    } else {
        a2 = ((int *)a0->_data)[km];
    }
    ((H_1b2fa0 *)DAT_005625f0)->vX(arg1, a2);
    mo = igTextureBindAttr_GetMetaObject();
    p = (igAttrStackManager *)arg0->_attrStack;
    l = ((igAttrStack **)((igAttrStackList *)p->_attrStacks)->_data)[((int *)p->_attrStackIndexTable)[mo->_id]];
    if (l != 0) {
        flag = !(l->_count == 0);
    } else {
        flag = 0;
    }
    b = ((H_1b2fa0 *)DAT_005625f0)->f184;
    s2 = b->_bitCount;
    FUN_001b1e50((void *)b, s2 + 1);
    b2 = ((H_1b2fa0 *)DAT_005625f0)->f184;
    if (flag) {
        idx = s2 >> 5;
        w = ((unsigned *)b2->_data)[idx] | (1 << (s2 & 31));
        if (b2->_count != 0 && (int)idx >= 0 && (int)idx < b2->_count) {
            ((unsigned *)b2->_data)[idx] = w;
        }
    } else {
        idx2 = s2 >> 5;
        w2 = ((unsigned *)b2->_data)[idx2] & ~(1 << (s2 & 31));
        if (b2->_count != 0 && (int)idx2 >= 0 && (int)idx2 < b2->_count) {
            ((unsigned *)b2->_data)[idx2] = w2;
        }
    }
    FUN_001c5660((Z_1c5660 *)arg1, 4, 1);
    return 0;
}

void FUN_001b3c90(A0 *arg0, A1 *arg1) {
    int temp_a0;
    int temp_s0;

    FUN_001b3030();
    temp_a0 = arg0->f160;
    FUN_00157200(temp_a0, 1, temp_a0);
    temp_s0 = arg1->f52;
    FUN_001dc500((A_1dc500 *)arg1->f68, 0, 0);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_005625e0[0]);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_005625e8[0]);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_005625b8[0]);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_005625c8[0]);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_005625c0[0]);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_005625d0[0]);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)arg0->f176);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)arg0->f32);
    igTraversal_TraverseChildren((int)arg1, (S_1e07a0 *)arg0);
    igAttrStackManager_PopOverrideAttr((struct A_1b13d0 *)temp_s0, (struct B_1b13d0 *)arg0->f32);
    igAttrStackManager_PopOverrideAttr((struct A_1b13d0 *)temp_s0, (struct B_1b13d0 *)arg0->f176);
    igAttrStackManager_PopOverrideAttr((struct A_1b13d0 *)temp_s0, (struct B_1b13d0 *)DAT_005625d0[0]);
    igAttrStackManager_PopOverrideAttr((struct A_1b13d0 *)temp_s0, (struct B_1b13d0 *)DAT_005625c0[0]);
    igAttrStackManager_PopOverrideAttr((struct A_1b13d0 *)temp_s0, (struct B_1b13d0 *)DAT_005625c8[0]);
    igAttrStackManager_PopOverrideAttr((struct A_1b13d0 *)temp_s0, (struct B_1b13d0 *)DAT_005625b8[0]);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_00562598[0]);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_005625d0[0]);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_005625c8[0]);
    igTraversal_TraverseChildren((int)arg1, (S_1e07a0 *)arg0);
    igAttrStackManager_PopOverrideAttr((struct A_1b13d0 *)temp_s0, (struct B_1b13d0 *)DAT_005625c8[0]);
    igAttrStackManager_PopOverrideAttr((struct A_1b13d0 *)temp_s0, (struct B_1b13d0 *)DAT_005625d0[0]);
    igAttrStackManager_PopOverrideAttr((struct A_1b13d0 *)temp_s0, (struct B_1b13d0 *)DAT_00562598[0]);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_005625b0[0]);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_005625c8[0]);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_005625c0[0]);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_005625d0[0]);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)arg0->f180);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)arg0->f32);
    igTraversal_TraverseChildren((int)arg1, (S_1e07a0 *)arg0);
    igAttrStackManager_PopOverrideAttr((struct A_1b13d0 *)temp_s0, (struct B_1b13d0 *)arg0->f32);
    igAttrStackManager_PopOverrideAttr((struct A_1b13d0 *)temp_s0, (struct B_1b13d0 *)arg0->f180);
    igAttrStackManager_PopOverrideAttr((struct A_1b13d0 *)temp_s0, (struct B_1b13d0 *)DAT_005625d0[0]);
    igAttrStackManager_PopOverrideAttr((struct A_1b13d0 *)temp_s0, (struct B_1b13d0 *)DAT_005625c0[0]);
    igAttrStackManager_PopOverrideAttr((struct A_1b13d0 *)temp_s0, (struct B_1b13d0 *)DAT_005625c8[0]);
    igAttrStackManager_PopOverrideAttr((struct A_1b13d0 *)temp_s0, (struct B_1b13d0 *)DAT_005625b0[0]);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_005625a8[0]);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_005625d0[0]);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_005625c8[0]);
    igTraversal_TraverseChildren((int)arg1, (S_1e07a0 *)arg0);
    igAttrStackManager_PopOverrideAttr((struct A_1b13d0 *)temp_s0, (struct B_1b13d0 *)DAT_005625c8[0]);
    igAttrStackManager_PopOverrideAttr((struct A_1b13d0 *)temp_s0, (struct B_1b13d0 *)DAT_005625d0[0]);
    igAttrStackManager_PopOverrideAttr((struct A_1b13d0 *)temp_s0, (struct B_1b13d0 *)DAT_005625a8[0]);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_005625d8[0]);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_005625c8[0]);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_005625a0[0]);
    igTraversal_TraverseChildren((int)arg1, (S_1e07a0 *)arg0);
    igAttrStackManager_PopOverrideAttr((struct A_1b13d0 *)temp_s0, (struct B_1b13d0 *)DAT_005625a0[0]);
    igAttrStackManager_PopOverrideAttr((struct A_1b13d0 *)temp_s0, (struct B_1b13d0 *)DAT_005625c8[0]);
    igAttrStackManager_PopOverrideAttr((struct A_1b13d0 *)temp_s0, (struct B_1b13d0 *)DAT_005625d8[0]);
    igAttrStackManager_PopOverrideAttr((struct A_1b13d0 *)temp_s0, (struct B_1b13d0 *)DAT_005625e8[0]);
    igAttrStackManager_PopOverrideAttr((struct A_1b13d0 *)temp_s0, (struct B_1b13d0 *)DAT_005625e0[0]);
    FUN_001dc610(arg1->f68);
}

void FUN_001b3ff0(void *arg0, int arg1) {
    void **temp_a0;
    void **temp_a0_2;

    if (FUN_001b4130((struct O4130 *)arg0) == 0) {
        igTraversal_TraverseChildren((int)arg1, (S_1e07a0 *)arg0);
        return;
    }
    FUN_001b4220((struct A4220 *)arg0, (struct B4220 *)arg1);
    FUN_001b42c0((TravFlattenView *)arg0, arg1);
    temp_a0 = (void **)(*(int *)((char *)(arg0) + 176));
    ((DW4VC_132_1 *)(temp_a0))->vX((int)(*(int *)((char *)(arg0) + 48)));
    temp_a0_2 = (void **)(*(int *)((char *)(arg0) + 180));
    ((DW4VC_132_1 *)(temp_a0_2))->vX((int)(*(int *)((char *)(arg0) + 52)));
    FUN_001b3c90((A0 *)arg0, (A1 *)arg1);
}

void FUN_001b4090(T_1b2fa0 *arg0, int arg1, int arg2) {
    if (arg1 < 8) {
        if (arg2 != 0) {
            arg0->flags |= (1 << arg1);
        } else {
            arg0->flags &= ~(1 << arg1);
        }
    }
}

int FUN_001b40f0(void *arg0, int arg1) {
    if (arg1 >= 8) {
        return 0;
    }
    return *(unsigned char *)((char *)(arg0) + 64) & (1 << arg1) & 0xFF;
}

int FUN_001b4120(int *p)
{
    return *(unsigned char *)((char *)p + 64);
}

int FUN_001b4130(struct O4130 *arg0) {
    struct Rc_1b2fa0 *temp_a0;
    struct Rc_1b2fa0 *temp_v0;

    if ((arg0->f32 == 0) || (FUN_001b4120((int *)arg0) == 0) || (arg0->f56->f8 == 0)) {
        return 0;
    }
    if (arg0->f160 == 0) {
        temp_v0 = ((struct Rc_1b2fa0 *)FUN_00140c00(arg0->f32->f12, 0));
        if (temp_v0 != 0) {
            temp_v0->rc = temp_v0->rc + 1;
        }
        temp_a0 = arg0->f160;
        if (temp_a0 != 0) {
            temp_a0->rc = temp_a0->rc - 1;
            if ((temp_a0->rc & 0x7FFFFF) == 0) {
                igObject_Destroy((void *)temp_a0);
            }
        }
        arg0->f160 = temp_v0;
        if (arg0->f160 == 0) {
            return 0;
        }
    }
    if (arg0->f160->f16 != 1) {
        return 0;
    }
    return 1;
}

void FUN_001b4220(struct A4220 *arg0, struct B4220 *arg1) {
    int temp_s2;
    int n;
    int i;
    struct Q_1b2fa0 *q;

    q = arg0->f144;
    temp_s2 = arg1->f52;
    n = 0;
    if (q != 0) {
        n = q->count;
    }
    if (n > 8) {
        n = 8;
    }
    for (i = 0; i < n; i++) {
        FUN_001b4090((T_1b2fa0 *)arg0, i, FUN_001b0ea0(temp_s2, arg0->f144->data[i]));
    }
}

void FUN_001b42c0(TravFlattenView *self, int root) {
    int saved[32];
    TravFunctionTable *table = ((TravFunctionTable *)DAT_00562640[0]);
    int meta = (int)g_igGeometry_metaObject[0];
    int n = igMetaObject_CountTree(meta);
    int i;
    for (i = 0; i < n; i++) {
        TravObject *m = ((TravObject *)FUN_002fe300(meta, i));
        saved[i] = table->_data[m->_id];
        igTraversal_RegisterFunction((struct L_1e06c0 *)table, (struct X_1e06c0 *)m, (void *)((void *)FUN_001b3ad0));
    }
    DAT_005625f0 = self;
    clearRetained(self->_a);
    clearRetained(self->_b);
    igTraversal_TraverseChildren(root, (S_1e07a0 *)self);
    for (i = 0; i < n; i++) {
        igTraversal_RegisterFunction((struct L_1e06c0 *)table, (struct X_1e06c0 *)(((TravObject *)FUN_002fe300(meta, i))), (void *)((void *)saved[i]));
    }
}

void FUN_001b4500(struct O4500 *o, struct S4500 *s, int b) {
    s = o->s;
    if (s != 0) {
        if (s->k == 1) { o->x = s->firstX; o->y = s->firstY; o->z = s->firstZ; o->w = 0x3F800000; return; }
        o->x = s->secondX; o->y = s->secondY; o->z = s->secondZ; o->w = 0;
    }
}

int FUN_001b4bb0(igCommonTraversal *arg0, int arg1) {
    igAttrStackManager *b;
    igAttrStack *l;
    int v;

    b = (igAttrStackManager *)arg0->_attrStack;
    l = ((igAttrStack **)((igAttrStackList *)b->_attrStacks)->_data)[((int *)b->_attrStackIndexTable)[g_igModelViewMatrixAttr_metaObject[0]->_id]];
    if (l->_count == 0) {
        v = 0;
    } else {
        v = *(int *)(l->_data + ((l->_count - 1) * 4));
    }
    DAT_00562638[0]->vX(arg1, v);
    return 0;
}

void FUN_001b68b0(int arg0) {
    FUN_001b68c0(((TravFunctionTable *)DAT_00562640[0]), (void *)arg0);
}

void FUN_001b68c0(void *self, void *meta) {
    FUN_001e02f0((int)(self), (int)(meta));
    if (FUN_002fe290(meta, ((int)igNode_GetMetaObject())) != 0) {
        NodeProcTable t = DAT_0048d8f0;
        int i;
        t.e[0].meta = (int)g_igActor_metaObject[0];
        t.e[1].meta = (int)g_igProjectiveShadowShader_metaObject[0];
        t.e[2].meta = DAT_005615d0;
        t.e[3].meta = DAT_00561bd8[0];
        t.e[4].meta = (int)g_igSegment_metaObject[0];
        t.e[5].meta = (int)g_igEnvironmentMapShader2_metaObject[0];
        t.e[6].meta = DAT_00561920;
        t.e[7].meta = DAT_00561908;
        t.e[8].meta = DAT_00561910;
        t.e[9].meta = DAT_00561860[0];
        t.e[10].meta = DAT_00561868;
        t.e[11].meta = DAT_00561e98[0];
        t.e[12].meta = DAT_00561ee8[0];
        t.e[13].meta = g_unlinkedTransformClass_metaObject[0];
        t.e[14].meta = DAT_00561878;
        t.e[15].meta = DAT_00561870;
        t.e[16].meta = (int)g_igLod_metaObject[0];
        t.e[17].meta = (int)g_igLightStateSet_metaObject[0];
        t.e[18].meta = (int)g_igLightSet_metaObject[0];
        t.e[19].meta = (int)g_igGeometry_metaObject[0];
        t.e[20].meta = (int)g_igPlanarShadowShader_metaObject[0];
        t.e[21].meta = DAT_00561578[0];
        t.e[22].meta = DAT_00561570;
        t.e[23].meta = (int)g_igBlendMatrixSelect_metaObject[0];
        t.e[24].meta = (int)g_igOverrideAttrSet_metaObject[0];
        t.e[25].meta = (int)g_igAttrSet_metaObject[0];
        t.e[26].meta = (int)g_igTransform_metaObject[0];
        t.e[27].meta = (int)g_igBillboard_metaObject[0];
        t.e[28].meta = (int)g_igSwitch_metaObject[0];
        t.e[29].meta = (int)g_igTransformRecorder_metaObject[0];
        t.e[30].meta = DAT_005612d8[0];
        t.e[31].meta = DAT_00561ca0[0];
        t.e[32].meta = (int)g_igModelViewMatrixBoneSelect_metaObject[0];
        t.e[33].meta = DAT_005612e0;
        for (i = 0; i < 34; i++) {
            NodeProcEntry *e = &t.e[i];
            if (e->meta != 0 && FUN_002fe290(meta, e->meta) != 0) {
                igTraversal_RegisterFunction((struct L_1e06c0 *)self, (struct X_1e06c0 *)meta, (void *)e->proc);
                return;
            }
        }
    }
}

void Gap__Sg__igCommonTraversal__vfunc_09(igCommonTraversal *arg0, int arg1) {
    igObject *s0;
    igObject *a0;

    Gap__Sg__igTraversal__vfunc_09((A_1e0380 *)arg0, arg1);
    if (arg1 == 0) {
        s0 = (igObject *)((TravFunctionTable *)DAT_00562640[0]);
        if (s0 != 0) {
            s0->_refCount = s0->_refCount + 1;
        }
        a0 = (igObject *)arg0->_travProcs;
        if (a0 != 0) {
            --a0->_refCount;
            if (((unsigned long long)(long long)a0->_refCount & 0x7fffffULL) == 0) {
                igObject_Destroy((void *)a0);
            }
        }
        arg0->_travProcs = (int)s0;
        ((C_1b2fa0 *)arg0->_matrixOptimization)->vX(0);
        *(char *)(arg0->_normalizeNormalsEnable + 12) = 1;
    }
}

void FUN_001b6be0(void) {
    *(int *)0x562640 = FUN_0019a6e0(Memory_GetAllocatorBySelector(*(int *)0x587038));
    FUN_0013b110();
    FUN_00132a00();
    FUN_001357e0();
    FUN_00130cf0();
    FUN_001318f0();
    FUN_00130830();
    FUN_00130a70();
}

void FUN_001b6c50(void) {
    void *temp_a0;

    temp_a0 = *(void **)0x562640;
    if (temp_a0 != 0) {
        *(int *)((char *)temp_a0 + 4) = (int) (*(int *)((char *)temp_a0 + 4) - 1);
        if (((unsigned long long) ((long long) *(int *)((char *)temp_a0 + 4) << 0x29) >> 0x29) == 0) {
            igObject_Destroy((void *)temp_a0);
        }
    }
}

