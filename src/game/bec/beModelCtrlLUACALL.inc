namespace Gap {
namespace Bec {

igMetaObject *beModelCtrlLUACALL::_Meta;
igMetaField *beModelCtrlLUACALL::k_modeName;

igMetaObject *beModelCtrlLUACALL::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *beModelCtrlLUACALL::retrieveVTablePointer()
{
    beModelCtrlLUACALL temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void beModelCtrlLUACALL::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *beModelCtrlLUACALL::arkRegisterInternal()
{
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igNamedObject::arkRegisterInternal,
        Gap::Core::igNamedObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "beModelCtrlLUACALL",
        sizeof(beModelCtrlLUACALL),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void beModelCtrlLUACALL::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igStringMetaField_Create };
    static const char *names[] = { "_modeName" };
    static igMetaField **enumStorage[] = { &k_modeName };
    static int offsets[] = { 12 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 1);
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

