namespace Gap {
namespace Core {

igMetaObject *igUnsignedLongMetaField::_Meta;
igUnsignedLongMetaField *igUnsignedLongMetaField::_MetaField;
}
}

igMetaField *igUnsignedLongMetaField_Create(igMemoryPoolView *pool) {
    void **field;

    if (g_objectSystem->active != 0) {
        Gap::Core::igUnsignedLongMetaField::arkRegister();
        field = (void **)(((void **)igMetaObject_CreateInstance((igMetaObject *)Gap::Core::igUnsignedLongMetaField::getClassMeta(), pool)));
    } else {
        field = (void **)(((void **)Gap::Core::igObject::operator new(0x34, 0, pool)));
        if (field != 0) {
            field = (void **)(((void **)igUnsignedLongMetaField_Construct((int **)field, 1)));
        }
        ((igObjectDispatchView *)(field))->InitDefaults();
        ((igObjectDispatchView *)(field))->userConstruct((int)(0));
    }
    return (igMetaField *)field;
}

namespace Gap {
namespace Core {

igObject *igUnsignedLongMetaField::cloneViaMetadata(int copyMode)
{
    if (g_objectSystem->active != 0) {
        arkRegister();
        return igObject::cloneViaMetadata(copyMode);
    }
    return new (0) igUnsignedLongMetaField(*this);
}

igMetaObject *igUnsignedLongMetaField::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igUnsignedLongMetaField::retrieveVTablePointer()
{
    igUnsignedLongMetaField temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igUnsignedLongMetaField::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igUnsignedLongMetaField::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { arkRegisterMetaValidate, 0 };

    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igMetaField::arkRegisterInternal,
        Gap::Core::igMetaField::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igUnsignedLongMetaField",
        sizeof(igUnsignedLongMetaField),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        regFunctions
    );
}


void igUnsignedLongMetaField::arkRegisterMetaValidate()
{
    igUnsignedLongMetaField *metaField;

    if (_MetaField == 0) {
        _MetaField = (igUnsignedLongMetaField *)igMetaObject_CreateInstance(_Meta, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
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

igUnsignedLongMetaField *igUnsignedLongMetaField::getMetaField()
{
    if (_MetaField == 0)
        arkRegister();
    return _MetaField;
}
}
}

