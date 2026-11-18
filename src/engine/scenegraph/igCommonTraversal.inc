igMetaObject *igCommonTraversal_GetMetaObject(void)
{
    igMetaObject *g = g_igCommonTraversal_metaObject;
    if (!g || ((g->_validity & 4) != 0) == false)
        igCommonTraversal_EnsureRegistered();
    return g_igCommonTraversal_metaObject;
}

int igCommonTraversal_GetVTable(void) {
    struct O_1a38e0 o; int t; int *p; int *q4; int *q3; int *q2; int *q1; int *q0; int *q6; int *q7; int *q8;
    p = (int*)&o;
    FUN_001a3d90((igTraversal *)p);
    o.vt = (int)&g_igCommonTraversal_vtable[0];
    igSmartPointer_igCapabilityManager_Construct((char*)&o + 32);
    igSmartPointer_igAttrDefaultManager_Construct((char*)&o + 36);
    igSmartPointer_igAttrStackManager_Construct((char*)&o + 52);
    igSmartPointer_igTransformStack_Construct((char*)&o + 56);
    igSmartPointer_igVisualContext_Construct((char*)&o + 60);
    igSmartPointer_igNonRefCountedAttrList_Construct((int *)((char*)&o + 64));
    q8 = (int*)((char*)&o + 68);
    igSmartPointer_igSorter_Construct(q8);
    q7 = (int*)((char*)&o + 72);
    igSmartPointer_igModelViewMatrixAttrPool_Construct(q7);
    q6 = (int*)((char*)&o + 76);
    igSmartPointer_igTimeAttrPool_Construct(q6);
    q0 = (int*)((char*)&o + 80);
    igSmartPointer_igVertexBlendMatrixAttrPool_Construct(q0);
    q1 = (int*)((char*)&o + 84);
    igSmartPointer_igTextureMatrixAttrPool_Construct(q1);
    q2 = (int*)((char*)&o + 88);
    igSmartPointer_igVertexBlendMatrixListAttrPool_Construct(q2);
    q3 = (int*)((char*)&o + 92);
    igSmartPointer_igMatrixObjectPool_Construct(q3);
    q4 = (int*)((char*)&o + 96);
    igSmartPointer_igProjectionMatrixAttrPool_Construct(q4);
    FUN_001510a0((char*)&o + 100);
    FUN_001510a0(p + 41);
    FUN_001a2c50((int *)(p + 58));
    FUN_001a3cb0(p + 59);
    FUN_001a3ca0(p + 60);
    igSmartPointer_igNonRefCountedMatrixObjectList_Construct((int *)(p + 61));
    igSmartPointer_igNonRefCountedTransformList_Construct((int *)(p + 62));
    igSmartPointer_igNonRefCountedTransformList_Construct((int *)(p + 63));
    igSmartPointer_igIntList_Construct(p + 64);
    FUN_001a3c90(p + 65);
    FUN_001a3c80(p + 66);
    FUN_001a3c70(p + 67);
    FUN_001510a0(p + 68);
    FUN_001a3c60(p + 84);
    FUN_001510a0(p + 86);
    FUN_001510a0(p + 102);
    t = *(int *)((char *)&o + g_objectSystem->vtableProbeOffset);
    o.vt = (int)&D_005293c0[0];
    igSmartPointer_igTimeAttr_Destruct((ObjectRefWord *)((char*)&o + 336), -1);
    igSmartPointer_igBlendMatricesAttrPool_Destruct((O *)((char*)&o + 268), -1);
    igSmartPointer_igNodeListList_Destruct((struct Ref * *)((char*)&o + 264), -1);
    igSmartPointer_igStringObjList_Destruct((igSmartPointer<igObject> *)((char*)&o + 260), -1);
    FUN_00150eb0((char*)&o + 256, -1);
    igSmartPointer_igNonRefCountedTransformList_Destruct((struct Ref * *)((char*)&o + 252), -1);
    igSmartPointer_igNonRefCountedTransformList_Destruct((struct Ref * *)((char*)&o + 248), -1);
    igSmartPointer_igNonRefCountedMatrixObjectList_Destruct((void * *)((char*)&o + 244), -1);
    igSmartPointer_igLongStack_Destruct((void * *)((char*)&o + 240), -1);
    igSmartPointer_igNormalizeNormalsStateAttr_Destruct((ObjectRefWord *)((char*)&o + 236), -1);
    igSmartPointer_igMatrixOptStateAttr_Destruct((struct R * *)((char*)&o + 232), -1);
    igSmartPointer_igProjectionMatrixAttrPool_Destruct((ObjectRefWord *)q4, -1);
    igSmartPointer_igMatrixObjectPool_Destruct((void * *)q3, -1);
    igSmartPointer_igVertexBlendMatrixListAttrPool_Destruct((ObjectRefWord *)q2, -1);
    igSmartPointer_igTextureMatrixAttrPool_Destruct((void * *)q1, -1);
    igSmartPointer_igVertexBlendMatrixAttrPool_Destruct((void * *)q0, -1);
    igSmartPointer_igTimeAttrPool_Destruct((O *)q6, -1);
    igSmartPointer_igModelViewMatrixAttrPool_Destruct((void * *)q7, -1);
    igSmartPointer_igSorter_Destruct((struct Ref * *)q8, -1);
    FUN_001380e0((char*)&o + 64, -1);
    igSmartPointer_igVisualContext_Destruct((igSmartPointer<igObject> *)((char*)&o + 60), -1);
    igSmartPointer_igTransformStack_Destruct((void * *)((char*)&o + 56), -1);
    igSmartPointer_igAttrStackManager_Destruct((void * *)((char*)&o + 52), -1);
    igSmartPointer_igAttrDefaultManager_Destruct((struct T_19fde0 * *)((char*)&o + 36), -1);
    igSmartPointer_igCapabilityManager_Destruct((struct R * *)((char*)&o + 32), -1);
    FUN_00194490((struct S *)&o, 0);
    return t;
}

