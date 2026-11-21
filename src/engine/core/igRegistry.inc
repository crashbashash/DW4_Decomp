igMetaObject *g_igRegistry_metaObject;
igMetaField *g_igRegistry_valueTableMetaField;
igMetaField *g_igRegistry_registryFileMetaField;
igMetaField *g_igRegistry_additionalSectionNamesMetaField;
igMetaField *g_igRegistry_showQueriesMetaField;
igMetaField *g_igRegistry_valueNameCaseSensitiveMetaField;

void * igRegistry_Create(int pool) {
    igRegistry_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance(g_igRegistry_metaObject, (igMemoryPoolView *)pool));
}

igMetaObject *igRegistry_GetOrCreateMetaObject(void) {
    if (g_igRegistry_metaObject == 0) {
        g_igRegistry_metaObject = (igMetaObject *)igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igRegistry_metaObject;
}

igMetaObject *igRegistry_GetMetaObject(void)
{
    igMetaObject *g = g_igRegistry_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igRegistry_EnsureRegistered();
    return g_igRegistry_metaObject;
}

int igRegistry_GetVTable(void) {
    igRegistry registry;
    int vtable;
    igObject *q0;
    igObject *q1;
    igObject *q2;

    igObject_InitHeader((igObject *)&registry);
    registry._vtable = (int)&g_igRegistry_vtable[0];
    q2 = (igObject *)&registry._valueTable;
    *(int *)q2 = 0;
    q1 = (igObject *)&registry._registryFile;
    *(int *)q1 = 0;
    q0 = (igObject *)&registry._additionalSectionNames;
    *(int *)q0 = 0;
    vtable = *(int *)((char *)&registry + g_objectSystem->vtableProbeOffset);
    registry._vtable = (int)&g_igRegistry_vtable[0];
    if (q0 != 0) {
        q0 = *(igObject **)q0;
        igObject::release(q0);
    }
    if (q1 != 0) {
        q1 = *(igObject **)q1;
        igObject::release(q1);
    }
    if (q2 != 0) {
        q2 = *(igObject **)q2;
        igObject::release(q2);
    }
    return vtable;
}

void igRegistry_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igRegistry_Register);
}

static igMetaObjectCallback g_igRegistry_callbackList[] = { igRegistryValueList_EnsureRegistered, igFile_EnsureRegistered, igStringObjList_EnsureRegistered, 0 };

CallbackArray *igRegistry_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igRegistry_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        igRegistry_GetMetaObjectFunction,
        "igRegistry",
        0x18,
        igRegistry_GetVTable,
        igRegistry_InitFields,
        0,
        g_igRegistry_callbackList
    );
}

void igRegistry_GetMetaObjectFunction(void) {
    igRegistry_GetMetaObject();
}

static FieldFactory g_igRegistry_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
};
static const char *g_igRegistry_fieldTable[] = {
    "_valueTable",
    "_registryFile",
    "_additionalSectionNames",
    "_showQueries",
    "_valueNameCaseSensitive",
};
static igMetaField **g_igRegistry_fieldDescriptors[] = {
    &g_igRegistry_valueTableMetaField,
    &g_igRegistry_registryFileMetaField,
    &g_igRegistry_additionalSectionNamesMetaField,
    &g_igRegistry_showQueriesMetaField,
    &g_igRegistry_valueNameCaseSensitiveMetaField,
};
static int g_igRegistry_fieldOffsets[] = {
    8,
    12,
    16,
    20,
    21,
};

void igRegistry_InitFields(void) {
    int first;
    void *valueTableField;
    void *registryFileField;
    void *sectionNamesField;
    void *meta;

    meta = (void *)g_igRegistry_metaObject;
    first = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igRegistry_ctorTable, 5);
    valueTableField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, first)));
    ((igObjectRefMetaField *)valueTableField)->_metaObject = (int)igRegistryValueList_GetOrCreateMetaObject();
    ((igRefMetaField *)valueTableField)->_construct = 1;
    registryFileField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, first + 1)));
    ((igObjectRefMetaField *)registryFileField)->_metaObject = (int)igFile_GetOrCreateMetaObject();
    ((igRefMetaField *)registryFileField)->_construct = 1;
    sectionNamesField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, first + 2)));
    ((igObjectRefMetaField *)sectionNamesField)->_metaObject = (int)igStringObjList_GetOrCreateMetaObject();
    ((igRefMetaField *)sectionNamesField)->_construct = 1;
    ((Gap::Core::igBoolMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)meta, first + 4)))->setDefault(1);
    igMetaObject_NameFields((igMetaObject *)meta, g_igRegistry_fieldTable, g_igRegistry_fieldDescriptors, g_igRegistry_fieldOffsets, first);
}

