igMetaObject *g_beNDMWSaveCtrl_metaObject;
igMetaField *g_beNDMWSaveCtrl_padManagerMetaField;

beNDMWSaveCtrl *beNDMWSaveCtrl_CreateInstance(int allocator) {
    beNDMWSaveCtrl_EnsureRegistered();
    return (beNDMWSaveCtrl *)igMetaObject_CreateInstance(g_beNDMWSaveCtrl_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beNDMWSaveCtrl_GetOrCreateMetaObject(void) {
    if (g_beNDMWSaveCtrl_metaObject == 0) {
        g_beNDMWSaveCtrl_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beNDMWSaveCtrl_metaObject;
}

void *beNDMWSaveCtrl_ResolveMetaObject(void) {
    igMetaObject *g = g_beNDMWSaveCtrl_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWSaveCtrl_EnsureRegistered();
    }
    return g_beNDMWSaveCtrl_metaObject;
}

int beNDMWSaveCtrl_GetVTable(void) {
    beNDMWSaveCtrl obj;
    int vtable;
    int *padManagerRef;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._infoList = 0;
    *(int **)&obj._vtable = &g_beNDMWSaveCtrl_vtable[0];
    padManagerRef = &obj._padManager;
    *padManagerRef = 0;
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem) + 916));
    *(int **)&obj._vtable = &g_beNDMWSaveCtrl_vtable[0];
    igSmartPointer_bePadManager_Destruct((igSmartPointer<igObject> *)padManagerRef, -1);
    beBaseInfoManager_Destroy((beBaseInfoManager *)&obj, 0);
    return vtable;
}

void beNDMWSaveCtrl_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWSaveCtrl_Register);
}

static igMetaObjectCallback g_beNDMWSaveCtrl_callbackList[] = { bePadManager_EnsureRegistered, 0 };

CallbackArray *beNDMWSaveCtrl_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWSaveCtrl_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beNDMWSaveCtrl_GetMetaObject,
        "beNDMWSaveCtrl",
        0x24, /* instance size */
        beNDMWSaveCtrl_GetVTable,
        beNDMWSaveCtrl_InitFields,
        0, /* extra callback item */
        g_beNDMWSaveCtrl_callbackList /* callback list */
    );
}

void beNDMWSaveCtrl_GetMetaObject(void)
{
    beNDMWSaveCtrl_ResolveMetaObject();
}

static FieldFactory g_beNDMWSaveCtrl_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beNDMWSaveCtrl_fieldTable[] = {
    "_padManager",
};
static igMetaField **g_beNDMWSaveCtrl_fieldHandles[] = {
    &g_beNDMWSaveCtrl_padManagerMetaField,
};
static int g_beNDMWSaveCtrl_fieldOffsets[] = {
    32,
};

void beNDMWSaveCtrl_InitFields(void) {
    int base;
    void *padManager;
    igMetaObject *meta;

    meta = g_beNDMWSaveCtrl_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNDMWSaveCtrl_ctorTable, 1);
    padManager = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)padManager)->_metaObject = (int)bePadManager_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beNDMWSaveCtrl_fieldTable, g_beNDMWSaveCtrl_fieldHandles, g_beNDMWSaveCtrl_fieldOffsets, base);
}

