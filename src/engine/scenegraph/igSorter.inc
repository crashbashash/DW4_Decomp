namespace Gap {
namespace Sg {

igMetaObject *igSorter::_Meta;
igMetaField *igSorter::k_dlist;
igMetaField *igSorter::k_mode;
igMetaField *igSorter::k_renderPackagePool;
igMetaField *igSorter::k_tmpAttrs;
igMetaField *igSorter::k_transpPackages;
igMetaField *igSorter::k_opaquePackages;
igMetaField *igSorter::k_firstPackages;
igMetaField *igSorter::k_lightAttrs;
igMetaField *igSorter::k_firstAttrs;
igMetaField *igSorter::k_transpAttrs;
igMetaField *igSorter::k_opaqueAttrs;
igMetaField *igSorter::k_firstPackageIndices;
igMetaField *igSorter::k_transpPackageIndices;
igMetaField *igSorter::k_opaquePackageIndices;
igMetaField *igSorter::k_depthWriteDisable;
igMetaField *igSorter::k_cullFaceFront;
igMetaField *igSorter::k_cullFaceBack;
igMetaField *igSorter::k_transparencyDrawMode;
igMetaField *igSorter::k_emptyRenderPackage;
igMetaField *igSorter::k_emptyRenderPackageList;
igMetaField *igSorter::k_emptyRenderPackageIndices;
igMetaField *igSorter::k_lastEmptyRenderPackageAttrs;
igMetaField *igSorter::k_firstEmptyRenderPackageAttrs;
igMetaField *igSorter::k_emptyGeometry;
igMetaField *igSorter::k_curList;
igMetaField *igSorter::k_prevList;
igMetaField *igSorter::k_isCompoundPackageOpen;
igMetaField *igSorter::k_isCompoundPackageTransparent;
igMetaField *igSorter::k_isCompoundPackageFirst;
igMetaField *igSorter::k_compoundPackage;
igMetaField *igSorter::k_compoundPackageNestCount;
igMetaField *igSorter::k_cachedPackage;
igMetaField *igSorter::k_outputCreated;
igMetaField *igSorter::k_useZSort;
igMetaField *igSorter::k_forceNoSeparate;
igMetaField *igSorter::k_printOutputState;

igMetaObject *igSorter::getClassTypeLazy()
{
    if (_Meta == 0)
        _Meta = igMetaObject_Create(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleMetaData));
    return _Meta;
}

igMetaObject *igSorter::getClassTypeSafe()
{
    if ((_Meta == 0) || !_Meta->isValid())
        arkRegister();
    return _Meta;
}

void *igSorter::retrieveVTablePointer()
{
    igSorter temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}

void igSorter::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igSorter::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Attrs::igDisplayListAttr::arkRegister, Gap::Sg::igRenderPackagePool::arkRegister, Gap::Attrs::igNonRefCountedAttrList::arkRegister, Gap::Sg::igRenderPackageList::arkRegister, Gap::Core::igIntList::arkRegister, Gap::Attrs::igDepthWriteStateAttr::arkRegister, Gap::Attrs::igCullFaceAttr::arkRegister, Gap::Sg::igRenderPackage::arkRegister, Gap::Sg::igGeometry::arkRegister, 0 };

    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Core::igObject::arkRegisterInternal,
        Gap::Core::igObject::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igSorter",
        sizeof(igSorter),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        0,
        regFunctions
    );
}

void igSorter::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igBoolMetaField_Create, igBoolMetaField_Create, igBoolMetaField_Create, igObjectRefMetaField_Create, (FieldFactory)Gap::Core::igIntMetaField::_instantiateFromPool, igObjectRefMetaField_Create, igBoolMetaField_Create, igBoolMetaField_Create, igBoolMetaField_Create, igBoolMetaField_Create };
    static const char *names[] = { "_dlist", "_mode", "_renderPackagePool", "_tmpAttrs", "_transpPackages", "_opaquePackages", "_firstPackages", "_lightAttrs", "_firstAttrs", "_transpAttrs", "_opaqueAttrs", "_firstPackageIndices", "_transpPackageIndices", "_opaquePackageIndices", "_depthWriteDisable", "_cullFaceFront", "_cullFaceBack", "_transparencyDrawMode", "_emptyRenderPackage", "_emptyRenderPackageList", "_emptyRenderPackageIndices", "_lastEmptyRenderPackageAttrs", "_firstEmptyRenderPackageAttrs", "_emptyGeometry", "_curList", "_prevList", "_isCompoundPackageOpen", "_isCompoundPackageTransparent", "_isCompoundPackageFirst", "_compoundPackage", "_compoundPackageNestCount", "_cachedPackage", "_outputCreated", "_useZSort", "_forceNoSeparate", "_printOutputState" };
    static igMetaField **enumStorage[] = { &k_dlist, &k_mode, &k_renderPackagePool, &k_tmpAttrs, &k_transpPackages, &k_opaquePackages, &k_firstPackages, &k_lightAttrs, &k_firstAttrs, &k_transpAttrs, &k_opaqueAttrs, &k_firstPackageIndices, &k_transpPackageIndices, &k_opaquePackageIndices, &k_depthWriteDisable, &k_cullFaceFront, &k_cullFaceBack, &k_transparencyDrawMode, &k_emptyRenderPackage, &k_emptyRenderPackageList, &k_emptyRenderPackageIndices, &k_lastEmptyRenderPackageAttrs, &k_firstEmptyRenderPackageAttrs, &k_emptyGeometry, &k_curList, &k_prevList, &k_isCompoundPackageOpen, &k_isCompoundPackageTransparent, &k_isCompoundPackageFirst, &k_compoundPackage, &k_compoundPackageNestCount, &k_cachedPackage, &k_outputCreated, &k_useZSort, &k_forceNoSeparate, &k_printOutputState };
    static int offsets[] = { 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60, 64, 68, 72, 76, 80, 84, 88, 92, 96, 100, 104, 108, 112, 113, 114, 116, 120, 124, 128, 129, 130, 131 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 36);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)Gap::Attrs::igDisplayListAttr::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->_metaObject = (int)Gap::Sg::igRenderPackagePool::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->_metaObject = (int)Gap::Attrs::igNonRefCountedAttrList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 4);
        metaField->_metaObject = (int)Gap::Sg::igRenderPackageList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 5);
        metaField->_metaObject = (int)Gap::Sg::igRenderPackageList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 6);
        metaField->_metaObject = (int)Gap::Sg::igRenderPackageList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 7);
        metaField->_metaObject = (int)Gap::Attrs::igDisplayListAttr::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 8);
        metaField->_metaObject = (int)Gap::Attrs::igDisplayListAttr::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 9);
        metaField->_metaObject = (int)Gap::Attrs::igDisplayListAttr::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 10);
        metaField->_metaObject = (int)Gap::Attrs::igDisplayListAttr::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 11);
        metaField->_metaObject = (int)Gap::Core::igIntList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 12);
        metaField->_metaObject = (int)Gap::Core::igIntList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 13);
        metaField->_metaObject = (int)Gap::Core::igIntList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 14);
        metaField->_metaObject = (int)Gap::Attrs::igDepthWriteStateAttr::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 15);
        metaField->_metaObject = (int)Gap::Attrs::igCullFaceAttr::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 16);
        metaField->_metaObject = (int)Gap::Attrs::igCullFaceAttr::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 18);
        metaField->_metaObject = (int)Gap::Sg::igRenderPackage::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 19);
        metaField->_metaObject = (int)Gap::Sg::igRenderPackageList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 20);
        metaField->_metaObject = (int)Gap::Core::igIntList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 21);
        metaField->_metaObject = (int)Gap::Attrs::igDisplayListAttr::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 22);
        metaField->_metaObject = (int)Gap::Attrs::igDisplayListAttr::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 23);
        metaField->_metaObject = (int)Gap::Sg::igGeometry::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 24);
        metaField->_metaObject = (int)Gap::Core::igIntList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 25);
        metaField->_metaObject = (int)Gap::Core::igIntList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 29);
        metaField->_metaObject = (int)Gap::Sg::igRenderPackage::getClassTypeLazy();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 31);
        metaField->_metaObject = (int)Gap::Sg::igRenderPackage::getClassTypeLazy();
        metaField->_refCounted = 0;
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 35);
        metaField->_persistent = 0;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
}
}
}

