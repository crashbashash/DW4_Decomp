int igDriverDatabase_GetSectionOverrideModeMetaEnum(void) {
    if (DAT_005865c8[0] == 0) {
        DAT_005865c8[0] = ((int)igMetaEnum_Create((char *)(&SECTION_OVERRIDE_MODE[0]), (char **)(&DAT_004c0fb8[0]), &DAT_004c0fc0[0], 2));
    }
    return DAT_005865c8[0];
}

void igDriverDatabase_Create(int arg0) {
    igDriverDatabase_EnsureRegistered();
    igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x5865D0), (igMemoryPoolView *)arg0);
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
    db._vtable = (int)&DAT_00530630[0];
    db._currentProperties = 0;
    db._subPropertyNames = 0;
    db._subPropertyValues = 0;
    db._overrideSource = 0;
    db._databaseFile = 0;
    db._databaseFileName = 0;
    db._rawDatabase = 0;
    r = *(int *)((char *)&db + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    db._vtable = (int)&DAT_00530630[0];
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
        0, /* abstract */
        ((char *)g_igDriverDatabase_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        igDriverDatabase_GetMetaObjectFunction,
        igDriverDatabase_className,
        0x38, /* instance size */
        igDriverDatabase_GetVTable,
        &igDriverDatabase_InitFields,
        0, /* extra callback item */
        g_igDriverDatabase_callbackList /* callback list */
    );
}

void igDriverDatabase_GetMetaObjectFunction(void) {
    igDriverDatabase_GetMetaObject();
}

void igDriverDatabase_InitFields(void) {
    int temp_s1;
    void *temp_s2;
    void *temp_s2_2;
    void *temp_s2_3;
    void *temp_s2_4;
    void *temp_s2_5;
    void *temp_s2_6;
    void *temp_s2_7;
    void *temp_v0;
    void *temp_v0_2;
    void *temp_v0_3;
    void *temp_s0;

    temp_s0 = (void *)g_igDriverDatabase_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount((igMetaObject *)temp_s0);
    igMetaObject_CreateFields((igMetaObject *)temp_s0, (igMetaField * (**)(void *))&g_igDriverDatabase_ctorTable[0], 0xC);
    temp_s2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1)));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = (int)igStringObjList_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s2)->_construct = 1;
    temp_s2_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 1)));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = (int)igStringRefListList_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s2_2)->_construct = 1;
    temp_s2_3 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 2)));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = (int)igStringRefListList_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s2_3)->_construct = 1;
    temp_s2_4 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 3)));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = (int)igRegistry_GetOrCreateMetaObject();
    igIntMetaField_SetDefault((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 4))), -1);
    temp_v0 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 5)));
    igEnumMetaField_SetDefaultValue((igMetaFieldView *)temp_v0, (const int *)&DAT_004c10b0[0]);
    ((igEnumMetaField *)temp_v0)->_getMetaEnumFunction = (int)(&igDriverDatabase_GetSectionOverrideModeMetaEnum);
    temp_s2_5 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 6)));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = (int)igFile_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s2_5)->_persistent = 0;
    ((igObjectRefMetaField *)temp_s2_5)->_deepCopyMethod = 3;
    ((igObjectRefMetaField *)temp_s2_5)->_shallowCopyMethod = 3;
    temp_s2_6 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 7)));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = (int)igStringObj_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s2_6)->_construct = 1;
    ((igObjectRefMetaField *)temp_s2_6)->_persistent = 0;
    ((igObjectRefMetaField *)temp_s2_6)->_deepCopyMethod = 3;
    ((igObjectRefMetaField *)temp_s2_6)->_shallowCopyMethod = 3;
    temp_s2_7 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 8)));
    ((igObjectRefMetaField *)temp_s2_7)->_metaObject = (int)igStringObj_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s2_7)->_construct = 1;
    ((igObjectRefMetaField *)temp_s2_7)->_persistent = 0;
    ((igObjectRefMetaField *)temp_s2_7)->_deepCopyMethod = 3;
    ((igObjectRefMetaField *)temp_s2_7)->_shallowCopyMethod = 3;
    temp_v0_2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 9)));
    ((igIntMetaField *)temp_v0_2)->_persistent = 0;
    ((igIntMetaField *)temp_v0_2)->_deepCopyMethod = 3;
    ((igIntMetaField *)temp_v0_2)->_shallowCopyMethod = 3;
    ((igBoolMetaField *)((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0xA)))->_persistent = 0;
    temp_v0_3 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)temp_s0, temp_s1 + 0xB)));
    ((igRawRefMetaField *)temp_v0_3)->_persistent = 0;
    ((igRawRefMetaField *)temp_v0_3)->_deepCopyMethod = 3;
    ((igRawRefMetaField *)temp_v0_3)->_shallowCopyMethod = 3;
    igMetaObject_NameFields((igMetaObject *)temp_s0, (const char **)&g_igDriverDatabase_fieldTable[0], (igMetaField ***)&DAT_004c1050[0], &DAT_004c1080[0], temp_s1);
}

