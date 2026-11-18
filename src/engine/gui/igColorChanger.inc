igMetaObject *g_igColorChanger_metaObject;

igMetaObject *igColorChanger_GetOrCreateMetaObject(void) {
    if (g_igColorChanger_metaObject == 0) {
        g_igColorChanger_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igColorChanger_metaObject;
}

igMetaObject *igColorChanger_GetMetaObject(void)
{
    igMetaObject *g = g_igColorChanger_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igColorChanger_RunStaticInit();
    return g_igColorChanger_metaObject;
}

int igColorChanger_GetVTable(void) {
    struct Obj_452270 obj;
    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igColorChanger_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igColorChanger_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igColorChanger_Register);
}

CallbackArray *igColorChanger_Register(void) {
    GuiLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igColorChanger_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igColorChanger_GetMetaObject,
        "igColorChanger",
        8, /* instance size */
        igColorChanger_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igColorChanger_GetMetaObject(void) {
    igColorChanger_GetMetaObject();
}

