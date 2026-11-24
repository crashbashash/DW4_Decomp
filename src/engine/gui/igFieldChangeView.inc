namespace Gap {
namespace Gui {

igMetaObject *igFieldChangeView::_Meta;
igMetaField *igFieldChangeView::k_synchronizer;
igMetaField *igFieldChangeView::k_field;

igFieldChangeView *igFieldChangeView::_instantiateFromPool(igMemoryPoolView *pool) {
    arkRegister();
    return (igFieldChangeView *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igFieldChangeView::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igFieldChangeView::retrieveVTablePointer()
{
    igFieldChangeView temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igFieldChangeView::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igFieldChangeView::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Gui::igFieldSynchronizer::arkRegister, Gap::Core::igMetaField::arkRegister, 0 };

    GuiLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Gui::igView::arkRegisterInternal,
        Gap::Gui::igView::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igFieldChangeView",
        sizeof(igFieldChangeView),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igFieldChangeView::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, igObjectRefMetaField_Create };
    static const char *names[] = { "_synchronizer", "_field" };
    static igMetaField **enumStorage[] = { &k_synchronizer, &k_field };
    static int offsets[] = { 12, 16 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 2);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)Gap::Gui::igFieldSynchronizer::getClassTypeLazy();
        metaField->_refCounted = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_metaObject = (int)Gap::Core::igMetaField::getClassTypeLazy();
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

