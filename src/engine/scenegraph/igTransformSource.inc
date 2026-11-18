igMetaObject *g_igTransformSource_metaObject;

igMetaObject *igTransformSource_GetOrCreateMetaObject(void) {
    if (g_igTransformSource_metaObject == 0) {
        g_igTransformSource_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igTransformSource_metaObject;
}

igMetaObject *igTransformSource_GetMetaObject(void)
{
    igMetaObject *g = g_igTransformSource_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igTransformSource_EnsureRegistered();
    return g_igTransformSource_metaObject;
}

void igTransformSource_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igTransformSource_Register);
}

CallbackArray *igTransformSource_Register(void) {
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igTransformSource_metaObject,
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        igTransformSource_GetMetaObjectFunction,
        "igTransformSource",
        8, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igTransformSource_GetMetaObjectFunction(void) {
    igTransformSource_GetMetaObject();
}

