namespace Gap {
namespace Core {

igMetaObject *igCharMetaField::_Meta;
igCharMetaField *igCharMetaField::_MetaField;
}
}

igMetaField *igCharMetaField_Create(igMemoryPoolView *pool) {
    void **field;

    if (g_objectSystem->active != 0) {
        Gap::Core::igCharMetaField::arkRegister();
        field = (void **)(((void **)igMetaObject_CreateInstance((igMetaObject *)Gap::Core::igCharMetaField::getClassMeta(), pool)));
    } else {
        field = (void **)(((void **)igObject_AllocateRawStorage(0x34, 0, pool)));
        if (field != 0) {
            field = (void **)(((void **)igCharMetaField_Construct((int **)field, 1)));
        }
        ((igObjectDispatchView *)(field))->InitDefaults();
        ((igObjectDispatchView *)(field))->userConstruct((int)(0));
    }
    return (igMetaField *)field;
}

namespace Gap {
namespace Core {

igObject *igCharMetaField::cloneViaMetadata(int copyMode)
{
    if (g_objectSystem->active != 0) {
        arkRegister();
        return igObject::cloneViaMetadata(copyMode);
    }
    return new (igObject_AllocateRawStorageDefault(sizeof(igCharMetaField), 0), 0) igCharMetaField(*this);
}

igMetaObject *igCharMetaField::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igCharMetaField::retrieveVTablePointer()
{
    igCharMetaField temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igCharMetaField::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igCharMetaField::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { arkRegisterMetaValidate, 0 };

    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igMetaField::arkRegisterInternal,
        Gap::Core::igMetaField::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igCharMetaField",
        sizeof(igCharMetaField),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        regFunctions
    );
}


void igCharMetaField::arkRegisterMetaValidate()
{
    igCharMetaField *metaField;

    if (_MetaField == 0) {
        _MetaField = (igCharMetaField *)igMetaObject_CreateInstance(_Meta, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
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

igCharMetaField *igCharMetaField::getMetaField()
{
    if (_MetaField == 0)
        arkRegister();
    return _MetaField;
}
}
}

