int Gap__Sg__igCommonTraversal__vfunc_30(igCommonTraversalView *self) {
    return self->f68->slot21(self->f52);
}

void FUN_001b6cd0(int a0, float, float, float, float, float, float) {
    FUN_00191910((char *)a0 + 272);
}

void FUN_001b6ce0(void *arg0, float fparg0, float fparg1, float fparg2, float fparg3, float fparg4) {
    float var_f23;
    float temp_f14;
    float temp_f23;
    float var_f22;

    var_f23 = 0.0174532924f * fparg0;
    var_f22 = 0.0174532924f * fparg1;
    if (fparg0 < 0.0f) {
        var_f23 = 2.0f * atanf((fparg2 * (fparg3 * tanf(0.5f * var_f22))) / fparg3);
    } else {
        var_f22 = 2.0f * atanf(((fparg3 * tanf(0.5f * var_f23)) / fparg2) / fparg3);
    }
    temp_f23 = fparg3 * -tanf(0.5f * var_f23);
    temp_f14 = fparg3 * -tanf(0.5f * var_f22);
    FUN_001b6cd0((int)(arg0), temp_f23, -temp_f23, temp_f14, -temp_f14, fparg3, fparg4);
}

void Gap__Sg__igCommonTraversal__vfunc_31(A_1b6e20 *arg0) {
    C_1b6e20 *temp_a0;

    temp_a0 = arg0->f68;
    if (temp_a0->f128 == 0) {
        FUN_001d9bb0((void *)temp_a0, (int)arg0->f52);
    }
    arg0->f48 = 0;
    arg0->f52->v92();
    arg0->f68->v96();
    arg0->f72->f20 = 0;
    arg0->f80->f20 = 0;
    arg0->f84->f20 = 0;
    arg0->f88->f20 = 0;
    arg0->f268->f20 = 0;
    arg0->f92->f20 = 0;
    arg0->f96->f20 = 0;
    arg0->f76->f20 = 0;
    arg0->f248->f8 = 0;
    arg0->f252->f8 = 0;
}

void FUN_001b6ee0(int arg0, int *arg1) {
    int sp3C;

    igMatrix44f_Copy(arg0 + 0x64);
    igMatrix44f_Invert(&sp3C, arg0 + 0xA4, arg1);
}

void FUN_001b6f30(A_1b6f30 *arg0, R_1b6f30 *arg1, R_1b6f30 *arg2) {
    R_1b6f30 *temp_a0;
    R_1b6f30 *temp_a0_2;

    if (arg2 != 0) {
        arg2->refs = arg2->refs + 1;
    }
    temp_a0 = arg0->f32;
    if (temp_a0 != 0) {
        temp_a0->refs = temp_a0->refs - 1;
        if (((unsigned long long)((long long)temp_a0->refs << 0x29) >> 0x29) == 0) {
            igObject_Destroy((void *)temp_a0);
        }
    }
    arg0->f32 = arg2;
    if (arg1 != 0) {
        arg1->refs = arg1->refs + 1;
    }
    temp_a0_2 = arg0->f36;
    if (temp_a0_2 != 0) {
        temp_a0_2->refs = temp_a0_2->refs - 1;
        if (((unsigned long long)((long long)temp_a0_2->refs << 0x29) >> 0x29) == 0) {
            igObject_Destroy((void *)temp_a0_2);
        }
    }
    arg0->f36 = arg1;
    FUN_001b0000((T_1b0000 *)arg0->f52, g_igAttr_metaObject[0], (Obj_1b0000 *)arg0->f36, (Obj_1b0000 *)arg0->f32);
}

void Gap__Sg__igCommonTraversal__vfunc_28(O_1b7010 *arg0, R_1b7010 *arg1) {
    void *a;
    bool var_s1;
    R_1b7010 *t;

    retain_1b7010(arg1);
    release(arg0->f60);
    arg0->f60 = arg1;
    var_s1 = 0;
    if (arg1 == 0) {
        a = ((void *)igObject_GetAllocator(arg0));
        release(arg0->f36);
        arg0->f36 = FUN_00137ab0(a);
        a = ((void *)igObject_GetAllocator(arg0));
        release(arg0->f32);
        arg0->f32 = FUN_0014f2c0(a);
        var_s1 = 1;
    } else {
        if (arg0->f36 == 0) {
            igSmartPointer<R_1b7010> created(FUN_00130020(((void *)igObject_GetAllocator(arg0))));
            t = created.get();
            retain_1b7010(arg1);
            release(t->f8);
            t->f8 = arg1;
            t = created.get();
            retain_1b7010(t);
            release(arg0->f36);
            arg0->f36 = t;
            var_s1 = 1;
        }
        if (arg0->f32 == 0) {
            igSmartPointer<R_1b7010> created(FUN_00149c30(((void *)igObject_GetAllocator(arg0))));
            t = created.get();
            retain_1b7010(arg1);
            release(t->f8);
            t->f8 = arg1;
            t = created.get();
            retain_1b7010(t);
            release(arg0->f32);
            arg0->f32 = t;
            var_s1 = 1;
        }
    }
    if (var_s1) {
        FUN_001b6f30((A_1b6f30 *)arg0, (R_1b6f30 *)arg0->f36, (R_1b6f30 *)arg0->f32);
    }
}

V128 *FUN_001b7330(O_1b7330 *arg0, float *arg1) {
    List_1b7330 *l = arg0->list;
    int idx;
    V128 *e;
    if (l->count >= l->cap) {
        igObjectPool_Grow((List_1dca40 *)l, (Obj_1dca40 * (*)(int))&FUN_001356b0);
    }
    idx = l->count;
    l->count = idx + 1;
    e = l->items[idx];
    e->vX((int)arg1);
    FUN_001b1030((igAttrStackManager *)arg0->f52, (igAttr *)e);
    return e;
}

void FUN_001b73d0(struct S_1b73d0 *arg0) {
    FUN_001b11b0((struct A_1b11b0 *)arg0->x, (struct B_1b11b0 *)((int *)g_igModelViewMatrixAttr_metaObject)[0]);
}

void Gap__Sg__igCommonTraversal__vfunc_23(igCommonTraversalOps *t, int root) {
    igClearAttr *attr;
    AttrManagerView *m;
    AttrSlotList *list;
    int unit;
    igMetaObject *meta;
    int vc = t->_vc;
    if (vc != 0) {
        meta = igClearAttr_GetMetaObject();
        m = t->_attrStack;
        pushAttr(m, meta, vc);
        vc = t->_vc;
        meta = igProjectionMatrixAttr_GetMetaObject();
        m = t->_attrStack;
        pushAttr(m, meta, vc);
    }
    FUN_001b7330((O_1b7330 *)t, t->_viewMat);
    if (t->_userTimeState) {
        t->setTime(t->_timeLong);
    }
    ((long long *)t->_defaultTimeAttr)[2] = t->getTime();
    m = t->_attrStack;
    attr = t->_defaultTimeAttr;
    list = (AttrSlotList *)m->_attrStacks;
    unit = attr->_cachedAttrIndex;
    unit = attr->_cachedUnitID + m->_firstUnit[unit];
    list = (AttrSlotList *)((AttrStackListView *)list)->_data[unit];
    list->append(attr);
    igAttrStackManager_MarkStackChanged((struct A_1b1490 *)m, (struct B_1b1490 *)list, unit);
    Gap__Sg__igTraversal__vfunc_23((void *)t, root);
}

void Gap__Sg__igCommonTraversal__vfunc_32(void *arg0, long long arg1) {
    int temp_s2;
    struct L_1b75b0 *temp_s1;

    temp_s1 = *(struct L_1b75b0 **)((char *)arg0 + 240);
    temp_s2 = temp_s1->size;
    if (temp_s2 < temp_s1->cap) {
        temp_s1->size = size_of(temp_s1) + 1;
    } else {
        List_Resize((void *)temp_s1, temp_s2 + 1, 8);
    }
    temp_s1->data[temp_s2] = arg1;
}

void Gap__Sg__igCommonTraversal__vfunc_24(igCommonTraversal *t, int arg1) {
    Mgr *m;
    int idx;
    Ent_1b7630 *e;
    int v;
    int last;
    FUN_001b73d0((S_1b73d0 *)t);
    if (t->_userTimeState != 0) {
        ((TravView *)t)->f31();
    }
    m = (Mgr *)t->_attrStack;
    idx = ((igTimeAttr *)t->_defaultTimeAttr)->_cachedUnitID + m->idx[((igTimeAttr *)t->_defaultTimeAttr)->_cachedAttrIndex];
    e = m->tab->ents[idx];
    last = e->count - 1; v = e->items[last];
    if (e->fn != 0) {
        e->fn(v, m->arg);
    }
    e->count = e->count - 1;
    igAttrStackManager_MarkStackChanged((struct A_1b1490 *)m, (struct B_1b1490 *)e, idx);
    Gap__Sg__igTraversal__vfunc_24(t, arg1);
}

void Gap__Sg__igCommonTraversal__vfunc_33(void *arg0) {
    void *temp_a0;

    temp_a0 = (void *)(*(int *)((char *)(arg0) + 240));
    *(int *)((char *)(temp_a0) + 8) = (int)((int) (*(int *)((char *)(temp_a0) + 8) - 1));
}

void FUN_001b7740(void **arg0, void **arg1) {
    int var_a0;
    int var_a1;

    var_a0 = *(int *)((char *)((*arg0)) + 8);
    if (var_a0 == 0) {
        var_a0 = ((int *)g_stringObjEmptyText)[0];
    }
    var_a1 = *(int *)((char *)((*arg1)) + 8);
    if (var_a1 == 0) {
        var_a1 = ((int *)g_stringObjEmptyText)[0];
    }
    strcmp(var_a0, var_a1);
}

void FUN_001b7770(igCommonTraversal *self, int name, int value) {
    SegmentOverrideRef newStackRef;
    igObject *searchKey;
    SegmentOverrideRef insertKey;
    int stacks;
    int index;
    int names;
    igObject *str;
    igObject *stack;
    int pos;
    int al = igObject_GetAllocator(self);
    al = g_useOwnerAllocator ? al : Memory_GetAllocatorBySelector(kIGMemoryPoolHandleTemporary[0]);
    str = ((igObject *)igStringObj_Create(al));
    igStringObj_Set(str, name);
    igStringObj_ToLower(str);
    { int first = self->_segmentOverrideNames; searchKey = str;
    index = List_BinarySearchWords(first, &searchKey, FUN_001b7740); }
    if (index < 0) {
        names = self->_segmentOverrideNames;
        insertKey.set(str);
        pos = List_LowerBound(names, &insertKey, FUN_001b7740);
        List_InsertWords(names, pos, 1, &insertKey);
        stack = ((igObject *)FUN_0019cba0(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem[0])));
        newStackRef.p = stack;
        stacks = self->_segmentOverrideStacks;
        newStackRef.retain();
        List_InsertWords(stacks, pos, 1, &newStackRef);
        stack->_refCount = stack->_refCount - 1;
        if (((unsigned long long)((long long)(int)stack->_refCount << 0x29) >> 0x29) == 0) {
            igObject_Destroy((void *)stack);
        }
    } else {
        stack = ((igObject **)((igObjectList *)self->_segmentOverrideStacks)->_data)[index];
    }
    ObjectList_AppendRetained(stack, value);
    str->_refCount = str->_refCount - 1;
    if (((unsigned long long)((long long)(int)str->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy((void *)str);
    }
}

igObject *FUN_001b7920(igCommonTraversal *self, int name) {
    int index;
    int last;
    SegmentStackList *stack;
    igObject *top;
    index = igStringObjList_BinarySearch((SegmentStackList *)self->_segmentOverrideNames, name, strcasecmp);
    if (index < 0) {
        return 0;
    }
    stack = ((SegmentStackList **)((SegmentStackList *)self->_segmentOverrideStacks)->_data)[index];
    {
        int i = stack->count() - 1;
        top = stack->_data[i];
    }
    last = stack->_count - 1;
    removeRetained(stack, last);
    if (stack->_count == 0) {
        removeRetained((SegmentStackList *)self->_segmentOverrideNames, index);
        removeRetained((SegmentStackList *)self->_segmentOverrideStacks, index);
    }
    return top;
}

int FUN_001b7af0(void *arg0, int arg1) {
    int temp_v0_2;
    void *temp_v0;

    if ((arg1 == 0) || (strlen(arg1) == 0)) {
        return 0;
    }
    temp_v0_2 = igStringObjList_BinarySearch(*(int *)((char *)(arg0) + 260), arg1, &strcasecmp);
    if (temp_v0_2 < 0) {
        return 0;
    }
    temp_v0 = (void *)(*(int *)(*(int *)((char *)(*(int *)((char *)(arg0) + 264)) + 16) + (temp_v0_2 * 4)));
    return *(int *)(*(int *)((char *)(temp_v0) + 16) + ((*(int *)((char *)(temp_v0) + 8) - 1) * 4));
}

int FUN_001b7b90(void *t, void *arg) {
    int r;
    int i;
    igGroupMaskView *n;
    int count;
    igBitMask *mask;
    n = (igGroupMaskView *)arg;
    mask = n->_mask;
    if (n->_childList) count = n->_childList->_count; else count = 0;
    for (i = 0; i < count; i++) {
        int m = 1 << (i & 31);
        if (m & ((int *)mask->_data)[(unsigned int)i >> 5]) {
            r = FUN_001e04c0((S_1e04c0 *)t, (V_1e04c0 *)(((int *)n->_childList->_data)[i]));
            if (r == 1) break;
            if (r == 2) return 2;
        }
    }
    return 0;
}

int FUN_001b7c70(void **arg0, void *arg1) {
    if (*(int *)((char *)(arg1) + 20) & 0x20) {
        return 0;
    }
    FUN_001d1550((void *)arg1, ((DW4VC_104_0 *)(arg0))->vX());
    return FUN_001b9530(arg0, arg1);
}

int FUN_001b7ce0(C_1b7ce0 *arg0, A_1b7ce0 *arg1) {
    int temp_s0;

    if (arg1->f20 & 0x20) {
        return 0;
    }
    FUN_001d1760((void *)arg1, arg0->vX());
    FUN_001b1030((igAttrStackManager *)arg0->f52, (igAttr *)arg0->f236);
    temp_s0 = FUN_001b9530(arg0, arg1);
    FUN_001b1100((struct A_1b1100 *)arg0->f52, (struct B_1b1100 *)arg0->f236);
    return temp_s0;
}

int FUN_001b7d70(void *arg0, void *arg1) {
    struct V_1b7d70 sp40;
    struct V_1b7d70 sp30;
    float temp_f4;
    float temp_f3;
    float dist;
    float dx, dy, dz;
    float r;
    void *temp_a0;
    void *temp_a1;
    int temp_v0;
    int temp_v0_2;
    int temp_v1;
    int var_v0;
    int var_a2;

    sp30.x = *(float *)((char *)(arg1) + 76);
    sp30.y = *(float *)((char *)(arg1) + 80);
    sp30.z = *(float *)((char *)(arg1) + 84);
    temp_a1 = (void *)(*(int *)((char *)(arg0) + 52));
    temp_a0 = (void *)(*(int *)(*(int *)((char *)(*(int *)((char *)(temp_a1) + 16)) + 16) + (*(int *)(*(int *)((char *)(temp_a1) + 68) + (*(int *)((char *)(((void * *)g_igModelViewMatrixAttr_metaObject)[0]) + 8) * 4)) * 4)));
    temp_v0 = *(int *)((char *)(temp_a0) + 24);
    if (temp_v0 >= 0) {
        var_v0 = *(int *)(*(int *)((char *)(temp_a0) + 16) + (temp_v0 * 4));
    } else {
        temp_v0_2 = *(int *)((char *)(temp_a0) + 8);
        if (temp_v0_2 != 0) {
            var_v0 = *(int *)(*(int *)((char *)(temp_a0) + 16) + ((temp_v0_2 - 1) * 4));
        } else {
            var_v0 = *(int *)((char *)(temp_a0) + 20);
        }
    }
    var_a2 = var_v0 + 0xC;
    if (*(int *)((char *)(arg1) + 20) & 0x20) {
        return 0;
    }
    Vec3f_TransformProjective(&sp40, &sp30, var_a2);
    dy = sp40.y;
    dx = sp40.x;
    dz = sp40.z;
    temp_f4 = *(float *)((char *)(arg1) + 88);
    temp_f3 = *(float *)((char *)(arg1) + 92);
    dist = sqrtf(dx * dx + dy * dy + dz * dz);
    if (dist <= temp_f4 || (temp_v1 = *(int *)((char *)(arg1) + 72)) == 3) {
        FUN_001d1da0((MorphLevelState *)arg1, 1.0f);
    } else {
        if (!(dist < temp_f3)) {
            FUN_001d1da0((MorphLevelState *)arg1, 0.0f);
        } else {
            r = (temp_f3 - dist) / (temp_f3 - temp_f4);
            if (temp_v1 == 0) {
                FUN_001d1da0((MorphLevelState *)arg1, r);
            } else if (temp_v1 == 1) {
                FUN_001d1da0((MorphLevelState *)arg1, r * r);
            } else if (temp_v1 == 2) {
                FUN_001d1da0((MorphLevelState *)arg1, sqrtf(r));
            }
        }
    }
    return FUN_001b9530(arg0, arg1);
}

static inline void pushMatrixAttr(igAttrStackManager *manager, MatrixAttrView *attr) {
    int n;
    AttrObjectStack *stack;
    int slot;
    slot = attr->_cachedUnitID + ((int *)manager->_attrStackIndexTable)[attr->_cachedAttrIndex];
    stack = ((AttrObjectStackList *)manager->_attrStacks)->_data[slot];
    igObject *pushed = (igObject *)attr;
    n = stack->getCount();
    if (n < stack->_capacity) {
        stack->_count = stack->_count + 1;
    } else {
        List_Resize(stack, n + 1, 4);
    }
    stack->set(n, &pushed);
    igAttrStackManager_MarkStackChanged((A_1b1490 *)manager, (B_1b1490 *)stack, slot);
}
static inline void setTransformMvm(TransformView *transform, MatrixAttrView *attr) {
    if (attr != 0) {
        attr->_refCount = attr->_refCount + 1;
    }
    {
        MatrixAttrView *old = transform->_mvm;
        IG_OBJECT_RELEASE(old);
    }
    transform->_mvm = attr;
}

float *igTransform_PushMatrix(TransformView *self, CommonTraversalView *traversal) {
    /* matching construct: declaration-order search — the order of these locals */
    int unit;
    int blendIndex;
    float *parent;
    MatrixAttrView *top;
    MatrixAttrView *attr;
    igAttrStackManager *manager;
    int target;
    self->update(traversal->getTime());
    target = self->_target;
    parent = 0;
    manager = traversal->_attrStack;
    switch (target) {
    case 0:
        top = (MatrixAttrView *)topAttr(((AttrObjectStackList *)manager->_attrStacks)->_data[((int *)manager->_attrStackIndexTable)[g_igModelViewMatrixAttr_metaObject[0]->_id]]);
        if (top != 0) {
            parent = top->_m;
        }
        attr = (MatrixAttrView *)takePooled(traversal->_matrixPool, (void *)FUN_001356b0);
        if (parent != 0) {
            FUN_001904f0(attr->_m, self->_m, parent);
        } else {
            attr->setMatrix(self->_m);
        }
        pushMatrixAttr(manager, attr);
        setTransformMvm(self, attr);
        return attr->_m;
    case 9: case 10: case 11: case 12: case 13: case 14: case 15: case 16:
        unit = target - 9;
        top = (MatrixAttrView *)topAttr(((AttrObjectStackList *)manager->_attrStacks)->_data[unit + ((int *)manager->_attrStackIndexTable)[g_igTextureMatrixAttr_metaObject[0]->_id]]);
        if (top != 0) {
            parent = top->_m;
        }
        attr = (MatrixAttrView *)takePooled(traversal->_texMatPool, (void *)FUN_001317c0);
        ((TextureMatrixAttrView *)attr)->_outputElementCount = -1;
        ((TextureMatrixAttrView *)attr)->_isProjective = 0;
        attr->setUnitID((short)unit);
        if (parent != 0) {
            FUN_001904f0((char *)attr + g_igTextureMatrixAttr_mField[0]->_offset, self->_m, parent);
        } else {
            attr->setMatrix(self->_m);
        }
        pushMatrixAttr(manager, attr);
        setTransformMvm(self, attr);
        return (float *)((char *)attr + g_igTextureMatrixAttr_mField[0]->_offset);
    default:
        blendIndex = target - 1;
        top = (MatrixAttrView *)topAttr(((AttrObjectStackList *)manager->_attrStacks)->_data[blendIndex + ((int *)manager->_attrStackIndexTable)[g_igVertexBlendMatrixAttr_metaObject[0]->_id]]);
        if (top != 0) {
            parent = (float *)((char *)top + g_igVertexBlendMatrixAttr_mField[0]->_offset);
        }
        attr = (MatrixAttrView *)takePooled(traversal->_blendMatrixPool, (void *)FUN_00130c10);
        attr->setUnitID((short)blendIndex);
        if (parent != 0) {
            FUN_001904f0((char *)attr + g_igVertexBlendMatrixAttr_mField[0]->_offset, self->_m, parent);
        } else {
            attr->setMatrix(self->_m);
        }
        pushMatrixAttr(manager, attr);
        setTransformMvm(self, attr);
        return (float *)((char *)attr + g_igVertexBlendMatrixAttr_mField[0]->_offset);
    }
}

int igTransform_TraverseChildrenAndPopMatrix(float *matrix, igTransform *self, igCommonTraversal *traversal) {
    int target;
    int result;
    igAttrStackManager *manager;
    int slot;
    int unit;
    igMetaObject *meta;
    AttrObjectStack *stack;
    void (*pop)(igObject *, int);
    manager = (igAttrStackManager *)traversal->_attrStack;
    target = self->_target;
    result = igTraversal_TraverseChildren((int)traversal, (S_1e07a0 *)self);
    unit = 0;
    switch (target) {
    case 0:
        meta = g_igModelViewMatrixAttr_metaObject[0];
        break;
    case 9: case 10: case 11: case 12: case 13: case 14: case 15: case 16:
        meta = g_igTextureMatrixAttr_metaObject[0];
        unit = target - 9;
        break;
    default:
        unit = target - 1;
        meta = g_igVertexBlendMatrixAttr_metaObject[0];
        break;
    }
    slot = unit + ((int *)manager->_attrStackIndexTable)[meta->_id];
    stack = ((AttrObjectStackList *)manager->_attrStacks)->_data[slot];
    {
        int last = stack->_count - 1;
        igObject **data = stack->_data;
        igObject *top;
        pop = stack->_popProc;
        top = data[last];
        if (pop != 0) {
            pop(top, manager->_popProcData);
        }
    }
    stack->_count = stack->_count - 1;
    igAttrStackManager_MarkStackChanged((A_1b1490 *)manager, (B_1b1490 *)stack, slot);
    if (result == 2) {
        return 2;
    }
    return 0;
}

int FUN_001b8720(void *arg0, ForwardTarget *arg1) {
    return arg1->vX(arg0);
}

