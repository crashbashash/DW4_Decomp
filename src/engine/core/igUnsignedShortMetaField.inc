namespace Gap {
namespace Core {

igMetaObject *igUnsignedShortMetaField::_Meta;
igUnsignedShortMetaField *igUnsignedShortMetaField::_MetaField;
}
}

igMetaField *igUnsignedShortMetaField_Create(igMemoryPoolView *pool) {
    void **field;

    if (g_objectSystem->active != 0) {
        Gap::Core::igUnsignedShortMetaField::arkRegister();
        field = (void **)(((void **)igMetaObject_CreateInstance((igMetaObject *)Gap::Core::igUnsignedShortMetaField::getClassMeta(), pool)));
    } else {
        field = (void **)(((void **)igObject_AllocateRawStorage(0x34, 0, pool)));
        if (field != 0) {
            field = (void **)(((void **)igUnsignedShortMetaField_Construct((int **)field, 1)));
        }
        ((igObjectDispatchView *)(field))->InitDefaults();
        ((igObjectDispatchView *)(field))->userConstruct((int)(0));
    }
    return (igMetaField *)field;
}

namespace Gap {
namespace Core {

igObject *igUnsignedShortMetaField::cloneViaMetadata(int copyMode)
{
    if (g_objectSystem->active != 0) {
        arkRegister();
        return igObject::cloneViaMetadata(copyMode);
    }
    return new (igObject_AllocateRawStorageDefault(sizeof(igUnsignedShortMetaField), 0), 0) igUnsignedShortMetaField(*this);
}

igMetaObject *igUnsignedShortMetaField::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igUnsignedShortMetaField::retrieveVTablePointer()
{
    igUnsignedShortMetaField temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igUnsignedShortMetaField::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igUnsignedShortMetaField::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { arkRegisterMetaValidate, 0 };

    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igMetaField::arkRegisterInternal,
        Gap::Core::igMetaField::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igUnsignedShortMetaField",
        sizeof(igUnsignedShortMetaField),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        regFunctions
    );
}


void igUnsignedShortMetaField::arkRegisterMetaValidate()
{
    igUnsignedShortMetaField *metaField;

    if (_MetaField == 0) {
        _MetaField = (igUnsignedShortMetaField *)igMetaObject_CreateInstance(_Meta, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
        metaField = _MetaField;
        if (metaField != 0) {
            getMetaFieldTypes()->append(metaField);
            {
                ::igObject *held = (::igObject *)_MetaField;
                held->release();
            }
            _MetaField->_internalIndex = (short)(getMetaFieldTypes()->_count - 1);
            _MetaField->validate();
        }
    }
}

igUnsignedShortMetaField *igUnsignedShortMetaField::getMetaField()
{
    if (_MetaField == 0)
        arkRegister();
    return _MetaField;
}
}
}

