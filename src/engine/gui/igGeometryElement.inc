namespace Gap {
namespace Gui {

igMetaObject *igGeometryElement::_Meta;
igMetaField *igGeometryElement::k_geometry;
igMetaField *igGeometryElement::k_defaultSize;
igMetaField *igGeometryElement::k_color;
igMetaField *igGeometryElement::k_sharableAttrs;

igMetaObject *igGeometryElement::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igGeometryElement::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void igGeometryElement::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igGeometryElement::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Sg::igGeometry::arkRegister, Gap::Attrs::igAttrList::arkRegister, 0 };

    GuiLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        true,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igGeometryElement",
        sizeof(igGeometryElement),
        0,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igGeometryElement::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, (FieldFactory)Gap::Math::igVec3fMetaField::_instantiateFromPool, (FieldFactory)Gap::Math::igVec4fMetaField::_instantiateFromPool, igObjectRefMetaField_Create };
    static const char *names[] = { "_geometry", "_defaultSize", "_color", "_sharableAttrs" };
    static igMetaField **enumStorage[] = { &k_geometry, &k_defaultSize, &k_color, &k_sharableAttrs };
    static int offsets[] = { 8, 12, 24, 40 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 4);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)Gap::Sg::igGeometry::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igVec3fMetaField *metaField = (igVec3fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->setDefault(igVec3f(0.0f, 0.0f, 0.0f));
    }
    {
        igVec4fMetaField *metaField = (igVec4fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->setDefault(igVec4f(1.0f, 1.0f, 1.0f, 1.0f));
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

