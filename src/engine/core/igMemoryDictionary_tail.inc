/* Accessor: number of entry slots allocated (`_capacity`, +8). */

int Gap__Core__igMemoryDictionary__vfunc_23(igMemoryDictionary *self) {
    return self->_capacity;
}

/* Setter for the dictionary capacity (`_capacity`, +8). */

void Gap__Core__igMemoryDictionary__vfunc_24(igMemoryDictionary *self, int capacity) {
    self->_capacity = capacity;
}

void Gap__Core__igMemoryDictionary__vfunc_25(D *arg0) {
    int a;
    int b;
    L_2ee530 *l;

    a = arg0->n * 2;
    l = arg0->list;
    if (a >= l->count) {
        List_Reserve((L_2d6680 *)l, a, 4);
    }
    b = arg0->n * 2;
    l = arg0->list;
    if (b >= 0) {
        if (b <= l->cap) {
            l->count = b;
        } else {
            List_Resize(l, b, 4);
        }
    }
    arg0->vf();
}

void Gap__Core__igMemoryDictionary__vfunc_26(struct D_2ee5c0 *arg0) {
    struct L_2ee5c0 *temp_a0;
    struct L_2ee5c0 *temp_a0_2;

    temp_a0 = arg0->list;
    if (0 <= temp_a0->cap) {
        temp_a0->count = 0;
    } else {
        List_Resize(temp_a0, 0, 4);
    }
    temp_a0_2 = arg0->list;
    if (!(0 < temp_a0_2->count)) {
        List_Reserve((L_2d6680 *)temp_a0_2, 0, 4);
    }
    arg0->fc = 0;
    arg0->f14 = 0;
}

/* Predicate: true once the dictionary has storage allocated, i.e. its `_capacity` (+8) is non-
 * zero. */

int Gap__Core__igMemoryDictionary__vfunc_28(igMemoryDictionary *self) {
    return self->_capacity != 0;
}

void Gap__Core__igMemoryDictionary__vfunc_27(struct O_2ee640 *arg0) {
    struct T_2ee640 *t; int half; int j; struct P_2ee640 *pp; int n; int i;
    t = arg0->t;
    half = *(int *)((char *)t + 8) / 2;
    pp = t->items;
    n = t->count;
    for (i = 0; i < n; i++) {
        ((int *)pp)[i] = DAT_004c2150[0];
    }
    arg0->f12 = 0;
    arg0->f20 = 0;
    for (j = 0; j < half; j++) {
        pp->b = -1;
        pp++;
    }
}

/* Accessor: number of entries in use (`_count`, +12). */

int Gap__Core__igMemoryDictionary__vfunc_29(igMemoryDictionary *self) {
    return self->_count;
}

void Gap__Core__igMemoryDictionary__vfunc_30(int *arg0, D_2ee6d0 *arg1, int arg2, int *arg3) {
    E_2ee6d0 *e;
    int idx;
    int n;
    int i;
    int res;
    S_2ee6d0 *s;
    e = &arg1->f10->f10[arg1->f14];
    if (e->key == arg2) {
        *arg3 = e->val;
        *arg0 = g_resultSuccess.v;
        return;
    }
    idx = arg1->vX(arg2);
    s = arg1->f10;
    n = s->f8 / 2;
    res = g_resultFailure.v;
    i = 0;
    e = &s->f10[idx];
    do {
        if (e->key == arg2) {
            *arg3 = e->val;
            res = g_resultSuccess.v;
            arg1->f14 = idx;
            break;
        }
        if (e->val == -1) {
            break;
        }
        idx++;
        if (idx >= n) {
            e = *(E_2ee6d0 **)&s->f10;
            idx = 0;
        } else {
            e++;
        }
        i++;
    } while (i < n);
    *arg0 = res;
}

R_2ee800 Gap__Core__igMemoryDictionary__vfunc_31(D_2ee800 *arg1, int key, int val) {
    int probes = 0;
    int cap = arg1->f10->f8 / 2;
    int half = cap / 2;
    int idx;
    S_2ee800 *s;
    E_2ee800 *e;
    if (cap != 0) {
        idx = arg1->v132(key);
        s = arg1->f10;
        e = &s->f10[idx];
        do {
            if (e->key == key) {
                e->val = val;
                return R_2ee800(g_resultSuccess.v);
            }
            if (e->key == 0) {
                e->key = key;
                e->val = val;
                arg1->f12 = arg1->f12 + 1;
                if (probes >= half) {
                    return arg1->v136(cap * 2);
                }
                return R_2ee800(g_resultSuccess.v);
            }
            idx++;
            if (idx >= cap) {
                e = *(E_2ee800 **)&s->f10;
                idx = 0;
            } else {
                e++;
            }
            probes++;
        } while (probes < cap);
    }
    return R_2ee800(g_resultFailure.v);
}

R_2ee970 Gap__Core__igMemoryDictionary__vfunc_32(Dict *arg1, int arg2) {
    int i;
    int half;
    int idx;
    Ent_2ee970 *e;
    Ent_2ee970 *next;
    Tbl *t;

    i = 0;
    half = arg1->t->cap / 2;
    if (half != 0) {
        idx = ((VT_2ee970 *)arg1)->vFind(arg2);
        t = arg1->t;
        e = t->ents + idx;
        do {
            idx += 1;
            next = e + 1;
            if (idx >= half) {
                next = *(Ent_2ee970 **)&t->ents;
                idx = 0;
            }
            if (e->key == arg2) {
                e->key = 0;
                arg1->cnt = arg1->cnt - 1;
                if (next->state == -1) {
                    e->state = -1;
                } else {
                    e->state = -2;
                }
                goto ok;
            }
            if (e->state == -1) {
                return R_2ee970(g_resultFailure.v);
            }
            i += 1;
            e = next;
        } while (i < half);
        return R_2ee970(g_resultFailure.v);
    }
ok:
    return R_2ee970(g_resultSuccess.v);
}

/* Hash-bucket index for `key`: key modulo the table capacity (`_capacity`), or 0 for an empty
 * table. */

unsigned int Gap__Core__igMemoryDictionary__vfunc_33(igMemoryDictionary *self, unsigned int key) {
    unsigned int capacity;

    capacity = self->_capacity;
    if (capacity != 0) {
        return key % capacity;
    }
    return 0U;
}

int Gap__Core__igMemoryDictionary__vfunc_34(int *result, Dict_2eeae0 *dict, int capacity) {
    igSmartPointer<Tbl_2eeae0> previous(dict->t, kRetainReference);
    int count = previous.get()->size;
    int *entry = previous.get()->data;
    int allocator;
    Tbl_2eeae0 *table;
    int words;
    int i;
    dict->f8 = capacity;
    dict->f20 = 0;
    allocator = ((int)igObject_GetAllocator((int)dict));
    table = dict->t;
    if (table != 0) {
        table->_refCount = table->_refCount - 1;
        if ((table->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(table);
        }
    }
    dict->t = (Tbl_2eeae0 *)FUN_002ca260(allocator);
    words = dict->f8 * 2;
    if (words >= dict->t->size) {
        List_Reserve((L_2d6680 *)dict->t, words, 4);
    }
    table = dict->t;
    if (table->data == 0) {
        *result = g_resultFailure.v;
        return 0;
    }
    words = dict->f8 * 2;
    if (words >= 0) {
        if (words <= table->cap) {
            table->size = words;
        } else {
            List_Resize(table, words, 4);
        }
    }
    table = dict->t;
    int size = table->size;
    int *data = table->data;
    for (int slot = 0; slot < size; slot++) {
        data[slot] = *(int *)DAT_004c2158;
    }
    dict->f12 = 0;
    for (i = 0; i < count; i += 2, entry += 2) {
        if (entry[0] != 0) {
            ((VT_2eeae0 *)dict)->vIns(entry[0], entry[1]);
        }
    }
    *result = g_resultSuccess.v;
    return 0;
}

void FUN_002eed00(A_2eed00 *arg0, V88 *arg1) {
    L_2eed00 *l;
    int i;
    int n;
    V88 *o;
    int r;

    arg0->f24 = arg1;
    if (arg1 != 0) {
        l = ((L_2eed00 *)FUN_002fc250());
        n = l->count;
        for (i = 0; i < n; i++) {
            o = l->items[i];
            r = o->vX();
            if (r == arg1->vX()) {
                arg0->f28 = i;
                return;
            }
        }
    }
}

