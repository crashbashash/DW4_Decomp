namespace Gap {
namespace Gui {

igMetaObject *igFieldSynchronizer::_Meta;
igMetaField *igFieldSynchronizer::k_views;

igFieldSynchronizer *igFieldSynchronizer::_instantiateFromPool(igMemoryPoolView *pool) {
    arkRegister();
    return (igFieldSynchronizer *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igFieldSynchronizer::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igFieldSynchronizer::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igFieldSynchronizer::retrieveVTablePointer()
{
    igFieldSynchronizer temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igFieldSynchronizer::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igFieldSynchronizer::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Gui::igFieldChangeViewList::arkRegister, 0 };

    GuiLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igFieldSynchronizer",
        sizeof(igFieldSynchronizer),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igFieldSynchronizer::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create };
    static const char *names[] = { "_views" };
    static igMetaField **enumStorage[] = { &k_views };
    static int offsets[] = { 8 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 1);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)Gap::Gui::igFieldChangeViewList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

