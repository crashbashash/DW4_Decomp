static inline void dropNames(AlignmentNameList *o) {
    if (o != 0) {
        o->_refCount = o->_refCount - 1;
        if (((unsigned long long)((long long)o->_refCount << 0x29) >> 0x29) == 0) { igObject_Destroy(o); }
    }
}

static inline int countOf(AlignmentNameList *l) { if (l != 0) { return l->count; } return 0; }

static inline char *textOf_2fb280(AlignmentName *s) { char *t = s->text; if (t == 0) { return (*(char * *)g_stringObjEmptyText); } return t; }

void igMemoryRefMetaField_SetAlignmentType(AlignmentFieldView *self, char *name) {
    AlignmentNameList *names;
    AlignmentNameList *held;
    int n;
    int i;
    if (name == 0) {
        self->alignmentType = -1;
        return;
    }
    *(AlignmentNameList **)&names = *(AlignmentNameList **)((*(char * *)&g_globalContext) + 44);
    held = names;
    if (held != 0) { held->_refCount = held->_refCount + 1; }
    n = countOf(names);
    for (i = 0; i < n; i++) {
        if (strcmp(textOf_2fb280((*(AlignmentName ***)((char *)names + 16))[i]), name) == 0) {
            self->alignmentType = i;
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
    if (igObject_IsKindOf((void *)f->_memType, (igMetaObject *)(((int *)g_igMemoryRefMetaField_metaObject)[0])) != 0) {
        n = Memory_GetBufferSize((void *)p) >> 2;
        s1 = FUN_002d8a80((L8a80 *)a2, (int)f, p, f->_memType, f->_alignmentType, 0, 0, 1);
        for (s0 = 0; s0 < (int)n; s0++) {
            int e = *(int *)(p + s0 * 4);
            if (e != 0) FUN_002d8a80((L8a80 *)a2, (int)f, e, 0, f->_alignmentType, 0, 0, 1);
        }
        return s1;
    }
    if (igObject_IsKindOf((void *)f->_memType, (igMetaObject *)g_igObjectRefMetaField_metaObject[0]) != 0) {
        s1 = FUN_002d8a80((L8a80 *)a2, (int)f, p, f->_memType, f->_alignmentType, 0, 0, f->_refCounted);
        return s1;
    }
    return FUN_002d8a80((L8a80 *)a2, (int)f, p, f->_memType, f->_alignmentType, 0, 0, 1);
}

int Gap__Core__igMemoryRefMetaField__vfunc_45(igMemoryRefMetaField *arg0, int arg1, int arg2) {
    int temp_v0;

    temp_v0 = arg0->_offset;
    return *(int *)(arg1 + temp_v0) == *(int *)(arg2 + temp_v0);
}

int igMemoryRefMetaField_IsAlikeDeep(igMemoryRefMetaField *arg0, int arg1, int arg2) {
    int off;
    int n;
    int a;
    int b;
    int i;

    if (igObject_IsKindOf((void *)arg0->_memType, (igMetaObject *)g_igObjectRefMetaField_metaObject[0]) == 0) {
        return ((igMetaFieldView *)arg0)->IsAlikeShallow(arg1, arg2);
    }
    off = arg0->_offset;
    a = *(int *)(arg1 + off);
    b = *(int *)(arg2 + off);
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
        if (!(igObject_IsAlikeDeep((DeepObject *)(*(int *)(a + i * 4)), (DeepObject *)(*(int *)(b + i * 4))) & 0xFF)) {
            return 0;
        }
    }
    return 1;
}

int igMemoryRefMetaField_ReadRawFieldMem(igMemoryRefMetaField *arg0, int a1, int *arg2, void *arg3, int arg4) {
    struct { int w0; } v;
    int *arg1 = (int *)a1;
    int t;
    igMemoryDirEntry *e;

    if (arg3 != 0 && (t = *arg2) != -1) {
        v.w0 = t;
        if (arg4 != 0) {
            ((igMetaFieldView *)igIntMetaField_GetDefaultDescriptor())->SwapBytes(&v.w0, 1);
        }
        e = (igMemoryDirEntry *)FUN_002d7e90((int *)arg3, v.w0);
        if (e != 0) {
            *arg1 = e->_ref;
            if (arg0->_memType == 0 && arg0 != ((void * *)DAT_00585d88)[0]) {
                arg0->_memType = e->_memType;
            }
        } else {
            *arg1 = 0;
        }
    } else {
        *arg1 = 0;
    }
    return 4;
}

int igMemoryRefMetaField_IsAlikeShallow(igMemoryRefMetaField *arg0, int arg1, int arg2) {
    int off;
    int n;
    char *a;
    char *b;
    int i;

    off = arg0->_offset;
    a = *(char **)(arg1 + off);
    b = *(char **)(arg2 + off);
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

void igMemoryRefMetaField_SetPoolName(igMemoryRefMetaField *arg0, int arg1) {
    int *temp_a1;
    int temp_v1;
    int var_v0;
    char *temp_a0;
    char *temp_s0;

    if (g_stringPool[0] == 0) {
        var_v0 = ((int)StringPool_Allocate(0x10));
        if (var_v0 != 0) {
            var_v0 = ((int)StringPool_Construct((S_2eadf0 *)var_v0));
        }
        g_stringPool[0] = var_v0;
    }
    temp_s0 = ((char *)StringPool_Intern((StringPool *)g_stringPool[0], (const char *)arg1));
    temp_a0 = (char *)arg0->_poolName;
    if (temp_a0 != 0) {
        temp_a1 = (int *)(temp_a0 - 8);
        temp_v1 = *(int *)(temp_a0 - 4) - 1;
        *(int *)(temp_a0 - 4) = temp_v1;
        if (temp_v1 == 0) {
            StringChunk_ReleaseHeader((StringChunkOwnerView *)(*temp_a1), (int)temp_a1);
        }
    }
    arg0->_poolName = (int)temp_s0;
}

int igMemoryRefMetaField_GetPoolName(int *p)
{
    return *(int *)((char *)p + 76);
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

void igMemoryRefMetaField_Destruct(void) {
    igRefMetaField_Destruct();
}

