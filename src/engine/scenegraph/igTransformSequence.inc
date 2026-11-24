namespace Gap {
namespace Sg {

igMetaObject *igTransformSequence::_Meta;
igMetaField *igTransformSequence::k_xlateList;
igMetaField *igTransformSequence::k_quatList;
igMetaField *igTransformSequence::k_scaleList;
igMetaField *igTransformSequence::k_timeList;
igMetaField *igTransformSequence::k_startTime;
igMetaField *igTransformSequence::k_uniformTimeEnabled;
igMetaField *igTransformSequence::k_playMode;
igMetaField *igTransformSequence::k_lastTime;
igMetaField *igTransformSequence::k_centerOfRotation;

void igTransformSequence1_5::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, (FieldFactory)Gap::Core::igUnsignedCharMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igUnsignedCharArrayMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igLongMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igLongMetaField::_instantiateFromPool, igObjectRefMetaField_Create };
    static const char *names[] = { "_timeListLong", "_interpolationDataTranslation", "_interpolationDataRotation", "_interpolationDataScale", "_drivenChannels", "_interpolationMethod", "_keyframeTimeOffset", "_animationDuration", "_compressedDataObject" };
    static igMetaField **enumStorage[] = { &k_timeListLong, &k_interpolationDataTranslation, &k_interpolationDataRotation, &k_interpolationDataScale, &k_drivenChannels, &k_interpolationMethod, &k_keyframeTimeOffset, &k_animationDuration, &k_compressedDataObject };
    static int offsets[] = { 56, 60, 64, 68, 72, 73, 80, 88, 96 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 9);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)Gap::Core::igLongList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_FindFieldByName(metaObject, "_timeList");
        int metaIndex = ((__internalNonRefCountedObjectList *)metaObject->_metaFields)->find(metaField);
        metaField = (igObjectRefMetaField *)((igObjectDispatchView *)metaField)->CloneViaMetadata(1);
        metaField->setDefault(0);
        metaField->_construct = 0;
        metaField->_externalEnumStorage = (int)&k_timeList;
        igMetaObject_FinalizeAndReplaceField(metaObject, metaIndex, (::igMetaField *)metaField);
        metaField->release();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_metaObject = (int)igVec3fList_GetOrCreateMetaObject();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->_metaObject = (int)igVec3fList_GetOrCreateMetaObject();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->_metaObject = (int)igVec3fList_GetOrCreateMetaObject();
    }
    {
        igUnsignedCharMetaField *metaField = (igUnsignedCharMetaField *)igMetaObject_GetFieldAt(metaObject, start + 4);
        metaField->setDefault(11);
    }
    {
        igUnsignedCharArrayMetaField *metaField = (igUnsignedCharArrayMetaField *)igMetaObject_GetFieldAt(metaObject, start + 5);
        metaField->_num = 3;
    }
    {
        igLongMetaField *metaField = (igLongMetaField *)igMetaObject_GetFieldAt(metaObject, start + 7);
        metaField->setDefault(-1);
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 8);
        metaField->_metaObject = (int)igCompressedTransformSequence1_5Data_GetOrCreateMetaObject();
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

void thunk_FUN_001ddfd0(void) {
    FUN_001ddfd0();
}

namespace Gap {
namespace Sg {

igMetaObject *igTransformSequence::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void igTransformSequence::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igTransformSequence::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { igVec3fList_EnsureRegistered, igQuaternionfList_EnsureRegistered, Gap::Core::igDoubleList::arkRegister, 0 };

    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        true,
        &_Meta,
        Gap::Sg::igTransformSource::arkRegisterInternal,
        Gap::Sg::igTransformSource::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igTransformSequence",
        sizeof(igTransformSequence),
        0,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igTransformSequence::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igDoubleMetaField_Create, igBoolMetaField_Create, igEnumMetaField_Create, igIntMetaField_Create, (FieldFactory)Gap::Math::igVec3fMetaField::_instantiateFromPool };
    static const char *names[] = { "_xlateList", "_quatList", "_scaleList", "_timeList", "_startTime", "_uniformTimeEnabled", "_playMode", "_lastTime", "_centerOfRotation" };
    static igMetaField **enumStorage[] = { &k_xlateList, &k_quatList, &k_scaleList, &k_timeList, &k_startTime, &k_uniformTimeEnabled, &k_playMode, &k_lastTime, &k_centerOfRotation };
    static int offsets[] = { 8, 12, 16, 20, 24, 32, 36, 40, 44 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 9);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)igVec3fList_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_metaObject = (int)igQuaternionfList_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->_metaObject = (int)igVec3fList_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->_metaObject = (int)Gap::Core::igDoubleList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igDoubleMetaField *metaField = (igDoubleMetaField *)igMetaObject_GetFieldAt(metaObject, start + 4);
        metaField->setDefault(-1.0);
    }
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 6);
        metaField->setDefault(0);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())igMetaEnum_GetEmpty;
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 7);
        metaField->setDefault(1);
        metaField->_persistent = 0;
    }
    {
        Gap::Math::igVec3fMetaField *metaField = (Gap::Math::igVec3fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 8);
        metaField->setDefault(igVec3f(0.0f, 0.0f, 0.0f));
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
    _Meta->_abstractProxy = (int)Gap::Sg::igTransformSequence1_5::getClassMetaSafe;
}
}
}

