igMetaObject *g_igEnvironmentMapShader2List_metaObject;

igMetaObject *igEnvironmentMapShader2List_GetOrCreateMetaObject(void) {
    if (g_igEnvironmentMapShader2List_metaObject == 0) {
        g_igEnvironmentMapShader2List_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igEnvironmentMapShader2List_metaObject;
}

igMetaObject *igEnvironmentMapShader2List_GetMetaObject(void)
{
    igMetaObject *g = g_igEnvironmentMapShader2List_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igEnvironmentMapShader2List_EnsureRegistered();
    return g_igEnvironmentMapShader2List_metaObject;
}

int igEnvironmentMapShader2List_GetVTable(void) {
    struct Obj_1a1480 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igEnvironmentMapShader2List_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igEnvironmentMapShader2List_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igEnvironmentMapShader2List_Register);
}

static igMetaObjectCallback g_igEnvironmentMapShader2List_callbackList[] = { igEnvironmentMapShader2_EnsureRegistered, 0 };

CallbackArray *igEnvironmentMapShader2List_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igEnvironmentMapShader2List_metaObject,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        igEnvironmentMapShader2List_GetMetaObjectFunction,
        "igEnvironmentMapShader2List",
        0x14, /* instance size */
        igEnvironmentMapShader2List_GetVTable,
        0,
        0, /* extra callback item */
        g_igEnvironmentMapShader2List_callbackList /* callback list */
    );
}

void igEnvironmentMapShader2List_GetMetaObjectFunction(void) {
    igEnvironmentMapShader2List_GetMetaObject();
}

