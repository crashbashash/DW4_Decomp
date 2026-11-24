namespace Gap {
namespace Bec {

igMetaObject *beGeneraterPlayerData::_Meta;
igMetaField *beGeneraterPlayerData::k_geneCount;
igMetaField *beGeneraterPlayerData::k_geneMaxCount;
igMetaField *beGeneraterPlayerData::k_itemDataList;
igMetaField *beGeneraterPlayerData::k_itemLastDataList;

igMetaObject *beGeneraterPlayerData::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *beGeneraterPlayerData::retrieveVTablePointer()
{
    beGeneraterPlayerData temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void beGeneraterPlayerData::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *beGeneraterPlayerData::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { beGeneraterItemDataList_EnsureRegistered, 0 };

    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "beGeneraterPlayerData",
        sizeof(beGeneraterPlayerData),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void beGeneraterPlayerData::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, igObjectRefMetaField_Create, igObjectRefMetaField_Create };
    static const char *names[] = { "_geneCount", "_geneMaxCount", "_itemDataList", "_itemLastDataList" };
    static igMetaField **enumStorage[] = { &k_geneCount, &k_geneMaxCount, &k_itemDataList, &k_itemLastDataList };
    static int offsets[] = { 8, 12, 16, 20 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 4);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->_metaObject = (int)beGeneraterItemDataList_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->_metaObject = (int)beGeneraterItemDataList_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

