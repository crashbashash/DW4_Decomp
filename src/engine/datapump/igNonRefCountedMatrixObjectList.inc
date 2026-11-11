int FUN_001e4970(void) {
    if (DAT_00562bb0[0] == 0) {
        DAT_00562bb0[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_00562bb0[0];
}

igMetaObject *igNonRefCountedMatrixObjectList_GetMetaObject(void)
{
    igMetaObject *g = g_igNonRefCountedMatrixObjectList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001e4a50();
    return g_igNonRefCountedMatrixObjectList_metaObject[0];
}

int igNonRefCountedMatrixObjectList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052bce0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_001e4a50(void)
{
    igMetaObject_RunStaticInit(igNonRefCountedMatrixObjectList_Register);
}

void igNonRefCountedMatrixObjectList_Register(void) {
    DataPumpLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igNonRefCountedMatrixObjectList_metaObject,
        igNonRefCountedObjectList_Register,
        igNonRefCountedObjectList_GetPublishedMetaObject,
        thunk_igNonRefCountedMatrixObjectList_GetMetaObject,
        igNonRefCountedMatrixObjectList_className,
        0x14, /* instance size */
        igNonRefCountedMatrixObjectList_GetVTable,
        0,
        0, /* extra callback item */
        g_igNonRefCountedMatrixObjectList_callbackList /* callback list */
    );
}

void thunk_igNonRefCountedMatrixObjectList_GetMetaObject(void) {
    igNonRefCountedMatrixObjectList_GetMetaObject();
}

