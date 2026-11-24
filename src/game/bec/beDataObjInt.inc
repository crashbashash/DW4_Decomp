namespace Gap {
namespace Bec {

igMetaObject *beDataObjInt::_Meta;
igMetaField *beDataObjInt::k_data;

beDataObjInt *beDataObjInt::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (beDataObjInt *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *beDataObjInt::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *beDataObjInt::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *beDataObjInt::retrieveVTablePointer()
{
    beDataObjInt temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void beDataObjInt::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *beDataObjInt::arkRegisterInternal()
{
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igNamedObject::arkRegisterInternal,
        Gap::Core::igNamedObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "beDataObjInt",
        sizeof(beDataObjInt),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void beDataObjInt::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool };
    static const char *names[] = { "_data" };
    static igMetaField **enumStorage[] = { &k_data };
    static int offsets[] = { 12 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 1);
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

