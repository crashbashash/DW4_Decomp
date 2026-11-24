namespace Gap {
namespace Gui {

igMetaObject *igGuiSystem::_Meta;
igMetaField *igGuiSystem::k_renderer;
igMetaField *igGuiSystem::k_model;
igMetaField *igGuiSystem::k_viewList;
igMetaField *igGuiSystem::k_root;
igMetaField *igGuiSystem::k_mouseCursor;
igMetaField *igGuiSystem::k_mouseCursorTransform;
igMetaField *igGuiSystem::k_mouseCursorVisible;

igMetaObject *igGuiSystem::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igGuiSystem::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igGuiSystem::retrieveVTablePointer()
{
    igGuiSystem temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}
}
}

namespace Gap {
namespace Gui {

void igGuiSystem::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igGuiSystem::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { igGuiSystemRenderer_RunStaticInit, Gap::Gui::igGuiSystemModel::arkRegister, Gap::Gui::igViewList::arkRegister, Gap::Sg::igAttrSet::arkRegister, Gap::Gui::igMouseCursor::arkRegister, Gap::Sg::igTransform::arkRegister, 0 };

    GuiLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Gui::igEventReceiver::arkRegisterInternal,
        Gap::Gui::igEventReceiver::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igGuiSystem",
        sizeof(igGuiSystem),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igGuiSystem::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igBoolMetaField_Create };
    static const char *names[] = { "_renderer", "_model", "_viewList", "_root", "_mouseCursor", "_mouseCursorTransform", "_mouseCursorVisible" };
    static igMetaField **enumStorage[] = { &k_renderer, &k_model, &k_viewList, &k_root, &k_mouseCursor, &k_mouseCursorTransform, &k_mouseCursorVisible };
    static int offsets[] = { 8, 12, 16, 20, 24, 28, 32 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 7);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)igGuiSystemRenderer_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_metaObject = (int)Gap::Gui::igGuiSystemModel::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->_metaObject = (int)Gap::Gui::igViewList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->_metaObject = (int)Gap::Sg::igAttrSet::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 4);
        metaField->_metaObject = (int)Gap::Gui::igMouseCursor::getClassTypeLazy();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 5);
        metaField->_metaObject = (int)Gap::Sg::igTransform::getClassTypeLazy();
        metaField->_construct = 1;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

