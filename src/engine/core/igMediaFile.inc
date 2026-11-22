namespace Gap {
namespace Core {

igMetaObject *igMediaFile::_Meta;
igMetaField *igMediaFile::k_isBinary;
igMetaField *igMediaFile::k_isOpen;
igMetaField *igMediaFile::k_write;
igMetaField *igMediaFile::k_read;
igMetaField *igMediaFile::k_bufSize;
igMetaField *igMediaFile::k_fileSize;
igMetaField *igMediaFile::k_bufPos;
igMetaField *igMediaFile::k_fBuf;
igMetaField *igMediaFile::k_media;

igMetaObject *igMediaFile::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igMediaFile::retrieveVTablePointer()
{
    igMediaFile temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igMediaFile::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igMediaFile::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Core::igMedia::arkRegister, 0 };

    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igFile::arkRegisterInternal,
        Gap::Core::igFile::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igMediaFile",
        sizeof(igMediaFile),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igMediaFile::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igBoolMetaField_Create, igBoolMetaField_Create, igBoolMetaField_Create, igBoolMetaField_Create, igIntMetaField_Create, igIntMetaField_Create, igIntMetaField_Create, igMemoryRefMetaField_Create, igObjectRefMetaField_Create };
    static const char *names[] = { "_isBinary", "_isOpen", "_write", "_read", "_bufSize", "_fileSize", "_bufPos", "_fBuf", "_media" };
    static igMetaField **enumStorage[] = { &k_isBinary, &k_isOpen, &k_write, &k_read, &k_bufSize, &k_fileSize, &k_bufPos, &k_fBuf, &k_media };
    static int offsets[] = { 44, 45, 46, 47, 48, 52, 56, 60, 64 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 9);
    {
        igMemoryRefMetaField *metaField = (igMemoryRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 7);
        metaField->_memType = (int)Gap::Core::igUnsignedCharMetaField::getMetaField();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 8);
        metaField->_metaObject = (int)Gap::Core::igMedia::getClassTypeLazy();
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

