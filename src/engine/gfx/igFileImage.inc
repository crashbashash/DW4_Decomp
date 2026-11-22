namespace Gap {
namespace Gfx {

igMetaObject *igFileImage::_Meta;

igMetaObject *igFileImage::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void igFileImage::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igFileImage::arkRegisterInternal()
{
    GfxLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        true,
        &_Meta,
        Gap::Gfx::igImage::arkRegisterInternal,
        Gap::Gfx::igImage::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igFileImage",
        sizeof(igFileImage),
        0,
        0,
        0,
        0
    );
}
}
}

