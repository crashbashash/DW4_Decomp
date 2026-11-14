igMetaObject *igPsx2CallStackTracer_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2CallStackTracer_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igPsx2CallStackTracer_EnsureRegistered();
    return g_igPsx2CallStackTracer_metaObject[0];
}

int igPsx2CallStackTracer_GetVTable(void) {
    int obj[8];
    igObject_InitHeader((igObject *)obj);
    obj[0] = (int)&DAT_0052dcb0[0];
    return *(int *)((char *)obj + *(int *)((char *)((void * *)g_objectSystem)[0] + 916));
}

void igPsx2CallStackTracer_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igPsx2CallStackTracer_Register);
}

void igPsx2CallStackTracer_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igPsx2CallStackTracer_metaObject),
        igCallStackTracer_Register,
        igCallStackTracer_GetPublishedMetaObject,
        igPsx2CallStackTracer_GetMetaObjectFunction,
        igPsx2CallStackTracer_className,
        0x14, /* instance size */
        igPsx2CallStackTracer_GetVTable,
        &igPsx2CallStackTracer_InitFields_002d0530[0],     /* Field adder. */
        0,                                                 /* extra callback-vector item (none) */
        0                                                  /* zero-terminated callback-vector item list (none) */
    );
}

igMetaObject *igCallStackTracer_GetPublishedMetaObject(void) {
    return g_igCallStackTracer_metaObject[0];
}

void igPsx2CallStackTracer_SetWriteProxy(void) {
    *(int *)((char *)(g_igPsx2CallStackTracer_metaObject[0]) + 64) = (int)(&igCallStackTracer_GetMetaObjectFunction);
}

