igMetaObject *FUN_0013a4d0(void) {
    if (g_igGeometryAttrList_metaObject[0] == 0) {
        g_igGeometryAttrList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igGeometryAttrList_metaObject[0];
}

igMetaObject *igGeometryAttrList_GetMetaObject(void)
{
    igMetaObject *g = g_igGeometryAttrList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0013a5b0();
    return g_igGeometryAttrList_metaObject[0];
}

int igGeometryAttrList_GetVTable(void) {
    int obj[8];
    igObject_InitHeader(obj);
    obj[0] = (int)&DAT_005245e0[0];
    return *(int *)((char *)obj + *(int *)((char *)g_objectSystem[0] + 916));
}

void FUN_0013a5b0(void)
{
    igMetaObject_RunStaticInit(igGeometryAttrList_Register);
}

void igGeometryAttrList_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igGeometryAttrList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igGeometryAttrList_GetMetaObject,
        igGeometryAttrList_className,
        0x14, /* instance size */
        igGeometryAttrList_GetVTable,
        0,
        0, /* extra callback item */
        g_igGeometryAttrList_callbackList /* callback list */
    );
}

void thunk_igGeometryAttrList_GetMetaObject(void) {
    igGeometryAttrList_GetMetaObject();
}

