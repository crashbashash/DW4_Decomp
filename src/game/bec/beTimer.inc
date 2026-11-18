igMetaObject *g_beTimer_metaObject;
igMetaField *g_beTimer_systemMetaField;
igMetaField *g_beTimer_padManagerMetaField;
igMetaField *g_beTimer_luaManagerMetaField;
igMetaField *g_beTimer_dataListMetaField;
igMetaField *g_beTimer_oldWorldTimeMetaField;

beTimer *beTimer_CreateInstance(int allocator) {
    beTimer_EnsureRegistered();
    return (beTimer *)igMetaObject_CreateInstance(g_beTimer_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beTimer_GetOrCreateMetaObject(void) {
    if (g_beTimer_metaObject == 0) {
        g_beTimer_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beTimer_metaObject;
}

void *beTimer_GetMetaObject(void) {
    igMetaObject *g = g_beTimer_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beTimer_EnsureRegistered();
    }
    return g_beTimer_metaObject;
}

int beTimer_GetVTable(void) {
    beTimer obj;
    int vtable;
    igObject **dataListSlot;
    char **nameSlot;

    igObject_InitHeader(&obj);
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    obj._vtable = (int)&g_beTimer_vtable[0];
    dataListSlot = (igObject **)&obj._dataList;
    *dataListSlot = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beTimer_vtable[0];
    igObjectRef_Release(dataListSlot);
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

void beTimer_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beTimer_Register);
}

static igMetaObjectCallback g_beTimer_callbackList[] = { beSystem_EnsureRegistered, bePadManager_EnsureRegistered, beLua_EnsureRegistered, beTimerDataList_EnsureRegistered, 0 };

CallbackArray *beTimer_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beTimer_metaObject,
        igInfoManager_Register,
        igInfoManager_GetPublishedMetaObject,
        beTimer_GetMetaObjectFunction,
        "beTimer",
        0x28, /* instance size */
        beTimer_GetVTable,
        beTimer_InitFields,
        0, /* extra callback item */
        g_beTimer_callbackList /* callback list */
    );
}

void beTimer_GetMetaObjectFunction(void)
{
    beTimer_GetMetaObject();
}

static FieldFactory g_beTimer_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igLongMetaField_Create,
};
static const char *g_beTimer_fieldTable[] = {
    "_system",
    "_padManager",
    "_luaManager",
    "_dataList",
    "_oldWorldTime",
};
static igMetaField **g_beTimer_fieldHandles[] = {
    &g_beTimer_systemMetaField,
    &g_beTimer_padManagerMetaField,
    &g_beTimer_luaManagerMetaField,
    &g_beTimer_dataListMetaField,
    &g_beTimer_oldWorldTimeMetaField,
};
static int g_beTimer_fieldOffsets[] = {
    16,
    20,
    24,
    28,
    32,
};

void beTimer_InitFields(void) {
    int base;
    void *dataList;
    void *luaManager;
    void *padManager;
    void *system;
    igMetaObject *meta;

    meta = g_beTimer_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beTimer_ctorTable, 5);
    system = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)system)->_metaObject = (int)beSystem_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)system)->_refCounted = 0;
    padManager = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)padManager)->_metaObject = (int)bePadManager_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)padManager)->_refCounted = 0;
    luaManager = (void *)(igMetaObject_GetFieldAt(meta, base + 2));
    ((igObjectRefMetaField *)luaManager)->_metaObject = (int)beLua_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)luaManager)->_refCounted = 0;
    dataList = (void *)(igMetaObject_GetFieldAt(meta, base + 3));
    ((igObjectRefMetaField *)dataList)->_metaObject = (int)beTimerDataList_GetOrCreateMetaObject();
    ((igRefMetaField *)dataList)->_construct = 1;
    igMetaObject_NameFields(meta, g_beTimer_fieldTable, g_beTimer_fieldHandles, g_beTimer_fieldOffsets, base);
}

