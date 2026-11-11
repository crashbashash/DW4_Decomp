int FUN_001e4ae0(void) {
    if (DAT_00562bb8[0] == 0) {
        DAT_00562bb8[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_00562bb8[0];
}

igMetaObject *igMatrixObjectList_GetMetaObject(void)
{
    igMetaObject *g = g_igMatrixObjectList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001e4bc0();
    return g_igMatrixObjectList_metaObject[0];
}

int igMatrixObjectList_GetVTable(void) {
    int obj[8];
    igObject_InitHeader(obj);
    obj[0] = (int)&DAT_0052bc70[0];
    return *(int *)((char *)obj + *(int *)((char *)DAT_00586dc8[0] + 916));
}

void FUN_001e4bc0(void)
{
    igMetaObject_RunStaticInit(igMatrixObjectList_Register);
}

void igMatrixObjectList_Register(void) {
    DataPumpLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igMatrixObjectList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igMatrixObjectList_GetMetaObject,
        igMatrixObjectList_className,
        0x14, /* instance size */
        igMatrixObjectList_GetVTable,
        0,
        0, /* extra callback item */
        g_igMatrixObjectList_callbackList /* callback list */
    );
}

void thunk_igMatrixObjectList_GetMetaObject(void) {
    igMatrixObjectList_GetMetaObject();
}

