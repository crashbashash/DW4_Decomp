igMetaObject *g_beNDMWStatusCtrlD0_metaObject;
igMetaField *g_beNDMWStatusCtrlD0_isBankFolderMetaField;
igMetaField *g_beNDMWStatusCtrlD0_kindListMetaField;
igMetaField *g_beNDMWStatusCtrlD0_isAbTypeMetaField;
igMetaField *g_beNDMWStatusCtrlD0_isEquipDisableMetaField;
igMetaField *g_beNDMWStatusCtrlD0_isUnknownEnableMetaField;
igMetaField *g_beNDMWStatusCtrlD0_isUnknownDisableMetaField;
igMetaField *g_beNDMWStatusCtrlD0_isAutoCloseMetaField;
igMetaField *g_beNDMWStatusCtrlD0_decideListMetaField;

beNDMWStatusCtrlD0 *beNDMWStatusCtrlD0_Create(int allocator) {
    beNDMWStatusCtrlD0_EnsureRegistered();
    return (beNDMWStatusCtrlD0 *)igMetaObject_CreateInstance(g_beNDMWStatusCtrlD0_metaObject, (igMemoryPoolView *)allocator);
}

void *beNDMWStatusCtrlD0_GetMetaObject(void) {
    unsigned char b;
    if (g_beNDMWStatusCtrlD0_metaObject != 0) {
        b = (g_beNDMWStatusCtrlD0_metaObject->_validity & 4) != 0;
        if (b != 0) goto done;
    }
    beNDMWStatusCtrlD0_EnsureRegistered();
done:
    return g_beNDMWStatusCtrlD0_metaObject;
}

int beNDMWStatusCtrlD0_GetVTable(void) {
    beNDMWStatusCtrlD0 obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._subWindow = 0;
    obj._mother = 0;
    obj._textCloseTypeList = 0;
    obj._textCloseNameList = 0;
    obj._modelCloseInfoNameList = 0;
    obj._modelCloseRamNoList = 0;
    obj._modelCloseSeqNameList = 0;
    *(int **)&obj._vtable = &g_beNDMWStatusCtrlD0_vtable[0];
    obj._kindList = 0;
    obj._decideList = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem) + 916));
    *(int **)&obj._vtable = &g_beNDMWStatusCtrlD0_vtable[0];
    igSmartPointer_igBoolList_Destruct((igSmartPointer<igObject> *)&obj._decideList, -1);
    igSmartPointer_igIntList_Destruct((igSmartPointer<igObject> *)&obj._kindList, -1);
    beNDMWListCtrl_Destroy((beNDMWListCtrl *)&obj, 0);
    return vtable;
}

void beNDMWStatusCtrlD0_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusCtrlD0_Register);
}

static igMetaObjectCallback g_beNDMWStatusCtrlD0_callbackList[] = { igIntList_EnsureRegistered, igBoolList_EnsureRegistered, 0 };

CallbackArray *beNDMWStatusCtrlD0_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWStatusCtrlD0_metaObject,
        beNDMWListCtrl_Register,
        beNDMWListCtrl_GetPublishedMetaObject,
        beNDMWStatusCtrlD0_GetMetaObjectFunction,
        "beNDMWStatusCtrlD0",
        0x74, /* instance size */
        beNDMWStatusCtrlD0_GetVTable,
        beNDMWStatusCtrlD0_InitFields,
        0, /* extra callback item */
        g_beNDMWStatusCtrlD0_callbackList /* callback list */
    );
}

void beNDMWStatusCtrlD0_GetMetaObjectFunction(void)
{
    beNDMWStatusCtrlD0_GetMetaObject();
}

static FieldFactory g_beNDMWStatusCtrlD0_ctorTable[] = {
    igBoolMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beNDMWStatusCtrlD0_fieldTable[] = {
    "_isBankFolder",
    "_kindList",
    "_isAbType",
    "_isEquipDisable",
    "_isUnknownEnable",
    "_isUnknownDisable",
    "_isAutoClose",
    "_decideList",
};
static igMetaField **g_beNDMWStatusCtrlD0_fieldHandles[] = {
    &g_beNDMWStatusCtrlD0_isBankFolderMetaField,
    &g_beNDMWStatusCtrlD0_kindListMetaField,
    &g_beNDMWStatusCtrlD0_isAbTypeMetaField,
    &g_beNDMWStatusCtrlD0_isEquipDisableMetaField,
    &g_beNDMWStatusCtrlD0_isUnknownEnableMetaField,
    &g_beNDMWStatusCtrlD0_isUnknownDisableMetaField,
    &g_beNDMWStatusCtrlD0_isAutoCloseMetaField,
    &g_beNDMWStatusCtrlD0_decideListMetaField,
};
static int g_beNDMWStatusCtrlD0_fieldOffsets[] = {
    96,
    100,
    104,
    108,
    109,
    110,
    111,
    112,
};

void beNDMWStatusCtrlD0_InitFields(void) {
    int base;
    void *decideList;
    void *kindList;
    igMetaObject *meta;

    meta = g_beNDMWStatusCtrlD0_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNDMWStatusCtrlD0_ctorTable, 8);
    kindList = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)kindList)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)kindList)->_construct = 1;
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt(meta, base + 6), 1);
    decideList = (void *)(igMetaObject_GetFieldAt(meta, base + 7));
    ((igObjectRefMetaField *)decideList)->_metaObject = (int)igBoolList_GetOrCreateMetaObject();
    ((igRefMetaField *)decideList)->_construct = 1;
    igMetaObject_NameFields(meta, g_beNDMWStatusCtrlD0_fieldTable, g_beNDMWStatusCtrlD0_fieldHandles, g_beNDMWStatusCtrlD0_fieldOffsets, base);
}

