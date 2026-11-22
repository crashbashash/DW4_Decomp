namespace Gap {
namespace Core {

igMetaObject *igFolder::_Meta;
igMetaField *igFolder::k_folderName;

igFolder *igFolder::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igFolder *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igFolder::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igFolder::retrieveVTablePointer()
{
    igFolder temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igFolder::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igFolder::arkRegisterInternal()
{
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igFolder",
        sizeof(igFolder),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void igFolder::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igStringMetaField_Create };
    static const char *names[] = { "_folderName" };
    static igMetaField **enumStorage[] = { &k_folderName };
    static int offsets[] = { 8 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 1);
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
    *(void (**)())&_Meta->_abstractProxy = (void (*)())igPsx2Folder_GetMetaObjectFunction;
}
}
}

