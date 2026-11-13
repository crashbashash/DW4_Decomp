void FUN_001da6e0(igSorter *arg0) {
    igDataList *h;
    int n;
    struct Obj_1da6e0 **arr;
    struct Pair *p;
    int b;
    h = (igDataList *)arg0->_opaquePackageIndices;
    n = h->_count;
    if (n > 2) {
        FUN_001da220(arg0, 0, n - 1);
        return;
    }
    if (n == 2) {
        int m, t;
        p = (struct Pair *)h->_data;
        b = p->b;
        arr = ((struct Tbl * *)DAT_005629f8)[0]->arr;
        if (arr[b]->key < arr[p->a]->key) {
            m = count_of_1da6e0(h);
            if (m != 0 && 0 < m && m > 1) {
                t = a_of(p);
                p->a = b;
                p->b = t;
            }
        }
    }
}

void FUN_001da790(SorterOpaqueView *o) {
    int c;
    unsigned int prev;
    int start;
    unsigned int key;
    int j;
    int i;
    int *p;
    int n;
    SorterIndexListView *l;
    n = o->_opaquePackageIndices->_count;
    start = 1;
    if (n < 2) { return; }
    while (start > 0) {
        j = start - 1;
        prev = ((SorterPackageListView *)DAT_005629f8[0])->_data[o->_opaquePackageIndices->_data[j]]->key;
        i = start;
        start = 0;
        for (; i < n; i++) {
            l = o->_opaquePackageIndices;
            p = &l->_data[i];
            key = ((SorterPackageListView *)DAT_005629f8[0])->_data[*p]->key;
            if (key < prev) {
                c = l->_count;
                if (c != 0 && i >= 0 && c > i) {
                    j = i - 1;
                    if (j >= 0 && c > j) {
                        const int *value = p;
                        int t = *value;
                        *p = p[-1];
                        p[-1] = t;
                    }
                }
                prev = key;
                if (start == 0) {
                    start = (i > 1) ? i - 1 : 1;
                }
            }
            prev = key;
        }
    }
}

void Gap__Sg__igSorter__vfunc_09(SorterState *o, int arg1) {
    int s3;
    SorterList *s2;
    SorterList *s0;
    SorterList *l;
    if (arg1 == 0) {
        FUN_001db500((A_1db500 *)o);
        o->a->f30(0);
        o->b->f30(1);
        o->b->f31(1);
        o->c->f30(0);
        o->c->f31(1);
        o->l80->cap = o->l80->count;
        s2 = o->l84;
        s3 = s2->count;
        s0 = o->l80;
        if (s3 < s2->cap) {
            s2->count = s2->getCount() + 1;
        } else {
            List_Resize((void *)s2, s3 + 1, 4);
        }
        s2->items[s3] = (int)s0;
        l = o->l88;
        if (l->cap > 0) {
            l->count = 1;
        } else {
            List_Resize((void *)l, 1, 4);
        }
        setRef(o->l88, 0, DAT_0048dae8[0]);
    }
}

void FUN_001db500(A_1db500 *arg0) {
    int temp_s0;
    int temp_s0_2;
    int temp_s2_2;
    int temp_s3;
    L_1db500 *temp_s1;
    L_1db500 *temp_s2;

    temp_s0 = arg0->f36;
    temp_s2 = arg0->f8->f12;
    temp_s3 = temp_s2->count;
    if (temp_s3 < temp_s2->cap) {
        temp_s2->count = count_of_1db500(temp_s2) + 1;
    } else {
        List_Resize((void *)temp_s2, temp_s3 + 1, 4);
    }
    temp_s2->data[temp_s3] = temp_s0;
    temp_s0_2 = arg0->f40;
    temp_s1 = arg0->f8->f12;
    temp_s2_2 = temp_s1->count;
    if (temp_s2_2 < temp_s1->cap) {
        temp_s1->count = count_of_1db500(temp_s1) + 1;
    } else {
        List_Resize((void *)temp_s1, temp_s2_2 + 1, 4);
    }
    temp_s1->data[temp_s2_2] = temp_s0_2;
}

void Gap__Sg__igSorter__vfunc_24(Sorter *arg0) {
    int i;
    List_1db5d0 *l;
    EL *e;
    if (arg0->f112 != 0) { arg0->f112 = 0; }
    arg0->f128 = 0;
    i = 0;
    arg0->f32->f8 = 0;
    arg0->f24->f8 = 0;
    arg0->f28->f8 = 0;
    for (; i < arg0->f16->f8; i++) {
        l = arg0->f16->f16[i]->f28;
        if (0 <= l->f12) { l->f8 = 0; } else { List_Resize((void *)l, 0, 4); }
    }
    arg0->f16->f20 = 0;
    arg0->f40->vX();
    arg0->f44->vX();
    arg0->f48->vX();
    arg0->f92->vX();
    arg0->f96->vX();
    arg0->f36->vX();
    arg0->f8->vX();
    FUN_001db500((A_1db500 *)arg0);
    arg0->f104->f8 = 0;
    arg0->f108->f8 = 0;
    arg0->f124 = 0;
}

void FUN_001dc400(igSorter *arg0, igGroup *arg1, igAttrStackManager *arg2) {
    igAttrStack *e;
    int v;
    int n;
    struct L_1dc400 *l;
    e = ((igAttrStack **)((igAttrStackList *)arg2->_attrStacks)->_data)[((int *)arg2->_attrStackIndexTable)[g_igModelViewMatrixAttr_metaObject[0]->_id]];
    if (e->_count == 0) {
        v = 0;
    } else {
        v = *(int *)((char *)e->_data + (e->_count - 1) * 4);
    }
    l = ((struct LA_1dc400 *)arg0->_lightAttrs)->l;
    n = l->cnt;
    if (n < l->cap) {
        l->cnt = cnt_of(l) + 1;
    } else {
        List_Resize((void *)l, n + 1, 4);
    }
    l->data[n] = v;
    List_AppendWords(((struct LA_1dc400 *)arg0->_lightAttrs)->l, ((igNodeList *)arg1->_childList)->_count, ((igNodeList *)arg1->_childList)->_data);
}

void FUN_001dc500(A_1dc500 *arg0, unsigned char arg1, int arg2) {
    int temp_a0;
    L_1dc500 *temp_s0;
    X_1dc500 *temp_s0_2;
    X_1dc500 *t;
    L2 *temp_a0_3;

    arg0->f120 = arg0->f120 + 1;
    if (arg0->f112 == 0) {
        arg0->f112 = 1;
        arg0->f113 = arg1;
        arg0->f114 = arg2;
        temp_s0 = arg0->f16;
        if (temp_s0->f20 >= temp_s0->f8) {
            igObjectPool_Grow((List_1dca40 *)temp_s0, (Obj_1dca40 * (*)(int))&FUN_00197ab0);
        }
        temp_a0 = temp_s0->f20;
        temp_s0->f20 = temp_a0 + 1;
        temp_s0_2 = temp_s0->f16[temp_a0];
        temp_s0_2->f12 = temp_s0_2->f8;
        if (temp_s0_2 != 0) {
            temp_s0_2->f4 = temp_s0_2->f4 + 1;
        }
        t = arg0->f116;
        if (t != 0) {
            t->f4 = t->f4 - 1;
            if (((unsigned long long) ((long long) t->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy((void *)t);
            }
        }
        arg0->f116 = temp_s0_2;
        temp_a0_3 = arg0->f116->f28;
        if (0 <= temp_a0_3->f12) {
            temp_a0_3->f8 = 0;
            return;
        }
        List_Resize((void *)temp_a0_3, 0, 4);
    }
}

void igSwitch_EnableChild(void *arg0, unsigned int arg1) {
    int *temp_a1;
    int temp_a2_2;
    unsigned int temp_a3;
    void *temp_a2;
    int nv;

    temp_a2 = (void *)(*(int *)((char *)(arg0) + 32));
    temp_a3 = arg1 >> 5;
    temp_a1 = (int *)(*(int *)((char *)(temp_a2) + 16) + (temp_a3 * 4));
    temp_a2_2 = *(int *)((char *)(temp_a2) + 8);
    nv = (1 << (arg1 & 0x1F)) | *temp_a1;
    if ((temp_a2_2 != 0) && ((int) temp_a3 >= 0) && ((int) temp_a3 < temp_a2_2)) {
        *temp_a1 = nv;
    }
}

void igSwitch_EnableAllChildren(int *p)
{
    igBitMask_SetAll((igDataList *)(*(int *)((char *)p + 32)));
}

void igSwitch_DisableChild(void *arg0, unsigned int arg1) {
    int *temp_a1;
    int temp_a2_2;
    unsigned int temp_a3;
    void *temp_a2;
    int v;

    temp_a2 = (void *)(*(int *)((char *)(arg0) + 32));
    temp_a3 = arg1 >> 5;
    temp_a1 = (int *)(*(int *)((char *)(temp_a2) + 16) + (temp_a3 * 4));
    temp_a2_2 = *(int *)((char *)(temp_a2) + 8);
    v = ~(1 << (arg1 & 0x1F)) & *temp_a1;
    if ((temp_a2_2 != 0) && ((int) temp_a3 >= 0) && ((int) temp_a3 < temp_a2_2)) {
        *temp_a1 = v;
    }
}

void igSwitch_DisableAllChildren(int *p)
{
    igBitMask_ClearAll((igDataList *)(*(int *)((char *)p + 32)));
}

int igSwitch_AppendChild(void *arg0, int arg1) {
    int temp_s0;
    int var_a1;
    int a0v;
    void *temp_v0;

    temp_s0 = igGroup_AppendChild((void *)arg0, arg1);
    temp_v0 = (void *)(*(int *)((char *)(arg0) + 28));
    a0v = *(int *)((char *)(arg0) + 32);
    if (temp_v0 != 0) {
        var_a1 = *(int *)((char *)(temp_v0) + 8);
    } else {
        var_a1 = 0;
    }
    FUN_001b1e50((void *)a0v, var_a1);
    return temp_s0;
}

