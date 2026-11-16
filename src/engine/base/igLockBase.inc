igMetaObject *g_igLockBase_metaObject;

igMetaObject *igLockBase_GetMetaObject(void)
{
    igMetaObject *g = g_igLockBase_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00226be0();
    return g_igLockBase_metaObject;
}

void FUN_00226be0(void)
{
    igMetaObject_RunStaticInit((igMetaObjectRegisterFunction)igLockBase_Register);
}

CallbackArray *igLockBase_Register(void) {
    BaseLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igLockBase_metaObject,
        (igMetaObjectRegisterFunction)igInterfaced_Register,
        (igMetaObjectGetFunction)igInterfaced_GetPublishedMetaObject,
        thunk_igLockBase_GetMetaObject,
        "igLockBase",
        0x20, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igLockBase_GetMetaObject(void) {
    igLockBase_GetMetaObject();
}

