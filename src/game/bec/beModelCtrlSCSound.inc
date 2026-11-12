void FUN_0034f4a0(int arg0) {
    FUN_0034f5c0();
    igMetaObject_CreateInstance(*(int *)0x5887B0, arg0);
}

igMetaObject *FUN_0034f4e0(void) {
    igMetaObject *g = g_beModelCtrlSCSound_metaObject[0];
    if (g != 0) {
        int b = !!(g->_validity & 4);
        if (b) goto done;
    }
    FUN_0034f5c0();
done:
    return g_beModelCtrlSCSound_metaObject[0];
}

int beModelCtrlSCSound_GetVTable(void) {
    union U_34f530 u;
    int temp_s0;
    char *ps;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_0053ae80[0];
    ps = &u.b[20];
    *(int *)ps = 0;
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&DAT_0053ae80[0];
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

void FUN_0034f5c0(void)
{
    igMetaObject_RunStaticInit(beModelCtrlSCSound_Register);
}

void *beModelCtrlSCSound_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlSCSound_metaObject,
        beModelCtrlSubComBase_Register,
        beModelCtrlSubComBase_GetPublishedMetaObject,
        beModelCtrlSCSound_GetMetaObject,
        beModelCtrlSCSound_className,
        0x20, /* instance size */
        beModelCtrlSCSound_GetVTable,
        beModelCtrlSCSound_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlSCSound_GetMetaObject(void)
{
    FUN_0034f4e0();
}

igMetaObject *FUN_0034f670(void) {
    return g_beModelCtrlSubComBase_metaObject[0];
}

void beModelCtrlSCSound_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beModelCtrlSCSound_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c4be0[0], 2);
    igMetaObject_NameFields(temp_s0, &DAT_004c4be8[0], &DAT_004c4bf0[0], &DAT_004c4bf8[0], temp_s1);
}

