igMetaObject *FUN_001a5900(void) {
    if (g_igAttrStackList_metaObject[0] == 0) {
        g_igAttrStackList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igAttrStackList_metaObject[0];
}

igMetaObject *igAttrStackList_GetMetaObject(void)
{
    igMetaObject *g = g_igAttrStackList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a59e0();
    return g_igAttrStackList_metaObject[0];
}

int igAttrStackList_GetVTable(void) {
    struct Obj_1a59a0 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052a1c0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_001a59e0(void)
{
    igMetaObject_RunStaticInit(igAttrStackList_Register);
}

void igAttrStackList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        ((char *)g_igAttrStackList_metaObject),
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igAttrStackList_GetMetaObject,
        igAttrStackList_className,
        0x14, /* instance size */
        igAttrStackList_GetVTable,
        0,
        0, /* extra callback item */
        g_igAttrStackList_callbackList /* callback list */
    );
}

void thunk_igAttrStackList_GetMetaObject(void) {
    igAttrStackList_GetMetaObject();
}

