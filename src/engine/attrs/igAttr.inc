namespace Gap {
namespace Attrs {

igMetaObject *igAttr::_Meta;
igMetaField *igAttr::k_cachedUnitID;
igMetaField *igAttr::k_cachedAttrIndex;

igMetaObject *igAttr::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igAttr::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void igAttr::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igAttr::arkRegisterInternal()
{
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        true,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igAttr",
        sizeof(igAttr),
        0,
        &arkRegisterInitialize,
        (igMetaObjectCallback)Gap::Attrs::igAttr::userRegister,
        0
    );
}

void igAttr::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igShortMetaField_Create, igShortMetaField_Create };
    static const char *names[] = { "_cachedUnitID", "_cachedAttrIndex" };
    static igMetaField **enumStorage[] = { &k_cachedUnitID, &k_cachedAttrIndex };
    static int offsets[] = { 10, 8 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 2);
    {
        igShortMetaField *metaField = (igShortMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->setDefault(-1);
        metaField->_persistent = 0;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}

void igAttr::userRegister()
{
    FUN_0013b800();
    igMetaObject_AddRegistrationCallback((int)&registerClass);
}
}
}

