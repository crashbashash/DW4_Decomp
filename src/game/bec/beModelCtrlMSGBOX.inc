void *FUN_00355a40(void) {
    unsigned char b;
    if (g_beModelCtrlMSGBOX_metaObject[0] != 0) {
        b = (*(int *)((char *)(g_beModelCtrlMSGBOX_metaObject[0]) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    FUN_00355b20();
done:
    return g_beModelCtrlMSGBOX_metaObject[0];
}

int beModelCtrlMSGBOX_GetVTable(void) {
    union U_355a90 u;
    int temp_s0;
    char *q1;
    int *tv1, *ta1;
    int tc1;

    igObject_InitHeader(u.b);
    q1 = &u.b[8];
    *(int *)q1 = 0;
    u.w[0] = (int)(&DAT_00524950[0]);
    u.w[0] = (int)(&DAT_005374d0[0]);
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.w[0] = (int)(&DAT_00524950[0]);
    if (q1 != 0) {
        tv1 = *(int **)q1;
        if (tv1 != 0) {
            ta1 = tv1 - 2;
            tc1 = tv1[-1] - 1;
            tv1[-1] = tc1;
            if (tc1 == 0) {
                StringChunk_ReleaseHeader(*ta1, ta1);
            }
        }
    }
    return temp_s0;
}

void FUN_00355b20(void)
{
    igMetaObject_RunStaticInit(beModelCtrlMSGBOX_Register);
}

void *beModelCtrlMSGBOX_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlMSGBOX_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beModelCtrlMSGBOX_GetMetaObject,
        beModelCtrlMSGBOX_className,
        0xc, /* instance size */
        beModelCtrlMSGBOX_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlMSGBOX_GetMetaObject(void)
{
    FUN_00355a40();
}

