igMetaObject *g_beMatCtrlDataList_metaObject;

igMetaObject *FUN_0035a2a0(void) {
    if (g_beMatCtrlDataList_metaObject == 0) {
        g_beMatCtrlDataList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beMatCtrlDataList_metaObject;
}

void *FUN_0035a2f0(void) {
    igMetaObject *g = g_beMatCtrlDataList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_0035a380();
    }
    return g_beMatCtrlDataList_metaObject;
}

int beMatCtrlDataList_GetVTable(void) {
    struct Obj_35a340 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00536a30[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_0035a380(void)
{
    igMetaObject_RunStaticInit(beMatCtrlDataList_Register);
}

static igMetaObjectCallback g_beMatCtrlDataList_callbackList[] = { FUN_0035a560, 0 };

void *beMatCtrlDataList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_beMatCtrlDataList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beMatCtrlDataList_GetMetaObject,
        "beMatCtrlDataList",
        0x14, /* instance size */
        beMatCtrlDataList_GetVTable,
        0,
        0, /* extra callback item */
        g_beMatCtrlDataList_callbackList /* callback list */
    );
}

void beMatCtrlDataList_GetMetaObject(void)
{
    FUN_0035a2f0();
}

