igMetaObject *g_beNDMWLoadIntf2_metaObject;
igMetaField *g_beNDMWLoadIntf2_padManagerMetaField;
igMetaField *g_beNDMWLoadIntf2_systemMetaField;
igMetaField *g_beNDMWLoadIntf2_kindHardMetaField;
igMetaField *g_beNDMWLoadIntf2_difficultMaxMetaField;

void beNDMWLoadIntf2_CreateInstance(int arg0) {
    FUN_003c4850();
    igMetaObject_CreateInstance(g_beNDMWLoadIntf2_metaObject, arg0);
}

igMetaObject *FUN_003c4740(void) {
    if (g_beNDMWLoadIntf2_metaObject == 0) {
        g_beNDMWLoadIntf2_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beNDMWLoadIntf2_metaObject;
}

void *beNDMWLoadIntf2_ResolveMetaObject(void) {
    igMetaObject *g = g_beNDMWLoadIntf2_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003c4850();
    }
    return g_beNDMWLoadIntf2_metaObject;
}

int beNDMWLoadIntf2_GetVTable(void) {
    struct Obj_3c47e0 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.w[1] = 0;
    obj.w[5] = 0;
    obj.vt = &DAT_0053e860[0];
    obj.w[8] = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_0053e860[0];
    FUN_0033dda0(&obj.w[8], -1);
    FUN_0033f5e0(&obj, 0);
    return r;
}

void FUN_003c4850(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadIntf2_Register);
}

static igMetaObjectCallback g_beNDMWLoadIntf2_callbackList[] = { FUN_0034cb30, FUN_00342f30, 0 };

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
    int temp_s2;
    void *temp_s1_2;
    void *temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_beNDMWLoadIntf2_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beNDMWLoadIntf2_ctorTable, 4);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0034c8e0();
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = FUN_00342ce0();
    ((igObjectRefMetaField *)temp_s1_2)->_refCounted = 0;
    igMetaObject_NameFields(temp_s0, g_beNDMWLoadIntf2_fieldTable, g_beNDMWLoadIntf2_fieldHandles, g_beNDMWLoadIntf2_fieldOffsets, temp_s2);
}

