igMetaObject *g_beGeneraterPlayerDataList_metaObject;

igMetaObject *FUN_0035ff20(void) {
    if (g_beGeneraterPlayerDataList_metaObject == 0) {
        g_beGeneraterPlayerDataList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beGeneraterPlayerDataList_metaObject;
}

void *FUN_0035ff70(void) {
    igMetaObject *g = g_beGeneraterPlayerDataList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00360000();
    }
    return g_beGeneraterPlayerDataList_metaObject;
}

int beGeneraterPlayerDataList_GetVTable(void) {
    union U_35ffc0 u;

    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00535e40[0];
    return *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
}

void FUN_00360000(void)
{
    igMetaObject_RunStaticInit(beGeneraterPlayerDataList_Register);
}

static igMetaObjectCallback g_beGeneraterPlayerDataList_callbackList[] = { FUN_003601e0, 0 };

void *beGeneraterPlayerDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beGeneraterPlayerDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beGeneraterPlayerDataList_GetMetaObject,
        "beGeneraterPlayerDataList",
        0x14, /* instance size */
        beGeneraterPlayerDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beGeneraterPlayerDataList_callbackList /* callback list */
    );
}

void beGeneraterPlayerDataList_GetMetaObject(void)
{
    FUN_0035ff70();
}

