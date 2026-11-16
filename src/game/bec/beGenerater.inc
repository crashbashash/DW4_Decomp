igMetaObject *g_beGenerater_metaObject;
igMetaField *g_beGenerater_luaManagerMetaField;
igMetaField *g_beGenerater_isPerfectDropMetaField;

void beGenerater_CreateInstance(int allocator) {
    beGenerater_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x5895D0, allocator);
}

igMetaObject *beGenerater_GetOrCreateMetaObject(void) {
    if (g_beGenerater_metaObject == 0) {
        g_beGenerater_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beGenerater_metaObject;
}

void *beGenerater_GetMetaObject(void) {
    igMetaObject *g = g_beGenerater_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beGenerater_EnsureRegistered();
    }
    return g_beGenerater_metaObject;
}

int beGenerater_GetVTable(void) {
    beGenerater obj;
    int vtable;
    igObject **infoListSlot;
    char **nameSlot;

    igObject_InitHeader(&obj);
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    obj._vtable = (int)&g_beBaseInfoManager_vtable[0];
    infoListSlot = (igObject **)&obj._infoList;
    *infoListSlot = 0;
    obj._vtable = (int)&g_beGenerater_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj._vtable = (int)&g_beBaseInfoManager_vtable[0];
    igObjectRef_Release(infoListSlot);
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

void beGenerater_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beGenerater_Register);
}

static igMetaObjectCallback g_beGenerater_callbackList[] = { beLua_EnsureRegistered, 0 };

void *beGenerater_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beGenerater_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beGenerater_GetMetaObjectFunction,
        "beGenerater",
        0x28, /* instance size */
        beGenerater_GetVTable,
        beGenerater_InitFields,
        0, /* extra callback item */
        g_beGenerater_callbackList /* callback list */
    );
}

void beGenerater_GetMetaObjectFunction(void)
{
    beGenerater_GetMetaObject();
}

static FieldFactory g_beGenerater_ctorTable[] = {
    igObjectRefMetaField_Create,
    igBoolMetaField_Create,
};
static const char *g_beGenerater_fieldTable[] = {
    "_luaManager",
    "_isPerfectDrop",
};
static igMetaField **g_beGenerater_fieldHandles[] = {
    &g_beGenerater_luaManagerMetaField,
    &g_beGenerater_isPerfectDropMetaField,
};
static int g_beGenerater_fieldOffsets[] = {
    32,
    36,
};

void beGenerater_InitFields(void) {
    int base;
    void *luaManager;
    void *meta;

    meta = (void *)g_beGenerater_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beGenerater_ctorTable, 2);
    luaManager = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)luaManager)->_metaObject = (int)beLua_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)luaManager)->_refCounted = 0;
    igMetaObject_NameFields(meta, g_beGenerater_fieldTable, g_beGenerater_fieldHandles, g_beGenerater_fieldOffsets, base);
}

