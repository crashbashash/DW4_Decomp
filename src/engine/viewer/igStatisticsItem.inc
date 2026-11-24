namespace Gap {
namespace Viewer {

igMetaObject *igStatisticsItem::_Meta;
igMetaField *igStatisticsItem::k_value;
igMetaField *igStatisticsItem::k_maximumValue;
igMetaField *igStatisticsItem::k_useMultiplier;
igMetaField *igStatisticsItem::k_text;
igMetaField *igStatisticsItem::k_numberFormat;
igMetaField *igStatisticsItem::k_visible;
igMetaField *igStatisticsItem::k_displayComponent;
igMetaField *igStatisticsItem::k_aspect;
igMetaField *igStatisticsItem::k_textElement;
igMetaField *igStatisticsItem::k_manager;
igMetaField *igStatisticsItem::k_statId;
igMetaField *igStatisticsItem::k_otherId;

igMetaObject *igStatisticsItem::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igStatisticsItem::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igStatisticsItem::retrieveVTablePointer()
{
    igStatisticsItem temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igStatisticsItem::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igStatisticsItem::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { igGuiComponent_EnsureRegistered, igDefaultAspect_EnsureRegistered, igTextElement_EnsureRegistered, Gap::Viewer::igViewerStatisticsManager::arkRegister, 0 };

    ViewerLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Gui::igView::arkRegisterInternal,
        Gap::Gui::igView::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igStatisticsItem",
        sizeof(igStatisticsItem),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igStatisticsItem::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, igBoolMetaField_Create, igStringMetaField_Create, igStringMetaField_Create, igBoolMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igEnumMetaField_Create, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool };
    static const char *names[] = { "_value", "_maximumValue", "_useMultiplier", "_text", "_numberFormat", "_visible", "_displayComponent", "_aspect", "_textElement", "_manager", "_statId", "_otherId" };
    static igMetaField **enumStorage[] = { &k_value, &k_maximumValue, &k_useMultiplier, &k_text, &k_numberFormat, &k_visible, &k_displayComponent, &k_aspect, &k_textElement, &k_manager, &k_statId, &k_otherId };
    static int offsets[] = { 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 12);
    {
        igFloatMetaField *metaField = (igFloatMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->setDefault(0.0f);
    }
    {
        igFloatMetaField *metaField = (igFloatMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->setDefault(-1.0f);
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 6);
        metaField->_metaObject = (int)igGuiComponent_GetOrCreateMetaObject();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 7);
        metaField->_metaObject = (int)igDefaultAspect_GetOrCreateMetaObject();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 8);
        metaField->_metaObject = (int)igTextElement_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 9);
        metaField->_metaObject = (int)Gap::Viewer::igViewerStatisticsManager::getClassTypeLazy();
        metaField->_refCounted = 0;
    }
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 10);
        metaField->setDefault(-1);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())IG_GFX_STATISTIC_GetMetaEnum;
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 11);
        metaField->setDefault(-1);
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

