namespace Gap {
namespace Gfx {

igMetaObject *igImageUtils::_Meta;

igMetaObject *igImageUtils::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void igImageUtils::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igImageUtils::arkRegisterInternal()
{
    GfxLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        true,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igImageUtils",
        sizeof(igImageUtils),
        0,
        0,
        0,
        0
    );
}
}
}

igSmartPointer<igObject> *FUN_0014dd40(igSmartPointer<igObject> *self, short deleteFlag) {
    if (self) {
        igObject *object = self->p;
        igObject::release(object);
        if (deleteFlag > 0) operator delete(self);
    }
    return self;
}

