igMetaObject *g_igListenerBase_metaObject;

igMetaObject *igListenerBase_GetMetaObject(void)
{
    igMetaObject *g = g_igListenerBase_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002272f0();
    return g_igListenerBase_metaObject;
}

int igListenerBase_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igListenerBase_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void FUN_002272f0(void)
{
    igMetaObject_RunStaticInit((igMetaObjectRegisterFunction)igListenerBase_Register);
}

CallbackArray *igListenerBase_Register(void) {
    BaseLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igListenerBase_metaObject,
        (igMetaObjectRegisterFunction)igBase_Register,
        (igMetaObjectGetFunction)igBase_GetPublishedMetaObject,
        igListenerBase_GetMetaObjectFunction,
        "igListenerBase",
        0x20, /* instance size */
        igListenerBase_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igListenerBase_GetMetaObjectFunction(void) {
    igListenerBase_GetMetaObject();
}

