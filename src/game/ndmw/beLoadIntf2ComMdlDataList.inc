igMetaObject *g_beLoadIntf2ComMdlDataList_metaObject;

igMetaObject *beLoadIntf2ComMdlDataList_GetOrCreateMetaObject(void) {
    if (g_beLoadIntf2ComMdlDataList_metaObject == 0) {
        g_beLoadIntf2ComMdlDataList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beLoadIntf2ComMdlDataList_metaObject;
}

void *beLoadIntf2ComMdlDataList_GetReadyMetaObject(void) {
    igMetaObject *g = g_beLoadIntf2ComMdlDataList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beLoadIntf2ComMdlDataList_EnsureRegistered();
    }
    return g_beLoadIntf2ComMdlDataList_metaObject;
}

int beLoadIntf2ComMdlDataList_GetVTable(void) {
    beLoadIntf2ComMdlDataList obj;

    igObject_InitHeader(&obj);
    *(int **)&obj._vtable = &g_beLoadIntf2ComMdlDataList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void beLoadIntf2ComMdlDataList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beLoadIntf2ComMdlDataList_Register);
}

static igMetaObjectCallback g_beLoadIntf2ComMdlDataList_callbackList[] = { beLoadIntf2ComMdlData_EnsureRegistered, 0 };

CallbackArray *beLoadIntf2ComMdlDataList_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beLoadIntf2ComMdlDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beLoadIntf2ComMdlDataList_GetMetaObject,
        "beLoadIntf2ComMdlDataList",
        0x14, /* instance size */
        beLoadIntf2ComMdlDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beLoadIntf2ComMdlDataList_callbackList /* callback list */
    );
}

void beLoadIntf2ComMdlDataList_GetMetaObject(void)
{
    beLoadIntf2ComMdlDataList_GetReadyMetaObject();
}

