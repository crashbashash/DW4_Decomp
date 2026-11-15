igMetaObject *g_beNDMWShopCtrlSales_metaObject;
igMetaField *g_beNDMWShopCtrlSales_salesItemListMetaField;
igMetaField *g_beNDMWShopCtrlSales_decideListMetaField;

void beNDMWShopCtrlSales_Create(int arg0) {
    FUN_003b6cf0();
    igMetaObject_CreateInstance(g_beNDMWShopCtrlSales_metaObject, arg0);
}

void *FUN_003b6c00(void) {
    igMetaObject *g = g_beNDMWShopCtrlSales_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003b6cf0();
    }
    return g_beNDMWShopCtrlSales_metaObject;
}

int beNDMWShopCtrlSales_GetVTable(void) {
    struct Obj_3b6c50 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w13 = 0;
    obj.w14 = 0;
    obj.w15 = 0;
    obj.w16 = 0;
    obj.w17 = 0;
    obj.w18 = 0;
    obj.w19 = 0;
    obj.vt = &DAT_0053f8e0[0];
    obj.w24 = 0;
    obj.w25 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_0053f8e0[0];
    FUN_00226990(&obj.w25, -1);
    FUN_003b6090((void **)&obj.w24, (long long)(-1));
    FUN_003b6770((int **)&obj, (long long)0);
    return t;
}

void FUN_003b6cf0(void)
{
    igMetaObject_RunStaticInit(beNDMWShopCtrlSales_Register);
}

static igMetaObjectCallback g_beNDMWShopCtrlSales_callbackList[] = { FUN_003c9210, igBoolList_EnsureRegistered, 0 };

void *beNDMWShopCtrlSales_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWShopCtrlSales_metaObject,
        beNDMWListCtrl_Register,
        beNDMWListCtrl_GetPublishedMetaObject,
        beNDMWShopCtrlSales_GetMetaObject,
        "beNDMWShopCtrlSales",
        0x68, /* instance size */
        beNDMWShopCtrlSales_GetVTable,
        beNDMWShopCtrlSales_InitFields,
        0, /* extra callback item */
        g_beNDMWShopCtrlSales_callbackList /* callback list */
    );
}

void beNDMWShopCtrlSales_GetMetaObject(void)
{
    FUN_003b6c00();
}

static FieldFactory g_beNDMWShopCtrlSales_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beNDMWShopCtrlSales_fieldTable[] = {
    "_salesItemList",
    "_decideList",
};
static igMetaField **g_beNDMWShopCtrlSales_fieldHandles[] = {
    &g_beNDMWShopCtrlSales_salesItemListMetaField,
    &g_beNDMWShopCtrlSales_decideListMetaField,
};
static int g_beNDMWShopCtrlSales_fieldOffsets[] = {
    96,
    100,
};

void beNDMWShopCtrlSales_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_beNDMWShopCtrlSales_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beNDMWShopCtrlSales_ctorTable, 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = (int)FUN_003c9130();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = igBoolList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    igMetaObject_NameFields(temp_s0, g_beNDMWShopCtrlSales_fieldTable, g_beNDMWShopCtrlSales_fieldHandles, g_beNDMWShopCtrlSales_fieldOffsets, temp_s2);
}

