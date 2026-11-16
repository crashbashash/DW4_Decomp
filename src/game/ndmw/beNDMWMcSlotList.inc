igMetaObject *g_beNDMWMcSlotList_metaObject;

igMetaObject *beNDMWMcSlotList_GetOrCreateMetaObject(void) {
    if (g_beNDMWMcSlotList_metaObject == 0) {
        g_beNDMWMcSlotList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beNDMWMcSlotList_metaObject;
}

void *beNDMWMcSlotList_GetReadyMetaObject(void) {
    igMetaObject *g = g_beNDMWMcSlotList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWMcSlotList_EnsureRegistered();
    }
    return g_beNDMWMcSlotList_metaObject;
}

int beNDMWMcSlotList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &g_beNDMWMcSlotList_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void beNDMWMcSlotList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWMcSlotList_Register);
}

static igMetaObjectCallback g_beNDMWMcSlotList_callbackList[] = { beNDMWMcSlot_EnsureRegistered, 0 };

void *beNDMWMcSlotList_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWMcSlotList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beNDMWMcSlotList_GetMetaObject,
        "beNDMWMcSlotList",
        0x14, /* instance size */
        beNDMWMcSlotList_GetVTable,
        0,
        0, /* extra callback item */
        g_beNDMWMcSlotList_callbackList /* callback list */
    );
}

void beNDMWMcSlotList_GetMetaObject(void)
{
    beNDMWMcSlotList_GetReadyMetaObject();
}

