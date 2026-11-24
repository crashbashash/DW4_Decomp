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
        igMatrix44f_Copy(o->_world, lastEntry(st->_stacks->_data[st->_slotOfIndex[((ActorMeta *)Gap::Attrs::igModelViewMatrixAttr::getClassMeta())->_offset]])->_matrix);
        igMatrix44f_Copy(o->_view, t->_view);
        if (o->_nodes->_count == 0 && o->_forced == 0) {
            o->_useCached = 0;
        } else {
            o->_useCached = 1;
        }
        {
            world = o->_world;
            rootBone = (char *)o + g_igActor_transformMetaField->_offset;
            igMatrix44f_Multiply(bonesOf(o), (const float *)rootBone, (const float *)world);
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
    else ((Gap::Core::igDataList *)l1)->resizeAndSetCount(c1 + 1, 4);
    l1->items[c1] = a;
    c = ((Sub *)((Mid *)arg0->f32)->f12)->g100();
    if (arg0->f121 != 0) b = arg0->f40; else b = arg0->f32->g116();
    l2 = arg1->l252;
    c2 = l2->count;
    if (c2 < l2->cap) l2->count = l2->getCount() + 1;
    else ((Gap::Core::igDataList *)l2)->resizeAndSetCount(c2 + 1, 4);
    l2->items[c2] = b;
    l3 = arg1->l256;
    c3 = l3->count;
    if (c3 < l3->cap) l3->count = l3->getCount() + 1;
    else ((Gap::Core::igDataList *)l3)->resizeAndSetCount(c3 + 1, 4);
    l3->items[c3] = c;
}

int igCommonTraversal_TraverseJointTransform(igCommonTraversal *self, int arg1) {
    int sp40[16];
    int *temp_s2;
    int temp_v0;
    void *temp_a1;
    void *temp_a2;

    temp_a2 = (void *)(self->_attrStack);
    temp_a1 = (void *)(*(int *)(*(int *)((char *)(*(int *)((char *)(temp_a2) + 16)) + 16) + (*(int *)(*(int *)((char *)(temp_a2) + 68) + (*(int *)((char *)(((void *)Gap::Attrs::igModelViewMatrixAttr::getClassMeta())) + 8) * 4)) * 4)));
    temp_v0 = *(int *)((char *)(temp_a1) + 8);
    if (temp_v0 != 0) {
        temp_s2 = (int *)(*(int *)(*(int *)((char *)(temp_a1) + 16) + ((temp_v0 - 1) * 4)) + 0xC);
        FUN_001d0130((SceneTransformNode *)arg1, (SceneRenderer *)self, (SceneMatrix *)temp_s2, ((DW4VC_104_2 *)(((char *)(self) + 0)))->vX((int)(temp_a1), (int)(temp_a2)));
    } else {
        igMatrix44f_SetIdentity((float *)sp40);
        FUN_001d0130((SceneTransformNode *)arg1, (SceneRenderer *)self, (SceneMatrix *)sp40, ((DW4VC_104_0 *)(((char *)(self) + 0)))->vX());
    }
    return 0;
}

void FUN_001b8c80(void *self, int arg1) {
    int arg0 = (int)self;
    int temp_v0;
    temp_v0 = (int)igTransform_PushMatrix((TransformView *)arg1, (CommonTraversalView *)arg0);
    igMatrix44f_Copy((float *)(arg1 + *(int *)((char *)(DAT_00561928[0]) + 8)), (const float *)temp_v0);
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
    a0 = ((igAttrStack **)((igAttrStackList *)a2->_attrStacks)->_data)[((int *)a2->_attrStackIndexTable)[((igMetaObject *)((int)Gap::Attrs::igModelViewMatrixAttr::getClassMeta()))->_id]];
    n = a0->_count;
    a1 = 0;
    if (n == 0) { v = 0; } else { k = n - 1; v = ((int *)a0->_data)[k]; }
    if (v != 0) { a1 = v + 12; }
    dst = arg1 + ((igMetaObject *)DAT_00561918[0])->_id;
    if (a1 != 0) {
        igMatrix44f_Copy((float *)dst, (const float *)a1);
    } else {
        igMatrix44f_SetIdentity((float *)dst);
    }
    igCommonTraversal_TraverseJointTransform((igCommonTraversal *)arg0, (int)arg1);
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
        if (lb->count >= lb->cap) igObjectPool_Grow((igObjectPool *)lb, (igObject *(*)(int))((void *)&Gap::Attrs::igModelViewMatrixAttr::_instantiateFromPool));
        o = lb->data[lb->count++];
        o->vY(b);
        ((Gap::Sg::igAttrStackManager *)s4)->pushAttr((Gap::Attrs::igAttr *)o);
        FUN_001b8cf0((igCommonTraversal *)arg0, (char *)a);
        ((Gap::Sg::igAttrStackManager *)s4)->popAttr((Gap::Attrs::igAttr *)o);
    }
    return 0;
}

int igCommonTraversal_TraverseBillboard(C_1b8f20 *arg0, D *arg1) {
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
    a = (Arr *)x->a16->data[x->a68[((G_1b8f20 *)Gap::Attrs::igModelViewMatrixAttr::getClassMeta())->f8]];
    s0 = arg0->v164;
    n = a->count;
    if (n == 0) v = 0; else v = *(int *)((char *)a->data + (n - 1) * 4);
    if (v != 0) {
        igMatrix44f_Multiply((float *)sp40, (const float *)(v + 12), (const float *)s0);
        ((Gap::Sg::igBillboard *)arg1)->computeTransform((igMatrix44f *)sp80, (const igMatrix44f *)sp40, (const igMatrix44f *)s0);
    } else {
        ((Gap::Sg::igBillboard *)arg1)->computeTransform((igMatrix44f *)sp80, (const igMatrix44f *)&g_matrix44Identity, (const igMatrix44f *)s0);
    }
    lb = arg0->l72;
    if (lb->count >= lb->cap) igObjectPool_Grow((igObjectPool *)lb, (igObject *(*)(int))((void *)&Gap::Attrs::igModelViewMatrixAttr::_instantiateFromPool));
    o = lb->data[lb->count++];
    if (o != 0) o->refs++;
    old = arg1->f60;
    if (old != 0) {
        old->refs--;
        if (!(old->refs & 0x7fffff)) igObject_Destroy((igObject *)old);
    }
    arg1->f60 = o;
    igMatrix44f_Multiply((float *)((char *)o + 12), (const float *)sp80, (const float *)arg0->v100);
    ((Gap::Sg::igAttrStackManager *)arg0->x)->pushAttr((Gap::Attrs::igAttr *)o);
    r = igTraversal_TraverseChildren((igTraversal *)arg0, (igNode *)arg1);
    ((Gap::Sg::igAttrStackManager *)arg0->x)->popAttr((Gap::Attrs::igAttr *)o);
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
                ((Gap::Core::igDataList *)stack)->resizeAndSetCount(n + 1, 4);
            }
            stack->set(n, &pushed);
        }
        igAttrStackManager_MarkStackChanged((igAttrStackManager *)manager, (igAttrStack *)stack, slot);
    }
    if (set->_trigger) {
        ((Gap::Sg::igAttrStackManager *)self->_attrStack)->flushUpdateAttrs((Gap::Attrs::igNonRefCountedAttrList *)(igNonRefCountedAttrList *)self->_flushedAttrs);
        List_AppendWords((igDataList *)(*(int *)((char *)((igSorter *)self->_sorter)->_dlist + 12)), ((igObjectList *)self->_flushedAttrs)->_count, (const int *)(((igObjectList *)self->_flushedAttrs)->_data));
    }
    result = igTraversal_TraverseChildren((igTraversal *)self, (igNode *)set);
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
            igAttrStackManager_MarkStackChanged((igAttrStackManager *)manager, (igAttrStack *)popStack, popSlot);
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
                ((Gap::Core::igDataList *)stack)->resizeAndSetCount(n + 1, 4);
            }
            stack->set(n, &pushed);
        }
        igAttrStackManager_MarkStackChanged((igAttrStackManager *)manager, (igAttrStack *)stack, slot);
    }
    if (set->_trigger != 0) {
        ((Gap::Sg::igAttrStackManager *)self->_attrStack)->flushUpdateAttrs((Gap::Attrs::igNonRefCountedAttrList *)(igNonRefCountedAttrList *)self->_flushedAttrs);
        List_AppendWords((igDataList *)(*(int *)((char *)((igSorter *)self->_sorter)->_dlist + 12)), ((igObjectList *)self->_flushedAttrs)->_count, (const int *)(((igObjectList *)self->_flushedAttrs)->_data));
    }
    result = igTraversal_TraverseChildren((igTraversal *)self, (igNode *)set);
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
            igAttrStackManager_MarkStackChanged((igAttrStackManager *)manager, (igAttrStack *)popStack, popSlot);
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
    ((Gap::Sg::igAttrStackManager *)o->_state)->pushAttr((Gap::Attrs::igAttr *)o->_baseAttr);
    count = g->_attrSets->_count;
    for (i = 0; i < count; i++) {
        if (FUN_001d8330((void *)g, i) == 0) {
            continue;
        }
        attr = ((ModelViewAttrView *)FUN_001d8310((void *)g, i));
        if (attr != 0) {
            src = ((void *)FUN_001d82f0((void *)g, i));
            if (base != 0) {
                igMatrix44f_SetIdentity((float *)m);
                igMatrix44f_Multiply((float *)m, (const float *)src, (const float *)base);
                attr->setMatrix(m);
            } else {
                attr->setMatrix(src);
            }
            ((Gap::Sg::igAttrStackManager *)o->_state)->pushAttr((Gap::Attrs::igAttr *)attr);
        }
        set = g->_attrSets->_data[i];
        n = set->_count;
        for (j = 0; j < n; j++) {
            ((Gap::Sg::igAttrStackManager *)o->_state)->pushAttr((Gap::Attrs::igAttr *)set->_data[j]);
        }
        switch (g->_mode) {
        case 0:
            ((Gap::Sg::igTraversal *)o)->dispatch((Gap::Core::igObject *)(g->_children->_data[i % nChild]));
            break;
        case 1:
            for (j = 0; j < nChild; j++) {
                ((Gap::Sg::igTraversal *)o)->dispatch((Gap::Core::igObject *)g->_children->_data[j]);
            }
            break;
        }
        if (!g->_nested) {
            for (j = n - 1; j >= 0; j--) {
                ((Gap::Sg::igAttrStackManager *)o->_state)->popAttr((Gap::Attrs::igAttr *)set->_data[j]);
            }
            if (attr != 0) {
                ((Gap::Sg::igAttrStackManager *)o->_state)->popAttr((Gap::Attrs::igAttr *)attr);
            }
        }
    }
    if (g->_nested) {
        for (i = count - 1; i >= 0; i--) {
            if (FUN_001d8330((void *)g, i) != 0) {
                set2 = g->_attrSets->_data[i];
                for (j = set2->_count - 1; j >= 0; j--) {
                    ((Gap::Sg::igAttrStackManager *)o->_state)->popAttr((Gap::Attrs::igAttr *)set2->_data[j]);
                }
                attr = ((ModelViewAttrView *)FUN_001d8310((void *)g, i));
                if (attr != 0) {
                    ((Gap::Sg::igAttrStackManager *)o->_state)->popAttr((Gap::Attrs::igAttr *)attr);
                }
            }
        }
    }
    ((Gap::Sg::igAttrStackManager *)o->_state)->popAttr((Gap::Attrs::igAttr *)o->_baseAttr);
    return 0;
}

void igCommonTraversal_TraverseTransform(int arg0, int arg1) {
    igTransform_TraverseChildrenAndPopMatrix(igTransform_PushMatrix((TransformView *)arg1, (CommonTraversalView *)arg0), (igTransform *)arg1, (igCommonTraversal *)arg0);
}

int igCommonTraversal_TraverseLightSet(LightTraversalView *o, LightSceneView *scene) {
    LightVec3 position;
    LightVec3 direction;
    float matrix[16];
    int i;
    FUN_001dc400((igSorter *)o->_collector, (igGroup *)scene, (igAttrStackManager *)o->_state);
    igMatrix44f_Multiply(matrix, currentEntry(stackOf_1b9d90(o->_state, ((CullMeta *)Gap::Attrs::igModelViewMatrixAttr::getClassMeta())))->_matrix, o->_view);
    for (i = 0; i < scene->_lights->_count; i++) {
        LightView *light = scene->_lights->_data[i];
        Vec3f_TransformProjective((float *)&position, (const float *)((char *)light + DAT_0055f0a0[0]->_offset), matrix);
        light->_worldPosition.x = position.x;
        light->_worldPosition.y = position.y;
        light->_worldPosition.z = position.z;
        if (light->_type == 0 || light->_type == 2) {
            Vec3f_TransformDirection((float *)&direction, (const float *)((char *)light + ((LightFieldMeta *)g_igLightAttr_directionMetaField)->_offset), matrix);
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
    temp_v0 = FUN_001be190(arg1, (igCompileTraversal *)arg0);
    if (temp_v0 == 0) {
        temp_v1 = (igAttrList *)arg1->_attributes;
        List_AppendWords((igDataList *)(*(int *)((char *)(temp_s0->_dlist) + 12)), temp_v1->_count, (const int *)temp_v1->_data);
        return 0;
    }
    if (temp_v0 == 4 || temp_v0 == 1) {
        return 0;
    }
    if (igTraversal_TraverseChildren((igTraversal *)arg0, (igNode *)arg1) == 2) {
        return 2;
    }
    return 0;
}

int igCommonTraversal_TraverseLightStateSet(struct A_1b9fc0 *arg0, struct B_1b9fc0 *arg1) {
    int s1;
    int s0;

    s0 = arg1->f32->n;
    for (s1 = 0; s1 < s0; s1++) {
        ((Gap::Sg::igAttrStackManager *)arg0->f52)->pushLightState((Gap::Attrs::igLightStateAttr *)arg1->f32->data[s1], 0);
    }
    igTraversal_TraverseChildren((igTraversal *)arg0, (igNode *)arg1);
    for (s0 = s0 - 1; s0 >= 0; s0--) {
        ((Gap::Sg::igAttrStackManager *)arg0->f52)->popLightState((Gap::Attrs::igLightStateAttr *)arg1->f32->data[s0], 0);
    }
    return 0;
}

int igCommonTraversal_TraverseLod(CullTraversalView *o, CullNodeView *node) {
    CullVec3 out;
    CullVec3 center;
    CullAttrState *st;
    CullMatrixStack *stack;
    int child;
    center.x = node->_center.x;
    center.y = node->_center.y;
    center.z = node->_center.z;
    st = o->_state;
    stack = st->_stacks->_data[st->_slotOfIndex[((CullMeta *)Gap::Attrs::igModelViewMatrixAttr::getClassMeta())->_index]];
    Vec3f_TransformProjective((float *)&out, (const float *)&center, currentEntry_1ba080(stack)->_matrix);
    child = ((int)FUN_001d0520((RangeLookup *)node, out.x * out.x + out.y * out.y + out.z * out.z));
    if (child != 0) {
        if (((Gap::Sg::igTraversal *)o)->dispatch((Gap::Core::igObject *)child) == 2) return 2;
        return 0;
    }
    return 0;
}

int igCommonTraversal_TraverseBumpMapShader(int a0, int arg1) {
    S_1ba1a0 *arg0 = (S_1ba1a0 *)a0;
    ((Gap::Sg::igAttrStackManager *)arg0->f52)->pushOverride((Gap::Attrs::igAttr *)arg0->f232);
    FUN_001b3ff0((void *)arg1, (int)arg0);
    ((Gap::Sg::igAttrStackManager *)arg0->f52)->popOverride((Gap::Attrs::igAttr *)arg0->f232);
    return 0;
}

int igCommonTraversal_TraverseCartoonShader(int arg0_, int arg1) {
    T_1ba200 *arg0 = (T_1ba200 *)arg0_;
    ((Gap::Sg::igAttrStackManager *)arg0->f34)->pushAttr((Gap::Attrs::igAttr *)arg0->fe8);
    igCommonTraversal_DrawCartoonShader((igCartoonShader *)arg1, (igCommonTraversal *)arg0);
    ((Gap::Sg::igAttrStackManager *)arg0->f34)->popAttr((Gap::Attrs::igAttr *)arg0->fe8);
    return 0;
}

struct MultiPassShaderView {
    char _pad0[32];
    igTDataList<igObject *> *_passData;
    char _pad36[24];
    unsigned short _technique;
    char _pad62[2];
    unsigned char _compiled;
    char _pad65[3];
    igTDataList<igTDataList<igAttr *> *> *_passes;
};
struct PassDataEntry { char _pad0[12]; int _type; };

static inline void pushPassAttr(igAttrStackManager *manager, igAttr *attr) {
    int slot = attr->_cachedUnitID + ((int *)manager->_attrStackIndexTable)[attr->_cachedAttrIndex];
    AttrObjectStack *stack = ((AttrObjectStackList *)manager->_attrStacks)->_data[slot];
    igObject *pushed = attr;
    int n = stack->getCount();
    if (n < stack->_capacity) {
        stack->_count = stack->_count + 1;
    } else {
        ((Gap::Core::igDataList *)stack)->resizeAndSetCount(n + 1, 4);
    }
    stack->set(n, &pushed);
    igAttrStackManager_MarkStackChanged(manager, (igAttrStack *)stack, slot);
}

static inline void pushTraversalAttr(igCommonTraversal *self, igAttr *attr) {
    /* matching construct: declaration-order search — the order of these locals */
    int n;
    igAttrStackManager *manager;
    AttrObjectStack *stack;
    int slot;
    igObject *pushed;
    manager = (igAttrStackManager *)self->_attrStack;
    slot = attr->_cachedUnitID + ((int *)manager->_attrStackIndexTable)[attr->_cachedAttrIndex];
    stack = ((AttrObjectStackList *)manager->_attrStacks)->_data[slot];
    pushed = attr;
    n = stack->getCount();
    if (n < stack->_capacity) {
        stack->_count = stack->_count + 1;
    } else {
        ((Gap::Core::igDataList *)stack)->resizeAndSetCount(n + 1, 4);
    }
    stack->set(n, &pushed);
    igAttrStackManager_MarkStackChanged(manager, (igAttrStack *)stack, slot);
}

static inline void popPassAttr(igAttrStackManager *manager, igAttr *attr) {
    int slot = attr->_cachedUnitID + ((int *)manager->_attrStackIndexTable)[attr->_cachedAttrIndex];
    AttrObjectStack *stack = ((AttrObjectStackList *)manager->_attrStacks)->_data[slot];
    igObject *top = stack->get(stack->_count - 1);
    void (*pop)(igObject *, int) = stack->_popProc;
    if (pop != 0) {
        pop(top, manager->_popProcData);
    }
    stack->_count = stack->_count - 1;
    igAttrStackManager_MarkStackChanged(manager, (igAttrStack *)stack, slot);
}

/* Multi-pass shader traversal: picks the technique once (falls back to 2 when a pass from the third on
 * has type 1, 2 or 4), then traverses the children once per pass with that pass's attributes pushed. */
int FUN_001ba260(igCommonTraversal *self, MultiPassShaderView *shader) {
    igAttrStackManager *manager = (igAttrStackManager *)self->_attrStack;
    if (!shader->_compiled) {
        shader->_technique = ((CapabilityQueryView *)self->_capabilityManager)->query(22);
        int i;
        int count = shader->_passData->_count;
        if (count > 2 && shader->_technique > 2) {
            for (i = 2; i < count; i++) {
                int type = ((PassDataEntry *)FUN_001d82c0(shader, i, 1))->_type;
                if (type == 1 || type == 4 || type == 2) {
                    shader->_technique = 2;
                    break;
                }
            }
        }
        FUN_001d23a0(shader);
    }
    int passCount = shader->_passes->_count;
    if (passCount > 1) {
        pushTraversalAttr(self, (igAttr *)self->_matrixOptimization);
    }
    FUN_001dc500((A_1dc500 *)self->_sorter, 0, 0);
    for (int pass = 0; pass < passCount; pass++) {
        igTDataList<igAttr *> *attrs = shader->_passes->_data[pass];
        igAttr **data = attrs->_data;
        for (int i = 0; i < attrs->_count; i++) {
            pushPassAttr(manager, data[i]);
        }
        igTraversal_TraverseChildren((igTraversal *)self, (igNode *)shader);
        for (int i = attrs->_count - 1; i >= 0; i--) {
            popPassAttr(manager, data[i]);
        }
    }
    FUN_001dc610((igSorter *)self->_sorter);
    if (passCount > 1) {
        popPassAttr((igAttrStackManager *)self->_attrStack, (igAttr *)self->_matrixOptimization);
    }
    return 0;
}

int igCommonTraversal_TraversePlanarShadowShader(int a0, int arg1) {
    S_1ba650 *arg0 = (S_1ba650 *)a0;
    ((Gap::Sg::igAttrStackManager *)arg0->f52)->pushAttr((Gap::Attrs::igAttr *)arg0->f232);
    ((Gap::Sg::igPlanarShadowShader *)arg1)->shade((Gap::Sg::igCommonTraversal *)arg0);
    ((Gap::Sg::igAttrStackManager *)arg0->f52)->popAttr((Gap::Attrs::igAttr *)arg0->f232);
    return 0;
}

int igCommonTraversal_TraverseProjectiveShadowShader(char *arg0, struct S_1d6190 *arg1) {
    FUN_001d6190(arg1, arg0);
    return 0;
}

int igCommonTraversal_TraverseSelfShadowShader(igCommonTraversal *self, igProjectiveShadowShader *shader) {
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
        ((Gap::Core::igDataList *)stack)->resizeAndSetCount(n + 1, 4);
    }
    stack->set(n, &pushed);
    igAttrStackManager_MarkStackChanged((igAttrStackManager *)manager, (igAttrStack *)stack, slot);
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
    igAttrStackManager_MarkStackChanged((igAttrStackManager *)manager, (igAttrStack *)stack, slot);
    return 0;
}

int FUN_001ba850(A1_1c03a0 *arg0, DepthOfFieldNode *arg1) {
    FUN_001c03a0(arg1, arg0);
    return 0;
}

int igCommonTraversal_TraverseTransformRecorder(igCommonTraversal *arg0, VC1 *arg1) {
    int sp30[16];
    igAttrStack *l;
    int i, k, v;
    l = ((igAttrStack **)((igAttrStackList *)((igAttrStackManager *)arg0->_attrStack)->_attrStacks)->_data)[((int *)((igAttrStackManager *)arg0->_attrStack)->_attrStackIndexTable)[Gap::Attrs::igModelViewMatrixAttr::getClassMeta()->_id]];
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
    igMatrix44f_Multiply((float *)sp30, (const float *)(v + 0xC), arg0->_viewMatInv);
    ((VC0 *)arg1)->vX(sp30);
    l = ((igAttrStack **)((igAttrStackList *)((igAttrStackManager *)arg0->_attrStack)->_attrStacks)->_data)[((int *)((igAttrStackManager *)arg0->_attrStack)->_attrStackIndexTable)[Gap::Attrs::igModelViewMatrixAttr::getClassMeta()->_id]];
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
    if (igTraversal_TraverseChildren((igTraversal *)arg0, (igNode *)arg1) == 2) {
        return 2;
    }
    return 0;
}

