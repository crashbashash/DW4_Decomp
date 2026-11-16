igMetaObject *g_igThreadManager_metaObject;
igMetaField *g_igThreadManager_threadListMetaField;
igMetaField *g_igThreadManager_semaMetaField;
int g_igThread_priorityMetaEnum;
int g_igThread_stateMetaEnum;
int g_igThread_scopeMetaEnum;
int g_igThread_typeMetaEnum;

void * igThreadManager_Create(int allocator) {
    igThreadManager_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance(g_igThreadManager_metaObject, (igMemoryPoolView *)allocator));
}

igMetaObject *igThreadManager_GetMetaObject(void)
{
    igMetaObject *g = g_igThreadManager_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igThreadManager_EnsureRegistered();
    return g_igThreadManager_metaObject;
}

void igThreadManager_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igThreadManager_Register);
}

static igMetaObjectCallback g_igThreadManager_callbackList[] = { igNonRefCountedThreadList_EnsureRegistered, igSemaphore_EnsureRegistered, 0 };

CallbackArray *igThreadManager_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1,
        &g_igThreadManager_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        igThreadManager_GetMetaObjectFunction,
        "igThreadManager",
        0x10,
        0,
        igThreadManager_InitFields,
        igThreadManager_StaticInitCallback,
        g_igThreadManager_callbackList
    );
}

void igThreadManager_GetMetaObjectFunction(void) {
    igThreadManager_GetMetaObject();
}

static FieldFactory g_igThreadManager_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igThreadManager_fieldTable[] = {
    "_threadList",
    "_sema",
};
static igMetaField **g_igThreadManager_fieldDescriptors[] = {
    &g_igThreadManager_threadListMetaField,
    &g_igThreadManager_semaMetaField,
};
static int g_igThreadManager_fieldOffsets[] = {
    8,
    12,
};

void igThreadManager_InitFields(void) {
    int base;
    void *semaField;
    void *threadListField;
    void *meta;

    ((igMetaObject *)(g_igThreadManager_metaObject))->_volatile = 1;
    meta = (void *)(g_igThreadManager_metaObject);
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igThreadManager_ctorTable, 2);
    threadListField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base)));
    ((igObjectRefMetaField *)threadListField)->_metaObject = (int)igNonRefCountedThreadList_GetOrCreateMetaObject();
    ((igRefMetaField *)threadListField)->_construct = 1;
    semaField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 1)));
    ((igObjectRefMetaField *)semaField)->_metaObject = (int)igSemaphore_GetOrCreateMetaObject();
    ((igRefMetaField *)semaField)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)meta, g_igThreadManager_fieldTable, g_igThreadManager_fieldDescriptors, g_igThreadManager_fieldOffsets, base);
    ((igMetaObject *)(g_igThreadManager_metaObject))->_abstractProxy = (int)igPsx2ThreadManager_GetMetaObjectFunction;
    igMetaObject_AddExitCallback((int)igThreadManager_ExitCallback);
}

