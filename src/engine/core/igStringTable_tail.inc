void igStringTable_SetCapacity(int object, int capacity)
{
    igStringTable *self = (igStringTable *)object;
    self->_capacity = capacity;
}

void igStringTable_SetHashCapacity(int object, int hashCapacity)
{
    igStringTable *self = (igStringTable *)object;
    self->_hashCapacity = hashCapacity;
}

void igStringTable_Reserve(void *object) {
    igStringTable *self = (igStringTable *)object;
    int capacity;
    igDataList *strings;

    capacity = self->_capacity;
    strings = (igDataList *)self->_strings;
    if (capacity >= strings->_count) {
        List_Reserve(strings, capacity, 1);
    }
    ((igStringTableView *)self)->SetHashing(self->_hashCapacity);
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

void igStringTable_RemoveAll(int self) {
    int result;

    igStringTable_Truncate(&result, (igStringTableView *)self, 0);
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
        table->SetHashing(table->_hashCapacity);
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

char *igStringTable_GetString(int *self, int index) {
    int *t;
    char *p;
    char *r;
    if (index < 0 || index >= (t = (int *)self[4])[2] || (p = (char *)t[4]) == 0) {
        r = 0;
    } else {
        r = p + index;
        if (index > 0 && r[-1] != 0) r = 0;
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
        self->Insert(self->_strings->_data + offset, offset);
    }
    return offset;
}

int igStringTable_FindOrAddString(int self, int string) {
    int r = igStringTable_Find((igStringTableView *)self, string);
    if (r != -1) return r;
    return igStringTable_AppendString((igStringTableView *)self, (char *)string);
}

int igStringTable_Find(igStringTableView *self, unsigned int string) {
    igTDataList<int> *t;
    int idx;
    int off;
    int n;
    int cnt;
    char *s;
    char *end;

    t = self->_hashIndex;
    if (t != 0 && t->_count != 0) {
        idx = self->Hash((char *)string);
        cnt = 0;
        n = self->_hashIndex->_count;
        for (;;) {
            off = self->_hashIndex->_data[idx];
            if (off == -1) {
                return -1;
            }
            if (strcmp(self->_strings->_data + off, (const char *)string) == 0) {
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
    s = self->_strings->_data;
    end = s + self->_strings->_count;
    while (s < end) {
        if (strcmp((const char *)string, s) == 0) {
            return s - self->_strings->_data;
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
        idx = self->Hash(s);
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
        self->SetHashing(size * 2);
        return 0;
    }
done:
    return 1;
}

int g_igStringTable_emptyHashSlot = -1;

void igStringTable_SetHashing(igStringTableView *self, int enable) {
    igTDataList<int> *old;
    igTDataList<int> *l;
    int alloc;
    int n;
    int *data;
    int i;
    char *base;
    char *end;
    char *p;
    igStringTable_SetHashCapacity((int)self, enable);
    if (enable != 0) {
        if (self->_hashIndex == 0) {
            alloc = ((int)igObject_GetAllocator((igObject *)self));
            old = self->_hashIndex;
            if (old != 0) {
                --old->_refCount;
                if (((unsigned long long)(long long)(int)old->_refCount & 0x7fffffULL) == 0) {
                    igObject_Destroy(old);
                }
            }
            self->_hashIndex = (igTDataList<int> *)igIntListNoClean_Create(alloc);
        }
        l = self->_hashIndex;
        if (enable >= 0) {
            if (enable <= l->_capacity) {
                l->_count = enable;
            } else {
                List_Resize(l, enable, 4);
            }
        }
        l = self->_hashIndex;
        if (enable >= l->_count) {
            List_Reserve((igDataList *)l, enable, 4);
        }
        l = self->_hashIndex;
        n = l->_count;
        data = l->_data;
        i = 0;
        while (i < n) {
            data[i] = g_igStringTable_emptyHashSlot;
            i++;
        }
        base = self->_strings->_data;
        p = base;
        end = base + self->_strings->_count;
        while (p < end) {
            if (self->Insert(p, p - base) == 0) {
                return;
            }
            p += strlen(p) + 1;
        }
    } else {
        old = self->_hashIndex;
        if (old != 0) {
            if (old != 0) {
                --old->_refCount;
                if (((unsigned long long)(long long)(int)old->_refCount & 0x7fffffULL) == 0) {
                    igObject_Destroy(old);
                }
            }
            self->_hashIndex = 0;
        }
    }
}

