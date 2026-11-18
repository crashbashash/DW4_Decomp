igMetaObject *g_igGuiComponentController_metaObject;

igMetaObject *igGuiComponentController_GetOrCreateMetaObject(void) {
    if (g_igGuiComponentController_metaObject == 0) {
        g_igGuiComponentController_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igGuiComponentController_metaObject;
}

igMetaObject *igGuiComponentController_GetMetaObject(void)
{
    igMetaObject *g = g_igGuiComponentController_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igGuiComponentController_EnsureRegistered();
    return g_igGuiComponentController_metaObject;
}

int igGuiComponentController_GetVTable(void) {
    struct Obj_44fae0 obj;
    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igGuiComponentController_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igGuiComponentController_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igGuiComponentController_Register);
}

CallbackArray *igGuiComponentController_Register(void) {
    GuiLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igGuiComponentController_metaObject,
        igView_Register,
        igView_GetPublishedMetaObject,
        igGuiComponentController_GetMetaObjectFunction,
        "igGuiComponentController",
        0xC, /* instance size */
        igGuiComponentController_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igGuiComponentController_GetMetaObjectFunction(void) {
    igGuiComponentController_GetMetaObject();
}

