void *FUN_00343b80(void) {
    struct G *g = DAT_00587e28[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00343bd0();
    }
    return DAT_00587e28[0];
}

void FUN_00343bd0(void)
{
    igMetaObject_RunStaticInit(beBinDataObject_Register);
}

void *beBinDataObject_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        g_beBinDataObject_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beBinDataObject_GetMetaObject,
        beBinDataObject_className,
        0x18, /* instance size */
        0,
        beBinDataObject_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beBinDataObject_GetMetaObject(void)
{
    FUN_00343b80();
}

int FUN_00343c80(void) {
    return ((int *)DAT_00589e08)[0];
}

void beBinDataObject_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_00587e28)[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c37c0[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igMemoryRefMetaField *)temp_s1)->_memType = FUN_002cc2c0();
    igMetaObject_NameFields(temp_s0, &DAT_004c37c8[0], &DAT_004c37d0[0], &DAT_004c37d8[0], temp_s2);
}

