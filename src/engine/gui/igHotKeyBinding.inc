namespace Gap {
namespace Gui {

igMetaObject *igHotKeyBinding::_Meta;
igMetaField *igHotKeyBinding::k_key;
igMetaField *igHotKeyBinding::k_button;
igMetaField *igHotKeyBinding::k_action;

igHotKeyBinding *igHotKeyBinding::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igHotKeyBinding *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igHotKeyBinding::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igHotKeyBinding::retrieveVTablePointer()
{
    igHotKeyBinding temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igHotKeyBinding::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igHotKeyBinding::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Gui::igAction::arkRegister, 0 };

    GuiLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igHotKeyBinding",
        sizeof(igHotKeyBinding),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}
}
}

namespace Gap {
namespace Gui {

void igHotKeyBinding::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igEnumMetaField_Create, igEnumMetaField_Create, igObjectRefMetaField_Create };
    static const char *names[] = { "_key", "_button", "_action" };
    static igMetaField **enumStorage[] = { &k_key, &k_button, &k_action };
    static int offsets[] = { 8, 12, 16 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 3);
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->setDefault(0);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())FUN_00145eb0;
    }
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->setDefault(32);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())FUN_00146850;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->_metaObject = (int)Gap::Gui::igAction::getClassTypeLazy();
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

