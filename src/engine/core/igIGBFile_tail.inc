inline bool igResult::failed() const { return v == g_resultFailure.v; }

int FUN_002e3a10(void *arg0, int arg1) {
    int sp1C;
    igMetaFieldView *temp_v0;

    sp1C = *(int *)((char *)(arg1) + 4);
    if (((igIGBFileView *)arg0)->_endianSwap != 0) {
        temp_v0 = (igMetaFieldView *)igIntMetaField_GetDefaultDescriptor();
        temp_v0->SwapBytes(&sp1C, 1);
    }
    return sp1C;
}

inline StreamHolder::~StreamHolder() {
    IG_OBJECT_RELEASE(p);
}

static inline void assign(igIGBFileView *self, const StreamHolder &h) {
    igFileView *v = h.p;
    igFileView *old;
    if (v != 0) {
        v->_refCount = v->_refCount + 1;
    }
    old = self->_file;
    IG_OBJECT_RELEASE(old);
    self->_file = v;
}

igResult FUN_002e3a60(igIGBFileView *self, const char *fileName, int mode) {
    if (fileName == 0 && self->_file == 0) {
        return g_resultFailure;
    }
    if (fileName == 0 && self->_file != 0) {
        return self->_file->vfunc_23(mode);
    }
    if (self->_file == 0 && fileName != 0) {
        {
            StreamHolder h(((igFileView *)igFile_Create((int)self->_temporaryMemoryPool)));
            assign(self, h);
        }
        if (self->_file == 0) {
            return g_resultFailure;
        }
        FUN_002e30b0((int *)self->_file, fileName);
        return self->_file->vfunc_23(mode);
    }
    self->_file->vfunc_24();
    {
        StreamHolder h(((igFileView *)igFile_Create((int)self->_temporaryMemoryPool)));
        assign(self, h);
    }
    FUN_002e30b0((int *)self->_file, fileName);
    return self->_file->vfunc_23(mode);
}

void FUN_002e3cb0(igIGBFileView *self) {
    igFileView *r;
    if (self->_file != 0) {
        self->_file->vfunc_24();
        r = self->_file;
        if (r != 0) {
            r->_refCount = r->_refCount - 1;
            if ((r->_refCount & 0x7FFFFF) == 0) igObject_Destroy(r);
        }
        self->_file = 0;
    }
}

void FUN_002e3d30(int *arg0) {
    int temp_s1;
    int *temp_a1;
    int var_v0;
    int temp_a0_2;
    void *temp_s0;
    int var_s0;
    int temp_v1;
    void *temp_a0_3;
    void *temp_a0;

    temp_a0 = (void *)(arg0[5]);
    if ((!temp_a0) || (strcmp(temp_a0, &DAT_004f7910[0]) == 0)) {
        temp_s1 = ((int *)arg0[26])[3];
        var_s0 = strlen(temp_s1) - 1;
        while (var_s0 > 0 && 0x2F != (temp_a0_2 = *(char *)((temp_s1 + var_s0) - 1)) && temp_a0_2 != 0x5C) {
            var_s0 = var_s0 - 1;
        }
        if (0 == (*(void * *)g_stringPool)) {
            var_v0 = (int)StringPool_Allocate(0x10);
            if (var_v0) {
                var_v0 = (int)StringPool_Construct((StringPool *)((void *)var_v0));
            }
            (*(void * *)g_stringPool) = (void *)var_v0;
        }
        temp_s0 = (void *)(((char *)StringPool_Intern((StringPool *)((*(void * *)g_stringPool)), (const char *)(temp_s1 + var_s0))));
        temp_a0_3 = (void *)(arg0[5]);
        if (temp_a0_3) {
            temp_a1 = (int *)((char *)temp_a0_3 - 8);
            temp_v1 = *(int *)((char *)(temp_a0_3) - 4) - 1;
            *(int *)((char *)(temp_a0_3) - 4) = temp_v1;
            if (!temp_v1) {
                StringChunk_ReleaseHeader((StringChunkOwnerView *)(*temp_a1), (int)temp_a1);
            }
        }
        arg0[5] = (int)(temp_s0);
    }
}

igResult FUN_002e3e30(igIGBFileView *f, const char *fileName) {
    if (f->_file == 0 && fileName == 0) {
        return g_resultFailure;
    }
    if (f->_file == 0) {
        if (FUN_002e3a60(f, fileName, 5) == g_resultFailure) {
            if (fileName != 0) {
                igFileView *h = f->_file;
                IG_OBJECT_RELEASE(h);
                f->_file = 0;
            }
            return g_resultFailure;
        }
        f->_autoOpened = 1;
    }
    if (f->_file == 0) {
        return g_resultFailure;
    }
    FUN_002e3d30((int *)f);
    FUN_002e31b0((int)f->_file, 5);
    return g_resultSuccess;
}

igResult FUN_002e3f50(igIGBFileView *arg1) {
    igMetaObject *meta;
    ObjectRefWord h;
    ObjectRefTarget *np;
    ObjectRefTarget *old;
    unsigned int n;
    unsigned int i;
    h.value = ((ObjectRefTarget *)FUN_002c8e10((int)arg1->_temporaryMemoryPool));
    np = h.value;
    if (np) {
        ++np->references;
    }
    old = (ObjectRefTarget *)arg1->_metaObjectListInFile;
    if (old) {
        --old->references;
        if (((unsigned long long)(long long)old->references & 0x7fffffULL) == 0)
            igObject_Destroy(old);
    }
    arg1->_metaObjectListInFile = (igObjectList *)np;
    h.releaseField();
    FUN_002fe600((igTDataList<ChainMeta *> *)arg1->_metaObjectListInFile, (ChainMeta *)g_igDirEntry_metaObject[0]);
    meta = g_igDirEntry_metaObject[0];
    n = ((unsigned int)igMetaObject_CountTree((MetaTreeNode *)meta));
    for (i = 0; i < n; i++) {
        ObjectList_AppendUniqueRetained((igTDataList<igObject *> *)arg1->_metaObjectListInFile, (igObject *)(((int)FUN_002fe300((igMetaObject *)meta, (int)i))));
    }
    return g_resultSuccess;
}

igResult FUN_002e4090(igIGBFileView *arg1) {
    int i;

    for (i = 0; i < arg1->_count; i++) {
        arg1->_data[i]->_index = i;
        arg1->_data[i]->vfunc_38(arg1);
    }
    return g_resultSuccess;
}

igResult FUN_002e4120(igIGBFileView *o) {
    int i; int s; char *p; int j; int n; int a;
    o->_memoryPoolNameBufferSize = 8;
    i = 0;
    do {
        a = strlen(FUN_002f8960(i)) + 1;
        i++;
        o->_memoryPoolNameBufferSize = o->_memoryPoolNameBufferSize + a;
    } while (i < 46);
    o->_memoryPoolNameBuffer = (int *)o->_temporaryMemoryPool->Allocate(o->_memoryPoolNameBufferSize);
    j = 0;
    p = (char *)o->_memoryPoolNameBuffer;
    ((int *)p)[0] = o->_memoryPoolNameBufferSize;
    ((int *)p)[1] = 46;
    p += 8;
    do {
        s = FUN_002f8960(j);
        n = strlen(s) + 1;
        memcpy(p, s, n);
        j++;
        p += n;
    } while (j < 46);
    if (o->_endianSwap) o->imf->SwapBytes(o->_memoryPoolNameBuffer, 2);
    return g_resultSuccess;
}

igResult FUN_002e4240(igIGBFile *arg1) {
    int var_s0;
    void *temp_a0;

    arg1->_objectCount = 0;
    arg1->_memoryRefCount = 0;
    arg1->_objectBufferSize = 0;
    arg1->_memoryRefBufferSize = 0;
    for (var_s0 = 0; var_s0 < arg1->_count; var_s0++) {
        temp_a0 = (void *)(*(int *)(arg1->_data + (var_s0 * 4)));
        ((igDirEntryView *)temp_a0)->vfunc_39((igIGBFileView *)arg1);
    }
    return g_resultSuccess;
}

static inline void bump(const IntListHolder &r, int off) { int *c = (int *)((char *)r.p->_data + off); *c = *c + 1; }

static inline void fillWords(igTDataList<int> *l, int c, int *value) {
    if (c >= 0) { if (c <= l->_capacity) { l->_count = c; } else { List_Resize(l, c, 4); } }
}

static inline int indexOfParent(igObjectList *l, const MetaTableKey &key) {
    int n = l->_count;
    int i;
    for (i = 0; i < n; i++) {
        if (key.v == ((int *)l->_data)[i]) { return i; }
    }
    return -1;
}

igResult FUN_002e42d0(igIGBFileView *self) {
    int base;
    int i;
    self->_metaObjectCount = self->_metaObjectListInFile->_count;
    self->_metaObjectBufferSize = self->_metaObjectCount * 24;
    {
    IntListHolder inherited((igTDataList<int> *)igIntList_Create((int)self->_temporaryMemoryPool));
    fillWords(inherited.p, self->_metaObjectCount, 0);
    {
        int n = inherited.p->_count;
        int *d = inherited.p->_data;
        int k;
        for (k = 0; k < n; k++) { d[k] = DAT_004c2130[0]; }
    }
    {
    IntListHolder persistent((igTDataList<int> *)igIntList_Create((int)self->_temporaryMemoryPool));
    fillWords(persistent.p, self->_metaObjectCount, 0);
    {
        int n = persistent.p->_count;
        int *d = persistent.p->_data;
        int k;
        for (k = 0; k < n; k++) { d[k] = DAT_004c2138[0]; }
    }
    base = igMetaObject_GetFieldCount((igMetaObject *)g_igObject_metaObject[0]);
    for (i = 0; i < self->_metaObjectCount; i++) {
        int j;
        __internalObjectList *fields;
        int n;
        igMetaObject *t;
        int off;
        off = i * 4;
        t = *(igMetaObject **)((char *)self->_metaObjectListInFile->_data + off);
        fields = (__internalObjectList *)t->_metaFields;
        n = fields->_count;
        for (j = base; j < n; j++) {
            igMetaField *f = ((igMetaField **)fields->_data)[j];
            if (f->_isRunTime == 0) {
                if (f->_persistent != 0) {
                    self->_metaObjectBufferSize = self->_metaObjectBufferSize + 6;
                    bump(inherited, off);
                }
                bump(persistent, off);
            }
        }
        self->_metaObjectBufferSize = self->_metaObjectBufferSize + (strlen((char *)t->_name) + 1);
        self->_metaObjectBufferSize = (self->_metaObjectBufferSize + 1) & ~1;
    }
    self->_metaObjectBuffer = self->_temporaryMemoryPool->AllocateAligned(self->_metaObjectBufferSize, 16);
    {
        igMetaObject *t;
        int off;
        int k;
        MetaTableRecord *rec = (MetaTableRecord *)self->_metaObjectBuffer;
        for (k = 0; k < self->_metaObjectCount; k++) {
            MetaTableKey key;
            int len;
            off = k * 4;
            t = *(igMetaObject **)((char *)self->_metaObjectListInFile->_data + off);
            len = strlen((char *)t->_name) + 1;
            rec->nameSize = (len + 1) & ~1;
            rec->majorVersion = t->_majorVersion;
            rec->minorVersion = t->_minorVersion;
            rec->fieldCount = *(int *)((char *)inherited.p->_data + off);
            {
                igObjectList *l = self->_metaObjectListInFile;
                *(int *)&key = t->_parent;
                rec->parentIndex = indexOfParent(l, key);
            }
            rec->persistCount = base + *(int *)((char *)persistent.p->_data + off);
            rec++;
        }
    }
    {
        char *out = (char *)((MetaTableRecord *)self->_metaObjectBuffer + self->_metaObjectCount);
        igMetaFieldView *desc;
        short *p;
        igMetaField *f;
        int k;
        int j;
        int n;
        int off;
        igMetaObject *t;
        __internalObjectList *fields;
        desc = (igMetaFieldView *)((void *)igShortMetaField_GetDefaultDescriptor());
        for (k = 0; k < self->_metaObjectCount; k++) {
            off = k * 4;
            t = *(igMetaObject **)((char *)self->_metaObjectListInFile->_data + off);
            strcpy(out, (char *)t->_name);
            fields = (__internalObjectList *)t->_metaFields;
            j = base;
            n = fields->_count;
            out += ((MetaTableRecord *)self->_metaObjectBuffer)[k].nameSize;
            p = (short *)out;
            for (; j < n; j++) {
                f = ((igMetaField **)fields->_data)[j];
                if (f->_persistent != 0 && f->_isRunTime == 0) {
                    p[0] = igMetaField_GetTypeIndex((igMetaFieldView *)f);
                    p[1] = f->_internalIndex;
                    p[2] = f->_size;
                    p += 3;
                }
            }
            if (self->_endianSwap != 0) {
                desc->SwapBytes(out, *(int *)((char *)inherited.p->_data + off) * 3);
            }
            out = (char *)p;
        }
    }
    if (self->_endianSwap != 0) { self->imf->SwapBytes(self->_metaObjectBuffer, self->_metaObjectCount * 6); }
    return g_resultSuccess;
    }
    }
}

igResult FUN_002e47f0(igIGBFileView *arg1) {
    int i;
    int j;
    int s5;
    int *s4;
    char *s2;
    igObjectDispatchView *p;
    arg1->_metaFieldCount = ((IgbRegistryTable *)((void *)FUN_002fc250()))->count;
    arg1->_metaFieldBufferSize = arg1->_metaFieldCount * 12;
    for (i = 0; i < arg1->_metaFieldCount; i++) {
        arg1->_metaFieldBufferSize = arg1->_metaFieldBufferSize + (strlen(((IgbRegistryTable *)((void *)FUN_002fc250()))->data[i]->getMeta()->_name) + 1);
    }
    arg1->_mfBuf = (char *)arg1->_temporaryMemoryPool->AllocateAligned(arg1->_metaFieldBufferSize, 16);
    s5 = 0;
    s4 = (int *)arg1->_mfBuf;
    for (i = 0; i < arg1->_metaFieldCount; i++) {
        p = ((IgbRegistryTable *)((void *)FUN_002fc250()))->data[i];
        s4[s5] = strlen(p->getMeta()->_name) + 1;
        s5++;
        s4[s5] = p->getMeta()->_majorVersion;
        s5++;
        s4[s5] = p->getMeta()->_minorVersion;
        s5++;
    }
    s2 = arg1->_mfBuf + arg1->_metaFieldCount * 12;
    for (j = 0; j < arg1->_metaFieldCount; j++) {
        strcpy(s2, ((IgbRegistryTable *)((void *)FUN_002fc250()))->data[j]->getMeta()->_name);
        s2 += *(int *)(arg1->_mfBuf + j * 12);
    }
    if (arg1->_endianSwap != 0) arg1->imf->SwapBytes(arg1->_mfBuf, arg1->_metaFieldCount * 3);
    return g_resultSuccess;
}

static inline char *nameOf(const NameListHolder &r, int i) {
    char *n = r.p->data[i]->name;
    n = (n == 0) ? (*(char * *)g_stringObjEmptyText) : n;
    return n;
}

igResult FUN_002e4a40(igIGBFileView *self) {
    NameListHolder names(g_globalContext->names);
    int i;
    int *lengths;
    char *out;
    self->_alignmentCount = (names.p != 0) ? names.p->count : 0;
    i = 0;
    self->_alignmentBufferSize = self->_alignmentCount * 4 + 12;
    for (; i < self->_alignmentCount; i++) {
        self->_alignmentBufferSize += strlen(nameOf(names, i)) + 1;
    }
    self->_alignmentBuffer = (int *)self->_temporaryMemoryPool->AllocateAligned(self->_alignmentBufferSize, 16);
    {
        int *b = self->_alignmentBuffer;
        lengths = b + 3;
        b[0] = self->_alignmentBufferSize;
        b[1] = 1;
        b[2] = self->_alignmentCount;
    }
    for (i = 0; i < self->_alignmentCount; i++) {
        lengths[i] = strlen(nameOf(names, i)) + 1;
    }
    out = (char *)(lengths + self->_alignmentCount);
    for (i = 0; i < self->_alignmentCount; i++) {
        strcpy(out, nameOf(names, i));
        out += lengths[i];
    }
    if (self->_endianSwap != 0) { self->imf->SwapBytes(self->_alignmentBuffer, self->_alignmentCount + 3); }
    return g_resultSuccess;
}

igResult FUN_002e4c90(igIGBFileView *self) {
    igDirectoryListView *l = self->_externalDirectoryList;
    int n, i, k;
    if (l != 0) { n = l->_count; if (n > 0) {
        char *p;
        int *q;
        int total;
        self->_hasExternal = 1;
        total = (n + 3) * 4;
        self->_externalDirectoryBufferSize = total;
        for (i = 0; i < n; i++) {
            self->_externalDirectoryBufferSize = self->_externalDirectoryBufferSize + (strlen(self->_externalDirectoryList->_data[i]->_name) + 1);
        }
        self->_externalDirectoryBuffer = (int *)self->_temporaryMemoryPool->AllocateAligned(self->_externalDirectoryBufferSize, 16);
        self->_externalDirectoryBuffer[0] = self->_externalDirectoryBufferSize;
        self->_externalDirectoryBuffer[1] = 1;
        self->_externalDirectoryBuffer[2] = n;
        q = self->_externalDirectoryBuffer + 3;
        for (i = 0; i < n; i++) {
            q[i] = strlen(self->_externalDirectoryList->_data[i]->_name) + 1;
        }
        p = (char *)self->_externalDirectoryBuffer + total;
        for (k = 0; k < n; k++) {
            strcpy(p, self->_externalDirectoryList->_data[k]->_name);
            p += strlen(p) + 1;
        }
        if (self->_endianSwap != 0) {
            self->imf->SwapBytes(self->_externalDirectoryBuffer, n + 2);
        }
    goto done; } } self->_hasExternal = 0; done:
    return g_resultSuccess;
}

/* Lays the unique entries out in one buffer: sizes them, allocates, then writes each. */
igResult FUN_002e4e60(igIGBFile *file) {
    char *cursor;
    int i;
    file->_entryBufferSize = 0;
    file->_entryCount = ((igObjectList *)file->_uniqueEntryList)->_count;
    for (i = 0; i < file->_entryCount; i++) {
        file->_entryBufferSize = file->_entryBufferSize + igObject_GetSerializedSize((SizeObject *)thunk_FUN_002d7e90((int *)file->_uniqueEntryList, i));
    }
    file->_dirBuf = (int)((igMemoryPoolView *)file->_temporaryMemoryPool)->AllocateAligned(file->_entryBufferSize, 16);
    cursor = (char *)file->_dirBuf;
    for (i = 0; i < file->_entryCount; i++) {
        cursor += igObject_WritePersistentFields((igObjectDispatchView *)thunk_FUN_002d7e90((int *)file->_uniqueEntryList, i), (int *)cursor, 0, (igTDataList<ChainMeta *> *)file->_metaObjectListInFile, file->_endianSwap);
    }
    return g_resultSuccess;
}

igResult FUN_002e5110(igIGBFileView *self) {
    int n;
    int i;
    if (self->_sharedEntries != 0) { return g_resultSuccess; }
    {
        igTDataList<int> *old = self->_refList;
        int pool = (int)self->_temporaryMemoryPool;
        IG_OBJECT_RELEASE(old);
        self->_refList = (igTDataList<int> *)FUN_002c9130(pool);
    }
    {
        int c = self->_count;
        igTDataList<int> *l = self->_refList;
        if (c >= 0) { if (c <= l->_capacity) { l->_count = c; } else { List_Resize(l, c, 4); } }
    }
    {
        igObject *old = self->_entryPool;
        int pool = (int)self->_temporaryMemoryPool;
        IG_OBJECT_RELEASE(old);
        self->_entryPool = (igObject *)FUN_002bd680(pool);
    }
    {
        igObjectList *old = self->_uniqueEntryList;
        int pool = (int)self->_temporaryMemoryPool;
        IG_OBJECT_RELEASE(old);
        self->_uniqueEntryList = (igObjectList *)FUN_002c72c0(pool);
    }
    n = self->_count;
    for (i = 0; i < n; i++) {
        igDirEntryView *o = self->_data[i];
        igDirEntryView *r;
        igDirEntryView *old;
        int c;
        if (o == o->resolve(self)) {
            igObjectList *list = self->_uniqueEntryList;
            IgbFixRetain keep(o);
            List_InsertWords((igDataList *)list, FUN_00142bb0(list, &keep), 1, &keep);
        }
        {
            int word;
            igTDataList<int> *w = self->_refList;
            word = o->_ref;
            int k = w->_count;
            if (k != 0 && i >= 0 && k > i) { ((int *)w->_data)[i] = word; }
        }
        o->setReferenceIndex(o->_ref);
        o->vfunc_23(0);
        o->_index = i;
        r = o->resolve(self);
        if (r != 0) { r->_refCount = r->_refCount + 1; }
        old = self->_data[i];
        IG_OBJECT_RELEASE(old);
        c = self->_count;
        if (c != 0 && i >= 0 && c > i) { self->_data[i] = r; }
    }
    self->_sharedEntries = 1;
    return g_resultSuccess;
}

/* The same layout for the file's own object list. */
igResult FUN_002e53f0(igIGBFile *file) {
    char *cursor;
    int i;
    file->_entryBufferSize = 0;
    file->_entryCount = file->_count;
    for (i = 0; i < file->_entryCount; i++) {
        file->_entryBufferSize = file->_entryBufferSize + igObject_GetSerializedSize(((SizeObject **)file->_data)[i]);
    }
    file->_dirBuf = (int)((igMemoryPoolView *)file->_temporaryMemoryPool)->AllocateAligned(file->_entryBufferSize, 16);
    cursor = (char *)file->_dirBuf;
    for (i = 0; i < file->_entryCount; i++) {
        cursor += igObject_WritePersistentFields(((igObjectDispatchView **)file->_data)[i], (int *)cursor, 0, (igTDataList<ChainMeta *> *)file->_metaObjectListInFile, file->_endianSwap);
    }
    return g_resultSuccess;
}

igResult FUN_002e54e0(igIGBFileView *o) {
    int i;
    int n;
    igMemoryPoolView *p = o->_temporaryMemoryPool; int x = o->_objectBufferSize;
    o->_objBuf = p->AllocateAligned(x, 16);
    o->_objectBufferPlace = (int)o->_objBuf;
    n = o->_count;
    for (i = 0; i < n; i++) {
        ((igDirEntryView *)FUN_002d7e90((int *)o, i))->vfunc_40(o);
    }
    return g_resultSuccess;
}

/* The 48-byte header: the table sizes and counts, then the magic cookie and the version word with the
 * file's flags in its top bits. */
igResult FUN_002e5590(igIGBFileView *o) {
    int *t = (int *)o->_temporaryMemoryPool->AllocateAligned(48, 16);
    memset(t, 0, 48);
    t[0] = o->_entryBufferSize; t[1] = o->_entryCount; t[2] = o->_metaObjectBufferSize; t[3] = o->_metaObjectCount; t[4] = o->_objectBufferSize; t[5] = o->_objectCount;
    t[6] = o->_memoryRefBufferSize; t[7] = o->_memoryRefCount; t[8] = o->_metaFieldBufferSize; t[9] = o->_metaFieldCount; t[10] = o->_magicCookie;
    int v = o->_magicVersion;
    if (o->_hasInfo) v |= 0x80000000;
    if (o->_hasExternal) v |= 0x40000000;
    if (o->_sharingState) v |= 0x20000000;
    if (o->_useMemoryPoolAssignmentsState) v |= 0x10000000;
    t[11] = v;
    if (o->_endianSwap) o->imf->SwapBytes(t, 12);
    o->_file->Write(t, 4, 12);
    o->_temporaryMemoryPool->Free(t);
    return g_resultSuccess;
}

igResult FUN_002e56f0(igIGBFileView *arg1) {
    int s4 = arg1->_file->Write(arg1->_mfBuf, arg1->_metaFieldBufferSize, 1);
    int s3 = arg1->_file->Write(arg1->_alignmentBuffer, arg1->_alignmentBufferSize, 1);
    int s2 = arg1->_file->Write(arg1->_metaObjectBuffer, arg1->_metaObjectBufferSize, 1);
    if (arg1->_externalDirectoryBuffer != 0) {
        arg1->_file->Write(arg1->_externalDirectoryBuffer, arg1->_externalDirectoryBufferSize, 1);
        arg1->_temporaryMemoryPool->Free(arg1->_externalDirectoryBuffer);
        arg1->_externalDirectoryBuffer = 0;
    }
    int s1 = 1;
    if (arg1->_useMemoryPoolAssignmentsState != 0) {
        s1 = arg1->_file->Write(arg1->_memoryPoolNameBuffer, arg1->_memoryPoolNameBufferSize, s1);
    }
    int s0 = arg1->_file->Write(arg1->_dirBuf, arg1->_entryBufferSize, 1);
    if (arg1->_endianSwap != 0) {
        arg1->imf->SwapBytes(arg1->_indexBuffer, 2);
    }
    int s7 = arg1->_file->Write(arg1->_indexBuffer, arg1->_indexBufferSize, 1);
    if (arg1->_infoListPlace > -1) {
        if (arg1->_endianSwap != 0) {
            arg1->imf->SwapBytes((char *)arg1 + DAT_00586280[0]->f8, 1);
        }
        arg1->_file->Write((char *)arg1 + DAT_00586280[0]->f8, 4, 1);
    }
    int s8 = arg1->_file->Write(arg1->_objBuf, arg1->_objectBufferSize, 1);
    int v = arg1->vfunc_34();
    if (s7 + (s3 + (s4 + (v + (s8 + (s0 + (s2 + s1)))))) == 0) {
        return g_resultFailure;
    } else {
        return g_resultSuccess;
    }
}

igResult FUN_002e5950(igIGBFileView *arg1) {
    if (arg1->_autoOpened != 0) {
        FUN_002e3cb0(arg1);
    }
    return igResult(*(int *)0x4FB410);
}

igResult FUN_002e5990(igIGBFileView *o) {
    o->_temporaryMemoryPool->Free(o->_metaObjectBuffer); o->_metaObjectBuffer = 0;
    o->_temporaryMemoryPool->Free(o->_dirBuf); o->_dirBuf = 0;
    o->_temporaryMemoryPool->Free(o->_objBuf); o->_objBuf = 0;
    o->_temporaryMemoryPool->Free(o->_mfBuf); o->_mfBuf = 0;
    o->_temporaryMemoryPool->Free(o->_alignmentBuffer); o->_alignmentBuffer = 0;
    if (o->_indexBuffer) o->_temporaryMemoryPool->Free(o->_indexBuffer);
    o->_memoryPoolNameBufferSize = 0;
    if (o->_memoryPoolNameBuffer) { o->_temporaryMemoryPool->Free(o->_memoryPoolNameBuffer); o->_memoryPoolNameBuffer = 0; }
    igIntList *r = o->_memoryPoolHandles;
    if (r) { r->_refCount -= 1; if ((r->_refCount & 0x7fffff) == 0) igObject_Destroy(r); }
    o->_memoryPoolHandles = 0;
    return g_resultSuccess;
}

igResult FUN_002e5ac0(void *arg1) {
    void *temp_a1;

    temp_a1 = (void *)(*(int *)((char *)(arg1) + 28));
    if (*(int *)((char *)(temp_a1) + 8) > 0) {
        *(int *)((char *)(arg1) + 220) = FUN_002d8620((int)arg1, (int)temp_a1, 0, 0);
        *(char *)((char *)(arg1) + 212) = 1;
    }
    return g_resultSuccess;
}

int Gap__Core__igIGBFile__vfunc_28(igIGBFileView *arg0, const char *fileName) {
    int *pp; igObject *t; igObject *t2; igObject *a; igObject *b;
    FUN_00306e50(((LogContext * *)g_objectSystem)[0]->f56, 2, (const char *)text_forceWriteMemoryPoolInfoFromMeta, (char *)&arg0->_forceWriteMemoryPoolInfoFromMetaState, 0, 0);
    igResult sp7C = FUN_002e3e30(arg0, fileName);
    pp = (int *)((int)&sp7C + 0);
    if (*pp == g_resultFailure.v) return 0;
    igResult sp78 = FUN_002e5ac0(arg0);
    pp = (int *)((int)&sp78 + 0);
    if (*pp == g_resultFailure.v) return 0;
    FUN_00302540((ObjectListView *)arg0, (Field *)DAT_00586730[0]);
    a = (igObject *)igIntMetaField_GetDefaultDescriptor();
    if (a != 0) a->_refCount = a->_refCount + 1;
    t = (igObject *)arg0->imf;
    IG_OBJECT_RELEASE(t);
    arg0->imf = (igMetaFieldView *)a;
    b = (igObject *)igShortMetaField_GetDefaultDescriptor();
    if (b != 0) b->_refCount = b->_refCount + 1;
    t2 = (igObject *)arg0->smf;
    IG_OBJECT_RELEASE(t2);
    arg0->smf = (igMetaFieldView *)b;
    igResult sp74 = FUN_002e3f50(arg0);
    pp = (int *)((int)&sp74 + 0);
    if (*pp == g_resultFailure.v) return 0;
    igResult sp70 = FUN_002e4090(arg0);
    pp = (int *)((int)&sp70 + 0);
    if (*pp == g_resultFailure.v) return 0;
    igResult sp6C = FUN_002e4120(arg0);
    pp = (int *)((int)&sp6C + 0);
    if (*pp == g_resultFailure.v) return 0;
    igResult sp68 = FUN_002e4240((igIGBFile *)arg0);
    pp = (int *)((int)&sp68 + 0);
    if (*pp == g_resultFailure.v) return 0;
    igResult sp64 = FUN_002e42d0(arg0);
    pp = (int *)((int)&sp64 + 0);
    if (*pp == g_resultFailure.v) return 0;
    igResult sp60 = FUN_002e47f0(arg0);
    pp = (int *)((int)&sp60 + 0);
    if (*pp == g_resultFailure.v) return 0;
    igResult sp5C = FUN_002e4a40(arg0);
    pp = (int *)((int)&sp5C + 0);
    if (*pp == g_resultFailure.v) return 0;
    igResult sp58 = FUN_002e4c90(arg0);
    pp = (int *)((int)&sp58 + 0);
    if (*pp == g_resultFailure.v) return 0;
    if (arg0->_sharingState == 0) {
    igResult sp54 = FUN_002e53f0((igIGBFile *)arg0);
    pp = (int *)((int)&sp54 + 0);
    if (*pp == g_resultFailure.v) return 0;
    } else {
    igResult sp50 = FUN_002e5110(arg0);
    pp = (int *)((int)&sp50 + 0);
    if (*pp == g_resultFailure.v) return 0;
    igResult sp4C = FUN_002e4e60((igIGBFile *)arg0);
    pp = (int *)((int)&sp4C + 0);
    if (*pp == g_resultFailure.v) return 0;
    igResult sp48 = FUN_002e4f60(arg0);
    pp = (int *)((int)&sp48 + 0);
    if (*pp == g_resultFailure.v) return 0;
    }
    igResult sp44 = FUN_002e54e0(arg0);
    pp = (int *)((int)&sp44 + 0);
    if (*pp == g_resultFailure.v) return 0;
    igResult sp40 = FUN_002e5590(arg0);
    pp = (int *)((int)&sp40 + 0);
    if (*pp == g_resultFailure.v) return 0;
    igResult sp3C = FUN_002e56f0(arg0);
    pp = (int *)((int)&sp3C + 0);
    if (*pp == g_resultFailure.v) return 0;
    igResult sp38 = FUN_002e5950(arg0);
    pp = (int *)((int)&sp38 + 0);
    if (*pp == g_resultFailure.v) return 0;
    igResult sp34 = FUN_002e5990(arg0);
    pp = (int *)((int)&sp34 + 0);
    if (*pp == g_resultFailure.v) return 0;
    if (arg0->_autoWriteFilePostProcessState == 1) { igResult sp30 = arg0->vfunc_32(); }
    return arg0->_count;
}

igResult FUN_002e5f70(igIGBFileView *arg1, const char *fileName) {
    igFileView *o;
    int *pp;
    if ((arg1->_file == 0) && (fileName == 0)) {
        return g_resultFailure;
    }
    if (arg1->_file == 0) {
        igResult r = FUN_002e3a60(arg1, fileName, 4);
        pp = (int *)((int)&r + 0);
        if (*pp == g_resultFailure.v) {
            if (fileName != 0) {
                o = arg1->_file;
                IG_OBJECT_RELEASE(o);
                arg1->_file = 0;
            }
            return g_resultFailure;
        }
        arg1->_autoOpened = 1;
    }
    if (arg1->_file == 0) {
        return g_resultFailure;
    }
    FUN_002e3d30((int *)arg1);
    FUN_002e31b0((int)arg1->_file, 4);
    return g_resultSuccess;
}

igResult igIGBFile_ReadHeader(igIGBFileView *arg1) {
    IgbFileHeader *h;
    igObject *o;
    igObject *t;

    if (igIGBFile_GetSectionBuffer(arg1, 0xC0) == g_resultFailure) {
        return g_resultFailure;
    }
    h = (IgbFileHeader *)arg1->_chunk;
    arg1->_file->Read(h, 4, 0xC);
    o = (igObject *)igIntMetaField_GetDefaultDescriptor();
    if (o != 0) {
        o->_refCount = o->_refCount + 1;
    }
    t = (igObject *)arg1->imf;
    IG_OBJECT_RELEASE(t);
    arg1->imf = (igMetaFieldView *)o;
    o = (igObject *)igShortMetaField_GetDefaultDescriptor();
    if (o != 0) {
        o->_refCount = o->_refCount + 1;
    }
    t = (igObject *)arg1->smf;
    IG_OBJECT_RELEASE(t);
    arg1->smf = (igMetaFieldView *)o;
    if (h->magicCookie != arg1->_magicCookie) {
        arg1->imf->SwapBytes(h, 0xC);
        if (h->magicCookie == arg1->_magicCookie) {
            arg1->_endianSwap = 1;
        }
    } else {
        arg1->_endianSwap = 0;
    }
    if (h->magicCookie != arg1->_magicCookie) {
        return g_resultFailure;
    } else {
        arg1->_magicVersion = (int)*(unsigned short *)&h->magicVersion;
        if ((int)arg1->_magicVersion > 7) {
            return g_resultFailure;
        } else {
            arg1->_hasInfo = (h->magicVersion & 0x80000000) != 0;
            arg1->_hasExternal = (h->magicVersion & 0x40000000) > 0;
            arg1->_sharedEntries = (h->magicVersion & 0x20000000) > 0;
            arg1->_hasVersion1Cruft = h->magicVersion == 1;
            arg1->_hasMemoryPoolNames = (h->magicVersion & 0x10000000) > 0;
            if (arg1->_hasVersion1Cruft != 0) {
                arg1->_version1CruftMultiply = 1;
            } else {
                arg1->_version1CruftMultiply = 0;
            }
            arg1->_entryBufferSize = h->entryBufferSize;
            arg1->_entryCount = h->entryCount;
            arg1->_metaObjectBufferSize = h->metaObjectBufferSize;
            arg1->_metaObjectCount = h->metaObjectCount;
            arg1->_objectBufferSize = h->objectBufferSize;
            arg1->_objectCount = h->objectCount;
            arg1->_memoryRefBufferSize = h->memoryRefBufferSize;
            arg1->_memoryRefCount = h->memoryRefCount;
            arg1->_metaFieldBufferSize = h->metaFieldBufferSize;
            arg1->_metaFieldCount = h->metaFieldCount;
            return g_resultSuccess;
        }
    }
}

igResult FUN_002e6330(igIGBFileView *arg1) {
    bool var_a0;
    int var_v1;

    if (igIGBFile_GetSectionBuffer(arg1, arg1->_metaObjectBufferSize) == g_resultFailure) {
        return g_resultFailure;
    }
    arg1->_metaObjectBuffer = arg1->_chunk;
    var_a0 = true;
    if (arg1->_metaObjectBufferSize != 0) {
        var_a0 = arg1->_file->Read(arg1->_metaObjectBuffer, arg1->_metaObjectBufferSize, 1) == 1;
    }
    var_v1 = g_resultSuccess.v;
    if (!(int)var_a0) {
        var_v1 = g_resultFailure.v;
    }
    return igResult(var_v1);
}

igResult FUN_002e6f50(igIGBFileView *arg1) {
    int n;
    char *p;
    char c;
    arg1->_basePath = (char *)arg1->_temporaryMemoryPool->vfunc_58(arg1->_file->_fileName);
    n = strlen(arg1->_basePath);
    while (--n >= 0) {
        p = arg1->_basePath + n;
        c = *p;
        if (c == 0x2F || c == 0x5C) {
            *p = 0;
            break;
        }
    }
    if (n < 0) {
        *arg1->_basePath = 0;
    }
    return g_resultSuccess;
}

void FUN_002e7000(void) {
    FUN_00306e50(*(int *)((char *)(((LogContext * *)g_objectSystem)[0]) + 56), 2, (const char *)text_blindObjects, (char *)&GPR_00554c04, 0, 0);
}

igResult FUN_002e7030(igIGBFileView *arg1) {
    int hi;
    int a2;
    hi = (arg1->_chunkSize - arg1->_chunkPlace) % arg1->_chunkSize;
    if (hi > 0) {
        memcpy(arg1->_chunk, arg1->_chunk + arg1->_chunkPlace, hi);
    }
    a2 = arg1->_chunkSize - hi;
    if (arg1->_bufferSize < hi + (arg1->_bufferPlace + a2)) {
        a2 = (arg1->_bufferSize - arg1->_bufferPlace) - hi;
    }
    if (arg1->_file->Read(arg1->_chunk + hi, a2, 1) != 1) {
        return g_resultFailure;
    } else {
        arg1->_chunkPlace = 0;
        return g_resultSuccess;
    }
}

static inline IgbReadEntry *castToKind(IgbReadEntry *object) {
    if (object != 0 && igObject_IsKindOf((void *)object, (igMetaObject *)g_igDirEntry_metaObject[0]) != 0) {
        return object;
    }
    return 0;
}

SectionObjectRef igIGBFile_ReadObject(igIGBFile *file) {
    int metaIndex;
    int *record;
    int end = file->_chunk + file->_chunkPlace;
    int position = file->_chunkPlace;
    int needed;
    if (position > file->_chunkSize - 9 || (needed = file->_version1CruftMultiply * 4 + (file->_chunkPlace + FUN_002e3a10(file, end)), file->_chunkSize < needed)) {
        if (FUN_002e7030((igIGBFileView *)file) == g_resultFailure) {
            return SectionObjectRef((igDirEntryView *)0, kRetainReference);
        }
    }
    record = (int *)(file->_chunk + file->_chunkPlace);
    metaIndex = *record;
    if (file->_endianSwap != 0) {
        ((igMetaFieldView *)igIntMetaField_GetDefaultDescriptor())->SwapBytes(&metaIndex, 1);
    }
    igSmartPointer<IgbReadEntry> object(castToKind((IgbReadEntry *)igMetaObject_CreateInstanceWithPool(((PooledMeta **)((igObjectList *)file->_metaObjectListInFile)->_data)[metaIndex], (MemoryPool *)file->_temporaryMemoryPool)), kRetainReference);
    object->release();
    igObject_RegisterInstance((void **)object.p, 0);
    int read;
    if (file->_magicVersion < 4) {
        read = FUN_002fff90((ReadObject *)object.p, (FieldRecordHead *)record, file, (igTDataList<ChainMeta *> *)file->_metaObjectListInFile, file->_endianSwap);
    } else {
        read = FUN_00300250((FieldObjectView *)object.p, (FieldRecordHead *)record, (FieldDirView *)file, (igTDataList<ChainMeta *> *)file->_metaObjectListInFile, file->_endianSwap);
    }
    file->_chunkPlace = file->_chunkPlace + read;
    file->_bufferPlace = file->_bufferPlace + read;
    file->_chunkPlace = file->_chunkPlace + file->_version1CruftMultiply * 4;
    file->_bufferPlace = file->_bufferPlace + file->_version1CruftMultiply * 4;
    return object;
}

igResult igIGBFile_ReadObjectSection(igIGBFileView *file) {
    int pool;
    igObjectList *list;
    int i;
    file->_chunkPlace = file->_chunkSize;
    file->_bufferPlace = 0;
    file->_bufferSize = file->_entryBufferSize;
    list = file->_uniqueEntryList;
    pool = (int)file->_temporaryMemoryPool;
    if (list != 0) {
        list->_refCount = list->_refCount - 1;
        if ((list->_refCount & 0x7FFFFF) == 0) igObject_Destroy(list);
    }
    file->_uniqueEntryList = (igObjectList *)FUN_002c72c0(pool);
    ObjectList_ResizeRetained((igTDataList<igObject *> *)file->_uniqueEntryList, file->_entryCount);
    if (FUN_002e7030(file) == g_resultFailure) {
        return g_resultFailure;
    }
    for (i = 0; i < file->_entryCount; i++) {
        SectionObjectRef object = igIGBFile_ReadObject((igIGBFile *)file);
        if (object.p == 0) {
            return g_resultFailure;
        }
        if (file->_useMemoryPoolAssignmentsState != 0 && file->_memoryPoolHandles != 0 && g_useOwnerAllocator == 0) {
            int index = object->memoryPoolIndex();
            if (index > 0) {
                object->setMemoryPool(((int *)file->_memoryPoolHandles->_data)[index]);
            }
        } else {
            object->setMemoryPool(-1);
        }
        igDirEntryView *entry = object.p;
        list = file->_uniqueEntryList;
        if (entry != 0) entry->_refCount = entry->_refCount + 1;
        igObject *old = ((igObject **)list->_data)[i];
        if (old != 0) {
            old->_refCount = old->_refCount - 1;
            if ((old->_refCount & 0x7FFFFF) == 0) igObject_Destroy(old);
        }
        if (list->_count != 0 && i >= 0 && i < list->_count) {
            ((igDirEntryView **)list->_data)[i] = entry;
        }
    }
    if (file->_hasCriticalFailure != 0) {
        return g_resultFailure;
    }
    return g_resultSuccess;
}

igResult FUN_002e7640(igIGBFileView *self) {
    int count = 0;
    int pos;
    int chunk;
    int words;
    int i;
    int base;
    self->_file->Read(&self->_indexBufferSize, 4, 1);
    self->_file->Read(&count, 4, 1);
    if (self->_endianSwap != 0) {
        self->imf->SwapBytes(&self->_indexBufferSize, 1);
        self->imf->SwapBytes(&count, 1);
    }
    if (igIGBFile_GetSectionBuffer(self, 0x1000) == g_resultFailure) {
        return g_resultFailure;
    }
    pos = 8;
    ObjectList_ResizeRetained((igTDataList<igObject *> *)self, count);
    for (; pos < self->_indexBufferSize; pos += chunk) {
        int rest = self->_indexBufferSize - pos;
        chunk = self->_chunkSize & ~1;
        if (chunk > rest) { chunk = rest; }
        words = chunk >> 1;
        self->_file->Read(self->_chunk, chunk, 1);
        if (self->_endianSwap != 0) { self->smf->SwapBytes(self->_chunk, words); }
        base = (unsigned int)(pos - 8) >> 1;
        for (i = 0; i < words; i++) {
            igDirEntryView *o = (igDirEntryView *)thunk_FUN_002d7e90((int *)self->_uniqueEntryList, ((short *)self->_chunk)[i]);
            int index;
            igDirEntryView *old;
            int n;
            if (o != 0) { o->_refCount = o->_refCount + 1; }
            index = i + base;
            old = self->_data[index];
            IG_OBJECT_RELEASE(old);
            n = self->_count;
            if (n != 0 && index >= 0 && n > index) { self->_data[index] = o; }
        }
    }
    return g_resultSuccess;
}

igResult FUN_002e78b0(igIGBFileView *arg1) {
    int temp_s1;
    int temp_s0;
    int i;
    igTDataList<int> *temp_a0;
    igTDataList<int> *temp_a0_2;
    temp_a0 = arg1->_refList;
    temp_s1 = arg1->_count;
    temp_s0 = (int)arg1->_temporaryMemoryPool;
    if (temp_a0 != 0) {
        temp_a0->_refCount = temp_a0->_refCount - 1;
        if (((unsigned long long)(long long)(int)temp_a0->_refCount & 0x7fffffULL) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    arg1->_refList = (igTDataList<int> *)FUN_002c9130(temp_s0);
    temp_a0_2 = arg1->_refList;
    if (temp_s1 >= 0) {
        if (temp_s1 <= temp_a0_2->_capacity) {
            temp_a0_2->_count = temp_s1;
        } else {
            List_Resize(temp_a0_2, temp_s1, 4);
        }
    }
    for (i = 0; i < temp_s1; i++) {
        ((igDirEntryView *)FUN_002d7e90((int *)arg1, i))->readFinished(arg1);
    }
    return g_resultSuccess;
}

igResult igIGBFile_ReadObjectSectionOld(igIGBFileView *file) {
    int pool;
    int i;
    file->_chunkPlace = file->_chunkSize;
    file->_bufferPlace = 0;
    file->_bufferSize = file->_entryBufferSize;
    if (file->_sharingState != 0) {
        igTDataList<int> *old = file->_refList;
        pool = (int)file->_temporaryMemoryPool;
        igRelease((igObject *)old);
        file->_refList = (igTDataList<int> *)FUN_002c9130(pool);
        int count = file->_entryCount;
        igTDataList<int> *indices = file->_refList;
        if (count >= 0) {
            if (count <= indices->_capacity) {
                indices->_count = count;
            } else {
                List_Resize(indices, count, 4);
            }
        }
        igObject *previous = file->_entryPool;
        pool = (int)file->_temporaryMemoryPool;
        igRelease(previous);
        file->_entryPool = (igObject *)FUN_002bd680(pool);
    }
    if (FUN_002e7030(file) == g_resultFailure) {
        return g_resultFailure;
    }
    ObjectList_ResizeRetained((igTDataList<igObject *> *)file, file->_entryCount);
    for (i = 0; i < file->_entryCount; i++) {
        SectionObjectRef object = igIGBFile_ReadObject((igIGBFile *)file);
        if (object.p == 0) {
            return g_resultFailure;
        }
        object->_index = i;
        file->setEntry(i, object);
        if (file->_useMemoryPoolAssignmentsState != 0 && file->_memoryPoolHandles != 0 && g_useOwnerAllocator == 0) {
            int index = object->memoryPoolIndex();
            if (index > 0) {
                object->setMemoryPool(((int *)file->_memoryPoolHandles->_data)[index]);
            }
        } else {
            object->setMemoryPool(-1);
        }
        object->readFinished(file);
        if (file->_sharingState != 0) {
            int reference = object->_ref;
            igTDataList<int> *indices = file->_refList;
            if (indices->_count != 0 && i >= 0 && i < indices->_count) {
                ((int *)indices->_data)[i] = reference;
            }
            object->setReferenceIndex(object->_ref);
            object->vfunc_23(0);
            object->_index = i;
            file->setEntryRaw(i, object->resolve(file));
        }
    }
    if (file->_hasCriticalFailure != 0) {
        return g_resultFailure;
    }
    return g_resultSuccess;
}

int Gap__Core__igIGBFile__vfunc_27(igIGBFileView *arg0) {
    if (arg0->_file->_openMode == 4) {
        return (int)arg0->_chunk + arg0->_chunkPlace;
    }
    return arg0->_objectBufferPlace;
}

void Gap__Core__igIGBFile__vfunc_26(igIGBFileView *self, int at) {
    if (self->_file->_openMode == 4) {
        int prev = (int)self->_chunk + self->_chunkPlace;
        self->_chunkPlace = at - (int)self->_chunk;
        self->_bufferPlace = self->_bufferPlace + (at - prev);
        if (self->_bufferPlace != self->_bufferSize) {
            if (self->_chunkPlace > self->_chunkSize - 9) {
                FUN_002e7030(self);
                return;
            }
            if (self->_chunkPlace + (self->_version1CruftMultiply * 4 + FUN_002e3a10(self, at)) > self->_chunkSize) {
                FUN_002e7030(self);
            }
        }
    } else {
        self->_objectBufferPlace = at;
    }
}

igResult FUN_002e7ed0(igIGBFileView *arg1) {
    arg1->_temporaryMemoryPool->Free(arg1->_basePath);
    arg1->_basePath = 0;
    return g_resultSuccess;
}

igResult FUN_002e7f20(igIGBFileView *self) {
    IgbRegistryTable *table;
    int count;
    int *sizes;
    char *name;
    int i;
    if (igIGBFile_GetSectionBuffer(self, self->_metaFieldBufferSize) == g_resultFailure) {
        return g_resultFailure;
    }
    self->_mfBuf = self->_chunk;
    self->_file->Read(self->_mfBuf, self->_metaFieldBufferSize, 1);
    table = (IgbRegistryTable *)((void *)FUN_002fc250());
    count = table->count;
    sizes = (int *)self->_mfBuf;
    name = (char *)sizes + self->_metaFieldCount * 12;
    if (self->_endianSwap != 0) { self->imf->SwapBytes(sizes, self->_metaFieldCount * 3); }
    {
        igObjectList *v = ((igObjectList *)FUN_002c8af0((int)self->_temporaryMemoryPool));
        igObjectList *old;
        if (v != 0) { v->_refCount = v->_refCount + 1; }
        old = self->_metaFieldListInFile;
        IG_OBJECT_RELEASE(old);
        self->_metaFieldListInFile = v;
    }
    {
        igObjectList *l = self->_metaFieldListInFile;
        int want = self->_metaFieldCount;
        if (want >= l->_count) { List_Reserve((igDataList *)l, want, 4); }
    }
    for (i = 0; i < self->_metaFieldCount; i++) {
        bool found = false;
        igObjectDispatchView *t = 0;
        int j;
        for (j = 0; j < count; j++) {
            t = table->data[j];
            if (strcmp(t->getMeta()->_name, name) == 0) { found = true; break; }
        }
        if (!found) { t = 0; } else { t->getMeta(); }
        ObjectList_AppendRetained(self->_metaFieldListInFile, (igObject *)t);
        name += sizes[i * 3];
    }
    self->_mfBuf = 0;
    return g_resultSuccess;
}

static inline void releasePool(igObject *object) {
    if (object) {
        --object->_refCount;
        if (((unsigned long long)(long long)(int)object->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy(object);
    }
}

void Gap__Core__igIGBFile__vfunc_13(igIGBFileView *arg0) {
    igObject *s0;
    s0 = ((igObject *)Memory_GetDefaultAllocator());
    if (s0) s0->_refCount++;
    releasePool((igObject *)arg0->_temporaryMemoryPool);
    arg0->_temporaryMemoryPool = (igMemoryPoolView *)s0;
    s0 = ((igObject *)Memory_GetDefaultAllocator());
    if (s0) s0->_refCount++;
    releasePool((igObject *)arg0->_dataMemoryPool);
    arg0->_dataMemoryPool = (igMemoryPoolView *)s0;
    s0 = ((igObject *)Memory_GetDefaultAllocator());
    if (s0) s0->_refCount++;
    releasePool((igObject *)arg0->_objectMemoryPool);
    arg0->_objectMemoryPool = (igMemoryPoolView *)s0;
}

static inline void assignTypes(igIGBFileView *self, const TypeListHolder &h) {
    igTDataList<int> *v = h.p;
    igTDataList<int> *old;
    if (v != 0) { v->_refCount = v->_refCount + 1; }
    old = (igTDataList<int> *)self->_alignmentListInFile;
    if (old != 0) { old->_refCount = old->_refCount - 1; if (((unsigned long long)((long long)(int)old->_refCount << 0x29) >> 0x29) == 0) igObject_Destroy(old); }
    self->_alignmentListInFile = (igIntList *)v;
}

static inline void addType(igTDataList<int> *l, int v) {
    int idx;
    idx = l->_count;
    if (l->_capacity > idx) { l->_count = l->getCount() + 1; } else { List_Resize(l, idx + 1, 4); }
    l->_data[idx] = v;
}

igResult FUN_002e82a0(igIGBFileView *self) {
    IgbSectionHeader hdr;
    int *sizes;
    char *name;
    int value;
    int nameCount;
    int i;
    if (self->_file->Read(&hdr, 12, 1) != 1) { return g_resultFailure; }
    if (self->_endianSwap != 0) { self->imf->SwapBytes(&hdr, 3); }
    self->_alignmentBufferSize = hdr.size - 12;
    self->_alignmentCount = hdr.count;
    if (self->_alignmentCount <= 0) { return g_resultSuccess; }
    self->_alignmentBuffer = (int *)self->_chunk;
    if (self->_file->Read(self->_alignmentBuffer, self->_alignmentBufferSize, 1) != 1) { return g_resultFailure; }
    sizes = self->_alignmentBuffer;
    if (self->_endianSwap != 0) { self->imf->SwapBytes(sizes, self->_alignmentCount); }
    name = (char *)sizes + self->_alignmentCount * 4;
    {
    RefObjectHolder names(g_globalContext->names);
    RefObjectHolder values(g_globalContext->values);
    nameCount = 0;
    if (names.p != 0) { nameCount = ((ReflectedNameList *)names.p)->count; }
    {
        TypeListHolder h((igTDataList<int> *)igIntList_Create((int)self->_temporaryMemoryPool));
        assignTypes(self, h);
    }
    {
        igTDataList<int> *l = (igTDataList<int> *)self->_alignmentListInFile;
        int want = self->_alignmentCount;
        if (want >= l->_count) { List_Reserve((igDataList *)l, want, 4); }
    }
    for (i = 0; i < self->_alignmentCount; i++) {
        bool found = false;
        value = 16;
        int j;
        for (j = 0; j < nameCount; j++) {
            char *n = ((ReflectedNameList *)names.p)->data[j]->name;
            n = (n == 0) ? (*(char * *)g_stringObjEmptyText) : n;
            if (strcmp(n, name) == 0) { found = true; break; }
        }
        if (found) { value = ((igTDataList<int> *)values.p)->_data[j]; }
        addType((igTDataList<int> *)self->_alignmentListInFile, value);
        name += sizes[i];
    }
    self->_alignmentBuffer = 0;
    return g_resultSuccess;
    }
}

igResult FUN_002e8670(igIGBFileView *arg1) {
    int n;
    int i;

    arg1->_objectBufferPlace = (int)arg1->_objBuf;
    arg1->_chunkPlace = arg1->_chunkSize;
    arg1->_bufferPlace = 0;
    arg1->_bufferSize = arg1->_objectBufferSize;
    if (FUN_002e7030(arg1) == g_resultFailure) {
        return g_resultFailure;
    }
    n = arg1->_count;
    for (i = 0; i < n; i++) {
        if (igObject_IsKindOf(arg1->_data[i], (igMetaObject *)g_igObjectDirEntry_metaObject[0]) != 0) {
            ((igDirEntryView *)FUN_002d7e90((int *)arg1, i))->vfunc_32(arg1);
        }
    }
    if (arg1->_magicVersion < 4) {
        for (i = 0; i < n; i++) {
            if (igObject_IsKindOf(arg1->_data[i], (igMetaObject *)g_igObjectDirEntry_metaObject[0]) != 0) {
                ((igDirEntryView *)FUN_002d7e90((int *)arg1, i))->vfunc_33(arg1);
            }
        }
    } else {
        for (i = 0; i < n; i++) {
            if (igObject_IsKindOf(arg1->_data[i], (igMetaObject *)g_igObjectDirEntry_metaObject[0]) != 0) {
                DirEntryHolder e((igDirEntryView *)FUN_002d7e90((int *)arg1, i));
                e.p->vfunc_34(arg1);
            }
        }
    }
    return g_resultSuccess;
}

igResult FUN_002e8880(igIGBFileView *arg1) {
    int i;
    for (i = 0; i < arg1->_count; i++) {
        if (((igObject_IsKindOf(arg1->_data[i], (igMetaObject *)g_igObjectDirEntry_metaObject[0]) != 0) ^ 1) != 0) {
            ((igDirEntryView *)FUN_002d7e90((int *)arg1, i))->vfunc_32(arg1);
        }
    }
    if (arg1->_magicVersion < 4) {
        for (i = 0; i < arg1->_count; i++) {
            if (((igObject_IsKindOf(arg1->_data[i], (igMetaObject *)g_igObjectDirEntry_metaObject[0]) != 0) ^ 1) != 0) {
                ((igDirEntryView *)FUN_002d7e90((int *)arg1, i))->vfunc_33(arg1);
            }
        }
    } else {
        for (i = 0; i < arg1->_count; i++) {
            if (((igObject_IsKindOf(arg1->_data[i], (igMetaObject *)g_igObjectDirEntry_metaObject[0]) != 0) ^ 1) != 0) {
                ((igDirEntryView *)FUN_002d7e90((int *)arg1, i))->vfunc_34(arg1);
            }
        }
    }
    return g_resultSuccess;
}

void FUN_002e8a10(igIGBFileView *arg0) {
    if (arg0->_autoOpened > 0) {
        FUN_002e3cb0(arg0);
    }
}

void FUN_002e8a40(igIGBFileView *a) {
    RELEASE_REF(a->_metaFieldListInFile);
    RELEASE_REF(a->_metaFieldListInFile);
    a->_metaFieldListInFile = 0;
    RELEASE_REF(a->_metaObjectListInFile);
    a->_metaObjectListInFile = 0;
    RELEASE_REF(a->_metaFieldPerObjectIndices);
    a->_metaFieldPerObjectIndices = 0;
    a->_metaObjectBuffer = 0;
    a->_dirBuf = 0;
    a->_mfBuf = 0;
    a->_objBuf = 0;
    RELEASE_REF(a->_entryPool);
    a->_entryPool = 0;
    a->_indexBuffer = 0;
    RELEASE_REF(a->_uniqueEntryList);
    a->_uniqueEntryList = 0;
    a->_temporaryMemoryPool->Free(a->_chunk);
    a->_chunk = 0;
    a->_memoryPoolNameBufferSize = 0;
    int *t = a->_memoryPoolNameBuffer;
    if (t != 0) {
        a->_temporaryMemoryPool->Free(t);
        a->_memoryPoolNameBuffer = 0;
    }
    RELEASE_REF(a->_memoryPoolHandles);
    a->_memoryPoolHandles = 0;
}

void Gap__Core__igIGBFile__vfunc_04(igIGBFileView *arg0) {
    if (arg0->_refList != 0) {
        for (int i = 0, count = arg0->_refList->_count; i < count; i++) {
            arg0->_data[i]->vfunc_28(((int *)arg0->_refList->_data)[i]);
        }
        RELEASE_REF(arg0->_refList);
        arg0->_refList = 0;
    }
    RELEASE_REF(arg0->_refList);
    arg0->_refList = 0;
    Gap__Core__igObject__destructFields((int)arg0);
}

igResult FUN_002e8d40(igIGBFileView *arg1) {
    igObject *temp_s0;
    igObject *t;

    if (arg1->_hasInfo != 0) {
        if (arg1->_file->Read((char *)arg1 + DAT_00586280[0]->f8, 4, 1) != 1) {
            return g_resultFailure;
        }
        if (arg1->_endianSwap != 0) {
            arg1->imf->SwapBytes((char *)arg1 + DAT_00586280[0]->f8, 1);
        }
        temp_s0 = (igObject *)((igDirEntryView *)FUN_002d7e90((int *)arg1, arg1->_infoListPlace))->_ref;
        if (temp_s0 != 0) {
            temp_s0->_refCount = temp_s0->_refCount + 1;
        }
        t = (igObject *)arg1->_infoList;
        IG_OBJECT_RELEASE(t);
        arg1->_infoList = (igTDataList<igInfoView *> *)temp_s0;
    }
    return g_resultSuccess;
}

static inline void *stringPool() {
    if ((*(void * *)g_stringPool) == 0) {
        void *p = StringPool_Allocate(16);
        if (p != 0) { p = ((void *)StringPool_Construct((StringPool *)p)); }
        (*(void * *)g_stringPool) = p;
    }
    return (*(void * *)g_stringPool);
}

static inline void setPooled(char **dst, char *src) {
    char *v = ((char *)StringPool_Intern((StringPool *)(stringPool()), src));
    char *old = *dst;
    if (old != 0) {
        PooledStringHead *h = (PooledStringHead *)(old - 8);
        int n = h->refs - 1;
        h->refs = n;
        if (n == 0) { StringChunk_ReleaseHeader((StringChunkOwnerView *)h->chunk, (int)h); }
    }
    *dst = v;
}

igResult FUN_002e8e50(igIGBFileView *self) {
    if (self->_hasExternal != 0) {
        IgbSectionHeader hdr;
        int count;
        int *sizes;
        char *name;
        int i;
        igResource *dir;
        if (self->_file->Read(&hdr, 12, 1) != 1) { return g_resultFailure; }
        if (self->_endianSwap != 0) { self->imf->SwapBytes(&hdr, 3); }
        self->_externalDirectoryBufferSize = hdr.size - 12;
        count = hdr.count;
        self->_externalDirectoryBuffer = (int *)self->_temporaryMemoryPool->AllocateAligned(self->_externalDirectoryBufferSize, 16);
        if (self->_file->Read(self->_externalDirectoryBuffer, self->_externalDirectoryBufferSize, 1) != 1) { return g_resultFailure; }
        sizes = self->_externalDirectoryBuffer;
        if (self->_endianSwap != 0) { self->imf->SwapBytes(sizes, count); }
        name = (char *)sizes + count * 4;
        if (self->_managingResource == 0) { self->_managingResource = ((igResource *)FUN_00309a50()); }
        if (self->_managingResource != 0) {
            setPooled(&self->_previousResourceFilePath, (char *)self->_managingResource->_relativeFilePath);
            { char *n; n = self->_basePath; dir = self->_managingResource; setPooled((char **)&dir->_relativeFilePath, n); }
        }
        for (i = 0; i < count; i++) {
            ObjectList_AppendRetained((igObjectList *)self->_externalDirectoryList, (igObject *)(((int)FUN_00308fb0(self->_managingResource, (int)name))));
            name += sizes[i];
        }
        self->_temporaryMemoryPool->Free(self->_externalDirectoryBuffer);
        self->_externalDirectoryBuffer = 0;
        dir = self->_managingResource;
        if (dir != 0) {
            setPooled((char **)&dir->_relativeFilePath, self->_previousResourceFilePath);
            setPooled(&self->_previousResourceFilePath, 0);
        }
    }
    return g_resultSuccess;
}

static inline void addName(igTDataList<int> *l, const int &v) {
    int idx = l->_count;
    if (l->_capacity > idx) { l->_count = l->getCount() + 1; } else { List_Resize(l, idx + 1, 4); }
    l->_data[idx] = v;
}

igResult FUN_002e91e0(igIGBFileView *self) {
    NameHeader hdr;
    char *buf;
    char *name;
    int i;
    if (self->_file->Read(&hdr, 8, 1) != 1) { return g_resultFailure; }
    if (self->_endianSwap != 0) { self->imf->SwapBytes(&hdr, 2); }
    buf = (char *)self->_temporaryMemoryPool->Allocate(hdr.size);
    if (buf == 0) { return g_resultFailure; }
    if (self->_file->Read(buf, hdr.size - 8, 1) != 1) { self->_temporaryMemoryPool->Free(buf); return g_resultFailure; }
    if (self->_memoryPoolHandles != 0) {
        self->_memoryPoolHandles->_count = 0;
    } else {
        igIntList *old = self->_memoryPoolHandles;
        igMemoryPoolView *pool = self->_temporaryMemoryPool;
        IG_OBJECT_RELEASE(old);
        self->_memoryPoolHandles = (igIntList *)igIntList_Create((int)pool);
    }
    name = buf;
    i = 0;
    while (hdr.count-- > 0) {
        addName((igTDataList<int> *)self->_memoryPoolHandles, FUN_002f89e0((int)name));
        { int len = strlen(name) + 1; i++; name += len; }
    }
    for (; i < 46; i++) {
        int idx; igTDataList<int> *l; l = (igTDataList<int> *)self->_memoryPoolHandles; idx = l->_count;
        if (l->_capacity > idx) { l->_count = l->getCount() + 1; } else { List_Resize(l, idx + 1, 4); }
        l->_data[idx] = DAT_004c2140[0];
    }
    self->_temporaryMemoryPool->Free(buf);
    return g_resultSuccess;
}

int FUN_002e9470(igIGBFileView *arg0) {
    FUN_002e8a40(arg0);
    arg0->_loadPendingState = 0;
    arg0->_validState = 0;
    FUN_002e8a10(arg0);
    return -1;
}

igResult FUN_002e94b0(igIGBFileView *arg1) {
    int i;
    int n;
    int flag;
    igDirEntryView *e;
    i = 0;
    n = arg1->_count;
    flag = !arg1->_concreteState;
    while (i < n) {
        e = (igDirEntryView *)FUN_002d7e90((int *)arg1, i);
        e->vfunc_36(flag);
        i += 1;
    }
    if (flag != 0) {
        arg1->_concreteState = 1;
    }
    return g_resultSuccess;
}

igResult FUN_002e9560(igIGBFileView *arg1) {
    int i;
    void **temp_v0;
    for (i = 0; i < arg1->_count; i++) {
        temp_v0 = (void **)(FUN_002d7e90((int *)arg1, i));
        ((igDirEntryView *)(temp_v0))->vfunc_37(arg1);
    }
    return g_resultSuccess;
}

int igIGBFile_ReadFile(igIGBFileView *self, const char *path) {
  int startTime;
  sprintf(DAT_00586e20, text_readFile_s, path);
  startTime = DAT_005871d8[0]->now();
  self->_validState = 0;
  self->_loadPendingState = 1;
  self->_concreteState = 0;
  if (FUN_002e5f70(self, path).failed()) return FUN_002e9470(self);
  if (igIGBFile_ReadHeader(self).failed()) return FUN_002e9470(self);
  if (self->_magicVersion < 5 && self->_hasExternal) {
    if (!GPR_00554c08) {
      int answer = igReportError(DAT_004f9af0, self->_file->_fileName, self->_file->_fileName);
      if (answer != 1 && answer == 2) GPR_00554c08 = 1;
    }
    return FUN_002e9470(self);
  }
  if (self->_magicVersion >= 3) {
    if (FUN_002e7f20(self).failed()) return FUN_002e9470(self);
    if (FUN_002e82a0(self).failed()) return FUN_002e9470(self);
  }
  if (FUN_002e6330(self).failed()) return FUN_002e9470(self);
  if (FUN_002e63e0(self).failed()) return FUN_002e9470(self);
  if (FUN_002e6f50(self).failed()) return FUN_002e9470(self);
  if (self->_magicVersion >= 5) {
    if (FUN_002e8e50(self).failed()) return FUN_002e9470(self);
  }
  if (self->_hasMemoryPoolNames) {
    if (FUN_002e91e0(self).failed()) return FUN_002e9470(self);
  }
  if (self->_sharedEntries) {
    if (igIGBFile_ReadObjectSection(self).failed()) return FUN_002e9470(self);
    if (FUN_002e7640(self).failed()) return FUN_002e9470(self);
    if (FUN_002e78b0(self).failed()) return FUN_002e9470(self);
  } else {
    if (igIGBFile_ReadObjectSectionOld(self).failed()) return FUN_002e9470(self);
  }
  if (self->_magicVersion >= 5) {
    if (FUN_002e8d40(self).failed()) return FUN_002e9470(self);
  }
  if (FUN_002e8670(self).failed()) return FUN_002e9470(self);
  if (self->vfunc_33().failed()) return FUN_002e9470(self);
  if (self->_magicVersion < 3) {
    if (FUN_002e7f20(self).failed()) return FUN_002e9470(self);
  }
  if (self->_magicVersion < 5) {
    if (FUN_002e8d40(self).failed()) return FUN_002e9470(self);
  }
  if (self->_magicVersion < 5) {
    if (FUN_002e8e50(self).failed()) return FUN_002e9470(self);
  }
  if (FUN_002e8880(self).failed()) return FUN_002e9470(self);
  if (FUN_002e7ed0(self).failed()) return FUN_002e9470(self);
  FUN_002e94b0(self);
  if (self->_autoReadFilePostProcessState == 1) {
    if (self->vfunc_30().failed()) return FUN_002e9470(self);
  }
  FUN_002e8a10(self);
  FUN_002e8a40(self);
  self->_validState = 1;
  self->_loadPendingState = 0;
  if (!GPR_00554c0c) {
    int answer = FUN_00308240(text_Total_Time_to_load_s_f_seconds, path, dpsub(DAT_005871d8[0]->now(), startTime));
    if (answer != 1 && answer == 2) GPR_00554c0c = 1;
  }
  return self->_count;
}

void Gap__Core__igIGBFile__vfunc_32(int *arg0, void *arg1) {
    if (*(unsigned char *)((char *)(arg1) + 56) == 0) {
        FUN_002d8f20((igDirectoryView *)arg1);
    }
    *arg0 = g_resultSuccess.v;
}

void Gap__Core__igIGBFile__vfunc_30(int *arg0, igIGBFileView *arg1) {
    if (arg1->_readFilePostProcessedState == 0) {
        igResult sp3C = FUN_002e9560(arg1);
        if (arg1->_managingResource != 0) {
            FUN_0030a260(arg1->_managingResource, (int)arg1->_name);
        }
        arg1->_readFilePostProcessedState = 1;
        *arg0 = sp3C.v;
    } else {
        *arg0 = g_resultSuccess.v;
    }
}

static inline igIGBFileView *castInfo(igIGBFileView *o) { if (o != 0 && igObject_IsKindOf((void *)o, (igMetaObject *)(((int *)g_igIGBFile_metaObject)[0])) != 0) { return o; } return 0; }

/* Checks each external file, then this file's own post-read step. */
igResult Gap__Core__igIGBFile__vfunc_31(igIGBFileView *self) {
    igResult result = g_resultSuccess;
    int i;
    for (i = 0; i < self->_externalDirectoryList->_count; i++) {
        ExternalFileHolder o(castInfo((igIGBFileView *)self->_externalDirectoryList->_data[i]));
        if (o.p != 0) {
            if (o.p->vfunc_31() == g_resultFailure) {
                result = g_resultFailure;
            }
        }
    }
    if (self->vfunc_30() == g_resultFailure) {
        result = g_resultFailure;
    }
    return result;
}

int Gap__Core__igIGBFile__vfunc_34(igIGBFileView *o) {
    int i;
    o->_chunkSize = o->_forceChunkSize;
    if (o->_chunkSize < 0) {
        o->_chunkSize = o->_file->_optimalWriteChunkSize;
    }
    if (o->_memoryRefBufferSize < o->_chunkSize) {
        o->_chunkSize = o->_memoryRefBufferSize;
    }
    o->_chunk = (char *)o->_temporaryMemoryPool->AllocateAligned(o->_chunkSize, o->_file->_pageSize);
    o->_memoryBufferPlace = 0;
    o->_memoryBytesCopied = 0;
    o->_bytesRemainingInChunk = o->_chunkSize;
    for (i = 0; i < o->_count; i++) {
        ((igDirEntryView *)FUN_002d7e90((int *)o, i))->vfunc_41(o);
    }
    o->_temporaryMemoryPool->Free(o->_chunk);
    o->_chunk = 0;
    return 1;
}

igResult igIGBFile_GetSectionBuffer(igIGBFileView *arg1, int arg2) {
    char *a1;
    a1 = arg1->_chunk;
    if (a1 != 0 && arg1->_chunkSize >= arg2) {
        return g_resultSuccess;
    } else {
        if (a1 != 0) {
            arg1->_temporaryMemoryPool->Free(a1);
        }
        arg1->_chunkSize = arg1->_forceChunkSize;
        if (arg1->_chunkSize < 0) {
            arg1->_chunkSize = arg1->_file->_optimalReadChunkSize;
        }
        if (arg1->_chunkSize < arg2) {
            arg1->_chunkSize = arg2;
        }
        arg1->_chunkSize = (arg1->_chunkSize + 3) & ~3;
        arg1->_chunk = (char *)arg1->_temporaryMemoryPool->AllocateAligned(arg1->_chunkSize, arg1->_file->_pageSize);
        if (arg1->_chunk == 0) {
            return g_resultFailure;
        } else {
            return g_resultSuccess;
        }
    }
}

void Gap__Core__igIGBFile__vfunc_33(int *arg0, igIGBFileView *arg1) {
    int n;
    int i;
    arg1->_memoryBufferPlace = 0;
    arg1->_memoryBytesCopied = 0;
    arg1->_bytesRemainingInChunk = 0;
    n = arg1->_count;
    for (i = 0; i < n; i++) {
        ((igDirEntryView *)FUN_002d7e90((int *)arg1, i))->vfunc_35(arg1);
    }
    *arg0 = g_resultSuccess.v;
}

