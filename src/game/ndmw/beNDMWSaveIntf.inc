igMetaObject *g_beNDMWSaveIntf_metaObject;
igMetaField *g_beNDMWSaveIntf_padManagerMetaField;
igMetaField *g_beNDMWSaveIntf_systemMetaField;
igMetaField *g_beNDMWSaveIntf_kindHardMetaField;

void beNDMWSaveIntf_CreateInstance(int allocator) {
    beNDMWSaveIntf_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWSaveIntf_metaObject, allocator);
}

igMetaObject *beNDMWSaveIntf_GetOrCreateMetaObject(void) {
    if (g_beNDMWSaveIntf_metaObject == 0) {
        g_beNDMWSaveIntf_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beNDMWSaveIntf_metaObject;
}

void *beNDMWSaveIntf_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWSaveIntf_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWSaveIntf_EnsureRegistered();
    }
    return g_beNDMWSaveIntf_metaObject;
}

int beNDMWSaveIntf_GetVTable(void) {
    struct F_3bcd60 f;
    int temp_s0;

    igObject_InitHeader(&f);
    f.w[1] = 0;
    f.w[5] = 0;
    f.vt = &g_beNDMWSaveIntf_vtable[0];
    f.w[8] = 0;
    temp_s0 = *(int *)((char *)&f + *(int *)((char *)(g_objectSystem[0]) + 916));
    f.vt = &g_beNDMWSaveIntf_vtable[0];
    FUN_0033dda0(&f.w[8], -1);
    FUN_0033f5e0(&f, 0);
    return temp_s0;
}

void beNDMWSaveIntf_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWSaveIntf_Register);
}

static igMetaObjectCallback g_beNDMWSaveIntf_callbackList[] = { bePadManager_EnsureRegistered, beSystem_EnsureRegistered, 0 };

void *beNDMWSaveIntf_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWSaveIntf_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beNDMWSaveIntf_GetMetaObjectFunction,
        "beNDMWSaveIntf",
        0x2c, /* instance size */
        beNDMWSaveIntf_GetVTable,
        beNDMWSaveIntf_InitFields,
        0, /* extra callback item */
        g_beNDMWSaveIntf_callbackList /* callback list */
    );
}

void beNDMWSaveIntf_GetMetaObjectFunction(void)
{
    beNDMWSaveIntf_GetMetaObject();
}

static FieldFactory g_beNDMWSaveIntf_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beNDMWSaveIntf_fieldTable[] = {
    "_padManager",
    "_system",
    "_kindHard",
};
static igMetaField **g_beNDMWSaveIntf_fieldHandles[] = {
    &g_beNDMWSaveIntf_padManagerMetaField,
    &g_beNDMWSaveIntf_systemMetaField,
    &g_beNDMWSaveIntf_kindHardMetaField,
};
static int g_beNDMWSaveIntf_fieldOffsets[] = {
    36,
    32,
    40,
};

void beNDMWSaveIntf_InitFields(void) {
    int base;
    void *system;
    void *padManager;
    igMetaObject *meta;

    meta = g_beNDMWSaveIntf_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNDMWSaveIntf_ctorTable, 3);
    padManager = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)padManager)->_metaObject = bePadManager_GetOrCreateMetaObject();
    system = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)system)->_metaObject = beSystem_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)system)->_refCounted = 0;
    igMetaObject_NameFields(meta, g_beNDMWSaveIntf_fieldTable, g_beNDMWSaveIntf_fieldHandles, g_beNDMWSaveIntf_fieldOffsets, base);
}

