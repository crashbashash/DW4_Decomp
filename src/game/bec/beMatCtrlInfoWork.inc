namespace Gap {
namespace Bec {

igMetaObject *beMatCtrlInfoWork::_Meta;
igMetaField *beMatCtrlInfoWork::k_runFlagList;
igMetaField *beMatCtrlInfoWork::k_matOnPlLists;

beMatCtrlInfoWork *beMatCtrlInfoWork::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (beMatCtrlInfoWork *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *beMatCtrlInfoWork::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *beMatCtrlInfoWork::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *beMatCtrlInfoWork::retrieveVTablePointer()
{
    beMatCtrlInfoWork temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void beMatCtrlInfoWork::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *beMatCtrlInfoWork::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Core::igBoolList::arkRegister, igIntListList_EnsureRegistered, 0 };

    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "beMatCtrlInfoWork",
        sizeof(beMatCtrlInfoWork),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void beMatCtrlInfoWork::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, igObjectRefMetaField_Create };
    static const char *names[] = { "_runFlagList", "_matOnPlLists" };
    static igMetaField **enumStorage[] = { &k_runFlagList, &k_matOnPlLists };
    static int offsets[] = { 8, 12 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 2);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)Gap::Core::igBoolList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_metaObject = (int)igIntListList_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

