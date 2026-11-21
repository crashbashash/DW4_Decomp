igMetaObject *g_igCollisionCellList_metaObject;

igMetaObject *igCollisionCellList_GetOrCreateMetaObject(void) {
    if (g_igCollisionCellList_metaObject == 0) {
        g_igCollisionCellList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igCollisionCellList_metaObject;
}

igMetaObject *igCollisionCellList_GetMetaObject(void)
{
    igMetaObject *g = g_igCollisionCellList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igCollisionCellList_EnsureRegistered();
    return g_igCollisionCellList_metaObject;
}

int igCollisionCellList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igCollisionCellList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igCollisionCellList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igCollisionCellList_Register);
}

static igMetaObjectCallback g_igCollisionCellList_callbackList[] = { igCollisionCell_EnsureRegistered, 0 };

CallbackArray *igCollisionCellList_Register(void) {
    CollisionLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igCollisionCellList_metaObject,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        igCollisionCellList_GetMetaObjectFunction,
        "igCollisionCellList",
        0x14, /* instance size */
        igCollisionCellList_GetVTable,
        0,
        0, /* extra callback item */
        g_igCollisionCellList_callbackList /* callback list */
    );
}

void igCollisionCellList_GetMetaObjectFunction(void) {
    igCollisionCellList_GetMetaObject();
}

