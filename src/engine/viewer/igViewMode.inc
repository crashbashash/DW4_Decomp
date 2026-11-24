namespace Gap {
namespace Viewer {

igMetaObject *igViewMode::_Meta;
igMetaField *igViewMode::k_inverseMatrix;

igMetaObject *igViewMode::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igViewMode::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igViewMode::retrieveVTablePointer()
{
    igViewMode temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igViewMode::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igViewMode::arkRegisterInternal()
{
    ViewerLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Gui::igView::arkRegisterInternal,
        Gap::Gui::igView::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igViewMode",
        sizeof(igViewMode),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void igViewMode::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { (FieldFactory)Gap::Math::igMatrix44fMetaField::_instantiateFromPool };
    static const char *names[] = { "_inverseMatrix" };
    static igMetaField **enumStorage[] = { &k_inverseMatrix };
    static int offsets[] = { 12 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 1);
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

