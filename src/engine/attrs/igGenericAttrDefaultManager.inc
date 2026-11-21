namespace Gap {
namespace Attrs {

igMetaObject *igGenericAttrDefaultManager::_Meta;

igGenericAttrDefaultManager *igGenericAttrDefaultManager::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igGenericAttrDefaultManager *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igGenericAttrDefaultManager::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igGenericAttrDefaultManager::retrieveVTablePointer()
{
    igGenericAttrDefaultManager temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igGenericAttrDefaultManager::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igGenericAttrDefaultManager::arkRegisterInternal()
{
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Attrs::igAttrDefaultManager::arkRegisterInternal,
        Gap::Attrs::igAttrDefaultManager::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igGenericAttrDefaultManager",
        sizeof(igGenericAttrDefaultManager),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        0
    );
}
}
}

