igMetaObject *FUN_0013abd0(void) {
    if (g_igAttrListList_metaObject[0] == 0) {
        g_igAttrListList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igAttrListList_metaObject[0];
}

igMetaObject *igAttrListList_GetMetaObject(void)
{
    igMetaObject *g = g_igAttrListList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0013acb0();
    return g_igAttrListList_metaObject[0];
}

int igAttrListList_GetVTable(void) {
    struct Obj_13ac70 obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_00524570[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_0013acb0(void)
{
    igMetaObject_RunStaticInit(igAttrListList_Register);
}

void igAttrListList_Register(void) {
    AttrsLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igAttrListList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igAttrListList_GetMetaObject,
        igAttrListList_className,
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

