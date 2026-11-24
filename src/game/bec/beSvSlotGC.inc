namespace Gap {
namespace Bec {

igMetaObject *beSvSlotGC::_Meta;

igMetaObject *beSvSlotGC::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *beSvSlotGC::retrieveVTablePointer()
{
    beSvSlotGC temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void beSvSlotGC::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *beSvSlotGC::arkRegisterInternal()
{
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Bec::beSvSlotData::arkRegisterInternal,
        Gap::Bec::beSvSlotData::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "beSvSlotGC",
        sizeof(beSvSlotGC),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        0
    );
}
}
}

