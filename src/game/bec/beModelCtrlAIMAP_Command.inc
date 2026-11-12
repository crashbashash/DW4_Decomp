igMetaObject *FUN_00354ea0(void) {
    igMetaObject *g = g_beModelCtrlAIMAP_metaObject[0];
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    FUN_00354f80();
done:
    return g_beModelCtrlAIMAP_metaObject[0];
}

int beModelCtrlAIMAP_GetVTable(void) {
    union U_354ef0 u;
    int temp_s0;
    char *ps;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    ps = &u.b[8];
    *(int *)ps = 0;
    u.vt = (int)&DAT_00524950[0];
    u.vt = (int)&DAT_00537710[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
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

void FUN_00354f80(void)
{
    igMetaObject_RunStaticInit(beModelCtrlAIMAP_Register);
}

void *beModelCtrlAIMAP_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlAIMAP_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beModelCtrlAIMAP_GetMetaObject,
        beModelCtrlAIMAP_className,
        0xc, /* instance size */
        beModelCtrlAIMAP_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlAIMAP_GetMetaObject(void)
{
    FUN_00354ea0();
}

