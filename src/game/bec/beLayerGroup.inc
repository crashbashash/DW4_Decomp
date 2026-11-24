namespace Gap {
namespace Bec {

igMetaObject *beLayerGroup::_Meta;

igMetaObject *beLayerGroup::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *beLayerGroup::retrieveVTablePointer()
{
    beLayerGroup temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void beLayerGroup::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *beLayerGroup::arkRegisterInternal()
{
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igNamedObject::arkRegisterInternal,
        Gap::Core::igNamedObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "beLayerGroup",
        sizeof(beLayerGroup),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        0
    );
}
}
}

igMetaEnum *g_beLayerGroup_swtCtlMetaEnum;
static const char *g_beLayerGroup_swtCtlNames[] = {
    "CLR", "SET", "DISPOFF", "DISPON",
    "FLIP",
};
static int g_beLayerGroup_swtCtlValues[] = {
    0, 1, 0, 1, 2,
};

igMetaEnum *beLayerCtl_GetSwtCtlEnum(void) {
    if (g_beLayerGroup_swtCtlMetaEnum == 0) {
        g_beLayerGroup_swtCtlMetaEnum = (igMetaEnum *)Gap::Core::igMetaEnum::createMetaEnum("SwtCtl", g_beLayerGroup_swtCtlNames, g_beLayerGroup_swtCtlValues, 5);
    }
    return g_beLayerGroup_swtCtlMetaEnum;
}

igMetaEnum *g_beLayerGroup_messageMetaEnum;
static const char *g_beLayerGroup_messageNames[] = {
    "ORDER", "SWITCH", "REMOVE", "GETNAMELIST",
    "GETLAYERNODE", "INFO",
};
static int g_beLayerGroup_messageValues[] = {
    0, 1, 2, 3, 4, 5,
};

igMetaEnum *beLayerCtl_GetMessageEnum(void) {
    if (g_beLayerGroup_messageMetaEnum == 0) {
        g_beLayerGroup_messageMetaEnum = (igMetaEnum *)Gap::Core::igMetaEnum::createMetaEnum("Message", g_beLayerGroup_messageNames, g_beLayerGroup_messageValues, 6);
    }
    return g_beLayerGroup_messageMetaEnum;
}

