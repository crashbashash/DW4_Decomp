int FUN_001ceab0(HitTraversal *self, HitNode *node) {
    float determinant;
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
        FUN_00300c00(bound, previous, 1);
        FUN_001901b0(bound, topMatrix(self));
    }
    if (self->flags & 1) {
        if (FUN_0018ffa0(self->query->volume, bound) != 0) {
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
        if (igObject_IsKindOf(node, ((void * *)g_igGeometry_metaObject)[0]) != 0 || igObject_IsKindOf(node, ((void * *)DAT_00561ca0)[0]) != 0) {
            bool hit;
            unsigned int i;
            HitSegmentList *segments;
            unsigned int count;
            segments = self->query->segments;
            hit = false;
            count = segments->count;
            for (i = 0; i < count; i++) {
                HitSegment *segment = segments->data[i];
                if (FUN_00190010(bound, segment) != 0) {
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
        if (igObject_IsKindOf(node, ((void * *)g_igGeometry_metaObject)[0]) != 0) {
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
                FUN_00191f30(&determinant, &inverse, matrix);
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
                    FUN_00300c00(self->scratch, volume, 1);
                    FUN_0018d360(self->scratch, &inverse);
                    volume = self->scratch;
                }
                for (a = 0; a < attrCount; a++) {
                    HitAttr *attr = attrs->data[a];
                    if (igObject_IsKindOf(attr, ((void * *)g_igGeometryAttr_metaObject)[0]) != 0 || igObject_IsKindOf(attr, ((void * *)DAT_0055f158)[0]) != 0) {
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
                            FUN_00192fc0(&pointReport.local, &pointReport.point, matrix);
                            {
                                float dx = segment->x - pointReport.local.x;
                                float dy = segment->y - pointReport.local.y;
                                float dz = segment->z - pointReport.local.z;
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

int FUN_001cf980(void) {
    return 0;
}

int FUN_001cf990(A_1cf990 *arg0, B_1cf990 *arg1) {
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
    ObjectList_AppendRetained(arg0->f36, arg1);
    r = FUN_001ceab0((HitTraversal *)arg0, (HitNode *)arg1);
    if (r == 0) {
        r = igTraversal_TraverseChildren((int)arg0, (S_1e07a0 *)arg1);
    }
    m = arg0->f36;
    k = m->n - 1;
    o = m->data[k];
    if (o != 0) {
        o->f4 = o->f4 - 1;
        if (((unsigned long long) ((long long) o->f4 << 0x29) >> 0x29) == 0) {
            igObject_Destroy((void *)o);
        }
    }
    List_RemoveWordAt(m, k);
    m->data[m->n] = 0;
    if (r == 2) return 2;
    return 0;
}

int FUN_001cfaa0(ModelTraversal *self, TraversalNode *node) {
    int result;
    if (self->enabled != 0) {
        int r = self->callback(self, node);
        if (r == 1) {
            return 0;
        }
        if (r == 2) {
            int meta = (int)g_igNode_metaObject[0];
            int got = node->getMeta();
            if (got != meta) {
                return passStop(igTraversal_TraverseChildren((int)(self), (S_1e07a0 *)node));
            }
        }
    }
    node->setContext(self->context());
    ObjectList_AppendRetained(self->nodes, node);
    result = FUN_001ceab0((HitTraversal *)self, (HitNode *)node);
    if (result == 0) {
        FUN_001e68e0(self->matrices, node->transform);
        result = igTraversal_TraverseChildren((int)(self), (S_1e07a0 *)node);
        {
            MatrixStack *s = self->matrices;
            TraversalMatrix m;
            s->count = s->count - 1;
            Matrix44_Copy(&m, &s->data[s->count]);
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
                igObject_Destroy(o);
            }
        }
        List_RemoveWordAt(s, last);
        s->data[s->count] = 0;
    }
    return passStop(result);
}

igMetaObject *FUN_001cfc60(void) {
    return g_igTransform_metaObject[0];
}

int Gap__Sg__igGeometry__vfunc_22(void) {
    return ((int *)g_igGeometry_metaObject)[0];
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
    igMatrix44f_SetIdentity(&world);
    FUN_001904f0(&world, &self->local, parent);
    FUN_001904f0(self->block + DAT_00562bc8->offset, &self->bind, &world);
    count = 0;
    if (self->children != 0) {
        count = self->children->count;
    }
    for (i = 0; i < count; i++) {
        child = self->children->data[i];
        meta = DAT_005618f8[0];
        got = child->getMeta();
        if (meta == got) {
            FUN_001d0130(child, renderer, &world, context);
        } else {
            pool = renderer->pool;
            if (!(pool->used < pool->capacity)) {
                igObjectPool_Grow((List_1dca40 *)pool, (Obj_1dca40 * (*)(int))((void *)FUN_001356b0));
            }
            item = pool->data[pool->used++];
            item->setMatrix(&world);
            state = renderer->state;
            FUN_001b1030((igAttrStackManager *)state, (igAttr *)item);
            FUN_001e04c0((S_1e04c0 *)renderer, (V_1e04c0 *)child);
            FUN_001b1100((struct A_1b1100 *)state, (struct B_1b1100 *)item);
        }
    }
}

