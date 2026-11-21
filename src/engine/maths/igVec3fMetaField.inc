namespace Gap {
namespace Math {

igMetaObject *igVec3fMetaField::_Meta;
igVec3fMetaField *igVec3fMetaField::_MetaField;

igVec3fMetaField *igVec3fMetaField::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igVec3fMetaField *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igVec3fMetaField::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igVec3fMetaField::retrieveVTablePointer()
{
    igVec3fMetaField temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igVec3fMetaField::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igVec3fMetaField::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { arkRegisterMetaValidate, 0 };

    FUN_00186a40();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igMetaField::arkRegisterInternal,
        Gap::Core::igMetaField::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igVec3fMetaField",
        sizeof(igVec3fMetaField),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        regFunctions
    );
}

void igVec3fMetaField::arkRegisterMetaValidate()
{
    igVec3fMetaField *metaField;

    if (_MetaField == 0) {
        _MetaField = (igVec3fMetaField *)igMetaObject_CreateInstance(_Meta, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
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

igVec3fMetaField *igVec3fMetaField::getMetaField()
{
    if (_MetaField == 0)
        arkRegister();
    return _MetaField;
}
}
}

