int FUN_001ceab0(HitTraversal *self, HitNode *node) {
    HitReport volumeReport;
    HitReport segmentReport;
    HitMatrix inverse;
    HitReport pointReport;
    HitBound *bound = node->bound;
    if (bound == 0) {
        return 0;
    }
    if (self->matrices->count > 1) {
        HitBound *previous = bound;
        HitMetaView *m = bound->getMeta();
        HitBoundList *cache = self->cache;
        bound = cache->data[m->index];
        ((Gap::Core::igObject *)bound)->copy((Gap::Core::igObject *)previous, 1);
        FUN_001901b0(bound, topMatrix(self));
    }
    if (self->flags & 1) {
        if (FUN_0018ffa0((void **)self->query->volume, (void **)bound) != 0) {
            int r;
            HitMatrix *m;
            volumeReport.type = 1;
            volumeReport.context = self->context;
            m = topMatrix(self);
            volumeReport.object = 0;
            volumeReport.matrix = m;
            volumeReport.query = self->query;
            r = self->callback(self, node, &volumeReport);
            if (r != 0) {
                return r;
            }
        } else {
            return 1;
        }
    }
    if (self->flags & 2) {
        if (((Gap::Core::igObject *)node)->isOfType((igMetaObject *)g_igGeometry_metaObject) != 0 || ((Gap::Core::igObject *)node)->isOfType(((igMetaObject **)g_igCompiledGraph_metaObject)[0]) != 0) {
            bool hit;
            unsigned int i;
            HitSegmentList *segments;
            unsigned int count;
            segments = self->query->segments;
            hit = false;
            count = segments->count;
            for (i = 0; i < count; i++) {
                HitSegment *segment = segments->data[i];
                if (FUN_00190010((void **)bound, (int)segment) != 0) {
                    int r;
                    HitMatrix *m;
                    segmentReport.type = 2;
                    segmentReport.context = self->context;
                    m = topMatrix(self);
                    segmentReport.object = segment;
                    segmentReport.matrix = m;
                    segmentReport.query = self->query;
                    hit = true;
                    r = self->callback(self, node, &segmentReport);
                    if (r != 0) {
                        return r;
                    }
                }
            }
            if (!hit) {
                return 1;
            }
        }
    }
    if (self->flags & 4) {
        if (((Gap::Core::igObject *)node)->isOfType(g_igGeometry_metaObject) != 0) {
            HitMatrix *matrix;
            unsigned int attrCount;
            unsigned int segmentCount;
            void *aux;
            HitAttrList *attrs;
            HitSegmentList *segments;
            unsigned int s;
            HitMatrixStack *stack = self->matrices;
            int n = stack->count;
            matrix = &stack->data[n - 1];
            if (n > 1) {
                igMatrix44f_Invert((float *)&inverse, (const float *)matrix);
            }
            attrs = node->attrs;
            attrCount = attrs->count;
            segments = self->query->segments;
            segmentCount = segments->count;
            for (s = 0; s < segmentCount; s++) {
                HitBound *volume = (HitBound *)segments->data[s];
                aux = self->query->aux->data[s];
                unsigned int a;
                if (self->matrices->count > 1) {
                    ((Gap::Core::igObject *)self->scratch)->copy((Gap::Core::igObject *)volume, 1);
                    igRay_Transform((igRay *)self->scratch, (const float *)((const void *)&inverse));
                    volume = self->scratch;
                }
                for (a = 0; a < attrCount; a++) {
                    HitAttr *attr = attrs->data[a];
                    if (((Gap::Core::igObject *)attr)->isOfType((igMetaObject *)(((void *)g_igGeometryAttr_metaObject))) != 0 || ((Gap::Core::igObject *)attr)->isOfType(((igMetaObject **)DAT_0055f158)[0]) != 0) {
                        int *f = &pointReport.first;
                        int *g = &pointReport.second;
                        *f = -1;
                        *g = -1;
                        while (FUN_001cef70(self, attr, volume, &pointReport.point, &pointReport.normal, &pointReport.first, &pointReport.second, aux, 1) != 0) {
                            HitSegment *segment = segments->data[s];
                            int r;
                            pointReport.type = 4;
                            pointReport.context = self->context;
                            pointReport.index = a;
                            pointReport.matrix = matrix;
                            pointReport.object = segment;
                            pointReport.query = self->query;
                            Vec3f_TransformProjective((float *)&pointReport.local, (const float *)&pointReport.point, (const float *)matrix);
                            {
                                float dx = segment->x - pointReport.local.vec[0];
                                float dy = segment->y - pointReport.local.vec[1];
                                float dz = segment->z - pointReport.local.vec[2];
                                pointReport.distance = sqrtf(dx * dx + dy * dy + dz * dz);
                            }
                            r = self->callback(self, node, &pointReport);
                            if (r != 0) {
                                return r;
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}

void FUN_001cf950(int **arg0, int *arg1) {
    int *a;
    *arg0 = (int *)arg1[4];
    a = *arg0;
    if (a != 0) {
        a[1] = a[1] + 1;
    }
}

int igIntersectTraversal_TraverseNode(void) {
    return 0;
}

int igIntersectTraversal_TraverseGroup(A_1cf990 *arg0, B_1cf990 *arg1) {
    Ls_1cf990 *l;
    int n;
    int r;
    int k;
    Ls_1cf990 *m;
    S_1cf990 *o;
    l = arg1->f28;
    if (l != 0) {
        n = l->n;
    } else {
        n = 0;
    }
    if (n == 0) return 0;
    ObjectList_AppendRetained((igObjectList *)arg0->f36, (igObject *)arg1);
    r = FUN_001ceab0((HitTraversal *)arg0, (HitNode *)arg1);
    if (r == 0) {
        r = igTraversal_TraverseChildren((igTraversal *)arg0, (igNode *)arg1);
    }
    m = arg0->f36;
    k = m->n - 1;
    o = m->data[k];
    if (o != 0) {
        o->f4 = o->f4 - 1;
        if (((unsigned long long) ((long long) o->f4 << 0x29) >> 0x29) == 0) {
            igObject_Destroy((igObject *)o);
        }
    }
    List_RemoveWordAt((igDataList *)m, k);
    m->data[m->n] = 0;
    if (r == 2) return 2;
    return 0;
}

int igIntersectTraversal_TraverseTransform(ModelTraversal *self, TraversalNode *node) {
    int result;
    if (self->enabled != 0) {
        int r = self->callback(self, node);
        if (r == 1) {
            return 0;
        }
        if (r == 2) {
            int meta = (int)g_igNode_metaObject;
            int got = node->getMeta();
            if (got != meta) {
                return passStop(igTraversal_TraverseChildren((igTraversal *)(self), (igNode *)node));
            }
        }
    }
    node->setContext(self->context());
    ObjectList_AppendRetained((igObjectList *)self->nodes, (igObject *)node);
    result = FUN_001ceab0((HitTraversal *)self, (HitNode *)node);
    if (result == 0) {
        igMatrixStack_PushPreMultiply((igMatrixStack *)self->matrices, node->transform);
        result = igTraversal_TraverseChildren((igTraversal *)(self), (igNode *)node);
        {
            MatrixStack *s = self->matrices;
            TraversalMatrix m;
            s->count = s->count - 1;
            igMatrix44f_Copy((float *)&m, (const float *)&s->data[s->count]);
        }
    }
    {
        int last;
        NodeStack *s = self->nodes;
        NodeRefObject *o;
        last = s->count - 1;
        o = s->data[last];
        if (o != 0) {
            o->_refCount = o->_refCount - 1;
            if (((unsigned long long)((long long)(int)o->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy((igObject *)o);
            }
        }
        List_RemoveWordAt((igDataList *)s, last);
        s->data[s->count] = 0;
    }
    return passStop(result);
}

igMetaObject *igTransform_GetMeta(void) {
    return g_igTransform_metaObject;
}

int igGeometry_GetMeta(void) {
    return ((int)g_igGeometry_metaObject);
}

void FUN_001d0130(SceneTransformNode *self, SceneRenderer *renderer, SceneMatrix *parent, int context) {
    SceneMatrix world;
    int i;
    int count;
    SceneDrawItem *item;
    SceneDrawItemPool *pool;
    void *state;
    int meta;
    int got;
    SceneTransformNode *child;
    self->setContext(context);
    igMatrix44f_SetIdentity((float *)&world);
    igMatrix44f_Multiply((float *)&world, (const float *)&self->local, (const float *)parent);
    igMatrix44f_Multiply((float *)(self->block + g_igMatrixObject_mMetaField->_offset), (const float *)&self->bind, (const float *)&world);
    count = 0;
    if (self->children != 0) {
        count = self->children->count;
    }
    for (i = 0; i < count; i++) {
        child = self->children->data[i];
        meta = (int)g_unlinkedTransformClass_metaObject;
        got = child->getMeta();
        if (meta == got) {
            FUN_001d0130(child, renderer, &world, context);
        } else {
            pool = renderer->pool;
            if (!(pool->used < pool->capacity)) {
                igObjectPool_Grow((igObjectPool *)pool, (igObject *(*)(int))((void *)igModelViewMatrixAttr_CreateInstance));
            }
            item = pool->data[pool->used++];
            item->setMatrix(&world);
            state = renderer->state;
            FUN_001b1030((igAttrStackManager *)state, (igAttr *)item);
            igTraversal_TraverseNode((igTraversal *)renderer, (igNode *)child);
            FUN_001b1100((struct A_1b1100 *)state, (struct B_1b1100 *)item);
        }
    }
}

