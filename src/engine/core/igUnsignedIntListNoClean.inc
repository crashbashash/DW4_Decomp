igMetaObject *g_igUnsignedIntListNoClean_metaObject;

void * igUnsignedIntListNoClean_Create(int pool) {
    igUnsignedIntListNoClean_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance(g_igUnsignedIntListNoClean_metaObject, (igMemoryPoolView *)pool));
}

igMetaObject *igUnsignedIntListNoClean_GetOrCreateMetaObject(void) {
    if (g_igUnsignedIntListNoClean_metaObject == 0) {
        g_igUnsignedIntListNoClean_metaObject = (igMetaObject *)igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igUnsignedIntListNoClean_metaObject;
}

igMetaObject *igUnsignedIntListNoClean_GetMetaObject(void)
{
    igMetaObject *g = g_igUnsignedIntListNoClean_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igUnsignedIntListNoClean_EnsureRegistered();
    return g_igUnsignedIntListNoClean_metaObject;
}

int igUnsignedIntListNoClean_GetVTable(void) {
    igUnsignedIntListNoClean list;

    igObject_InitHeader((igObject *)&list);
    list._vtable = (int)&g_igUnsignedIntListNoClean_vtable[0];
    return *(int *)((char *)&list + g_objectSystem->vtableProbeOffset);
}

void igUnsignedIntListNoClean_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igUnsignedIntListNoClean_Register);
}

CallbackArray *igUnsignedIntListNoClean_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igUnsignedIntListNoClean_metaObject,
        igUnsignedIntList_Register,
        (igMetaObjectGetFunction)igUnsignedIntList_GetPublishedMetaObject,
        igUnsignedIntListNoClean_GetMetaObjectFunction,
        "igUnsignedIntListNoClean",
        0x14,
        igUnsignedIntListNoClean_GetVTable,
        0,
        0,
        0
    );
}

void igUnsignedIntListNoClean_GetMetaObjectFunction(void) {
    igUnsignedIntListNoClean_GetMetaObject();
}

