int FUN_002cc630(void) {
    if (DAT_00586958[0] == 0) {
        DAT_00586958[0] = ((int)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(DAT_00587040[0]))));
    }
    return DAT_00586958[0];
}

igMetaObject *igCallStackTracer_GetMetaObject(void)
{
    igMetaObject *g = g_igCallStackTracer_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002cc710();
    return g_igCallStackTracer_metaObject[0];
}

int igCallStackTracer_GetVTable(void) {
    int tmp[8];
    int off;
    igObject_InitHeader((ObjectHeader *)&tmp[0]);
    tmp[0] = (int)&DAT_00530b80[0];
    off = *(int *)((char *)(((int * *)DAT_00586dc8)[0]) + 916);
    return *(int *)((char *)tmp + off);
}

void FUN_002cc710(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igCallStackTracer_Register);
}

void igCallStackTracer_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igCallStackTracer_metaObject),
        igUnsignedIntListNoClean_Register,
        igUnsignedIntListNoClean_GetPublishedMetaObject,
        thunk_igCallStackTracer_GetMetaObject,
        igCallStackTracer_className,
        0x14, /* instance size */
        igCallStackTracer_GetVTable,
        FUN_002cc7b0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igCallStackTracer_GetMetaObject(void) {
    igCallStackTracer_GetMetaObject();
}

int FUN_002cc7a0(void) {
    return DAT_00586850[0];
}

void FUN_002cc7b0(void) {
    *(int *)((char *)(((void * *)DAT_00586958)[0]) + 60) = (int)(&thunk_igPsx2CallStackTracer_GetMetaObject);
}

