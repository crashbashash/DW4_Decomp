igMetaObject *g_igTimeAttrPool_metaObject;

igMetaObject *igTimeAttrPool_GetOrCreateMetaObject(void) {
    if (g_igTimeAttrPool_metaObject == 0) {
        g_igTimeAttrPool_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igTimeAttrPool_metaObject;
}

igMetaObject *igTimeAttrPool_GetMetaObject(void)
{
    igMetaObject *g = g_igTimeAttrPool_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igTimeAttrPool_EnsureRegistered();
    return g_igTimeAttrPool_metaObject;
}

int igTimeAttrPool_GetVTable(void) {
    int obj[8];
    igObject_InitHeader((igObject *)obj);
    obj[0] = (int)&g_igTimeAttrPool_vtable[0];
    return *(int *)((char *)obj + g_objectSystem->vtableProbeOffset);
}

void igTimeAttrPool_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igTimeAttrPool_Register);
}

static igMetaObjectCallback g_igTimeAttrPool_callbackList[] = { Gap::Attrs::igTimeAttr::arkRegister, 0 };

CallbackArray *igTimeAttrPool_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igTimeAttrPool_metaObject,
        igObjectPool_Register,
        igObjectPool_GetPublishedMetaObject,
        igTimeAttrPool_GetMetaObjectFunction,
        "igTimeAttrPool",
        0x20, /* instance size */
        igTimeAttrPool_GetVTable,
        0,
        0, /* extra callback item */
        g_igTimeAttrPool_callbackList /* callback list */
    );
}

void igTimeAttrPool_GetMetaObjectFunction(void) {
    igTimeAttrPool_GetMetaObject();
}

