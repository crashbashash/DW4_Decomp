namespace Gap {
namespace Core {

igMetaObject *igDependencyList::_Meta;
igMetaField *igDependencyList::k_data;

igMetaObject *igDependencyList::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igDependencyList::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igDependencyList::retrieveVTablePointer()
{
    igDependencyList temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igDependencyList::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igDependencyList::arkRegisterInternal()
{
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igDataList::arkRegisterInternal,
        Gap::Core::igDataList::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igDependencyList",
        sizeof(igDependencyList),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void igDependencyList::arkRegisterInitialize()
{
    igMetaObject *metaObject = _Meta;	// cache in a local variable

    {
        igMemoryRefMetaField *metaField = (igMemoryRefMetaField *)igMetaObject_FindFieldByName(metaObject, "_data");
        int metaIndex = ObjectPointerList_FindIndex((__internalNonRefCountedObjectList *)metaObject->_metaFields, (int)metaField);
        metaField = (igMemoryRefMetaField *)((igObjectDispatchView *)metaField)->CloneViaMetadata(1);
        metaField->_memType = igDependencyMetaField_GetDefaultDescriptor();
        metaField->_memSize = 0;
        metaField->_externalEnumStorage = (int)&k_data;
        igMetaObject_FinalizeAndReplaceField(metaObject, metaIndex, (::igMetaField *)metaField);
        metaField->release();
    }
}
}
}

