namespace Gap {
namespace Attrs {

igMetaObject *igRenderListAttr::_Meta;
igMetaField *igRenderListAttr::k_handle;
igMetaField *igRenderListAttr::k_vc;

igMetaObject *igRenderListAttr::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igRenderListAttr::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igRenderListAttr::retrieveVTablePointer()
{
    igRenderListAttr temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igRenderListAttr::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igRenderListAttr::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { igVisualContext_EnsureRegistered, 0 };

    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Attrs::igVisualAttribute::arkRegisterInternal,
        Gap::Attrs::igVisualAttribute::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igRenderListAttr",
        sizeof(igRenderListAttr),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igRenderListAttr::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igIntMetaField_Create, igObjectRefMetaField_Create };
    static const char *names[] = { "_handle", "_vc" };
    static igMetaField **enumStorage[] = { &k_handle, &k_vc };
    static int offsets[] = { 12, 16 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 2);
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->setDefault(-1);
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_metaObject = (int)igVisualContext_GetOrCreateMetaObject();
        metaField->_persistent = 0;
        metaField->_deepCopyMethod = 1;
        metaField->_shallowCopyMethod = 1;
        metaField->_isAlikeShallowMethod = 3;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

