igMetaObject *igPsx2IndexArray_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2IndexArray_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00153b40();
    return g_igPsx2IndexArray_metaObject[0];
}

int igPsx2IndexArray_GetVTable(void) {
    Obj_153aa0 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.ref = 0;
    obj.vt = &DAT_00526760[0];
    obj.vt = &DAT_00526ad0[0];
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &DAT_00526760[0];
    obj.releaseRef();
    return r;
}

void FUN_00153b40(void)
{
    igMetaObject_RunStaticInit(igPsx2IndexArray_Register);
}

void igPsx2IndexArray_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPsx2IndexArray_metaObject,
        igIndexArray_Register,
        igIndexArray_GetPublishedMetaObject,
        thunk_igPsx2IndexArray_GetMetaObject,
        igPsx2IndexArray_className,
        0x1C, /* instance size */
        igPsx2IndexArray_GetVTable,
        &igPsx2IndexArray_InitFields_00153bd0[0],     /* Field adder. */
        0,                                            /* extra callback-vector item (none) */
        0                                             /* zero-terminated callback-vector item list (none) */
    );
}

igMetaObject *FUN_00153bc0(void) {
    return g_igIndexArray_metaObject[0];
}

void FUN_00153bd0(void) {
    *(int *)((char *)(g_igPsx2IndexArray_metaObject[0]) + 64) = (int)(&thunk_igIndexArray_GetMetaObject);
}

