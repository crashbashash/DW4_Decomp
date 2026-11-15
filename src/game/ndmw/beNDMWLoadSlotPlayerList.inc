igMetaObject *g_beNDMWLoadSlotPlayerList_metaObject;

igMetaObject *FUN_003c61d0(void) {
    if (g_beNDMWLoadSlotPlayerList_metaObject == 0) {
        g_beNDMWLoadSlotPlayerList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beNDMWLoadSlotPlayerList_metaObject;
}

void *beNDMWLoadSlotPlayerList_GetReadyMetaObject(void) {
    igMetaObject *g = g_beNDMWLoadSlotPlayerList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003c62b0();
    }
    return g_beNDMWLoadSlotPlayerList_metaObject;
}

int beNDMWLoadSlotPlayerList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0053cad0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_003c62b0(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadSlotPlayerList_Register);
}

static igMetaObjectCallback g_beNDMWLoadSlotPlayerList_callbackList[] = { FUN_003c6520, 0 };

void *beNDMWLoadSlotPlayerList_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWLoadSlotPlayerList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beNDMWLoadSlotPlayerList_GetMetaObject,
        "beNDMWLoadSlotPlayerList",
        0x14, /* instance size */
        beNDMWLoadSlotPlayerList_GetVTable,
        0,
        0, /* extra callback item */
        g_beNDMWLoadSlotPlayerList_callbackList /* callback list */
    );
}

void beNDMWLoadSlotPlayerList_GetMetaObject(void)
{
    beNDMWLoadSlotPlayerList_GetReadyMetaObject();
}

