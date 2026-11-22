namespace Gap {
namespace Gfx {

igMetaObject *igImageConvert::_Meta;

igImageConvert *igImageConvert::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igImageConvert *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igImageConvert::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void igImageConvert::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igImageConvert::arkRegisterInternal()
{
    GfxLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        true,
        &_Meta,
        Gap::Gfx::igImageUtils::arkRegisterInternal,
        Gap::Gfx::igImageUtils::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igImageConvert",
        sizeof(igImageConvert),
        0,
        &arkRegisterInitialize,
        0,
        0
    );
}
}
}

