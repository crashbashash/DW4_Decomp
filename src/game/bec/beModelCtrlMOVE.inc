void *FUN_00355840(void) {
    igMetaObject *g = g_beModelCtrlMOVE_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00355920();
    }
    return g_beModelCtrlMOVE_metaObject[0];
}

int beModelCtrlMOVE_GetVTable(void) {
    union U_355890 u;
    int temp_s0;
    char *ps;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    ps = &u.b[8];
    *(int *)ps = 0;
    u.vt = (int)&g_igNamedObject_vtable[0];
    u.vt = (int)&DAT_00537530[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_igNamedObject_vtable[0];
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

void FUN_00355920(void)
{
    igMetaObject_RunStaticInit(beModelCtrlMOVE_Register);
}

void *beModelCtrlMOVE_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlMOVE_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beModelCtrlMOVE_GetMetaObject,
        beModelCtrlMOVE_className,
        0x14, /* instance size */
        beModelCtrlMOVE_GetVTable,
        beModelCtrlMOVE_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlMOVE_GetMetaObject(void)
{
    FUN_00355840();
}

void beModelCtrlMOVE_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beModelCtrlMOVE_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beModelCtrlMOVE_ctorTable[0], 2);
    igMetaObject_NameFields(temp_s0, &g_beModelCtrlMOVE_fieldTable[0], &DAT_004c5868[0], &DAT_004c5870[0], temp_s1);
}

