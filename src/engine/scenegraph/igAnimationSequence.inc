namespace Gap {
namespace Sg {

igMetaObject *igAnimationSequence::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void igAnimationSequence::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igAnimationSequence::arkRegisterInternal()
{
    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        true,
        &_Meta,
        Gap::Sg::igTransformSource::arkRegisterInternal,
        Gap::Sg::igTransformSource::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igAnimationSequence",
        sizeof(igAnimationSequence),
        0,
        0,
        0,
        0
    );
}
}
}

