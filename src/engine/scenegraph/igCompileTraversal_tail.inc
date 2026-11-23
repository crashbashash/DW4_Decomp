void FUN_001bb1f0(int arg0) {
    igCompileTraversal_RegisterClassFunction(((int)DAT_00562648[0]), arg0);
}

void FUN_001bb200(void) {
    *(int *)0x562648 = (int)Gap::Sg::igTraversalFunctionList::_instantiateFromPool(Memory_GetAllocatorBySelector(*(int *)0x587038));
}

void FUN_001bb230(void) {
    void *temp_a0;

    temp_a0 = *(void **)0x562648;
    if (temp_a0 != 0) {
        *(int *)((char *)temp_a0 + 4) = (int) (*(int *)((char *)temp_a0 + 4) - 1);
        if (((unsigned long long) ((long long) *(int *)((char *)temp_a0 + 4) << 0x29) >> 0x29) == 0) {
            igObject_Destroy((igObject *)temp_a0);
        }
    }
}

void igCompileTraversal_userConstruct(C_1bb280 *arg0, int arg1) {
    Q *t;
    Q *s;

    igCommonTraversal_userConstruct((igCommonTraversal *)arg0, arg1);
    if (arg1 == 0) {
        s = DAT_00562648[0];
        if (s != 0) {
            s->f4 += 1;
        }
        t = arg0->f28;
        if (t != 0) {
            t->f4 -= 1;
            if ((t->f4 & 0x7fffff) == 0) {
                igObject_Destroy((igObject *)t);
            }
        }
        arg0->f28 = s;
    }
}

void Gap__Sg__igCompileTraversal__vfunc_31(char *p) {
    clearEntries(*(RefCountedEntryList **)(p + 472));
    clearEntries(*(RefCountedEntryList **)(p + 476));
    *(int *)(*(char **)(p + 492) + 8) = 0;
    clearEntries(*(RefCountedEntryList **)(p + 504));
    p[484] = 0;
    p[496] = 0;
}

void igCompileTraversal_userDestruct(void **self) {
    igCommonTraversal_userDestruct((igObject *)self);
    ((igCompileTraversalVSlots *)(self))->slot31();
}

void igCompileTraversal_RegisterClassFunction(int arg0, int arg1) {
    igCommonTraversal_RegisterClassFunction((void *)arg0, (void *)arg1);
    if (igMetaObject_IsOfType((igMetaObject *)arg1, g_igProjectiveShadowShader_metaObject) != 0) {
        Gap::Sg::igTraversal::_setFunction((Gap::Sg::igTraversalFunctionList *)arg0, (igMetaObject *)arg1, (igTraversalFunction *)igCompileTraversal_TraverseProjectiveShadowShader);
        return;
    }
    if (igMetaObject_IsOfType((igMetaObject *)arg1, (igMetaObject *)g_igDOFShader_metaObject[0]) != 0) {
        Gap::Sg::igTraversal::_setFunction((Gap::Sg::igTraversalFunctionList *)arg0, (igMetaObject *)arg1, (igTraversalFunction *)FUN_001bcd90);
        return;
    }
    if (igMetaObject_IsOfType((igMetaObject *)arg1, g_igEnvironmentMapShader2_metaObject) != 0) {
        Gap::Sg::igTraversal::_setFunction((Gap::Sg::igTraversalFunctionList *)arg0, (igMetaObject *)arg1, (igTraversalFunction *)igCompileTraversal_TraverseEnvironmentMapShader2);
        return;
    }
    if (igMetaObject_IsOfType((igMetaObject *)arg1, (igMetaObject *)g_igMultiTextureShader_metaObject[0]) != 0) {
        Gap::Sg::igTraversal::_setFunction((Gap::Sg::igTraversalFunctionList *)arg0, (igMetaObject *)arg1, (igTraversalFunction *)FUN_001bcda0);
        return;
    }
    if (igMetaObject_IsOfType((igMetaObject *)arg1, (igMetaObject *)g_igCartoonShader_metaObject[0]) != 0) {
        Gap::Sg::igTraversal::_setFunction((Gap::Sg::igTraversalFunctionList *)arg0, (igMetaObject *)arg1, (igTraversalFunction *)FUN_001bcdb0);
        return;
    }
    if (igMetaObject_IsOfType((igMetaObject *)arg1, (igMetaObject *)g_igBumpMapShader_metaObject[0]) != 0) {
        Gap::Sg::igTraversal::_setFunction((Gap::Sg::igTraversalFunctionList *)arg0, (igMetaObject *)arg1, (igTraversalFunction *)FUN_001bcdc0);
        return;
    }
    if (igMetaObject_IsOfType((igMetaObject *)arg1, g_igPlanarShadowShader_metaObject) != 0) {
        Gap::Sg::igTraversal::_setFunction((Gap::Sg::igTraversalFunctionList *)arg0, (igMetaObject *)arg1, (igTraversalFunction *)igCompileTraversal_TraversePlanarShadowShader);
        return;
    }
    if (igMetaObject_IsOfType((igMetaObject *)arg1, (igMetaObject *)g_igShader_metaObject[0]) != 0) {
        Gap::Sg::igTraversal::_setFunction((Gap::Sg::igTraversalFunctionList *)arg0, (igMetaObject *)arg1, (igTraversalFunction *)FUN_001bcde0);
        return;
    }
    if (igMetaObject_IsOfType((igMetaObject *)arg1, g_igGeometry_metaObject) != 0) {
        Gap::Sg::igTraversal::_setFunction((Gap::Sg::igTraversalFunctionList *)arg0, (igMetaObject *)arg1, (igTraversalFunction *)igCompileTraversal_TraverseGeometry);
        return;
    }
    if (igMetaObject_IsOfType((igMetaObject *)arg1, g_unlinkedTransformClass_metaObject) != 0) {
        Gap::Sg::igTraversal::_setFunction((Gap::Sg::igTraversalFunctionList *)arg0, (igMetaObject *)arg1, (igTraversalFunction *)igCompileTraversal_TraverseJointTransform);
        return;
    }
    if (igMetaObject_IsOfType((igMetaObject *)arg1, g_igTransform_metaObject) != 0) {
        Gap::Sg::igTraversal::_setFunction((Gap::Sg::igTraversalFunctionList *)arg0, (igMetaObject *)arg1, (igTraversalFunction *)igCompileTraversal_TraverseTransform);
        return;
    }
    if (igMetaObject_IsOfType((igMetaObject *)arg1, (igMetaObject *)g_igCompiledGraph_metaObject[0]) != 0) {
        Gap::Sg::igTraversal::_setFunction((Gap::Sg::igTraversalFunctionList *)arg0, (igMetaObject *)arg1, (igTraversalFunction *)FUN_001bd0e0);
        return;
    }
    if (igMetaObject_IsOfType((igMetaObject *)arg1, g_igModelViewMatrixBoneSelect_metaObject) != 0) {
        Gap::Sg::igTraversal::_setFunction((Gap::Sg::igTraversalFunctionList *)arg0, (igMetaObject *)arg1, (igTraversalFunction *)igCompileTraversal_TraverseModelViewMatrixBoneSelect);
        return;
    }
    if (igMetaObject_IsOfType((igMetaObject *)arg1, g_igBlendMatrixSelect_metaObject) != 0) {
        Gap::Sg::igTraversal::_setFunction((Gap::Sg::igTraversalFunctionList *)arg0, (igMetaObject *)arg1, (igTraversalFunction *)igCompileTraversal_TraverseBlendMatrixSelect);
        return;
    }
    if (igMetaObject_IsOfType((igMetaObject *)arg1, g_igActor_metaObject) != 0) {
        Gap::Sg::igTraversal::_setFunction((Gap::Sg::igTraversalFunctionList *)arg0, (igMetaObject *)arg1, (igTraversalFunction *)igCompileTraversal_TraverseActor);
        return;
    }
    if (igMetaObject_IsOfType((igMetaObject *)arg1, g_igSegment_metaObject) != 0) {
        Gap::Sg::igTraversal::_setFunction((Gap::Sg::igTraversalFunctionList *)arg0, (igMetaObject *)arg1, (igTraversalFunction *)igCompileTraversal_TraverseSegment);
    }
}

void Gap__Sg__igCompileTraversal__vfunc_23(igCompileTraversal *self, int arg1) {
    int a1 = self->_vc;
    if (a1 != 0) {
        L0 *stack = (L0 *)self->_attrStack;
        ((VC104 *)(stack->f16->f16[stack->f68[Gap::Attrs::igClearAttr::getClassMeta()->_id]]->f20))->vX(a1, (int)stack);
    }
    {
    igSmartPointer<T_1bb880> matrix((T_1bb880 *)((void *)Gap::Attrs::igModelViewMatrixAttr::_instantiateFromPool(((Gap::Core::igObject *)self)->getMemoryPool())));
    igSmartPointer<T_1bb880> info((T_1bb880 *)((void *)FUN_001a3590((int)((Gap::Core::igObject *)self)->getMemoryPool())));
    T_1bb880 **slot = &info->f12;
    T_1bb880 *old = *slot;
    if (old != 0) {
        --old->_refCount;
        if ((old->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(old);
        }
    }
    *slot = 0;
    info->f8 = -1;
    info->f32 = 0;
    self->_currentBoneIndex = 1;
    int identity[16];
    igMatrix44f_SetIdentity((float *)identity);
    igCommonTraversal_SetViewMatrix((int)self, (int *)identity);
    matrix->setMatrix((int)&self->_viewMat);
    ((Gap::Core::igObjectList *)self->_mvmList)->append((Gap::Core::igObject *)matrix.p);
    ((Gap::Core::igObjectList *)self->_xformInfoList)->append((Gap::Core::igObject *)info.p);
    FUN_001b1030((igAttrStackManager *)self->_attrStack, (igAttr *)matrix.p);
    }
    if (self->_userTimeState != 0) {
        ((VC128L *)self)->vX(self->_timeLong);
    }
    Gap__Sg__igTraversal__vfunc_23((void *)self, arg1);
}

void Gap__Sg__igCompileTraversal__vfunc_24(igCompileTraversal *arg0, int arg1) {
    FUN_001b73d0((S_1b73d0 *)arg0);
    FUN_001d9bb0((void *)arg0->_sorter, arg0->_attrStack);
    if (arg0->_userTimeState != 0) {
        ((DW4VC_132_0 *)(((char *)(arg0) + 0)))->vX();
    }
    Gap__Sg__igTraversal__vfunc_24((void *)arg0, arg1);
}

int igCompileTraversal_TraverseTransform(int arg0, int arg1) {
    return igTransform_CompileChildrenAndPopMatrix((float *)FUN_001bbb30(arg1, arg0), (igTransform *)arg1, (igCompileTraversal *)arg0);
}

int igTransform_CompileChildrenAndPopMatrix(float *matrix, igTransform *self, igCompileTraversal *traversal) {
    int result;
    igAttrStackManager *manager;
    int target;
    manager = (igAttrStackManager *)traversal->_attrStack;
    target = self->_target;
    result = igTraversal_TraverseChildren((igTraversal *)traversal, (igNode *)self);
    if (target == 0) {
        FUN_001b11b0((A_1b11b0 *)manager, (B_1b11b0 *)Gap::Attrs::igModelViewMatrixAttr::getClassMeta());
    } else {
        FUN_001b1250((A_1b1250 *)manager, (B_1b1250 *)Gap::Attrs::igVertexBlendMatrixAttr::getClassMeta(), target - 1);
    }
    return result == 2 ? 2 : 0;
}

int igCompileTraversal_TraverseJointTransform(igTraversal *traversal, igTransform *node) {
    int result;
    igCompileTraversal *self = (igCompileTraversal *)traversal;
    self->_jointChainCount_++;
    if (self->_jointChainCount_ == 1) {
        igAttrStackManager *manager = (igAttrStackManager *)self->_attrStack;
        igObject *top = topAttr(((AttrObjectStackList *)manager->_attrStacks)->_data[((int *)manager->_attrStackIndexTable)[Gap::Attrs::igModelViewMatrixAttr::getClassMeta()->_id]]);
        igTDataList<igObject *> *mvms = (igTDataList<igObject *> *)self->_mvmList;
        self->_jointBaseMvmIndex = mvms->find(top);
    }
    result = igCompileTraversal_TraverseTransform((int)traversal, (int)node);
    self->_jointChainCount_--;
    return result;
}

/* A geometry's compiled transform record (FUN_001a3590 creates it). */
struct XformInfo_1bc1e0 : igObject {
    int _matrixIndex;
    igSmartPointer<igObject> _transform;
    char _pad16[12];
    unsigned char _shared;
    char _pad29[3];
    int _blendIndex;
};
class MatrixAttrView_1bc1e0 : public igVirtualObject {
public:
    virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4();
    virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
    virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14();
    virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24();
    virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
    virtual void setMatrix(const void *matrix);
};
class GeometryAttrView_1bc1e0 {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4();
    virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
    virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14();
    virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual int getMeta();
};
struct BoolAttr_1bc1e0 { char _pad0[12]; unsigned char _enabled; };
static inline void releaseKnown_1bc1e0(igObject *o) {
    o->release();
}
static inline AttrObjectStack *stackFor_1bc1e0(igAttrStackManager *m, igMetaObject *meta) {
    return ((AttrObjectStackList *)m->_attrStacks)->_data[((int *)m->_attrStackIndexTable)[meta->_id]];
}
static inline igObject *current_1bc1e0(AttrObjectStack *s) {
    if (s->_cachedOverride >= 0) return s->_data[s->_cachedOverride];
    if (s->_count != 0) return s->get(s->_count - 1);
    return (igObject *)s->_default;
}
/* Grows [mn, mx] to cover [bmin, bmax], one component at a time through igVec3f::operator[]. */
static inline void grow_1bc1e0(igVec3f &mn, igVec3f &mx, const igVec3f &bmin, const igVec3f &bmax) {
    if (FUN_001bcd70(bmin.vec, 0) < *FUN_001bcd60(mn.vec, 0)) *FUN_001bcd60(mn.vec, 0) = FUN_001bcd70(bmin.vec, 0);
    if (FUN_001bcd70(bmax.vec, 0) > *FUN_001bcd60(mx.vec, 0)) *FUN_001bcd60(mx.vec, 0) = FUN_001bcd70(bmax.vec, 0);
    if (FUN_001bcd70(bmin.vec, 1) < *FUN_001bcd60(mn.vec, 1)) *FUN_001bcd60(mn.vec, 1) = FUN_001bcd70(bmin.vec, 1);
    if (FUN_001bcd70(bmax.vec, 1) > *FUN_001bcd60(mx.vec, 1)) *FUN_001bcd60(mx.vec, 1) = FUN_001bcd70(bmax.vec, 1);
    if (FUN_001bcd70(bmin.vec, 2) < *FUN_001bcd60(mn.vec, 2)) *FUN_001bcd60(mn.vec, 2) = FUN_001bcd70(bmin.vec, 2);
    if (FUN_001bcd70(bmax.vec, 2) > *FUN_001bcd60(mx.vec, 2)) *FUN_001bcd60(mx.vec, 2) = FUN_001bcd70(bmax.vec, 2);
}

int igCompileTraversal_TraverseGeometry(igCompileTraversal *self, igGeometry *geometry) {
    if (geometry->_trigger == 0) {
        return 0;
    }
    int n = ((igTDataList<igObject *> *)geometry->_attributes)->_count;
    igVec3f mn;
    igVec3f mx;
    mn[0] = mn[1] = mn[2] = 1e20f;
    mx[0] = mx[1] = mx[2] = -1e20f;
    igTDataList<igObject *> *list = (igTDataList<igObject *> *)geometry->_attributes;
    int i;
    /* matching construct: `found` declared after `i` gives it s3 (retail); declared first it takes s0 */
    bool found = false;
    for (i = 0; i < n; i++) {
        igVec3f bmin;
        igVec3f bmax;
        igObject *attr = list->_data[i];
        if (((Gap::Core::igObject *)attr)->isOfType(Gap::Attrs::igGeometryAttr::getClassMeta()) != 0) {
            FUN_001b1fa0((igGeometryAttr *)attr, &bmin, &bmax);
            grow_1bc1e0(mn, mx, bmin, bmax);
            found = true;
        } else if (DAT_0055f158[0] == ((GeometryAttrView_1bc1e0 *)attr)->getMeta()) {
            FUN_001b21d0((A_1b21d0 *)attr, (igVec3f *)&bmin, (igVec3f *)&bmax);
            grow_1bc1e0(mn, mx, bmin, bmax);
            found = true;
        }
    }
    if (found) {
        if (self->_bound == 0) {
            igAABox *box = (igAABox *)igAABox_CreateInstance((int)((Gap::Core::igObject *)self)->getMemoryPool());
            ((igSmartPointer<igAABox> &)self->_bound) = box;
            ((igAABox *)self->_bound)->_min = mn;
            ((igAABox *)self->_bound)->_max = mx;
            releaseKnown_1bc1e0(box);
        } else {
            igVec3f curMin = ((igAABox *)self->_bound)->_min;
            igVec3f curMax = ((igAABox *)self->_bound)->_max;
            grow_1bc1e0(curMin, curMax, mn, mx);
            ((igAABox *)self->_bound)->_min = curMin;
            ((igAABox *)self->_bound)->_max = curMax;
        }
    }
    if ((geometry->_flags & 0x20) != 0) {
        return 0;
    }
    {
        /* matching construct: the meta before the stack test, and `hasList` before `restore` (s4 vs s3) */
        igMetaObject *listMeta = g_igVertexBlendMatrixListAttr_metaObject;
        bool hasList = !(stackFor_1bc1e0((igAttrStackManager *)self->_attrStack, listMeta)->_count == 0);
        igObject *restore = 0;
        bool pushed = false;
        if (hasList) {
            igSmartPointer<XformInfo_1bc1e0> info((XformInfo_1bc1e0 *)FUN_001a3590((int)((Gap::Core::igObject *)self)->getMemoryPool()));
            info->_transform = 0;
            info->_matrixIndex = -2;
            info->_blendIndex = -1;
            info->_shared = 0;
            igObject *mvm = (igObject *)Gap::Attrs::igModelViewMatrixAttr::getIdentityAttr();
            ((Gap::Core::igObjectList *)self->_mvmList)->append((Gap::Core::igObject *)mvm);
            ((Gap::Core::igObjectList *)self->_xformInfoList)->append((Gap::Core::igObject *)info.p);
            FUN_001b1030((igAttrStackManager *)self->_attrStack, (igAttr *)mvm);
            restore = topAttr(stackFor_1bc1e0((igAttrStackManager *)self->_attrStack, listMeta));
            FUN_001b1030((igAttrStackManager *)self->_attrStack, (igAttr *)restore);
        } else if (((BoolAttr_1bc1e0 *)current_1bc1e0(stackFor_1bc1e0((igAttrStackManager *)self->_attrStack, Gap::Attrs::igVertexBlendStateAttr::getClassMeta())))->_enabled != 0) {
            igTDataList<igObject *> *palettes = (igTDataList<igObject *> *)self->_boneMatrixPaletteList;
            igObject *palette = palettes->_count > 0 ? palettes->get(palettes->_count - 1) : 0;
            if (palette != 0) {
                igSmartPointer<MatrixAttrView_1bc1e0> mvm((MatrixAttrView_1bc1e0 *)Gap::Attrs::igModelViewMatrixAttr::_instantiateFromPool(((Gap::Core::igObject *)self)->getMemoryPool()));
                igSmartPointer<XformInfo_1bc1e0> info((XformInfo_1bc1e0 *)FUN_001a3590((int)((Gap::Core::igObject *)self)->getMemoryPool()));
                info->_transform = 0;
                info->_matrixIndex = 0;
                info->_blendIndex = -1;
                info->_shared = 0;
                mvm->setMatrix(&g_matrix44Identity);
                ((Gap::Core::igObjectList *)self->_mvmList)->append((Gap::Core::igObject *)mvm.p);
                ((Gap::Core::igObjectList *)self->_xformInfoList)->append((Gap::Core::igObject *)info.p);
                FUN_001b1030((igAttrStackManager *)self->_attrStack, (igAttr *)mvm.p);
                pushed = true;
            }
        }
        FUN_001db720((igSorter *)self->_sorter, (igGeometry *)geometry, (igAttrStackManager *)self->_attrStack);
        if (hasList) {
            FUN_001b1100((struct A_1b1100 *)self->_attrStack, (struct B_1b1100 *)restore);
            FUN_001b11b0((struct A_1b11b0 *)self->_attrStack, (struct B_1b11b0 *)Gap::Attrs::igModelViewMatrixAttr::getClassMeta());
        } else if (pushed) {
            FUN_001b11b0((struct A_1b11b0 *)self->_attrStack, (struct B_1b11b0 *)Gap::Attrs::igModelViewMatrixAttr::getClassMeta());
        }
    }
    return 0;
}

float *FUN_001bcd60(float *v, int i) {
    return &v[i];
}

float FUN_001bcd70(const float *v, int i) {
    return v[i];
}

int igCompileTraversal_TraverseProjectiveShadowShader(igCompileTraversal *self) {
    self->_containsShader = 1;
    return 2;
}

int FUN_001bcd90(void *arg0) {
    *(char *)((char *)(arg0) + 484) = 1;
    return 2;
}

int FUN_001bcda0(void *arg0) {
    *(char *)((char *)(arg0) + 484) = 1;
    return 2;
}

int FUN_001bcdb0(void *arg0) {
    *(char *)((char *)(arg0) + 484) = 1;
    return 2;
}

int FUN_001bcdc0(void *arg0) {
    *(char *)((char *)(arg0) + 484) = 1;
    return 2;
}

int igCompileTraversal_TraversePlanarShadowShader(igCompileTraversal *self) {
    self->_containsShader = 1;
    return 2;
}

int FUN_001bcde0(void *arg0) {
    *(char *)((char *)(arg0) + 484) = 1;
    return 2;
}

int igCompileTraversal_TraverseEnvironmentMapShader2(igCompileTraversal *self, void **arg1) {
    ((Gap::Core::igObjectList *)self->_environmentShader2List)->append((Gap::Core::igObject *)arg1);
    ((DW4VC_176_1 *)(arg1))->vX((int)(self));
    return 0;
}

int igCompileTraversal_TraverseModelViewMatrixBoneSelect(igCompileTraversal *self, int *arg1) {
    X_1bce40 *temp_s2;
    X_1bce40 *temp_v0;
    int temp_s0;
    int temp_s1;
    temp_s0 = self->_attrStack;
    self->_isSkin = 1;
    temp_s2 = ((X_1bce40 *)Gap::Attrs::igModelViewMatrixAttr::_instantiateFromPool(((Gap::Core::igObject *)self)->getMemoryPool()));
    temp_v0 = ((X_1bce40 *)FUN_001a3590((int)((Gap::Core::igObject *)self)->getMemoryPool()));
    temp_v0->f8 = arg1[8];
    ((Gap::Core::igObjectList *)self->_mvmList)->append((Gap::Core::igObject *)temp_s2);
    ((Gap::Core::igObjectList *)self->_xformInfoList)->append((Gap::Core::igObject *)temp_v0);
    temp_s2->f4 = temp_s2->f4 - 1;
    if (((unsigned long long) ((long long) temp_s2->f4 << 0x29) >> 0x29) == 0) {
        igObject_Destroy((igObject *)temp_s2);
    }
    temp_v0->f4 = temp_v0->f4 - 1;
    if (((unsigned long long) ((long long) temp_v0->f4 << 0x29) >> 0x29) == 0) {
        igObject_Destroy((igObject *)temp_v0);
    }
    FUN_001b1030((igAttrStackManager *)temp_s0, (igAttr *)temp_s2);
    temp_s1 = igTraversal_TraverseChildren((igTraversal *)self, (igNode *)arg1);
    FUN_001b1100((struct A_1b1100 *)temp_s0, (struct B_1b1100 *)temp_s2);
    if (temp_s1 == 2) {
        return 2;
    }
    return 0;
}

int igCompileTraversal_TraverseBlendMatrixSelect(A_1bcf70 *arg0, B_1bcf70 *arg1) {
    Obj_1bcf70 *o;
    int s0;
    s0 = arg0->f52;
    arg0->f496 = 1;
    o = ((Obj_1bcf70 *)Gap::Attrs::igBlendMatrixPaletteAttr::_instantiateFromPool(((Gap::Core::igObject *)arg0)->getMemoryPool()));
    ((Gap::Core::igObjectList *)arg0->f504)->append((Gap::Core::igObject *)o);
    o->refs = o->refs - 1;
    if ((o->refs & 0x7FFFFF) == 0) igObject_Destroy((igObject *)o);
    unsigned int n = arg1->f40->count;
    if (o->f24 < n) {
        if (o->f12 != 0) ((Gap::Core::igObject *)o)->free((void *)o->f12);
        if (o->f16 != 0) ((Gap::Core::igObject *)o)->free(o->f16);
        o->f16 = ((int *)((Gap::Core::igObject *)o)->malloc(n * 4));
        o->f24 = n;
    }
    o->f20 = n;
    int i = 0;
    while (i < arg1->f40->count) {
        o->f16[i] = arg1->f40->data[i];
        i++;
    }
    FUN_001b1030((igAttrStackManager *)s0, (igAttr *)o);
    int r = igCommonTraversal_TraverseAttrSet((igCommonTraversal *)arg0, (igAttrSet *)arg1);
    FUN_001b1100((struct A_1b1100 *)s0, (struct B_1b1100 *)o);
    if (r == 2) return 2;
    return 0;
}

int FUN_001bd0e0(int arg0, void *arg1) {
    if (*(int *)((char *)(*(int *)((char *)(arg1) + 32)) + 8) > 0) {
        ((DW4VC_124_0 *)(((char *)(arg1) + 0)))->vX();
    }
    if (igTraversal_TraverseChildren((igTraversal *)arg0, (igNode *)arg1) == 2) {
        return 2;
    }
    return 0;
}

int igCompileTraversal_TraverseActor(void) {
    return 0;
}

int igCompileTraversal_TraverseSegment(void) {
    return 0;
}

void FUN_001bd170(struct A_1bd170 *arg0, struct B_1bd170 *arg1) {
    int i;
    int n;
    int idx;
    struct B_1bd170 *c;
    struct Arr_1bd170 *o;
    n = arg1->list->n;
    for (i = 0; i < n; i++) {
        c = (struct B_1bd170 *)arg1->list->data[i];
        if (((Gap::Core::igObject *)c)->isOfType(Gap::Attrs::igDisplayListAttr::getClassMeta()) != 0) {
            FUN_001bd170(arg0, c);
        } else {
            o = arg0->out;
            idx = o->n;
            if (idx < o->cap) {
                o->n = n_of_1bd170(o) + 1;
            } else {
                ((Gap::Core::igDataList *)o)->resizeAndSetCount(idx + 1, 4);
            }
            o->data[idx] = (int)c;
        }
    }
}

class CompiledAttr {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18();
    virtual CompiledAttr *createCopy(int deep);
    virtual igMetaObject *getMeta();
    unsigned int _refCount;
};
typedef igTDataList<CompiledAttr *> CompiledAttrList;
template <class T> static inline void setValueAt(igTDataList<T> *list, int i, T value) {
    if (list->_count != 0 && i >= 0 && i < list->_count) {
        list->_data[i] = value;
    }
}
template <class T> static inline void appendValue(igTDataList<T> *list, T value) {
    int n = list->_count;
    if (n < list->_capacity) {
        list->_count = list->count() + 1;
    } else {
        ((Gap::Core::igDataList *)list)->resizeAndSetCount(n + 1, 4);
    }
    list->_data[n] = value;
}
struct CompiledAttrSet {
    char _pad0[32];
    CompiledAttrList *_attributes;
    char _pad36[16];
    int _defaultAttrMode;
    igTDataList<CompiledAttr **> *_attrSlots;
    CompiledAttrList *_slotAttrs;
    CompiledAttrList *_sharedAttrs;
};
static inline void appendSlotAttr(CompiledAttrSet *set, CompiledAttr *attr) {
    int n;
    CompiledAttrList *slotAttrs = set->_slotAttrs;
    n = slotAttrs->_count;
    if (n < slotAttrs->_capacity) {
        slotAttrs->_count = slotAttrs->count() + 1;
    } else {
        ((Gap::Core::igDataList *)slotAttrs)->resizeAndSetCount(n + 1, 4);
    }
    slotAttrs->_data[n] = attr;
}
extern "C" void igAttrSet_ShareCompiledAttrs(CompiledAttrSet *set, igCompileTraversal *traversal);

void igAttrSet_ShareCompiledAttrs(CompiledAttrSet *set, igCompileTraversal *traversal) {
    CompiledAttrList *defaults = (CompiledAttrList *)((igAttrStackManager *)traversal->_attrStack)->_attrDefaults;
    int i;
    int count;
    if (set->_defaultAttrMode == 0) {
        i = 0;
        while (i < set->_attributes->_count) {
            if (defaults->find(set->_attributes->_data[i]) != -1) {
                List_RemoveWordAt((igDataList *)set->_attributes, i);
            } else {
                i++;
            }
        }
        return;
    }
    i = set->_attributes->_count;
    if (set->_defaultAttrMode == 1) {
        while (i != 0) {
            i--;
            if (defaults->find(set->_attributes->_data[i]) == -1) {
                break;
            }
            List_RemoveWordAt((igDataList *)set->_attributes, set->_attributes->_count - 1);
        }
    }
    count = set->_attributes->_count;
    for (i = 0; i < count; i++) {
        CompiledAttr *attr = set->_attributes->_data[i];
        if (defaults->find(attr) != -1) {
            bool unique;
            appendValue(set->_attrSlots, &set->_attributes->_data[i]);
            int shared = set->_sharedAttrs->_count;
            unique = true;
            if (Gap::Attrs::igLightStateAttr::getClassMeta() != attr->getMeta()) {
                int j;
                for (j = 0; j < shared; j++) {
                    CompiledAttr *other = set->_sharedAttrs->_data[j];
                    if (((Gap::Core::igObject *)other)->isAlikeShallow((Gap::Core::igObject *)attr)) {
                        setValueAt(set->_attributes, i, other);
                        appendSlotAttr(set, other);
                        unique = false;
                        break;
                    }
                }
            }
            if (unique) {
                CompiledAttr *copy = attr->createCopy(0);
                setValueAt(set->_attributes, i, copy);
                appendSlotAttr(set, copy);
                ((Gap::Core::igObjectList *)set->_sharedAttrs)->append((Gap::Core::igObject *)copy);
                releaseRefCounted(copy);
            }
        }
    }
}

void FUN_001bd6b0(Links *links, Shape *shape) {
    int index;
    igTDataList<int> *indices;
    int n;
    int i;
    int j;
    void **slot;
    void *target;
    int index2;
    igTDataList<void **> *slots;
    n = shape->list->count();
    for (i = 0; i < n; i++) {
        target = shape->list->_data[i];
        j = links->targets->find(target);
        while (j != -1) {
            indices = links->indices;
            index = indices->_count;
            if (index < indices->_capacity) {
                indices->_count = indices->count() + 1;
            } else {
                ((Gap::Core::igDataList *)indices)->resizeAndSetCount(index + 1, 4);
            }
            indices->_data[index] = i;
            slot = links->targets->_data + j;
            slots = links->slots;
            index2 = slots->_count;
            if (index2 < slots->_capacity) {
                slots->_count = slots->count() + 1;
            } else {
                ((Gap::Core::igDataList *)slots)->resizeAndSetCount(index2 + 1, 4);
            }
            slots->_data[index2] = slot;
            j = links->targets->find(target, j + 1);
        }
    }
}

int FUN_001bd890(RemapOwner *o, RemapContext *ctx) {
    int count = o->_items->_count;
    int i;
    for (i = 0; i < count; i++) {
        RemapObject *item = o->_items->_data[i];
        if (((Gap::Core::igObject *)item)->isOfType(g_igVertexBlendMatrixListAttr_metaObject) != 0) {
            RemapEntry *e = ((RemapEntry *)FUN_001a2c70((int)(((void *)((Gap::Core::igObject *)ctx)->getMemoryPool()))));
            RemapTable *t;
            unsigned int n;
            int j;
            ((Gap::Core::igObjectList *)o->_entries)->append((Gap::Core::igObject *)e);
            releaseRefCounted(e);
            t = ((RemapTable *)Gap::Attrs::igBlendMatrixPaletteAttr::_instantiateFromPool(((Gap::Core::igObject *)ctx)->getMemoryPool()));
            setTarget(e, t);
            releaseRefCounted(t);
            e->_slot = &o->_items->_data[i];
            setAt(o->_items, i, (RemapObject *)t);
            n = item->_indices->_count;
            setCount_1bd890(t, n);
            for (j = 0; j < (int)n; j++) {
                int r = ctx->_pool->find(item->_indices->_data[j]);
                if (r == -1) {
                    r = 0;
                }
                t->_data[(unsigned int)j] = r;
            }
        } else if (((Gap::Core::igObject *)item)->isOfType(Gap::Attrs::igBlendMatrixPaletteAttr::getClassMeta()) != 0) {
            RemapEntry *e = ((RemapEntry *)FUN_001a2c70((int)(((void *)((Gap::Core::igObject *)ctx)->getMemoryPool()))));
            ((Gap::Core::igObjectList *)o->_entries)->append((Gap::Core::igObject *)e);
            releaseRefCounted(e);
            setTarget(e, item);
            e->_slot = &o->_items->_data[i];
            setAt(o->_items, i, item);
        } else if (Gap::Attrs::igMatrixOptStateAttr::getClassMeta() == item->getMeta()) {
            RemapObject *v = o->_fallback;
            setAt(o->_items, i, v);
        }
    }
    return 0;
}

void FUN_001bf020(void) {

}

