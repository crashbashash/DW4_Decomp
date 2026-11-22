namespace Gap {
namespace Gfx {

igMetaObject *igTgaLoader::_Meta;
igMetaField *igTgaLoader::k_file;
igMetaField *igTgaLoader::k_palette;
igMetaField *igTgaLoader::k_tempMap;
igMetaField *igTgaLoader::k_tempRow;
igMetaField *igTgaLoader::k_bCount;
igMetaField *igTgaLoader::k_bType;
igMetaField *igTgaLoader::k_psize;
igMetaField *igTgaLoader::k_nextChar;
igMetaField *igTgaLoader::k_limitChar;
igMetaField *igTgaLoader::k_sbpr;

igTgaLoader *igTgaLoader::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igTgaLoader *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igTgaLoader::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igTgaLoader::retrieveVTablePointer()
{
    igTgaLoader temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igTgaLoader::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igTgaLoader::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Core::igFile::arkRegister, 0 };

    GfxLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Gfx::igImageLoader::arkRegisterInternal,
        Gap::Gfx::igImageLoader::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igTgaLoader",
        sizeof(igTgaLoader),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igTgaLoader::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, igMemoryRefMetaField_Create, igMemoryRefMetaField_Create, igMemoryRefMetaField_Create, igIntMetaField_Create, igIntMetaField_Create, igIntMetaField_Create, igIntMetaField_Create, igIntMetaField_Create, igIntMetaField_Create };
    static const char *names[] = { "_file", "_palette", "_tempMap", "_tempRow", "_bCount", "_bType", "_psize", "_nextChar", "_limitChar", "_sbpr" };
    static igMetaField **enumStorage[] = { &k_file, &k_palette, &k_tempMap, &k_tempRow, &k_bCount, &k_bType, &k_psize, &k_nextChar, &k_limitChar, &k_sbpr };
    static int offsets[] = { 8, 12, 16, 20, 24, 28, 32, 36, 40, 44 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 10);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)Gap::Core::igFile::getClassTypeLazy();
    }
    {
        igMemoryRefMetaField *metaField = (igMemoryRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_memType = (int)Gap::Core::igUnsignedCharMetaField::getMetaField();
    }
    {
        igMemoryRefMetaField *metaField = (igMemoryRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->_memType = (int)Gap::Core::igUnsignedCharMetaField::getMetaField();
    }
    {
        igMemoryRefMetaField *metaField = (igMemoryRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->_memType = (int)Gap::Core::igUnsignedCharMetaField::getMetaField();
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

