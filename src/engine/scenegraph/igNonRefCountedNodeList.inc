igMetaObject *g_igNonRefCountedNodeList_metaObject;

igMetaObject *FUN_0019c8c0(void) {
    if (g_igNonRefCountedNodeList_metaObject == 0) {
        g_igNonRefCountedNodeList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igNonRefCountedNodeList_metaObject;
}

igMetaObject *igNonRefCountedNodeList_GetMetaObject(void)
{
    igMetaObject *g = g_igNonRefCountedNodeList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igNonRefCountedNodeList_EnsureRegistered();
    return g_igNonRefCountedNodeList_metaObject;
}

int igNonRefCountedNodeList_GetVTable(void) {
    struct Obj_19c960 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igNonRefCountedNodeList_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
}

void igNonRefCountedNodeList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igNonRefCountedNodeList_Register);
}

static igMetaObjectCallback g_igNonRefCountedNodeList_callbackList[] = { igNode_EnsureRegistered, 0 };

CallbackArray *igNonRefCountedNodeList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igNonRefCountedNodeList_metaObject,
        igNonRefCountedObjectList_Register,
        igNonRefCountedObjectList_GetPublishedMetaObject,
        thunk_igNonRefCountedNodeList_GetMetaObject,
        "igNonRefCountedNodeList",
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

