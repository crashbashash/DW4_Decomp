void igElfFile_GetMetaObjectFunction(void) {
    igElfFile_GetMetaObject();
}

igMetaObject *g_igElfFile_metaObject;
igMetaField *g_igElfFile_headerMetaField;
igMetaField *g_igElfFile_sectionHeaderStringTableSizeMetaField;
igMetaField *g_igElfFile_sectionHeaderStringTableMetaField;
igMetaField *g_igElfFile_sectionHeaderCountMetaField;
igMetaField *g_igElfFile_sectionHeadersMetaField;
igMetaField *g_igElfFile_symbolStringTableSizeMetaField;
igMetaField *g_igElfFile_symbolStringTableMetaField;
igMetaField *g_igElfFile_symbolCountMetaField;
igMetaField *g_igElfFile_symbolsMetaField;

void * igElfFile_Create(int pool) {
    igElfFile_EnsureRegistered();
    return (void *)(igMetaObject_CreateInstance(g_igElfFile_metaObject, (igMemoryPoolView *)pool));
}

igMetaObject *igElfFile_GetMetaObject(void)
{
    igMetaObject *g = g_igElfFile_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igElfFile_EnsureRegistered();
    return g_igElfFile_metaObject;
}

int igElfFile_GetVTable(void) {
    igElfFile elf;
    int r;
    int *tv1, *ta1;
    int tc1;
    char *q1;
    igObject *q2;
    igObject_InitHeader((igObject *)&elf);
    elf._vtable = (int)&g_igProgramFile_vtable[0];
    q1 = (char *)&elf._fileName;
    *(int *)q1 = 0;
    q2 = (igObject *)&elf._file;
    *(int *)q2 = 0;
    elf._vtable = (int)&g_igElfFile_vtable[0];
    r = *(int *)((char *)&elf + g_objectSystem->vtableProbeOffset);
    elf._vtable = (int)&g_igProgramFile_vtable[0];
    if (q2 != 0) {
        q2 = *(igObject **)q2;
        igObject::release(q2);
    }
    if (q1 != 0) {
        tv1 = *(int **)q1;
        if (tv1 != 0) {
            ta1 = tv1 - 2;
            tc1 = tv1[-1] - 1;
            tv1[-1] = tc1;
            if (tc1 == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*ta1), (StringTokenHeader *)ta1);
            }
        }
    }
    return r;
}

void igElfFile_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igElfFile_Register);
}

CallbackArray *igElfFile_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igElfFile_metaObject,
        igProgramFile_Register,
        (igMetaObjectGetFunction)igProgramFile_GetPublishedMetaObject,
        igElfFile_GetMetaObjectFunction,
        "igElfFile",
        0x64,
        igElfFile_GetVTable,
        igElfFile_InitFields,
        0,
        0
    );
}

int igProgramFile_GetPublishedMetaObject(void) {
    return (int)g_igProgramFile_metaObject;
}

static FieldFactory g_igElfFile_ctorTable[] = {
    (FieldFactory)igStructMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igStructMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igStructMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igStructMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igStructMetaField_Create,
};
static const char *g_igElfFile_fieldTable[] = {
    "_header",
    "_sectionHeaderStringTableSize",
    "_sectionHeaderStringTable",
    "_sectionHeaderCount",
    "_sectionHeaders",
    "_symbolStringTableSize",
    "_symbolStringTable",
    "_symbolCount",
    "_symbols",
};
static igMetaField **g_igElfFile_fieldDescriptors[] = {
    &g_igElfFile_headerMetaField,
    &g_igElfFile_sectionHeaderStringTableSizeMetaField,
    &g_igElfFile_sectionHeaderStringTableMetaField,
    &g_igElfFile_sectionHeaderCountMetaField,
    &g_igElfFile_sectionHeadersMetaField,
    &g_igElfFile_symbolStringTableSizeMetaField,
    &g_igElfFile_symbolStringTableMetaField,
    &g_igElfFile_symbolCountMetaField,
    &g_igElfFile_symbolsMetaField,
};
static int g_igElfFile_fieldOffsets[] = {
    16,
    68,
    72,
    76,
    80,
    84,
    88,
    92,
    96,
};

void igElfFile_InitFields(void) {
    void *headerField;
    void *sectionHeaderStringTableField;
    void *sectionHeadersField;
    void *symbolStringTableField;
    void *symbolsField;
    int first;
    void *meta;

    ((igMetaObject *)g_igElfFile_metaObject)->_persistent = 0;
    meta = (void *)(g_igElfFile_metaObject);
    first = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igElfFile_ctorTable, 9);
    headerField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, first)));
    ((igMetaField *)headerField)->_size = 0x34;
    ((igMetaField *)headerField)->_persistent = 0;
    ((igMetaField *)((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, first + 1)))->_persistent = 0;
    sectionHeaderStringTableField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, first + 2)));
    ((igMetaField *)sectionHeaderStringTableField)->_size = 4;
    ((igMetaField *)sectionHeaderStringTableField)->_persistent = 0;
    ((igMetaField *)((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, first + 3)))->_persistent = 0;
    sectionHeadersField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, first + 4)));
    ((igMetaField *)sectionHeadersField)->_size = 4;
    ((igMetaField *)sectionHeadersField)->_persistent = 0;
    ((igMetaField *)((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, first + 5)))->_persistent = 0;
    symbolStringTableField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, first + 6)));
    ((igMetaField *)symbolStringTableField)->_size = 4;
    ((igMetaField *)symbolStringTableField)->_persistent = 0;
    ((igMetaField *)((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, first + 7)))->_persistent = 0;
    symbolsField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, first + 8)));
    ((igMetaField *)symbolsField)->_size = 4;
    ((igMetaField *)symbolsField)->_persistent = 0;
    igMetaObject_NameFields((igMetaObject *)meta, g_igElfFile_fieldTable, g_igElfFile_fieldDescriptors, g_igElfFile_fieldOffsets, first);
}

