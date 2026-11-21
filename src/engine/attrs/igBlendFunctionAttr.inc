namespace Gap {
namespace Attrs {

igMetaEnum *igBlendFunctionAttr::BLENDING_FUNCTION_ALPHA_PSX2_Meta;
igMetaEnum *igBlendFunctionAttr::BLENDING_FUNCTION_COLOR_PSX2_Meta;
igMetaObject *igBlendFunctionAttr::_Meta;
igMetaField *igBlendFunctionAttr::k_src;
igMetaField *igBlendFunctionAttr::k_dst;
igMetaField *igBlendFunctionAttr::k_eq;
igMetaField *igBlendFunctionAttr::k_blendEquationExt;
igMetaField *igBlendFunctionAttr::k_blendConstant;
igMetaField *igBlendFunctionAttr::k_blendStage;
igMetaField *igBlendFunctionAttr::k_blendConstantFloat;
igMetaField *igBlendFunctionAttr::k_blendA;
igMetaField *igBlendFunctionAttr::k_blendB;
igMetaField *igBlendFunctionAttr::k_blendC;
igMetaField *igBlendFunctionAttr::k_blendD;
}
}

static const char *g_igBlendFunctionAttr_alphaPsx2Names[] = {
    "IG_BLENDING_ALPHA_SOURCE",
    "IG_BLENDING_ALPHA_DESTINATION",
    "IG_BLENDING_ALPHA_FIX",
};
static int g_igBlendFunctionAttr_alphaPsx2Values[] = {
    0,
    1,
    2,
};

namespace Gap {
namespace Attrs {

igMetaEnum *igBlendFunctionAttr::getBLENDING_FUNCTION_ALPHA_PSX2MetaEnum() {
    if (BLENDING_FUNCTION_ALPHA_PSX2_Meta == 0) {
        BLENDING_FUNCTION_ALPHA_PSX2_Meta = igMetaEnum_Create("BLENDING_FUNCTION_ALPHA_PSX2", g_igBlendFunctionAttr_alphaPsx2Names, g_igBlendFunctionAttr_alphaPsx2Values, 3);
    }
    return BLENDING_FUNCTION_ALPHA_PSX2_Meta;
}
}
}

static const char *g_igBlendFunctionAttr_colorPsx2Names[] = {
    "IG_BLENDING_COLOR_SOURCE",
    "IG_BLENDING_COLOR_DESTINATION",
    "IG_BLENDING_COLOR_ZERO",
};
static int g_igBlendFunctionAttr_colorPsx2Values[] = {
    0,
    1,
    2,
};

namespace Gap {
namespace Attrs {

igMetaEnum *igBlendFunctionAttr::getBLENDING_FUNCTION_COLOR_PSX2MetaEnum() {
    if (BLENDING_FUNCTION_COLOR_PSX2_Meta == 0) {
        BLENDING_FUNCTION_COLOR_PSX2_Meta = igMetaEnum_Create("BLENDING_FUNCTION_COLOR_PSX2", g_igBlendFunctionAttr_colorPsx2Names, g_igBlendFunctionAttr_colorPsx2Values, 3);
    }
    return BLENDING_FUNCTION_COLOR_PSX2_Meta;
}

igBlendFunctionAttr *igBlendFunctionAttr::_instantiateFromPool(igMemoryPoolView *pool)
{
    arkRegister();
    return (igBlendFunctionAttr *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igBlendFunctionAttr::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igBlendFunctionAttr::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igBlendFunctionAttr::retrieveVTablePointer()
{
    igBlendFunctionAttr temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igBlendFunctionAttr::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igBlendFunctionAttr::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { igBlendEquationExt_EnsureRegistered, 0 };

    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Attrs::igVisualAttribute::arkRegisterInternal,
        Gap::Attrs::igVisualAttribute::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igBlendFunctionAttr",
        sizeof(igBlendFunctionAttr),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}
}
}

int g_igBlendFunctionAttr_srcDefault = 4;
int g_igBlendFunctionAttr_dstDefault = 5;
int g_igBlendFunctionAttr_blendBDefault = 2;
int g_igBlendFunctionAttr_blendCDefault = 2;
int g_igBlendFunctionAttr_blendDDefault = 1;

namespace Gap {
namespace Attrs {

void igBlendFunctionAttr::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igEnumMetaField_Create, igEnumMetaField_Create, igEnumMetaField_Create, igObjectRefMetaField_Create, (FieldFactory)Gap::Core::igUnsignedCharMetaField::_instantiateFromPool, igShortMetaField_Create, (FieldFactory)Gap::Core::igFloatMetaField::_instantiateFromPool, igEnumMetaField_Create, igEnumMetaField_Create, igEnumMetaField_Create, igEnumMetaField_Create };
    static const char *names[] = { "_src", "_dst", "_eq", "_blendEquationExt", "_blendConstant", "_blendStage", "_blendConstantFloat", "_blendA", "_blendB", "_blendC", "_blendD" };
    static igMetaField **enumStorage[] = { &k_src, &k_dst, &k_eq, &k_blendEquationExt, &k_blendConstant, &k_blendStage, &k_blendConstantFloat, &k_blendA, &k_blendB, &k_blendC, &k_blendD };
    static int offsets[] = { 12, 16, 20, 24, 28, 30, 32, 36, 40, 44, 48 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 11);
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->setDefault(4);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())IG_GFX_BLENDING_FUNCTION_GetMetaEnum;
    }
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->setDefault(5);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())IG_GFX_BLENDING_FUNCTION_GetMetaEnum;
    }
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->setDefault(0);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())igMetaEnum_GetEmpty;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->_metaObject = (int)igBlendEquationExt_GetOrCreateMetaObject();
        metaField->_deepCopyMethod = 1;
        metaField->_shallowCopyMethod = 1;
        metaField->_isAlikeShallowMethod = 3;
    }
    {
        igUnsignedCharMetaField *metaField = (igUnsignedCharMetaField *)igMetaObject_GetFieldAt(metaObject, start + 4);
        metaField->setDefault(0);
    }
    {
        igShortMetaField *metaField = (igShortMetaField *)igMetaObject_GetFieldAt(metaObject, start + 5);
        *(void (**)())&metaField->_invarianceFunction = (void (*)())Gap::Attrs::igBlendFunctionAttr::synchronizeCachedUnitID;
    }
    {
        igFloatMetaField *metaField = (igFloatMetaField *)igMetaObject_GetFieldAt(metaObject, start + 6);
        metaField->setDefault(0.0f);
        metaField->_persistent = 0;
        *(void (**)())&metaField->_invarianceFunction = (void (*)())Gap::Attrs::igBlendFunctionAttr::constantChanged;
    }
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 7);
        metaField->setDefault(0);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())Gap::Attrs::igBlendFunctionAttr::getBLENDING_FUNCTION_COLOR_PSX2MetaEnum;
    }
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 8);
        metaField->setDefault(2);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())Gap::Attrs::igBlendFunctionAttr::getBLENDING_FUNCTION_COLOR_PSX2MetaEnum;
    }
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 9);
        metaField->setDefault(2);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())Gap::Attrs::igBlendFunctionAttr::getBLENDING_FUNCTION_ALPHA_PSX2MetaEnum;
    }
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 10);
        metaField->setDefault(1);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())Gap::Attrs::igBlendFunctionAttr::getBLENDING_FUNCTION_COLOR_PSX2MetaEnum;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

