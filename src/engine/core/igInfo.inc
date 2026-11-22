namespace Gap {
namespace Core {

igMetaObject *igInfo::_Meta;
igMetaField *igInfo::k_directory;
igMetaField *igInfo::k_resolveState;

igMetaObject *igInfo::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igInfo::retrieveVTablePointer()
{
    igInfo temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igInfo::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igInfo::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Core::igDirectory::arkRegister, 0 };

    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igNamedObject::arkRegisterInternal,
        Gap::Core::igNamedObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igInfo",
        sizeof(igInfo),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igInfo::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, igBoolMetaField_Create };
    static const char *names[] = { "_directory", "_resolveState" };
    static igMetaField **enumStorage[] = { &k_directory, &k_resolveState };
    static int offsets[] = { 12, 16 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 2);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)Gap::Core::igDirectory::getClassTypeLazy();
        metaField->_refCounted = 0;
        metaField->_persistent = 0;
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->setDefault(1);
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

