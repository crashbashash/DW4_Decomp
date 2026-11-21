namespace Gap {
namespace Core {

igMetaObject *igFloatMetaField::_Meta;
igFloatMetaField *igFloatMetaField::_MetaField;
}
}

igMetaField *igFloatMetaField_Create(igMemoryPoolView *pool) {
    Gap::Core::igFloatMetaField::arkRegister();
    return (igMetaField *)igMetaObject_CreateInstance(Gap::Core::igFloatMetaField::getClassMeta(), pool);
}

namespace Gap {
namespace Core {

igMetaObject *igFloatMetaField::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igFloatMetaField::retrieveVTablePointer()
{
    igFloatMetaField temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igFloatMetaField::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igFloatMetaField::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { arkRegisterMetaValidate, 0 };

    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igMetaField::arkRegisterInternal,
        Gap::Core::igMetaField::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igFloatMetaField",
        sizeof(igFloatMetaField),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        regFunctions
    );
}


void igFloatMetaField::arkRegisterMetaValidate()
{
    igFloatMetaField *metaField;

    if (_MetaField == 0) {
        _MetaField = (igFloatMetaField *)igMetaObject_CreateInstance(_Meta, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
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

igFloatMetaField *igFloatMetaField::getMetaField()
{
    if (_MetaField == 0)
        arkRegister();
    return _MetaField;
}
}
}

