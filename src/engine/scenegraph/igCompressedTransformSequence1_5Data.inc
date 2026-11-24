namespace Gap {
namespace Sg {

igMetaObject *igCompressedTransformSequence1_5Data::_Meta;
igMetaField *igCompressedTransformSequence1_5Data::k_compressedTranslationList;
igMetaField *igCompressedTransformSequence1_5Data::k_compressedQuatList;
igMetaField *igCompressedTransformSequence1_5Data::k_compressedScaleList;
igMetaField *igCompressedTransformSequence1_5Data::k_compressedTimeList;
igMetaField *igCompressedTransformSequence1_5Data::k_translationBase;
igMetaField *igCompressedTransformSequence1_5Data::k_translationRange;
igMetaField *igCompressedTransformSequence1_5Data::k_quatBase;
igMetaField *igCompressedTransformSequence1_5Data::k_quatRange;
igMetaField *igCompressedTransformSequence1_5Data::k_scaleBase;
igMetaField *igCompressedTransformSequence1_5Data::k_scaleRange;

igMetaObject *igCompressedTransformSequence1_5Data::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igCompressedTransformSequence1_5Data::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igCompressedTransformSequence1_5Data::retrieveVTablePointer()
{
    igCompressedTransformSequence1_5Data temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igCompressedTransformSequence1_5Data::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igCompressedTransformSequence1_5Data::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Core::igUnsignedShortList::arkRegister, 0 };

    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igCompressedTransformSequence1_5Data",
        sizeof(igCompressedTransformSequence1_5Data),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igCompressedTransformSequence1_5Data::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool };
    static const char *names[] = { "_compressedTranslationList", "_compressedQuatList", "_compressedScaleList", "_compressedTimeList", "_translationBase", "_translationRange", "_quatBase", "_quatRange", "_scaleBase", "_scaleRange" };
    static igMetaField **enumStorage[] = { &k_compressedTranslationList, &k_compressedQuatList, &k_compressedScaleList, &k_compressedTimeList, &k_translationBase, &k_translationRange, &k_quatBase, &k_quatRange, &k_scaleBase, &k_scaleRange };
    static int offsets[] = { 8, 12, 16, 20, 24, 28, 32, 36, 40, 44 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 10);
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
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->_metaObject = (int)Gap::Core::igUnsignedShortList::getClassTypeLazy();
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

