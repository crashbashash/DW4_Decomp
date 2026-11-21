namespace Gap {
namespace Math {

igMetaObject *igVec4fArrayMetaField::_Meta;
igMetaField *igVec4fArrayMetaField::k_num;
igVec4fArrayMetaField *igVec4fArrayMetaField::_MetaField;

igVec4fArrayMetaField *igVec4fArrayMetaField::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igVec4fArrayMetaField *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igVec4fArrayMetaField::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igVec4fArrayMetaField::retrieveVTablePointer()
{
    igVec4fArrayMetaField temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igVec4fArrayMetaField::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igVec4fArrayMetaField::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { arkRegisterMetaValidate, 0 };

    FUN_00186a40();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Math::igVec4fMetaField::arkRegisterInternal,
        Gap::Math::igVec4fMetaField::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igVec4fArrayMetaField",
        sizeof(igVec4fArrayMetaField),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igVec4fArrayMetaField::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igIntMetaField_Create };
    static const char *names[] = { "_num" };
    static igMetaField **enumStorage[] = { &k_num };
    static int offsets[] = { 52 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 1);
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->setDefault(1);
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}

void igVec4fArrayMetaField::arkRegisterMetaValidate()
{
    igVec4fArrayMetaField *metaField;

    if (_MetaField == 0) {
        _MetaField = (igVec4fArrayMetaField *)igMetaObject_CreateInstance(_Meta, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
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
}
}

