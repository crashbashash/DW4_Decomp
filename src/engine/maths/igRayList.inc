igMetaObject *FUN_001880b0(void) {
    if (g_igRayList_metaObject[0] == 0) {
        g_igRayList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igRayList_metaObject[0];
}

igMetaObject *igRayList_GetMetaObject(void)
{
    igMetaObject *g = g_igRayList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00188190();
    return g_igRayList_metaObject[0];
}

int igRayList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00527f70[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_00188190(void)
{
    igMetaObject_RunStaticInit(igRayList_Register);
}

void igRayList_Register(void) {
    FUN_00186a40();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igRayList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igRayList_GetMetaObject,
        igRayList_className,
        0x14, /* instance size */
        igRayList_GetVTable,
        0,
        0, /* extra callback item */
        g_igRayList_callbackList /* callback list */
    );
}

void thunk_igRayList_GetMetaObject(void) {
    igRayList_GetMetaObject();
}

