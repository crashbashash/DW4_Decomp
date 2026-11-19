igMetaObject *g_igInterfaceManager_metaObject;
igMetaField *g_igInterfaceManager_devicesMetaField;

igMetaObject *igInterfaceManager_GetMetaObject(void)
{
    igMetaObject *g = g_igInterfaceManager_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igInterfaceManager_EnsureRegistered();
    return g_igInterfaceManager_metaObject;
}

void igInterfaceManager_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igInterfaceManager_Register);
}

static igMetaObjectCallback g_igInterfaceManager_callbackList[] = { igEventProducerList_EnsureRegistered, 0 };

CallbackArray *igInterfaceManager_Register(void) {
    WindowInputLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igInterfaceManager_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        igInterfaceManager_GetMetaObjectFunction,
        "igInterfaceManager",
        0xC, /* instance size */
        0,
        &igInterfaceManager_InitFields,
        0, /* extra callback item */
        g_igInterfaceManager_callbackList /* callback list */
    );
}

void igInterfaceManager_GetMetaObjectFunction(void) {
    igInterfaceManager_GetMetaObject();
}

static FieldFactory g_igInterfaceManager_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_igInterfaceManager_fieldTable[] = {
    "_devices",
};
static igMetaField **g_igInterfaceManager_fieldHandles[] = {
    &g_igInterfaceManager_devicesMetaField,
};
static int g_igInterfaceManager_fieldOffsets[] = {
    8,
};

void igInterfaceManager_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_igInterfaceManager_metaObject;
    temp_s2 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, g_igInterfaceManager_ctorTable, 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)igEventProducerList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igInterfaceManager_fieldTable, g_igInterfaceManager_fieldHandles, g_igInterfaceManager_fieldOffsets, temp_s2);
    *(int *)((char *)(g_igInterfaceManager_metaObject) + 60) = (int)(igDefaultInterfaceManager_GetMetaObjectFunction);
}

void igDefaultInterfaceManager_GetMetaObjectFunction(void) {
    igDefaultInterfaceManager_GetMetaObject();
}

