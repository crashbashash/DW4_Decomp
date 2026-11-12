int FUN_0034d8f0(void) {
    if (((int *)DAT_00588688)[0] == 0) {
        ((int *)DAT_00588688)[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return ((int *)DAT_00588688)[0];
}

SFUN_0034d940 *FUN_0034d940(void) {
    if (DAT_00588688[0] == 0 || !DAT_00588688[0]->ok()) FUN_0034d9d0();
    return DAT_00588688[0];
}

int beNumVerDataList_GetVTable(void) {
    struct Obj_34d990 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00538460[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_0034d9d0(void)
{
    igMetaObject_RunStaticInit(beNumVerDataList_Register);
}

void *beNumVerDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beNumVerDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beNumVerDataList_GetMetaObject,
        beNumVerDataList_className,
        0x14, /* instance size */
        beNumVerDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beNumVerDataList_callbackList /* callback list */
    );
}

void beNumVerDataList_GetMetaObject(void)
{
    FUN_0034d940();
}

