static const char *g_igFile_readModeNames[] = {
    "kDefaultReadMode", "kSequentialReadMode", "kChunkReadMode",
};
static int g_igFile_readModeValues[] = {
    0, 1, 2,
};


int igFile_GetReadModeMetaEnum(void) {
    if (g_igFile_readModeMetaEnum == 0) {
        g_igFile_readModeMetaEnum = ((int)igMetaEnum_Create((char *)("ReadMode"), g_igFile_readModeNames, g_igFile_readModeValues, 3));
    }
    return g_igFile_readModeMetaEnum;
}

static const char *g_igFile_openModeNames[] = {
    "kRead", "kWrite", "kAppend", "kReadWrite",
    "kReadBinary", "kWriteBinary", "kAppendBinary", "kReadWriteBinary",
    "kDefaultOpenMode",
};
static int g_igFile_openModeValues[] = {
    0, 1, 2, 3, 4, 5, 6, 7,
    8,
};


int igFile_GetOpenModeMetaEnum(void) {
    if (g_igFile_openModeMetaEnum == 0) {
        g_igFile_openModeMetaEnum = ((int)igMetaEnum_Create((char *)("OpenMode"), g_igFile_openModeNames, g_igFile_openModeValues, 9));
    }
    return g_igFile_openModeMetaEnum;
}

void * igFile_Create(int allocator) {
    igFile_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance(g_igFile_metaObject, (igMemoryPoolView *)allocator));
}

igMetaObject *igFile_GetOrCreateMetaObject(void) {
    if (g_igFile_metaObject == 0) {
        g_igFile_metaObject = (igMetaObject *)igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g_igFile_metaObject;
}

igMetaObject *igFile_GetMetaObject(void)
{
    igMetaObject *g = g_igFile_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igFile_EnsureRegistered();
    return g_igFile_metaObject;
}

void igFile_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igFile_Register);
}

CallbackArray *igFile_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        1,
        &g_igFile_metaObject,
        igNamedObject_Register,
        (igMetaObjectGetFunction)igNamedObject_GetPublishedMetaObject,
        igFile_GetMetaObjectFunction,
        "igFile",
        0x2C,
        0,
        igFile_InitFields,
        0,
        0
    );
}

static FieldFactory g_igFile_ctorTable[] = {
    (FieldFactory)igStringMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igEnumMetaField_Create,
    (FieldFactory)igRawRefMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igStringMetaField_Create,
};
static const char *g_igFile_fieldTable[] = {
    "_fileName",
    "_readMode",
    "_openMode",
    "_fileHandle",
    "_optimalReadChunkSize",
    "_optimalWriteChunkSize",
    "_pageSize",
    "_completeFilename",
};
static igMetaField **g_igFile_fieldDescriptors[] = {
    &g_igFile_fileNameMetaField,
    &g_igFile_readModeMetaField,
    &g_igFile_openModeMetaField,
    &g_igFile_fileHandleMetaField,
    &g_igFile_optimalReadChunkSizeMetaField,
    &g_igFile_optimalWriteChunkSizeMetaField,
    &g_igFile_pageSizeMetaField,
    &g_igFile_completeFilenameMetaField,
};
static int g_igFile_fieldOffsets[] = {
    12,
    16,
    20,
    24,
    28,
    32,
    36,
    40,
};

void igFile_InitFields(void) {
    int base;
    void *openMode;
    void *readMode;
    void *meta;

    meta = (void *)((void *)g_igFile_metaObject);
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igFile_ctorTable, 8);
    igStringMetaField_SetDefaultText((int *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base))), (int)"DefaultFileName");
    readMode = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 1)));
    igEnumMetaField_SetDefaultValue((igMetaFieldView *)readMode, 0);
    ((igEnumMetaField *)readMode)->_getMetaEnumFunction = (int)(&igFile_GetReadModeMetaEnum);
    openMode = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 2)));
    igEnumMetaField_SetDefaultValue((igMetaFieldView *)openMode, 0);
    ((igEnumMetaField *)openMode)->_getMetaEnumFunction = (int)(&igFile_GetOpenModeMetaEnum);
    ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 3))->_persistent = 0;
    igIntMetaField_SetDefault((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 4))), 0x100000);
    igIntMetaField_SetDefault((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 5))), 0x100000);
    igIntMetaField_SetDefault((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 6))), 0x1000);
    ((igMetaField *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 7))->_persistent = 0;
    igMetaObject_NameFields((igMetaObject *)meta, g_igFile_fieldTable, g_igFile_fieldDescriptors, g_igFile_fieldOffsets, base);
    *(int *)((char *)((void *)g_igFile_metaObject) + 60) = (int)(&igPsx2File_GetMetaObjectFunction);
}

