void FUN_001ce710(void) {
    *(int *)0x562790 = (int)Gap::Sg::igTraversalFunctionList::_instantiateFromPool(Memory_GetAllocatorBySelector(*(int *)0x587038));
}

void igIntersectTraversal_UserUnregister(void) {
    void *temp_a0;

    temp_a0 = *(void **)0x562790;
    if (temp_a0 != 0) {
        *(int *)((char *)temp_a0 + 4) = (int) (*(int *)((char *)temp_a0 + 4) - 1);
        if (((unsigned long long) ((long long) *(int *)((char *)temp_a0 + 4) << 0x29) >> 0x29) == 0) {
            igObject_Destroy((igObject *)temp_a0);
        }
    }
}

void igIntersectTraversal_RegisterClassFunction(int arg0, int arg1) {
    igTraversal_RegisterClassFunction(arg0, arg1);
    if (igMetaObject_IsOfType((igMetaObject *)arg1, (igMetaObject *)(((int)Gap::Sg::igNode::getClassTypeSafe()))) != 0) {
        if (igMetaObject_IsOfType((igMetaObject *)arg1, (igMetaObject *)(((int)Gap::Sg::igGeometry::getClassTypeSafe()))) != 0) {
            Gap::Sg::igTraversal::_setFunction((Gap::Sg::igTraversalFunctionList *)arg0, (igMetaObject *)arg1, (igTraversalFunction *)&igIntersectTraversal_TraverseGeometry);
            return;
        }
        if (igMetaObject_IsOfType((igMetaObject *)arg1, (igMetaObject *)(((int)igTransform_GetMetaObject()))) != 0) {
            Gap::Sg::igTraversal::_setFunction((Gap::Sg::igTraversalFunctionList *)arg0, (igMetaObject *)arg1, (igTraversalFunction *)&igIntersectTraversal_TraverseTransform);
            return;
        }
        if (igMetaObject_IsOfType((igMetaObject *)arg1, (igMetaObject *)(((int)Gap::Sg::igGroup::getClassTypeSafe()))) != 0) {
            Gap::Sg::igTraversal::_setFunction((Gap::Sg::igTraversalFunctionList *)arg0, (igMetaObject *)arg1, (igTraversalFunction *)&igIntersectTraversal_TraverseGroup);
            return;
        }
        Gap::Sg::igTraversal::_setFunction((Gap::Sg::igTraversalFunctionList *)arg0, (igMetaObject *)arg1, (igTraversalFunction *)igIntersectTraversal_TraverseNode);
    }
}

void igIntersectTraversal_resetFields(beHitLandModelTraversal *arg0, int flags) {
    Gap__Core__igObject__resetFields((igObject *)arg0, flags);
    *(igSmartPointer<igVolumeList> *)&arg0->_volumes = FUN_0018f760(((Gap::Core::igObject *)arg0)->getMemoryPool());
    igIntersectTraversal_ResetStacks((igIntersectTraversal *)arg0);
}

void igIntersectTraversal_ResetStacks(igIntersectTraversal *traversal) {
    TraversalMatrixState *self = (TraversalMatrixState *)traversal;
    ReleasableList *o;
    int cnt;
    int idx;
    int j;
    MatrixStackList *m;
    int n;
    int i;
    self->mats->n = 0;
    m = self->mats;
    idx = m->n;
    if (idx < m->cap) {
        m->n = n_of_1ce970(m) + 1;
    } else {
        ((Gap::Core::igDataList *)m)->resizeAndSetCount(idx + 1, 64);
    }
    igMatrix44f_Copy((float *)(m->data + idx), g_matrix44Identity.m);
    o = self->objs;
    n = o->n;
    for (i = 0; i < n; i++) {
        CountedObject *p = (CountedObject *)o->data[i];
        if (p != 0) {
            p->rc = p->rc - 1;
            if (((unsigned long long)((long long)p->rc << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)p);
            }
        }
    }
    cnt = o->n;
    for (j = 0; j < cnt; j++) {
        o->data[j] = 0;
    }
    o->n = 0;
}

void Gap__Bec__beHitLandModelTraversal__vfunc_21(void *self, int arg1)
{
    Gap__Sg__igTraversal__vfunc_23(self, arg1);
}

void Gap__Bec__beHitLandModelTraversal__vfunc_22(void *self, int arg1)
{
    Gap__Sg__igTraversal__vfunc_24(self, arg1);
}

