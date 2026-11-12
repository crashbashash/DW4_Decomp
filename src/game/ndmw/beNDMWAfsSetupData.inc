void *beNDMWAfsSetupData_ResolveMetaObject(void) {
    struct G *g = DAT_0058c130[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003caa70();
    }
    return DAT_0058c130[0];
}

int beNDMWAfsSetupData_GetVTable(void) {
    union U_3ca9e0 u;
    int temp_s0;
    char *ps;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    ps = &u.b[8];
    *(int *)ps = 0;
    u.vt = (int)&DAT_00524950[0];
    u.vt = (int)&DAT_0053c3a0[0];
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

void FUN_003caa70(void)
{
    igMetaObject_RunStaticInit(beNDMWAfsSetupData_Register);
}

void *beNDMWAfsSetupData_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWAfsSetupData_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beNDMWAfsSetupData_GetMetaObject,
        beNDMWAfsSetupData_className,
        0x10, /* instance size */
        beNDMWAfsSetupData_GetVTable,
        beNDMWAfsSetupData_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWAfsSetupData_GetMetaObject(void)
{
    beNDMWAfsSetupData_ResolveMetaObject();
}

void beNDMWAfsSetupData_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_0058c130)[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004cc5d8[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_004cc5e0[0], &DAT_004cc5e8[0], &DAT_004cc5f0[0], temp_s1);
}

