void igLocationTable_SetHashCapacity(int table, int capacity)
{
    ((igLocationTable *)table)->_hashCapacity = capacity;
}

void igLocationTable_Allocate(igLocationTableView *self) {
    igTDataList<unsigned int> *locations;
    int size;
    size = self->_capacity * 5;
    locations = self->_locations;
    if (size >= locations->_count) {
        List_Reserve((igDataList *)locations, size, 4);
    }
    self->Rehash(self->_hashCapacity);
    igStringTable_SetCapacity(self->_symbolNames, self->_capacity * 4);
    igStringTable_SetHashCapacity(self->_symbolNames, self->_capacity);
    igStringTable_Reserve((void *)self->_symbolNames);
    igStringTable_SetCapacity(self->_sourceFileNames, 0x1000);
    igStringTable_SetHashCapacity(self->_sourceFileNames, 0x100);
    igStringTable_Reserve((void *)self->_sourceFileNames);
}

void igLocationTable_Clear(igLocationTableView *table) {
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
    igStringTable_Clear((igStringTableView *)table->_symbolNames);
    igStringTable_Clear((igStringTableView *)table->_sourceFileNames);
}

int igLocationTable_IsInitialized(void *table) {
    return ((igLocationTable *)table)->_capacity != 0;
}

/* Number of locations in the table. The locations list stores five ints per location, so the count
 * is the list length divided by five (the resize sibling vfunc_24 sets the length to count * 5). */

int igLocationTable_GetCount(igLocationTable *self) {
    return ((igDataList *)(self->_locations))->_count / 5;
}

void igLocationTable_Resize(int *result, igLocationTable *self, int count)
{
  int size;
  igTDataList<unsigned int> *locations;
  locations = (igTDataList<unsigned int> *)self->_locations;
  size = count * 5;
  if (size >= 0)
  {
    if (size <= locations->_capacity)
    {
      locations->_count = size;
    }
    else
    {
      List_Resize(locations, size, 4);
    }
  }
  *result = g_resultSuccess.v;
}

void igLocationTable_GetLocationByIndex(int *result, igLocationTableView *self, int index, int *address, char *name, int nameSize, int *offset, char *file, int fileSize, int *line) {
    int status;
    igTDataList<unsigned int> *locations;
    LocationRecord *record;
    int text;
    status = g_resultFailure.v;
    if (index >= 0) {
        locations = self->_locations;
        if (index * 5 < locations->_count) {
            record = (LocationRecord *)((char *)locations->_data + index * 0x14);
            *address = record->address;
            if (name != 0) {
                if ((text = ((int)igStringTable_GetString((int *)self->_symbolNames, record->name))) != 0) {
                    strncpy(name, text, nameSize);
                } else {
                    *name = 0;
                }
            }
            *offset = record->offset;
            if (file != 0) {
                if ((text = ((int)igStringTable_GetString((int *)self->_sourceFileNames, record->file))) != 0) {
                    strncpy(file, text, fileSize);
                } else {
                    *file = 0;
                }
            }
            *line = record->line;
            status = g_resultSuccess.v;
        }
    }
    *result = status;
}

int igLocationTable_FindLocationIndex(igLocationTableView *o, int key) {
int i = o->Hash(key);
igTDataList<int> *l = o->_hashIndex;
int e;
int n = l->_count;
int j = 0;
int r = -1;
for (;;) { e = l->_data[i]; if (e == -1) { return r; } { int kk = ((LocationRecord *)o->_locations->_data)[e].address; if (kk == key) { r = e; break; } } i++; if (i >= n) i = 0; j++; if (!(j < n)) break; } return r;}

void igLocationTable_GetLocation(int *result, igLocationTableView *self, int address, char *name, int nameSize, int *offset, char *file, int fileSize, int *line) {
    int h; 
    int n; 
    int i; 
    int res; 
    int *idx;
    igTDataList<int> *d;
    LocationRecord *e;
    char *s;
    char *s2;

    h = self->Hash(address);
    d = self->_hashIndex;
    res = g_resultFailure.v;
    n = d->_count;
    idx = d->_data;
    i = 0;
    do {
        if (idx[h] == -1) {
            *result = res;
            return;
        }
        e = &((LocationRecord *)self->_locations->_data)[idx[h]];
        if (e->address == address) {
            if (name != 0) {
                if ((s = igStringTable_GetString((int *)self->_symbolNames, e->name)) != 0) {
                    strncpy(name, s, nameSize);
                } else {
                    *name = 0;
                }
            }
            *offset = e->offset;
            if (file != 0) {
                if ((s2 = igStringTable_GetString((int *)self->_sourceFileNames, e->file)) != 0) {
                    strncpy(file, s2, fileSize);
                } else {
                    *file = 0;
                }
            }
            *line = e->line;
            res = g_resultSuccess.v;
            break;
        }
        h++;
        if (h >= n) {
            h = 0;
        }
        i++;
    } while (i < n);
    *result = res;
}

void igLocationTable_AddLocationIfMissing(igLocationTableView *o, int a1, char *a2, int a3, char *a4, int a5) {
    switch (o->FindLocationIndex(a1)) { case -1: o->AddLocation(a1,a2,a3,a4,a5); break; default: break; }
}

/* Hash-bucket index for `key`: key modulo the hash-table size (`_hashCapacity`), or 0 when there
 * is none. */

unsigned int igLocationTable_Hash(igLocationTable *self, unsigned int key) {
    unsigned int hash_capacity;

    hash_capacity = self->_hashCapacity;
    if (hash_capacity != 0) {
        return key % hash_capacity;
    }
    return 0U;
}

int igLocationTable_InsertHash(igLocationTableView *self, int address, int index) {
    int probes = 0;
    int size = self->_hashIndex->_count;
    int limit = size / 2;
    int i;
    igTDataList<int> *t;
    int *data;
    if (size != 0) {
        i = self->Hash(address);
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
        self->Rehash(size * 2);
        return 0;
    }
done:
    return 1;
}

void igLocationTable_Rehash(igLocationTableView *self, int capacity) {
    igTDataList<int> *l; int n; int *a; int i; LocationRecord *s1; LocationRecord *s0; LocationRecord *s3;
    igLocationTable_SetHashCapacity((int)self, capacity);
    l = self->_hashIndex;
    if (!(capacity < l->_count)) List_Reserve((igDataList *)l, capacity, 4);
    l = self->_hashIndex;
    if (capacity >= 0) {
        if (!(capacity > l->_capacity)) { l->_count = capacity; } else { List_Resize((void *)l, capacity, 4); }
    }
    l = self->_hashIndex;
    n = l->_count;
    a = l->_data;
    for (i = 0; i < n; i++) {
        a[i] = g_locationTableEmptySlot;
    }
    igTDataList<unsigned int> *e = self->_locations;
    s1 = (LocationRecord *)e->_data;
    s0 = s1;
    s3 = s1 + e->_count / 5;
    while (s0 < s3) {
        if (self->InsertHash(s0->address, s0 - s1) == 0) break;
        s0++;
    }
}

