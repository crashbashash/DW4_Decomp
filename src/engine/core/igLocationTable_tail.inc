void FUN_002eb0a0(int a0, int a1)
{
    *(int *)((char *)a0 + 12) = a1;
}

void FUN_002eb0b0(igLocationTableView *arg0) {
    igTDataList<unsigned int> *temp_a0;
    int temp_a1;
    temp_a1 = arg0->_capacity * 5;
    temp_a0 = arg0->_locations;
    if (temp_a1 >= temp_a0->_count) {
        List_Reserve((igDataList *)temp_a0, temp_a1, 4);
    }
    arg0->vfunc_32(arg0->_hashCapacity);
    FUN_0030cf20(arg0->_symbolNames, arg0->_capacity * 4);
    FUN_0030cf30(arg0->_symbolNames, arg0->_capacity);
    FUN_0030cf40((void *)arg0->_symbolNames);
    FUN_0030cf20(arg0->_sourceFileNames, 0x1000);
    FUN_0030cf30(arg0->_sourceFileNames, 0x100);
    FUN_0030cf40((void *)arg0->_sourceFileNames);
}

void FUN_002eb150(igLocationTableView *table) {
    igTDataList<unsigned int> *locations;
    igTDataList<int> *hashIndex;
    locations = table->_locations;
    if (0 <= locations->_capacity) {
        locations->_count = 0;
    } else {
        List_Resize(locations, 0, 4);
    }
    locations = table->_locations;
    if (!(0 < locations->_count)) {
        List_Reserve((igDataList *)locations, 0, 4);
    }
    if (table->_hashIndex != 0) {
        hashIndex = table->_hashIndex;
        if (0 <= hashIndex->_capacity) {
            hashIndex->_count = 0;
        } else {
            List_Resize(hashIndex, 0, 4);
        }
        hashIndex = table->_hashIndex;
        if (!(0 < hashIndex->_count)) {
            List_Reserve((igDataList *)hashIndex, 0, 4);
        }
    }
    FUN_0030cfa0((igStringTableView *)table->_symbolNames);
    FUN_0030cfa0((igStringTableView *)table->_sourceFileNames);
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
  *arg0 = g_resultSuccess.v;
}

void Gap__Core__igLocationTable__vfunc_25(int *arg0, igLocationTableView *arg1, int arg2, int *arg3, char *arg4, int arg5, int *arg6, char *arg7, int arg8, int *arg9) {
    int rc;
    igTDataList<unsigned int> *t;
    LocationRecord *e;
    int r;
    rc = g_resultFailure.v;
    if (arg2 >= 0) {
        t = arg1->_locations;
        if (arg2 * 5 < t->_count) {
            e = (LocationRecord *)((char *)t->_data + arg2 * 0x14);
            *arg3 = e->address;
            if (arg4 != 0) {
                if ((r = ((int)FUN_0030d1d0((int *)arg1->_symbolNames, e->name))) != 0) {
                    strncpy(arg4, r, arg5);
                } else {
                    *arg4 = 0;
                }
            }
            *arg6 = e->offset;
            if (arg7 != 0) {
                if ((r = ((int)FUN_0030d1d0((int *)arg1->_sourceFileNames, e->file))) != 0) {
                    strncpy(arg7, r, arg8);
                } else {
                    *arg7 = 0;
                }
            }
            *arg9 = e->line;
            rc = g_resultSuccess.v;
        }
    }
    *arg0 = rc;
}

int Gap__Core__igLocationTable__vfunc_26(igLocationTableView *o, int key) {
int i = o->vfunc_30(key);
igTDataList<int> *l = o->_hashIndex;
int e;
int n = l->_count;
int j = 0;
int r = -1;
for (;;) { e = l->_data[i]; if (e == -1) { return r; } { int kk = ((LocationRecord *)o->_locations->_data)[e].address; if (kk == key) { r = e; break; } } i++; if (i >= n) i = 0; j++; if (!(j < n)) break; } return r;}

void Gap__Core__igLocationTable__vfunc_27(int *arg0, igLocationTableView *arg1, int arg2, char *arg3, int arg4, int *arg5, char *arg6, int arg7, int *arg_sp0) {
    int h; 
    int n; 
    int i; 
    int res; 
    int *idx;
    igTDataList<int> *d;
    LocationRecord *e;
    char *s;
    char *s2;

    h = arg1->vfunc_30(arg2);
    d = arg1->_hashIndex;
    res = g_resultFailure.v;
    n = d->_count;
    idx = d->_data;
    i = 0;
    do {
        if (idx[h] == -1) {
            *arg0 = res;
            return;
        }
        e = &((LocationRecord *)arg1->_locations->_data)[idx[h]];
        if (e->address == arg2) {
            if (arg3 != 0) {
                if ((s = FUN_0030d1d0((int *)arg1->_symbolNames, e->name)) != 0) {
                    strncpy(arg3, s, arg4);
                } else {
                    *arg3 = 0;
                }
            }
            *arg5 = e->offset;
            if (arg6 != 0) {
                if ((s2 = FUN_0030d1d0((int *)arg1->_sourceFileNames, e->file)) != 0) {
                    strncpy(arg6, s2, arg7);
                } else {
                    *arg6 = 0;
                }
            }
            *arg_sp0 = e->line;
            res = g_resultSuccess.v;
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

void Gap__Core__igLocationTable__vfunc_28(igLocationTableView *o, int a1, char *a2, int a3, char *a4, int a5) {
    switch (o->vfunc_26(a1)) { case -1: o->vfunc_29(a1,a2,a3,a4,a5); break; default: break; }
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

int Gap__Core__igLocationTable__vfunc_31(igLocationTableView *self, int address, int index) {
    int probes = 0;
    int size = self->_hashIndex->_count;
    int limit = size / 2;
    int i;
    igTDataList<int> *t;
    int *data;
    if (size != 0) {
        i = self->vfunc_30(address);
        t = self->_hashIndex;
        data = t->_data;
        do {
            if (data[i] == -1) {
                int n = t->_count;
                if (n != 0 && i >= 0 && n > i) { ((int *)((igIntList *)t)->_data)[i] = index; }
                goto done;
            }
            i++;
            if (i >= size) { i = 0; }
            probes++;
        } while (probes < limit);
        self->vfunc_32(size * 2);
        return 0;
    }
done:
    return 1;
}

void Gap__Core__igLocationTable__vfunc_32(igLocationTableView *arg0, int arg1) {
    igTDataList<int> *l; int n; int *a; int i; LocationRecord *s1; LocationRecord *s0; LocationRecord *s3;
    FUN_002eb0a0((int)arg0, arg1);
    l = arg0->_hashIndex;
    if (!(arg1 < l->_count)) List_Reserve((igDataList *)l, arg1, 4);
    l = arg0->_hashIndex;
    if (arg1 >= 0) {
        if (!(arg1 > l->_capacity)) { l->_count = arg1; } else { List_Resize((void *)l, arg1, 4); }
    }
    l = arg0->_hashIndex;
    n = l->_count;
    a = l->_data;
    for (i = 0; i < n; i++) {
        a[i] = DAT_004c2148;
    }
    igTDataList<unsigned int> *e = arg0->_locations;
    s1 = (LocationRecord *)e->_data;
    s0 = s1;
    s3 = s1 + e->_count / 5;
    while (s0 < s3) {
        if (arg0->vfunc_31(s0->address, s0 - s1) == 0) break;
        s0++;
    }
}

