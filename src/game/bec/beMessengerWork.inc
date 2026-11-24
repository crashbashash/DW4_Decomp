namespace Gap {
namespace Bec {

igMetaObject *beMessengerWork::_Meta;
igMetaField *beMessengerWork::k_groupName;
igMetaField *beMessengerWork::k_infoName;
igMetaField *beMessengerWork::k_ramNo;
igMetaField *beMessengerWork::k_message;
igMetaField *beMessengerWork::k_findRamNoList;
igMetaField *beMessengerWork::k_findRamList;

beMessengerWork *beMessengerWork::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (beMessengerWork *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *beMessengerWork::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *beMessengerWork::retrieveVTablePointer()
{
    beMessengerWork temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void beMessengerWork::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *beMessengerWork::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Core::igIntList::arkRegister, beBaseInfoRamList_EnsureRegistered, 0 };

    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "beMessengerWork",
        sizeof(beMessengerWork),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void beMessengerWork::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igStringMetaField_Create, igStringMetaField_Create, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, igStringMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create };
    static const char *names[] = { "_groupName", "_infoName", "_ramNo", "_message", "_findRamNoList", "_findRamList" };
    static igMetaField **enumStorage[] = { &k_groupName, &k_infoName, &k_ramNo, &k_message, &k_findRamNoList, &k_findRamList };
    static int offsets[] = { 8, 12, 16, 20, 24, 28 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 6);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 4);
        metaField->_metaObject = (int)Gap::Core::igIntList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 5);
        metaField->_metaObject = (int)beBaseInfoRamList_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

