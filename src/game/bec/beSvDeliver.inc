igMetaObject *g_beSvDeliver_metaObject;
igMetaField *g_beSvDeliver_actConnectMetaField;
igMetaField *g_beSvDeliver_targetConnectMetaField;
igMetaField *g_beSvDeliver_saveVerMetaField;
igMetaField *g_beSvDeliver_resultMetaField;
igMetaField *g_beSvDeliver_operateMetaField;
igMetaField *g_beSvDeliver_memCapaMetaField;
igMetaField *g_beSvDeliver_fileCapaMetaField;
igMetaField *g_beSvDeliver_useMtapMetaField;
igMetaField *g_beSvDeliver_chgUseMtapMetaField;
igMetaField *g_beSvDeliver_isMemCapaOKMetaField;
igMetaField *g_beSvDeliver_isfileCapaOKMetaField;
igMetaField *g_beSvDeliver_isEndOperatMetaField;
igMetaField *g_beSvDeliver_freeSizeListMetaField;
igMetaField *g_beSvDeliver_freeFileListMetaField;
igMetaField *g_beSvDeliver_formatListMetaField;
igMetaField *g_beSvDeliver_totalSizeListMetaField;
igMetaField *g_beSvDeliver_gameDataMetaField;
igMetaField *g_beSvDeliver_platformDataMetaField;

igMetaObject *beSvDeliver_GetOrCreateMetaObject(void) {
    if (g_beSvDeliver_metaObject == 0) {
        g_beSvDeliver_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beSvDeliver_metaObject;
}

igMetaObject *beSvDeliver_GetMetaObject(void) {
    if (g_beSvDeliver_metaObject == 0 || !isValid(g_beSvDeliver_metaObject)) beSvDeliver_EnsureRegistered();
    return g_beSvDeliver_metaObject;
}

int beSvDeliver_GetVTable(void) {
    beSvDeliver obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beSvDeliver_vtable[0];
    obj._actConnect = 0;
    obj._freeSizeList = 0;
    obj._freeFileList = 0;
    obj._formatList = 0;
    obj._totalSizeList = 0;
    obj._platformData = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beSvDeliver_vtable[0];
    igSmartPointer_beSvPlatBaseData_Destruct((igSmartPointer<igObject> *)(&obj._platformData), (long long)(-1));
    igSmartPointer_igIntList_Destruct((igSmartPointer<igObject> *)&obj._totalSizeList, -1);
    igSmartPointer_igIntList_Destruct((igSmartPointer<igObject> *)&obj._formatList, -1);
    igSmartPointer_igIntList_Destruct((igSmartPointer<igObject> *)&obj._freeFileList, -1);
    igSmartPointer_igIntList_Destruct((igSmartPointer<igObject> *)&obj._freeSizeList, -1);
    igSmartPointer_igIntList_Destruct((igSmartPointer<igObject> *)&obj._actConnect, -1);
    return vtable;
}

void beSvDeliver_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSvDeliver_Register);
}

static igMetaObjectCallback g_beSvDeliver_callbackList[] = { Gap::Core::igIntList::arkRegister, beSaveDataDeliver_EnsureRegistered, beSvPlatBaseData_EnsureRegistered, 0 };

CallbackArray *beSvDeliver_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSvDeliver_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        beSvDeliver_GetMetaObjectFunction,
        "beSvDeliver",
        0x44, /* instance size */
        beSvDeliver_GetVTable,
        beSvDeliver_InitFields,
        0, /* extra callback item */
        g_beSvDeliver_callbackList /* callback list */
    );
}

void beSvDeliver_GetMetaObjectFunction(void)
{
    beSvDeliver_GetMetaObject();
}

static FieldFactory g_beSvDeliver_ctorTable[] = {
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igCharMetaField_Create,
    igCharMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beSvDeliver_fieldTable[] = {
    "_actConnect",
    "_targetConnect",
    "_saveVer",
    "_result",
    "_operate",
    "_memCapa",
    "_fileCapa",
    "_useMtap",
    "_chgUseMtap",
    "_isMemCapaOK",
    "_isfileCapaOK",
    "_isEndOperat",
    "_freeSizeList",
    "_freeFileList",
    "_formatList",
    "_totalSizeList",
    "_gameData",
    "_platformData",
};
static igMetaField **g_beSvDeliver_fieldHandles[] = {
    &g_beSvDeliver_actConnectMetaField,
    &g_beSvDeliver_targetConnectMetaField,
    &g_beSvDeliver_saveVerMetaField,
    &g_beSvDeliver_resultMetaField,
    &g_beSvDeliver_operateMetaField,
    &g_beSvDeliver_memCapaMetaField,
    &g_beSvDeliver_fileCapaMetaField,
    &g_beSvDeliver_useMtapMetaField,
    &g_beSvDeliver_chgUseMtapMetaField,
    &g_beSvDeliver_isMemCapaOKMetaField,
    &g_beSvDeliver_isfileCapaOKMetaField,
    &g_beSvDeliver_isEndOperatMetaField,
    &g_beSvDeliver_freeSizeListMetaField,
    &g_beSvDeliver_freeFileListMetaField,
    &g_beSvDeliver_formatListMetaField,
    &g_beSvDeliver_totalSizeListMetaField,
    &g_beSvDeliver_gameDataMetaField,
    &g_beSvDeliver_platformDataMetaField,
};
static int g_beSvDeliver_fieldOffsets[] = {
    12,
    16,
    20,
    24,
    28,
    32,
    36,
    40,
    41,
    42,
    43,
    44,
    48,
    52,
    56,
    60,
    8,
    64,
};

void beSvDeliver_InitFields(void) {
    int base;
    void *actConnect;
    void *freeSizeList;
    void *freeFileList;
    void *formatList;
    void *totalSizeList;
    void *gameData;
    void *platformData;
    igMetaObject *meta;

    meta = g_beSvDeliver_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beSvDeliver_ctorTable, 0x12);
    actConnect = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)actConnect)->_metaObject = (int)Gap::Core::igIntList::getClassTypeLazy();
    ((igRefMetaField *)actConnect)->_construct = 1;
    ((Gap::Core::igCharMetaField *)(igMetaObject_GetFieldAt(meta, base + 7)))->setDefault(-1);
    ((Gap::Core::igCharMetaField *)(igMetaObject_GetFieldAt(meta, base + 8)))->setDefault(0);
    freeSizeList = (void *)(igMetaObject_GetFieldAt(meta, base + 0xC));
    ((igObjectRefMetaField *)freeSizeList)->_metaObject = (int)Gap::Core::igIntList::getClassTypeLazy();
    ((igRefMetaField *)freeSizeList)->_construct = 1;
    freeFileList = (void *)(igMetaObject_GetFieldAt(meta, base + 0xD));
    ((igObjectRefMetaField *)freeFileList)->_metaObject = (int)Gap::Core::igIntList::getClassTypeLazy();
    ((igRefMetaField *)freeFileList)->_construct = 1;
    formatList = (void *)(igMetaObject_GetFieldAt(meta, base + 0xE));
    ((igObjectRefMetaField *)formatList)->_metaObject = (int)Gap::Core::igIntList::getClassTypeLazy();
    ((igRefMetaField *)formatList)->_construct = 1;
    totalSizeList = (void *)(igMetaObject_GetFieldAt(meta, base + 0xF));
    ((igObjectRefMetaField *)totalSizeList)->_metaObject = (int)Gap::Core::igIntList::getClassTypeLazy();
    ((igRefMetaField *)totalSizeList)->_construct = 1;
    gameData = (void *)(igMetaObject_GetFieldAt(meta, base + 0x10));
    ((igObjectRefMetaField *)gameData)->_metaObject = (int)beSaveDataDeliver_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)gameData)->_refCounted = 0;
    platformData = (void *)(igMetaObject_GetFieldAt(meta, base + 0x11));
    ((igObjectRefMetaField *)platformData)->_metaObject = (int)beSvPlatBaseData_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beSvDeliver_fieldTable, g_beSvDeliver_fieldHandles, g_beSvDeliver_fieldOffsets, base);
}

