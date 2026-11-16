igMetaObject *g_beNDMWStatusTitle02_metaObject;

void beNDMWStatusTitle02_Create(int arg0) {
    beNDMWStatusTitle02_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWStatusTitle02_metaObject, arg0);
}

igMetaObject *beNDMWStatusTitle02_GetMetaObject(void)
{
    igMetaObject *g = g_beNDMWStatusTitle02_metaObject;
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        beNDMWStatusTitle02_EnsureRegistered();
    return g_beNDMWStatusTitle02_metaObject;
}

int beNDMWStatusTitle02_GetVTable(void) {
    struct W o;
    int r;

    igObject_InitHeader(&o);
    o.f[12] = 0;
    o.f[13] = 0;
    o.f[14] = 0;
    o.f[15] = 0;
    o.f[16] = 0;
    o.f[17] = 0;
    o.f[18] = 0;
    o.vt = g_beNDMWStatusTitle02_vtable;
    r = *(int *)((char *)&o + *(int *)(((char * *)g_objectSystem)[0] + 916));
    o.vt = g_beNDMWStatusTitle02_vtable;
    FUN_003b3030((int **)&o, (long long)0);
    return r;
}

void beNDMWStatusTitle02_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusTitle02_Register);
}

void *beNDMWStatusTitle02_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWStatusTitle02_metaObject,
        beNDMWWindowTitle_Register,
        beNDMWWindowTitle_GetPublishedMetaObject,
        beNDMWStatusTitle02_GetMetaObjectFunction,
        "beNDMWStatusTitle02",
        0x50, /* instance size */
        beNDMWStatusTitle02_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWStatusTitle02_GetMetaObjectFunction(void)
{
    beNDMWStatusTitle02_GetMetaObject();
}

