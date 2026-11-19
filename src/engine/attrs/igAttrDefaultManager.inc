igMetaObject *g_igAttrDefaultManager_metaObject;

igMetaObject *igAttrDefaultManager_GetOrCreateMetaObject(void) {
    if (g_igAttrDefaultManager_metaObject == 0) {
        g_igAttrDefaultManager_metaObject = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igAttrDefaultManager_metaObject;
}

igMetaObject *igAttrDefaultManager_GetMetaObject(void)
{
    igMetaObject *g = g_igAttrDefaultManager_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igAttrDefaultManager_EnsureRegistered();
    return g_igAttrDefaultManager_metaObject;
}

void igAttrDefaultManager_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igAttrDefaultManager_Register);
}

CallbackArray *igAttrDefaultManager_Register(void) {
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1, /* abstract */
        &g_igAttrDefaultManager_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        igAttrDefaultManager_GetMetaObjectFunction,
        "igAttrDefaultManager",
        8, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igAttrDefaultManager_GetMetaObjectFunction(void) {
    igAttrDefaultManager_GetMetaObject();
}

