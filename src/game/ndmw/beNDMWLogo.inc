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

void beNDMWLogo_CreateInstance(int arg0) {
    beNDMWLogo_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWLogo_metaObject, arg0);
}

igMetaObject *beNDMWLogo_GetOrCreateMetaObject(void) {
    if (g_beNDMWLogo_metaObject == 0) {
        g_beNDMWLogo_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
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
    struct Obj_3c2420 obj;
    int temp_s0;

    igObject_InitHeader(&obj);
    obj.f8 = 0;
    obj.f18 = 0;
    obj.vt = (&g_beNDMWLogo_vtable[0]);
    obj.f28 = 0;
    temp_s0 = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = (&g_beNDMWLogo_vtable[0]);
    FUN_003b2a10((ObjectRefWord *)&obj.f28, -1);
    FUN_0033f5e0(&obj, 0);
    return temp_s0;
}

void beNDMWLogo_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWLogo_Register);
}

static igMetaObjectCallback g_beNDMWLogo_callbackList[] = { bePadManager_EnsureRegistered, beSystem_EnsureRegistered, beNDMWMcUtilCtrl_EnsureRegistered, 0 };

void *beNDMWLogo_Register(void) {
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
    int temp_s2;
    void *temp_s1_3;
    void *temp_s1_2;
    void *temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_beNDMWLogo_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beNDMWLogo_ctorTable, 0xB);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = bePadManager_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = beSystem_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)temp_s1_2)->_refCounted = 0;
    temp_s1_3 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 2));
    ((igObjectRefMetaField *)temp_s1_3)->_metaObject = (int)beNDMWMcUtilCtrl_GetOrCreateMetaObject();
    igBoolMetaField_SetDefaultValue(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 6), 1);
    igIntMetaField_SetDefault(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 9), -1);
    igMetaObject_NameFields(temp_s0, g_beNDMWLogo_fieldTable, g_beNDMWLogo_fieldHandles, g_beNDMWLogo_fieldOffsets, temp_s2);
}

