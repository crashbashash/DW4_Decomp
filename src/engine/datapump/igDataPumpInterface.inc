igMetaObject *g_igDataPumpInterface_metaObject;

igMetaObject *FUN_001e5530(void) {
    if (g_igDataPumpInterface_metaObject == 0) {
        g_igDataPumpInterface_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igDataPumpInterface_metaObject;
}

igMetaObject *igDataPumpInterface_GetMetaObject(void)
{
    igMetaObject *g = g_igDataPumpInterface_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001e55d0();
    return g_igDataPumpInterface_metaObject;
}

void FUN_001e55d0(void)
{
    igMetaObject_RunStaticInit(igDataPumpInterface_Register);
}

CallbackArray *igDataPumpInterface_Register(void) {
    DataPumpLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igDataPumpInterface_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igDataPumpInterface_GetMetaObject,
        "igDataPumpInterface",
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

