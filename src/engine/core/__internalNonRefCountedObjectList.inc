void **__internalNonRefCountedObjectList_Create(int pool) {
    void **list;

    if (*g_objectSystem[0] != 0) {
        __internalNonRefCountedObjectList_EnsureRegistered();
        list = (void **)(((void **)igMetaObject_CreateInstance((igMetaObject *)g___internalNonRefCountedObjectList_metaObject[0], (igMemoryPoolView *)pool)));
    } else {
        list = (void **)(((void **)igObject_AllocateRawStorage(0x10, 0, (igMemoryPoolView *)pool)));
        if (list != 0) {
            list = (void **)(((void **)ObjectPointerList_Construct((__internalNonRefCountedObjectList *)list, 1)));
        }
        ((igObjectDispatchView *)(list))->InitDefaults();
        ((igObjectDispatchView *)(list))->userConstruct((int)(0));
    }
    return list;
}

int __internalNonRefCountedObjectList_Clone(int source, int copyMode) {
    int copy;

    if (*g_objectSystem[0] != 0) {
        __internalNonRefCountedObjectList_EnsureRegistered();
        return igObject_CloneViaMetadata((void **)source, copyMode);
    }
    copy = ((int)igObject_AllocateRawStorageDefault(0x10, 0));
    if (copy != 0) {
        copy = ((int)ObjectPointerList_CopyConstruct((__internalNonRefCountedObjectList *)copy, (__internalNonRefCountedObjectList *)source));
    }
    return copy;
}

igMetaObject *__internalNonRefCountedObjectList_GetOrCreateMetaObject(void) {
    if (g___internalNonRefCountedObjectList_metaObject[0] == 0) {
        g___internalNonRefCountedObjectList_metaObject[0] = (igMetaObject *)igMetaObject_Create(((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData)));
    }
    return g___internalNonRefCountedObjectList_metaObject[0];
}

igMetaObject *__internalNonRefCountedObjectList_GetMetaObject(void)
{
    igMetaObject *g = g___internalNonRefCountedObjectList_metaObject[0];
    if (!g || ((g->_validity & 4) != 0) == false)
        __internalNonRefCountedObjectList_EnsureRegistered();
    return g___internalNonRefCountedObjectList_metaObject[0];
}

int __internalNonRefCountedObjectList_GetVTable(void) {
    int o[4];

    ObjectPointerList_Init((__internalNonRefCountedObjectList *)o);
    return *(int *)((char *)o + *(int *)((char *)(((void * *)g_objectSystem)[0]) + 916));
}

void __internalNonRefCountedObjectList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit((StaticInitCallbacks * (*)())__internalNonRefCountedObjectList_Register);
}

void __internalNonRefCountedObjectList_Register(void) {
    igMetaObject_RegisterClass(
        0,
        g___internalNonRefCountedObjectList_metaObject,
        (igMetaObjectRegisterFunction)igObject_Register,
        (igMetaObjectGetFunction)igObject_GetMetaObject_ParentAccessor,
        __internalNonRefCountedObjectList_GetMetaObjectFunction,
        __internalNonRefCountedObjectList_className,
        0x10,
        __internalNonRefCountedObjectList_GetVTable,
        __internalNonRefCountedObjectList_InitFields,
        0,
        0
    );
}

void __internalNonRefCountedObjectList_GetMetaObjectFunction(void) {
    __internalNonRefCountedObjectList_GetMetaObject();
}

void __internalNonRefCountedObjectList_InitFields(void) {
    int first;
    void *field;
    void *meta;

    meta = (void *)g___internalNonRefCountedObjectList_metaObject[0];
    first = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, (igMetaField * (**)(void *))&g___internalNonRefCountedObjectList_ctorTable[0], 2);
    field = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, first)));
    ((igMemoryRefMetaField *)field)->_memType = igObjectRefMetaField_GetDefaultDescriptor();
    ((igMemoryRefMetaField *)field)->_memSize = 0x40;
    ((igRefMetaField *)field)->_construct = 1;
    ((igRefMetaField *)field)->_destruct = 1;
    ((igMemoryRefMetaField *)field)->_releaseOnCopy = 1;
    ((igMemoryRefMetaField *)field)->_releaseOnReset = 1;
    ((igMemoryRefMetaField *)field)->_refCounted = 0;
    igMetaObject_NameFields((igMetaObject *)meta, (const char **)&g___internalNonRefCountedObjectList_fieldTable[0], (igMetaField ***)&g___internalNonRefCountedObjectList_fieldDescriptors[0], &g___internalNonRefCountedObjectList_fieldOffsets[0], first);
}

