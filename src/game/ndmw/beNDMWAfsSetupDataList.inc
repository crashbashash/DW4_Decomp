int FUN_003ca800(void) {
    if (((int *)DAT_0058c128)[0] == 0) {
        ((int *)DAT_0058c128)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_0058c128)[0];
}

void *beNDMWAfsSetupDataList_ResolveMetaObject(void) {
    bool ok;
    if (DAT_0058c128[0] == 0) goto make;
    ok = !!(DAT_0058c128[0]->f & 4);
    if (ok != false) goto done;
make:
    FUN_003ca8e0();
done:;
    return DAT_0058c128[0];
}

int beNDMWAfsSetupDataList_GetVTable(void) {
    Obj_3ca8a0 o;

    igObject_InitHeader(&o);
    o.vt = &DAT_0053c400[0];
    return *(int *)((char *)&o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_003ca8e0(void)
{
    igMetaObject_RunStaticInit(beNDMWAfsSetupDataList_Register);
}

void *beNDMWAfsSetupDataList_Register(void) {
    NdmwLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNDMWAfsSetupDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beNDMWAfsSetupDataList_GetMetaObject,
        beNDMWAfsSetupDataList_className,
        0x14, /* instance size */
        beNDMWAfsSetupDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beNDMWAfsSetupDataList_callbackList /* callback list */
    );
}

void beNDMWAfsSetupDataList_GetMetaObject(void)
{
    beNDMWAfsSetupDataList_ResolveMetaObject();
}

