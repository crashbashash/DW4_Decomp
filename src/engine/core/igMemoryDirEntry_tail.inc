void Gap__Core__igMemoryDirEntry__vfunc_42(int arg0) {
    igObject_IsKindOf((void *)(*(int *)((char *)(arg0) + 36)), (igMetaObject *)((*(int *)g_igRefMetaField_metaObject)));
}

void Gap__Core__igMemoryDirEntry__vfunc_31(igMemoryDirEntry *self, igIGBFile *file) {
    igObjectList *fields = (igObjectList *)file->_metaFieldListInFile;
    int align = 16;
    igSmartPointer<igIntList> alignments((igIntList *)file->_alignmentListInFile, kRetainReference);
    igMemoryPoolView *pool;

    if (0 <= self->_alignmentTypeIndex) {
        align = ((int *)alignments->_data)[self->_alignmentTypeIndex];
    } else if (fields != 0) {
        if (0 <= self->_memTypeIndex) {
            self->_memType = ((int *)fields->_data)[self->_memTypeIndex];
            align = ((igMetaFieldView *)self->_memType)->vfunc_27();
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
        FUN_002d7da0((igDirectoryView *)file, self->_index, (int)pool->Allocate(self->_memSize));
    } else {
        FUN_002d7da0((igDirectoryView *)file, self->_index, (int)pool->AllocateAligned(self->_memSize, align & 0xFFFF));
    }
}

void Gap__Core__igMemoryDirEntry__vfunc_41(igMemoryDirEntry *arg0, igIGBFile *arg1) {
    int s4 = arg1->_chunkSize;
    int s3 = arg1->_memoryBufferPlace;
    int s6 = arg1->_memoryBytesCopied;
    int s2 = arg1->_bytesRemainingInChunk;
    int s8 = arg1->_chunk;
    int cnt = arg0->_memSize;
    Cod *s1 = (Cod *)arg0->_memType;
    int esz = ((igMetaField *)s1)->_size;
    int per = cnt / esz;
    int s0, s7, i, src, j, dst, t0, t1, t2;
    if (((igObject_IsKindOf((void *)s1, (igMetaObject *)g_igRefMetaField_metaObject[0]) != 0) ^ 1) && arg1->_endianSwap != 0) {
        s1->v50(arg0->_ref, per);
    }
    s7 = 0;
    i = 0;
    src = arg0->_ref;
    while (i < cnt) {
        t0 = cnt - i;
        s0 = (t0 < s2) ? t0 : s2;
        if (igObject_IsKindOf((void *)s1, (igMetaObject *)g_igRefMetaField_metaObject[0]) != 0) {
            int q = s0 / esz;
            t1 = per - s7;
            s7 = (t1 < q) ? t1 : q;
            dst = s8 + s3;
            for (j = 0; j < s7; j++) {
                s1->v48(src + j * esz, dst + j * esz, arg1, arg1->_endianSwap);
            }
        } else {
            memcpy(s8 + s3, src, s0);
        }
        src += s0;
        s3 = (s3 + s0) % s4;
        s2 -= s0;
        i += s0;
        if (s2 == 0) {
            s6 += s4 * ((igFileView *)arg1->_file)->Write((void *)s8, s4, 1);
            t2 = arg1->_memoryRefBufferSize - s6;
            s2 = (t2 < s4) ? t2 : s4;
            s4 = s2;
        }
    }
    if (s4 != 0) {
        s0 = ((s3 + 3) & ~3) % s4;
        s2 = s2 - (s0 - s3);
        if (s0 < s3) {
            s6 += s4 * ((igFileView *)arg1->_file)->Write((void *)s8, s4, 1);
            t2 = arg1->_memoryRefBufferSize - s6;
            s2 = (t2 < s4) ? t2 : s4;
            s4 = s2;
        }
        if (((igObject_IsKindOf((void *)s1, (igMetaObject *)g_igRefMetaField_metaObject[0]) != 0) ^ 1) && arg1->_endianSwap != 0) {
            s1->v50(arg0->_ref, per);
        }
        arg1->_memoryBytesCopied = s6;
        arg1->_bytesRemainingInChunk = s2;
        arg1->_memoryBufferPlace = s0;
        arg1->_chunkSize = s4;
    }
}

/* igMemoryDirEntry slot 39: tally this memory block into the igIGBFile that is sizing its buffers.
 * Called once per directory entry by the file's sizing pass (FUN_002e4240, which zeroes the four
 * counters first): the block count goes up by one and the memory buffer size by the block's
 * _memSize rounded up to a multiple of four, the same rounding the pool layout uses. */

void Gap__Core__igMemoryDirEntry__vfunc_39(igMemoryDirEntry *self, igIGBFile *file) {
    file->_memoryRefCount = file->_memoryRefCount + 1;
    file->_memoryRefBufferSize = file->_memoryRefBufferSize + ((self->_memSize + 3) & ~3);
}

static inline EntryList *asEntryList(igObject *object) {
    if (object != 0 && igObject_IsKindOf(object, (igMetaObject *)g_igObjectList_metaObject[0]) != 0) return (EntryList *)object;
    return 0;
}

igMemoryDirEntry *Gap__Core__igMemoryDirEntry__vfunc_26(igMemoryDirEntry *self, DirFile *file) {
    igSmartPointer<EntryList> lists(file->sharedEntries, kRetainReference);
    if (lists.p == 0) return self;
    int index = ((DirEntryView *)self)->getMeta()->index;
    if (lists->_count <= index) {
        ObjectList_ResizeRetained((igTDataList<igObject *> *)lists.p, index + 1);
        lists->set(index, 0);
    }
    igSmartPointer<EntryList> entries(asEntryList(((igObject **)lists->_data)[index]), kRetainReference);
    if (entries.p == 0) {
        int pool = file->pool;
        entries.release();
        entries.p = ((EntryList *)FUN_002bd680(pool));
        lists->set(index, entries.p);
    }
    int i;
    int count = entries->_count;
    self->_index = -1;
    EntryList *list = entries.p;
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

int Gap__Core__igMemoryDirEntry__vfunc_22(void) {
    return ((int *)g_igMemoryDirEntry_metaObject)[0];
}

void Gap__Core__igMemoryDirEntry__vfunc_35(igMemoryDirEntry *arg0, igIGBFile *arg1) {
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
    s8 = arg0->_memSize;
    s7 = (char *)arg0->_ref;
    s4 = arg1->_chunkSize;
    s3 = arg1->_memoryBufferPlace;
    s2 = arg1->_memoryBytesCopied;
    s1 = arg1->_bytesRemainingInChunk;
    base = arg1->_chunk;
    while (s6 < s8) {
        if (s1 == 0) {
            t = arg1->_memoryRefBufferSize;
            if (t < s4 + s2) {
                s4 = t - s2;
            }
            s2 += s4 * ((igFileView *)arg1->_file)->Read((void *)base, s4, 1);
            s1 = s4;
        }
        s0 = s8 - s6;
        s0 = s0 < s1 ? s0 : s1;
        memcpy(s7, base + s3, s0);
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
    arg1->_chunkSize = s4;
    arg1->_memoryBufferPlace = s3;
    arg1->_memoryBytesCopied = s2;
    arg1->_bytesRemainingInChunk = s1;
}

void Gap__Core__igMemoryDirEntry__vfunc_36(void) {
}

void Gap__Core__igMemoryDirEntry__vfunc_33(igMemoryDirEntryView *self, igIGBFileView *file)
{
    self->vfunc_34(file);
}

void Gap__Core__igMemoryDirEntry__vfunc_34(MemoryDirEntryView *self, MemoryDirReader *r) {
    MemoryDirField *f = r->fields->data[self->fieldIndex];
    self->field = f;
    if (((igObject_IsKindOf(f, (igMetaObject *)g_igRefMetaField_metaObject[0]) != 0) ^ 1) && r->swapped != 0) {
        f->swapArray(self->base, self->size / f->elementSize);
    }
    if (igObject_IsKindOf(f, (igMetaObject *)g_igRefMetaField_metaObject[0]) != 0) {
        int esize = f->elementSize;
        int count = self->size / esize;
        int base = self->base;
        unsigned char saved = 0;
        int isSwap = igObject_IsKindOf(f, (igMetaObject *)g_igObjectRefMetaField_metaObject[0]) & 0xff;
        int i;
        if (isSwap != 0) {
            saved = f->swapFlag;
            f->swapFlag = self->swapFlag;
        }
        for (i = 0; i < count; i++) {
            int p = base + i * esize;
            f->fix(p, p, r, r->swapped);
        }
        if (isSwap != 0) {
            f->swapFlag = saved;
        }
    }
}

/* Setter for the memory-pool handle (`_memoryPoolHandle`, +48). */

void Gap__Core__igMemoryDirEntry__vfunc_29(igMemoryDirEntry *self, int memoryPoolHandle) {
    self->_memoryPoolHandle = memoryPoolHandle;
}

/* Accessor: the memory-pool handle this directory entry was allocated from (`_memoryPoolHandle`,
 * +48). */

int Gap__Core__igMemoryDirEntry__vfunc_30(igMemoryDirEntry *self) {
    return self->_memoryPoolHandle;
}

void FUN_002ef9a0(void) {
    *(int *)0x586F48 = FUN_002c0a00(((int)Memory_GetAllocatorBySelector(*(int *)0x587038)));
}

void FUN_002ef9d0(void) {
    int *o;

    o = DAT_00586f48[0];
    o[1] = o[1] - 1;
    if ((o[1] & 0x7FFFFF) == 0) {
        igObject_Destroy(o);
    }
    DAT_00586f48[0] = 0;
}

