namespace Gap {
namespace Bec {

igMetaObject *beModelCtrlMOVEEX::_Meta;
igMetaField *beModelCtrlMOVEEX::k_value;
igMetaField *beModelCtrlMOVEEX::k_frame;
igMetaField *beModelCtrlMOVEEX::k_playTime;
igMetaField *beModelCtrlMOVEEX::k_isSeqStop;
igMetaField *beModelCtrlMOVEEX::k_stopValue;
igMetaField *beModelCtrlMOVEEX::k_stopFrame;

igMetaObject *beModelCtrlMOVEEX::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *beModelCtrlMOVEEX::retrieveVTablePointer()
{
    beModelCtrlMOVEEX temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void beModelCtrlMOVEEX::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *beModelCtrlMOVEEX::arkRegisterInternal()
{
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igNamedObject::arkRegisterInternal,
        Gap::Core::igNamedObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "beModelCtrlMOVEEX",
        sizeof(beModelCtrlMOVEEX),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void beModelCtrlMOVEEX::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, igBoolMetaField_Create, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool };
    static const char *names[] = { "_value", "_frame", "_playTime", "_isSeqStop", "_stopValue", "_stopFrame" };
    static igMetaField **enumStorage[] = { &k_value, &k_frame, &k_playTime, &k_isSeqStop, &k_stopValue, &k_stopFrame };
    static int offsets[] = { 12, 16, 20, 24, 28, 32 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 6);
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

