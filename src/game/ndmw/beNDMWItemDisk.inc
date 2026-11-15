igMetaObject *g_beNDMWItemDisk_metaObject;
igMetaField *g_beNDMWItemDisk_kazuMetaField;

void beNDMWItemDisk_Create(int arg0) {
    FUN_003c86d0();
    igMetaObject_CreateInstance(g_beNDMWItemDisk_metaObject, arg0);
}

igMetaObject *FUN_003c85f0(void) {
    if (g_beNDMWItemDisk_metaObject == 0) {
        g_beNDMWItemDisk_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beNDMWItemDisk_metaObject;
}

void *beNDMWItemDisk_GetReadyMetaObject(void) {
    igMetaObject *g = g_beNDMWItemDisk_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003c86d0();
    }
    return g_beNDMWItemDisk_metaObject;
}

int beNDMWItemDisk_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_005407a0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_003c86d0(void)
{
    igMetaObject_RunStaticInit(beNDMWItemDisk_Register);
}

void *beNDMWItemDisk_Register(void) {
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
    int temp_s1;
    igMetaObject *temp_s0;

    temp_s0 = g_beNDMWItemDisk_metaObject;
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, g_beNDMWItemDisk_ctorTable, 1);
    igMetaObject_NameFields(temp_s0, g_beNDMWItemDisk_fieldTable, g_beNDMWItemDisk_fieldHandles, g_beNDMWItemDisk_fieldOffsets, temp_s1);
}

