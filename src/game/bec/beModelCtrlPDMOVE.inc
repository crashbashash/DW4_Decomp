void *FUN_003551c0(void) {
    struct G *g = DAT_00588d70[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003552a0();
    }
    return DAT_00588d70[0];
}

int beModelCtrlPDMOVE_GetVTable(void) {
    union U_355210 u;
    int temp_s0;
    char *ps;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    ps = &u.b[8];
    *(int *)ps = 0;
    u.vt = (int)&DAT_00524950[0];
    u.vt = (int)&DAT_00537650[0];
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

void FUN_003552a0(void)
{
    igMetaObject_RunStaticInit(beModelCtrlPDMOVE_Register);
}

void *beModelCtrlPDMOVE_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlPDMOVE_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beModelCtrlPDMOVE_GetMetaObject,
        beModelCtrlPDMOVE_className,
        0x14, /* instance size */
        beModelCtrlPDMOVE_GetVTable,
        beModelCtrlPDMOVE_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlPDMOVE_GetMetaObject(void)
{
    FUN_003551c0();
}

void beModelCtrlPDMOVE_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_00588d70)[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c5798[0], 2);
    igMetaObject_NameFields(temp_s0, &DAT_004c57a0[0], &DAT_004c57a8[0], &DAT_004c57b0[0], temp_s1);
}

