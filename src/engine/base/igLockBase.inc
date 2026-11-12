igMetaObject *igLockBase_GetMetaObject(void)
{
    igMetaObject *g = g_igLockBase_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00226be0();
    return g_igLockBase_metaObject[0];
}

void FUN_00226be0(void)
{
    igMetaObject_RunStaticInit(igLockBase_Register);
}

void igLockBase_Register(void) {
    BaseLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igLockBase_metaObject,
        igInterfaced_Register,
        igInterfaced_GetPublishedMetaObject,
        thunk_igLockBase_GetMetaObject,
        igLockBase_className,
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

