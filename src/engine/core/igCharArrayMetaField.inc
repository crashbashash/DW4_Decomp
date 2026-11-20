namespace Gap {
namespace Core {

igMetaObject *igCharArrayMetaField::_Meta;
igCharArrayMetaField *igCharArrayMetaField::_MetaField;
igMetaField *igCharArrayMetaField::k_num;
}
}

igMetaField *igCharArrayMetaField_Create(igMemoryPoolView *pool) {
    Gap::Core::igCharArrayMetaField::arkRegister();
    return (igMetaField *)igMetaObject_CreateInstance(Gap::Core::igCharArrayMetaField::getClassMeta(), pool);
}

namespace Gap {
namespace Core {

igMetaObject *igCharArrayMetaField::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igCharArrayMetaField::retrieveVTablePointer()
{
    igCharArrayMetaField temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igCharArrayMetaField::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igCharArrayMetaField::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { arkRegisterMetaValidate, 0 };

    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igCharMetaField::arkRegisterInternal,
        Gap::Core::igCharMetaField::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igCharArrayMetaField",
        sizeof(igCharArrayMetaField),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igCharArrayMetaField::arkRegisterInitialize()
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

void igCharArrayMetaField::arkRegisterMetaValidate()
{
    igCharArrayMetaField *metaField;

    if (_MetaField == 0) {
        _MetaField = (igCharArrayMetaField *)igMetaObject_CreateInstance(_Meta, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
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
}
}

