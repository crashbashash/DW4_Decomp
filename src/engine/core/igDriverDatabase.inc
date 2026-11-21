static const char *g_sectionOverrideModeNames[] = {
    "USE_DEFAULT_SECTION", "IGNORE_SETTING",
};
static int g_sectionOverrideModeValues[] = {
    0, 1,
};

int igDriverDatabase_GetSectionOverrideModeMetaEnum(void) {
    if (g_sectionOverrideModeMetaEnum == 0) {
        g_sectionOverrideModeMetaEnum = ((int)Gap::Core::igMetaEnum::createMetaEnum((char *)("SECTION_OVERRIDE_MODE"), g_sectionOverrideModeNames, g_sectionOverrideModeValues, 2));
    }
    return g_sectionOverrideModeMetaEnum;
}

igMetaObject *g_igDriverDatabase_metaObject;
igMetaField *g_igDriverDatabase_currentPropertiesMetaField;
igMetaField *g_igDriverDatabase_subPropertyNamesMetaField;
igMetaField *g_igDriverDatabase_subPropertyValuesMetaField;
igMetaField *g_igDriverDatabase_overrideSourceMetaField;
igMetaField *g_igDriverDatabase_overrideSourceSectionMetaField;
igMetaField *g_igDriverDatabase_overrideModeMetaField;
igMetaField *g_igDriverDatabase_databaseFileMetaField;
igMetaField *g_igDriverDatabase_databaseFileNameMetaField;
igMetaField *g_igDriverDatabase_rawDatabaseMetaField;
igMetaField *g_igDriverDatabase_currentLineMetaField;
igMetaField *g_igDriverDatabase_verboseMetaField;
igMetaField *g_igDriverDatabase_dbIndexMetaField;

void *igDriverDatabase_Create(int pool) {
    igDriverDatabase_EnsureRegistered();
    return (void *)igMetaObject_CreateInstance(g_igDriverDatabase_metaObject, (igMemoryPoolView *)pool);
}

igMetaObject *igDriverDatabase_GetMetaObject(void)
{
    igMetaObject *g = g_igDriverDatabase_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igDriverDatabase_EnsureRegistered();
    return g_igDriverDatabase_metaObject;
}

int igDriverDatabase_GetVTable(void) {
    igDriverDatabase db;
    int r;

    igObject_InitHeader((igObject *)&db);
    db._vtable = (int)&g_igDriverDatabase_vtable[0];
    db._currentProperties = 0;
    db._subPropertyNames = 0;
    db._subPropertyValues = 0;
    db._overrideSource = 0;
    db._databaseFile = 0;
    db._databaseFileName = 0;
    db._rawDatabase = 0;
    r = *(int *)((char *)&db + g_objectSystem->vtableProbeOffset);
    db._vtable = (int)&g_igDriverDatabase_vtable[0];
    igSmartPointer_igStringObj_Destruct((igSmartPointer<igObject> *)&db._rawDatabase, -1);
    igSmartPointer_igStringObj_Destruct((igSmartPointer<igObject> *)&db._databaseFileName, -1);
    igSmartPointer_igFile_Destruct((igSmartPointer<igObject> *)&db._databaseFile, -1);
    igSmartPointer_igRegistry_Destruct((igSmartPointer<igObject> *)&db._overrideSource, -1);
    igSmartPointer_igStringRefListList_Destruct((igSmartPointer<igObject> *)&db._subPropertyValues, -1);
    igSmartPointer_igStringRefListList_Destruct((igSmartPointer<igObject> *)&db._subPropertyNames, -1);
    igSmartPointer_igStringObjList_Destruct((igSmartPointer<igObject> *)&db._currentProperties, -1);
    return r;
}

void igDriverDatabase_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igDriverDatabase_Register);
}

static igMetaObjectCallback g_igDriverDatabase_callbackList[] = { igStringObjList_EnsureRegistered, igStringRefListList_EnsureRegistered, Gap::Core::igRegistry::arkRegister, igFile_EnsureRegistered, igStringObj_EnsureRegistered, 0 };

CallbackArray *igDriverDatabase_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igDriverDatabase_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        igDriverDatabase_GetMetaObjectFunction,
        "igDriverDatabase",
        0x38,
        igDriverDatabase_GetVTable,
        igDriverDatabase_InitFields,
        0,
        g_igDriverDatabase_callbackList
    );
}

void igDriverDatabase_GetMetaObjectFunction(void) {
    igDriverDatabase_GetMetaObject();
}

static FieldFactory g_igDriverDatabase_ctorTable[] = {
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igRawRefMetaField_Create,
};
static const char *g_igDriverDatabase_fieldTable[] = {
    "_currentProperties",
    "_subPropertyNames",
    "_subPropertyValues",
    "_overrideSource",
    "_overrideSourceSection",
    "_overrideMode",
    "_databaseFile",
    "_databaseFileName",
    "_rawDatabase",
    "_currentLine",
    "_verbose",
    "_dbIndex",
};
static igMetaField **g_igDriverDatabase_fieldDescriptors[] = {
    &g_igDriverDatabase_currentPropertiesMetaField,
    &g_igDriverDatabase_subPropertyNamesMetaField,
    &g_igDriverDatabase_subPropertyValuesMetaField,
    &g_igDriverDatabase_overrideSourceMetaField,
    &g_igDriverDatabase_overrideSourceSectionMetaField,
    &g_igDriverDatabase_overrideModeMetaField,
    &g_igDriverDatabase_databaseFileMetaField,
    &g_igDriverDatabase_databaseFileNameMetaField,
    &g_igDriverDatabase_rawDatabaseMetaField,
    &g_igDriverDatabase_currentLineMetaField,
    &g_igDriverDatabase_verboseMetaField,
    &g_igDriverDatabase_dbIndexMetaField,
};
static int g_igDriverDatabase_fieldOffsets[] = {
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

void igDriverDatabase_InitFields(void) {
    int base;
    void *currentPropertiesField;
    void *subPropertyNamesField;
    void *subPropertyValuesField;
    void *overrideSourceField;
    void *databaseFileField;
    void *databaseFileNameField;
    void *rawDatabaseField;
    void *overrideModeField;
    void *currentLineField;
    void *dbIndexField;
    void *meta;

    meta = (void *)g_igDriverDatabase_metaObject;
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igDriverDatabase_ctorTable, 0xC);
    currentPropertiesField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base)));
    ((igObjectRefMetaField *)currentPropertiesField)->_metaObject = (int)igStringObjList_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)currentPropertiesField)->_construct = 1;
    subPropertyNamesField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 1)));
    ((igObjectRefMetaField *)subPropertyNamesField)->_metaObject = (int)igStringRefListList_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)subPropertyNamesField)->_construct = 1;
    subPropertyValuesField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 2)));
    ((igObjectRefMetaField *)subPropertyValuesField)->_metaObject = (int)igStringRefListList_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)subPropertyValuesField)->_construct = 1;
    overrideSourceField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 3)));
    ((igObjectRefMetaField *)overrideSourceField)->_metaObject = (int)Gap::Core::igRegistry::getClassTypeLazy();
    ((Gap::Core::igIntMetaField *)(igMetaObject_GetFieldAt((igMetaObject *)meta, base + 4)))->setDefault(-1);
    overrideModeField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 5)));
    ((Gap::Core::igEnumMetaField *)overrideModeField)->setDefault(0);
    ((igEnumMetaField *)overrideModeField)->_getMetaEnumFunction = (int)(&igDriverDatabase_GetSectionOverrideModeMetaEnum);
    databaseFileField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 6)));
    ((igObjectRefMetaField *)databaseFileField)->_metaObject = (int)igFile_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)databaseFileField)->_persistent = 0;
    ((igObjectRefMetaField *)databaseFileField)->_deepCopyMethod = 3;
    ((igObjectRefMetaField *)databaseFileField)->_shallowCopyMethod = 3;
    databaseFileNameField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 7)));
    ((igObjectRefMetaField *)databaseFileNameField)->_metaObject = (int)igStringObj_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)databaseFileNameField)->_construct = 1;
    ((igObjectRefMetaField *)databaseFileNameField)->_persistent = 0;
    ((igObjectRefMetaField *)databaseFileNameField)->_deepCopyMethod = 3;
    ((igObjectRefMetaField *)databaseFileNameField)->_shallowCopyMethod = 3;
    rawDatabaseField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 8)));
    ((igObjectRefMetaField *)rawDatabaseField)->_metaObject = (int)igStringObj_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)rawDatabaseField)->_construct = 1;
    ((igObjectRefMetaField *)rawDatabaseField)->_persistent = 0;
    ((igObjectRefMetaField *)rawDatabaseField)->_deepCopyMethod = 3;
    ((igObjectRefMetaField *)rawDatabaseField)->_shallowCopyMethod = 3;
    currentLineField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 9)));
    ((igIntMetaField *)currentLineField)->_persistent = 0;
    ((igIntMetaField *)currentLineField)->_deepCopyMethod = 3;
    ((igIntMetaField *)currentLineField)->_shallowCopyMethod = 3;
    ((igBoolMetaField *)((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0xA)))->_persistent = 0;
    dbIndexField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0xB)));
    ((igRawRefMetaField *)dbIndexField)->_persistent = 0;
    ((igRawRefMetaField *)dbIndexField)->_deepCopyMethod = 3;
    ((igRawRefMetaField *)dbIndexField)->_shallowCopyMethod = 3;
    igMetaObject_NameFields((igMetaObject *)meta, g_igDriverDatabase_fieldTable, g_igDriverDatabase_fieldDescriptors, g_igDriverDatabase_fieldOffsets, base);
}

