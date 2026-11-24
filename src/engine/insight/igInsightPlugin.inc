namespace Gap {
namespace Insight {

igMetaObject *igInsightPlugin::_Meta;

igMetaObject *igInsightPlugin::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void igInsightPlugin::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igInsightPlugin::arkRegisterInternal()
{
    InsightLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        true,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igInsightPlugin",
        sizeof(igInsightPlugin),
        0,
        0,
        0,
        0
    );
}
}
}

