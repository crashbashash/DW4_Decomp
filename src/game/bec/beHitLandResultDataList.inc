int FUN_0035e270(void) {
    if (((int *)DAT_005893e0)[0] == 0) {
        ((int *)DAT_005893e0)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_005893e0)[0];
}

void *FUN_0035e2c0(void) {
    struct G *g = DAT_005893e0[0];
    if (!g || ((g->f & 4) != 0) == false) {
        FUN_0035e350();
    }
    return DAT_005893e0[0];
}

int beHitLandResultDataList_GetVTable(void) {
    int tmp[8];
    int off;

    igObject_InitHeader(&tmp[0]);
    tmp[0] = (int)&DAT_005362f0[0];
    off = *(int *)((char *)(((int * *)DAT_00586dc8)[0]) + 916);
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

