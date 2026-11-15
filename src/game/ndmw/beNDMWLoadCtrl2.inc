igMetaObject *g_beNDMWLoadCtrl2_metaObject;
igMetaField *g_beNDMWLoadCtrl2_padManagerMetaField;
igMetaField *g_beNDMWLoadCtrl2_cameraModeMetaField;
igMetaField *g_beNDMWLoadCtrl2_lightModeMetaField;

void beNDMWLoadCtrl2_CreateInstance(int arg0) {
    FUN_003c7ef0();
    igMetaObject_CreateInstance(g_beNDMWLoadCtrl2_metaObject, arg0);
}

igMetaObject *FUN_003c7de0(void) {
    if (g_beNDMWLoadCtrl2_metaObject == 0) {
        g_beNDMWLoadCtrl2_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beNDMWLoadCtrl2_metaObject;
}

igMetaObject *beNDMWLoadCtrl2_GetReadyMetaObject(void)
{
    igMetaObject *g = g_beNDMWLoadCtrl2_metaObject;
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_003c7ef0();
    return g_beNDMWLoadCtrl2_metaObject;
}

int beNDMWLoadCtrl2_GetVTable(void) {
    struct Obj_3c7e80 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.w[1] = 0;
    obj.w[5] = 0;
    obj.vt = &DAT_0053e900[0];
    obj.w[7] = 0;
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_0053e900[0];
    FUN_0033dda0(&obj.w[7], -1);
    FUN_0033f5e0(&obj, 0);
    return r;
}

void FUN_003c7ef0(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadCtrl2_Register);
}

static igMetaObjectCallback g_beNDMWLoadCtrl2_callbackList[] = { FUN_0034cb30, 0 };

void *beNDMWLoadCtrl2_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWLoadCtrl2_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beNDMWLoadCtrl2_GetMetaObject,
        "beNDMWLoadCtrl2",
        0x2c, /* instance size */
        beNDMWLoadCtrl2_GetVTable,
        beNDMWLoadCtrl2_InitFields,
        0, /* extra callback item */
        g_beNDMWLoadCtrl2_callbackList /* callback list */
    );
}

void beNDMWLoadCtrl2_GetMetaObject(void)
{
    beNDMWLoadCtrl2_GetReadyMetaObject();
}

static FieldFactory g_beNDMWLoadCtrl2_ctorTable[] = {
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beNDMWLoadCtrl2_fieldTable[] = {
    "_padManager",
    "_cameraMode",
    "_lightMode",
};
static igMetaField **g_beNDMWLoadCtrl2_fieldHandles[] = {
    &g_beNDMWLoadCtrl2_padManagerMetaField,
    &g_beNDMWLoadCtrl2_cameraModeMetaField,
    &g_beNDMWLoadCtrl2_lightModeMetaField,
};
static int g_beNDMWLoadCtrl2_fieldOffsets[] = {
    32,
    36,
    40,
};

void beNDMWLoadCtrl2_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_beNDMWLoadCtrl2_metaObject;
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beNDMWLoadCtrl2_ctorTable, 3);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_0034c8e0();
    igMetaObject_NameFields(temp_s0, g_beNDMWLoadCtrl2_fieldTable, g_beNDMWLoadCtrl2_fieldHandles, g_beNDMWLoadCtrl2_fieldOffsets, temp_s2);
}

