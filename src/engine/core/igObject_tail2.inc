struct ObjectHeader *igObject_InitHeader(struct ObjectHeader *p) {
    p->vt = &g_igObject_vtable[0];
    p->refs = 1;
    p->flag = 0;
    p->b7 = 0;
    return p;
}

CopyHeader *igObject_CopyConstructHeader(CopyHeader *arg0, CopyHeader *arg1) {
    arg0->vt = (int)&g_igObject_vtable[0];
    if (arg0 != 0) {
        igObject_InitHeader((ObjectHeader *)arg0);
    }
    arg0->hi = arg1->hi;
    if (*g_objectSystem[0] != 0) {
        arg0->b7 = ((char)igAllocator_EncodeIndex((AllocatorLookupView *)(Memory_FindOwningAllocator((int)(igObject_GetAllocationBase(arg0))))));
    }
    return arg0;
}

igObject *igObject_ConstructHeader(igObject *self) {
    void **owner;

    self->_vtable = (int)(&g_igObject_vtable[0]);
    if (self != 0) {
        igObject_InitHeader((ObjectHeader *)self);
    }
    if (*g_objectSystem[0] != 0) {
        owner = (void **)(Memory_FindOwningAllocator((int)(igObject_GetAllocationBase(self))));
        if (owner != 0) {
            *(unsigned char *)((char *)(self) + 7) = ((igMemoryPoolView *)(owner))->GetPoolIndex();
        } else {
            *(unsigned char *)((char *)(self) + 7) = 0;
        }
    } else {
        *(unsigned char *)((char *)(self) + 7) = 0;
    }
    return self;
}

/* Shared default virtual slots that almost every class inherits, so most are empty or return a
 * constant. The slot number is the only name evidence, so the bodies are documented by what they
 * do. The `__<addr>` names are distinct bodies resolved to the same slot. */
int Gap__Core__igObject__vfunc_00__002ff0a0(int extra0)
{
}

/* Slot 1 default: empty. */
void Gap__Core__igObject__constructFields(int extra0, int extra1)
{
}

/* Slot 2 default: empty. */
void Gap__Core__igObject__destructFields(int extra0)
{
}

/* Slot 3 default: empty. */
void Gap__Core__igObject__vfunc_03(void)
{
}

/* Slot 7 default: empty. */
void Gap__Core__igObject__userConstruct(void)
{
}

void Gap__Core__igObject__userDestruct(void)
{
}

/* Slot 4 default: empty. */
void Gap__Core__igObject__vfunc_04(void)
{
}

/* Slot 5 default: always 1. */
int Gap__Core__igObject__vfunc_05(void)
{
    return 1;
}

/* Slot 6 default: always 1. */
int Gap__Core__igObject__vfunc_06(void)
{
    return 1;
}

/* Slot 11 default: empty. */
void Gap__Core__igObject__resetFields(int extra0, int extra1)
{
}

/* Slot 9 default: empty. */
void Gap__Core__igObject__vfunc_09(int extra0)
{
}

/* Slot 10 default: empty. */
void Gap__Core__igObject__vfunc_10(int extra0)
{
}

/* Slot 12 default: empty. */
void Gap__Core__igObject__vfunc_12(void)
{
}

/* Slot 13 default: empty. */
void Gap__Core__igObject__vfunc_13(void)
{
}

/* Slot 15 default: empty. */
void Gap__Core__igObject__vfunc_15(void)
{
}

/* Slot 14 default: empty. */
void Gap__Core__igObject__vfunc_14(void)
{
}

/* Slot 16 default: empty. */
void Gap__Core__igObject__vfunc_16(int extra0)
{
}

/* Slot 17 default: empty. */
void Gap__Core__igObject__vfunc_17(void)
{
}

/* Slot 18 default: empty. */
void Gap__Core__igObject__vfunc_18(void)
{
}

void igObject_Construct(ConstructedObject *arg0, char *arg1) {
    igMemoryPoolView *a;
    igMetaObject *l;
    *(int *)((char *)arg0 + *(int *)((char *)g_objectSystem[0] + 916)) = *(int *)(arg1 + 92);
    arg0->u.w4 = 0;
    arg0->u.b.cnt = 1;
    arg0->u.c.hi = 0;
    a = (igMemoryPoolView *)Memory_FindOwningAllocator((int)(igObject_GetAllocationBase(arg0)));
    if (a != 0) {
        arg0->u.c.id = a->GetPoolIndex();
    } else {
        arg0->u.c.id = 0;
    }
    igObject_ZeroFields((igObjectDispatchView *)arg0);
    igObject_ConstructFields((igObjectDispatchView *)arg0);
    igObject_ResetUnconstructedFields((igObjectDispatchView *)arg0);
    arg0->v11();
    arg0->v9(0);
    l = arg0->v22();
    if (l != 0) {
        l->_instanceCount = l->_instanceCount + 1;
        if (l->_instances != 0) {
            ObjectPointerList_Append((PointerList *)l->_instances, (int)arg0);
        }
    }
}

void igObject_ConstructPooled(PooledHeader *arg0, char *arg1) {
    igMemoryPoolView *g;

    *(int *)((char *)arg0 + *(int *)((char *)(g_objectSystem[0]) + 916)) = *(int *)(arg1 + 92);
    arg0->refs = 1;
    arg0->flag = 0 & 1;
    g = (igMemoryPoolView *)Memory_FindOwningAllocator((int)(igObject_GetAllocationBase(arg0)));
    if (g != 0) {
        arg0->rest = g->GetPoolIndex();
    } else {
        arg0->rest = 0;
    }
    igObject_ZeroFields((igObjectDispatchView *)arg0);
}

void igObject_RegisterInstance(void **arg0, void *arg1) {
    int temp_a0;
    void *temp_v0;

    if ((arg1 != 0) && (*(int *)((char *)(arg1) + 60) != 0)) {
        ((igObjectDispatchView *)arg0)->vfunc_18();
    }
    ((igObjectDispatchView *)arg0)->constructFields(0);
    ((igObjectDispatchView *)arg0)->resetFields(0);
    ((igObjectDispatchView *)(arg0))->userConstruct((int)(1));
    temp_v0 = (void *)(((igObjectDispatchView *)(arg0))->getMeta());
    if (temp_v0 != 0) {
        *(int *)((char *)(temp_v0) + 44) = (int)((int) (*(int *)((char *)(temp_v0) + 44) + 1));
        temp_a0 = *(int *)((char *)(temp_v0) + 48);
        if (temp_a0 != 0) {
            ObjectPointerList_Append((PointerList *)temp_a0, (int)arg0);
        }
    }
}

/* Class-registration "extra callbacks" factory for igObject (passed to igMetaObject_RegisterClass
 * by igObject_Register): allocate a 12-byte callback array from the metadata allocator selector
 * and construct it empty. Returns the array, or 0 when the allocation fails. */
int igObject_CreateEmptyInitCallbacks(void) {
    int callbacks;

    callbacks = ((int)Memory_AllocateBufferDirect(0xC, (igMemoryPoolView *)((igMemoryPool *)(((void **)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData))))));
    if (callbacks != 0) {
        callbacks = ((int)igArray_Construct((CallbackArray *)callbacks));
    }
    return callbacks;
}

void *igObject_GetNoParentMetaObject(void){return 0;}

int igObject_GetVTable(void) {
    int o[2];

    igObject_InitHeader((ObjectHeader *)o);
    return *(int *)((char *)o + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void igObject_EnsureRegistered(void){igMetaObject_RunStaticInit((StaticInitCallbacks *(*)())igObject_Register);}

void *igObject_Register(void) {
    return ((void *)igMetaObject_RegisterClass(
        0, /* abstract */
        g_igObject_metaObject,
        igObject_CreateEmptyInitCallbacks,
        igObject_GetNoParentMetaObject,
        igObject_GetMetaObject,
        igObject_className,
        8, /* instance size */
        igObject_GetVTable,
        &igObject_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    ));
}

void *igObject_GetMetaObject(void){return (void *)g_igObject_metaObject[0];}

void igObject_InitFields(void) {
    void *sp2C;
    void *sp28;
    int *temp_a1;
    int *temp_a1_2;
    int temp_v0_2;
    int temp_v0_4;
    int var_v0_2;
    int var_v0_4;
    igUnsignedIntMetaField *temp_v0;
    igUnsignedIntMetaField *temp_v0_3;
    void *var_v0;
    void *var_v0_3;

    temp_v0 = ((igUnsignedIntMetaField *)igUnsignedIntMetaField_Create((int)(((void **)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)))));
    temp_v0->_offset = 4;
    temp_v0->_externalEnumStorage = (int)(&DAT_005871a0[0]);
    if (&text_refCount[0] == 0) {
        var_v0 = (void *)(0);
    } else {
        if (g_stringPool[0] == 0) {
            var_v0_2 = ((int)StringPool_Allocate(0x10));
            if (var_v0_2 != 0) {
                var_v0_2 = ((int)StringPool_Construct((StringPool *)var_v0_2));
            }
            g_stringPool[0] = var_v0_2;
        }
        var_v0 = (void *)(((void *)StringPool_Intern((StringPool *)g_stringPool[0], (const char *)&text_refCount[0])));
    }
    sp2C = (void *)(var_v0);
    igMetaField_SetFieldName((igMetaField *)temp_v0, &sp2C);
    if (sp2C != 0) {
        temp_a1 = (int *)((char *)sp2C - 8);
        temp_v0_2 = *(int *)((char *)(sp2C) - 4) - 1;
        *(int *)((char *)(sp2C) - 4) = temp_v0_2;
        if (temp_v0_2 == 0) {
            StringChunk_ReleaseHeader((StringChunkOwnerView *)(*temp_a1), (int)temp_a1);
        }
    }
    temp_v0->_persistent = 0;
    temp_v0->_resetMethod = 3;
    igMetaObject_FinalizeAndAppendField(g_igObject_metaObject[0], temp_v0);
    temp_v0->_refCount = (int)temp_v0->_refCount - 1;
    if (((unsigned long long)((long long)(int)temp_v0->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_v0);
    }
    temp_v0_3 = ((igUnsignedIntMetaField *)igUnsignedIntMetaField_Create((int)(((void **)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)))));
    temp_v0_3->_offset = 4;
    temp_v0_3->_externalEnumStorage = (int)(&DAT_005871a8[0]);
    if (&text_memPoolIndex[0] == 0) {
        var_v0_3 = (void *)(0);
    } else {
        if (g_stringPool[0] == 0) {
            var_v0_4 = ((int)StringPool_Allocate(0x10));
            if (var_v0_4 != 0) {
                var_v0_4 = ((int)StringPool_Construct((StringPool *)var_v0_4));
            }
            g_stringPool[0] = var_v0_4;
        }
        var_v0_3 = (void *)(((void *)StringPool_Intern((StringPool *)g_stringPool[0], (const char *)&text_memPoolIndex[0])));
    }
    sp28 = (void *)(var_v0_3);
    igMetaField_SetFieldName((igMetaField *)temp_v0_3, &sp28);
    if (sp28 != 0) {
        temp_a1_2 = (int *)((char *)sp28 - 8);
        temp_v0_4 = *(int *)((char *)(sp28) - 4) - 1;
        *(int *)((char *)(sp28) - 4) = temp_v0_4;
        if (temp_v0_4 == 0) {
            StringChunk_ReleaseHeader((StringChunkOwnerView *)(*temp_a1_2), (int)temp_a1_2);
        }
    }
    temp_v0_3->_persistent = 0;
    temp_v0_3->_resetMethod = 3;
    igMetaObject_FinalizeAndAppendField(g_igObject_metaObject[0], temp_v0_3);
    temp_v0_3->_refCount = (int)temp_v0_3->_refCount - 1;
    if (((unsigned long long)((long long)(int)temp_v0_3->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(temp_v0_3);
    }
}

char *igObject_AllocateRawStorage(int size, int prefix_size, igMemoryPoolView *requested_pool) {
    int total_size;
    igMemoryPoolView *pool;

    pool = requested_pool;
    total_size = size + prefix_size;
    if (pool == 0) {
        pool = (igMemoryPoolView *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleBootstrap);
    }
    if (pool == 0) {
        /* no pool at all: the prefix is not added on this path (retail behaviour) */
        return ((char *)malloc(total_size));
    }
    return (char *)pool->Allocate(total_size) + prefix_size;
}

void *igObject_AllocateRawStorageDefault(int size,int prefix){return igObject_AllocateRawStorage(size,prefix,0);}

int thunk_FUN_002ed460__002ff810(int extra0)
{
    return Memory_FreeBuffer((void *)extra0);
}

void igObject_Destroy(void *input) {
    if (g_objectSystem[0]) {
        igObjectDispatchView *object = (igObjectDispatchView *)input;
        if (!*g_objectSystem[0]) {
            object->userDestruct();
            object->vfunc_10();
            object->vfunc_00();
            Memory_FreeBuffer(object);
            return;
        }
        igMetaObject *type = object->getMeta();
        type->_instanceCount = (int)((unsigned)type->_instanceCount - 1);
        void *instances = (void *)type->_instances;
        if (instances) ObjectPointerList_EraseAt((PointerList *)instances, ObjectPointerList_FindIndex((char *)instances, (int)object));
        object->vfunc_16();
        object->userDestruct();
        object->vfunc_10();
        igObject_DestructFieldValues((int *)object);
        igObject_ClearFieldValues((int *)object);
        Memory_FreeBuffer(igObject_GetAllocationBase(object));
    }
}

static inline int isValid(igMetaObject *m) { return (m->_validity & 4) != 0; }

void igObject_ZeroFields(igObjectDispatchView *object) {
    igMetaObject *meta = object->getMeta();
    if (((meta != 0) && isValid(meta)) || (*(unsigned char *)((char *)(g_objectSystem[0]) + 20) == 0) || (*(unsigned char *)((char *)(g_objectSystem[0]) + 0) != 0)) {
        __internalObjectList *fields = (__internalObjectList *)meta->_metaFields;
        int first = ((__internalObjectList *)g_igObject_metaObject[0]->_metaFields)->_count;
        int count = fields->_count;
        for (int i = first; i < count; i++) {
            ((igMetaFieldSlots **)fields->_data)[i]->ZeroValue(object);
        }
    }
}

void igObject_ConstructFields(igObjectDispatchView *object) {
    __internalObjectList *fields = (__internalObjectList *)object->getMeta()->_metaFields;
    int first = ((__internalObjectList *)g_igObject_metaObject[0]->_metaFields)->_count;
    int count = fields->_count;
    for (int i = first; i < count; i++) {
        ((igMetaFieldSlots **)fields->_data)[i]->ConstructValue(object);
    }
    object->constructFields(1);
}

void igObject_ResetFields(igObjectDispatchView *object) {
    __internalObjectList *fields = (__internalObjectList *)object->getMeta()->_metaFields;
    int first = ((__internalObjectList *)g_igObject_metaObject[0]->_metaFields)->_count;
    int count = fields->_count;
    for (int i = first; i < count; i++) {
        igMetaField_Reset(((igMetaField **)fields->_data)[i], object);
    }
    object->resetFields(1);
}

void igObject_ResetUnconstructedFields(igObjectDispatchView *object) {
    __internalObjectList *fields = (__internalObjectList *)object->getMeta()->_metaFields;
    int first = ((__internalObjectList *)g_igObject_metaObject[0]->_metaFields)->_count;
    int count = fields->_count;
    for (int i = first; i < count; i++) {
        igMetaFieldSlots *field = ((igMetaFieldSlots **)fields->_data)[i];
        if (field->IsConstruct() == 0) {
            igMetaField_Reset((igMetaField *)field, object);
        }
    }
    object->resetFields(1);
}

void igObject_DestructFieldValues(int *arg0) {
    DestructFieldList *q;
    int i;
    int n;

    ((DestructSelf *)arg0)->vX();
    q = (DestructFieldList *)((int *)((MetaSource *)arg0)->vX())[10];
    i = ((DestructFieldList *)((int *)g_igObject_metaObject[0])[10])->count;
    n = q->count;
    for (; i < n; i++) {
        q->data[i]->vX(arg0);
    }
}

void igObject_ClearFieldValues(int *arg0) {
    ClearFieldList *q;
    int i;
    int n;

    q = (ClearFieldList *)((int *)((MetaSource *)arg0)->vX())[10];
    i = ((ClearFieldList *)((int *)g_igObject_metaObject[0])[10])->count;
    n = q->count;
    for (; i < n; i++) {
        q->data[i]->vX(arg0);
    }
}

int igObject_GetSerializedSize(SizeObject *arg0) {
    SizeMeta *m0 = arg0->GetMeta();
    SizeMeta *m;
    int size, i, n;
    SizeMeta *(*fp)();
    fp = m0->f40;
    if (fp != 0) { m = fp(); } else { m = m0; }
    if (m->b19 == 0) return 0;
    size = 8;
    i = igMetaObject_GetFieldCount(g_igObject_metaObject[0]);
    n = igMetaObject_GetFieldCount((igMetaObject *)m);
    for (; i < n; i++) { size += ((SizeField *)((void *)igMetaObject_GetFieldAt((igMetaObject *)m, i)))->GetSize(arg0); }
    return size;
}

int igObject_WritePersistentFields(igObjectDispatchView *object, int *buffer, igIGBFile *file, igTDataList<ChainMeta *> *metaObjectList, unsigned char endianSwap) {
    igMetaObject *meta = object->getMeta();
    if (meta->_persistent == 0) {
        return 0;
    }
    object->vfunc_12();
    int index = 0;
    igMetaObject *writeMeta = (meta->_writeProxy != 0) ? ((igMetaObject *(*)())meta->_writeProxy)() : meta;
    if (metaObjectList != 0) {
        index = FUN_002fe600(metaObjectList, (ChainMeta *)writeMeta);
    }
    int count = igMetaObject_GetFieldCount(writeMeta);
    int i = igMetaObject_GetFieldCount(g_igObject_metaObject[0]);
    buffer[0] = index;
    buffer[1] = igObject_GetSerializedSize((SizeObject *)object);
    if (endianSwap) {
        ((SwapDescriptor *)igIntMetaField_GetDefaultDescriptor())->Swap(buffer, 2);
    }
    buffer += 2;
    for (; i < count; i++) {
        igMetaField *field = (igMetaField *)igMetaObject_GetFieldAt(writeMeta, i);
        if (field->_persistent == 1 && field->_isRunTime == 0) {
            buffer = (int *)((char *)buffer + igMetaField_WritePersistentValue(field, object, buffer, file, endianSwap));
        }
    }
    return igObject_GetSerializedSize((SizeObject *)object);
}

int FUN_002fff90(ReadObject *object, FieldRecordHead *head, igIGBFile *file, igTDataList<ChainMeta *> *metaObjectList, unsigned char endianSwap) {
    igMetaObject *meta;
    char *data;
    int i;
    int count;
    int runTimeFields, readFields;
    igMetaField *field;
    meta = object->v20();
    if (meta->_persistent == 0) return 0;
    if (endianSwap) {
        ((SwapDescriptor *)igIntMetaField_GetDefaultDescriptor())->Swap(head, 3);
    }
    data = (char *)head + 12;
    i = igMetaObject_GetFieldCount(g_igObject_metaObject[0]);
    count = igMetaObject_GetFieldCount(meta);
    runTimeFields = 0;
    readFields = 0;
    for (; i < count; i++) {
        field = (igMetaField *)igMetaObject_GetFieldAt(meta, i);
        if (field->_isRunTime != 0) {
            runTimeFields += 1;
            ((ReadField *)field)->v29(object);
            if (igObject_IsKindOf(field, (igMetaObject *)g_igRefMetaField_metaObject[0]) == 0 || ((igRefMetaField *)field)->_construct == 0) igMetaField_Reset(field, object);
        } else if (readFields >= head->fieldCount) {
            ((ReadField *)field)->v29(object);
            if (igObject_IsKindOf(field, (igMetaObject *)g_igRefMetaField_metaObject[0]) == 0 || ((igRefMetaField *)field)->_construct == 0) igMetaField_Reset(field, object);
        } else {
            if (endianSwap) ((SwapDescriptor *)igShortMetaField_GetDefaultDescriptor())->Swap(data, 2);
            if (i < *(short *)data + runTimeFields) {
                ((ReadField *)field)->v29(object);
                if (igObject_IsKindOf(field, (igMetaObject *)g_igRefMetaField_metaObject[0]) == 0 || ((igRefMetaField *)field)->_construct == 0) igMetaField_Reset(field, object);
                if (endianSwap) ((SwapDescriptor *)igShortMetaField_GetDefaultDescriptor())->Swap(data, 2);
            } else {
                readFields += 1;
                data += FUN_002fc740((PersistentSizeView *)field, (char *)object, data, file, endianSwap);
            }
        }
    }
    {
        int size = head->size;
        if (endianSwap) ((SwapDescriptor *)igIntMetaField_GetDefaultDescriptor())->Swap(head, 3);
        object->v14();
        return size;
    }
}

int FUN_00300250(FieldObjectView *object, FieldRecordHead *head, FieldDirView *dir, igTDataList<ChainMeta *> *metaObjectList, unsigned char endianSwap) {
    FieldMetaView *meta;
    FieldListTable *lists;
    FieldOffsetList *offsets;
    char *data;
    int i;
    int first;
    int count;
    int done;
    int next;
    short limit;
    FieldEntryView *field;
    int size;
    meta = object->Meta();
    if (meta->_persistent == 0) {
        return 0;
    }
    lists = dir->lists;
    if (endianSwap) {
        ((SwapDescriptor *)igIntMetaField_GetDefaultDescriptor())->Swap(head, 2);
    }
    offsets = lists->data[head->kind];
    data = (char *)head + 8;
    first = igMetaObject_GetFieldCount(g_igObject_metaObject[0]);
    count = igMetaObject_GetFieldCount((igMetaObject *)meta);
    done = 0;
    next = 0;
    if (offsets->count == 0) {
        limit = count;
    } else {
        limit = offsets->data[next++];
    }
    for (i = first; i < count; i++) {
        field = (FieldEntryView *)igMetaObject_GetFieldAt((igMetaObject *)meta, i);
        if (i < limit) {
            field->Prepare(object);
            if (igObject_IsKindOf(field, (igMetaObject *)g_igRefMetaField_metaObject[0]) == 0 || field->_skipReset == 0) {
                igMetaField_Reset((igMetaField *)field, object);
            }
        } else {
            done++;
            data += FUN_002fc780(field, object, data, dir, endianSwap);
            if (done == offsets->count) {
                limit = count;
            } else {
                limit = offsets->data[next++];
            }
        }
    }
    size = head->size;
    if (endianSwap) {
        ((SwapDescriptor *)igIntMetaField_GetDefaultDescriptor())->Swap(head, 2);
    }
    object->Finish();
    return size;
}

void FUN_00300490(void **arg0, int arg1, int arg2) {
    void **temp_a0;
    void *temp_s3;
    int temp_v0;
    unsigned int temp_s1;
    unsigned int var_s0;

    temp_s3 = (void *)(((igObjectDispatchView *)arg0)->getMeta()->_metaFields);
    FUN_00304430(DAT_004faf60, arg2, arg0, ((igObjectDispatchView *)arg0)->getMeta()->_name);
    FUN_00304680();
    if (arg1 != 0) {
        temp_v0 = igObject_AllocateStorage((int)arg0, (strlen(arg2) + 2) * 4);
        sprintf(temp_v0, &DAT_004faf78[0], arg2);
        ((igObjectDispatchView *)arg0)->vfunc_16();
        temp_s1 = *(int *)((char *)(temp_s3) + 12);
        var_s0 = *(int *)((char *)(g_igObject_metaObject[0]->_metaFields) + 12);
        FUN_00304430(DAT_004faf80, arg2);
        FUN_00304680();
        for (; var_s0 < temp_s1; var_s0++) {
            int *base = *(int **)((char *)(temp_s3) + 8);
            temp_a0 = (void **)base[var_s0];
            { int d = arg1 - 1; ((igMetaFieldView *)temp_a0)->Print((int)arg0, d, (int)temp_v0); }
        }
        FUN_00304430(DAT_004faf88, arg2);
        FUN_00304680();
        FUN_00300f50((int)arg0, temp_v0);
    }
}

void FUN_00300600(ShallowObject *self, int source) {
    ShallowFields *meta = self->v20()->meta;
    int n = meta->count;
    for (int i = igMetaObject_GetFieldCount(g_igObject_metaObject[0]); i < n; i++) {
        igMetaField_ConstructCopy(meta->arr[i], (int)self, source);
    }
}

void FUN_003006a0(ShallowObject *self, ShallowObject *source) {
    ShallowHolder *holder;
    ShallowFields *meta;
    int n;
    int i;

    holder = self->v20();
    self->v16();
    source->v16();
    meta = holder->meta;
    n = meta->count;
    for (i = igMetaObject_GetFieldCount(g_igObject_metaObject[0]); i < n; i++) {
        igMetaField_DeepCopy(meta->arr[i], (int)self, (int)source);
    }
    self->v3(source);
}

void FUN_00300770(ShallowObject *self, int source) {
    ShallowFields *m = self->v20()->meta;
    int n = m->count;
    int i;
    for (i = igMetaObject_GetFieldCount(g_igObject_metaObject[0]); i < n; i++) {
        igMetaField_ShallowCopy(m->arr[i], (int)self, source);
    }
    self->v4(source);
}

int igObject_IsAlikeDeep(DeepObject *a, DeepObject *b) {
    int i;
    DeepFieldList *fl;
    int n;
    if (b->v20() != a->v20()) return 0;
    fl = a->v20()->fields;
    n = fl->count;
    i = igMetaObject_GetFieldCount(g_igObject_metaObject[0]);
    for (; i < n; i++) {
        if (igMetaField_IsAlikeDeep(fl->items[i], (int)a, (int)b) == 0) return 0;
    }
    return a->v5(b);
}

int igObject_IsAlikeShallow(igObjectDispatchView *arg0, igObjectDispatchView *arg1) {
    igMetaObject *meta;
    int i;
    DeepFieldList *fields;
    int count;
    meta = arg1->getMeta();
    if (meta != arg0->getMeta()) {
        return 0;
    }
    fields = (DeepFieldList *)arg0->getMeta()->_metaFields;
    count = fields->count;
    for (i = igMetaObject_GetFieldCount(g_igObject_metaObject[0]); i < count; i++) {
        if (igMetaField_IsAlikeShallow(fields->items[i], (int)arg0, (int)arg1) == 0) {
            return 0;
        }
    }
    return arg0->vfunc_06(arg1);
}

int igObject_IsAlikeExactly(void *arg0, void *arg1) {
    int meta;
    int i;
    DeepFieldList *fields;
    int count;

    meta = (int)((igObjectDispatchView *)arg1)->getMeta();
    if (meta != (int)((igObjectDispatchView *)arg0)->getMeta()) {
        return 0;
    }
    fields = (DeepFieldList *)((igObjectDispatchView *)arg0)->getMeta()->_metaFields;
    count = fields->count;
    for (i = igMetaObject_GetFieldCount(g_igObject_metaObject[0]); i < count; i++) {
        if (igMetaField_IsAlikeExactly(fields->items[i], (int)arg0, (int)arg1) == 0) {
            return 0;
        }
    }
    return 1;
}

void igObject_VisitFields(VisitorObjectView *object,Visitor callback,void *context){
    FieldVector *fields;
    int count;
    int i;
    VisitorFieldView *field;
    if(callback(object,0,context)==1)return;
    object->Prepare();
    fields=(FieldVector *)object->Meta()->_metaFields;
    count=fields->count;
    for(i=igMetaObject_GetFieldCount((igMetaObject *)g_igObject_metaObject[0]);i<count;++i){
        field=fields->data[i];
        if(callback(object,field,context)!=1)field->Visit(object,callback,context);
    }
}

void FUN_00300c00(int arg0, int arg1, int arg2) {
    switch (arg2) {
    case 1:
        FUN_003006a0((ShallowObject *)arg0, (ShallowObject *)arg1);
        break;
    case 0:
        FUN_00300770((ShallowObject *)arg0, arg1);
        break;
    case 2:
        FUN_00300600((ShallowObject *)arg0, arg1);
        break;
    }
}

/* Generic clone of any object. Asks the source for its metaobject through vtable slot 20 (the
 * GetMetaObject slot), creates an instance of that class on the source's own allocator and copies
 * the contents across. `copyMode` is passed to the contents copy unchanged (the copy dispatches on
 * 0, 1 and 2). */
int igObject_CloneViaMetadata(void **source, int copyMode) {
    int metaObject;
    int copy;

    metaObject = (int)((igObjectDispatchView *)(source))->getMeta();
    copy = igMetaObject_CreateInstance((CreateMeta *)metaObject, (MemoryPool *)(igObject_GetAllocator((int)source)));
    FUN_00300c00(copy, (int)source, copyMode);
    return copy;
}

int igObject_IsKindOf(void *object, igMetaObject *kind) {
    igMetaObject *meta = (igMetaObject *)((KindVC *)object)->vX((int)kind);
    while (meta != 0) {
        if (meta == kind) return 1;
        meta = (igMetaObject *)meta->_parent;
    }
    return 0;
}

void *igObject_GetAllocationBase(void *self) {
    return (char *)self - ((MetadataDispatchView *)self)->GetMetadata()->_runTimeSize;
}

/* Object storage dispatch: every helper re-selects the allocator from the object header
 * (igObject_GetAllocator) and calls one slot of that allocator's vtable, forwarding its arguments
 * unchanged. */
int igObject_AllocateStorage(int object, int size) {
    Allocator *allocator = igObject_GetAllocator(object);
    return allocator->allocate_storage(size);
}

int FUN_00300db0(int object, int size, int alignment) {
    Allocator *allocator = igObject_GetAllocator(object);
    return allocator->slot_220(size, alignment);
}

int FUN_00300e00(int object, int size, int option) {
    Allocator *allocator = igObject_GetAllocator(object);
    return allocator->slot_224(size, option);
}

int FUN_00300e50(int object, int storage, int size) {
    Allocator *allocator = igObject_GetAllocator(object);
    return allocator->slot_232(storage, size);
}

int FUN_00300ea0(int object, int storage, int size, int alignment) {
    Allocator *allocator = igObject_GetAllocator(object);
    return allocator->slot_236(storage, size, alignment);
}

/* A null storage pointer returns without touching the allocator */
void igObject_FreeStorage(int object, int storage) {
    if (storage != 0) {
        Allocator *allocator = igObject_GetAllocator(object);
        allocator->free_storage(storage);
    }
}

/* Same instruction body as igObject_FreeStorage. */
void FUN_00300f50(int object, int storage) {
    if (storage != 0) {
        Allocator *allocator = igObject_GetAllocator(object);
        allocator->free_storage(storage);
    }
}

/* Copy a C string into storage owned by `self`: allocate strlen + 1 bytes with the igObject
 * storage allocator (vtable slot 216, igObject_AllocateStorage), strcpy into it and return the
 * copy. */
int igObject_DuplicateString(int self, int string) {
    int copy;

    copy = igObject_AllocateStorage(self, strlen(string) + 1);
    strcpy(copy, string);
    return copy;
}

Allocator *igObject_GetAllocator(int a0) {
    return ((Allocator *)igAllocator_ResolveEncodedIndex(*(unsigned char *)((char *)a0 + 7)));
}

igSmartPointer<ClonedObject> FUN_00301010(CloneSource *arg1, int arg2) {
    igSmartPointer<ClonedObject> created(arg1->v84(arg2), kRetainReference);
    created.release();
    return created;
}

