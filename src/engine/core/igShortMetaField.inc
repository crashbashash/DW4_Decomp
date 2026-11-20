namespace Gap {
namespace Core {

igMetaObject *igShortMetaField::_Meta;
igShortMetaField *igShortMetaField::_MetaField;
}
}

igMetaField *igShortMetaField_Create(igMemoryPoolView *pool) {
    void **instance;

    if (g_objectSystem->active != 0) {
        Gap::Core::igShortMetaField::arkRegister();
        instance = (void **)(((void **)igMetaObject_CreateInstance((igMetaObject *)Gap::Core::igShortMetaField::getClassMeta(), pool)));
    } else {
        instance = (void **)(((void **)igObject_AllocateRawStorage(0x34, 0, pool)));
        if (instance != 0) {
            instance = (void **)(((void **)igShortMetaField_Construct((int **)instance, 1)));
        }
        ((igObjectDispatchView *)(instance))->InitDefaults();
        ((igObjectDispatchView *)(instance))->userConstruct((int)(0));
    }
    return (igMetaField *)instance;
}

namespace Gap {
namespace Core {

igObject *igShortMetaField::cloneViaMetadata(int copyMode)
{
    if (g_objectSystem->active != 0) {
        arkRegister();
        return igObject::cloneViaMetadata(copyMode);
    }
    return new (igObject_AllocateRawStorageDefault(sizeof(igShortMetaField), 0), 0) igShortMetaField(*this);
}

igMetaObject *igShortMetaField::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igShortMetaField::retrieveVTablePointer()
{
    igShortMetaField temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igShortMetaField::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igShortMetaField::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { arkRegisterMetaValidate, 0 };

    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igMetaField::arkRegisterInternal,
        Gap::Core::igMetaField::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igShortMetaField",
        sizeof(igShortMetaField),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        regFunctions
    );
}


void igShortMetaField::arkRegisterMetaValidate()
{
    igShortMetaField *metaField;

    if (_MetaField == 0) {
        _MetaField = (igShortMetaField *)igMetaObject_CreateInstance(_Meta, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
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

igShortMetaField *igShortMetaField::getMetaField()
{
    if (_MetaField == 0)
        arkRegister();
    return _MetaField;
}
}
}

