igMetaObject *g_beNumVerInsideDataList_metaObject;

igMetaObject *beNumVerInsideDataList_GetOrCreateMetaObject(void) {
    if (g_beNumVerInsideDataList_metaObject == 0) {
        g_beNumVerInsideDataList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beNumVerInsideDataList_metaObject;
}

void *beNumVerInsideDataList_GetMetaObject(void) {
    igMetaObject *g = g_beNumVerInsideDataList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNumVerInsideDataList_EnsureRegistered();
    }
    return g_beNumVerInsideDataList_metaObject;
}

int beNumVerInsideDataList_GetVTable(void) {
    beNumVerInsideDataList obj;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beNumVerInsideDataList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void beNumVerInsideDataList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNumVerInsideDataList_Register);
}

static igMetaObjectCallback g_beNumVerInsideDataList_callbackList[] = { beNumVerInsideData_EnsureRegistered, 0 };

CallbackArray *beNumVerInsideDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNumVerInsideDataList_metaObject,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        beNumVerInsideDataList_GetMetaObjectFunction,
        "beNumVerInsideDataList",
        0x14, /* instance size */
        beNumVerInsideDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beNumVerInsideDataList_callbackList /* callback list */
    );
}

void beNumVerInsideDataList_GetMetaObjectFunction(void)
{
    beNumVerInsideDataList_GetMetaObject();
}

