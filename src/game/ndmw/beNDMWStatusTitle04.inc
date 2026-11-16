igMetaObject *g_beNDMWStatusTitle04_metaObject;

void beNDMWStatusTitle04_Create(int allocator) {
    beNDMWStatusTitle04_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWStatusTitle04_metaObject, allocator);
}

void *beNDMWStatusTitle04_GetMetaObject(void) {
    igMetaObject *g = g_beNDMWStatusTitle04_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWStatusTitle04_EnsureRegistered();
    }
    return g_beNDMWStatusTitle04_metaObject;
}

int beNDMWStatusTitle04_GetVTable(void) {
    Obj_3b35c0 o;
    int r;

    igObject_InitHeader(&o);
    o.w[12] = 0;
    o.w[13] = 0;
    o.w[14] = 0;
    o.w[15] = 0;
    o.w[16] = 0;
    o.w[17] = 0;
    o.w[18] = 0;
    o.vt = &g_beNDMWStatusTitle04_vtable[0];
    r = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
    o.vt = &g_beNDMWStatusTitle04_vtable[0];
    FUN_003b3030((int **)&o, (long long)0);
    return r;
}

void beNDMWStatusTitle04_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWStatusTitle04_Register);
}

void *beNDMWStatusTitle04_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWStatusTitle04_metaObject,
        beNDMWWindowTitle_Register,
        beNDMWWindowTitle_GetPublishedMetaObject,
        beNDMWStatusTitle04_GetMetaObjectFunction,
        "beNDMWStatusTitle04",
        0x50, /* instance size */
        beNDMWStatusTitle04_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWStatusTitle04_GetMetaObjectFunction(void)
{
    beNDMWStatusTitle04_GetMetaObject();
}

