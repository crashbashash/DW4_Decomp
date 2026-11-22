namespace Gap {
namespace Gfx {

igMetaObject *igMemoryImage::_Meta;

igMetaObject *igMemoryImage::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void igMemoryImage::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igMemoryImage::arkRegisterInternal()
{
    GfxLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        true,
        &_Meta,
        Gap::Gfx::igImage::arkRegisterInternal,
        Gap::Gfx::igImage::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igMemoryImage",
        sizeof(igMemoryImage),
        0,
        0,
        0,
        0
    );
}
}
}

