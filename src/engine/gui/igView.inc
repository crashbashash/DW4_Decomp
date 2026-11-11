igMetaObject *igView_GetMetaObject(void)
{
    igMetaObject *g = g_igView_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igView_EnsureRegistered();
    return g_igView_metaObject[0];
}

void igView_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igView_Register);
}

void igView_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igView_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igView_GetMetaObject,
        igView_className,
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

void igView_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0058c1c0[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004cfef8[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0044d5d0();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    igMetaObject_NameFields(temp_s0, &DAT_004cff00[0], &DAT_004cff08[0], &DAT_004cff10[0], temp_s2);
}

