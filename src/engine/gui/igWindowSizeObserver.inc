igMetaObject *g_igWindowSizeObserver_metaObject;

int FUN_0044f0b0(int arg0) {
    igWindowSizeObserver_RunStaticInit();
    return (int)(igMetaObject_CreateInstance(g_igWindowSizeObserver_metaObject, (igMemoryPoolView *)arg0));
}

igMetaObject *igWindowSizeObserver_GetMetaObject(void)
{
    igMetaObject *g = g_igWindowSizeObserver_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igWindowSizeObserver_RunStaticInit();
    return g_igWindowSizeObserver_metaObject;
}

int igWindowSizeObserver_GetVTable(void) {
    struct O o;
    igObject_InitHeader((igObject *)&o.vt);
    o.vt = g_igWindowSizeObserver_vtable;
    return *(int *)((char *)&o.vt + *(int *)((char *)(g_objectSystem) + 916));
}

void igWindowSizeObserver_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igWindowSizeObserver_Register);
}

CallbackArray *igWindowSizeObserver_Register(void) {
    GuiLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igWindowSizeObserver_metaObject,
        igView_Register,
        igView_GetPublishedMetaObject,
        thunk_igWindowSizeObserver_GetMetaObject,
        "igWindowSizeObserver",
        0xC, /* instance size */
        igWindowSizeObserver_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igWindowSizeObserver_GetMetaObject(void) {
    igWindowSizeObserver_GetMetaObject();
}

