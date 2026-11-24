namespace Gap {
namespace Bec {

igMetaObject *beSvSlotPS2::_Meta;

igMetaObject *beSvSlotPS2::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *beSvSlotPS2::retrieveVTablePointer()
{
    beSvSlotPS2 temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void beSvSlotPS2::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *beSvSlotPS2::arkRegisterInternal()
{
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Bec::beSvSlotData::arkRegisterInternal,
        Gap::Bec::beSvSlotData::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "beSvSlotPS2",
        sizeof(beSvSlotPS2),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        0
    );
}
}
}

