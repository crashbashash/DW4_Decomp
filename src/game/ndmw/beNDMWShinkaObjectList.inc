igMetaObject *FUN_003c9810(void) {
    if (g_beNDMWShinkaObjectList_metaObject[0] == 0) {
        g_beNDMWShinkaObjectList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beNDMWShinkaObjectList_metaObject[0];
}

igMetaObject *beNDMWShinkaObjectList_ResolveMetaObject(void)
{
    igMetaObject *g = g_beNDMWShinkaObjectList_metaObject[0];
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        FUN_003c98f0();
    return g_beNDMWShinkaObjectList_metaObject[0];
}

int beNDMWShinkaObjectList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0053c610[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_003c98f0(void)
{
    igMetaObject_RunStaticInit(beNDMWShinkaObjectList_Register);
}

void *beNDMWShinkaObjectList_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWShinkaObjectList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beNDMWShinkaObjectList_GetMetaObject,
        beNDMWShinkaObjectList_className,
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

