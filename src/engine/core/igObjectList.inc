namespace Gap {
namespace Core {

igMetaObject *igObjectList::_Meta;
igMetaField *igObjectList::k_data;

igObjectList *igObjectList::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igObjectList *)igMetaObject_CreateInstance(_Meta, pool);
}

/* Created with allocation only, no field registration, when missing. */
igMetaObject *igObjectList::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igObjectList::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igObjectList::retrieveVTablePointer()
{
    igObjectList temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igObjectList::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igObjectList::arkRegisterInternal()
{
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igDataList::arkRegisterInternal,
        Gap::Core::igDataList::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igObjectList",
        sizeof(igObjectList),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void igObjectList::arkRegisterInitialize()
{
    igMetaObject *metaObject = _Meta;	// cache in a local variable

    {
        igMemoryRefMetaField *metaField = (igMemoryRefMetaField *)igMetaObject_FindFieldByName(metaObject, "_data");
        int metaIndex = ObjectPointerList_FindIndex((__internalNonRefCountedObjectList *)metaObject->_metaFields, (int)metaField);
        metaField = (igMemoryRefMetaField *)((igObjectDispatchView *)metaField)->CloneViaMetadata(1);
        metaField->_memType = (int)Gap::Core::igObjectRefMetaField::getMetaField();
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

