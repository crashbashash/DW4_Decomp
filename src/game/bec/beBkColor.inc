igMetaObject *g_beBkColor_metaObject;
igMetaField *g_beBkColor_isClearMetaField;

beBkColor *beBkColor_CreateInstance(int allocator) {
    beBkColor_EnsureRegistered();
    return (beBkColor *)igMetaObject_CreateInstance(g_beBkColor_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beBkColor_GetOrCreateMetaObject(void) {
    if (g_beBkColor_metaObject == 0) {
        g_beBkColor_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beBkColor_metaObject;
}

void *beBkColor_GetMetaObject(void) {
    igMetaObject *g = g_beBkColor_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beBkColor_EnsureRegistered();
    }
    return g_beBkColor_metaObject;
}

int beBkColor_GetVTable(void) {
    beBkColor obj;
    int vtable;
    igObject **infoListSlot;
    char **nameSlot;

    igObject_InitHeader(&obj);
    nameSlot = (char **)&obj._name;
    *nameSlot = 0;
    obj._vtable = (int)&g_beBaseInfoManager_vtable[0];
    infoListSlot = (igObject **)&obj._infoList;
    *infoListSlot = 0;
    obj._vtable = (int)&g_beBkColor_vtable[0];
    vtable = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_beBaseInfoManager_vtable[0];
    igObjectRef_Release(infoListSlot);
    obj._vtable = (int)&g_igNamedObject_vtable[0];
    igStringRef_Release(nameSlot);
    return vtable;
}

void beBkColor_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beBkColor_Register);
}

CallbackArray *beBkColor_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beBkColor_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beBkColor_GetMetaObjectFunction,
        "beBkColor",
        0x24, /* instance size */
        beBkColor_GetVTable,
        beBkColor_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beBkColor_GetMetaObjectFunction(void)
{
    beBkColor_GetMetaObject();
}

static FieldFactory g_beBkColor_ctorTable[] = {
    igBoolMetaField_Create,
};
static const char *g_beBkColor_fieldTable[] = {
    "_isClear",
};
static igMetaField **g_beBkColor_fieldHandles[] = {
    &g_beBkColor_isClearMetaField,
};
static int g_beBkColor_fieldOffsets[] = {
    32,
};

void beBkColor_InitFields(void) {
    int base;
    igMetaObject *meta;

    meta = g_beBkColor_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beBkColor_ctorTable, 1);
    igMetaObject_NameFields(meta, g_beBkColor_fieldTable, g_beBkColor_fieldHandles, g_beBkColor_fieldOffsets, base);
}

