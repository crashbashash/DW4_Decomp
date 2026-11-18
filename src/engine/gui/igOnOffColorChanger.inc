igMetaObject *g_igOnOffColorChanger_metaObject;

igMetaObject *igOnOffColorChanger_GetOrCreateMetaObject(void) {
    if (g_igOnOffColorChanger_metaObject == 0) {
        g_igOnOffColorChanger_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igOnOffColorChanger_metaObject;
}

igMetaObject *igOnOffColorChanger_GetMetaObject(void)
{
    igMetaObject *g = g_igOnOffColorChanger_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igOnOffColorChanger_RunStaticInit();
    return g_igOnOffColorChanger_metaObject;
}

int igOnOffColorChanger_GetVTable(void) {
    struct Obj_451ee0 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igOnOffColorChanger_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igOnOffColorChanger_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igOnOffColorChanger_Register);
}

CallbackArray *igOnOffColorChanger_Register(void) {
    GuiLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igOnOffColorChanger_metaObject,
        igBasicColorChanger_Register,
        igBasicColorChanger_GetPublishedMetaObject,
        thunk_igOnOffColorChanger_GetMetaObject,
        "igOnOffColorChanger",
        0x58, /* instance size */
        igOnOffColorChanger_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igOnOffColorChanger_GetMetaObject(void) {
    igOnOffColorChanger_GetMetaObject();
}

