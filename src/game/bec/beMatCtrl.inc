igMetaObject *g_beMatCtrl_metaObject;
igMetaField *g_beMatCtrl_wkChkMatMetaField;
igMetaField *g_beMatCtrl_wkChkPlMetaField;
igMetaField *g_beMatCtrl_wkChgFlagNOMetaField;
igMetaField *g_beMatCtrl_wkChgFlagMetaField;
igMetaField *g_beMatCtrl_wkPlExistMetaField;
igMetaField *g_beMatCtrl_wkMatOnListMetaField;
igMetaField *g_beMatCtrl_wkMatOldOnListMetaField;
igMetaField *g_beMatCtrl_isLuaCallDispMetaField;
igMetaField *g_beMatCtrl_luaMetaField;

beMatCtrl *beMatCtrl_CreateInstance(int allocator) {
    beMatCtrl_EnsureRegistered();
    return (beMatCtrl *)igMetaObject_CreateInstance(g_beMatCtrl_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beMatCtrl_GetOrCreateMetaObject(void) {
    if (g_beMatCtrl_metaObject == 0) {
        g_beMatCtrl_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beMatCtrl_metaObject;
}

void *beMatCtrl_GetMetaObject(void) {
    igMetaObject *g = g_beMatCtrl_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beMatCtrl_EnsureRegistered();
    }
    return g_beMatCtrl_metaObject;
}

int beMatCtrl_GetVTable(void) {
    beMatCtrl obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._infoList = 0;
    obj._vtable = (int)&g_beMatCtrl_vtable[0];
    obj._wkMatOnList = 0;
    obj._wkMatOldOnList = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beMatCtrl_vtable[0];
    igSmartPointer_igIntList_Destruct((igSmartPointer<igObject> *)&obj._wkMatOldOnList, -1);
    igSmartPointer_igIntList_Destruct((igSmartPointer<igObject> *)&obj._wkMatOnList, -1);
    beBaseInfoManager_Destroy((beBaseInfoManager *)&obj, (short)0);
    return vtable;
}

void beMatCtrl_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beMatCtrl_Register);
}

static igMetaObjectCallback g_beMatCtrl_callbackList[] = { igIntList_EnsureRegistered, beLua_EnsureRegistered, 0 };

CallbackArray *beMatCtrl_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beMatCtrl_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beMatCtrl_GetMetaObjectFunction,
        "beMatCtrl",
        0x44, /* instance size */
        beMatCtrl_GetVTable,
        beMatCtrl_InitFields,
        0, /* extra callback item */
        g_beMatCtrl_callbackList /* callback list */
    );
}

void beMatCtrl_GetMetaObjectFunction(void)
{
    beMatCtrl_GetMetaObject();
}

static FieldFactory g_beMatCtrl_ctorTable[] = {
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igBoolMetaField_Create,
    igBoolArrayMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igBoolMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beMatCtrl_fieldTable[] = {
    "_wkChkMat",
    "_wkChkPl",
    "_wkChgFlagNO",
    "_wkChgFlag",
    "_wkPlExist",
    "_wkMatOnList",
    "_wkMatOldOnList",
    "_isLuaCallDisp",
    "_lua",
};
static igMetaField **g_beMatCtrl_fieldHandles[] = {
    &g_beMatCtrl_wkChkMatMetaField,
    &g_beMatCtrl_wkChkPlMetaField,
    &g_beMatCtrl_wkChgFlagNOMetaField,
    &g_beMatCtrl_wkChgFlagMetaField,
    &g_beMatCtrl_wkPlExistMetaField,
    &g_beMatCtrl_wkMatOnListMetaField,
    &g_beMatCtrl_wkMatOldOnListMetaField,
    &g_beMatCtrl_isLuaCallDispMetaField,
    &g_beMatCtrl_luaMetaField,
};
static int g_beMatCtrl_fieldOffsets[] = {
    40,
    44,
    48,
    52,
    32,
    56,
    60,
    64,
    36,
};

void beMatCtrl_InitFields(void) {
    igMetaObject *meta;
    int base;
    igObjectRefMetaField *wkMatOnList;
    igObjectRefMetaField *wkMatOldOnList;
    igObjectRefMetaField *lua;
    igBoolArrayMetaField *wkPlExist;

    meta = g_beMatCtrl_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beMatCtrl_ctorTable, 9);
    wkPlExist = (igBoolArrayMetaField *)igMetaObject_GetFieldAt(meta, base + 4);
    wkPlExist->_num = 4;
    wkMatOnList = (igObjectRefMetaField *)igMetaObject_GetFieldAt(meta, base + 5);
    wkMatOnList->_metaObject = (int)igIntList_GetOrCreateMetaObject();
    wkMatOldOnList = (igObjectRefMetaField *)igMetaObject_GetFieldAt(meta, base + 6);
    wkMatOldOnList->_metaObject = (int)igIntList_GetOrCreateMetaObject();
    lua = (igObjectRefMetaField *)igMetaObject_GetFieldAt(meta, base + 8);
    lua->_metaObject = (int)beLua_GetOrCreateMetaObject();
    lua->_refCounted = 0;
    igMetaObject_NameFields(meta, g_beMatCtrl_fieldTable, g_beMatCtrl_fieldHandles, g_beMatCtrl_fieldOffsets, base);
}

