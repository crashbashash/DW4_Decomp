int FUN_001365e0(void) {
    if (DAT_0055f080[0] == 0) {
        DAT_0055f080[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0055f080[0];
}

igMetaObject *igLightList_GetMetaObject(void)
{
    igMetaObject *g = g_igLightList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001366c0();
    return g_igLightList_metaObject[0];
}

int igLightList_GetVTable(void) {
    struct Obj_136680 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00524730[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_001366c0(void)
{
    igMetaObject_RunStaticInit(igLightList_Register);
}

void igLightList_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igLightList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igLightList_GetMetaObject,
        igLightList_className,
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

