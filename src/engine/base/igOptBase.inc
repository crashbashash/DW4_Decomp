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
        thunk_igOptBase_GetMetaObject,
        "igOptBase",
        0x28, /* instance size */
        0,
        &igOptBase_InitFields,
        0, /* extra callback item */
        (igMetaObjectCallback *)g_igOptBase_callbackList /* callback list */
    );
}

void thunk_igOptBase_GetMetaObject(void) {
    igOptBase_GetMetaObject();
}

igMetaObject *FUN_00226010(void) {
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
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_igOptBase_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_igOptBase_ctorTable, 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = igRegistry_GetOrCreateMetaObject();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)FUN_00225dc0();
    igMetaObject_NameFields(temp_s0, g_igOptBase_fieldTable, g_igOptBase_fieldHandles, g_igOptBase_fieldOffsets, temp_s2);
}

