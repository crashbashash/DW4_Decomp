igMetaObject *g_beNDMWMdlMapBase_metaObject;

void beNDMWMdlMapBase_CreateInstance(int arg0) {
    beNDMWMdlMapBase_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWMdlMapBase_metaObject, arg0);
}

igMetaObject *beNDMWMdlMapBase_GetOrCreateMetaObject(void) {
    if (g_beNDMWMdlMapBase_metaObject == 0) {
        g_beNDMWMdlMapBase_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beNDMWMdlMapBase_metaObject;
}

igMetaObject *beNDMWMdlMapBase_GetReadyMetaObject(void)
{
    igMetaObject *g = g_beNDMWMdlMapBase_metaObject;
    bool t;
    if (!g || (t = g->_validity & 4) == 0)
        beNDMWMdlMapBase_EnsureRegistered();
    return g_beNDMWMdlMapBase_metaObject;
}

int beNDMWMdlMapBase_GetVTable(void) {
    struct Obj_3c1010 obj;
    int temp_s0;

    igObject_InitHeader(&obj);
    obj.f8 = 0;
    obj.f18 = 0;
    obj.vt = (&g_beNDMWMdlMapBase_vtable[0]);
    temp_s0 = *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
    obj.vt = (&g_beNDMWMdlMapBase_vtable[0]);
    FUN_003bf2f0((struct NamedRefObject *)&obj, (long long)0);
    return temp_s0;
}

void beNDMWMdlMapBase_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWMdlMapBase_Register);
}

void *beNDMWMdlMapBase_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWMdlMapBase_metaObject,
        beModelCtrl_Register,
        beModelCtrl_GetPublishedMetaObject,
        beNDMWMdlMapBase_GetMetaObject,
        "beNDMWMdlMapBase",
        0x2c, /* instance size */
        beNDMWMdlMapBase_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWMdlMapBase_GetMetaObject(void)
{
    beNDMWMdlMapBase_GetReadyMetaObject();
}

