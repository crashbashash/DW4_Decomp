igMetaObject *g_igMemoryFile_metaObject;
igMetaField *g_igMemoryFile_bIsOpenMetaField;
igMetaField *g_igMemoryFile_bufferMetaField;
igMetaField *g_igMemoryFile_iBufferSizeMetaField;
igMetaField *g_igMemoryFile_iSeekPositionMetaField;

void *igMemoryFile_Create(int pool) {
    igMemoryFile_EnsureRegistered();
    return (void *)igMetaObject_CreateInstance(g_igMemoryFile_metaObject, (igMemoryPoolView *)pool);
}

igMetaObject *igMemoryFile_GetMetaObject(void)
{
    igMetaObject *g = g_igMemoryFile_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igMemoryFile_EnsureRegistered();
    return g_igMemoryFile_metaObject;
}

int igMemoryFile_GetVTable(void) {
    igMemoryFile file;
    int vtable;

    igObject_InitHeader((igObject *)&file);
    file._name = 0;
    file._fileName = 0;
    file._completeFilename = 0;
    file._vtable = (int)(&g_igMemoryFile_vtable[0]);
    vtable = *(int *)((char *)&file + *(int *)((char *)((*(void * *)&g_objectSystem)) + 916));
    file._vtable = (int)(&g_igMemoryFile_vtable[0]);
    igFile_Destroy((igFile *)&file, 0);
    return vtable;
}

void *igFile_Destroy(igFile *self, short deleteFlag) {
    void *p;
    int *h;
    int rc;

    if (self != 0) {
        self->_vtable = (int)&g_igFile_vtable[0];
        if (&self->_completeFilename) {
            p = (void *)self->_completeFilename;
            if (p != 0) {
                h = (int *)((char *)(p) - 8);
                rc = *(int *)((char *)(p) - 4) - 1;
                *(int *)((char *)(p) - 4) = rc;
                if (rc == 0) {
                    StringChunk_ReleaseHeader((StringChunk *)(*h), (int)h);
                }
            }
        }
        if (&self->_fileName) {
            p = (void *)self->_fileName;
            if (p != 0) {
                h = (int *)((char *)(p) - 8);
                rc = *(int *)((char *)(p) - 4) - 1;
                *(int *)((char *)(p) - 4) = rc;
                if (rc == 0) {
                    StringChunk_ReleaseHeader((StringChunk *)(*h), (int)h);
                }
            }
        }
        if (self != 0) {
            self->_vtable = (int)&g_igNamedObject_vtable[0];
            if (&self->_name) {
                p = (void *)self->_name;
                if (p != 0) {
                    h = (int *)((char *)(p) - 8);
                    rc = *(int *)((char *)(p) - 4) - 1;
                    *(int *)((char *)(p) - 4) = rc;
                    if (rc == 0) {
                        StringChunk_ReleaseHeader((StringChunk *)(*h), (int)h);
                    }
                }
            }
        }
        if (deleteFlag > 0) {
            Memory_FreeBufferAliasC((int)self);
        }
    }
    return self;
}

void igMemoryFile_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igMemoryFile_Register);
}

void igMemoryFile_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        &g_igMemoryFile_metaObject,
        (igMetaObjectRegisterFunction)igFile_Register,
        igFile_GetPublishedMetaObject,
        igMemoryFile_GetMetaObjectFunction,
        "igMemoryFile",
        0x3C,
        igMemoryFile_GetVTable,
        igMemoryFile_InitFields,
        igMemoryFile_StaticInitCallback,
        0
    );
}

void igMemoryFile_GetMetaObjectFunction(void) {
    igMemoryFile_GetMetaObject();
}

igMetaObject *g_igFile_metaObject;
igMetaField *g_igFile_fileNameMetaField;
igMetaField *g_igFile_readModeMetaField;
igMetaField *g_igFile_openModeMetaField;
igMetaField *g_igFile_fileHandleMetaField;
igMetaField *g_igFile_optimalReadChunkSizeMetaField;
igMetaField *g_igFile_optimalWriteChunkSizeMetaField;
igMetaField *g_igFile_pageSizeMetaField;
igMetaField *g_igFile_completeFilenameMetaField;

igMetaObject *igFile_GetPublishedMetaObject(void) {
    return g_igFile_metaObject;
}

static FieldFactory g_igMemoryFile_ctorTable[] = {
    (FieldFactory)igBoolMetaField_Create,
    (FieldFactory)igRawRefMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
};
static const char *g_igMemoryFile_fieldTable[] = {
    "_bIsOpen",
    "_buffer",
    "_iBufferSize",
    "_iSeekPosition",
};
static igMetaField **g_igMemoryFile_fieldDescriptors[] = {
    &g_igMemoryFile_bIsOpenMetaField,
    &g_igMemoryFile_bufferMetaField,
    &g_igMemoryFile_iBufferSizeMetaField,
    &g_igMemoryFile_iSeekPositionMetaField,
};
static int g_igMemoryFile_fieldOffsets[] = {
    44,
    48,
    52,
    56,
};

void igMemoryFile_InitFields(void) {
    int first;
    void *meta;

    meta = (void *)(g_igMemoryFile_metaObject);
    first = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g_igMemoryFile_ctorTable, 4);
    igMetaObject_NameFields((igMetaObject *)meta, g_igMemoryFile_fieldTable, g_igMemoryFile_fieldDescriptors, g_igMemoryFile_fieldOffsets, first);
    g_igMemoryFile_metaObject->_writeProxy = (int)(&igFile_GetMetaObjectFunction);
    igMetaObject_AddExitCallback((int)&igMemoryFile_ExitCallback);
}

