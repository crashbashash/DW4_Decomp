igMetaObject *g_beLayerCtl_metaObject;
igMetaField *g_beLayerCtl_isOrderedMetaField;
igMetaField *g_beLayerCtl_layerSwtMetaField;

void beLayerCtl_CreateInstance(int allocator) {
    beLayerCtl_EnsureRegistered();
    igMetaObject_CreateInstance(*(int *)0x589298, allocator);
}

igMetaObject *beLayerCtl_GetOrCreateMetaObject(void) {
    if (g_beLayerCtl_metaObject == 0) {
        g_beLayerCtl_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
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
    union U u;
    int temp_s0;
    int *p;

    igObject_InitHeader(u.b);
    *(int *)&u.b[8] = 0;
    *(int *)&u.b[24] = 0;
    u.vt = (int)&g_beLayerCtl_vtable[0];
    p = (int *)&u.b[36];
    *p = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_beLayerCtl_vtable[0];
    FUN_00343260((igSmartPointer<igObject> *)p, -1);
    FUN_0033f5e0((O_33f5e0 *)u.b, (short)0);
    return temp_s0;
}

void beLayerCtl_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beLayerCtl_Register);
}

static igMetaObjectCallback g_beLayerCtl_callbackList[] = { igSwitch_EnsureRegistered, 0 };

void *beLayerCtl_Register(void) {
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
    void *meta;

    meta = (void *)g_beLayerCtl_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beLayerCtl_ctorTable, 2);
    layerSwt = (void *)(igMetaObject_GetFieldAt(meta, base + 1));
    ((igObjectRefMetaField *)layerSwt)->_metaObject = igSwitch_GetOrCreateMetaObject();
    igMetaObject_NameFields(meta, g_beLayerCtl_fieldTable, g_beLayerCtl_fieldHandles, g_beLayerCtl_fieldOffsets, base);
}

