igMetaObject *FUN_0019f930(void) {
    if (g_igGeometryList_metaObject[0] == 0) {
        g_igGeometryList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igGeometryList_metaObject[0];
}

igMetaObject *igGeometryList_GetMetaObject(void)
{
    igMetaObject *g = g_igGeometryList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0019fa10();
    return g_igGeometryList_metaObject[0];
}

int igGeometryList_GetVTable(void) {
    union U u;
    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_0052a7a0[0];
    return *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
}

void FUN_0019fa10(void)
{
    igMetaObject_RunStaticInit(igGeometryList_Register);
}

void igGeometryList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igGeometryList_metaObject),
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igGeometryList_GetMetaObject,
        igGeometryList_className,
        0x14, /* instance size */
        igGeometryList_GetVTable,
        0,
        0, /* extra callback item */
        g_igGeometryList_callbackList /* callback list */
    );
}

void thunk_igGeometryList_GetMetaObject(void) {
    igGeometryList_GetMetaObject();
}

