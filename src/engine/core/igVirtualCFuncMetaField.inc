namespace Gap {
namespace Core {

igMetaObject *igVirtualCFuncMetaField::_Meta;
igVirtualCFuncMetaField *igVirtualCFuncMetaField::_MetaField;

igMetaObject *igVirtualCFuncMetaField::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}
}
}

ObjectSystemView *g_objectSystem;

namespace Gap {
namespace Core {

void *igVirtualCFuncMetaField::retrieveVTablePointer()
{
    igVirtualCFuncMetaField temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igVirtualCFuncMetaField::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igVirtualCFuncMetaField::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { arkRegisterMetaValidate, 0 };

    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igMetaField::arkRegisterInternal,
        Gap::Core::igMetaField::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igVirtualCFuncMetaField",
        sizeof(igVirtualCFuncMetaField),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        regFunctions
    );
}

void igVirtualCFuncMetaField::arkRegisterMetaValidate()
{
    igVirtualCFuncMetaField *metaField;

    if (_MetaField == 0) {
        _MetaField = (igVirtualCFuncMetaField *)igMetaObject_CreateInstance(_Meta, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
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
}
}

