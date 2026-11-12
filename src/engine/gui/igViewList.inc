igMetaObject *FUN_0044b9f0(void) {
    if (g_igViewList_metaObject[0] == 0) {
        g_igViewList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igViewList_metaObject[0];
}

igMetaObject *igViewList_GetMetaObject(void)
{
    igMetaObject *g = g_igViewList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igViewList_EnsureRegistered();
    return g_igViewList_metaObject[0];
}

int igViewList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00541f00[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void igViewList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igViewList_Register);
}

void igViewList_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igViewList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igViewList_GetMetaObject,
        igViewList_className,
        0x14, /* instance size */
        igViewList_GetVTable,
        0,
        0, /* extra callback item */
        g_igViewList_callbackList /* callback list */
    );
}

void thunk_igViewList_GetMetaObject(void) {
    igViewList_GetMetaObject();
}

