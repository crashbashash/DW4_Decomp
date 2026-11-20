namespace Gap {
namespace Core {

igMetaObject *igLongMetaField::_Meta;
igLongMetaField *igLongMetaField::_MetaField;
}
}

igMetaField *igLongMetaField_Create(igMemoryPoolView *pool) {
    Gap::Core::igLongMetaField::arkRegister();
    return (igMetaField *)igMetaObject_CreateInstance((igMetaObject *)Gap::Core::igLongMetaField::getClassMeta(), pool);
}

namespace Gap {
namespace Core {

igMetaObject *igLongMetaField::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igLongMetaField::retrieveVTablePointer()
{
    igLongMetaField temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igLongMetaField::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igLongMetaField::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { arkRegisterMetaValidate, 0 };

    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igMetaField::arkRegisterInternal,
        Gap::Core::igMetaField::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igLongMetaField",
        sizeof(igLongMetaField),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        regFunctions
    );
}


void igLongMetaField::arkRegisterMetaValidate()
{
    igLongMetaField *metaField;

    if (_MetaField == 0) {
        _MetaField = (igLongMetaField *)igMetaObject_CreateInstance(_Meta, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
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

igLongMetaField *igLongMetaField::getMetaField()
{
    if (_MetaField == 0)
        arkRegister();
    return _MetaField;
}
}
}

