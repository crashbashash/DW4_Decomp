void Gap__Core__igMemoryDirEntry__vfunc_42(int arg0) {
    igObject_IsKindOf((void *)(*(int *)((char *)(arg0) + 36)), (igMetaObject *)((*(int *)g_igRefMetaField_metaObject)));
}

void Gap__Core__igMemoryDirEntry__vfunc_31(Ent_2eedd0 *arg0, Own *arg1) {
    Lst2 *fields = arg1->f188;
    int align = 16;
    Ref_2eedd0 sizes(arg1->f244);
    Alloc_2eedd0 *a;

    if (0 <= arg0->f44) {
        align = sizes.p->data[arg0->f44];
    } else if (fields != 0) {
        if (0 <= arg0->f40) {
            arg0->f36 = fields->data[arg0->f40];
            align = arg0->f36->v108();
        }
    }
    if ((arg0->f48 == -1) || (arg0->f48 == 1) || (arg0->f48 == 2)) {
        a = arg1->f284;
    } else {
        a = (Alloc_2eedd0 *)Memory_GetAllocatorBySelector(arg0->f48);
        if (a == 0) {
            a = arg1->f284;
        }
    }
    if (align < 5) {
        FUN_002d7da0((A7da0 *)arg1, arg0->f12, a->v216(arg0->f28));
    } else {
        FUN_002d7da0((A7da0 *)arg1, arg0->f12, a->v220(arg0->f28, align & 0xFFFF));
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
            s6 += s4 * ((Dev_2eef60 *)arg1->_file)->v27(s8, s4, 1);
            t2 = arg1->_memoryRefBufferSize - s6;
            s2 = (t2 < s4) ? t2 : s4;
            s4 = s2;
        }
    }
    if (s4 != 0) {
        s0 = ((s3 + 3) & ~3) % s4;
        s2 = s2 - (s0 - s3);
        if (s0 < s3) {
            s6 += s4 * ((Dev_2eef60 *)arg1->_file)->v27(s8, s4, 1);
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
        ObjectList_ResizeRetained((L_301ee0 *)lists.p, index + 1);
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

void Gap__Core__igMemoryDirEntry__vfunc_35(Dst *arg0, Rd_2ef680 *arg1) {
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
    s8 = arg0->f28;
    s7 = arg0->f24;
    s4 = arg1->f260;
    s3 = arg1->f256;
    s2 = arg1->f268;
    s1 = arg1->f272;
    base = arg1->f264;
    while (s6 < s8) {
        if (s1 == 0) {
            t = arg1->f156;
            if (t < s4 + s2) {
                s4 = t - s2;
            }
            s2 += s4 * arg1->f104->rd(base, s4, 1);
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
    arg1->f260 = s4;
    arg1->f256 = s3;
    arg1->f268 = s2;
    arg1->f272 = s1;
}

void Gap__Core__igMemoryDirEntry__vfunc_36(void) {
}

void Gap__Core__igMemoryDirEntry__vfunc_33(igMemoryDirEntryView *self)
{
    self->vfunc_32();
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

