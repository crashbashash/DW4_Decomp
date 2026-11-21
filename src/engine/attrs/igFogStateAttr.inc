namespace Gap {
namespace Attrs {

igMetaObject *igFogStateAttr::_Meta;
igMetaField *igFogStateAttr::k_enabled;

igMetaObject *igFogStateAttr::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igFogStateAttr::retrieveVTablePointer()
{
    igFogStateAttr temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igFogStateAttr::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igFogStateAttr::arkRegisterInternal()
{
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Attrs::igVisualAttribute::arkRegisterInternal,
        Gap::Attrs::igVisualAttribute::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igFogStateAttr",
        sizeof(igFogStateAttr),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void igFogStateAttr::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igBoolMetaField_Create };
    static const char *names[] = { "_enabled" };
    static igMetaField **enumStorage[] = { &k_enabled };
    static int offsets[] = { 12 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 1);
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

