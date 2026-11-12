igMetaObject *FUN_00136040(void) {
    if (g_igLightStateAttrList_metaObject[0] == 0) {
        g_igLightStateAttrList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igLightStateAttrList_metaObject[0];
}

igMetaObject *igLightStateAttrList_GetMetaObject(void)
{
    igMetaObject *g = g_igLightStateAttrList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00136120();
    return g_igLightStateAttrList_metaObject[0];
}

int igLightStateAttrList_GetVTable(void) {
    Obj_1360e0 o;

    igObject_InitHeader(&o);
    o.vt = &DAT_005247a0[0];
    return *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_00136120(void)
{
    igMetaObject_RunStaticInit(igLightStateAttrList_Register);
}

void igLightStateAttrList_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igLightStateAttrList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igLightStateAttrList_GetMetaObject,
        igLightStateAttrList_className,
        0x14, /* instance size */
        igLightStateAttrList_GetVTable,
        0,
        0, /* extra callback item */
        g_igLightStateAttrList_callbackList /* callback list */
    );
}

void thunk_igLightStateAttrList_GetMetaObject(void) {
    igLightStateAttrList_GetMetaObject();
}

