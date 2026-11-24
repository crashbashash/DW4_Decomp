namespace Gap {
namespace Bec {

igMetaObject *beSvPlatDataPC::_Meta;

igMetaObject *beSvPlatDataPC::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *beSvPlatDataPC::retrieveVTablePointer()
{
    beSvPlatDataPC temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}
}
}

namespace Gap {
namespace Bec {

void beSvPlatDataPC::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *beSvPlatDataPC::arkRegisterInternal()
{
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Bec::beSvPlatBaseData::arkRegisterInternal,
        Gap::Bec::beSvPlatBaseData::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "beSvPlatDataPC",
        sizeof(beSvPlatDataPC),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        0
    );
}
}
}

