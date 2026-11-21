namespace Gap {
namespace Core {

igMetaObject *igEnumMetaField::_Meta;
igEnumMetaField *igEnumMetaField::_MetaField;
igMetaField *igEnumMetaField::k_getMetaEnumFunction;
}
}

igMetaField *igEnumMetaField_Create(igMemoryPoolView *pool) {
    void **field;

    if (g_objectSystem->active != 0) {
        Gap::Core::igEnumMetaField::arkRegister();
        field = (void **)(((void **)igMetaObject_CreateInstance((igMetaObject *)Gap::Core::igEnumMetaField::getClassMeta(), pool)));
    } else {
        field = (void **)(((void **)igObject_AllocateRawStorage(0x38, 0, pool)));
        if (field != 0) {
            field = (void **)(((void **)igEnumMetaField_Construct((int **)field, 1)));
        }
        ((igObjectDispatchView *)(field))->InitDefaults();
        ((igObjectDispatchView *)(field))->userConstruct((int)(0));
    }
    return (igMetaField *)field;
}

namespace Gap {
namespace Core {

igObject *igEnumMetaField::cloneViaMetadata(int copyMode)
{
    if (g_objectSystem->active != 0) {
        arkRegister();
        return igObject::cloneViaMetadata(copyMode);
    }
    return new (igObject_AllocateRawStorageDefault(sizeof(igEnumMetaField), 0), 0) igEnumMetaField(*this);
}

igMetaObject *igEnumMetaField::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igEnumMetaField::retrieveVTablePointer()
{
    igEnumMetaField temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igEnumMetaField::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igEnumMetaField::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { arkRegisterMetaValidate, 0 };

    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igMetaField::arkRegisterInternal,
        Gap::Core::igMetaField::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igEnumMetaField",
        sizeof(igEnumMetaField),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igEnumMetaField::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igRawRefMetaField_Create };
    static const char *names[] = { "_getMetaEnumFunction" };
    static igMetaField **enumStorage[] = { &k_getMetaEnumFunction };
    static int offsets[] = { 52 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 1);
    {
        igRawRefMetaField *metaField = (igRawRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_persistent = 0;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}

void igEnumMetaField::arkRegisterMetaValidate()
{
    igEnumMetaField *metaField;

    if (_MetaField == 0) {
        _MetaField = (igEnumMetaField *)igMetaObject_CreateInstance(_Meta, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
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

igEnumMetaField *igEnumMetaField::getMetaField()
{
    if (_MetaField == 0)
        arkRegister();
    return _MetaField;
}
}
}

