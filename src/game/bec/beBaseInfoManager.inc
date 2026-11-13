igMetaObject *FUN_0036a8d0(void) {
    if (g_beBaseInfoManager_metaObject[0] == 0) {
        g_beBaseInfoManager_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beBaseInfoManager_metaObject[0];
}

igMetaObject *FUN_0036a920(void) {
    igMetaObject *g = g_beBaseInfoManager_metaObject[0];
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        FUN_0036a970();
    return g_beBaseInfoManager_metaObject[0];
}

void FUN_0036a970(void)
{
    igMetaObject_RunStaticInit(beBaseInfoManager_Register);
}

void *beBaseInfoManager_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        g_beBaseInfoManager_metaObject,
        igInfoManager_Register,
        igInfoManager_GetPublishedMetaObject,
        beBaseInfoManager_GetMetaObject,
        beBaseInfoManager_className,
        0x20, /* instance size */
        0,
        beBaseInfoManager_InitFields,
        0, /* extra callback item */
        g_beBaseInfoManager_callbackList /* callback list */
    );
}

void beBaseInfoManager_GetMetaObject(void)
{
    FUN_0036a920();
}

void beBaseInfoManager_InitFields(void) {
    int temp_s2;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beBaseInfoManager_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beBaseInfoManager_ctorTable[0], 4);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_00342ce0();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)FUN_00357910();
    ((igObjectRefMetaField *)temp_s1_2)->_refCounted = 0;
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = (int)FUN_0036aaf0();
    ((igRefMetaField *)temp_s1_3)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &g_beBaseInfoManager_fieldTable[0], &DAT_004c7d20[0], &DAT_004c7d30[0], temp_s2);
}

