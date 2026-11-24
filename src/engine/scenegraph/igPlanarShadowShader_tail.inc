namespace Gap {
namespace Sg {

void igPlanarShadowShader::userConstruct(int arg1) {
    igNode_userConstruct((void * *)(void * *)this, arg1);
    if (igMetaObject_CountInstances((igMetaObject *)(((DW4VC_88_0 *)((void * *)this))->vX()), 1) == 0) {
        DAT_00562798[0] = (void **)(((void * *)Gap::Attrs::igBlendFunctionAttr::_instantiateFromPool(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem))));
        DAT_005627a0[0] = (void **)(((void * *)Gap::Attrs::igBlendFunctionAttr::_instantiateFromPool(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem))));
        ((DW4VC_128_1 *)(DAT_005627a0[0]))->vX((int)(0));
        ((DW4VC_132_1 *)(DAT_005627a0[0]))->vX((int)(0));
        DAT_005627a8[0] = (void **)(((void * *)Gap::Attrs::igBlendStateAttr::_instantiateFromPool(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem))));
        ((DW4VC_128_1 *)(DAT_005627a8[0]))->vX((int)(1));
        DAT_005627b0[0] = (void **)(((void * *)Gap::Attrs::igLightingStateAttr::_instantiateFromPool(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem))));
        ((DW4VC_128_1 *)(DAT_005627b0[0]))->vX((int)(0));
        DAT_005627b8[0] = (void **)(((void * *)Gap::Attrs::igTextureStateAttr::_instantiateFromPool(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem))));
        ((DW4VC_128_1 *)(DAT_005627b8[0]))->vX((int)(0));
        DAT_005627c8[0] = (void **)(((void * *)Gap::Attrs::igAlphaStateAttr::_instantiateFromPool(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem))));
        ((DW4VC_128_1 *)(DAT_005627c8[0]))->vX((int)(0));
        DAT_005627c0[0] = (void *)(Gap::Attrs::igGeometryMaskAttr::_instantiateFromPool(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem)));
        *(int *)((char *)(DAT_005627c0[0]) + 12) = 1;
        DAT_005627d0[0] = (void **)(Gap::Attrs::igStencilFunctionAttr::_instantiateFromPool(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem)));
        ((DW4VC_128_1 *)(DAT_005627d0[0]))->vX((int)(1));
        ((DW4VC_136_1 *)(DAT_005627d0[0]))->vX((int)(2));
        ((DW4VC_140_3 *)(DAT_005627d0[0]))->vX((int)(0), (int)(3), (int)(3));
        DAT_005627d8[0] = (void **)(Gap::Attrs::igCullFaceAttr::_instantiateFromPool(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem)));
        ((DW4VC_132_1 *)(DAT_005627d8[0]))->vX((int)(0));
    }
}

void igPlanarShadowShader::userDestruct()
{
    Obj_1d39b0 *o;
    if (igMetaObject_CountInstances((igMetaObject *)(((T_1d39b0 *)this)->vX()), 1) == 0) {
        o = ((Obj_1d39b0 * *)DAT_00562798)[0];
        if (o != 0) {
            o->references = o->references - 1;
            if (((unsigned long long)((long long)o->references << 0x29) >> 0x29) == 0) {
                igObject_Destroy((::igObject *)o);
            }
        }
        o = ((Obj_1d39b0 * *)DAT_005627a0)[0];
        if (o != 0) {
            o->references = o->references - 1;
            if (((unsigned long long)((long long)o->references << 0x29) >> 0x29) == 0) {
                igObject_Destroy((::igObject *)o);
            }
        }
        o = ((Obj_1d39b0 * *)DAT_005627a8)[0];
        if (o != 0) {
            o->references = o->references - 1;
            if (((unsigned long long)((long long)o->references << 0x29) >> 0x29) == 0) {
                igObject_Destroy((::igObject *)o);
            }
        }
        o = ((Obj_1d39b0 * *)DAT_005627b0)[0];
        if (o != 0) {
            o->references = o->references - 1;
            if (((unsigned long long)((long long)o->references << 0x29) >> 0x29) == 0) {
                igObject_Destroy((::igObject *)o);
            }
        }
        o = ((Obj_1d39b0 * *)DAT_005627b8)[0];
        if (o != 0) {
            o->references = o->references - 1;
            if (((unsigned long long)((long long)o->references << 0x29) >> 0x29) == 0) {
                igObject_Destroy((::igObject *)o);
            }
        }
        o = ((Obj_1d39b0 * *)DAT_005627c8)[0];
        if (o != 0) {
            o->references = o->references - 1;
            if (((unsigned long long)((long long)o->references << 0x29) >> 0x29) == 0) {
                igObject_Destroy((::igObject *)o);
            }
        }
        o = ((Obj_1d39b0 * *)DAT_005627c0)[0];
        if (o != 0) {
            o->references = o->references - 1;
            if (((unsigned long long)((long long)o->references << 0x29) >> 0x29) == 0) {
                igObject_Destroy((::igObject *)o);
            }
        }
        o = ((Obj_1d39b0 * *)DAT_005627d0)[0];
        if (o != 0) {
            o->references = o->references - 1;
            if (((unsigned long long)((long long)o->references << 0x29) >> 0x29) == 0) {
                igObject_Destroy((::igObject *)o);
            }
        }
        o = ((Obj_1d39b0 * *)DAT_005627d8)[0];
        if (o != 0) {
            o->references = o->references - 1;
            if (((unsigned long long)((long long)o->references << 0x29) >> 0x29) == 0) {
                igObject_Destroy((::igObject *)o);
            }
        }
    }
    igGroup_userDestruct((T_1c5e20 *)this);
}

void igPlanarShadowShader::appendGeometry(igGeometry *geom, igModelViewMatrixAttr *mvm, igAttr *blend)
{
    _geoms->append(geom);
    _mats->append(mvm);
    _blendmats->append(blend);
}

void igPlanarShadowShader::shade(igCommonTraversal *arg1) {
    int sp70[16];
    igAttrStackManager *s1 = (igAttrStackManager *)arg1->_attrStack;
    int i;
    ((VA_1d3e20 *)_shadowColorAttr.get())->v30(_shadowColor.vec);
    ((VB *)_stencilState.get())->v30(_shadowUseStencil);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)s1, (::igAttr *)((int *)DAT_005627a8)[0]);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)s1, (::igAttr *)((int *)DAT_005627b0)[0]);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)s1, (::igAttr *)((int *)DAT_005627b8)[0]);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)s1, (::igAttr *)_shadowColorAttr.get());
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)s1, (::igAttr *)((int *)DAT_005627c8)[0]);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)s1, (::igAttr *)((int *)DAT_005627c0)[0]);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)s1, (::igAttr *)_stencilState.get());
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)s1, (::igAttr *)((int *)DAT_005627d0)[0]);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)s1, (::igAttr *)((int *)DAT_005627d8)[0]);
    if (_shadowUseBlend != 0) {
        igAttrStackManager_PushOverrideAttr((igAttrStackManager *)s1, (::igAttr *)((int *)DAT_00562798)[0]);
    } else {
        igAttrStackManager_PushOverrideAttr((igAttrStackManager *)s1, (::igAttr *)((int *)DAT_005627a0)[0]);
    }
    FUN_001d3c60((::igPlanarShadowShader *)this, (::igCommonTraversal *)arg1);
    for (i = 0; i < ((::igDataList *)_lights.get())->_count; i++) {
        if (igAttrStackManager_IsLightEnabled((igAttrStackManager *)s1, ((::igLightAttr **)((::igDataList *)_lights.get())->_data)[i]) != 0) {
            int *m = (int *)((int *)((::igDataList *)_mvmList.get())->_data)[i];
            igAttrStack *nd;
            int *s5;
            igObjectPool *pool;
            char *o;
            igMatrix44f_Copy((float *)sp70, (const float *)&arg1->_viewMatInv);
            igMatrix44f_Multiply((float *)sp70, (const float *)sp70, (const float *)((char *)m + 12));
            igMatrix44f_Multiply((float *)sp70, (const float *)sp70, (const float *)&arg1->_viewMat);
            nd = (igAttrStack *)((int *)((::igObjectList *)s1->_attrStacks)->_data)[((int *)s1->_attrStackIndexTable)[((igMetaObject *)Gap::Attrs::igProjectionMatrixAttr::getClassMeta())->_id]];
            if (nd->_cachedOverride >= 0) {
                s5 = (int *)((int *)nd->_data)[nd->_cachedOverride];
            } else if (nd->_count != 0) {
                int k = nd->_count - 1;
                s5 = (int *)((int *)nd->_data)[k];
            } else {
                s5 = (int *)nd->_default;
            }
            pool = (igObjectPool *)arg1->_projectionMatrixPool.get();
            if (pool->_freeIndex >= pool->_count) igObjectPool_Grow((igObjectPool *)pool, (::igObject *(*)(int))((void *)&Gap::Attrs::igProjectionMatrixAttr::_instantiateFromPool));
            o = (char *)((int *)pool->_data)[pool->_freeIndex++];
            igMatrix44f_Multiply((float *)(o + 12), (const float *)sp70, (const float *)((char *)s5 + 12));
            FUN_001b1030((igAttrStackManager *)s1, (::igAttr *)o);
            igTraversal_TraverseChildren((::igTraversal *)arg1, (::igNode *)this);
            FUN_001b1100((struct A_1b1100 *)s1, (struct B_1b1100 *)o);
        }
    }
    if (_shadowUseBlend != 0) {
        igAttrStackManager_PopOverrideAttr((igAttrStackManager *)s1, (::igAttr *)((int *)DAT_00562798)[0]);
    } else {
        igAttrStackManager_PopOverrideAttr((igAttrStackManager *)s1, (::igAttr *)((int *)DAT_005627a0)[0]);
    }
    igAttrStackManager_PopOverrideAttr((igAttrStackManager *)s1, (::igAttr *)((int *)DAT_005627d8)[0]);
    igAttrStackManager_PopOverrideAttr((igAttrStackManager *)s1, (::igAttr *)((int *)DAT_005627d0)[0]);
    igAttrStackManager_PopOverrideAttr((igAttrStackManager *)s1, (::igAttr *)_stencilState.get());
    igAttrStackManager_PopOverrideAttr((igAttrStackManager *)s1, (::igAttr *)((int *)DAT_005627c0)[0]);
    igAttrStackManager_PopOverrideAttr((igAttrStackManager *)s1, (::igAttr *)((int *)DAT_005627c8)[0]);
    igAttrStackManager_PopOverrideAttr((igAttrStackManager *)s1, (::igAttr *)_shadowColorAttr.get());
    igAttrStackManager_PopOverrideAttr((igAttrStackManager *)s1, (::igAttr *)((int *)DAT_005627b8)[0]);
    igAttrStackManager_PopOverrideAttr((igAttrStackManager *)s1, (::igAttr *)((int *)DAT_005627b0)[0]);
    igAttrStackManager_PopOverrideAttr((igAttrStackManager *)s1, (::igAttr *)((int *)DAT_005627a8)[0]);
}
}
}

