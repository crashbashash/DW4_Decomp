namespace Gap {
namespace Core {

igMetaObject *igMemoryFileEntryList::_Meta;

igMemoryFileEntryList *igMemoryFileEntryList::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igMemoryFileEntryList *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igMemoryFileEntryList::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igMemoryFileEntryList::retrieveVTablePointer()
{
    igMemoryFileEntryList temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igMemoryFileEntryList::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igMemoryFileEntryList::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Core::igMemoryFileEntry::arkRegister, 0 };

    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObjectList::arkRegisterInternal,
        Gap::Core::igObjectList::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igMemoryFileEntryList",
        sizeof(igMemoryFileEntryList),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        0,
        0,
        regFunctions
    );
}
}
}

