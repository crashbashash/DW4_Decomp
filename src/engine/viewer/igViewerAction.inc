namespace Gap {
namespace Viewer {

igMetaObject *igViewerAction::_Meta;
igMetaField *igViewerAction::k_ref;
igMetaField *igViewerAction::k_function;
}
}

igViewerAction *igViewerAction_Create(int allocator) {
    Gap::Viewer::igViewerAction::arkRegister();
    return (igViewerAction *)igMetaObject_CreateInstance(Gap::Viewer::igViewerAction::getClassMeta(), (igMemoryPoolView *)allocator);
}

namespace Gap {
namespace Viewer {

igMetaObject *igViewerAction::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igViewerAction::retrieveVTablePointer()
{
    igViewerAction temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igViewerAction::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igViewerAction::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { igViewerSceneInfoManager_EnsureRegistered, 0 };

    ViewerLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Gui::igAction::arkRegisterInternal,
        Gap::Gui::igAction::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igViewerAction",
        sizeof(igViewerAction),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igViewerAction::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, (FieldFactory)Gap::Core::igStructMetaField::_instantiateFromPool };
    static const char *names[] = { "_ref", "_function" };
    static igMetaField **enumStorage[] = { &k_ref, &k_function };
    static int offsets[] = { 8, 12 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 2);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)igViewerSceneInfoManager_GetOrCreateMetaObject();
        metaField->_refCounted = 0;
    }
    {
        igStructMetaField *metaField = (igStructMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_size = 12;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

