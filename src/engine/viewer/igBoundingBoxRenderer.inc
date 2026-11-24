namespace Gap {
namespace Viewer {

igMetaObject *igBoundingBoxRenderer::_Meta;
igMetaField *igBoundingBoxRenderer::k_parameters;
igMetaField *igBoundingBoxRenderer::k_displayList;
igMetaField *igBoundingBoxRenderer::k_attrList;
igMetaField *igBoundingBoxRenderer::k_modelViewAttr;
igMetaField *igBoundingBoxRenderer::k_box;
igMetaField *igBoundingBoxRenderer::k_border;
igMetaField *igBoundingBoxRenderer::k_path;
igMetaField *igBoundingBoxRenderer::k_draw;

igMetaObject *igBoundingBoxRenderer::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igBoundingBoxRenderer::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igBoundingBoxRenderer::retrieveVTablePointer()
{
    igBoundingBoxRenderer temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igBoundingBoxRenderer::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igBoundingBoxRenderer::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Viewer::igViewerParameters::arkRegister, Gap::Attrs::igDisplayListAttr::arkRegister, Gap::Attrs::igAttrList::arkRegister, Gap::Attrs::igModelViewMatrixAttr::arkRegister, Gap::Attrs::igGeometryAttr::arkRegister, Gap::Sg::igGraphPath::arkRegister, 0 };

    ViewerLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Gui::igRenderer::arkRegisterInternal,
        Gap::Gui::igRenderer::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igBoundingBoxRenderer",
        sizeof(igBoundingBoxRenderer),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igBoundingBoxRenderer::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igBoolMetaField_Create };
    static const char *names[] = { "_parameters", "_displayList", "_attrList", "_modelViewAttr", "_box", "_border", "_path", "_draw" };
    static igMetaField **enumStorage[] = { &k_parameters, &k_displayList, &k_attrList, &k_modelViewAttr, &k_box, &k_border, &k_path, &k_draw };
    static int offsets[] = { 12, 16, 20, 24, 28, 32, 36, 40 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 8);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)Gap::Viewer::igViewerParameters::getClassTypeLazy();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_metaObject = (int)Gap::Attrs::igDisplayListAttr::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->_metaObject = (int)Gap::Attrs::igAttrList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->_metaObject = (int)Gap::Attrs::igModelViewMatrixAttr::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 4);
        metaField->_metaObject = (int)Gap::Attrs::igGeometryAttr::getClassTypeLazy();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 5);
        metaField->_metaObject = (int)Gap::Attrs::igGeometryAttr::getClassTypeLazy();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 6);
        metaField->_metaObject = (int)Gap::Sg::igGraphPath::getClassTypeLazy();
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

