namespace Gap {
namespace Core {

igMetaObject *igUnsignedCharMetaField::_Meta;
igUnsignedCharMetaField *igUnsignedCharMetaField::_MetaField;
}
}

igMetaField *igUnsignedCharMetaField_Create(igMemoryPoolView *pool) {
    Gap::Core::igUnsignedCharMetaField::arkRegister();
    return (igMetaField *)igMetaObject_CreateInstance(Gap::Core::igUnsignedCharMetaField::getClassMeta(), pool);
}

namespace Gap {
namespace Core {

igMetaObject *igUnsignedCharMetaField::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igUnsignedCharMetaField::retrieveVTablePointer()
{
    igUnsignedCharMetaField temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igUnsignedCharMetaField::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igUnsignedCharMetaField::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { arkRegisterMetaValidate, 0 };

    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igMetaField::arkRegisterInternal,
        Gap::Core::igMetaField::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igUnsignedCharMetaField",
        sizeof(igUnsignedCharMetaField),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        regFunctions
    );
}


void igUnsignedCharMetaField::arkRegisterMetaValidate()
{
    igUnsignedCharMetaField *metaField;

    if (_MetaField == 0) {
        _MetaField = (igUnsignedCharMetaField *)igMetaObject_CreateInstance(_Meta, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
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

igUnsignedCharMetaField *igUnsignedCharMetaField::getMetaField()
{
    if (_MetaField == 0)
        arkRegister();
    return _MetaField;
}
}
}

