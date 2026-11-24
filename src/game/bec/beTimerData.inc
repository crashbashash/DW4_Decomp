namespace Gap {
namespace Bec {

igMetaObject *beTimerData::_Meta;
igMetaField *beTimerData::k_startTime;
igMetaField *beTimerData::k_resetCondition;
igMetaField *beTimerData::k_callLuaFile;
igMetaField *beTimerData::k_downTimer;

igMetaObject *beTimerData::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *beTimerData::retrieveVTablePointer()
{
    beTimerData temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void beTimerData::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *beTimerData::arkRegisterInternal()
{
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "beTimerData",
        sizeof(beTimerData),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void beTimerData::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { (FieldFactory)Gap::Core::igLongMetaField::_instantiateFromPool, igStringMetaField_Create, igStringMetaField_Create, (FieldFactory)Gap::Core::igLongMetaField::_instantiateFromPool };
    static const char *names[] = { "_startTime", "_resetCondition", "_callLuaFile", "_downTimer" };
    static igMetaField **enumStorage[] = { &k_startTime, &k_resetCondition, &k_callLuaFile, &k_downTimer };
    static int offsets[] = { 8, 16, 20, 24 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 4);
    {
        igStringMetaField *metaField = (igStringMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->setDefault(0);
    }
    {
        igStringMetaField *metaField = (igStringMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->setDefault(0);
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

