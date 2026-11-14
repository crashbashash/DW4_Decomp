int igDriverDatabase_GetSectionOverrideModeMetaEnum(void) {
    if (g_sectionOverrideModeMetaEnum[0] == 0) {
        g_sectionOverrideModeMetaEnum[0] = ((int)igMetaEnum_Create((char *)(&SECTION_OVERRIDE_MODE[0]), (char **)(&g_sectionOverrideModeNames[0]), &g_sectionOverrideModeValues[0], 2));
    }
    return g_sectionOverrideModeMetaEnum[0];
}

void *igDriverDatabase_Create(int pool) {
    igDriverDatabase_EnsureRegistered();
    return (void *)igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x5865D0), (igMemoryPoolView *)pool);
}

igMetaObject *igDriverDatabase_GetMetaObject(void)
{
    igMetaObject *g = g_igDriverDatabase_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igDriverDatabase_EnsureRegistered();
    return g_igDriverDatabase_metaObject[0];
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
    r = *(int *)((char *)&db + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    db._vtable = (int)&g_igDriverDatabase_vtable[0];
    FUN_001489a0(&db._rawDatabase, -1);
    FUN_001489a0(&db._databaseFileName, -1);
    FUN_00150180(&db._databaseFile, -1);
    FUN_0019eeb0(&db._overrideSource, -1);
    FUN_00227e70(&db._subPropertyValues, -1);
    FUN_00227e70(&db._subPropertyNames, -1);
    FUN_001a0790(&db._currentProperties, -1);
    return r;
}

void igDriverDatabase_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igDriverDatabase_Register);
}

void igDriverDatabase_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        g_igDriverDatabase_metaObject,
        (igMetaObjectRegisterFunction)igObject_Register,
        (igMetaObjectGetFunction)igObject_GetMetaObject_ParentAccessor,
        igDriverDatabase_GetMetaObjectFunction,
        igDriverDatabase_className,
        0x38,
        igDriverDatabase_GetVTable,
        igDriverDatabase_InitFields,
        0,
        (igMetaObjectCallback *)g_igDriverDatabase_callbackList
    );
}

void igDriverDatabase_GetMetaObjectFunction(void) {
    igDriverDatabase_GetMetaObject();
}

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

    meta = (void *)g_igDriverDatabase_metaObject[0];
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, (igMetaField * (**)(void *))&g_igDriverDatabase_ctorTable[0], 0xC);
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
    ((igObjectRefMetaField *)overrideSourceField)->_metaObject = (int)igRegistry_GetOrCreateMetaObject();
    igIntMetaField_SetDefault((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 4))), -1);
    overrideModeField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 5)));
    igEnumMetaField_SetDefaultValue((igMetaFieldView *)overrideModeField, (const int *)&g_igDriverDatabase_defaultSectionOverrideMode[0]);
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
    igMetaObject_NameFields((igMetaObject *)meta, (const char **)&g_igDriverDatabase_fieldTable[0], (igMetaField ***)&g_igDriverDatabase_fieldDescriptors[0], &g_igDriverDatabase_fieldOffsets[0], base);
}

