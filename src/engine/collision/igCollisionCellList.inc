igMetaObject *g_igCollisionCellList_metaObject;

igMetaObject *FUN_0023a570(void) {
    if (g_igCollisionCellList_metaObject == 0) {
        g_igCollisionCellList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData[0]));
    }
    return g_igCollisionCellList_metaObject;
}

igMetaObject *igCollisionCellList_GetMetaObject(void)
{
    igMetaObject *g = g_igCollisionCellList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0023a650();
    return g_igCollisionCellList_metaObject;
}

int igCollisionCellList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &g_igCollisionCellList_vtable[0];
    return *(int *)((char *)&obj + *(int *)((char *)(g_objectSystem[0]) + 916));
}

void FUN_0023a650(void)
{
    igMetaObject_RunStaticInit(igCollisionCellList_Register);
}

static igMetaObjectCallback g_igCollisionCellList_callbackList[] = { FUN_0023a850, 0 };

void igCollisionCellList_Register(void) {
    CollisionLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igCollisionCellList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igCollisionCellList_GetMetaObject,
        "igCollisionCellList",
        0x14, /* instance size */
        igCollisionCellList_GetVTable,
        0,
        0, /* extra callback item */
        g_igCollisionCellList_callbackList /* callback list */
    );
}

void thunk_igCollisionCellList_GetMetaObject(void) {
    igCollisionCellList_GetMetaObject();
}

