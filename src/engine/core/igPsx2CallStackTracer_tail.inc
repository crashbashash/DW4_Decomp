igMetaObject *igPsx2CallStackTracer_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2CallStackTracer_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002d04a0();
    return g_igPsx2CallStackTracer_metaObject[0];
}

int igPsx2CallStackTracer_GetVTable(void) {
    int obj[8];
    igObject_InitHeader((ObjectHeader *)obj);
    obj[0] = (int)&DAT_0052dcb0[0];
    return *(int *)((char *)obj + *(int *)((char *)((void * *)DAT_00586dc8)[0] + 916));
}

void FUN_002d04a0(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igPsx2CallStackTracer_Register);
}

void igPsx2CallStackTracer_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igPsx2CallStackTracer_metaObject),
        igCallStackTracer_Register,
        igCallStackTracer_GetPublishedMetaObject,
        thunk_igPsx2CallStackTracer_GetMetaObject,
        igPsx2CallStackTracer_className,
        0x14, /* instance size */
        igPsx2CallStackTracer_GetVTable,
        &igPsx2CallStackTracer_InitFields_002d0530[0],     /* Field adder. */
        0,                                                 /* extra callback-vector item (none) */
        0                                                  /* zero-terminated callback-vector item list (none) */
    );
}

int FUN_002d0520(void) {
    return DAT_00586958[0];
}

void FUN_002d0530(void) {
    *(int *)((char *)(DAT_00586db8[0]) + 64) = (int)(&thunk_igCallStackTracer_GetMetaObject);
}

