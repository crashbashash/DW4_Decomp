namespace Gap {
namespace Sg {

void igFrustCullTraversal::registerClass(igMetaObject *meta) {
    _registerClass(travProcs, meta);
}

void igFrustCullTraversal::userRegister() {
    travProcs = igTraversalFunctionList::_instantiateFromPool(Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem));
}

void igFrustCullTraversal::userUnregister() {
    igObject::release(travProcs);
}

void igFrustCullTraversal::reset()
{
    igCommonTraversal::reset();
    _curMVMat = 0;
    _curProjectionMat = 0;
}

void igFrustCullTraversal::userConstruct(int flag) {
    /* matching construct: the receiver is a named local and the table's reference is counted by hand */
    O_1c4650 *arg0 = (O_1c4650 *)this;
    R_1c4650 *s0;
    R_1c4650 *a0;
    igCommonTraversal::userConstruct(flag);
    if (flag == 0) {
        s0 = (R_1c4650 *)travProcs;
        if (s0 != 0) {
            s0->references = s0->references + 1;
        }
        a0 = arg0->ref;
        if (a0 != 0) {
            a0->references = a0->references - 1;
            if (((unsigned long long)(long long)a0->references & 0x7fffffULL) == 0) {
                igObject_Destroy((::igObject *)a0);
            }
        }
        arg0->ref = s0;
        arg0->flags = arg0->flags | 0x200;
        arg0->v->vX(0);
    }
}

void igFrustCullTraversal::_registerClass(igTraversalFunctionList *arg0, igMetaObject *arg1) {
    Gap::Sg::igCommonTraversal::_registerClass((Gap::Sg::igTraversalFunctionList *)arg0, (igMetaObject *)arg1);
    if (igMetaObject_IsOfType((igMetaObject *)arg1, (igMetaObject *)(((int)Gap::Sg::igNode::getClassTypeSafe()))) != 0) {
        Gap::Sg::igTraversal::_setFunction((Gap::Sg::igTraversalFunctionList *)arg0, (igMetaObject *)arg1, (igTraversalFunction *)&igFrustCullTraversal_TraverseNode);
    }
    if (igMetaObject_IsOfType((igMetaObject *)arg1, (igMetaObject *)(((int)Gap::Sg::igPlanarShadowShader::getClassTypeSafe()))) != 0) {
        Gap::Sg::igTraversal::_setFunction((Gap::Sg::igTraversalFunctionList *)arg0, (igMetaObject *)arg1, (igTraversalFunction *)&igFrustCullTraversal_TraversePlanarShadowShader);
    }
}

void igFrustCullTraversal::end(igNode *root)
{
    igCommonTraversal::end(root);
}

void igFrustCullTraversal::computeCompositeMatrix(const igMatrix44f *mat, const igMatrix44f *proj) {
    igMatrix44f_Multiply((float *)&_compMat, (const float *)mat, (const float *)proj);
    _curMVMat = (int)mat;
    _curProjectionMat = (int)proj;
}
}
}

/* Classifies a box against the view frustum: the box corners are transformed to clip space and their
 * clip flags combined. */
int FUN_001c47f0(const float *matrix, const float *boxMin, const float *boxMax) {
    unsigned int all;
    unsigned int any;
    unsigned char narrow;
    float scale = DAT_0048da28[0];

    if (scale == 1.0f) {
        scale = DAT_0048da28[2];
        narrow = 0;
    } else {
        narrow = 1;
    }
    asm volatile {
            mtsab matrix, 0
            lq a2,0(matrix)
            lq a3,16(matrix)
            lq t0,32(matrix)
            lq t1,48(matrix)
            lq t2,64(matrix)
            qfsrv a2,a3,a2
            qfsrv a3,t0,a3
            qfsrv t0,t1,t0
            qfsrv t1,t2,t1
            qmtc2 a2,vf1
            qmtc2 a3,vf2
            qmtc2 t0,vf3
            qmtc2 t1,vf4
            lq a2,0(boxMin)
            lq a3,16(boxMin)
            mtsab boxMin, 0
            qfsrv a2,a3,a2
            lq a3,0(boxMax)
            lq t0,16(boxMax)
            qmtc2 a2,vf5
            mtsab boxMax, 0
            qfsrv a3,t0,a3
            vmulax.xyzw ACC,vf1,vf5x
            qmtc2 a3,vf6
            vmadday.xyzw ACC,vf2,vf5y
            vmaddaz.xyzw ACC,vf3,vf5z
            vmaddw.xyzw vf20,vf4,vf0w
            vmulax.xyzw ACC,vf1,vf6x
            vmadday.xyzw ACC,vf2,vf5y
            vmaddaz.xyzw ACC,vf3,vf5z
            vclipw.xyz vf20,vf20w
            vmaddw.xyzw vf21,vf4,vf0w
            vmulax.xyzw ACC,vf1,vf5x
            vmadday.xyzw ACC,vf2,vf6y
            vmaddaz.xyzw ACC,vf3,vf5z
            cfc2 all, vi18
            vclipw.xyz vf21,vf21w
            vmaddw.xyzw vf22,vf4,vf0w
            vmulax.xyzw ACC,vf1,vf5x
            vmadday.xyzw ACC,vf2,vf5y
            vmaddaz.xyzw ACC,vf3,vf6z
            cfc2 a2,vi18
            vclipw.xyz vf22,vf22w
            vmaddw.xyzw vf23,vf4,vf0w
            and all, all, a2
            vmulax.xyzw ACC,vf1,vf6x
            vmadday.xyzw ACC,vf2,vf6y
            vmaddaz.xyzw ACC,vf3,vf5z
            cfc2 a2,vi18
            vclipw.xyz vf23,vf23w
            vmaddw.xyzw vf24,vf4,vf0w
            and all, all, a2
            vmulax.xyzw ACC,vf1,vf6x
            vmadday.xyzw ACC,vf2,vf5y
            vmaddaz.xyzw ACC,vf3,vf6z
            cfc2 a2,vi18
            cfc2 any, vi18
            vclipw.xyz vf24,vf24w
            vmaddw.xyzw vf25,vf4,vf0w
            and all, all, a2
            vmulax.xyzw ACC,vf1,vf5x
            vmadday.xyzw ACC,vf2,vf6y
            vmaddaz.xyzw ACC,vf3,vf6z
            cfc2 a2,vi18
            vclipw.xyz vf25,vf25w
            vmaddw.xyzw vf26,vf4,vf0w
            and all, all, a2
            vmulax.xyzw ACC,vf1,vf6x
            vmadday.xyzw ACC,vf2,vf6y
            vmaddaz.xyzw ACC,vf3,vf6z
            cfc2 a2,vi18
            vclipw.xyz vf26,vf26w
            vmaddw.xyzw vf27,vf4,vf0w
            and all, all, a2
            mfc1 v0, scale
            nop
            ctc2 v0,vi21
            vmuli.xy vf10,vf20,I
            cfc2 a2,vi18
            vclipw.xyz vf27,vf27w
            and all, all, a2
            vmuli.xy vf11,vf21,I
            vmuli.xy vf12,vf22,I
            vmuli.xy vf13,vf23,I
            vnop
            cfc2 a2,vi18
            vmuli.xy vf14,vf24,I
            or any, any, a2
            and all, all, a2
    }
    if ((any & 0xffffff) == 0) {
        return 1;
    }
    if ((all & 0x3f) != 0) {
        return 2;
    }
    if ((any & 0xc30c30) == 0) {
        if (narrow) {
            /* matching construct: a separate local and a volatile asm statement: the PCode peephole skips a block
             * that starts at a volatile asm statement, so this lwc1 and the block's mfc1 are not folded into lw.
             * Every block of this function is written `asm volatile`, the VU0 inline-asm idiom's uniform form. */
            float full = DAT_0048da28[2];
            asm volatile {
                    vclipw.xyz vf10,vf20w
                    vclipw.xyz vf11,vf21w
                    vclipw.xyz vf12,vf22w
                    vclipw.xyz vf13,vf23w
                    vmuli.xy vf15,vf25,I
                    vmuli.xy vf16,vf26,I
                    vmuli.xy vf17,vf27,I
                    mfc1 v0, full
                    nop
                    ctc2 v0,vi21
                    cfc2 a3, vi18
                    vclipw.xyz vf14,vf24w
                    vclipw.xyz vf15,vf25w
                    vclipw.xyz vf16,vf26w
                    vclipw.xyz vf17,vf27w
                    vmuli.xy vf10,vf20,I
                    vmuli.xy vf11,vf21,I
                    vmuli.xy vf12,vf22,I
                    cfc2 a2,vi18
                    vmuli.xy vf13,vf23,I
                    or any, a3, a2
                    vmuli.xy vf14,vf24,I
            }
            if ((any & 0x3cf3cf) == 0) {
                return 5;
            }
        }
        asm volatile {
            vclipw.xyz vf10,vf20w
            vclipw.xyz vf11,vf21w
            vclipw.xyz vf12,vf22w
            vclipw.xyz vf13,vf23w
            vmuli.xy vf15,vf25,I
            vmuli.xy vf16,vf26,I
            vmuli.xy vf17,vf27,I
            vnop
            cfc2 a3,vi18
            vclipw.xyz vf14,vf24w
            vclipw.xyz vf15,vf25w
            vclipw.xyz vf16,vf26w
            vclipw.xyz vf17,vf27w
            vnop
            vnop
            vnop
            cfc2 a2,vi18
            nop
            or any, a3, a2
            nop
        }
        if ((any & 0x3cf3cf) == 0) {
            return 4;
        }
    }
    return 3;
}

int FUN_001c4ac0(CullFrustumView *o, CullBoundsView *b) {
    CullAttrState *st;
    /* matching construct: permuter — st assigned inside the first lookup, so the second reloads its fields */
    float *world = currentEntry_1c4ac0(stackOf_1c4ac0(st = o->_state, ((CullMeta *)Gap::Attrs::igModelViewMatrixAttr::getClassMeta())))->_matrix;
    float *view = currentEntry_1c4ac0(stackOf_1c4ac0(st, (CullMeta *)Gap::Attrs::igProjectionMatrixAttr::getClassMeta()))->_matrix;
    int same = o->_lastWorld == world;
    if (same) {
        same = o->_lastView == view;
    }
    if (!same) {
        ((Gap::Sg::igFrustCullTraversal *)o)->computeCompositeMatrix((igMatrix44f const *)world, (igMatrix44f const *)view);
    }
    return FUN_001c47f0(o->_frustum, b->_min, b->_max);
}

int FUN_001c4c20(igFrustCullTraversal *self, igNode *node, int result) {
    int status;
    switch (result) {
    case 2:
        return 0;
    case 5:
    case 1: {
        ((Gap::Sg::igFrustCullTraversal *)self)->_attrStack->fastPushAttr((Gap::Attrs::igAttr *)self->_cd);
        igObject *saved = (igObject *)self->_travProcs;
        ((igSmartPointer<igObject> &)self->_travProcs) = (igObject *)Gap::Sg::igCommonTraversal::_getTraversalFunctions();
        status = Gap::Sg::igCommonTraversal::_getTraversalFunctions()->get((unsigned)node->_handle)((::igTraversal *)self, (::igObject *)node);
        ((igSmartPointer<igObject> &)self->_travProcs) = saved;
        ((Gap::Sg::igAttrStackManager *)self->_attrStack)->fastPopAttr((Gap::Attrs::igAttr *)self->_cd);
        if (status == 2) {
            return 2;
        }
        return 0;
    }
    case 3:
        if (Gap::Sg::igCommonTraversal::_getTraversalFunctions()->get((unsigned)node->_handle)((::igTraversal *)self, (::igObject *)node) == 2) {
            return 2;
        }
        return 0;
    case 4:
        ((Gap::Sg::igFrustCullTraversal *)self)->_attrStack->fastPushAttr((Gap::Attrs::igAttr *)self->_cd);
        status = Gap::Sg::igCommonTraversal::_getTraversalFunctions()->get((unsigned)node->_handle)((::igTraversal *)self, (::igObject *)node);
        ((Gap::Sg::igAttrStackManager *)self->_attrStack)->fastPopAttr((Gap::Attrs::igAttr *)self->_cd);
        if (status == 2) {
            return 2;
        }
        return 0;
    }
    return 0;
}

void igFrustCullTraversal_TraverseNode(igFrustCullTraversal *arg0, igNode *arg1) {
    if (arg0->_modeMask & 0x200) {
        BoundVolume *o = (BoundVolume *)arg1->_bound;
        void *var = o;
        if (o != 0) {
            int t = (int)g_igAABox_metaObject;
            if (t == o->ty()) {
                var = o;
            } else {
                igAABox *x = (igAABox *)arg0->_boundingBox;
                var = x;
                float *mn = x->_min.vec;
                float *mx = (float *)&x->_max;
                mn[0] = mn[1] = mn[2] = 3.4028235e38f;
                mx[0] = mx[1] = mx[2] = -3.4028235e38f;
                igVolume_ExtendBy((void **)x, (void **)o);
            }
            FUN_001c4c20(arg0, arg1, FUN_001c4ac0((CullFrustumView *)arg0, (CullBoundsView *)var));
            return;
        }
    }
    unsigned sel = arg1->_handle;
    Gap::Sg::igCommonTraversal::_getTraversalFunctions()->get(sel)((::igTraversal *)arg0, (::igObject *)arg1);
}

int igFrustCullTraversal_TraversePlanarShadowShader(void *arg0, TraversalNodeView *arg1) {
    return Gap::Sg::igCommonTraversal::_getTraversalFunctions()->get(arg1->_id)((::igTraversal *)arg0, (::igObject *)arg1);
}

namespace Gap {
namespace Sg {

bool igFrustCullTraversal::setOuterFrustCullScale(float scale) {
    if (scale < _outerScissorWindowScale && !(scale < 1.0f)) { _outerFrustCullScale = scale; DAT_0048da28[0] = 1.0f / scale; return 1; } return 0;
}
}
}

int igFrustCullTraversal_ClassifyBox(const float *boxMin, const float *boxMax, const float *matrix) {
    return FUN_001c47f0(matrix, boxMin, boxMax);
}

