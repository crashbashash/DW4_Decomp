namespace Gap {
namespace Viewer {

igMetaObject *igViewerGuiFactory::_Meta;
igMetaField *igViewerGuiFactory::k_menuBackColor;
igMetaField *igViewerGuiFactory::k_menuItemForeColor;
igMetaField *igViewerGuiFactory::k_menuMarkColor;
igMetaField *igViewerGuiFactory::k_iconBackColor;
igMetaField *igViewerGuiFactory::k_bigIconColor;
igMetaField *igViewerGuiFactory::k_bigIconHighlightColor;
igMetaField *igViewerGuiFactory::k_smallIconOnOffColor;
igMetaField *igViewerGuiFactory::k_font;

igMetaObject *igViewerGuiFactory::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igViewerGuiFactory::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igViewerGuiFactory::retrieveVTablePointer()
{
    igViewerGuiFactory temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igViewerGuiFactory::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igViewerGuiFactory::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { igBasicColorChanger_RunStaticInit, igOnOffColorChanger_RunStaticInit, igBitmapFont_RunStaticInit, 0 };

    ViewerLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igViewerGuiFactory",
        sizeof(igViewerGuiFactory),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igViewerGuiFactory::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create };
    static const char *names[] = { "_menuBackColor", "_menuItemForeColor", "_menuMarkColor", "_iconBackColor", "_bigIconColor", "_bigIconHighlightColor", "_smallIconOnOffColor", "_font" };
    static igMetaField **enumStorage[] = { &k_menuBackColor, &k_menuItemForeColor, &k_menuMarkColor, &k_iconBackColor, &k_bigIconColor, &k_bigIconHighlightColor, &k_smallIconOnOffColor, &k_font };
    static int offsets[] = { 8, 12, 16, 20, 24, 28, 32, 36 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 8);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)igBasicColorChanger_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_metaObject = (int)igBasicColorChanger_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->_metaObject = (int)igOnOffColorChanger_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->_metaObject = (int)igBasicColorChanger_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 4);
        metaField->_metaObject = (int)igOnOffColorChanger_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 5);
        metaField->_metaObject = (int)igOnOffColorChanger_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 6);
        metaField->_metaObject = (int)igOnOffColorChanger_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 7);
        metaField->_metaObject = (int)igBitmapFont_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

