namespace Gap {
namespace Sg {

igGraphPath *igGraphPath::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igGraphPath *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igGraphPath::_Meta;
igMetaField *igGraphPath::k_path;
igMetaField *igGraphPath::k_center;
igMetaField *igGraphPath::k_length;

igMetaObject *igGraphPath::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igGraphPath::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igGraphPath::retrieveVTablePointer()
{
    igGraphPath temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igGraphPath::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igGraphPath::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Sg::igNodeList::arkRegister, 0 };

    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igGraphPath",
        sizeof(igGraphPath),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igGraphPath::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, (FieldFactory)Gap::Math::igVec3fMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool };
    static const char *names[] = { "_path", "_center", "_length" };
    static igMetaField **enumStorage[] = { &k_path, &k_center, &k_length };
    static int offsets[] = { 8, 12, 24 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 3);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)Gap::Sg::igNodeList::getClassTypeLazy();
        metaField->_resetMethod = 3;
        metaField->_construct = 1;
    }
    {
        igVec3fMetaField *metaField = (igVec3fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->setDefault(igVec3f(0.0f, 0.0f, 0.0f));
    }
    {
        igFloatMetaField *metaField = (igFloatMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->setDefault(1.0f);
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

