igMetaObject *g_beDataBase_metaObject;
igMetaField *g_beDataBase_charOffsetListMetaField;
igMetaField *g_beDataBase_charDataMetaField;
igMetaField *g_beDataBase_shortOffsetListMetaField;
igMetaField *g_beDataBase_shortDataMetaField;
igMetaField *g_beDataBase_intOffsetListMetaField;
igMetaField *g_beDataBase_intDataMetaField;
igMetaField *g_beDataBase_floatOffsetListMetaField;
igMetaField *g_beDataBase_floatDataMetaField;
igMetaField *g_beDataBase_boolOffsetListMetaField;
igMetaField *g_beDataBase_boolDataMetaField;
igMetaField *g_beDataBase_stringOffsetListMetaField;
igMetaField *g_beDataBase_stringDataMetaField;

igMetaObject *beDataBase_GetOrCreateMetaObject(void) {
    if (g_beDataBase_metaObject == 0) {
        g_beDataBase_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beDataBase_metaObject;
}

void *beDataBase_GetMetaObject(void) {
    igMetaObject *g = g_beDataBase_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beDataBase_EnsureRegistered();
    }
    return g_beDataBase_metaObject;
}

int beDataBase_GetVTable(void) {
    beDataBase obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beDataBase_vtable[0];
    obj._charOffsetList = 0;
    obj._charData = 0;
    obj._shortOffsetList = 0;
    obj._shortData = 0;
    obj._intOffsetList = 0;
    obj._intData = 0;
    obj._floatOffsetList = 0;
    obj._floatData = 0;
    obj._boolOffsetList = 0;
    obj._boolData = 0;
    obj._stringOffsetList = 0;
    obj._stringData = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beDataBase_vtable[0];
    igSmartPointer_igNamedObjectList_Destruct((igSmartPointer<igObject> *)&obj._stringData, -1);
    igSmartPointer_igNamedObjectList_Destruct((igSmartPointer<igObject> *)&obj._stringOffsetList, -1);
    igSmartPointer_igBoolList_Destruct((igSmartPointer<igObject> *)&obj._boolData, -1);
    igSmartPointer_igNamedObjectList_Destruct((igSmartPointer<igObject> *)&obj._boolOffsetList, -1);
    igSmartPointer_igFloatList_Destruct((igSmartPointer<igObject> *)&obj._floatData, -1);
    igSmartPointer_igNamedObjectList_Destruct((igSmartPointer<igObject> *)&obj._floatOffsetList, -1);
    igSmartPointer_igIntList_Destruct((igSmartPointer<igObject> *)&obj._intData, -1);
    igSmartPointer_igNamedObjectList_Destruct((igSmartPointer<igObject> *)&obj._intOffsetList, -1);
    igSmartPointer_igShortList_Destruct((igSmartPointer<igObject> *)&obj._shortData, -1);
    igSmartPointer_igNamedObjectList_Destruct((igSmartPointer<igObject> *)&obj._shortOffsetList, -1);
    igSmartPointer_igCharList_Destruct((igSmartPointer<igObject> *)&obj._charData, -1);
    igSmartPointer_igNamedObjectList_Destruct((igSmartPointer<igObject> *)&obj._charOffsetList, -1);
    return vtable;
}

void beDataBase_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beDataBase_Register);
}

static igMetaObjectCallback g_beDataBase_callbackList[] = { igNamedObjectList_EnsureRegistered, Gap::Core::igCharList::arkRegister, Gap::Core::igShortList::arkRegister, Gap::Core::igIntList::arkRegister, Gap::Core::igFloatList::arkRegister, Gap::Core::igBoolList::arkRegister, 0 };

CallbackArray *beDataBase_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beDataBase_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        beDataBase_GetMetaObjectFunction,
        "beDataBase",
        0x38, /* instance size */
        beDataBase_GetVTable,
        beDataBase_InitFields,
        0, /* extra callback item */
        g_beDataBase_callbackList /* callback list */
    );
}

void beDataBase_GetMetaObjectFunction(void)
{
    beDataBase_GetMetaObject();
}

static FieldFactory g_beDataBase_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beDataBase_fieldTable[] = {
    "_charOffsetList",
    "_charData",
    "_shortOffsetList",
    "_shortData",
    "_intOffsetList",
    "_intData",
    "_floatOffsetList",
    "_floatData",
    "_boolOffsetList",
    "_boolData",
    "_stringOffsetList",
    "_stringData",
};
static igMetaField **g_beDataBase_fieldHandles[] = {
    &g_beDataBase_charOffsetListMetaField,
    &g_beDataBase_charDataMetaField,
    &g_beDataBase_shortOffsetListMetaField,
    &g_beDataBase_shortDataMetaField,
    &g_beDataBase_intOffsetListMetaField,
    &g_beDataBase_intDataMetaField,
    &g_beDataBase_floatOffsetListMetaField,
    &g_beDataBase_floatDataMetaField,
    &g_beDataBase_boolOffsetListMetaField,
    &g_beDataBase_boolDataMetaField,
    &g_beDataBase_stringOffsetListMetaField,
    &g_beDataBase_stringDataMetaField,
};
static int g_beDataBase_fieldOffsets[] = {
    8,
    12,
    16,
    20,
    24,
    28,
    32,
    36,
    40,
    44,
    48,
    52,
};

void beDataBase_InitFields(void) {
    int base;
    void *charOffsetList;
    void *boolData;
    void *stringOffsetList;
    void *stringData;
    void *charData;
    void *shortOffsetList;
    void *shortData;
    void *intOffsetList;
    void *intData;
    void *floatOffsetList;
    void *floatData;
    void *boolOffsetList;
    igMetaObject *meta;

    meta = g_beDataBase_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beDataBase_ctorTable, 0xC);
    charOffsetList = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)charOffsetList)->_metaObject = (int)igNamedObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)charOffsetList)->_construct = 1;
    charData = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)charData)->_metaObject = (int)Gap::Core::igCharList::getClassTypeLazy();
    ((igRefMetaField *)charData)->_construct = 1;
    shortOffsetList = (void *)(igMetaObject_GetFieldAt(meta, base + 2));
    ((igObjectRefMetaField *)shortOffsetList)->_metaObject = (int)igNamedObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)shortOffsetList)->_construct = 1;
    shortData = (void *)(igMetaObject_GetFieldAt(meta, base + 3));
    ((igObjectRefMetaField *)shortData)->_metaObject = (int)Gap::Core::igShortList::getClassTypeLazy();
    ((igRefMetaField *)shortData)->_construct = 1;
    intOffsetList = (void *)(igMetaObject_GetFieldAt(meta, base + 4));
    ((igObjectRefMetaField *)intOffsetList)->_metaObject = (int)igNamedObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)intOffsetList)->_construct = 1;
    intData = (void *)(igMetaObject_GetFieldAt(meta, base + 5));
    ((igObjectRefMetaField *)intData)->_metaObject = (int)Gap::Core::igIntList::getClassTypeLazy();
    ((igRefMetaField *)intData)->_construct = 1;
    floatOffsetList = (void *)(igMetaObject_GetFieldAt(meta, base + 6));
    ((igObjectRefMetaField *)floatOffsetList)->_metaObject = (int)igNamedObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)floatOffsetList)->_construct = 1;
    floatData = (void *)(igMetaObject_GetFieldAt(meta, base + 7));
    ((igObjectRefMetaField *)floatData)->_metaObject = (int)Gap::Core::igFloatList::getClassTypeLazy();
    ((igRefMetaField *)floatData)->_construct = 1;
    boolOffsetList = (void *)(igMetaObject_GetFieldAt(meta, base + 8));
    ((igObjectRefMetaField *)boolOffsetList)->_metaObject = (int)igNamedObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)boolOffsetList)->_construct = 1;
    boolData = (void *)(igMetaObject_GetFieldAt(meta, base + 9));
    ((igObjectRefMetaField *)boolData)->_metaObject = (int)Gap::Core::igBoolList::getClassTypeLazy();
    ((igRefMetaField *)boolData)->_construct = 1;
    stringOffsetList = (void *)(igMetaObject_GetFieldAt(meta, base + 0xA));
    ((igObjectRefMetaField *)stringOffsetList)->_metaObject = (int)igNamedObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)stringOffsetList)->_construct = 1;
    stringData = (void *)(igMetaObject_GetFieldAt(meta, base + 0xB));
    ((igObjectRefMetaField *)stringData)->_metaObject = (int)igNamedObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)stringData)->_construct = 1;
    igMetaObject_NameFields(meta, g_beDataBase_fieldTable, g_beDataBase_fieldHandles, g_beDataBase_fieldOffsets, base);
}

