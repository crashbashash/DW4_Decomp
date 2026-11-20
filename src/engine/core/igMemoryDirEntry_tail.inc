void igMemoryDirEntry_IsRefMemory(int entry) {
    ((Gap::Core::igObject *)(((igMemoryDirEntry *)entry)->_memType))->isOfType((igMetaObject *)(((int)Gap::Core::igRefMetaField::getClassMeta())));
}

void igMemoryDirEntry_AllocateMemory(igMemoryDirEntry *self, igIGBFile *file) {
    igObjectList *fields = (igObjectList *)file->_metaFieldListInFile;
    int align = 16;
    igSmartPointer<igIntList> alignments((igIntList *)file->_alignmentListInFile, kRetainReference);
    igMemoryPoolView *pool;

    if (0 <= self->_alignmentTypeIndex) {
        align = ((int *)alignments->_data)[self->_alignmentTypeIndex];
    } else if (fields != 0) {
        if (0 <= self->_memTypeIndex) {
            self->_memType = ((int *)fields->_data)[self->_memTypeIndex];
            align = ((igMetaFieldView *)self->_memType)->GetAlignment();
        }
    }
    if ((self->_memoryPoolHandle == -1) || (self->_memoryPoolHandle == 1) || (self->_memoryPoolHandle == 2)) {
        pool = (igMemoryPoolView *)file->_dataMemoryPool;
    } else {
        pool = (igMemoryPoolView *)Memory_GetAllocatorBySelector(self->_memoryPoolHandle);
        if (pool == 0) {
            pool = (igMemoryPoolView *)file->_dataMemoryPool;
        }
    }
    if (align < 5) {
        igDirectory_SetEntryRef((igDirectoryView *)file, self->_index, (int)pool->Allocate(self->_memSize));
    } else {
        igDirectory_SetEntryRef((igDirectoryView *)file, self->_index, (int)pool->AllocateAligned(self->_memSize, align & 0xFFFF));
    }
}

void igMemoryDirEntry_WriteMemory(igMemoryDirEntry *self, igIGBFile *file) {
    int s4 = file->_chunkSize;
    int s3 = file->_memoryBufferPlace;
    int s6 = file->_memoryBytesCopied;
    int s2 = file->_bytesRemainingInChunk;
    int s8 = file->_chunk;
    int cnt = self->_memSize;
    igMetaFieldView *s1 = (igMetaFieldView *)self->_memType;
    int esz = ((igMetaField *)s1)->_size;
    int per = cnt / esz;
    int s0, s7, i, src, j, dst, t0, t1, t2;
    if (((((Gap::Core::igObject *)s1)->isOfType((igMetaObject *)Gap::Core::igRefMetaField::getClassMeta()) != 0) ^ 1) && file->_endianSwap != 0) {
        s1->SwapBytes((void *)self->_ref, per);
    }
    s7 = 0;
    i = 0;
    src = self->_ref;
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
            s1->SwapBytes((void *)self->_ref, per);
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

void igMemoryDirEntry_AccumulateFileSize(igMemoryDirEntry *self, igIGBFile *file) {
    file->_memoryRefCount = file->_memoryRefCount + 1;
    file->_memoryRefBufferSize = file->_memoryRefBufferSize + ((self->_memSize + 3) & ~3);
}

static inline igObjectList *asEntryList(igObject *object) {
    if (object != 0 && ((Gap::Core::igObject *)object)->isOfType((igMetaObject *)g_igObjectList_metaObject) != 0) return (igObjectList *)object;
    return 0;
}

igMemoryDirEntry *igMemoryDirEntry_GetSharedEntry(igMemoryDirEntry *self, igIGBFile *file) {
    igSmartPointer<igObjectList> lists((igObjectList *)file->_entryPool, kRetainReference);
    if (lists.p == 0) return self;
    int index = ((igObjectDispatchView *)self)->GetMeta()->_index;
    if (lists->_count <= index) {
        ObjectList_ResizeRetained((igTDataList<igObject *> *)lists.p, index + 1);
        objectListSetRetained(index, 0, lists.p);
    }
    igSmartPointer<igObjectList> entries(asEntryList(((igObject **)lists->_data)[index]), kRetainReference);
    if (entries.p == 0) {
        int pool = file->_temporaryMemoryPool;
        entries.release();
        entries.p = ((igObjectList *)igObjectList_Create(pool));
        objectListSetRetained(index, entries.p, lists.p);
    }
    int i;
    int count = entries->_count;
    self->_index = -1;
    igObjectList *list = entries.p;
    for (i = 0; i < count; i++) {
        igMemoryDirEntry *entry = ((igMemoryDirEntry **)list->_data)[i];
        if (entry->_memTypeIndex == self->_memTypeIndex && entry->_memSize == self->_memSize &&
            entry->_refCounted == self->_refCounted && entry->_memoryPoolHandle == self->_memoryPoolHandle &&
            entry->_alignmentTypeIndex == self->_alignmentTypeIndex) {
            return entry;
        }
    }
    ObjectList_AppendRetained((igObjectList *)list, (igObject *)self);
    return self;
}

int igMemoryDirEntry_GetMeta(void) {
    return (int)g_igMemoryDirEntry_metaObject;
}

void igMemoryDirEntry_ReadMemory(igMemoryDirEntry *self, igIGBFile *file) {
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
    s8 = self->_memSize;
    s7 = (char *)self->_ref;
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

void igMemoryDirEntry_RegisterRef(void) {
}

void igMemoryDirEntry_ResolveRefOld(igMemoryDirEntryView *self, igIGBFileView *file)
{
    self->ResolveRef(file);
}

void igMemoryDirEntry_ResolveMemory(igMemoryDirEntryView *self, igIGBFileView *r) {
    igMetaFieldView *f = ((igMetaFieldView **)r->_metaFieldListInFile->_data)[self->_memTypeIndex];
    self->_memType = (int)f;
    if (((((Gap::Core::igObject *)f)->isOfType((igMetaObject *)Gap::Core::igRefMetaField::getClassMeta()) != 0) ^ 1) && r->_endianSwap != 0) {
        f->SwapBytes((void *)self->_ref, self->_memSize / f->_size);
    }
    if (((Gap::Core::igObject *)f)->isOfType((igMetaObject *)Gap::Core::igRefMetaField::getClassMeta()) != 0) {
        int esize = f->_size;
        int count = self->_memSize / esize;
        int base = self->_ref;
        unsigned char saved = 0;
        int isSwap = ((Gap::Core::igObject *)f)->isOfType((igMetaObject *)Gap::Core::igObjectRefMetaField::getClassMeta()) & 0xff;
        int i;
        if (isSwap != 0) {
            saved = ((igObjectRefMetaField *)f)->_refCounted;
            ((igObjectRefMetaField *)f)->_refCounted = self->_refCounted;
        }
        for (i = 0; i < count; i++) {
            int p = base + i * esize;
            f->ReadRawFieldMem(p, p, (int)r, r->_endianSwap);
        }
        if (isSwap != 0) {
            ((igObjectRefMetaField *)f)->_refCounted = saved;
        }
    }
}

/* Setter for the memory-pool handle (`_memoryPoolHandle`, +48). */

void igMemoryDirEntry_SetMemoryPoolHandle(igMemoryDirEntry *self, int memoryPoolHandle) {
    self->_memoryPoolHandle = memoryPoolHandle;
}

/* Accessor: the memory-pool handle this directory entry was allocated from (`_memoryPoolHandle`,
 * +48). */

int igMemoryDirEntry_GetMemoryPoolHandle(igMemoryDirEntry *self) {
    return self->_memoryPoolHandle;
}

void igMemoryFile_CreateEntryList(void) {
    *(int *)0x586F48 = igMemoryFileEntryList_Create(((int)Memory_GetAllocatorBySelector(*(int *)0x587038)));
}

int *g_memoryFileEntries;

void igMemoryFile_ReleaseEntryList(void) {
    int *o;

    o = g_memoryFileEntries;
    o[1] = o[1] - 1;
    if ((o[1] & 0x7FFFFF) == 0) {
        igObject_Destroy((igObject *)o);
    }
    g_memoryFileEntries = 0;
}

