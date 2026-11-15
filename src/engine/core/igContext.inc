igMetaObject *g_igContext_metaObject;
igMetaField *g_igContext_pExtListMetaField;
igMetaField *g_igContext_iNumExtsMetaField;
igMetaField *g_igContext_pExtInstancesMetaField;

igMetaObject *igContext_GetMetaObject(void)
{
    igMetaObject *g = g_igContext_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igContext_EnsureRegistered();
    return g_igContext_metaObject;
}

void igContext_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igContext_Register);
}

static igMetaObjectCallback g_igContext_callbackList[] = { igContextExtInfoList_EnsureRegistered, igContextExtList_EnsureRegistered, 0 };

void igContext_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1,
        &g_igContext_metaObject,
        (igMetaObjectRegisterFunction)igObject_Register,
        (igMetaObjectGetFunction)igObject_GetMetaObject_ParentAccessor,
        igContext_GetMetaObjectFunction,
        "igContext",
        0x14,
        0,
        igContext_InitFields,
        0,
        g_igContext_callbackList
    );
}

void igContext_GetMetaObjectFunction(void) {
    igContext_GetMetaObject();
}

static FieldFactory g_igContext_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igContext_fieldTable[] = {
    "_pExtList",
    "_iNumExts",
    "_pExtInstances",
};
static igMetaField **g_igContext_fieldDescriptors[] = {
    &g_igContext_pExtListMetaField,
    &g_igContext_iNumExtsMetaField,
    &g_igContext_pExtInstancesMetaField,
};
static int g_igContext_fieldOffsets[] = {
    8,
    12,
    16,
};

void igContext_InitFields(void) {
    int base;
    void *extInstances;
    void *extList;
    void *meta;

    meta = (void *)g_igContext_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igContext_ctorTable, 3);
    extList = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base)));
    ((igObjectRefMetaField *)extList)->_metaObject = (int)igContextExtInfoList_GetOrCreateMetaObject();
    extInstances = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 2)));
    ((igObjectRefMetaField *)extInstances)->_metaObject = (int)igContextExtList_GetOrCreateMetaObject();
    ((igRefMetaField *)extInstances)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)meta, g_igContext_fieldTable, g_igContext_fieldDescriptors, g_igContext_fieldOffsets, base);
}

