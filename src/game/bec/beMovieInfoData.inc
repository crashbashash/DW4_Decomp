void *FUN_0034ec80(void) {
    igMetaObject *g = g_beMovieInfoData_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0034ed80();
    }
    return g_beMovieInfoData_metaObject[0];
}

int beMovieInfoData_GetVTable(void) {
    struct Obj_34ecd0 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.vt = &DAT_00538040[0];
    obj.w4 = 0;
    obj.w5 = 0;
    obj.w6 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_00538040[0];
    FUN_001d3650(&obj.w6, -1);
    FUN_00130720(&obj.w5, -1);
    FUN_00130720(&obj.w4, -1);
    FUN_00344030((struct W_344030 *)&obj, (short)0);
    return t;
}

void FUN_0034ed80(void)
{
    igMetaObject_RunStaticInit(beMovieInfoData_Register);
}

void *beMovieInfoData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beMovieInfoData_metaObject,
        beBaseInfoData_Register,
        beBaseInfoData_GetPublishedMetaObject,
        beMovieInfoData_GetMetaObject,
        beMovieInfoData_className,
        0x1c, /* instance size */
        beMovieInfoData_GetVTable,
        beMovieInfoData_InitFields,
        0, /* extra callback item */
        g_beMovieInfoData_callbackList /* callback list */
    );
}

void beMovieInfoData_GetMetaObject(void)
{
    FUN_0034ec80();
}

void beMovieInfoData_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beMovieInfoData_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beMovieInfoData_ctorTable[0], 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0019aee0();
    igMetaObject_NameFields(temp_s0, &g_beMovieInfoData_fieldTable[0], &DAT_004c4b50[0], &DAT_004c4b60[0], temp_s2);
}

int FUN_0034eed0(void) {
    if (DAT_00588780[0] == 0) {
        DAT_00588780[0] = igMetaEnum_Create(&text_Message[0], &DAT_004c4b70[0], &DAT_004c4b80[0], 4);
    }
    return DAT_00588780[0];
}

