namespace Gap {
namespace Bec {

igMetaObject *beCriSndf::_Meta;
igMetaField *beCriSndf::k_req;
igMetaField *beCriSndf::k_seq;
igMetaField *beCriSndf::k_isPlaying;

beCriSndf *beCriSndf::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (beCriSndf *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *beCriSndf::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *beCriSndf::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *beCriSndf::retrieveVTablePointer()
{
    beCriSndf temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void beCriSndf::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *beCriSndf::arkRegisterInternal()
{
    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "beCriSndf",
        sizeof(beCriSndf),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void beCriSndf::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igLongMetaField::_instantiateFromPool, igBoolMetaField_Create };
    static const char *names[] = { "_req", "_seq", "_isPlaying" };
    static igMetaField **enumStorage[] = { &k_req, &k_seq, &k_isPlaying };
    static int offsets[] = { 8, 16, 24 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 3);
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

