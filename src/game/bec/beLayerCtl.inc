igMetaObject *g_beLayerCtl_metaObject;
igMetaField *g_beLayerCtl_isOrderedMetaField;
igMetaField *g_beLayerCtl_layerSwtMetaField;

beLayerCtl *beLayerCtl_CreateInstance(int allocator) {
    beLayerCtl_EnsureRegistered();
    return (beLayerCtl *)igMetaObject_CreateInstance(g_beLayerCtl_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beLayerCtl_GetOrCreateMetaObject(void) {
    if (g_beLayerCtl_metaObject == 0) {
        g_beLayerCtl_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beLayerCtl_metaObject;
}

void *beLayerCtl_GetMetaObject(void) {
    igMetaObject *g = g_beLayerCtl_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beLayerCtl_EnsureRegistered();
    }
    return g_beLayerCtl_metaObject;
}

int beLayerCtl_GetVTable(void) {
    beLayerCtl obj;
    int vtable;
    int *layerSwtSlot;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._infoList = 0;
    obj._vtable = (int)&g_beLayerCtl_vtable[0];
    layerSwtSlot = (int *)&obj._layerSwt;
    *layerSwtSlot = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beLayerCtl_vtable[0];
    igSmartPointer_igSwitch_Destruct((igSmartPointer<igObject> *)layerSwtSlot, -1);
    beBaseInfoManager_Destroy((beBaseInfoManager *)&obj, (short)0);
    return vtable;
}

void beLayerCtl_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beLayerCtl_Register);
}

static igMetaObjectCallback g_beLayerCtl_callbackList[] = { igSwitch_EnsureRegistered, 0 };

CallbackArray *beLayerCtl_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beLayerCtl_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beLayerCtl_GetMetaObjectFunction,
        "beLayerCtl",
        0x28, /* instance size */
        beLayerCtl_GetVTable,
        beLayerCtl_InitFields,
        0, /* extra callback item */
        g_beLayerCtl_callbackList /* callback list */
    );
}

void beLayerCtl_GetMetaObjectFunction(void)
{
    beLayerCtl_GetMetaObject();
}

static FieldFactory g_beLayerCtl_ctorTable[] = {
    igBoolMetaField_Create,
    igObjectRefMetaField_Create,
};
static const char *g_beLayerCtl_fieldTable[] = {
    "_isOrdered",
    "_layerSwt",
};
static igMetaField **g_beLayerCtl_fieldHandles[] = {
    &g_beLayerCtl_isOrderedMetaField,
    &g_beLayerCtl_layerSwtMetaField,
};
static int g_beLayerCtl_fieldOffsets[] = {
    32,
    36,
};

void beLayerCtl_InitFields(void) {
    int base;
    void *layerSwt;
    igMetaObject *meta;

    meta = g_beLayerCtl_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beLayerCtl_ctorTable, 2);
    layerSwt = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)layerSwt)->_metaObject = (int)igSwitch_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beLayerCtl_fieldTable, g_beLayerCtl_fieldHandles, g_beLayerCtl_fieldOffsets, base);
}

