void FUN_003b6940(int arg0) {
    FUN_003b6a60();
    igMetaObject_CreateInstance(*(int *)0x58ACB8, arg0);
}

void *FUN_003b6980(void) {
    igMetaObject *g = g_beNDMWShopCtrlXdataChip_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003b6a60();
    }
    return g_beNDMWShopCtrlXdataChip_metaObject[0];
}

int beNDMWShopCtrlXdataChip_GetVTable(void) {
    struct Obj_3b69d0 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.w[12] = 0;
    obj.w[13] = 0;
    obj.w[14] = 0;
    obj.w[15] = 0;
    obj.w[16] = 0;
    obj.w[17] = 0;
    obj.w[18] = 0;
    obj.vt = &DAT_0053f870[0];
    obj.w[23] = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_0053f870[0];
    FUN_003b6090((void **)(&obj.w[23]), (long long)(-1));
    FUN_003b6770((int **)&obj, (long long)0);
    return r;
}

void FUN_003b6a60(void)
{
    igMetaObject_RunStaticInit(beNDMWShopCtrlXdataChip_Register);
}

void *beNDMWShopCtrlXdataChip_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWShopCtrlXdataChip_metaObject,
        beNDMWListCtrl_Register,
        beNDMWListCtrl_GetPublishedMetaObject,
        beNDMWShopCtrlXdataChip_GetMetaObject,
        beNDMWShopCtrlXdataChip_className,
        0x64, /* instance size */
        beNDMWShopCtrlXdataChip_GetVTable,
        beNDMWShopCtrlXdataChip_InitFields,
        0, /* extra callback item */
        g_beNDMWShopCtrlXdataChip_callbackList /* callback list */
    );
}

void beNDMWShopCtrlXdataChip_GetMetaObject(void)
{
    FUN_003b6980();
}

void beNDMWShopCtrlXdataChip_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beNDMWShopCtrlXdataChip_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c9968[0], 1);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_003c9130();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004c9970[0], &DAT_004c9978[0], &DAT_004c9980[0], temp_s2);
}

