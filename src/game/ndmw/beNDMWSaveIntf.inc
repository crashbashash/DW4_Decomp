igMetaObject *g_beNDMWSaveIntf_metaObject;
igMetaField *g_beNDMWSaveIntf_padManagerMetaField;
igMetaField *g_beNDMWSaveIntf_systemMetaField;
igMetaField *g_beNDMWSaveIntf_kindHardMetaField;

void beNDMWSaveIntf_CreateInstance(int arg0) {
    beNDMWSaveIntf_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWSaveIntf_metaObject, arg0);
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
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_beNDMWSaveIntf_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beNDMWSaveIntf_ctorTable, 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = bePadManager_GetOrCreateMetaObject();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = beSystem_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s1_2)->_refCounted = 0;
    igMetaObject_NameFields(temp_s0, g_beNDMWSaveIntf_fieldTable, g_beNDMWSaveIntf_fieldHandles, g_beNDMWSaveIntf_fieldOffsets, temp_s2);
}

