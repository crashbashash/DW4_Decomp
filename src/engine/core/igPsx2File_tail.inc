igMetaObject *g_igPsx2File_metaObject;
igMetaField *g_igPsx2File_fBufMetaField;
igMetaField *g_igPsx2File_bufSizeMetaField;
igMetaField *g_igPsx2File_bufPosMetaField;
igMetaField *g_igPsx2File_fileSizeMetaField;
igMetaField *g_igPsx2File_isBinaryMetaField;
igMetaField *g_igPsx2File_isOpenMetaField;
igMetaField *g_igPsx2File_stringFileMetaField;
igMetaField *g_igPsx2File_prefixMetaField;

int igPsx2File_Create(int allocator) {
    igPsx2File_EnsureRegistered();
    return (int)igMetaObject_CreateInstance(g_igPsx2File_metaObject, (igMemoryPoolView *)allocator);
}

igMetaObject *igPsx2File_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2File_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igPsx2File_EnsureRegistered();
    return g_igPsx2File_metaObject;
}

int igPsx2File_GetVTable(void) {
    igPsx2File f;
    int vtable;

    igObject_InitHeader((igObject *)&f);
    f._name = 0;
    f._fileName = 0;
    f._completeFilename = 0;
    f._vtable = (int)&g_igPsx2File_vtable[0];
    f._prefix = 0;
    vtable = *(int *)((char *)&f + g_objectSystem->vtableProbeOffset);
    f._vtable = (int)&g_igPsx2File_vtable[0];
    igStringRef_Destruct((igStringRef *)&f._prefix, -1);
    igFile_Destroy((igFile *)&f, (short)0);
    return vtable;
}

void igPsx2File_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igPsx2File_Register);
}

CallbackArray *igPsx2File_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igPsx2File_metaObject,
        Gap::Core::igFile::arkRegisterInternal,
        Gap::Core::igFile::getClassMeta,
        igPsx2File_GetMetaObjectFunction,
        "igPsx2File",
        0x4C,
        igPsx2File_GetVTable,
        igPsx2File_InitFields,
        igPsx2File_StaticInitCallback,
        0
    );
}

static FieldFactory g_igPsx2File_ctorTable[] = {
    (FieldFactory)igMemoryRefMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igRawRefMetaField_Create,
    (FieldFactory)igStringMetaField_Create,
};
static const char *g_igPsx2File_fieldTable[] = {
    "_fBuf",
    "_bufSize",
    "_bufPos",
    "_fileSize",
    "_isBinary",
    "_isOpen",
    "_stringFile",
    "_prefix",
};
static igMetaField **g_igPsx2File_fieldDescriptors[] = {
    &g_igPsx2File_fBufMetaField,
    &g_igPsx2File_bufSizeMetaField,
    &g_igPsx2File_bufPosMetaField,
    &g_igPsx2File_fileSizeMetaField,
    &g_igPsx2File_isBinaryMetaField,
    &g_igPsx2File_isOpenMetaField,
    &g_igPsx2File_stringFileMetaField,
    &g_igPsx2File_prefixMetaField,
};
static int g_igPsx2File_fieldOffsets[] = {
    44,
    48,
    52,
    56,
    60,
    64,
    68,
    72,
};

void igPsx2File_InitFields(void) {
    void *prefixField;
    int base;
    void *bufferField;
    void *meta;

    meta = (void *)(g_igPsx2File_metaObject);
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igPsx2File_ctorTable, 8);
    bufferField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base)));
    ((igMemoryRefMetaField *)bufferField)->_memType = (int)Gap::Core::igUnsignedCharMetaField::getMetaField();
    prefixField = ((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 7));
    ((igMetaField *)prefixField)->_resetMethod = 3;
    igMetaObject_NameFields((igMetaObject *)meta, g_igPsx2File_fieldTable, g_igPsx2File_fieldDescriptors, g_igPsx2File_fieldOffsets, base);
    ((igMetaObject *)g_igPsx2File_metaObject)->_writeProxy = (int)(&Gap::Core::igFile::getClassMetaSafe);
}

void igPsx2File_StaticInitCallback(void) {
    igPsx2File_InitDefaultPrefix();
}

