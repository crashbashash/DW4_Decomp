igMetaObject *FUN_002bfd60(void) {
    if (g_igMemoryPoolInfoList_metaObject[0] == 0) {
        g_igMemoryPoolInfoList_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(g_memoryContextMetaData)));
    }
    return g_igMemoryPoolInfoList_metaObject[0];
}

igMetaObject *igMemoryPoolInfoList_GetMetaObject(void)
{
    igMetaObject *g = g_igMemoryPoolInfoList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002bfe40();
    return g_igMemoryPoolInfoList_metaObject[0];
}

int igMemoryPoolInfoList_GetVTable(void) {
    struct Obj_2bfe00 obj;

    igObject_InitHeader((struct ObjectHeader *)&obj);
    obj.vt = &DAT_005329e0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void FUN_002bfe40(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igMemoryPoolInfoList_Register);
}

void igMemoryPoolInfoList_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igMemoryPoolInfoList_metaObject),
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igMemoryPoolInfoList_GetMetaObject,
        igMemoryPoolInfoList_className,
        0x14, /* instance size */
        igMemoryPoolInfoList_GetVTable,
        0,
        0, /* extra callback item */
        g_igMemoryPoolInfoList_callbackList /* callback list */
    );
}

void thunk_igMemoryPoolInfoList_GetMetaObject(void) {
    igMemoryPoolInfoList_GetMetaObject();
}

