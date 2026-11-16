igMetaObject *g_beNDMWStatusSelectE0_metaObject;

void beNDMWStatusSelectE0_Create(int allocator) {
    beNDMWStatusSelectE0_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWStatusSelectE0_metaObject, allocator);
}

igMetaObject *beNDMWStatusSelectE0_GetMetaObject(void)
{
    igMetaObject *g = g_beNDMWStatusSelectE0_metaObject;
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        beNDMWStatusSelectE0_EnsureRegistered();
    return g_beNDMWStatusSelectE0_metaObject;
}

int beNDMWStatusSelectE0_GetVTable(void) {
    struct W_3b5400 o;
    int r;

    igObject_InitHeader(&o);
    o.f[12] = 0;
    o.f[13] = 0;
    o.f[14] = 0;
    o.f[15] = 0;
    o.f[16] = 0;
    o.f[17] = 0;
    o.f[18] = 0;
    o.f[19] = 0;
    o.f[26] = 0;
    o.vt = g_beNDMWStatusSelectE0_vtable;
    r = *(int *)((char *)&o + *(int *)(((char * *)g_objectSystem)[0] + 916));
    o.vt = g_beNDMWStatusSelectE0_vtable;
    FUN_003b4050((struct S_3b4050 *)&o, (short)0);
    return r;
}

void beNDMWStatusSelectE0_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusSelectE0_Register);
}

void *beNDMWStatusSelectE0_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWStatusSelectE0_metaObject,
        beNDMWWindowSelect_Register,
        beNDMWWindowSelect_GetPublishedMetaObject,
        beNDMWStatusSelectE0_GetMetaObjectFunction,
        "beNDMWStatusSelectE0",
        0x70, /* instance size */
        beNDMWStatusSelectE0_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWStatusSelectE0_GetMetaObjectFunction(void)
{
    beNDMWStatusSelectE0_GetMetaObject();
}

