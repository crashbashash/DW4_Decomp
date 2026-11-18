igMetaObject *g_igInterface_metaObject;

igMetaObject *igInterface_GetMetaObject(void)
{
    igMetaObject *g = g_igInterface_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00228c60();
    return g_igInterface_metaObject;
}

int igInterface_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igInterface_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void FUN_00228c60(void)
{
    igMetaObject_RunStaticInit((igMetaObjectRegisterFunction)igInterface_Register);
}

CallbackArray *igInterface_Register(void) {
    BaseLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igInterface_metaObject,
        (igMetaObjectRegisterFunction)igInterfaced_Register,
        (igMetaObjectGetFunction)igInterfaced_GetPublishedMetaObject,
        thunk_igInterface_GetMetaObject,
        "igInterface",
        0x20, /* instance size */
        igInterface_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igInterface_GetMetaObject(void) {
    igInterface_GetMetaObject();
}

