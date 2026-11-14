inline bool igResult::failed() const { return v == g_resultFailure.v; }

int igIGBFile_GetObjectSize(void *self, int record) {
    int size;
    igMetaFieldView *intField;

    size = ((FieldRecordHead *)record)->size;
    if (((igIGBFileView *)self)->_endianSwap != 0) {
        intField = (igMetaFieldView *)igIntMetaField_GetDefaultDescriptor();
        intField->SwapBytes(&size, 1);
    }
    return size;
}

igResult igIGBFile_OpenFile(igIGBFileView *self, const char *fileName, int mode) {
    if (fileName == 0 && self->_file == 0) {
        return g_resultFailure;
    }
    if (fileName == 0 && self->_file != 0) {
        return self->_file->OpenWithMode(mode);
    }
    if (self->_file == 0 && fileName != 0) {
        assignReference(self->_file, igSmartPointer<igFileView>((igFileView *)igFile_Create((int)self->_temporaryMemoryPool)));
        if (self->_file == 0) {
            return g_resultFailure;
        }
        igFile_SetFileName((int *)self->_file, fileName);
        return self->_file->OpenWithMode(mode);
    }
    self->_file->CloseHandle();
    assignReference(self->_file, igSmartPointer<igFileView>((igFileView *)igFile_Create((int)self->_temporaryMemoryPool)));
    igFile_SetFileName((int *)self->_file, fileName);
    return self->_file->OpenWithMode(mode);
}

void igIGBFile_CloseFile(igIGBFileView *self) {
    igFileView *r;
    if (self->_file != 0) {
        self->_file->CloseHandle();
        r = self->_file;
        if (r != 0) {
            r->_refCount = r->_refCount - 1;
            if ((r->_refCount & 0x7FFFFF) == 0) igObject_Destroy(r);
        }
        self->_file = 0;
    }
}

void igIGBFile_SetDefaultName(int *self) {
    int fileName;
    int *header;
    int pool;
    int c;
    void *baseName;
    int i;
    int count;
    void *oldName;
    void *name;

    name = (void *)(self[5]);
    if ((!name) || (strcmp(name, &emptyString_4[0]) == 0)) {
        fileName = ((int *)self[26])[3];
        i = strlen(fileName) - 1;
        while (i > 0 && 0x2F != (c = *(char *)((fileName + i) - 1)) && c != 0x5C) {
            i = i - 1;
        }
        if (0 == (*(void * *)g_stringPool)) {
            pool = (int)StringPool_Allocate(0x10);
            if (pool) {
                pool = (int)StringPool_Construct((StringPool *)((void *)pool));
            }
            (*(void * *)g_stringPool) = (void *)pool;
        }
        baseName = (void *)(((char *)StringPool_Intern((StringPool *)((*(void * *)g_stringPool)), (const char *)(fileName + i))));
        oldName = (void *)(self[5]);
        if (oldName) {
            header = (int *)((char *)oldName - 8);
            count = *(int *)((char *)(oldName) - 4) - 1;
            *(int *)((char *)(oldName) - 4) = count;
            if (!count) {
                StringChunk_ReleaseHeader((StringChunk *)(*header), (int)header);
            }
        }
        self[5] = (int)(baseName);
    }
}

igResult igIGBFile_OpenForWrite(igIGBFileView *f, const char *fileName) {
    if (f->_file == 0 && fileName == 0) {
        return g_resultFailure;
    }
    if (f->_file == 0) {
        if (igIGBFile_OpenFile(f, fileName, 5) == g_resultFailure) {
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
    igIGBFile_SetDefaultName((int *)f);
    igAdxFile_SetOpenMode((int)f->_file, 5);
    return g_resultSuccess;
}

igResult igIGBFile_BuildMetaObjectList(igIGBFileView *self) {
    igMetaObject *meta;
    unsigned int n;
    unsigned int i;
    assignReference(self->_metaObjectListInFile, igSmartPointer<igObjectList>((igObjectList *)igMetaObjectList_Create((int)self->_temporaryMemoryPool)));
    igMetaObject_AddToMetaObjectList((igTDataList<igMetaObject *> *)self->_metaObjectListInFile, (igMetaObject *)g_igDirEntry_metaObject[0]);
    meta = g_igDirEntry_metaObject[0];
    n = ((unsigned int)igMetaObject_CountTree((igMetaObject *)meta));
    for (i = 0; i < n; i++) {
        ObjectList_AppendUniqueRetained((igTDataList<igObject *> *)self->_metaObjectListInFile, (igObject *)(((int)igMetaObject_GetTreeNode((igMetaObject *)meta, (int)i))));
    }
    return g_resultSuccess;
}

igResult igIGBFile_PrepareEntriesForWrite(igIGBFileView *self) {
    int i;

    for (i = 0; i < self->_count; i++) {
        self->_data[i]->_index = i;
        self->_data[i]->PrepareWrite(self);
    }
    return g_resultSuccess;
}

igResult igIGBFile_BuildMemoryPoolNameBuffer(igIGBFileView *o) {
    int i; int s; char *p; int j; int n; int a;
    o->_memoryPoolNameBufferSize = 8;
    i = 0;
    do {
        a = strlen(Memory_GetPoolNameByIndex(i)) + 1;
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
        s = Memory_GetPoolNameByIndex(j);
        n = strlen(s) + 1;
        memcpy(p, s, n);
        j++;
        p += n;
    } while (j < 46);
    if (o->_endianSwap) o->imf->SwapBytes(o->_memoryPoolNameBuffer, 2);
    return g_resultSuccess;
}

igResult igIGBFile_ComputeBufferSizes(igIGBFile *self) {
    int i;
    void *entry;

    self->_objectCount = 0;
    self->_memoryRefCount = 0;
    self->_objectBufferSize = 0;
    self->_memoryRefBufferSize = 0;
    for (i = 0; i < self->_count; i++) {
        entry = (void *)(*(int *)(self->_data + (i * 4)));
        ((igDirEntryView *)entry)->ComputeWriteSize((igIGBFileView *)self);
    }
    return g_resultSuccess;
}

static inline void bump(const igSmartPointer<igTDataList<int> > &r, int off) { int *c = (int *)((char *)r.p->_data + off); *c = *c + 1; }

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

igResult igIGBFile_BuildMetaObjectBuffer(igIGBFileView *self) {
    int base;
    int i;
    self->_metaObjectCount = self->_metaObjectListInFile->_count;
    self->_metaObjectBufferSize = self->_metaObjectCount * 24;
    {
    igSmartPointer<igTDataList<int> > inherited((igTDataList<int> *)igIntList_Create((int)self->_temporaryMemoryPool));
    fillWords(inherited.p, self->_metaObjectCount, 0);
    {
        int n = inherited.p->_count;
        int *d = inherited.p->_data;
        int k;
        for (k = 0; k < n; k++) { d[k] = g_igIGBFile_inheritedFieldCountFill[0]; }
    }
    {
    igSmartPointer<igTDataList<int> > persistent((igTDataList<int> *)igIntList_Create((int)self->_temporaryMemoryPool));
    fillWords(persistent.p, self->_metaObjectCount, 0);
    {
        int n = persistent.p->_count;
        int *d = persistent.p->_data;
        int k;
        for (k = 0; k < n; k++) { d[k] = g_igIGBFile_persistentFieldCountFill[0]; }
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

igResult igIGBFile_BuildMetaFieldBuffer(igIGBFileView *self) {
    int i;
    int j;
    int s5;
    int *s4;
    char *s2;
    igObjectDispatchView *p;
    self->_metaFieldCount = igMetaField_GetMetaFieldList()->_count;
    self->_metaFieldBufferSize = self->_metaFieldCount * 12;
    for (i = 0; i < self->_metaFieldCount; i++) {
        self->_metaFieldBufferSize = self->_metaFieldBufferSize + (strlen(registeredMetaField(igMetaField_GetMetaFieldList(), i)->GetMeta()->_name) + 1);
    }
    self->_mfBuf = (char *)self->_temporaryMemoryPool->AllocateAligned(self->_metaFieldBufferSize, 16);
    s5 = 0;
    s4 = (int *)self->_mfBuf;
    for (i = 0; i < self->_metaFieldCount; i++) {
        p = registeredMetaField(igMetaField_GetMetaFieldList(), i);
        s4[s5] = strlen(p->GetMeta()->_name) + 1;
        s5++;
        s4[s5] = p->GetMeta()->_majorVersion;
        s5++;
        s4[s5] = p->GetMeta()->_minorVersion;
        s5++;
    }
    s2 = self->_mfBuf + self->_metaFieldCount * 12;
    for (j = 0; j < self->_metaFieldCount; j++) {
        strcpy(s2, registeredMetaField(igMetaField_GetMetaFieldList(), j)->GetMeta()->_name);
        s2 += *(int *)(self->_mfBuf + j * 12);
    }
    if (self->_endianSwap != 0) self->imf->SwapBytes(self->_mfBuf, self->_metaFieldCount * 3);
    return g_resultSuccess;
}

static inline char *nameOf(const igSmartPointer<igTDataList<igStringObj *> > &r, int i) {
    char *n = (char *)r.p->_data[i]->_buffer;
    n = (n == 0) ? (*(char * *)g_stringObjEmptyText) : n;
    return n;
}

igResult igIGBFile_BuildAlignmentBuffer(igIGBFileView *self) {
    igSmartPointer<igTDataList<igStringObj *> > names(g_globalContext->_alignmentStrings, kRetainReference);
    int i;
    int *lengths;
    char *out;
    self->_alignmentCount = (names.p != 0) ? names.p->_count : 0;
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

igResult igIGBFile_BuildExternalDirectoryBuffer(igIGBFileView *self) {
    igTDataList<igDirectoryView *> *l = self->_externalDirectoryList;
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
igResult igIGBFile_BuildDirectoryBuffer(igIGBFile *file) {
    char *cursor;
    int i;
    file->_entryBufferSize = 0;
    file->_entryCount = ((igObjectList *)file->_uniqueEntryList)->_count;
    for (i = 0; i < file->_entryCount; i++) {
        file->_entryBufferSize = file->_entryBufferSize + igObject_GetSerializedSize((igObjectDispatchView *)igDirectory_GetEntryAlias((int *)file->_uniqueEntryList, i));
    }
    file->_dirBuf = (int)((igMemoryPoolView *)file->_temporaryMemoryPool)->AllocateAligned(file->_entryBufferSize, 16);
    cursor = (char *)file->_dirBuf;
    for (i = 0; i < file->_entryCount; i++) {
        cursor += igObject_WritePersistentFields((igObjectDispatchView *)igDirectory_GetEntryAlias((int *)file->_uniqueEntryList, i), (int *)cursor, 0, (igTDataList<igMetaObject *> *)file->_metaObjectListInFile, file->_endianSwap);
    }
    return g_resultSuccess;
}

igResult igIGBFile_BuildIndexBuffer(igIGBFileView *self) {
    int count = self->_count;
    int i;
    self->_indexBufferSize = count * 2 + 8;
    self->_indexBuffer = self->_temporaryMemoryPool->AllocateAligned(self->_indexBufferSize, 16);
    ((int *)self->_indexBuffer)[0] = self->_indexBufferSize;
    ((int *)self->_indexBuffer)[1] = count;
    for (i = 0; i < count; i++) {
        igTDataList<igDirEntryView *> *unique = (igTDataList<igDirEntryView *> *)self->_uniqueEntryList;
        ((short *)((char *)self->_indexBuffer + 8))[i] = unique->sortedFind(&self->_data[i]);
    }
    if (self->_endianSwap != 0) {
        self->imf->SwapBytes(self->_indexBuffer, 2);
        self->smf->SwapBytes((char *)self->_indexBuffer + 8, count);
    }
    return g_resultSuccess;
}

igResult igIGBFile_ShareEntries(igIGBFileView *self) {
    int n;
    int i;
    if (self->_sharedEntries != 0) { return g_resultSuccess; }
    {
        igTDataList<int> *old = self->_refList;
        int pool = (int)self->_temporaryMemoryPool;
        IG_OBJECT_RELEASE(old);
        self->_refList = (igTDataList<int> *)igPointerList_Create(pool);
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
        self->_entryPool = (igObject *)igObjectList_Create(pool);
    }
    {
        igObjectList *old = self->_uniqueEntryList;
        int pool = (int)self->_temporaryMemoryPool;
        IG_OBJECT_RELEASE(old);
        self->_uniqueEntryList = (igObjectList *)igDirectory_Create(pool);
    }
    n = self->_count;
    for (i = 0; i < n; i++) {
        igDirEntryView *o = self->_data[i];
        igDirEntryView *r;
        igDirEntryView *old;
        int c;
        if (o == o->Resolve(self)) {
            insertObjectSorted(self->_uniqueEntryList, o);
        }
        {
            int word;
            igTDataList<int> *w = self->_refList;
            word = o->_ref;
            int k = w->_count;
            if (k != 0 && i >= 0 && k > i) { ((int *)w->_data)[i] = word; }
        }
        o->SetReferenceIndex(o->_ref);
        o->SetRef(0);
        o->_index = i;
        r = o->Resolve(self);
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
igResult igIGBFile_WriteEntryBuffer(igIGBFile *file) {
    char *cursor;
    int i;
    file->_entryBufferSize = 0;
    file->_entryCount = file->_count;
    for (i = 0; i < file->_entryCount; i++) {
        file->_entryBufferSize = file->_entryBufferSize + igObject_GetSerializedSize(((igObjectDispatchView **)file->_data)[i]);
    }
    file->_dirBuf = (int)((igMemoryPoolView *)file->_temporaryMemoryPool)->AllocateAligned(file->_entryBufferSize, 16);
    cursor = (char *)file->_dirBuf;
    for (i = 0; i < file->_entryCount; i++) {
        cursor += igObject_WritePersistentFields(((igObjectDispatchView **)file->_data)[i], (int *)cursor, 0, (igTDataList<igMetaObject *> *)file->_metaObjectListInFile, file->_endianSwap);
    }
    return g_resultSuccess;
}

igResult igIGBFile_AllocateObjectBuffer(igIGBFileView *o) {
    int i;
    int n;
    igMemoryPoolView *p = o->_temporaryMemoryPool; int x = o->_objectBufferSize;
    o->_objBuf = p->AllocateAligned(x, 16);
    o->_objectBufferPlace = (int)o->_objBuf;
    n = o->_count;
    for (i = 0; i < n; i++) {
        ((igDirEntryView *)igDirectory_GetEntry((int *)o, i))->WriteObject(o);
    }
    return g_resultSuccess;
}

/* The 48-byte header: the table sizes and counts, then the magic cookie and the version word with the
 * file's flags in its top bits. */
igResult igIGBFile_WriteHeader(igIGBFileView *o) {
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

igResult igIGBFile_WriteBuffers(igIGBFileView *self) {
    int s4 = self->_file->Write(self->_mfBuf, self->_metaFieldBufferSize, 1);
    int s3 = self->_file->Write(self->_alignmentBuffer, self->_alignmentBufferSize, 1);
    int s2 = self->_file->Write(self->_metaObjectBuffer, self->_metaObjectBufferSize, 1);
    if (self->_externalDirectoryBuffer != 0) {
        self->_file->Write(self->_externalDirectoryBuffer, self->_externalDirectoryBufferSize, 1);
        self->_temporaryMemoryPool->Free(self->_externalDirectoryBuffer);
        self->_externalDirectoryBuffer = 0;
    }
    int s1 = 1;
    if (self->_useMemoryPoolAssignmentsState != 0) {
        s1 = self->_file->Write(self->_memoryPoolNameBuffer, self->_memoryPoolNameBufferSize, s1);
    }
    int s0 = self->_file->Write(self->_dirBuf, self->_entryBufferSize, 1);
    if (self->_endianSwap != 0) {
        self->imf->SwapBytes(self->_indexBuffer, 2);
    }
    int s7 = self->_file->Write(self->_indexBuffer, self->_indexBufferSize, 1);
    if (self->_infoListPlace > -1) {
        if (self->_endianSwap != 0) {
            self->imf->SwapBytes((char *)self + g_igIGBFile_infoListPlaceField[0]->_offset, 1);
        }
        self->_file->Write((char *)self + g_igIGBFile_infoListPlaceField[0]->_offset, 4, 1);
    }
    int s8 = self->_file->Write(self->_objBuf, self->_objectBufferSize, 1);
    int v = self->WriteMemoryRefs();
    if (s7 + (s3 + (s4 + (v + (s8 + (s0 + (s2 + s1)))))) == 0) {
        return g_resultFailure;
    } else {
        return g_resultSuccess;
    }
}

igResult igIGBFile_CloseAfterWrite(igIGBFileView *self) {
    if (self->_autoOpened != 0) {
        igIGBFile_CloseFile(self);
    }
    return igResult(*(int *)0x4FB410);
}

igResult igIGBFile_FreeReadBuffers(igIGBFileView *o) {
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

igResult igIGBFile_AddInfoListEntry(void *self) {
    void *infoList;

    infoList = (void *)(((igIGBFileView *)self)->_infoList);
    if (((igTDataList<igInfoView *> *)infoList)->_count > 0) {
        ((igIGBFileView *)self)->_infoListPlace = igDirectory_AddObjectRecursive((int)self, (int)infoList, 0, 0);
        ((igIGBFileView *)self)->_hasInfo = 1;
    }
    return g_resultSuccess;
}

int igIGBFile_WriteFile(igIGBFileView *self, const char *fileName) {
    int *pp; igObject *t; igObject *t2; igObject *a; igObject *b;
    igRegistry_GetValueBool((int)((ObjectSystemView **)g_objectSystem)[0]->configRegistry, 2, (const char *)text_forceWriteMemoryPoolInfoFromMeta, (char *)&self->_forceWriteMemoryPoolInfoFromMetaState, 0, 0);
    igResult openResult = igIGBFile_OpenForWrite(self, fileName);
    pp = (int *)((int)&openResult + 0);
    if (*pp == g_resultFailure.v) return 0;
    igResult infoResult = igIGBFile_AddInfoListEntry(self);
    pp = (int *)((int)&infoResult + 0);
    if (*pp == g_resultFailure.v) return 0;
    igObjectList_SortByField((igTDataList<igObject *> *)self, (igMetaField *)g_igDirEntry_refField[0]);
    a = (igObject *)igIntMetaField_GetDefaultDescriptor();
    if (a != 0) a->_refCount = a->_refCount + 1;
    t = (igObject *)self->imf;
    IG_OBJECT_RELEASE(t);
    self->imf = (igMetaFieldView *)a;
    b = (igObject *)igShortMetaField_GetDefaultDescriptor();
    if (b != 0) b->_refCount = b->_refCount + 1;
    t2 = (igObject *)self->smf;
    IG_OBJECT_RELEASE(t2);
    self->smf = (igMetaFieldView *)b;
    igResult metaObjectListResult = igIGBFile_BuildMetaObjectList(self);
    pp = (int *)((int)&metaObjectListResult + 0);
    if (*pp == g_resultFailure.v) return 0;
    igResult prepareResult = igIGBFile_PrepareEntriesForWrite(self);
    pp = (int *)((int)&prepareResult + 0);
    if (*pp == g_resultFailure.v) return 0;
    igResult poolNamesResult = igIGBFile_BuildMemoryPoolNameBuffer(self);
    pp = (int *)((int)&poolNamesResult + 0);
    if (*pp == g_resultFailure.v) return 0;
    igResult sizesResult = igIGBFile_ComputeBufferSizes((igIGBFile *)self);
    pp = (int *)((int)&sizesResult + 0);
    if (*pp == g_resultFailure.v) return 0;
    igResult metaObjectBufferResult = igIGBFile_BuildMetaObjectBuffer(self);
    pp = (int *)((int)&metaObjectBufferResult + 0);
    if (*pp == g_resultFailure.v) return 0;
    igResult metaFieldBufferResult = igIGBFile_BuildMetaFieldBuffer(self);
    pp = (int *)((int)&metaFieldBufferResult + 0);
    if (*pp == g_resultFailure.v) return 0;
    igResult alignmentResult = igIGBFile_BuildAlignmentBuffer(self);
    pp = (int *)((int)&alignmentResult + 0);
    if (*pp == g_resultFailure.v) return 0;
    igResult externalResult = igIGBFile_BuildExternalDirectoryBuffer(self);
    pp = (int *)((int)&externalResult + 0);
    if (*pp == g_resultFailure.v) return 0;
    if (self->_sharingState == 0) {
    igResult entryResult = igIGBFile_WriteEntryBuffer((igIGBFile *)self);
    pp = (int *)((int)&entryResult + 0);
    if (*pp == g_resultFailure.v) return 0;
    } else {
    igResult shareResult = igIGBFile_ShareEntries(self);
    pp = (int *)((int)&shareResult + 0);
    if (*pp == g_resultFailure.v) return 0;
    igResult directoryResult = igIGBFile_BuildDirectoryBuffer((igIGBFile *)self);
    pp = (int *)((int)&directoryResult + 0);
    if (*pp == g_resultFailure.v) return 0;
    igResult sharedBufferResult = igIGBFile_BuildIndexBuffer(self);
    pp = (int *)((int)&sharedBufferResult + 0);
    if (*pp == g_resultFailure.v) return 0;
    }
    igResult objectBufferResult = igIGBFile_AllocateObjectBuffer(self);
    pp = (int *)((int)&objectBufferResult + 0);
    if (*pp == g_resultFailure.v) return 0;
    igResult headerResult = igIGBFile_WriteHeader(self);
    pp = (int *)((int)&headerResult + 0);
    if (*pp == g_resultFailure.v) return 0;
    igResult buffersResult = igIGBFile_WriteBuffers(self);
    pp = (int *)((int)&buffersResult + 0);
    if (*pp == g_resultFailure.v) return 0;
    igResult closeResult = igIGBFile_CloseAfterWrite(self);
    pp = (int *)((int)&closeResult + 0);
    if (*pp == g_resultFailure.v) return 0;
    igResult freeResult = igIGBFile_FreeReadBuffers(self);
    pp = (int *)((int)&freeResult + 0);
    if (*pp == g_resultFailure.v) return 0;
    if (self->_autoWriteFilePostProcessState == 1) { igResult concreteResult = self->EnsureConcrete(); }
    return self->_count;
}

igResult igIGBFile_BeginRead(igIGBFileView *self, const char *fileName) {
    igFileView *o;
    int *pp;
    if ((self->_file == 0) && (fileName == 0)) {
        return g_resultFailure;
    }
    if (self->_file == 0) {
        igResult r = igIGBFile_OpenFile(self, fileName, 4);
        pp = (int *)((int)&r + 0);
        if (*pp == g_resultFailure.v) {
            if (fileName != 0) {
                o = self->_file;
                IG_OBJECT_RELEASE(o);
                self->_file = 0;
            }
            return g_resultFailure;
        }
        self->_autoOpened = 1;
    }
    if (self->_file == 0) {
        return g_resultFailure;
    }
    igIGBFile_SetDefaultName((int *)self);
    igAdxFile_SetOpenMode((int)self->_file, 4);
    return g_resultSuccess;
}

igResult igIGBFile_ReadHeader(igIGBFileView *self) {
    IgbFileHeader *h;
    igObject *o;
    igObject *t;

    if (igIGBFile_GetSectionBuffer(self, 0xC0) == g_resultFailure) {
        return g_resultFailure;
    }
    h = (IgbFileHeader *)self->_chunk;
    self->_file->Read(h, 4, 0xC);
    o = (igObject *)igIntMetaField_GetDefaultDescriptor();
    if (o != 0) {
        o->_refCount = o->_refCount + 1;
    }
    t = (igObject *)self->imf;
    IG_OBJECT_RELEASE(t);
    self->imf = (igMetaFieldView *)o;
    o = (igObject *)igShortMetaField_GetDefaultDescriptor();
    if (o != 0) {
        o->_refCount = o->_refCount + 1;
    }
    t = (igObject *)self->smf;
    IG_OBJECT_RELEASE(t);
    self->smf = (igMetaFieldView *)o;
    if (h->magicCookie != self->_magicCookie) {
        self->imf->SwapBytes(h, 0xC);
        if (h->magicCookie == self->_magicCookie) {
            self->_endianSwap = 1;
        }
    } else {
        self->_endianSwap = 0;
    }
    if (h->magicCookie != self->_magicCookie) {
        return g_resultFailure;
    } else {
        self->_magicVersion = (int)*(unsigned short *)&h->magicVersion;
        if ((int)self->_magicVersion > 7) {
            return g_resultFailure;
        } else {
            self->_hasInfo = (h->magicVersion & 0x80000000) != 0;
            self->_hasExternal = (h->magicVersion & 0x40000000) > 0;
            self->_sharedEntries = (h->magicVersion & 0x20000000) > 0;
            self->_hasVersion1Cruft = h->magicVersion == 1;
            self->_hasMemoryPoolNames = (h->magicVersion & 0x10000000) > 0;
            if (self->_hasVersion1Cruft != 0) {
                self->_version1CruftMultiply = 1;
            } else {
                self->_version1CruftMultiply = 0;
            }
            self->_entryBufferSize = h->entryBufferSize;
            self->_entryCount = h->entryCount;
            self->_metaObjectBufferSize = h->metaObjectBufferSize;
            self->_metaObjectCount = h->metaObjectCount;
            self->_objectBufferSize = h->objectBufferSize;
            self->_objectCount = h->objectCount;
            self->_memoryRefBufferSize = h->memoryRefBufferSize;
            self->_memoryRefCount = h->memoryRefCount;
            self->_metaFieldBufferSize = h->metaFieldBufferSize;
            self->_metaFieldCount = h->metaFieldCount;
            return g_resultSuccess;
        }
    }
}

igResult igIGBFile_ReadMetaObjectBuffer(igIGBFileView *self) {
    bool readOk;
    int status;

    if (igIGBFile_GetSectionBuffer(self, self->_metaObjectBufferSize) == g_resultFailure) {
        return g_resultFailure;
    }
    self->_metaObjectBuffer = self->_chunk;
    readOk = true;
    if (self->_metaObjectBufferSize != 0) {
        readOk = self->_file->Read(self->_metaObjectBuffer, self->_metaObjectBufferSize, 1) == 1;
    }
    status = g_resultSuccess.v;
    if (!(int)readOk) {
        status = g_resultFailure.v;
    }
    return igResult(status);
}

/* One persistent field of a metaobject in the file: the index of its type in the file's field
 * types, its slot among the fields of the class that wrote it, and its size. */
struct MetaTableField { short typeIndex; short slot; short size; };

typedef igTDataList<short> igShortListData;

static inline int fieldOffset(const igMetaField *field) { return field->_offset; }
static inline unsigned short fieldSize(const igMetaField *field) { return field->_size; }

/* Appends `field` to `meta` at the next offset that suits the field's own alignment. */
static inline void appendAlignedField(igMetaObject *meta, igMetaField *field) {
    int mask = ((igMetaFieldView *)field)->GetAlignment() - 1;
    meta->_requiredAlignment = meta->_requiredAlignment < mask + 1 ? mask + 1 : meta->_requiredAlignment;
    field->_offset = ~mask & (mask + meta->_sizeofSize);
    igMetaObject_FinalizeAndAppendField(meta, field);
}

/* Reads the file's metaobject table into _metaObjectListInFile. From version 4 each record also
 * lists the persistent fields its class had when the file was written, and the file's slot numbers
 * are mapped to this program's: _metaFieldPerObjectIndices gets one list of slots per metaobject,
 * each slot moved by the number of fields the class that declares it gained or lost since. A class
 * this program does not have fails the read, unless blind objects are on: then a stand-in class is
 * built from its parent and the listed fields, with one-byte fields filling the unlisted slots. */
igResult igIGBFile_ReadMetaObjectList(igIGBFileView *file) {
    int i;
    int fieldWords;
    bool hasFields;
    MetaTableRecord *records;
    MetaTableRecord *record;
    char *name;
    int stride;
    assignReference(file->_metaObjectListInFile, igSmartPointer<igObjectList>((igObjectList *)igMetaObjectList_Create((int)file->_temporaryMemoryPool)));
    setCapacity((igTDataList<igObject *> *)file->_metaObjectListInFile, file->_metaObjectCount);
    igSmartPointer<igShortListData> slotShifts;
    if (file->_magicVersion < 4) {
        stride = 3;
        fieldWords = 0;
        hasFields = false;
    } else {
        fieldWords = 3;
        hasFields = true;
        stride = 6;
        assignReference(file->_metaFieldPerObjectIndices, igSmartPointer<igTDataList<igShortListData *> >(igShortListList_Create(file->_temporaryMemoryPool)));
        setCapacity(file->_metaFieldPerObjectIndices, file->_metaObjectCount);
        {
            igMemoryPoolView *pool = file->_temporaryMemoryPool;
            slotShifts.release();
            slotShifts.p = igShortList_Create(pool);
        }
        setCapacity(slotShifts.p, file->_metaObjectCount);
    }
    if (file->_endianSwap != 0) {
        file->imf->SwapBytes(file->_metaObjectBuffer, stride * file->_metaObjectCount);
    }
    records = (MetaTableRecord *)file->_metaObjectBuffer;
    record = records;
    name = (char *)((int *)record + stride * file->_metaObjectCount);
    for (i = 0; i < file->_metaObjectCount; i++) {
        igMetaObject *meta = (igMetaObject *)igObjectSystem_FindMetaByNameDefault(name);
        if (meta != 0) {
            int majorVersion = record->majorVersion;
            if (majorVersion == 0) {
                majorVersion = 1;
            }
            if (majorVersion == meta->_majorVersion && record->minorVersion == meta->_minorVersion) {
                ObjectList_AppendRetained(file->_metaObjectListInFile, (igObject *)meta);
                if (hasFields) {
                    igSmartPointer<igShortListData> slots(igShortList_Create(file->_temporaryMemoryPool));
                    MetaTableField *field;
                    int j;
                    setCapacity(slots.p, record->fieldCount);
                    ObjectList_AppendRetained((igObjectList *)file->_metaFieldPerObjectIndices, (igObject *)slots.p);
                    field = (MetaTableField *)(name + record->nameSize);
                    j = 0;
                    if (file->_endianSwap != 0) {
                        ((igMetaFieldView *)igShortMetaField_GetDefaultDescriptor())->SwapBytes(field, fieldWords * record->fieldCount);
                    }
                    for (; j < record->fieldCount; j++) {
                        /* The class that declares the slot: the nearest ancestor whose own slots reach it. */
                        int firstOwnSlot = record->persistCount;
                        int owner = i;
                        short slot = field->slot;
                        MetaTableRecord *ancestor = record;
                        while (slot < firstOwnSlot) {
                            owner = ancestor->parentIndex;
                            ancestor = (MetaTableRecord *)((int *)records + owner * stride);
                            firstOwnSlot = ancestor->persistCount;
                        }
                        slot += (*slotShifts.p)[owner];
                        slots.p->append(slot);
                        field = (MetaTableField *)((short *)field + fieldWords);
                    }
                    {
                        short shift = igMetaObject_GetFieldCount(meta) - record->persistCount;
                        slotShifts.p->append(shift);
                    }
                }
            } else {
                return g_resultFailure;
            }
        } else if (hasFields && g_igIGBFile_blindObjects != 0) {
            int parentIndex = record->parentIndex;
            MetaTableRecord *parentRecord = (MetaTableRecord *)((int *)records + parentIndex * stride);
            igMetaObject *parent = ((igMetaObject **)file->_metaObjectListInFile->_data)[parentIndex];
            int inherited;
            int target;
            int slot;
            igMetaObject *blind;
            MetaTableField *field;
            int j;
            if (parent->_abstractState != 0) {
                return g_resultFailure;
            }
            slot = igMetaObject_GetPersistentFieldCount((int)parent);
            inherited = igMetaObject_GetFieldCount(parent) - slot;
            blind = (igMetaObject *)igMetaObject_Create((int)Memory_GetDefaultAllocator());
            igMetaObject_SetName(blind, (int)name);
            igMetaObject_InheritFromBase(blind, parent);
            ObjectList_AppendRetained(file->_metaObjectListInFile, (igObject *)blind);
            field = (MetaTableField *)(name + record->nameSize);
            if (file->_endianSwap != 0) {
                ((igMetaFieldView *)igShortMetaField_GetDefaultDescriptor())->SwapBytes(field, fieldWords * record->fieldCount);
            }
            for (j = 0; j < record->fieldCount; j++) {
                igMetaField *created;
                if (field->slot < parentRecord->persistCount) {
                    field = (MetaTableField *)((short *)field + fieldWords);
                    continue;
                }
                target = field->slot + (*slotShifts.p)[parentIndex] - inherited;
                while (slot < target) {
                    created = (igMetaField *)igCharMetaField_Create((int)file->_temporaryMemoryPool);
                    created->_persistent = 0;
                    igMetaField_Configure(created, "fakeField", 0, -1, blind);
                    created->_internalIndex = slot;
                    created->_size = 1;
                    appendAlignedField(blind, created);
                    slot++;
                    blind->_sizeofSize = fieldOffset(created) + fieldSize(created);
                }
                created = (igMetaField *)igMetaObject_CreateInstance(
                    ((igObjectDispatchView **)file->_metaFieldListInFile->_data)[field->typeIndex]->GetMeta(), (igMemoryPoolView *)Memory_GetDefaultAllocator());
                igMetaField_Configure(created, "Generated", 0, -1, blind);
                created->_internalIndex = target;
                created->_size = field->size;
                appendAlignedField(blind, created);
                slot++;
                field = (MetaTableField *)((short *)field + fieldWords);
                blind->_sizeofSize = fieldOffset(created) + fieldSize(created);
            }
            blind->_sizeofSize = (blind->_sizeofSize + blind->_requiredAlignment - 1) & ~(blind->_requiredAlignment - 1);
            blind->_validity |= 4;
            igObjectSystem_AppendMetaObject(g_objectSystem[0], blind);
            igObjectSystem_RunRegistrationCallbacks((int *)g_objectSystem[0], (int)blind);
            field = (MetaTableField *)(name + record->nameSize);
            {
                igSmartPointer<igShortListData> slots(igShortList_Create(file->_temporaryMemoryPool));
                ObjectList_AppendRetained((igObjectList *)file->_metaFieldPerObjectIndices, (igObject *)slots.p);
                for (j = 0; j < record->fieldCount; j++) {
                    int firstOwnSlot = record->persistCount;
                    int owner = i;
                    short fileSlot = field->slot;
                    MetaTableRecord *ancestor = record;
                    while (fileSlot < firstOwnSlot) {
                        owner = ancestor->parentIndex;
                        ancestor = (MetaTableRecord *)((int *)records + owner * stride);
                        firstOwnSlot = ancestor->persistCount;
                    }
                    fileSlot += (*slotShifts.p)[owner];
                    slots.p->append(fileSlot);
                    field = (MetaTableField *)((short *)field + fieldWords);
                }
                {
                    short shift = igMetaObject_GetFieldCount(blind) - record->persistCount;
                    slotShifts.p->append(shift);
                }
            }
        } else if (hasFields) {
            return g_resultFailure;
        } else {
            return g_resultFailure;
        }
        name += record->nameSize;
        if (hasFields) {
            name += fieldWords * (record->fieldCount * 2);
        }
        record = (MetaTableRecord *)((int *)record + stride);
    }
    file->_metaObjectBuffer = 0;
    return g_resultSuccess;
}

igResult igIGBFile_SetupBasePath(igIGBFileView *self) {
    int n;
    char *p;
    char c;
    self->_basePath = (char *)self->_temporaryMemoryPool->StrDup(self->_file->_fileName);
    n = strlen(self->_basePath);
    while (--n >= 0) {
        p = self->_basePath + n;
        c = *p;
        if (c == 0x2F || c == 0x5C) {
            *p = 0;
            break;
        }
    }
    if (n < 0) {
        *self->_basePath = 0;
    }
    return g_resultSuccess;
}

void igIGBFile_RegisterBlindObjectsConfig(void) {
    igRegistry_GetValueBool((int)((ObjectSystemView **)g_objectSystem)[0]->configRegistry, 2, (const char *)text_blindObjects, (char *)&g_igIGBFile_blindObjects, 0, 0);
}

igResult igIGBFile_ReadNextChunk(igIGBFileView *self) {
    int hi;
    int a2;
    hi = (self->_chunkSize - self->_chunkPlace) % self->_chunkSize;
    if (hi > 0) {
        memcpy(self->_chunk, self->_chunk + self->_chunkPlace, hi);
    }
    a2 = self->_chunkSize - hi;
    if (self->_bufferSize < hi + (self->_bufferPlace + a2)) {
        a2 = (self->_bufferSize - self->_bufferPlace) - hi;
    }
    if (self->_file->Read(self->_chunk + hi, a2, 1) != 1) {
        return g_resultFailure;
    } else {
        self->_chunkPlace = 0;
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
    if (position > file->_chunkSize - 9 || (needed = file->_version1CruftMultiply * 4 + (file->_chunkPlace + igIGBFile_GetObjectSize(file, end)), file->_chunkSize < needed)) {
        if (igIGBFile_ReadNextChunk((igIGBFileView *)file) == g_resultFailure) {
            return SectionObjectRef((igDirEntryView *)0, kRetainReference);
        }
    }
    record = (int *)(file->_chunk + file->_chunkPlace);
    metaIndex = *record;
    if (file->_endianSwap != 0) {
        ((igMetaFieldView *)igIntMetaField_GetDefaultDescriptor())->SwapBytes(&metaIndex, 1);
    }
    igSmartPointer<IgbReadEntry> object(castToKind((IgbReadEntry *)igMetaObject_CreateInstanceWithPool(((igMetaObject **)((igObjectList *)file->_metaObjectListInFile)->_data)[metaIndex], (igMemoryPoolView *)file->_temporaryMemoryPool)), kRetainReference);
    object->release();
    igObject_RegisterInstance((void **)object.p, 0);
    int read;
    if (file->_magicVersion < 4) {
        read = igObject_ReadFields((igObjectDispatchView *)object.p, (FieldRecordHead *)record, file, (igTDataList<igMetaObject *> *)file->_metaObjectListInFile, file->_endianSwap);
    } else {
        read = igObject_ReadPersistentFields((igObjectDispatchView *)object.p, (FieldRecordHead *)record, (igDirectoryView *)file, (igTDataList<igMetaObject *> *)file->_metaObjectListInFile, file->_endianSwap);
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
    file->_uniqueEntryList = (igObjectList *)igDirectory_Create(pool);
    ObjectList_ResizeRetained((igTDataList<igObject *> *)file->_uniqueEntryList, file->_entryCount);
    if (igIGBFile_ReadNextChunk(file) == g_resultFailure) {
        return g_resultFailure;
    }
    for (i = 0; i < file->_entryCount; i++) {
        SectionObjectRef object = igIGBFile_ReadObject((igIGBFile *)file);
        if (object.p == 0) {
            return g_resultFailure;
        }
        if (file->_useMemoryPoolAssignmentsState != 0 && file->_memoryPoolHandles != 0 && g_useOwnerAllocator == 0) {
            int index = object->MemoryPoolIndex();
            if (index > 0) {
                object->SetMemoryPool(((int *)file->_memoryPoolHandles->_data)[index]);
            }
        } else {
            object->SetMemoryPool(-1);
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

igResult igIGBFile_ReadObjectIndex(igIGBFileView *self) {
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
            igDirEntryView *o = (igDirEntryView *)igDirectory_GetEntryAlias((int *)self->_uniqueEntryList, ((short *)self->_chunk)[i]);
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

igResult igIGBFile_ReadFinished(igIGBFileView *self) {
    int count;
    int pool;
    int i;
    igTDataList<int> *oldRefList;
    igTDataList<int> *refList;
    oldRefList = self->_refList;
    count = self->_count;
    pool = (int)self->_temporaryMemoryPool;
    if (oldRefList != 0) {
        oldRefList->_refCount = oldRefList->_refCount - 1;
        if (((unsigned long long)(long long)(int)oldRefList->_refCount & 0x7fffffULL) == 0) {
            igObject_Destroy(oldRefList);
        }
    }
    self->_refList = (igTDataList<int> *)igPointerList_Create(pool);
    refList = self->_refList;
    if (count >= 0) {
        if (count <= refList->_capacity) {
            refList->_count = count;
        } else {
            List_Resize(refList, count, 4);
        }
    }
    for (i = 0; i < count; i++) {
        ((igDirEntryView *)igDirectory_GetEntry((int *)self, i))->ReadFinished(self);
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
        file->_refList = (igTDataList<int> *)igPointerList_Create(pool);
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
        file->_entryPool = (igObject *)igObjectList_Create(pool);
    }
    if (igIGBFile_ReadNextChunk(file) == g_resultFailure) {
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
            int index = object->MemoryPoolIndex();
            if (index > 0) {
                object->SetMemoryPool(((int *)file->_memoryPoolHandles->_data)[index]);
            }
        } else {
            object->SetMemoryPool(-1);
        }
        object->ReadFinished(file);
        if (file->_sharingState != 0) {
            int reference = object->_ref;
            igTDataList<int> *indices = file->_refList;
            if (indices->_count != 0 && i >= 0 && i < indices->_count) {
                ((int *)indices->_data)[i] = reference;
            }
            object->SetReferenceIndex(object->_ref);
            object->SetRef(0);
            object->_index = i;
            file->setEntryRaw(i, object->Resolve(file));
        }
    }
    if (file->_hasCriticalFailure != 0) {
        return g_resultFailure;
    }
    return g_resultSuccess;
}

int igIGBFile_GetCurrentPosition(igIGBFileView *self) {
    if (self->_file->_openMode == 4) {
        return (int)self->_chunk + self->_chunkPlace;
    }
    return self->_objectBufferPlace;
}

void igIGBFile_SetCurrentPosition(igIGBFileView *self, int at) {
    if (self->_file->_openMode == 4) {
        int prev = (int)self->_chunk + self->_chunkPlace;
        self->_chunkPlace = at - (int)self->_chunk;
        self->_bufferPlace = self->_bufferPlace + (at - prev);
        if (self->_bufferPlace != self->_bufferSize) {
            if (self->_chunkPlace > self->_chunkSize - 9) {
                igIGBFile_ReadNextChunk(self);
                return;
            }
            if (self->_chunkPlace + (self->_version1CruftMultiply * 4 + igIGBFile_GetObjectSize(self, at)) > self->_chunkSize) {
                igIGBFile_ReadNextChunk(self);
            }
        }
    } else {
        self->_objectBufferPlace = at;
    }
}

igResult igIGBFile_FreeBasePath(igIGBFileView *self) {
    self->_temporaryMemoryPool->Free(self->_basePath);
    self->_basePath = 0;
    return g_resultSuccess;
}

igResult igIGBFile_ReadMetaFieldList(igIGBFileView *self) {
    __internalObjectList *table;
    int count;
    int *sizes;
    char *name;
    int i;
    if (igIGBFile_GetSectionBuffer(self, self->_metaFieldBufferSize) == g_resultFailure) {
        return g_resultFailure;
    }
    self->_mfBuf = self->_chunk;
    self->_file->Read(self->_mfBuf, self->_metaFieldBufferSize, 1);
    table = igMetaField_GetMetaFieldList();
    count = table->_count;
    sizes = (int *)self->_mfBuf;
    name = (char *)sizes + self->_metaFieldCount * 12;
    if (self->_endianSwap != 0) { self->imf->SwapBytes(sizes, self->_metaFieldCount * 3); }
    {
        igObjectList *v = ((igObjectList *)igMetaFieldList_Create((int)self->_temporaryMemoryPool));
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
            t = registeredMetaField(table, j);
            if (strcmp(t->GetMeta()->_name, name) == 0) { found = true; break; }
        }
        if (!found) { t = 0; } else { t->GetMeta(); }
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

void Gap__Core__igIGBFile__resetFields(igIGBFileView *self) {
    igObject *s0;
    s0 = ((igObject *)Memory_GetDefaultAllocator());
    if (s0) s0->_refCount++;
    releasePool((igObject *)self->_temporaryMemoryPool);
    self->_temporaryMemoryPool = (igMemoryPoolView *)s0;
    s0 = ((igObject *)Memory_GetDefaultAllocator());
    if (s0) s0->_refCount++;
    releasePool((igObject *)self->_dataMemoryPool);
    self->_dataMemoryPool = (igMemoryPoolView *)s0;
    s0 = ((igObject *)Memory_GetDefaultAllocator());
    if (s0) s0->_refCount++;
    releasePool((igObject *)self->_objectMemoryPool);
    self->_objectMemoryPool = (igMemoryPoolView *)s0;
}

static inline void addType(igTDataList<int> *l, int v) {
    int idx;
    idx = l->_count;
    if (l->_capacity > idx) { l->_count = l->getCount() + 1; } else { List_Resize(l, idx + 1, 4); }
    l->_data[idx] = v;
}

igResult igIGBFile_ReadAlignmentTable(igIGBFileView *self) {
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
    igSmartPointer<igTDataList<igStringObj *> > names(g_globalContext->_alignmentStrings, kRetainReference);
    igSmartPointer<igTDataList<int> > values(g_globalContext->_alignmentValues, kRetainReference);
    nameCount = 0;
    if (names.p != 0) { nameCount = names.p->_count; }
    assignReference(self->_alignmentListInFile, igSmartPointer<igTDataList<int> >((igTDataList<int> *)igIntList_Create((int)self->_temporaryMemoryPool)));
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
            char *n = (char *)names.p->_data[j]->_buffer;
            n = (n == 0) ? (*(char * *)g_stringObjEmptyText) : n;
            if (strcmp(n, name) == 0) { found = true; break; }
        }
        if (found) { value = values.p->_data[j]; }
        addType((igTDataList<int> *)self->_alignmentListInFile, value);
        name += sizes[i];
    }
    self->_alignmentBuffer = 0;
    return g_resultSuccess;
    }
}

igResult igIGBFile_ReadObjects(igIGBFileView *self) {
    int n;
    int i;

    self->_objectBufferPlace = (int)self->_objBuf;
    self->_chunkPlace = self->_chunkSize;
    self->_bufferPlace = 0;
    self->_bufferSize = self->_objectBufferSize;
    if (igIGBFile_ReadNextChunk(self) == g_resultFailure) {
        return g_resultFailure;
    }
    n = self->_count;
    for (i = 0; i < n; i++) {
        if (igObject_IsKindOf(self->_data[i], (igMetaObject *)g_igObjectDirEntry_metaObject[0]) != 0) {
            ((igDirEntryView *)igDirectory_GetEntry((int *)self, i))->ResolveEntry(self);
        }
    }
    if (self->_magicVersion < 4) {
        for (i = 0; i < n; i++) {
            if (igObject_IsKindOf(self->_data[i], (igMetaObject *)g_igObjectDirEntry_metaObject[0]) != 0) {
                ((igDirEntryView *)igDirectory_GetEntry((int *)self, i))->ResolveRefOld(self);
            }
        }
    } else {
        for (i = 0; i < n; i++) {
            if (igObject_IsKindOf(self->_data[i], (igMetaObject *)g_igObjectDirEntry_metaObject[0]) != 0) {
                igSmartPointer<igDirEntryView> e((igDirEntryView *)igDirectory_GetEntry((int *)self, i), kRetainReference);
                e.p->ResolveRef(self);
            }
        }
    }
    return g_resultSuccess;
}

igResult igIGBFile_ReadMemoryRefs(igIGBFileView *self) {
    int i;
    for (i = 0; i < self->_count; i++) {
        if (((igObject_IsKindOf(self->_data[i], (igMetaObject *)g_igObjectDirEntry_metaObject[0]) != 0) ^ 1) != 0) {
            ((igDirEntryView *)igDirectory_GetEntry((int *)self, i))->ResolveEntry(self);
        }
    }
    if (self->_magicVersion < 4) {
        for (i = 0; i < self->_count; i++) {
            if (((igObject_IsKindOf(self->_data[i], (igMetaObject *)g_igObjectDirEntry_metaObject[0]) != 0) ^ 1) != 0) {
                ((igDirEntryView *)igDirectory_GetEntry((int *)self, i))->ResolveRefOld(self);
            }
        }
    } else {
        for (i = 0; i < self->_count; i++) {
            if (((igObject_IsKindOf(self->_data[i], (igMetaObject *)g_igObjectDirEntry_metaObject[0]) != 0) ^ 1) != 0) {
                ((igDirEntryView *)igDirectory_GetEntry((int *)self, i))->ResolveRef(self);
            }
        }
    }
    return g_resultSuccess;
}

void igIGBFile_CloseAfterRead(igIGBFileView *self) {
    if (self->_autoOpened > 0) {
        igIGBFile_CloseFile(self);
    }
}

void igIGBFile_CleanUpReadState(igIGBFileView *a) {
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

void Gap__Core__igIGBFile__destructFields(igIGBFileView *self) {
    if (self->_refList != 0) {
        for (int i = 0, count = self->_refList->_count; i < count; i++) {
            self->_data[i]->ReleaseSharedRef(((int *)self->_refList->_data)[i]);
        }
        RELEASE_REF(self->_refList);
        self->_refList = 0;
    }
    RELEASE_REF(self->_refList);
    self->_refList = 0;
    Gap__Core__igObject__destructFields((int)self);
}

igResult igIGBFile_ReadInfoList(igIGBFileView *self) {
    igObject *infoList;
    igObject *t;

    if (self->_hasInfo != 0) {
        if (self->_file->Read((char *)self + g_igIGBFile_infoListPlaceField[0]->_offset, 4, 1) != 1) {
            return g_resultFailure;
        }
        if (self->_endianSwap != 0) {
            self->imf->SwapBytes((char *)self + g_igIGBFile_infoListPlaceField[0]->_offset, 1);
        }
        infoList = (igObject *)((igDirEntryView *)igDirectory_GetEntry((int *)self, self->_infoListPlace))->_ref;
        if (infoList != 0) {
            infoList->_refCount = infoList->_refCount + 1;
        }
        t = (igObject *)self->_infoList;
        IG_OBJECT_RELEASE(t);
        self->_infoList = (igTDataList<igInfoView *> *)infoList;
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
        StringTokenHeader *h = (StringTokenHeader *)(old - 8);
        int n = h->refCount - 1;
        h->refCount = n;
        if (n == 0) { StringChunk_ReleaseHeader((StringChunk *)h->owner, (int)h); }
    }
    *dst = v;
}

igResult igIGBFile_ReadExternalDirectories(igIGBFileView *self) {
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
        if (self->_managingResource == 0) { self->_managingResource = ((igResource *)igResource_GetDefaultResource()); }
        if (self->_managingResource != 0) {
            setPooled(&self->_previousResourceFilePath, (char *)self->_managingResource->_relativeFilePath);
            { char *n; n = self->_basePath; dir = self->_managingResource; setPooled((char **)&dir->_relativeFilePath, n); }
        }
        for (i = 0; i < count; i++) {
            ObjectList_AppendRetained((igObjectList *)self->_externalDirectoryList, (igObject *)(((int)igResource_GetOrLoadDirectory(self->_managingResource, (int)name))));
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

igResult igIGBFile_ReadMemoryPoolNames(igIGBFileView *self) {
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
        addName((igTDataList<int> *)self->_memoryPoolHandles, igMemoryPoolContextInfo_GetMemoryPoolHandle((int)name));
        { int len = strlen(name) + 1; i++; name += len; }
    }
    for (; i < 46; i++) {
        int idx; igTDataList<int> *l; l = (igTDataList<int> *)self->_memoryPoolHandles; idx = l->_count;
        if (l->_capacity > idx) { l->_count = l->getCount() + 1; } else { List_Resize(l, idx + 1, 4); }
        l->_data[idx] = g_igIGBFile_memoryPoolHandleFill[0];
    }
    self->_temporaryMemoryPool->Free(buf);
    return g_resultSuccess;
}

int igIGBFile_AbortRead(igIGBFileView *self) {
    igIGBFile_CleanUpReadState(self);
    self->_loadPendingState = 0;
    self->_validState = 0;
    igIGBFile_CloseAfterRead(self);
    return -1;
}

igResult igIGBFile_MakeConcrete(igIGBFileView *self) {
    int i;
    int n;
    int flag;
    igDirEntryView *e;
    i = 0;
    n = self->_count;
    flag = !self->_concreteState;
    while (i < n) {
        e = (igDirEntryView *)igDirectory_GetEntry((int *)self, i);
        e->RegisterRef(flag);
        i += 1;
    }
    if (flag != 0) {
        self->_concreteState = 1;
    }
    return g_resultSuccess;
}

igResult igIGBFile_PostProcessEntries(igIGBFileView *self) {
    int i;
    void **entry;
    for (i = 0; i < self->_count; i++) {
        entry = (void **)(igDirectory_GetEntry((int *)self, i));
        ((igDirEntryView *)(entry))->PostProcess(self);
    }
    return g_resultSuccess;
}

int igIGBFile_ReadFile(igIGBFileView *self, const char *path) {
  double startTime;
  sprintf(g_igIGBFile_readFileLabel, text_readFile_s, path);
  startTime = g_igIGBFile_loadTimer[0]->GetElapsedSeconds();
  self->_validState = 0;
  self->_loadPendingState = 1;
  self->_concreteState = 0;
  if (igIGBFile_BeginRead(self, path).failed()) return igIGBFile_AbortRead(self);
  if (igIGBFile_ReadHeader(self).failed()) return igIGBFile_AbortRead(self);
  if (self->_magicVersion < 5 && self->_hasExternal) {
    if (!g_igIGBFile_oldVersionErrorSuppressed) {
      int answer = igReportError(text_igIGBFile_readFile_s_unable_to_r, self->_file->_fileName, self->_file->_fileName);
      if (answer != 1 && answer == 2) g_igIGBFile_oldVersionErrorSuppressed = 1;
    }
    return igIGBFile_AbortRead(self);
  }
  if (self->_magicVersion >= 3) {
    if (igIGBFile_ReadMetaFieldList(self).failed()) return igIGBFile_AbortRead(self);
    if (igIGBFile_ReadAlignmentTable(self).failed()) return igIGBFile_AbortRead(self);
  }
  if (igIGBFile_ReadMetaObjectBuffer(self).failed()) return igIGBFile_AbortRead(self);
  if (igIGBFile_ReadMetaObjectList(self).failed()) return igIGBFile_AbortRead(self);
  if (igIGBFile_SetupBasePath(self).failed()) return igIGBFile_AbortRead(self);
  if (self->_magicVersion >= 5) {
    if (igIGBFile_ReadExternalDirectories(self).failed()) return igIGBFile_AbortRead(self);
  }
  if (self->_hasMemoryPoolNames) {
    if (igIGBFile_ReadMemoryPoolNames(self).failed()) return igIGBFile_AbortRead(self);
  }
  if (self->_sharedEntries) {
    if (igIGBFile_ReadObjectSection(self).failed()) return igIGBFile_AbortRead(self);
    if (igIGBFile_ReadObjectIndex(self).failed()) return igIGBFile_AbortRead(self);
    if (igIGBFile_ReadFinished(self).failed()) return igIGBFile_AbortRead(self);
  } else {
    if (igIGBFile_ReadObjectSectionOld(self).failed()) return igIGBFile_AbortRead(self);
  }
  if (self->_magicVersion >= 5) {
    if (igIGBFile_ReadInfoList(self).failed()) return igIGBFile_AbortRead(self);
  }
  if (igIGBFile_ReadObjects(self).failed()) return igIGBFile_AbortRead(self);
  if (self->ReadMemoryEntries().failed()) return igIGBFile_AbortRead(self);
  if (self->_magicVersion < 3) {
    if (igIGBFile_ReadMetaFieldList(self).failed()) return igIGBFile_AbortRead(self);
  }
  if (self->_magicVersion < 5) {
    if (igIGBFile_ReadInfoList(self).failed()) return igIGBFile_AbortRead(self);
  }
  if (self->_magicVersion < 5) {
    if (igIGBFile_ReadExternalDirectories(self).failed()) return igIGBFile_AbortRead(self);
  }
  if (igIGBFile_ReadMemoryRefs(self).failed()) return igIGBFile_AbortRead(self);
  if (igIGBFile_FreeBasePath(self).failed()) return igIGBFile_AbortRead(self);
  igIGBFile_MakeConcrete(self);
  if (self->_autoReadFilePostProcessState == 1) {
    if (self->ReadFilePostProcess().failed()) return igIGBFile_AbortRead(self);
  }
  igIGBFile_CloseAfterRead(self);
  igIGBFile_CleanUpReadState(self);
  self->_validState = 1;
  self->_loadPendingState = 0;
  if (!g_igIGBFile_loadTimeReportSuppressed) {
    int answer = igReport_Detail(text_Total_Time_to_load_s_f_seconds, path, g_igIGBFile_loadTimer[0]->GetElapsedSeconds() - startTime);
    if (answer != 1 && answer == 2) g_igIGBFile_loadTimeReportSuppressed = 1;
  }
  return self->_count;
}

void igIGBFile_EnsureConcrete(int *result, void *self) {
    if (((igIGBFileView *)self)->_concreteState == 0) {
        igDirectory_MakeConcrete((igDirectoryView *)self);
    }
    *result = g_resultSuccess.v;
}

void igIGBFile_ReadFilePostProcess(int *result, igIGBFileView *self) {
    if (self->_readFilePostProcessedState == 0) {
        igResult postProcessed = igIGBFile_PostProcessEntries(self);
        if (self->_managingResource != 0) {
            igResource_FinishAsyncLoad(self->_managingResource, (int)self->_name);
        }
        self->_readFilePostProcessedState = 1;
        *result = postProcessed.v;
    } else {
        *result = g_resultSuccess.v;
    }
}

static inline igIGBFileView *castInfo(igIGBFileView *o) { if (o != 0 && igObject_IsKindOf((void *)o, (igMetaObject *)(((int *)g_igIGBFile_metaObject)[0])) != 0) { return o; } return 0; }

/* Checks each external file, then this file's own post-read step. */
igResult igIGBFile_ReadFilePostProcessAll(igIGBFileView *self) {
    igResult result = g_resultSuccess;
    int i;
    for (i = 0; i < self->_externalDirectoryList->_count; i++) {
        igSmartPointer<igIGBFileView> o(castInfo((igIGBFileView *)self->_externalDirectoryList->_data[i]), kRetainReference);
        if (o.p != 0) {
            if (o.p->ReadFilePostProcessAll() == g_resultFailure) {
                result = g_resultFailure;
            }
        }
    }
    if (self->ReadFilePostProcess() == g_resultFailure) {
        result = g_resultFailure;
    }
    return result;
}

int igIGBFile_WriteMemoryRefs(igIGBFileView *o) {
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
        ((igDirEntryView *)igDirectory_GetEntry((int *)o, i))->WriteMemory(o);
    }
    o->_temporaryMemoryPool->Free(o->_chunk);
    o->_chunk = 0;
    return 1;
}

igResult igIGBFile_GetSectionBuffer(igIGBFileView *self, int size) {
    char *a1;
    a1 = self->_chunk;
    if (a1 != 0 && self->_chunkSize >= size) {
        return g_resultSuccess;
    } else {
        if (a1 != 0) {
            self->_temporaryMemoryPool->Free(a1);
        }
        self->_chunkSize = self->_forceChunkSize;
        if (self->_chunkSize < 0) {
            self->_chunkSize = self->_file->_optimalReadChunkSize;
        }
        if (self->_chunkSize < size) {
            self->_chunkSize = size;
        }
        self->_chunkSize = (self->_chunkSize + 3) & ~3;
        self->_chunk = (char *)self->_temporaryMemoryPool->AllocateAligned(self->_chunkSize, self->_file->_pageSize);
        if (self->_chunk == 0) {
            return g_resultFailure;
        } else {
            return g_resultSuccess;
        }
    }
}

void igIGBFile_ReadMemoryEntries(int *result, igIGBFileView *self) {
    int n;
    int i;
    self->_memoryBufferPlace = 0;
    self->_memoryBytesCopied = 0;
    self->_bytesRemainingInChunk = 0;
    n = self->_count;
    for (i = 0; i < n; i++) {
        ((igDirEntryView *)igDirectory_GetEntry((int *)self, i))->ReadMemory(self);
    }
    *result = g_resultSuccess.v;
}

