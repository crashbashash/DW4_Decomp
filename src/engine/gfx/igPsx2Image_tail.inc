igMetaObject *igPsx2Image_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2Image_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00153e60();
    return g_igPsx2Image_metaObject[0];
}

int igPsx2Image_GetVTable(void) {
    union U_153d80 u;
    int r;
    int *v1; int *a1; int v0; int *a0;
    char *pr; char *ps;
    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00526800[0];
    pr = &u.b[68];
    *(int *)pr = 0;
    ps = &u.b[88];
    *(int *)ps = 0;
    u.vt = (int)&DAT_00525630[0];
    r = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_00526800[0];
    if (ps != 0) {
        v1 = *(int **)ps;
        if (v1 != 0) {
            a1 = v1 - 2;
            v0 = v1[-1] - 1;
            v1[-1] = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    if (pr != 0) {
        a0 = *(int **)pr;
        if (a0 != 0) {
            a0[1] = a0[1] - 1;
            if ((a0[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(a0);
            }
        }
    }
    return r;
}

void FUN_00153e60(void)
{
    igMetaObject_RunStaticInit(igPsx2Image_Register);
}

void igPsx2Image_Register(void) {
    FUN_00149bc0();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igPsx2Image_metaObject,
        igMemoryImage_Register,
        igMemoryImage_GetPublishedMetaObject,
        thunk_igPsx2Image_GetMetaObject,
        igPsx2Image_className,
        0x5C, /* instance size */
        igPsx2Image_GetVTable,
        &igPsx2Image_InitFields_00153ef0[0],           /* Field adder. */
        0,                                             /* extra callback-vector item (none) */
        0                                              /* zero-terminated callback-vector item list (none) */
    );
}

int FUN_00153ee0(void) {
    return DAT_0055fd70[0];
}

void FUN_00153ef0(void) {
    *(int *)((char *)(DAT_005605e0[0]) + 64) = (int)(&thunk_igImage_GetMetaObject);
}

