igMetaObject *g_igAttrListList_metaObject;

igMetaObject *FUN_0013abd0(void) {
    if (g_igAttrListList_metaObject == 0) {
        g_igAttrListList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igAttrListList_metaObject;
}

igMetaObject *igAttrListList_GetMetaObject(void)
{
    igMetaObject *g = g_igAttrListList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igAttrListList_EnsureRegistered();
    return g_igAttrListList_metaObject;
}

int igAttrListList_GetVTable(void) {
    struct Obj_13ac70 obj;

    igObject_InitHeader(&obj);
    obj.vt = &g_igAttrListList_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void igAttrListList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igAttrListList_Register);
}

static igMetaObjectCallback g_igAttrListList_callbackList[] = { igAttrList_EnsureRegistered, 0 };

void igAttrListList_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igAttrListList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igAttrListList_GetMetaObject,
        "igAttrListList",
        0x14, /* instance size */
        igAttrListList_GetVTable,
        0,
        0, /* extra callback item */
        g_igAttrListList_callbackList /* callback list */
    );
}

void thunk_igAttrListList_GetMetaObject(void) {
    igAttrListList_GetMetaObject();
}

