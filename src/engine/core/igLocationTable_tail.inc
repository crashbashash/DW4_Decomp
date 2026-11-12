void FUN_002eb0a0(int a0, int a1)
{
    *(int *)((char *)a0 + 12) = a1;
}

void FUN_002eb0b0(int *arg0) {
    int *temp_a0;
    int temp_a1;
    temp_a1 = arg0[2] * 5;
    temp_a0 = (int *)arg0[4];
    if (temp_a1 >= temp_a0[2]) {
        List_Reserve((L_2d6680 *)temp_a0, temp_a1, 4);
    }
    ((A_2eb0b0 *)arg0)->vX(arg0[3]);
    FUN_0030cf20(arg0[6], arg0[2] * 4);
    FUN_0030cf30(arg0[6], arg0[2]);
    FUN_0030cf40((void *)arg0[6]);
    FUN_0030cf20(arg0[7], 0x1000);
    FUN_0030cf30(arg0[7], 0x100);
    FUN_0030cf40((void *)arg0[7]);
}

void FUN_002eb150(struct O_2eb150 *arg0) {
    struct L_2eb150 *a;
    a = arg0->f16;
    if (0 <= a->f12) {
        a->f8 = 0;
    } else {
        List_Resize(a, 0, 4);
    }
    a = arg0->f16;
    if (!(0 < a->f8)) {
        List_Reserve((L_2d6680 *)a, 0, 4);
    }
    if (arg0->f20 != 0) {
        a = arg0->f20;
        if (0 <= a->f12) {
            a->f8 = 0;
        } else {
            List_Resize(a, 0, 4);
        }
        a = arg0->f20;
        if (!(0 < a->f8)) {
            List_Reserve((L_2d6680 *)a, 0, 4);
        }
    }
    FUN_0030cfa0((ClearOwner *)arg0->f24);
    FUN_0030cfa0((ClearOwner *)arg0->f28);
}

int FUN_002eb210(void *arg0) {
    return *(int *)((char *)arg0 + 8) != 0;
}

/* Number of locations in the table. The locations list stores five ints per location, so the count
 * is the list length divided by five (the resize sibling vfunc_24 sets the length to count * 5). */

int Gap__Core__igLocationTable__vfunc_23(igLocationTable *self) {
    return ((igDataList *)(self->_locations))->_count / 5;
}

void Gap__Core__igLocationTable__vfunc_24(int *arg0, void *arg1, int arg2)
{
  int temp_a1;
  void *temp_a0;
  temp_a0 = (void *) (*((int *) (((char *) arg1) + 16)));
  temp_a1 = arg2 * 5;
  if (temp_a1 >= 0)
  {
    if (temp_a1 <= (*((int *) (((char *) temp_a0) + 12))))
    {
      *((int *) (((char *) temp_a0) + 8)) = temp_a1;
    }
    else
    {
      List_Resize(temp_a0, temp_a1, 4);
    }
  }
  *arg0 = g_statusSucceeded.v;
}

void Gap__Core__igLocationTable__vfunc_25(int *arg0, S_2eb2b0 *arg1, int arg2, int *arg3, char *arg4, int arg5, int *arg6, char *arg7, int arg8, int *arg9) {
    int rc;
    Tb *t;
    E_2eb2b0 *e;
    int r;
    rc = g_allocatorFailureStatus.v;
    if (arg2 >= 0) {
        t = arg1->f16;
        if (arg2 * 5 < t->n) {
            e = (E_2eb2b0 *)(t->v + arg2 * 0x14);
            *arg3 = e->f0;
            if (arg4 != 0) {
                if ((r = ((int)FUN_0030d1d0((int *)arg1->f24, e->f4))) != 0) {
                    strncpy(arg4, r, arg5);
                } else {
                    *arg4 = 0;
                }
            }
            *arg6 = e->f8;
            if (arg7 != 0) {
                if ((r = ((int)FUN_0030d1d0((int *)arg1->f28, e->f12))) != 0) {
                    strncpy(arg7, r, arg8);
                } else {
                    *arg7 = 0;
                }
            }
            *arg9 = e->f16;
            rc = g_statusSucceeded.v;
        }
    }
    *arg0 = rc;
}

int Gap__Core__igLocationTable__vfunc_26(O_2eb3d0 *o, int key) {
int i = o->v28();
L_2eb3d0 *l = o->idx;
int e;
int n = l->cnt;
int j = 0;
int r = -1;
for (;;) { e = l->arr[i]; if (e == -1) { return r; } { int kk = o->ents->arr[e].key; if (kk == key) { r = e; break; } } i++; if (i >= n) i = 0; j++; if (!(j < n)) break; } return r;}

void Gap__Core__igLocationTable__vfunc_27(int *arg0, LT *arg1, int arg2, char *arg3, int arg4, int *arg5, char *arg6, int arg7, int *arg_sp0) {
    int h; 
    int n; 
    int i; 
    int res; 
    int *idx;
    Dat *d;
    Entry *e;
    char *s;
    char *s2;

    h = arg1->v120(arg2);
    d = arg1->f20;
    res = g_allocatorFailureStatus.v;
    n = d->count;
    idx = d->data;
    i = 0;
    do {
        if (idx[h] == -1) {
            *arg0 = res;
            return;
        }
        e = &arg1->f16->data[idx[h]];
        if (e->key == arg2) {
            if (arg3 != 0) {
                if ((s = FUN_0030d1d0((int *)arg1->f24, e->f4)) != 0) {
                    strncpy(arg3, s, arg4);
                } else {
                    *arg3 = 0;
                }
            }
            *arg5 = e->f8;
            if (arg6 != 0) {
                if ((s2 = FUN_0030d1d0((int *)arg1->f28, e->f12)) != 0) {
                    strncpy(arg6, s2, arg7);
                } else {
                    *arg6 = 0;
                }
            }
            *arg_sp0 = e->f16;
            res = g_statusSucceeded.v;
            break;
        }
        h++;
        if (h >= n) {
            h = 0;
        }
        i++;
    } while (i < n);
    *arg0 = res;
}

void Gap__Core__igLocationTable__vfunc_28(C_2eb630 *o, int a1, int a2, int a3, int a4, int a5) {
    switch (o->v24()) { case -1: o->v27(a1,a2,a3,a4,a5); break; default: break; }
}

/* Hash-bucket index for `key`: key modulo the hash-table size (`_hashCapacity`), or 0 when there
 * is none. */

unsigned int Gap__Core__igLocationTable__vfunc_30(igLocationTable *self, unsigned int key) {
    unsigned int hash_capacity;

    hash_capacity = self->_hashCapacity;
    if (hash_capacity != 0) {
        return key % hash_capacity;
    }
    return 0U;
}

int Gap__Core__igLocationTable__vfunc_31(LocationHashTable *self, int key, int value) {
    int probes = 0;
    int size = self->table->count;
    int limit = size / 2;
    int i;
    LocationHashWords *t;
    int *data;
    if (size != 0) {
        i = self->slot(key);
        t = self->table;
        data = t->data;
        do {
            if (data[i] == -1) {
                int n = t->count;
                if (n != 0 && i >= 0 && n > i) { ((LocationHashWords *)t)->data[i] = value; }
                goto done;
            }
            i++;
            if (i >= size) { i = 0; }
            probes++;
        } while (probes < limit);
        self->rehash(size * 2);
        return 0;
    }
done:
    return 1;
}

void Gap__Core__igLocationTable__vfunc_32(Tab_2eb980 *arg0, int arg1) {
    IL *l; int n; W_2eb980 *a; int i; E_2eb980 *s1; E_2eb980 *s0; E_2eb980 *s3;
    FUN_002eb0a0((int)arg0, arg1);
    l = arg0->idx;
    if (!(arg1 < l->cnt)) List_Reserve((L_2d6680 *)l, arg1, 4);
    l = arg0->idx;
    if (arg1 >= 0) {
        if (!(arg1 > l->cap)) { l->cnt = arg1; } else { List_Resize((void *)l, arg1, 4); }
    }
    l = arg0->idx;
    n = l->cnt;
    a = l->arr;
    for (i = 0; i < n; i++) {
        a[i] = DAT_004c2148;
    }
    EL_2eb980 *e = arg0->ents;
    s1 = e->arr;
    s0 = s1;
    s3 = s1 + e->cnt / 5;
    while (s0 < s3) {
        if (arg0->v124(s0->w[0], s0 - s1) == 0) break;
        s0++;
    }
}

