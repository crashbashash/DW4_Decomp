igMetaObject *g_beNDMWLoadIntf2_metaObject;
igMetaField *g_beNDMWLoadIntf2_padManagerMetaField;
igMetaField *g_beNDMWLoadIntf2_systemMetaField;
igMetaField *g_beNDMWLoadIntf2_kindHardMetaField;
igMetaField *g_beNDMWLoadIntf2_difficultMaxMetaField;

void beNDMWLoadIntf2_CreateInstance(int allocator) {
    beNDMWLoadIntf2_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWLoadIntf2_metaObject, allocator);
}

igMetaObject *beNDMWLoadIntf2_GetOrCreateMetaObject(void) {
    if (g_beNDMWLoadIntf2_metaObject == 0) {
        g_beNDMWLoadIntf2_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beNDMWLoadIntf2_metaObject;
}

void *beNDMWLoadIntf2_ResolveMetaObject(void) {
    igMetaObject *g = g_beNDMWLoadIntf2_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWLoadIntf2_EnsureRegistered();
    }
    return g_beNDMWLoadIntf2_metaObject;
}

int beNDMWLoadIntf2_GetVTable(void) {
    beNDMWLoadIntf2 obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._infoList = 0;
    *(int **)&obj._vtable = &g_beNDMWLoadIntf2_vtable[0];
    obj._padManager = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    *(int **)&obj._vtable = &g_beNDMWLoadIntf2_vtable[0];
    igSmartPointer_bePadManager_Destruct(&obj._padManager, -1);
    beBaseInfoManager_Destroy(&obj, 0);
    return vtable;
}

void beNDMWLoadIntf2_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadIntf2_Register);
}

static igMetaObjectCallback g_beNDMWLoadIntf2_callbackList[] = { bePadManager_EnsureRegistered, beSystem_EnsureRegistered, 0 };

void *beNDMWLoadIntf2_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWLoadIntf2_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beNDMWLoadIntf2_GetMetaObject,
        "beNDMWLoadIntf2",
        0x30, /* instance size */
        beNDMWLoadIntf2_GetVTable,
        beNDMWLoadIntf2_InitFields,
        0, /* extra callback item */
        g_beNDMWLoadIntf2_callbackList /* callback list */
    );
}

void beNDMWLoadIntf2_GetMetaObject(void)
{
    beNDMWLoadIntf2_ResolveMetaObject();
}

static FieldFactory g_beNDMWLoadIntf2_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beNDMWLoadIntf2_fieldTable[] = {
    "_padManager",
    "_system",
    "_kindHard",
    "_difficultMax",
};
static igMetaField **g_beNDMWLoadIntf2_fieldHandles[] = {
    &g_beNDMWLoadIntf2_padManagerMetaField,
    &g_beNDMWLoadIntf2_systemMetaField,
    &g_beNDMWLoadIntf2_kindHardMetaField,
    &g_beNDMWLoadIntf2_difficultMaxMetaField,
};
static int g_beNDMWLoadIntf2_fieldOffsets[] = {
    36,
    32,
    40,
    44,
};

void beNDMWLoadIntf2_InitFields(void) {
    int base;
    void *system;
    void *padManager;
    igMetaObject *meta;

    meta = g_beNDMWLoadIntf2_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNDMWLoadIntf2_ctorTable, 4);
    padManager = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)padManager)->_metaObject = bePadManager_GetOrCreateMetaObject();
    system = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)system)->_metaObject = beSystem_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)system)->_refCounted = 0;
    igMetaObject_NameFields(meta, g_beNDMWLoadIntf2_fieldTable, g_beNDMWLoadIntf2_fieldHandles, g_beNDMWLoadIntf2_fieldOffsets, base);
}

