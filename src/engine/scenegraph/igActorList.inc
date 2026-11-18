igMetaObject *g_igActorList_metaObject;

igMetaObject *igActorList_GetOrCreateMetaObject(void) {
    if (g_igActorList_metaObject == 0) {
        g_igActorList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igActorList_metaObject;
}

igMetaObject *igActorList_GetMetaObject(void)
{
    igMetaObject *g = g_igActorList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igActorList_EnsureRegistered();
    return g_igActorList_metaObject;
}

int igActorList_GetVTable(void) {
    struct Obj_1aa660 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igActorList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igActorList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igActorList_Register);
}

static igMetaObjectCallback g_igActorList_callbackList[] = { igActor_EnsureRegistered, 0 };

CallbackArray *igActorList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igActorList_metaObject,
        igObjectList_Register,
        igObjectList_GetPublishedMetaObject,
        igActorList_GetMetaObjectFunction,
        "igActorList",
        0x14, /* instance size */
        igActorList_GetVTable,
        0,
        0, /* extra callback item */
        g_igActorList_callbackList /* callback list */
    );
}

void igActorList_GetMetaObjectFunction(void) {
    igActorList_GetMetaObject();
}

