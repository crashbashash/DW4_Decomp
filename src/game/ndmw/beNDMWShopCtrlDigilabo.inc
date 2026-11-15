igMetaObject *g_beNDMWShopCtrlDigilabo_metaObject;
igMetaField *g_beNDMWShopCtrlDigilabo_playerNoListMetaField;
igMetaField *g_beNDMWShopCtrlDigilabo_digimonNoListMetaField;
igMetaField *g_beNDMWShopCtrlDigilabo_wpuNoListListMetaField;
igMetaField *g_beNDMWShopCtrlDigilabo_isDigimonChangeMetaField;
igMetaField *g_beNDMWShopCtrlDigilabo_isWeaponChangeMetaField;
igMetaField *g_beNDMWShopCtrlDigilabo_topMenuMetaField;
igMetaField *g_beNDMWShopCtrlDigilabo_isDemoRunMetaField;

void beNDMWShopCtrlDigilabo_Create(int arg0) {
    FUN_003b78a0();
    igMetaObject_CreateInstance(g_beNDMWShopCtrlDigilabo_metaObject, arg0);
}

igMetaObject *FUN_003b7790(void) {
    igMetaObject *g = g_beNDMWShopCtrlDigilabo_metaObject;
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        FUN_003b78a0();
    return g_beNDMWShopCtrlDigilabo_metaObject;
}

int beNDMWShopCtrlDigilabo_GetVTable(void) {
    struct Obj_3b77e0 obj;
    int t;

    igObject_InitHeader(&obj);
    obj.w13 = 0;
    obj.w14 = 0;
    obj.w15 = 0;
    obj.w16 = 0;
    obj.w17 = 0;
    obj.w18 = 0;
    obj.w19 = 0;
    obj.vt = &DAT_0053fae0[0];
    obj.w21 = 0;
    obj.w22 = 0;
    obj.w23 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_0053fae0[0];
    FUN_0019d200(&obj.w23, -1);
    igSmartPointer_igIntList_Destruct(&obj.w22, -1);
    igSmartPointer_igIntList_Destruct(&obj.w21, -1);
    beNDMWWindowCtrl_Destroy((beNDMWWindowCtrl *)&obj, (long long)0);
    return t;
}

void FUN_003b78a0(void)
{
    igMetaObject_RunStaticInit(beNDMWShopCtrlDigilabo_Register);
}

static igMetaObjectCallback g_beNDMWShopCtrlDigilabo_callbackList[] = { igIntList_EnsureRegistered, igIntListList_EnsureRegistered, 0 };

void *beNDMWShopCtrlDigilabo_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWShopCtrlDigilabo_metaObject,
        beNDMWWindowCtrl_Register,
        beNDMWWindowCtrl_GetPublishedMetaObject,
        beNDMWShopCtrlDigilabo_GetMetaObject,
        "beNDMWShopCtrlDigilabo",
        0x6c, /* instance size */
        beNDMWShopCtrlDigilabo_GetVTable,
        beNDMWShopCtrlDigilabo_InitFields,
        0, /* extra callback item */
        g_beNDMWShopCtrlDigilabo_callbackList /* callback list */
    );
}

void beNDMWShopCtrlDigilabo_GetMetaObject(void)
{
    FUN_003b7790();
}

static FieldFactory g_beNDMWShopCtrlDigilabo_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igIntMetaField_Create,
    igBoolMetaField_Create,
};
static const char *g_beNDMWShopCtrlDigilabo_fieldTable[] = {
    "_playerNoList",
    "_digimonNoList",
    "_wpuNoListList",
    "_isDigimonChange",
    "_isWeaponChange",
    "_topMenu",
    "_isDemoRun",
};
static igMetaField **g_beNDMWShopCtrlDigilabo_fieldHandles[] = {
    &g_beNDMWShopCtrlDigilabo_playerNoListMetaField,
    &g_beNDMWShopCtrlDigilabo_digimonNoListMetaField,
    &g_beNDMWShopCtrlDigilabo_wpuNoListListMetaField,
    &g_beNDMWShopCtrlDigilabo_isDigimonChangeMetaField,
    &g_beNDMWShopCtrlDigilabo_isWeaponChangeMetaField,
    &g_beNDMWShopCtrlDigilabo_topMenuMetaField,
    &g_beNDMWShopCtrlDigilabo_isDemoRunMetaField,
};
static int g_beNDMWShopCtrlDigilabo_fieldOffsets[] = {
    84,
    88,
    92,
    96,
    97,
    100,
    104,
};

void beNDMWShopCtrlDigilabo_InitFields(void) {
    int temp_s2;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_beNDMWShopCtrlDigilabo_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beNDMWShopCtrlDigilabo_ctorTable, 7);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1)->_construct = 1;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = igIntListList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1_3)->_construct = 1;
    igMetaObject_NameFields(temp_s0, g_beNDMWShopCtrlDigilabo_fieldTable, g_beNDMWShopCtrlDigilabo_fieldHandles, g_beNDMWShopCtrlDigilabo_fieldOffsets, temp_s2);
}

