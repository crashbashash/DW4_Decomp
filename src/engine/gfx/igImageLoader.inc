namespace Gap {
namespace Gfx {

igMetaObject *igImageLoader::_Meta;

igMetaObject *igImageLoader::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void igImageLoader::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igImageLoader::arkRegisterInternal()
{
    GfxLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        true,
        &_Meta,
        Gap::Gfx::igImageUtils::arkRegisterInternal,
        Gap::Gfx::igImageUtils::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igImageLoader",
        sizeof(igImageLoader),
        0,
        0,
        0,
        0
    );
}
}
}

