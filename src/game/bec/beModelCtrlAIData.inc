namespace Gap {
namespace Bec {

igMetaObject *beModelCtrlAIData::_Meta;
igMetaField *beModelCtrlAIData::k_dirRadian;
igMetaField *beModelCtrlAIData::k_time;
igMetaField *beModelCtrlAIData::k_limit;

igMetaObject *beModelCtrlAIData::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *beModelCtrlAIData::retrieveVTablePointer()
{
    beModelCtrlAIData temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void beModelCtrlAIData::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *beModelCtrlAIData::arkRegisterInternal()
{
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igNamedObject::arkRegisterInternal,
        Gap::Core::igNamedObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "beModelCtrlAIData",
        sizeof(beModelCtrlAIData),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void beModelCtrlAIData::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool };
    static const char *names[] = { "_dirRadian", "_time", "_limit" };
    static igMetaField **enumStorage[] = { &k_dirRadian, &k_time, &k_limit };
    static int offsets[] = { 12, 16, 20 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 3);
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

