igMetaObject *g_igMessageBase_metaObject;

igMetaObject *igMessageBase_GetMetaObject(void)
{
    igMetaObject *g = g_igMessageBase_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00226540();
    return g_igMessageBase_metaObject;
}

int igMessageBase_GetVTable(void) {
    Obj_4 o;

    igObject_InitHeader((igObject *)&o);
    o.vt = &g_igMessageBase_vtable[0];
    return *(int *)((char *)&o + g_objectSystem->vtableProbeOffset);
}

void FUN_00226540(void)
{
    igMetaObject_RunStaticInit((igMetaObjectRegisterFunction)igMessageBase_Register);
}

CallbackArray *igMessageBase_Register(void) {
    BaseLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igMessageBase_metaObject,
        (igMetaObjectRegisterFunction)igBase_Register,
        (igMetaObjectGetFunction)igBase_GetPublishedMetaObject,
        thunk_igMessageBase_GetMetaObject,
        "igMessageBase",
        0x20, /* instance size */
        igMessageBase_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igMessageBase_GetMetaObject(void) {
    igMessageBase_GetMetaObject();
}

igMetaObject *FUN_002265d0(void) {
    return g_igInterfaced_metaObject;
}

