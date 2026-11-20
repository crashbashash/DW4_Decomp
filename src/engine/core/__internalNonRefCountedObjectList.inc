void **__internalNonRefCountedObjectList_Create(int pool) {
    void **list;

    if (g_objectSystem->active != 0) {
        __internalNonRefCountedObjectList_EnsureRegistered();
        list = (void **)(((void **)igMetaObject_CreateInstance((igMetaObject *)g___internalNonRefCountedObjectList_metaObject, (igMemoryPoolView *)pool)));
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

    if (g_objectSystem->active != 0) {
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
    if (g___internalNonRefCountedObjectList_metaObject == 0) {
        g___internalNonRefCountedObjectList_metaObject = (igMetaObject *)igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g___internalNonRefCountedObjectList_metaObject;
}

igMetaObject *__internalNonRefCountedObjectList_GetMetaObject(void)
{
    igMetaObject *g = g___internalNonRefCountedObjectList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        __internalNonRefCountedObjectList_EnsureRegistered();
    return g___internalNonRefCountedObjectList_metaObject;
}

int __internalNonRefCountedObjectList_GetVTable(void) {
    int o[4];

    ObjectPointerList_Init((__internalNonRefCountedObjectList *)o);
    return *(int *)((char *)o + g_objectSystem->vtableProbeOffset);
}

void __internalNonRefCountedObjectList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(__internalNonRefCountedObjectList_Register);
}

CallbackArray *__internalNonRefCountedObjectList_Register(void) {
    return igMetaObject_RegisterClass(
        0,
        &g___internalNonRefCountedObjectList_metaObject,
        Gap::Core::igObject::arkRegisterInternal,
        igObject_GetMetaObject_ParentAccessor,
        __internalNonRefCountedObjectList_GetMetaObjectFunction,
        "__internalNonRefCountedObjectList",
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

static FieldFactory g___internalNonRefCountedObjectList_ctorTable[] = {
    (FieldFactory)igMemoryRefMetaField_Create,
    (FieldFactory)igIntMetaField_Create,
};
static const char *g___internalNonRefCountedObjectList_fieldTable[] = {
    "_data",
    "_count",
};
static igMetaField **g___internalNonRefCountedObjectList_fieldDescriptors[] = {
    &g___internalNonRefCountedObjectList_dataMetaField,
    &g___internalNonRefCountedObjectList_countMetaField,
};
static int g___internalNonRefCountedObjectList_fieldOffsets[] = {
    8,
    12,
};

void __internalNonRefCountedObjectList_InitFields(void) {
    int first;
    void *field;
    void *meta;

    meta = (void *)g___internalNonRefCountedObjectList_metaObject;
    first = igMetaObject_GetFieldCount((igMetaObject *)meta);
    igMetaObject_CreateFields((igMetaObject *)meta, g___internalNonRefCountedObjectList_ctorTable, 2);
    field = (void *)(((void *)igMetaObject_GetFieldAt((igMetaObject *)meta, first)));
    ((igMemoryRefMetaField *)field)->_memType = (int)Gap::Core::igObjectRefMetaField::getMetaField();
    ((igMemoryRefMetaField *)field)->_memSize = 0x40;
    ((igRefMetaField *)field)->_construct = 1;
    ((igRefMetaField *)field)->_destruct = 1;
    ((igMemoryRefMetaField *)field)->_releaseOnCopy = 1;
    ((igMemoryRefMetaField *)field)->_releaseOnReset = 1;
    ((igMemoryRefMetaField *)field)->_refCounted = 0;
    igMetaObject_NameFields((igMetaObject *)meta, g___internalNonRefCountedObjectList_fieldTable, g___internalNonRefCountedObjectList_fieldDescriptors, g___internalNonRefCountedObjectList_fieldOffsets, first);
}

