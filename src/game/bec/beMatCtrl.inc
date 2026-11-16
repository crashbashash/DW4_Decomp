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

void beMatCtrl_CreateInstance(int allocator) {
    beMatCtrl_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x589160, allocator);
}

igMetaObject *beMatCtrl_GetOrCreateMetaObject(void) {
    if (g_beMatCtrl_metaObject == 0) {
        g_beMatCtrl_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
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
    struct Obj_35a7f0 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.w[1] = 0;
    obj.w[5] = 0;
    obj.vt = &g_beMatCtrl_vtable[0];
    obj.w[13] = 0;
    obj.w[14] = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_beMatCtrl_vtable[0];
    igSmartPointer_igIntList_Destruct(&obj.w[14], -1);
    igSmartPointer_igIntList_Destruct(&obj.w[13], -1);
    FUN_0033f5e0((O_33f5e0 *)&obj, (short)0);
    return r;
}

void beMatCtrl_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beMatCtrl_Register);
}

static igMetaObjectCallback g_beMatCtrl_callbackList[] = { igIntList_EnsureRegistered, beLua_EnsureRegistered, 0 };

void *beMatCtrl_Register(void) {
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
    struct F_35a940 *wkMatOnList;
    struct F_35a940 *wkMatOldOnList;
    struct F_35a940 *lua;
    struct F_35a940 *t;

    meta = g_beMatCtrl_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beMatCtrl_ctorTable, 9);
    t = ((struct F_35a940 *)igMetaObject_GetFieldAt(meta, base + 4));
    t->f52 = 4;
    wkMatOnList = ((struct F_35a940 *)igMetaObject_GetFieldAt(meta, base + 5));
    wkMatOnList->f56 = igIntList_GetOrCreateMetaObject();
    wkMatOldOnList = ((struct F_35a940 *)igMetaObject_GetFieldAt(meta, base + 6));
    wkMatOldOnList->f56 = igIntList_GetOrCreateMetaObject();
    lua = ((struct F_35a940 *)igMetaObject_GetFieldAt(meta, base + 8));
    lua->f56 = (int)beLua_GetOrCreateMetaObject();
    lua->f60 = 0;
    igMetaObject_NameFields(meta, g_beMatCtrl_fieldTable, g_beMatCtrl_fieldHandles, g_beMatCtrl_fieldOffsets, base);
}

