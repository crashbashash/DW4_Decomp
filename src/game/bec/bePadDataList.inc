igMetaObject *g_bePadDataList_metaObject;

igMetaObject *FUN_0034ccc0(void) {
    if (g_bePadDataList_metaObject == 0) {
        g_bePadDataList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_bePadDataList_metaObject;
}

void *FUN_0034cd10(void) {
    igMetaObject *g = g_bePadDataList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0034cda0();
    }
    return g_bePadDataList_metaObject;
}

int bePadDataList_GetVTable(void) {
    union U_34cd60 u;

    igObject_InitHeader(u.b);
    u.vt = (int)&DAT_00538600[0];
    return *(int *)&u.b[*(int *)((char *)(g_objectSystem[0]) + 916)];
}

void FUN_0034cda0(void)
{
    igMetaObject_RunStaticInit(bePadDataList_Register);
}

static igMetaObjectCallback g_bePadDataList_callbackList[] = { FUN_0034cf20, 0 };

void *bePadDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_bePadDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        bePadDataList_GetMetaObject,
        "bePadDataList",
        0x14, /* instance size */
        bePadDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_bePadDataList_callbackList /* callback list */
    );
}

void bePadDataList_GetMetaObject(void)
{
    FUN_0034cd10();
}

