namespace Gap {
namespace Core {

igMetaObject *igIntMetaField::_Meta;
igIntMetaField *igIntMetaField::_MetaField;
}
}

/* Same factory shape for an igIntMetaField (52-byte instance). */
igMetaField *igIntMetaField_Create(igMemoryPoolView *pool) {
    void **field;

    if (g_objectSystem->active != 0) {
        Gap::Core::igIntMetaField::arkRegister();
        field = ((void **)igMetaObject_CreateInstance((igMetaObject *)((int)Gap::Core::igIntMetaField::getClassMeta()), pool));
    } else {
        field = ((void **)Gap::Core::igObject::operator new(0x34, 0, pool));
        if (field != 0) {
            field = ((void **)igIntMetaField_Construct((igMetaField *)field, 1));
        }
        ((igObjectDispatchView *)field)->InitDefaults();
        ((igObjectDispatchView *)field)->userConstruct(0);
    }
    return (igMetaField *)field;
}

namespace Gap {
namespace Core {

igObject *igIntMetaField::cloneViaMetadata(int copyMode)
{
    if (g_objectSystem->active != 0) {
        arkRegister();
        return igObject::cloneViaMetadata(copyMode);
    }
    return new (0) igIntMetaField(*this);
}

igMetaObject *igIntMetaField::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igIntMetaField::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igIntMetaField::retrieveVTablePointer()
{
    igIntMetaField temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igIntMetaField::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igIntMetaField::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { arkRegisterMetaValidate, 0 };

    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igMetaField::arkRegisterInternal,
        Gap::Core::igMetaField::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igIntMetaField",
        sizeof(igIntMetaField),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        regFunctions
    );
}

void igIntMetaField::arkRegisterMetaValidate()
{
    igIntMetaField *metaField;

    if (_MetaField == 0) {
        _MetaField = (igIntMetaField *)igMetaObject_CreateInstance(_Meta, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
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

igIntMetaField *igIntMetaField::getMetaField()
{
    if (_MetaField == 0)
        arkRegister();
    return _MetaField;
}
}
}
