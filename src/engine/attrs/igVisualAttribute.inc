namespace Gap {
namespace Attrs {

igMetaObject *igVisualAttribute::_Meta;

igMetaObject *igVisualAttribute::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igVisualAttribute::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void igVisualAttribute::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igVisualAttribute::arkRegisterInternal()
{
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        true,
        &_Meta,
        Gap::Attrs::igAttr::arkRegisterInternal,
        Gap::Attrs::igAttr::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igVisualAttribute",
        sizeof(igVisualAttribute),
        0,
        0,
        0,
        0
    );
}
}
}

