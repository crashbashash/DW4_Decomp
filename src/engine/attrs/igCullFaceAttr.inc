namespace Gap {
namespace Attrs {

igMetaObject *igCullFaceAttr::_Meta;
igMetaField *igCullFaceAttr::k_enabled;
igMetaField *igCullFaceAttr::k_mode;

igCullFaceAttr *igCullFaceAttr::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igCullFaceAttr *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igCullFaceAttr::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igCullFaceAttr::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igCullFaceAttr::retrieveVTablePointer()
{
    igCullFaceAttr temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igCullFaceAttr::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igCullFaceAttr::arkRegisterInternal()
{
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Attrs::igVisualAttribute::arkRegisterInternal,
        Gap::Attrs::igVisualAttribute::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igCullFaceAttr",
        sizeof(igCullFaceAttr),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void igCullFaceAttr::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igBoolMetaField_Create, igEnumMetaField_Create };
    static const char *names[] = { "_enabled", "_mode" };
    static igMetaField **enumStorage[] = { &k_enabled, &k_mode };
    static int offsets[] = { 12, 16 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 2);
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->setDefault(0);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())IG_GFX_CULL_FACE_MODE_GetMetaEnum;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

