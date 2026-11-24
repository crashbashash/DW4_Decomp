namespace Gap {
namespace Viewer {

igMetaObject *igViewerSceneInfoManagerController::_Meta;
igMetaField *igViewerSceneInfoManagerController::k_application;
igMetaField *igViewerSceneInfoManagerController::k_viewerRenderer;

igMetaObject *igViewerSceneInfoManagerController::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igViewerSceneInfoManagerController::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igViewerSceneInfoManagerController::retrieveVTablePointer()
{
    igViewerSceneInfoManagerController temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igViewerSceneInfoManagerController::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igViewerSceneInfoManagerController::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { igViewerSceneInfoManager_EnsureRegistered, igViewerRenderer_EnsureRegistered, 0 };

    ViewerLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Gui::igView::arkRegisterInternal,
        Gap::Gui::igView::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igViewerSceneInfoManagerController",
        sizeof(igViewerSceneInfoManagerController),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igViewerSceneInfoManagerController::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, igObjectRefMetaField_Create };
    static const char *names[] = { "_application", "_viewerRenderer" };
    static igMetaField **enumStorage[] = { &k_application, &k_viewerRenderer };
    static int offsets[] = { 12, 16 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 2);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)igViewerSceneInfoManager_GetOrCreateMetaObject();
        metaField->_refCounted = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_metaObject = (int)igViewerRenderer_GetOrCreateMetaObject();
        metaField->_refCounted = 0;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

