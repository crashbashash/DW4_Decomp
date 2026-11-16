igMetaObject *g_igInterfaceManager_metaObject;
igMetaField *g_igInterfaceManager_devicesMetaField;

igMetaObject *igInterfaceManager_GetMetaObject(void)
{
    igMetaObject *g = g_igInterfaceManager_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00145f60();
    return g_igInterfaceManager_metaObject;
}

void FUN_00145f60(void)
{
    igMetaObject_RunStaticInit(igInterfaceManager_Register);
}

static igMetaObjectCallback g_igInterfaceManager_callbackList[] = { FUN_00146190, 0 };

CallbackArray *igInterfaceManager_Register(void) {
    WindowInputLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igInterfaceManager_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igInterfaceManager_GetMetaObject,
        "igInterfaceManager",
        0xC, /* instance size */
        0,
        &igInterfaceManager_InitFields,
        0, /* extra callback item */
        g_igInterfaceManager_callbackList /* callback list */
    );
}

void thunk_igInterfaceManager_GetMetaObject(void) {
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
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_001460b0();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)temp_s0, g_igInterfaceManager_fieldTable, g_igInterfaceManager_fieldHandles, g_igInterfaceManager_fieldOffsets, temp_s2);
    *(int *)((char *)(g_igInterfaceManager_metaObject) + 60) = (int)(thunk_FUN_00146470);
}

void thunk_FUN_00146470(void) {
    FUN_00146470();
}

