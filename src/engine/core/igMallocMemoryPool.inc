static const char *g_igMallocMemoryPool_messageLevelNames[] = {
    "kNoMessages", "kErrorMessages", "kWarningMessages", "kNotifications",
};
static int g_igMallocMemoryPool_messageLevelValues[] = {
    0, 1, 2, 3,
};


int igMallocMemoryPool_GetMessageLevelMetaEnum(void) {
    if (g_igMallocMemoryPool_messageLevelMetaEnum == 0) {
        g_igMallocMemoryPool_messageLevelMetaEnum = ((int)igMetaEnum_Create((char *)"MessageLevel", g_igMallocMemoryPool_messageLevelNames, g_igMallocMemoryPool_messageLevelValues, 4));
    }
    return g_igMallocMemoryPool_messageLevelMetaEnum;
}

unsigned char g_igMallocMemoryPool_instanceCount;

void igMallocMemoryPool_InitDefaults(int extra0) {
    g_igMallocMemoryPool_instanceCount = (g_igMallocMemoryPool_instanceCount + 1);
    igMemoryPool_InitDefaults((void *)extra0);
}

void *igMallocMemoryPool_Clone(void *self, void *src) {
    void *o;
    if (*g_objectSystem != 0) {
        igMallocMemoryPool_EnsureRegistered();
        return ((void *)igObject_CloneViaMetadata((void **)self, (int)src));
    }
    o = igObject_OperatorNew(0xA0, 0, (int)(Memory_GetDefaultAllocator()));
    if (o != 0) {
        o = igMallocMemoryPool_CopyConstruct((igMallocMemoryPool *)o, (int)self);
    }
    return o;
}

igMetaObject *g_igMallocMemoryPool_metaObject;
igMetaField *g_igMallocMemoryPool_poolIndexMetaField;
igMetaField *g_igMallocMemoryPool_elementSizeMetaField;
igMetaField *g_igMallocMemoryPool_maxSizeMetaField;
igMetaField *g_igMallocMemoryPool_sizeMetaField;
igMetaField *g_igMallocMemoryPool_alignmentMetaField;
igMetaField *g_igMallocMemoryPool_eventTrackerMetaField;
igMetaField *g_igMallocMemoryPool_isActiveMetaField;
igMetaField *g_igMallocMemoryPool_allocationLockMetaField;
igMetaField *g_igMallocMemoryPool_messageLevelMetaField;
igMetaField *g_igMallocMemoryPool_poolOptionFlagsMetaField;

igMetaObject *igMallocMemoryPool_GetMetaObject(void)
{
    unsigned char ready;
    if (g_igMallocMemoryPool_metaObject != 0) {
        ready = (g_igMallocMemoryPool_metaObject->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    igMallocMemoryPool_EnsureRegistered();
done:
    return g_igMallocMemoryPool_metaObject;
}

int igMallocMemoryPool_GetVTable(void) {
    igMallocMemoryPool pool;
    int vtable;
    igObject *q0;
    igObject *q1;
    igMallocMemoryPool_Initialize(&pool);
    vtable = *(int *)((char *)&pool + *(int *)((char *)((*(void * *)&g_objectSystem)) + 916));
    pool._vtable = (int)&g_igMallocMemoryPool_vtable[0];
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

    return vtable;
}

void igMallocMemoryPool_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igMallocMemoryPool_Register);
}

static igMetaObjectCallback g_igMallocMemoryPool_callbackList[] = { igEventTracker_EnsureRegistered, igSemaphore_EnsureRegistered, 0 };

void igMallocMemoryPool_Register(void) {
    igMetaObject_RegisterClass(
        0,
        &g_igMallocMemoryPool_metaObject,
        (igMetaObjectRegisterFunction)igMemoryPool_Register,
        igMemoryPool_GetPublishedMetaObject,
        igMallocMemoryPool_GetMetaObjectFunction,
        "igMallocMemoryPool",
        0xA0,
        igMallocMemoryPool_GetVTable,
        igMallocMemoryPool_InitFields,
        0,
        g_igMallocMemoryPool_callbackList
    );
}

void igMallocMemoryPool_GetMetaObjectFunction(void) {
    igMallocMemoryPool_GetMetaObject();
}

static FieldFactory g_igMallocMemoryPool_ctorTable[] = {
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igUnsignedIntMetaField_Create,
    (FieldFactory)igUnsignedLongMetaField_Create,
    (FieldFactory)igUnsignedLongMetaField_Create,
    (FieldFactory)igUnsignedShortMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
};
static const char *g_igMallocMemoryPool_fieldTable[] = {
    "_poolIndex",
    "_elementSize",
    "_maxSize",
    "_size",
    "_alignment",
    "_eventTracker",
    "_isActive",
    "_allocationLock",
    "_messageLevel",
    "_poolOptionFlags",
};
static igMetaField **g_igMallocMemoryPool_fieldDescriptors[] = {
    &g_igMallocMemoryPool_poolIndexMetaField,
    &g_igMallocMemoryPool_elementSizeMetaField,
    &g_igMallocMemoryPool_maxSizeMetaField,
    &g_igMallocMemoryPool_sizeMetaField,
    &g_igMallocMemoryPool_alignmentMetaField,
    &g_igMallocMemoryPool_eventTrackerMetaField,
    &g_igMallocMemoryPool_isActiveMetaField,
    &g_igMallocMemoryPool_allocationLockMetaField,
    &g_igMallocMemoryPool_messageLevelMetaField,
    &g_igMallocMemoryPool_poolOptionFlagsMetaField,
};
static int g_igMallocMemoryPool_fieldOffsets[] = {
    120,
    124,
    128,
    136,
    144,
    148,
    112,
    116,
    152,
    156,
};

int g_igMallocMemoryPool_defaultPoolOptionFlags = 0xc;

int g_igMallocMemoryPool_defaultMessageLevel = 1;

void igMallocMemoryPool_InitFields(void) {
    igMetaObject *meta = g_igMallocMemoryPool_metaObject;
    int base = igMetaObject_GetFieldCount(meta);
    igObjectRefMetaField *eventTracker;
    igObjectRefMetaField *allocationLock;
    igEnumMetaField *messageLevel;
    int defaultMessageLevel;
    igMetaObject_CreateFields(meta, g_igMallocMemoryPool_ctorTable, 10);
    igIntMetaField_SetDefault((void **)igMetaObject_GetFieldAt(meta, base), -1);
    igUnsignedLongMetaField_SetDefaultValue((void **)igMetaObject_GetFieldAt(meta, base + 2), 0xFFFFFFFFFFFFFFFFULL);
    igUnsignedShortMetaField_SetDefaultValue((void **)igMetaObject_GetFieldAt(meta, base + 4), 4);
    eventTracker = (igObjectRefMetaField *)igMetaObject_GetFieldAt(meta, base + 5);
    eventTracker->_metaObject = (int)igEventTracker_GetOrCreateMetaObject();
    allocationLock = (igObjectRefMetaField *)igMetaObject_GetFieldAt(meta, base + 7);
    allocationLock->_metaObject = (int)igSemaphore_GetOrCreateMetaObject();
    messageLevel = (igEnumMetaField *)igMetaObject_GetFieldAt(meta, base + 8);
    defaultMessageLevel = g_igMallocMemoryPool_defaultMessageLevel;
    igEnumMetaField_SetDefaultValue((igMetaFieldView *)messageLevel, &defaultMessageLevel);
    messageLevel->_getMetaEnumFunction = (int)igMallocMemoryPool_GetMessageLevelMetaEnum;
    igIntMetaField_SetDefault((void **)igMetaObject_GetFieldAt(meta, base + 9), g_igMallocMemoryPool_defaultPoolOptionFlags);
    igMetaObject_NameFields(meta, g_igMallocMemoryPool_fieldTable, g_igMallocMemoryPool_fieldDescriptors, g_igMallocMemoryPool_fieldOffsets, base);
    g_igMallocMemoryPool_metaObject->_writeProxy = (int)igMemoryPool_GetMetaObjectFunction;
}

