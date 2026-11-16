igMetaObject *g_beNDMWStatusSelect01_metaObject;

void beNDMWStatusSelect01_Create(int arg0) {
    beNDMWStatusSelect01_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWStatusSelect01_metaObject, arg0);
}

igMetaObject *beNDMWStatusSelect01_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWStatusSelect01_metaObject;
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        beNDMWStatusSelect01_EnsureRegistered();
    return g_beNDMWStatusSelect01_metaObject;
}

int beNDMWStatusSelect01_GetVTable(void) {
    union U_3b55c0 u;
    int t;

    igObject_InitHeader(u.b);
    *(int *)&u.b[52] = 0;
    *(int *)&u.b[56] = 0;
    *(int *)&u.b[60] = 0;
    *(int *)&u.b[64] = 0;
    *(int *)&u.b[68] = 0;
    *(int *)&u.b[72] = 0;
    *(int *)&u.b[76] = 0;
    *(int *)&u.b[80] = 0;
    *(int *)&u.b[108] = 0;
    u.vt = (int)&g_beNDMWStatusSelect01_vtable[0];
    t = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_beNDMWStatusSelect01_vtable[0];
    FUN_003b4050((struct S_3b4050 *)u.b, (short)0);
    return t;
}

void beNDMWStatusSelect01_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusSelect01_Register);
}

void *beNDMWStatusSelect01_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWStatusSelect01_metaObject,
        beNDMWWindowSelect_Register,
        beNDMWWindowSelect_GetPublishedMetaObject,
        beNDMWStatusSelect01_GetMetaObjectFunction,
        "beNDMWStatusSelect01",
        0x70, /* instance size */
        beNDMWStatusSelect01_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWStatusSelect01_GetMetaObjectFunction(void)
{
    beNDMWStatusSelect01_GetMetaObject();
}

