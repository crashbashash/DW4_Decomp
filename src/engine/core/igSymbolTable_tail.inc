void igSymbolTable_SetHashCapacity(int table, int capacity)
{
    ((igSymbolTable *)table)->_hashCapacity = capacity;
}

void igSymbolTable_SetAddressRange(igSymbolTableView *self, unsigned low, unsigned high) {
    unsigned hashCapacity;

    self->_lowAddress = low;
    self->_highAddress = high;
    hashCapacity = self->_hashCapacity;
    if (hashCapacity != 0) {
        self->_hashIncrement = (self->_highAddress - self->_lowAddress) / hashCapacity;
        if (((self->_highAddress - self->_lowAddress) % self->_hashCapacity) != 0) {
            self->_hashIncrement = self->_hashIncrement + 1;
        }
    } else {
        self->_hashIncrement = 1;
    }
}

void igSymbolTable_ReserveStorage(igSymbolTableView *self) {
    igTDataList<int> *symbols;
    int words;
    words = self->_capacity * 4;
    symbols = self->_symbols;
    if (words >= symbols->_count) {
        List_Reserve((igDataList *)symbols, words, 4);
    }
    self->RebuildHashIndex(self->_hashCapacity);
    igStringTable_SetCapacity(self->_symbolNames, self->_capacity * 4);
    igStringTable_SetHashCapacity(self->_symbolNames, self->_capacity);
    igStringTable_Reserve((void *)self->_symbolNames);
    igStringTable_SetCapacity(self->_sourceFileNames, 0x1000);
    igStringTable_SetHashCapacity(self->_sourceFileNames, 0x100);
    igStringTable_Reserve((void *)self->_sourceFileNames);
}

/* Number of symbols in the table. The symbols list stores four ints per symbol, so the count is
 * the list length divided by four (the resize sibling vfunc_24 sets the length to count << 2). */

int igSymbolTable_GetSymbolCount(igSymbolTable *self) {
    return ((igDataList *)(self->_symbols))->_count / 4;
}

void igSymbolTable_SetSymbolCount(int *result, igSymbolTableView *self, int count) {
    igTDataList<int> *l = self->_symbols;
    int n = count << 2;
    if (n >= 0) {
        if (n <= l->_capacity) {
            l->_count = n;
        } else {
            List_Resize((void *)l, n, 4);
        }
    }
    *result = g_resultSuccess.v;
}

igResult igSymbolTable_GetSymbol(igSymbolTable *self, int idx, char *name, int nameSize, int *a, int *b, char *path, int pathSize) {
    igResult result = g_resultFailure;
    SymbolRecord *e;
    char *s;

    if (idx >= 0 && idx * 4 < ((igTDataList<SymbolRecord> *)self->_symbols)->_count) {
        e = &((igTDataList<SymbolRecord> *)self->_symbols)->_data[idx];
        *a = e->address;
        if (name != 0) {
if ((s = igStringTable_GetString((int *)self->_symbolNames, e->name)) != 0) { strncpy(name, s, nameSize); } else { *name = 0; }
        }
        *b = e->size;
        if (path != 0) {
if ((s = igStringTable_GetString((int *)self->_sourceFileNames, e->path)) != 0) { strncpy(path, s, pathSize); } else { *path = 0; }
        }
        result = g_resultSuccess;
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

int igSymbolTable_FindSymbolIndex(igSymbolTableView *o, unsigned key) {
SymbolRecord *en1; int len2; int i; int i0; int e1; int len1; unsigned st2; int cnt; int e2; unsigned end1; unsigned end2; int k; unsigned st1; int j; SymbolRecord *en2; igTDataList<int> *l;
    i0 = o->HashAddress(key);
    i = i0;
    l = o->_hashIndex;
    cnt = l->_count;
    j = 0;
    for (;;) {
        e1 = l->_data[i];
        if (e1 == -1) break;
        en1 = &((SymbolRecord *)o->_symbols->_data)[e1];
        len1 = en1->size;
        if (len1 != 0) { st1 = en1->address; end1 = st1 + len1; }
        else { st1 = en1->address; end1 = st1 + len1 + 1; }
        if (key >= st1) { if (key <= end1) return e1; }
        i++;
        if (i >= cnt) i = 0;
        j++;
        if (j >= cnt) return -1;
    }
    k = i0 - 1;
    igTDataList<unsigned int> *l2 = (igTDataList<unsigned int> *)l;
    while (k > 0) {
        if (l2->_data[k] != (unsigned)-1) break;
        k--;
    }
    while (k > 0) {
        e2 = l2->_data[k];
        if (e2 == -1) return -1;
        en2 = &((SymbolRecord *)o->_symbols->_data)[e2];
        len2 = en2->size;
        if (len2 != 0) { st2 = en2->address; end2 = st2 + len2; }
        else { st2 = en2->address; end2 = st2 + len2 + 1; }
        if (key >= st2) { if (key <= end2) return e2; }
        k--;
    }
    return -1;
}

void igSymbolTable_GetSymbolAtAddress(int *out, igSymbolTableView *o, int a, int b, int c, int d, int e, int f, int g, int *h) {
    igResult r;
    int i = o->FindSymbolIndex(a);
    r.v = g_resultFailure.v;
    *h = 0;
    if (i != -1) r = o->GetSymbol(i, b, c, d, e, f, g);
    *out = r.v;
}

void igSymbolTable_AddSymbolIfMissing(igSymbolTableView *o, int a, int b, int c, int d) { switch (o->FindSymbolIndex(b)) { case -1: o->AddSymbol((const char *)a, (void *)b, c, d); break; default: break; } }

typedef igSmartPointer<igTDataList<int> > igIntListRef;

/* Appends a symbol record, doubling the record list when it is full, enters it in the hash index and
 * returns its index. The name and the source file go to the two string tables; -1 stands for none. */
extern "C" int igSymbolTable_AddSymbol(igSymbolTableView *self, const char *name, int address, unsigned int size, const char *sourceFile);
int igSymbolTable_AddSymbol(igSymbolTableView *self, const char *name, int address, unsigned int size, const char *sourceFile) {
    int nameIndex;
    int pathIndex;
    int index;
    SymbolRecord record;
    pathIndex = nameIndex = -1;
    index = self->_symbols->_count / 4;
    if (name != 0 && *name != 0) {
        nameIndex = igStringTable_FindOrAddString(self->_symbolNames, (int)name);
    }
    if (sourceFile != 0 && *sourceFile != 0) {
        pathIndex = igStringTable_FindOrAddString(self->_sourceFileNames, (int)sourceFile);
    }
    record.name = nameIndex;
    record.path = pathIndex;
    record.address = address;
    record.size = size;
    if (((igIntListRef &)self->_symbols)->count() + 4 > ((igIntListRef &)self->_symbols)->capacity()) {
        setCapacity(((igIntListRef &)self->_symbols).get(), ((igIntListRef &)self->_symbols)->capacity() * 2);
    }
    List_AppendWords((igDataList *)self->_symbols, 4, (const int *)&record);
    self->InsertHashEntry(address, size, index);
    return index;
}

unsigned int igSymbolTable_HashAddress(igSymbolTable *self, int address) {
    unsigned int hashCapacity;
    unsigned int increment;
    unsigned int slot;

    hashCapacity = self->_hashCapacity;
    slot = 0;
    if (hashCapacity != 0) {
        increment = self->_hashIncrement;
        if (increment != 0) {
            slot = (int)((unsigned int) ((unsigned int) (address - self->_lowAddress) / increment) % hashCapacity);
        }
    }
    return slot;
}

int igSymbolTable_InsertHashEntry(igSymbolTableView *self, int key, int key2, int value) {
    int probes = 0;
    int size = self->_hashIndex->_count;
    int half = size / 2;
    int idx;
    igTDataList<int> *l;

    if (size != 0) {
        idx = self->HashAddress(key);
        l = self->_hashIndex;
        do {
            if (l->_data[idx] == -1) {
                igIntList_SetChecked((igIntList *)l, idx, value);
                goto done;
            }
            idx++;
            if (idx >= size) {
                idx = 0;
            }
            probes++;
        } while (probes < half);
        self->RebuildHashIndex(size * 2);
        return 0;
    }
done:
    return 1;
}

static inline void reserve(igTDataList<int> *l, int n) { if (n >= l->_count) { List_Reserve((igDataList *)l, n, 4); } }

static inline void setListCount(igTDataList<int> *l, int n) { if (n >= 0) { if (n <= l->_capacity) { l->_count = n; } else { List_Resize(l, n, 4); } } }

int g_igSymbolTable_emptyHashSlot = -1;

void igSymbolTable_RebuildHashIndex(igSymbolTableView *self, int n) {
    igTDataList<int> *l;
    int count;
    int *data;
    int i;
    SymbolRecord *begin;
    SymbolRecord *end;
    SymbolRecord *e;

    igSymbolTable_SetHashCapacity((int)self, n);
    reserve(self->_hashIndex, n);
    setListCount(self->_hashIndex, n);
    l = self->_hashIndex;
    count = l->_count;
    data = l->_data;
    for (i = 0; i < count; i++) {
        data[i] = g_igSymbolTable_emptyHashSlot;
    }
    if (self->_hashCapacity != 0) {
        self->_hashIncrement = (self->_highAddress - self->_lowAddress) / self->_hashCapacity;
        if ((self->_highAddress - self->_lowAddress) % self->_hashCapacity != 0) {
            self->_hashIncrement = self->_hashIncrement + 1;
        }
    } else {
        self->_hashIncrement = 1;
    }
    l = self->_symbols;
    begin = (SymbolRecord *)l->_data;
    end = begin + l->_count / 4;
    for (e = begin; e < end; e++) {
        int bb = e->size; if (self->InsertHashEntry(e->address, bb, e - begin) == 0) {
            break;
        }
    }
}

igResult igThread_SetPriority(igPsx2Thread *self, int priority) {
    self->_priority = priority;
    return g_resultSuccess;
}

