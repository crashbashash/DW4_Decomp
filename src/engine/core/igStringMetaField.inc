namespace Gap {
namespace Core {

igMetaObject *igStringMetaField::_Meta;
igStringMetaField *igStringMetaField::_MetaField;
igMetaField *igStringMetaField::k_shallowCopyMethod;
igMetaField *igStringMetaField::k_destruct;
igMetaField *igStringMetaField::k_refCounted;
}
}

/* Factory for an igStringMetaField (60-byte instance). Once the object system is live, ensure the
 * class is registered and let its MetaObject create the instance with the given allocator. Before
 * that, allocate by hand, construct in place (second argument 1 is the flag retail passes) and run
 * the post-construction hooks, vfunc_09 then vfunc_07(0). */
igMetaField *igStringMetaField_Create(igMemoryPoolView *pool) {
    void **field;

    if (g_objectSystem->active != 0) {
        Gap::Core::igStringMetaField::arkRegister();
        field = ((void **)igMetaObject_CreateInstance((igMetaObject *)((int)Gap::Core::igStringMetaField::getClassMeta()), pool));
    } else {
        field = ((void **)igObject_AllocateRawStorage(0x3C, 0, pool));
        if (field != 0) {
            field = ((void **)igStringMetaField_Construct((igStringMetaField *)field, 1));
        }
        ((igObjectDispatchView *)field)->InitDefaults();
        ((igObjectDispatchView *)field)->userConstruct(0);
    }
    return (igMetaField *)field;
}

namespace Gap {
namespace Core {

igObject *igStringMetaField::cloneViaMetadata(int copyMode)
{
    if (g_objectSystem->active != 0) {
        arkRegister();
        return igObject::cloneViaMetadata(copyMode);
    }
    return new (igObject_AllocateRawStorageDefault(sizeof(igStringMetaField), 0), 0) igStringMetaField(*this);
}

igMetaObject *igStringMetaField::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igStringMetaField::retrieveVTablePointer()
{
    igStringMetaField temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igStringMetaField::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igStringMetaField::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { arkRegisterMetaValidate, 0 };

    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igRefMetaField::arkRegisterInternal,
        Gap::Core::igRefMetaField::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igStringMetaField",
        sizeof(igStringMetaField),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

igMetaObject *igRefMetaField::_Meta;
igRefMetaField *igRefMetaField::_MetaField;
igMetaField *igRefMetaField::k_construct;
igMetaField *igRefMetaField::k_destruct;

void igStringMetaField::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igBoolMetaField_Create };
    static const char *names[] = { "_refCounted" };
    static igMetaField **enumStorage[] = { &k_refCounted };
    static int offsets[] = { 56 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 1);
    {
        igCharMetaField *metaField = (igCharMetaField *)igMetaObject_FindFieldByName(metaObject, "_shallowCopyMethod");
        int metaIndex = ObjectPointerList_FindIndex((__internalNonRefCountedObjectList *)metaObject->_metaFields, (int)metaField);
        metaField = (igCharMetaField *)((igObjectDispatchView *)metaField)->CloneViaMetadata(1);
        metaField->setDefault(2);
        metaField->_externalEnumStorage = (int)&k_shallowCopyMethod;
        igMetaObject_FinalizeAndReplaceField(metaObject, metaIndex, (::igMetaField *)metaField);
        metaField->_refCount = metaField->_refCount - 1;
        if (((unsigned long long)(long long)metaField->_refCount & 0x7fffffULL) == 0) {
            igObject_Destroy((::igObject *)metaField);
        }
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_FindFieldByName(metaObject, "_destruct");
        int metaIndex = ObjectPointerList_FindIndex((__internalNonRefCountedObjectList *)metaObject->_metaFields, (int)metaField);
        metaField = (igBoolMetaField *)((igObjectDispatchView *)metaField)->CloneViaMetadata(1);
        metaField->setDefault(1);
        metaField->_externalEnumStorage = (int)&k_destruct;
        igMetaObject_FinalizeAndReplaceField(metaObject, metaIndex, (::igMetaField *)metaField);
        metaField->_refCount = metaField->_refCount - 1;
        if (((unsigned long long)(long long)metaField->_refCount & 0x7fffffULL) == 0) {
            igObject_Destroy((::igObject *)metaField);
        }
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->setDefault(1);
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}

void igStringMetaField::arkRegisterMetaValidate()
{
    igStringMetaField *metaField;

    if (_MetaField == 0) {
        _MetaField = (igStringMetaField *)igMetaObject_CreateInstance(_Meta, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
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

igStringMetaField *igStringMetaField::getMetaField()
{
    if (_MetaField == 0)
        arkRegister();
    return _MetaField;
}
}
}

