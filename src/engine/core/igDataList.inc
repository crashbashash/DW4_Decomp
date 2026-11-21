namespace Gap {
namespace Core {

igMetaObject *igDataList::_Meta;
igMetaField *igDataList::k_count;
igMetaField *igDataList::k_capacity;
igMetaField *igDataList::k_data;

igDataList *igDataList::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igDataList *)igMetaObject_CreateInstance(_Meta, pool);
}
}
}

/* Created with allocation only when missing. */
igMetaObject *igDataList_GetOrCreateMetaObject(void) {
    if (Gap::Core::igDataList::getClassMeta() == 0) {
        g_igDataList_metaObject = (igMetaObject *)igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    }
    return Gap::Core::igDataList::getClassMeta();
}

namespace Gap {
namespace Core {

igMetaObject *igDataList::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igDataList::retrieveVTablePointer()
{
    igDataList temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igDataList::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igDataList::arkRegisterInternal()
{
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igDataList",
        sizeof(igDataList),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void igDataList::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igIntMetaField_Create, igIntMetaField_Create, igMemoryRefMetaField_Create };
    static const char *names[] = { "_count", "_capacity", "_data" };
    static igMetaField **enumStorage[] = { &k_count, &k_capacity, &k_data };
    static int offsets[] = { 8, 12, 16 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 3);
    {
        igMemoryRefMetaField *metaField = (igMemoryRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->_memType = (int)Gap::Core::igUnsignedCharMetaField::getMetaField();
        metaField->_destruct = 1;
        metaField->_releaseOnCopy = 1;
        metaField->_releaseOnReset = 1;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

