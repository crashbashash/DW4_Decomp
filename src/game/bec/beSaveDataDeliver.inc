namespace Gap {
namespace Bec {

igMetaObject *beSaveDataDeliver::_Meta;
igMetaField *beSaveDataDeliver::k_size;
igMetaField *beSaveDataDeliver::k_data;

igMetaObject *beSaveDataDeliver::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *beSaveDataDeliver::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *beSaveDataDeliver::retrieveVTablePointer()
{
    beSaveDataDeliver temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void beSaveDataDeliver::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *beSaveDataDeliver::arkRegisterInternal()
{
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "beSaveDataDeliver",
        sizeof(beSaveDataDeliver),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void beSaveDataDeliver::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, igMemoryRefMetaField_Create };
    static const char *names[] = { "_size", "_data" };
    static igMetaField **enumStorage[] = { &k_size, &k_data };
    static int offsets[] = { 12, 8 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 2);
    {
        igMemoryRefMetaField *metaField = (igMemoryRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_memType = (int)Gap::Core::igCharMetaField::getMetaField();
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

