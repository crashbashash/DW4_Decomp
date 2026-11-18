igMetaObject *g_beStaticInfoCtl_metaObject;
igMetaField *g_beStaticInfoCtl_staticInfoListMetaField;

beStaticInfoCtl *beStaticInfoCtl_CreateInstance(int allocator) {
    beStaticInfoCtl_EnsureRegistered();
    return (beStaticInfoCtl *)igMetaObject_CreateInstance(g_beStaticInfoCtl_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beStaticInfoCtl_GetOrCreateMetaObject(void) {
    if (g_beStaticInfoCtl_metaObject == 0) {
        g_beStaticInfoCtl_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beStaticInfoCtl_metaObject;
}

void *beStaticInfoCtl_GetMetaObject(void) {
    igMetaObject *g = g_beStaticInfoCtl_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beStaticInfoCtl_EnsureRegistered();
    }
    return g_beStaticInfoCtl_metaObject;
}

int beStaticInfoCtl_GetVTable(void) {
    beStaticInfoCtl obj;
    int vtable;

    igObject_InitHeader(&obj);
    obj._name = 0;
    obj._infoList = 0;
    obj._vtable = (int)&g_beStaticInfoCtl_vtable[0];
    obj._staticInfoList = 0;
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beStaticInfoCtl_vtable[0];
    igSmartPointer_beBaseInfoList_Destruct((igSmartPointer<igObject> *)&obj._staticInfoList, -1);
    beBaseInfoManager_Destroy((beBaseInfoManager *)&obj, (short)0);
    return vtable;
}

void beStaticInfoCtl_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beStaticInfoCtl_Register);
}

static igMetaObjectCallback g_beStaticInfoCtl_callbackList[] = { beBaseInfoList_EnsureRegistered, 0 };

CallbackArray *beStaticInfoCtl_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beStaticInfoCtl_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beStaticInfoCtl_GetMetaObjectFunction,
        "beStaticInfoCtl",
        0x24, /* instance size */
        beStaticInfoCtl_GetVTable,
        beStaticInfoCtl_InitFields,
        0, /* extra callback item */
        g_beStaticInfoCtl_callbackList /* callback list */
    );
}

void beStaticInfoCtl_GetMetaObjectFunction(void)
{
    beStaticInfoCtl_GetMetaObject();
}

static FieldFactory g_beStaticInfoCtl_ctorTable[] = {
    igObjectRefMetaField_Create,
};
static const char *g_beStaticInfoCtl_fieldTable[] = {
    "_staticInfoList",
};
static igMetaField **g_beStaticInfoCtl_fieldHandles[] = {
    &g_beStaticInfoCtl_staticInfoListMetaField,
};
static int g_beStaticInfoCtl_fieldOffsets[] = {
    32,
};

void beStaticInfoCtl_InitFields(void) {
    int base;
    void *staticInfoList;
    igMetaObject *meta;

    meta = g_beStaticInfoCtl_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beStaticInfoCtl_ctorTable, 1);
    staticInfoList = (void *)(igMetaObject_GetFieldAt(meta, base));
    ((igObjectRefMetaField *)staticInfoList)->_metaObject = (int)beBaseInfoList_GetOrCreateMetaObject();
    ((igRefMetaField *)staticInfoList)->_construct = 1;
    igMetaObject_NameFields(meta, g_beStaticInfoCtl_fieldTable, g_beStaticInfoCtl_fieldHandles, g_beStaticInfoCtl_fieldOffsets, base);
}

