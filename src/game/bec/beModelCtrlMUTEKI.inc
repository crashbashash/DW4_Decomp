G_354ca0 *FUN_00354ca0(void) {
    G_354ca0 *g = DAT_00588d50[0];
    int t;
    if (!g || !(t = (g->f & 4) != 0))
        FUN_00354d80();
    return DAT_00588d50[0];
}

int beModelCtrlMUTEKI_GetVTable(void) {
    union U_354cf0 u;
    int temp_s0;
    char *ps;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    ps = &u.b[8];
    *(int *)ps = 0;
    u.vt = (int)&DAT_00524950[0];
    u.vt = (int)&DAT_00537770[0];
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

void FUN_00354d80(void)
{
    igMetaObject_RunStaticInit(beModelCtrlMUTEKI_Register);
}

void *beModelCtrlMUTEKI_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlMUTEKI_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beModelCtrlMUTEKI_GetMetaObject,
        beModelCtrlMUTEKI_className,
        0x10, /* instance size */
        beModelCtrlMUTEKI_GetVTable,
        beModelCtrlMUTEKI_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlMUTEKI_GetMetaObject(void)
{
    FUN_00354ca0();
}

void beModelCtrlMUTEKI_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_00588d50)[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c5778[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_004c5780[0], &DAT_004c5788[0], &DAT_004c5790[0], temp_s1);
}

