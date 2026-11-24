namespace Gap {
namespace Sg {

igMetaObject *igCompressedAnimationSequenceQS::_Meta;
igMetaField *igCompressedAnimationSequenceQS::k_compressedTranslationList;
igMetaField *igCompressedAnimationSequenceQS::k_compressedQuaternionList;
igMetaField *igCompressedAnimationSequenceQS::k_compressedTimeList;
igMetaField *igCompressedAnimationSequenceQS::k_translationBase;
igMetaField *igCompressedAnimationSequenceQS::k_translationRangeOverMaxUShort;
igMetaField *igCompressedAnimationSequenceQS::k_quaternionBase;
igMetaField *igCompressedAnimationSequenceQS::k_quaternionRangeOverMaxUShort;
igMetaField *igCompressedAnimationSequenceQS::k_animationDuration;
igMetaField *igCompressedAnimationSequenceQS::k_playMode;
igMetaField *igCompressedAnimationSequenceQS::k_lastTime;
igMetaField *igCompressedAnimationSequenceQS::k_channels;
igMetaField *igCompressedAnimationSequenceQS::k_interpolationMethod;

igMetaObject *igCompressedAnimationSequenceQS::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igCompressedAnimationSequenceQS::retrieveVTablePointer()
{
    igCompressedAnimationSequenceQS temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igCompressedAnimationSequenceQS::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igCompressedAnimationSequenceQS::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Core::igUnsignedShortList::arkRegister, 0 };

    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Sg::igAnimationSequence::arkRegisterInternal,
        Gap::Sg::igAnimationSequence::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igCompressedAnimationSequenceQS",
        sizeof(igCompressedAnimationSequenceQS),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igCompressedAnimationSequenceQS::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igUnsignedLongMetaField::_instantiateFromPool, igEnumMetaField_Create, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igUnsignedCharMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igUnsignedCharArrayMetaField::_instantiateFromPool };
    static const char *names[] = { "_compressedTranslationList", "_compressedQuaternionList", "_compressedTimeList", "_translationBase", "_translationRangeOverMaxUShort", "_quaternionBase", "_quaternionRangeOverMaxUShort", "_animationDuration", "_playMode", "_lastTime", "_channels", "_interpolationMethod" };
    static igMetaField **enumStorage[] = { &k_compressedTranslationList, &k_compressedQuaternionList, &k_compressedTimeList, &k_translationBase, &k_translationRangeOverMaxUShort, &k_quaternionBase, &k_quaternionRangeOverMaxUShort, &k_animationDuration, &k_playMode, &k_lastTime, &k_channels, &k_interpolationMethod };
    static int offsets[] = { 8, 12, 16, 20, 24, 28, 32, 40, 48, 52, 56, 57 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 12);
    {
    igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
    metaField->_metaObject = (int)Gap::Core::igUnsignedShortList::getClassTypeLazy();
    }
    {
    igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
    metaField->_metaObject = (int)Gap::Core::igUnsignedShortList::getClassTypeLazy();
    }
    {
    igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
    metaField->_metaObject = (int)Gap::Core::igUnsignedShortList::getClassTypeLazy();
    }
    {
    igUnsignedLongMetaField *metaField = (igUnsignedLongMetaField *)igMetaObject_GetFieldAt(metaObject, start + 7);
    metaField->setDefault(0xFFFFFFFFFFFFFFFFULL);
    }
    {
    igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 8);
    metaField->setDefault(0);
    *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())igMetaEnum_GetEmpty;
    }
    {
    igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 9);
    metaField->setDefault(1);
    metaField->_persistent = 0;
    }
    {
    igUnsignedCharMetaField *metaField = (igUnsignedCharMetaField *)igMetaObject_GetFieldAt(metaObject, start + 10);
    metaField->setDefault(0);
    }
    {
    igUnsignedCharArrayMetaField *metaField = (igUnsignedCharArrayMetaField *)igMetaObject_GetFieldAt(metaObject, start + 11);
    metaField->_num = 3;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}
