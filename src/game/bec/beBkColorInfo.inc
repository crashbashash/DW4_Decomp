void *FUN_00369be0(void) {
    igMetaObject *g = g_beBkColorInfo_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00369ca0();
    }
    return g_beBkColorInfo_metaObject[0];
}

int beBkColorInfo_GetVTable(void) {
    struct Obj_369c30 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w2 = 0;
    obj.w5 = 0;
    obj.w6 = 0;
    obj.vt = &DAT_00534900[0];
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_00534900[0];
    FUN_0033ec80((struct S_33ec80 *)&obj, (short)0);
    return t;
}

void FUN_00369ca0(void)
{
    igMetaObject_RunStaticInit(beBkColorInfo_Register);
}

void *beBkColorInfo_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beBkColorInfo_metaObject,
        beBaseInfo_Register,
        beBaseInfo_GetPublishedMetaObject,
        beBkColorInfo_GetMetaObject,
        beBkColorInfo_className,
        0x2c, /* instance size */
        beBkColorInfo_GetVTable,
        beBkColorInfo_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beBkColorInfo_GetMetaObject(void)
{
    FUN_00369be0();
}

void beBkColorInfo_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beBkColorInfo_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c7b58[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_004c7b60[0], &DAT_004c7b68[0], &DAT_004c7b70[0], temp_s1);
}

