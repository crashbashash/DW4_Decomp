namespace Gap {
namespace Core {

igMetaObject *igCompoundMetaField::_Meta;
igCompoundMetaField *igCompoundMetaField::_MetaField;
igMetaField *igCompoundMetaField::k_fieldList;

igMetaObject *igCompoundMetaField::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void igCompoundMetaField::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igCompoundMetaField::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { igMetaFieldList_EnsureRegistered, arkRegisterMetaValidate, 0 };

    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        true,
        &_Meta,
        Gap::Core::igMetaField::arkRegisterInternal,
        Gap::Core::igMetaField::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igCompoundMetaField",
        sizeof(igCompoundMetaField),
        0,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igCompoundMetaField::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create };
    static const char *names[] = { "_fieldList" };
    static igMetaField **enumStorage[] = { &k_fieldList };
    static int offsets[] = { 52 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 1);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)igMetaFieldList_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}

void igCompoundMetaField::arkRegisterMetaValidate()
{
    igCompoundMetaField *metaField;

    if (_MetaField == 0) {
        _MetaField = (igCompoundMetaField *)igMetaObject_CreateInstance(_Meta, Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
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

unsigned short igCompoundMetaField::computeSize()
{
    return 1;
}

void igCompoundMetaField::initDefaults()
{
    arkRegisterCompoundFields(_fieldList);
}

void igCompoundMetaField::arkRegisterCompoundFields(igMetaFieldList *fieldList)
{
}
}
}

