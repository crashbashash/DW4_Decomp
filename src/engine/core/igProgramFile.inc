igMetaObject *g_igProgramFile_metaObject;
igMetaField *g_igProgramFile_fileNameMetaField;
igMetaField *g_igProgramFile_fileMetaField;

igMetaObject *igProgramFile_GetMetaObject(void)
{
    igMetaObject *g = g_igProgramFile_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igProgramFile_EnsureRegistered();
    return g_igProgramFile_metaObject;
}

int igProgramFile_GetVTable(void) {
    igProgramFile obj;
    char *o;
    int *a1;
    int v0;
    int t;
    igObject_InitHeader((igObject *)&obj);
    *(int **)&obj._vtable = &g_igProgramFile_vtable[0];
    obj._fileName = 0;
    obj._file = 0;
    t = *(int *)((char *)&obj + g_objectSystem->vtableProbeOffset);
    obj._vtable = (int)&g_igProgramFile_vtable[0];
    if (&obj._file != 0) {
        o = (char *)obj._file;
        igObject::release(((igObject *)o));
    }
    if (&obj._fileName != 0) {
        o = (char *)obj._fileName;
        if (o != 0) {
            a1 = (int *)(o - 8);
            v0 = *(int *)(o - 4) - 1;
            *(int *)(o - 4) = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*a1), (StringTokenHeader *)a1);
            }
        }
    }
    return t;
}

void igProgramFile_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igProgramFile_Register);
}

static igMetaObjectCallback g_igProgramFile_callbackList[] = { igFile_EnsureRegistered, 0 };

CallbackArray *igProgramFile_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igProgramFile_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        igProgramFile_GetMetaObjectFunction,
        "igProgramFile",
        0x10,
        igProgramFile_GetVTable,
        igProgramFile_InitFields,
        0,
        g_igProgramFile_callbackList
    );
}

void igProgramFile_GetMetaObjectFunction(void) {
    igProgramFile_GetMetaObject();
}

static FieldFactory g_igProgramFile_ctorTable[] = {
    (FieldFactory)igStringMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igProgramFile_fieldTable[] = {
    "_fileName",
    "_file",
};
static igMetaField **g_igProgramFile_fieldDescriptors[] = {
    &g_igProgramFile_fileNameMetaField,
    &g_igProgramFile_fileMetaField,
};
static int g_igProgramFile_fieldOffsets[] = {
    8,
    12,
};

void igProgramFile_InitFields(void) {
    int base;
    void *fileField;
    void *meta;

    ((igMetaObject *)(g_igProgramFile_metaObject))->_persistent = 0;
    meta = (void *)(g_igProgramFile_metaObject);
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igProgramFile_ctorTable, 2);
    ((igMetaField *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base))))->_persistent = 0;
    fileField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 1)));
    ((igObjectRefMetaField *)fileField)->_metaObject = (int)igFile_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)fileField)->_construct = 0;
    ((igObjectRefMetaField *)fileField)->_persistent = 0;
    igMetaObject_NameFields((igMetaObject *)meta, g_igProgramFile_fieldTable, g_igProgramFile_fieldDescriptors, g_igProgramFile_fieldOffsets, base);
    ((igMetaObject *)(g_igProgramFile_metaObject))->_abstractProxy = (int)igElfFile_GetMetaObjectFunction;
}

