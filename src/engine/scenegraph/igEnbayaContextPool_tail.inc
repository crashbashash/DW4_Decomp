void Gap__Sg__igEnbayaContextPool__vfunc_13(int arg0) {
    void *sp5C;
    int var_a0;
    int temp_s2;
    int var_s1;
    int sp58;
    int var_a2;
    int temp_s0;
    int sp54;
    int var_v0;

    Gap__Core__igObject__resetFields();
    temp_s2 = *(int *)((char *)(g_objectSystem[0]) + 56);
    var_v0 = igObject_GetAllocator(arg0);
    var_v0 = g_useOwnerAllocator != 0 ? var_v0 : Memory_GetAllocatorBySelector(g_temporaryAllocatorSelector[0]);
    sp5C = (void *)(igStringObj_Create(var_v0));
    temp_s0 = FUN_003064b0(temp_s2, 7);
    var_s1 = 0;
    while (var_s1 < temp_s0) {
        if (igRegistry_GetKeyName(temp_s2, 7, var_s1, &sp5C) != 0) {
            sp58 = 0;
            var_a2 = *(int *)((char *)(sp5C) + 8);
            var_a2 = (var_a2 == 0) ? ((int *)g_stringObjEmptyText)[0] : var_a2;
            if (FUN_003065f0(temp_s2, 7, var_a2, &sp58, 0, 0) != 0) {
                sp54 = 0;
                var_a0 = *(int *)((char *)(sp5C) + 8);
                var_a0 = (var_a0 == 0) ? ((int *)g_stringObjEmptyText)[0] : var_a0;
                if ((sscanf(var_a0, &text_enbayaContextPool_d[0], &sp54) == 1) && (sp54 >= 0) && (sp58 >= 0)) {
                    FUN_001c1a80((T_1c1a80 *)arg0, sp54, sp58);
                }
            }
        }
        var_s1 += 1;
    }
    var_v0 = (int)sp5C;
    if (var_v0 != 0) {
        *(int *)((char *)(var_v0) + 4) = (int)((int) (*(int *)((char *)(var_v0) + 4) - 1));
        if (((unsigned long long) ((long long) *(int *)((char *)(var_v0) + 4) << 0x29) >> 0x29) == 0) {
            igObject_Destroy((void *)var_v0);
        }
    }
}

void Gap__Sg__igEnbayaContextPool__vfunc_04(Obj_1c1450 *arg0) {
    int i;
    int n;
    L_1c1450 *inner;
    int j;
    int m;
    L_1c1450 *d;
    void *x;
    Alloc *al;
    n = arg0->outer->count;
    for (i = 0; i < n; i++) {
        d = arg0->dst;
        inner = (L_1c1450 *)arg0->outer->data[i];
        if (d->count != 0 && i >= 0 && i < d->count) {
            d->data[i] = DAT_0048da00[0];
        }
        m = inner->count;
        for (j = 0; j < m; j++) {
            x = (void *)inner->data[j];
            al = ((Alloc *)igObject_GetAllocator(arg0));
            al->vX(x);
        }
    }
    Gap__Core__igObject__destructFields(arg0);
}

int FUN_001c1560(T_1c1560 *arg0, int arg1) {
    int i;
    int r;
    L_1c1560 *l;
    int n;
    int s1;
    int nv;
    L_1c1560 *q;
    int v;
    l = arg0->f12;
    n = l->n;
    for (i = 0; i < n; i++) { if (arg1 == l->d[i]) { r = i; goto found; } }
    r = -1;
found:
    if (r == -1) {
        FUN_001c17e0((EnbayaContextPoolView *)arg0, arg1);
        r = arg0->f8->n - 1;
    }
    s1 = arg0->f16->d[r];
    if (s1 >= ((O_1c1560 *)arg0->f8->d[r])->c) {
        /* matching construct: permuter — l reused for arg0->f8 before the grow call */
        l = arg0->f8;
        FUN_001c1a80((T_1c1a80 *)arg0, arg1, ((O_1c1560 *)l->d[r])->c + 1);
    }
    v = ((int *)((L_1c1560 *)arg0->f8->d[r])->d)[s1];
    nv = s1 + 1;
    q = arg0->f16;
    if (q->n != 0 && r >= 0 && r < q->n) q->d[r] = nv;
    return v;
}

void FUN_001c17e0(EnbayaContextPoolView *o, int boneCount) {
    EnbayaIntList *l0;
    int n1;
    EnbayaIntList *l1;
    int n2;
    int i;
    PoolObject *held;
    int n0;
    EnbayaIntList *l2;
    l0 = o->_boneCountList;
    n0 = l0->_count;
    if (findIndex(l0, n0, boneCount, i) == -1) {
        PoolListHolder list;
        list.p = FUN_002c9130(igObject_GetAllocator(o));
        ObjectList_AppendRetained(o->_poolList, list.p);
        l1 = o->_boneCountList;
        n1 = l1->_count;
        if (n1 < l1->_capacity) {
            l1->_count = l1->count() + 1;
        } else {
            List_Resize((void *)l1, n1 + 1, 4);
        }
        l1->_data[n1] = boneCount;
        l2 = o->_freeIndexList;
        n2 = l2->_count;
        if (n2 < l2->_capacity) {
            l2->_count = l2->count() + 1;
        } else {
            List_Resize((void *)l2, n2 + 1, 4);
        }
        l2->_data[n2] = DAT_0048da08[0];
        held = list.p;
        if (held != 0) {
            held->_refCount = held->_refCount - 1;
            if (((unsigned long long)((long long)held->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy((void *)held);
            }
        }
    }
}

void FUN_001c1a80(T_1c1a80 *arg0, int arg1, int arg2) {
    int i;
    int r;
    L_1c1a80 *l;
    int n;
    FUN_001c17e0((EnbayaContextPoolView *)arg0, arg1);
    l = arg0->f12;
    n = l->n;
    for (i = 0; i < n; i++) { if (arg1 == l->d[i]) { r = i; goto found; } }
    r = -1;
found:
    if (r == -1) {
        FUN_001c17e0((EnbayaContextPoolView *)arg0, arg1);
        r = arg0->f8->n - 1;
    }
    FUN_001c1950(arg0, arg0->f8->d[r], arg1, arg2);
}

