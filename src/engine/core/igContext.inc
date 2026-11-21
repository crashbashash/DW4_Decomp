namespace Gap {
namespace Core {

igMetaObject *igContext::_Meta;
igMetaField *igContext::k_pExtList;
igMetaField *igContext::k_iNumExts;
igMetaField *igContext::k_pExtInstances;

igMetaObject *igContext::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void igContext::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igContext::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { igContextExtInfoList_EnsureRegistered, igContextExtList_EnsureRegistered, 0 };

    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        true,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igContext",
        sizeof(igContext),
        0,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igContext::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, igIntMetaField_Create, igObjectRefMetaField_Create };
    static const char *names[] = { "_pExtList", "_iNumExts", "_pExtInstances" };
    static igMetaField **enumStorage[] = { &k_pExtList, &k_iNumExts, &k_pExtInstances };
    static int offsets[] = { 8, 12, 16 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 3);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)igContextExtInfoList_GetOrCreateMetaObject();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->_metaObject = (int)igContextExtList_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

