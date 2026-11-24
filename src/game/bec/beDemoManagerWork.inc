namespace Gap {
namespace Bec {

igMetaObject *beDemoManagerWork::_Meta;
igMetaField *beDemoManagerWork::k_advancec;
igMetaField *beDemoManagerWork::k_keepMesList;

beDemoManagerWork *beDemoManagerWork::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (beDemoManagerWork *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *beDemoManagerWork::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *beDemoManagerWork::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *beDemoManagerWork::retrieveVTablePointer()
{
    beDemoManagerWork temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void beDemoManagerWork::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *beDemoManagerWork::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Bec::beDemoKeepMesList::arkRegister, 0 };

    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "beDemoManagerWork",
        sizeof(beDemoManagerWork),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void beDemoManagerWork::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, igObjectRefMetaField_Create };
    static const char *names[] = { "_advancec", "_keepMesList" };
    static igMetaField **enumStorage[] = { &k_advancec, &k_keepMesList };
    static int offsets[] = { 8, 12 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 2);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_metaObject = (int)Gap::Bec::beDemoKeepMesList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

