namespace Gap {
namespace Attrs {

igMetaEnum *igTextureCubeAttr::ApplyType_Meta;
igMetaObject *igTextureCubeAttr::_Meta;
igMetaField *igTextureCubeAttr::k_cubeImage;
igMetaField *igTextureCubeAttr::k_applyType;
igMetaField *igTextureCubeAttr::k_unused;
}
}

static const char *g_igTextureCubeAttr_applyTypeNames[] = {
    "NOT_SET",
    "CUBE_MAP",
    "SPHERE_MAP",
};
static int g_igTextureCubeAttr_applyTypeValues[] = {
    0,
    1,
    2,
};

namespace Gap {
namespace Attrs {

igMetaEnum *igTextureCubeAttr::getApplyTypeMetaEnum() {
    if (ApplyType_Meta == 0) {
        ApplyType_Meta = Gap::Core::igMetaEnum::createMetaEnum("ApplyType", g_igTextureCubeAttr_applyTypeNames, g_igTextureCubeAttr_applyTypeValues, 3);
    }
    return ApplyType_Meta;
}

igMetaObject *igTextureCubeAttr::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igTextureCubeAttr::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igTextureCubeAttr::retrieveVTablePointer()
{
    igTextureCubeAttr temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igTextureCubeAttr::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igTextureCubeAttr::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Gfx::igImage::arkRegister, 0 };

    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Attrs::igTextureAttr::arkRegisterInternal,
        Gap::Attrs::igTextureAttr::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igTextureCubeAttr",
        sizeof(igTextureCubeAttr),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igTextureCubeAttr::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { (FieldFactory)Gap::Core::igObjectRefArrayMetaField::_instantiateFromPool, igEnumMetaField_Create, igIntMetaField_Create };
    static const char *names[] = { "_cubeImage", "_applyType", "_unused" };
    static igMetaField **enumStorage[] = { &k_cubeImage, &k_applyType, &k_unused };
    static int offsets[] = { 72, 96, 100 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 3);
    {
        igObjectRefArrayMetaField *metaField = (igObjectRefArrayMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)Gap::Gfx::igImage::getClassTypeLazy();
        metaField->_num = 6;
    }
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->setDefault(0);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())Gap::Attrs::igTextureCubeAttr::getApplyTypeMetaEnum;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

