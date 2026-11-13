int Gap__Sg__igActor__vfunc_37(ActorView *o0, ActorTraversal *t0) {
    ActorAnimationHolder *holder;
    int r;
    ActorCountedList *nodes;
    float *world;
    float *bones;
    ActorView *o;
    ActorTraversal *t;
    int status;
    char *rootBone;
    o = (ActorView *)(int)o0;
    t = (ActorTraversal *)(int)t0;
    if (o->_animate) {
        ActorAttrState *st = t->_state;
        Matrix44_Copy(o->_world, lastEntry(st->_stacks->_data[st->_slotOfIndex[((ActorMeta * *)g_igModelViewMatrixAttr_metaObject)[0]->_offset]])->_matrix);
        Matrix44_Copy(o->_view, t->_view);
        if (o->_nodes->_count == 0 && o->_forced == 0) {
            o->_useCached = 0;
        } else {
            o->_useCached = 1;
        }
        {
            world = o->_world;
            rootBone = (char *)o + g_igActor_transformMetaField[0]->_offset;
            FUN_001904f0(bonesOf(o), rootBone, world);
        }
        status = o->_animationState->update(t, o);
        if (o->_useCached == 0) {
            if (o->_animationState->isReady() != 0) {
                goto skip;
            }
            o->_animationState->setReady(1);
        }
        {
            holder = o->_animationState->_holder;
            nodes = o->_nodes;
            bones = bonesOf(o);
            holder->updateNodes(t, o, status, bones, blendsOf(o), nodes);
        }
    }
skip:
    if (o->_traverse) {
        FUN_001b8a20((Src *)o, (Dst *)t);
        if (FUN_001b8a10((int *)&o->_children) != 0) {
            r = FUN_001af620((igAppearanceView *)(((void *)FUN_001b8a00((int *)&o->_children))), (void *)t);
        } else {
            r = 0;
        }
        FUN_001b89b0((void *)o, (igCommonTraversal *)t);
        return r;
    }
    return 0;
}

void FUN_001b89b0(void *arg0, igCommonTraversal *arg1) {
    igDataList *temp_a0;
    igDataList *temp_a0_2;
    igDataList *temp_a0_3;

    temp_a0 = (igDataList *)arg1->_boneMatrixPaletteList;
    List_RemoveWordAt(temp_a0, temp_a0->_count - 1);
    temp_a0_2 = (igDataList *)arg1->_blendMatrixPaletteList;
    List_RemoveWordAt(temp_a0_2, temp_a0_2->_count - 1);
    temp_a0_3 = (igDataList *)arg1->_blendMatrixPaletteLengths;
    List_RemoveWordAt(temp_a0_3, temp_a0_3->_count - 1);
}

int FUN_001b8a00(int *p)
{
    return *(int *)((char *)p + 0);
}

int FUN_001b8a10(int *p)
{
    return *(int *)((char *)p + 0);
}

void FUN_001b8a20(Src *arg0, Dst *arg1) {
    int a, b, c1, c2, c, c3;
    List_1b8a20 *l1; List_1b8a20 *l2; List_1b8a20 *l3;
    if (arg0->f121 != 0) a = arg0->f36; else a = arg0->f32->g108();
    l1 = arg1->l248;
    c1 = l1->count;
    if (c1 < l1->cap) l1->count = l1->getCount() + 1;
    else List_Resize((void *)l1, c1 + 1, 4);
    l1->items[c1] = a;
    c = ((Sub *)((Mid *)arg0->f32)->f12)->g100();
    if (arg0->f121 != 0) b = arg0->f40; else b = arg0->f32->g116();
    l2 = arg1->l252;
    c2 = l2->count;
    if (c2 < l2->cap) l2->count = l2->getCount() + 1;
    else List_Resize((void *)l2, c2 + 1, 4);
    l2->items[c2] = b;
    l3 = arg1->l256;
    c3 = l3->count;
    if (c3 < l3->cap) l3->count = l3->getCount() + 1;
    else List_Resize((void *)l3, c3 + 1, 4);
    l3->items[c3] = c;
}

int FUN_001b8ba0(void *arg0, int arg1) {
    int sp40[16];
    int *temp_s2;
    int temp_v0;
    void *temp_a1;
    void *temp_a2;

    temp_a2 = (void *)(*(int *)((char *)(arg0) + 52));
    temp_a1 = (void *)(*(int *)(*(int *)((char *)(*(int *)((char *)(temp_a2) + 16)) + 16) + (*(int *)(*(int *)((char *)(temp_a2) + 68) + (*(int *)((char *)(((void * *)g_igModelViewMatrixAttr_metaObject)[0]) + 8) * 4)) * 4)));
    temp_v0 = *(int *)((char *)(temp_a1) + 8);
    if (temp_v0 != 0) {
        temp_s2 = (int *)(*(int *)(*(int *)((char *)(temp_a1) + 16) + ((temp_v0 - 1) * 4)) + 0xC);
        FUN_001d0130((SceneTransformNode *)arg1, (SceneRenderer *)arg0, (SceneMatrix *)temp_s2, ((DW4VC_104_2 *)(((char *)(arg0) + 0)))->vX((int)(temp_a1), (int)(temp_a2)));
    } else {
        igMatrix44f_SetIdentity(sp40, temp_a1, temp_a2);
        FUN_001d0130((SceneTransformNode *)arg1, (SceneRenderer *)arg0, (SceneMatrix *)sp40, ((DW4VC_104_0 *)(((char *)(arg0) + 0)))->vX());
    }
    return 0;
}

void FUN_001b8c80(void *self, int arg1) {
    int arg0 = (int)self;
    int temp_v0;
    temp_v0 = (int)igTransform_PushMatrix((TransformView *)arg1, (CommonTraversalView *)arg0);
    Matrix44_Copy(arg1 + *(int *)((char *)(DAT_00561928[0]) + 8), temp_v0);
    igTransform_TraverseChildrenAndPopMatrix((float *)temp_v0, (igTransform *)arg1, (igCommonTraversal *)arg0);
}

void FUN_001b8cf0(igCommonTraversal *arg0, char *arg1) {
    igAttrStackManager *a2;
    igAttrStack *a0;
    int n;
    int v;
    int a1;
    int k;
    char *dst;
    ((VC_156b *)arg1)->vX(((VC_104a *)arg0)->vX());
    a2 = (igAttrStackManager *)arg0->_attrStack;
    a0 = ((igAttrStack **)((igAttrStackList *)a2->_attrStacks)->_data)[((int *)a2->_attrStackIndexTable)[((igMetaObject *)((int *)g_igModelViewMatrixAttr_metaObject)[0])->_id]];
    n = a0->_count;
    a1 = 0;
    if (n == 0) { v = 0; } else { k = n - 1; v = ((int *)a0->_data)[k]; }
    if (v != 0) { a1 = v + 12; }
    dst = arg1 + ((igMetaObject *)DAT_00561918[0])->_id;
    if (a1 != 0) {
        Matrix44_Copy(dst, a1, a2);
    } else {
        igMatrix44f_SetIdentity(dst, a1, a2);
    }
    FUN_001b8ba0((void *)arg0, (int)arg1);
}

int FUN_001b8de0(Dst_1b8de0 *arg0, Src_1b8de0 *arg1) {
    int s4, n, i;
    arg1->vX();
    s4 = arg0->f52;
    n = arg1->list->count;
    for (i = 0; i < n; i++) {
        int a = FUN_001ce640((void *)arg1->list->data[i], 0);
        LB *lb = arg0->l72;
        int b = a + ((G_1b8de0 * *)DAT_00561918)[0]->f8;
        V128_1b8de0 *o;
        if (lb->count >= lb->cap) igObjectPool_Grow((List_1dca40 *)lb, (Obj_1dca40 * (*)(int))((void *)&FUN_001356b0));
        o = lb->data[lb->count++];
        o->vY(b);
        FUN_001b1030((igAttrStackManager *)s4, (igAttr *)o);
        FUN_001b8cf0((igCommonTraversal *)arg0, (char *)a);
        FUN_001b1100((struct A_1b1100 *)s4, (struct B_1b1100 *)o);
    }
    return 0;
}

int FUN_001b8f20(C_1b8f20 *arg0, D *arg1) {
    char sp80[64];
    char sp40[64];
    X_1b8f20 *x;
    Arr *a;
    int v;
    LB_1b8f20 *lb;
    RC *o;
    RC *old;
    int r;
    int n;
    char *s0;
    x = arg0->x;
    a = (Arr *)x->a16->data[x->a68[((G_1b8f20 * *)g_igModelViewMatrixAttr_metaObject)[0]->f8]];
    s0 = arg0->v164;
    n = a->count;
    if (n == 0) v = 0; else v = *(int *)((char *)a->data + (n - 1) * 4);
    if (v != 0) {
        FUN_001904f0(sp40, v + 12, s0);
        FUN_001b1aa0(arg1, sp80, sp40, s0);
    } else {
        FUN_001b1aa0(arg1, sp80, ((char *)DAT_004e0ef0), s0);
    }
    lb = arg0->l72;
    if (lb->count >= lb->cap) igObjectPool_Grow((List_1dca40 *)lb, (Obj_1dca40 * (*)(int))((void *)&FUN_001356b0));
    o = lb->data[lb->count++];
    if (o != 0) o->refs++;
    old = arg1->f60;
    if (old != 0) {
        old->refs--;
        if (!(old->refs & 0x7fffff)) igObject_Destroy((void *)old);
    }
    arg1->f60 = o;
    FUN_001904f0((char *)o + 12, sp80, arg0->v100);
    FUN_001b1030((igAttrStackManager *)arg0->x, (igAttr *)o);
    r = igTraversal_TraverseChildren((int)arg0, (S_1e07a0 *)arg1);
    FUN_001b1100((struct A_1b1100 *)arg0->x, (struct B_1b1100 *)o);
    if (r == 2) return 2;
    return 0;
}

int igCommonTraversal_TraverseOverrideAttrSet(igCommonTraversal *self, igOverrideAttrSet *set) {
    igAttrStackManager *manager;
    int result;
    igAttr **p;
    int n;
    int slot;
    igAttrList *attrs;
    igAttr **end;
    int popSlot;
    AttrObjectStack *stack;
    AttrObjectStack *popStack;
    igAttr **begin;
    attrs = (igAttrList *)set->_attributes;
    manager = (igAttrStackManager *)self->_attrStack;
    p = (igAttr **)attrs->_data;
    end = p + attrs->_count;
    for (; p < end; p++) {
        igAttr *attr = *p;
        slot = attr->_cachedUnitID + ((int *)manager->_attrStackIndexTable)[attr->_cachedAttrIndex];
        stack = ((AttrObjectStackList *)manager->_attrStacks)->_data[slot];
        if (stack->_cachedOverride < 0) {
            stack->_cachedOverride = stack->_count;
        }
        {
            igObject *pushed = attr;
            n = stack->getCount();
            if (n < stack->_capacity) {
                stack->_count++;
            } else {
                List_Resize(stack, n + 1, 4);
            }
            stack->set(n, &pushed);
        }
        igAttrStackManager_MarkStackChanged((A_1b1490 *)manager, (B_1b1490 *)stack, slot);
    }
    if (set->_trigger) {
        FUN_001b0440(self->_attrStack, self->_flushedAttrs);
        List_AppendWords(*(int *)((char *)((igSorter *)self->_sorter)->_dlist + 12), ((igObjectList *)self->_flushedAttrs)->_count, ((igObjectList *)self->_flushedAttrs)->_data);
    }
    result = igTraversal_TraverseChildren((int)self, (S_1e07a0 *)set);
    if (p != 0) {
        begin = (igAttr **)attrs->_data;
        for (p--; p >= begin; p--) {
            igAttr *attr = *p;
            igObject *top;
            void (*pop)(igObject *, int);
            popSlot = attr->_cachedUnitID + ((int *)manager->_attrStackIndexTable)[attr->_cachedAttrIndex];
            popStack = ((AttrObjectStackList *)manager->_attrStacks)->_data[popSlot];
            top = popStack->get(popStack->_count - 1);
            pop = popStack->_popProc;
            if (pop != 0 && top == attr) {
                pop(top, manager->_popProcData);
            }
            popStack->_count--;
            if (popStack->_count == popStack->_cachedOverride) {
                popStack->_cachedOverride = -1;
            }
            igAttrStackManager_MarkStackChanged((A_1b1490 *)manager, (B_1b1490 *)popStack, popSlot);
        }
    }
    if (result == 2) {
        return 2;
    }
    return 0;
}

int igCommonTraversal_TraverseAttrSet(igCommonTraversal *self, igAttrSet *set) {
    igAttrStackManager *manager;
    int result;
    igAttr **p;
    int n;
    int slot;
    igAttrList *attrs;
    igAttr **end;
    int popSlot;
    AttrObjectStack *stack;
    AttrObjectStack *popStack;
    igAttr **begin;
    attrs = (igAttrList *)set->_attributes;
    manager = (igAttrStackManager *)self->_attrStack;
    p = (igAttr **)attrs->_data;
    end = p + attrs->_count;
    for (; p < end; p++) {
        igAttr *attr = *p;
        slot = attr->_cachedUnitID + ((int *)manager->_attrStackIndexTable)[attr->_cachedAttrIndex];
        stack = ((AttrObjectStackList *)manager->_attrStacks)->_data[slot];
        {
            igObject *pushed = attr;
            n = stack->getCount();
            if (n < stack->_capacity) {
                stack->_count = stack->_count + 1;
            } else {
                List_Resize(stack, n + 1, 4);
            }
            stack->set(n, &pushed);
        }
        igAttrStackManager_MarkStackChanged((A_1b1490 *)manager, (B_1b1490 *)stack, slot);
    }
    if (set->_trigger != 0) {
        FUN_001b0440(self->_attrStack, self->_flushedAttrs);
        List_AppendWords(*(int *)((char *)((igSorter *)self->_sorter)->_dlist + 12), ((igObjectList *)self->_flushedAttrs)->_count, ((igObjectList *)self->_flushedAttrs)->_data);
    }
    result = igTraversal_TraverseChildren((int)self, (S_1e07a0 *)set);
    if (p != 0) {
        begin = (igAttr **)attrs->_data;
        for (p--; p >= begin; p--) {
            igAttr *attr = *p;
            igObject *top;
            void (*pop)(igObject *, int);
            popSlot = attr->_cachedUnitID + ((int *)manager->_attrStackIndexTable)[attr->_cachedAttrIndex];
            popStack = ((AttrObjectStackList *)manager->_attrStacks)->_data[popSlot];
            top = popStack->get(popStack->_count - 1);
            pop = popStack->_popProc;
            if (pop != 0) {
                pop(top, manager->_popProcData);
            }
            popStack->_count = popStack->_count - 1;
            igAttrStackManager_MarkStackChanged((A_1b1490 *)manager, (B_1b1490 *)popStack, popSlot);
        }
    }
    if (result == 2) {
        return 2;
    }
    return 0;
}

int FUN_001b99d0(DrawTraversalView *o, SwitchGroupView *g) {
    char m[64];
    RefList *set;
    int n;
    int nChild;
    void *src;
    char *base;
    int j;
    int i;
    ModelViewAttrView *attr;
    int count;
    RefList *set2;
    nChild = g->_children != 0 ? g->_children->_count : 0;
    if (nChild == 0) {
        return 0;
    }
        base = topOf(stackOf(((TraversalStateHolder *)o)->_state))->_matrix;
    FUN_001b1030((igAttrStackManager *)o->_state, (igAttr *)o->_baseAttr);
    count = g->_attrSets->_count;
    for (i = 0; i < count; i++) {
        if (FUN_001d8330((void *)g, i) == 0) {
            continue;
        }
        attr = ((ModelViewAttrView *)FUN_001d8310((void *)g, i));
        if (attr != 0) {
            src = ((void *)FUN_001d82f0((void *)g, i));
            if (base != 0) {
                igMatrix44f_SetIdentity(m);
                FUN_001904f0(m, src, base);
                attr->setMatrix(m);
            } else {
                attr->setMatrix(src);
            }
            FUN_001b1030((igAttrStackManager *)o->_state, (igAttr *)attr);
        }
        set = g->_attrSets->_data[i];
        n = set->_count;
        for (j = 0; j < n; j++) {
            FUN_001b1030((igAttrStackManager *)o->_state, (igAttr *)set->_data[j]);
        }
        switch (g->_mode) {
        case 0:
            FUN_001e04c0((S_1e04c0 *)o, (V_1e04c0 *)(g->_children->_data[i % nChild]));
            break;
        case 1:
            for (j = 0; j < nChild; j++) {
                FUN_001e04c0((S_1e04c0 *)o, (V_1e04c0 *)g->_children->_data[j]);
            }
            break;
        }
        if (!g->_nested) {
            for (j = n - 1; j >= 0; j--) {
                FUN_001b1100((struct A_1b1100 *)o->_state, (struct B_1b1100 *)set->_data[j]);
            }
            if (attr != 0) {
                FUN_001b1100((struct A_1b1100 *)o->_state, (struct B_1b1100 *)attr);
            }
        }
    }
    if (g->_nested) {
        for (i = count - 1; i >= 0; i--) {
            if (FUN_001d8330((void *)g, i) != 0) {
                set2 = g->_attrSets->_data[i];
                for (j = set2->_count - 1; j >= 0; j--) {
                    FUN_001b1100((struct A_1b1100 *)o->_state, (struct B_1b1100 *)set2->_data[j]);
                }
                attr = ((ModelViewAttrView *)FUN_001d8310((void *)g, i));
                if (attr != 0) {
                    FUN_001b1100((struct A_1b1100 *)o->_state, (struct B_1b1100 *)attr);
                }
            }
        }
    }
    FUN_001b1100((struct A_1b1100 *)o->_state, (struct B_1b1100 *)o->_baseAttr);
    return 0;
}

void FUN_001b9d40(int arg0, int arg1) {
    igTransform_TraverseChildrenAndPopMatrix(igTransform_PushMatrix((TransformView *)arg1, (CommonTraversalView *)arg0), (igTransform *)arg1, (igCommonTraversal *)arg0);
}

int FUN_001b9d90(LightTraversalView *o, LightSceneView *scene) {
    LightVec3 position;
    LightVec3 direction;
    float matrix[16];
    int i;
    FUN_001dc400((igSorter *)o->_collector, (igGroup *)scene, (igAttrStackManager *)o->_state);
    FUN_001904f0(matrix, currentEntry(stackOf_1b9d90(o->_state, ((CullMeta * *)g_igModelViewMatrixAttr_metaObject)[0]))->_matrix, o->_view);
    for (i = 0; i < scene->_lights->_count; i++) {
        LightView *light = scene->_lights->_data[i];
        Vec3f_TransformProjective(&position, (char *)light + DAT_0055f0a0[0]->_offset, matrix);
        light->_worldPosition.x = position.x;
        light->_worldPosition.y = position.y;
        light->_worldPosition.z = position.z;
        if (light->_type == 0 || light->_type == 2) {
            Vec3f_TransformDirection(&direction, (char *)light + g_igLightAttr_directionMetaField[0]->_offset, matrix);
            light->_worldDirection.x = direction.x;
            light->_worldDirection.y = direction.y;
            light->_worldDirection.z = direction.z;
        }
    }
    return 0;
}

int FUN_001b9f00(igCompileTraversal *arg0, igAttrSet *arg1) {
    int temp_v0;
    igSorter *temp_s0;
    igAttrList *temp_v1;
    temp_s0 = (igSorter *)arg0->_sorter;
    FUN_001d9bb0((void *)temp_s0, arg0->_attrStack);
    temp_v0 = FUN_001be190(arg1, arg0);
    if (temp_v0 == 0) {
        temp_v1 = (igAttrList *)arg1->_attributes;
        List_AppendWords(*(int *)((char *)(temp_s0->_dlist) + 12), temp_v1->_count, temp_v1->_data);
        return 0;
    }
    if (temp_v0 == 4 || temp_v0 == 1) {
        return 0;
    }
    if (igTraversal_TraverseChildren((int)arg0, (S_1e07a0 *)arg1) == 2) {
        return 2;
    }
    return 0;
}

int FUN_001b9fc0(struct A_1b9fc0 *arg0, struct B_1b9fc0 *arg1) {
    int s1;
    int s0;

    s0 = arg1->f32->n;
    for (s1 = 0; s1 < s0; s1++) {
        FUN_001b06f0(arg0->f52, arg1->f32->data[s1], 0);
    }
    igTraversal_TraverseChildren((int)arg0, (S_1e07a0 *)arg1);
    for (s0 = s0 - 1; s0 >= 0; s0--) {
        igAttrStackManager_PopLightStateAttr((igAttrStackManager *)arg0->f52, (LightStateAttrView *)arg1->f32->data[s0], 0);
    }
    return 0;
}

int FUN_001ba080(CullTraversalView *o, CullNodeView *node) {
    CullVec3 out;
    CullVec3 center;
    CullAttrState *st;
    CullMatrixStack *stack;
    int child;
    center.x = node->_center.x;
    center.y = node->_center.y;
    center.z = node->_center.z;
    st = o->_state;
    stack = st->_stacks->_data[st->_slotOfIndex[((CullMeta * *)g_igModelViewMatrixAttr_metaObject)[0]->_index]];
    Vec3f_TransformProjective(&out, &center, currentEntry_1ba080(stack)->_matrix);
    child = ((int)FUN_001d0520((RangeLookup *)node, out.x * out.x + out.y * out.y + out.z * out.z));
    if (child != 0) {
        if (FUN_001e04c0((S_1e04c0 *)o, (V_1e04c0 *)child) == 2) return 2;
        return 0;
    }
    return 0;
}

int FUN_001ba1a0(int a0, int arg1) {
    S_1ba1a0 *arg0 = (S_1ba1a0 *)a0;
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)arg0->f52, (igAttr *)arg0->f232);
    FUN_001b3ff0((void *)arg1, (int)arg0);
    igAttrStackManager_PopOverrideAttr((struct A_1b13d0 *)arg0->f52, (struct B_1b13d0 *)arg0->f232);
    return 0;
}

int FUN_001ba200(int arg0_, int arg1) {
    T_1ba200 *arg0 = (T_1ba200 *)arg0_;
    FUN_001b1030((igAttrStackManager *)arg0->f34, (igAttr *)arg0->fe8);
    FUN_001b4c40(arg1, arg0);
    FUN_001b1100((struct A_1b1100 *)arg0->f34, (struct B_1b1100 *)arg0->fe8);
    return 0;
}

int FUN_001ba650(int a0, int arg1) {
    S_1ba650 *arg0 = (S_1ba650 *)a0;
    FUN_001b1030((igAttrStackManager *)arg0->f52, (igAttr *)arg0->f232);
    FUN_001d3e20((igPlanarShadowShader *)arg1, (igCommonTraversal *)arg0);
    FUN_001b1100((struct A_1b1100 *)arg0->f52, (struct B_1b1100 *)arg0->f232);
    return 0;
}

int FUN_001ba6b0(char *arg0, struct S_1d6190 *arg1) {
    FUN_001d6190(arg1, arg0);
    return 0;
}

int igCommonTraversal_TraverseProjectiveShadowShader(igCommonTraversal *self, igProjectiveShadowShader *shader) {
    igObject *pushed;
    int n;
    igAttrStackManager *manager;
    AttrObjectStack *stack;
    int slot;
    igAttr *attr;
    igObject *top;

    attr = (igAttr *)self->_matrixOptimization;
    manager = (igAttrStackManager *)self->_attrStack;
    slot = attr->_cachedUnitID + ((int *)manager->_attrStackIndexTable)[attr->_cachedAttrIndex];
    stack = ((AttrObjectStackList *)manager->_attrStacks)->_data[slot];
    pushed = attr;
    n = stack->getCount();
    if (n < stack->_capacity) {
        stack->_count = stack->_count + 1;
    } else {
        List_Resize(stack, n + 1, 4);
    }
    stack->set(n, &pushed);
    igAttrStackManager_MarkStackChanged((A_1b1490 *)manager, (B_1b1490 *)stack, slot);
    FUN_001d7b70((S0_1d7b70 *)shader, (S1_1d7b70 *)self);
    attr = (igAttr *)self->_matrixOptimization;
    manager = (igAttrStackManager *)self->_attrStack;
    slot = attr->_cachedUnitID + ((int *)manager->_attrStackIndexTable)[attr->_cachedAttrIndex];
    stack = ((AttrObjectStackList *)manager->_attrStacks)->_data[slot];
    n = stack->_count - 1;
    top = stack->_data[n];
    if (stack->_popProc != 0) {
        stack->_popProc(top, manager->_popProcData);
    }
    stack->_count = stack->_count - 1;
    igAttrStackManager_MarkStackChanged((A_1b1490 *)manager, (B_1b1490 *)stack, slot);
    return 0;
}

int FUN_001ba850(A1_1c03a0 *arg0, DepthOfFieldNode *arg1) {
    FUN_001c03a0(arg1, arg0);
    return 0;
}

int FUN_001ba880(igCommonTraversal *arg0, VC1 *arg1) {
    int sp30[16];
    igAttrStack *l;
    int i, k, v;
    l = ((igAttrStack **)((igAttrStackList *)((igAttrStackManager *)arg0->_attrStack)->_attrStacks)->_data)[((int *)((igAttrStackManager *)arg0->_attrStack)->_attrStackIndexTable)[g_igModelViewMatrixAttr_metaObject[0]->_id]];
    i = l->_cachedOverride;
    if (i >= 0) {
        v = ((int *)l->_data)[i];
    } else {
        i = l->_count;
        if (i != 0) {
            k = i - 1;
            v = ((int *)l->_data)[k];
        } else {
            v = l->_default;
        }
    }
    FUN_001904f0(sp30, v + 0xC, arg0->_viewMatInv);
    ((VC0 *)arg1)->vX(sp30);
    l = ((igAttrStack **)((igAttrStackList *)((igAttrStackManager *)arg0->_attrStack)->_attrStacks)->_data)[((int *)((igAttrStackManager *)arg0->_attrStack)->_attrStackIndexTable)[g_igModelViewMatrixAttr_metaObject[0]->_id]];
    i = l->_cachedOverride;
    if (i >= 0) {
        v = ((int *)l->_data)[i];
    } else {
        i = l->_count;
        if (i != 0) {
            k = i - 1;
            v = ((int *)l->_data)[k];
        } else {
            v = l->_default;
        }
    }
    arg1->vX(v + 0xC);
    if (igTraversal_TraverseChildren((int)arg0, (S_1e07a0 *)arg1) == 2) {
        return 2;
    }
    return 0;
}

