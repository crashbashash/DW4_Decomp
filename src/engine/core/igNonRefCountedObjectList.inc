namespace Gap {
namespace Core {

igMetaObject *igNonRefCountedObjectList::_Meta;
igMetaField *igNonRefCountedObjectList::k_data;

igMetaObject *igNonRefCountedObjectList::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igNonRefCountedObjectList::retrieveVTablePointer()
{
    igNonRefCountedObjectList temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igNonRefCountedObjectList::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igNonRefCountedObjectList::arkRegisterInternal()
{
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igDataList::arkRegisterInternal,
        Gap::Core::igDataList::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igNonRefCountedObjectList",
        sizeof(igNonRefCountedObjectList),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void igNonRefCountedObjectList::arkRegisterInitialize()
{
    igMetaObject *metaObject = _Meta;	// cache in a local variable

    {
        igMemoryRefMetaField *metaField = (igMemoryRefMetaField *)igMetaObject_FindFieldByName(metaObject, "_data");
        int metaIndex = ObjectPointerList_FindIndex((__internalNonRefCountedObjectList *)metaObject->_metaFields, (int)metaField);
        metaField = (igMemoryRefMetaField *)((igObjectDispatchView *)metaField)->CloneViaMetadata(1);
        metaField->_memType = (int)Gap::Core::igObjectRefMetaField::getMetaField();
        metaField->_memSize = 0;
        metaField->_refCounted = 0;
        metaField->_externalEnumStorage = (int)&k_data;
        igMetaObject_FinalizeAndReplaceField(metaObject, metaIndex, (::igMetaField *)metaField);
        metaField->release();
    }
}
}
}

