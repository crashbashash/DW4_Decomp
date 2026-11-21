igMetaObject *g_igTextureMatrixAttrPool_metaObject;

igMetaObject *igTextureMatrixAttrPool_GetOrCreateMetaObject(void) {
    if (g_igTextureMatrixAttrPool_metaObject == 0) {
        g_igTextureMatrixAttrPool_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igTextureMatrixAttrPool_metaObject;
}

igMetaObject *igTextureMatrixAttrPool_GetMetaObject(void)
{
    igMetaObject *g = g_igTextureMatrixAttrPool_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igTextureMatrixAttrPool_EnsureRegistered();
    return g_igTextureMatrixAttrPool_metaObject;
}

int igTextureMatrixAttrPool_GetVTable(void) {
    struct Obj_199c00 obj;

    igObject_InitHeader((igObject *)&obj);
    obj.vt = &g_igTextureMatrixAttrPool_vtable[0];
    return *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
}

void igTextureMatrixAttrPool_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igTextureMatrixAttrPool_Register);
}

static igMetaObjectCallback g_igTextureMatrixAttrPool_callbackList[] = { Gap::Attrs::igTextureMatrixAttr::arkRegister, 0 };

CallbackArray *igTextureMatrixAttrPool_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0, /* abstract */
        &g_igTextureMatrixAttrPool_metaObject,
        igObjectPool_Register,
        igObjectPool_GetPublishedMetaObject,
        igTextureMatrixAttrPool_GetMetaObjectFunction,
        "igTextureMatrixAttrPool",
        0x20, /* instance size */
        igTextureMatrixAttrPool_GetVTable,
        0,
        0, /* extra callback item */
        g_igTextureMatrixAttrPool_callbackList /* callback list */
    );
}

void igTextureMatrixAttrPool_GetMetaObjectFunction(void) {
    igTextureMatrixAttrPool_GetMetaObject();
}

