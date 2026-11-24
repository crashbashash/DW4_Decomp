namespace Gap {
namespace Viewer {

igMetaObject *igViewManager::_Meta;
igMetaField *igViewManager::k_viewMode;
igMetaField *igViewManager::k_viewModel;
igMetaField *igViewManager::k_synchronizers;
igMetaField *igViewManager::k_homeMatrix;

igMetaObject *igViewManager::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igViewManager::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igViewManager::retrieveVTablePointer()
{
    igViewManager temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igViewManager::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igViewManager::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Viewer::igViewMode::arkRegister, Gap::Viewer::igViewModel::arkRegister, Gap::Core::igObjectList::arkRegister, 0 };

    ViewerLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Gui::igEventReceiver::arkRegisterInternal,
        Gap::Gui::igEventReceiver::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igViewManager",
        sizeof(igViewManager),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igViewManager::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, (FieldFactory)Gap::Math::igMatrix44fMetaField::_instantiateFromPool };
    static const char *names[] = { "_viewMode", "_viewModel", "_synchronizers", "_homeMatrix" };
    static igMetaField **enumStorage[] = { &k_viewMode, &k_viewModel, &k_synchronizers, &k_homeMatrix };
    static int offsets[] = { 8, 12, 16, 20 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 4);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)Gap::Viewer::igViewMode::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_metaObject = (int)Gap::Viewer::igViewModel::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->_metaObject = (int)Gap::Core::igObjectList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

