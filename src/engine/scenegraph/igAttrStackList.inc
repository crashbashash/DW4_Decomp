igMetaObject *g_igAttrStackList_metaObject;

igMetaObject *FUN_001a5900(void) {
    if (g_igAttrStackList_metaObject == 0) {
        g_igAttrStackList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igAttrStackList_metaObject;
}

igMetaObject *igAttrStackList_GetMetaObject(void)
{
    igMetaObject *g = g_igAttrStackList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_001a59e0();
    return g_igAttrStackList_metaObject;
}

int igAttrStackList_GetVTable(void) {
    struct Obj_1a59a0 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igAttrStackList_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)g_objectSystem + 916));
}

void FUN_001a59e0(void)
{
    igMetaObject_RunStaticInit(igAttrStackList_Register);
}

static igMetaObjectCallback g_igAttrStackList_callbackList[] = { FUN_001a5b90, 0 };

CallbackArray *igAttrStackList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igAttrStackList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igAttrStackList_GetMetaObject,
        "igAttrStackList",
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

