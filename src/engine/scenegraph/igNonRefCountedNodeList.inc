int FUN_0019c8c0(void) {
    if (DAT_00561820[0] == 0) {
        DAT_00561820[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_00561820[0];
}

igMetaObject *igNonRefCountedNodeList_GetMetaObject(void)
{
    igMetaObject *g = g_igNonRefCountedNodeList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0019c9a0();
    return g_igNonRefCountedNodeList_metaObject[0];
}

int igNonRefCountedNodeList_GetVTable(void) {
    struct Obj_19c960 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052ac00[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_0019c9a0(void)
{
    igMetaObject_RunStaticInit(igNonRefCountedNodeList_Register);
}

void igNonRefCountedNodeList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igNonRefCountedNodeList_metaObject),
        igNonRefCountedObjectList_Register,
        igNonRefCountedObjectList_GetPublishedMetaObject,
        thunk_igNonRefCountedNodeList_GetMetaObject,
        igNonRefCountedNodeList_className,
        0x14, /* instance size */
        igNonRefCountedNodeList_GetVTable,
        0,
        0, /* extra callback item */
        g_igNonRefCountedNodeList_callbackList /* callback list */
    );
}

void thunk_igNonRefCountedNodeList_GetMetaObject(void) {
    igNonRefCountedNodeList_GetMetaObject();
}

