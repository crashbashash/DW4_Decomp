igMetaObject *FUN_002c2290(void) {
    if (g_igLibraryLoader_metaObject[0] == 0) {
        g_igLibraryLoader_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(g_memoryContextMetaData)));
    }
    return g_igLibraryLoader_metaObject[0];
}

igMetaObject *igLibraryLoader_GetMetaObject(void)
{
    igMetaObject *g = g_igLibraryLoader_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        FUN_002c2330();
    return g_igLibraryLoader_metaObject[0];
}

void FUN_002c2330(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igLibraryLoader_Register);
}

void igLibraryLoader_Register(void) {
    FUN_002b5d50();
    igMetaObject_RegisterClass(
        1, /* abstract */
        ((char *)g_igLibraryLoader_metaObject),
        igObject_Register,
        igObject_GetMetaObject_ParentAccessor,
        thunk_igLibraryLoader_GetMetaObject,
        igLibraryLoader_className,
        8, /* instance size */
        0,
        0,
        0, /* extra callback item */
        0 /* callback list */
    );
}

void thunk_igLibraryLoader_GetMetaObject(void) {
    igLibraryLoader_GetMetaObject();
}

