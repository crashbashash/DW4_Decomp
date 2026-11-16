igMetaObject *g_beNDMWMdlEBullet_metaObject;

void beNDMWMdlEBullet_CreateInstance(int allocator) {
    beNDMWMdlEBullet_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWMdlEBullet_metaObject, allocator);
}

igMetaObject *beNDMWMdlEBullet_GetOrCreateMetaObject(void) {
    if (g_beNDMWMdlEBullet_metaObject == 0) {
        g_beNDMWMdlEBullet_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beNDMWMdlEBullet_metaObject;
}

void *beNDMWMdlEBullet_GetReadyMetaObject(void) {
    bool ok;
    if (g_beNDMWMdlEBullet_metaObject == 0) goto make;
    ok = !!(g_beNDMWMdlEBullet_metaObject->_validity & 4);
    if (ok != false) goto done;
make:
    beNDMWMdlEBullet_EnsureRegistered();
done:;
    return g_beNDMWMdlEBullet_metaObject;
}

int beNDMWMdlEBullet_GetVTable(void) {
    union U_3c1d80 u;
    int temp_s0;

    igObject_InitHeader(u.b);
    *(int *)&u.b[8] = 0;
    *(int *)&u.b[24] = 0;
    u.vt = (int)&g_beNDMWMdlEBullet_vtable[0];
    temp_s0 = *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
    u.vt = (int)&g_beNDMWMdlEBullet_vtable[0];
    FUN_003bf2f0((struct NamedRefObject *)u.b, (long long)0);
    return temp_s0;
}

void beNDMWMdlEBullet_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWMdlEBullet_Register);
}

void *beNDMWMdlEBullet_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWMdlEBullet_metaObject,
        beModelCtrl_Register,
        beModelCtrl_GetPublishedMetaObject,
        beNDMWMdlEBullet_GetMetaObject,
        "beNDMWMdlEBullet",
        0x2c, /* instance size */
        beNDMWMdlEBullet_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWMdlEBullet_GetMetaObject(void)
{
    beNDMWMdlEBullet_GetReadyMetaObject();
}

