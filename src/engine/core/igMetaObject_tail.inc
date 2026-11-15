static inline void retain(Instance *object) {
    if (object != 0) {
        object->_refCount = object->_refCount + 1;
    }
}

int igMetaObject_CreateInstanceDefaultRef(Instance **out, int meta) {
    igSmartPointer<Instance> created((Instance *)igMetaObject_CreateInstanceDefault((void *)meta), kRetainReference);
    igRelease(created.p);
    *out = created.p;
    retain(*out);
    return 0;
}

/* The new instance arrives with one reference; the pointer takes its own and drops that one. */
igSmartPointer<igObject> igMetaObject_CreateInstanceRef(int meta, int pool) {
    igSmartPointer<igObject> created((igObject *)igMetaObject_CreateInstance((igMetaObject *)meta, (igMemoryPoolView *)pool), kRetainReference);
    igRelease(created.get());
    return created;
}

/* Construct a metaobject: base header, igMetaObject vtable, no name or pool
 * name, and an empty field list. */
void *igMetaObject_Construct(igMetaObject *meta, int extra1){
    igObject_ConstructHeader((igObject *)meta);
    meta->_vtable=(int)g_igMetaObject_vtable;
    meta->_name=0;
    meta->_poolName=0;
    if(meta)igMetaObject_Init(meta);
    meta->_metaFields=((int)InternalObjectList_Create(0));
    return meta;
}

/* Reset a freshly constructed metaobject to its defaults, then intern the empty string as the
 * pool name, creating the shared string pool on first use. No previous lists are released. */
igMetaObject *igMetaObject_Init(igMetaObject *meta){
    int pool,oldName,refCount;int *oldHeader;void *emptyToken;
    igObject_InitHeader((igObject *)meta);meta->_vtable=(int)g_igMetaObject_vtable;
    meta->_name=0;
    meta->_poolName=0;
    meta->_metaFields=0;
    meta->_instances=0;
    meta->_children=0;
    meta->_parent=0;
    meta->_abstractProxy=0;
    meta->_writeProxy=0;
    meta->_templateObject=0;
    meta->_volatile=0;
    meta->_persistent=1;
    meta->_abstractState=0;
    meta->_majorVersion=1;
    meta->_minorVersion=0;
    meta->_index=0;
    meta->_id=0;
    meta->_metaFields=0;
    meta->_runTimeSize=0;
    meta->_instanceCount=0;
    meta->_validity=0;
    meta->_sizeofSize=-1;
    meta->_setupFunction=0;
    meta->_cleanupFunction=0;
    meta->_getMetaObjectFunction=0;
    meta->_requiredAlignment=4;
    meta->_vTablePointer=0;
    if(g_stringPool==0){
        pool=((int)StringPool_Allocate(16));if(pool)pool=((int)StringPool_Construct((StringPool *)pool));
        g_stringPool=pool;
    }
    emptyToken=(void *)StringPool_Intern((StringPool *)g_stringPool, (const char *)0);
    /* Drop the old pool-name token: owner chunk at -8, reference count at -4. */
    oldName=meta->_poolName;
    if(oldName){oldHeader=(int *)(oldName-8);refCount=*(int *)(oldName-4)-1;*(int *)(oldName-4)=refCount;
        if(!refCount)StringChunk_ReleaseHeader((StringChunk *)(*oldHeader), (int)oldHeader);
    }
    meta->_poolName=(int)emptyToken;return meta;
}

/* Copy-construct: base header copy, vtable stamp and cleared names; the other
 * metadata members are not copied here. */
void *igMetaObject_CopyConstruct(igMetaObject *meta,void *source){
    igObject_CopyConstructHeader((igObject *)meta, (igObject *)source);
    meta->_vtable=(int)g_igMetaObject_vtable;
    meta->_name=0;
    meta->_poolName=0;
    return meta;
}

/* Drop the field list and then the child list: decrement the reference count
 * and destroy the list once its 23 low count bits reach zero.  The member cells
 * are left untouched. */
void igMetaObject_ReleaseLists(igMetaObject *meta){
    igObject *list=(igObject *)meta->_metaFields;
    if(list){
        --list->_refCount;
        if(!(list->_refCount&0x7fffff))igObject_Destroy(list);
    }
    list=(igObject *)meta->_children;
    if(list){
        --list->_refCount;
        if(!(list->_refCount&0x7fffff))igObject_Destroy(list);
    }
}

void *igMetaObject_CreateInstanceDefault(void *meta){return (void *)igMetaObject_CreateInstance((igMetaObject *)meta,((igMemoryPoolView *)Memory_GetDefaultAllocator()));}

int igMetaObject_CreateInstance(igMetaObject *self, igMemoryPoolView *pool) {
    int instance;
    int headerSize;
    char *poolName;
    igMemoryPoolView *allocator;
    igMemoryPoolView *fallback;
    igMetaObject *(*proxy)();

    allocator = pool;
    proxy = (igMetaObject *(*)())self->_abstractProxy;
    if (proxy != 0) {
        return igMetaObject_CreateInstance(proxy(), allocator);
    }
    if (self->_abstractState == 1) {
        return 0;
    }
    if (allocator == 0) {
        poolName = (char *)self->_poolName;
        if ((poolName != 0) && (*poolName != 0)) {
            allocator = ((igMemoryPoolView *)Memory_GetAllocatorByName((int)poolName));
            if (allocator == 0) {
                fallback = ((igMemoryPoolView *)Memory_GetDefaultAllocator());
                goto use_fallback;
            }
        } else {
            fallback = ((igMemoryPoolView *)Memory_GetDefaultAllocator());
use_fallback:
            allocator = fallback;
        }
    }
    headerSize = self->_runTimeSize;
    instance = (int)allocator->Allocate(headerSize + self->_sizeofSize);
    instance = instance + headerSize;
    if (instance != 0) {
        igObject_Construct((igObjectDispatchView *)instance, (char *)self);
    }
    return instance;
}

int igMetaObject_CreateInstanceWithPool(igMetaObject *self, igMemoryPoolView *pool) {
    int instance;
    int headerSize;
    char *poolName;
    igMemoryPoolView *allocator;
    igMemoryPoolView *fallback;
    igMetaObject *(*proxy)();

    allocator = pool;
    if (((self->_validity & 4) != 0) == 0) {
        return 0;
    }
    proxy = (igMetaObject *(*)())self->_abstractProxy;
    if (proxy != 0) {
        return igMetaObject_CreateInstanceWithPool(proxy(), allocator);
    }
    if (self->_abstractState == 1) {
        return 0;
    }
    if (allocator == 0) {
        poolName = (char *)self->_poolName;
        if ((poolName != 0) && (*poolName != 0)) {
            allocator = ((igMemoryPoolView *)Memory_GetAllocatorByName((int)poolName));
            if (allocator == 0) {
                fallback = ((igMemoryPoolView *)Memory_GetDefaultAllocator());
                goto use_fallback;
            }
        } else {
            fallback = ((igMemoryPoolView *)Memory_GetDefaultAllocator());
use_fallback:
            allocator = fallback;
        }
    }
    headerSize = self->_runTimeSize;
    instance = (int)allocator->Allocate(headerSize + self->_sizeofSize);
    instance = instance + headerSize;
    if (instance != 0) {
        igObject_ConstructPooled((igObject *)instance, (char *)self);
    }
    return instance;
}

void igMetaObject_InheritFromBase(igMetaObject *meta,igMetaObject *parent){
    if(parent!=0){
        if(parent->_children==0)parent->_children=(int)__internalNonRefCountedObjectList_Create((int)(Memory_GetAllocatorBySelector(*(int *)0x587040)));
        ObjectPointerList_Append((__internalNonRefCountedObjectList *)((void *)parent->_children), (int)meta);
        meta->_parent=(int)parent;
        meta->_vTablePointer=parent->_vTablePointer;
        meta->_requiredAlignment=((igMetaObject *)meta->_parent)->_requiredAlignment;
        meta->_runTimeSize=((igMetaObject *)meta->_parent)->_runTimeSize;
        meta->_sizeofSize=((igMetaObject *)meta->_parent)->_sizeofSize;
        int count=((__internalObjectList *)parent->_metaFields)->_count;
        for(int i=0;i<count;i++)igMetaObject_AppendField(meta,(igMetaField *)igMetaObject_GetFieldAt(parent,i));
    }
}

int igMetaObject_CountInstances(igMetaObject *self, int recursive) {
    int count = self->_instanceCount;
    __internalObjectList *children;
    int i;
    int childCount;
    if (recursive != 0) {
        children = (__internalObjectList *)self->_children;
        if (children != 0) {
            childCount = children->_count;
            for (i = 0; i < childCount; i++) {
                count += igMetaObject_CountInstances(((igMetaObject **)((__internalObjectList *)self->_children)->_data)[i], 1);
            }
        }
    }
    return count;
}

/* Give a metaobject its (interned) class name. The shared string pool is created on first use even
 * for a null name; the new name is interned first, then the previous name token is released. */
void igMetaObject_SetName(igMetaObject *meta, int name) {
    int pool, internedName, oldName, refCount;
    int *oldHeader;

    if (g_stringPool == 0) {
        pool = ((int)StringPool_Allocate(16));
        if (pool) {
            pool = ((int)StringPool_Construct((StringPool *)pool));
        }
        g_stringPool = pool;
    }
    internedName = StringPool_Intern((StringPool *)g_stringPool, (const char *)name);
    oldName = meta->_name;
    if (oldName) {
        oldHeader = (int *)(oldName - 8);
        refCount = *(int *)(oldName - 4) - 1;
        *(int *)(oldName - 4) = refCount;
        if (!refCount) {
            StringChunk_ReleaseHeader((StringChunk *)(*oldHeader), (int)oldHeader);
        }
    }
    meta->_name = internedName;
}

void igMetaObject_AppendField(igMetaObject *meta, igMetaField *field)
{
    MetaRefList_AppendRetained((__internalObjectList *)((void *)meta->_metaFields), (igObject *)field);
}

void igMetaObject_FinalizeAndAppendField(void *meta,void *field){
    igMetaField_FinalizeDescriptor((igMetaField *)field);igMetaObject_AppendField((igMetaObject *)meta,(igMetaField *)field);
}

void igMetaObject_FinalizeAndReplaceField(igMetaObject *meta,int index,igMetaField *field){
    igMetaField_FinalizeDescriptor((igMetaField *)field);
    InternalObjectList_SetAtRetained((__internalObjectList *)((void *)meta->_metaFields), index, (igObject *)field);
}

int FUN_002fdef0(int a0, int a1)
{
    return a1;
}

/* The item array is read at +8 of the field list object. */
int igMetaObject_GetFieldAt(igMetaObject *self, int index) {
    return *(int *)(*(int *)((char *)(self->_metaFields) + 8) + (index * 4));
}

void *igMetaObject_FindFieldByName(igMetaObject *meta, const char *name) {
    return ObjectPointerList_FindByStringField((__internalNonRefCountedObjectList *)((void *)meta->_metaFields), g_fieldNameMember, name);
}

void igMetaObject_CreateFields(igMetaObject *meta,FieldFactory *factories,int count){
    int i;
    igMetaField *field;
    for(i=0;i<count;i++){
        field=factories[i](Memory_GetAllocatorBySelector(*(int *)0x587040));
        igMetaObject_AppendField(meta,field);
        --field->_refCount;
        if(!(field->_refCount&0x7fffff))igObject_Destroy(field);
    }
}

void igMetaObject_NameFields(igMetaObject *meta,const char **names,igMetaField ***handles,int *offsets,int start){
    int count;
    int row;
    igMetaField *field;
    count=igMetaObject_GetFieldCount(meta);
    row=0;
    for(;start<count;start++,row++){
        field=((igMetaField **)((__internalObjectList *)meta->_metaFields)->_data)[start];
        igMetaField_Configure(field,names[row],handles[row],offsets[row],meta);
        igMetaField_FinalizeDescriptor(field);
    }
}

void igMetaObject_FinalizeFieldLayout(igMetaObject *self) {
    int offset;
    int minAlignment;
    unsigned short alignment;
    int i;
    igMetaFieldView *field;
    int count;
    int runTimeCount;
    int end;
    unsigned short maxAlignment;
    int maxEnd;
    bool ownField;
    count = igMetaObject_GetFieldCount(self);
    offset = 0;
    maxEnd = 0;
    minAlignment = 4;
    runTimeCount = 0;
    maxAlignment = 4;
    for (i = 0; i < count; i++) {
        field = (igMetaFieldView *)igMetaObject_GetFieldAt(self, i);
        alignment = field->GetAlignment();
        if (maxAlignment < alignment) maxAlignment = alignment;
        if (field->_isRunTime != 0) {
            runTimeCount++;
            offset = ~(alignment - 1) & (offset - field->_size);
            field->_offset = offset;
        } else {
            ownField = 0;
            if (self->_parent == 0 || igMetaObject_GetFieldCount((igMetaObject *)self->_parent) <= i) {
                ownField = 1;
            } else if ((igMetaFieldView *)igMetaObject_GetFieldAt((igMetaObject *)self->_parent, i) != field) {
                ownField = 1;
            }
            if (ownField) {
                field->_internalIndex = i - runTimeCount;
                field->_parentMetaObject = (int)self;
            }
            minAlignment = (alignment < minAlignment) ? minAlignment : alignment;
        }
        end = field->_offset; end += field->_size;
        if (maxEnd < end) maxEnd = end;
    }
    self->_requiredAlignment = maxAlignment;
    if (self->_sizeofSize != -1) self->_runTimeSize = -(offset & ~(minAlignment - 1));
    self->_validity |= 4;
    igObjectSystem_RunRegistrationCallbacks((int *)((*(void * *)&g_objectSystem)), (int)self);
}

int igMetaObject_IsOfType(igMetaObject *self, igMetaObject *type) {
    while (self != 0) {
        if (type == self) {
            return 1;
        }
        self = (igMetaObject *)self->_parent;
    }
    return 0;
}

int igMetaObject_GetChildCount(igMetaObject *self) {
    __internalObjectList *children;

    children = (__internalObjectList *)self->_children;
    if (children == 0) {
        return 0;
    }
    return children->_count;
}

/* The item array is read at +8 of the child list object. */
int igMetaObject_GetChildAt(igMetaObject *self, int index) {
    return *(int *)(*(int *)((char *)(self->_children) + 8) + (index * 4));
}

void *igMetaObject_GetTreeNode(igMetaObject *self, int index) {
    int childCount;
    int first;
    int i;
    int next;
    igMetaObject *child;
    if (index == 0) {
        return self;
    }
    if (self->_children == 0) {
        return 0;
    }
    childCount = ((__internalObjectList *)self->_children)->_count;
    first = 1;
    for (i = 0; i < childCount; i++) {
        child = ((igMetaObject **)((__internalObjectList *)self->_children)->_data)[i];
        next = igMetaObject_CountTree((igMetaObject *)child);
        next += first;
        if (index < next) {
            return igMetaObject_GetTreeNode(child, index - first);
        }
        first = next;
    }
    return 0;
}

int igMetaObject_CountTree(igMetaObject *self) {
    __internalObjectList *children = (__internalObjectList *)self->_children;
    int count;
    int childCount;
    int i;
    if (children == 0) return 1;
    childCount = children->_count;
    count = 1;
    for (i = 0; i < childCount; i++) {
        count += igMetaObject_CountTree(((igMetaObject **)((__internalObjectList *)self->_children)->_data)[i]);
    }
    return count;
}

int igObjectSystem_FindMetaByNameDefault(const char *name){return igObjectSystem_FindMetaByName((ObjectSystemView *)((*(void * *)&g_objectSystem)), name);}

/* Read from the field list's `_capacity` slot (+12), not `_count` (+8). */
int igMetaObject_GetFieldCount(igMetaObject *self) {
    return ((igMetaFieldList *)self->_metaFields)->_capacity;
}

void igMetaObject_AddExitCallback(int callback) {
    igObjectSystem_AddExitCallback((int *)((*(void * *)&g_objectSystem)), callback);
}

void igMetaObject_AddRegistrationCallback(int callback) {
    igObjectSystem_AddRegistrationCallback((ObjectSystemView *)((*(void * *)&g_objectSystem)), (int (*)(int))callback);
}

void igMetaObject_AddField(igMetaObject *self, void *object) {
    igMetaField *field = (igMetaField *)object;
    int flags;
    int index;
    igMetaObject *node;
    int nodeCount;
    int i;

    flags = self->_validity;
    self->_validity = flags & ~4;
    field->_isRunTime = 1;
    field->_parentMetaObject = (int)(self);
    igMetaField_FinalizeDescriptor(field);
    index = MetaRefList_AppendRetained((__internalObjectList *)((void *)self->_metaFields), (igObject *)field);
    nodeCount = igMetaObject_CountTree((igMetaObject *)self);
    for (i = 1; i < nodeCount; i++) {
        node = (igMetaObject *)igMetaObject_GetTreeNode(self, i);
        node->_validity = node->_validity & ~4;
        InternalObjectList_InsertRetained((__internalObjectList *)node->_metaFields, index, (igObject *)field);
    }
}

void igMetaObject_AddFieldAndFinalize(igMetaObject *self, void *field) {
    igMetaObject_AddField(self, field);
    igMetaObject_FinalizeFieldLayoutTree((int)self);
}

void igMetaObject_FinalizeFieldLayoutTree(int self) {
    int nodeCount;
    int i;
    nodeCount = igMetaObject_CountTree((igMetaObject *)self);
    for (i = 0; i < nodeCount; i++) {
        igMetaObject_FinalizeFieldLayout((igMetaObject *)igMetaObject_GetTreeNode((igMetaObject *)self, i));
    }
}

int igMetaObject_AddToMetaObjectList(igTDataList<igMetaObject *> *list, igMetaObject *object) {
    int i = list->find(object);
    if (i != -1) {
        return i;
    }
    int n = list->count();
    while (i == -1 && object != 0) {
        /* insertObject() written out: as an inlined call its word is allocated after the first
         * find()'s key, at 72(sp) with the key at 76(sp); retail has them the other way round. */
        RetainedWord<igMetaObject> word(object);
        List_InsertWords((igDataList *)list, n, 1, &word);
        object = (igMetaObject *)object->_parent;
        i = list->find(object);
    }
    return list->_count - 1;
}

int igMetaObject_GetPersistentFieldCount(int self) {
    int count = 0;
    int i;

    for (i = 0; i < igMetaObject_GetFieldCount((igMetaObject *)self); i++) {
        if (((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)self, i))->_isRunTime == 0) {
            count += 1;
        }
    }
    return count;
}

/* Search the object system's registry; when absent (-1) append the metaobject and search again,
 * since appending can replace the registry. */
void igMetaObject_AssignTypeId(igMetaObject *meta){
    meta->_index=ObjectPointerList_FindIndex((char *)(((ObjectSystemView *)(*(void * *)&g_objectSystem))->metaRegistry), (int)meta);
    if(meta->_index==-1){
        igObjectSystem_AppendMetaObject((*(void * *)&g_objectSystem),meta);
        meta->_index=ObjectPointerList_FindIndex((char *)(((ObjectSystemView *)(*(void * *)&g_objectSystem))->metaRegistry), (int)meta);
    }
}

igResult igMetaObject_CopyVTable(igMetaObject *s, igMemoryPoolView *a) {
    if (s->_vTablePointer == 0) return g_resultFailure;
    if (s->_abstractState != 0) return g_resultFailure;
    if (a == 0) a = ((igMemoryPoolView *)Memory_GetDefaultAllocator());
    int *p; int *base = (int *)s->_vTablePointer;
    p = base;
    while (!*p) p++;
    while (*p != 0) p++;
    int n = (char *)p - (char *)base;
    int *nb = (int *)a->Allocate(n);
    if (nb == 0) return g_resultFailure;
    memcpy(nb, (int *)s->_vTablePointer, n);
    s->_vTablePointer = (int)nb;
    return g_resultSuccess;
}

int igMetaObject_GetPoolName(int *object)
{
    igMetaObject *self = (igMetaObject *)object;
    return self->_poolName;
}

void igMetaObject_RunStaticInit(StaticInitCallbacks *(*initialize)()){
    StaticInitCallbacks *list=initialize();
    int count; int i;
    if(list){count=list->count;for(i=0;i<count;i++)list->functions[i]();igArray_Destruct((CallbackArray *)list, 1);}
}

/* The registration state bits of _validity: 1 the parent is registered, 2 the class is set up, 4 the
 * registration is complete, 8 a registration is in progress. */
static inline int hasValidity(const igMetaObject &meta, int bit) {
    return (meta._validity & bit) != 0;
}

CallbackArray *igMetaObject_RegisterClass(bool abstract, igMetaObject **metaObject,
    igMetaObjectRegisterFunction registerParent, igMetaObjectGetFunction getParentMetaObject,
    igMetaObjectCallback getMetaObjectFunction, const char *className, int instanceSize,
    igMetaObjectGetVTableFunction getVTable, igMetaObjectCallback initFields,
    igMetaObjectCallback staticInitCallback, igMetaObjectCallback *callbacks)
{
    int pool = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData);
    igMetaObject *meta;
    CallbackArray *list;
    bool firstRegistration;
    if (*metaObject == 0) {
        char name[256];
        strcpy(name, "igMetaObject: ");
        if (className != 0) {
            strcat(name, className);
        }
        *metaObject = (igMetaObject *)igMetaObject_Create(pool);
    }
    meta = *metaObject;
    list = 0;
    if (!hasValidity(*meta, 8)) {
        meta->_validity |= 8;
        firstRegistration = false;
        if (!hasValidity(*meta, 4)) {
            if (!hasValidity(*meta, 2)) {
                firstRegistration = true;
                if (!hasValidity(*meta, 1)) {
                    list = registerParent();
                    igMetaObject_InheritFromBase(meta, getParentMetaObject());
                    meta->_validity |= 1;
                }
                igMetaObject_SetName(meta, (int)className);
                meta->_sizeofSize = instanceSize;
                meta->_getMetaObjectFunction = (int)getMetaObjectFunction;
                meta->_abstractState = abstract;
                if (!abstract) {
                    meta->_vTablePointer = getVTable();
                }
                if (initFields != 0) {
                    initFields();
                }
                meta->_validity |= 2;
                igMetaObject_AssignTypeId(meta);
                meta->_refCount = meta->_refCount - 1;
                if ((meta->_refCount & 0x7FFFFF) == 0) igObject_Destroy(meta);
                ObjectSystemView *system = (*(ObjectSystemView * *)&g_objectSystem);
                if (system->copyVTables != 0 && system->fastPool != 0 && system->vtableClassNames != 0 &&
                    igStringTable_Find(system->vtableClassNames, (unsigned int)className) != -1) {
                    igMetaObject_CopyVTable(meta, (*(ObjectSystemView * *)&g_objectSystem)->fastPool);
                }
            }
            igMetaObject_FinalizeFieldLayout(meta);
            if (meta->_setupFunction != 0) {
                ((void (*)(igMetaObject *))meta->_setupFunction)(meta);
            }
            if (list == 0) {
                CallbackArray *array = (CallbackArray *)Memory_AllocateBufferDirect(12,
                    (igMemoryPoolView *)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
                if (array != 0) {
                    array = igArray_Construct(array);
                }
                list = array;
            }
            if (callbacks != 0) {
                igMetaObjectCallback *callback;
                for (callback = callbacks; *callback != 0; callback++) {
                    igArray_Append(list, (int)*callback);
                }
            }
            if (firstRegistration && staticInitCallback != 0) {
                igArray_Append(list, (int)staticInitCallback);
            }
            meta->_validity |= 4;
        }
        meta->_validity &= ~8;
    }
    return list;
}
