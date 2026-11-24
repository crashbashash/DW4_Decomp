namespace Gap {
namespace Viewer {

igMetaObject *igNormalsRenderer::_Meta;
igMetaField *igNormalsRenderer::k_parameters;
igMetaField *igNormalsRenderer::k_attrList;
igMetaField *igNormalsRenderer::k_defaultAttrList;
igMetaField *igNormalsRenderer::k_modelViewAttr;
igMetaField *igNormalsRenderer::k_colorAttr;
igMetaField *igNormalsRenderer::k_normals;
igMetaField *igNormalsRenderer::k_invalidStoredNormals;
igMetaField *igNormalsRenderer::k_path;
igMetaField *igNormalsRenderer::k_draw;

igMetaObject *igNormalsRenderer::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igNormalsRenderer::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igNormalsRenderer::retrieveVTablePointer()
{
    igNormalsRenderer temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igNormalsRenderer::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igNormalsRenderer::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Viewer::igViewerParameters::arkRegister, Gap::Attrs::igAttrList::arkRegister, Gap::Attrs::igModelViewMatrixAttr::arkRegister, Gap::Attrs::igColorAttr::arkRegister, Gap::Attrs::igGeometryAttrList::arkRegister, Gap::Sg::igGraphPath::arkRegister, 0 };

    ViewerLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Gui::igRenderer::arkRegisterInternal,
        Gap::Gui::igRenderer::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igNormalsRenderer",
        sizeof(igNormalsRenderer),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igNormalsRenderer::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igBoolMetaField_Create, igObjectRefMetaField_Create, igBoolMetaField_Create };
    static const char *names[] = { "_parameters", "_attrList", "_defaultAttrList", "_modelViewAttr", "_colorAttr", "_normals", "_invalidStoredNormals", "_path", "_draw" };
    static igMetaField **enumStorage[] = { &k_parameters, &k_attrList, &k_defaultAttrList, &k_modelViewAttr, &k_colorAttr, &k_normals, &k_invalidStoredNormals, &k_path, &k_draw };
    static int offsets[] = { 12, 16, 20, 24, 28, 32, 36, 40, 44 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 9);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)Gap::Viewer::igViewerParameters::getClassTypeLazy();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_metaObject = (int)Gap::Attrs::igAttrList::getClassTypeLazy();
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
        metaField->_metaObject = (int)Gap::Attrs::igColorAttr::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 5);
        metaField->_metaObject = (int)Gap::Attrs::igGeometryAttrList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 7);
        metaField->_metaObject = (int)Gap::Sg::igGraphPath::getClassTypeLazy();
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

