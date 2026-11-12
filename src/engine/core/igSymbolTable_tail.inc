void FUN_0030da10(int a0, int a1)
{
    *(int *)((char *)a0 + 12) = a1;
}

void FUN_0030da20(S_30da20 *arg0, unsigned arg1, unsigned arg2) {
    unsigned temp_a2;

    arg0->f16 = arg1;
    arg0->f20 = arg2;
    temp_a2 = arg0->f12;
    if (temp_a2 != 0) {
        arg0->f24 = (arg0->f20 - arg0->f16) / temp_a2;
        if (((arg0->f20 - arg0->f16) % arg0->f12) != 0) {
            arg0->f24 = arg0->f24 + 1;
        }
    } else {
        arg0->f24 = 1;
    }
}

void FUN_0030daa0(int *arg0) {
    int *temp_a0;
    int temp_a1;
    temp_a1 = arg0[2] * 4;
    temp_a0 = (int *)arg0[7];
    if (temp_a1 >= temp_a0[2]) {
        List_Reserve((L_2d6680 *)temp_a0, temp_a1, 4);
    }
    ((A_30daa0 *)arg0)->vX(arg0[3]);
    FUN_0030cf20(arg0[9], arg0[2] * 4);
    FUN_0030cf30(arg0[9], arg0[2]);
    FUN_0030cf40((void *)arg0[9]);
    FUN_0030cf20(arg0[10], 0x1000);
    FUN_0030cf30(arg0[10], 0x100);
    FUN_0030cf40((void *)arg0[10]);
}

/* Number of symbols in the table. The symbols list stores four ints per symbol, so the count is
 * the list length divided by four (the resize sibling vfunc_24 sets the length to count << 2). */

int Gap__Core__igSymbolTable__vfunc_23(igSymbolTable *self) {
    return ((igDataList *)(self->_symbols))->_count / 4;
}

void Gap__Core__igSymbolTable__vfunc_24(int *arg0, struct T_30db60 *arg1, int arg2) {
    struct L_30db60 *l = arg1->list;
    int n = arg2 << 2;
    if (n >= 0) {
        if (n <= l->cap) {
            l->len = n;
        } else {
            List_Resize((void *)l, n, 4);
        }
    }
    *arg0 = g_statusSucceeded.v;
}

igResult_30dbc0 Gap__Core__igSymbolTable__vfunc_25(Table *self, int idx, char *name, int nameSize, int *a, int *b, char *path, int pathSize) {
    igResult_30dbc0 result = (*(igResult_30dbc0 *)&g_allocatorFailureStatus);
    Entry_30dbc0 *e;
    char *s;

    if (idx >= 0 && idx * 4 < self->entries->count) {
        e = &self->entries->data[idx];
        *a = e->a;
        if (name != 0) {
if ((s = FUN_0030d1d0((int *)self->names, e->name)) != 0) { strncpy(name, s, nameSize); } else { *name = 0; }
        }
        *b = e->b;
        if (path != 0) {
if ((s = FUN_0030d1d0((int *)self->paths, e->path)) != 0) { strncpy(path, s, pathSize); } else { *path = 0; }
        }
        result = (*(igResult_30dbc0 *)&g_statusSucceeded);
    } else {
        if (name != 0) {
            *name = 0;
        }
        *a = 0;
        *b = 0;
        if (path != 0) {
            *path = 0;
        }
    }
    return result;
}

int Gap__Core__igSymbolTable__vfunc_26(O_30dcf0 *o, unsigned key) {
E_30dcf0 *en1; int len2; int i; int i0; int e1; int len1; unsigned st2; int cnt; int e2; unsigned end1; unsigned end2; int k; unsigned st1; int j; E_30dcf0 *en2; L_30dcf0 *l;
    i0 = o->v28();
    i = i0;
    l = o->idx;
    cnt = l->cnt;
    j = 0;
    for (;;) {
        e1 = l->arr[i];
        if (e1 == -1) break;
        en1 = &o->ents->arr[e1];
        len1 = en1->len;
        if (len1 != 0) { st1 = en1->start; end1 = st1 + len1; }
        else { st1 = en1->start; end1 = st1 + len1 + 1; }
        if (key >= st1) { if (key <= end1) return e1; }
        i++;
        if (i >= cnt) i = 0;
        j++;
        if (j >= cnt) return -1;
    }
    k = i0 - 1;
    L2 *l2 = (L2*)l;
    while (k > 0) {
        if (l2->arr[k] != (unsigned)-1) break;
        k--;
    }
    while (k > 0) {
        e2 = l2->arr[k];
        if (e2 == -1) return -1;
        en2 = &o->ents->arr[e2];
        len2 = en2->len;
        if (len2 != 0) { st2 = en2->start; end2 = st2 + len2; }
        else { st2 = en2->start; end2 = st2 + len2 + 1; }
        if (key >= st2) { if (key <= end2) return e2; }
        k--;
    }
    return -1;
}

void Gap__Core__igSymbolTable__vfunc_27(int *out, O_30de90 *o, int a, int b, int c, int d, int e, int f, int g, int *h) {
    S_30de90 r;
    int i = o->v24(a);
    r.v = g_allocatorFailureStatus.v;
    *h = 0;
    if (i != -1) r = o->v23(i, b, c, d, e, f, g);
    *out = r.v;
}

void Gap__Core__igSymbolTable__vfunc_28(O_30df60 *o, int a, int b, int c, int d) { switch (o->v24(b)) { case -1: o->v27(a, b, c, d); break; default: break; } }

unsigned int Gap__Core__igSymbolTable__vfunc_30(igSymbolTable *arg0, int arg1) {
    unsigned int temp_a2;
    unsigned int temp_v1;
    unsigned int var_v0;

    temp_a2 = arg0->_hashCapacity;
    var_v0 = 0;
    if (temp_a2 != 0) {
        temp_v1 = arg0->_hashIncrement;
        if (temp_v1 != 0) {
            var_v0 = (int)((unsigned int) ((unsigned int) (arg1 - arg0->_lowAddress) / temp_v1) % temp_a2);
        }
    }
    return var_v0;
}

static inline void setAt_30e190(List_30e190 *l, int i, int v) { if (l->count != 0 && i >= 0 && i < l->count) { ((List_30e190 *)l)->data[i] = v; } }

int Gap__Core__igSymbolTable__vfunc_31(Table_30e190 *self, int key, int key2, int value) {
    int probes = 0;
    int size = self->hash->count;
    int half = size / 2;
    int idx;
    List_30e190 *l;

    if (size != 0) {
        idx = self->vHash(key, key2);
        l = self->hash;
        do {
            if (l->data[idx] == -1) {
                setAt_30e190(l, idx, value);
                goto done;
            }
            idx++;
            if (idx >= size) {
                idx = 0;
            }
            probes++;
        } while (probes < half);
        self->vRehash(size * 2);
        return 0;
    }
done:
    return 1;
}

static inline void reserve(List_30e2a0 *l, int n) { if (n >= l->count) { List_Reserve((L_2d6680 *)l, n, 4); } }

static inline void setCount_30e2a0(List_30e2a0 *l, int n) { if (n >= 0) { if (n <= l->capacity) { l->count = n; } else { List_Resize(l, n, 4); } } }

void Gap__Core__igSymbolTable__vfunc_32(Table_30e2a0 *self, int n) {
    List_30e2a0 *l;
    int count;
    int *data;
    int i;
    Entry_30e2a0 *begin;
    Entry_30e2a0 *end;
    Entry_30e2a0 *e;

    FUN_0030da10((int)self, n);
    reserve(self->hash, n);
    setCount_30e2a0(self->hash, n);
    l = self->hash;
    count = l->count;
    data = (int *)l->data;
    for (i = 0; i < count; i++) {
        data[i] = DAT_004c2300;
    }
    if (self->bucketSize != 0) {
        self->buckets = (self->end - self->start) / self->bucketSize;
        if ((self->end - self->start) % self->bucketSize != 0) {
            self->buckets = self->buckets + 1;
        }
    } else {
        self->buckets = 1;
    }
    l = self->entries;
    begin = (Entry_30e2a0 *)l->data;
    end = begin + l->count / 4;
    for (e = begin; e < end; e++) {
        int bb = e->b; if (self->vX(e->a, bb, e - begin) == 0) {
            break;
        }
    }
}

int FUN_0030e430(int *arg0, void *arg1, int arg2) {
    *(int *)((char *)arg1 + 24) = arg2;
    *arg0 = *(int *)0x4FB410;
}

