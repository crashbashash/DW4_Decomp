igMetaObject *g_beNumVerDataList_metaObject;

igMetaObject *beNumVerDataList_GetOrCreateMetaObject(void) {
    if (g_beNumVerDataList_metaObject == 0) {
        g_beNumVerDataList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beNumVerDataList_metaObject;
}

igMetaObject *beNumVerDataList_GetMetaObject(void) {
    if (g_beNumVerDataList_metaObject == 0 || !isValid(g_beNumVerDataList_metaObject)) beNumVerDataList_EnsureRegistered();
    return g_beNumVerDataList_metaObject;
}

int beNumVerDataList_GetVTable(void) {
    beNumVerDataList obj;

    igObject_InitHeader(&obj);
    obj._vtable = (int)&g_beNumVerDataList_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void beNumVerDataList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNumVerDataList_Register);
}

static igMetaObjectCallback g_beNumVerDataList_callbackList[] = { beNumVerData_EnsureRegistered, 0 };

void *beNumVerDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNumVerDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beNumVerDataList_GetMetaObjectFunction,
        "beNumVerDataList",
        0x14, /* instance size */
        beNumVerDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beNumVerDataList_callbackList /* callback list */
    );
}

void beNumVerDataList_GetMetaObjectFunction(void)
{
    beNumVerDataList_GetMetaObject();
}

