igMetaObject *igOptBase_GetMetaObject(void)
{
    igMetaObject *g = g_igOptBase_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00225f80();
    return g_igOptBase_metaObject[0];
}

void FUN_00225f80(void)
{
    igMetaObject_RunStaticInit(igOptBase_Register);
}

void igOptBase_Register(void) {
    BaseLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igOptBase_metaObject,
        igBase_Register,
        igBase_GetPublishedMetaObject,
        thunk_igOptBase_GetMetaObject,
        igOptBase_className,
        0x28, /* instance size */
        0,
        &igOptBase_InitFields,
        0, /* extra callback item */
        g_igOptBase_callbackList /* callback list */
    );
}

void thunk_igOptBase_GetMetaObject(void) {
    igOptBase_GetMetaObject();
}

int FUN_00226010(void) {
    return DAT_0056da60[0];
}

void igOptBase_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0056d890[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00497c10[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002bb030();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_00225dc0();
    igMetaObject_NameFields(temp_s0, &DAT_00497c18[0], &DAT_00497c20[0], &DAT_00497c28[0], temp_s2);
}

