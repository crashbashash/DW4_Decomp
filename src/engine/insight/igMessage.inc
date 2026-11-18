igMetaObject *g_igMessage_metaObject;

igMetaObject *igMessage_GetMetaObject(void)
{
    igMetaObject *g = g_igMessage_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igMessage_EnsureRegistered();
    return g_igMessage_metaObject;
}

int igMessage_GetVTable(void) {
    struct Obj_2316c0 o; igObject_InitHeader((igObject *)&o);
    o.vt = &g_igMessage_vtable[0];
    return *(int *)((char *)&o + g_objectSystem->vtableProbeOffset);
}

void igMessage_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igMessage_Register);
}

CallbackArray *igMessage_Register(void) {
    InsightLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igMessage_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        igMessage_GetMetaObjectFunction,
        "igMessage",
        8, /* instance size */
        igMessage_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igMessage_GetMetaObjectFunction(void) {
    igMessage_GetMetaObject();
}

