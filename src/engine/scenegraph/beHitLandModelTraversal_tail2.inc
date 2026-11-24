namespace Gap {
namespace Sg {

void igIntersectTraversal::userRegister() {
    travProcs = igTraversalFunctionList::_instantiateFromPool(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem));
}

void igIntersectTraversal::userUnregister() {
    igObject::release(travProcs);
}

void igIntersectTraversal::_registerClass(igTraversalFunctionList *arg0, igMetaObject *arg1) {
    igTraversal::_registerClass(arg0, arg1);
    if (igMetaObject_IsOfType((igMetaObject *)arg1, (igMetaObject *)(((int)Gap::Sg::igNode::getClassTypeSafe()))) != 0) {
        if (igMetaObject_IsOfType((igMetaObject *)arg1, (igMetaObject *)(((int)Gap::Sg::igGeometry::getClassTypeSafe()))) != 0) {
            Gap::Sg::igTraversal::_setFunction((Gap::Sg::igTraversalFunctionList *)arg0, (igMetaObject *)arg1, (igTraversalFunction *)&igIntersectTraversal_TraverseGeometry);
            return;
        }
        if (igMetaObject_IsOfType((igMetaObject *)arg1, (igMetaObject *)(((int)Gap::Sg::igTransform::getClassTypeSafe()))) != 0) {
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

void igIntersectTraversal::resetFields(int flags) {
    igObject::resetFields(flags);
    _volumes = FUN_0018f760(getMemoryPool());
    reset();
}

void igIntersectTraversal::reset() {
    TraversalMatrixState *self = (TraversalMatrixState *)this;
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
                igObject_Destroy((::igObject *)p);
            }
        }
    }
    cnt = o->n;
    for (j = 0; j < cnt; j++) {
        o->data[j] = 0;
    }
    o->n = 0;
}

void igIntersectTraversal::begin(igNode *root)
{
    igTraversal::begin(root);
}

void igIntersectTraversal::end(igNode *root)
{
    igTraversal::end(root);
}
}
}

