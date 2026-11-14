void igPsx2Media_Create(int pool) {
    igPsx2Media_EnsureRegistered();
    igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x586CF8), (igMemoryPoolView *)pool);
}

igMetaObject *igPsx2Media_GetMetaObject(void)
{
    igMetaObject *g = g_igPsx2Media_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igPsx2Media_EnsureRegistered();
    return g_igPsx2Media_metaObject[0];
}

int igPsx2Media_GetVTable(void) {
    igPsx2Media media;
    int result;
    igObject * sema;
    igObject * connection;
    igObject * conversionString;
    igObject_InitHeader((igObject *)&media);
    media._vtable = (int)(&g_igPsx2Media_vtable[0]);
    connection = (igObject *)&media._connection;
    *(int *)connection = 0;
    sema = (igObject *)&media._sema;
    *(int *)sema = 0;
    conversionString = (igObject *)&media._conversionString;
    *(int *)conversionString = 0;
    result = *(int *)((char *)&media + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    media._vtable = (int)(&g_igPsx2Media_vtable[0]);
    if (conversionString != 0) {
        conversionString = *(igObject **)conversionString;
        if (conversionString != 0) {
            conversionString->_refCount = (int)((int) (conversionString->_refCount - 1));
            if (((unsigned long long) ((long long)(int) conversionString->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(conversionString);
            }
        }
    }
    if (sema != 0) {
        sema = *(igObject **)sema;
        if (sema != 0) {
            sema->_refCount = (int)((int) (sema->_refCount - 1));
            if (((unsigned long long) ((long long)(int) sema->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(sema);
            }
        }
    }
    if (connection != 0) {
        connection = *(igObject **)connection;
        if (connection != 0) {
            connection->_refCount = (int)((int) (connection->_refCount - 1));
            if (((unsigned long long) ((long long)(int) connection->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(connection);
            }
        }
    }
    return result;
}

void igPsx2Media_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igPsx2Media_Register);
}

void igPsx2Media_Register(void) {
    CoreLibrary_MarkRegistered();
    igMetaObject_RegisterClass(
        0,
        g_igPsx2Media_metaObject,
        (igMetaObjectRegisterFunction)igMedia_Register,
        igMedia_GetPublishedMetaObject,
        igPsx2Media_GetMetaObjectFunction,
        igPsx2Media_className,
        0x28,
        igPsx2Media_GetVTable,
        igPsx2Media_InitFields,
        0,
        (igMetaObjectCallback *)g_igPsx2Media_callbackList
    );
}

igMetaObject *igMedia_GetPublishedMetaObject(void) {
    return g_igMedia_metaObject[0];
}

void igPsx2Media_InitFields(void) {
    int base;
    void *field;
    igRawRefMetaField *handlePoolField;
    void *meta;

    meta = (void *)g_igPsx2Media_metaObject[0];
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, (igMetaField * (**)(void *))&g_igPsx2Media_ctorTable[0], 8);
    field = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base)));
    ((igMemoryRefMetaField *)field)->_memType = igUnsignedCharMetaField_GetDefaultDescriptor();
    ((igMemoryRefMetaField *)field)->_resetMethod = 3;
    ((igMemoryRefMetaField *)field)->_destruct = 1;
    ((igMemoryRefMetaField *)field)->_releaseOnCopy = 1;
    ((igMemoryRefMetaField *)field)->_releaseOnReset = 1;
    field = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 1)));
    ((igObjectRefMetaField *)field)->_metaObject = (int)igPsx2IopRpcConnection_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)field)->_construct = 1;
    field = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 2)));
    ((igObjectRefMetaField *)field)->_metaObject = (int)igSemaphore_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)field)->_construct = 1;
    field = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 3)));
    ((igMemoryRefMetaField *)field)->_memType = igUnsignedCharMetaField_GetDefaultDescriptor();
    ((igMemoryRefMetaField *)field)->_resetMethod = 3;
    ((igMemoryRefMetaField *)field)->_destruct = 1;
    ((igMemoryRefMetaField *)field)->_releaseOnCopy = 1;
    ((igMemoryRefMetaField *)field)->_releaseOnReset = 1;
    field = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 4)));
    ((igMemoryRefMetaField *)field)->_memType = igUnsignedCharMetaField_GetDefaultDescriptor();
    ((igMemoryRefMetaField *)field)->_resetMethod = 3;
    ((igMemoryRefMetaField *)field)->_destruct = 1;
    ((igMemoryRefMetaField *)field)->_releaseOnCopy = 1;
    ((igMemoryRefMetaField *)field)->_releaseOnReset = 1;
    handlePoolField = (igRawRefMetaField *)((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 5));
    handlePoolField->_resetMethod = 3;
    field = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 6)));
    ((igObjectRefMetaField *)field)->_metaObject = (int)igStringObj_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)field)->_construct = 1;
    igMetaObject_NameFields((igMetaObject *)meta, (const char **)&g_igPsx2Media_fieldTable[0], (igMetaField ***)&g_igPsx2Media_fieldDescriptors[0], &g_igPsx2Media_fieldOffsets[0], base);
}

