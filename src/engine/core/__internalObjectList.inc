igMetaObject *g___internalObjectList_metaObject;
int g___internalObjectList_dataDescriptorCell;

void **InternalObjectList_Create(int allocator) {
    void **list;

    if (g_objectSystem->active != 0) {
        __internalObjectList_EnsureRegistered();
        list = (void **)(((void **)igMetaObject_CreateInstance((igMetaObject *)((int)g___internalObjectList_metaObject), (igMemoryPoolView *)allocator)));
    } else {
        list = (void **)(((void **)igObject_AllocateRawStorage(0x10, 0, (igMemoryPoolView *)allocator)));
        if (list != 0) {
            list = (void **)(((void **)InternalObjectList_Construct((__internalObjectList *)list, 1)));
        }
        ((igObjectDispatchView *)(list))->InitDefaults();
        ((igObjectDispatchView *)(list))->userConstruct((int)(0));
    }
    return list;
}

int __internalObjectList_Clone(int source, int copyMode) {
    int clone;

    if (g_objectSystem->active != 0) {
        __internalObjectList_EnsureRegistered();
        return igObject_CloneViaMetadata((void **)source, copyMode);
    }
    clone = ((int)igObject_AllocateRawStorageDefault(0x10, 0));
    if (clone != 0) {
        clone = ((int)InternalObjectList_CopyConstruct((__internalObjectList *)clone, (__internalObjectList *)source));
    }
    return clone;
}

igMetaObject *__internalObjectList_GetOrCreateMetaObject(void) {
    if (g___internalObjectList_metaObject == 0) {
        g___internalObjectList_metaObject = (igMetaObject *)igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return g___internalObjectList_metaObject;
}

igMetaObject *__internalObjectList_GetMetaObject(void)
{
    igMetaObject *g = g___internalObjectList_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        __internalObjectList_EnsureRegistered();
    return g___internalObjectList_metaObject;
}

int __internalObjectList_GetVTable(void) {
    int o[4];
    InternalObjectList_Init((__internalObjectList *)o);
    return *(int *)((char *)o + g_objectSystem->vtableProbeOffset);
}

void __internalObjectList_EnsureRegistered(void)
{
    igMetaObject_RunStaticInit(__internalObjectList_Register);
}

CallbackArray *__internalObjectList_Register(void) {
    return igMetaObject_RegisterClass(
        0,
        &g___internalObjectList_metaObject,
        __internalNonRefCountedObjectList_Register,
        __internalNonRefCountedObjectList_GetPublishedMetaObject,
        __internalObjectList_GetMetaObjectFunction,
        "__internalObjectList",
        0x10,
        __internalObjectList_GetVTable,
        __internalObjectList_InitFields,
        0,
        0
    );
}

void __internalObjectList_GetMetaObjectFunction(void) {
    __internalObjectList_GetMetaObject();
}

igMetaObject *g___internalNonRefCountedObjectList_metaObject;
igMetaField *g___internalNonRefCountedObjectList_dataMetaField;
igMetaField *g___internalNonRefCountedObjectList_countMetaField;

igMetaObject *__internalNonRefCountedObjectList_GetPublishedMetaObject(void) {
    return g___internalNonRefCountedObjectList_metaObject;
}


void __internalObjectList_InitFields(void) {
    void **found;
    int index;
    igMetaObject *meta;
    igMemoryRefMetaField *clone;

    meta = g___internalObjectList_metaObject;
    found = (void **)igMetaObject_FindFieldByName(meta, data);
    index = ObjectPointerList_FindIndex((__internalNonRefCountedObjectList *)meta->_metaFields, (int)found);
    clone = (igMemoryRefMetaField *)(((igObjectDispatchView *)(found))->CloneViaMetadata((int)(1)));
    clone->_refCounted = 1;
    clone->_externalEnumStorage = (int)(&g___internalObjectList_dataDescriptorCell);
    igMetaObject_FinalizeAndReplaceField(meta, index, (igMetaField *)clone);
    clone->release();
}

