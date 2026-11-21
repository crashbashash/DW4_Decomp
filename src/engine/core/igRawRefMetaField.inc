namespace Gap {
namespace Core {

igMetaObject *igRawRefMetaField::_Meta;
igRawRefMetaField *igRawRefMetaField::_MetaField;
}
}

igMetaField *igRawRefMetaField_Create(igMemoryPoolView *pool) {
    void **field;

    if (g_objectSystem->active != 0) {
        Gap::Core::igRawRefMetaField::arkRegister();
        field = (void **)(((void **)igMetaObject_CreateInstance((igMetaObject *)Gap::Core::igRawRefMetaField::getClassMeta(), pool)));
    } else {
        field = (void **)(((void **)igObject_AllocateRawStorage(0x38, 0, pool)));
        if (field != 0) {
            field = (void **)(((void **)igRawRefMetaField_Construct((int **)field, 1)));
        }
        ((igObjectDispatchView *)(field))->InitDefaults();
        ((igObjectDispatchView *)(field))->userConstruct((int)(0));
    }
    return (igMetaField *)field;
}

namespace Gap {
namespace Core {

igObject *igRawRefMetaField::cloneViaMetadata(int copyMode)
{
    if (g_objectSystem->active != 0) {
        arkRegister();
        return igObject::cloneViaMetadata(copyMode);
    }
    return new (igObject_AllocateRawStorageDefault(sizeof(igRawRefMetaField), 0), 0) igRawRefMetaField(*this);
}

igMetaObject *igRawRefMetaField::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igRawRefMetaField::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igRawRefMetaField::retrieveVTablePointer()
{
    igRawRefMetaField temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igRawRefMetaField::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igRawRefMetaField::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { arkRegisterMetaValidate, 0 };

    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igRefMetaField::arkRegisterInternal,
        Gap::Core::igRefMetaField::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igRawRefMetaField",
        sizeof(igRawRefMetaField),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        regFunctions
    );
}

void igRawRefMetaField::arkRegisterMetaValidate()
{
    igRawRefMetaField *metaField;

    if (_MetaField == 0) {
        _MetaField = (igRawRefMetaField *)igMetaObject_CreateInstance(_Meta, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
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

igRawRefMetaField *igRawRefMetaField::getMetaField()
{
    if (_MetaField == 0)
        arkRegister();
    return _MetaField;
}
}
}

