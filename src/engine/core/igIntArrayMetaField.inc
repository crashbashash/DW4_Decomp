namespace Gap {
namespace Core {

igMetaObject *igIntArrayMetaField::_Meta;
igIntArrayMetaField *igIntArrayMetaField::_MetaField;
igMetaField *igIntArrayMetaField::k_num;
}
}

igMetaField *igIntArrayMetaField_Create(igMemoryPoolView *pool) {
    Gap::Core::igIntArrayMetaField::arkRegister();
    return (igMetaField *)igMetaObject_CreateInstance(Gap::Core::igIntArrayMetaField::getClassMeta(), pool);
}

namespace Gap {
namespace Core {

igMetaObject *igIntArrayMetaField::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igIntArrayMetaField::retrieveVTablePointer()
{
    igIntArrayMetaField temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igIntArrayMetaField::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igIntArrayMetaField::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { arkRegisterMetaValidate, 0 };

    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igIntMetaField::arkRegisterInternal,
        Gap::Core::igIntMetaField::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igIntArrayMetaField",
        sizeof(igIntArrayMetaField),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igIntArrayMetaField::arkRegisterInitialize()
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

void igIntArrayMetaField::arkRegisterMetaValidate()
{
    igIntArrayMetaField *metaField;

    if (_MetaField == 0) {
        _MetaField = (igIntArrayMetaField *)igMetaObject_CreateInstance(_Meta, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
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

