igMetaObject *g_igCollisionGroupList_metaObject;

igMetaObject *igCollisionGroupList_GetOrCreateMetaObject(void) {
    if (g_igCollisionGroupList_metaObject == 0) {
        g_igCollisionGroupList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igCollisionGroupList_metaObject;
}

igMetaObject *igCollisionGroupList_GetMetaObject(void)
{
    igMetaObject *g = g_igCollisionGroupList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igCollisionGroupList_EnsureRegistered();
    return g_igCollisionGroupList_metaObject;
}

int igCollisionGroupList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igCollisionGroupList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igCollisionGroupList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igCollisionGroupList_Register);
}

static igMetaObjectCallback g_igCollisionGroupList_callbackList[] = { igCollisionGroup_EnsureRegistered, 0 };

CallbackArray *igCollisionGroupList_Register(void) {
    CollisionLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igCollisionGroupList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        igCollisionGroupList_GetMetaObjectFunction,
        "igCollisionGroupList",
        0x14, /* instance size */
        igCollisionGroupList_GetVTable,
        0,
        0, /* extra callback item */
        g_igCollisionGroupList_callbackList /* callback list */
    );
}

void igCollisionGroupList_GetMetaObjectFunction(void) {
    igCollisionGroupList_GetMetaObject();
}

