igMetaObject *FUN_0036ac80(void) {
    if (g_beBaseInfo_metaObject[0] == 0) {
        g_beBaseInfo_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_beBaseInfo_metaObject[0];
}

igMetaObject *FUN_0036acd0(void) {
    if (g_beBaseInfo_metaObject[0] == 0 || !isValid(g_beBaseInfo_metaObject[0])) FUN_0036ad20();
    return g_beBaseInfo_metaObject[0];
}

void FUN_0036ad20(void)
{
    igMetaObject_RunStaticInit(beBaseInfo_Register);
}

void *beBaseInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        g_beBaseInfo_metaObject,
        igInfo_Register,
        igInfo_GetPublishedMetaObject,
        beBaseInfo_GetMetaObject,
        beBaseInfo_className,
        0x1c, /* instance size */
        0,
        beBaseInfo_InitFields,
        0, /* extra callback item */
        g_beBaseInfo_callbackList /* callback list */
    );
}

void beBaseInfo_GetMetaObject(void)
{
    FUN_0036acd0();
}

void beBaseInfo_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beBaseInfo_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c7d58[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_0036aec0();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = (int)beBaseInfoRamList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004c7d60[0], &DAT_004c7d68[0], &DAT_004c7d70[0], temp_s2);
}

