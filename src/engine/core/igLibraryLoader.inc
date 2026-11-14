igMetaObject *igLibraryLoader_GetOrCreateMetaObject(void) {
    if (g_igLibraryLoader_metaObject[0] == 0) {
        g_igLibraryLoader_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igLibraryLoader_metaObject[0];
}

igMetaObject *igLibraryLoader_GetMetaObject(void)
{
    igMetaObject *g = g_igLibraryLoader_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igLibraryLoader_EnsureRegistered();
    return g_igLibraryLoader_metaObject[0];
}

void igLibraryLoader_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igLibraryLoader_Register);
}

void igLibraryLoader_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1, /* abstract */
        ((char *)g_igLibraryLoader_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        igLibraryLoader_GetMetaObjectFunction,
        igLibraryLoader_className,
        8, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void igLibraryLoader_GetMetaObjectFunction(void) {
    igLibraryLoader_GetMetaObject();
}

