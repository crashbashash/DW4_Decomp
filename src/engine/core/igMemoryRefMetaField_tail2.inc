static inline void dropNames(igTDataList<igStringObj *> *o) {
    IG_OBJECT_RELEASE(o);
}

static inline int countOf(igTDataList<igStringObj *> *l) { if (l != 0) { return l->_count; } return 0; }


void igMemoryRefMetaField_SetAlignmentType(igMemoryRefMetaField *self, char *name) {
    igTDataList<igStringObj *> *names;
    igTDataList<igStringObj *> *held;
    int n;
    int i;
    if (name == 0) {
        self->_alignmentType = -1;
        return;
    }
    *(igTDataList<igStringObj *> **)&names = g_globalContext->_alignmentStrings;
    held = names;
    if (held != 0) { held->_refCount = (int)held->_refCount + 1; }
    n = countOf(names);
    for (i = 0; i < n; i++) {
        if (strcmp(igStringObj_Text(names->_data[i]), name) == 0) {
            self->_alignmentType = i;
            dropNames(names);
            return;
        }
    }
    dropNames(names);
}

int igMemoryRefMetaField_Write(igMemoryRefMetaField *f, int off, int a2) {
    unsigned int n;
    int p;
    int s1;
    int s0;
    if (f->_persistent == 0) return -1;
    p = *(int *)(off + f->_offset);
    if (p == 0) return -1;
    if (igObject_IsKindOf((void *)f->_memType, (igMetaObject *)((int)g_igMemoryRefMetaField_metaObject)) != 0) {
        n = Memory_GetBufferSize((void *)p) >> 2;
        s1 = igDirectory_AddMemoryRef((igDirectoryView *)a2, (int)f, p, f->_memType, f->_alignmentType, 0, 0, 1);
        for (s0 = 0; s0 < (int)n; s0++) {
            int e = *(int *)(p + s0 * 4);
            if (e != 0) igDirectory_AddMemoryRef((igDirectoryView *)a2, (int)f, e, 0, f->_alignmentType, 0, 0, 1);
        }
        return s1;
    }
    if (igObject_IsKindOf((void *)f->_memType, (igMetaObject *)g_igObjectRefMetaField_metaObject) != 0) {
        s1 = igDirectory_AddMemoryRef((igDirectoryView *)a2, (int)f, p, f->_memType, f->_alignmentType, 0, 0, f->_refCounted);
        return s1;
    }
    return igDirectory_AddMemoryRef((igDirectoryView *)a2, (int)f, p, f->_memType, f->_alignmentType, 0, 0, 1);
}

int igMemoryRefMetaField_IsAlikeExactly(igMemoryRefMetaField *self, int a, int b) {
    int offset;

    offset = self->_offset;
    return *(int *)(a + offset) == *(int *)(b + offset);
}

int igMemoryRefMetaField_IsAlikeDeep(igMemoryRefMetaField *self, int objectA, int objectB) {
    int off;
    int n;
    int a;
    int b;
    int i;

    if (igObject_IsKindOf((void *)self->_memType, (igMetaObject *)g_igObjectRefMetaField_metaObject) == 0) {
        return ((igMetaFieldView *)self)->IsAlikeShallow(objectA, objectB);
    }
    off = self->_offset;
    a = *(int *)(objectA + off);
    b = *(int *)(objectB + off);
    if (a == b) {
        return 1;
    }
    if (a == 0 || b == 0) {
        return 0;
    }
    n = ((int)Memory_GetBufferSize((void *)a));
    if (n != ((int)Memory_GetBufferSize((void *)b))) {
        return 0;
    }
    for (i = 0; i < n; i++) {
        if (!(igObject_IsAlikeDeep((igObjectDispatchView *)(*(int *)(a + i * 4)), (igObjectDispatchView *)(*(int *)(b + i * 4))) & 0xFF)) {
            return 0;
        }
    }
    return 1;
}

int igMemoryRefMetaField_ReadRawFieldMem(igMemoryRefMetaField *self, int destination, int *source, void *directory, int swapBytes) {
    struct { int w0; } index;
    int *out = (int *)destination;
    int raw;
    igMemoryDirEntry *entry;

    if (directory != 0 && (raw = *source) != -1) {
        index.w0 = raw;
        if (swapBytes != 0) {
            ((igMetaFieldView *)igIntMetaField_GetDefaultDescriptor())->SwapBytes(&index.w0, 1);
        }
        entry = (igMemoryDirEntry *)igDirectory_GetEntry((int *)directory, index.w0);
        if (entry != 0) {
            *out = entry->_ref;
            if (self->_memType == 0 && self != (*(void * *)&g_igMemoryRefMetaField_descriptor)) {
                self->_memType = entry->_memType;
            }
        } else {
            *out = 0;
        }
    } else {
        *out = 0;
    }
    return 4;
}

int igMemoryRefMetaField_IsAlikeShallow(igMemoryRefMetaField *self, int objectA, int objectB) {
    int off;
    int n;
    char *a;
    char *b;
    int i;

    off = self->_offset;
    a = *(char **)(objectA + off);
    b = *(char **)(objectB + off);
    if (a == b) {
        return 1;
    }
    if (a == 0 || b == 0) {
        return 0;
    }
    n = ((int)Memory_GetBufferSize(a));
    if (n != ((int)Memory_GetBufferSize(b))) {
        return 0;
    }
    for (i = 0; i < n; i++) {
        if (a[i] != b[i]) {
            return 0;
        }
    }
    return 1;
}

void igMemoryRefMetaField_SetPoolName(igMemoryRefMetaField *self, int name) {
    int *header;
    int references;
    int pool;
    char *previous;
    char *interned;

    if (g_stringPool == 0) {
        pool = ((int)StringPool_Allocate(0x10));
        if (pool != 0) {
            pool = ((int)StringPool_Construct((StringPool *)pool));
        }
        g_stringPool = pool;
    }
    interned = ((char *)StringPool_Intern((StringPool *)g_stringPool, (const char *)name));
    previous = (char *)self->_poolName;
    if (previous != 0) {
        header = (int *)(previous - 8);
        references = *(int *)(previous - 4) - 1;
        *(int *)(previous - 4) = references;
        if (references == 0) {
            StringChunk_ReleaseHeader((StringChunk *)(*header), (int)header);
        }
    }
    self->_poolName = (int)interned;
}

int igMemoryRefMetaField_GetPoolName(igMemoryRefMetaField *self)
{
    return self->_poolName;
}

/* Run the base-class constructor, point the descriptor at its own vtable and
 * clear the two reference members, then (for a live object) apply the field
 * defaults with igMemoryRefMetaField_Init. */
igMemoryRefMetaField *igMemoryRefMetaField_Construct(igMemoryRefMetaField *self, int extra1) {
    igRefMetaField_Construct((igRefMetaField *)self);
    self->_vtable = (int)g_igMemoryRefMetaField_vtable;
    self->_memTypeRef = 0;
    self->_poolName = 0;
    if (self) igMemoryRefMetaField_Init(self);
    return self;
}

/* Default values of a memory-reference descriptor: reference counted, no size
 * or memory type, reset method 3, release on reset and on copy, alignment
 * type -1 and shallow-copy method 2. */
igMemoryRefMetaField *igMemoryRefMetaField_Init(igMemoryRefMetaField *self) {
    igRefMetaField_Init((igRefMetaField *)self);
    self->_vtable = (int)g_igMemoryRefMetaField_vtable;
    self->_memTypeRef = 0;
    self->_poolName = 0;
    self->_refCounted = 1;
    self->_memSize = 0;
    self->_memType = 0;
    self->_resetMethod = 3;
    self->_releaseOnReset = 1;
    self->_releaseOnCopy = 1;
    self->_alignmentType = -1;
    self->_shallowCopyMethod = 2;
    return self;
}

/* Copy the reference layer, stamp the memory-reference vtable and clear the two borrowed
 * references (_memTypeRef, _poolName), then copy the ref-counting, memory type/size, reset,
 * release and alignment settings. */
igMemoryRefMetaField *igMemoryRefMetaField_CopyConstruct(igMemoryRefMetaField *self, igMemoryRefMetaField *source) {
    igRefMetaField_CopyConstruct((igRefMetaField *)self, (igRefMetaField *)source);
    self->_vtable = (int)g_igMemoryRefMetaField_vtable;
    self->_memTypeRef = 0;
    self->_poolName = 0;
    self->_refCounted = source->_refCounted;
    self->_memType = source->_memType;
    self->_memSize = source->_memSize;
    self->_resetMethod = source->_resetMethod;
    self->_releaseOnReset = source->_releaseOnReset;
    self->_releaseOnCopy = source->_releaseOnCopy;
    self->_alignmentType = source->_alignmentType;
    return self;
}

void igMemoryRefMetaField_Destruct(igMemoryRefMetaField *self) {
    igRefMetaField_Destruct((igRefMetaField *)self);
}

