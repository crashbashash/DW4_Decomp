void *FUN_00355bd0(void) {
    igMetaObject *g = g_beModelCtrlCTRL_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00355cb0();
    }
    return g_beModelCtrlCTRL_metaObject[0];
}

int beModelCtrlCTRL_GetVTable(void) {
    union U_355c20 u;
    int temp_s0;
    char *ps;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    ps = &u.b[8];
    *(int *)ps = 0;
    u.vt = (int)&g_igNamedObject_vtable[0];
    u.vt = (int)&DAT_00537470[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_igNamedObject_vtable[0];
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

void FUN_00355cb0(void)
{
    igMetaObject_RunStaticInit(beModelCtrlCTRL_Register);
}

void *beModelCtrlCTRL_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlCTRL_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beModelCtrlCTRL_GetMetaObject,
        beModelCtrlCTRL_className,
        0xc, /* instance size */
        beModelCtrlCTRL_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlCTRL_GetMetaObject(void)
{
    FUN_00355bd0();
}

