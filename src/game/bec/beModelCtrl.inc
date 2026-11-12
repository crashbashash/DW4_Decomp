SFUN_00356b10 *FUN_00356b10(void) {
    if (DAT_00588e58[0] == 0 || !DAT_00588e58[0]->ok()) FUN_00356b60();
    return DAT_00588e58[0];
}

void FUN_00356b60(void)
{
    igMetaObject_RunStaticInit(beModelCtrl_Register);
}

void *beModelCtrl_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        g_beModelCtrl_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beModelCtrl_GetMetaObject,
        beModelCtrl_className,
        0x2c, /* instance size */
        0,
        beModelCtrl_InitFields,
        0, /* extra callback item */
        g_beModelCtrl_callbackList /* callback list */
    );
}

void beModelCtrl_GetMetaObject(void)
{
    FUN_00356b10();
}

void beModelCtrl_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_00588e58)[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c5a18[0], 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0035b770();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_003429b0();
    ((igObjectRefMetaField *)temp_s1_2)->_refCounted = 0;
    igMetaObject_NameFields(temp_s0, &DAT_004c5a28[0], &DAT_004c5a38[0], &DAT_004c5a48[0], temp_s2);
}

