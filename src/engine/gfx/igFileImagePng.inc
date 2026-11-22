namespace Gap {
namespace Gfx {

igMetaObject *igFileImagePng::_Meta;
igMetaField *igFileImagePng::k_file;

igFileImagePng *igFileImagePng::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igFileImagePng *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igFileImagePng::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igFileImagePng::retrieveVTablePointer()
{
    igFileImagePng temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igFileImagePng::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igFileImagePng::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Core::igFile::arkRegister, 0 };

    GfxLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Gfx::igFileImage::arkRegisterInternal,
        Gap::Gfx::igFileImage::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igFileImagePng",
        sizeof(igFileImagePng),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igFileImagePng::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create };
    static const char *names[] = { "_file" };
    static igMetaField **enumStorage[] = { &k_file };
    static int offsets[] = { 92 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 1);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)Gap::Core::igFile::getClassTypeLazy();
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

