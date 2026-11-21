igMetaObject *g_igShaderFactoryList_metaObject;

igMetaObject *igShaderFactoryList_GetOrCreateMetaObject(void) {
    if (g_igShaderFactoryList_metaObject == 0) {
        g_igShaderFactoryList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igShaderFactoryList_metaObject;
}

igMetaObject *igShaderFactoryList_GetMetaObject(void)
{
    igMetaObject *g = g_igShaderFactoryList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igShaderFactoryList_EnsureRegistered();
    return g_igShaderFactoryList_metaObject;
}

int igShaderFactoryList_GetVTable(void) {
    struct Obj_199040 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igShaderFactoryList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igShaderFactoryList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igShaderFactoryList_Register);
}

static igMetaObjectCallback g_igShaderFactoryList_callbackList[] = { igShaderFactory_EnsureRegistered, 0 };

CallbackArray *igShaderFactoryList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igShaderFactoryList_metaObject,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        igShaderFactoryList_GetMetaObjectFunction,
        "igShaderFactoryList",
        0x14, /* instance size */
        igShaderFactoryList_GetVTable,
        0,
        0, /* extra callback item */
        g_igShaderFactoryList_callbackList /* callback list */
    );
}

void igShaderFactoryList_GetMetaObjectFunction(void) {
    igShaderFactoryList_GetMetaObject();
}

