namespace Gap {
namespace Gfx {

igMetaObject *igCapabilityManager::_Meta;

igMetaObject *igCapabilityManager::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void igCapabilityManager::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igCapabilityManager::arkRegisterInternal()
{
    GfxLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        true,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igCapabilityManager",
        sizeof(igCapabilityManager),
        0,
        0,
        0,
        0
    );
}
}
}

