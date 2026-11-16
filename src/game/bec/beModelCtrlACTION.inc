igMetaObject *g_beModelCtrlACTION_metaObject;

void *beModelCtrlACTION_GetMetaObject(void) {
    igMetaObject *g = g_beModelCtrlACTION_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beModelCtrlACTION_EnsureRegistered();
    }
    return g_beModelCtrlACTION_metaObject;
}

int beModelCtrlACTION_GetVTable(void) {
    union U_355f40 u;
    int temp_s0;
    char *ps;
    int *temp_v1;
    int *temp_a1;
    int temp_v0;

    igObject_InitHeader(u.b);
    ps = &u.b[8];
    *(int *)ps = 0;
    u.vt = (int)&g_igNamedObject_vtable[0];
    u.vt = (int)&g_beModelCtrlACTION_vtable[0];
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

void beModelCtrlACTION_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beModelCtrlACTION_Register);
}

void *beModelCtrlACTION_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beModelCtrlACTION_metaObject,
        igNamedObject_Register,
        igNamedObject_GetPublishedMetaObject,
        beModelCtrlACTION_GetMetaObjectFunction,
        "beModelCtrlACTION",
        0xc, /* instance size */
        beModelCtrlACTION_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beModelCtrlACTION_GetMetaObjectFunction(void)
{
    beModelCtrlACTION_GetMetaObject();
}

