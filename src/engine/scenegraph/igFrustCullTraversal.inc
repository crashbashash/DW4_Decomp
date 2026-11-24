namespace Gap {
namespace Sg {

igFrustCullTraversal *igFrustCullTraversal::_instantiateFromPool(igMemoryPoolView *pool) {
    arkRegister();
    return (igFrustCullTraversal *)igMetaObject_CreateInstance(_Meta, pool);
}

igMetaObject *igFrustCullTraversal::_Meta;
igMetaField *igFrustCullTraversal::k_compMat;
igMetaField *igFrustCullTraversal::k_curMVMat;
igMetaField *igFrustCullTraversal::k_curProjectionMat;
igMetaField *igFrustCullTraversal::k_cd;
igMetaField *igFrustCullTraversal::k_outerFrustCullScale;
igMetaField *igFrustCullTraversal::k_outerScissorWindowScale;
igMetaField *igFrustCullTraversal::k_boundingBox;
igTraversalFunctionList *igFrustCullTraversal::travProcs;

igMetaObject *igFrustCullTraversal::getClassTypeSafe()
{
    igMetaObject *g = _Meta;
    if (!g || ((g->_validity & 4) != 0) == false)
        arkRegister();
    return _Meta;
}

void *igFrustCullTraversal::retrieveVTablePointer()
{
    igFrustCullTraversal temporary;
    return *(void **)(((char *)&temporary) + g_objectSystem->vtableProbeOffset);
}
}
}

namespace Gap {
namespace Sg {

void igFrustCullTraversal::arkRegister()
{
    igMetaObject_RunStaticInit(arkRegisterInternal);
}

CallbackArray *igFrustCullTraversal::arkRegisterInternal()
{
    static igMetaObjectCallback regFunctions[] = { Gap::Attrs::igClippingStateAttr::arkRegister, igAABox_EnsureRegistered, 0 };

    SceneGraphLibrary_MarkRegistered();
    return igMetaObject_RegisterClass(
        false,
        &_Meta,
        Gap::Sg::igCommonTraversal::arkRegisterInternal,
        Gap::Sg::igCommonTraversal::getClassMeta,
        (igMetaObjectCallback)getClassMetaSafe,
        "igFrustCullTraversal",
        sizeof(igFrustCullTraversal),
        (igMetaObjectGetVTableFunction)retrieveVTablePointer,
        &arkRegisterInitialize,
        (igMetaObjectCallback)arkRegisterUser,
        regFunctions
    );
}

igMetaObject *igCommonTraversal::_Meta;
igMetaField *igCommonTraversal::k_attrStack;
igMetaField *igCommonTraversal::k_transformStack;
igMetaField *igCommonTraversal::k_vc;
igMetaField *igCommonTraversal::k_capabilityManager;
igMetaField *igCommonTraversal::k_defaultManager;
igMetaField *igCommonTraversal::k_flushedAttrs;
igMetaField *igCommonTraversal::k_sorter;
igMetaField *igCommonTraversal::k_matrixPool;
igMetaField *igCommonTraversal::k_timePool;
igMetaField *igCommonTraversal::k_blendMatrixPool;
igMetaField *igCommonTraversal::k_texMatPool;
igMetaField *igCommonTraversal::k_vertexBlendMatListPool;
igMetaField *igCommonTraversal::k_matrixObjectPool;
igMetaField *igCommonTraversal::k_projectionMatrixPool;
igMetaField *igCommonTraversal::k_viewMat;
igMetaField *igCommonTraversal::k_viewMatInv;
igMetaField *igCommonTraversal::k_modeMask;
igMetaField *igCommonTraversal::k_matrixOptimization;
igMetaField *igCommonTraversal::k_normalizeNormalsEnable;
igMetaField *igCommonTraversal::k_timeStack;
igMetaField *igCommonTraversal::k_matrixObjectList;
igMetaField *igCommonTraversal::k_timeLongBuf;
igMetaField *igCommonTraversal::k_timeBuffered;
igMetaField *igCommonTraversal::k_boneMatrixPaletteList;
igMetaField *igCommonTraversal::k_blendMatrixPaletteList;
igMetaField *igCommonTraversal::k_blendMatrixPaletteLengths;
igMetaField *igCommonTraversal::k_segmentOverrideNames;
igMetaField *igCommonTraversal::k_segmentOverrideStacks;
igMetaField *igCommonTraversal::k_blendMatricesAttrPool;
igMetaField *igCommonTraversal::k_projMat;
igMetaField *igCommonTraversal::k_defaultTimeAttr;
igMetaField *igCommonTraversal::k_jointChainCount;
igMetaField *igCommonTraversal::k_jointMvmBase;
igMetaField *igCommonTraversal::k_jointMvmInverseBase;
igMetaField *igCommonTraversal::k_jointGraphRootTraversed;
igTraversalFunctionList *igCommonTraversal::travProcs;

void igFrustCullTraversal::arkRegisterInitialize()
{
    static FieldFactory instFuncs[] = { (FieldFactory)Gap::Math::igMatrix44fMetaField::_instantiateFromPool, igRawRefMetaField_Create, igRawRefMetaField_Create, igObjectRefMetaField_Create, igFloatMetaField_Create, igFloatMetaField_Create, igObjectRefMetaField_Create };
    static const char *names[] = { "_compMat", "_curMVMat", "_curProjectionMat", "_cd", "_outerFrustCullScale", "_outerScissorWindowScale", "_boundingBox" };
    static igMetaField **enumStorage[] = { &k_compMat, &k_curMVMat, &k_curProjectionMat, &k_cd, &k_outerFrustCullScale, &k_outerScissorWindowScale, &k_boundingBox };
    static int offsets[] = { 476, 540, 544, 548, 552, 556, 472 };
    igMetaObject *metaObject = _Meta;	// cache in a local variable
    int start = igMetaObject_GetFieldCount(metaObject);

    igMetaObject_CreateFields(metaObject, instFuncs, 7);
    {
        igMatrix44fMetaField *metaField = (igMatrix44fMetaField *)igMetaObject_GetFieldAt(metaObject, start + 0);
        metaField->setDefault(igMatrix44f(igVec4f(1.0f, 0.0f, 0.0f, 0.0f), igVec4f(0.0f, 1.0f, 0.0f, 0.0f),
                                                  igVec4f(0.0f, 0.0f, 1.0f, 0.0f), igVec4f(0.0f, 0.0f, 0.0f, 1.0f)));
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 3);
        metaField->_metaObject = (int)igClippingStateAttr::getClassTypeLazy();
        metaField->_construct = 1;
    }
    {
        igFloatMetaField *metaField = (igFloatMetaField *)igMetaObject_GetFieldAt(metaObject, start + 4);
        metaField->setDefault(1.0f);
    }
    {
        igFloatMetaField *metaField = (igFloatMetaField *)igMetaObject_GetFieldAt(metaObject, start + 5);
        metaField->setDefault(2.0f);
    }
    {
        igObjectRefMetaField *metaField = (igObjectRefMetaField *)igMetaObject_GetFieldAt(metaObject, start + 6);
        metaField->_metaObject = (int)igAABox_GetOrCreateMetaObject();
        metaField->_construct = 1;
    }
    igMetaObject_NameFields(metaObject, names, enumStorage, offsets, start);
    igMetaObject_AddExitCallback((int)thunk_FUN_001c45d0);
}

void igFrustCullTraversal::arkRegisterUser() {
    userRegister();
    igMetaObject_AddRegistrationCallback((int)((int *)registerClass));
}
}
}

void thunk_FUN_001c45d0(void) {
    Gap::Sg::igFrustCullTraversal::userUnregister();
}

