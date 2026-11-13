void beNDMWShopCtrlA1_Create(int arg0) {
    FUN_003b7d30();
    igMetaObject_CreateInstance(*(int *)0x58AD88, arg0);
}

igMetaObject *FUN_003b7c40(void) {
    if (g_beNDMWShopCtrlA1_metaObject[0] == 0 || !isValid(g_beNDMWShopCtrlA1_metaObject[0])) FUN_003b7d30();
    return g_beNDMWShopCtrlA1_metaObject[0];
}

int beNDMWShopCtrlA1_GetVTable(void) {
    struct Obj_3b7c90 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w13 = 0;
    obj.w14 = 0;
    obj.w15 = 0;
    obj.w16 = 0;
    obj.w17 = 0;
    obj.w18 = 0;
    obj.w19 = 0;
    obj.vt = &DAT_0053fc10[0];
    obj.w21 = 0;
    obj.w22 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_0053fc10[0];
    ObjectRef_Destruct_00150eb0(&obj.w22, -1);
    ObjectRef_Destruct_001c6460(&obj.w21, -1);
    beNDMWWindowCtrl_Destroy((beNDMWWindowCtrl *)&obj, (long long)0);
    return t;
}

void FUN_003b7d30(void)
{
    igMetaObject_RunStaticInit(beNDMWShopCtrlA1_Register);
}

void *beNDMWShopCtrlA1_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWShopCtrlA1_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWShopCtrlA1_GetMetaObject,
        beNDMWShopCtrlA1_className,
        0x5c, /* instance size */
        beNDMWShopCtrlA1_GetVTable,
        beNDMWShopCtrlA1_InitFields,
        0, /* extra callback item */
        g_beNDMWShopCtrlA1_callbackList /* callback list */
    );
}

void beNDMWShopCtrlA1_GetMetaObject(void)
{
    FUN_003b7c40();
}

void beNDMWShopCtrlA1_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beNDMWShopCtrlA1_metaObject[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beNDMWShopCtrlA1_ctorTable[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_002b9120();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &g_beNDMWShopCtrlA1_fieldTable[0], &DAT_004c9b30[0], &DAT_004c9b38[0], temp_s2);
}

