void FUN_003ca1a0(int arg0) {
    FUN_003ca2d0();
    igMetaObject_CreateInstance(*(int *)0x58C100, arg0);
}

igMetaObject *beNDMWGameRamInfoRam_ResolveMetaObject(void) {
    if (g_beNDMWGameRamInfoRam_metaObject[0] == 0 || !isValid(g_beNDMWGameRamInfoRam_metaObject[0])) FUN_003ca2d0();
    return g_beNDMWGameRamInfoRam_metaObject[0];
}

int beNDMWGameRamInfoRam_GetVTable(void) {
    union U_3ca230 u;
    int temp_s0;
    char *q1;
    int *a0;

    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00539e90[0];
    q1 = &u.b[40];
    *(int *)q1 = 0;
    u.vt = (int)&DAT_0053c550[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_00539e90[0];
    if (q1 != 0) {
        a0 = *(int **)q1;
        if (a0 != 0) {
            a0[1] = a0[1] - 1;
            if ((a0[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(a0);
            }
        }
    }
    return temp_s0;
}

void FUN_003ca2d0(void)
{
    igMetaObject_RunStaticInit(beNDMWGameRamInfoRam_Register);
}

void *beNDMWGameRamInfoRam_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWGameRamInfoRam_metaObject,
        beBaseInfoRam_Register,
        beBaseInfoRam_GetPublishedMetaObject,
        beNDMWGameRamInfoRam_GetMetaObject,
        beNDMWGameRamInfoRam_className,
        0x2c, /* instance size */
        beNDMWGameRamInfoRam_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWGameRamInfoRam_GetMetaObject(void)
{
    beNDMWGameRamInfoRam_ResolveMetaObject();
}

