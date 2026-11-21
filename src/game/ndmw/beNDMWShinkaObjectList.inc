igMetaObject *g_beNDMWShinkaObjectList_metaObject;

igMetaObject *beNDMWShinkaObjectList_GetOrCreateMetaObject(void) {
    if (g_beNDMWShinkaObjectList_metaObject == 0) {
        g_beNDMWShinkaObjectList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
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
    beNDMWShinkaObjectList obj;

    igObject_InitHeader(&obj);
    *(int **)&obj._vtable = &g_beNDMWShinkaObjectList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void beNDMWShinkaObjectList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWShinkaObjectList_Register);
}

static igMetaObjectCallback g_beNDMWShinkaObjectList_callbackList[] = { beNDMWShinkaObject_EnsureRegistered, 0 };

CallbackArray *beNDMWShinkaObjectList_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWShinkaObjectList_metaObject,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
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

