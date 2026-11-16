igMetaObject *g_beNDMWStageCtl_metaObject;
igMetaField *g_beNDMWStageCtl_resetTrgTimeMetaField;

beNDMWStageCtl *beNDMWStageCtl_CreateInstance(int allocator) {
    beNDMWStageCtl_EnsureRegistered();
    return (beNDMWStageCtl *)igMetaObject_CreateInstance(g_beNDMWStageCtl_metaObject, allocator);
}

igMetaObject *beNDMWStageCtl_GetOrCreateMetaObject(void) {
    if (g_beNDMWStageCtl_metaObject == 0) {
        g_beNDMWStageCtl_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beNDMWStageCtl_metaObject;
}

igMetaObject *beNDMWStageCtl_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWStageCtl_metaObject;
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        beNDMWStageCtl_EnsureRegistered();
    return g_beNDMWStageCtl_metaObject;
}

int beNDMWStageCtl_GetVTable(void) {
    beNDMWStageCtl obj;
    int vtable;

    igObject_InitHeader(&obj);
    *(int **)&obj._vtable = &g_beBaseInfoManager_vtable[0];
    obj._name = 0;
    obj._infoList = 0;
    *(int **)&obj._vtable = &g_beNDMWStageCtl_vtable[0];
    vtable = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    *(int **)&obj._vtable = &g_beBaseInfoManager_vtable[0];
    if (&obj._infoList != 0) {
        igRelease((igObject *)obj._infoList);
    }
    *(int **)&obj._vtable = &g_igNamedObject_vtable[0];
    if (&obj._name != 0) {
        releaseString((const char *)obj._name);
    }
    return vtable;
}

void beNDMWStageCtl_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWStageCtl_Register);
}

void *beNDMWStageCtl_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWStageCtl_metaObject,
        beBaseInfoManager_Register,
        beBaseInfoManager_GetPublishedMetaObject,
        beNDMWStageCtl_GetMetaObjectFunction,
        "beNDMWStageCtl",
        0x28, /* instance size */
        beNDMWStageCtl_GetVTable,
        beNDMWStageCtl_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWStageCtl_GetMetaObjectFunction(void)
{
    beNDMWStageCtl_GetMetaObject();
}

static FieldFactory g_beNDMWStageCtl_ctorTable[] = {
    igLongMetaField_Create,
};
static const char *g_beNDMWStageCtl_fieldTable[] = {
    "_resetTrgTime",
};
static igMetaField **g_beNDMWStageCtl_fieldHandles[] = {
    &g_beNDMWStageCtl_resetTrgTimeMetaField,
};
static int g_beNDMWStageCtl_fieldOffsets[] = {
    32,
};

void beNDMWStageCtl_InitFields(void) {
    int base;
    igMetaObject *meta;

    meta = g_beNDMWStageCtl_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNDMWStageCtl_ctorTable, 1);
    igMetaObject_NameFields(meta, g_beNDMWStageCtl_fieldTable, g_beNDMWStageCtl_fieldHandles, g_beNDMWStageCtl_fieldOffsets, base);
}

