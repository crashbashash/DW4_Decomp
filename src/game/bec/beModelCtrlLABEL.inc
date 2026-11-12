void *FUN_003562c0(void) {
    igMetaObject *g = g_beModelCtrlLABEL_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003563a0();
    }
    return g_beModelCtrlLABEL_metaObject[0];
}

int beModelCtrlLABEL_GetVTable(void) {
    union U_356310 u;
    int temp_s0;
    char *ps;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    ps = &u.b[8];
    *(int *)ps = 0;
    u.vt = (int)&DAT_00524950[0];
    u.vt = (int)&DAT_005372f0[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_00524950[0];
    if (ps != 0) {
        temp_v1 = *(int **)ps;
        if (temp_v1 != 0) {
            temp_a1 = temp_v1 - 2;
            temp_v0 = temp_v1[-1] - 1;
            temp_v1[-1] = temp_v0;
            if (temp_v0 == 0) {
                StringChunk_ReleaseHeader(*temp_a1, temp_a1);
            }
        }
    }
    return temp_s0;
}

void FUN_003563a0(void)
{
    igMetaObject_RunStaticInit(beModelCtrlLABEL_Register);
}

void *beModelCtrlLABEL_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlLABEL_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beModelCtrlLABEL_GetMetaObject,
        beModelCtrlLABEL_className,
        0xc, /* instance size */
        beModelCtrlLABEL_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlLABEL_GetMetaObject(void)
{
    FUN_003562c0();
}

