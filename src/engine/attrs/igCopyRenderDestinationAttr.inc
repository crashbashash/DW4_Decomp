namespace Gap {
namespace Attrs {

igMetaEnum *igCopyRenderDestinationAttr::CopyType_Meta;
igMetaObject *igCopyRenderDestinationAttr::_Meta;
igMetaField *igCopyRenderDestinationAttr::k_copyType;
igMetaField *igCopyRenderDestinationAttr::k_pRDAttr;
igMetaField *igCopyRenderDestinationAttr::k_pImage;
igMetaField *igCopyRenderDestinationAttr::k_pTextureAttr;
igMetaField *igCopyRenderDestinationAttr::k_sourceX;
igMetaField *igCopyRenderDestinationAttr::k_sourceY;
igMetaField *igCopyRenderDestinationAttr::k_destinationX;
igMetaField *igCopyRenderDestinationAttr::k_destinationY;
igMetaField *igCopyRenderDestinationAttr::k_sizeW;
igMetaField *igCopyRenderDestinationAttr::k_sizeH;
}
}

static const char *g_igCopyRenderDestinationAttr_copyTypeNames[] = {
    "NOT_SET",
    "FROM_RENDERDESTINATION_TO_TEXTURE",
    "FROM_RENDERDESTINATION_TO_MEMORY",
    "FROM_RENDERDESTINATION_DEPTH_TO_TEXTURE",
    "FROM_RENDERDESTINATION_DEPTH_TO_MEMORY",
};
static int g_igCopyRenderDestinationAttr_copyTypeValues[] = {
    0,
    1,
    2,
    3,
    4,
};

namespace Gap {
namespace Attrs {

igMetaEnum *igCopyRenderDestinationAttr::getCopyTypeMetaEnum() {
    if (CopyType_Meta == 0) {
        CopyType_Meta = Gap::Core::igMetaEnum::createMetaEnum("CopyType", g_igCopyRenderDestinationAttr_copyTypeNames, g_igCopyRenderDestinationAttr_copyTypeValues, 5);
    }
    return CopyType_Meta;
}

igMetaObject *igCopyRenderDestinationAttr::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igCopyRenderDestinationAttr::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igCopyRenderDestinationAttr::retrieveVTablePointer()
{
    igCopyRenderDestinationAttr temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igCopyRenderDestinationAttr::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igCopyRenderDestinationAttr::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Attrs::igRenderDestinationAttr::arkRegister, igImage_EnsureRegistered, Gap::Attrs::igTextureAttr::arkRegister, 0 };

    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Attrs::igVisualAttribute::arkRegisterInternal,
        Gap::Attrs::igVisualAttribute::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igCopyRenderDestinationAttr",
        sizeof(igCopyRenderDestinationAttr),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igCopyRenderDestinationAttr::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igEnumMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igIntMetaField_Create, igIntMetaField_Create, igIntMetaField_Create, igIntMetaField_Create, igIntMetaField_Create, igIntMetaField_Create };
    static const char *names[] = { "_copyType", "_pRDAttr", "_pImage", "_pTextureAttr", "_sourceX", "_sourceY", "_destinationX", "_destinationY", "_sizeW", "_sizeH" };
    static igMetaField **enumStorage[] = { &k_copyType, &k_pRDAttr, &k_pImage, &k_pTextureAttr, &k_sourceX, &k_sourceY, &k_destinationX, &k_destinationY, &k_sizeW, &k_sizeH };
    static int offsets[] = { 12, 16, 20, 24, 28, 32, 36, 40, 44, 48 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 10);
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->setDefault(0);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())Gap::Attrs::igCopyRenderDestinationAttr::getCopyTypeMetaEnum;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_metaObject = (int)Gap::Attrs::igRenderDestinationAttr::getClassTypeLazy();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->_metaObject = (int)igImage_GetOrCreateMetaObject();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->_metaObject = (int)Gap::Attrs::igTextureAttr::getClassTypeLazy();
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

