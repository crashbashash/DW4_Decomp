namespace Gap {
namespace Bec {

igMetaObject *beFontGeomAttrPair::_Meta;
igMetaField *beFontGeomAttrPair::k_category;
igMetaField *beFontGeomAttrPair::k_panel;
igMetaField *beFontGeomAttrPair::k_geomAttrs;

beFontGeomAttrPair *beFontGeomAttrPair::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (beFontGeomAttrPair *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *beFontGeomAttrPair::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *beFontGeomAttrPair::retrieveVTablePointer()
{
    beFontGeomAttrPair temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void beFontGeomAttrPair::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *beFontGeomAttrPair::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Attrs::igGeometryAttrList::arkRegister, 0 };

    BecLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "beFontGeomAttrPair",
        sizeof(beFontGeomAttrPair),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void beFontGeomAttrPair::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igStringMetaField_Create, igStringMetaField_Create, igObjectRefMetaField_Create };
    static const char *names[] = { "_category", "_panel", "_geomAttrs" };
    static igMetaField **enumStorage[] = { &k_category, &k_panel, &k_geomAttrs };
    static int offsets[] = { 8, 12, 16 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 3);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->_metaObject = (int)Gap::Attrs::igGeometryAttrList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

