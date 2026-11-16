igMetaObject *g_beNDMWPanelWaza_metaObject;
igMetaField *g_beNDMWPanelWaza_padManagerMetaField;

void beNDMWPanelWaza_CreateInstance(int allocator) {
    beNDMWPanelWaza_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWPanelWaza_metaObject, allocator);
}

igMetaObject *beNDMWPanelWaza_GetOrCreateMetaObject(void) {
    if (g_beNDMWPanelWaza_metaObject == 0) {
        g_beNDMWPanelWaza_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beNDMWPanelWaza_metaObject;
}

void *beNDMWPanelWaza_ResolveMetaObject(void) {
    igMetaObject *g = g_beNDMWPanelWaza_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWPanelWaza_EnsureRegistered();
    }
    return g_beNDMWPanelWaza_metaObject;
}

int beNDMWPanelWaza_GetVTable(void) {
    beNDMWPanelWaza obj;
    int vtable;
    int *nameRef;
    int *infoListRef;

    igObject_InitHeader(&obj);
    *(int **)&obj._vtable = &g_beBaseInfoManager_vtable[0];
    nameRef = &obj._name;
    *nameRef = 0;
    infoListRef = &obj._infoList;
    *infoListRef = 0;
    *(int **)&obj._vtable = &g_beNDMWPanelWaza_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    *(int **)&obj._vtable = &g_beBaseInfoManager_vtable[0];
    if (infoListRef != 0) {
        igRelease((igObject *)*infoListRef);
    }
    *(int **)&obj._vtable = &g_igNamedObject_vtable[0];
    if (nameRef != 0) {
        releaseString((const char *)*nameRef);
    }
    return vtable;
}

void beNDMWPanelWaza_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWPanelWaza_Register);
}

static igMetaObjectCallback g_beNDMWPanelWaza_callbackList[] = { bePadManager_EnsureRegistered, 0 };

void *beNDMWPanelWaza_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWPanelWaza_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beNDMWPanelWaza_GetMetaObject,
        "beNDMWPanelWaza",
        0x24, /* instance size */
        beNDMWPanelWaza_GetVTable,
        beNDMWPanelWaza_InitFields,
        0, /* extra callback item */
        g_beNDMWPanelWaza_callbackList /* callback list */
    );
}

void beNDMWPanelWaza_GetMetaObject(void)
{
    beNDMWPanelWaza_ResolveMetaObject();
}

static FieldFactory g_beNDMWPanelWaza_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beNDMWPanelWaza_fieldTable[] = {
    "_padManager",
};
static igMetaField **g_beNDMWPanelWaza_fieldHandles[] = {
    &g_beNDMWPanelWaza_padManagerMetaField,
};
static int g_beNDMWPanelWaza_fieldOffsets[] = {
    32,
};

void beNDMWPanelWaza_InitFields(void) {
    int base;
    void *padManager;
    igMetaObject *meta;

    meta = g_beNDMWPanelWaza_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNDMWPanelWaza_ctorTable, 1);
    padManager = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)padManager)->_metaObject = bePadManager_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)padManager)->_refCounted = 0;
    igMetaObject_NameFields(meta, g_beNDMWPanelWaza_fieldTable, g_beNDMWPanelWaza_fieldHandles, g_beNDMWPanelWaza_fieldOffsets, base);
}

