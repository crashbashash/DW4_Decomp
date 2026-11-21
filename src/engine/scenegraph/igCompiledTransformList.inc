igMetaObject *g_igCompiledTransformList_metaObject;

igMetaObject *igCompiledTransformList_GetOrCreateMetaObject(void) {
    if (g_igCompiledTransformList_metaObject == 0) {
        g_igCompiledTransformList_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igCompiledTransformList_metaObject;
}

igMetaObject *igCompiledTransformList_GetMetaObject(void)
{
    igMetaObject *g = g_igCompiledTransformList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igCompiledTransformList_EnsureRegistered();
    return g_igCompiledTransformList_metaObject;
}

int igCompiledTransformList_GetVTable(void) {
    struct Obj_1a34c0 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igCompiledTransformList_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igCompiledTransformList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igCompiledTransformList_Register);
}

static igMetaObjectCallback g_igCompiledTransformList_callbackList[] = { igCompiledTransform_EnsureRegistered, 0 };

CallbackArray *igCompiledTransformList_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igCompiledTransformList_metaObject,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        igCompiledTransformList_GetMetaObjectFunction,
        "igCompiledTransformList",
        0x14, /* instance size */
        igCompiledTransformList_GetVTable,
        0,
        0, /* extra callback item */
        g_igCompiledTransformList_callbackList /* callback list */
    );
}

void igCompiledTransformList_GetMetaObjectFunction(void) {
    igCompiledTransformList_GetMetaObject();
}

