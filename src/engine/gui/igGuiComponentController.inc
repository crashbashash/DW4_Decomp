igMetaObject *FUN_0044fa40(void) {
    if (g_igGuiComponentController_metaObject[0] == 0) {
        g_igGuiComponentController_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igGuiComponentController_metaObject[0];
}

igMetaObject *igGuiComponentController_GetMetaObject(void)
{
    igMetaObject *g = g_igGuiComponentController_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igGuiComponentController_EnsureRegistered();
    return g_igGuiComponentController_metaObject[0];
}

int igGuiComponentController_GetVTable(void) {
    struct Obj_44fae0 obj;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_00541270[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void igGuiComponentController_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igGuiComponentController_Register);
}

void igGuiComponentController_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igGuiComponentController_metaObject,
        igView_Register,
        igView_GetPublishedMetaObject,
        thunk_igGuiComponentController_GetMetaObject,
        igGuiComponentController_className,
        0xC, /* instance size */
        igGuiComponentController_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igGuiComponentController_GetMetaObject(void) {
    igGuiComponentController_GetMetaObject();
}

