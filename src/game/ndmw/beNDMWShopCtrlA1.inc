igMetaObject *g_beNDMWShopCtrlA1_metaObject;
igMetaField *g_beNDMWShopCtrlA1_cardInfoListMetaField;
igMetaField *g_beNDMWShopCtrlA1_cardRamNoListMetaField;

void beNDMWShopCtrlA1_Create(int arg0) {
    FUN_003b7d30();
    igMetaObject_CreateInstance(g_beNDMWShopCtrlA1_metaObject, arg0);
}

igMetaObject *FUN_003b7c40(void) {
    if (g_beNDMWShopCtrlA1_metaObject == 0 || !isValid(g_beNDMWShopCtrlA1_metaObject)) FUN_003b7d30();
    return g_beNDMWShopCtrlA1_metaObject;
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
    igSmartPointer_igIntList_Destruct(&obj.w22, -1);
    igSmartPointer_igStringRefList_Destruct(&obj.w21, -1);
    beNDMWWindowCtrl_Destroy((beNDMWWindowCtrl *)&obj, (long long)0);
    return t;
}

void FUN_003b7d30(void)
{
    igMetaObject_RunStaticInit(beNDMWShopCtrlA1_Register);
}

static igMetaObjectCallback g_beNDMWShopCtrlA1_callbackList[] = { igStringRefList_EnsureRegistered, igIntList_EnsureRegistered, 0 };

void *beNDMWShopCtrlA1_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWShopCtrlA1_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWShopCtrlA1_GetMetaObject,
        "beNDMWShopCtrlA1",
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

static FieldFactory g_beNDMWShopCtrlA1_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beNDMWShopCtrlA1_fieldTable[] = {
    "_cardInfoList",
    "_cardRamNoList",
};
static igMetaField **g_beNDMWShopCtrlA1_fieldHandles[] = {
    &g_beNDMWShopCtrlA1_cardInfoListMetaField,
    &g_beNDMWShopCtrlA1_cardRamNoListMetaField,
};
static int g_beNDMWShopCtrlA1_fieldOffsets[] = {
    84,
    88,
};

void beNDMWShopCtrlA1_InitFields(void) {
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_beNDMWShopCtrlA1_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beNDMWShopCtrlA1_ctorTable, 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = igStringRefList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    igMetaObject_NameFields(temp_s0, g_beNDMWShopCtrlA1_fieldTable, g_beNDMWShopCtrlA1_fieldHandles, g_beNDMWShopCtrlA1_fieldOffsets, temp_s2);
}

