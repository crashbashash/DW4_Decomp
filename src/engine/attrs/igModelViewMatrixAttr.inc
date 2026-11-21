namespace Gap {
namespace Attrs {

igMetaObject *igModelViewMatrixAttr::_Meta;
igMetaField *igModelViewMatrixAttr::k_m;

igModelViewMatrixAttr *igModelViewMatrixAttr::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igModelViewMatrixAttr *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igModelViewMatrixAttr::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igModelViewMatrixAttr::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igModelViewMatrixAttr::retrieveVTablePointer()
{
    igModelViewMatrixAttr temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igModelViewMatrixAttr::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igModelViewMatrixAttr::arkRegisterInternal()
{
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Attrs::igVisualAttribute::arkRegisterInternal,
        Gap::Attrs::igVisualAttribute::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igModelViewMatrixAttr",
        sizeof(igModelViewMatrixAttr),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        (igMetaObjectCallback)arkRegisterUser,
        0
    );
}

void igModelViewMatrixAttr::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { (FieldFactory)Gap::Math::igMatrix44fMetaField::_instantiateFromPool };
    static const char *names[] = { "_m" };
    static igMetaField **enumStorage[] = { &k_m };
    static int offsets[] = { 12 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 1);
    {
        igMatrix44fMetaField *metaField = (igMatrix44fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->setDefault(igMatrix44f(igVec4f(1.0f, 0.0f, 0.0f, 0.0f), igVec4f(0.0f, 1.0f, 0.0f, 0.0f),
                                          igVec4f(0.0f, 0.0f, 1.0f, 0.0f), igVec4f(0.0f, 0.0f, 0.0f, 1.0f)));
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
    igMetaObject_AddExitCallback((int)&thunk_igModelViewMatrixAttr_UserUnregister);
}

void igModelViewMatrixAttr::arkRegisterUser()
{
    userRegister();
}
}
}

void thunk_igModelViewMatrixAttr_UserUnregister(void) {
    Gap::Attrs::igModelViewMatrixAttr::userUnregister();
}

