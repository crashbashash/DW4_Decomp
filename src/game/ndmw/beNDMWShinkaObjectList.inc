igMetaObject *g_beNDMWShinkaObjectList_metaObject;

igMetaObject *beNDMWShinkaObjectList_GetOrCreateMetaObject(void) {
    if (g_beNDMWShinkaObjectList_metaObject == 0) {
        g_beNDMWShinkaObjectList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beNDMWShinkaObjectList_metaObject;
}

igMetaObject *beNDMWShinkaObjectList_ResolveMetaObject(void)
{
    igMetaObject *g = g_beNDMWShinkaObjectList_metaObject;
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        beNDMWShinkaObjectList_EnsureRegistered();
    return g_beNDMWShinkaObjectList_metaObject;
}

int beNDMWShinkaObjectList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &g_beNDMWShinkaObjectList_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void beNDMWShinkaObjectList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWShinkaObjectList_Register);
}

static igMetaObjectCallback g_beNDMWShinkaObjectList_callbackList[] = { beNDMWShinkaObject_EnsureRegistered, 0 };

void *beNDMWShinkaObjectList_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWShinkaObjectList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beNDMWShinkaObjectList_GetMetaObject,
        "beNDMWShinkaObjectList",
        0x14, /* instance size */
        beNDMWShinkaObjectList_GetVTable,
        0,
        0, /* extra callback item */
        g_beNDMWShinkaObjectList_callbackList /* callback list */
    );
}

void beNDMWShinkaObjectList_GetMetaObject(void)
{
    beNDMWShinkaObjectList_ResolveMetaObject();
}

