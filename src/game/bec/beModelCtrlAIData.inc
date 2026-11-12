void *FUN_00354860(void) {
    struct G *g = DAT_00588d00[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_00354940();
    }
    return DAT_00588d00[0];
}

int beModelCtrlAIData_GetVTable(void) {
    union U_3548b0 u;
    int s0;
    char *ps;
    int *v1;
    int *a1;
    int v0;

    igObject_InitHeader(u.b);
    ps = &u.b[8];
    *(int *)ps = 0;
    u.vt = (int)&DAT_00524950[0];
    u.vt = (int)&DAT_00537830[0];
    s0 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
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

void FUN_00354940(void)
{
    igMetaObject_RunStaticInit(beModelCtrlAIData_Register);
}

void *beModelCtrlAIData_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlAIData_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beModelCtrlAIData_GetMetaObject,
        beModelCtrlAIData_className,
        0x18, /* instance size */
        beModelCtrlAIData_GetVTable,
        beModelCtrlAIData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlAIData_GetMetaObject(void)
{
    FUN_00354860();
}

void beModelCtrlAIData_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_00588d00)[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c56c0[0], 3);
    igMetaObject_NameFields(temp_s0, &DAT_004c56d0[0], &DAT_004c56e0[0], &DAT_004c56f0[0], temp_s1);
}

