namespace Gap {
namespace Gui {

igMetaObject *igRendererOrderedList::_Meta;

igRendererOrderedList *igRendererOrderedList::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igRendererOrderedList *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igRendererOrderedList::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igRendererOrderedList::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igRendererOrderedList::retrieveVTablePointer()
{
    igRendererOrderedList temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igRendererOrderedList::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igRendererOrderedList::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Gui::igRenderer::arkRegister, 0 };

    GuiLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igDependencyOrderedList::arkRegisterInternal,
        Gap::Core::igDependencyOrderedList::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igRendererOrderedList",
        sizeof(igRendererOrderedList),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        regFunctions
    );
}
}
}

