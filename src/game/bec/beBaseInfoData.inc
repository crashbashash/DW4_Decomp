void *FUN_0036b050(void) {
    struct G *g = DAT_00589e08[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0036b0a0();
    }
    return DAT_00589e08[0];
}

void FUN_0036b0a0(void)
{
    igMetaObject_RunStaticInit(beBaseInfoData_Register);
}

void *beBaseInfoData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        g_beBaseInfoData_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beBaseInfoData_GetMetaObject,
        beBaseInfoData_className,
        0x10, /* instance size */
        0,
        beBaseInfoData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beBaseInfoData_GetMetaObject(void)
{
    FUN_0036b050();
}

void beBaseInfoData_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_00589e08)[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c7d80[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_004c7d88[0], &DAT_004c7d90[0], &DAT_004c7d98[0], temp_s1);
}

