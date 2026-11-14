igMetaObject *igMediaFile_GetMetaObject(void)
{
    igMetaObject *g = g_igMediaFile_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igMediaFile_EnsureRegistered();
    return g_igMediaFile_metaObject[0];
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
    vtable = *(int *)((char *)&file + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
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
                igObject_Destroy(r);
            }
        }
        if (deleteFlag > 0) {
            __dl__FPv(self);
        }
    }
    return self;
}

void igMediaFile_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igMediaFile_Register);
}

void igMediaFile_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        g_igMediaFile_metaObject,
        (igMetaObjectRegisterFunction)igFile_Register,
        igFile_GetPublishedMetaObject,
        igMediaFile_GetMetaObjectFunction,
        igMediaFile_className,
        0x44,
        igMediaFile_GetVTable,
        igMediaFile_InitFields,
        0,
        (igMetaObjectCallback *)g_igMediaFile_callbackList
    );
}

void igMediaFile_GetMetaObjectFunction(void) {
    igMediaFile_GetMetaObject();
}

void igMediaFile_InitFields(void) {
    int first;
    void *mediaField;
    void *bufferField;
    void *meta;

    meta = (void *)g_igMediaFile_metaObject[0];
    first = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, (igMetaField * (**)(void *))&g_igMediaFile_ctorTable[0], 9);
    bufferField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, first + 7)));
    ((igMemoryRefMetaField *)bufferField)->_memType = igUnsignedCharMetaField_GetDefaultDescriptor();
    mediaField = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, first + 8)));
    ((igObjectRefMetaField *)mediaField)->_metaObject = (int)igMedia_GetOrCreateMetaObject();
    igMetaObject_NameFields((igMetaObject *)meta, (const char **)&g_igMediaFile_fieldTable[0], (igMetaField ***)&g_igMediaFile_fieldDescriptors[0], &g_igMediaFile_fieldOffsets[0], first);
}

