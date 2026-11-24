namespace Gap {
namespace Bec {

igMetaObject *beAction2InfoWork::_Meta;
igMetaField *beAction2InfoWork::k_comData;
igMetaField *beAction2InfoWork::k_comIndex;
igMetaField *beAction2InfoWork::k_isNoHokan;
igMetaField *beAction2InfoWork::k_isMotion;
igMetaField *beAction2InfoWork::k_motionSt0;
igMetaField *beAction2InfoWork::k_motionIsEnd;
igMetaField *beAction2InfoWork::k_jointSt0;
igMetaField *beAction2InfoWork::k_jointStartTimeL;
igMetaField *beAction2InfoWork::k_jointEndTimeL;
igMetaField *beAction2InfoWork::k_jointIsEnd;
igMetaField *beAction2InfoWork::k_fadeSt0;
igMetaField *beAction2InfoWork::k_fadeLimitValue;
igMetaField *beAction2InfoWork::k_fadeAddValue;
igMetaField *beAction2InfoWork::k_fadeValue;
igMetaField *beAction2InfoWork::k_waitSt0;
igMetaField *beAction2InfoWork::k_flashSt0;
igMetaField *beAction2InfoWork::k_isFreeze;
igMetaField *beAction2InfoWork::k_colorAttr;
igMetaField *beAction2InfoWork::k_blendStateAttr;
igMetaField *beAction2InfoWork::k_textureStateAttr;
igMetaField *beAction2InfoWork::k_lightingStateAttr;

beAction2InfoWork *beAction2InfoWork::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (beAction2InfoWork *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *beAction2InfoWork::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *beAction2InfoWork::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *beAction2InfoWork::retrieveVTablePointer()
{
    beAction2InfoWork temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}
}
}

namespace Gap {
namespace Bec {

void beAction2InfoWork::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *beAction2InfoWork::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { beAction2Data_EnsureRegistered, Gap::Attrs::igColorAttr::arkRegister, Gap::Attrs::igBlendStateAttr::arkRegister, Gap::Attrs::igTextureStateAttr::arkRegister, Gap::Attrs::igLightingStateAttr::arkRegister, 0 };

    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "beAction2InfoWork",
        sizeof(beAction2InfoWork),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void beAction2InfoWork::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, igBoolMetaField_Create, igBoolMetaField_Create, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, igBoolMetaField_Create, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igLongMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igLongMetaField::_instantiateFromPool, igBoolMetaField_Create, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, igBoolMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create };
    static const char *names[] = { "_comData", "_comIndex", "_isNoHokan", "_isMotion", "_motionSt0", "_motionIsEnd", "_jointSt0", "_jointStartTimeL", "_jointEndTimeL", "_jointIsEnd", "_fadeSt0", "_fadeLimitValue", "_fadeAddValue", "_fadeValue", "_waitSt0", "_flashSt0", "_isFreeze", "_colorAttr", "_blendStateAttr", "_textureStateAttr", "_lightingStateAttr" };
    static igMetaField **enumStorage[] = { &k_comData, &k_comIndex, &k_isNoHokan, &k_isMotion, &k_motionSt0, &k_motionIsEnd, &k_jointSt0, &k_jointStartTimeL, &k_jointEndTimeL, &k_jointIsEnd, &k_fadeSt0, &k_fadeLimitValue, &k_fadeAddValue, &k_fadeValue, &k_waitSt0, &k_flashSt0, &k_isFreeze, &k_colorAttr, &k_blendStateAttr, &k_textureStateAttr, &k_lightingStateAttr };
    static int offsets[] = { 8, 12, 16, 17, 20, 24, 28, 32, 40, 48, 52, 56, 60, 64, 68, 72, 76, 80, 84, 88, 92 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 21);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)beAction2Data_GetOrCreateMetaObject();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 17);
        metaField->_metaObject = (int)Gap::Attrs::igColorAttr::getClassTypeLazy();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 18);
        metaField->_metaObject = (int)Gap::Attrs::igBlendStateAttr::getClassTypeLazy();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 19);
        metaField->_metaObject = (int)Gap::Attrs::igTextureStateAttr::getClassTypeLazy();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 20);
        metaField->_metaObject = (int)Gap::Attrs::igLightingStateAttr::getClassTypeLazy();
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

