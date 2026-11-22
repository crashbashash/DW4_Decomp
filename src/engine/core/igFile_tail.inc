static const char *g_igFile_readModeNames[] = {
    "kDefaultReadMode", "kSequentialReadMode", "kChunkReadMode",
};
static int g_igFile_readModeValues[] = {
    0, 1, 2,
};

namespace Gap {
namespace Core {

igMetaEnum *igFile::getReadModeMetaEnum() {
    if (ReadMode_Meta == 0) {
        ReadMode_Meta = igMetaEnum::createMetaEnum("ReadMode", g_igFile_readModeNames, g_igFile_readModeValues, 3);
    }
    return ReadMode_Meta;
}
}
}

static const char *g_igFile_openModeNames[] = {
    "kRead", "kWrite", "kAppend", "kReadWrite",
    "kReadBinary", "kWriteBinary", "kAppendBinary", "kReadWriteBinary",
    "kDefaultOpenMode",
};
static int g_igFile_openModeValues[] = {
    0, 1, 2, 3, 4, 5, 6, 7,
    8,
};

namespace Gap {
namespace Core {

igMetaEnum *igFile::getOpenModeMetaEnum() {
    if (OpenMode_Meta == 0) {
        OpenMode_Meta = igMetaEnum::createMetaEnum("OpenMode", g_igFile_openModeNames, g_igFile_openModeValues, 9);
    }
    return OpenMode_Meta;
}

igFile *igFile::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igFile *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igFile::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igFile::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void igFile::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igFile::arkRegisterInternal()
{
    CoreLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        true,
        &_Meta,
        Gap::Core::igNamedObject::arkRegisterInternal,
        Gap::Core::igNamedObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igFile",
        sizeof(igFile),
        0,
        &arkRegisterInitialize,
        0,
        0
    );
}

void igFile::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igStringMetaField_Create, igEnumMetaField_Create, igEnumMetaField_Create, igRawRefMetaField_Create, igIntMetaField_Create, igIntMetaField_Create, igIntMetaField_Create, igStringMetaField_Create };
    static const char *names[] = { "_fileName", "_readMode", "_openMode", "_fileHandle", "_optimalReadChunkSize", "_optimalWriteChunkSize", "_pageSize", "_completeFilename" };
    static igMetaField **enumStorage[] = { &k_fileName, &k_readMode, &k_openMode, &k_fileHandle, &k_optimalReadChunkSize, &k_optimalWriteChunkSize, &k_pageSize, &k_completeFilename };
    static int offsets[] = { 12, 16, 20, 24, 28, 32, 36, 40 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 8);
    {
        igStringMetaField *metaField = (igStringMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->setDefault("DefaultFileName");
    }
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->setDefault(0);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())Gap::Core::igFile::getReadModeMetaEnum;
    }
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->setDefault(0);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())Gap::Core::igFile::getOpenModeMetaEnum;
    }
    {
        igRawRefMetaField *metaField = (igRawRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->_persistent = 0;
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 4);
        metaField->setDefault(1048576);
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 5);
        metaField->setDefault(1048576);
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 6);
        metaField->setDefault(4096);
    }
    {
        igStringMetaField *metaField = (igStringMetaField *)igMetaObject_GetFieldAt(metaObject, start + 7);
        metaField->_persistent = 0;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
    *(void (**)())&_Meta->_abstractProxy = (void (*)())Gap::Core::igPsx2File::getClassMetaSafe;
}
}
}

