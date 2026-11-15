igMetaObject *g_beLayerGroupList_metaObject;

igMetaObject *FUN_0035c6c0(void) {
    if (g_beLayerGroupList_metaObject == 0) {
        g_beLayerGroupList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beLayerGroupList_metaObject;
}

void *FUN_0035c710(void) {
    igMetaObject *g = g_beLayerGroupList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0035c7a0();
    }
    return g_beLayerGroupList_metaObject;
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

static igMetaObjectCallback g_beLayerGroupList_callbackList[] = { FUN_0035c930, 0 };

void *beLayerGroupList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beLayerGroupList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beLayerGroupList_GetMetaObject,
        "beLayerGroupList",
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

