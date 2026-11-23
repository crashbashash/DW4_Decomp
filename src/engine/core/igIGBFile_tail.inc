inline bool igResult::failed() const { return v == g_resultFailure.v; }

namespace Gap {
namespace Core {

int igIGBFile::getReadSizeFromMemory(void *src) {
    int size;
    igIntMetaField *intField;

    size = ((FieldRecordHead *)src)->size;
    if (_endianSwap != 0) {
        intField = igIntMetaField::getMetaField();
        intField->endianSwapMemory(&size, 1);
    }
    return size;
}

igResult igIGBFile::open(const char *fileName, igFile::OpenMode e) {
    if (fileName == 0 && _file == 0) {
        return g_resultFailure;
    }
    if (fileName == 0 && _file != 0) {
        return _file->open(e);
    }
    if (_file == 0 && fileName != 0) {
        _file = igSmartPointer<igFile>(igFile::_instantiateFromPool((igMemoryPoolView *)_temporaryMemoryPool.p));
        if (_file == 0) {
            return g_resultFailure;
        }
        _file->setFileName(fileName);
        return _file->open(e);
    }
    _file->close();
    _file = igSmartPointer<igFile>(igFile::_instantiateFromPool((igMemoryPoolView *)_temporaryMemoryPool.p));
    _file->setFileName(fileName);
    return _file->open(e);
}

void igIGBFile::close() {
    if (_file != 0) {
        _file->close();
        _file = 0;
    }
}

/* Names an unnamed directory after its file: the file name past the last path separator. */
void igIGBFile::setDirectoryNameBasedOnFileName() {
    const char *fileName;
    int i;
    int c;

    if (_name.p == 0 || strcmp(_name.p, "") == 0) {
        fileName = _file->_fileName.p;
        i = strlen(fileName) - 1;
        while (i > 0 && '/' != (c = *((fileName + i) - 1)) && c != '\\') {
            i = i - 1;
        }
        setName(fileName + i);
    }
}

igResult igIGBFile::writeOpen(const char *fileName) {
    if (_file == 0 && fileName == 0) {
        return g_resultFailure;
    }
    if (_file == 0) {
        if (open(fileName, igFile::kWriteBinary) == g_resultFailure) {
            if (fileName != 0) {
                _file = 0;
            }
            return g_resultFailure;
        }
        _autoOpened = 1;
    }
    if (_file == 0) {
        return g_resultFailure;
    }
    setDirectoryNameBasedOnFileName();
    _file->setOpenMode(igFile::kWriteBinary);
    return g_resultSuccess;
}

igResult igIGBFile::writeCreateMetaObjectList() {
    igMetaObject *meta;
    unsigned int n;
    unsigned int i;
    _metaObjectListInFile = igSmartPointer< ::igMetaObjectList>((::igMetaObjectList *)igMetaObjectList_Create((int)_temporaryMemoryPool.p));
    igMetaObject_AddToMetaObjectList((::igTDataList<igMetaObject *> *)_metaObjectListInFile.p, igDirEntry::getClassMeta());
    meta = igDirEntry::getClassMeta();
    n = (unsigned int)igMetaObject_CountTree(meta);
    for (i = 0; i < n; i++) {
        ((igObjectList *)_metaObjectListInFile.p)->appendUnique((igObject *)igMetaObject_GetTreeNode(meta, (int)i));
    }
    return g_resultSuccess;
}

igResult igIGBFile::writeMakeProxies() {
    int i;

    for (i = 0; i < _count; i++) {
        getNonShared(i)->_index = i;
        getNonShared(i)->writeMakeProxy(this);
    }
    return g_resultSuccess;
}

/* The memory pool names, in pool order: the buffer's size and the name count, then the names. */
igResult igIGBFile::writeCreateMemoryPoolReferences() {
    int i; const char *name; char *p; int j; int n; int length;
    _memoryPoolNameBufferSize = 8;
    i = 0;
    do {
        length = strlen((const char *)Memory_GetPoolNameByIndex(i)) + 1;
        i++;
        _memoryPoolNameBufferSize = _memoryPoolNameBufferSize + length;
    } while (i < 46);
    _memoryPoolNameBuffer = (char *)((igMemoryPoolView *)_temporaryMemoryPool.p)->Allocate(_memoryPoolNameBufferSize);
    j = 0;
    p = _memoryPoolNameBuffer;
    ((int *)p)[0] = _memoryPoolNameBufferSize;
    ((int *)p)[1] = 46;
    p += 8;
    do {
        name = (const char *)Memory_GetPoolNameByIndex(j);
        n = strlen(name) + 1;
        memcpy(p, name, n);
        j++;
        p += n;
    } while (j < 46);
    if (_endianSwap) imf->endianSwapMemory(_memoryPoolNameBuffer, 2);
    return g_resultSuccess;
}

igResult igIGBFile::writeComputeBufferSizes() {
    int i;

    _objectCount = 0;
    _memoryRefCount = 0;
    _objectBufferSize = 0;
    _memoryRefBufferSize = 0;
    for (i = 0; i < _count; i++) {
        getNonShared(i)->writeComputeBufferSize(this);
    }
    return g_resultSuccess;
}
}
}

static inline void bump(const igSmartPointer<igTDataList<int> > &r, int off) { int *c = (int *)((char *)r.p->_data + off); *c = *c + 1; }

static inline void fillWords(igTDataList<int> *l, int c, int *value) {
    if (c >= 0) { if (c <= l->_capacity) { l->_count = c; } else { ((Gap::Core::igDataList *)l)->resizeAndSetCount(c, 4); } }
}

static inline int indexOfParent(igObjectList *l, const MetaTableKey &key) {
    int n = l->_count;
    int i;
    for (i = 0; i < n; i++) {
        if (key.v == ((int *)l->_data)[i]) { return i; }
    }
    return -1;
}

namespace Gap {
namespace Core {

igResult igIGBFile::writeCreateMetaObjectBuffer() {
    int base;
    int i;
    _metaObjectCount = _metaObjectListInFile->_count;
    _metaObjectBufferSize = _metaObjectCount * 24;
    {
    igSmartPointer< ::igTDataList<int> > inherited((::igTDataList<int> *)igIntList_Create((int)_temporaryMemoryPool.p));
    fillWords(inherited.p, _metaObjectCount, 0);
    {
        int n = inherited.p->_count;
        int *d = inherited.p->_data;
        int k;
        for (k = 0; k < n; k++) { d[k] = g_igIGBFile_inheritedFieldCountFill[0]; }
    }
    {
    igSmartPointer< ::igTDataList<int> > persistent((::igTDataList<int> *)igIntList_Create((int)_temporaryMemoryPool.p));
    fillWords(persistent.p, _metaObjectCount, 0);
    {
        int n = persistent.p->_count;
        int *d = persistent.p->_data;
        int k;
        for (k = 0; k < n; k++) { d[k] = g_igIGBFile_persistentFieldCountFill[0]; }
    }
    base = igMetaObject_GetFieldCount(igObject::getClassMeta());
    for (i = 0; i < _metaObjectCount; i++) {
        int j;
        ::__internalObjectList *fields;
        int n;
        igMetaObject *t;
        int off;
        off = i * 4;
        t = *(igMetaObject **)((char *)_metaObjectListInFile->_data + off);
        fields = (::__internalObjectList *)t->_metaFields;
        n = fields->_count;
        for (j = base; j < n; j++) {
            ::igMetaField *f = ((::igMetaField **)fields->_data)[j];
            if (f->_isRunTime == 0) {
                if (f->_persistent != 0) {
                    _metaObjectBufferSize = _metaObjectBufferSize + 6;
                    bump(inherited, off);
                }
                bump(persistent, off);
            }
        }
        _metaObjectBufferSize = _metaObjectBufferSize + (strlen((char *)t->_name) + 1);
        _metaObjectBufferSize = (_metaObjectBufferSize + 1) & ~1;
    }
    _metaObjectBuffer = (char *)((igMemoryPoolView *)_temporaryMemoryPool.p)->AllocateAligned(_metaObjectBufferSize, 16);
    {
        igMetaObject *t;
        int off;
        int k;
        MetaTableRecord *rec = (MetaTableRecord *)_metaObjectBuffer;
        for (k = 0; k < _metaObjectCount; k++) {
            MetaTableKey key;
            int len;
            off = k * 4;
            t = *(igMetaObject **)((char *)_metaObjectListInFile->_data + off);
            len = strlen((char *)t->_name) + 1;
            rec->nameSize = (len + 1) & ~1;
            rec->majorVersion = t->_majorVersion;
            rec->minorVersion = t->_minorVersion;
            rec->fieldCount = *(int *)((char *)inherited.p->_data + off);
            {
                ::igObjectList *l = (::igObjectList *)_metaObjectListInFile.p;
                *(int *)&key = t->_parent;
                rec->parentIndex = indexOfParent(l, key);
            }
            rec->persistCount = base + *(int *)((char *)persistent.p->_data + off);
            rec++;
        }
    }
    {
        char *out = (char *)((MetaTableRecord *)_metaObjectBuffer + _metaObjectCount);
        igShortMetaField *desc;
        short *p;
        ::igMetaField *f;
        int k;
        int j;
        int n;
        int off;
        igMetaObject *t;
        ::__internalObjectList *fields;
        desc = igShortMetaField::getMetaField();
        for (k = 0; k < _metaObjectCount; k++) {
            off = k * 4;
            t = *(igMetaObject **)((char *)_metaObjectListInFile->_data + off);
            strcpy(out, (char *)t->_name);
            fields = (::__internalObjectList *)t->_metaFields;
            j = base;
            n = fields->_count;
            out += ((MetaTableRecord *)_metaObjectBuffer)[k].nameSize;
            p = (short *)out;
            for (; j < n; j++) {
                f = ((::igMetaField **)fields->_data)[j];
                if (f->_persistent != 0 && f->_isRunTime == 0) {
                    p[0] = ((igMetaField *)f)->getTypeIndex();
                    p[1] = f->_internalIndex;
                    p[2] = f->_size;
                    p += 3;
                }
            }
            if (_endianSwap != 0) {
                desc->endianSwapMemory(out, *(int *)((char *)inherited.p->_data + off) * 3);
            }
            out = (char *)p;
        }
    }
    if (_endianSwap != 0) { imf->endianSwapMemory(_metaObjectBuffer, _metaObjectCount * 6); }
    return g_resultSuccess;
    }
    }
}

/* The registered metafield types: a record per type (its name's length and version), then the names. */
igResult igIGBFile::writeCreateMetaFieldBuffer() {
    int i;
    int j;
    int k;
    int *records;
    char *name;
    igObjectDispatchView *type;
    _metaFieldCount = igMetaField::getMetaFieldTypes()->_count;
    _metaFieldBufferSize = _metaFieldCount * 12;
    for (i = 0; i < _metaFieldCount; i++) {
        _metaFieldBufferSize = _metaFieldBufferSize + (strlen((const char *)registeredMetaField(igMetaField::getMetaFieldTypes(), i)->GetMeta()->_name) + 1);
    }
    _mfBuf = (char *)((igMemoryPoolView *)_temporaryMemoryPool.p)->AllocateAligned(_metaFieldBufferSize, 16);
    k = 0;
    records = (int *)_mfBuf;
    for (i = 0; i < _metaFieldCount; i++) {
        type = registeredMetaField(igMetaField::getMetaFieldTypes(), i);
        records[k] = strlen((const char *)type->GetMeta()->_name) + 1;
        k++;
        records[k] = type->GetMeta()->_majorVersion;
        k++;
        records[k] = type->GetMeta()->_minorVersion;
        k++;
    }
    name = _mfBuf + _metaFieldCount * 12;
    for (j = 0; j < _metaFieldCount; j++) {
        strcpy(name, (const char *)registeredMetaField(igMetaField::getMetaFieldTypes(), j)->GetMeta()->_name);
        name += *(int *)(_mfBuf + j * 12);
    }
    if (_endianSwap != 0) imf->endianSwapMemory(_mfBuf, _metaFieldCount * 3);
    return g_resultSuccess;
}
}
}

static inline char *nameOf(const igSmartPointer<igTDataList< ::igStringObj *> > &r, int i) {
    char *n = (char *)r.p->_data[i]->_buffer;
    n = (n == 0) ? (g_stringObjEmptyText) : n;
    return n;
}

namespace Gap {
namespace Core {

/* The alignment names the global resource knows: the buffer's size, a version word and the count, each name's
 * length, then the names. */
igResult igIGBFile::writeCreateMemoryAlignmentBuffer() {
    igSmartPointer< ::igTDataList< ::igStringObj *> > names((::igTDataList< ::igStringObj *> *)g_globalContext->_alignmentStrings.p, kRetainReference);
    int i;
    int *lengths;
    char *out;
    _alignmentCount = (names.p != 0) ? names.p->_count : 0;
    i = 0;
    _alignmentBufferSize = _alignmentCount * 4 + 12;
    for (; i < _alignmentCount; i++) {
        _alignmentBufferSize += strlen(nameOf(names, i)) + 1;
    }
    _alignmentBuffer = (char *)((igMemoryPoolView *)_temporaryMemoryPool.p)->AllocateAligned(_alignmentBufferSize, 16);
    {
        int *header = (int *)_alignmentBuffer;
        lengths = header + 3;
        header[0] = _alignmentBufferSize;
        header[1] = 1;
        header[2] = _alignmentCount;
    }
    for (i = 0; i < _alignmentCount; i++) {
        lengths[i] = strlen(nameOf(names, i)) + 1;
    }
    out = (char *)(lengths + _alignmentCount);
    for (i = 0; i < _alignmentCount; i++) {
        strcpy(out, nameOf(names, i));
        out += lengths[i];
    }
    if (_endianSwap != 0) { imf->endianSwapMemory(_alignmentBuffer, _alignmentCount + 3); }
    return g_resultSuccess;
}

/* The external directories' names, laid out as the alignment names are. */
igResult igIGBFile::writeCreateExternalDirectoryBuffer() {
    igDirectoryList *list = _externalDirectoryList;
    int count, i, k;
    if (list != 0 && (count = list->_count) > 0) {
        char *name;
        int *lengths;
        int total;
        _hasExternal = 1;
        total = (count + 3) * 4;
        _externalDirectoryBufferSize = total;
        for (i = 0; i < count; i++) {
            _externalDirectoryBufferSize = _externalDirectoryBufferSize + (strlen(_externalDirectoryList->get(i)->_name.p) + 1);
        }
        _externalDirectoryBuffer = (char *)((igMemoryPoolView *)_temporaryMemoryPool.p)->AllocateAligned(_externalDirectoryBufferSize, 16);
        ((int *)_externalDirectoryBuffer)[0] = _externalDirectoryBufferSize;
        ((int *)_externalDirectoryBuffer)[1] = 1;
        ((int *)_externalDirectoryBuffer)[2] = count;
        lengths = (int *)_externalDirectoryBuffer + 3;
        for (i = 0; i < count; i++) {
            lengths[i] = strlen(_externalDirectoryList->get(i)->_name.p) + 1;
        }
        name = _externalDirectoryBuffer + total;
        for (k = 0; k < count; k++) {
            strcpy(name, _externalDirectoryList->get(k)->_name.p);
            name += strlen(name) + 1;
        }
        if (_endianSwap != 0) {
            imf->endianSwapMemory(_externalDirectoryBuffer, count + 2);
        }
    } else {
        _hasExternal = 0;
    }
    return g_resultSuccess;
}

/* Lays the unique entries out in one buffer: sizes them, allocates, then writes each. */
igResult igIGBFile::writeCreateAndFillSharedEntryBuffer() {
    char *cursor;
    int i;
    _entryBufferSize = 0;
    _entryCount = _uniqueEntryList->_count;
    for (i = 0; i < _entryCount; i++) {
        _entryBufferSize = _entryBufferSize + ((igObject *)igDirectory_GetEntryAlias((int *)_uniqueEntryList.p, i))->getIoSize();
    }
    _dirBuf = (char *)((igMemoryPoolView *)_temporaryMemoryPool.p)->AllocateAligned(_entryBufferSize, 16);
    cursor = _dirBuf;
    for (i = 0; i < _entryCount; i++) {
        cursor += igObject_WritePersistentFields((igObjectDispatchView *)igDirectory_GetEntryAlias((int *)_uniqueEntryList.p, i), (int *)cursor, 0, (::igTDataList<igMetaObject *> *)_metaObjectListInFile.p, _endianSwap);
    }
    return g_resultSuccess;
}

/* For each entry, the index of its shared entry among the unique ones. */
igResult igIGBFile::writeCreateAndFillEntryIndexBuffer() {
    int count = _count;
    int i;
    _indexBufferSize = count * 2 + 8;
    _indexBuffer = (char *)((igMemoryPoolView *)_temporaryMemoryPool.p)->AllocateAligned(_indexBufferSize, 16);
    ((int *)_indexBuffer)[0] = _indexBufferSize;
    ((int *)_indexBuffer)[1] = count;
    for (i = 0; i < count; i++) {
        ::igTDataList<igDirEntry *> *unique = (::igTDataList<igDirEntry *> *)_uniqueEntryList.p;
        ((short *)(_indexBuffer + 8))[i] = unique->sortedFind((igDirEntry **)_data + i);
    }
    if (_endianSwap != 0) {
        imf->endianSwapMemory(_indexBuffer, 2);
        smf->endianSwapMemory(_indexBuffer + 8, count);
    }
    return g_resultSuccess;
}

/* Replaces each entry by the one it shares with the entries before it, keeping each reference in _refList. */
igResult igIGBFile::writeShareEntries() {
    int n;
    int i;
    if (_sharedEntries != 0) { return g_resultSuccess; }
    {
        int pool = (int)_temporaryMemoryPool.p;
        _refList.release();
        _refList.p = (igPointerList *)igPointerList_Create(pool);
    }
    _refList->setCount(_count);
    {
        igMemoryPoolView *pool = (igMemoryPoolView *)_temporaryMemoryPool.p;
        _entryPool.release();
        _entryPool.p = igObjectList::_instantiateFromPool(pool);
    }
    {
        igMemoryPoolView *pool = (igMemoryPoolView *)_temporaryMemoryPool.p;
        _uniqueEntryList.release();
        _uniqueEntryList.p = igDirectory::_instantiateFromPool(pool);
    }
    n = _count;
    for (i = 0; i < n; i++) {
        igDirEntry *entry = ((igDirEntry **)_data)[i];
        if (entry == entry->share(this)) {
            insertObjectSorted((::igObjectList *)_uniqueEntryList.p, entry);
        }
        _refList->set(i, entry->getRef());
        entry->refEntry(entry->getRef());
        entry->setRef(0);
        entry->_index = i;
        set(i, entry->share(this));
    }
    _sharedEntries = 1;
    return g_resultSuccess;
}

/* The same layout for the file's own object list. */
igResult igIGBFile::writeCreateAndFillEntryBuffer() {
    char *cursor;
    int i;
    _entryBufferSize = 0;
    _entryCount = _count;
    for (i = 0; i < _entryCount; i++) {
        _entryBufferSize = _entryBufferSize + getNonShared(i)->getIoSize();
    }
    _dirBuf = (char *)((igMemoryPoolView *)_temporaryMemoryPool.p)->AllocateAligned(_entryBufferSize, 16);
    cursor = _dirBuf;
    for (i = 0; i < _entryCount; i++) {
        cursor += igObject_WritePersistentFields((igObjectDispatchView *)getNonShared(i), (int *)cursor, 0, (::igTDataList<igMetaObject *> *)_metaObjectListInFile.p, _endianSwap);
    }
    return g_resultSuccess;
}

igResult igIGBFile::writeCreateAndFillObjectBuffer() {
    int i;
    int n;
    _objBuf = (char *)((igMemoryPoolView *)_temporaryMemoryPool.p)->AllocateAligned(_objectBufferSize, 16);
    _objectBufferPlace = _objBuf;
    n = _count;
    for (i = 0; i < n; i++) {
        get(i)->writeWrite(this);
    }
    return g_resultSuccess;
}

/* The 48-byte header: the table sizes and counts, then the magic cookie and the version word with the
 * file's flags in its top bits. */
igResult igIGBFile::writeCreateAndWriteHeader() {
    IgbFileHeader *header = (IgbFileHeader *)((igMemoryPoolView *)_temporaryMemoryPool.p)->AllocateAligned(48, 16);
    memset(header, 0, 48);
    header->entryBufferSize = _entryBufferSize; header->entryCount = _entryCount;
    header->metaObjectBufferSize = _metaObjectBufferSize; header->metaObjectCount = _metaObjectCount;
    header->objectBufferSize = _objectBufferSize; header->objectCount = _objectCount;
    header->memoryRefBufferSize = _memoryRefBufferSize; header->memoryRefCount = _memoryRefCount;
    header->metaFieldBufferSize = _metaFieldBufferSize; header->metaFieldCount = _metaFieldCount;
    header->magicCookie = _magicCookie;
    int version = _magicVersion;
    if (_hasInfo) version |= 0x80000000;
    if (_hasExternal) version |= 0x40000000;
    if (_sharingState) version |= 0x20000000;
    if (_useMemoryPoolAssignmentsState) version |= 0x10000000;
    header->magicVersion = version;
    if (_endianSwap) imf->endianSwapMemory(header, 12);
    _file->fwrite(header, 4, 12);
    ((igMemoryPoolView *)_temporaryMemoryPool.p)->Free(header);
    return g_resultSuccess;
}

/* Writes the tables in file order, then the objects and the memory blocks; fails only when nothing was written. */
igResult igIGBFile::writeWriteAllBuffers() {
    int metaFields = _file->fwrite(_mfBuf, _metaFieldBufferSize, 1);
    int alignments = _file->fwrite(_alignmentBuffer, _alignmentBufferSize, 1);
    int metaObjects = _file->fwrite(_metaObjectBuffer, _metaObjectBufferSize, 1);
    if (_externalDirectoryBuffer != 0) {
        _file->fwrite(_externalDirectoryBuffer, _externalDirectoryBufferSize, 1);
        ((igMemoryPoolView *)_temporaryMemoryPool.p)->Free(_externalDirectoryBuffer);
        _externalDirectoryBuffer = 0;
    }
    int poolNames = 1;
    if (_useMemoryPoolAssignmentsState != 0) {
        poolNames = _file->fwrite(_memoryPoolNameBuffer, _memoryPoolNameBufferSize, poolNames);
    }
    int entries = _file->fwrite(_dirBuf, _entryBufferSize, 1);
    if (_endianSwap != 0) {
        imf->endianSwapMemory(_indexBuffer, 2);
    }
    int indices = _file->fwrite(_indexBuffer, _indexBufferSize, 1);
    if (_infoListPlace > -1) {
        if (_endianSwap != 0) {
            imf->endianSwapMemory((char *)this + k_infoListPlace->_offset, 1);
        }
        _file->fwrite((char *)this + k_infoListPlace->_offset, 4, 1);
    }
    int objects = _file->fwrite(_objBuf, _objectBufferSize, 1);
    int memory = writeMemoryRefBuffer();
    if (indices + (alignments + (metaFields + (memory + (objects + (entries + (metaObjects + poolNames)))))) == 0) {
        return g_resultFailure;
    } else {
        return g_resultSuccess;
    }
}

igResult igIGBFile::writeClose() {
    if (_autoOpened != 0) {
        close();
    }
    return g_resultSuccess;
}

igResult igIGBFile::writeReleaseAllBuffers() {
    ((igMemoryPoolView *)_temporaryMemoryPool.p)->Free(_metaObjectBuffer); _metaObjectBuffer = 0;
    ((igMemoryPoolView *)_temporaryMemoryPool.p)->Free(_dirBuf); _dirBuf = 0;
    ((igMemoryPoolView *)_temporaryMemoryPool.p)->Free(_objBuf); _objBuf = 0;
    ((igMemoryPoolView *)_temporaryMemoryPool.p)->Free(_mfBuf); _mfBuf = 0;
    ((igMemoryPoolView *)_temporaryMemoryPool.p)->Free(_alignmentBuffer); _alignmentBuffer = 0;
    if (_indexBuffer) ((igMemoryPoolView *)_temporaryMemoryPool.p)->Free(_indexBuffer);
    _memoryPoolNameBufferSize = 0;
    if (_memoryPoolNameBuffer) { ((igMemoryPoolView *)_temporaryMemoryPool.p)->Free(_memoryPoolNameBuffer); _memoryPoolNameBuffer = 0; }
    _memoryPoolHandles = 0;
    return g_resultSuccess;
}

/* Adds the info list as an object entry, when the file has infos. */
igResult igIGBFile::writeProcessInfoList() {
    igInfoList *infoList = _infoList;
    if (infoList->_count > 0) {
        _infoListPlace = addObject(infoList, 0, 0);
        _hasInfo = 1;
    }
    return g_resultSuccess;
}

int igIGBFile::writeFile(const char *fileName)
{
    ((igRegistry *)g_objectSystem->configRegistry)->getValue(2, "forceWriteMemoryPoolInfoFromMetaState", _forceWriteMemoryPoolInfoFromMetaState, 0, 0);
    if (writeOpen(fileName).failed()) return 0;
    if (writeProcessInfoList().failed()) return 0;
    bubbleSort((igRefMetaField *)igDirEntry::k_ref);
    imf = igIntMetaField::getMetaField();
    smf = igShortMetaField::getMetaField();
    if (writeCreateMetaObjectList().failed()) return 0;
    if (writeMakeProxies().failed()) return 0;
    if (writeCreateMemoryPoolReferences().failed()) return 0;
    if (writeComputeBufferSizes().failed()) return 0;
    if (writeCreateMetaObjectBuffer().failed()) return 0;
    if (writeCreateMetaFieldBuffer().failed()) return 0;
    if (writeCreateMemoryAlignmentBuffer().failed()) return 0;
    if (writeCreateExternalDirectoryBuffer().failed()) return 0;
    if (_sharingState == 0) {
        if (writeCreateAndFillEntryBuffer().failed()) return 0;
    } else {
        if (writeShareEntries().failed()) return 0;
        if (writeCreateAndFillSharedEntryBuffer().failed()) return 0;
        if (writeCreateAndFillEntryIndexBuffer().failed()) return 0;
    }
    if (writeCreateAndFillObjectBuffer().failed()) return 0;
    if (writeCreateAndWriteHeader().failed()) return 0;
    if (writeWriteAllBuffers().failed()) return 0;
    if (writeClose().failed()) return 0;
    if (writeReleaseAllBuffers().failed()) return 0;
    if (_autoWriteFilePostProcessState == 1) {
        ensureConcrete();
    }
    return _count;
}

igResult igIGBFile::readOpen(const char *fileName) {
    if ((_file == 0) && (fileName == 0)) {
        return g_resultFailure;
    }
    if (_file == 0) {
        if (open(fileName, igFile::kReadBinary).failed()) {
            if (fileName != 0) {
                _file = 0;
            }
            return g_resultFailure;
        }
        _autoOpened = 1;
    }
    if (_file == 0) {
        return g_resultFailure;
    }
    setDirectoryNameBasedOnFileName();
    _file->setOpenMode(igFile::kReadBinary);
    return g_resultSuccess;
}

/* Reads the 48-byte header, detecting a file written with the other byte order by its magic cookie. */
igResult igIGBFile::readHeader() {
    IgbFileHeader *header;

    if (allocateReadChunkBuffer(0xC0) == g_resultFailure) {
        return g_resultFailure;
    }
    header = (IgbFileHeader *)_chunk;
    _file->fread(header, 4, 12);
    imf = igIntMetaField::getMetaField();
    smf = igShortMetaField::getMetaField();
    if (header->magicCookie != _magicCookie) {
        imf->endianSwapMemory(header, 12);
        if (header->magicCookie == _magicCookie) {
            _endianSwap = 1;
        }
    } else {
        _endianSwap = 0;
    }
    if (header->magicCookie != _magicCookie) {
        return g_resultFailure;
    } else {
        /* the version number is the version word's low half; its top bits are the file's flags */
        _magicVersion = *(unsigned short *)&header->magicVersion;
        if (_magicVersion > 7) {
            return g_resultFailure;
        } else {
            _hasInfo = (header->magicVersion & 0x80000000) != 0;
            _hasExternal = (header->magicVersion & 0x40000000) > 0;
            _sharedEntries = (header->magicVersion & 0x20000000) > 0;
            _hasVersion1Cruft = header->magicVersion == 1;
            _hasMemoryPoolNames = (header->magicVersion & 0x10000000) > 0;
            if (_hasVersion1Cruft != 0) {
                _version1CruftMultiply = 1;
            } else {
                _version1CruftMultiply = 0;
            }
            _entryBufferSize = header->entryBufferSize;
            _entryCount = header->entryCount;
            _metaObjectBufferSize = header->metaObjectBufferSize;
            _metaObjectCount = header->metaObjectCount;
            _objectBufferSize = header->objectBufferSize;
            _objectCount = header->objectCount;
            _memoryRefBufferSize = header->memoryRefBufferSize;
            _memoryRefCount = header->memoryRefCount;
            _metaFieldBufferSize = header->metaFieldBufferSize;
            _metaFieldCount = header->metaFieldCount;
            return g_resultSuccess;
        }
    }
}

igResult igIGBFile::readMetaObjectBuffer() {
    bool readOk;
    int status;

    if (allocateReadChunkBuffer(_metaObjectBufferSize) == g_resultFailure) {
        return g_resultFailure;
    }
    _metaObjectBuffer = _chunk;
    readOk = true;
    if (_metaObjectBufferSize != 0) {
        readOk = _file->fread(_metaObjectBuffer, _metaObjectBufferSize, 1) == 1;
    }
    status = g_resultSuccess.v;
    if (!readOk) {
        status = g_resultFailure.v;
    }
    return igResult(status);
}
}
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

namespace Gap {
namespace Core {

unsigned char igIGBFile::gBlindObjectEnabled;

/* Reads the file's metaobject table into _metaObjectListInFile. From version 4 each record also
 * lists the persistent fields its class had when the file was written, and the file's slot numbers
 * are mapped to this program's: _metaFieldPerObjectIndices gets one list of slots per metaobject,
 * each slot moved by the number of fields the class that declares it gained or lost since. A class
 * this program does not have fails the read, unless blind objects are on: then a stand-in class is
 * built from its parent and the listed fields, with one-byte fields filling the unlisted slots. */
igResult igIGBFile::processMetaObjectList() {
    int i;
    int fieldWords;
    bool hasFields;
    MetaTableRecord *records;
    MetaTableRecord *record;
    char *name;
    int stride;
    _metaObjectListInFile = igSmartPointer< ::igMetaObjectList>((::igMetaObjectList *)igMetaObjectList_Create((int)_temporaryMemoryPool.p));
    ::setCapacity((::igTDataList< ::igObject *> *)_metaObjectListInFile.p, _metaObjectCount);
    igSmartPointer<igShortListData> slotShifts;
    if (_magicVersion < 4) {
        stride = 3;
        fieldWords = 0;
        hasFields = false;
    } else {
        fieldWords = 3;
        hasFields = true;
        stride = 6;
        _metaFieldPerObjectIndices = igSmartPointer< ::igShortListList>((::igShortListList *)igShortListList_Create((igMemoryPoolView *)_temporaryMemoryPool.p));
        ::setCapacity((::igTDataList<igShortListData *> *)_metaFieldPerObjectIndices.p, _metaObjectCount);
        {
            igMemoryPoolView *pool = (igMemoryPoolView *)_temporaryMemoryPool.p;
            slotShifts.release();
            slotShifts.p = igShortList_Create(pool);
        }
        ::setCapacity(slotShifts.p, _metaObjectCount);
    }
    if (_endianSwap != 0) {
        imf->endianSwapMemory(_metaObjectBuffer, stride * _metaObjectCount);
    }
    records = (MetaTableRecord *)_metaObjectBuffer;
    record = records;
    name = (char *)((int *)record + stride * _metaObjectCount);
    for (i = 0; i < _metaObjectCount; i++) {
        igMetaObject *meta = (igMetaObject *)igObjectSystem_FindMetaByNameDefault(name);
        if (meta != 0) {
            int majorVersion = record->majorVersion;
            if (majorVersion == 0) {
                majorVersion = 1;
            }
            if (majorVersion == meta->_majorVersion && record->minorVersion == meta->_minorVersion) {
                ((igObjectList *)_metaObjectListInFile.p)->append((igObject *)meta);
                if (hasFields) {
                    igSmartPointer<igShortListData> slots(igShortList_Create((igMemoryPoolView *)_temporaryMemoryPool.p));
                    MetaTableField *field;
                    int j;
                    ::setCapacity(slots.p, record->fieldCount);
                    ((igObjectList *)_metaFieldPerObjectIndices.p)->append((igObject *)slots.p);
                    field = (MetaTableField *)(name + record->nameSize);
                    j = 0;
                    if (_endianSwap != 0) {
                        igShortMetaField::getMetaField()->endianSwapMemory(field, fieldWords * record->fieldCount);
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
        } else if (hasFields && gBlindObjectEnabled != 0) {
            int parentIndex = record->parentIndex;
            MetaTableRecord *parentRecord = (MetaTableRecord *)((int *)records + parentIndex * stride);
            igMetaObject *parent = ((igMetaObject **)_metaObjectListInFile->_data)[parentIndex];
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
            blind = (igMetaObject *)igMetaObject_Create((igMemoryPoolView *)Memory_GetDefaultAllocator());
            igMetaObject_SetName(blind, (int)name);
            igMetaObject_InheritFromBase(blind, parent);
            ((igObjectList *)_metaObjectListInFile.p)->append((igObject *)blind);
            field = (MetaTableField *)(name + record->nameSize);
            if (_endianSwap != 0) {
                igShortMetaField::getMetaField()->endianSwapMemory(field, fieldWords * record->fieldCount);
            }
            for (j = 0; j < record->fieldCount; j++) {
                ::igMetaField *created;
                if (field->slot < parentRecord->persistCount) {
                    field = (MetaTableField *)((short *)field + fieldWords);
                    continue;
                }
                target = field->slot + (*slotShifts.p)[parentIndex] - inherited;
                while (slot < target) {
                    created = (::igMetaField *)igCharMetaField_Create((igMemoryPoolView *)_temporaryMemoryPool.p);
                    created->_persistent = 0;
                    ((igMetaField *)created)->setBasicProperties("fakeField", 0, -1, blind);
                    created->_internalIndex = slot;
                    created->_size = 1;
                    appendAlignedField(blind, created);
                    slot++;
                    blind->_sizeofSize = fieldOffset(created) + fieldSize(created);
                }
                created = (::igMetaField *)igMetaObject_CreateInstance(
                    ((igObjectDispatchView **)_metaFieldListInFile->_data)[field->typeIndex]->GetMeta(), (igMemoryPoolView *)Memory_GetDefaultAllocator());
                ((igMetaField *)created)->setBasicProperties("Generated", 0, -1, blind);
                created->_internalIndex = target;
                created->_size = field->size;
                appendAlignedField(blind, created);
                slot++;
                field = (MetaTableField *)((short *)field + fieldWords);
                blind->_sizeofSize = fieldOffset(created) + fieldSize(created);
            }
            blind->_sizeofSize = (blind->_sizeofSize + blind->_requiredAlignment - 1) & ~(blind->_requiredAlignment - 1);
            blind->_validity |= 4;
            igObjectSystem_AppendMetaObject(g_objectSystem, blind);
            igObjectSystem_RunRegistrationCallbacks((int *)g_objectSystem, (int)blind);
            field = (MetaTableField *)(name + record->nameSize);
            {
                igSmartPointer<igShortListData> slots(igShortList_Create((igMemoryPoolView *)_temporaryMemoryPool.p));
                ((igObjectList *)_metaFieldPerObjectIndices.p)->append((igObject *)slots.p);
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
    _metaObjectBuffer = 0;
    return g_resultSuccess;
}

/* The directory the file is in: its name up to the last path separator, or empty. */
igResult igIGBFile::setupFilePaths() {
    int n;
    char *p;
    char c;
    _basePath = (char *)((igMemoryPoolView *)_temporaryMemoryPool.p)->StrDup(_file->_fileName.p);
    n = strlen(_basePath);
    while (--n >= 0) {
        p = _basePath + n;
        c = *p;
        if (c == 0x2F || c == 0x5C) {
            *p = 0;
            break;
        }
    }
    if (n < 0) {
        *_basePath = 0;
    }
    return g_resultSuccess;
}

void igIGBFile::userRegister() {
    ((igRegistry *)g_objectSystem->configRegistry)->getValue(2, "blindObjects", gBlindObjectEnabled, 0, 0);
}

/* Moves the chunk's unread bytes to its start and fills the rest from the file, as far as the section goes. */
igResult igIGBFile::readNextObjectChunk() {
    int remaining;
    int size;
    remaining = (_chunkSize - _chunkPlace) % _chunkSize;
    if (remaining > 0) {
        memcpy(_chunk, _chunk + _chunkPlace, remaining);
    }
    size = _chunkSize - remaining;
    if (_bufferSize < remaining + (_bufferPlace + size)) {
        size = (_bufferSize - _bufferPlace) - remaining;
    }
    if (_file->fread(_chunk + remaining, size, 1) != 1) {
        return g_resultFailure;
    } else {
        _chunkPlace = 0;
        return g_resultSuccess;
    }
}
}
}

static inline igObject *castToKind(igObject *object) {
    if (object != 0 && ((Gap::Core::igObject *)object)->isOfType((igMetaObject *)Gap::Core::igDirEntry::getClassMeta()) != 0) {
        return object;
    }
    return 0;
}

namespace Gap {
namespace Core {

/* Creates the next entry of the object section and reads its fields, reading the next chunk when the record
 * does not fit the one in memory. */
igSmartPointer<igDirEntry> igIGBFile::readNextDirEntry() {
    int metaIndex;
    int *record;
    char *end = _chunk + _chunkPlace;
    int position = _chunkPlace;
    int needed;
    if (position > _chunkSize - 9 || (needed = _version1CruftMultiply * 4 + (_chunkPlace + getReadSizeFromMemory(end)), _chunkSize < needed)) {
        if (readNextObjectChunk() == g_resultFailure) {
            return igSmartPointer<igDirEntry>((igDirEntry *)0, kRetainReference);
        }
    }
    record = (int *)(_chunk + _chunkPlace);
    metaIndex = *record;
    if (_endianSwap != 0) {
        igIntMetaField::getMetaField()->endianSwapMemory(&metaIndex, 1);
    }
    igSmartPointer< ::igObject> object(castToKind((::igObject *)igMetaObject_CreateInstanceWithPool(((igMetaObject **)_metaObjectListInFile->_data)[metaIndex], (igMemoryPoolView *)_temporaryMemoryPool.p)), kRetainReference);
    object->release();
    igObject_RegisterInstance((void **)object.p, 0);
    int read;
    if (_magicVersion < 4) {
        read = igObject_ReadFields((igObjectDispatchView *)object.p, (FieldRecordHead *)record, this, (::igTDataList<igMetaObject *> *)_metaObjectListInFile.p, _endianSwap);
    } else {
        read = igObject_ReadPersistentFields((igObjectDispatchView *)object.p, (FieldRecordHead *)record, this, (::igTDataList<igMetaObject *> *)_metaObjectListInFile.p, _endianSwap);
    }
    _chunkPlace = _chunkPlace + read;
    _bufferPlace = _bufferPlace + read;
    _chunkPlace = _chunkPlace + _version1CruftMultiply * 4;
    _bufferPlace = _bufferPlace + _version1CruftMultiply * 4;
    return object;
}

/* Reads the shared entries into a new _uniqueEntryList. */
igResult igIGBFile::readReadSharedEntries() {
    int i;
    _chunkPlace = _chunkSize;
    _bufferPlace = 0;
    _bufferSize = _entryBufferSize;
    {
        igDirectory *previous = _uniqueEntryList;
        igMemoryPoolView *pool = (igMemoryPoolView *)_temporaryMemoryPool.p;
        igObject::release(previous);
        _uniqueEntryList.p = igDirectory::_instantiateFromPool(pool);
    }
    _uniqueEntryList->setCount(_entryCount);
    if (readNextObjectChunk() == g_resultFailure) {
        return g_resultFailure;
    }
    for (i = 0; i < _entryCount; i++) {
        igSmartPointer<igDirEntry> entry = readNextDirEntry();
        if (entry == 0) {
            return g_resultFailure;
        }
        if (_useMemoryPoolAssignmentsState != 0 && _memoryPoolHandles != 0 && g_useOwnerAllocator == 0) {
            int handle = entry->getMemoryPoolHandle();
            if (handle > 0) {
                entry->setMemoryPoolHandle(_memoryPoolHandles->get(handle));
            }
        } else {
            entry->setMemoryPoolHandle(-1);
        }
        _uniqueEntryList->set(i, entry);
    }
    if (_hasCriticalFailure != 0) {
        return g_resultFailure;
    }
    return g_resultSuccess;
}

/* Reads the entry index table: each entry is the shared entry its index names. */
igResult igIGBFile::readReadSharedIndexes() {
    int count = 0;
    int pos;
    int chunk;
    int words;
    int i;
    int base;
    _file->fread(&_indexBufferSize, 4, 1);
    _file->fread(&count, 4, 1);
    if (_endianSwap != 0) {
        imf->endianSwapMemory(&_indexBufferSize, 1);
        imf->endianSwapMemory(&count, 1);
    }
    if (allocateReadChunkBuffer(0x1000) == g_resultFailure) {
        return g_resultFailure;
    }
    pos = 8;
    setCount(count);
    for (; pos < _indexBufferSize; pos += chunk) {
        int rest = _indexBufferSize - pos;
        chunk = _chunkSize & ~1;
        if (chunk > rest) { chunk = rest; }
        words = chunk >> 1;
        _file->fread(_chunk, chunk, 1);
        if (_endianSwap != 0) { smf->endianSwapMemory(_chunk, words); }
        base = (unsigned int)(pos - 8) >> 1;
        for (i = 0; i < words; i++) {
            set(i + base, (igDirEntry *)igDirectory_GetEntryAlias((int *)_uniqueEntryList.p, ((short *)_chunk)[i]));
        }
    }
    return g_resultSuccess;
}

igResult igIGBFile::readProcessSharedDirectory() {
    int count;
    int i;
    {
        igPointerList *previous = _refList;
        int pool;
        count = _count;
        pool = (int)_temporaryMemoryPool.p;
        igObject::release(previous);
        _refList.p = (igPointerList *)igPointerList_Create(pool);
    }
    _refList->setCount(count);
    for (i = 0; i < count; i++) {
        get(i)->readSetup(this);
    }
    return g_resultSuccess;
}

/* Reads the entries in file order; a file with sharing on shares each with the ones before it as it goes. */
igResult igIGBFile::readProcessDirectory() {
    int i;
    _chunkPlace = _chunkSize;
    _bufferPlace = 0;
    _bufferSize = _entryBufferSize;
    if (_sharingState != 0) {
        {
            igPointerList *previous = _refList;
            int pool = (int)_temporaryMemoryPool.p;
            igObject::release(previous);
            _refList.p = (igPointerList *)igPointerList_Create(pool);
        }
        _refList->setCount(_entryCount);
        {
            igObjectList *previous = _entryPool;
            igMemoryPoolView *pool = (igMemoryPoolView *)_temporaryMemoryPool.p;
            igObject::release(previous);
            _entryPool.p = igObjectList::_instantiateFromPool(pool);
        }
    }
    if (readNextObjectChunk() == g_resultFailure) {
        return g_resultFailure;
    }
    setCount(_entryCount);
    for (i = 0; i < _entryCount; i++) {
        igSmartPointer<igDirEntry> entry = readNextDirEntry();
        if (entry == 0) {
            return g_resultFailure;
        }
        entry->_index = i;
        set(i, entry);
        if (_useMemoryPoolAssignmentsState != 0 && _memoryPoolHandles != 0 && g_useOwnerAllocator == 0) {
            int handle = entry->getMemoryPoolHandle();
            if (handle > 0) {
                entry->setMemoryPoolHandle(_memoryPoolHandles->get(handle));
            }
        } else {
            entry->setMemoryPoolHandle(-1);
        }
        entry->readSetup(this);
        if (_sharingState != 0) {
            _refList->set(i, entry->getRef());
            entry->refEntry(entry->getRef());
            entry->setRef(0);
            entry->_index = i;
            set(i, entry->share(this));
        }
    }
    if (_hasCriticalFailure != 0) {
        return g_resultFailure;
    }
    return g_resultSuccess;
}

const char *igIGBFile::getObjectBufferPlace() const
{
    if (_file->_openMode == igFile::kReadBinary) {
        return _chunk + _chunkPlace;
    }
    return _objectBufferPlace;
}

void igIGBFile::setObjectBufferPlace(char *objectBufferPlaceParam)
{
    if (_file->_openMode == igFile::kReadBinary) {
        char *previous = _chunk + _chunkPlace;
        _chunkPlace = objectBufferPlaceParam - _chunk;
        _bufferPlace = _bufferPlace + (objectBufferPlaceParam - previous);
        if (_bufferPlace != _bufferSize) {
            if (_chunkPlace > _chunkSize - 9) {
                readNextObjectChunk();
                return;
            }
            if (_chunkPlace + (_version1CruftMultiply * 4 + getReadSizeFromMemory((void *)objectBufferPlaceParam)) > _chunkSize) {
                readNextObjectChunk();
            }
        }
    } else {
        _objectBufferPlace = objectBufferPlaceParam;
    }
}

igResult igIGBFile::freeFilePaths() {
    ((igMemoryPoolView *)_temporaryMemoryPool.p)->Free(_basePath);
    _basePath = 0;
    return g_resultSuccess;
}

/* Maps the file's metafield types, by name, to this program's registered ones (0 for a type it lacks). */
igResult igIGBFile::readMetaFieldList() {
    __internalObjectList *table;
    int count;
    int *sizes;
    char *name;
    int i;
    if (allocateReadChunkBuffer(_metaFieldBufferSize) == g_resultFailure) {
        return g_resultFailure;
    }
    _mfBuf = _chunk;
    _file->fread(_mfBuf, _metaFieldBufferSize, 1);
    table = igMetaField::getMetaFieldTypes();
    count = table->_count;
    sizes = (int *)_mfBuf;
    name = (char *)sizes + _metaFieldCount * 12;
    if (_endianSwap != 0) { imf->endianSwapMemory(sizes, _metaFieldCount * 3); }
    _metaFieldListInFile = (::igMetaFieldList *)igMetaFieldList_Create((int)_temporaryMemoryPool.p);
    ::setCapacity((::igTDataList< ::igObject *> *)_metaFieldListInFile.p, _metaFieldCount);
    for (i = 0; i < _metaFieldCount; i++) {
        bool found = false;
        igObjectDispatchView *type = 0;
        int j;
        for (j = 0; j < count; j++) {
            type = registeredMetaField(table, j);
            if (strcmp((const char *)type->GetMeta()->_name, name) == 0) { found = true; break; }
        }
        if (!found) { type = 0; } else { type->GetMeta(); }
        ((igObjectList *)_metaFieldListInFile.p)->append((igObject *)type);
        name += sizes[i * 3];
    }
    _mfBuf = 0;
    return g_resultSuccess;
}
}
}

static inline void releasePool(igObject *object) {
    igObject::release(object);
}

namespace Gap {
namespace Core {

void igIGBFile::resetFields(int flag)
{
    setTemporaryMemoryPool((::igMemoryPool *)Memory_GetDefaultAllocator());
    setDataMemoryPool((::igMemoryPool *)Memory_GetDefaultAllocator());
    setObjectMemoryPool((::igMemoryPool *)Memory_GetDefaultAllocator());
}
}
}

static inline void addType(igTDataList<int> *l, int v) {
    int idx;
    idx = l->_count;
    if (l->_capacity > idx) { l->_count = l->getCount() + 1; } else { ((Gap::Core::igDataList *)l)->resizeAndSetCount(idx + 1, 4); }
    l->_data[idx] = v;
}

namespace Gap {
namespace Core {

/* Maps the file's alignment names to the global resource's alignments (16 for a name it lacks). */
igResult igIGBFile::readAlignmentList() {
    IgbSectionHeader header;
    int *sizes;
    char *name;
    int value;
    int nameCount;
    int i;
    if (_file->fread(&header, 12, 1) != 1) { return g_resultFailure; }
    if (_endianSwap != 0) { imf->endianSwapMemory(&header, 3); }
    _alignmentBufferSize = header.size - 12;
    _alignmentCount = header.count;
    if (_alignmentCount <= 0) { return g_resultSuccess; }
    _alignmentBuffer = _chunk;
    if (_file->fread(_alignmentBuffer, _alignmentBufferSize, 1) != 1) { return g_resultFailure; }
    sizes = (int *)_alignmentBuffer;
    if (_endianSwap != 0) { imf->endianSwapMemory(sizes, _alignmentCount); }
    name = (char *)sizes + _alignmentCount * 4;
    {
    igSmartPointer< ::igTDataList< ::igStringObj *> > names((::igTDataList< ::igStringObj *> *)g_globalContext->_alignmentStrings.p, kRetainReference);
    igSmartPointer< ::igTDataList<int> > values((::igTDataList<int> *)g_globalContext->_alignmentValues.p, kRetainReference);
    nameCount = 0;
    if (names.p != 0) { nameCount = names.p->_count; }
    _alignmentListInFile = igSmartPointer<igIntList>((igIntList *)igIntList_Create((int)_temporaryMemoryPool.p));
    ::setCapacity((::igTDataList<int> *)_alignmentListInFile.p, _alignmentCount);
    for (i = 0; i < _alignmentCount; i++) {
        bool found = false;
        value = 16;
        int j;
        for (j = 0; j < nameCount; j++) {
            char *n = (char *)names.p->_data[j]->_buffer;
            n = (n == 0) ? (g_stringObjEmptyText) : n;
            if (strcmp(n, name) == 0) { found = true; break; }
        }
        if (found) { value = values.p->_data[j]; }
        addType((::igTDataList<int> *)_alignmentListInFile.p, value);
        name += sizes[i];
    }
    _alignmentBuffer = 0;
    return g_resultSuccess;
    }
}

/* Reads the object section: each object entry creates its object, then reads its fields. */
igResult igIGBFile::readProcessObjectEntries() {
    int n;
    int i;

    _objectBufferPlace = _objBuf;
    _chunkPlace = _chunkSize;
    _bufferPlace = 0;
    _bufferSize = _objectBufferSize;
    if (readNextObjectChunk() == g_resultFailure) {
        return g_resultFailure;
    }
    n = _count;
    for (i = 0; i < n; i++) {
        if (getNonShared(i)->isOfType(igObjectDirEntry::getClassMeta()) != 0) {
            get(i)->readPreRead(this);
        }
    }
    if (_magicVersion < 4) {
        for (i = 0; i < n; i++) {
            if (getNonShared(i)->isOfType(igObjectDirEntry::getClassMeta()) != 0) {
                get(i)->readReadVersion3(this);
            }
        }
    } else {
        for (i = 0; i < n; i++) {
            if (getNonShared(i)->isOfType(igObjectDirEntry::getClassMeta()) != 0) {
                igSmartPointer<igDirEntry> entry(get(i), kRetainReference);
                entry->readRead(this);
            }
        }
    }
    return g_resultSuccess;
}

/* The same passes over the other entries, which read the memory blocks. */
igResult igIGBFile::readProcessAllOtherEntries() {
    int i;
    for (i = 0; i < _count; i++) {
        if (((getNonShared(i)->isOfType(igObjectDirEntry::getClassMeta()) != 0) ^ 1) != 0) {
            get(i)->readPreRead(this);
        }
    }
    if (_magicVersion < 4) {
        for (i = 0; i < _count; i++) {
            if (((getNonShared(i)->isOfType(igObjectDirEntry::getClassMeta()) != 0) ^ 1) != 0) {
                get(i)->readReadVersion3(this);
            }
        }
    } else {
        for (i = 0; i < _count; i++) {
            if (((getNonShared(i)->isOfType(igObjectDirEntry::getClassMeta()) != 0) ^ 1) != 0) {
                get(i)->readRead(this);
            }
        }
    }
    return g_resultSuccess;
}

void igIGBFile::readClose() {
    if (_autoOpened > 0) {
        close();
    }
}

void igIGBFile::releaseAllBuffers() {
    _metaFieldListInFile.release();
    _metaFieldListInFile = 0;
    _metaObjectListInFile = 0;
    _metaFieldPerObjectIndices = 0;
    _metaObjectBuffer = 0;
    _dirBuf = 0;
    _mfBuf = 0;
    _objBuf = 0;
    _entryPool = 0;
    _indexBuffer = 0;
    _uniqueEntryList = 0;
    ((igMemoryPoolView *)_temporaryMemoryPool.p)->Free(_chunk);
    _chunk = 0;
    _memoryPoolNameBufferSize = 0;
    char *poolNames = _memoryPoolNameBuffer;
    if (poolNames != 0) {
        ((igMemoryPoolView *)_temporaryMemoryPool.p)->Free(poolNames);
        _memoryPoolNameBuffer = 0;
    }
    _memoryPoolHandles = 0;
}

void igIGBFile::destructFields()
{
    if (_refList != 0) {
        for (int i = 0, count = _refList->getCount(); i < count; i++) {
            getNonShared(i)->releaseEntry(_refList->get(i));
        }
        _refList = 0;
    }
    _refList = 0;
    igObject::destructFields();
}

/* Reads the info list's entry index and takes the list from that entry. */
igResult igIGBFile::readInfoIndex() {
    if (_hasInfo != 0) {
        if (_file->fread((char *)this + k_infoListPlace->_offset, 4, 1) != 1) {
            return g_resultFailure;
        }
        if (_endianSwap != 0) {
            imf->endianSwapMemory((char *)this + k_infoListPlace->_offset, 1);
        }
        _infoList = (igInfoList *)get(_infoListPlace)->getRef();
    }
    return g_resultSuccess;
}
}
}

static inline void *stringPool() {
    if (((*(void * *)&g_stringPool)) == 0) {
        void *p = StringPool_Allocate(16);
        if (p != 0) { p = ((void *)StringPool_Construct((StringPool *)p)); }
        ((*(void * *)&g_stringPool)) = p;
    }
    return ((*(void * *)&g_stringPool));
}

static inline void setPooled(char **dst, char *src) {
    char *v = ((char *)StringPool_Intern((StringPool *)(stringPool()), src));
    char *old = *dst;
    if (old != 0) {
        StringTokenHeader *h = (StringTokenHeader *)(old - 8);
        int n = h->refCount - 1;
        h->refCount = n;
        if (n == 0) { StringChunk_ReleaseHeader((StringChunk *)h->owner, (StringTokenHeader *)h); }
    }
    *dst = v;
}

namespace Gap {
namespace Core {

/* Loads each external directory through the managing resource, with the resource's relative path set to
 * this file's directory meanwhile. */
igResult igIGBFile::readAndResolveExternalDirectories() {
    if (_hasExternal != 0) {
        IgbSectionHeader header;
        int count;
        int *sizes;
        char *name;
        int i;
        igResource *resource;
        if (_file->fread(&header, 12, 1) != 1) { return g_resultFailure; }
        if (_endianSwap != 0) { imf->endianSwapMemory(&header, 3); }
        _externalDirectoryBufferSize = header.size - 12;
        count = header.count;
        _externalDirectoryBuffer = (char *)((igMemoryPoolView *)_temporaryMemoryPool.p)->AllocateAligned(_externalDirectoryBufferSize, 16);
        if (_file->fread(_externalDirectoryBuffer, _externalDirectoryBufferSize, 1) != 1) { return g_resultFailure; }
        sizes = (int *)_externalDirectoryBuffer;
        if (_endianSwap != 0) { imf->endianSwapMemory(sizes, count); }
        name = (char *)sizes + count * 4;
        if (_managingResource == 0) { _managingResource = igResource::getGlobalResource(); }
        if (_managingResource != 0) {
            _previousResourceFilePath = _managingResource->_relativeFilePath.p;
            _managingResource->setRelativeFilePath(_basePath);
        }
        for (i = 0; i < count; i++) {
            _externalDirectoryList->append(_managingResource->loadSynchronous(name));
            name += sizes[i];
        }
        ((igMemoryPoolView *)_temporaryMemoryPool.p)->Free(_externalDirectoryBuffer);
        _externalDirectoryBuffer = 0;
        resource = _managingResource;
        if (resource != 0) {
            resource->setRelativeFilePath(_previousResourceFilePath.p);
            _previousResourceFilePath = (const char *)0;
        }
    }
    return g_resultSuccess;
}
}
}

static inline void addName(igTDataList<int> *l, const int &v) {
    int idx = l->_count;
    if (l->_capacity > idx) { l->_count = l->getCount() + 1; } else { ((Gap::Core::igDataList *)l)->resizeAndSetCount(idx + 1, 4); }
    l->_data[idx] = v;
}

int g_igIGBFile_memoryPoolHandleFill = -1;

namespace Gap {
namespace Core {

/* Maps the file's memory pool names to this program's pools; the pools the file does not name keep the
 * default handle. */
igResult igIGBFile::readMemoryPoolNames() {
    NameHeader header;
    char *buffer;
    char *name;
    int i;
    if (_file->fread(&header, 8, 1) != 1) { return g_resultFailure; }
    if (_endianSwap != 0) { imf->endianSwapMemory(&header, 2); }
    buffer = (char *)((igMemoryPoolView *)_temporaryMemoryPool.p)->Allocate(header.size);
    if (buffer == 0) { return g_resultFailure; }
    if (_file->fread(buffer, header.size - 8, 1) != 1) { ((igMemoryPoolView *)_temporaryMemoryPool.p)->Free(buffer); return g_resultFailure; }
    if (_memoryPoolHandles != 0) {
        _memoryPoolHandles->_count = 0;
    } else {
        igIntList *previous = _memoryPoolHandles;
        igMemoryPoolView *pool = (igMemoryPoolView *)_temporaryMemoryPool.p;
        igObject::release(previous);
        _memoryPoolHandles.p = (igIntList *)igIntList_Create((int)pool);
    }
    name = buffer;
    i = 0;
    while (header.count-- > 0) {
        addName((::igTDataList<int> *)_memoryPoolHandles.p, igMemoryPoolContextInfo_GetMemoryPoolHandle((int)name));
        { int length = strlen(name) + 1; i++; name += length; }
    }
    for (; i < 46; i++) {
        /* matching construct: declaration-order search — the count declared before the list keeps retail's registers */
        int count;
        ::igTDataList<int> *handles;
        handles = (::igTDataList<int> *)_memoryPoolHandles.p;
        count = handles->_count;
        if (handles->_capacity > count) { handles->_count = handles->getCount() + 1; } else { ((igDataList *)handles)->resizeAndSetCount(count + 1, 4); }
        handles->_data[count] = g_igIGBFile_memoryPoolHandleFill;
    }
    ((igMemoryPoolView *)_temporaryMemoryPool.p)->Free(buffer);
    return g_resultSuccess;
}

int igIGBFile::readErrorCleanup() {
    releaseAllBuffers();
    _loadPendingState = 0;
    _validState = 0;
    readClose();
    return -1;
}

/* Registers the entries' objects, making them concrete the first time. */
igResult igIGBFile::readFinishConstruction() {
    int i;
    int n;
    bool makeConcrete;
    i = 0;
    n = _count;
    makeConcrete = !_concreteState;
    while (i < n) {
        get(i)->readFinishConstruction(makeConcrete);
        i += 1;
    }
    if (makeConcrete) {
        _concreteState = 1;
    }
    return g_resultSuccess;
}

igResult igIGBFile::postReadEntryProcessing() {
    int i;
    for (i = 0; i < _count; i++) {
        get(i)->readPostRead(this);
    }
    return g_resultSuccess;
}
}
}

unsigned char g_igIGBFile_oldVersionErrorSuppressed;
unsigned char g_igIGBFile_loadTimeReportSuppressed;
char g_igIGBFile_readFileLabel[256];

namespace Gap {
namespace Core {

/* Reads the file's sections in file order (the version decides which tables come first); a step that fails
 * ends the read through readErrorCleanup. */
int igIGBFile::readFile(const char *path) {
    double startTime;
    sprintf(g_igIGBFile_readFileLabel, "readFile(%s)", path);
    startTime = g_igIGBFile_loadTimer->GetElapsedSeconds();
    _validState = 0;
    _loadPendingState = 1;
    _concreteState = 0;
    if (readOpen(path).failed()) return readErrorCleanup();
    if (readHeader().failed()) return readErrorCleanup();
    if (_magicVersion < 5 && _hasExternal) {
        if (!g_igIGBFile_oldVersionErrorSuppressed) {
            int answer = igReportError("igIGBFile::readFile(%s) - unable to read this oldversion of igb file format with external references.Run igbUpdate %s on this file (or re-export) to fix.", _file->_fileName.p, _file->_fileName.p);
            if (answer != 1 && answer == 2) g_igIGBFile_oldVersionErrorSuppressed = 1;
        }
        return readErrorCleanup();
    }
    if (_magicVersion >= 3) {
        if (readMetaFieldList().failed()) return readErrorCleanup();
        if (readAlignmentList().failed()) return readErrorCleanup();
    }
    if (readMetaObjectBuffer().failed()) return readErrorCleanup();
    if (processMetaObjectList().failed()) return readErrorCleanup();
    if (setupFilePaths().failed()) return readErrorCleanup();
    if (_magicVersion >= 5) {
        if (readAndResolveExternalDirectories().failed()) return readErrorCleanup();
    }
    if (_hasMemoryPoolNames) {
        if (readMemoryPoolNames().failed()) return readErrorCleanup();
    }
    if (_sharedEntries) {
        if (readReadSharedEntries().failed()) return readErrorCleanup();
        if (readReadSharedIndexes().failed()) return readErrorCleanup();
        if (readProcessSharedDirectory().failed()) return readErrorCleanup();
    } else {
        if (readProcessDirectory().failed()) return readErrorCleanup();
    }
    if (_magicVersion >= 5) {
        if (readInfoIndex().failed()) return readErrorCleanup();
    }
    if (readProcessObjectEntries().failed()) return readErrorCleanup();
    if (readMemoryRefBuffer().failed()) return readErrorCleanup();
    if (_magicVersion < 3) {
        if (readMetaFieldList().failed()) return readErrorCleanup();
    }
    if (_magicVersion < 5) {
        if (readInfoIndex().failed()) return readErrorCleanup();
    }
    if (_magicVersion < 5) {
        if (readAndResolveExternalDirectories().failed()) return readErrorCleanup();
    }
    if (readProcessAllOtherEntries().failed()) return readErrorCleanup();
    if (freeFilePaths().failed()) return readErrorCleanup();
    readFinishConstruction();
    if (_autoReadFilePostProcessState == 1) {
        if (readFilePostProcess().failed()) return readErrorCleanup();
    }
    readClose();
    releaseAllBuffers();
    _validState = 1;
    _loadPendingState = 0;
    if (!g_igIGBFile_loadTimeReportSuppressed) {
        int answer = igReport_Detail("Total Time to load %s - %f seconds", path, g_igIGBFile_loadTimer->GetElapsedSeconds() - startTime);
        if (answer != 1 && answer == 2) g_igIGBFile_loadTimeReportSuppressed = 1;
    }
    return _count;
}

igResult igIGBFile::ensureConcrete()
{
    if (_concreteState == 0) {
        makeAllConcrete();
    }
    return g_resultSuccess;
}

igResult igIGBFile::readFilePostProcess()
{
    if (_readFilePostProcessedState == 0) {
        igResult postProcessed = postReadEntryProcessing();
        if (_managingResource != 0) {
            _managingResource->makeCompatible(_name.p);
        }
        _readFilePostProcessedState = 1;
        return postProcessed;
    }
    return g_resultSuccess;
}

/* The external directory as an IGB file, or 0. */
static inline igIGBFile *asIGBFile(igDirectory *directory)
{
    if (directory != 0 && directory->isOfType(igIGBFile::getClassMeta()) != 0) {
        return (igIGBFile *)directory;
    }
    return 0;
}

/* Checks each external file, then this file's own post-read step. */
igResult igIGBFile::readFilePostProcessRecursive()
{
    igResult result = g_resultSuccess;
    int i;
    for (i = 0; i < _externalDirectoryList->_count; i++) {
        igSmartPointer<igIGBFile> file(asIGBFile(_externalDirectoryList->get(i)), kRetainReference);
        if (file != 0) {
            if (file->readFilePostProcessRecursive() == g_resultFailure) {
                result = g_resultFailure;
            }
        }
    }
    if (readFilePostProcess() == g_resultFailure) {
        result = g_resultFailure;
    }
    return result;
}

int igIGBFile::writeMemoryRefBuffer()
{
    int i;
    _chunkSize = _forceChunkSize;
    if (_chunkSize < 0) {
        _chunkSize = _file->_optimalWriteChunkSize;
    }
    if (_memoryRefBufferSize < _chunkSize) {
        _chunkSize = _memoryRefBufferSize;
    }
    _chunk = (char *)((igMemoryPoolView *)_temporaryMemoryPool.p)->AllocateAligned(_chunkSize, _file->_pageSize);
    _memoryBufferPlace = 0;
    _memoryBytesCopied = 0;
    _bytesRemainingInChunk = _chunkSize;
    for (i = 0; i < _count; i++) {
        get(i)->writeMemorySpecial(this);
    }
    ((igMemoryPoolView *)_temporaryMemoryPool.p)->Free(_chunk);
    _chunk = 0;
    return 1;
}

/* Makes the chunk buffer hold at least `minChunkBufferSize` bytes: the forced chunk size, else the file's
 * optimal read size, rounded up to a word. */
igResult igIGBFile::allocateReadChunkBuffer(int minChunkBufferSize) {
    char *chunk;
    chunk = _chunk;
    if (chunk != 0 && _chunkSize >= minChunkBufferSize) {
        return g_resultSuccess;
    } else {
        if (chunk != 0) {
            ((igMemoryPoolView *)_temporaryMemoryPool.p)->Free(chunk);
        }
        _chunkSize = _forceChunkSize;
        if (_chunkSize < 0) {
            _chunkSize = _file->_optimalReadChunkSize;
        }
        if (_chunkSize < minChunkBufferSize) {
            _chunkSize = minChunkBufferSize;
        }
        _chunkSize = (_chunkSize + 3) & ~3;
        _chunk = (char *)((igMemoryPoolView *)_temporaryMemoryPool.p)->AllocateAligned(_chunkSize, _file->_pageSize);
        if (_chunk == 0) {
            return g_resultFailure;
        } else {
            return g_resultSuccess;
        }
    }
}

igResult igIGBFile::readMemoryRefBuffer()
{
    int n;
    int i;
    _memoryBufferPlace = 0;
    _memoryBytesCopied = 0;
    _bytesRemainingInChunk = 0;
    n = _count;
    for (i = 0; i < n; i++) {
        get(i)->readMemorySpecial(this);
    }
    return g_resultSuccess;
}
}
}

