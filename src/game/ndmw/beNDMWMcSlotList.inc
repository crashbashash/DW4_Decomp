igMetaObject *g_beNDMWMcSlotList_metaObject;

igMetaObject *beNDMWMcSlotList_GetOrCreateMetaObject(void) {
    if (g_beNDMWMcSlotList_metaObject == 0) {
        g_beNDMWMcSlotList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
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
    beNDMWMcSlotList obj;

    igObject_InitHeader(&obj);
    *(int **)&obj._vtable = &g_beNDMWMcSlotList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void beNDMWMcSlotList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWMcSlotList_Register);
}

static igMetaObjectCallback g_beNDMWMcSlotList_callbackList[] = { beNDMWMcSlot_EnsureRegistered, 0 };

CallbackArray *beNDMWMcSlotList_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWMcSlotList_metaObject,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
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

