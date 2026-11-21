namespace Gap {
namespace Core {

igMetaObject *igExternalInfoEntry::_Meta;
igMetaField *igExternalInfoEntry::k_key;
igMetaField *igExternalInfoEntry::k_directoryIndex;
igMetaField *igExternalInfoEntry::k_infoName;

igExternalInfoEntry *igExternalInfoEntry::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igExternalInfoEntry *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igExternalInfoEntry::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igExternalInfoEntry::retrieveVTablePointer()
{
    igExternalInfoEntry temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igExternalInfoEntry::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igExternalInfoEntry::arkRegisterInternal()
{
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igDirEntry::arkRegisterInternal,
        Gap::Core::igDirEntry::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igExternalInfoEntry",
        sizeof(igExternalInfoEntry),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void igExternalInfoEntry::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igStringMetaField_Create, igIntMetaField_Create, igStringMetaField_Create };
    static const char *names[] = { "_key", "_directoryIndex", "_infoName" };
    static igMetaField **enumStorage[] = { &k_key, &k_directoryIndex, &k_infoName };
    static int offsets[] = { 28, 32, 36 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 3);
    {
        igStringMetaField *metaField = (igStringMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->setDefault(0);
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->setDefault(-1);
    }
    {
        igStringMetaField *metaField = (igStringMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->setDefault(0);
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

