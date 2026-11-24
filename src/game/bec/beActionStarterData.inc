namespace Gap {
namespace Bec {

igMetaObject *beActionStarterData::_Meta;
igMetaField *beActionStarterData::k_message;
igMetaField *beActionStarterData::k_delay;
igMetaField *beActionStarterData::k_offset;
igMetaField *beActionStarterData::k_isSeqDead;
igMetaField *beActionStarterData::k_isPositionLock;

igMetaObject *beActionStarterData::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *beActionStarterData::retrieveVTablePointer()
{
    beActionStarterData temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void beActionStarterData::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *beActionStarterData::arkRegisterInternal()
{
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igNamedObject::arkRegisterInternal,
        Gap::Core::igNamedObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "beActionStarterData",
        sizeof(beActionStarterData),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void beActionStarterData::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igStringMetaField_Create, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, (FieldFactory)Gap::Math::igVec3fMetaField::_instantiateFromPool, igBoolMetaField_Create, igBoolMetaField_Create };
    static const char *names[] = { "_message", "_delay", "_offset", "_isSeqDead", "_isPositionLock" };
    static igMetaField **enumStorage[] = { &k_message, &k_delay, &k_offset, &k_isSeqDead, &k_isPositionLock };
    static int offsets[] = { 12, 16, 20, 32, 33 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 5);
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

