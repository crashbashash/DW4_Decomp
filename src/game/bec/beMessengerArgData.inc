namespace Gap {
namespace Bec {

igMetaObject *beMessengerArgData::_Meta;
igMetaField *beMessengerArgData::k_isRunCheck;
igMetaField *beMessengerArgData::k_debugString;
igMetaField *beMessengerArgData::k_boolList;
igMetaField *beMessengerArgData::k_intList;
igMetaField *beMessengerArgData::k_floatList;
igMetaField *beMessengerArgData::k_longList;
igMetaField *beMessengerArgData::k_vec3fList;
igMetaField *beMessengerArgData::k_matrix44fList;
igMetaField *beMessengerArgData::k_objectList;
igMetaField *beMessengerArgData::k_stringList;

beMessengerArgData *beMessengerArgData::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (beMessengerArgData *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *beMessengerArgData::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *beMessengerArgData::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *beMessengerArgData::retrieveVTablePointer()
{
    beMessengerArgData temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void beMessengerArgData::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *beMessengerArgData::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Core::igBoolList::arkRegister, Gap::Core::igIntList::arkRegister, Gap::Core::igFloatList::arkRegister, Gap::Core::igLongList::arkRegister, igVec3fList_EnsureRegistered, igMatrix44fList_EnsureRegistered, Gap::Core::igObjectList::arkRegister, igStringRefList_EnsureRegistered, 0 };

    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "beMessengerArgData",
        sizeof(beMessengerArgData),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void beMessengerArgData::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igBoolMetaField_Create, igStringMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create };
    static const char *names[] = { "_isRunCheck", "_debugString", "_boolList", "_intList", "_floatList", "_longList", "_vec3fList", "_matrix44fList", "_objectList", "_stringList" };
    static igMetaField **enumStorage[] = { &k_isRunCheck, &k_debugString, &k_boolList, &k_intList, &k_floatList, &k_longList, &k_vec3fList, &k_matrix44fList, &k_objectList, &k_stringList };
    static int offsets[] = { 8, 12, 16, 20, 24, 28, 32, 36, 40, 44 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 10);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->_metaObject = (int)Gap::Core::igBoolList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->_metaObject = (int)Gap::Core::igIntList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 4);
        metaField->_metaObject = (int)Gap::Core::igFloatList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 5);
        metaField->_metaObject = (int)Gap::Core::igLongList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 6);
        metaField->_metaObject = (int)igVec3fList_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 7);
        metaField->_metaObject = (int)igMatrix44fList_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 8);
        metaField->_metaObject = (int)Gap::Core::igObjectList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 9);
        metaField->_metaObject = (int)igStringRefList_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

