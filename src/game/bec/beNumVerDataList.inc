igMetaObject *FUN_0034d8f0(void) {
    if (g_beNumVerDataList_metaObject[0] == 0) {
        g_beNumVerDataList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beNumVerDataList_metaObject[0];
}

igMetaObject *FUN_0034d940(void) {
    if (g_beNumVerDataList_metaObject[0] == 0 || !isValid(g_beNumVerDataList_metaObject[0])) FUN_0034d9d0();
    return g_beNumVerDataList_metaObject[0];
}

int beNumVerDataList_GetVTable(void) {
    struct Obj_34d990 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00538460[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
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

