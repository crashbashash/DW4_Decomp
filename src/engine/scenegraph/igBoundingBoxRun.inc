int igTransformSequence_ExtendBound(AABoxFields *arg0, TransformInputView *arg1) {
    if (igObject_IsKindOf(arg1, g_igTransformSequence_metaObject[0]) != 0) {
        Ref_1b2750 a((AABoxFields *)igAABox_CreateInstance(FUN_00301000(arg0)));
        igVolume_ExtendBy(a.o, arg0);
        Ref_1b2750 b((AABoxFields *)igAABox_CreateInstance(FUN_00301000(arg0)));
        AABoxFields *p = b.o;
        p->f8 = p->f12 = p->f16 = 3.402823466e+38f;
        p->f20 = p->f24 = p->f28 = -3.402823466e+38f;
        unsigned n;
        unsigned i;
        n = arg1->count();
        char sp50[64];
        for (i = 0; i < n; i++) {
            igMatrix44f_SetIdentity(sp50);
            arg1->get(i, sp50);
            igAABox_Transform(arg0, sp50);
            igVolume_ExtendBy(b.o, arg0);
            arg0->f8 = arg0->f12 = arg0->f16 = 3.402823466e+38f;
            arg0->f20 = arg0->f24 = arg0->f28 = -3.402823466e+38f;
            igVolume_ExtendBy(arg0, a.o);
        }
        arg0->f8 = arg0->f12 = arg0->f16 = 3.402823466e+38f;
        arg0->f20 = arg0->f24 = arg0->f28 = -3.402823466e+38f;
        igVolume_ExtendBy(arg0, b.o);
        return 1;
    }
    return 0;
}


/* A node flagged 0x40 never keeps its computed bound; otherwise the caller's request stands. */
static inline unsigned char boundCacheable(const igNode *node, const unsigned char &requested) {
    if ((node->_flags & 0x40) == 0x40) return 0;
    return requested;
}

static inline void makeEmpty(igAABox *box) {
    box->_min[0] = box->_min[1] = box->_min[2] = 3.402823466e+38f;
    box->_max[0] = box->_max[1] = box->_max[2] = -3.402823466e+38f;
}

unsigned char igNode_ComputeBound(igAABox *bound, igAABox *uncachedBound, int nodeHandle, int parentHandle,
                           unsigned char applySequences, unsigned char cacheBound, long long time) {
    igNode *node = (igNode *)nodeHandle;
    igAABox *cached = (igAABox *)node->_bound;
    if (cached != 0) {
        if (igObject_IsKindOf(node, g_igPlanarShadowShader_metaObject[0]) != 0) return 0;
        igVolume_ExtendBy(bound, cached);
        return 1;
    }
    igSmartPointer<igAABox> box((igAABox *)igAABox_CreateInstance(igObject_GetAllocator(node)));
    makeEmpty(box);
    igSmartPointer<igAABox> uncachedBox((igAABox *)igAABox_CreateInstance(igObject_GetAllocator(node)));
    makeEmpty(uncachedBox);
    unsigned char ok = boundCacheable(node, cacheBound);
    if (igObject_IsKindOf(node, g_igGroup_metaObject[0]) != 0) {
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
    if (igObject_IsKindOf(node, g_igGeometry_metaObject[0]) != 0) {
        if (!igGeometry_ExtendBound((int)box.get(), node)) {
            ok = 0;
            igGeometry_ExtendBound((int)uncachedBox.get(), node);
        }
    } else if (igObject_IsKindOf(node, g_igTransform_metaObject[0]) != 0) {
        igTransform *transform = (igTransform *)node;
        int input = transform->_transformInput;
        if (transform->_target == 0) {
            if (applySequences) {
                if (input != 0) {
                    unsigned char sequenced = igTransformSequence_ExtendBound((AABoxFields *)box.get(), (TransformInputView *)input);
                    if (igObject_IsKindOf(node, g_unlinkedTransformClass_metaObject[0]) != 0) {
                        /* the parent test is made and its answer discarded: a sequenced child never caches */
                        if (parentHandle != 0 && igObject_IsKindOf(parentHandle, g_unlinkedTransformClass_metaObject[0]) != 0) {
                        }
                        sequenced = 0;
                    }
                    ok = ok && sequenced;
                } else if (igObject_IsKindOf(node, g_unlinkedTransformClass_metaObject[0]) != 0) {
                    ok = 0;
                } else {
                    igTransform_ExtendBound((int)box.get(), node, 0);
                }
            } else if (igObject_IsKindOf(node, g_unlinkedTransformClass_metaObject[0]) != 0) {
                ok = 0;
            } else {
                igTransform_ExtendBound((int)box.get(), node, time);
            }
        }
    } else if (igObject_IsKindOf(node, g_igPlanarShadowShader_metaObject[0]) != 0) {
        igAABox *shadowBox = box;
        if (shadowBox->_min[0] <= shadowBox->_max[0] && ok) {
            (igSmartPointer<igAABox> &)node->_bound = shadowBox;
        }
        ok = 0;
    } else if (igObject_IsKindOf(node, g_igActor_metaObject[0]) != 0) {
        igActor *actor = (igActor *)node;
        igSkin *skin = (igSkin *)((igAppearance *)actor->_appearance)->_skin;
        igNode_ComputeBound(box.get(), uncachedBound, skin->_skinnedGraph, nodeHandle, applySequences, 0, time);
        if (box->_min[0] <= box->_max[0]) {
            float *transformMatrix = (float *)((char *)actor + g_igActor_transformMetaField[0]->_offset);
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
    igVolume_ExtendBy(uncachedBound, uncachedBox.get());
    igVolume_ExtendBy(bound, box.get());
    if (ok && box->_min[0] <= box->_max[0]) {
        (igSmartPointer<igAABox> &)node->_bound = box.get();
    }
    return ok;
}

int FUN_001b2ed0(int arg0, int arg1) {
    int temp_v0;

    temp_v0 = (int)igAABox_CreateInstance(((void *)igObject_GetAllocator((void *)arg1)));
    FUN_001b2f30((struct O_1b2750 *)arg0, arg1, (struct B_1b2750 *)temp_v0);
    return temp_v0;
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

