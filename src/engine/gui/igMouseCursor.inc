namespace Gap {
namespace Gui {

igMetaObject *igMouseCursor::_Meta;
igMetaField *igMouseCursor::k_geometryElement;
igMetaField *igMouseCursor::k_offset;

igMetaObject *igMouseCursor::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igMouseCursor::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igMouseCursor::retrieveVTablePointer()
{
    igMouseCursor temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igMouseCursor::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igMouseCursor::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Gui::igGeometryElement::arkRegister, 0 };

    GuiLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igMouseCursor",
        sizeof(igMouseCursor),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igMouseCursor::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, (FieldFactory)Gap::Math::igVec2fMetaField::_instantiateFromPool };
    static const char *names[] = { "_geometryElement", "_offset" };
    static igMetaField **enumStorage[] = { &k_geometryElement, &k_offset };
    static int offsets[] = { 8, 12 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 2);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)Gap::Gui::igGeometryElement::getClassTypeLazy();
    }
    {
        igVec2fMetaField *metaField = (igVec2fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->setDefault(igVec2f(0.0f, 0.0f));
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

