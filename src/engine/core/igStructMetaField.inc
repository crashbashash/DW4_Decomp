namespace Gap {
namespace Core {

igMetaObject *igStructMetaField::_Meta;
igStructMetaField *igStructMetaField::_MetaField;
igUnsignedShortMetaField *igStructMetaField::k_size;
igMetaField *igStructMetaField::k_alignment;
igMetaField *igStructMetaField::k_cppConstructor;
igMetaField *igStructMetaField::k_cppDestructor;
}
}

igMetaField *igStructMetaField_Create(igMemoryPoolView *pool) {
    Gap::Core::igStructMetaField::arkRegister();
    return (igMetaField *)igMetaObject_CreateInstance(Gap::Core::igStructMetaField::getClassMeta(), pool);
}

namespace Gap {
namespace Core {

igMetaObject *igStructMetaField::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igStructMetaField::retrieveVTablePointer()
{
    igStructMetaField temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igStructMetaField::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igStructMetaField::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { arkRegisterMetaValidate, 0 };

    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igMetaField::arkRegisterInternal,
        Gap::Core::igMetaField::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igStructMetaField",
        sizeof(igStructMetaField),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}
}
}

static inline void releaseField(igMetaField *f) {
    f->release();
}

namespace Gap {
namespace Core {

void igStructMetaField::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igIntMetaField_Create, igRawRefMetaField_Create, igRawRefMetaField_Create };
    static const char *names[] = { "_alignment", "_cppConstructor", "_cppDestructor" };
    static igMetaField **enumStorage[] = { &k_alignment, &k_cppConstructor, &k_cppDestructor };
    static int offsets[] = { 52, 56, 60 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 3);
    {
        igUnsignedShortMetaField *metaField = (igUnsignedShortMetaField *)igMetaObject_FindFieldByName(metaObject, "_size");
        int metaIndex = ObjectPointerList_FindIndex((__internalNonRefCountedObjectList *)metaObject->_metaFields, (int)metaField);
        metaField = (igUnsignedShortMetaField *)((igObjectDispatchView *)metaField)->CloneViaMetadata(1);
        metaField->setDefault(1);
        metaField->_persistent = 0;
        metaField->_externalEnumStorage = (int)&k_size;
        igMetaObject_FinalizeAndReplaceField(metaObject, metaIndex, (::igMetaField *)metaField);
        metaField->release();
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->setDefault(1);
        metaField->_persistent = 0;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}

void igStructMetaField::arkRegisterMetaValidate()
{
    igStructMetaField *metaField;

    if (_MetaField == 0) {
        _MetaField = (igStructMetaField *)igMetaObject_CreateInstance(_Meta, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
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
}
}

