namespace Gap {
namespace Core {

igMetaObject *igMemoryFileEntry::_Meta;
igMetaField *igMemoryFileEntry::k_buffer;
igMetaField *igMemoryFileEntry::k_size;

igMemoryFileEntry *igMemoryFileEntry::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igMemoryFileEntry *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igMemoryFileEntry::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igMemoryFileEntry::retrieveVTablePointer()
{
    igMemoryFileEntry temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igMemoryFileEntry::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igMemoryFileEntry::arkRegisterInternal()
{
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igNamedObject::arkRegisterInternal,
        Gap::Core::igNamedObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igMemoryFileEntry",
        sizeof(igMemoryFileEntry),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        0
    );
}

void igMemoryFileEntry::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igRawRefMetaField_Create, igUnsignedIntMetaField_Create };
    static const char *names[] = { "_buffer", "_size" };
    static igMetaField **enumStorage[] = { &k_buffer, &k_size };
    static int offsets[] = { 12, 16 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 2);
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

