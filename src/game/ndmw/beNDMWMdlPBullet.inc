igMetaObject *g_beNDMWMdlPBullet_metaObject;

void beNDMWMdlPBullet_CreateInstance(int arg0) {
    beNDMWMdlPBullet_EnsureRegistered();
    igMetaObject_CreateInstance(g_beNDMWMdlPBullet_metaObject, arg0);
}

igMetaObject *beNDMWMdlPBullet_GetOrCreateMetaObject(void) {
    if (g_beNDMWMdlPBullet_metaObject == 0) {
        g_beNDMWMdlPBullet_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beNDMWMdlPBullet_metaObject;
}

void *beNDMWMdlPBullet_GetReadyMetaObject(void) {
    igMetaObject *g = g_beNDMWMdlPBullet_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        beNDMWMdlPBullet_EnsureRegistered();
    }
    return g_beNDMWMdlPBullet_metaObject;
}

int beNDMWMdlPBullet_GetVTable(void) {
    struct F_3c0a40 f;
    int temp_s0;

    igObject_InitHeader(&f);
    f.w[1] = 0;
    f.w[5] = 0;
    f.vt = &g_beNDMWMdlPBullet_vtable[0];
    temp_s0 = *(int *)((char *)&f + *(int *)((char *)(g_objectSystem[0]) + 916));
    f.vt = &g_beNDMWMdlPBullet_vtable[0];
    FUN_003bf2f0((struct NamedRefObject *)&f, (long long)0);
    return temp_s0;
}

void beNDMWMdlPBullet_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(beNDMWMdlPBullet_Register);
}

void *beNDMWMdlPBullet_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beNDMWMdlPBullet_metaObject,
        beModelCtrl_Register,
        beModelCtrl_GetPublishedMetaObject,
        beNDMWMdlPBullet_GetMetaObject,
        "beNDMWMdlPBullet",
        0x2c, /* instance size */
        beNDMWMdlPBullet_GetVTable,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWMdlPBullet_GetMetaObject(void)
{
    beNDMWMdlPBullet_GetReadyMetaObject();
}

