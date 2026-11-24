namespace Gap {
namespace Sg {

igShaderProcessor *igShaderProcessor::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igShaderProcessor *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igShaderProcessor::_Meta;

igMetaObject *igShaderProcessor::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igShaderProcessor::retrieveVTablePointer()
{
    igShaderProcessor temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igShaderProcessor::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igShaderProcessor::arkRegisterInternal()
{
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igShaderProcessor",
        sizeof(igShaderProcessor),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        0
    );
}
}
}

