igMetaObject *g_beNDMWStageCtlInfoRam_metaObject;

void *beNDMWStageCtlInfoRam_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWStageCtlInfoRam_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWStageCtlInfoRam_EnsureRegistered();
    }
    return g_beNDMWStageCtlInfoRam_metaObject;
}

int beNDMWStageCtlInfoRam_GetVTable(void) {
    union U_3bba80 u;
    int temp_s0;
    S_ref *q1;

    igObject_InitHeader(u.b);
    u.w[0] = (int)(&g_beBaseInfoRam_vtable[0]);
    q1 = (S_ref *)&u.b[40];
    *(int *)q1 = 0;
    u.w[0] = (int)(&g_beNDMWStageCtlInfoRam_vtable[0]);
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.w[0] = (int)(&g_beBaseInfoRam_vtable[0]);
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

void beNDMWStageCtlInfoRam_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWStageCtlInfoRam_Register);
}

void *beNDMWStageCtlInfoRam_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWStageCtlInfoRam_metaObject,
        beBaseInfoRam_Register,
        beBaseInfoRam_GetPublishedMetaObject,
        beNDMWStageCtlInfoRam_GetMetaObjectFunction,
        "beNDMWStageCtlInfoRam",
        0x2c, /* instance size */
        beNDMWStageCtlInfoRam_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWStageCtlInfoRam_GetMetaObjectFunction(void)
{
    beNDMWStageCtlInfoRam_GetMetaObject();
}

