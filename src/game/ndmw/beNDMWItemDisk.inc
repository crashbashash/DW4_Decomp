igMetaObject *g_beNDMWItemDisk_metaObject;
igMetaField *g_beNDMWItemDisk_kazuMetaField;

beNDMWItemDisk *beNDMWItemDisk_Create(int allocator) {
    beNDMWItemDisk_EnsureRegistered();
    return (beNDMWItemDisk *)igMetaObject_CreateInstance(g_beNDMWItemDisk_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *beNDMWItemDisk_GetOrCreateMetaObject(void) {
    if (g_beNDMWItemDisk_metaObject == 0) {
        g_beNDMWItemDisk_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beNDMWItemDisk_metaObject;
}

void *beNDMWItemDisk_GetReadyMetaObject(void) {
    igMetaObject *g = g_beNDMWItemDisk_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWItemDisk_EnsureRegistered();
    }
    return g_beNDMWItemDisk_metaObject;
}

int beNDMWItemDisk_GetVTable(void) {
    beNDMWItemDisk obj;

    igObject_InitHeader(&obj);
    *(int **)&obj._vtable = &g_beNDMWItemDisk_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void beNDMWItemDisk_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWItemDisk_Register);
}

CallbackArray *beNDMWItemDisk_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWItemDisk_metaObject,
        beNDMWItemBase_Register,
        beNDMWItemBase_GetPublishedMetaObject,
        beNDMWItemDisk_GetMetaObject,
        "beNDMWItemDisk",
        0x18, /* instance size */
        beNDMWItemDisk_GetVTable,
        beNDMWItemDisk_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWItemDisk_GetMetaObject(void)
{
    beNDMWItemDisk_GetReadyMetaObject();
}

static FieldFactory g_beNDMWItemDisk_ctorTable[] = {
    igIntMetaField_Create,
};
static const char *g_beNDMWItemDisk_fieldTable[] = {
    "_kazu",
};
static igMetaField **g_beNDMWItemDisk_fieldHandles[] = {
    &g_beNDMWItemDisk_kazuMetaField,
};
static int g_beNDMWItemDisk_fieldOffsets[] = {
    20,
};

void beNDMWItemDisk_InitFields(void) {
    int base;
    igMetaObject *meta;

    meta = g_beNDMWItemDisk_metaObject;
    base = igMetaObject_GetFieldCount(meta);
    igMetaObject_CreateFields(meta, g_beNDMWItemDisk_ctorTable, 1);
    igMetaObject_NameFields(meta, g_beNDMWItemDisk_fieldTable, g_beNDMWItemDisk_fieldHandles, g_beNDMWItemDisk_fieldOffsets, base);
}

