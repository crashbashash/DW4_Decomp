igMetaObject *g_beNDMWStatusTitle01_metaObject;

void beNDMWStatusTitle01_Create(int allocator) {
    beNDMWStatusTitle01_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWStatusTitle01_metaObject, allocator);
}

igMetaObject *beNDMWStatusTitle01_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWStatusTitle01_metaObject;
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        beNDMWStatusTitle01_EnsureRegistered();
    return g_beNDMWStatusTitle01_metaObject;
}

int beNDMWStatusTitle01_GetVTable(void) {
    union U_3b3b50 u;
    int t;

    igObject_InitHeader(u.b);
    *(int *)&u.b[52] = 0;
    *(int *)&u.b[56] = 0;
    *(int *)&u.b[60] = 0;
    *(int *)&u.b[64] = 0;
    *(int *)&u.b[68] = 0;
    *(int *)&u.b[72] = 0;
    *(int *)&u.b[76] = 0;
    u.vt = (int)&g_beNDMWStatusTitle01_vtable[0];
    t = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_beNDMWStatusTitle01_vtable[0];
    FUN_003b3030((int **)u.b, (long long)0);
    return t;
}

void beNDMWStatusTitle01_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusTitle01_Register);
}

void *beNDMWStatusTitle01_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWStatusTitle01_metaObject,
        beNDMWWindowTitle_Register,
        beNDMWWindowTitle_GetPublishedMetaObject,
        beNDMWStatusTitle01_GetMetaObjectFunction,
        "beNDMWStatusTitle01",
        0x50, /* instance size */
        beNDMWStatusTitle01_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWStatusTitle01_GetMetaObjectFunction(void)
{
    beNDMWStatusTitle01_GetMetaObject();
}

