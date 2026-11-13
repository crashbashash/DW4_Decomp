void beNDMWItemDisk_Create(int arg0) {
    FUN_003c86d0();
    igMetaObject_CreateInstance(*(int *)0x58BF38, arg0);
}

igMetaObject *FUN_003c85f0(void) {
    if (g_beNDMWItemDisk_metaObject[0] == 0) {
        g_beNDMWItemDisk_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_beNDMWItemDisk_metaObject[0];
}

void *beNDMWItemDisk_GetReadyMetaObject(void) {
    igMetaObject *g = g_beNDMWItemDisk_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003c86d0();
    }
    return g_beNDMWItemDisk_metaObject[0];
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
        g_beNDMWItemDisk_metaObject,
        beNDMWItemBase_Register,
        beNDMWItemBase_GetPublishedMetaObject,
        beNDMWItemDisk_GetMetaObject,
        beNDMWItemDisk_className,
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

void beNDMWItemDisk_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beNDMWItemDisk_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beNDMWItemDisk_ctorTable[0], 1);
    igMetaObject_NameFields(temp_s0, &g_beNDMWItemDisk_fieldTable[0], &DAT_004cc0d8[0], &DAT_004cc0e0[0], temp_s1);
}

