namespace Gap {
namespace Core {

igMetaObject *igObjectRefMetaField::_Meta;
igObjectRefMetaField *igObjectRefMetaField::_MetaField;
igMetaField *igObjectRefMetaField::k_metaObject;
igMetaField *igObjectRefMetaField::k_refCounted;
igMetaField *igObjectRefMetaField::k_poolName;
}
}

/* Same factory shape for an igObjectRefMetaField (68-byte instance). */
igMetaField *igObjectRefMetaField_Create(igMemoryPoolView *pool) {
    void **field;

    if (g_objectSystem->active != 0) {
        Gap::Core::igObjectRefMetaField::arkRegister();
        field = ((void **)igMetaObject_CreateInstance((igMetaObject *)((int)Gap::Core::igObjectRefMetaField::getClassMeta()), pool));
    } else {
        field = ((void **)igObject_AllocateRawStorage(0x44, 0, pool));
        if (field != 0) {
            field = ((void **)igObjectRefMetaField_Construct((igObjectRefMetaField *)field, 1));
        }
        ((igObjectDispatchView *)field)->InitDefaults();
        ((igObjectDispatchView *)field)->userConstruct(0);
    }
    return (igMetaField *)field;
}

namespace Gap {
namespace Core {

igObject *igObjectRefMetaField::cloneViaMetadata(int copyMode)
{
    if (g_objectSystem->active != 0) {
        arkRegister();
        return igObject::cloneViaMetadata(copyMode);
    }
    return new (igObject_AllocateRawStorageDefault(sizeof(igObjectRefMetaField), 0), 0) igObjectRefMetaField(*this);
}

igMetaObject *igObjectRefMetaField::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igObjectRefMetaField::retrieveVTablePointer()
{
    igObjectRefMetaField temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igObjectRefMetaField::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igObjectRefMetaField::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { igMetaObject_EnsureRegistered, arkRegisterMetaValidate, 0 };

    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igRefMetaField::arkRegisterInternal,
        Gap::Core::igRefMetaField::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igObjectRefMetaField",
        sizeof(igObjectRefMetaField),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igObjectRefMetaField::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, igBoolMetaField_Create, igStringMetaField_Create };
    static const char *names[] = { "_metaObject", "_refCounted", "_poolName" };
    static igMetaField **enumStorage[] = { &k_metaObject, &k_refCounted, &k_poolName };
    static int offsets[] = { 56, 60, 64 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 3);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)igMetaObject_GetOrCreateMetaObject();
        metaField->_refCounted = 0;
        metaField->_deepCopyMethod = 1;
        metaField->_shallowCopyMethod = 1;
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->setDefault(1);
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}

void igObjectRefMetaField::arkRegisterMetaValidate()
{
    igObjectRefMetaField *metaField;

    if (_MetaField == 0) {
        _MetaField = (igObjectRefMetaField *)igMetaObject_CreateInstance(_Meta, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
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

igObjectRefMetaField *igObjectRefMetaField::getMetaField()
{
    if (_MetaField == 0)
        arkRegister();
    return _MetaField;
}
}
}

