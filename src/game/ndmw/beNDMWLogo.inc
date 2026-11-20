igMetaObject *g_beNDMWLogo_metaObject;
igMetaField *g_beNDMWLogo_padManagerMetaField;
igMetaField *g_beNDMWLogo_systemMetaField;
igMetaField *g_beNDMWLogo_mcUtilCtrlMetaField;
igMetaField *g_beNDMWLogo_connectMetaField;
igMetaField *g_beNDMWLogo_reCheckMetaField;
igMetaField *g_beNDMWLogo_retryCountMetaField;
igMetaField *g_beNDMWLogo_isUseSaveMetaField;
igMetaField *g_beNDMWLogo_isMtapMetaField;
igMetaField *g_beNDMWLogo_selectMetaField;
igMetaField *g_beNDMWLogo_errTargetMetaField;
igMetaField *g_beNDMWLogo_errTypeMetaField;

beNDMWLogo *beNDMWLogo_CreateInstance(int allocator) {
    beNDMWLogo_EnsureRegistered();
    return (beNDMWLogo *)igMetaObject_CreateInstance(g_beNDMWLogo_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beNDMWLogo_GetOrCreateMetaObject(void) {
    if (g_beNDMWLogo_metaObject == 0) {
        g_beNDMWLogo_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beNDMWLogo_metaObject;
}

void *beNDMWLogo_GetReadyMetaObject(void) {
    igMetaObject *g = g_beNDMWLogo_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWLogo_EnsureRegistered();
    }
    return g_beNDMWLogo_metaObject;
}

int beNDMWLogo_GetVTable(void) {
    beNDMWLogo obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._infoList = 0;
    *(int **)&obj._vtable = &g_beNDMWLogo_vtable[0];
    obj._mcUtilCtrl = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    *(int **)&obj._vtable = &g_beNDMWLogo_vtable[0];
    igSmartPointer_beNDMWMcUtilCtrl_Destruct((igSmartPointer<igObject> *)&obj._mcUtilCtrl, -1);
    beBaseInfoManager_Destroy((beBaseInfoManager *)&obj, 0);
    return vtable;
}

void beNDMWLogo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWLogo_Register);
}

static igMetaObjectCallback g_beNDMWLogo_callbackList[] = { bePadManager_EnsureRegistered, beSystem_EnsureRegistered, beNDMWMcUtilCtrl_EnsureRegistered, 0 };

CallbackArray *beNDMWLogo_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWLogo_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beNDMWLogo_GetMetaObject,
        "beNDMWLogo",
        0x5c, /* instance size */
        beNDMWLogo_GetVTable,
        beNDMWLogo_InitFields,
        0, /* extra callback item */
        g_beNDMWLogo_callbackList /* callback list */
    );
}

void beNDMWLogo_GetMetaObject(void)
{
    beNDMWLogo_GetReadyMetaObject();
}

static FieldFactory g_beNDMWLogo_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igBoolMetaField_Create,
    igIntMetaField_Create,
    igBoolMetaField_Create,
    igBoolMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beNDMWLogo_fieldTable[] = {
    "_padManager",
    "_system",
    "_mcUtilCtrl",
    "_connect",
    "_reCheck",
    "_retryCount",
    "_isUseSave",
    "_isMtap",
    "_select",
    "_errTarget",
    "_errType",
};
static igMetaField **g_beNDMWLogo_fieldHandles[] = {
    &g_beNDMWLogo_padManagerMetaField,
    &g_beNDMWLogo_systemMetaField,
    &g_beNDMWLogo_mcUtilCtrlMetaField,
    &g_beNDMWLogo_connectMetaField,
    &g_beNDMWLogo_reCheckMetaField,
    &g_beNDMWLogo_retryCountMetaField,
    &g_beNDMWLogo_isUseSaveMetaField,
    &g_beNDMWLogo_isMtapMetaField,
    &g_beNDMWLogo_selectMetaField,
    &g_beNDMWLogo_errTargetMetaField,
    &g_beNDMWLogo_errTypeMetaField,
};
static int g_beNDMWLogo_fieldOffsets[] = {
    36,
    32,
    40,
    44,
    48,
    52,
    56,
    57,
    60,
    64,
    68,
};

void beNDMWLogo_InitFields(void) {
    int base;
    void *mcUtilCtrl;
    void *system;
    void *padManager;
    igMetaObject *meta;

    meta = g_beNDMWLogo_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNDMWLogo_ctorTable, 0xB);
    padManager = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)padManager)->_metaObject = (int)bePadManager_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)padManager)->_refCounted = 0;
    system = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)system)->_metaObject = (int)beSystem_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)system)->_refCounted = 0;
    mcUtilCtrl = (void *)(igMetaObject_GetFieldAt(meta, base + 2));
    ((igObjectRefMetaField *)mcUtilCtrl)->_metaObject = (int)beNDMWMcUtilCtrl_GetOrCreateMetaObject();
    ((Gap::Core::igBoolMetaField *)(igMetaObject_GetFieldAt(meta, base + 6)))->setDefault(1);
    ((Gap::Core::igIntMetaField *)(igMetaObject_GetFieldAt(meta, base + 9)))->setDefault(-1);
    igMetaObject_NameFields(meta, g_beNDMWLogo_fieldTable, g_beNDMWLogo_fieldHandles, g_beNDMWLogo_fieldOffsets, base);
}

