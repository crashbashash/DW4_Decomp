namespace Gap {
namespace Sg {

CallbackArray *igCommonTraversal::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { igAttrStackManager_EnsureRegistered, igTransformStack_EnsureRegistered, Gap::Gfx::igVisualContext::arkRegister, Gap::Gfx::igCapabilityManager::arkRegister, Gap::Attrs::igAttrDefaultManager::arkRegister, Gap::Attrs::igNonRefCountedAttrList::arkRegister, igSorter_EnsureRegistered, igModelViewMatrixAttrPool_EnsureRegistered, igTimeAttrPool_EnsureRegistered, igVertexBlendMatrixAttrPool_EnsureRegistered, igTextureMatrixAttrPool_EnsureRegistered, igVertexBlendMatrixListAttrPool_EnsureRegistered, igMatrixObjectPool_EnsureRegistered, igProjectionMatrixAttrPool_EnsureRegistered, Gap::Attrs::igMatrixOptStateAttr::arkRegister, Gap::Attrs::igNormalizeNormalsStateAttr::arkRegister, igLongStack_EnsureRegistered, igNonRefCountedMatrixObjectList_EnsureRegistered, igNonRefCountedTransformList_EnsureRegistered, Gap::Core::igIntList::arkRegister, igStringObjList_EnsureRegistered, Gap::Sg::igNodeListList::arkRegister, igBlendMatricesAttrPool_EnsureRegistered, Gap::Attrs::igTimeAttr::arkRegister, 0 };

    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Sg::igTraversal::arkRegisterInternal,
        Gap::Sg::igTraversal::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igCommonTraversal",
        sizeof(igCommonTraversal),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        (igMetaObjectCallback)arkRegisterUser,
        regFunctions
    );
}

void igCommonTraversal::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, (FieldFactory)Gap::Math::igMatrix44fMetaField::_instantiateFromPool, (FieldFactory)Gap::Math::igMatrix44fMetaField::_instantiateFromPool, igIntMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, (FieldFactory)Gap::Core::igLongMetaField::_instantiateFromPool, igBoolMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, igObjectRefMetaField_Create, (FieldFactory)Gap::Math::igMatrix44fMetaField::_instantiateFromPool, igObjectRefMetaField_Create, igIntMetaField_Create, (FieldFactory)Gap::Math::igMatrix44fMetaField::_instantiateFromPool, (FieldFactory)Gap::Math::igMatrix44fMetaField::_instantiateFromPool, igBoolMetaField_Create };
    static const char *names[] = { "_attrStack", "_transformStack", "_vc", "_capabilityManager", "_defaultManager", "_flushedAttrs", "_sorter", "_matrixPool", "_timePool", "_blendMatrixPool", "_texMatPool", "_vertexBlendMatListPool", "_matrixObjectPool", "_projectionMatrixPool", "_viewMat", "_viewMatInv", "_modeMask", "_matrixOptimization", "_normalizeNormalsEnable", "_timeStack", "_matrixObjectList", "_timeLongBuf", "_timeBuffered", "_boneMatrixPaletteList", "_blendMatrixPaletteList", "_blendMatrixPaletteLengths", "_segmentOverrideNames", "_segmentOverrideStacks", "_blendMatricesAttrPool", "_projMat", "_defaultTimeAttr", "_jointChainCount", "_jointMvmBase", "_jointMvmInverseBase", "_jointGraphRootTraversed" };
    static igMetaField **enumStorage[] = { &k_attrStack, &k_transformStack, &k_vc, &k_capabilityManager, &k_defaultManager, &k_flushedAttrs, &k_sorter, &k_matrixPool, &k_timePool, &k_blendMatrixPool, &k_texMatPool, &k_vertexBlendMatListPool, &k_matrixObjectPool, &k_projectionMatrixPool, &k_viewMat, &k_viewMatInv, &k_modeMask, &k_matrixOptimization, &k_normalizeNormalsEnable, &k_timeStack, &k_matrixObjectList, &k_timeLongBuf, &k_timeBuffered, &k_boneMatrixPaletteList, &k_blendMatrixPaletteList, &k_blendMatrixPaletteLengths, &k_segmentOverrideNames, &k_segmentOverrideStacks, &k_blendMatricesAttrPool, &k_projMat, &k_defaultTimeAttr, &k_jointChainCount, &k_jointMvmBase, &k_jointMvmInverseBase, &k_jointGraphRootTraversed };
    static int offsets[] = { 52, 56, 60, 32, 36, 64, 68, 72, 76, 80, 84, 88, 92, 96, 100, 164, 228, 232, 236, 240, 244, 40, 48, 248, 252, 256, 260, 264, 268, 272, 336, 340, 344, 408, 49 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 35);
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->_metaObject = (int)igAttrStackManager_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 1);
        metaField->_metaObject = (int)igTransformStack_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 2);
        metaField->_metaObject = (int)igVisualContext::getClassTypeLazy();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->_metaObject = (int)igCapabilityManager::getClassTypeLazy();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 4);
        metaField->_metaObject = (int)igAttrDefaultManager::getClassTypeLazy();
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 5);
        metaField->_metaObject = (int)igNonRefCountedAttrList::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 6);
        metaField->_metaObject = (int)FUN_00196c10();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 7);
        metaField->_metaObject = (int)igModelViewMatrixAttrPool_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 8);
        metaField->_metaObject = (int)igTimeAttrPool_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 9);
        metaField->_metaObject = (int)igVertexBlendMatrixAttrPool_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 10);
        metaField->_metaObject = (int)igTextureMatrixAttrPool_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 11);
        metaField->_metaObject = (int)igVertexBlendMatrixListAttrPool_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 12);
        metaField->_metaObject = (int)igMatrixObjectPool_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 13);
        metaField->_metaObject = (int)igProjectionMatrixAttrPool_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    {
        igMatrix44fMetaField *metaField = (igMatrix44fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 14);
        metaField->setDefault(igMatrix44f(igVec4f(1.0f, 0.0f, 0.0f, 0.0f), igVec4f(0.0f, 1.0f, 0.0f, 0.0f),
                                                  igVec4f(0.0f, 0.0f, 1.0f, 0.0f), igVec4f(0.0f, 0.0f, 0.0f, 1.0f)));
    }
    {
        igMatrix44fMetaField *metaField = (igMatrix44fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 15);
        metaField->setDefault(igMatrix44f(igVec4f(1.0f, 0.0f, 0.0f, 0.0f), igVec4f(0.0f, 1.0f, 0.0f, 0.0f),
                                                  igVec4f(0.0f, 0.0f, 1.0f, 0.0f), igVec4f(0.0f, 0.0f, 0.0f, 1.0f)));
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 17);
        metaField->_metaObject = (int)igMatrixOptStateAttr::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 18);
        metaField->_metaObject = (int)igNormalizeNormalsStateAttr::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 19);
        metaField->_metaObject = (int)igLongStack_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 20);
        metaField->_metaObject = (int)igNonRefCountedMatrixObjectList_GetOrCreateMetaObject();
        metaField->_construct = 1;
        metaField->_persistent = 0;
    }
    {
        igLongMetaField *metaField = (igLongMetaField *)igMetaObject_GetFieldAt(metaObject, start + 21);
        metaField->setDefault(-1);
        metaField->_persistent = 0;
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 22);
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 23);
        metaField->_metaObject = (int)igNonRefCountedTransformList_GetOrCreateMetaObject();
        metaField->_construct = 1;
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 24);
        metaField->_metaObject = (int)igNonRefCountedTransformList_GetOrCreateMetaObject();
        metaField->_construct = 1;
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 25);
        metaField->_metaObject = (int)igIntList::getClassTypeLazy();
        metaField->_construct = 1;
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 26);
        metaField->_metaObject = (int)igStringObjList_GetOrCreateMetaObject();
        metaField->_construct = 1;
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 27);
        metaField->_metaObject = (int)igNodeListList::getClassTypeLazy();
        metaField->_construct = 1;
        metaField->_persistent = 0;
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 28);
        metaField->_metaObject = (int)igBlendMatricesAttrPool_GetOrCreateMetaObject();
        metaField->_construct = 1;
        metaField->_persistent = 0;
    }
    {
        igMatrix44fMetaField *metaField = (igMatrix44fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 29);
        metaField->setDefault(igMatrix44f(igVec4f(1.0f, 0.0f, 0.0f, 0.0f), igVec4f(0.0f, 1.0f, 0.0f, 0.0f),
                                                  igVec4f(0.0f, 0.0f, 1.0f, 0.0f), igVec4f(0.0f, 0.0f, 0.0f, 1.0f)));
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 30);
        metaField->_metaObject = (int)igTimeAttr::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igIntMetaField *metaField = (igIntMetaField *)igMetaObject_GetFieldAt(metaObject, start + 31);
        metaField->_persistent = 0;
    }
    {
        igMatrix44fMetaField *metaField = (igMatrix44fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 32);
        metaField->setDefault(igMatrix44f(igVec4f(1.0f, 0.0f, 0.0f, 0.0f), igVec4f(0.0f, 1.0f, 0.0f, 0.0f),
                                                  igVec4f(0.0f, 0.0f, 1.0f, 0.0f), igVec4f(0.0f, 0.0f, 0.0f, 1.0f)));
        metaField->_persistent = 0;
    }
    {
        igMatrix44fMetaField *metaField = (igMatrix44fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 33);
        metaField->setDefault(igMatrix44f(igVec4f(1.0f, 0.0f, 0.0f, 0.0f), igVec4f(0.0f, 1.0f, 0.0f, 0.0f),
                                                  igVec4f(0.0f, 0.0f, 1.0f, 0.0f), igVec4f(0.0f, 0.0f, 0.0f, 1.0f)));
        metaField->_persistent = 0;
    }
    {
        igBoolMetaField *metaField = (igBoolMetaField *)igMetaObject_GetFieldAt(metaObject, start + 34);
        metaField->_persistent = 0;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
    igMetaObject_AddExitCallback((int)thunk_igCommonTraversal_UserUnregister);
}
}
}

