igMetaObject *g_igQueue_metaObject;
igMetaField *g_igQueue_serviceThreadsMetaField;

void * igQueue_Create(int pool) {
    igQueue_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance(g_igQueue_metaObject, (igMemoryPoolView *)pool));
}

igMetaObject *igQueue_GetOrCreateMetaObject(void) {
    if (g_igQueue_metaObject == 0) {
        g_igQueue_metaObject = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igQueue_metaObject;
}

igMetaObject *igQueue_GetMetaObject(void)
{
    igMetaObject *g = g_igQueue_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igQueue_EnsureRegistered();
    return g_igQueue_metaObject;
}

void igQueue_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igQueue_Register);
}

static igMetaObjectCallback g_igQueue_callbackList[] = { igThreadList_EnsureRegistered, 0 };

void igQueue_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1,
        &g_igQueue_metaObject,
        (igMetaObjectRegisterFunction)igObject_Register,
        (igMetaObjectGetFunction)igObject_GetMetaObject_ParentAccessor,
        igQueue_GetMetaObjectFunction,
        "igQueue",
        0xC,
        0,
        igQueue_InitFields,
        0,
        g_igQueue_callbackList
    );
}

void igQueue_GetMetaObjectFunction(void) {
    igQueue_GetMetaObject();
}

static FieldFactory g_igQueue_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igQueue_fieldTable[] = {
    "_serviceThreads",
};
static igMetaField **g_igQueue_fieldDescriptors[] = {
    &g_igQueue_serviceThreadsMetaField,
};
static int g_igQueue_fieldOffsets[] = {
    8,
};

void igQueue_InitFields(void) {
    int base;
    igObjectRefMetaField *threads;
    igMetaObject *meta;

    meta = g_igQueue_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igQueue_ctorTable, 1);
    threads = (igObjectRefMetaField *)igMetaObject_GetFieldAt(meta, base);
    threads->_metaObject = (int)igThreadList_GetOrCreateMetaObject();
    threads->_construct = 1;
    igMetaObject_NameFields(meta, g_igQueue_fieldTable, g_igQueue_fieldDescriptors, g_igQueue_fieldOffsets, base);
    g_igQueue_metaObject->_abstractProxy = (int)igStandardQueue_GetMetaObjectFunction;
}

