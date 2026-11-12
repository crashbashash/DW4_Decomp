void FUN_002d38e0(int a0, int a1)
{
    *(int *)((char *)a0 + 12) = a1;
}

void FUN_002d38f0(void *arg0) {
    int temp_a1;
    void *temp_a0;

    temp_a1 = *(int *)((char *)(arg0) + 8);
    temp_a0 = (void *)(*(int *)((char *)(arg0) + 16));
    if (temp_a1 >= *(int *)((char *)(temp_a0) + 8)) {
        List_Reserve((L_2d6680 *)temp_a0, temp_a1, 4);
    }
    ((DW4VC_124_1 *)(((char *)(arg0) + 0)))->vX((int)(*(int *)((char *)(arg0) + 12)));
}

void FUN_002d3950(struct S_2d3950 *arg0) {
    struct L_2d3950 *temp_a0;
    struct L_2d3950 *temp_a0_2;
    struct L_2d3950 *temp_a0_3;
    struct L_2d3950 *temp_a0_4;
    struct L_2d3950 *temp_a0_5;
    temp_a0 = arg0->f16;
    if (!(0 > temp_a0->cap)) {
        temp_a0->cnt = 0;
    } else {
        List_Resize(temp_a0, 0, 4);
    }
    temp_a0_2 = arg0->f16;
    if (!(0 < temp_a0_2->cnt)) {
        List_Reserve((L_2d6680 *)temp_a0_2, 0, 4);
    }
    temp_a0_3 = arg0->f20;
    if (!(0 > temp_a0_3->cap)) {
        temp_a0_3->cnt = 0;
    } else {
        List_Resize(temp_a0_3, 0, 4);
    }
    temp_a0_4 = arg0->f20;
    if (temp_a0_4 != 0) {
    if (!(0 > temp_a0_4->cap)) {
        temp_a0_4->cnt = 0;
    } else {
        List_Resize(temp_a0_4, 0, 4);
    }
    temp_a0_5 = arg0->f20;
    if (!(0 < temp_a0_5->cnt)) {
        List_Reserve((L_2d6680 *)temp_a0_5, 0, 4);
    }
    }
}

void FUN_002d3a20(void **arg0) {
    DW4SR4 sp1C;

    sp1C = ((DW4VCSR_96_1 *)(arg0))->vX((int)(0));
}

int Gap__Core__igCallStackTable__vfunc_23(void *arg0) {
    void *obj;
    int *p;
    int n;
    int i;
    int cnt;

    obj = (void *)(*(int *)((char *)(arg0) + 16));
    cnt = 0;
    p = (int *)(*(int *)((char *)(obj) + 16));
    n = *(int *)((char *)(obj) + 8);
    for (i = 0; i < n; i++) {
        if (*p == 0) {
            cnt++;
        }
        p++;
    }
    return cnt;
}

void Gap__Core__igCallStackTable__vfunc_24(int *arg0, struct S_2d3aa0 *arg1, int arg2) {
    struct L_2d3aa0 *l;
    int i;
    int cnt;
    int *data;
    int n;
    int t;
    l = arg1->f16;
    data = l->data;
    n = l->n;
    cnt = 0;
    if (arg2 == 0) {
        if (0 <= l->cap) { l->n = 0; } else { List_Resize(l, 0, 4); }
        *arg0 = g_statusSucceeded.v;
        return;
    }
    for (i = 0; i < n; i++) {
        if (data[0] == 0) {
            cnt = cnt + 1;
            if (cnt == arg2) {
                t = i + 1;
                if (t >= 0) {
                    if (t <= l->cap) { l->n = t; } else { List_Resize(l, t, 4); }
                }
                *arg0 = g_statusSucceeded.v;
                return;
            }
        }
    }
    *arg0 = g_allocatorFailureStatus.v;
}

int *Gap__Core__igCallStackTable__vfunc_25(struct O_2d3b80 *o, int i) {
int *r; if (i < 0 || i >= o->l->count || o->l->data == 0) { r = 0; } else { r = o->l->data + i; if (i > 0 && r[-1] != 0) r = 0; } return r;
}

void Gap__Core__igCallStackTable__vfunc_27(O_2d3cd0 *o, int x) { switch (o->v26()) { case -1: o->v24(x); break; default: break; } }

unsigned int Gap__Core__igCallStackTable__vfunc_29(CallStackTableView *self, unsigned int *stack) {
    CallStackHashTable *t = self->table;
    unsigned int sum = 0;
    unsigned int n;
    unsigned int v;
    unsigned int r;
    if (t != 0) { n = t->count; } else { n = 0; }
    if (stack != 0 && t != 0) {
        r = 0;
        if (n != 0) {
            v = *stack;
            while (v != 0) { sum += v; stack++; v = *stack; }
            r = sum % n;
        }
    } else {
        r = 0;
    }
    return r;
}

static inline void setAt(CallStackIndexCells *l, int i, int v) {
    if (l->count != 0 && i >= 0 && i < l->count) {
        l->data[i] = v;
    }
}

int Gap__Core__igCallStackTable__vfunc_30(CallStackTableHashView *self, int *key, int value) {
    int tries = 0;
    int n = self->index->count;
    int half = n / 2;
    int h;
    CallStackIndexList *index;
    if (n != 0) {
        h = self->Hash(key);
        index = self->index;
        do {
            if (index->data[h] == -1) {
                setAt((CallStackIndexCells *)index, h, value);
                goto ok;
            }
            h++;
            if (h >= n) {
                h = 0;
            }
            tries++;
        } while (tries < half);
        self->Rehash(n * 2);
        return 0;
    }
ok:
    return 1;
}

void Gap__Core__igCallStackTable__vfunc_31(T_2d40f0 *self, int arg1)
{
    Ref *r;
    int cnt;
    IList *l;
    unsigned *var_a1_2;
    unsigned *data;
    int var_a0;
    IList *v;
    unsigned *temp_s2;
    int var_a1;
    unsigned *temp_s1_2;
    unsigned *var_s0;
    int temp_s1;

    FUN_002d38e0((int)self, arg1);
    if (arg1 != 0) {
        if (self->list == 0) {
            temp_s1 = ((int)igObject_GetAllocator((int)self));
            r = (Ref *)self->list;
            if (r != 0) {
                r->u.w = r->u.w - 1;
                if (r->u.b.cnt == 0) igObject_Destroy(r);
            }
            self->list = (IList *)FUN_002ca8b0(temp_s1);
        }
        l = self->list;
        if (arg1 >= l->count) List_Reserve((L_2d6680 *)l, arg1, 4);
        l = self->list;
        if (arg1 >= 0) {
            if (arg1 <= l->cap) l->count = arg1;
            else List_Resize(l, arg1, 4);
        }
        v = self->list;
        cnt = v->count;
        data = v->data;
        for (var_a1 = 0; var_a1 < cnt; var_a1++) data[var_a1] = *(unsigned *)DAT_004c1e98;
        temp_s2 = self->tab->data;
        var_s0 = temp_s2;
        temp_s1_2 = temp_s2 + self->tab->count;
        while (var_s0 < temp_s1_2) {
            if (!self->v28(var_s0, var_s0 - temp_s2)) return;
            var_a1_2 = var_s0;
            var_a0 = 0;
            while (*var_a1_2++ != 0) var_a0++;
            var_s0 += var_a0 + 1;
        }
    } else {
        r = (Ref *)self->list;
        if (r != 0) {
            if (r != 0) {
                r->u.w = r->u.w - 1;
                if (r->u.b.cnt == 0) igObject_Destroy(r);
            }
            self->list = 0;
        }
    }
}

