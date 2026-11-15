igMetaObject *g_igPsx2CallStackTracer_metaObject;

igMetaObject *igPsx2CallStackTracer_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2CallStackTracer_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igPsx2CallStackTracer_EnsureRegistered();
    return g_igPsx2CallStackTracer_metaObject;
}

int igPsx2CallStackTracer_GetVTable(void) {
    int obj[8];
    igObject_InitHeader((igObject *)obj);
    obj[0] = (int)&g_igPsx2CallStackTracer_vtable[0];
    return *(int *)((char *)obj + *(int *)((char *)(*(void * *)&g_objectSystem) + 916));
}

void igPsx2CallStackTracer_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igPsx2CallStackTracer_Register);
}

void igPsx2CallStackTracer_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        &g_igPsx2CallStackTracer_metaObject,
        (igMetaObjectRegisterFunction)igCallStackTracer_Register,
        igCallStackTracer_GetPublishedMetaObject,
        igPsx2CallStackTracer_GetMetaObjectFunction,
        "igPsx2CallStackTracer",
        0x14,
        igPsx2CallStackTracer_GetVTable,
        igPsx2CallStackTracer_SetWriteProxy,
        0,
        0
    );
}

igMetaObject *igCallStackTracer_GetPublishedMetaObject(void) {
    return g_igCallStackTracer_metaObject;
}

void igPsx2CallStackTracer_SetWriteProxy(void) {
    *(int *)((char *)(g_igPsx2CallStackTracer_metaObject) + 64) = (int)(&igCallStackTracer_GetMetaObjectFunction);
}

