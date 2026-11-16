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
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igRandomNumber_GetMetaObject,
        "igRandomNumber",
        8, /* instance size */
        0,
        igRandomNumber_InitFields_001e4370,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igRandomNumber_GetMetaObject(void) {
    igRandomNumber_GetMetaObject();
}

void FUN_001e4370(void) {
    *(int *)((char *)(g_igRandomNumber_metaObject) + 60) = (int)(&thunk_igMersenneTwisterRandomNumber_GetMetaObject);
}

