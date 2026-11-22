namespace Gap {
namespace Core {

igMetaObject *igPsx2File::_Meta;
igMetaField *igPsx2File::k_fBuf;
igMetaField *igPsx2File::k_bufSize;
igMetaField *igPsx2File::k_bufPos;
igMetaField *igPsx2File::k_fileSize;
igMetaField *igPsx2File::k_isBinary;
igMetaField *igPsx2File::k_isOpen;
igMetaField *igPsx2File::k_stringFile;
igMetaField *igPsx2File::k_prefix;

igPsx2File *igPsx2File::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igPsx2File *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igPsx2File::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igPsx2File::retrieveVTablePointer()
{
    igPsx2File temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igPsx2File::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igPsx2File::arkRegisterInternal()
{
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igFile::arkRegisterInternal,
        Gap::Core::igFile::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igPsx2File",
        sizeof(igPsx2File),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        (igMetaObjectCallback)Gap::Core::igPsx2File::arkRegisterUser,
        0
    );
}

void igPsx2File::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igMemoryRefMetaField_Create, igIntMetaField_Create, igIntMetaField_Create, igIntMetaField_Create, igIntMetaField_Create, igIntMetaField_Create, igRawRefMetaField_Create, igStringMetaField_Create };
    static const char *names[] = { "_fBuf", "_bufSize", "_bufPos", "_fileSize", "_isBinary", "_isOpen", "_stringFile", "_prefix" };
    static igMetaField **enumStorage[] = { &k_fBuf, &k_bufSize, &k_bufPos, &k_fileSize, &k_isBinary, &k_isOpen, &k_stringFile, &k_prefix };
    static int offsets[] = { 44, 48, 52, 56, 60, 64, 68, 72 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 8);
    {
        igMemoryRefMetaField *metaField = (igMemoryRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_memType = (int)Gap::Core::igUnsignedCharMetaField::getMetaField();
    }
    {
        igStringMetaField *metaField = (igStringMetaField *)igMetaObject_GetFieldAt(metaObject, start + 7);
        metaField->_resetMethod = 3;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
    *(void (**)())&_Meta->_writeProxy = (void (*)())Gap::Core::igFile::getClassMetaSafe;
}

void igPsx2File::arkRegisterUser() {
    userRegister();
}
}
}

