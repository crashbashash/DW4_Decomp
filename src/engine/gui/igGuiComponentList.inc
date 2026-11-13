igMetaObject *FUN_0044fdd0(void) {
    if (g_igGuiComponentList_metaObject[0] == 0) {
        g_igGuiComponentList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igGuiComponentList_metaObject[0];
}

igMetaObject *igGuiComponentList_GetMetaObject(void)
{
    igMetaObject *g = g_igGuiComponentList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igGuiComponentList_EnsureRegistered();
    return g_igGuiComponentList_metaObject[0];
}

int igGuiComponentList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00541aa0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void igGuiComponentList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igGuiComponentList_Register);
}

void igGuiComponentList_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igGuiComponentList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igGuiComponentList_GetMetaObject,
        igGuiComponentList_className,
        0x14, /* instance size */
        igGuiComponentList_GetVTable,
        0,
        0, /* extra callback item */
        g_igGuiComponentList_callbackList /* callback list */
    );
}

void thunk_igGuiComponentList_GetMetaObject(void) {
    igGuiComponentList_GetMetaObject();
}

