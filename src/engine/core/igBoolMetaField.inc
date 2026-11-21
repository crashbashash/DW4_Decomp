namespace Gap {
namespace Core {

igMetaObject *igBoolMetaField::_Meta;
igBoolMetaField *igBoolMetaField::_MetaField;
}
}

igMetaField *igBoolMetaField_Create(igMemoryPoolView *pool) {
    void **instance;

    if (g_objectSystem->active != 0) {
        Gap::Core::igBoolMetaField::arkRegister();
        instance = (void **)(((void **)igMetaObject_CreateInstance((igMetaObject *)Gap::Core::igBoolMetaField::getClassMeta(), pool)));
    } else {
        instance = (void **)(((void **)igObject_AllocateRawStorage(0x34, 0, pool)));
        if (instance != 0) {
            instance = (void **)(((void **)igBoolMetaField_Construct((int **)instance, 1)));
        }
        ((igObjectDispatchView *)(instance))->InitDefaults();
        ((igObjectDispatchView *)(instance))->userConstruct((int)(0));
    }
    return (igMetaField *)instance;
}

namespace Gap {
namespace Core {

igObject *igBoolMetaField::cloneViaMetadata(int copyMode)
{
    if (g_objectSystem->active != 0) {
        arkRegister();
        return igObject::cloneViaMetadata(copyMode);
    }
    return new (igObject_AllocateRawStorageDefault(sizeof(igBoolMetaField), 0), 0) igBoolMetaField(*this);
}

igMetaObject *igBoolMetaField::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igBoolMetaField::retrieveVTablePointer()
{
    igBoolMetaField temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igBoolMetaField::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igBoolMetaField::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { arkRegisterMetaValidate, 0 };

    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igMetaField::arkRegisterInternal,
        Gap::Core::igMetaField::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igBoolMetaField",
        sizeof(igBoolMetaField),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        regFunctions
    );
}


void igBoolMetaField::arkRegisterMetaValidate()
{
    igBoolMetaField *metaField;

    if (_MetaField == 0) {
        _MetaField = (igBoolMetaField *)igMetaObject_CreateInstance(_Meta, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
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

igBoolMetaField *igBoolMetaField::getMetaField()
{
    if (_MetaField == 0)
        arkRegister();
    return _MetaField;
}
}
}

