igMetaObject *g_beNDMWStatus_metaObject;
igMetaField *g_beNDMWStatus_windowProMetaField;
igMetaField *g_beNDMWStatus_whoGenerateMetaField;
igMetaField *g_beNDMWStatus_subWndNoMetaField;

beNDMWStatus *beNDMWStatus_CreateInstance(int allocator) {
    beNDMWStatus_EnsureRegistered();
    return (beNDMWStatus *)igMetaObject_CreateInstance(g_beNDMWStatus_metaObject, allocator);
}

igMetaObject *beNDMWStatus_GetOrCreateMetaObject(void) {
    if (g_beNDMWStatus_metaObject == 0) {
        g_beNDMWStatus_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beNDMWStatus_metaObject;
}

void *beNDMWStatus_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWStatus_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWStatus_EnsureRegistered();
    }
    return g_beNDMWStatus_metaObject;
}

int beNDMWStatus_GetVTable(void) {
    beNDMWStatus obj;
    int vtable;
    int *windowProRef;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._infoList = 0;
    *(int **)&obj._vtable = &g_beNDMWStatus_vtable[0];
    windowProRef = &obj._windowPro;
    *windowProRef = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    *(int **)&obj._vtable = &g_beNDMWStatus_vtable[0];
    beNDMWWindow_igSmartPointer_beNDMWWindow_Destruct((igSmartPointer<igObject> *)windowProRef, -1);
    beBaseInfoManager_Destroy(&obj, 0);
    return vtable;
}

void beNDMWStatus_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWStatus_Register);
}

static igMetaObjectCallback g_beNDMWStatus_callbackList[] = { beNDMWWindow_EnsureRegistered, 0 };

void *beNDMWStatus_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWStatus_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beNDMWStatus_GetMetaObjectFunction,
        "beNDMWStatus",
        0x2c, /* instance size */
        beNDMWStatus_GetVTable,
        beNDMWStatus_InitFields,
        0, /* extra callback item */
        g_beNDMWStatus_callbackList /* callback list */
    );
}

void beNDMWStatus_GetMetaObjectFunction(void)
{
    beNDMWStatus_GetMetaObject();
}

static FieldFactory g_beNDMWStatus_ctorTable[] = {
    igObjectRefMetaField_Create,
    igIntMetaField_Create,
    igIntMetaField_Create,
};
static const char *g_beNDMWStatus_fieldTable[] = {
    "_windowPro",
    "_whoGenerate",
    "_subWndNo",
};
static igMetaField **g_beNDMWStatus_fieldHandles[] = {
    &g_beNDMWStatus_windowProMetaField,
    &g_beNDMWStatus_whoGenerateMetaField,
    &g_beNDMWStatus_subWndNoMetaField,
};
static int g_beNDMWStatus_fieldOffsets[] = {
    32,
    36,
    40,
};

void beNDMWStatus_InitFields(void) {
    int base;
    void *windowPro;
    igMetaObject *meta;

    meta = g_beNDMWStatus_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNDMWStatus_ctorTable, 3);
    windowPro = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)windowPro)->_metaObject = (int)beNDMWWindow_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beNDMWStatus_fieldTable, g_beNDMWStatus_fieldHandles, g_beNDMWStatus_fieldOffsets, base);
}

