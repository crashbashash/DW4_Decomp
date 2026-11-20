namespace Gap {
namespace Core {

igObject::igObject() {
    ((igRefCountWord *)&_refCount)->header.count = 1;
    ((igRefCountWord *)&_refCount)->header.flag = 0;
    ((igRefCountWord *)&_refCount)->header.poolIndex = 0;
}

/* The copy constructor and the bootstrap constructor are the ones the bootstrap classes (igMetaField,
 * igMetaObject, igMemoryPool, __internalNonRefCountedObjectList) construct their base with: the header
 * through the default constructor, then the pool index the object was allocated from. The copy also keeps
 * the source's flag bit. */
igObject::igObject(const igObject &other) {
    new (this, 0) igObject;
    ((igRefCountWord *)&_refCount)->bytes.flag = ((igRefCountWord *)&other._refCount)->bytes.flag;
    if (g_objectSystem->active != 0) {
        ((igRefCountWord *)&_refCount)->bytes.poolIndex = ((char)igAllocator_EncodeIndex((igMemoryPoolView *)(Memory_FindOwningAllocator((int)(getClassStorage())))));
    }
}

igObject::igObject(bool bootstrap) {
    void **owner;

    new (this, 0) igObject;
    if (g_objectSystem->active != 0) {
        owner = (void **)(Memory_FindOwningAllocator((int)(getClassStorage())));
        if (owner != 0) {
            ((igRefCountWord *)&_refCount)->bytes.poolIndex = ((igMemoryPoolView *)(owner))->GetPoolIndex();
        } else {
            ((igRefCountWord *)&_refCount)->bytes.poolIndex = 0;
        }
    } else {
        ((igRefCountWord *)&_refCount)->bytes.poolIndex = 0;
    }
}

/* Shared default virtual slots that almost every class inherits, so most are empty or return a
 * constant. The slot number is the only name evidence, so the bodies are documented by what they
 * do. The `__<addr>` names are distinct bodies resolved to the same slot. */
void igObject::__bootstrapDestruct()
{
}

/* Slot 1 default: empty. */
void igObject::constructFields(int flags)
{
}

/* Slot 2 default: empty. */
void igObject::destructFields()
{
}

/* Slot 3 default: empty. */
void igObject::userDeepCopy(igObject *source)
{
}

/* Slot 7 default: empty. */
void igObject::userConstruct(int flag)
{
}

void igObject::userDestruct()
{
}

/* Slot 4 default: empty. */
void igObject::userShallowCopy(int source)
{
}

/* Slot 5 default: always 1. */
int igObject::userIsAlikeDeep(igObject *other)
{
    return 1;
}

/* Slot 6 default: always 1. */
int igObject::userIsAlikeShallow(igObject *other)
{
    return 1;
}

/* Slot 11 default: empty. */
void igObject::resetFields(int flags)
{
}

/* Slot 9 default: empty. */
void igObject::initDefaults()
{
}

/* Slot 10 default: empty. */
void igObject::releaseDefaults()
{
}

/* Slot 12 default: empty. */
void igObject::userPreWrite()
{
}

/* Slot 13 default: empty. */
void igObject::userWriteFilePreProcess()
{
}

/* Slot 15 default: empty. */
void igObject::userPostLoad()
{
}

/* Slot 14 default: empty. */
void igObject::userPostRead()
{
}

/* Slot 16 default: empty. */
void igObject::trimCapacity()
{
}

/* Slot 17 default: empty. */
void igObject::userApplyWriteProxy(int value)
{
}

/* Slot 18 default: empty. */
void igObject::userMakeConcrete(igMetaObject *meta)
{
}

void igObject::constructDerived(igMetaObject *meta) {
    igMemoryPoolView *a;
    igMetaObject *l;
    *(int *)((char *)this + g_objectSystem->vtableProbeOffset) = meta->_vTablePointer;
    ((igRefCountWord *)&_refCount)->word = 0;
    ((igRefCountWord *)&_refCount)->bits.count = 1;
    ((igRefCountWord *)&_refCount)->bytes.flag = 0;
    a = (igMemoryPoolView *)Memory_FindOwningAllocator((int)(getClassStorage()));
    if (a != 0) {
        ((igRefCountWord *)&_refCount)->bytes.poolIndex = a->GetPoolIndex();
    } else {
        ((igRefCountWord *)&_refCount)->bytes.poolIndex = 0;
    }
    commission();
    construct();
    internalResetFields();
    initDefaults();
    userConstruct(0);
    l = getMeta();
    if (l != 0) {
        l->_instanceCount = l->_instanceCount + 1;
        if (l->_instances != 0) {
            ObjectPointerList_Append((__internalNonRefCountedObjectList *)l->_instances, (int)this);
        }
    }
}

void igObject::constructDerivedFromFile(igMetaObject *meta) {
    igMemoryPoolView *g;

    *(int *)((char *)this + g_objectSystem->vtableProbeOffset) = meta->_vTablePointer;
    ((igRefCountWord *)&_refCount)->pooled.count = 1;
    ((igRefCountWord *)&_refCount)->pooled.flag = 0 & 1;
    g = (igMemoryPoolView *)Memory_FindOwningAllocator((int)(getClassStorage()));
    if (g != 0) {
        ((igRefCountWord *)&_refCount)->pooled.poolIndex = g->GetPoolIndex();
    } else {
        ((igRefCountWord *)&_refCount)->pooled.poolIndex = 0;
    }
    commission();
}

void igObject::finishConstructDerivedFromFile(igMetaObject *meta) {
    int instances;
    igMetaObject *type;

    if ((meta != 0) && (meta->_abstractProxy != 0)) {
        userMakeConcrete(meta);
    }
    constructFields(0);
    resetFields(0);
    userConstruct(1);
    type = getMeta();
    if (type != 0) {
        type->_instanceCount = (int)((int) (type->_instanceCount + 1));
        instances = type->_instances;
        if (instances != 0) {
            ObjectPointerList_Append((__internalNonRefCountedObjectList *)instances, (int)this);
        }
    }
}

/* Class-registration "extra callbacks" factory for igObject (passed to igMetaObject_RegisterClass by
 * Gap::Core::igObject::arkRegisterInternal): allocate a 12-byte callback array from the metadata allocator
 * selector and construct it empty. Returns the array, or 0 when the allocation fails. */
CallbackArray *igObject::emptyArkRegisterInternal() {
    CallbackArray *callbacks;

    callbacks = (CallbackArray *)Memory_AllocateBufferDirect(0xC, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    if (callbacks != 0) {
        callbacks = igArray_Construct(callbacks);
    }
    return callbacks;
}

igMetaObject *igObject::emptyGetClassMetaSafe(){return 0;}

void *igObject::retrieveVTablePointer() {
    igObject temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igObject::arkRegister(){igMetaObject_RunStaticInit(arkRegisterInternal);}

CallbackArray *igObject::arkRegisterInternal() {
    return igMetaObject_RegisterClass(
        0,
        &_Meta,
        emptyArkRegisterInternal,
        (igMetaObjectGetFunction)emptyGetClassMetaSafe,
        (igMetaObjectCallback)getClassMetaSafe,
        "igObject",
        8,
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        arkRegisterInitialize,
        0,
        0
    );
}
}
}

int g_igObject_refCountDescriptorCell;
int g_igObject_memPoolIndexDescriptorCell;

namespace Gap {
namespace Core {

void igObject::arkRegisterInitialize() {
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

    refCountField = ((igUnsignedIntMetaField *)igUnsignedIntMetaField_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
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
    ((igMetaField *)refCountField)->setFieldName(&refCountName);
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
    igMetaObject_FinalizeAndAppendField(_Meta, refCountField);
    refCountField->_refCount = (int)refCountField->_refCount - 1;
    if (((unsigned long long)((long long)(int)refCountField->_refCount << 0x29) >> 0x29) == 0) {
        ((igObject *)refCountField)->internalRelease();
    }
    poolIndexField = ((igUnsignedIntMetaField *)igUnsignedIntMetaField_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
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
    ((igMetaField *)poolIndexField)->setFieldName(&poolIndexName);
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
    igMetaObject_FinalizeAndAppendField(_Meta, poolIndexField);
    poolIndexField->_refCount = (int)poolIndexField->_refCount - 1;
    if (((unsigned long long)((long long)(int)poolIndexField->_refCount << 0x29) >> 0x29) == 0) {
        ((igObject *)poolIndexField)->internalRelease();
    }
}
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

namespace Gap {
namespace Core {

/* The kit declares it const; the release itself writes the object, through a non-const pointer. */
void igObject::internalRelease() const {
    if (g_objectSystem) {
        igObject *object = (igObject *)this;
        if (!g_objectSystem->active) {
            object->userDestruct();
            object->releaseDefaults();
            object->__bootstrapDestruct();
            Memory_FreeBuffer(object);
            return;
        }
        igMetaObject *type = object->getMeta();
        type->_instanceCount = (int)((unsigned)type->_instanceCount - 1);
        void *instances = (void *)type->_instances;
        if (instances) ObjectPointerList_EraseAt((__internalNonRefCountedObjectList *)instances, ObjectPointerList_FindIndex((__internalNonRefCountedObjectList *)instances, (int)object));
        object->trimCapacity();
        object->userDestruct();
        object->releaseDefaults();
        object->destruct();
        object->decommission();
        Memory_FreeBuffer(object->getClassStorage());
    }
}
}
}

static inline int isValid(igMetaObject *m) { return (m->_validity & 4) != 0; }

namespace Gap {
namespace Core {

void igObject::commission() {
    igMetaObject *meta = getMeta();
    if (((meta != 0) && isValid(meta)) || (g_objectSystem->started == 0) || (g_objectSystem->active != 0)) {
        __internalObjectList *fields = (__internalObjectList *)meta->_metaFields;
        int first = ((__internalObjectList *)Gap::Core::igObject::getClassMeta()->_metaFields)->_count;
        int count = fields->_count;
        for (int i = first; i < count; i++) {
            ((igMetaFieldView **)fields->_data)[i]->ZeroValue((int)this);
        }
    }
}

void igObject::construct() {
    __internalObjectList *fields = (__internalObjectList *)getMeta()->_metaFields;
    int first = ((__internalObjectList *)Gap::Core::igObject::getClassMeta()->_metaFields)->_count;
    int count = fields->_count;
    for (int i = first; i < count; i++) {
        ((igMetaFieldView **)fields->_data)[i]->ConstructValue((int)this);
    }
    constructFields(1);
}
}
}

void igObject_ResetFields(igObjectDispatchView *object) {
    __internalObjectList *fields = (__internalObjectList *)object->GetMeta()->_metaFields;
    int first = ((__internalObjectList *)Gap::Core::igObject::getClassMeta()->_metaFields)->_count;
    int count = fields->_count;
    for (int i = first; i < count; i++) {
        ((Gap::Core::igMetaField *)(((igMetaField **)fields->_data)[i]))->reset((Gap::Core::igObject *)object);
    }
    object->resetFields(1);
}

namespace Gap {
namespace Core {

void igObject::internalResetFields() {
    __internalObjectList *fields = (__internalObjectList *)getMeta()->_metaFields;
    int first = ((__internalObjectList *)Gap::Core::igObject::getClassMeta()->_metaFields)->_count;
    int count = fields->_count;
    for (int i = first; i < count; i++) {
        igMetaFieldView *field = ((igMetaFieldView **)fields->_data)[i];
        if (field->IsConstruct() == 0) {
            ((igMetaField *)field)->reset(this);
        }
    }
    resetFields(1);
}

void igObject::destruct() {
    __internalObjectList *q;
    int i;
    int n;

    destructFields();
    q = (__internalObjectList *)getMeta()->_metaFields;
    i = ((__internalObjectList *)Gap::Core::igObject::getClassMeta()->_metaFields)->_count;
    n = q->_count;
    for (; i < n; i++) {
        ((igMetaFieldView **)q->_data)[i]->DestructValue((int)this);
    }
}

void igObject::decommission() {
    __internalObjectList *q;
    int i;
    int n;

    q = (__internalObjectList *)getMeta()->_metaFields;
    i = ((__internalObjectList *)Gap::Core::igObject::getClassMeta()->_metaFields)->_count;
    n = q->_count;
    for (; i < n; i++) {
        ((igMetaFieldView **)q->_data)[i]->ClearValue((int)this);
    }
}

int igObject::getIoSize() const {
    igMetaObject *m0 = ((igObjectDispatchView *)this)->GetMeta();
    igMetaObject *m;
    int size, i, n;
    igMetaObject *(*fp)();
    fp = (igMetaObject *(*)())m0->_writeProxy;
    if (fp != 0) { m = fp(); } else { m = m0; }
    if (m->_persistent == 0) return 0;
    size = 8;
    i = igMetaObject_GetFieldCount(Gap::Core::igObject::_Meta);
    n = igMetaObject_GetFieldCount(m);
    for (; i < n; i++) { size += ((igMetaFieldView *)igMetaObject_GetFieldAt(m, i))->GetRawFieldMemSize((int)(igObjectDispatchView *)this); }
    return size;
}
}
}

int igObject_WritePersistentFields(igObjectDispatchView *object, int *buffer, igIGBFile *file, igTDataList<igMetaObject *> *metaObjectList, bool endianSwap) {
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
    int i = igMetaObject_GetFieldCount(Gap::Core::igObject::getClassMeta());
    buffer[0] = index;
    buffer[1] = ((Gap::Core::igObject *)object)->getIoSize();
    if (endianSwap) {
        ((igMetaFieldView *)igIntMetaField_GetDefaultDescriptor())->SwapBytes(buffer, 2);
    }
    buffer += 2;
    for (; i < count; i++) {
        igMetaField *field = (igMetaField *)igMetaObject_GetFieldAt(writeMeta, i);
        if (field->_persistent == 1 && field->_isRunTime == 0) {
            buffer = (int *)((char *)buffer + ((Gap::Core::igMetaField *)field)->writeToMemory((Gap::Core::igObject *)object, buffer, (igDirectory *)file, endianSwap));
        }
    }
    return ((Gap::Core::igObject *)object)->getIoSize();
}

int igObject_ReadFields(igObjectDispatchView *object, FieldRecordHead *head, igIGBFile *file, igTDataList<igMetaObject *> *metaObjectList, bool endianSwap) {
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
    i = igMetaObject_GetFieldCount(Gap::Core::igObject::getClassMeta());
    count = igMetaObject_GetFieldCount(meta);
    runTimeFields = 0;
    readFields = 0;
    for (; i < count; i++) {
        field = (igMetaField *)igMetaObject_GetFieldAt(meta, i);
        if (field->_isRunTime != 0) {
            runTimeFields += 1;
            ((igMetaFieldView *)field)->ConstructValue((int)object);
            if (((Gap::Core::igObject *)field)->isOfType((igMetaObject *)g_igRefMetaField_metaObject) == 0 || ((igRefMetaField *)field)->_construct == 0) ((Gap::Core::igMetaField *)field)->reset((Gap::Core::igObject *)object);
        } else if (readFields >= head->fieldCount) {
            ((igMetaFieldView *)field)->ConstructValue((int)object);
            if (((Gap::Core::igObject *)field)->isOfType((igMetaObject *)g_igRefMetaField_metaObject) == 0 || ((igRefMetaField *)field)->_construct == 0) ((Gap::Core::igMetaField *)field)->reset((Gap::Core::igObject *)object);
        } else {
            if (endianSwap) ((igMetaFieldView *)igShortMetaField_GetDefaultDescriptor())->SwapBytes(data, 2);
            if (i < *(short *)data + runTimeFields) {
                ((igMetaFieldView *)field)->ConstructValue((int)object);
                if (((Gap::Core::igObject *)field)->isOfType((igMetaObject *)g_igRefMetaField_metaObject) == 0 || ((igRefMetaField *)field)->_construct == 0) ((Gap::Core::igMetaField *)field)->reset((Gap::Core::igObject *)object);
                if (endianSwap) ((igMetaFieldView *)igShortMetaField_GetDefaultDescriptor())->SwapBytes(data, 2);
            } else {
                readFields += 1;
                data += ((Gap::Core::igMetaField *)field)->readFromMemoryVersion3((Gap::Core::igObject *)object, data, (igDirectory *)file, endianSwap);
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

int igObject_ReadPersistentFields(igObjectDispatchView *object, FieldRecordHead *head, igDirectoryView *dir, igTDataList<igMetaObject *> *metaObjectList, bool endianSwap) {
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
    first = igMetaObject_GetFieldCount(Gap::Core::igObject::getClassMeta());
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
            if (((Gap::Core::igObject *)field)->isOfType((igMetaObject *)g_igRefMetaField_metaObject) == 0 || ((igRefMetaField *)field)->_construct == 0) {
                ((Gap::Core::igMetaField *)field)->reset((Gap::Core::igObject *)object);
            }
        } else {
            done++;
            data += ((Gap::Core::igMetaField *)field)->readFromMemory((Gap::Core::igObject *)object, data, (igDirectory *)dir, endianSwap);
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

namespace Gap {
namespace Core {

void igObject::printFields(int depth, int indent) {
    void **field;
    __internalObjectList *fields;
    int prefix;
    unsigned int count;
    unsigned int i;

    fields = (__internalObjectList *)(((igObjectDispatchView *)this)->GetMeta()->_metaFields);
    igReport_Printf("%s0x%x (type %s)\n", indent, (void * *)this, ((igObjectDispatchView *)this)->GetMeta()->_name);
    igReport_Flush();
    if (depth != 0) {
        prefix = (int)malloc((strlen((const char *)indent) + 2) * 4);
        sprintf((char *)prefix, "\t%s", indent);
        ((igObjectDispatchView *)this)->TrimCapacity();
        count = fields->_count;
        i = ((__internalObjectList *)Gap::Core::igObject::_Meta->_metaFields)->_count;
        igReport_Printf("%s{\n", indent);
        igReport_Flush();
        for (; i < count; i++) {
            int *base = (int *)fields->_data;
            field = (void **)base[i];
            { int d = depth - 1; ((igMetaFieldView *)field)->Print((int)(void * *)this, d, (int)prefix); }
        }
        igReport_Printf("%s}\n", indent);
        igReport_Flush();
        free((void *)prefix);
    }
}
}
}

void igObject_CopyFields(igObjectDispatchView *self, int source) {
    __internalObjectList *meta = (__internalObjectList *)self->GetMeta()->_metaFields;
    int n = meta->_count;
    for (int i = igMetaObject_GetFieldCount(Gap::Core::igObject::getClassMeta()); i < n; i++) {
        igMetaField_ConstructCopy(((int *)meta->_data)[i], (int)self, source);
    }
}

namespace Gap {
namespace Core {

void igObject::copyDeep(igObject *source) {
    igMetaObject *holder;
    __internalObjectList *meta;
    int n;
    int i;

    holder = getMeta();
    trimCapacity();
    source->trimCapacity();
    meta = (__internalObjectList *)holder->_metaFields;
    n = meta->_count;
    for (i = igMetaObject_GetFieldCount(Gap::Core::igObject::getClassMeta()); i < n; i++) {
        ((igMetaField *)(((int *)meta->_data)[i]))->copyDeep((igObject *)((int)this), (igObject *)((int)source));
    }
    userDeepCopy(source);
}

void igObject::copyShallow(int source) {
    __internalObjectList *m = (__internalObjectList *)((igObjectDispatchView *)this)->GetMeta()->_metaFields;
    int n = m->_count;
    int i;
    for (i = igMetaObject_GetFieldCount(Gap::Core::igObject::_Meta); i < n; i++) {
        ((igMetaField *)(((int *)m->_data)[i]))->copyShallow((igObject *)((int)(igObjectDispatchView *)this), (igObject *)source);
    }
    ((igObjectDispatchView *)this)->userShallowCopy(source);
}

int igObject::isAlikeDeep(igObject *b) {
    int i;
    __internalObjectList *fl;
    int n;
    if (b->getMeta() != getMeta()) return 0;
    fl = (__internalObjectList *)getMeta()->_metaFields;
    n = fl->_count;
    i = igMetaObject_GetFieldCount(Gap::Core::igObject::getClassMeta());
    for (; i < n; i++) {
        if (((igMetaField *)(((int *)fl->_data)[i]))->isAlikeDeep((igObject *)((int)this), (igObject *)((int)b)) == 0) return 0;
    }
    return userIsAlikeDeep(b);
}

int igObject::isAlikeShallow(igObject *b) {
    igMetaObject *meta;
    int i;
    __internalObjectList *fields;
    int count;
    meta = b->getMeta();
    if (meta != getMeta()) {
        return 0;
    }
    fields = (__internalObjectList *)getMeta()->_metaFields;
    count = fields->_count;
    for (i = igMetaObject_GetFieldCount(Gap::Core::igObject::getClassMeta()); i < count; i++) {
        if (((igMetaField *)(((int *)fields->_data)[i]))->isAlikeShallow((igObject *)((int)this), (igObject *)((int)b)) == 0) {
            return 0;
        }
    }
    return userIsAlikeShallow(b);
}

int igObject::isAlikeExactly(void *b) const {
    int meta;
    int i;
    __internalObjectList *fields;
    int count;

    meta = (int)((igObjectDispatchView *)b)->GetMeta();
    if (meta != (int)((igObjectDispatchView *)this)->GetMeta()) {
        return 0;
    }
    fields = (__internalObjectList *)((igObjectDispatchView *)this)->GetMeta()->_metaFields;
    count = fields->_count;
    for (i = igMetaObject_GetFieldCount(Gap::Core::igObject::_Meta); i < count; i++) {
        if (((igMetaField *)(((int *)fields->_data)[i]))->isAlikeExactly((igObject *)((int)(void *)this), (igObject *)((int)b)) == 0) {
            return 0;
        }
    }
    return 1;
}

void igObject::traverseFields(Visitor callback, void *context){
    __internalObjectList *fields;
    int count;
    int i;
    igMetaFieldView *field;
    if(callback((igObjectDispatchView *)this,0,context)==1)return;
    ((igObjectDispatchView *)this)->TrimCapacity();
    fields=(__internalObjectList *)((igObjectDispatchView *)this)->GetMeta()->_metaFields;
    count=fields->_count;
    for(i=igMetaObject_GetFieldCount((igMetaObject *)Gap::Core::igObject::_Meta);i<count;++i){
        field=((igMetaFieldView **)fields->_data)[i];
        if(callback((igObjectDispatchView *)this,field,context)!=1)field->ReleaseElements((int)(igObjectDispatchView *)this,(int)callback,(int)context);
    }
}

void igObject::copy(igObject *source, int copyMode) {
    switch (copyMode) {
    case 1:
        copyDeep(source);
        break;
    case 0:
        copyShallow((int)source);
        break;
    case 2:
        igObject_CopyFields((igObjectDispatchView *)this, (int)source);
        break;
    }
}

/* Generic clone of any object. Asks the source for its metaobject through vtable slot 20 (the
 * GetMetaObject slot), creates an instance of that class on the source's own allocator and copies
 * the contents across. `copyMode` is passed to the contents copy unchanged (the copy dispatches on
 * 0, 1 and 2). */
igObject *igObject::cloneViaMetadata(int copyMode) {
    igMetaObject *meta = getMeta();
    ::igObject *copy = igMetaObject_CreateInstance(meta, getMemoryPool());
    ((igObject *)copy)->copy(this, copyMode);
    return (igObject *)copy;
}

int igObject::isOfType(const igMetaObject *kind) const {
    igMetaObject *meta = getMeta();
    while (meta != 0) {
        if (meta == kind) return 1;
        meta = (igMetaObject *)meta->_parent;
    }
    return 0;
}

void *igObject::getClassStorage() const {
    return (char *)this - getMeta()->_runTimeSize;
}

/* Object storage dispatch: every helper re-selects the allocator from the object header
 * (Gap::Core::igObject::getMemoryPool) and calls one slot of that allocator's vtable, forwarding its arguments
 * unchanged. */
void *igObject::malloc(int size) const {
    igMemoryPoolView *allocator = getMemoryPool();
    return allocator->Allocate(size);
}

void *igObject::mallocAligned(int size, unsigned short alignment) const {
    igMemoryPoolView *allocator = getMemoryPool();
    return allocator->AllocateAligned(size, alignment);
}

void *igObject::calloc(int count, int size) const {
    igMemoryPoolView *allocator = getMemoryPool();
    return allocator->Callocate(count, size);
}

void *igObject::realloc(void *storage, int size) const {
    igMemoryPoolView *allocator = getMemoryPool();
    return allocator->Reallocate(storage, size);
}

void *igObject::reallocAligned(void *storage, int size, unsigned short alignment) const {
    igMemoryPoolView *allocator = getMemoryPool();
    return allocator->ReallocateAligned(storage, size, alignment);
}
}
}

/* A null storage pointer returns without touching the allocator */
void igObject_FreeStorage(int object, int storage) {
    if (storage != 0) {
        igMemoryPoolView *allocator = ((Gap::Core::igObject *)object)->getMemoryPool();
        allocator->Free((void *)storage);
    }
}

namespace Gap {
namespace Core {

/* Same instruction body as igObject_FreeStorage. */
void igObject::free(void *storage) const {
    if (storage != 0) {
        igMemoryPoolView *allocator = getMemoryPool();
        allocator->Free(storage);
    }
}

/* Copy a C string into storage owned by `self`: allocate strlen + 1 bytes with the igObject
 * storage allocator (vtable slot 216, Gap::Core::igObject::malloc), strcpy into it and return the
 * copy. */
char *igObject::strdup(const char *string) const {
    char *copy;

    copy = (char *)malloc(strlen(string) + 1);
    strcpy(copy, string);
    return copy;
}

igMemoryPoolView *igObject::getMemoryPool() const {
    return ((igMemoryPoolView *)igAllocator_ResolveEncodedIndex(((igRefCountWord *)&_refCount)->bytes.poolIndex));
}
}
}

igSmartPointer<igObject> igObject_Clone(igObjectDispatchView *source, int copyMode) {
    igSmartPointer<igObject> created(source->CloneViaMetadata(copyMode), kRetainReference);
    created.release();
    return created;
}

