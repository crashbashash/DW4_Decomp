int Gap__Core__igCharMetaField__vfunc_56(void *arg0, char *arg1, int arg2) {
    int sp2C;
    int sp28;
    int t;
    sp2C = 0;
    sp28 = 0;
    sscanf(arg2, DAT_004f9588, &sp28, &sp2C);
    t = sp28;
    *arg1 = t;
    return sp2C;
}

void Gap__Core__igCharMetaField__vfunc_57(int *arg0, int arg1, char *arg2) {
    char sp20[1024];
    int var_v0;
    int var_v1;

    sprintf(sp20, &DAT_004f95c0[0], *arg2);
    if (sp20 == 0) {
        var_v1 = 0;
    } else {
        if (g_stringPool[0] == 0) {
            var_v0 = ((int)StringPool_Allocate(0x10));
            if (var_v0 != 0) {
                var_v0 = ((int)StringPool_Construct((S_2eadf0 *)var_v0));
            }
            g_stringPool[0] = var_v0;
        }
        var_v1 = StringPool_Intern((StringPool *)g_stringPool[0], (const char *)sp20);
    }
    *arg0 = var_v1;
}

int **FUN_002d4d60(int **arg0, int extra1) {
    igMetaField_Construct((igMetaField *)arg0);
    *arg0 = &DAT_00531640[0];
    if (arg0 != 0) {
        FUN_002d4da0(arg0);
    }
    return arg0;
}

int **FUN_002d4da0(int **arg0) {
    igMetaField_Init((igMetaField *)arg0);
    *arg0 = &DAT_00531640[0];
    return arg0;
}

int **FUN_002d4de0(int **arg0, int extra1) {
    igMetaField_CopyConstruct((igMetaField *)arg0, (igMetaField *)extra1);
    *arg0 = &DAT_00531640[0];
    return arg0;
}

void Gap__Core__igCharMetaField__vfunc_02(int extra0) {
    igMetaField_Destruct((igMetaField *)extra0);
}

int FUN_002d4e30(void) {
    return 1;
}

void FUN_002d4e40(void **arg0, char arg1) {
    char sp1F;

    sp1F = arg1;
    ((DW4VC_140_1 *)(arg0))->vX((int)(&sp1F));
}

/* igMetaField slot 27 (+0x6c) for a char array: returns 1, the alignment of a single char element.
 * The receiver is not read. */
int Gap__Core__igCharMetaField__vfunc_27(void) {
    return 1;
}

unsigned short FUN_002d4e80(void *arg0) {
    return *(int *)((char *)(arg0) + 20);
}

int FUN_002d4e90(S_2d4e90 *arg0) {
    int mx = 0;
    int i = 0;
    while (i < arg0->list->count) {
        int r = arg0->list->data[i]->vX();
        if (mx < r) mx = r;
        i++;
    }
    return mx;
}

void FUN_002d4f20(void *arg0, int arg1) {
    int var_s0;
    int *temp_a0;
    void *temp_a0_2;

    for (var_s0 = 0; temp_a0 = (int *)*(int *)((char *)(arg0) + 52), var_s0 < temp_a0[2]; var_s0++) {
        temp_a0_2 = (void *)(*(int *)(temp_a0[4] + (var_s0 * 4)));
        ((C112 *)temp_a0_2)->vX(arg1);
    }
}

void FUN_002d4fa0(void *arg0, int arg1) {
    int i;
    int lst;
    for (i = 0; lst = *(int *)((char *)arg0 + 52), i < *(int *)(lst + 8); i++) {
        ((V120 *)(*(int *)(*(int *)(lst + 16) + i * 4)))->vX(arg1);
    }
}

void FUN_002d5020(S_2d5020 *arg0, int arg1) {
    int i;
    L_2d5020 *l;
    i = 0;
    while (l = arg0->list, i < l->n) {
        l->arr[i]->vX(arg1);
        i++;
    }
}

void FUN_002d50a0(H *arg0, int arg1) {
    int i;
    void **o;
    for (i = 0; i < arg0->list->count; i++) {
        o = arg0->list->items[i];
        ((V128 *)o)->vX(arg1);
    }
}

void FUN_002d5120(A *a, int x) {
    int i;
    for (i = 0; i < a->b->cnt; i++) {
        a->b->arr[i]->vX(x);
    }
}

void FUN_002d51a0(S_2d51a0 *arg0, int arg1) {
    int i = 0;
    while (i < arg0->list->count) {
        arg0->list->data[i]->vX(arg1);
        i++;
    }
}

void FUN_002d5220(void *arg0, int arg1, int arg2) {
    int i;
    for (i = 0; i < (*(L_2d5220 **)((char *)arg0 + 52))->n; i++) {
        (*(L_2d5220 **)((char *)arg0 + 52))->a[i]->vX(arg1, arg2);
    }
}

void FUN_002d52b0(void *arg0, int arg1, int arg2) {
    int i;
    for (i = 0; i < (*(L_2d52b0 **)((char *)arg0 + 52))->n; i++) {
        DW4VC_148 *o = (*(L_2d52b0 **)((char *)arg0 + 52))->arr[i];
        o->vX(arg1, arg2);
    }
}

void FUN_002d5340(H_2d5340 *arg0, int arg1, int arg2) {
    int i;
    void **o;
    for (i = 0; i < arg0->list->count; i++) {
        o = arg0->list->items[i];
        ((V156 *)o)->vX(arg1, arg2);
    }
}

void FUN_002d53d0(S_2d53d0 *arg0, int arg1, int arg2) {
    int i = 0;
    while (i < arg0->list->count) {
        arg0->list->data[i]->vX(arg1, arg2);
        i++;
    }
}

void FUN_002d5460(A_2d5460 *arg0, int arg1, int arg2, int arg3) {
    unsigned int temp_s1;
    unsigned int i;

    temp_s1 = arg0->f52->n;
    for (i = 0; i < temp_s1; i++) {
        arg0->f52->arr[i]->vX(arg1, arg2, arg3);
    }
}

void FUN_002d5500(S52 *arg0, int arg1, int arg2, int arg3) {
    int i;

    for (i = 0; i < arg0->f52->count; i++) {
        arg0->f52->data[i]->vX(arg1, arg2, arg3);
    }
}

int FUN_002d55a0(Self *arg0, int arg1, int arg2) {
    int sum = 0;
    int i;
    for (i = 0; i < arg0->list->count; i++) {
        sum += arg0->list->arr[i]->v41(arg1, arg2);
    }
    return sum;
}

int FUN_002d5640(struct S_2d5640 *arg0, int arg1, int arg2) {
    int i;
    DW4VC_176 *o;

    for (i = 0; i < arg0->list->n; i++) {
        o = (DW4VC_176 *)arg0->list->data[i];
        if (o->vX(arg1, arg2) != 0) {
            return -1;
        }
    }
    return 0;
}

int FUN_002d56e0(O_2d56e0 *arg0, int arg1, int arg2) {
    int i;
    for (i = 0; i < arg0->list->count; i++) {
        if (arg0->list->items[i]->vX(arg1, arg2) == 0) {
            return 0;
        }
    }
    return 1;
}

int FUN_002d5780(T_2d5780 *arg0, int arg1, int arg2) {
    int var_s0;

    for (var_s0 = 0; var_s0 < arg0->f52->f8; var_s0++) {
        if (arg0->f52->f16[var_s0]->vX(arg1, arg2) == 0) {
            return 0;
        }
    }
    return 1;
}

int FUN_002d5820(S_2d5820 *arg0, int arg1, int arg2) {
    int i;

    for (i = 0; i < arg0->l->cnt; i++) {
        if (arg0->l->arr[i]->vX(arg1, arg2) == 0) {
            return 0;
        }
    }
    return 1;
}

int FUN_002d58c0(O_2d58c0 *arg0, int arg1, int arg2) {
    int i;
    for (i = 0; i < arg0->l->n; i++) {
        if (arg0->l->a[i]->vX(arg1, arg2) == 0) {
            return 0;
        }
    }
    return 1;
}

int FUN_002d59f0(Obj_2d59f0 *arg0, int arg1, int arg2, int arg3, int arg4) {
    int sum = 0;
    int n;
    int base;
    int i;
    base = arg0->base;
    n = arg0->arr->n;
    for (i = 0; i < n; i++) {
        Elem *e = arg0->arr->data[i];
        int o = e->off;
        sum += e->run((arg1 + o) - base, (arg2 + o) - base, arg3, arg4);
    }
    return sum;
}

int FUN_002d5ad0(S_2d5ad0 *arg0, int arg1, int arg2, int arg3, int arg4) {
    VC_2d5ad0 *temp_a0;
    int var_s7;
    int temp_v0;
    int temp_s6;
    int temp_s5;
    int var_s4;

    var_s7 = 0;
    var_s4 = 0;
    temp_s5 = arg0->f8;
    temp_s6 = arg0->f34->cnt;
    for (; var_s4 < temp_s6; var_s4++) {
        temp_a0 = (VC_2d5ad0 *)arg0->f34->arr[var_s4];
        temp_v0 = ((E *)temp_a0)->f8;
        var_s7 += temp_a0->vX((arg1 + temp_v0) - temp_s5, (arg2 + temp_v0) - temp_s5, arg3, arg4);
    }
    return var_s7;
}

void FUN_002d5bb0(A_2d5bb0 *arg0, int arg1, int arg2) {
    int var_s3;
    L_2d5bb0 *temp_s2;
    E_2d5bb0 *temp_a0;
    int var_s1;
    int var_s0;

    var_s3 = arg1;
    temp_s2 = arg0->vX()->f52;
    for (var_s1 = 0; var_s1 < arg2; var_s1++) {
        for (var_s0 = 0; var_s0 < temp_s2->count; var_s0++) {
            temp_a0 = temp_s2->data[var_s0];
            temp_a0->vX(var_s3 + temp_a0->f8, 1);
        }
        var_s3 += arg0->f20;
    }
}

int FUN_002d5c80(void) {
    return ((int *)DAT_00586920)[0];
}

void FUN_002d5c90(void *arg0, int arg1) {
    int i;
    int *t;
    VC212 *o;
    i = 0;
    while (t = *(int **)((char *)arg0 + 52), i < t[2]) {
        o = (VC212 *)(*(int *)(t[4] + (i * 4)));
        o->vX(arg1);
        i += 1;
    }
}

int FUN_002d5d10(int *arg0, int arg1, int arg2, int arg3) {
    int b;
    int a;
    Q_2d5d10 *q;
    int i;

    a = 0;
    sscanf(arg2, &DAT_004f95e8[0], &a);
    q = (Q_2d5d10 *)((A_2d5d10 *)arg0)->vX()[13];
    for (i = 0; i < q->count; i++) {
        B_2d5d10 *o = q->data[i];
        o->vX(arg1 + ((int *)o)[2], arg2 + a, arg3);
    }
    sscanf(arg2, &DAT_004f95f0[0], &b);
    return a + b;
}

int FUN_002d5df0(RecoveryString *out, Ctx *ctx, int a2, int a3) {
    char *sepA = (char *)&DAT_004f95f8[0];
    char *sepB = (char *)&DAT_004f9600[0];
    igMetaFieldList *list = (igMetaFieldList *)ctx->get()->_fieldList;
    int n = list->_count;
    RecoveryString *arr = (RecoveryString *)((void *)FUN_00300e00((int)ctx, n, 4));
    int total = 9;
    int i;
    for (i = 0; i < n; i++) {
        int off = i * 4;
        Elem_2d5df0 *e = ((Elem_2d5df0 **)list->_data)[i];
        *(RecoveryString *)((char *)arr + off) = e->vf(a2 + ((igMetaField *)e)->_offset, a3);
        total += strlen(((RecoveryString *)((char *)arr + off))->p) + 1;
    }
    char *buf = ((char *)igObject_AllocateStorage((int)ctx, total));
    strcpy(buf, sepA);
    char *p = buf + 4;
    buf[3] = 0x20;
    for (i = 0; i < n; i++) {
        strcpy(p, arr[i].p);
        p += strlen(arr[i].p);
        *p = 0x20;
        p++;
    }
    strcpy(p, sepB);
    char *r;
    if (buf == 0) r = 0;
    else {
        if (g_stringPool[0] == 0) {
            int v = ((int)StringPool_Allocate(0x10));
            if (v != 0) v = ((int)StringPool_Construct((S_2eadf0 *)v));
            g_stringPool[0] = v;
        }
        r = (char *)StringPool_Intern((StringPool *)g_stringPool[0], (const char *)buf);
    }
    RecoveryString res(r);
    FUN_00300f50((int)ctx, (int)buf);
    out->p = res.p;
    if (out->p != 0) *(int *)(out->p - 4) = *(int *)(out->p - 4) + 1;
    return 0;
}

void FUN_002d6090(void) {

}

int FUN_002d60a0(void) {
    return 1;
}

void FUN_002d60b0(igContext *arg0) {
    if (arg0->_pExtList == 0) {
        igContextExtInfoList *l;
        int meta;
        int i;
        l = ((igContextExtInfoList *)FUN_002cb4b0(((int)igObject_GetAllocator((int)arg0))));
        if (l != 0) ++l->_refCount;
        Util::rel((igObject *)arg0->_pExtList);
        arg0->_pExtList = (int)l;
        {
            igContextExtInfoList *o = (igContextExtInfoList *)arg0->_pExtList;
            --o->_refCount;
            if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy((void *)((igObject *)o));
        }
        ((igObjectDispatchView *)arg0)->getMeta();
        meta = igObjectSystem_FindMetaByNameDefault(igContextExt_className);
        arg0->_iNumExts = igMetaObject_CountTree((MetaTreeNode *)meta) - 1;
        if (arg0->_iNumExts >= ((igContextExtInfoList *)arg0->_pExtList)->_count) List_Reserve((L_2d6680 *)((igContextExtInfoList *)arg0->_pExtList), arg0->_iNumExts, 4);
        ObjectList_ResizeRetained((L_301ee0 *)((igContextExtInfoList *)arg0->_pExtList), arg0->_iNumExts);
        for (i = 0; i < arg0->_iNumExts; i++) {
            int nm;
            igMetaObject *nd;
            igContextExtInfo *it;
            igContextExtInfoList *lst;
            nd = ((igMetaObject *)FUN_002fe300((igMetaObject *)meta, i + 1));
            it = ((igContextExtInfo *)FUN_002cb660(((int)igObject_GetAllocator((int)arg0))));
            if (nd != 0) ++nd->_refCount;
            Util::rel((igObject *)it->_pMeta);
            it->_pMeta = (int)nd;
            nm = nd->_name;
            if (g_stringPool[0] == 0) {
                int al = ((int)StringPool_Allocate(16));
                if (al != 0) al = ((int)StringPool_Construct((struct S_2eadf0 *)al));
                g_stringPool[0] = al;
            }
            {
                int sv = StringPool_Intern((StringPool *)g_stringPool[0], (const char *)nm);
                int old = it->_pName;
                if (old != 0) {
                    int *h = (int *)(old - 8);
                    int c = *(int *)(old - 4) - 1;
                    *(int *)(old - 4) = c;
                    if (c == 0) StringChunk_ReleaseHeader((StringChunkOwnerView *)(*h), (int)h);
                }
                it->_pName = sv;
            }
            it->_pVendorName = 0;
            lst = (igContextExtInfoList *)arg0->_pExtList;
            if (it != 0) ++it->_refCount;
            Util::rel(((igObject **)lst->_data)[i]);
            if (lst->_count != 0 && i >= 0 && i < lst->_count) ((igContextExtInfo **)lst->_data)[i] = it;
            --it->_refCount;
            if ((it->_refCount & 0x7fffff) == 0) igObject_Destroy((void *)((igObject *)it));
        }
    }
}

int FUN_002d6380(void) {
    return ((int *)g_igContext_metaObject)[0];
}

int FUN_002d6390(S_2d6390 *arg0) {
    if (arg0->a == 0) {
        FUN_002d60b0((igContext *)arg0);
    }
    if (arg0->n <= 0) {
        return 0;
    }
    return arg0->a;
}

int FUN_002d63e0(struct A_2d63e0 *arg0, int arg1) {
    int i;
    bool found;
    struct E_2d63e0 *e;

    e = 0;
    if (arg0->f8 == 0) {
        FUN_002d60b0((igContext *)arg0);
    }
    i = 0;
    if (arg0->n <= 0) {
        return 0;
    }
    found = true;
    while (i < arg0->n && found) {
        e = arg0->f8->arr[i];
        if (strcmp(e->name, arg1) == 0) {
            found = false;
        } else {
            i += 1;
        }
    }
    if ((found & 0xFF) == 1) {
        return 0;
    }
    return e->f8;
}

void *FUN_002d64c0(igVisualContext *arg0, int extra1) {
    int temp_v0;
    igObject *var_s0;

    temp_v0 = FUN_002d63e0((struct A_2d63e0 *)arg0, extra1);
    if (temp_v0 == 0) {
        return 0;
    }
    var_s0 = (igObject *)(((void *)FUN_002d65e0((O_2d65e0 *)arg0, temp_v0)));
    if (var_s0 == 0) {
        var_s0 = (igObject *)(((void *)igMetaObject_CreateInstance((CreateMeta *)temp_v0, (MemoryPool *)(((int)igObject_GetAllocator((int)arg0))))));
        if (var_s0 != 0) {
            if (((DW4VC_112_1 *)(((char *)(var_s0) + 0)))->vX((int)(arg0)) == 0) {
                var_s0->_refCount = var_s0->_refCount - 1;
                if ((var_s0->_refCount & 0x7FFFFF) == 0) {
                    igObject_Destroy(var_s0);
                }
                var_s0 = (igObject *)(0);
            } else {
                ObjectList_AppendRetained((igObjectList *)arg0->_pExtInstances, var_s0);
                var_s0->_refCount = var_s0->_refCount - 1;
                if ((var_s0->_refCount & 0x7FFFFF) == 0) {
                    igObject_Destroy(var_s0);
                }
                ((DW4VC_116_1 *)(((char *)(var_s0) + 0)))->vX((int)(arg0));
            }
        }
    }
    return var_s0;
}

int FUN_002d65e0(struct O_2d65e0 *arg0, int arg1) {
    int i;
    for (i = 0; i < arg0->list->n; i++) {
        if (igObject_IsKindOf((void *)arg0->list->arr[i], (igMetaObject *)arg1) != 0) {
            return arg0->list->arr[i];
        }
    }
    return 0;
}

