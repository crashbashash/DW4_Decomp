int FUN_0044f0b0(int arg0) {
    igWindowSizeObserver_RunStaticInit();
    return igMetaObject_CreateInstance(*(int *)0x58C3C0, arg0);
}

igMetaObject *igWindowSizeObserver_GetMetaObject(void)
{
    igMetaObject *g = g_igWindowSizeObserver_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igWindowSizeObserver_RunStaticInit();
    return g_igWindowSizeObserver_metaObject[0];
}

int igWindowSizeObserver_GetVTable(void) {
    struct O o;
    igObject_InitHeader(&o.vt);
    o.vt = DAT_00541100;
    return *(int *)((char *)&o.vt + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void igWindowSizeObserver_RunStaticInit(void)
{
    igMetaObject_RunStaticInit(igWindowSizeObserver_Register);
}

void igWindowSizeObserver_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igWindowSizeObserver_metaObject,
        igView_Register,
        igView_GetPublishedMetaObject,
        thunk_igWindowSizeObserver_GetMetaObject,
        igWindowSizeObserver_className,
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

