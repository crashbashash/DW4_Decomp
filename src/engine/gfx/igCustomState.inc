igMetaObject *g_igCustomState_metaObject;

igMetaObject *igCustomState_GetMetaObject(void)
{
    igMetaObject *g = g_igCustomState_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0014f240();
    return g_igCustomState_metaObject;
}

void FUN_0014f240(void)
{
    igMetaObject_RunStaticInit(igCustomState_Register);
}

void igCustomState_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igCustomState_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        thunk_igCustomState_GetMetaObject,
        "igCustomState",
        0xC, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igCustomState_GetMetaObject(void) {
    igCustomState_GetMetaObject();
}

