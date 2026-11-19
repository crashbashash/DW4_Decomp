namespace Gap {
namespace Gui {

igMetaObject *igRenderer::_Meta;
igMetaField *igRenderer::k_visualContext;

igMetaObject *igRenderer::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void igRenderer::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igRenderer::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { igVisualContext_EnsureRegistered, 0 };

    GuiLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        true,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igRenderer",
        sizeof(igRenderer),
        0,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igRenderer::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create };
    static const char *names[] = { "_visualContext" };
    static igMetaField **enumStorage[] = { &k_visualContext };
    static int offsets[] = { 8 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 1);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)igVisualContext_GetOrCreateMetaObject();
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}
