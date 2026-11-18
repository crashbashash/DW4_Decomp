igMetaObject *g_igVisualAttribute_metaObject;

igMetaObject *igVisualAttribute_GetOrCreateMetaObject(void) {
    if (g_igVisualAttribute_metaObject == 0) {
        g_igVisualAttribute_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igVisualAttribute_metaObject;
}

igMetaObject *igVisualAttribute_GetMetaObject(void)
{
    igMetaObject *g = g_igVisualAttribute_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igVisualAttribute_EnsureRegistered();
    return g_igVisualAttribute_metaObject;
}

void igVisualAttribute_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igVisualAttribute_Register);
}

CallbackArray *igVisualAttribute_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igVisualAttribute_metaObject,
        igAttr_Register,
        igAttr_GetPublishedMetaObject,
        igVisualAttribute_GetMetaObjectFunction,
        "igVisualAttribute",
        0xC, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igVisualAttribute_GetMetaObjectFunction(void) {
    igVisualAttribute_GetMetaObject();
}

igMetaObject *igAttr_GetPublishedMetaObject(void) {
    return g_igAttr_metaObject;
}

