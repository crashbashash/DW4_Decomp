namespace Gap {
namespace Bec {

igMetaObject *beSvDeliver::_Meta;
igMetaField *beSvDeliver::k_actConnect;
igMetaField *beSvDeliver::k_targetConnect;
igMetaField *beSvDeliver::k_saveVer;
igMetaField *beSvDeliver::k_result;
igMetaField *beSvDeliver::k_operate;
igMetaField *beSvDeliver::k_memCapa;
igMetaField *beSvDeliver::k_fileCapa;
igMetaField *beSvDeliver::k_useMtap;
igMetaField *beSvDeliver::k_chgUseMtap;
igMetaField *beSvDeliver::k_isMemCapaOK;
igMetaField *beSvDeliver::k_isfileCapaOK;
igMetaField *beSvDeliver::k_isEndOperat;
igMetaField *beSvDeliver::k_freeSizeList;
igMetaField *beSvDeliver::k_freeFileList;
igMetaField *beSvDeliver::k_formatList;
igMetaField *beSvDeliver::k_totalSizeList;
igMetaField *beSvDeliver::k_gameData;
igMetaField *beSvDeliver::k_platformData;

igMetaObject *beSvDeliver::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *beSvDeliver::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *beSvDeliver::retrieveVTablePointer()
{
    beSvDeliver temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void beSvDeliver::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *beSvDeliver::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Core::igIntList::arkRegister, Gap::Bec::beSaveDataDeliver::arkRegister, Gap::Bec::beSvPlatBaseData::arkRegister, 0 };

    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "beSvDeliver",
        sizeof(beSvDeliver),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void beSvDeliver::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, igCharMetaField_Create, igCharMetaField_Create, igBoolMetaField_Create, igBoolMetaField_Create, igBoolMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create };
    static const char *names[] = { "_actConnect", "_targetConnect", "_saveVer", "_result", "_operate", "_memCapa", "_fileCapa", "_useMtap", "_chgUseMtap", "_isMemCapaOK", "_isfileCapaOK", "_isEndOperat", "_freeSizeList", "_freeFileList", "_formatList", "_totalSizeList", "_gameData", "_platformData" };
    static igMetaField **enumStorage[] = { &k_actConnect, &k_targetConnect, &k_saveVer, &k_result, &k_operate, &k_memCapa, &k_fileCapa, &k_useMtap, &k_chgUseMtap, &k_isMemCapaOK, &k_isfileCapaOK, &k_isEndOperat, &k_freeSizeList, &k_freeFileList, &k_formatList, &k_totalSizeList, &k_gameData, &k_platformData };
    static int offsets[] = { 12, 16, 20, 24, 28, 32, 36, 40, 41, 42, 43, 44, 48, 52, 56, 60, 8, 64 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 18);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)Gap::Core::igIntList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igCharMetaField *metaField = (igCharMetaField *)igMetaObject_GetFieldAt(metaObject, start + 7);
        metaField->setDefault(-1);
    }
    {
        igCharMetaField *metaField = (igCharMetaField *)igMetaObject_GetFieldAt(metaObject, start + 8);
        metaField->setDefault(0);
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 12);
        metaField->_metaObject = (int)Gap::Core::igIntList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 13);
        metaField->_metaObject = (int)Gap::Core::igIntList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 14);
        metaField->_metaObject = (int)Gap::Core::igIntList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 15);
        metaField->_metaObject = (int)Gap::Core::igIntList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 16);
        metaField->_metaObject = (int)Gap::Bec::beSaveDataDeliver::getClassTypeLazy();
        metaField->_refCounted = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 17);
        metaField->_metaObject = (int)Gap::Bec::beSvPlatBaseData::getClassTypeLazy();
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

