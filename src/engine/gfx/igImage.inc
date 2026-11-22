namespace Gap {
namespace Gfx {

igMetaObject *igImage::_Meta;
igMetaField *igImage::k_px;
igMetaField *igImage::k_py;
igMetaField *igImage::k_pz;
igMetaField *igImage::k_ps;
igMetaField *igImage::k_order;
igMetaField *igImage::k_bitsRed;
igMetaField *igImage::k_bitsGrn;
igMetaField *igImage::k_bitsBlu;
igMetaField *igImage::k_bitsAlpha;
igMetaField *igImage::k_pfmt;
igMetaField *igImage::k_imageSize;
igMetaField *igImage::k_pImage;
igMetaField *igImage::k_pName;
igMetaField *igImage::k_localImage;
igMetaField *igImage::k_bitsInt;
igMetaField *igImage::k_pClut;
igMetaField *igImage::k_bitsIdx;
igMetaField *igImage::k_bytesPerRow;
igMetaField *igImage::k_compressed;
igMetaField *igImage::k_bitsDepth;
igMetaField *igImage::k_pNameString;

igImage *igImage::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igImage *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igImage::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igImage::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void igImage::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igImage::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Gfx::igClut::arkRegister, 0 };

    GfxLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        true,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igImage",
        sizeof(igImage),
        0,
        &arkRegisterInitialize,
        (igMetaObjectCallback)Gap::Gfx::igImage::arkRegisterUser,
        regFunctions
    );
}
}
}

static int g_igImage_pfmtDefault = 7;

namespace Gap {
namespace Gfx {

void igImage::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igUnsignedIntMetaField_Create, igUnsignedIntMetaField_Create, igUnsignedIntMetaField_Create, igUnsignedIntMetaField_Create, igUnsignedIntMetaField_Create, igUnsignedIntMetaField_Create, igUnsignedIntMetaField_Create, igUnsignedIntMetaField_Create, igUnsignedIntMetaField_Create, igEnumMetaField_Create, igIntMetaField_Create, igMemoryRefMetaField_Create, igMemoryRefMetaField_Create, igBoolMetaField_Create, igUnsignedIntMetaField_Create, igObjectRefMetaField_Create, igUnsignedIntMetaField_Create, igIntMetaField_Create, igBoolMetaField_Create, igUnsignedIntMetaField_Create, igStringMetaField_Create };
    static const char *names[] = { "_px", "_py", "_pz", "_ps", "_order", "_bitsRed", "_bitsGrn", "_bitsBlu", "_bitsAlpha", "_pfmt", "_imageSize", "_pImage", "_pName", "_localImage", "_bitsInt", "_pClut", "_bitsIdx", "_bytesPerRow", "_compressed", "_bitsDepth", "_pNameString" };
    static igMetaField **enumStorage[] = { &k_px, &k_py, &k_pz, &k_ps, &k_order, &k_bitsRed, &k_bitsGrn, &k_bitsBlu, &k_bitsAlpha, &k_pfmt, &k_imageSize, &k_pImage, &k_pName, &k_localImage, &k_bitsInt, &k_pClut, &k_bitsIdx, &k_bytesPerRow, &k_compressed, &k_bitsDepth, &k_pNameString };
    static int offsets[] = { 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60, 64, 68, 72, 76, 80, 84, 88 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 21);
    {
        igUnsignedIntMetaField *metaField = (igUnsignedIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->setDefault(1);
    }
    {
        igUnsignedIntMetaField *metaField = (igUnsignedIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 4);
        metaField->setDefault(100);
    }
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 9);
        metaField->setDefault(7);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())IG_GFX_TEXTURE_FORMAT_GetMetaEnum;
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 10);
        metaField->setDefault(-2);
    }
    {
        igMemoryRefMetaField *metaField = (igMemoryRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 11);
        metaField->_memType = (int)Gap::Core::igUnsignedCharMetaField::getMetaField();
        metaField->setPool("Image");
    }
    {
        igMemoryRefMetaField *metaField = (igMemoryRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 12);
        metaField->_memType = (int)Gap::Core::igCharMetaField::getMetaField();
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 13);
        metaField->setDefault(1);
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 15);
        metaField->_metaObject = (int)Gap::Gfx::igClut::getClassTypeLazy();
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 17);
        metaField->setDefault(-1);
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
    *(void (**)())&_Meta->_abstractProxy = (void (*)())Gap::Gfx::igPsx2Image::getClassMetaSafe;
}
}
}

