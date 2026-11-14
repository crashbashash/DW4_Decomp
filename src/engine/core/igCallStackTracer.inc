igMetaObject *igCallStackTracer_GetOrCreateMetaObject(void) {
    if (g_igCallStackTracer_metaObject[0] == 0) {
        g_igCallStackTracer_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igCallStackTracer_metaObject[0];
}

igMetaObject *igCallStackTracer_GetMetaObject(void)
{
    igMetaObject *g = g_igCallStackTracer_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igCallStackTracer_EnsureRegistered();
    return g_igCallStackTracer_metaObject[0];
}

int igCallStackTracer_GetVTable(void) {
    int tmp[8];
    int off;
    igObject_InitHeader((igObject *)&tmp[0]);
    tmp[0] = (int)&DAT_00530b80[0];
    off = *(int *)((char *)(((int * *)g_objectSystem)[0]) + 916);
    return *(int *)((char *)tmp + off);
}

void igCallStackTracer_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igCallStackTracer_Register);
}

void igCallStackTracer_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igCallStackTracer_metaObject),
        igUnsignedIntListNoClean_Register,
        igUnsignedIntListNoClean_GetPublishedMetaObject,
        igCallStackTracer_GetMetaObjectFunction,
        igCallStackTracer_className,
        0x14, /* instance size */
        igCallStackTracer_GetVTable,
        igCallStackTracer_SetAbstractProxy,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igCallStackTracer_GetMetaObjectFunction(void) {
    igCallStackTracer_GetMetaObject();
}

igMetaObject *igUnsignedIntListNoClean_GetPublishedMetaObject(void) {
    return g_igUnsignedIntListNoClean_metaObject[0];
}

void igCallStackTracer_SetAbstractProxy(void) {
    *(int *)((char *)(((void * *)g_igCallStackTracer_metaObject)[0]) + 60) = (int)(&igPsx2CallStackTracer_GetMetaObjectFunction);
}

