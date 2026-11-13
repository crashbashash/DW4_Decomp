void beNDMWMdlObject_CreateInstance(int arg0) {
    FUN_003c0c90();
    igMetaObject_CreateInstance(*(int *)0x58B490, arg0);
}

igMetaObject *FUN_003c0b90(void) {
    if (g_beNDMWMdlObject_metaObject[0] == 0) {
        g_beNDMWMdlObject_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beNDMWMdlObject_metaObject[0];
}

void *beNDMWMdlObject_GetReadyMetaObject(void) {
    igMetaObject *g = g_beNDMWMdlObject_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003c0c90();
    }
    return g_beNDMWMdlObject_metaObject[0];
}

int beNDMWMdlObject_GetVTable(void) {
    struct W_3c0c30 o;
    int r;

    igObject_InitHeader(&o);
    o.w[1] = 0;
    o.w[5] = 0;
    o.vt = DAT_0053e480;
    r = *(int *)((char *)&o + *(int *)(((char * *)g_objectSystem)[0] + 916));
    o.vt = DAT_0053e480;
    FUN_003bf2f0((struct NamedRefObject *)&o, (long long)0);
    return r;
}

void FUN_003c0c90(void)
{
    igMetaObject_RunStaticInit(beNDMWMdlObject_Register);
}

void *beNDMWMdlObject_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWMdlObject_metaObject,
        beModelCtrl_Register,
        beModelCtrl_GetPublishedMetaObject,
        beNDMWMdlObject_GetMetaObject,
        beNDMWMdlObject_className,
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

