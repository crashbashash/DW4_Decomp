namespace Gap {
namespace Core {

igMetaObject *igFloatArrayMetaField::_Meta;
igFloatArrayMetaField *igFloatArrayMetaField::_MetaField;
igMetaField *igFloatArrayMetaField::k_num;

igMetaEnum *igFile::ReadMode_Meta;
igMetaEnum *igFile::OpenMode_Meta;
}
}

igMetaField *igFloatArrayMetaField_Create(igMemoryPoolView *pool) {
    Gap::Core::igFloatArrayMetaField::arkRegister();
    return (igMetaField *)igMetaObject_CreateInstance(Gap::Core::igFloatArrayMetaField::getClassMeta(), pool);
}

namespace Gap {
namespace Core {

igMetaObject *igFloatArrayMetaField::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igFloatArrayMetaField::retrieveVTablePointer()
{
    igFloatArrayMetaField temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igFloatArrayMetaField::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igFloatArrayMetaField::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { arkRegisterMetaValidate, 0 };

    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igFloatMetaField::arkRegisterInternal,
        Gap::Core::igFloatMetaField::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igFloatArrayMetaField",
        sizeof(igFloatArrayMetaField),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igFloatArrayMetaField::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igIntMetaField_Create };
    static const char *names[] = { "_num" };
    static igMetaField **enumStorage[] = { &k_num };
    static int offsets[] = { 52 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 1);
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->setDefault(1);
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}

void igFloatArrayMetaField::arkRegisterMetaValidate()
{
    igFloatArrayMetaField *metaField;

    if (_MetaField == 0) {
        _MetaField = (igFloatArrayMetaField *)igMetaObject_CreateInstance(_Meta, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
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

