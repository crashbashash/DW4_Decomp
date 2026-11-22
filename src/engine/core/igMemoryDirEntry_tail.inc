namespace Gap {
namespace Core {

int igMemoryDirEntry::refNeedsEntryForPostFileReadCleanup()
{
    return ((igObject *)_memType)->isOfType((igMetaObject *)igRefMetaField::getClassMeta());
}

void igMemoryDirEntry::readSetup(igIGBFile *file) {
    ::igObjectList *fields = (::igObjectList *)file->_metaFieldListInFile;
    int align = 16;
    igSmartPointer< ::igIntList> alignments((::igIntList *)file->_alignmentListInFile, kRetainReference);
    igMemoryPoolView *pool;

    if (0 <= _alignmentTypeIndex) {
        align = ((int *)alignments->_data)[_alignmentTypeIndex];
    } else if (fields != 0) {
        if (0 <= _memTypeIndex) {
            _memType = ((int *)fields->_data)[_memTypeIndex];
            align = ((igMetaFieldView *)_memType)->GetAlignment();
        }
    }
    if ((_memoryPoolHandle == -1) || (_memoryPoolHandle == 1) || (_memoryPoolHandle == 2)) {
        pool = (igMemoryPoolView *)file->_dataMemoryPool;
    } else {
        pool = (igMemoryPoolView *)Memory_GetAllocatorBySelector(_memoryPoolHandle);
        if (pool == 0) {
            pool = (igMemoryPoolView *)file->_dataMemoryPool;
        }
    }
    if (align < 5) {
        ((igDirectory *)file)->setRef(_index, (void *)pool->Allocate(_memSize));
    } else {
        ((igDirectory *)file)->setRef(_index, (void *)pool->AllocateAligned(_memSize, align & 0xFFFF));
    }
}

void igMemoryDirEntry::writeMemorySpecial(igIGBFile *file) {
    int s4 = file->_chunkSize;
    int s3 = file->_memoryBufferPlace;
    int s6 = file->_memoryBytesCopied;
    int s2 = file->_bytesRemainingInChunk;
    int s8 = file->_chunk;
    int cnt = _memSize;
    igMetaFieldView *s1 = (igMetaFieldView *)_memType;
    int esz = ((::igMetaField *)s1)->_size;
    int per = cnt / esz;
    int s0, s7, i, src, j, dst, t0, t1, t2;
    if (((((Gap::Core::igObject *)s1)->isOfType((igMetaObject *)Gap::Core::igRefMetaField::getClassMeta()) != 0) ^ 1) && file->_endianSwap != 0) {
        s1->SwapBytes((void *)_ref, per);
    }
    s7 = 0;
    i = 0;
    src = _ref;
    while (i < cnt) {
        t0 = cnt - i;
        s0 = (t0 < s2) ? t0 : s2;
        if (((Gap::Core::igObject *)s1)->isOfType((igMetaObject *)Gap::Core::igRefMetaField::getClassMeta()) != 0) {
            int q = s0 / esz;
            t1 = per - s7;
            s7 = (t1 < q) ? t1 : q;
            dst = s8 + s3;
            for (j = 0; j < s7; j++) {
                s1->WriteRawFieldMem(src + j * esz, dst + j * esz, (int)file, file->_endianSwap);
            }
        } else {
            memcpy((void *)(s8 + s3), (void *)src, s0);
        }
        src += s0;
        s3 = (s3 + s0) % s4;
        s2 -= s0;
        i += s0;
        if (s2 == 0) {
            s6 += s4 * ((igFileView *)file->_file)->Write((void *)s8, s4, 1);
            t2 = file->_memoryRefBufferSize - s6;
            s2 = (t2 < s4) ? t2 : s4;
            s4 = s2;
        }
    }
    if (s4 != 0) {
        s0 = ((s3 + 3) & ~3) % s4;
        s2 = s2 - (s0 - s3);
        if (s0 < s3) {
            s6 += s4 * ((igFileView *)file->_file)->Write((void *)s8, s4, 1);
            t2 = file->_memoryRefBufferSize - s6;
            s2 = (t2 < s4) ? t2 : s4;
            s4 = s2;
        }
        if (((((Gap::Core::igObject *)s1)->isOfType((igMetaObject *)Gap::Core::igRefMetaField::getClassMeta()) != 0) ^ 1) && file->_endianSwap != 0) {
            s1->SwapBytes((void *)_ref, per);
        }
        file->_memoryBytesCopied = s6;
        file->_bytesRemainingInChunk = s2;
        file->_memoryBufferPlace = s0;
        file->_chunkSize = s4;
    }
}

/* igMemoryDirEntry slot 39: tally this memory block into the igIGBFile that is sizing its buffers.
 * Called once per directory entry by the file's sizing pass (igIGBFile_ComputeBufferSizes, which zeroes the four
 * counters first): the block count goes up by one and the memory buffer size by the block's
 * _memSize rounded up to a multiple of four, the same rounding the pool layout uses. */

void igMemoryDirEntry::writeComputeBufferSize(igIGBFile *file) {
    file->_memoryRefCount = file->_memoryRefCount + 1;
    file->_memoryRefBufferSize = file->_memoryRefBufferSize + ((_memSize + 3) & ~3);
}
}
}

static inline igObjectList *asEntryList(igObject *object) {
    if (object != 0 && ((Gap::Core::igObject *)object)->isOfType((igMetaObject *)Gap::Core::igObjectList::getClassMeta()) != 0) return (igObjectList *)object;
    return 0;
}

namespace Gap {
namespace Core {

igDirEntry *igMemoryDirEntry::share(igIGBFile *file) {
    igSmartPointer< ::igObjectList> lists((::igObjectList *)file->_entryPool, kRetainReference);
    if (lists.p == 0) return this;
    int index = ((igObjectDispatchView *)this)->GetMeta()->_index;
    if (lists->_count <= index) {
        ((igObjectList *)((::igTDataList< ::igObject *> *)lists.p))->setCount(index + 1);
        objectListSetRetained(index, 0, lists.p);
    }
    igSmartPointer< ::igObjectList> entries(asEntryList(((::igObject **)lists->_data)[index]), kRetainReference);
    if (entries.p == 0) {
        int pool = file->_temporaryMemoryPool;
        entries.release();
        entries.p = ((::igObjectList *)igObjectList::_instantiateFromPool((igMemoryPoolView *)pool));
        objectListSetRetained(index, entries.p, lists.p);
    }
    int i;
    int count = entries->_count;
    _index = -1;
    ::igObjectList *list = entries.p;
    for (i = 0; i < count; i++) {
        igMemoryDirEntry *entry = ((igMemoryDirEntry **)list->_data)[i];
        if (entry->_memTypeIndex == _memTypeIndex && entry->_memSize == _memSize &&
            entry->_refCounted == _refCounted && entry->_memoryPoolHandle == _memoryPoolHandle &&
            entry->_alignmentTypeIndex == _alignmentTypeIndex) {
            return entry;
        }
    }
    ((igObjectList *)list)->append(this);
    return this;
}

void igMemoryDirEntry::readMemorySpecial(igIGBFile *file) {
    int s6;
    int s8;
    char *s7;
    int s4;
    int s3;
    int s2;
    int s1;
    int base;
    int s0;
    int t;
    s6 = 0;
    s8 = _memSize;
    s7 = (char *)_ref;
    s4 = file->_chunkSize;
    s3 = file->_memoryBufferPlace;
    s2 = file->_memoryBytesCopied;
    s1 = file->_bytesRemainingInChunk;
    base = file->_chunk;
    while (s6 < s8) {
        if (s1 == 0) {
            t = file->_memoryRefBufferSize;
            if (t < s4 + s2) {
                s4 = t - s2;
            }
            s2 += s4 * ((igFileView *)file->_file)->Read((void *)base, s4, 1);
            s1 = s4;
        }
        s0 = s8 - s6;
        s0 = s0 < s1 ? s0 : s1;
        memcpy(s7, (void *)(base + s3), s0);
        s7 += s0;
        s1 -= s0;
        s6 += s0;
        s3 = (s3 + s0) % s4;
    }
    t = s3;
    if (s4 > 0) {
        s3 = ((s3 + 3) & ~3) % s4;
    }
    s1 = s1 - (s3 - t);
    if (s3 < t) s1 = 0;
    file->_chunkSize = s4;
    file->_memoryBufferPlace = s3;
    file->_memoryBytesCopied = s2;
    file->_bytesRemainingInChunk = s1;
}

void igMemoryDirEntry::readFinishConstruction(bool doMakeConcrete)
{

}

void igMemoryDirEntry::readReadVersion3(igIGBFile *igb)
{
    readRead(igb);
}

void igMemoryDirEntry::readRead(igIGBFile *igb) {
    igIGBFileView *r = (igIGBFileView *)igb;
    igMetaFieldView *f = ((igMetaFieldView **)r->_metaFieldListInFile->_data)[_memTypeIndex];
    _memType = (int)f;
    if (((((Gap::Core::igObject *)f)->isOfType((igMetaObject *)Gap::Core::igRefMetaField::getClassMeta()) != 0) ^ 1) && r->_endianSwap != 0) {
        f->SwapBytes((void *)_ref, _memSize / f->_size);
    }
    if (((Gap::Core::igObject *)f)->isOfType((igMetaObject *)Gap::Core::igRefMetaField::getClassMeta()) != 0) {
        int esize = f->_size;
        int count = _memSize / esize;
        int base = _ref;
        unsigned char saved = 0;
        int isSwap = ((Gap::Core::igObject *)f)->isOfType((igMetaObject *)Gap::Core::igObjectRefMetaField::getClassMeta()) & 0xff;
        int i;
        if (isSwap != 0) {
            saved = ((::igObjectRefMetaField *)f)->_refCounted;
            ((::igObjectRefMetaField *)f)->_refCounted = _refCounted;
        }
        for (i = 0; i < count; i++) {
            int p = base + i * esize;
            f->ReadRawFieldMem(p, p, (int)r, r->_endianSwap);
        }
        if (isSwap != 0) {
            ((::igObjectRefMetaField *)f)->_refCounted = saved;
        }
    }
}

/* Setter for the memory-pool handle (`_memoryPoolHandle`, +48). */

void igMemoryDirEntry::setMemoryPoolHandle(int memoryPoolHandle) {
    _memoryPoolHandle = memoryPoolHandle;
}

/* Accessor: the memory-pool handle this directory entry was allocated from (`_memoryPoolHandle`,
 * +48). */

int igMemoryDirEntry::getMemoryPoolHandle() {
    return _memoryPoolHandle;
}

void igMemoryFile::userRegister()
{
    _entryList = (::igMemoryFileEntryList *)igMemoryFileEntryList_Create(
        (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem));
}

::igMemoryFileEntryList *igMemoryFile::_entryList;

void igMemoryFile::userUnregister()
{
    ((::igObject *)_entryList)->release();
    _entryList = 0;
}
}
}

