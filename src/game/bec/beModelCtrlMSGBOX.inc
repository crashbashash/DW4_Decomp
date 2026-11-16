igMetaObject *g_beModelCtrlMSGBOX_metaObject;

void *beModelCtrlMSGBOX_GetMetaObject(void) {
    unsigned char b;
    if (g_beModelCtrlMSGBOX_metaObject != 0) {
        b = (*(int *)((char *)(g_beModelCtrlMSGBOX_metaObject) + 36) & 4) != 0;
        if (b != 0) goto done;
    }
    beModelCtrlMSGBOX_EnsureRegistered();
done:
    return g_beModelCtrlMSGBOX_metaObject;
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
    u.w[0] = (int)(&g_igNamedObject_vtable[0]);
    u.w[0] = (int)(&g_beModelCtrlMSGBOX_vtable[0]);
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.w[0] = (int)(&g_igNamedObject_vtable[0]);
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

void beModelCtrlMSGBOX_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beModelCtrlMSGBOX_Register);
}

void *beModelCtrlMSGBOX_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beModelCtrlMSGBOX_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beModelCtrlMSGBOX_GetMetaObjectFunction,
        "beModelCtrlMSGBOX",
        0xc, /* instance size */
        beModelCtrlMSGBOX_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlMSGBOX_GetMetaObjectFunction(void)
{
    beModelCtrlMSGBOX_GetMetaObject();
}

