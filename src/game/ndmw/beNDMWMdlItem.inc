igMetaObject *g_beNDMWMdlItem_metaObject;
igMetaField *g_beNDMWMdlItem_viewerSIManagerMetaField;
igMetaField *g_beNDMWMdlItem_lockRamListMetaField;

beNDMWMdlItem *beNDMWMdlItem_CreateInstance(int allocator) {
    beNDMWMdlItem_EnsureRegistered();
    return (beNDMWMdlItem *)igMetaObject_CreateInstance(g_beNDMWMdlItem_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beNDMWMdlItem_GetOrCreateMetaObject(void) {
    if (g_beNDMWMdlItem_metaObject == 0) {
        g_beNDMWMdlItem_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beNDMWMdlItem_metaObject;
}

igMetaObject *beNDMWMdlItem_GetReadyMetaObject(void) {
    igMetaObject *g = g_beNDMWMdlItem_metaObject;
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        beNDMWMdlItem_EnsureRegistered();
    return g_beNDMWMdlItem_metaObject;
}

int beNDMWMdlItem_GetVTable(void) {
    beNDMWMdlItem obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._infoList = 0;
    *(int **)&obj._vtable = &g_beNDMWMdlItem_vtable[0];
    obj._lockRamList = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    *(int **)&obj._vtable = &g_beNDMWMdlItem_vtable[0];
    igSmartPointer_igObjectList_Destruct((igSmartPointer<igObject> *)&obj._lockRamList, -1);
    beModelCtrl_Destroy((beModelCtrl *)&obj, 0);
    return vtable;
}

void beNDMWMdlItem_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWMdlItem_Register);
}

static igMetaObjectCallback g_beNDMWMdlItem_callbackList[] = { igViewerSceneInfoManager_EnsureRegistered, Gap::Core::igObjectList::arkRegister, 0 };

CallbackArray *beNDMWMdlItem_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWMdlItem_metaObject,
        beModelCtrl_Register,
        beModelCtrl_GetPublishedMetaObject,
        beNDMWMdlItem_GetMetaObject,
        "beNDMWMdlItem",
        0x34, /* instance size */
        beNDMWMdlItem_GetVTable,
        beNDMWMdlItem_InitFields,
        0, /* extra callback item */
        g_beNDMWMdlItem_callbackList /* callback list */
    );
}

void beNDMWMdlItem_GetMetaObject(void)
{
    beNDMWMdlItem_GetReadyMetaObject();
}

static FieldFactory g_beNDMWMdlItem_ctorTable[] = {
    igObjectRefMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beNDMWMdlItem_fieldTable[] = {
    "_viewerSIManager",
    "_lockRamList",
};
static igMetaField **g_beNDMWMdlItem_fieldHandles[] = {
    &g_beNDMWMdlItem_viewerSIManagerMetaField,
    &g_beNDMWMdlItem_lockRamListMetaField,
};
static int g_beNDMWMdlItem_fieldOffsets[] = {
    44,
    48,
};

void beNDMWMdlItem_InitFields(void) {
    int base;
    void *viewerSIManager;
    void *lockRamList;
    igMetaObject *meta;

    meta = g_beNDMWMdlItem_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNDMWMdlItem_ctorTable, 2);
    viewerSIManager = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)viewerSIManager)->_metaObject = (int)igViewerSceneInfoManager_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)viewerSIManager)->_refCounted = 0;
    lockRamList = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)lockRamList)->_metaObject = (int)Gap::Core::igObjectList::getClassTypeLazy();
    ((igRefMetaField *)lockRamList)->_construct = 1;
    igMetaObject_NameFields(meta, g_beNDMWMdlItem_fieldTable, g_beNDMWMdlItem_fieldHandles, g_beNDMWMdlItem_fieldOffsets, base);
}

