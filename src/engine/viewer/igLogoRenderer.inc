namespace Gap {
namespace Viewer {

igMetaObject *igLogoRenderer::_Meta;
igMetaField *igLogoRenderer::k_time;
igMetaField *igLogoRenderer::k_geometryAttr;
igMetaField *igLogoRenderer::k_colorAttr;
igMetaField *igLogoRenderer::k_attrList;

igLogoRenderer *igLogoRenderer::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igLogoRenderer *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igLogoRenderer::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igLogoRenderer::retrieveVTablePointer()
{
    igLogoRenderer temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igLogoRenderer::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igLogoRenderer::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Attrs::igGeometryAttr::arkRegister, Gap::Attrs::igColorAttr::arkRegister, Gap::Attrs::igAttrList::arkRegister, 0 };

    ViewerLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Gui::igRenderer::arkRegisterInternal,
        Gap::Gui::igRenderer::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igLogoRenderer",
        sizeof(igLogoRenderer),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igLogoRenderer::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { (FieldFactory)Gap::Core::igLongMetaField::_instantiateFromPool, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create };
    static const char *names[] = { "_time", "_geometryAttr", "_colorAttr", "_attrList" };
    static igMetaField **enumStorage[] = { &k_time, &k_geometryAttr, &k_colorAttr, &k_attrList };
    static int offsets[] = { 16, 24, 28, 32 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 4);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_metaObject = (int)Gap::Attrs::igGeometryAttr::getClassTypeLazy();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->_metaObject = (int)Gap::Attrs::igColorAttr::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->_metaObject = (int)Gap::Attrs::igAttrList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

