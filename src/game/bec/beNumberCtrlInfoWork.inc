namespace Gap {
namespace Bec {

igMetaObject *beNumberCtrlInfoWork::_Meta;
igMetaField *beNumberCtrlInfoWork::k_dispNum;
igMetaField *beNumberCtrlInfoWork::k_realNum;
igMetaField *beNumberCtrlInfoWork::k_changeNum;

beNumberCtrlInfoWork *beNumberCtrlInfoWork::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (beNumberCtrlInfoWork *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *beNumberCtrlInfoWork::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *beNumberCtrlInfoWork::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *beNumberCtrlInfoWork::retrieveVTablePointer()
{
    beNumberCtrlInfoWork temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void beNumberCtrlInfoWork::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *beNumberCtrlInfoWork::arkRegisterInternal()
{
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "beNumberCtrlInfoWork",
        sizeof(beNumberCtrlInfoWork),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void beNumberCtrlInfoWork::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool };
    static const char *names[] = { "_dispNum", "_realNum", "_changeNum" };
    static igMetaField **enumStorage[] = { &k_dispNum, &k_realNum, &k_changeNum };
    static int offsets[] = { 8, 12, 16 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 3);
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->setDefault(-1);
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->setDefault(-1);
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->setDefault(-1);
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

