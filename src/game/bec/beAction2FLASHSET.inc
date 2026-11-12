void *FUN_0036ce10(void) {
    igMetaObject *g = g_beAction2FLASHSET_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0036cef0();
    }
    return g_beAction2FLASHSET_metaObject[0];
}

int beAction2FLASHSET_GetVTable(void) {
    union U_36ce60 u;
    int temp_s0;
    char *ps;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    ps = &u.b[8];
    *(int *)ps = 0;
    u.vt = (int)&g_igNamedObject_vtable[0];
    u.vt = (int)&DAT_00534210[0];
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

void FUN_0036cef0(void)
{
    igMetaObject_RunStaticInit(beAction2FLASHSET_Register);
}

void *beAction2FLASHSET_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beAction2FLASHSET_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beAction2FLASHSET_GetMetaObject,
        beAction2FLASHSET_className,
        0xc, /* instance size */
        beAction2FLASHSET_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beAction2FLASHSET_GetMetaObject(void)
{
    FUN_0036ce10();
}

