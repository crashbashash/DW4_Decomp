igMetaObject *g_igOptBase_metaObject;
igMetaField *g_igOptBase_registryMetaField;
igMetaField *g_igOptBase_configurationMetaField;

igMetaObject *igOptBase_GetMetaObject(void)
{
    igMetaObject *g = g_igOptBase_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00225f80();
    return g_igOptBase_metaObject;
}

void FUN_00225f80(void)
{
    igMetaObject_RunStaticInit((igMetaObjectRegisterFunction)igOptBase_Register);
}

static igMetaObjectCallback g_igOptBase_callbackList[] = { igRegistry_EnsureRegistered, FUN_00225ea0, 0 };

CallbackArray *igOptBase_Register(void) {
    BaseLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igOptBase_metaObject,
        (igMetaObjectRegisterFunction)igBase_Register,
        (igMetaObjectGetFunction)igBase_GetPublishedMetaObject,
        igOptBase_GetMetaObjectFunction,
        "igOptBase",
        0x28, /* instance size */
        0,
        &igOptBase_InitFields,
        0, /* extra callback item */
        (igMetaObjectCallback *)g_igOptBase_callbackList /* callback list */
    );
}

void igOptBase_GetMetaObjectFunction(void) {
    igOptBase_GetMetaObject();
}

igMetaObject *igBase_GetPublishedMetaObject(void) {
    return g_igBase_metaObject;
}

static FieldFactory g_igOptBase_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igOptBase_fieldTable[] = {
    "_registry",
    "_configuration",
};
static igMetaField **g_igOptBase_fieldHandles[] = {
    &g_igOptBase_registryMetaField,
    &g_igOptBase_configurationMetaField,
};
static int g_igOptBase_fieldOffsets[] = {
    32,
    36,
};

void igOptBase_InitFields(void) {
    int base;
    void *field;
    void *field2;
    igMetaObject *meta;

    meta = g_igOptBase_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_igOptBase_ctorTable, 2);
    field2 = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)field2)->_metaObject = (int)igRegistry_GetOrCreateMetaObject();
    field = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)field)->_metaObject = (int)igOptConfiguration_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_igOptBase_fieldTable, g_igOptBase_fieldHandles, g_igOptBase_fieldOffsets, base);
}

