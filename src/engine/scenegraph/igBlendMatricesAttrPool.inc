igMetaObject *g_igBlendMatricesAttrPool_metaObject;

igMetaObject *igBlendMatricesAttrPool_GetOrCreateMetaObject(void) {
    if (g_igBlendMatricesAttrPool_metaObject == 0) {
        g_igBlendMatricesAttrPool_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igBlendMatricesAttrPool_metaObject;
}

igMetaObject *igBlendMatricesAttrPool_GetMetaObject(void)
{
    igMetaObject *g = g_igBlendMatricesAttrPool_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igBlendMatricesAttrPool_EnsureRegistered();
    return g_igBlendMatricesAttrPool_metaObject;
}

int igBlendMatricesAttrPool_GetVTable(void) {
    struct Obj_199a90 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igBlendMatricesAttrPool_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igBlendMatricesAttrPool_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igBlendMatricesAttrPool_Register);
}

static igMetaObjectCallback g_igBlendMatricesAttrPool_callbackList[] = { Gap::Attrs::igBlendMatricesAttr::arkRegister, 0 };

CallbackArray *igBlendMatricesAttrPool_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igBlendMatricesAttrPool_metaObject,
        igObjectPool_Register,
        igObjectPool_GetPublishedMetaObject,
        igBlendMatricesAttrPool_GetMetaObjectFunction,
        "igBlendMatricesAttrPool",
        0x20, /* instance size */
        igBlendMatricesAttrPool_GetVTable,
        0,
        0, /* extra callback item */
        g_igBlendMatricesAttrPool_callbackList /* callback list */
    );
}

void igBlendMatricesAttrPool_GetMetaObjectFunction(void) {
    igBlendMatricesAttrPool_GetMetaObject();
}

