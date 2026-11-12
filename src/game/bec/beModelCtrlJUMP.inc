void *FUN_00355d60(void) {
    igMetaObject *g = g_beModelCtrlJUMP_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00355e40();
    }
    return g_beModelCtrlJUMP_metaObject[0];
}

int beModelCtrlJUMP_GetVTable(void) {
    union U_355db0 u;
    int s0;
    char *ps;
    int *v1;
    int *a1;
    int v0;

    igObject_InitHeader(u.b);
    ps = &u.b[8];
    *(int *)ps = 0;
    u.vt = (int)&DAT_00524950[0];
    u.vt = (int)&DAT_00537410[0];
    s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_00524950[0];
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
    return s0;
}

void FUN_00355e40(void)
{
    igMetaObject_RunStaticInit(beModelCtrlJUMP_Register);
}

void *beModelCtrlJUMP_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlJUMP_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beModelCtrlJUMP_GetMetaObject,
        beModelCtrlJUMP_className,
        0xc, /* instance size */
        beModelCtrlJUMP_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlJUMP_GetMetaObject(void)
{
    FUN_00355d60();
}

