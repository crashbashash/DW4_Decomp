igObject *igObject_InitHeader(igObject *p) {
    p->_vtable = (int)&g_igObject_vtable[0];
    ((igRefCountWord *)&p->_refCount)->header.count = 1;
    ((igRefCountWord *)&p->_refCount)->header.flag = 0;
    ((igRefCountWord *)&p->_refCount)->header.poolIndex = 0;
    return p;
}

igObject *igObject_CopyConstructHeader(igObject *self, igObject *source) {
    self->_vtable = (int)&g_igObject_vtable[0];
    if (self != 0) {
        igObject_InitHeader(self);
    }
    ((igRefCountWord *)&self->_refCount)->bytes.flag = ((igRefCountWord *)&source->_refCount)->bytes.flag;
    if (g_objectSystem->active != 0) {
        ((igRefCountWord *)&self->_refCount)->bytes.poolIndex = ((char)igAllocator_EncodeIndex((igMemoryPoolView *)(Memory_FindOwningAllocator((int)(igObject_GetAllocationBase(self))))));
    }
    return self;
}

igObject *igObject_ConstructHeader(igObject *self) {
    void **owner;

    self->_vtable = (int)(&g_igObject_vtable[0]);
    if (self != 0) {
        igObject_InitHeader((igObject *)self);
    }
    if (g_objectSystem->active != 0) {
        owner = (void **)(Memory_FindOwningAllocator((int)(igObject_GetAllocationBase(self))));
        if (owner != 0) {
            ((igRefCountWord *)&self->_refCount)->bytes.poolIndex = ((igMemoryPoolView *)(owner))->GetPoolIndex();
        } else {
            ((igRefCountWord *)&self->_refCount)->bytes.poolIndex = 0;
        }
    } else {
        ((igRefCountWord *)&self->_refCount)->bytes.poolIndex = 0;
    }
    return self;
}

/* Shared default virtual slots that almost every class inherits, so most are empty or return a
 * constant. The slot number is the only name evidence, so the bodies are documented by what they
 * do. The `__<addr>` names are distinct bodies resolved to the same slot. */
int igObject_Destruct(int extra0)
{
}

/* Slot 1 default: empty. */
void Gap__Core__igObject__constructFields(igObject *self, int flags)
{
}

/* Slot 2 default: empty. */
void Gap__Core__igObject__destructFields(igObject *self)
{
}

/* Slot 3 default: empty. */
void igObject_UserDeepCopy(void)
{
}

/* Slot 7 default: empty. */
void Gap__Core__igObject__userConstruct(igObject *self)
{
}

void Gap__Core__igObject__userDestruct(igObject *self)
{
}

/* Slot 4 default: empty. */
void igObject_UserShallowCopy(void)
{
}

/* Slot 5 default: always 1. */
int igObject_UserIsAlikeDeep(void)
{
    return 1;
}

/* Slot 6 default: always 1. */
int igObject_UserIsAlikeShallow(void)
{
    return 1;
}

/* Slot 11 default: empty. */
void Gap__Core__igObject__resetFields(igObject *self, int flags)
{
}

/* Slot 9 default: empty. */
void igObject_InitDefaults(igObject *self)
{
}

/* Slot 10 default: empty. */
void igObject_ReleaseDefaults(igObject *self)
{
}

/* Slot 12 default: empty. */
void igObject_UserPreWrite(void)
{
}

/* Slot 13 default: empty. */
void igObject_UserWriteFilePreProcess(void)
{
}

/* Slot 15 default: empty. */
void igObject_UserPostLoad(void)
{
}

/* Slot 14 default: empty. */
void igObject_UserPostRead(void)
{
}

/* Slot 16 default: empty. */
void igObject_TrimCapacity(int extra0)
{
}

/* Slot 17 default: empty. */
void igObject_UserApplyWriteProxy(void)
{
}

/* Slot 18 default: empty. */
void igObject_UserMakeConcrete(void)
{
}

void igObject_Construct(igObjectDispatchView *object, char *meta) {
    igMemoryPoolView *a;
    igMetaObject *l;
    *(int *)((char *)object + g_objectSystem->vtableProbeOffset) = ((igMetaObject *)meta)->_vTablePointer;
    ((igRefCountWord *)&object->_refCount)->word = 0;
    ((igRefCountWord *)&object->_refCount)->bits.count = 1;
    ((igRefCountWord *)&object->_refCount)->bytes.flag = 0;
    a = (igMemoryPoolView *)Memory_FindOwningAllocator((int)(igObject_GetAllocationBase(object)));
    if (a != 0) {
        ((igRefCountWord *)&object->_refCount)->bytes.poolIndex = a->GetPoolIndex();
    } else {
        ((igRefCountWord *)&object->_refCount)->bytes.poolIndex = 0;
    }
    igObject_ZeroFields(object);
    igObject_ConstructFields(object);
    igObject_ResetUnconstructedFields(object);
    object->InitDefaults();
    object->userConstruct(0);
    l = object->GetMeta();
    if (l != 0) {
        l->_instanceCount = l->_instanceCount + 1;
        if (l->_instances != 0) {
            ObjectPointerList_Append((__internalNonRefCountedObjectList *)l->_instances, (int)object);
        }
    }
}

void igObject_ConstructPooled(igObject *object, char *meta) {
    igMemoryPoolView *g;

    *(int *)((char *)object + g_objectSystem->vtableProbeOffset) = ((igMetaObject *)meta)->_vTablePointer;
    ((igRefCountWord *)&object->_refCount)->pooled.count = 1;
    ((igRefCountWord *)&object->_refCount)->pooled.flag = 0 & 1;
    g = (igMemoryPoolView *)Memory_FindOwningAllocator((int)(igObject_GetAllocationBase(object)));
    if (g != 0) {
        ((igRefCountWord *)&object->_refCount)->pooled.poolIndex = g->GetPoolIndex();
    } else {
        ((igRefCountWord *)&object->_refCount)->pooled.poolIndex = 0;
    }
    igObject_ZeroFields((igObjectDispatchView *)object);
}

void igObject_RegisterInstance(void **object, void *meta) {
    int instances;
    igMetaObject *type;

    if ((meta != 0) && (((igMetaObject *)meta)->_abstractProxy != 0)) {
        ((igObjectDispatchView *)object)->userMakeConcrete((igMetaObject *)meta);
    }
    ((igObjectDispatchView *)object)->constructFields(0);
    ((igObjectDispatchView *)object)->resetFields(0);
    ((igObjectDispatchView *)(object))->userConstruct((int)(1));
    type = ((igObjectDispatchView *)(object))->GetMeta();
    if (type != 0) {
        type->_instanceCount = (int)((int) (type->_instanceCount + 1));
        instances = type->_instances;
        if (instances != 0) {
            ObjectPointerList_Append((__internalNonRefCountedObjectList *)instances, (int)object);
        }
    }
}

/* Class-registration "extra callbacks" factory for igObject (passed to igMetaObject_RegisterClass
 * by igObject_Register): allocate a 12-byte callback array from the metadata allocator selector
 * and construct it empty. Returns the array, or 0 when the allocation fails. */
CallbackArray *igObject_CreateEmptyInitCallbacks(void) {
    CallbackArray *callbacks;

    callbacks = (CallbackArray *)Memory_AllocateBufferDirect(0xC, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    if (callbacks != 0) {
        callbacks = igArray_Construct(callbacks);
    }
    return callbacks;
}

void *igObject_GetNoParentMetaObject(void){return 0;}

int igObject_GetVTable(void) {
    int o[2];

    igObject_InitHeader((igObject *)o);
    return *(int *)((char *)o + g_objectSystem->vtableProbeOffset);
}

void igObject_EnsureRegistered(void){igMetaObject_RunStaticInit(igObject_Register);}

CallbackArray *igObject_Register(void) {
    return igMetaObject_RegisterClass(
        0,
        &g_igObject_metaObject,
        igObject_CreateEmptyInitCallbacks,
        (igMetaObjectGetFunction)igObject_GetNoParentMetaObject,
        (igMetaObjectCallback)igObject_GetMetaObject,
        "igObject",
        8,
        igObject_GetVTable,
        igObject_InitFields,
        0,
        0
    );
}

void *igObject_GetMetaObject(void){return (void *)g_igObject_metaObject;}

int g_igObject_refCountDescriptorCell;
int g_igObject_memPoolIndexDescriptorCell;

void igObject_InitFields(void) {
    void *refCountName;
    void *poolIndexName;
    int *header;
    int *header2;
    int count;
    int count2;
    int pool;
    int pool2;
    igUnsignedIntMetaField *refCountField;
    igUnsignedIntMetaField *poolIndexField;
    void *interned;
    void *interned2;

    refCountField = ((igUnsignedIntMetaField *)igUnsignedIntMetaField_Create((int)(((void **)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)))));
    refCountField->_offset = 4;
    refCountField->_externalEnumStorage = (int)(&g_igObject_refCountDescriptorCell);
    if ("_refCount" == 0) {
        interned = (void *)(0);
    } else {
        if (g_stringPool == 0) {
            pool = ((int)StringPool_Allocate(0x10));
            if (pool != 0) {
                pool = ((int)StringPool_Construct((StringPool *)pool));
            }
            g_stringPool = (StringPool *)pool;
        }
        interned = (void *)(((void *)StringPool_Intern((StringPool *)g_stringPool, (const char *)"_refCount")));
    }
    refCountName = (void *)(interned);
    igMetaField_SetFieldName((igMetaField *)refCountField, &refCountName);
    if (refCountName != 0) {
        header = (int *)((char *)refCountName - 8);
        count = *(int *)((char *)(refCountName) - 4) - 1;
        *(int *)((char *)(refCountName) - 4) = count;
        if (count == 0) {
            StringChunk_ReleaseHeader((StringChunk *)(*header), (StringTokenHeader *)header);
        }
    }
    refCountField->_persistent = 0;
    refCountField->_resetMethod = 3;
    igMetaObject_FinalizeAndAppendField(g_igObject_metaObject, refCountField);
    refCountField->_refCount = (int)refCountField->_refCount - 1;
    if (((unsigned long long)((long long)(int)refCountField->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(refCountField);
    }
    poolIndexField = ((igUnsignedIntMetaField *)igUnsignedIntMetaField_Create((int)(((void **)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)))));
    poolIndexField->_offset = 4;
    poolIndexField->_externalEnumStorage = (int)(&g_igObject_memPoolIndexDescriptorCell);
    if ("_memPoolIndex" == 0) {
        interned2 = (void *)(0);
    } else {
        if (g_stringPool == 0) {
            pool2 = ((int)StringPool_Allocate(0x10));
            if (pool2 != 0) {
                pool2 = ((int)StringPool_Construct((StringPool *)pool2));
            }
            g_stringPool = (StringPool *)pool2;
        }
        interned2 = (void *)(((void *)StringPool_Intern((StringPool *)g_stringPool, (const char *)"_memPoolIndex")));
    }
    poolIndexName = (void *)(interned2);
    igMetaField_SetFieldName((igMetaField *)poolIndexField, &poolIndexName);
    if (poolIndexName != 0) {
        header2 = (int *)((char *)poolIndexName - 8);
        count2 = *(int *)((char *)(poolIndexName) - 4) - 1;
        *(int *)((char *)(poolIndexName) - 4) = count2;
        if (count2 == 0) {
            StringChunk_ReleaseHeader((StringChunk *)(*header2), (StringTokenHeader *)header2);
        }
    }
    poolIndexField->_persistent = 0;
    poolIndexField->_resetMethod = 3;
    igMetaObject_FinalizeAndAppendField(g_igObject_metaObject, poolIndexField);
    poolIndexField->_refCount = (int)poolIndexField->_refCount - 1;
    if (((unsigned long long)((long long)(int)poolIndexField->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(poolIndexField);
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

int Memory_FreeBufferAliasC(void *block)
{
    return Memory_FreeBuffer(block);
}

void igObject_Destroy(void *input) {
    if (g_objectSystem) {
        igObjectDispatchView *object = (igObjectDispatchView *)input;
        if (!g_objectSystem->active) {
            object->userDestruct();
            object->ReleaseDefaults();
            object->Destruct();
            Memory_FreeBuffer(object);
            return;
        }
        igMetaObject *type = object->GetMeta();
        type->_instanceCount = (int)((unsigned)type->_instanceCount - 1);
        void *instances = (void *)type->_instances;
        if (instances) ObjectPointerList_EraseAt((__internalNonRefCountedObjectList *)instances, ObjectPointerList_FindIndex((char *)instances, (int)object));
        object->TrimCapacity();
        object->userDestruct();
        object->ReleaseDefaults();
        igObject_DestructFieldValues((int *)object);
        igObject_ClearFieldValues((int *)object);
        Memory_FreeBuffer(igObject_GetAllocationBase(object));
    }
}

static inline int isValid(igMetaObject *m) { return (m->_validity & 4) != 0; }

void igObject_ZeroFields(igObjectDispatchView *object) {
    igMetaObject *meta = object->GetMeta();
    if (((meta != 0) && isValid(meta)) || (g_objectSystem->started == 0) || (g_objectSystem->active != 0)) {
        __internalObjectList *fields = (__internalObjectList *)meta->_metaFields;
        int first = ((__internalObjectList *)g_igObject_metaObject->_metaFields)->_count;
        int count = fields->_count;
        for (int i = first; i < count; i++) {
            ((igMetaFieldView **)fields->_data)[i]->ZeroValue((int)object);
        }
    }
}

void igObject_ConstructFields(igObjectDispatchView *object) {
    __internalObjectList *fields = (__internalObjectList *)object->GetMeta()->_metaFields;
    int first = ((__internalObjectList *)g_igObject_metaObject->_metaFields)->_count;
    int count = fields->_count;
    for (int i = first; i < count; i++) {
        ((igMetaFieldView **)fields->_data)[i]->ConstructValue((int)object);
    }
    object->constructFields(1);
}

void igObject_ResetFields(igObjectDispatchView *object) {
    __internalObjectList *fields = (__internalObjectList *)object->GetMeta()->_metaFields;
    int first = ((__internalObjectList *)g_igObject_metaObject->_metaFields)->_count;
    int count = fields->_count;
    for (int i = first; i < count; i++) {
        igMetaField_Reset(((igMetaField **)fields->_data)[i], object);
    }
    object->resetFields(1);
}

void igObject_ResetUnconstructedFields(igObjectDispatchView *object) {
    __internalObjectList *fields = (__internalObjectList *)object->GetMeta()->_metaFields;
    int first = ((__internalObjectList *)g_igObject_metaObject->_metaFields)->_count;
    int count = fields->_count;
    for (int i = first; i < count; i++) {
        igMetaFieldView *field = ((igMetaFieldView **)fields->_data)[i];
        if (field->IsConstruct() == 0) {
            igMetaField_Reset((igMetaField *)field, object);
        }
    }
    object->resetFields(1);
}

void igObject_DestructFieldValues(int *object) {
    __internalObjectList *q;
    int i;
    int n;

    ((igObjectDispatchView *)object)->destructFields();
    q = (__internalObjectList *)((igObjectDispatchView *)object)->GetMeta()->_metaFields;
    i = ((__internalObjectList *)g_igObject_metaObject->_metaFields)->_count;
    n = q->_count;
    for (; i < n; i++) {
        ((igMetaFieldView **)q->_data)[i]->DestructValue((int)object);
    }
}

void igObject_ClearFieldValues(int *object) {
    __internalObjectList *q;
    int i;
    int n;

    q = (__internalObjectList *)((igObjectDispatchView *)object)->GetMeta()->_metaFields;
    i = ((__internalObjectList *)g_igObject_metaObject->_metaFields)->_count;
    n = q->_count;
    for (; i < n; i++) {
        ((igMetaFieldView **)q->_data)[i]->ClearValue((int)object);
    }
}

int igObject_GetSerializedSize(igObjectDispatchView *object) {
    igMetaObject *m0 = object->GetMeta();
    igMetaObject *m;
    int size, i, n;
    igMetaObject *(*fp)();
    fp = (igMetaObject *(*)())m0->_writeProxy;
    if (fp != 0) { m = fp(); } else { m = m0; }
    if (m->_persistent == 0) return 0;
    size = 8;
    i = igMetaObject_GetFieldCount(g_igObject_metaObject);
    n = igMetaObject_GetFieldCount(m);
    for (; i < n; i++) { size += ((igMetaFieldView *)igMetaObject_GetFieldAt(m, i))->GetRawFieldMemSize((int)object); }
    return size;
}

int igObject_WritePersistentFields(igObjectDispatchView *object, int *buffer, igIGBFile *file, igTDataList<igMetaObject *> *metaObjectList, unsigned char endianSwap) {
    igMetaObject *meta = object->GetMeta();
    if (meta->_persistent == 0) {
        return 0;
    }
    object->userPreWrite();
    int index = 0;
    igMetaObject *writeMeta = (meta->_writeProxy != 0) ? ((igMetaObject *(*)())meta->_writeProxy)() : meta;
    if (metaObjectList != 0) {
        index = igMetaObject_AddToMetaObjectList(metaObjectList, writeMeta);
    }
    int count = igMetaObject_GetFieldCount(writeMeta);
    int i = igMetaObject_GetFieldCount(g_igObject_metaObject);
    buffer[0] = index;
    buffer[1] = igObject_GetSerializedSize(object);
    if (endianSwap) {
        ((igMetaFieldView *)igIntMetaField_GetDefaultDescriptor())->SwapBytes(buffer, 2);
    }
    buffer += 2;
    for (; i < count; i++) {
        igMetaField *field = (igMetaField *)igMetaObject_GetFieldAt(writeMeta, i);
        if (field->_persistent == 1 && field->_isRunTime == 0) {
            buffer = (int *)((char *)buffer + igMetaField_WritePersistentValue(field, object, buffer, file, endianSwap));
        }
    }
    return igObject_GetSerializedSize(object);
}

int igObject_ReadFields(igObjectDispatchView *object, FieldRecordHead *head, igIGBFile *file, igTDataList<igMetaObject *> *metaObjectList, unsigned char endianSwap) {
    igMetaObject *meta;
    char *data;
    int i;
    int count;
    int runTimeFields, readFields;
    igMetaField *field;
    meta = object->GetMeta();
    if (meta->_persistent == 0) return 0;
    if (endianSwap) {
        ((igMetaFieldView *)igIntMetaField_GetDefaultDescriptor())->SwapBytes(head, 3);
    }
    data = (char *)&head[1];
    i = igMetaObject_GetFieldCount(g_igObject_metaObject);
    count = igMetaObject_GetFieldCount(meta);
    runTimeFields = 0;
    readFields = 0;
    for (; i < count; i++) {
        field = (igMetaField *)igMetaObject_GetFieldAt(meta, i);
        if (field->_isRunTime != 0) {
            runTimeFields += 1;
            ((igMetaFieldView *)field)->ConstructValue((int)object);
            if (igObject_IsKindOf(field, (igMetaObject *)g_igRefMetaField_metaObject) == 0 || ((igRefMetaField *)field)->_construct == 0) igMetaField_Reset(field, object);
        } else if (readFields >= head->fieldCount) {
            ((igMetaFieldView *)field)->ConstructValue((int)object);
            if (igObject_IsKindOf(field, (igMetaObject *)g_igRefMetaField_metaObject) == 0 || ((igRefMetaField *)field)->_construct == 0) igMetaField_Reset(field, object);
        } else {
            if (endianSwap) ((igMetaFieldView *)igShortMetaField_GetDefaultDescriptor())->SwapBytes(data, 2);
            if (i < *(short *)data + runTimeFields) {
                ((igMetaFieldView *)field)->ConstructValue((int)object);
                if (igObject_IsKindOf(field, (igMetaObject *)g_igRefMetaField_metaObject) == 0 || ((igRefMetaField *)field)->_construct == 0) igMetaField_Reset(field, object);
                if (endianSwap) ((igMetaFieldView *)igShortMetaField_GetDefaultDescriptor())->SwapBytes(data, 2);
            } else {
                readFields += 1;
                data += igMetaField_ReadFieldMem((igMetaFieldView *)field, (char *)object, data, file, endianSwap);
            }
        }
    }
    {
        int size = head->size;
        if (endianSwap) ((igMetaFieldView *)igIntMetaField_GetDefaultDescriptor())->SwapBytes(head, 3);
        object->userPostRead();
        return size;
    }
}

int igObject_ReadPersistentFields(igObjectDispatchView *object, FieldRecordHead *head, igDirectoryView *dir, igTDataList<igMetaObject *> *metaObjectList, unsigned char endianSwap) {
    igMetaObject *meta;
    igTDataList<igTDataList<short> *> *lists;
    igTDataList<short> *offsets;
    char *data;
    int i;
    int first;
    int count;
    int done;
    int next;
    short limit;
    igMetaFieldView *field;
    int size;
    meta = object->GetMeta();
    if (meta->_persistent == 0) {
        return 0;
    }
    lists = dir->_metaFieldPerObjectIndices;
    if (endianSwap) {
        ((igMetaFieldView *)igIntMetaField_GetDefaultDescriptor())->SwapBytes(head, 2);
    }
    offsets = lists->_data[head->kind];
    data = (char *)&head->fieldCount;  /* this record format has no field count: the fields start in its place */
    first = igMetaObject_GetFieldCount(g_igObject_metaObject);
    count = igMetaObject_GetFieldCount(meta);
    done = 0;
    next = 0;
    if (offsets->_count == 0) {
        limit = count;
    } else {
        limit = offsets->_data[next++];
    }
    for (i = first; i < count; i++) {
        field = (igMetaFieldView *)igMetaObject_GetFieldAt(meta, i);
        if (i < limit) {
            field->ConstructValue((int)object);
            if (igObject_IsKindOf((igObject *)field, (igMetaObject *)g_igRefMetaField_metaObject) == 0 || ((igRefMetaField *)field)->_construct == 0) {
                igMetaField_Reset((igMetaField *)field, object);
            }
        } else {
            done++;
            data += igMetaField_ReadRawFieldMemAligned(field, object, data, dir, endianSwap);
            if (done == offsets->_count) {
                limit = count;
            } else {
                limit = offsets->_data[next++];
            }
        }
    }
    size = head->size;
    if (endianSwap) {
        ((igMetaFieldView *)igIntMetaField_GetDefaultDescriptor())->SwapBytes(head, 2);
    }
    object->userPostRead();
    return size;
}

void igObject_Print(void **object, int depth, int indent) {
    void **field;
    __internalObjectList *fields;
    int prefix;
    unsigned int count;
    unsigned int i;

    fields = (__internalObjectList *)(((igObjectDispatchView *)object)->GetMeta()->_metaFields);
    igReport_Printf("%s0x%x (type %s)\n", indent, object, ((igObjectDispatchView *)object)->GetMeta()->_name);
    igReport_Flush();
    if (depth != 0) {
        prefix = (int)igObject_AllocateStorage((igObject *)object, (strlen((const char *)indent) + 2) * 4);
        sprintf((char *)prefix, "\t%s", indent);
        ((igObjectDispatchView *)object)->TrimCapacity();
        count = fields->_count;
        i = ((__internalObjectList *)g_igObject_metaObject->_metaFields)->_count;
        igReport_Printf("%s{\n", indent);
        igReport_Flush();
        for (; i < count; i++) {
            int *base = (int *)fields->_data;
            field = (void **)base[i];
            { int d = depth - 1; ((igMetaFieldView *)field)->Print((int)object, d, (int)prefix); }
        }
        igReport_Printf("%s}\n", indent);
        igReport_Flush();
        igObject_FreeMemory((igObject *)object, (void *)prefix);
    }
}

void igObject_CopyFields(igObjectDispatchView *self, int source) {
    __internalObjectList *meta = (__internalObjectList *)self->GetMeta()->_metaFields;
    int n = meta->_count;
    for (int i = igMetaObject_GetFieldCount(g_igObject_metaObject); i < n; i++) {
        igMetaField_ConstructCopy(((int *)meta->_data)[i], (int)self, source);
    }
}

void igObject_DeepCopy(igObjectDispatchView *self, igObjectDispatchView *source) {
    igMetaObject *holder;
    __internalObjectList *meta;
    int n;
    int i;

    holder = self->GetMeta();
    self->TrimCapacity();
    source->TrimCapacity();
    meta = (__internalObjectList *)holder->_metaFields;
    n = meta->_count;
    for (i = igMetaObject_GetFieldCount(g_igObject_metaObject); i < n; i++) {
        igMetaField_DeepCopy(((int *)meta->_data)[i], (int)self, (int)source);
    }
    self->userDeepCopy(source);
}

void igObject_ShallowCopy(igObjectDispatchView *self, int source) {
    __internalObjectList *m = (__internalObjectList *)self->GetMeta()->_metaFields;
    int n = m->_count;
    int i;
    for (i = igMetaObject_GetFieldCount(g_igObject_metaObject); i < n; i++) {
        igMetaField_ShallowCopy(((int *)m->_data)[i], (int)self, source);
    }
    self->userShallowCopy(source);
}

int igObject_IsAlikeDeep(igObjectDispatchView *a, igObjectDispatchView *b) {
    int i;
    __internalObjectList *fl;
    int n;
    if (b->GetMeta() != a->GetMeta()) return 0;
    fl = (__internalObjectList *)a->GetMeta()->_metaFields;
    n = fl->_count;
    i = igMetaObject_GetFieldCount(g_igObject_metaObject);
    for (; i < n; i++) {
        if (igMetaField_IsAlikeDeep(((int *)fl->_data)[i], (int)a, (int)b) == 0) return 0;
    }
    return a->userIsAlikeDeep(b);
}

int igObject_IsAlikeShallow(igObjectDispatchView *a, igObjectDispatchView *b) {
    igMetaObject *meta;
    int i;
    __internalObjectList *fields;
    int count;
    meta = b->GetMeta();
    if (meta != a->GetMeta()) {
        return 0;
    }
    fields = (__internalObjectList *)a->GetMeta()->_metaFields;
    count = fields->_count;
    for (i = igMetaObject_GetFieldCount(g_igObject_metaObject); i < count; i++) {
        if (igMetaField_IsAlikeShallow(((int *)fields->_data)[i], (int)a, (int)b) == 0) {
            return 0;
        }
    }
    return a->userIsAlikeShallow(b);
}

int igObject_IsAlikeExactly(void *a, void *b) {
    int meta;
    int i;
    __internalObjectList *fields;
    int count;

    meta = (int)((igObjectDispatchView *)b)->GetMeta();
    if (meta != (int)((igObjectDispatchView *)a)->GetMeta()) {
        return 0;
    }
    fields = (__internalObjectList *)((igObjectDispatchView *)a)->GetMeta()->_metaFields;
    count = fields->_count;
    for (i = igMetaObject_GetFieldCount(g_igObject_metaObject); i < count; i++) {
        if (igMetaField_IsAlikeExactly(((int *)fields->_data)[i], (int)a, (int)b) == 0) {
            return 0;
        }
    }
    return 1;
}

void igObject_VisitFields(igObjectDispatchView *object,Visitor callback,void *context){
    __internalObjectList *fields;
    int count;
    int i;
    igMetaFieldView *field;
    if(callback(object,0,context)==1)return;
    object->TrimCapacity();
    fields=(__internalObjectList *)object->GetMeta()->_metaFields;
    count=fields->_count;
    for(i=igMetaObject_GetFieldCount((igMetaObject *)g_igObject_metaObject);i<count;++i){
        field=((igMetaFieldView **)fields->_data)[i];
        if(callback(object,field,context)!=1)field->ReleaseElements((int)object,(int)callback,(int)context);
    }
}

void igObject_Copy(int dest, int source, int copyMode) {
    switch (copyMode) {
    case 1:
        igObject_DeepCopy((igObjectDispatchView *)dest, (igObjectDispatchView *)source);
        break;
    case 0:
        igObject_ShallowCopy((igObjectDispatchView *)dest, source);
        break;
    case 2:
        igObject_CopyFields((igObjectDispatchView *)dest, source);
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

    metaObject = (int)((igObjectDispatchView *)(source))->GetMeta();
    copy = (int)igMetaObject_CreateInstance((igMetaObject *)metaObject, (igMemoryPoolView *)(igObject_GetAllocator((igObject *)source)));
    igObject_Copy(copy, (int)source, copyMode);
    return copy;
}

int igObject_IsKindOf(void *object, igMetaObject *kind) {
    igMetaObject *meta = ((igObjectDispatchView *)object)->GetMeta();
    while (meta != 0) {
        if (meta == kind) return 1;
        meta = (igMetaObject *)meta->_parent;
    }
    return 0;
}

void *igObject_GetAllocationBase(void *self) {
    return (char *)self - ((igObjectDispatchView *)self)->GetMeta()->_runTimeSize;
}

/* Object storage dispatch: every helper re-selects the allocator from the object header
 * (igObject_GetAllocator) and calls one slot of that allocator's vtable, forwarding its arguments
 * unchanged. */
void *igObject_AllocateStorage(igObject *object, int size) {
    igMemoryPoolView *allocator = igObject_GetAllocator(object);
    return allocator->Allocate(size);
}

void *igObject_MallocAligned(igObject *object, int size, unsigned short alignment) {
    igMemoryPoolView *allocator = igObject_GetAllocator(object);
    return allocator->AllocateAligned(size, alignment);
}

void *igObject_Callocate(igObject *object, int count, int size) {
    igMemoryPoolView *allocator = igObject_GetAllocator(object);
    return allocator->Callocate(count, size);
}

void *igObject_Reallocate(igObject *object, void *storage, int size) {
    igMemoryPoolView *allocator = igObject_GetAllocator(object);
    return allocator->Reallocate(storage, size);
}

void *igObject_ReallocateAligned(igObject *object, void *storage, int size, unsigned short alignment) {
    igMemoryPoolView *allocator = igObject_GetAllocator(object);
    return allocator->ReallocateAligned(storage, size, alignment);
}

/* A null storage pointer returns without touching the allocator */
void igObject_FreeStorage(int object, int storage) {
    if (storage != 0) {
        igMemoryPoolView *allocator = igObject_GetAllocator((igObject *)object);
        allocator->Free((void *)storage);
    }
}

/* Same instruction body as igObject_FreeStorage. */
void igObject_FreeMemory(igObject *object, void *storage) {
    if (storage != 0) {
        igMemoryPoolView *allocator = igObject_GetAllocator(object);
        allocator->Free(storage);
    }
}

/* Copy a C string into storage owned by `self`: allocate strlen + 1 bytes with the igObject
 * storage allocator (vtable slot 216, igObject_AllocateStorage), strcpy into it and return the
 * copy. */
char *igObject_DuplicateString(void *self, const char *string) {
    char *copy;

    copy = (char *)igObject_AllocateStorage((igObject *)self, strlen(string) + 1);
    strcpy(copy, string);
    return copy;
}

igMemoryPoolView *igObject_GetAllocator(igObject *object) {
    return ((igMemoryPoolView *)igAllocator_ResolveEncodedIndex(((igRefCountWord *)&object->_refCount)->bytes.poolIndex));
}

igSmartPointer<igObject> igObject_Clone(igObjectDispatchView *source, int copyMode) {
    igSmartPointer<igObject> created(source->CloneViaMetadata(copyMode), kRetainReference);
    created.release();
    return created;
}

