int FUN_0023a570(void) {
    if (DAT_0056ddc0[0] == 0) {
        DAT_0056ddc0[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0056ddc0[0];
}

igMetaObject *igCollisionCellList_GetMetaObject(void)
{
    igMetaObject *g = g_igCollisionCellList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_0023a650();
    return g_igCollisionCellList_metaObject[0];
}

int igCollisionCellList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader(&obj);
    obj.vt = &DAT_0052d2f0[0];
    return *(int *)((char *)&obj + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}

void FUN_0023a650(void)
{
    igMetaObject_RunStaticInit(igCollisionCellList_Register);
}

void igCollisionCellList_Register(void) {
    CollisionLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0, /* abstract */
        g_igCollisionCellList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igCollisionCellList_GetMetaObject,
        igCollisionCellList_className,
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

