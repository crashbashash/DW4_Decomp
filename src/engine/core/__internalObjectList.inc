namespace Gap {
namespace Core {

igMetaObject *__internalObjectList::_Meta;
igMetaField *__internalObjectList::k_data;

__internalObjectList *__internalObjectList::_instantiateFromPool(igMemoryPoolView *pool)
{
    __internalObjectList *list;

    if (g_objectSystem->active != 0) {
        arkRegister();
        list = (__internalObjectList *)igMetaObject_CreateInstance(_Meta, pool);
    } else {
        list = (__internalObjectList *)igObject_AllocateRawStorage(sizeof(__internalObjectList), 0, pool);
        if (list != 0) {
            list = (__internalObjectList *)InternalObjectList_Construct((::__internalObjectList *)list, 1);
        }
        list->initDefaults();
        list->userConstruct(0);
    }
    return list;
}

igObject *__internalObjectList::cloneViaMetadata(int copyMode)
{
    if (g_objectSystem->active != 0) {
        arkRegister();
        return igObject::cloneViaMetadata(copyMode);
    }
    return new (igObject_AllocateRawStorageDefault(sizeof(__internalObjectList), 0), 0) __internalObjectList(*this);
}

igMetaObject *__internalObjectList::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *__internalObjectList::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *__internalObjectList::retrieveVTablePointer()
{
    __internalObjectList temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void __internalObjectList::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *__internalObjectList::arkRegisterInternal()
{
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::__internalNonRefCountedObjectList::arkRegisterInternal,
        Gap::Core::__internalNonRefCountedObjectList::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "__internalObjectList",
        sizeof(__internalObjectList),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

igMetaObject *__internalNonRefCountedObjectList::_Meta;
igMetaField *__internalNonRefCountedObjectList::k_data;
igMetaField *__internalNonRefCountedObjectList::k_count;

void __internalObjectList::arkRegisterInitialize()
{
    igMetaObject *metaObject = _Meta;	// cache in a local variable

    {
        igMemoryRefMetaField *metaField = (igMemoryRefMetaField *)igMetaObject_FindFieldByName(metaObject, "_data");
        int metaIndex = ((__internalNonRefCountedObjectList *)metaObject->_metaFields)->find(metaField);
        metaField = (igMemoryRefMetaField *)((igObjectDispatchView *)metaField)->CloneViaMetadata(1);
        metaField->_refCounted = 1;
        metaField->_externalEnumStorage = (int)&k_data;
        igMetaObject_FinalizeAndReplaceField(metaObject, metaIndex, (::igMetaField *)metaField);
        metaField->release();
    }
}
}
}

