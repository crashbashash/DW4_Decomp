igMetaObject *FUN_00355030(void) {
    if (g_beModelCtrlWCHECK_metaObject[0] == 0 || !isValid(g_beModelCtrlWCHECK_metaObject[0])) FUN_00355110();
    return g_beModelCtrlWCHECK_metaObject[0];
}

int beModelCtrlWCHECK_GetVTable(void) {
    union U_355080 u;
    int s0;
    char *ps;
    int *v1;
    int *a1;
    int v0;

    igObject_InitHeader(u.b);
    ps = &u.b[8];
    *(int *)ps = 0;
    u.vt = (int)&g_igNamedObject_vtable[0];
    u.vt = (int)&DAT_005376b0[0];
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

void FUN_00355110(void)
{
    igMetaObject_RunStaticInit(beModelCtrlWCHECK_Register);
}

void *beModelCtrlWCHECK_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beModelCtrlWCHECK_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beModelCtrlWCHECK_GetMetaObject,
        beModelCtrlWCHECK_className,
        0xc, /* instance size */
        beModelCtrlWCHECK_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlWCHECK_GetMetaObject(void)
{
    FUN_00355030();
}

