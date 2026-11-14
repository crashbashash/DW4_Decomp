void FUN_0030cf20(int a0, int a1)
{
    *(int *)((char *)a0 + 8) = a1;
}

void FUN_0030cf30(int a0, int a1)
{
    *(int *)((char *)a0 + 12) = a1;
}

void FUN_0030cf40(void *arg0) {
    int temp_a1;
    void *temp_a0;

    temp_a1 = *(int *)((char *)(arg0) + 8);
    temp_a0 = (void *)(*(int *)((char *)(arg0) + 16));
    if (temp_a1 >= *(int *)((char *)(temp_a0) + 8)) {
        List_Reserve((igDataList *)temp_a0, temp_a1, 1);
    }
    ((igStringTableView *)(((char *)(arg0) + 0)))->setHashing((int)(*(int *)((char *)(arg0) + 12)));
}

void FUN_0030cfa0(struct ClearOwner *arg0) {
    struct ClearList *temp_a0;
    struct ClearList *temp_a0_2;
    struct ClearList *temp_a0_3;
    struct ClearList *temp_a0_4;
    temp_a0 = arg0->a;
    if (!(0 > temp_a0->cap)) {
        temp_a0->n = 0;
    } else {
        List_Resize(temp_a0, 0, 1);
    }
    temp_a0_2 = arg0->a;
    if (!(0 < temp_a0_2->n)) {
        List_Reserve((igDataList *)temp_a0_2, 0, 1);
    }
    temp_a0_3 = arg0->b;
    if (temp_a0_3 != 0) {
        if (!(0 > temp_a0_3->cap)) {
            temp_a0_3->n = 0;
        } else {
            List_Resize(temp_a0_3, 0, 4);
        }
        temp_a0_4 = arg0->b;
        if (!(0 < temp_a0_4->n)) {
            List_Reserve((igDataList *)temp_a0_4, 0, 4);
        }
    }
}

void FUN_0030d050(int arg0) {
    int sp1C;

    FUN_0030d0d0(&sp1C, (void *)arg0, 0);
}

int FUN_0030d080(CountOwner *arg0) {
    CountList *b;
    char *p;
    int n;
    int count;
    int i;

    b = arg0->b;
    p = b->data;
    n = b->cnt;
    count = 0;
    if (p == 0) {
        return 0;
    }
    for (i = 0; i < n; i++) {
        if (*p == 0) {
            count++;
        }
        p++;
    }
    return count;
}

void FUN_0030d0d0(int *arg0, void *arg1, int arg2) {
    int i;
    int hits;
    char *data;
    TruncateList *l;
    int n;
    l = ((TruncateOwner *)arg1)->l;
    data = l->data;
    n = l->count;
    hits = 0;
    if (arg2 == 0) {
        l->SetCount(0);
        ((igStringTableView *)arg1)->setHashing(((TruncateOwner *)arg1)->f12);
        *arg0 = g_resultSuccess.v;
    } else {
        for (i = 0; i < n; i++) {
            if (*data == 0) {
                hits++;
                if (hits == arg2) {
                    l->SetCount(i + 1);
                    *arg0 = g_resultSuccess.v;
                    return;
                }
            }
        }
        *arg0 = g_resultFailure.v;
    }
}

char *FUN_0030d1d0(int *arg0, int arg1) {
    int *t;
    char *p;
    char *r;
    if (arg1 < 0 || arg1 >= (t = (int *)arg0[4])[2] || (p = (char *)t[4]) == 0) {
        r = 0;
    } else {
        r = p + arg1;
        if (arg1 > 0 && r[-1] != 0) r = 0;
    }
    return r;
}

int FUN_0030d230(igStringTableView *self, char *s) {
    int length;
    int offset;
    length = strlen(s) + 1;
    self->strings->reserveFor(length + (offset = self->strings->count));
    List_AppendBytes((igDataList *)self->strings, length, (int)s, 1);
    if (self->hashTable != 0 && self->hashTable->count != 0) {
        self->insert(self->strings->data + offset, offset);
    }
    return offset;
}

int FUN_0030d300(int arg0, int arg1) {
    int r = FUN_0030d350((igStringTableView *)arg0, arg1);
    if (r != -1) return r;
    return FUN_0030d230((igStringTableView *)arg0, (char *)arg1);
}

int FUN_0030d350(igStringTableView *arg0, unsigned int arg1) {
    igIntListView *t;
    int idx;
    int off;
    int n;
    int cnt;
    char *s;
    char *end;

    t = arg0->hashTable;
    if (t != 0 && t->count != 0) {
        idx = arg0->hash((char *)arg1);
        cnt = 0;
        n = arg0->hashTable->count;
        for (;;) {
            off = arg0->hashTable->data[idx];
            if (off == -1) {
                return -1;
            }
            if (strcmp(arg0->strings->data + off, arg1) == 0) {
                return off;
            }
            idx += 1;
            if (idx >= n) {
                idx = 0;
            }
            cnt += 1;
            if (cnt >= n) {
                return -1;
            }
        }
    }
    s = arg0->strings->data;
    end = s + arg0->strings->count;
    while (s < end) {
        if (strcmp(arg1, s) == 0) {
            return s - arg0->strings->data;
        }
        s += strlen(s) + 1;
    }
    return -1;
}

int FUN_0030d4a0(struct NextOwner *o, int i) {
    struct NextIn *s = o->in;
    char *p = s->buf + i;
    int n = s->len;
    if (p == 0 || i < 0) return -1;
    while (i < n) {
        char c = *p;
        i++;
        if (c == 0) {
            if (i >= n) goto bad;
            return i;
        }
        p++;
    }
bad:
    return -1;
}

unsigned int Gap__Core__igStringTable__vfunc_23(igStringTableView *self, char *s) {
    unsigned int h = 0; unsigned int n;
    if (self->hashTable != 0) { n = self->hashTable->count; } else { n = 0; }
    if (s != 0 && n != 0) {
        while (*s != 0) { h ^= (h << 5) + (h >> 2) + (char)*s; s++; }
        h = h % n;
    } else { h = 0; }
    return h;
}

static inline void setAt_30cf20(ProbeList *l, int i, int v) { if (l->count != 0 && i >= 0 && i < l->count) { ((ProbeList *)l)->data[i] = v; } }

int Gap__Core__igStringTable__vfunc_24(ProbeTable *self, int key, int value) {
    int probes = 0;
    int size = self->hash->count;
    int half = size / 2;
    int idx;
    ProbeList *l;

    if (size != 0) {
        idx = self->vHash(key);
        l = self->hash;
        do {
            if (l->data[idx] == -1) {
                setAt_30cf20(l, idx, value);
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

void Gap__Core__igStringTable__vfunc_25(igStringTableView *arg0, int arg1) {
    igIntListView *old;
    igIntListView *l;
    int alloc;
    int n;
    int *data;
    int i;
    char *base;
    char *end;
    char *p;
    FUN_0030cf30((int)arg0, arg1);
    if (arg1 != 0) {
        if (arg0->hashTable == 0) {
            alloc = ((int)igObject_GetAllocator((int)arg0));
            old = arg0->hashTable;
            if (old != 0) {
                --old->references;
                if (((unsigned long long)(long long)old->references & 0x7fffffULL) == 0) {
                    igObject_Destroy(old);
                }
            }
            arg0->hashTable = (igIntListView *)FUN_002ca8b0(alloc);
        }
        l = arg0->hashTable;
        if (arg1 >= 0) {
            if (arg1 <= l->capacity) {
                l->count = arg1;
            } else {
                List_Resize(l, arg1, 4);
            }
        }
        l = arg0->hashTable;
        if (arg1 >= l->count) {
            List_Reserve((igDataList *)l, arg1, 4);
        }
        l = arg0->hashTable;
        n = l->count;
        data = l->data;
        i = 0;
        while (i < n) {
            data[i] = DAT_004c22f8[0];
            i++;
        }
        base = arg0->strings->data;
        p = base;
        end = base + arg0->strings->count;
        while (p < end) {
            if (arg0->insert(p, p - base) == 0) {
                return;
            }
            p += strlen(p) + 1;
        }
    } else {
        old = arg0->hashTable;
        if (old != 0) {
            if (old != 0) {
                --old->references;
                if (((unsigned long long)(long long)old->references & 0x7fffffULL) == 0) {
                    igObject_Destroy(old);
                }
            }
            arg0->hashTable = 0;
        }
    }
}

