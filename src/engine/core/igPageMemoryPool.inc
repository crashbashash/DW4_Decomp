int igPageMemoryPool_Clone(int source, int copyMode) {
    int clone;

    if (g_objectSystem->active != 0) {
        igPageMemoryPool_EnsureRegistered();
        return igObject_CloneViaMetadata((void **)source, copyMode);
    }
    clone = ((int)igObject_OperatorNew(0x110, 0, ((int)Memory_GetDefaultAllocator())));
    if (clone != 0) {
        clone = ((int)igPageMemoryPool_CopyConstruct((igPageMemoryPool *)clone, source));
    }
    return clone;
}

igMetaObject *g_igPageMemoryPool_metaObject;
igMetaField *g_igPageMemoryPool_maxSizeMetaField;
igMetaField *g_igPageMemoryPool_eventTrackerMetaField;
igMetaField *g_igPageMemoryPool_isActiveMetaField;
igMetaField *g_igPageMemoryPool_allocationLockMetaField;
igMetaField *g_igPageMemoryPool_poolIndexMetaField;
igMetaField *g_igPageMemoryPool_messageLevelMetaField;
igMetaField *g_igPageMemoryPool_poolOptionFlagsMetaField;
int g_arenaMemoryPoolFlagsMetaEnum;
int g_messageLevelMetaEnum;
int g_heapIntegrityCheckLevelMetaEnum;

igMetaObject *igPageMemoryPool_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igPageMemoryPool_metaObject != 0) {
        ready = (g_igPageMemoryPool_metaObject->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    igPageMemoryPool_EnsureRegistered();
done:
    return g_igPageMemoryPool_metaObject;
}

int igPageMemoryPool_GetVTable(void) {
    igPageMemoryPool pool;
    int result;
    igObject *q0;
    igObject *q1;
    igPageMemoryPool_Initialize(&pool);
    result = *(int *)((char *)&pool + g_objectSystem->vtableProbeOffset);
    pool._vtable = (int)&g_igPageMemoryPool_vtable[0];
    q0 = (igObject *)&pool._eventTracker;
    if (q0 != 0) {
        q0 = *(igObject **)q0;
        if (q0 != 0) {
            q0->_refCount = (int)((int) (q0->_refCount - 1));
            if (((unsigned long long) ((long long)(int) q0->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q0);
            }
        }
    }
    q1 = (igObject *)&pool._allocationLock;
    if (q1 != 0) {
        q1 = *(igObject **)q1;
        if (q1 != 0) {
            q1->_refCount = (int)((int) (q1->_refCount - 1));
            if (((unsigned long long) ((long long)(int) q1->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q1);
            }
        }
    }

    return result;
}

void igPageMemoryPool_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igPageMemoryPool_Register);
}

static igMetaObjectCallback g_igPageMemoryPool_callbackList[] = { igEventTracker_EnsureRegistered, igSemaphore_EnsureRegistered, 0 };

CallbackArray *igPageMemoryPool_Register(void) {
    return igMetaObject_RegisterClass(
        0,
        &g_igPageMemoryPool_metaObject,
        igMemoryPool_Register,
        igMemoryPool_GetPublishedMetaObject,
        igPageMemoryPool_GetMetaObjectFunction,
        "igPageMemoryPool",
        0x110,
        igPageMemoryPool_GetVTable,
        igPageMemoryPool_InitFields,
        0,
        g_igPageMemoryPool_callbackList
    );
}

void igPageMemoryPool_GetMetaObjectFunction(void) {
    igPageMemoryPool_GetMetaObject();
}

static FieldFactory g_igPageMemoryPool_ctorTable[] = {
    (FieldFactory)igUnsignedLongMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
};
static const char *g_igPageMemoryPool_fieldTable[] = {
    "_maxSize",
    "_eventTracker",
    "_isActive",
    "_allocationLock",
    "_poolIndex",
    "_messageLevel",
    "_poolOptionFlags",
};
static igMetaField **g_igPageMemoryPool_fieldDescriptors[] = {
    &g_igPageMemoryPool_maxSizeMetaField,
    &g_igPageMemoryPool_eventTrackerMetaField,
    &g_igPageMemoryPool_isActiveMetaField,
    &g_igPageMemoryPool_allocationLockMetaField,
    &g_igPageMemoryPool_poolIndexMetaField,
    &g_igPageMemoryPool_messageLevelMetaField,
    &g_igPageMemoryPool_poolOptionFlagsMetaField,
};
static int g_igPageMemoryPool_fieldOffsets[] = {
    120,
    128,
    112,
    116,
    132,
    136,
    140,
};

int g_igPageMemoryPool_defaultPoolOptionFlags = 6;

int g_igPageMemoryPool_defaultMessageLevel = 1;

void igPageMemoryPool_InitFields(void) {
    igMetaObject *meta = g_igPageMemoryPool_metaObject;
    int base = igMetaObject_GetFieldCount(meta);
    int defaultMessageLevel;
    igObjectRefMetaField *eventTracker;
    igObjectRefMetaField *allocationLock;
    igEnumMetaField *messageLevel;
    igMetaObject_CreateFields(meta, g_igPageMemoryPool_ctorTable, 7);
    ((Gap::Core::igUnsignedLongMetaField *)(igMetaObject_GetFieldAt(meta, base)))->setDefault(0xFFFFFFFFFFFFFFFFULL);
    eventTracker = (igObjectRefMetaField *)igMetaObject_GetFieldAt(meta, base + 1);
    eventTracker->_metaObject = (int)igEventTracker_GetOrCreateMetaObject();
    allocationLock = (igObjectRefMetaField *)igMetaObject_GetFieldAt(meta, base + 3);
    allocationLock->_metaObject = (int)igSemaphore_GetOrCreateMetaObject();
    ((Gap::Core::igIntMetaField *)(igMetaObject_GetFieldAt(meta, base + 4)))->setDefault(-1);
    messageLevel = (igEnumMetaField *)igMetaObject_GetFieldAt(meta, base + 5);
    defaultMessageLevel = g_igPageMemoryPool_defaultMessageLevel;
    ((Gap::Core::igEnumMetaField *)messageLevel)->setDefault(defaultMessageLevel);
    messageLevel->_getMetaEnumFunction = (int)igPageMemoryPool_GetMessageLevelMetaEnum;
    ((Gap::Core::igIntMetaField *)(igMetaObject_GetFieldAt(meta, base + 6)))->setDefault(g_igPageMemoryPool_defaultPoolOptionFlags);
    igMetaObject_NameFields(meta, g_igPageMemoryPool_fieldTable, g_igPageMemoryPool_fieldDescriptors, g_igPageMemoryPool_fieldOffsets, base);
    g_igPageMemoryPool_metaObject->_writeProxy = (int)igMemoryPool_GetMetaObjectFunction;
}

static const char *g_arenaMemoryPoolFlagsNames[] = {
    "kSentinels", "kFillMemory", "kZeroMemory", "kAutoLock",
    "kContiguous", "kAssertOnMaxSizeReached", "kAssertOnPreSizeReached", "kAssertOnSystemMemoryExhausted",
    "kAssertOnMemoryOperation", "kInhibitArenaCountMessage",
};
static int g_arenaMemoryPoolFlagsValues[] = {
    1, 2, 4, 8, 0x10, 0x20, 0x40, 0x80,
    0x100, 0x200,
};


int igArenaMemoryPool_GetArenaMemoryPoolFlagsMetaEnum(void) {
    if (g_arenaMemoryPoolFlagsMetaEnum == 0) {
        g_arenaMemoryPoolFlagsMetaEnum = ((int)igMetaEnum_Create((char *)"ArenaMemoryPoolFlags", g_arenaMemoryPoolFlagsNames, g_arenaMemoryPoolFlagsValues, 0xA));
    }
    return g_arenaMemoryPoolFlagsMetaEnum;
}

static const char *g_messageLevelNames[] = {
    "kNoMessages", "kErrorMessages", "kWarningMessages", "kNotifications",
};
static int g_messageLevelValues[] = {
    0, 1, 2, 3,
};


int igArenaMemoryPool_GetMessageLevelMetaEnum(void) {
    if (g_messageLevelMetaEnum == 0) {
        g_messageLevelMetaEnum = ((int)igMetaEnum_Create((char *)"MessageLevel", g_messageLevelNames, g_messageLevelValues, 4));
    }
    return g_messageLevelMetaEnum;
}

static const char *g_heapIntegrityCheckLevelNames[] = {
    "kNoChecking", "kLightChecking", "kModerateChecking", "kHeavyChecking",
};
static int g_heapIntegrityCheckLevelValues[] = {
    0, 1, 2, 3,
};


int igArenaMemoryPool_GetHeapIntegrityCheckLevelMetaEnum(void) {
    if (g_heapIntegrityCheckLevelMetaEnum == 0) {
        g_heapIntegrityCheckLevelMetaEnum = ((int)igMetaEnum_Create((char *)"HeapIntegrityCheckLevel", g_heapIntegrityCheckLevelNames, g_heapIntegrityCheckLevelValues, 4));
    }
    return g_heapIntegrityCheckLevelMetaEnum;
}

