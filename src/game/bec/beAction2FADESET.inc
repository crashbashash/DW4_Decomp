void *FUN_0036d1a0(void) {
    bool ok;
    if (g_beAction2FADESET_metaObject[0] == 0) goto make;
    ok = !!(g_beAction2FADESET_metaObject[0]->_validity & 4);
    if (ok != false) goto done;
make:
    FUN_0036d280();
done:;
    return g_beAction2FADESET_metaObject[0];
}

int beAction2FADESET_GetVTable(void) {
    union U_36d1f0 u;
    int s0;
    char *ps;
    int *v1;
    int *a1;
    int v0;

    igObject_InitHeader(u.b);
    ps = &u.b[8];
    *(int *)ps = 0;
    u.vt = (int)&g_igNamedObject_vtable[0];
    u.vt = (int)&DAT_00534150[0];
    s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_igNamedObject_vtable[0];
    if (ps != 0) {
        v1 = *(int **)ps;
        if (v1 != 0) {
            a1 = v1 - 2;
            v0 = v1[-1] - 1;
            v1[-1] = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    return s0;
}

void FUN_0036d280(void)
{
    igMetaObject_RunStaticInit(beAction2FADESET_Register);
}

void *beAction2FADESET_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beAction2FADESET_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beAction2FADESET_GetMetaObject,
        beAction2FADESET_className,
        0x14, /* instance size */
        beAction2FADESET_GetVTable,
        beAction2FADESET_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beAction2FADESET_GetMetaObject(void)
{
    FUN_0036d1a0();
}

void beAction2FADESET_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beAction2FADESET_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &g_beAction2FADESET_ctorTable[0], 2);
    igMetaObject_NameFields(temp_s0, &g_beAction2FADESET_fieldTable[0], &DAT_004c8130[0], &DAT_004c8138[0], temp_s1);
}

