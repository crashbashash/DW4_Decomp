namespace Gap {
namespace Gfx {

igMetaObject *igPrimLengthArray::_Meta;
igMetaField *igPrimLengthArray::k_lengthData;
igMetaField *igPrimLengthArray::k_numStrips;
igMetaField *igPrimLengthArray::k_dataSize;

igPrimLengthArray *igPrimLengthArray::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igPrimLengthArray *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igPrimLengthArray::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igPrimLengthArray::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void igPrimLengthArray::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igPrimLengthArray::arkRegisterInternal()
{
    GfxLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        true,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igPrimLengthArray",
        sizeof(igPrimLengthArray),
        0,
        &arkRegisterInitialize,
        0,
        0
    );
}

void igPrimLengthArray::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igMemoryRefMetaField_Create, igUnsignedIntMetaField_Create, igUnsignedIntMetaField_Create };
    static const char *names[] = { "_lengthData", "_numStrips", "_dataSize" };
    static igMetaField **enumStorage[] = { &k_lengthData, &k_numStrips, &k_dataSize };
    static int offsets[] = { 8, 12, 16 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 3);
    {
        igMemoryRefMetaField *metaField = (igMemoryRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_memType = (int)Gap::Core::igUnsignedCharMetaField::getMetaField();
        metaField->_destruct = 1;
        metaField->_releaseOnCopy = 1;
        metaField->_releaseOnReset = 1;
    }
    {
        igUnsignedIntMetaField *metaField = (igUnsignedIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->setDefault(32);
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
    *(void (**)())&_Meta->_abstractProxy = (void (*)())Gap::Gfx::igPrimLengthArray1_1::getClassMetaSafe;
}
}
}

static const char *g_igPrimLengthArray_spriteTypeNames[] = {
    "IG_GFX_SPRITE_TYPE_NONE", "IG_GFX_SPRITE_TYPE_POINTS",
};
static int g_igPrimLengthArray_spriteTypeValues[] = {
    0, 1,
};
igMetaEnum *g_igPrimLengthArray_spriteTypeMetaEnum;

int IG_GFX_SPRITE_TYPE_GetMetaEnum(void) {
    if (g_igPrimLengthArray_spriteTypeMetaEnum == 0) {
        g_igPrimLengthArray_spriteTypeMetaEnum = (igMetaEnum *)Gap::Core::igMetaEnum::createMetaEnum("IG_GFX_SPRITE_TYPE", g_igPrimLengthArray_spriteTypeNames, g_igPrimLengthArray_spriteTypeValues, 2);
    }
    return (int)g_igPrimLengthArray_spriteTypeMetaEnum;
}

