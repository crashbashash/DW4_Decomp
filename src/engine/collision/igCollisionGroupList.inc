igMetaObject *g_igCollisionGroupList_metaObject;

igMetaObject *FUN_00239a40(void) {
    if (g_igCollisionGroupList_metaObject == 0) {
        g_igCollisionGroupList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igCollisionGroupList_metaObject;
}

igMetaObject *igCollisionGroupList_GetMetaObject(void)
{
    igMetaObject *g = g_igCollisionGroupList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00239b20();
    return g_igCollisionGroupList_metaObject;
}

int igCollisionGroupList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igCollisionGroupList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void FUN_00239b20(void)
{
    igMetaObject_RunStaticInit(igCollisionGroupList_Register);
}

static igMetaObjectCallback g_igCollisionGroupList_callbackList[] = { FUN_00239c80, 0 };

CallbackArray *igCollisionGroupList_Register(void) {
    CollisionLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igCollisionGroupList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        thunk_igCollisionGroupList_GetMetaObject,
        "igCollisionGroupList",
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

