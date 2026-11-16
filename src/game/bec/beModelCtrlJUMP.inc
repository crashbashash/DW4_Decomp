igMetaObject *g_beModelCtrlJUMP_metaObject;

void *beModelCtrlJUMP_GetMetaObject(void) {
    igMetaObject *g = g_beModelCtrlJUMP_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beModelCtrlJUMP_EnsureRegistered();
    }
    return g_beModelCtrlJUMP_metaObject;
}

int beModelCtrlJUMP_GetVTable(void) {
    union U_355db0 u;
    int s0;
    char *ps;
    int *v1;
    int *a1;
    int v0;

    igObject_InitHeader(u.b);
    ps = &u.b[8];
    *(int *)ps = 0;
    u.vt = (int)&g_igNamedObject_vtable[0];
    u.vt = (int)&g_beModelCtrlJUMP_vtable[0];
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

void beModelCtrlJUMP_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beModelCtrlJUMP_Register);
}

void *beModelCtrlJUMP_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beModelCtrlJUMP_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beModelCtrlJUMP_GetMetaObjectFunction,
        "beModelCtrlJUMP",
        0xc, /* instance size */
        beModelCtrlJUMP_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlJUMP_GetMetaObjectFunction(void)
{
    beModelCtrlJUMP_GetMetaObject();
}

