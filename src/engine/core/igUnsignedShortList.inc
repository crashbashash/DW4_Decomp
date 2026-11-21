namespace Gap {
namespace Core {

igMetaObject *igUnsignedShortList::_Meta;
igMetaField *igUnsignedShortList::k_data;
}
}

igUnsignedShortList *igUnsignedShortList_Create(int pool) {
    Gap::Core::igUnsignedShortList::arkRegister();
    return (igUnsignedShortList *)igMetaObject_CreateInstance(Gap::Core::igUnsignedShortList::getClassMeta(), (igMemoryPoolView *)pool);
}

namespace Gap {
namespace Core {

igMetaObject *igUnsignedShortList::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igUnsignedShortList::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igUnsignedShortList::retrieveVTablePointer()
{
    igUnsignedShortList temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igUnsignedShortList::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igUnsignedShortList::arkRegisterInternal()
{
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igDataList::arkRegisterInternal,
        Gap::Core::igDataList::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igUnsignedShortList",
        sizeof(igUnsignedShortList),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void igUnsignedShortList::arkRegisterInitialize()
{
    igMetaObject *metaObject = _Meta;	// cache in a local variable

    {
        igMemoryRefMetaField *metaField = (igMemoryRefMetaField *)igMetaObject_FindFieldByName(metaObject, "_data");
        int metaIndex = ObjectPointerList_FindIndex((__internalNonRefCountedObjectList *)metaObject->_metaFields, (int)metaField);
        metaField = (igMemoryRefMetaField *)((igObjectDispatchView *)metaField)->CloneViaMetadata(1);
        metaField->_memType = (int)Gap::Core::igUnsignedShortMetaField::getMetaField();
        metaField->_memSize = 0;
        metaField->_externalEnumStorage = (int)&k_data;
        igMetaObject_FinalizeAndReplaceField(metaObject, metaIndex, (::igMetaField *)metaField);
        metaField->_refCount = metaField->_refCount - 1;
        if (((unsigned long long)(long long)metaField->_refCount & 0x7fffffULL) == 0) {
            igObject_Destroy((::igObject *)metaField);
        }
    }
}
}
}

