igMetaObject *FUN_00152200(void)
{
    unsigned char ready;
    if (g_igPsx2VertexArray2_metaObject[0] != 0) {
        ready = (g_igPsx2VertexArray2_metaObject[0]->_validity & 4) != 0;
        if (ready != 0) goto done;
    }
    FUN_001522c0();
done:
    return g_igPsx2VertexArray2_metaObject[0];
}

int igPsx2VertexArray2_GetVTable(void) {
    union U_152250 u;
    int temp_s0;

    igObject_InitHeader(u.b);
    *(int *)&u.b[8] = 0;
    *(int *)&u.b[12] = 0;
    *(int *)&u.b[16] = 0;
    *(int *)&u.b[20] = 0;
    u.vt = (int)&DAT_00525120[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_00525120[0];
    FUN_0014a910((Obj_14a910 *)u.b, 0);
    return temp_s0;
}

void FUN_001522c0(void)
{
    igMetaObject_RunStaticInit(igPsx2VertexArray2_Register);
}

void igPsx2VertexArray2_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPsx2VertexArray2_metaObject,
        igVertexArray2_Register,
        igVertexArray2_GetPublishedMetaObject,
        thunk_igPsx2VertexArray2_GetMetaObject_0014acf0,
        igPsx2VertexArray2_className,
        0x18, /* instance size */
        igPsx2VertexArray2_GetVTable,
        &igPsx2VertexArray2_InitFields_00152350[0],      /* Field adder. */
        0,                                               /* extra callback-vector item (none) */
        0                                                /* zero-terminated callback-vector item list (none) */
    );
}

igMetaObject *FUN_00152340(void) {
    return g_igVertexArray2_metaObject[0];
}

void FUN_00152350(void) {
    *(int *)((char *)(g_igPsx2VertexArray2_metaObject[0]) + 64) = (int)(&thunk_igVertexArray2_GetMetaObject);
}

