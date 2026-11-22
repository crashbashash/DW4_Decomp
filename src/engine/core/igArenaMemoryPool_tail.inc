igMetaObject *g_igArenaMemoryPool_metaObject;
igMetaField *g_igArenaMemoryPool_arenaStateMetaField;
igMetaField *g_igArenaMemoryPool_rawMemoryMetaField;
igMetaField *g_igArenaMemoryPool_isAlchemyMemoryMetaField;
igMetaField *g_igArenaMemoryPool_systemAllocatedMetaField;
igMetaField *g_igArenaMemoryPool_elementSizeMetaField;
igMetaField *g_igArenaMemoryPool_maxSizeMetaField;
igMetaField *g_igArenaMemoryPool_sizeMetaField;
igMetaField *g_igArenaMemoryPool_preSizeMetaField;
igMetaField *g_igArenaMemoryPool_alignmentMetaField;
igMetaField *g_igArenaMemoryPool_eventTrackerMetaField;
igMetaField *g_igArenaMemoryPool_isActiveMetaField;
igMetaField *g_igArenaMemoryPool_allocationLockMetaField;
igMetaField *g_igArenaMemoryPool_poolIndexMetaField;
igMetaField *g_igArenaMemoryPool_heapIntegrityCheckLevelMetaField;
igMetaField *g_igArenaMemoryPool_messageLevelMetaField;
igMetaField *g_igArenaMemoryPool_poolOptionFlagsMetaField;
igMetaField *g_igArenaMemoryPool_poolPreSizedMetaField;
igMetaField *g_igArenaMemoryPool_smallestChunkSizeMetaField;

void **igArenaMemoryPool_Create(int allocator) {
    void **pool;

    if (g_objectSystem->active != 0) {
        igArenaMemoryPool_EnsureRegistered();
        pool = (void **)(((void **)igMetaObject_CreateInstance((igMetaObject *)g_igArenaMemoryPool_metaObject, (igMemoryPoolView *)allocator)));
    } else {
        pool = (void **)(((void **)igObject_OperatorNew(0xD0, 0, allocator)));
        if (pool != 0) {
            pool = (void **)(((void **)igArenaMemoryPool_Construct((igArenaMemoryPool *)pool, 1)));
        }
        ((igObjectDispatchView *)(pool))->InitDefaults();
        ((igObjectDispatchView *)(pool))->userConstruct((int)(0));
    }
    return pool;
}

int igArenaMemoryPool_Clone(int source, int copyMode) {
    int copy;
    if (g_objectSystem->active != 0) {
        igArenaMemoryPool_EnsureRegistered();
        return igObject_CloneViaMetadata((void **)source, copyMode);
    }
    copy = ((int)igObject_OperatorNew(0xD0, 0, ((int)Memory_GetDefaultAllocator())));
    if (copy != 0) {
        copy = ((int)igArenaMemoryPool_CopyConstruct((igArenaMemoryPool *)copy, source));
    }
    return copy;
}

igMetaObject *igArenaMemoryPool_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igArenaMemoryPool_metaObject != 0) {
        ready = (g_igArenaMemoryPool_metaObject->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    igArenaMemoryPool_EnsureRegistered();
done:
    return g_igArenaMemoryPool_metaObject;
}

int igArenaMemoryPool_GetVTable(void) {
    igArenaMemoryPool pool;
    int vtable;
    igObject *p;
    igObject *r;

    igArenaMemoryPool_Initialize(&pool);
    vtable = *(int *)((char *)&pool + g_objectSystem->vtableProbeOffset);
    pool._vtable = (int)&g_igArenaMemoryPool_vtable[0];
    p = (igObject *)&pool._eventTracker;
    if (p != 0) {
        p = *(igObject **)p;
        igObject::release(p);
    }
    r = (igObject *)&pool._allocationLock;
    if (r != 0) {
        r = *(igObject **)r;
        igObject::release(r);
    }
    return vtable;
}

void igArenaMemoryPool_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igArenaMemoryPool_Register);
}

static igMetaObjectCallback g_igArenaMemoryPool_callbackList[] = { igEventTracker_EnsureRegistered, Gap::Core::igSemaphore::arkRegister, 0 };

CallbackArray *igArenaMemoryPool_Register(void) {
    return igMetaObject_RegisterClass(
        0,
        &g_igArenaMemoryPool_metaObject,
        igMemoryPool_Register,
        igMemoryPool_GetPublishedMetaObject,
        igArenaMemoryPool_GetMetaObjectFunction,
        "igArenaMemoryPool",
        0xD0,
        igArenaMemoryPool_GetVTable,
        igArenaMemoryPool_InitFields,
        0,
        g_igArenaMemoryPool_callbackList
    );
}

static FieldFactory g_igArenaMemoryPool_ctorTable[] = {
    (FieldFactory)igRawRefMetaField_Create,
    (FieldFactory)igRawRefMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igUnsignedLongMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igUnsignedLongMetaField_Create,
    (FieldFactory)igUnsignedLongMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igUnsignedShortMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
};
static const char *g_igArenaMemoryPool_fieldTable[] = {
    "_arenaState",
    "_rawMemory",
    "_isAlchemyMemory",
    "_systemAllocated",
    "_elementSize",
    "_maxSize",
    "_size",
    "_preSize",
    "_alignment",
    "_eventTracker",
    "_isActive",
    "_allocationLock",
    "_poolIndex",
    "_heapIntegrityCheckLevel",
    "_messageLevel",
    "_poolOptionFlags",
    "_poolPreSized",
    "_smallestChunkSize",
};
static igMetaField **g_igArenaMemoryPool_fieldDescriptors[] = {
    &g_igArenaMemoryPool_arenaStateMetaField,
    &g_igArenaMemoryPool_rawMemoryMetaField,
    &g_igArenaMemoryPool_isAlchemyMemoryMetaField,
    &g_igArenaMemoryPool_systemAllocatedMetaField,
    &g_igArenaMemoryPool_elementSizeMetaField,
    &g_igArenaMemoryPool_maxSizeMetaField,
    &g_igArenaMemoryPool_sizeMetaField,
    &g_igArenaMemoryPool_preSizeMetaField,
    &g_igArenaMemoryPool_alignmentMetaField,
    &g_igArenaMemoryPool_eventTrackerMetaField,
    &g_igArenaMemoryPool_isActiveMetaField,
    &g_igArenaMemoryPool_allocationLockMetaField,
    &g_igArenaMemoryPool_poolIndexMetaField,
    &g_igArenaMemoryPool_heapIntegrityCheckLevelMetaField,
    &g_igArenaMemoryPool_messageLevelMetaField,
    &g_igArenaMemoryPool_poolOptionFlagsMetaField,
    &g_igArenaMemoryPool_poolPreSizedMetaField,
    &g_igArenaMemoryPool_smallestChunkSizeMetaField,
};
static int g_igArenaMemoryPool_fieldOffsets[] = {
    112,
    124,
    128,
    136,
    144,
    152,
    160,
    168,
    172,
    176,
    116,
    120,
    180,
    184,
    188,
    192,
    196,
    200,
};

int g_igArenaMemoryPool_defaultMessageLevel = 1;
int g_igArenaMemoryPool_defaultPoolOptionFlags = 0xc;
int g_igArenaMemoryPool_defaultHeapIntegrityCheckLevel;

void igArenaMemoryPool_InitFields(void) {
    int base;
    igMetaObject *meta = g_igArenaMemoryPool_metaObject;
    int defaultHeapCheck;
    int defaultMessageLevel;
    igRawRefMetaField *arenaState;
    igObjectRefMetaField *eventTracker;
    igObjectRefMetaField *allocationLock;
    igEnumMetaField *heapIntegrityCheckLevel;
    igEnumMetaField *messageLevel;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igArenaMemoryPool_ctorTable, 18);
    arenaState = (igRawRefMetaField *)igMetaObject_GetFieldAt(meta, base);
    arenaState->_resetMethod = 3;
    arenaState->_persistent = 0;
    ((Gap::Core::igUnsignedLongMetaField *)(igMetaObject_GetFieldAt(meta, base + 5)))->setDefault(0xFFFFFFFFFFFFFFFFULL);
    ((Gap::Core::igUnsignedShortMetaField *)(igMetaObject_GetFieldAt(meta, base + 8)))->setDefault(8);
    eventTracker = (igObjectRefMetaField *)igMetaObject_GetFieldAt(meta, base + 9);
    eventTracker->_metaObject = (int)igEventTracker_GetOrCreateMetaObject();
    allocationLock = (igObjectRefMetaField *)igMetaObject_GetFieldAt(meta, base + 11);
    allocationLock->_metaObject = (int)Gap::Core::igSemaphore::getClassTypeLazy();
    ((Gap::Core::igIntMetaField *)(igMetaObject_GetFieldAt(meta, base + 12)))->setDefault(-1);
    heapIntegrityCheckLevel = (igEnumMetaField *)igMetaObject_GetFieldAt(meta, base + 13);
    defaultHeapCheck = g_igArenaMemoryPool_defaultHeapIntegrityCheckLevel;
    ((Gap::Core::igEnumMetaField *)heapIntegrityCheckLevel)->setDefault(defaultHeapCheck);
    heapIntegrityCheckLevel->_getMetaEnumFunction = (int)igArenaMemoryPool_GetHeapIntegrityCheckLevelMetaEnum;
    messageLevel = (igEnumMetaField *)igMetaObject_GetFieldAt(meta, base + 14);
    defaultMessageLevel = g_igArenaMemoryPool_defaultMessageLevel;
    ((Gap::Core::igEnumMetaField *)messageLevel)->setDefault(defaultMessageLevel);
    messageLevel->_getMetaEnumFunction = (int)igArenaMemoryPool_GetMessageLevelMetaEnum;
    ((Gap::Core::igIntMetaField *)(igMetaObject_GetFieldAt(meta, base + 15)))->setDefault(g_igArenaMemoryPool_defaultPoolOptionFlags);
    ((Gap::Core::igUnsignedIntMetaField *)(igMetaObject_GetFieldAt(meta, base + 17)))->setDefault(16);
    igMetaObject_NameFields(meta, g_igArenaMemoryPool_fieldTable, g_igArenaMemoryPool_fieldDescriptors, g_igArenaMemoryPool_fieldOffsets, base);
    g_igArenaMemoryPool_metaObject->_writeProxy = (int)igMemoryPool_GetMetaObjectFunction;
}

