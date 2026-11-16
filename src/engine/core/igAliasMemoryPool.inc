igMetaObject *g_igAliasMemoryPool_metaObject;
igMetaField *g_igAliasMemoryPool_poolIndexMetaField;
igMetaField *g_igAliasMemoryPool_allocedBytesMetaField;
igMetaField *g_igAliasMemoryPool_nAllocsMetaField;
igMetaField *g_igAliasMemoryPool_nFreesMetaField;
igMetaField *g_igAliasMemoryPool_maxSizeMetaField;
igMetaField *g_igAliasMemoryPool_eventTrackerMetaField;
igMetaField *g_igAliasMemoryPool_allocedBytesHighMetaField;
igMetaField *g_igAliasMemoryPool_netAllocsHighMetaField;
igMetaField *g_igAliasMemoryPool_isActiveMetaField;
igMetaField *g_igAliasMemoryPool_isReassignableMetaField;
igMetaField *g_igAliasMemoryPool_allocationLockMetaField;
igMetaField *g_igAliasMemoryPool_elementSizeMetaField;
igMetaField *g_igAliasMemoryPool_alignmentMetaField;
igMetaField *g_igAliasMemoryPool_aliasedMemoryPoolMetaField;
int g_igPageMemoryPool_messageLevelMetaEnum;

igAliasMemoryPoolView *igAliasMemoryPool_Create(void *allocator) {
    igAliasMemoryPoolView *pool;
    if (g_objectSystem->active) {
        igAliasMemoryPool_EnsureRegistered();
        pool=((igAliasMemoryPoolView *)igMetaObject_CreateInstance((igMetaObject *)((void *)g_igAliasMemoryPool_metaObject), (igMemoryPoolView *)allocator));
    } else {
        pool=((igAliasMemoryPoolView *)igObject_OperatorNew(184, 0, (int)allocator));
        if(pool)pool=((igAliasMemoryPoolView *)igAliasMemoryPool_Construct((igAliasMemoryPool *)pool, 1));
        pool->InitDefaults();
        pool->userConstruct(0);
    }
    return pool;
}

void *igAliasMemoryPool_Clone(int source, int flags) {
    void *copy;
    if (g_objectSystem->active != 0) {
        igAliasMemoryPool_EnsureRegistered();
        return (void *)igObject_CloneViaMetadata((void **)source, flags);
    }
    copy = igObject_OperatorNew(0xB8, 0, (int)(Memory_GetDefaultAllocator()));
    if (copy != 0) {
        copy = igAliasMemoryPool_CopyConstruct((igAliasMemoryPool *)copy, source);
    }
    return copy;
}

igMetaObject *igAliasMemoryPool_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igAliasMemoryPool_metaObject != 0) {
        ready = (g_igAliasMemoryPool_metaObject->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    igAliasMemoryPool_EnsureRegistered();
done:
    return g_igAliasMemoryPool_metaObject;
}

int igAliasMemoryPool_GetVTable(void) {
    igAliasMemoryPool pool;
    int vtable;
    igObject *lockSlot;
    igObject *trackerSlot;
    igObject *aliasedSlot;

    igAliasMemoryPool_Initialize(&pool);
    vtable = *(int *)((char *)&pool + g_objectSystem->vtableProbeOffset);
    pool._vtable = (int)&g_igAliasMemoryPool_vtable[0];
    aliasedSlot = (igObject *)&pool._aliasedMemoryPool;
    if (aliasedSlot != 0) {
        aliasedSlot = *(igObject **)aliasedSlot;
        if (aliasedSlot != 0) {
            aliasedSlot->_refCount = (int)((int) (aliasedSlot->_refCount - 1));
            if (((unsigned long long) ((long long)(int) aliasedSlot->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(aliasedSlot);
            }
        }
    }
    trackerSlot = (igObject *)&pool._eventTracker;
    if (trackerSlot != 0) {
        trackerSlot = *(igObject **)trackerSlot;
        if (trackerSlot != 0) {
            trackerSlot->_refCount = (int)((int) (trackerSlot->_refCount - 1));
            if (((unsigned long long) ((long long)(int) trackerSlot->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(trackerSlot);
            }
        }
    }
    lockSlot = (igObject *)&pool._allocationLock;
    if (lockSlot != 0) {
        lockSlot = *(igObject **)lockSlot;
        if (lockSlot != 0) {
            lockSlot->_refCount = (int)((int) (lockSlot->_refCount - 1));
            if (((unsigned long long) ((long long)(int) lockSlot->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(lockSlot);
            }
        }
    }
    return vtable;
}

void igAliasMemoryPool_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igAliasMemoryPool_Register);
}

static igMetaObjectCallback g_igAliasMemoryPool_callbackList[] = { igEventTracker_EnsureRegistered, igSemaphore_EnsureRegistered, igMemoryPool_EnsureRegistered, 0 };

CallbackArray *igAliasMemoryPool_Register(void) {
    return igMetaObject_RegisterClass(
        0,
        &g_igAliasMemoryPool_metaObject,
        igMemoryPool_Register,
        igMemoryPool_GetPublishedMetaObject,
        igAliasMemoryPool_GetMetaObjectFunction,
        "igAliasMemoryPool",
        0xB8,
        igAliasMemoryPool_GetVTable,
        igAliasMemoryPool_InitFields,
        0,
        g_igAliasMemoryPool_callbackList
    );
}

void igAliasMemoryPool_GetMetaObjectFunction(void) {
    igAliasMemoryPool_GetMetaObject();
}

igMetaObject *igMemoryPool_GetPublishedMetaObject(void) {
    return g_igMemoryPool_metaObject;
}

static FieldFactory g_igAliasMemoryPool_ctorTable[] = {
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igUnsignedLongMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igUnsignedLongMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igUnsignedLongMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igUnsignedShortMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igAliasMemoryPool_fieldTable[] = {
    "_poolIndex",
    "_allocedBytes",
    "_nAllocs",
    "_nFrees",
    "_maxSize",
    "_eventTracker",
    "_allocedBytesHigh",
    "_netAllocsHigh",
    "_isActive",
    "_isReassignable",
    "_allocationLock",
    "_elementSize",
    "_alignment",
    "_aliasedMemoryPool",
};
static igMetaField **g_igAliasMemoryPool_fieldDescriptors[] = {
    &g_igAliasMemoryPool_poolIndexMetaField,
    &g_igAliasMemoryPool_allocedBytesMetaField,
    &g_igAliasMemoryPool_nAllocsMetaField,
    &g_igAliasMemoryPool_nFreesMetaField,
    &g_igAliasMemoryPool_maxSizeMetaField,
    &g_igAliasMemoryPool_eventTrackerMetaField,
    &g_igAliasMemoryPool_allocedBytesHighMetaField,
    &g_igAliasMemoryPool_netAllocsHighMetaField,
    &g_igAliasMemoryPool_isActiveMetaField,
    &g_igAliasMemoryPool_isReassignableMetaField,
    &g_igAliasMemoryPool_allocationLockMetaField,
    &g_igAliasMemoryPool_elementSizeMetaField,
    &g_igAliasMemoryPool_alignmentMetaField,
    &g_igAliasMemoryPool_aliasedMemoryPoolMetaField,
};
static int g_igAliasMemoryPool_fieldOffsets[] = {
    120,
    128,
    136,
    140,
    144,
    152,
    160,
    168,
    112,
    113,
    116,
    172,
    176,
    180,
};

void igAliasMemoryPool_InitFields(void) {
    igObjectRefMetaField *eventTracker;
    igObjectRefMetaField *allocationLock;
    int base;
    igObjectRefMetaField *aliasedPool;
    igMetaObject *meta = g_igAliasMemoryPool_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igAliasMemoryPool_ctorTable, 14);
    igIntMetaField_SetDefault((void **)igMetaObject_GetFieldAt(meta, base), -1);
    igUnsignedLongMetaField_SetDefaultValue((void **)igMetaObject_GetFieldAt(meta, base + 4), 0xFFFFFFFFFFFFFFFFULL);
    eventTracker = (igObjectRefMetaField *)igMetaObject_GetFieldAt(meta, base + 5);
    eventTracker->_metaObject = (int)igEventTracker_GetOrCreateMetaObject();
    allocationLock = (igObjectRefMetaField *)igMetaObject_GetFieldAt(meta, base + 10);
    allocationLock->_metaObject = (int)igSemaphore_GetOrCreateMetaObject();
    igUnsignedShortMetaField_SetDefaultValue((void **)igMetaObject_GetFieldAt(meta, base + 12), 8);
    aliasedPool = (igObjectRefMetaField *)igMetaObject_GetFieldAt(meta, base + 13);
    aliasedPool->_metaObject = (int)igMemoryPool_GetOrCreateMetaObject();
    aliasedPool->_construct = 0;
    aliasedPool->_destruct = 0;
    igMetaObject_NameFields(meta, g_igAliasMemoryPool_fieldTable, g_igAliasMemoryPool_fieldDescriptors, g_igAliasMemoryPool_fieldOffsets, base);
    g_igAliasMemoryPool_metaObject->_writeProxy = (int)igMemoryPool_GetMetaObjectFunction;
}

static const char *g_igPageMemoryPool_messageLevelNames[] = {
    "kNoMessages", "kErrorMessages", "kWarningMessages", "kNotifications",
};
static int g_igPageMemoryPool_messageLevelValues[] = {
    0, 1, 2, 3,
};


int igPageMemoryPool_GetMessageLevelMetaEnum(void) {
    if (g_igPageMemoryPool_messageLevelMetaEnum == 0) {
        g_igPageMemoryPool_messageLevelMetaEnum = ((int)igMetaEnum_Create((char *)"MessageLevel", g_igPageMemoryPool_messageLevelNames, g_igPageMemoryPool_messageLevelValues, 4));
    }
    return g_igPageMemoryPool_messageLevelMetaEnum;
}

