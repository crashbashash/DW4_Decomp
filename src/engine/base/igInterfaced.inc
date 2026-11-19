igMetaObject *g_igInterfaced_metaObject;
igMetaField *g_igInterfaced_optInterfaceMetaField;
igMetaField *g_igInterfaced_itemInterfaceMetaField;
igMetaField *g_igInterfaced_listenerInterfaceMetaField;
igMetaField *g_igInterfaced_messageInterfaceMetaField;
igMetaField *g_igInterfaced_lockInterfaceMetaField;
igMetaField *g_igInterfaced_logInterfaceMetaField;

igMetaObject *igInterfaced_GetMetaObject(void)
{
    igMetaObject *g = g_igInterfaced_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00228a20();
    return g_igInterfaced_metaObject;
}

void FUN_00228a20(void)
{
    igMetaObject_RunStaticInit((igMetaObjectRegisterFunction)igInterfaced_Register);
}

static igMetaObjectCallback g_igInterfaced_callbackList[] = { FUN_00225c10, FUN_00227ef0, FUN_00226e30, FUN_00226200, FUN_00226a10, FUN_002266c0, 0 };

CallbackArray *igInterfaced_Register(void) {
    BaseLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igInterfaced_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        igInterfaced_GetMetaObjectFunction,
        "igInterfaced",
        0x20, /* instance size */
        0,
        &igInterfaced_InitFields,
        0, /* extra callback item */
        g_igInterfaced_callbackList /* callback list */
    );
}

void igInterfaced_GetMetaObjectFunction(void) {
    igInterfaced_GetMetaObject();
}

static FieldFactory g_igInterfaced_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igInterfaced_fieldTable[] = {
    "_optInterface",
    "_itemInterface",
    "_listenerInterface",
    "_messageInterface",
    "_lockInterface",
    "_logInterface",
};
static igMetaField **g_igInterfaced_fieldHandles[] = {
    &g_igInterfaced_optInterfaceMetaField,
    &g_igInterfaced_itemInterfaceMetaField,
    &g_igInterfaced_listenerInterfaceMetaField,
    &g_igInterfaced_messageInterfaceMetaField,
    &g_igInterfaced_lockInterfaceMetaField,
    &g_igInterfaced_logInterfaceMetaField,
};
static int g_igInterfaced_fieldOffsets[] = {
    8,
    12,
    16,
    20,
    24,
    28,
};

void igInterfaced_InitFields(void) {
    int base;
    void *field;
    void *field2;
    void *field3;
    void *field4;
    void *field5;
    void *field6;
    igMetaObject *meta;

    meta = g_igInterfaced_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igInterfaced_ctorTable, 6);
    field = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)field)->_metaObject = (int)igOptInterface_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)field)->_refCounted = 0;
    field2 = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)field2)->_metaObject = (int)igItemInterface_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)field2)->_refCounted = 0;
    field3 = (void *)(igMetaObject_GetFieldAt(meta, base + 2));
    ((igObjectRefMetaField *)field3)->_metaObject = (int)igListenerInterface_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)field3)->_refCounted = 0;
    field4 = (void *)(igMetaObject_GetFieldAt(meta, base + 3));
    ((igObjectRefMetaField *)field4)->_metaObject = (int)igMessageInterface_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)field4)->_refCounted = 0;
    field5 = (void *)(igMetaObject_GetFieldAt(meta, base + 4));
    ((igObjectRefMetaField *)field5)->_metaObject = (int)igLockInterface_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)field5)->_refCounted = 0;
    field6 = (void *)(igMetaObject_GetFieldAt(meta, base + 5));
    ((igObjectRefMetaField *)field6)->_metaObject = (int)igLogInterface_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)field6)->_refCounted = 0;
    igMetaObject_NameFields(meta, g_igInterfaced_fieldTable, g_igInterfaced_fieldHandles, g_igInterfaced_fieldOffsets, base);
}

