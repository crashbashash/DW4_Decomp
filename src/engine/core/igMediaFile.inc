igMetaObject *g_igMediaFile_metaObject;
igMetaField *g_igMediaFile_isBinaryMetaField;
igMetaField *g_igMediaFile_isOpenMetaField;
igMetaField *g_igMediaFile_writeMetaField;
igMetaField *g_igMediaFile_readMetaField;
igMetaField *g_igMediaFile_bufSizeMetaField;
igMetaField *g_igMediaFile_fileSizeMetaField;
igMetaField *g_igMediaFile_bufPosMetaField;
igMetaField *g_igMediaFile_fBufMetaField;
igMetaField *g_igMediaFile_mediaMetaField;

igMetaObject *igMediaFile_GetMetaObject(void)
{
    igMetaObject *g = g_igMediaFile_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igMediaFile_EnsureRegistered();
    return g_igMediaFile_metaObject;
}

int igMediaFile_GetVTable(void) {
    igMediaFile file;
    int vtable;
    char *ps;
    igObject_InitHeader((igObject *)&file);
    file._name = 0;
    file._fileName = 0;
    file._completeFilename = 0;
    file._vtable = (int)&g_igMediaFile_vtable[0];
    ps = (char *)&file._media;
    *(int *)ps = 0;
    vtable = *(int *)((char *)&file + g_objectSystem->vtableProbeOffset);
    file._vtable = (int)&g_igMediaFile_vtable[0];
    igSmartPointer_igMedia_Destruct((void **)ps, -1);
    igFile_Destroy((igFile *)&file, 0);
    return vtable;
}

void **igSmartPointer_igMedia_Destruct(void **self, short deleteFlag) {
    int *r;
    if (self != 0) {
        r = (int *)*self;
        if (r != 0) {
            r[1] = r[1] - 1;
            if ((r[1] & 0x7fffff) == 0) {
                igObject_Destroy((igObject *)r);
            }
        }
        if (deleteFlag > 0) {
            operator delete(self);
        }
    }
    return self;
}

void igMediaFile_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(igMediaFile_Register);
}

static igMetaObjectCallback g_igMediaFile_callbackList[] = { Gap::Core::igMedia::arkRegister, 0 };

CallbackArray *igMediaFile_Register(void) {
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        0,
        &g_igMediaFile_metaObject,
        igFile_Register,
        igFile_GetPublishedMetaObject,
        igMediaFile_GetMetaObjectFunction,
        "igMediaFile",
        0x44,
        igMediaFile_GetVTable,
        igMediaFile_InitFields,
        0,
        g_igMediaFile_callbackList
    );
}

void igMediaFile_GetMetaObjectFunction(void) {
    igMediaFile_GetMetaObject();
}

static FieldFactory g_igMediaFile_ctorTable[] = {
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igMemoryRefMetaField_Create,
    (FieldFactory)igObjectRefMetaField_Create,
};
static const char *g_igMediaFile_fieldTable[] = {
    "_isBinary",
    "_isOpen",
    "_write",
    "_read",
    "_bufSize",
    "_fileSize",
    "_bufPos",
    "_fBuf",
    "_media",
};
static igMetaField **g_igMediaFile_fieldDescriptors[] = {
    &g_igMediaFile_isBinaryMetaField,
    &g_igMediaFile_isOpenMetaField,
    &g_igMediaFile_writeMetaField,
    &g_igMediaFile_readMetaField,
    &g_igMediaFile_bufSizeMetaField,
    &g_igMediaFile_fileSizeMetaField,
    &g_igMediaFile_bufPosMetaField,
    &g_igMediaFile_fBufMetaField,
    &g_igMediaFile_mediaMetaField,
};
static int g_igMediaFile_fieldOffsets[] = {
    44,
    45,
    46,
    47,
    48,
    52,
    56,
    60,
    64,
};

void igMediaFile_InitFields(void) {
    int first;
    void *mediaField;
    void *bufferField;
    void *meta;

    meta = (void *)g_igMediaFile_metaObject;
    first = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igMediaFile_ctorTable, 9);
    bufferField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, first + 7)));
    ((igMemoryRefMetaField *)bufferField)->_memType = (int)Gap::Core::igUnsignedCharMetaField::getMetaField();
    mediaField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, first + 8)));
    ((igObjectRefMetaField *)mediaField)->_metaObject = (int)Gap::Core::igMedia::getClassTypeLazy();
    igMetaObject_NameFields((igMetaObject *)meta, g_igMediaFile_fieldTable, g_igMediaFile_fieldDescriptors, g_igMediaFile_fieldOffsets, first);
}

