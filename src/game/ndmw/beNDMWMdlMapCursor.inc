igMetaObject *g_beNDMWMdlMapCursor_metaObject;

void beNDMWMdlMapCursor_CreateInstance(int arg0) {
    beNDMWMdlMapCursor_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWMdlMapCursor_metaObject, arg0);
}

igMetaObject *beNDMWMdlMapCursor_GetOrCreateMetaObject(void) {
    if (g_beNDMWMdlMapCursor_metaObject == 0) {
        g_beNDMWMdlMapCursor_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beNDMWMdlMapCursor_metaObject;
}

void *beNDMWMdlMapCursor_GetReadyMetaObject(void) {
    igMetaObject *g = g_beNDMWMdlMapCursor_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWMdlMapCursor_EnsureRegistered();
    }
    return g_beNDMWMdlMapCursor_metaObject;
}

int beNDMWMdlMapCursor_GetVTable(void) {
    struct Obj_3c0e20 o;
    int r;
    igObject_InitHeader(&o);
    o.f8 = 0;
    o.f24 = 0;
    o.vt = &g_beNDMWMdlMapCursor_vtable[0];
    r = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
    o.vt = &g_beNDMWMdlMapCursor_vtable[0];
    
    FUN_003bf2f0((struct NamedRefObject *)&o, (long long)0);
    return r;
}

void beNDMWMdlMapCursor_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWMdlMapCursor_Register);
}

void *beNDMWMdlMapCursor_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWMdlMapCursor_metaObject,
        beModelCtrl_Register,
        beModelCtrl_GetPublishedMetaObject,
        beNDMWMdlMapCursor_GetMetaObject,
        "beNDMWMdlMapCursor",
        0x2c, /* instance size */
        beNDMWMdlMapCursor_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWMdlMapCursor_GetMetaObject(void)
{
    beNDMWMdlMapCursor_GetReadyMetaObject();
}

