igMetaObject *g_igLibraryLoader_metaObject;

igMetaObject *igLibraryLoader_GetOrCreateMetaObject(void) {
    if (g_igLibraryLoader_metaObject == 0) {
        g_igLibraryLoader_metaObject = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igLibraryLoader_metaObject;
}

igMetaObject *igLibraryLoader_GetMetaObject(void)
{
    igMetaObject *g = g_igLibraryLoader_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igLibraryLoader_EnsureRegistered();
    return g_igLibraryLoader_metaObject;
}

void igLibraryLoader_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igLibraryLoader_Register);
}

void igLibraryLoader_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1,
        &g_igLibraryLoader_metaObject,
        (igMetaObjectRegisterFunction)igObject_Register,
        (igMetaObjectGetFunction)igObject_GetMetaObject_ParentAccessor,
        igLibraryLoader_GetMetaObjectFunction,
        "igLibraryLoader",
        8,
        0,
        0,
        0,
        0
    );
}

void igLibraryLoader_GetMetaObjectFunction(void) {
    igLibraryLoader_GetMetaObject();
}

