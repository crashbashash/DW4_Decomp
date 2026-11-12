void FUN_003c8040(int arg0) {
    FUN_003c8110();
    igMetaObject_CreateInstance(*(int *)0x58BF10, arg0);
}

igMetaObject *beNDMWItemWaza_GetReadyMetaObject(void) {
    igMetaObject *g = g_beNDMWItemWaza_metaObject[0];
    int t;
    if (!g || !(t = (g->_validity & 4) != 0))
        FUN_003c8110();
    return g_beNDMWItemWaza_metaObject[0];
}

int beNDMWItemWaza_GetVTable(void) {
    int obj[8];

    igObject_InitHeader(obj);
    obj[0] = (int)&DAT_00540650[0];
    return *(int *)((char *)obj + *(int *)((char *)g_objectSystem[0] + 916));
}

void FUN_003c8110(void)
{
    igMetaObject_RunStaticInit(beNDMWItemWaza_Register);
}

void *beNDMWItemWaza_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWItemWaza_metaObject,
        beNDMWItemBase_Register,
        beNDMWItemBase_GetPublishedMetaObject,
        beNDMWItemWaza_GetMetaObject,
        beNDMWItemWaza_className,
        0x18, /* instance size */
        beNDMWItemWaza_GetVTable,
        beNDMWItemWaza_InitFields,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void beNDMWItemWaza_GetMetaObject(void)
{
    beNDMWItemWaza_GetReadyMetaObject();
}

igMetaObject *FUN_003c81c0(void) {
    return g_beNDMWItemBase_metaObject[0];
}

void beNDMWItemWaza_InitFields(void) {
    int temp_s1;
    void *temp_s0;

    temp_s0 = (void *)g_beNDMWItemWaza_metaObject[0];
    temp_s1 = igMetaObject_GetFieldCount(temp_s0);
    igMetaObject_CreateFields(temp_s0, &DAT_004cc088[0], 1);
    igMetaObject_NameFields(temp_s0, &DAT_004cc090[0], &DAT_004cc098[0], &DAT_004cc0a0[0], temp_s1);
}

