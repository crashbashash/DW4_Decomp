namespace Gap {
namespace Viewer {

igMetaObject *igViewerStatisticsManager::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igViewerStatisticsManager::retrieveVTablePointer()
{
    igViewerStatisticsManager temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igViewerStatisticsManager::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igViewerStatisticsManager::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Viewer::igStatisticsItemList::arkRegister, Gap::Gfx::igVisualContext::arkRegister, Gap::Viewer::igViewerGuiFactory::arkRegister, igBoxComponent_RunStaticInit, igStringObj_EnsureRegistered, igMetaObjectList_EnsureRegistered, igMetaFieldList_EnsureRegistered, 0 };

    ViewerLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igViewerStatisticsManager",
        sizeof(igViewerStatisticsManager),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igViewerStatisticsManager::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igBoolMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool };
    static const char *names[] = { "_items", "_visualContext", "_guiFactory", "_menu", "_boxComponent", "_string", "_recordStatisticMaximum", "_attrMetaObjects", "_extraSgStatistics", "_attrCount", "_displayListAttrCount", "_textureAttrCount", "_geometryAttrCount", "_geometrySetAttrCount", "_mvmAttrCount" };
    static igMetaField **enumStorage[] = { &k_items, &k_visualContext, &k_guiFactory, &k_menu, &k_boxComponent, &k_string, &k_recordStatisticMaximum, &k_attrMetaObjects, &k_extraSgStatistics, &k_attrCount, &k_displayListAttrCount, &k_textureAttrCount, &k_geometryAttrCount, &k_geometrySetAttrCount, &k_mvmAttrCount };
    static int offsets[] = { 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60, 64 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 15);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)Gap::Viewer::igStatisticsItemList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_metaObject = (int)Gap::Gfx::igVisualContext::getClassTypeLazy();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->_metaObject = (int)Gap::Viewer::igViewerGuiFactory::getClassTypeLazy();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->_metaObject = (int)igBoxComponent_GetOrCreateMetaObject();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 4);
        metaField->_metaObject = (int)igBoxComponent_GetOrCreateMetaObject();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 5);
        metaField->_metaObject = (int)igStringObj_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 7);
        metaField->_metaObject = (int)igMetaObjectList_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 8);
        metaField->_metaObject = (int)igMetaFieldList_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

