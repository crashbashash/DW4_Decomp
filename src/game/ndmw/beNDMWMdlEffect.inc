void FUN_003c1ab0(int arg0) {
    FUN_003c1bf0();
    igMetaObject_CreateInstance(*(int *)0x58B518, arg0);
}

int FUN_003c1af0(void) {
    if (((int *)DAT_0058b518)[0] == 0) {
        ((int *)DAT_0058b518)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_0058b518)[0];
}

void *beNDMWMdlEffect_GetReadyMetaObject(void) {
    struct G *g = DAT_0058b518[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_003c1bf0();
    }
    return DAT_0058b518[0];
}

int beNDMWMdlEffect_GetVTable(void) {
    struct Obj_3c1b90 obj;
    int r;

    igObject_InitHeader(&obj);
    obj.w[1] = 0;
    obj.w[5] = 0;
    obj.vt = &DAT_0053e2e0[0];
    r = *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    obj.vt = &DAT_0053e2e0[0];
    FUN_003bf2f0((struct NamedRefObject *)&obj, (long long)0);
    return r;
}

void FUN_003c1bf0(void)
{
    igMetaObject_RunStaticInit(beNDMWMdlEffect_Register);
}

void *beNDMWMdlEffect_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWMdlEffect_metaObject,
        beModelCtrl_Register,
        beModelCtrl_GetPublishedMetaObject,
        beNDMWMdlEffect_GetMetaObject,
        beNDMWMdlEffect_className,
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

