igMetaObject *g_igLightStateAttrPool_metaObject;

igMetaObject *igLightStateAttrPool_GetOrCreateMetaObject(void) {
    if (g_igLightStateAttrPool_metaObject == 0) {
        g_igLightStateAttrPool_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igLightStateAttrPool_metaObject;
}

igMetaObject *igLightStateAttrPool_GetMetaObject(void)
{
    igMetaObject *g = g_igLightStateAttrPool_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igLightStateAttrPool_EnsureRegistered();
    return g_igLightStateAttrPool_metaObject;
}

int igLightStateAttrPool_GetVTable(void) {
    struct Obj_19a610 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igLightStateAttrPool_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igLightStateAttrPool_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igLightStateAttrPool_Register);
}

static igMetaObjectCallback g_igLightStateAttrPool_callbackList[] = { Gap::Attrs::igLightStateAttr::arkRegister, 0 };

CallbackArray *igLightStateAttrPool_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igLightStateAttrPool_metaObject,
        igObjectPool_Register,
        igObjectPool_GetPublishedMetaObject,
        igLightStateAttrPool_GetMetaObjectFunction,
        "igLightStateAttrPool",
        0x20, /* instance size */
        igLightStateAttrPool_GetVTable,
        0,
        0, /* extra callback item */
        g_igLightStateAttrPool_callbackList /* callback list */
    );
}

void igLightStateAttrPool_GetMetaObjectFunction(void) {
    igLightStateAttrPool_GetMetaObject();
}

