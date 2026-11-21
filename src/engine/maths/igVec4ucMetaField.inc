namespace Gap {
namespace Math {

igMetaObject *igVec4ucMetaField::_Meta;
igVec4ucMetaField *igVec4ucMetaField::_MetaField;

igMetaObject *igVec4ucMetaField::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igVec4ucMetaField::retrieveVTablePointer()
{
    igVec4ucMetaField temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igVec4ucMetaField::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igVec4ucMetaField::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { arkRegisterMetaValidate, 0 };

    FUN_00186a40();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igMetaField::arkRegisterInternal,
        Gap::Core::igMetaField::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igVec4ucMetaField",
        sizeof(igVec4ucMetaField),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        regFunctions
    );
}

void igVec4ucMetaField::arkRegisterMetaValidate()
{
    igVec4ucMetaField *metaField;

    if (_MetaField == 0) {
        _MetaField = (igVec4ucMetaField *)igMetaObject_CreateInstance(_Meta, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
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

igVec4ucMetaField *igVec4ucMetaField::getMetaField()
{
    if (_MetaField == 0)
        arkRegister();
    return _MetaField;
}
}
}

