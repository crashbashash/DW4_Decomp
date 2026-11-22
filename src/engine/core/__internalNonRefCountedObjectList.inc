namespace Gap {
namespace Core {

__internalNonRefCountedObjectList *__internalNonRefCountedObjectList::_instantiateFromPool(igMemoryPoolView *pool)
{
    __internalNonRefCountedObjectList *list;

    if (g_objectSystem->active != 0) {
        arkRegister();
        list = (__internalNonRefCountedObjectList *)igMetaObject_CreateInstance(_Meta, pool);
    } else {
        list = new (0, pool) __internalNonRefCountedObjectList(true);
        list->initDefaults();
        list->userConstruct(0);
    }
    return list;
}

igObject *__internalNonRefCountedObjectList::cloneViaMetadata(int copyMode)
{
    if (g_objectSystem->active != 0) {
        arkRegister();
        return igObject::cloneViaMetadata(copyMode);
    }
    return new (0) __internalNonRefCountedObjectList(*this);
}

igMetaObject *__internalNonRefCountedObjectList::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *__internalNonRefCountedObjectList::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *__internalNonRefCountedObjectList::retrieveVTablePointer()
{
    __internalNonRefCountedObjectList temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void __internalNonRefCountedObjectList::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *__internalNonRefCountedObjectList::arkRegisterInternal()
{
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "__internalNonRefCountedObjectList",
        sizeof(__internalNonRefCountedObjectList),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void __internalNonRefCountedObjectList::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igMemoryRefMetaField_Create, igIntMetaField_Create };
    static const char *names[] = { "_data", "_count" };
    static igMetaField **enumStorage[] = { &k_data, &k_count };
    static int offsets[] = { 8, 12 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 2);
    {
        igMemoryRefMetaField *metaField = (igMemoryRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_memType = (int)Gap::Core::igObjectRefMetaField::getMetaField();
        metaField->_memSize = 64;
        metaField->_construct = 1;
        metaField->_destruct = 1;
        metaField->_releaseOnCopy = 1;
        metaField->_releaseOnReset = 1;
        metaField->_refCounted = 0;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

