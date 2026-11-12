igMetaObject *FUN_0035e270(void) {
    if (g_beHitLandResultDataList_metaObject[0] == 0) {
        g_beHitLandResultDataList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_beHitLandResultDataList_metaObject[0];
}

void *FUN_0035e2c0(void) {
    igMetaObject *g = g_beHitLandResultDataList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0035e350();
    }
    return g_beHitLandResultDataList_metaObject[0];
}

int beHitLandResultDataList_GetVTable(void) {
    int tmp[8];
    int off;

    igObject_InitHeader(&tmp[0]);
    tmp[0] = (int)&DAT_005362f0[0];
    off = *(int *)((char *)(((int * *)g_objectSystem)[0]) + 916);
    return *(int *)((char *)tmp + off);
}

void FUN_0035e350(void)
{
    igMetaObject_RunStaticInit(beHitLandResultDataList_Register);
}

void *beHitLandResultDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beHitLandResultDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beHitLandResultDataList_GetMetaObject,
        beHitLandResultDataList_className,
        0x14, /* instance size */
        beHitLandResultDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beHitLandResultDataList_callbackList /* callback list */
    );
}

void beHitLandResultDataList_GetMetaObject(void)
{
    FUN_0035e2c0();
}

