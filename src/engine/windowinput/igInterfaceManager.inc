igMetaObject *igInterfaceManager_GetMetaObject(void)
{
    igMetaObject *g = g_igInterfaceManager_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00145f60();
    return g_igInterfaceManager_metaObject[0];
}

void FUN_00145f60(void)
{
    igMetaObject_RunStaticInit(igInterfaceManager_Register);
}

void igInterfaceManager_Register(void) {
    WindowInputLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igInterfaceManager_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igInterfaceManager_GetMetaObject,
        igInterfaceManager_className,
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

void igInterfaceManager_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)(g_igInterfaceManager_metaObject[0]);
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00487130[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_001460b0();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_00487138[0], &DAT_00487140[0], &DAT_00487148[0], temp_s2);
    *(int *)((char *)(g_igInterfaceManager_metaObject[0]) + 60) = (int)(thunk_FUN_00146470);
}

void thunk_FUN_00146470(void) {
    FUN_00146470();
}

