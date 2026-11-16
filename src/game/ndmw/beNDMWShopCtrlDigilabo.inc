igMetaObject *g_beNDMWShopCtrlDigilabo_metaObject;
igMetaField *g_beNDMWShopCtrlDigilabo_playerNoListMetaField;
igMetaField *g_beNDMWShopCtrlDigilabo_digimonNoListMetaField;
igMetaField *g_beNDMWShopCtrlDigilabo_wpuNoListListMetaField;
igMetaField *g_beNDMWShopCtrlDigilabo_isDigimonChangeMetaField;
igMetaField *g_beNDMWShopCtrlDigilabo_isWeaponChangeMetaField;
igMetaField *g_beNDMWShopCtrlDigilabo_topMenuMetaField;
igMetaField *g_beNDMWShopCtrlDigilabo_isDemoRunMetaField;

void beNDMWShopCtrlDigilabo_Create(int allocator) {
    beNDMWShopCtrlDigilabo_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWShopCtrlDigilabo_metaObject, allocator);
}

igMetaObject *beNDMWShopCtrlDigilabo_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWShopCtrlDigilabo_metaObject;
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        beNDMWShopCtrlDigilabo_EnsureRegistered();
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
    obj.vt = &g_beNDMWShopCtrlDigilabo_vtable[0];
    obj.w21 = 0;
    obj.w22 = 0;
    obj.w23 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_beNDMWShopCtrlDigilabo_vtable[0];
    FUN_0019d200(&obj.w23, -1);
    igSmartPointer_igIntList_Destruct(&obj.w22, -1);
    igSmartPointer_igIntList_Destruct(&obj.w21, -1);
    beNDMWWindowCtrl_Destroy((beNDMWWindowCtrl *)&obj, (long long)0);
    return t;
}

void beNDMWShopCtrlDigilabo_EnsureRegistered(void)
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
        beNDMWShopCtrlDigilabo_GetMetaObjectFunction,
        "beNDMWShopCtrlDigilabo",
        0x6c, /* instance size */
        beNDMWShopCtrlDigilabo_GetVTable,
        beNDMWShopCtrlDigilabo_InitFields,
        0, /* extra callback item */
        g_beNDMWShopCtrlDigilabo_callbackList /* callback list */
    );
}

void beNDMWShopCtrlDigilabo_GetMetaObjectFunction(void)
{
    beNDMWShopCtrlDigilabo_GetMetaObject();
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
    int base;
    void *wpuNoListList;
    void *digimonNoList;
    void *playerNoList;
    igMetaObject *meta;

    meta = g_beNDMWShopCtrlDigilabo_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNDMWShopCtrlDigilabo_ctorTable, 7);
    playerNoList = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)playerNoList)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)playerNoList)->_construct = 1;
    digimonNoList = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)digimonNoList)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)digimonNoList)->_construct = 1;
    wpuNoListList = (void *)(igMetaObject_GetFieldAt(meta, base + 2));
    ((igObjectRefMetaField *)wpuNoListList)->_metaObject = igIntListList_GetOrCreateMetaObject();
    ((igRefMetaField *)wpuNoListList)->_construct = 1;
    igMetaObject_NameFields(meta, g_beNDMWShopCtrlDigilabo_fieldTable, g_beNDMWShopCtrlDigilabo_fieldHandles, g_beNDMWShopCtrlDigilabo_fieldOffsets, base);
}

