igMetaObject *g_beSaveIntfComMdlDataList_metaObject;

igMetaObject *FUN_003bc580(void) {
    if (g_beSaveIntfComMdlDataList_metaObject == 0) {
        g_beSaveIntfComMdlDataList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beSaveIntfComMdlDataList_metaObject;
}

void *FUN_003bc5d0(void) {
    igMetaObject *g = g_beSaveIntfComMdlDataList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003bc660();
    }
    return g_beSaveIntfComMdlDataList_metaObject;
}

int beSaveIntfComMdlDataList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0053d890[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_003bc660(void)
{
    igMetaObject_RunStaticInit(beSaveIntfComMdlDataList_Register);
}

static igMetaObjectCallback g_beSaveIntfComMdlDataList_callbackList[] = { FUN_003bc820, 0 };

void *beSaveIntfComMdlDataList_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSaveIntfComMdlDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beSaveIntfComMdlDataList_GetMetaObject,
        "beSaveIntfComMdlDataList",
        0x14, /* instance size */
        beSaveIntfComMdlDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beSaveIntfComMdlDataList_callbackList /* callback list */
    );
}

void beSaveIntfComMdlDataList_GetMetaObject(void)
{
    FUN_003bc5d0();
}

