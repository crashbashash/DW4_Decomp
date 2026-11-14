/* Accessor: number of entry slots allocated (`_capacity`, +8). */

int igMemoryDictionary_GetCapacity(igMemoryDictionary *self) {
    return self->_capacity;
}

/* Setter for the dictionary capacity (`_capacity`, +8). */

void igMemoryDictionary_SetCapacity(igMemoryDictionary *self, int capacity) {
    self->_capacity = capacity;
}

void igMemoryDictionary_InitEntries(igMemoryDictionaryView *self) {
    int a;
    int b;
    igTDataList<MemoryDictionaryEntry> *l;

    a = self->_capacity * 2;
    l = self->_memoryEntries;
    if (a >= l->_count) {
        List_Reserve((igDataList *)l, a, 4);
    }
    b = self->_capacity * 2;
    l = self->_memoryEntries;
    if (b >= 0) {
        if (b <= l->_capacity) {
            l->_count = b;
        } else {
            List_Resize(l, b, 4);
        }
    }
    self->vfunc_27();
}

void igMemoryDictionary_Clear(igMemoryDictionaryView *self) {
    igTDataList<MemoryDictionaryEntry> *entries;
    igTDataList<MemoryDictionaryEntry> *entries2;

    entries = self->_memoryEntries;
    if (0 <= entries->_capacity) {
        entries->_count = 0;
    } else {
        List_Resize(entries, 0, 4);
    }
    entries2 = self->_memoryEntries;
    if (!(0 < entries2->_count)) {
        List_Reserve((igDataList *)entries2, 0, 4);
    }
    self->_count = 0;
    self->_cachedIndex = 0;
}

/* Predicate: true once the dictionary has storage allocated, i.e. its `_capacity` (+8) is non-
 * zero. */

int igMemoryDictionary_IsEnabled(igMemoryDictionary *self) {
    return self->_capacity != 0;
}

void igMemoryDictionary_ResetEntries(igMemoryDictionaryView *self) {
    igTDataList<MemoryDictionaryEntry> *t; int half; int j; MemoryDictionaryEntry *pp; int n; int i;
    t = self->_memoryEntries;
    half = *(int *)&t->_count / 2;
    pp = t->_data;
    n = t->_count;
    for (i = 0; i < n; i++) {
        ((int *)pp)[i] = DAT_004c2150[0];
    }
    self->_count = 0;
    self->_cachedIndex = 0;
    for (j = 0; j < half; j++) {
        pp->value = -1;
        pp++;
    }
}

/* Accessor: number of entries in use (`_count`, +12). */

int igMemoryDictionary_GetCount(igMemoryDictionary *self) {
    return self->_count;
}

void igMemoryDictionary_GetValue(igResult *result, igMemoryDictionaryView *self, int key, int *value) {
    MemoryDictionaryEntry *e;
    int idx;
    int n;
    int i;
    int res;
    igTDataList<MemoryDictionaryEntry> *s;
    e = &self->_memoryEntries->_data[self->_cachedIndex];
    if (e->key == key) {
        *value = e->value;
        result->v = g_resultSuccess.v;
        return;
    }
    idx = self->vfunc_33(key);
    s = self->_memoryEntries;
    n = s->_count / 2;
    res = g_resultFailure.v;
    i = 0;
    e = &s->_data[idx];
    do {
        if (e->key == key) {
            *value = e->value;
            res = g_resultSuccess.v;
            self->_cachedIndex = idx;
            break;
        }
        if (e->value == -1) {
            break;
        }
        idx++;
        if (idx >= n) {
            e = *(MemoryDictionaryEntry **)&s->_data;
            idx = 0;
        } else {
            e++;
        }
        i++;
    } while (i < n);
    result->v = res;
}

igResult igMemoryDictionary_Insert(igMemoryDictionaryView *self, int key, int val) {
    int probes = 0;
    int cap = self->_memoryEntries->_count / 2;
    int half = cap / 2;
    int idx;
    igTDataList<MemoryDictionaryEntry> *s;
    MemoryDictionaryEntry *e;
    if (cap != 0) {
        idx = self->vfunc_33(key);
        s = self->_memoryEntries;
        e = &s->_data[idx];
        do {
            if (e->key == key) {
                e->value = val;
                return igResult(g_resultSuccess.v);
            }
            if (e->key == 0) {
                e->key = key;
                e->value = val;
                self->_count = self->_count + 1;
                if (probes >= half) {
                    return self->vfunc_34(cap * 2);
                }
                return igResult(g_resultSuccess.v);
            }
            idx++;
            if (idx >= cap) {
                e = *(MemoryDictionaryEntry **)&s->_data;
                idx = 0;
            } else {
                e++;
            }
            probes++;
        } while (probes < cap);
    }
    return igResult(g_resultFailure.v);
}

igResult igMemoryDictionary_Remove(igMemoryDictionaryView *self, int key) {
    int i;
    int half;
    int idx;
    MemoryDictionaryEntry *e;
    MemoryDictionaryEntry *next;
    igTDataList<MemoryDictionaryEntry> *t;

    i = 0;
    half = self->_memoryEntries->_count / 2;
    if (half != 0) {
        idx = self->vfunc_33(key);
        t = self->_memoryEntries;
        e = t->_data + idx;
        do {
            idx += 1;
            next = e + 1;
            if (idx >= half) {
                next = *(MemoryDictionaryEntry **)&t->_data;
                idx = 0;
            }
            if (e->key == key) {
                e->key = 0;
                self->_count = self->_count - 1;
                if (next->value == -1) {
                    e->value = -1;
                } else {
                    e->value = -2;
                }
                goto ok;
            }
            if (e->value == -1) {
                return igResult(g_resultFailure.v);
            }
            i += 1;
            e = next;
        } while (i < half);
        return igResult(g_resultFailure.v);
    }
ok:
    return igResult(g_resultSuccess.v);
}

/* Hash-bucket index for `key`: key modulo the table capacity (`_capacity`), or 0 for an empty
 * table. */

unsigned int igMemoryDictionary_HashKey(igMemoryDictionary *self, unsigned int key) {
    unsigned int capacity;

    capacity = self->_capacity;
    if (capacity != 0) {
        return key % capacity;
    }
    return 0U;
}

int igMemoryDictionary_Resize(igResult *result, igMemoryDictionaryView *self, int capacity) {
    igSmartPointer<igIntList> previous((igIntList *)self->_memoryEntries, kRetainReference);
    int count = previous.get()->_count;
    int *entry = (int *)previous.get()->_data;
    int allocator;
    igTDataList<MemoryDictionaryEntry> *table;
    int words;
    int i;
    self->_capacity = capacity;
    self->_cachedIndex = 0;
    allocator = ((int)igObject_GetAllocator((int)self));
    table = self->_memoryEntries;
    if (table != 0) {
        table->_refCount = table->_refCount - 1;
        if ((table->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(table);
        }
    }
    self->_memoryEntries = (igTDataList<MemoryDictionaryEntry> *)igUnsignedIntListNoClean_Create(allocator);
    words = self->_capacity * 2;
    if (words >= self->_memoryEntries->_count) {
        List_Reserve((igDataList *)self->_memoryEntries, words, 4);
    }
    table = self->_memoryEntries;
    if (table->_data == 0) {
        result->v = g_resultFailure.v;
        return 0;
    }
    words = self->_capacity * 2;
    if (words >= 0) {
        if (words <= table->_capacity) {
            table->_count = words;
        } else {
            List_Resize(table, words, 4);
        }
    }
    table = self->_memoryEntries;
    int size = table->_count;
    int *data = (int *)table->_data;
    for (int slot = 0; slot < size; slot++) {
        data[slot] = *(int *)DAT_004c2158;
    }
    self->_count = 0;
    for (i = 0; i < count; i += 2, entry += 2) {
        if (entry[0] != 0) {
            self->vfunc_31(entry[0], entry[1]);
        }
    }
    result->v = g_resultSuccess.v;
    return 0;
}

void igMemoryDirEntry_SetMemType(igMemoryDirEntry *arg0, igObjectDispatchView *arg1) {
    __internalObjectList *l;
    int i;
    int n;
    igObjectDispatchView *o;
    igMetaObject *r;

    arg0->_memType = (int)arg1;
    if (arg1 != 0) {
        l = ((__internalObjectList *)igMetaField_GetMetaFieldList());
        n = l->_count;
        for (i = 0; i < n; i++) {
            o = ((igObjectDispatchView **)l->_data)[i];
            r = o->getMeta();
            if (r == arg1->getMeta()) {
                arg0->_memTypeIndex = i;
                return;
            }
        }
    }
}

