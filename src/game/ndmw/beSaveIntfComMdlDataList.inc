igMetaObject *g_beSaveIntfComMdlDataList_metaObject;

igMetaObject *beSaveIntfComMdlDataList_GetOrCreateMetaObject(void) {
    if (g_beSaveIntfComMdlDataList_metaObject == 0) {
        g_beSaveIntfComMdlDataList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_beSaveIntfComMdlDataList_metaObject;
}

void *beSaveIntfComMdlDataList_GetMetaObject(void) {
    igMetaObject *g = g_beSaveIntfComMdlDataList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beSaveIntfComMdlDataList_EnsureRegistered();
    }
    return g_beSaveIntfComMdlDataList_metaObject;
}

int beSaveIntfComMdlDataList_GetVTable(void) {
    beSaveIntfComMdlDataList obj;

    igObject_InitHeader(&obj);
    *(int **)&obj._vtable = &g_beSaveIntfComMdlDataList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void beSaveIntfComMdlDataList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beSaveIntfComMdlDataList_Register);
}

static igMetaObjectCallback g_beSaveIntfComMdlDataList_callbackList[] = { beSaveIntfComMdlData_EnsureRegistered, 0 };

CallbackArray *beSaveIntfComMdlDataList_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beSaveIntfComMdlDataList_metaObject,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        beSaveIntfComMdlDataList_GetMetaObjectFunction,
        "beSaveIntfComMdlDataList",
        0x14, /* instance size */
        beSaveIntfComMdlDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beSaveIntfComMdlDataList_callbackList /* callback list */
    );
}

void beSaveIntfComMdlDataList_GetMetaObjectFunction(void)
{
    beSaveIntfComMdlDataList_GetMetaObject();
}

