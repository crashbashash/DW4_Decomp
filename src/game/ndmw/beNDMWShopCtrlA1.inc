igMetaObject *g_beNDMWShopCtrlA1_metaObject;
igMetaField *g_beNDMWShopCtrlA1_cardInfoListMetaField;
igMetaField *g_beNDMWShopCtrlA1_cardRamNoListMetaField;

beNDMWShopCtrlA1 *beNDMWShopCtrlA1_Create(int allocator) {
    beNDMWShopCtrlA1_EnsureRegistered();
    return (beNDMWShopCtrlA1 *)igMetaObject_CreateInstance(g_beNDMWShopCtrlA1_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beNDMWShopCtrlA1_GetMetaObject(void) {
    if (g_beNDMWShopCtrlA1_metaObject == 0 || !isValid(g_beNDMWShopCtrlA1_metaObject)) beNDMWShopCtrlA1_EnsureRegistered();
    return g_beNDMWShopCtrlA1_metaObject;
}

int beNDMWShopCtrlA1_GetVTable(void) {
    beNDMWShopCtrlA1 obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._subWindow = 0;
    obj._mother = 0;
    obj._textCloseTypeList = 0;
    obj._textCloseNameList = 0;
    obj._modelCloseInfoNameList = 0;
    obj._modelCloseRamNoList = 0;
    obj._modelCloseSeqNameList = 0;
    *(int **)&obj._vtable = &g_beNDMWShopCtrlA1_vtable[0];
    obj._cardInfoList = 0;
    obj._cardRamNoList = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    *(int **)&obj._vtable = &g_beNDMWShopCtrlA1_vtable[0];
    igSmartPointer_igIntList_Destruct((igSmartPointer<igObject> *)&obj._cardRamNoList, -1);
    igSmartPointer_igStringRefList_Destruct((igSmartPointer<igObject> *)&obj._cardInfoList, -1);
    beNDMWWindowCtrl_Destroy((beNDMWWindowCtrl *)&obj, (long long)0);
    return vtable;
}

void beNDMWShopCtrlA1_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWShopCtrlA1_Register);
}

static igMetaObjectCallback g_beNDMWShopCtrlA1_callbackList[] = { igStringRefList_EnsureRegistered, Gap::Core::igIntList::arkRegister, 0 };

CallbackArray *beNDMWShopCtrlA1_Register(void) {
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
    ((igObjectRefMetaField *)cardInfoList)->_metaObject = (int)igStringRefList_GetOrCreateMetaObject();
    ((igRefMetaField *)cardInfoList)->_construct = 1;
    cardRamNoList = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)cardRamNoList)->_metaObject = (int)Gap::Core::igIntList::getClassTypeLazy();
    ((igRefMetaField *)cardRamNoList)->_construct = 1;
    igMetaObject_NameFields(meta, g_beNDMWShopCtrlA1_fieldTable, g_beNDMWShopCtrlA1_fieldHandles, g_beNDMWShopCtrlA1_fieldOffsets, base);
}

