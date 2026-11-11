int FUN_001e5530(void) {
    if (DAT_00562c08[0] == 0) {
        DAT_00562c08[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_00562c08[0];
}

igMetaObject *igDataPumpInterface_GetMetaObject(void)
{
    igMetaObject *g = g_igDataPumpInterface_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001e55d0();
    return g_igDataPumpInterface_metaObject[0];
}

void FUN_001e55d0(void)
{
    igMetaObject_RunStaticInit(igDataPumpInterface_Register);
}

void igDataPumpInterface_Register(void) {
    DataPumpLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        g_igDataPumpInterface_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igDataPumpInterface_GetMetaObject,
        igDataPumpInterface_className,
        8, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igDataPumpInterface_GetMetaObject(void) {
    igDataPumpInterface_GetMetaObject();
}

