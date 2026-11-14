void **igMetaObject_Create(int allocator) {
    void **metaObject;

    if (*g_objectSystem[0] != 0) {
        igMetaObject_EnsureRegistered();
        metaObject = (void **)(((void **)igMetaObject_CreateInstance((igMetaObject *)(((int *)g_igMetaObject_metaObject)[0]), (igMemoryPoolView *)allocator)));
    } else {
        metaObject = (void **)(((void **)igObject_AllocateRawStorage(0x64, 0, (igMemoryPoolView *)allocator)));
        if (metaObject != 0) {
            metaObject = (void **)(((void **)igMetaObject_Construct((igMetaObject *)metaObject, 1)));
        }
        ((igObjectDispatchView *)(metaObject))->InitDefaults();
        ((igObjectDispatchView *)(metaObject))->userConstruct((int)(0));
    }
    return metaObject;
}

void *igMetaObject_Clone(int source, int pool) {
    void *r;
    if (*g_objectSystem[0] != 0) {
        igMetaObject_EnsureRegistered();
        r = ((void *)igObject_CloneViaMetadata((void **)source, pool));
    } else {
        r = igObject_AllocateRawStorageDefault(0x64, 0);
        if (r != 0) {
            r = igMetaObject_CopyConstruct((igMetaObject *)r, (void *)source);
        }
    }
    return r;
}

igMetaObject *igMetaObject_GetOrCreateMetaObject(void) {
    if (g_igMetaObject_metaObject[0] == 0) {
        g_igMetaObject_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g_igMetaObject_metaObject[0];
}

igMetaObject *igMetaObject_GetMetaObject(void)
{
    igMetaObject *g = g_igMetaObject_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        igMetaObject_EnsureRegistered();
    return g_igMetaObject_metaObject[0];
}

int igMetaObject_GetVTable(void) {
    igMetaObject prototype;
    int *header;
    int *nameHeader;
    int vtable;
    int refCount;
    int nameRefCount;
    void *text;
    void *nameText;

    igMetaObject_Init((igMetaObject *)&prototype);
    vtable = *(int *)((char *)&prototype + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
    prototype._vtable = (int)&g_igMetaObject_vtable[0];
    if ((void **)&prototype._poolName != 0) {
        text = (void *)((void *)prototype._poolName);
        if (text != 0) {
            header = (int *)((char *)text - 8);
            refCount = *(int *)((char *)(text) - 4) - 1;
            *(int *)((char *)(text) - 4) = refCount;
            if (refCount == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*header), (int)header);
            }
        }
    }
    if ((void **)&prototype._name != 0) {
        nameText = (void *)((void *)prototype._name);
        if (nameText != 0) {
            nameHeader = (int *)((char *)nameText - 8);
            nameRefCount = *(int *)((char *)(nameText) - 4) - 1;
            *(int *)((char *)(nameText) - 4) = nameRefCount;
            if (nameRefCount == 0) {
                StringChunk_ReleaseHeader((StringChunk *)(*nameHeader), (int)nameHeader);
            }
        }
    }
    return vtable;
}

void igMetaObject_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())igMetaObject_Register);
}

void igMetaObject_Register(void) {
    igMetaObject_RegisterClass(
        0,
        g_igMetaObject_metaObject,
        (igMetaObjectRegisterFunction)igObject_Register,
        (igMetaObjectGetFunction)igObject_GetMetaObject_ParentAccessor,
        igMetaObject_GetMetaObjectFunction,
        igMetaObject_className,
        0x64,
        igMetaObject_GetVTable,
        igMetaObject_InitFields,
        0,
        (igMetaObjectCallback *)g_igMetaObject_callbackList
    );
}

void igMetaObject_GetMetaObjectFunction(void) {
    igMetaObject_GetMetaObject();
}

void igMetaObject_InitFields(void) {
    int base;
    void *field4;
    void *field5;
    void *field6;
    void *field7;
    void *field;
    void *field2;
    void *field3;
    void *field8;
    void *field9;
    void *field10;
    void *meta;

    meta = (void *)g_igMetaObject_metaObject[0];
    base = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, (igMetaField * (**)(void *))&g_igMetaObject_ctorTable[0], 0x19);
    field = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base)));
    igIntMetaField_SetDefault((void **)field, -1);
    ((igMetaField *)field)->_persistent = 0;
    field2 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 1)));
    igIntMetaField_SetDefault((void **)field2, -1);
    ((igMetaField *)field2)->_persistent = 0;
    igIntMetaField_SetDefault((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 2))), 1);
    igBoolMetaField_SetDefaultValue((void **)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 5))), 1);
    igStringMetaField_SetDefaultText((int *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 7))), 0);
    field3 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 8)));
    igIntMetaField_SetDefault((void **)field3, -1);
    ((igMetaField *)field3)->_persistent = 0;
    ((igMetaField *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 9))))->_persistent = 0;
    field4 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0xA)));
    ((igObjectRefMetaField *)field4)->_metaObject = (int)__internalObjectList_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)field4)->_construct = 1;
    ((igObjectRefMetaField *)field4)->_destruct = 1;
    ((igObjectRefMetaField *)field4)->_refCounted = 0;
    ((igMetaField *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0xB))))->_persistent = 0;
    field5 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0xC)));
    ((igObjectRefMetaField *)field5)->_metaObject = (int)__internalNonRefCountedObjectList_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)field5)->_destruct = 1;
    ((igObjectRefMetaField *)field5)->_refCounted = 0;
    ((igObjectRefMetaField *)field5)->_persistent = 0;
    field6 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0xD)));
    ((igObjectRefMetaField *)field6)->_metaObject = (int)__internalNonRefCountedObjectList_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)field6)->_destruct = 1;
    ((igObjectRefMetaField *)field6)->_refCounted = 0;
    ((igObjectRefMetaField *)field6)->_persistent = 0;
    field7 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0xE)));
    ((igObjectRefMetaField *)field7)->_metaObject = (int)igMetaObject_GetOrCreateMetaObject();
    ((igObjectRefMetaField *)field7)->_refCounted = 0;
    ((igObjectRefMetaField *)field7)->_persistent = 0;
    ((igMetaField *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0xF))))->_persistent = 0;
    ((igMetaField *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0x10))))->_persistent = 0;
    field8 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0x11)));
    ((igObjectRefMetaField *)field8)->_metaObject = (int)((int) g_igObject_metaObject[0]);
    ((igObjectRefMetaField *)field8)->_destruct = 1;
    ((igObjectRefMetaField *)field8)->_refCounted = 0;
    ((igObjectRefMetaField *)field8)->_persistent = 0;
    field9 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0x12)));
    igIntMetaField_SetDefault((void **)field9, -1);
    ((igMetaField *)field9)->_persistent = 0;
    ((igMetaField *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0x13))))->_persistent = 0;
    ((igMetaField *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0x14))))->_persistent = 0;
    ((igMetaField *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0x15))))->_persistent = 0;
    field10 = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0x16)));
    igUnsignedShortMetaField_SetDefaultValue((void **)field10, 4);
    ((igMetaField *)field10)->_persistent = 0;
    ((igMetaField *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, base + 0x17))))->_persistent = 0;
    igMetaObject_NameFields((igMetaObject *)meta, (const char **)&g_igMetaObject_fieldTable[0], (igMetaField ***)&g_igMetaObject_fieldDescriptors[0], &g_igMetaObject_fieldOffsets[0], base);
}

void *igMetaFieldInfo_Create(int pool) {
    igMetaFieldInfo_EnsureRegistered();
    return (void *)igMetaObject_CreateInstance((igMetaObject *)(*(int *)0x585CB8), (igMemoryPoolView *)pool);
}

