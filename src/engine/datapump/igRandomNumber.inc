igMetaObject *g_igRandomNumber_metaObject;

igMetaObject *igRandomNumber_GetOrCreateMetaObject(void) {
    if (g_igRandomNumber_metaObject == 0) {
        g_igRandomNumber_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igRandomNumber_metaObject;
}

igMetaObject *igRandomNumber_GetMetaObject(void)
{
    igMetaObject *g = g_igRandomNumber_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igRandomNumber_EnsureRegistered();
    return g_igRandomNumber_metaObject;
}

void igRandomNumber_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igRandomNumber_Register);
}

CallbackArray *igRandomNumber_Register(void) {
    DataPumpLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igRandomNumber_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        igRandomNumber_GetMetaObjectFunction,
        "igRandomNumber",
        8, /* instance size */
        0,
        igRandomNumber_SetAbstractProxy,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igRandomNumber_GetMetaObjectFunction(void) {
    igRandomNumber_GetMetaObject();
}

void igRandomNumber_SetAbstractProxy(void) {
    g_igRandomNumber_metaObject->_abstractProxy = (int)&igMersenneTwisterRandomNumber_GetMetaObjectFunction;
}

