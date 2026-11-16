igMetaObject *g_igEventReceiver_metaObject;

igMetaObject *igEventReceiver_GetMetaObject(void)
{
    igMetaObject *g = g_igEventReceiver_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igEventReceiver_EnsureRegistered();
    return g_igEventReceiver_metaObject;
}

int igEventReceiver_GetVTable(void) {
    struct Obj_4512e0 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igEventReceiver_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem) + 916));
}

void igEventReceiver_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igEventReceiver_Register);
}

CallbackArray *igEventReceiver_Register(void) {
    GuiLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igEventReceiver_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igEventReceiver_GetMetaObject,
        "igEventReceiver",
        8, /* instance size */
        igEventReceiver_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igEventReceiver_GetMetaObject(void) {
    igEventReceiver_GetMetaObject();
}

