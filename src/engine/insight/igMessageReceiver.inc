igMetaObject *igMessageReceiver_GetMetaObject(void)
{
    igMetaObject *g = g_igMessageReceiver_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00231950();
    return g_igMessageReceiver_metaObject[0];
}

void FUN_00231950(void)
{
    igMetaObject_RunStaticInit(igMessageReceiver_Register);
}

void igMessageReceiver_Register(void) {
    InsightLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igMessageReceiver_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igMessageReceiver_GetMetaObject,
        igMessageReceiver_className,
        8, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igMessageReceiver_GetMetaObject(void) {
    igMessageReceiver_GetMetaObject();
}

