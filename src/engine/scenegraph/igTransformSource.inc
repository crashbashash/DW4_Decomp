igMetaObject *g_igTransformSource_metaObject;

igMetaObject *FUN_00194dd0(void) {
    if (g_igTransformSource_metaObject == 0) {
        g_igTransformSource_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igTransformSource_metaObject;
}

igMetaObject *igTransformSource_GetMetaObject(void)
{
    igMetaObject *g = g_igTransformSource_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_00194e70();
    return g_igTransformSource_metaObject;
}

void FUN_00194e70(void)
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
        thunk_igTransformSource_GetMetaObject,
        "igTransformSource",
        8, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igTransformSource_GetMetaObject(void) {
    igTransformSource_GetMetaObject();
}

