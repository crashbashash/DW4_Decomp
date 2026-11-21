namespace Gap {
namespace Math {

igMetaObject *igMatrix44fMetaField::_Meta;
igMatrix44fMetaField *igMatrix44fMetaField::_MetaField;

igMatrix44fMetaField *igMatrix44fMetaField::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igMatrix44fMetaField *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igMatrix44fMetaField::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igMatrix44fMetaField::retrieveVTablePointer()
{
    igMatrix44fMetaField temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igMatrix44fMetaField::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igMatrix44fMetaField::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { arkRegisterMetaValidate, 0 };

    FUN_00186a40();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igMetaField::arkRegisterInternal,
        Gap::Core::igMetaField::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igMatrix44fMetaField",
        sizeof(igMatrix44fMetaField),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        regFunctions
    );
}

void igMatrix44fMetaField::arkRegisterMetaValidate()
{
    igMatrix44fMetaField *metaField;

    if (_MetaField == 0) {
        _MetaField = (igMatrix44fMetaField *)igMetaObject_CreateInstance(_Meta, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
        metaField = _MetaField;
        if (metaField != 0) {
            MetaRefList_AppendRetained(getMetaFieldTypes(), (::igObject *)metaField);
            {
                ::igObject *held = (::igObject *)_MetaField;
                held->_refCount = (int)held->_refCount - 1;
                if (((unsigned long long) ((long long)(int)held->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(held);
                }
            }
            _MetaField->_internalIndex = (short)(getMetaFieldTypes()->_count - 1);
            _MetaField->validate();
        }
    }
}

igMatrix44fMetaField *igMatrix44fMetaField::getMetaField()
{
    if (_MetaField == 0)
        arkRegister();
    return _MetaField;
}
}
}

