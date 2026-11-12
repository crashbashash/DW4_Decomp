void *beNDMWMdlPEBaseInfoWork_ResolveMetaObject(void) {
    igMetaObject *g = g_beNDMWMdlPEBaseInfoWork_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_003c0770();
    }
    return g_beNDMWMdlPEBaseInfoWork_metaObject[0];
}

int beNDMWMdlPEBaseInfoWork_GetVTable(void) {
    PEBaseInfoWorkObj work;
    return *(int *)((char *)&work + *(int *)((char *)g_objectSystem[0] + 916));
}

int *FUN_003c0760(int *p)
{
    *(int *)((char *)p + 0) = 0;
    return p;
}

void FUN_003c0770(void)
{
    igMetaObject_RunStaticInit(beNDMWMdlPEBaseInfoWork_Register);
}

void *beNDMWMdlPEBaseInfoWork_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWMdlPEBaseInfoWork_metaObject,
        beModelCtrlInfoWork_Register,
        beModelCtrlInfoWork_GetPublishedMetaObject,
        beNDMWMdlPEBaseInfoWork_GetMetaObject,
        beNDMWMdlPEBaseInfoWork_className,
        0x114, /* instance size */
        beNDMWMdlPEBaseInfoWork_GetVTable,
        beNDMWMdlPEBaseInfoWork_InitFields,
        0, /* extra callback item */
        g_beNDMWMdlPEBaseInfoWork_callbackList /* callback list */
    );
}

void beNDMWMdlPEBaseInfoWork_GetMetaObject(void)
{
    beNDMWMdlPEBaseInfoWork_ResolveMetaObject();
}

void beNDMWMdlPEBaseInfoWork_InitFields(void) {
    void *temp_s2_7;
    void *temp_s2_6;
    void *temp_s2_5;
    void *temp_s2_4;
    void *temp_s2_3;
    void *temp_s2_2;
    void *temp_s2;
    void *temp_s1;
    int temp_s0;

    temp_s1 = (void *)g_beNDMWMdlPEBaseInfoWork_metaObject[0];
    temp_s0 = igMetaObject_GetFieldCount(temp_s1);
    igMetaObject_CreateFields(temp_s1, &DAT_004caa90[0], 0xA);
    temp_s2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 1));
    ((igObjectRefMetaField *)temp_s2)->_metaObject = igIntList_GetOrCreateMetaObject();
    temp_s2_2 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 2));
    ((igObjectRefMetaField *)temp_s2_2)->_metaObject = igIntList_GetOrCreateMetaObject();
    temp_s2_3 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 3));
    ((igObjectRefMetaField *)temp_s2_3)->_metaObject = igIntList_GetOrCreateMetaObject();
    temp_s2_4 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 4));
    ((igObjectRefMetaField *)temp_s2_4)->_metaObject = FUN_002cb110();
    temp_s2_5 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 7));
    ((igObjectRefMetaField *)temp_s2_5)->_metaObject = igIntList_GetOrCreateMetaObject();
    temp_s2_6 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 8));
    ((igObjectRefMetaField *)temp_s2_6)->_metaObject = igIntList_GetOrCreateMetaObject();
    temp_s2_7 = (void *)(igMetaObject_GetFieldAt(temp_s1, temp_s0 + 9));
    ((igObjectRefMetaField *)temp_s2_7)->_metaObject = FUN_00357910();
    ((igObjectRefMetaField *)temp_s2_7)->_refCounted = 0;
    igMetaObject_NameFields(temp_s1, &DAT_004caac0[0], &DAT_004caaf0[0], &DAT_004cab20[0], temp_s0);
}

