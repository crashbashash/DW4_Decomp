namespace Gap {
namespace Gui {

igMetaObject *igClearRenderer::_Meta;
igMetaField *igClearRenderer::k_buffersToClear;

igMetaObject *igClearRenderer::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igClearRenderer::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igClearRenderer::retrieveVTablePointer()
{
    igClearRenderer temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igClearRenderer::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igClearRenderer::arkRegisterInternal()
{
    GuiLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Gui::igRenderer::arkRegisterInternal,
        Gap::Gui::igRenderer::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igClearRenderer",
        sizeof(igClearRenderer),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void igClearRenderer::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igUnsignedIntMetaField_Create };
    static const char *names[] = { "_buffersToClear" };
    static igMetaField **enumStorage[] = { &k_buffersToClear };
    static int offsets[] = { 12 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 1);
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}
