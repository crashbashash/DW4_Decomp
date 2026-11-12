int FUN_0035f9d0(void) {
    if (((int *)DAT_005894e8)[0] == 0) {
        ((int *)DAT_005894e8)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_005894e8)[0];
}

SFUN_0035fa20 *FUN_0035fa20(void) {
    if (DAT_005894e8[0] == 0 || !DAT_005894e8[0]->ok()) FUN_0035fab0();
    return DAT_005894e8[0];
}

int beGeneraterDataList_GetVTable(void) {
    struct Obj_35fa70 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00535f10[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_0035fab0(void)
{
    igMetaObject_RunStaticInit(beGeneraterDataList_Register);
}

void *beGeneraterDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beGeneraterDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beGeneraterDataList_GetMetaObject,
        beGeneraterDataList_className,
        0x14, /* instance size */
        beGeneraterDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beGeneraterDataList_callbackList /* callback list */
    );
}

void beGeneraterDataList_GetMetaObject(void)
{
    FUN_0035fa20();
}

