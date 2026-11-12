int FUN_0036a8d0(void) {
    if (((int *)DAT_00589db8)[0] == 0) {
        ((int *)DAT_00589db8)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_00589db8)[0];
}

G_36a920 *FUN_0036a920(void) {
    G_36a920 *g = DAT_00589db8[0];
    int t;
    if (!g || !(t = (g->f & 4) != 0))
        FUN_0036a970();
    return DAT_00589db8[0];
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

    temp_s0 = (void *)((int *)DAT_00589db8)[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c7d00[0], 4);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00342ce0();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_00357910();
    ((igObjectRefMetaField *)temp_s1_2)->_refCounted = 0;
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = FUN_0036aaf0();
    ((igRefMetaField *)temp_s1_3)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004c7d10[0], &DAT_004c7d20[0], &DAT_004c7d30[0], temp_s2);
}

