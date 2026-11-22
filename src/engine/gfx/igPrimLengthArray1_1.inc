namespace Gap {
namespace Gfx {

igMetaObject *igPrimLengthArray1_1::_Meta;

igMetaObject *igPrimLengthArray1_1::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igPrimLengthArray1_1::retrieveVTablePointer()
{
    igPrimLengthArray1_1 temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igPrimLengthArray1_1::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igPrimLengthArray1_1::arkRegisterInternal()
{
    GfxLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Gfx::igPrimLengthArray::arkRegisterInternal,
        Gap::Gfx::igPrimLengthArray::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igPrimLengthArray1_1",
        sizeof(igPrimLengthArray1_1),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

igMetaField *igPrimLengthArray1_1::k_lengthData;

void igPrimLengthArray1_1::arkRegisterInitialize()
{
    igMetaObject *metaObject = _Meta;	// cache in a local variable

    {
        igMemoryRefMetaField *metaField = (igMemoryRefMetaField *)igMetaObject_FindFieldByName(metaObject, "_lengthData");
        int metaIndex = ((__internalNonRefCountedObjectList *)metaObject->_metaFields)->find(metaField);
        metaField = (igMemoryRefMetaField *)((igObjectDispatchView *)metaField)->CloneViaMetadata(1);
        metaField->_memType = (int)Gap::Core::igUnsignedIntMetaField::getMetaField();
        metaField->_memSize = 0;
        metaField->setDefault(0);
        metaField->_destruct = 1;
        metaField->_releaseOnCopy = 1;
        metaField->_releaseOnReset = 1;
        metaField->_externalEnumStorage = (int)&k_lengthData;
        igMetaObject_FinalizeAndReplaceField(metaObject, metaIndex, (::igMetaField *)metaField);
        metaField->release();
    }
}
}
}

