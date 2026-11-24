namespace Gap {
namespace Bec {

igMetaObject *beWaterMoveData::_Meta;
igMetaField *beWaterMoveData::k_time;
igMetaField *beWaterMoveData::k_power;
igMetaField *beWaterMoveData::k_posList;

igMetaObject *beWaterMoveData::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *beWaterMoveData::retrieveVTablePointer()
{
    beWaterMoveData temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void beWaterMoveData::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *beWaterMoveData::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { igVec3fList_EnsureRegistered, 0 };

    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "beWaterMoveData",
        sizeof(beWaterMoveData),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void beWaterMoveData::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { (FieldFactory)Gap::Core::igLongMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, igObjectRefMetaField_Create };
    static const char *names[] = { "_time", "_power", "_posList" };
    static igMetaField **enumStorage[] = { &k_time, &k_power, &k_posList };
    static int offsets[] = { 8, 16, 20 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 3);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->_metaObject = (int)igVec3fList_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

