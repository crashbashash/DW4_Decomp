namespace Gap {
namespace Core {

igMetaObject *igMetaEnum::_Meta;
igMetaField *igMetaEnum::k_name;
igMetaField *igMetaEnum::k_names;
igMetaField *igMetaEnum::k_values;

igMetaEnum *igMetaEnum::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igMetaEnum *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igMetaEnum::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igMetaEnum::retrieveVTablePointer()
{
    igMetaEnum temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igMetaEnum::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igMetaEnum::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { igStringRefList_EnsureRegistered, Gap::Core::igIntList::arkRegister, 0 };

    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igMetaEnum",
        sizeof(igMetaEnum),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igMetaEnum::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igStringMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create };
    static const char *names[] = { "_name", "_names", "_values" };
    static igMetaField **enumStorage[] = { &k_name, &k_names, &k_values };
    static int offsets[] = { 8, 12, 16 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 3);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_metaObject = (int)igStringRefList_GetOrCreateMetaObject();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->_metaObject = (int)Gap::Core::igIntList::getClassTypeLazy();
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

