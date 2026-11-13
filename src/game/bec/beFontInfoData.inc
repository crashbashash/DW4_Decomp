void *FUN_00361130(void) {
    igMetaObject *g = g_beFontInfoData_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00361210();
    }
    return g_beFontInfoData_metaObject[0];
}

int beFontInfoData_GetVTable(void) {
    struct F_361180 f;
    int temp_s0;

    igObject_InitHeader(&f);
    f.w[1] = 0;
    f.vt = &DAT_00535b70[0];
    f.w[3] = 0;
    f.w[9] = 0;
    temp_s0 = *(int *)((char *)&f + *(int *)((char *)(g_objectSystem[0]) + 916));
    f.vt = &DAT_00535b70[0];
    FUN_00130720(&f.w[9], -1);
    FUN_001d97f0(&f.w[3], -1);
    FUN_00344030((struct W_344030 *)&f, (short)0);
    return temp_s0;
}

void FUN_00361210(void)
{
    igMetaObject_RunStaticInit(beFontInfoData_Register);
}

void *beFontInfoData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beFontInfoData_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beFontInfoData_GetMetaObject,
        beFontInfoData_className,
        0x2c, /* instance size */
        beFontInfoData_GetVTable,
        beFontInfoData_InitFields,
        0, /* extra callback item */
        g_beFontInfoData_callbackList /* callback list */
    );
}

void beFontInfoData_GetMetaObject(void)
{
    FUN_00361130();
}

void beFontInfoData_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beFontInfoData_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beFontInfoData_ctorTable[0], 7);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_001a5d70();
    igMetaObject_NameFields(temp_s0, &g_beFontInfoData_fieldTable[0], &DAT_004c6c30[0], &DAT_004c6c50[0], temp_s2);
}

