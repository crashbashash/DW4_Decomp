igMetaObject *g_beNDMWShopCtrlA1_metaObject;
igMetaField *g_beNDMWShopCtrlA1_cardInfoListMetaField;
igMetaField *g_beNDMWShopCtrlA1_cardRamNoListMetaField;

void beNDMWShopCtrlA1_Create(int allocator) {
    beNDMWShopCtrlA1_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWShopCtrlA1_metaObject, allocator);
}

igMetaObject *beNDMWShopCtrlA1_GetMetaObject(void) {
    if (g_beNDMWShopCtrlA1_metaObject == 0 || !isValid(g_beNDMWShopCtrlA1_metaObject)) beNDMWShopCtrlA1_EnsureRegistered();
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
    obj.vt = &g_beNDMWShopCtrlA1_vtable[0];
    obj.w21 = 0;
    obj.w22 = 0;
    t = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_beNDMWShopCtrlA1_vtable[0];
    igSmartPointer_igIntList_Destruct(&obj.w22, -1);
    igSmartPointer_igStringRefList_Destruct(&obj.w21, -1);
    beNDMWWindowCtrl_Destroy((beNDMWWindowCtrl *)&obj, (long long)0);
    return t;
}

void beNDMWShopCtrlA1_EnsureRegistered(void)
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
        beNDMWShopCtrlA1_GetMetaObjectFunction,
        "beNDMWShopCtrlA1",
        0x5c, /* instance size */
        beNDMWShopCtrlA1_GetVTable,
        beNDMWShopCtrlA1_InitFields,
        0, /* extra callback item */
        g_beNDMWShopCtrlA1_callbackList /* callback list */
    );
}

void beNDMWShopCtrlA1_GetMetaObjectFunction(void)
{
    beNDMWShopCtrlA1_GetMetaObject();
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
    int base;
    void *cardRamNoList;
    void *cardInfoList;
    igMetaObject *meta;

    meta = g_beNDMWShopCtrlA1_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNDMWShopCtrlA1_ctorTable, 2);
    cardInfoList = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)cardInfoList)->_metaObject = igStringRefList_GetOrCreateMetaObject();
    ((igRefMetaField *)cardInfoList)->_construct = 1;
    cardRamNoList = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)cardRamNoList)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)cardRamNoList)->_construct = 1;
    igMetaObject_NameFields(meta, g_beNDMWShopCtrlA1_fieldTable, g_beNDMWShopCtrlA1_fieldHandles, g_beNDMWShopCtrlA1_fieldOffsets, base);
}

