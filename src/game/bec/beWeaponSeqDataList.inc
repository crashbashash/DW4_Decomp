igMetaObject *FUN_0033efe0(void) {
    if (g_beWeaponSeqDataList_metaObject[0] == 0) {
        g_beWeaponSeqDataList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_beWeaponSeqDataList_metaObject[0];
}

void *FUN_0033f030(void) {
    igMetaObject *g = g_beWeaponSeqDataList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0033f0c0();
    }
    return g_beWeaponSeqDataList_metaObject[0];
}

int beWeaponSeqDataList_GetVTable(void) {
    union U_33f080 u;

    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00539ce0[0];
    return *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
}

void FUN_0033f0c0(void)
{
    igMetaObject_RunStaticInit(beWeaponSeqDataList_Register);
}

void *beWeaponSeqDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beWeaponSeqDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beWeaponSeqDataList_GetMetaObject,
        beWeaponSeqDataList_className,
        0x14, /* instance size */
        beWeaponSeqDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beWeaponSeqDataList_callbackList /* callback list */
    );
}

void beWeaponSeqDataList_GetMetaObject(void)
{
    FUN_0033f030();
}

