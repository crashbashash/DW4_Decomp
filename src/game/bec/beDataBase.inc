namespace Gap {
namespace Bec {

igMetaObject *beDataBase::_Meta;
igMetaField *beDataBase::k_charOffsetList;
igMetaField *beDataBase::k_charData;
igMetaField *beDataBase::k_shortOffsetList;
igMetaField *beDataBase::k_shortData;
igMetaField *beDataBase::k_intOffsetList;
igMetaField *beDataBase::k_intData;
igMetaField *beDataBase::k_floatOffsetList;
igMetaField *beDataBase::k_floatData;
igMetaField *beDataBase::k_boolOffsetList;
igMetaField *beDataBase::k_boolData;
igMetaField *beDataBase::k_stringOffsetList;
igMetaField *beDataBase::k_stringData;

igMetaObject *beDataBase::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *beDataBase::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *beDataBase::retrieveVTablePointer()
{
    beDataBase temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void beDataBase::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *beDataBase::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { igNamedObjectList_EnsureRegistered, Gap::Core::igCharList::arkRegister, Gap::Core::igShortList::arkRegister, Gap::Core::igIntList::arkRegister, Gap::Core::igFloatList::arkRegister, Gap::Core::igBoolList::arkRegister, 0 };

    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "beDataBase",
        sizeof(beDataBase),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void beDataBase::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create };
    static const char *names[] = { "_charOffsetList", "_charData", "_shortOffsetList", "_shortData", "_intOffsetList", "_intData", "_floatOffsetList", "_floatData", "_boolOffsetList", "_boolData", "_stringOffsetList", "_stringData" };
    static igMetaField **enumStorage[] = { &k_charOffsetList, &k_charData, &k_shortOffsetList, &k_shortData, &k_intOffsetList, &k_intData, &k_floatOffsetList, &k_floatData, &k_boolOffsetList, &k_boolData, &k_stringOffsetList, &k_stringData };
    static int offsets[] = { 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 12);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)igNamedObjectList_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_metaObject = (int)Gap::Core::igCharList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->_metaObject = (int)igNamedObjectList_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->_metaObject = (int)Gap::Core::igShortList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 4);
        metaField->_metaObject = (int)igNamedObjectList_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 5);
        metaField->_metaObject = (int)Gap::Core::igIntList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 6);
        metaField->_metaObject = (int)igNamedObjectList_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 7);
        metaField->_metaObject = (int)Gap::Core::igFloatList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 8);
        metaField->_metaObject = (int)igNamedObjectList_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 9);
        metaField->_metaObject = (int)Gap::Core::igBoolList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 10);
        metaField->_metaObject = (int)igNamedObjectList_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 11);
        metaField->_metaObject = (int)igNamedObjectList_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

