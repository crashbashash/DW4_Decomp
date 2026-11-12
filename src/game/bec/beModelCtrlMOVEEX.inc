void *FUN_00355640(void) {
    bool ok;
    if (g_beModelCtrlMOVEEX_metaObject[0] == 0) goto make;
    ok = !!(g_beModelCtrlMOVEEX_metaObject[0]->_validity & 4);
    if (ok != false) goto done;
make:
    FUN_00355720();
done:;
    return g_beModelCtrlMOVEEX_metaObject[0];
}

int beModelCtrlMOVEEX_GetVTable(void) {
    union U u;
    int temp_s0;
    char *ps;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    ps = &u.b[8];
    *(int *)ps = 0;
    u.vt = (int)&g_igNamedObject_vtable[0];
    u.vt = (int)&DAT_00537590[0];
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

void FUN_00355720(void)
{
    igMetaObject_RunStaticInit(beModelCtrlMOVEEX_Register);
}

void *beModelCtrlMOVEEX_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlMOVEEX_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beModelCtrlMOVEEX_GetMetaObject,
        beModelCtrlMOVEEX_className,
        0x24, /* instance size */
        beModelCtrlMOVEEX_GetVTable,
        beModelCtrlMOVEEX_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlMOVEEX_GetMetaObject(void)
{
    FUN_00355640();
}

void beModelCtrlMOVEEX_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beModelCtrlMOVEEX_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004c57e0[0], 6);
    igMetaObject_NameFields(temp_s0, &DAT_004c5800[0], &DAT_004c5820[0], &DAT_004c5840[0], temp_s1);
}

