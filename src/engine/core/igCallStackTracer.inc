igMetaObject *g_igCallStackTracer_metaObject;

igMetaObject *igCallStackTracer_GetOrCreateMetaObject(void) {
    if (g_igCallStackTracer_metaObject == 0) {
        g_igCallStackTracer_metaObject = (igMetaObject *)igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igCallStackTracer_metaObject;
}

igMetaObject *igCallStackTracer_GetMetaObject(void)
{
    igMetaObject *g = g_igCallStackTracer_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igCallStackTracer_EnsureRegistered();
    return g_igCallStackTracer_metaObject;
}

int igCallStackTracer_GetVTable(void) {
    int tmp[8];
    int off;
    igObject_InitHeader((igObject *)&tmp[0]);
    tmp[0] = (int)&g_igCallStackTracer_vtable[0];
    off = g_objectSystem->vtableProbeOffset;
    return *(int *)((char *)tmp + off);
}

void igCallStackTracer_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igCallStackTracer_Register);
}

CallbackArray *igCallStackTracer_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igCallStackTracer_metaObject,
        igUnsignedIntListNoClean_Register,
        igUnsignedIntListNoClean_GetPublishedMetaObject,
        igCallStackTracer_GetMetaObjectFunction,
        "igCallStackTracer",
        0x14,
        igCallStackTracer_GetVTable,
        igCallStackTracer_SetAbstractProxy,
        0,
        0
    );
}

void igCallStackTracer_GetMetaObjectFunction(void) {
    igCallStackTracer_GetMetaObject();
}

igMetaObject *igUnsignedIntListNoClean_GetPublishedMetaObject(void) {
    return g_igUnsignedIntListNoClean_metaObject;
}

void igCallStackTracer_SetAbstractProxy(void) {
    *(int *)((char *)((void *)g_igCallStackTracer_metaObject) + 60) = (int)(&igPsx2CallStackTracer_GetMetaObjectFunction);
}

