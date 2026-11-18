igMetaObject *g_beSeDataList_metaObject;

igMetaObject *beSeDataList_GetOrCreateMetaObject(void) {
    if (g_beSeDataList_metaObject == 0) {
        g_beSeDataList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beSeDataList_metaObject;
}

igMetaObject *beSeDataList_GetMetaObject(void)
{
    igMetaObject *g = g_beSeDataList_metaObject;
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        beSeDataList_EnsureRegistered();
    return g_beSeDataList_metaObject;
}

int beSeDataList_GetVTable(void) {
    beSeDataList obj;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beSeDataList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void beSeDataList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSeDataList_Register);
}

static igMetaObjectCallback g_beSeDataList_callbackList[] = { beSeData_EnsureRegistered, 0 };

CallbackArray *beSeDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSeDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beSeDataList_GetMetaObjectFunction,
        "beSeDataList",
        0x14, /* instance size */
        beSeDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beSeDataList_callbackList /* callback list */
    );
}

void beSeDataList_GetMetaObjectFunction(void)
{
    beSeDataList_GetMetaObject();
}

