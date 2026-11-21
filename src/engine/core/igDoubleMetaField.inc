namespace Gap {
namespace Core {

igMetaObject *igDoubleMetaField::_Meta;
igDoubleMetaField *igDoubleMetaField::_MetaField;
}
}

igMetaField *igDoubleMetaField_Create(igMemoryPoolView *pool) {
    Gap::Core::igDoubleMetaField::arkRegister();
    return (igMetaField *)igMetaObject_CreateInstance(Gap::Core::igDoubleMetaField::getClassMeta(), pool);
}

namespace Gap {
namespace Core {

igMetaObject *igDoubleMetaField::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igDoubleMetaField::retrieveVTablePointer()
{
    igDoubleMetaField temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igDoubleMetaField::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igDoubleMetaField::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { arkRegisterMetaValidate, 0 };

    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igMetaField::arkRegisterInternal,
        Gap::Core::igMetaField::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igDoubleMetaField",
        sizeof(igDoubleMetaField),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        regFunctions
    );
}


void igDoubleMetaField::arkRegisterMetaValidate()
{
    igDoubleMetaField *metaField;

    if (_MetaField == 0) {
        _MetaField = (igDoubleMetaField *)igMetaObject_CreateInstance(_Meta, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
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

igDoubleMetaField *igDoubleMetaField::getMetaField()
{
    if (_MetaField == 0)
        arkRegister();
    return _MetaField;
}
}
}

