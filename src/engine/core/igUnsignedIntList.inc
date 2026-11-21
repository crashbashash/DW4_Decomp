namespace Gap {
namespace Core {

igMetaObject *igUnsignedIntList::_Meta;
igMetaField *igUnsignedIntList::k_data;
}
}

void igUnsignedIntList_Create(int pool) {
    Gap::Core::igUnsignedIntList::arkRegister();
    igMetaObject_CreateInstance(Gap::Core::igUnsignedIntList::getClassMeta(), (igMemoryPoolView *)pool);
}

namespace Gap {
namespace Core {

igMetaObject *igUnsignedIntList::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igUnsignedIntList::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igUnsignedIntList::retrieveVTablePointer()
{
    igUnsignedIntList temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igUnsignedIntList::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igUnsignedIntList::arkRegisterInternal()
{
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igDataList::arkRegisterInternal,
        Gap::Core::igDataList::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igUnsignedIntList",
        sizeof(igUnsignedIntList),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void igUnsignedIntList::arkRegisterInitialize()
{
    igMetaObject *metaObject = _Meta;	// cache in a local variable

    {
        igMemoryRefMetaField *metaField = (igMemoryRefMetaField *)igMetaObject_FindFieldByName(metaObject, "_data");
        int metaIndex = ObjectPointerList_FindIndex((__internalNonRefCountedObjectList *)metaObject->_metaFields, (int)metaField);
        metaField = (igMemoryRefMetaField *)((igObjectDispatchView *)metaField)->CloneViaMetadata(1);
        metaField->_memType = (int)Gap::Core::igUnsignedIntMetaField::getMetaField();
        metaField->_memSize = 0;
        metaField->_externalEnumStorage = (int)&k_data;
        igMetaObject_FinalizeAndReplaceField(metaObject, metaIndex, (::igMetaField *)metaField);
        metaField->release();
    }
}
}
}

