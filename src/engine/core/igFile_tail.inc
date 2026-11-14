int igFile_GetReadModeMetaEnum(void) {
    if (g_igFile_readModeMetaEnum[0] == 0) {
        g_igFile_readModeMetaEnum[0] = ((int)igMetaEnum_Create((char *)(&text_ReadMode[0]), (char **)(&g_igFile_readModeNames[0]), &g_igFile_readModeValues[0], 3));
    }
    return g_igFile_readModeMetaEnum[0];
}

int igFile_GetOpenModeMetaEnum(void) {
    if (g_igFile_openModeMetaEnum[0] == 0) {
        g_igFile_openModeMetaEnum[0] = ((int)igMetaEnum_Create((char *)(&text_OpenMode[0]), (char **)(&g_igFile_openModeNames[0]), &g_igFile_openModeValues[0], 9));
    }
    return g_igFile_openModeMetaEnum[0];
}

void * igFile_Create(int allocator) {
    igFile_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x5863B0), (igMemoryPoolView *)allocator));
}

igMetaObject *igFile_GetOrCreateMetaObject(void) {
    if (g_igFile_metaObject[0] == 0) {
        g_igFile_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igFile_metaObject[0];
}

igMetaObject *igFile_GetMetaObject(void)
{
    igMetaObject *g = g_igFile_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igFile_EnsureRegistered();
    return g_igFile_metaObject[0];
}

void igFile_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igFile_Register);
}

void igFile_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        1,
        g_igFile_metaObject,
        (igMetaObjectRegisterFunction)igNamedObject_Register,
        (igMetaObjectGetFunction)igNamedObject_GetPublishedMetaObject,
        igFile_GetMetaObjectFunction,
        igFile_className,
        0x2C,
        0,
        igFile_InitFields,
        0,
        0
    );
}

void igFile_InitFields(void) {
    int base;
    void *openMode;
    void *readMode;
    void *meta;

    meta = (void *)(((void * *)g_igFile_metaObject)[0]);
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, (igMetaField * (**)(void *))&g_igFile_ctorTable[0], 8);
    igStringMetaField_SetDefaultText((int *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base))), (int)&text_DefaultFileName[0]);
    readMode = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 1)));
    igEnumMetaField_SetDefaultValue((igMetaFieldView *)readMode, (const int *)&g_igFile_defaultReadMode[0]);
    ((igEnumMetaField *)readMode)->_getMetaEnumFunction = (int)(&igFile_GetReadModeMetaEnum);
    openMode = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 2)));
    igEnumMetaField_SetDefaultValue((igMetaFieldView *)openMode, (const int *)&g_igFile_defaultOpenMode[0]);
    ((igEnumMetaField *)openMode)->_getMetaEnumFunction = (int)(&igFile_GetOpenModeMetaEnum);
    ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 3))->_persistent = 0;
    igIntMetaField_SetDefault((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 4))), 0x100000);
    igIntMetaField_SetDefault((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 5))), 0x100000);
    igIntMetaField_SetDefault((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 6))), 0x1000);
    ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 7))->_persistent = 0;
    igMetaObject_NameFields((igMetaObject *)meta, (const char **)&g_igFile_fieldTable[0], (igMetaField ***)&g_igFile_fieldDescriptors[0], &g_igFile_fieldOffsets[0], base);
    *(int *)((char *)(((void * *)g_igFile_metaObject)[0]) + 60) = (int)(&igPsx2File_GetMetaObjectFunction);
}

