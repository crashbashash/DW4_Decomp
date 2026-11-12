void FUN_001bb1f0(int arg0) {
    FUN_001bb550(((int)DAT_00562648[0]), arg0);
}

void FUN_001bb200(void) {
    *(int *)0x562648 = FUN_0019a6e0(Memory_GetAllocatorBySelector(*(int *)0x587038));
}

void FUN_001bb230(void) {
    void *temp_a0;

    temp_a0 = *(void **)0x562648;
    if (temp_a0 != 0) {
        *(int *)((char *)temp_a0 + 4) = (int) (*(int *)((char *)temp_a0 + 4) - 1);
        if (((unsigned long long) ((long long) *(int *)((char *)temp_a0 + 4) << 0x29) >> 0x29) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
}

void Gap__Sg__igCompileTraversal__vfunc_09(C_1bb280 *arg0, int arg1) {
    Q *t;
    Q *s;

    Gap__Sg__igCommonTraversal__vfunc_09((igCommonTraversal *)arg0, arg1);
    if (arg1 == 0) {
        s = DAT_00562648[0];
        if (s != 0) {
            s->f4 += 1;
        }
        t = arg0->f28;
        if (t != 0) {
            t->f4 -= 1;
            if ((t->f4 & 0x7fffff) == 0) {
                igObject_Destroy((void *)t);
            }
        }
        arg0->f28 = s;
    }
}

void Gap__Sg__igCompileTraversal__vfunc_31(char *p) {
    clearEntries(*(RefCountedEntryList **)(p + 472));
    clearEntries(*(RefCountedEntryList **)(p + 476));
    *(int *)(*(char **)(p + 492) + 8) = 0;
    clearEntries(*(RefCountedEntryList **)(p + 504));
    p[484] = 0;
    p[496] = 0;
}

void Gap__Sg__igCompileTraversal__vfunc_10(void **self) {
    Gap__Core__igObject__vfunc_08();
    ((igCompileTraversalVSlots *)(self))->slot31();
}

void FUN_001bb550(int arg0, int arg1) {
    FUN_001b68c0((void *)arg0, (void *)arg1);
    if (FUN_002fe290(arg1, DAT_00561620[0]) != 0) {
        igTraversal_RegisterFunction((struct L_1e06c0 *)arg0, (struct X_1e06c0 *)arg1, (void *)FUN_001bcd80);
        return;
    }
    if (FUN_002fe290(arg1, DAT_00561bd8[0]) != 0) {
        igTraversal_RegisterFunction((struct L_1e06c0 *)arg0, (struct X_1e06c0 *)arg1, (void *)FUN_001bcd90);
        return;
    }
    if (FUN_002fe290(arg1, DAT_00561a98[0]) != 0) {
        igTraversal_RegisterFunction((struct L_1e06c0 *)arg0, (struct X_1e06c0 *)arg1, (void *)FUN_001bcdf0);
        return;
    }
    if (FUN_002fe290(arg1, DAT_00561860[0]) != 0) {
        igTraversal_RegisterFunction((struct L_1e06c0 *)arg0, (struct X_1e06c0 *)arg1, (void *)FUN_001bcda0);
        return;
    }
    if (FUN_002fe290(arg1, DAT_00561e98[0]) != 0) {
        igTraversal_RegisterFunction((struct L_1e06c0 *)arg0, (struct X_1e06c0 *)arg1, (void *)FUN_001bcdb0);
        return;
    }
    if (FUN_002fe290(arg1, DAT_00561ee8[0]) != 0) {
        igTraversal_RegisterFunction((struct L_1e06c0 *)arg0, (struct X_1e06c0 *)arg1, (void *)FUN_001bcdc0);
        return;
    }
    if (FUN_002fe290(arg1, DAT_005617a8[0]) != 0) {
        igTraversal_RegisterFunction((struct L_1e06c0 *)arg0, (struct X_1e06c0 *)arg1, (void *)FUN_001bcdd0);
        return;
    }
    if (FUN_002fe290(arg1, DAT_00561578[0]) != 0) {
        igTraversal_RegisterFunction((struct L_1e06c0 *)arg0, (struct X_1e06c0 *)arg1, (void *)FUN_001bcde0);
        return;
    }
    if (FUN_002fe290(arg1, DAT_00561a38[0]) != 0) {
        igTraversal_RegisterFunction((struct L_1e06c0 *)arg0, (struct X_1e06c0 *)arg1, (void *)FUN_001bc1e0);
        return;
    }
    if (FUN_002fe290(arg1, DAT_005618f8[0]) != 0) {
        igTraversal_RegisterFunction((struct L_1e06c0 *)arg0, (struct X_1e06c0 *)arg1, (void *)FUN_001bc0e0);
        return;
    }
    if (FUN_002fe290(arg1, DAT_005612b0[0]) != 0) {
        igTraversal_RegisterFunction((struct L_1e06c0 *)arg0, (struct X_1e06c0 *)arg1, (void *)FUN_001bbae0);
        return;
    }
    if (FUN_002fe290(arg1, DAT_00561ca0[0]) != 0) {
        igTraversal_RegisterFunction((struct L_1e06c0 *)arg0, (struct X_1e06c0 *)arg1, (void *)FUN_001bd0e0);
        return;
    }
    if (FUN_002fe290(arg1, DAT_00561888[0]) != 0) {
        igTraversal_RegisterFunction((struct L_1e06c0 *)arg0, (struct X_1e06c0 *)arg1, (void *)FUN_001bce40);
        return;
    }
    if (FUN_002fe290(arg1, DAT_00561f38[0]) != 0) {
        igTraversal_RegisterFunction((struct L_1e06c0 *)arg0, (struct X_1e06c0 *)arg1, (void *)FUN_001bcf70);
        return;
    }
    if (FUN_002fe290(arg1, DAT_00562488[0]) != 0) {
        igTraversal_RegisterFunction((struct L_1e06c0 *)arg0, (struct X_1e06c0 *)arg1, (void *)FUN_001bd150);
        return;
    }
    if (FUN_002fe290(arg1, DAT_005615d8[0]) != 0) {
        igTraversal_RegisterFunction((struct L_1e06c0 *)arg0, (struct X_1e06c0 *)arg1, (void *)FUN_001bd160);
    }
}

void Gap__Sg__igCompileTraversal__vfunc_23(igCompileTraversal *self, int arg1) {
    int a1 = self->_vc;
    if (a1 != 0) {
        L0 *stack = (L0 *)self->_attrStack;
        ((VC104 *)(stack->f16->f16[stack->f68[DAT_0055f308[0]->f8]]->f20))->vX(a1, (int)stack);
    }
    {
    igSmartPointer<T_1bb880> matrix((T_1bb880 *)((void *)FUN_001356b0(igObject_GetAllocator(self))));
    igSmartPointer<T_1bb880> info((T_1bb880 *)((void *)FUN_001a3590(igObject_GetAllocator(self))));
    T_1bb880 **slot = &info->f12;
    T_1bb880 *old = *slot;
    if (old != 0) {
        --old->_refCount;
        if ((old->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(old);
        }
    }
    *slot = 0;
    info->f8 = -1;
    info->f32 = 0;
    self->_currentBoneIndex = 1;
    int identity[16];
    igMatrix44f_SetIdentity(identity);
    FUN_001b6ee0((int)self, (int *)identity);
    matrix->setMatrix((int)&self->_viewMat);
    ObjectList_AppendRetained(self->_mvmList, matrix.p);
    ObjectList_AppendRetained(self->_xformInfoList, info.p);
    FUN_001b1030((igAttrStackManager *)self->_attrStack, (igAttr *)matrix.p);
    }
    if (self->_userTimeState != 0) {
        ((VC128L *)self)->vX(self->_timeLong);
    }
    Gap__Sg__igTraversal__vfunc_23((void *)self, arg1);
}

void Gap__Sg__igCompileTraversal__vfunc_24(igCompileTraversal *arg0, int arg1) {
    FUN_001b73d0((S_1b73d0 *)arg0);
    FUN_001d9bb0((void *)arg0->_sorter, arg0->_attrStack);
    if (arg0->_userTimeState != 0) {
        ((DW4VC_132_0 *)(((char *)(arg0) + 0)))->vX();
    }
    Gap__Sg__igTraversal__vfunc_24((void *)arg0, arg1);
}

void FUN_001bbae0(int arg0, int arg1) {
    FUN_001bc050(FUN_001bbb30(arg1, arg0), arg1, arg0);
}

int FUN_001bcd60(int arg0, int arg1) {
    return arg0 + (arg1 * 4);
}

float FUN_001bcd70(float *arg0, int arg1) {
    return arg0[arg1];
}

int FUN_001bcd80(void *arg0) {
    *(char *)((char *)(arg0) + 484) = 1;
    return 2;
}

int FUN_001bcd90(void *arg0) {
    *(char *)((char *)(arg0) + 484) = 1;
    return 2;
}

int FUN_001bcda0(void *arg0) {
    *(char *)((char *)(arg0) + 484) = 1;
    return 2;
}

int FUN_001bcdb0(void *arg0) {
    *(char *)((char *)(arg0) + 484) = 1;
    return 2;
}

int FUN_001bcdc0(void *arg0) {
    *(char *)((char *)(arg0) + 484) = 1;
    return 2;
}

int FUN_001bcdd0(void *arg0) {
    *(char *)((char *)(arg0) + 484) = 1;
    return 2;
}

int FUN_001bcde0(void *arg0) {
    *(char *)((char *)(arg0) + 484) = 1;
    return 2;
}

int FUN_001bcdf0(void *arg0, void **arg1) {
    ObjectList_AppendRetained(*(int *)((char *)(arg0) + 500));
    ((DW4VC_176_1 *)(arg1))->vX((int)(arg0));
    return 0;
}

int FUN_001bce40(A_1bce40 *arg0, int *arg1) {
    X_1bce40 *temp_s2;
    X_1bce40 *temp_v0;
    int temp_s0;
    int temp_s1;
    temp_s0 = arg0->f52;
    *(char *)((char *)arg0 + 496) = 1;
    temp_s2 = ((X_1bce40 *)FUN_001356b0(igObject_GetAllocator()));
    temp_v0 = ((X_1bce40 *)FUN_001a3590(igObject_GetAllocator(arg0)));
    temp_v0->f8 = arg1[8];
    ObjectList_AppendRetained(arg0->f472, temp_s2);
    ObjectList_AppendRetained(arg0->f476, temp_v0);
    temp_s2->f4 = temp_s2->f4 - 1;
    if (((unsigned long long) ((long long) temp_s2->f4 << 0x29) >> 0x29) == 0) {
        igObject_Destroy((void *)temp_s2);
    }
    temp_v0->f4 = temp_v0->f4 - 1;
    if (((unsigned long long) ((long long) temp_v0->f4 << 0x29) >> 0x29) == 0) {
        igObject_Destroy((void *)temp_v0);
    }
    FUN_001b1030((igAttrStackManager *)temp_s0, (igAttr *)temp_s2);
    temp_s1 = igTraversal_TraverseChildren((int)arg0, (S_1e07a0 *)arg1);
    FUN_001b1100((struct A_1b1100 *)temp_s0, (struct B_1b1100 *)temp_s2);
    if (temp_s1 == 2) {
        return 2;
    }
    return 0;
}

int FUN_001bcf70(A_1bcf70 *arg0, B_1bcf70 *arg1) {
    Obj_1bcf70 *o;
    int s0;
    s0 = arg0->f52;
    arg0->f496 = 1;
    o = ((Obj_1bcf70 *)FUN_00139990(igObject_GetAllocator(arg0)));
    ObjectList_AppendRetained(arg0->f504, o);
    o->refs = o->refs - 1;
    if ((o->refs & 0x7FFFFF) == 0) igObject_Destroy((void *)o);
    unsigned int n = arg1->f40->count;
    if (o->f24 < n) {
        if (o->f12 != 0) FUN_00300f50(o, o->f12);
        if (o->f16 != 0) FUN_00300f50(o, o->f16);
        o->f16 = ((int *)igObject_AllocateStorage(o, n * 4));
        o->f24 = n;
    }
    o->f20 = n;
    int i = 0;
    while (i < arg1->f40->count) {
        o->f16[i] = arg1->f40->data[i];
        i++;
    }
    FUN_001b1030((igAttrStackManager *)s0, (igAttr *)o);
    int r = FUN_001b9320(arg0, arg1);
    FUN_001b1100((struct A_1b1100 *)s0, (struct B_1b1100 *)o);
    if (r == 2) return 2;
    return 0;
}

int FUN_001bd0e0(int arg0, void *arg1) {
    if (*(int *)((char *)(*(int *)((char *)(arg1) + 32)) + 8) > 0) {
        ((DW4VC_124_0 *)(((char *)(arg1) + 0)))->vX();
    }
    if (igTraversal_TraverseChildren(arg0, (S_1e07a0 *)arg1) == 2) {
        return 2;
    }
    return 0;
}

int FUN_001bd150(void) {
    return 0;
}

int FUN_001bd160(void) {
    return 0;
}

void FUN_001bd170(struct A_1bd170 *arg0, struct B_1bd170 *arg1) {
    int i;
    int n;
    int idx;
    struct B_1bd170 *c;
    struct Arr_1bd170 *o;
    n = arg1->list->n;
    for (i = 0; i < n; i++) {
        c = (struct B_1bd170 *)arg1->list->data[i];
        if (igObject_IsKindOf(c, DAT_0055f208[0]) != 0) {
            FUN_001bd170(arg0, c);
        } else {
            o = arg0->out;
            idx = o->n;
            if (idx < o->cap) {
                o->n = n_of_1bd170(o) + 1;
            } else {
                List_Resize((void *)o, idx + 1, 4);
            }
            o->data[idx] = (int)c;
        }
    }
}

void FUN_001bd6b0(Links *links, Shape *shape) {
    int index;
    igTDataList<int> *indices;
    int n;
    int i;
    int j;
    void **slot;
    void *target;
    int index2;
    igTDataList<void **> *slots;
    n = shape->list->count();
    for (i = 0; i < n; i++) {
        target = shape->list->_data[i];
        j = links->targets->find(target);
        while (j != -1) {
            indices = links->indices;
            index = indices->_count;
            if (index < indices->_capacity) {
                indices->_count = indices->count() + 1;
            } else {
                List_Resize(indices, index + 1, 4);
            }
            indices->_data[index] = i;
            slot = links->targets->_data + j;
            slots = links->slots;
            index2 = slots->_count;
            if (index2 < slots->_capacity) {
                slots->_count = slots->count() + 1;
            } else {
                List_Resize(slots, index2 + 1, 4);
            }
            slots->_data[index2] = slot;
            j = links->targets->find(target, j + 1);
        }
    }
}

int FUN_001bd890(RemapOwner *o, RemapContext *ctx) {
    int count = o->_items->_count;
    int i;
    for (i = 0; i < count; i++) {
        RemapObject *item = o->_items->_data[i];
        if (igObject_IsKindOf(item, DAT_0055ec28[0]) != 0) {
            RemapEntry *e = ((RemapEntry *)FUN_001a2c70((int)(((void *)igObject_GetAllocator(ctx)))));
            RemapTable *t;
            unsigned int n;
            int j;
            ObjectList_AppendRetained(o->_entries, e);
            release_1bd890(e);
            t = ((RemapTable *)FUN_00139990(((void *)igObject_GetAllocator(ctx))));
            setTarget(e, t);
            release_1bd890(t);
            e->_slot = &o->_items->_data[i];
            setAt(o->_items, i, (RemapObject *)t);
            n = item->_indices->_count;
            setCount_1bd890(t, n);
            for (j = 0; j < (int)n; j++) {
                int r = ctx->_pool->find(item->_indices->_data[j]);
                if (r == -1) {
                    r = 0;
                }
                t->_data[(unsigned int)j] = r;
            }
        } else if (igObject_IsKindOf(item, DAT_0055f360[0]) != 0) {
            RemapEntry *e = ((RemapEntry *)FUN_001a2c70((int)(((void *)igObject_GetAllocator(ctx)))));
            ObjectList_AppendRetained(o->_entries, e);
            release_1bd890(e);
            setTarget(e, item);
            e->_slot = &o->_items->_data[i];
            setAt(o->_items, i, item);
        } else if (DAT_0055f000[0] == item->getMeta()) {
            RemapObject *v = o->_fallback;
            setAt(o->_items, i, v);
        }
    }
    return 0;
}

void FUN_001bf020(void) {

}

