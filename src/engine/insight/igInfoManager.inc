igMetaObject *igInfoManager_GetMetaObject(void)
{
    igMetaObject *g = g_igInfoManager_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00233910();
    return g_igInfoManager_metaObject[0];
}

void FUN_00233910(void)
{
    igMetaObject_RunStaticInit(igInfoManager_Register);
}

void igInfoManager_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igInfoManager_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        thunk_igInfoManager_GetMetaObject,
        igInfoManager_className,
        0x10, /* instance size */
        0,
        &igInfoManager_InitFields,
        0, /* extra callback item */
        g_igInfoManager_callbackList /* callback list */
    );
}

void thunk_igInfoManager_GetMetaObject(void) {
    igInfoManager_GetMetaObject();
}

void igInfoManager_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)DAT_0056dc38[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_00498250[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00232840();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    igMetaObject_NameFields(temp_s0, &DAT_00498258[0], &DAT_00498260[0], &DAT_00498268[0], temp_s2);
}

