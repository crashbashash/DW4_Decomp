igMetaObject *g_igCharListNoClean_metaObject;

igMetaObject *igCharListNoClean_GetOrCreateMetaObject(void) {
    if (g_igCharListNoClean_metaObject == 0) {
        g_igCharListNoClean_metaObject = (igMetaObject *)igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igCharListNoClean_metaObject;
}

igMetaObject *igCharListNoClean_GetMetaObject(void)
{
    igMetaObject *g = g_igCharListNoClean_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igCharListNoClean_EnsureRegistered();
    return g_igCharListNoClean_metaObject;
}

int igCharListNoClean_GetVTable(void) {
    igCharListNoClean list;

    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&g_igCharListNoClean_vtable[0];
    return *(int *)((char *)&list + g_objectSystem->vtableProbeOffset);
}

void igCharListNoClean_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igCharListNoClean_Register);
}

CallbackArray *igCharListNoClean_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igCharListNoClean_metaObject,
        igCharList_Register,
        igCharList_GetPublishedMetaObject,
        igCharListNoClean_GetMetaObjectFunction,
        "igCharListNoClean",
        0x14,
        igCharListNoClean_GetVTable,
        0,
        0,
        0
    );
}

void igCharListNoClean_GetMetaObjectFunction(void) {
    igCharListNoClean_GetMetaObject();
}

