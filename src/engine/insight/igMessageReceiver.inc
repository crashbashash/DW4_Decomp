namespace Gap {
namespace Insight {

igMetaObject *igMessageReceiver::_Meta;

igMetaObject *igMessageReceiver::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void igMessageReceiver::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igMessageReceiver::arkRegisterInternal()
{
    InsightLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        true,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igMessageReceiver",
        sizeof(igMessageReceiver),
        0,
        0,
        0,
        0
    );
}
}
}

