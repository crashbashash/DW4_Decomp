namespace Gap {
namespace Bec {

igMetaObject *beSvPlatBaseData::_Meta;
igMetaField *beSvPlatBaseData::k_connectMax;
igMetaField *beSvPlatBaseData::k_slotList;
igMetaField *beSvPlatBaseData::k_dataSize;
igMetaField *beSvPlatBaseData::k_memNeed;

igMetaObject *beSvPlatBaseData::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *beSvPlatBaseData::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *beSvPlatBaseData::retrieveVTablePointer()
{
    beSvPlatBaseData temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void beSvPlatBaseData::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *beSvPlatBaseData::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Bec::beSvSlotDataList::arkRegister, 0 };

    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "beSvPlatBaseData",
        sizeof(beSvPlatBaseData),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void beSvPlatBaseData::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, igObjectRefMetaField_Create, igUnsignedIntMetaField_Create, igUnsignedIntMetaField_Create };
    static const char *names[] = { "_connectMax", "_slotList", "_dataSize", "_memNeed" };
    static igMetaField **enumStorage[] = { &k_connectMax, &k_slotList, &k_dataSize, &k_memNeed };
    static int offsets[] = { 8, 12, 16, 20 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 4);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_metaObject = (int)Gap::Bec::beSvSlotDataList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

