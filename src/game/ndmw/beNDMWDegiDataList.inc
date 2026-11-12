int FUN_003c66a0(void) {
    if (((int *)DAT_0058bd20)[0] == 0) {
        ((int *)DAT_0058bd20)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_0058bd20)[0];
}

void *beNDMWDegiDataList_GetReadyMetaObject(void) {
    bool ok;
    if (DAT_0058bd20[0] == 0) goto make;
    ok = !!(DAT_0058bd20[0]->f & 4);
    if (ok != false) goto done;
make:
    FUN_003c6780();
done:;
    return DAT_0058bd20[0];
}

int beNDMWDegiDataList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0053ca00[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_003c6780(void)
{
    igMetaObject_RunStaticInit(beNDMWDegiDataList_Register);
}

void *beNDMWDegiDataList_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWDegiDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beNDMWDegiDataList_GetMetaObject,
        beNDMWDegiDataList_className,
        0x14, /* instance size */
        beNDMWDegiDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beNDMWDegiDataList_callbackList /* callback list */
    );
}

void beNDMWDegiDataList_GetMetaObject(void)
{
    beNDMWDegiDataList_GetReadyMetaObject();
}

