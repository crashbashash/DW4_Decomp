void FUN_003c1120(int arg0) {
    FUN_003c1270();
    igMetaObject_CreateInstance(*(int *)0x58B4A8, arg0);
}

int FUN_003c1160(void) {
    if (((int *)DAT_0058b4a8)[0] == 0) {
        ((int *)DAT_0058b4a8)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_0058b4a8)[0];
}

G_3c11b0 *beNDMWMdlItem_GetReadyMetaObject(void) {
    G_3c11b0 *g = DAT_0058b4a8[0];
    int t;
    if (!g || !(t = (g->f & 4) != 0))
        FUN_003c1270();
    return DAT_0058b4a8[0];
}

int beNDMWMdlItem_GetVTable(void) {
    struct Obj_3c1200 o;
    int r;
    igObject_InitHeader(&o);
    o.f8 = 0;
    o.f24 = 0;
    o.vt = &DAT_00540450[0];
    o.f48 = 0;
    r = *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    o.vt = &DAT_00540450[0];
    FUN_0014aa70(&o.f48, -1);
    FUN_003bf2f0((struct NamedRefObject *)&o, (long long)0);
    return r;
}

void FUN_003c1270(void)
{
    igMetaObject_RunStaticInit(beNDMWMdlItem_Register);
}

void *beNDMWMdlItem_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWMdlItem_metaObject,
        beModelCtrl_Register,
        beModelCtrl_GetPublishedMetaObject,
        beNDMWMdlItem_GetMetaObject,
        beNDMWMdlItem_className,
        0x34, /* instance size */
        beNDMWMdlItem_GetVTable,
        beNDMWMdlItem_InitFields,
        0, /* extra callback item */
        g_beNDMWMdlItem_callbackList /* callback list */
    );
}

void beNDMWMdlItem_GetMetaObject(void)
{
    beNDMWMdlItem_GetReadyMetaObject();
}

void beNDMWMdlItem_InitFields(void) {
    int temp_s2;
    void *temp_s1;
    void *temp_s1_2;
    void *temp_s0;

    temp_s0 = (void *)((int *)DAT_0058b4a8)[0];
    temp_s2 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004cab58[0], 2);
    temp_s1 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2));
    ((igObjectRefMetaField *)temp_s1)->_metaObject = FUN_00459380();
    ((igObjectRefMetaField *)temp_s1)->_refCounted = 0;
    temp_s1_2 = (void *)(igMetaObject_GetFieldAt(temp_s0, temp_s2 + 1));
    ((igObjectRefMetaField *)temp_s1_2)->_metaObject = igObjectList_GetOrCreateMetaObject();
    ((igRefMetaField *)temp_s1_2)->_construct = 1;
    igMetaObject_NameFields(temp_s0, &DAT_004cab60[0], &DAT_004cab68[0], &DAT_004cab70[0], temp_s2);
}

