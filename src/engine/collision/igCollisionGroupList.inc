igMetaObject *FUN_00239a40(void) {
    if (g_igCollisionGroupList_metaObject[0] == 0) {
        g_igCollisionGroupList_metaObject[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(g_metadataAllocatorKey[0]));
    }
    return g_igCollisionGroupList_metaObject[0];
}

igMetaObject *igCollisionGroupList_GetMetaObject(void)
{
    igMetaObject *g = g_igCollisionGroupList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00239b20();
    return g_igCollisionGroupList_metaObject[0];
}

int igCollisionGroupList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052d460[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_00239b20(void)
{
    igMetaObject_RunStaticInit(igCollisionGroupList_Register);
}

void igCollisionGroupList_Register(void) {
    CollisionLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igCollisionGroupList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igCollisionGroupList_GetMetaObject,
        igCollisionGroupList_className,
        0x14, /* instance size */
        igCollisionGroupList_GetVTable,
        0,
        0, /* extra callback item */
        g_igCollisionGroupList_callbackList /* callback list */
    );
}

void thunk_igCollisionGroupList_GetMetaObject(void) {
    igCollisionGroupList_GetMetaObject();
}

