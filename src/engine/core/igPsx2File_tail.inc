int igPsx2File_Create(int allocator) {
    igPsx2File_EnsureRegistered();
    return igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x586D70), (igMemoryPoolView *)allocator);
}

igMetaObject *igPsx2File_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2File_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igPsx2File_EnsureRegistered();
    return g_igPsx2File_metaObject[0];
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
    vtable = *(int *)((char *)&f + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    f._vtable = (int)&g_igPsx2File_vtable[0];
    FUN_00130720(&f._prefix, -1);
    igFile_Destroy((igFile *)&f, (short)0);
    return vtable;
}

void igPsx2File_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igPsx2File_Register);
}

void igPsx2File_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        g_igPsx2File_metaObject,
        (igMetaObjectRegisterFunction)igFile_Register,
        igFile_GetPublishedMetaObject,
        igPsx2File_GetMetaObjectFunction,
        igPsx2File_className,
        0x4C,
        igPsx2File_GetVTable,
        igPsx2File_InitFields,
        igPsx2File_StaticInitCallback,
        0
    );
}

void igPsx2File_InitFields(void) {
    void *prefixField;
    int base;
    void *bufferField;
    void *meta;

    meta = (void *)(g_igPsx2File_metaObject[0]);
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, (igMetaField * (**)(void *))&g_igPsx2File_ctorTable[0], 8);
    bufferField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base)));
    ((igMemoryRefMetaField *)bufferField)->_memType = igUnsignedCharMetaField_GetDefaultDescriptor();
    prefixField = ((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 7));
    ((igMetaField *)prefixField)->_resetMethod = 3;
    igMetaObject_NameFields((igMetaObject *)meta, (const char **)&g_igPsx2File_fieldTable[0], (igMetaField ***)&g_igPsx2File_fieldDescriptors[0], &g_igPsx2File_fieldOffsets[0], base);
    ((igMetaObject *)g_igPsx2File_metaObject[0])->_writeProxy = (int)(&igFile_GetMetaObjectFunction);
}

void igPsx2File_StaticInitCallback(void) {
    igPsx2File_InitDefaultPrefix();
}

