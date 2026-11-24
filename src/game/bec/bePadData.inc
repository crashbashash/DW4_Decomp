namespace Gap {
namespace Bec {

igMetaObject *bePadData::_Meta;
igMetaField *bePadData::k_isConnect;
igMetaField *bePadData::k_LStick;
igMetaField *bePadData::k_RStick;
igMetaField *bePadData::k_lTrg;
igMetaField *bePadData::k_lRpt;
igMetaField *bePadData::k_lStk;
igMetaField *bePadData::k_lLast;
igMetaField *bePadData::k_lTime;
igMetaField *bePadData::k_rTrg;
igMetaField *bePadData::k_rRpt;
igMetaField *bePadData::k_rStk;
igMetaField *bePadData::k_rLast;
igMetaField *bePadData::k_rTime;
igMetaField *bePadData::k_button;
igMetaField *bePadData::k_trigger;
igMetaField *bePadData::k_repeat;
igMetaField *bePadData::k_last;
igMetaField *bePadData::k_rptime;
igMetaField *bePadData::k_enaLen;
igMetaField *bePadData::k_adAngle;
igMetaField *bePadData::k_1sttime;
igMetaField *bePadData::k_2ndtime;

bePadData *bePadData::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (bePadData *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *bePadData::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *bePadData::retrieveVTablePointer()
{
    bePadData temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void bePadData::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *bePadData::arkRegisterInternal()
{
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "bePadData",
        sizeof(bePadData),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void bePadData::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igBoolMetaField_Create, (FieldFactory)Gap::Math::igVec2fMetaField::_instantiateFromPool, (FieldFactory)Gap::Math::igVec2fMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool };
    static const char *names[] = { "_isConnect", "_LStick", "_RStick", "_lTrg", "_lRpt", "_lStk", "_lLast", "_lTime", "_rTrg", "_rRpt", "_rStk", "_rLast", "_rTime", "_button", "_trigger", "_repeat", "_last", "_rptime", "_enaLen", "_adAngle", "_1sttime", "_2ndtime" };
    static igMetaField **enumStorage[] = { &k_isConnect, &k_LStick, &k_RStick, &k_lTrg, &k_lRpt, &k_lStk, &k_lLast, &k_lTime, &k_rTrg, &k_rRpt, &k_rStk, &k_rLast, &k_rTime, &k_button, &k_trigger, &k_repeat, &k_last, &k_rptime, &k_enaLen, &k_adAngle, &k_1sttime, &k_2ndtime };
    static int offsets[] = { 8, 12, 20, 28, 32, 36, 40, 44, 48, 52, 56, 60, 64, 68, 72, 76, 80, 84, 88, 92, 96, 100 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 22);
    {
        igVec2fMetaField *metaField = (igVec2fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->setDefault(igVec2f(0.0f, 0.0f));
    }
    {
        igVec2fMetaField *metaField = (igVec2fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->setDefault(igVec2f(0.0f, 0.0f));
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

