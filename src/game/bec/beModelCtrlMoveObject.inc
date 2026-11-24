namespace Gap {
namespace Bec {

igMetaObject *beModelCtrlMoveObject::_Meta;
igMetaField *beModelCtrlMoveObject::k_isRun;
igMetaField *beModelCtrlMoveObject::k_endTime;
igMetaField *beModelCtrlMoveObject::k_mode;
igMetaField *beModelCtrlMoveObject::k_value;
igMetaField *beModelCtrlMoveObject::k_acc;
igMetaField *beModelCtrlMoveObject::k_speed;
igMetaField *beModelCtrlMoveObject::k_isSeqStop;
igMetaField *beModelCtrlMoveObject::k_stopValue;
igMetaField *beModelCtrlMoveObject::k_stopFrame;

beModelCtrlMoveObject *beModelCtrlMoveObject::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (beModelCtrlMoveObject *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *beModelCtrlMoveObject::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *beModelCtrlMoveObject::retrieveVTablePointer()
{
    beModelCtrlMoveObject temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void beModelCtrlMoveObject::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *beModelCtrlMoveObject::arkRegisterInternal()
{
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "beModelCtrlMoveObject",
        sizeof(beModelCtrlMoveObject),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void beModelCtrlMoveObject::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igBoolMetaField_Create, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, igBoolMetaField_Create, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool };
    static const char *names[] = { "_isRun", "_endTime", "_mode", "_value", "_acc", "_speed", "_isSeqStop", "_stopValue", "_stopFrame" };
    static igMetaField **enumStorage[] = { &k_isRun, &k_endTime, &k_mode, &k_value, &k_acc, &k_speed, &k_isSeqStop, &k_stopValue, &k_stopFrame };
    static int offsets[] = { 8, 12, 16, 20, 24, 28, 32, 36, 40 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 9);
    {
        igFloatMetaField *metaField = (igFloatMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->setDefault(0.0f);
    }
    {
        igFloatMetaField *metaField = (igFloatMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->setDefault(0.0f);
    }
    {
        igFloatMetaField *metaField = (igFloatMetaField *)igMetaObject_GetFieldAt(metaObject, start + 4);
        metaField->setDefault(0.0f);
    }
    {
        igFloatMetaField *metaField = (igFloatMetaField *)igMetaObject_GetFieldAt(metaObject, start + 5);
        metaField->setDefault(0.0f);
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

