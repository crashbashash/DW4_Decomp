void *FUN_003bba30(void) {
    igMetaObject *g = g_beNDMWStageCtlInfoRam_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003bbb20();
    }
    return g_beNDMWStageCtlInfoRam_metaObject[0];
}

int beNDMWStageCtlInfoRam_GetVTable(void) {
    union U_3bba80 u;
    int temp_s0;
    S_ref *q1;

    igObject_InitHeader(u.b);
    u.w[0] = (int)(&DAT_00539e90[0]);
    q1 = (S_ref *)&u.b[40];
    *(int *)q1 = 0;
    u.w[0] = (int)(&DAT_0053da40[0]);
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.w[0] = (int)(&DAT_00539e90[0]);
    if (q1 != 0) {
        q1 = *(S_ref **)q1;
        if (q1 != 0) {
            q1->f4 = (int)((int) (q1->f4 - 1));
            if (((unsigned long long) ((long long) q1->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q1);
            }
        }
    }
    return temp_s0;
}

void FUN_003bbb20(void)
{
    igMetaObject_RunStaticInit(beNDMWStageCtlInfoRam_Register);
}

void *beNDMWStageCtlInfoRam_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWStageCtlInfoRam_metaObject,
        beBaseInfoRam_Register,
        beBaseInfoRam_GetPublishedMetaObject,
        beNDMWStageCtlInfoRam_GetMetaObject,
        beNDMWStageCtlInfoRam_className,
        0x2c, /* instance size */
        beNDMWStageCtlInfoRam_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWStageCtlInfoRam_GetMetaObject(void)
{
    FUN_003bba30();
}

