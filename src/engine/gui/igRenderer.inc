igMetaObject *g_igRenderer_metaObject;
igMetaField *g_igRenderer_visualContextMetaField;

igMetaObject *igRenderer_GetMetaObject(void)
{
    igMetaObject *g = g_igRenderer_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igRenderer_EnsureRegistered();
    return g_igRenderer_metaObject;
}

void igRenderer_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igRenderer_Register);
}

static igMetaObjectCallback g_igRenderer_callbackList[] = { igVisualContext_EnsureRegistered, 0 };

CallbackArray *igRenderer_Register(void) {
    GuiLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igRenderer_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        igRenderer_GetMetaObjectFunction,
        "igRenderer",
        0xC, /* instance size */
        0,
        &igRenderer_InitFields,
        0, /* extra callback item */
        g_igRenderer_callbackList /* callback list */
    );
}

void igRenderer_GetMetaObjectFunction(void) {
    igRenderer_GetMetaObject();
}

static FieldFactory g_igRenderer_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_igRenderer_fieldTable[] = {
    "_visualContext",
};
static igMetaField **g_igRenderer_fieldHandles[] = {
    &g_igRenderer_visualContextMetaField,
};
static int g_igRenderer_fieldOffsets[] = {
    8,
};

void igRenderer_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_igRenderer_metaObject;
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igRenderer_ctorTable, 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)(igVisualContext_GetOrCreateMetaObject());
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igRenderer_fieldTable, g_igRenderer_fieldHandles, g_igRenderer_fieldOffsets, temp_s2);
}

