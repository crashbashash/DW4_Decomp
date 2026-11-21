namespace Gap {
namespace Attrs {

igMetaObject *igPixelPipelineModeAttr::_Meta;
igMetaField *igPixelPipelineModeAttr::k_pipelineMode;

igPixelPipelineModeAttr *igPixelPipelineModeAttr::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igPixelPipelineModeAttr *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igPixelPipelineModeAttr::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igPixelPipelineModeAttr::retrieveVTablePointer()
{
    igPixelPipelineModeAttr temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igPixelPipelineModeAttr::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igPixelPipelineModeAttr::arkRegisterInternal()
{
    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Attrs::igVisualAttribute::arkRegisterInternal,
        Gap::Attrs::igVisualAttribute::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igPixelPipelineModeAttr",
        sizeof(igPixelPipelineModeAttr),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void igPixelPipelineModeAttr::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igEnumMetaField_Create };
    static const char *names[] = { "_pipelineMode" };
    static igMetaField **enumStorage[] = { &k_pipelineMode };
    static int offsets[] = { 12 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 1);
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->setDefault(0);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())IG_GFX_PIXEL_PIPELINE_MODE_GetMetaEnum;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

