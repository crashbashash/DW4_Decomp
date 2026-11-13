void beNDMWMdlPBullet_CreateInstance(int arg0) {
    FUN_003c0aa0();
    igMetaObject_CreateInstance(*(int *)0x58B488, arg0);
}

igMetaObject *FUN_003c09a0(void) {
    if (g_beNDMWMdlPBullet_metaObject[0] == 0) {
        g_beNDMWMdlPBullet_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_beNDMWMdlPBullet_metaObject[0];
}

void *beNDMWMdlPBullet_GetReadyMetaObject(void) {
    igMetaObject *g = g_beNDMWMdlPBullet_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003c0aa0();
    }
    return g_beNDMWMdlPBullet_metaObject[0];
}

int beNDMWMdlPBullet_GetVTable(void) {
    struct F_3c0a40 f;
    int temp_s0;

    igObject_InitHeader(&f);
    f.w[1] = 0;
    f.w[5] = 0;
    f.vt = &DAT_0053e550[0];
    temp_s0 = *(int *)((char *)&f + *(int *)((char *)(g_objectSystem[0]) + 916));
    f.vt = &DAT_0053e550[0];
    FUN_003bf2f0((struct NamedRefObject *)&f, (long long)0);
    return temp_s0;
}

void FUN_003c0aa0(void)
{
    igMetaObject_RunStaticInit(beNDMWMdlPBullet_Register);
}

void *beNDMWMdlPBullet_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWMdlPBullet_metaObject,
        beModelCtrl_Register,
        beModelCtrl_GetPublishedMetaObject,
        beNDMWMdlPBullet_GetMetaObject,
        beNDMWMdlPBullet_className,
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

