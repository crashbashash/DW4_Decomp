igMetaObject *g_beNDMWLoadSlotPlayerList_metaObject;

igMetaObject *beNDMWLoadSlotPlayerList_GetOrCreateMetaObject(void) {
    if (g_beNDMWLoadSlotPlayerList_metaObject == 0) {
        g_beNDMWLoadSlotPlayerList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beNDMWLoadSlotPlayerList_metaObject;
}

void *beNDMWLoadSlotPlayerList_GetReadyMetaObject(void) {
    igMetaObject *g = g_beNDMWLoadSlotPlayerList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWLoadSlotPlayerList_EnsureRegistered();
    }
    return g_beNDMWLoadSlotPlayerList_metaObject;
}

int beNDMWLoadSlotPlayerList_GetVTable(void) {
    beNDMWLoadSlotPlayerList obj;

    igObject_InitHeader(&obj);
    *(int **)&obj._vtable = &g_beNDMWLoadSlotPlayerList_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void beNDMWLoadSlotPlayerList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWLoadSlotPlayerList_Register);
}

static igMetaObjectCallback g_beNDMWLoadSlotPlayerList_callbackList[] = { beNDMWLoadSlotPlayer_EnsureRegistered, 0 };

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

