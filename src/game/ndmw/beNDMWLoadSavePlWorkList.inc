igMetaObject *g_beNDMWLoadSavePlWorkList_metaObject;

igMetaObject *FUN_003c5520(void) {
    if (g_beNDMWLoadSavePlWorkList_metaObject == 0) {
        g_beNDMWLoadSavePlWorkList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beNDMWLoadSavePlWorkList_metaObject;
}

void *beNDMWLoadSavePlWorkList_ResolveMetaObject(void) {
    igMetaObject *g = g_beNDMWLoadSavePlWorkList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003c5600();
    }
    return g_beNDMWLoadSavePlWorkList_metaObject;
}

int beNDMWLoadSavePlWorkList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0053cd30[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_003c5600(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadSavePlWorkList_Register);
}

static igMetaObjectCallback g_beNDMWLoadSavePlWorkList_callbackList[] = { FUN_003c5780, 0 };

void *beNDMWLoadSavePlWorkList_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWLoadSavePlWorkList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beNDMWLoadSavePlWorkList_GetMetaObject,
        "beNDMWLoadSavePlWorkList",
        0x14, /* instance size */
        beNDMWLoadSavePlWorkList_GetVTable,
        0,
        0, /* extra callback item */
        g_beNDMWLoadSavePlWorkList_callbackList /* callback list */
    );
}

void beNDMWLoadSavePlWorkList_GetMetaObject(void)
{
    beNDMWLoadSavePlWorkList_ResolveMetaObject();
}

