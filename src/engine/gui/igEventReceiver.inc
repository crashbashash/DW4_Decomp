igMetaObject *igEventReceiver_GetMetaObject(void)
{
    igMetaObject *g = g_igEventReceiver_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igEventReceiver_EnsureRegistered();
    return g_igEventReceiver_metaObject[0];
}

int igEventReceiver_GetVTable(void) {
    struct Obj_4512e0 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052cce0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void igEventReceiver_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igEventReceiver_Register);
}

void igEventReceiver_Register(void) {
    GuiLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igEventReceiver_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igEventReceiver_GetMetaObject,
        igEventReceiver_className,
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

