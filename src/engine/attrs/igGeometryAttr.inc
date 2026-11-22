namespace Gap {
namespace Attrs {

igMetaObject *igGeometryAttr::_Meta;
igMetaField *igGeometryAttr::k_vertexArray;
igMetaField *igGeometryAttr::k_indexArray;
igMetaField *igGeometryAttr::k_primType;
igMetaField *igGeometryAttr::k_numPrims;
igMetaField *igGeometryAttr::k_offset;
igMetaField *igGeometryAttr::k_primLengths;
igMetaField *igGeometryAttr::k_handle;
igMetaField *igGeometryAttr::k_dPds;
igMetaField *igGeometryAttr::k_dPdt;
}
}

igGeometryAttr *igGeometryAttr_Create(int allocator) {
    Gap::Attrs::igGeometryAttr::arkRegister();
    return (igGeometryAttr *)igMetaObject_CreateInstance(Gap::Attrs::igGeometryAttr::getClassMeta(), (igMemoryPoolView *)allocator);
}

namespace Gap {
namespace Attrs {

igMetaObject *igGeometryAttr::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igGeometryAttr::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void igGeometryAttr::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igGeometryAttr::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Gfx::igVertexArray::arkRegister, Gap::Gfx::igIndexArray::arkRegister, Gap::Core::igUnsignedIntList::arkRegister, igVec3fList_EnsureRegistered, 0 };

    AttrsLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        true,
        &_Meta,
        Gap::Attrs::igVisualAttribute::arkRegisterInternal,
        Gap::Attrs::igVisualAttribute::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igGeometryAttr",
        sizeof(igGeometryAttr),
        0,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igGeometryAttr::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, igObjectRefMetaField_Create, igEnumMetaField_Create, igUnsignedIntMetaField_Create, igUnsignedIntMetaField_Create, igObjectRefMetaField_Create, igIntMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create };
    static const char *names[] = { "_vertexArray", "_indexArray", "_primType", "_numPrims", "_offset", "_primLengths", "_handle", "_dPds", "_dPdt" };
    static igMetaField **enumStorage[] = { &k_vertexArray, &k_indexArray, &k_primType, &k_numPrims, &k_offset, &k_primLengths, &k_handle, &k_dPds, &k_dPdt };
    static int offsets[] = { 12, 16, 20, 24, 28, 32, 36, 40, 44 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 9);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)Gap::Gfx::igVertexArray::getClassTypeLazy();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_metaObject = (int)Gap::Gfx::igIndexArray::getClassTypeLazy();
    }
    {
        igEnumMetaField *metaField = (igEnumMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->setDefault(0);
        *(void (**)())&metaField->_getMetaEnumFunction = (void (*)())IG_GFX_DRAW_GetMetaEnum;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 5);
        metaField->_metaObject = (int)Gap::Core::igUnsignedIntList::getClassTypeLazy();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 7);
        metaField->_metaObject = (int)igVec3fList_GetOrCreateMetaObject();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 8);
        metaField->_metaObject = (int)igVec3fList_GetOrCreateMetaObject();
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
    *(void (**)())&_Meta->_abstractProxy = (void (*)())igGeometryAttr1_5_GetMetaObjectFunction;
}
}
}

