igMetaObject *FUN_0035c6c0(void) {
    if (g_beLayerGroupList_metaObject[0] == 0) {
        g_beLayerGroupList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_beLayerGroupList_metaObject[0];
}

void *FUN_0035c710(void) {
    igMetaObject *g = g_beLayerGroupList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0035c7a0();
    }
    return g_beLayerGroupList_metaObject[0];
}

int beLayerGroupList_GetVTable(void) {
    struct Obj_35c760 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_005365a0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_0035c7a0(void)
{
    igMetaObject_RunStaticInit(beLayerGroupList_Register);
}

void *beLayerGroupList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beLayerGroupList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beLayerGroupList_GetMetaObject,
        beLayerGroupList_className,
        0x14, /* instance size */
        beLayerGroupList_GetVTable,
        0,
        0, /* extra callback item */
        g_beLayerGroupList_callbackList /* callback list */
    );
}

void beLayerGroupList_GetMetaObject(void)
{
    FUN_0035c710();
}

