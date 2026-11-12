void *FUN_0035c280(void) {
    igMetaObject *g = g_beLayerInfoRam_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0035c370();
    }
    return g_beLayerInfoRam_metaObject[0];
}

int beLayerInfoRam_GetVTable(void) {
    union U u;
    S_ref *q0;
    int temp_s0;

    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00539e90[0];
    q0 = (S_ref *)&u.b[40];
    *(int *)q0 = 0;
    u.vt = (int)&DAT_00536680[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_00539e90[0];
    if (q0 != 0) {
        q0 = *(S_ref **)q0;
        if (q0 != 0) {
            q0->f4 = (int)((int) (q0->f4 - 1));
            if (((unsigned long long) ((long long) q0->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(q0);
            }
        }
    }
    return temp_s0;
}

void FUN_0035c370(void)
{
    igMetaObject_RunStaticInit(beLayerInfoRam_Register);
}

void *beLayerInfoRam_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beLayerInfoRam_metaObject,
        beBaseInfoRam_Register,
        beBaseInfoRam_GetPublishedMetaObject,
        beLayerInfoRam_GetMetaObject,
        beLayerInfoRam_className,
        0x2c, /* instance size */
        beLayerInfoRam_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beLayerInfoRam_GetMetaObject(void)
{
    FUN_0035c280();
}

