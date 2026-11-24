int igTransformSequence_ExtendBound(AABoxFields *arg0, TransformInputView *arg1) {
    if (((Gap::Core::igObject *)arg1)->isOfType(g_igTransformSequence_metaObject) != 0) {
        Ref_1b2750 a((AABoxFields *)igAABox_CreateInstance((int)((Gap::Core::igObject *)arg0)->getMemoryPool()));
        igVolume_ExtendBy((void **)a.o, (void **)arg0);
        Ref_1b2750 b((AABoxFields *)igAABox_CreateInstance((int)((Gap::Core::igObject *)arg0)->getMemoryPool()));
        AABoxFields *p = b.o;
        p->f8 = p->f12 = p->f16 = 3.402823466e+38f;
        p->f20 = p->f24 = p->f28 = -3.402823466e+38f;
        unsigned n;
        unsigned i;
        n = arg1->count();
        char sp50[64];
        for (i = 0; i < n; i++) {
            igMatrix44f_SetIdentity((float *)sp50);
            arg1->get(i, sp50);
            igAABox_Transform((igAABox *)arg0, (const float *)sp50);
            igVolume_ExtendBy((void **)b.o, (void **)arg0);
            arg0->f8 = arg0->f12 = arg0->f16 = 3.402823466e+38f;
            arg0->f20 = arg0->f24 = arg0->f28 = -3.402823466e+38f;
            igVolume_ExtendBy((void **)arg0, (void **)a.o);
        }
        arg0->f8 = arg0->f12 = arg0->f16 = 3.402823466e+38f;
        arg0->f20 = arg0->f24 = arg0->f28 = -3.402823466e+38f;
        igVolume_ExtendBy((void **)arg0, (void **)b.o);
        return 1;
    }
    return 0;
}


/* A node flagged 0x40 never keeps its computed bound; otherwise the caller's request stands. */
static inline unsigned char boundCacheable(const igNode *node, const unsigned char &requested) {
    if ((node->_flags & 0x40) == 0x40) return 0;
    return requested;
}

igMetaObject *g_unlinkedTransformClass_metaObject;

static inline void makeEmpty(igAABox *box) {
    box->_min[0] = box->_min[1] = box->_min[2] = 3.402823466e+38f;
    box->_max[0] = box->_max[1] = box->_max[2] = -3.402823466e+38f;
}

unsigned char igNode_ComputeBound(igAABox *bound, igAABox *uncachedBound, int nodeHandle, int parentHandle,
                           unsigned char applySequences, unsigned char cacheBound, long long time) {
    igNode *node = (igNode *)nodeHandle;
    igAABox *cached = (igAABox *)node->_bound;
    if (cached != 0) {
        if (((Gap::Core::igObject *)node)->isOfType(g_igPlanarShadowShader_metaObject) != 0) return 0;
        igVolume_ExtendBy((void **)bound, (void **)cached);
        return 1;
    }
    igSmartPointer<igAABox> box((igAABox *)igAABox_CreateInstance((int)((Gap::Core::igObject *)node)->getMemoryPool()));
    makeEmpty(box);
    igSmartPointer<igAABox> uncachedBox((igAABox *)igAABox_CreateInstance((int)((Gap::Core::igObject *)node)->getMemoryPool()));
    makeEmpty(uncachedBox);
    unsigned char ok = boundCacheable(node, cacheBound);
    if (((Gap::Core::igObject *)node)->isOfType(Gap::Sg::igGroup::getClassMeta()) != 0) {
        igGroup *group = (igGroup *)node;
        unsigned count = 0;
        if (group->_childList != 0) count = ((igNodeList *)group->_childList)->_count;
        for (unsigned i = 0; i < count; i++) {
            ok = igNode_ComputeBound(box.get(), uncachedBound,
                              ((int *)((igNodeList *)group->_childList)->_data)[i], nodeHandle, applySequences,
                              cacheBound, time) &&
                 ok;
        }
    }
    if (((Gap::Core::igObject *)node)->isOfType(Gap::Sg::igGeometry::getClassMeta()) != 0) {
        if (!igGeometry_ExtendBound((int)box.get(), node)) {
            ok = 0;
            igGeometry_ExtendBound((int)uncachedBox.get(), node);
        }
    } else if (((Gap::Core::igObject *)node)->isOfType(g_igTransform_metaObject) != 0) {
        igTransform *transform = (igTransform *)node;
        int input = transform->_transformInput;
        if (transform->_target == 0) {
            if (applySequences) {
                if (input != 0) {
                    unsigned char sequenced = igTransformSequence_ExtendBound((AABoxFields *)box.get(), (TransformInputView *)input);
                    if (((Gap::Core::igObject *)node)->isOfType(g_unlinkedTransformClass_metaObject) != 0) {
                        /* the parent test is made and its answer discarded: a sequenced child never caches */
                        if (parentHandle != 0 && ((Gap::Core::igObject *)parentHandle)->isOfType(g_unlinkedTransformClass_metaObject) != 0) {
                        }
                        sequenced = 0;
                    }
                    ok = ok && sequenced;
                } else if (((Gap::Core::igObject *)node)->isOfType(g_unlinkedTransformClass_metaObject) != 0) {
                    ok = 0;
                } else {
                    igTransform_ExtendBound((int)box.get(), node, 0);
                }
            } else if (((Gap::Core::igObject *)node)->isOfType(g_unlinkedTransformClass_metaObject) != 0) {
                ok = 0;
            } else {
                igTransform_ExtendBound((int)box.get(), node, time);
            }
        }
    } else if (((Gap::Core::igObject *)node)->isOfType(g_igPlanarShadowShader_metaObject) != 0) {
        igAABox *shadowBox = box;
        if (shadowBox->_min[0] <= shadowBox->_max[0] && ok) {
            (igSmartPointer<igAABox> &)node->_bound = shadowBox;
        }
        ok = 0;
    } else if (((Gap::Core::igObject *)node)->isOfType(g_igActor_metaObject) != 0) {
        igActor *actor = (igActor *)node;
        igSkin *skin = (igSkin *)((igAppearance *)actor->_appearance)->_skin;
        igNode_ComputeBound(box.get(), uncachedBound, skin->_skinnedGraph, nodeHandle, applySequences, 0, time);
        if (box->_min[0] <= box->_max[0]) {
            float *transformMatrix = (float *)((char *)actor + g_igActor_transformMetaField->_offset);
            float w = transformMatrix[15];
            bool unitW = w >= 0.9999995f && w <= 1.0000005f;
            if (unitW) {
                igAABox_Transform(box.get(), transformMatrix);
            } else if (!(w <= 0.0f) && w < 1.0f) {
                ok = 0;
            }
        } else {
            ok = 0;
        }
    }
    igVolume_ExtendBy((void **)uncachedBound, (void **)(uncachedBox.get()));
    igVolume_ExtendBy((void **)bound, (void **)(box.get()));
    if (ok && box->_min[0] <= box->_max[0]) {
        (igSmartPointer<igAABox> &)node->_bound = box.get();
    }
    return ok;
}

igAABox *igBoundingBoxesMaker_ComputeBox(igBoundingBoxesMaker *maker, igNode *node) {
    igAABox *box;

    box = igAABox_CreateInstance((int)((Gap::Core::igObject *)node)->getMemoryPool());
    FUN_001b2f30((struct O_1b2750 *)maker, (int)node, (struct B_1b2750 *)box);
    return box;
}

void FUN_001b2f30(struct O_1b2750 *arg0, int arg1, struct B_1b2750 *arg2) {
    struct B_1b2750 *p;
    arg0->b17 = 0;
    arg2->f8 = arg2->f12 = arg2->f16 = 3.402823466e+38f;
    arg2->f20 = arg2->f24 = arg2->f28 = -3.402823466e+38f;
    p = arg0->f20;
    p->f8 = p->f12 = p->f16 = 3.402823466e+38f;
    p->f20 = p->f24 = p->f28 = -3.402823466e+38f;
    igNode_ComputeBound((igAABox *)arg2, (igAABox *)arg0->f20, arg1, 0, arg0->b16, arg0->b17, arg0->f8);
}

