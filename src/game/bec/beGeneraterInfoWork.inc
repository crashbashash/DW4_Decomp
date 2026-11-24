namespace Gap {
namespace Bec {

igMetaObject *beGeneraterInfoWork::_Meta;
igMetaField *beGeneraterInfoWork::k_isSystemFreeze;
igMetaField *beGeneraterInfoWork::k_isFreeze;
igMetaField *beGeneraterInfoWork::k_playerCount;
igMetaField *beGeneraterInfoWork::k_nokoriKazu;
igMetaField *beGeneraterInfoWork::k_enemyRamList;
igMetaField *beGeneraterInfoWork::k_genePoint;
igMetaField *beGeneraterInfoWork::k_geneEnemyName;
igMetaField *beGeneraterInfoWork::k_geneEnemyRecNo;
igMetaField *beGeneraterInfoWork::k_geneEnemyMHp;

beGeneraterInfoWork *beGeneraterInfoWork::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (beGeneraterInfoWork *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *beGeneraterInfoWork::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *beGeneraterInfoWork::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *beGeneraterInfoWork::retrieveVTablePointer()
{
    beGeneraterInfoWork temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void beGeneraterInfoWork::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *beGeneraterInfoWork::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { beBaseInfoRamList_EnsureRegistered, 0 };

    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "beGeneraterInfoWork",
        sizeof(beGeneraterInfoWork),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void beGeneraterInfoWork::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igBoolMetaField_Create, igBoolMetaField_Create, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, igObjectRefMetaField_Create, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, igStringMetaField_Create, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool };
    static const char *names[] = { "_isSystemFreeze", "_isFreeze", "_playerCount", "_nokoriKazu", "_enemyRamList", "_genePoint", "_geneEnemyName", "_geneEnemyRecNo", "_geneEnemyMHp" };
    static igMetaField **enumStorage[] = { &k_isSystemFreeze, &k_isFreeze, &k_playerCount, &k_nokoriKazu, &k_enemyRamList, &k_genePoint, &k_geneEnemyName, &k_geneEnemyRecNo, &k_geneEnemyMHp };
    static int offsets[] = { 8, 9, 12, 16, 20, 24, 28, 32, 36 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 9);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 4);
        metaField->_metaObject = (int)beBaseInfoRamList_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

