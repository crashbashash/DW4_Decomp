igMetaObject *g_igView_metaObject;
igMetaField *g_igView_modelMetaField;

igMetaObject *igView_GetMetaObject(void)
{
    igMetaObject *g = g_igView_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igView_EnsureRegistered();
    return g_igView_metaObject;
}

void igView_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igView_Register);
}

static igMetaObjectCallback g_igView_callbackList[] = { igModel_RunStaticInit, 0 };

CallbackArray *igView_Register(void) {
    GuiLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igView_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igView_GetMetaObject,
        "igView",
        0xC, /* instance size */
        0,
        &igView_InitFields,
        0, /* extra callback item */
        g_igView_callbackList /* callback list */
    );
}

void thunk_igView_GetMetaObject(void) {
    igView_GetMetaObject();
}

static FieldFactory g_igView_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_igView_fieldTable[] = {
    "_model",
};
static igMetaField **g_igView_fieldHandles[] = {
    &g_igView_modelMetaField,
};
static int g_igView_fieldOffsets[] = {
    8,
};

void igView_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igView_metaObject;
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igView_ctorTable, 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_0044d5d0();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igView_fieldTable, g_igView_fieldHandles, g_igView_fieldOffsets, temp_s2);
}

