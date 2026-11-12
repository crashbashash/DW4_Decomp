void *FUN_0036cfa0(void) {
    igMetaObject *g = g_beAction2WAITCHECK_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0036d080();
    }
    return g_beAction2WAITCHECK_metaObject[0];
}

int beAction2WAITCHECK_GetVTable(void) {
    union U_36cff0 u;
    int temp_s0;
    char *ps;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    ps = &u.b[8];
    *(int *)ps = 0;
    u.vt = (int)&g_igNamedObject_vtable[0];
    u.vt = (int)&DAT_005341b0[0];
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

void FUN_0036d080(void)
{
    igMetaObject_RunStaticInit(beAction2WAITCHECK_Register);
}

void *beAction2WAITCHECK_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beAction2WAITCHECK_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beAction2WAITCHECK_GetMetaObject,
        beAction2WAITCHECK_className,
        0x10, /* instance size */
        beAction2WAITCHECK_GetVTable,
        beAction2WAITCHECK_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beAction2WAITCHECK_GetMetaObject(void)
{
    FUN_0036cfa0();
}

void beAction2WAITCHECK_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beAction2WAITCHECK_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c8100[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_004c8108[0], &DAT_004c8110[0], &DAT_004c8118[0], temp_s1);
}

