igMetaObject *g_igDataPumpInterface_metaObject;

igMetaObject *igDataPumpInterface_GetOrCreateMetaObject(void) {
    if (g_igDataPumpInterface_metaObject == 0) {
        g_igDataPumpInterface_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igDataPumpInterface_metaObject;
}

igMetaObject *igDataPumpInterface_GetMetaObject(void)
{
    igMetaObject *g = g_igDataPumpInterface_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igDataPumpInterface_EnsureRegistered();
    return g_igDataPumpInterface_metaObject;
}

void igDataPumpInterface_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igDataPumpInterface_Register);
}

CallbackArray *igDataPumpInterface_Register(void) {
    DataPumpLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igDataPumpInterface_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        igDataPumpInterface_GetMetaObjectFunction,
        "igDataPumpInterface",
        8, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igDataPumpInterface_GetMetaObjectFunction(void) {
    igDataPumpInterface_GetMetaObject();
}

