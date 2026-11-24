namespace Gap {
namespace Bec {

igMetaObject *beWaterMove::_Meta;
igMetaField *beWaterMove::k_baseTime;
igMetaField *beWaterMove::k_elapseTime;
igMetaField *beWaterMove::k_maxTime;
igMetaField *beWaterMove::k_targetData;
igMetaField *beWaterMove::k_dataList;

igMetaObject *beWaterMove::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *beWaterMove::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *beWaterMove::retrieveVTablePointer()
{
    beWaterMove temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void beWaterMove::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *beWaterMove::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Bec::beWaterMoveDataList::arkRegister, 0 };

    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "beWaterMove",
        sizeof(beWaterMove),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void beWaterMove::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { (FieldFactory)Gap::Core::igLongMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igLongMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igLongMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, igObjectRefMetaField_Create };
    static const char *names[] = { "_baseTime", "_elapseTime", "_maxTime", "_targetData", "_dataList" };
    static igMetaField **enumStorage[] = { &k_baseTime, &k_elapseTime, &k_maxTime, &k_targetData, &k_dataList };
    static int offsets[] = { 8, 16, 24, 32, 36 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 5);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 4);
        metaField->_metaObject = (int)Gap::Bec::beWaterMoveDataList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

