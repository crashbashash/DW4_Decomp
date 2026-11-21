namespace Gap {
namespace Math {

igMetaObject *igVec4fMetaField::_Meta;
igVec4fMetaField *igVec4fMetaField::_MetaField;

igVec4fMetaField *igVec4fMetaField::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igVec4fMetaField *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igVec4fMetaField::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igVec4fMetaField::retrieveVTablePointer()
{
    igVec4fMetaField temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igVec4fMetaField::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igVec4fMetaField::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { arkRegisterMetaValidate, 0 };

    FUN_00186a40();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igMetaField::arkRegisterInternal,
        Gap::Core::igMetaField::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igVec4fMetaField",
        sizeof(igVec4fMetaField),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        regFunctions
    );
}

void igVec4fMetaField::arkRegisterMetaValidate()
{
    igVec4fMetaField *metaField;

    if (_MetaField == 0) {
        _MetaField = (igVec4fMetaField *)igMetaObject_CreateInstance(_Meta, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
        metaField = _MetaField;
        if (metaField != 0) {
            MetaRefList_AppendRetained(getMetaFieldTypes(), (::igObject *)metaField);
            {
                ::igObject *held = (::igObject *)_MetaField;
                held->release();
            }
            _MetaField->_internalIndex = (short)(getMetaFieldTypes()->_count - 1);
            _MetaField->validate();
        }
    }
}

igVec4fMetaField *igVec4fMetaField::getMetaField()
{
    if (_MetaField == 0)
        arkRegister();
    return _MetaField;
}
}
}

