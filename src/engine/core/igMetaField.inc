namespace Gap {
namespace Core {

igMetaObject *igMetaField::_Meta;
igMetaField *igMetaField::k_offset;
igMetaField *igMetaField::k_fieldName;
igMetaField *igMetaField::k_typeIndex;
igMetaField *igMetaField::k_internalIndex;
igMetaField *igMetaField::k_size;
igMetaField *igMetaField::k_parentMetaObject;
igMetaField *igMetaField::k_externalEnumStorage;
igMetaField *igMetaField::k_default;
igMetaField *igMetaField::k_resetMethod;
igMetaField *igMetaField::k_isRunTime;
igMetaField *igMetaField::k_persistent;
igMetaField *igMetaField::k_shallowCopyMethod;
igMetaField *igMetaField::k_deepCopyMethod;
igMetaField *igMetaField::k_constructCopyMethod;
igMetaField *igMetaField::k_isAlikeExactlyMethod;
igMetaField *igMetaField::k_isAlikeDeepMethod;
igMetaField *igMetaField::k_isAlikeShallowMethod;
igMetaField *igMetaField::k_invarianceFunction;

igMetaObject *igMetaField::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igMetaField::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void igMetaField::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igMetaField::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { igMetaObject_EnsureRegistered, 0 };

    return igMetaObject_RegisterClass(
        true,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igMetaField",
        sizeof(igMetaField),
        0,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igMetaField::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igIntMetaField_Create, igStringMetaField_Create, igShortMetaField_Create, igShortMetaField_Create, igUnsignedShortMetaField_Create, igObjectRefMetaField_Create, igRawRefMetaField_Create, igMemoryRefMetaField_Create, igCharMetaField_Create, igBoolMetaField_Create, igBoolMetaField_Create, igCharMetaField_Create, igCharMetaField_Create, igCharMetaField_Create, igCharMetaField_Create, igCharMetaField_Create, igCharMetaField_Create, igRawRefMetaField_Create };
    static const char *names[] = { "_offset", "_fieldName", "_typeIndex", "_internalIndex", "_size", "_parentMetaObject", "_externalEnumStorage", "_default", "_resetMethod", "_isRunTime", "_persistent", "_shallowCopyMethod", "_deepCopyMethod", "_constructCopyMethod", "_isAlikeExactlyMethod", "_isAlikeDeepMethod", "_isAlikeShallowMethod", "_invarianceFunction" };
    static igMetaField **enumStorage[] = { &k_offset, &k_fieldName, &k_typeIndex, &k_internalIndex, &k_size, &k_parentMetaObject, &k_externalEnumStorage, &k_default, &k_resetMethod, &k_isRunTime, &k_persistent, &k_shallowCopyMethod, &k_deepCopyMethod, &k_constructCopyMethod, &k_isAlikeExactlyMethod, &k_isAlikeDeepMethod, &k_isAlikeShallowMethod, &k_invarianceFunction };
    static int offsets[] = { 8, 12, 16, 18, 20, 24, 28, 32, 36, 37, 38, 39, 40, 41, 42, 43, 44, 48 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 18);
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_persistent = 0;
    }
    {
        igShortMetaField *metaField = (igShortMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        igShortMetaField_SetDefault((::igMetaField *)metaField, -1);
        metaField->_persistent = 0;
    }
    {
        igShortMetaField *metaField = (igShortMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        igShortMetaField_SetDefault((::igMetaField *)metaField, -1);
        metaField->_persistent = 0;
    }
    {
        igUnsignedShortMetaField *metaField = (igUnsignedShortMetaField *)igMetaObject_GetFieldAt(metaObject, start + 4);
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 5);
        metaField->_metaObject = (int)igMetaObject_GetOrCreateMetaObject();
        metaField->_refCounted = 0;
        metaField->_persistent = 0;
        metaField->_deepCopyMethod = 1;
        metaField->_shallowCopyMethod = 1;
    }
    {
        igRawRefMetaField *metaField = (igRawRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 6);
        metaField->_persistent = 0;
        metaField->_deepCopyMethod = 1;
    }
    {
        igMemoryRefMetaField *metaField = (igMemoryRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 7);
        metaField->_destruct = 1;
        metaField->_releaseOnCopy = 1;
        metaField->_releaseOnReset = 1;
        metaField->_persistent = 0;
    }
    {
        igCharMetaField *metaField = (igCharMetaField *)igMetaObject_GetFieldAt(metaObject, start + 8);
        igCharMetaField_SetDefaultValue((::igMetaField *)metaField, 0);
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 10);
        igBoolMetaField_SetDefaultValue((::igMetaField *)metaField, 1);
    }
    {
        igCharMetaField *metaField = (igCharMetaField *)igMetaObject_GetFieldAt(metaObject, start + 11);
        igCharMetaField_SetDefaultValue((::igMetaField *)metaField, 1);
    }
    {
        igCharMetaField *metaField = (igCharMetaField *)igMetaObject_GetFieldAt(metaObject, start + 12);
        igCharMetaField_SetDefaultValue((::igMetaField *)metaField, 0);
    }
    {
        igCharMetaField *metaField = (igCharMetaField *)igMetaObject_GetFieldAt(metaObject, start + 13);
        igCharMetaField_SetDefaultValue((::igMetaField *)metaField, 0);
    }
    {
        igCharMetaField *metaField = (igCharMetaField *)igMetaObject_GetFieldAt(metaObject, start + 14);
        igCharMetaField_SetDefaultValue((::igMetaField *)metaField, 0);
    }
    {
        igCharMetaField *metaField = (igCharMetaField *)igMetaObject_GetFieldAt(metaObject, start + 15);
        igCharMetaField_SetDefaultValue((::igMetaField *)metaField, 1);
    }
    {
        igCharMetaField *metaField = (igCharMetaField *)igMetaObject_GetFieldAt(metaObject, start + 16);
        igCharMetaField_SetDefaultValue((::igMetaField *)metaField, 2);
    }
    {
        igRawRefMetaField *metaField = (igRawRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 17);
        metaField->_persistent = 0;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}
