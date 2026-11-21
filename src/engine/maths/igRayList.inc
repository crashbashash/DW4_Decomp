igMetaObject *g_igRayList_metaObject;

igMetaObject *igRayList_GetOrCreateMetaObject(void) {
    if (g_igRayList_metaObject == 0) {
        g_igRayList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igRayList_metaObject;
}

igMetaObject *igRayList_GetMetaObject(void)
{
    igMetaObject *g = g_igRayList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igRayList_EnsureRegistered();
    return g_igRayList_metaObject;
}

int igRayList_GetVTable(void) {
    struct Obj obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igRayList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igRayList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igRayList_Register);
}

static igMetaObjectCallback g_igRayList_callbackList[] = { igRay_EnsureRegistered, 0 };

CallbackArray *igRayList_Register(void) {
    FUN_00186a40();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igRayList_metaObject,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        igRayList_GetMetaObjectFunction,
        "igRayList",
        0x14, /* instance size */
        igRayList_GetVTable,
        0,
        0, /* extra callback item */
        g_igRayList_callbackList /* callback list */
    );
}

void igRayList_GetMetaObjectFunction(void) {
    igRayList_GetMetaObject();
}

