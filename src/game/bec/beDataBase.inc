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
        g_beDataBase_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
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
    union U_365980 u;
    int temp_s5;

    igObject_InitHeader(u.b);
    u.w[0] = (int)(&g_beDataBase_vtable[0]);
    u.w[2] = 0;
    u.w[3] = 0;
    u.w[4] = 0;
    u.w[5] = 0;
    u.w[6] = 0;
    u.w[7] = 0;
    u.w[8] = 0;
    u.w[9] = 0;
    u.w[10] = 0;
    u.w[11] = 0;
    u.w[12] = 0;
    u.w[13] = 0;
    temp_s5 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.w[0] = (int)(&g_beDataBase_vtable[0]);
    FUN_00199450(&u.w[13], -1);
    FUN_00199450(&u.w[12], -1);
    FUN_00226990(&u.w[11], -1);
    FUN_00199450(&u.w[10], -1);
    FUN_001354b0(&u.w[9], -1);
    FUN_00199450(&u.w[8], -1);
    igSmartPointer_igIntList_Destruct(&u.w[7], -1);
    FUN_00199450(&u.w[6], -1);
    FUN_001648f0(&u.w[5], -1);
    FUN_00199450(&u.w[4], -1);
    FUN_00164970(&u.w[3], -1);
    FUN_00199450(&u.w[2], -1);
    return temp_s5;
}

void beDataBase_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beDataBase_Register);
}

static igMetaObjectCallback g_beDataBase_callbackList[] = { igNamedObjectList_EnsureRegistered, igCharList_EnsureRegistered, igShortList_EnsureRegistered, igIntList_EnsureRegistered, igFloatList_EnsureRegistered, igBoolList_EnsureRegistered, 0 };

void *beDataBase_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beDataBase_metaObject,
        igObject_Register,
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
    void *meta;

    meta = (void *)g_beDataBase_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beDataBase_ctorTable, 0xC);
    charOffsetList = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)charOffsetList)->_metaObject = igNamedObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)charOffsetList)->_construct = 1;
    charData = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)charData)->_metaObject = igCharList_GetOrCreateMetaObject();
    ((igRefMetaField *)charData)->_construct = 1;
    shortOffsetList = (void *)(igMetaObject_GetFieldAt(meta, base + 2));
    ((igObjectRefMetaField *)shortOffsetList)->_metaObject = igNamedObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)shortOffsetList)->_construct = 1;
    shortData = (void *)(igMetaObject_GetFieldAt(meta, base + 3));
    ((igObjectRefMetaField *)shortData)->_metaObject = igShortList_GetOrCreateMetaObject();
    ((igRefMetaField *)shortData)->_construct = 1;
    intOffsetList = (void *)(igMetaObject_GetFieldAt(meta, base + 4));
    ((igObjectRefMetaField *)intOffsetList)->_metaObject = igNamedObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)intOffsetList)->_construct = 1;
    intData = (void *)(igMetaObject_GetFieldAt(meta, base + 5));
    ((igObjectRefMetaField *)intData)->_metaObject = igIntList_GetOrCreateMetaObject();
    ((igRefMetaField *)intData)->_construct = 1;
    floatOffsetList = (void *)(igMetaObject_GetFieldAt(meta, base + 6));
    ((igObjectRefMetaField *)floatOffsetList)->_metaObject = igNamedObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)floatOffsetList)->_construct = 1;
    floatData = (void *)(igMetaObject_GetFieldAt(meta, base + 7));
    ((igObjectRefMetaField *)floatData)->_metaObject = igFloatList_GetOrCreateMetaObject();
    ((igRefMetaField *)floatData)->_construct = 1;
    boolOffsetList = (void *)(igMetaObject_GetFieldAt(meta, base + 8));
    ((igObjectRefMetaField *)boolOffsetList)->_metaObject = igNamedObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)boolOffsetList)->_construct = 1;
    boolData = (void *)(igMetaObject_GetFieldAt(meta, base + 9));
    ((igObjectRefMetaField *)boolData)->_metaObject = igBoolList_GetOrCreateMetaObject();
    ((igRefMetaField *)boolData)->_construct = 1;
    stringOffsetList = (void *)(igMetaObject_GetFieldAt(meta, base + 0xA));
    ((igObjectRefMetaField *)stringOffsetList)->_metaObject = igNamedObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)stringOffsetList)->_construct = 1;
    stringData = (void *)(igMetaObject_GetFieldAt(meta, base + 0xB));
    ((igObjectRefMetaField *)stringData)->_metaObject = igNamedObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)stringData)->_construct = 1;
    igMetaObject_NameFields(meta, g_beDataBase_fieldTable, g_beDataBase_fieldHandles, g_beDataBase_fieldOffsets, base);
}

