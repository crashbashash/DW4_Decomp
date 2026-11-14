void igStringTable_SetCapacity(int a0, int a1)
{
    *(int *)((char *)a0 + 8) = a1;
}

void igStringTable_SetHashCapacity(int a0, int a1)
{
    *(int *)((char *)a0 + 12) = a1;
}

void igStringTable_Reserve(void *arg0) {
    int temp_a1;
    void *temp_a0;

    temp_a1 = *(int *)((char *)(arg0) + 8);
    temp_a0 = (void *)(*(int *)((char *)(arg0) + 16));
    if (temp_a1 >= *(int *)((char *)(temp_a0) + 8)) {
        List_Reserve((igDataList *)temp_a0, temp_a1, 1);
    }
    ((igStringTableView *)(((char *)(arg0) + 0)))->setHashing((int)(*(int *)((char *)(arg0) + 12)));
}

void igStringTable_Clear(igStringTableView *table) {
    igTDataList<char> *strings;
    igTDataList<char> *strings2;
    igTDataList<int> *hashIndex;
    igTDataList<int> *hashIndex2;
    strings = table->_strings;
    if (!(0 > strings->_capacity)) {
        strings->_count = 0;
    } else {
        List_Resize(strings, 0, 1);
    }
    strings2 = table->_strings;
    if (!(0 < strings2->_count)) {
        List_Reserve((igDataList *)strings2, 0, 1);
    }
    hashIndex = table->_hashIndex;
    if (hashIndex != 0) {
        if (!(0 > hashIndex->_capacity)) {
            hashIndex->_count = 0;
        } else {
            List_Resize(hashIndex, 0, 4);
        }
        hashIndex2 = table->_hashIndex;
        if (!(0 < hashIndex2->_count)) {
            List_Reserve((igDataList *)hashIndex2, 0, 4);
        }
    }
}

void igStringTable_RemoveAll(int arg0) {
    int sp1C;

    igStringTable_Truncate(&sp1C, (igStringTableView *)arg0, 0);
}

int igStringTable_GetCount(igStringTableView *table) {
    igTDataList<char> *strings;
    char *p;
    int n;
    int count;
    int i;

    strings = table->_strings;
    p = strings->_data;
    n = strings->_count;
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

/* Sets the byte count of the packed strings, growing their storage when it no longer fits. */
static inline void setStringBytes(igTDataList<char> *strings, int n) {
    if (n >= 0) {
        if (n <= strings->_capacity) {
            strings->_count = n;
        } else {
            List_Resize(strings, n, 1);
        }
    }
}

void igStringTable_Truncate(int *result, igStringTableView *table, int count) {
    int i;
    int hits;
    char *data;
    igTDataList<char> *strings;
    int n;
    strings = table->_strings;
    data = strings->_data;
    n = strings->_count;
    hits = 0;
    if (count == 0) {
        setStringBytes(strings, 0);
        table->setHashing(table->_hashCapacity);
        *result = g_resultSuccess.v;
    } else {
        for (i = 0; i < n; i++) {
            if (*data == 0) {
                hits++;
                if (hits == count) {
                    setStringBytes(strings, i + 1);
                    *result = g_resultSuccess.v;
                    return;
                }
            }
        }
        *result = g_resultFailure.v;
    }
}

char *igStringTable_GetString(int *arg0, int arg1) {
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

/* Grows the packed strings to twice their capacity once n bytes no longer fit. */
static inline void reserveStringBytes(const igTDataList<char> *strings, int n) {
    int grown = strings->_capacity * 2;
    if (strings->_capacity < n) {
        if (!(grown < strings->_count)) {
            List_Reserve((igDataList *)strings, grown, 1);
        }
    }
}

int igStringTable_AppendString(igStringTableView *self, char *s) {
    int length;
    int offset;
    length = strlen(s) + 1;
    reserveStringBytes(self->_strings, length + (offset = self->_strings->_count));
    List_AppendBytes((igDataList *)self->_strings, length, (int)s, 1);
    if (self->_hashIndex != 0 && self->_hashIndex->_count != 0) {
        self->insert(self->_strings->_data + offset, offset);
    }
    return offset;
}

int igStringTable_FindOrAddString(int arg0, int arg1) {
    int r = igStringTable_Find((igStringTableView *)arg0, arg1);
    if (r != -1) return r;
    return igStringTable_AppendString((igStringTableView *)arg0, (char *)arg1);
}

int igStringTable_Find(igStringTableView *arg0, unsigned int arg1) {
    igTDataList<int> *t;
    int idx;
    int off;
    int n;
    int cnt;
    char *s;
    char *end;

    t = arg0->_hashIndex;
    if (t != 0 && t->_count != 0) {
        idx = arg0->hash((char *)arg1);
        cnt = 0;
        n = arg0->_hashIndex->_count;
        for (;;) {
            off = arg0->_hashIndex->_data[idx];
            if (off == -1) {
                return -1;
            }
            if (strcmp(arg0->_strings->_data + off, arg1) == 0) {
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
    s = arg0->_strings->_data;
    end = s + arg0->_strings->_count;
    while (s < end) {
        if (strcmp(arg1, s) == 0) {
            return s - arg0->_strings->_data;
        }
        s += strlen(s) + 1;
    }
    return -1;
}

int igStringTable_GetNextStringIndex(igStringTableView *table, int i) {
    igTDataList<char> *s = table->_strings;
    char *p = s->_data + i;
    int n = s->_count;
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

unsigned int igStringTable_Hash(igStringTableView *self, char *s) {
    unsigned int h = 0; unsigned int n;
    if (self->_hashIndex != 0) { n = self->_hashIndex->_count; } else { n = 0; }
    if (s != 0 && n != 0) {
        while (*s != 0) { h ^= (h << 5) + (h >> 2) + (char)*s; s++; }
        h = h % n;
    } else { h = 0; }
    return h;
}

int igStringTable_InsertHash(igStringTableView *self, char *s, int offset) {
    int probes = 0;
    int size = self->_hashIndex->_count;
    int half = size / 2;
    int idx;
    igTDataList<int> *l;

    if (size != 0) {
        idx = self->hash(s);
        l = self->_hashIndex;
        do {
            if (l->_data[idx] == -1) {
                igIntList_SetChecked((igIntList *)l, idx, offset);
                goto done;
            }
            idx++;
            if (idx >= size) {
                idx = 0;
            }
            probes++;
        } while (probes < half);
        self->setHashing(size * 2);
        return 0;
    }
done:
    return 1;
}

void igStringTable_SetHashing(igStringTableView *arg0, int arg1) {
    igTDataList<int> *old;
    igTDataList<int> *l;
    int alloc;
    int n;
    int *data;
    int i;
    char *base;
    char *end;
    char *p;
    igStringTable_SetHashCapacity((int)arg0, arg1);
    if (arg1 != 0) {
        if (arg0->_hashIndex == 0) {
            alloc = ((int)igObject_GetAllocator((int)arg0));
            old = arg0->_hashIndex;
            if (old != 0) {
                --old->_refCount;
                if (((unsigned long long)(long long)(int)old->_refCount & 0x7fffffULL) == 0) {
                    igObject_Destroy(old);
                }
            }
            arg0->_hashIndex = (igTDataList<int> *)igIntListNoClean_Create(alloc);
        }
        l = arg0->_hashIndex;
        if (arg1 >= 0) {
            if (arg1 <= l->_capacity) {
                l->_count = arg1;
            } else {
                List_Resize(l, arg1, 4);
            }
        }
        l = arg0->_hashIndex;
        if (arg1 >= l->_count) {
            List_Reserve((igDataList *)l, arg1, 4);
        }
        l = arg0->_hashIndex;
        n = l->_count;
        data = l->_data;
        i = 0;
        while (i < n) {
            data[i] = DAT_004c22f8[0];
            i++;
        }
        base = arg0->_strings->_data;
        p = base;
        end = base + arg0->_strings->_count;
        while (p < end) {
            if (arg0->insert(p, p - base) == 0) {
                return;
            }
            p += strlen(p) + 1;
        }
    } else {
        old = arg0->_hashIndex;
        if (old != 0) {
            if (old != 0) {
                --old->_refCount;
                if (((unsigned long long)(long long)(int)old->_refCount & 0x7fffffULL) == 0) {
                    igObject_Destroy(old);
                }
            }
            arg0->_hashIndex = 0;
        }
    }
}

