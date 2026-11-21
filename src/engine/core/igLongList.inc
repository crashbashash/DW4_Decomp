namespace Gap {
namespace Core {

igMetaObject *igLongList::_Meta;
igMetaField *igLongList::k_data;

igMetaObject *igLongList::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igLongList::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igLongList::retrieveVTablePointer()
{
    igLongList temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igLongList::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igLongList::arkRegisterInternal()
{
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igDataList::arkRegisterInternal,
        Gap::Core::igDataList::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igLongList",
        sizeof(igLongList),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void igLongList::arkRegisterInitialize()
{
    igMetaObject *metaObject = _Meta;	// cache in a local variable

    {
        igMemoryRefMetaField *metaField = (igMemoryRefMetaField *)igMetaObject_FindFieldByName(metaObject, "_data");
        int metaIndex = ObjectPointerList_FindIndex((__internalNonRefCountedObjectList *)metaObject->_metaFields, (int)metaField);
        metaField = (igMemoryRefMetaField *)((igObjectDispatchView *)metaField)->CloneViaMetadata(1);
        metaField->_memType = (int)Gap::Core::igLongMetaField::getMetaField();
        metaField->_memSize = 0;
        metaField->_externalEnumStorage = (int)&k_data;
        igMetaObject_FinalizeAndReplaceField(metaObject, metaIndex, (::igMetaField *)metaField);
        metaField->release();
    }
}
}
}

