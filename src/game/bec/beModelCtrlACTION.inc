void *FUN_00355ef0(void) {
    struct G *g = DAT_00588e08[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00355fd0();
    }
    return DAT_00588e08[0];
}

int beModelCtrlACTION_GetVTable(void) {
    union U_355f40 u;
    int temp_s0;
    char *ps;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    ps = &u.b[8];
    *(int *)ps = 0;
    u.vt = (int)&DAT_00524950[0];
    u.vt = (int)&DAT_005373b0[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
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

void FUN_00355fd0(void)
{
    igMetaObject_RunStaticInit(beModelCtrlACTION_Register);
}

void *beModelCtrlACTION_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlACTION_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beModelCtrlACTION_GetMetaObject,
        beModelCtrlACTION_className,
        0xc, /* instance size */
        beModelCtrlACTION_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlACTION_GetMetaObject(void)
{
    FUN_00355ef0();
}

