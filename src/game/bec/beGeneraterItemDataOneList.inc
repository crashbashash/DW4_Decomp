igMetaObject *FUN_00360780(void) {
    if (g_beGeneraterItemDataOneList_metaObject[0] == 0) {
        g_beGeneraterItemDataOneList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_beGeneraterItemDataOneList_metaObject[0];
}

void *FUN_003607d0(void) {
    igMetaObject *g = g_beGeneraterItemDataOneList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false) {
        FUN_00360860();
    }
    return g_beGeneraterItemDataOneList_metaObject[0];
}

int beGeneraterItemDataOneList_GetVTable(void) {
    int obj[8];

    igObject_InitHeader(obj);
    obj[0] = (int)&DAT_00535ca0[0];
    return *(int *)((char *)obj + *(int *)((char *)g_objectSystem[0] + 916));
}

void FUN_00360860(void)
{
    igMetaObject_RunStaticInit(beGeneraterItemDataOneList_Register);
}

void *beGeneraterItemDataOneList_Register(void) {
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        g_beGeneraterItemDataOneList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        beGeneraterItemDataOneList_GetMetaObject,
        beGeneraterItemDataOneList_className,
        0x14, /* instance size */
        beGeneraterItemDataOneList_GetVTable,
        0,
        0, /* extra callback item */
        g_beGeneraterItemDataOneList_callbackList /* callback list */
    );
}

void beGeneraterItemDataOneList_GetMetaObject(void)
{
    FUN_003607d0();
}

