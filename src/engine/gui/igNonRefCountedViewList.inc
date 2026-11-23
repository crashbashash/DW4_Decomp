namespace Gap {
namespace Gui {

igMetaObject *igNonRefCountedViewList::_Meta;

igMetaObject *igNonRefCountedViewList::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igNonRefCountedViewList::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igNonRefCountedViewList::retrieveVTablePointer()
{
    igNonRefCountedViewList temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igNonRefCountedViewList::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igNonRefCountedViewList::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Gui::igView::arkRegister, 0 };

    GuiLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igNonRefCountedObjectList::arkRegisterInternal,
        Gap::Core::igNonRefCountedObjectList::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igNonRefCountedViewList",
        sizeof(igNonRefCountedViewList),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        regFunctions
    );
}
}
}

