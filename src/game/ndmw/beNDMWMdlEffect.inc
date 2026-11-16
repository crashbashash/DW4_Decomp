igMetaObject *g_beNDMWMdlEffect_metaObject;

void beNDMWMdlEffect_CreateInstance(int arg0) {
    beNDMWMdlEffect_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWMdlEffect_metaObject, arg0);
}

igMetaObject *beNDMWMdlEffect_GetOrCreateMetaObject(void) {
    if (g_beNDMWMdlEffect_metaObject == 0) {
        g_beNDMWMdlEffect_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beNDMWMdlEffect_metaObject;
}

void *beNDMWMdlEffect_GetReadyMetaObject(void) {
    igMetaObject *g = g_beNDMWMdlEffect_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWMdlEffect_EnsureRegistered();
    }
    return g_beNDMWMdlEffect_metaObject;
}

int beNDMWMdlEffect_GetVTable(void) {
    struct Obj_3c1b90 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.w[1] = 0;
    obj.w[5] = 0;
    obj.vt = &g_beNDMWMdlEffect_vtable[0];
    r = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = &g_beNDMWMdlEffect_vtable[0];
    FUN_003bf2f0((struct NamedRefObject *)&obj, (long long)0);
    return r;
}

void beNDMWMdlEffect_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWMdlEffect_Register);
}

void *beNDMWMdlEffect_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWMdlEffect_metaObject,
        beModelCtrl_Register,
        beModelCtrl_GetPublishedMetaObject,
        beNDMWMdlEffect_GetMetaObject,
        "beNDMWMdlEffect",
        0x2c, /* instance size */
        beNDMWMdlEffect_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWMdlEffect_GetMetaObject(void)
{
    beNDMWMdlEffect_GetReadyMetaObject();
}

