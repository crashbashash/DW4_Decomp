namespace Gap {
namespace Core {

igMetaObject *igMediaList::_Meta;

igMediaList *igMediaList::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igMediaList *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igMediaList::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igMediaList::retrieveVTablePointer()
{
    igMediaList temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igMediaList::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igMediaList::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Core::igMedia::arkRegister, 0 };

    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igMediaList",
        sizeof(igMediaList),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        regFunctions
    );
}
}
}

