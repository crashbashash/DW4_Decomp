igMetaObject *g_beNDMWStatusCtrlD0_metaObject;
igMetaField *g_beNDMWStatusCtrlD0_isBankFolderMetaField;
igMetaField *g_beNDMWStatusCtrlD0_kindListMetaField;
igMetaField *g_beNDMWStatusCtrlD0_isAbTypeMetaField;
igMetaField *g_beNDMWStatusCtrlD0_isEquipDisableMetaField;
igMetaField *g_beNDMWStatusCtrlD0_isUnknownEnableMetaField;
igMetaField *g_beNDMWStatusCtrlD0_isUnknownDisableMetaField;
igMetaField *g_beNDMWStatusCtrlD0_isAutoCloseMetaField;
igMetaField *g_beNDMWStatusCtrlD0_decideListMetaField;

void beNDMWStatusCtrlD0_Create(int allocator) {
    beNDMWStatusCtrlD0_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWStatusCtrlD0_metaObject, allocator);
}

void *beNDMWStatusCtrlD0_GetMetaObject(void) {
    unsigned char b;
    if (g_beNDMWStatusCtrlD0_metaObject != 0) {
        b = (*(int *)((char *)(g_beNDMWStatusCtrlD0_metaObject) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    beNDMWStatusCtrlD0_EnsureRegistered();
done:
    return g_beNDMWStatusCtrlD0_metaObject;
}

int beNDMWStatusCtrlD0_GetVTable(void) {
    struct Obj_3bafa0 obj;
    int temp_s1;

    igObject_InitHeader(&obj);
    obj.f34 = 0;
    obj.f38 = 0;
    obj.f3C = 0;
    obj.f40 = 0;
    obj.f44 = 0;
    obj.f48 = 0;
    obj.f4C = 0;
    obj.vt = (&g_beNDMWStatusCtrlD0_vtable[0]);
    obj.f64 = 0;
    obj.f70 = 0;
    temp_s1 = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = (&g_beNDMWStatusCtrlD0_vtable[0]);
    FUN_00226990(&obj.f70, -1);
    igSmartPointer_igIntList_Destruct(&obj.f64, -1);
    FUN_003b6770((int **)&obj, (long long)0);
    return temp_s1;
}

void beNDMWStatusCtrlD0_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusCtrlD0_Register);
}

static igMetaObjectCallback g_beNDMWStatusCtrlD0_callbackList[] = { igIntList_EnsureRegistered, igBoolList_EnsureRegistered, 0 };

void *beNDMWStatusCtrlD0_Register(void) {
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
    ((igObjectRefMetaField *)decideList)->_metaObject = igBoolList_GetOrCreateMetaObject();
    ((igRefMetaField *)decideList)->_construct = 1;
    igMetaObject_NameFields(meta, g_beNDMWStatusCtrlD0_fieldTable, g_beNDMWStatusCtrlD0_fieldHandles, g_beNDMWStatusCtrlD0_fieldOffsets, base);
}

