namespace Gap {
namespace Math {

igMetaObject *igVec2fMetaField::_Meta;
igVec2fMetaField *igVec2fMetaField::_MetaField;

igVec2fMetaField *igVec2fMetaField::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igVec2fMetaField *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igVec2fMetaField::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igVec2fMetaField::retrieveVTablePointer()
{
    igVec2fMetaField temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igVec2fMetaField::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igVec2fMetaField::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { arkRegisterMetaValidate, 0 };

    FUN_00186a40();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igMetaField::arkRegisterInternal,
        Gap::Core::igMetaField::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igVec2fMetaField",
        sizeof(igVec2fMetaField),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        regFunctions
    );
}

void igVec2fMetaField::arkRegisterMetaValidate()
{
    igVec2fMetaField *metaField;

    if (_MetaField == 0) {
        _MetaField = (igVec2fMetaField *)igMetaObject_CreateInstance(_Meta, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
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

igVec2fMetaField *igVec2fMetaField::getMetaField()
{
    if (_MetaField == 0)
        arkRegister();
    return _MetaField;
}
}
}

