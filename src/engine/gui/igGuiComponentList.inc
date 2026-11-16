igMetaObject *g_igGuiComponentList_metaObject;

igMetaObject *FUN_0044fdd0(void) {
    if (g_igGuiComponentList_metaObject == 0) {
        g_igGuiComponentList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igGuiComponentList_metaObject;
}

igMetaObject *igGuiComponentList_GetMetaObject(void)
{
    igMetaObject *g = g_igGuiComponentList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igGuiComponentList_EnsureRegistered();
    return g_igGuiComponentList_metaObject;
}

int igGuiComponentList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igGuiComponentList_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem) + 916));
}

void igGuiComponentList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igGuiComponentList_Register);
}

static igMetaObjectCallback g_igGuiComponentList_callbackList[] = { igGuiComponent_EnsureRegistered, 0 };

CallbackArray *igGuiComponentList_Register(void) {
    GuiLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igGuiComponentList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igGuiComponentList_GetMetaObject,
        "igGuiComponentList",
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

