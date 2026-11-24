namespace Gap {
namespace Bec {

igMetaObject *beCriFxXbData::_Meta;
igMetaField *beCriFxXbData::k_lRoom;
igMetaField *beCriFxXbData::k_lRoomHF;
igMetaField *beCriFxXbData::k_flRoomRolloffFactor;
igMetaField *beCriFxXbData::k_flDecayTime;
igMetaField *beCriFxXbData::k_flDecayHFRatio;
igMetaField *beCriFxXbData::k_lReflections;
igMetaField *beCriFxXbData::k_flReflectionsDelay;
igMetaField *beCriFxXbData::k_lReverb;
igMetaField *beCriFxXbData::k_flReverbDelay;
igMetaField *beCriFxXbData::k_flDiffusion;
igMetaField *beCriFxXbData::k_flDensity;
igMetaField *beCriFxXbData::k_flHFReference;

igMetaObject *beCriFxXbData::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *beCriFxXbData::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *beCriFxXbData::retrieveVTablePointer()
{
    beCriFxXbData temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void beCriFxXbData::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *beCriFxXbData::arkRegisterInternal()
{
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "beCriFxXbData",
        sizeof(beCriFxXbData),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void beCriFxXbData::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool };
    static const char *names[] = { "_lRoom", "_lRoomHF", "_flRoomRolloffFactor", "_flDecayTime", "_flDecayHFRatio", "_lReflections", "_flReflectionsDelay", "_lReverb", "_flReverbDelay", "_flDiffusion", "_flDensity", "_flHFReference" };
    static igMetaField **enumStorage[] = { &k_lRoom, &k_lRoomHF, &k_flRoomRolloffFactor, &k_flDecayTime, &k_flDecayHFRatio, &k_lReflections, &k_flReflectionsDelay, &k_lReverb, &k_flReverbDelay, &k_flDiffusion, &k_flDensity, &k_flHFReference };
    static int offsets[] = { 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 12);
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

