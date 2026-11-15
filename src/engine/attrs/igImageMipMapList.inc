igMetaObject *g_igImageMipMapList_metaObject;

igMetaObject *FUN_00132ff0(void) {
    if (g_igImageMipMapList_metaObject == 0) {
        g_igImageMipMapList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igImageMipMapList_metaObject;
}

igMetaObject *igImageMipMapList_GetMetaObject(void)
{
    igMetaObject *g = g_igImageMipMapList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001330d0();
    return g_igImageMipMapList_metaObject;
}

int igImageMipMapList_GetVTable(void) {
    Obj_133090 o;

    igObject_InitHeader(&o);
    o.vt = &DAT_005248e0[0];
    return *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_001330d0(void)
{
    igMetaObject_RunStaticInit(igImageMipMapList_Register);
}

static igMetaObjectCallback g_igImageMipMapList_callbackList[] = { FUN_0014e050, 0 };

void igImageMipMapList_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igImageMipMapList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igImageMipMapList_GetMetaObject,
        "igImageMipMapList",
        0x14, /* instance size */
        igImageMipMapList_GetVTable,
        0,
        0, /* extra callback item */
        g_igImageMipMapList_callbackList /* callback list */
    );
}

void thunk_igImageMipMapList_GetMetaObject(void) {
    igImageMipMapList_GetMetaObject();
}

