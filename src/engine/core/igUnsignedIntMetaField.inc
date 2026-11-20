namespace Gap {
namespace Core {

igMetaObject *igUnsignedIntMetaField::_Meta;
igUnsignedIntMetaField *igUnsignedIntMetaField::_MetaField;
}
}

igMetaField *igUnsignedIntMetaField_Create(igMemoryPoolView *pool) {
    void **field;

    if (g_objectSystem->active != 0) {
        Gap::Core::igUnsignedIntMetaField::arkRegister();
        field = (void **)(((void **)igMetaObject_CreateInstance((igMetaObject *)((int)Gap::Core::igUnsignedIntMetaField::getClassMeta()), pool)));
    } else {
        field = (void **)(((void **)igObject_AllocateRawStorage(0x34, 0, pool)));
        if (field != 0) {
            field = (void **)(((void **)igUnsignedIntMetaField_Construct((igMetaField *)field, 1)));
        }
        ((igObjectDispatchView *)(field))->InitDefaults();
        ((igObjectDispatchView *)(field))->userConstruct((int)(0));
    }
    return (igMetaField *)field;
}

namespace Gap {
namespace Core {

igObject *igUnsignedIntMetaField::cloneViaMetadata(int copyMode)
{
    if (g_objectSystem->active != 0) {
        arkRegister();
        return igObject::cloneViaMetadata(copyMode);
    }
    return new (igObject_AllocateRawStorageDefault(sizeof(igUnsignedIntMetaField), 0), 0) igUnsignedIntMetaField(*this);
}

igMetaObject *igUnsignedIntMetaField::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igUnsignedIntMetaField::retrieveVTablePointer()
{
    igUnsignedIntMetaField temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igUnsignedIntMetaField::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igUnsignedIntMetaField::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { arkRegisterMetaValidate, 0 };

    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igMetaField::arkRegisterInternal,
        Gap::Core::igMetaField::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igUnsignedIntMetaField",
        sizeof(igUnsignedIntMetaField),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        regFunctions
    );
}


void igUnsignedIntMetaField::arkRegisterMetaValidate()
{
    igUnsignedIntMetaField *metaField;

    if (_MetaField == 0) {
        _MetaField = (igUnsignedIntMetaField *)igMetaObject_CreateInstance(_Meta, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
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

igUnsignedIntMetaField *igUnsignedIntMetaField::getMetaField()
{
    if (_MetaField == 0)
        arkRegister();
    return _MetaField;
}
}
}

