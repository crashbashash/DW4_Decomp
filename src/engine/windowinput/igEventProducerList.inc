igMetaObject *FUN_001460b0(void) {
    if (g_igEventProducerList_metaObject[0] == 0) {
        g_igEventProducerList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igEventProducerList_metaObject[0];
}

igMetaObject *igEventProducerList_GetMetaObject(void)
{
    igMetaObject *g = g_igEventProducerList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00146190();
    return g_igEventProducerList_metaObject[0];
}

int igEventProducerList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00525040[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_00146190(void)
{
    igMetaObject_RunStaticInit(igEventProducerList_Register);
}

void igEventProducerList_Register(void) {
    WindowInputLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igEventProducerList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igEventProducerList_GetMetaObject,
        igEventProducerList_className,
        0x14, /* instance size */
        igEventProducerList_GetVTable,
        0,
        0, /* extra callback item */
        g_igEventProducerList_callbackList /* callback list */
    );
}

void thunk_igEventProducerList_GetMetaObject(void) {
    igEventProducerList_GetMetaObject();
}

