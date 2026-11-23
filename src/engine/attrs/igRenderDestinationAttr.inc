namespace Gap {
namespace Attrs {

igMetaEnum *igRenderDestinationAttr::RENDERDESTINATION_TEXTURE_CREATE_MODE_Meta;
igMetaEnum *igRenderDestinationAttr::RENDERDESTINATION_CREATE_MODE_Meta;
igMetaObject *igRenderDestinationAttr::_Meta;
igMetaField *igRenderDestinationAttr::k_iCreateMode;
igMetaField *igRenderDestinationAttr::k_iTexCreateMode;
igMetaField *igRenderDestinationAttr::k_iRDHandle;
igMetaField *igRenderDestinationAttr::k_bEnabled;
igMetaField *igRenderDestinationAttr::k_iPrevRDHandle;
igMetaField *igRenderDestinationAttr::k_pTex;
igMetaField *igRenderDestinationAttr::k_iType;
igMetaField *igRenderDestinationAttr::k_iSizeX;
igMetaField *igRenderDestinationAttr::k_iSizeY;
igMetaField *igRenderDestinationAttr::k_iColorBitCount;
igMetaField *igRenderDestinationAttr::k_iAlphaBitCount;
igMetaField *igRenderDestinationAttr::k_iDepthBitCount;
igMetaField *igRenderDestinationAttr::k_iStencilBitCount;
igMetaField *igRenderDestinationAttr::k_vc;
}
}

static const char *g_igRenderDestinationAttr_textureCreateNames[] = {
    "RENDERDESTINATION_TEXTURE_CREATE_MODE_AUTO_CREATE",
    "RENDERDESTINATION_TEXTURE_CREATE_MODE_USE_SPECIFIED",
};
static int g_igRenderDestinationAttr_textureCreateValues[] = {
    0,
    1,
};

namespace Gap {
namespace Attrs {

igMetaEnum *igRenderDestinationAttr::getRENDERDESTINATION_TEXTURE_CREATE_MODEMetaEnum() {
    if (RENDERDESTINATION_TEXTURE_CREATE_MODE_Meta == 0) {
        RENDERDESTINATION_TEXTURE_CREATE_MODE_Meta = Gap::Core::igMetaEnum::createMetaEnum("RENDERDESTINATION_TEXTURE_CREATE_MODE", g_igRenderDestinationAttr_textureCreateNames, g_igRenderDestinationAttr_textureCreateValues, 2);
    }
    return RENDERDESTINATION_TEXTURE_CREATE_MODE_Meta;
}
}
}

static const char *g_igRenderDestinationAttr_createModeNames[] = {
    "RENDERDESTINATION_CREATE_MODE_INHERIT",
    "RENDERDESTINATION_CREATE_MODE_AUTONOMOUS",
    "RENDERDESTINATION_CREATE_MODE_USE_DEFAULT",
};
static int g_igRenderDestinationAttr_createModeValues[] = {
    0,
    1,
    2,
};

namespace Gap {
namespace Attrs {

igMetaEnum *igRenderDestinationAttr::getRENDERDESTINATION_CREATE_MODEMetaEnum() {
    if (RENDERDESTINATION_CREATE_MODE_Meta == 0) {
        RENDERDESTINATION_CREATE_MODE_Meta = Gap::Core::igMetaEnum::createMetaEnum("RENDERDESTINATION_CREATE_MODE", g_igRenderDestinationAttr_createModeNames, g_igRenderDestinationAttr_createModeValues, 3);
    }
    return RENDERDESTINATION_CREATE_MODE_Meta;
}

igRenderDestinationAttr *igRenderDestinationAttr::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igRenderDestinationAttr *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igRenderDestinationAttr::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igRenderDestinationAttr::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igRenderDestinationAttr::retrieveVTablePointer()
{
    igRenderDestinationAttr temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igRenderDestinationAttr::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igRenderDestinationAttr::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Attrs::igTextureAttr::arkRegister, Gap::Gfx::igVisualContext::arkRegister, 0 };

    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Attrs::igVisualAttribute::arkRegisterInternal,
        Gap::Attrs::igVisualAttribute::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igRenderDestinationAttr",
        sizeof(igRenderDestinationAttr),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}
}
}

int g_igRenderDestinationAttr_iTypeDefault = 1;

namespace Gap {
namespace Attrs {

void igRenderDestinationAttr::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igEnumMetaField_Create, igEnumMetaField_Create, igIntMetaField_Create, igBoolMetaField_Create, igIntMetaField_Create, igObjectRefMetaField_Create, igEnumMetaField_Create, igIntMetaField_Create, igIntMetaField_Create, igIntMetaField_Create, igIntMetaField_Create, igIntMetaField_Create, igIntMetaField_Create, igObjectRefMetaField_Create };
    static const char *names[] = { "_iCreateMode", "_iTexCreateMode", "_iRDHandle", "_bEnabled", "_iPrevRDHandle", "_pTex", "_iType", "_iSizeX", "_iSizeY", "_iColorBitCount", "_iAlphaBitCount", "_iDepthBitCount", "_iStencilBitCount", "_vc" };
    static igMetaField **enumStorage[] = { &k_iCreateMode, &k_iTexCreateMode, &k_iRDHandle, &k_bEnabled, &k_iPrevRDHandle, &k_pTex, &k_iType, &k_iSizeX, &k_iSizeY, &k_iColorBitCount, &k_iAlphaBitCount, &k_iDepthBitCount, &k_iStencilBitCount, &k_vc };
    static int offsets[] = { 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60, 64 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 14);
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->setDefault(0);
        metaField->_persistent = 0;
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())Gap::Attrs::igRenderDestinationAttr::getRENDERDESTINATION_CREATE_MODEMetaEnum;
    }
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->setDefault(0);
        metaField->_persistent = 0;
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())Gap::Attrs::igRenderDestinationAttr::getRENDERDESTINATION_TEXTURE_CREATE_MODEMetaEnum;
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->setDefault(-1);
        metaField->_persistent = 0;
        metaField->_deepCopyMethod = 4;
        metaField->_shallowCopyMethod = 4;
        metaField->_isAlikeShallowMethod = 3;
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->_persistent = 0;
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 4);
        metaField->setDefault(-1);
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 5);
        metaField->_metaObject = (int)Gap::Attrs::igTextureAttr::getClassTypeLazy();
        metaField->_persistent = 0;
    }
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 6);
        metaField->setDefault(1);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())IG_GFX_RENDERDESTINATION_TYPE_GetMetaEnum;
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 7);
        metaField->setDefault(-1);
        metaField->_persistent = 0;
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 8);
        metaField->setDefault(-1);
        metaField->_persistent = 0;
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 9);
        metaField->setDefault(-1);
        metaField->_persistent = 0;
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 10);
        metaField->setDefault(-1);
        metaField->_persistent = 0;
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 11);
        metaField->setDefault(-1);
        metaField->_persistent = 0;
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 12);
        metaField->setDefault(-1);
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 13);
        metaField->_metaObject = (int)Gap::Gfx::igVisualContext::getClassTypeLazy();
        metaField->_persistent = 0;
        metaField->_deepCopyMethod = 1;
        metaField->_shallowCopyMethod = 1;
        metaField->_isAlikeShallowMethod = 3;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

