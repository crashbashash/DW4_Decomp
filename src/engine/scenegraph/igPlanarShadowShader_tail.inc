void Gap__Sg__igPlanarShadowShader__vfunc_09(void **arg0, int arg1) {
    Gap__Sg__igNode__vfunc_09((void * *)arg0, arg1);
    if (igMetaObject_CountInstances(((DW4VC_88_0 *)(arg0))->vX(), 1) == 0) {
        DAT_00562798[0] = (void **)(((void * *)FUN_00139ed0(Memory_GetAllocatorBySelector(DAT_00587038[0]))));
        DAT_005627a0[0] = (void **)(((void * *)FUN_00139ed0(Memory_GetAllocatorBySelector(DAT_00587038[0]))));
        ((DW4VC_128_1 *)(DAT_005627a0[0]))->vX((int)(0));
        ((DW4VC_132_1 *)(DAT_005627a0[0]))->vX((int)(0));
        DAT_005627a8[0] = (void **)(((void * *)FUN_00139600(Memory_GetAllocatorBySelector(DAT_00587038[0]))));
        ((DW4VC_128_1 *)(DAT_005627a8[0]))->vX((int)(1));
        DAT_005627b0[0] = (void **)(((void * *)FUN_00135e20(Memory_GetAllocatorBySelector(DAT_00587038[0]))));
        ((DW4VC_128_1 *)(DAT_005627b0[0]))->vX((int)(0));
        DAT_005627b8[0] = (void **)(((void * *)FUN_00131390(Memory_GetAllocatorBySelector(DAT_00587038[0]))));
        ((DW4VC_128_1 *)(DAT_005627b8[0]))->vX((int)(0));
        DAT_005627c8[0] = (void **)(((void * *)FUN_0013b270(Memory_GetAllocatorBySelector(DAT_00587038[0]))));
        ((DW4VC_128_1 *)(DAT_005627c8[0]))->vX((int)(0));
        DAT_005627c0[0] = (void *)(FUN_00137070(Memory_GetAllocatorBySelector(DAT_00587038[0])));
        *(int *)((char *)(DAT_005627c0[0]) + 12) = 1;
        DAT_005627d0[0] = (void **)(FUN_00133610(Memory_GetAllocatorBySelector(DAT_00587038[0])));
        ((DW4VC_128_1 *)(DAT_005627d0[0]))->vX((int)(1));
        ((DW4VC_136_1 *)(DAT_005627d0[0]))->vX((int)(2));
        ((DW4VC_140_3 *)(DAT_005627d0[0]))->vX((int)(0), (int)(3), (int)(3));
        DAT_005627d8[0] = (void **)(FUN_00138690(Memory_GetAllocatorBySelector(DAT_00587038[0])));
        ((DW4VC_132_1 *)(DAT_005627d8[0]))->vX((int)(0));
    }
}

int Gap__Sg__igPlanarShadowShader__vfunc_22(void) {
    return ((int *)g_igPlanarShadowShader_metaObject)[0];
}

void Gap__Sg__igPlanarShadowShader__vfunc_10(T_1d39b0 *arg0)
{
    Obj_1d39b0 *o;
    if (igMetaObject_CountInstances(arg0->vX(), 1) == 0) {
        o = ((Obj_1d39b0 * *)DAT_00562798)[0];
        if (o != 0) {
            o->references = o->references - 1;
            if (((unsigned long long)((long long)o->references << 0x29) >> 0x29) == 0) {
                igObject_Destroy(o);
            }
        }
        o = ((Obj_1d39b0 * *)DAT_005627a0)[0];
        if (o != 0) {
            o->references = o->references - 1;
            if (((unsigned long long)((long long)o->references << 0x29) >> 0x29) == 0) {
                igObject_Destroy(o);
            }
        }
        o = ((Obj_1d39b0 * *)DAT_005627a8)[0];
        if (o != 0) {
            o->references = o->references - 1;
            if (((unsigned long long)((long long)o->references << 0x29) >> 0x29) == 0) {
                igObject_Destroy(o);
            }
        }
        o = ((Obj_1d39b0 * *)DAT_005627b0)[0];
        if (o != 0) {
            o->references = o->references - 1;
            if (((unsigned long long)((long long)o->references << 0x29) >> 0x29) == 0) {
                igObject_Destroy(o);
            }
        }
        o = ((Obj_1d39b0 * *)DAT_005627b8)[0];
        if (o != 0) {
            o->references = o->references - 1;
            if (((unsigned long long)((long long)o->references << 0x29) >> 0x29) == 0) {
                igObject_Destroy(o);
            }
        }
        o = ((Obj_1d39b0 * *)DAT_005627c8)[0];
        if (o != 0) {
            o->references = o->references - 1;
            if (((unsigned long long)((long long)o->references << 0x29) >> 0x29) == 0) {
                igObject_Destroy(o);
            }
        }
        o = ((Obj_1d39b0 * *)DAT_005627c0)[0];
        if (o != 0) {
            o->references = o->references - 1;
            if (((unsigned long long)((long long)o->references << 0x29) >> 0x29) == 0) {
                igObject_Destroy(o);
            }
        }
        o = ((Obj_1d39b0 * *)DAT_005627d0)[0];
        if (o != 0) {
            o->references = o->references - 1;
            if (((unsigned long long)((long long)o->references << 0x29) >> 0x29) == 0) {
                igObject_Destroy(o);
            }
        }
        o = ((Obj_1d39b0 * *)DAT_005627d8)[0];
        if (o != 0) {
            o->references = o->references - 1;
            if (((unsigned long long)((long long)o->references << 0x29) >> 0x29) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    FUN_001c5e20((T_1c5e20 *)arg0);
}

void Gap__Sg__igPlanarShadowShader__vfunc_39(igPlanarShadowShader *arg0, int dummy1, int arg2, int arg3) {
    ObjectList_AppendRetained(arg0->_geoms);
    ObjectList_AppendRetained(arg0->_mats, arg2);
    ObjectList_AppendRetained(arg0->_blendmats, arg3);
}

void FUN_001d3e20(igPlanarShadowShader *arg0, igCommonTraversal *arg1) {
    int sp70[16];
    igAttrStackManager *s1 = (igAttrStackManager *)arg1->_attrStack;
    int i;
    ((VA_1d3e20 *)arg0->_shadowColorAttr)->v30(arg0->_shadowColor);
    ((VB *)arg0->_stencilState)->v30(arg0->_shadowUseStencil);
    FUN_001b12f0((igAttrStackManager *)s1, (igAttr *)((int *)DAT_005627a8)[0]);
    FUN_001b12f0((igAttrStackManager *)s1, (igAttr *)((int *)DAT_005627b0)[0]);
    FUN_001b12f0((igAttrStackManager *)s1, (igAttr *)((int *)DAT_005627b8)[0]);
    FUN_001b12f0((igAttrStackManager *)s1, (igAttr *)arg0->_shadowColorAttr);
    FUN_001b12f0((igAttrStackManager *)s1, (igAttr *)((int *)DAT_005627c8)[0]);
    FUN_001b12f0((igAttrStackManager *)s1, (igAttr *)((int *)DAT_005627c0)[0]);
    FUN_001b12f0((igAttrStackManager *)s1, (igAttr *)arg0->_stencilState);
    FUN_001b12f0((igAttrStackManager *)s1, (igAttr *)((int *)DAT_005627d0)[0]);
    FUN_001b12f0((igAttrStackManager *)s1, (igAttr *)((int *)DAT_005627d8)[0]);
    if (arg0->_shadowUseBlend != 0) {
        FUN_001b12f0((igAttrStackManager *)s1, (igAttr *)((int *)DAT_00562798)[0]);
    } else {
        FUN_001b12f0((igAttrStackManager *)s1, (igAttr *)((int *)DAT_005627a0)[0]);
    }
    FUN_001d3c60(arg0, arg1);
    for (i = 0; i < ((igDataList *)arg0->_lights)->_count; i++) {
        if (FUN_001b0ea0(s1, ((int *)((igDataList *)arg0->_lights)->_data)[i]) != 0) {
            int *m = (int *)((int *)((igDataList *)arg0->_mvmList)->_data)[i];
            igAttrStack *nd;
            int *s5;
            igObjectPool *pool;
            char *o;
            FUN_001908f0(sp70, arg1->_viewMatInv);
            FUN_001904f0(sp70, sp70, (char *)m + 12);
            FUN_001904f0(sp70, sp70, arg1->_viewMat);
            nd = (igAttrStack *)((int *)((igObjectList *)s1->_attrStacks)->_data)[((int *)s1->_attrStackIndexTable)[((igMetaObject * *)DAT_0055ef50)[0]->_id]];
            if (nd->_cachedOverride >= 0) {
                s5 = (int *)((int *)nd->_data)[nd->_cachedOverride];
            } else if (nd->_count != 0) {
                int k = nd->_count - 1;
                s5 = (int *)((int *)nd->_data)[k];
            } else {
                s5 = (int *)nd->_default;
            }
            pool = (igObjectPool *)arg1->_projectionMatrixPool;
            if (pool->_freeIndex >= pool->_count) igObjectPool_Grow((List_1dca40 *)pool, (Obj_1dca40 * (*)(int))((void *)&FUN_00134690));
            o = (char *)((int *)pool->_data)[pool->_freeIndex++];
            FUN_001904f0(o + 12, sp70, (char *)s5 + 12);
            FUN_001b1030((igAttrStackManager *)s1, (igAttr *)o);
            igTraversal_TraverseChildren((int)arg1, (S_1e07a0 *)arg0);
            FUN_001b1100((struct A_1b1100 *)s1, (struct B_1b1100 *)o);
        }
    }
    if (arg0->_shadowUseBlend != 0) {
        FUN_001b13d0((struct A_1b13d0 *)s1, (struct B_1b13d0 *)((int *)DAT_00562798)[0]);
    } else {
        FUN_001b13d0((struct A_1b13d0 *)s1, (struct B_1b13d0 *)((int *)DAT_005627a0)[0]);
    }
    FUN_001b13d0((struct A_1b13d0 *)s1, (struct B_1b13d0 *)((int *)DAT_005627d8)[0]);
    FUN_001b13d0((struct A_1b13d0 *)s1, (struct B_1b13d0 *)((int *)DAT_005627d0)[0]);
    FUN_001b13d0((struct A_1b13d0 *)s1, (struct B_1b13d0 *)arg0->_stencilState);
    FUN_001b13d0((struct A_1b13d0 *)s1, (struct B_1b13d0 *)((int *)DAT_005627c0)[0]);
    FUN_001b13d0((struct A_1b13d0 *)s1, (struct B_1b13d0 *)((int *)DAT_005627c8)[0]);
    FUN_001b13d0((struct A_1b13d0 *)s1, (struct B_1b13d0 *)arg0->_shadowColorAttr);
    FUN_001b13d0((struct A_1b13d0 *)s1, (struct B_1b13d0 *)((int *)DAT_005627b8)[0]);
    FUN_001b13d0((struct A_1b13d0 *)s1, (struct B_1b13d0 *)((int *)DAT_005627b0)[0]);
    FUN_001b13d0((struct A_1b13d0 *)s1, (struct B_1b13d0 *)((int *)DAT_005627a8)[0]);
}

