igMetaObject *g_igPsx2ThreadManager_metaObject;

igMetaObject *igPsx2ThreadManager_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2ThreadManager_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igPsx2ThreadManager_EnsureRegistered();
    return g_igPsx2ThreadManager_metaObject;
}

int igPsx2ThreadManager_GetVTable(void) {
    igPsx2ThreadManager manager;

    igObject_InitHeader((igObject *)&manager);
    manager._vtable = (int)&g_igPsx2ThreadManager_vtable[0];
    return *(int *)((char *)&manager + g_objectSystem->vtableProbeOffset);
}

void igPsx2ThreadManager_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igPsx2ThreadManager_Register);
}

CallbackArray *igPsx2ThreadManager_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igPsx2ThreadManager_metaObject,
        igThreadManager_Register,
        (igMetaObjectGetFunction)igThreadManager_GetPublishedMetaObject,
        igPsx2ThreadManager_GetMetaObjectFunction,
        "igPsx2ThreadManager",
        0x10,
        igPsx2ThreadManager_GetVTable,
        igPsx2ThreadManager_SetWriteProxy,
        0,
        0
    );
}

int igThreadManager_GetPublishedMetaObject(void) {
    return (int)g_igThreadManager_metaObject;
}

void igPsx2ThreadManager_SetWriteProxy(void) {
    *(int *)((char *)(g_igPsx2ThreadManager_metaObject) + 64) = (int)(&igThreadManager_GetMetaObjectFunction);
}

