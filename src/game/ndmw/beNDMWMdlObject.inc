igMetaObject *g_beNDMWMdlObject_metaObject;

void beNDMWMdlObject_CreateInstance(int arg0) {
    beNDMWMdlObject_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWMdlObject_metaObject, arg0);
}

igMetaObject *beNDMWMdlObject_GetOrCreateMetaObject(void) {
    if (g_beNDMWMdlObject_metaObject == 0) {
        g_beNDMWMdlObject_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beNDMWMdlObject_metaObject;
}

void *beNDMWMdlObject_GetReadyMetaObject(void) {
    igMetaObject *g = g_beNDMWMdlObject_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWMdlObject_EnsureRegistered();
    }
    return g_beNDMWMdlObject_metaObject;
}

int beNDMWMdlObject_GetVTable(void) {
    struct W_3c0c30 o;
    int r;

    igObject_InitHeader(&o);
    o.w[1] = 0;
    o.w[5] = 0;
    o.vt = g_beNDMWMdlObject_vtable;
    r = *(int *)((char *)&o + *(int *)(((char * *)g_objectSystem)[0] + 916));
    o.vt = g_beNDMWMdlObject_vtable;
    FUN_003bf2f0((struct NamedRefObject *)&o, (long long)0);
    return r;
}

void beNDMWMdlObject_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWMdlObject_Register);
}

void *beNDMWMdlObject_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWMdlObject_metaObject,
        beModelCtrl_Register,
        beModelCtrl_GetPublishedMetaObject,
        beNDMWMdlObject_GetMetaObject,
        "beNDMWMdlObject",
        0x2c, /* instance size */
        beNDMWMdlObject_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWMdlObject_GetMetaObject(void)
{
    beNDMWMdlObject_GetReadyMetaObject();
}

