void *FUN_003553c0(void) {
    struct G *g = DAT_00588d88[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00355520();
    }
    return DAT_00588d88[0];
}

int beModelCtrlMOVERL_GetVTable(void) {
    union U_355410 u;
    int r;
    int *v1;
    int *a1;
    int v0;
    char *p4C;
    char *p48;
    char *p50;

    igObject_InitHeader(u.b);
    p48 = &u.b[8];
    *(int *)p48 = 0;
    u.vt = (int)&DAT_005375f0[0];
    p4C = &u.b[12];
    *(int *)p4C = 0;
    p50 = &u.b[16];
    *(int *)p50 = 0;
    r = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_005375f0[0];
    if (p50 != 0) {
        v1 = *(int **)p50;
        if (v1 != 0) {
            a1 = v1 - 2;
            v0 = v1[-1] - 1;
            v1[-1] = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    if (p4C != 0) {
        v1 = *(int **)p4C;
        if (v1 != 0) {
            a1 = v1 - 2;
            v0 = v1[-1] - 1;
            v1[-1] = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    u.vt = (int)&DAT_00524950[0];
    if (p48 != 0) {
        v1 = *(int **)p48;
        if (v1 != 0) {
            a1 = v1 - 2;
            v0 = v1[-1] - 1;
            v1[-1] = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    return r;
}

void FUN_00355520(void)
{
    igMetaObject_RunStaticInit(beModelCtrlMOVERL_Register);
}

void *beModelCtrlMOVERL_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlMOVERL_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beModelCtrlMOVERL_GetMetaObject,
        beModelCtrlMOVERL_className,
        0x14, /* instance size */
        beModelCtrlMOVERL_GetVTable,
        beModelCtrlMOVERL_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlMOVERL_GetMetaObject(void)
{
    FUN_003553c0();
}

void beModelCtrlMOVERL_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_00588d88)[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c57b8[0], 2);
    igMetaObject_NameFields(temp_s0, &DAT_004c57c0[0], &DAT_004c57c8[0], &DAT_004c57d0[0], temp_s1);
}

