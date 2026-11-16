igMetaObject *g_beActionStarterDataList_metaObject;

igMetaObject *beActionStarterDataList_GetOrCreateMetaObject(void) {
    if (g_beActionStarterDataList_metaObject == 0) {
        g_beActionStarterDataList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beActionStarterDataList_metaObject;
}

void *beActionStarterDataList_GetMetaObject(void) {
    igMetaObject *g = g_beActionStarterDataList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beActionStarterDataList_EnsureRegistered();
    }
    return g_beActionStarterDataList_metaObject;
}

int beActionStarterDataList_GetVTable(void) {
    struct Obj_36bd00 obj;

    igObject_InitHeader(&obj);
    obj.vt = &g_beActionStarterDataList_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void beActionStarterDataList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beActionStarterDataList_Register);
}

static igMetaObjectCallback g_beActionStarterDataList_callbackList[] = { beActionStarterData_EnsureRegistered, 0 };

void *beActionStarterDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beActionStarterDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beActionStarterDataList_GetMetaObjectFunction,
        "beActionStarterDataList",
        0x14, /* instance size */
        beActionStarterDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beActionStarterDataList_callbackList /* callback list */
    );
}

void beActionStarterDataList_GetMetaObjectFunction(void)
{
    beActionStarterDataList_GetMetaObject();
}

