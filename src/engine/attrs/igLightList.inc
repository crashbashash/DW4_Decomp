igMetaObject *g_igLightList_metaObject;

igMetaObject *FUN_001365e0(void) {
    if (g_igLightList_metaObject == 0) {
        g_igLightList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igLightList_metaObject;
}

igMetaObject *igLightList_GetMetaObject(void)
{
    igMetaObject *g = g_igLightList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001366c0();
    return g_igLightList_metaObject;
}

int igLightList_GetVTable(void) {
    struct Obj_136680 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00524730[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_001366c0(void)
{
    igMetaObject_RunStaticInit(igLightList_Register);
}

static igMetaObjectCallback g_igLightList_callbackList[] = { FUN_00136880, 0 };

void igLightList_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igLightList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igLightList_GetMetaObject,
        "igLightList",
        0x14, /* instance size */
        igLightList_GetVTable,
        0,
        0, /* extra callback item */
        g_igLightList_callbackList /* callback list */
    );
}

void thunk_igLightList_GetMetaObject(void) {
    igLightList_GetMetaObject();
}

