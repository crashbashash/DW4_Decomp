namespace Gap {
namespace Attrs {

igMetaObject *igTextureAttr::_Meta;
igMetaField *igTextureAttr::k_bColor;
igMetaField *igTextureAttr::k_magFilter;
igMetaField *igTextureAttr::k_minFilter;
igMetaField *igTextureAttr::k_wrapS;
igMetaField *igTextureAttr::k_wrapT;
igMetaField *igTextureAttr::k_texId;
igMetaField *igTextureAttr::k_mipmapMode;
igMetaField *igTextureAttr::k_source;
igMetaField *igTextureAttr::k_image;
igMetaField *igTextureAttr::k_paging;
igMetaField *igTextureAttr::k_tu;
igMetaField *igTextureAttr::k_imageCount;
igMetaField *igTextureAttr::k_imageMipMaps;
igMetaField *igTextureAttr::k_vc;
igMetaField *igTextureAttr::k_videoBuffer;

igTextureAttr *igTextureAttr::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igTextureAttr *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igTextureAttr::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igTextureAttr::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igTextureAttr::retrieveVTablePointer()
{
    igTextureAttr temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igTextureAttr::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igTextureAttr::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Gfx::igImage::arkRegister, Gap::Attrs::igTextureUnloadAttr::arkRegister, Gap::Attrs::igImageMipMapList::arkRegister, igVisualContext_EnsureRegistered, 0 };

    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Attrs::igVisualAttribute::arkRegisterInternal,
        Gap::Attrs::igVisualAttribute::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igTextureAttr",
        sizeof(igTextureAttr),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}
}
}

int g_igTextureAttr_wrapSDefault = 1;
int g_igTextureAttr_wrapTDefault = 1;

namespace Gap {
namespace Attrs {

void igTextureAttr::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igUnsignedIntMetaField_Create, igEnumMetaField_Create, igEnumMetaField_Create, igEnumMetaField_Create, igEnumMetaField_Create, igIntMetaField_Create, igEnumMetaField_Create, igEnumMetaField_Create, igObjectRefMetaField_Create, igBoolMetaField_Create, igObjectRefMetaField_Create, igIntMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igRawRefMetaField_Create };
    static const char *names[] = { "_bColor", "_magFilter", "_minFilter", "_wrapS", "_wrapT", "_texId", "_mipmapMode", "_source", "_image", "_paging", "_tu", "_imageCount", "_imageMipMaps", "_vc", "_videoBuffer" };
    static igMetaField **enumStorage[] = { &k_bColor, &k_magFilter, &k_minFilter, &k_wrapS, &k_wrapT, &k_texId, &k_mipmapMode, &k_source, &k_image, &k_paging, &k_tu, &k_imageCount, &k_imageMipMaps, &k_vc, &k_videoBuffer };
    static int offsets[] = { 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60, 64, 12, 68 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 15);
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->setDefault(0);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())IG_GFX_TEXTURE_FILTER_GetMetaEnum;
    }
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->setDefault(0);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())IG_GFX_TEXTURE_FILTER_GetMetaEnum;
    }
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->setDefault(1);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())IG_GFX_TEXTURE_WRAP_GetMetaEnum;
    }
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 4);
        metaField->setDefault(1);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())IG_GFX_TEXTURE_WRAP_GetMetaEnum;
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 5);
        metaField->setDefault(-1);
        metaField->_persistent = 0;
        metaField->_deepCopyMethod = 4;
        metaField->_shallowCopyMethod = 4;
        metaField->_isAlikeShallowMethod = 3;
    }
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 6);
        metaField->setDefault(0);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())IG_GFX_TEXTURE_MODE_GetMetaEnum;
    }
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 7);
        metaField->setDefault(0);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())IG_GFX_TEXTURE_SOURCE_GetMetaEnum;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 8);
        metaField->_metaObject = (int)Gap::Gfx::igImage::getClassTypeLazy();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 10);
        metaField->_metaObject = (int)Gap::Attrs::igTextureUnloadAttr::getClassTypeLazy();
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 11);
        metaField->setDefault(1);
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 12);
        metaField->_metaObject = (int)Gap::Attrs::igImageMipMapList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 13);
        metaField->_metaObject = (int)igVisualContext_GetOrCreateMetaObject();
        metaField->_persistent = 0;
        metaField->_deepCopyMethod = 1;
        metaField->_shallowCopyMethod = 1;
        metaField->_isAlikeShallowMethod = 3;
    }
    {
        igRawRefMetaField *metaField = (igRawRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 14);
        metaField->_persistent = 0;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

