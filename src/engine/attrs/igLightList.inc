igMetaObject *g_igLightList_metaObject;

igMetaObject *igLightList_GetOrCreateMetaObject(void) {
    if (g_igLightList_metaObject == 0) {
        g_igLightList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igLightList_metaObject;
}

igMetaObject *igLightList_GetMetaObject(void)
{
    igMetaObject *g = g_igLightList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igLightList_EnsureRegistered();
    return g_igLightList_metaObject;
}

int igLightList_GetVTable(void) {
    struct Obj_136680 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igLightList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igLightList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igLightList_Register);
}

static igMetaObjectCallback g_igLightList_callbackList[] = { igLightAttr_EnsureRegistered, 0 };

CallbackArray *igLightList_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igLightList_metaObject,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        igLightList_GetMetaObjectFunction,
        "igLightList",
        0x14, /* instance size */
        igLightList_GetVTable,
        0,
        0, /* extra callback item */
        g_igLightList_callbackList /* callback list */
    );
}

void igLightList_GetMetaObjectFunction(void) {
    igLightList_GetMetaObject();
}

