void beNDMWMdlMapCursor_CreateInstance(int arg0) {
    FUN_003c0e80();
    igMetaObject_CreateInstance(*(int *)0x58B498, arg0);
}

igMetaObject *FUN_003c0d80(void) {
    if (g_beNDMWMdlMapCursor_metaObject[0] == 0) {
        g_beNDMWMdlMapCursor_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_beNDMWMdlMapCursor_metaObject[0];
}

void *beNDMWMdlMapCursor_GetReadyMetaObject(void) {
    igMetaObject *g = g_beNDMWMdlMapCursor_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003c0e80();
    }
    return g_beNDMWMdlMapCursor_metaObject[0];
}

int beNDMWMdlMapCursor_GetVTable(void) {
    struct Obj_3c0e20 o;
    int r;
    igObject_InitHeader(&o);
    o.f8 = 0;
    o.f24 = 0;
    o.vt = &DAT_00540b40[0];
    r = *(int *)((char *)&o + *(int *)((char *)(g_objectSystem[0]) + 916));
    o.vt = &DAT_00540b40[0];
    
    FUN_003bf2f0((struct NamedRefObject *)&o, (long long)0);
    return r;
}

void FUN_003c0e80(void)
{
    igMetaObject_RunStaticInit(beNDMWMdlMapCursor_Register);
}

void *beNDMWMdlMapCursor_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWMdlMapCursor_metaObject,
        beModelCtrl_Register,
        beModelCtrl_GetPublishedMetaObject,
        beNDMWMdlMapCursor_GetMetaObject,
        beNDMWMdlMapCursor_className,
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

