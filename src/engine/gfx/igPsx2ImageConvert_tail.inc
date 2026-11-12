igMetaObject *igPsx2ImageConvert_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2ImageConvert_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00153c80();
    return g_igPsx2ImageConvert_metaObject[0];
}

int igPsx2ImageConvert_GetVTable(void) {
    struct Obj_153c40 obj;
    igObject_InitHeader(&obj);
    obj.vt = &DAT_005255a0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_00153c80(void)
{
    igMetaObject_RunStaticInit(igPsx2ImageConvert_Register);
}

void igPsx2ImageConvert_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPsx2ImageConvert_metaObject,
        igImageConvert_Register,
        igImageConvert_GetPublishedMetaObject,
        thunk_igPsx2ImageConvert_GetMetaObject,
        igPsx2ImageConvert_className,
        8, /* instance size */
        igPsx2ImageConvert_GetVTable,
        &igPsx2ImageConvert_InitFields_00153d10[0],     /* Field adder. */
        0,                                              /* extra callback-vector item (none) */
        0                                               /* zero-terminated callback-vector item list (none) */
    );
}

int FUN_00153d00(void) {
    return (int)g_igImageConvert_metaObject[0];
}

void FUN_00153d10(void) {
    *(int *)((char *)(g_igPsx2ImageConvert_metaObject[0]) + 64) = (int)(&thunk_igImageConvert_GetMetaObject);
}

