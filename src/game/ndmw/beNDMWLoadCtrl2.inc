igMetaObject *g_beNDMWLoadCtrl2_metaObject;
igMetaField *g_beNDMWLoadCtrl2_padManagerMetaField;
igMetaField *g_beNDMWLoadCtrl2_cameraModeMetaField;
igMetaField *g_beNDMWLoadCtrl2_lightModeMetaField;

beNDMWLoadCtrl2 *beNDMWLoadCtrl2_CreateInstance(int allocator) {
    beNDMWLoadCtrl2_EnsureRegistered();
    return (beNDMWLoadCtrl2 *)igMetaObject_CreateInstance(g_beNDMWLoadCtrl2_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beNDMWLoadCtrl2_GetOrCreateMetaObject(void) {
    if (g_beNDMWLoadCtrl2_metaObject == 0) {
        g_beNDMWLoadCtrl2_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beNDMWLoadCtrl2_metaObject;
}

igMetaObject *beNDMWLoadCtrl2_GetReadyMetaObject(void)
{
    igMetaObject *g = g_beNDMWLoadCtrl2_metaObject;
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        beNDMWLoadCtrl2_EnsureRegistered();
    return g_beNDMWLoadCtrl2_metaObject;
}

int beNDMWLoadCtrl2_GetVTable(void) {
    beNDMWLoadCtrl2 obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._infoList = 0;
    *(int **)&obj._vtable = &g_beNDMWLoadCtrl2_vtable[0];
    obj._padManager = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem) + 916));
    *(int **)&obj._vtable = &g_beNDMWLoadCtrl2_vtable[0];
    igSmartPointer_bePadManager_Destruct(&obj._padManager, -1);
    beBaseInfoManager_Destroy((beBaseInfoManager *)&obj, 0);
    return vtable;
}

void beNDMWLoadCtrl2_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadCtrl2_Register);
}

static igMetaObjectCallback g_beNDMWLoadCtrl2_callbackList[] = { bePadManager_EnsureRegistered, 0 };

CallbackArray *beNDMWLoadCtrl2_Register(void) {
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
    int base;
    void *padManager;
    igMetaObject *meta;

    meta = g_beNDMWLoadCtrl2_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNDMWLoadCtrl2_ctorTable, 3);
    padManager = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)padManager)->_metaObject = (int)bePadManager_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beNDMWLoadCtrl2_fieldTable, g_beNDMWLoadCtrl2_fieldHandles, g_beNDMWLoadCtrl2_fieldOffsets, base);
}

