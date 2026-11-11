igMetaObject *igCapabilityManager_GetMetaObject(void)
{
    igMetaObject *g = g_igCapabilityManager_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0014fde0();
    return g_igCapabilityManager_metaObject[0];
}

void FUN_0014fde0(void)
{
    igMetaObject_RunStaticInit(igCapabilityManager_Register);
}

void igCapabilityManager_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igCapabilityManager_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igCapabilityManager_GetMetaObject,
        igCapabilityManager_className,
        8, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igCapabilityManager_GetMetaObject(void) {
    igCapabilityManager_GetMetaObject();
}

