namespace Gap {
namespace Core {

igMetaObject *igMemoryFile::_Meta;
igMetaField *igMemoryFile::k_bIsOpen;
igMetaField *igMemoryFile::k_buffer;
igMetaField *igMemoryFile::k_iBufferSize;
igMetaField *igMemoryFile::k_iSeekPosition;

igMemoryFile *igMemoryFile::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igMemoryFile *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igMemoryFile::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igMemoryFile::retrieveVTablePointer()
{
    igMemoryFile temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igMemoryFile::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igMemoryFile::arkRegisterInternal()
{
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igFile::arkRegisterInternal,
        Gap::Core::igFile::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igMemoryFile",
        sizeof(igMemoryFile),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        (igMetaObjectCallback)Gap::Core::igMemoryFile::arkRegisterUser,
        0
    );
}

igMetaObject *igFile::_Meta;
igMetaField *igFile::k_fileName;
igMetaField *igFile::k_readMode;
igMetaField *igFile::k_openMode;
igMetaField *igFile::k_fileHandle;
igMetaField *igFile::k_optimalReadChunkSize;
igMetaField *igFile::k_optimalWriteChunkSize;
igMetaField *igFile::k_pageSize;
igMetaField *igFile::k_completeFilename;

void igMemoryFile::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igBoolMetaField_Create, igRawRefMetaField_Create, igIntMetaField_Create, igIntMetaField_Create };
    static const char *names[] = { "_bIsOpen", "_buffer", "_iBufferSize", "_iSeekPosition" };
    static igMetaField **enumStorage[] = { &k_bIsOpen, &k_buffer, &k_iBufferSize, &k_iSeekPosition };
    static int offsets[] = { 44, 48, 52, 56 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 4);
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
    *(void (**)())&_Meta->_writeProxy = (void (*)())Gap::Core::igFile::getClassMetaSafe;
    igMetaObject_AddExitCallback((int)Gap::Core::igMemoryFile::_classDestructor);
}
}
}

