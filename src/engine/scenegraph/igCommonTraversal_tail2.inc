long long Gap__Sg__igCommonTraversal__vfunc_26(igCommonTraversal *t) {
    int top; igLongStack *stack = (igLongStack *)t->_timeStack; int n = stack->_count; top = n - 1;
    if (n == 0) {
        if (!t->_timeBuffered) {
            if (t->_userTimeState) {
                t->_timeLongBuf = t->_timeLong;
            } else {
                t->_timeLongBuf = ((igTimerSourceView *)DAT_005871d8[0])->getTime();
            }
            t->_timeBuffered = 1;
        }
        return t->_timeLongBuf;
    }
    return ((long long *)stack->_data)[top];
}

int FUN_001b3ad0(igCommonTraversal *arg0, int arg1) {
    igAttrStackManager *p;
    igMetaObject *mo;
    igAttrStack *a0;
    igAttrStack *l;
    int a2;
    int km;
    int k;
    unsigned s2;
    bool flag;
    igBitMask *b;
    igBitMask *b2;
    unsigned idx;
    int n;
    unsigned *d;
    unsigned w;
    unsigned idx2;
    unsigned w2;

    p = (igAttrStackManager *)arg0->_attrStack;
    a0 = ((igAttrStack **)((igAttrStackList *)p->_attrStacks)->_data)[((int *)p->_attrStackIndexTable)[g_igModelViewMatrixAttr_metaObject->_id]];
    k = a0->_count;
    km = k - 1;
    if (k == 0) {
        a2 = 0;
    } else {
        a2 = ((int *)a0->_data)[km];
    }
    ((H_1b2fa0 *)DAT_005625f0)->vX(arg1, a2);
    mo = igTextureBindAttr_GetMetaObject();
    p = (igAttrStackManager *)arg0->_attrStack;
    l = ((igAttrStack **)((igAttrStackList *)p->_attrStacks)->_data)[((int *)p->_attrStackIndexTable)[mo->_id]];
    if (l != 0) {
        flag = !(l->_count == 0);
    } else {
        flag = 0;
    }
    b = ((H_1b2fa0 *)DAT_005625f0)->f184;
    s2 = b->_bitCount;
    igBitMask_SetBitCount((igBitMask *)b, s2 + 1);
    b2 = ((H_1b2fa0 *)DAT_005625f0)->f184;
    if (flag) {
        idx = s2 >> 5;
        w = ((unsigned *)b2->_data)[idx] | (1 << (s2 & 31));
        if (b2->_count != 0 && (int)idx >= 0 && (int)idx < b2->_count) {
            ((unsigned *)b2->_data)[idx] = w;
        }
    } else {
        idx2 = s2 >> 5;
        w2 = ((unsigned *)b2->_data)[idx2] & ~(1 << (s2 & 31));
        if (b2->_count != 0 && (int)idx2 >= 0 && (int)idx2 < b2->_count) {
            ((unsigned *)b2->_data)[idx2] = w2;
        }
    }
    FUN_001c5660((Z_1c5660 *)arg1, 4, 1);
    return 0;
}

void FUN_001b3c90(A0 *arg0, A1 *arg1) {
    int temp_a0;
    int temp_s0;

    FUN_001b3030((igProjectiveShadowShader *)arg0, (igCommonTraversal *)arg1);
    temp_a0 = arg0->f160;
    FUN_00157200((igImage *)temp_a0, 1, (igImage *)temp_a0);
    temp_s0 = arg1->f52;
    FUN_001dc500((A_1dc500 *)arg1->f68, 0, 0);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_005625e0[0]);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_005625e8[0]);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_005625b8[0]);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_005625c8[0]);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_005625c0[0]);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_005625d0[0]);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)arg0->f176);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)arg0->f32);
    igTraversal_TraverseChildren((igTraversal *)arg1, (igNode *)arg0);
    igAttrStackManager_PopOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)arg0->f32);
    igAttrStackManager_PopOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)arg0->f176);
    igAttrStackManager_PopOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_005625d0[0]);
    igAttrStackManager_PopOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_005625c0[0]);
    igAttrStackManager_PopOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_005625c8[0]);
    igAttrStackManager_PopOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_005625b8[0]);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_00562598[0]);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_005625d0[0]);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_005625c8[0]);
    igTraversal_TraverseChildren((igTraversal *)arg1, (igNode *)arg0);
    igAttrStackManager_PopOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_005625c8[0]);
    igAttrStackManager_PopOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_005625d0[0]);
    igAttrStackManager_PopOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_00562598[0]);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_005625b0[0]);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_005625c8[0]);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_005625c0[0]);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_005625d0[0]);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)arg0->f180);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)arg0->f32);
    igTraversal_TraverseChildren((igTraversal *)arg1, (igNode *)arg0);
    igAttrStackManager_PopOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)arg0->f32);
    igAttrStackManager_PopOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)arg0->f180);
    igAttrStackManager_PopOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_005625d0[0]);
    igAttrStackManager_PopOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_005625c0[0]);
    igAttrStackManager_PopOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_005625c8[0]);
    igAttrStackManager_PopOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_005625b0[0]);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_005625a8[0]);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_005625d0[0]);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_005625c8[0]);
    igTraversal_TraverseChildren((igTraversal *)arg1, (igNode *)arg0);
    igAttrStackManager_PopOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_005625c8[0]);
    igAttrStackManager_PopOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_005625d0[0]);
    igAttrStackManager_PopOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_005625a8[0]);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_005625d8[0]);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_005625c8[0]);
    igAttrStackManager_PushOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_005625a0[0]);
    igTraversal_TraverseChildren((igTraversal *)arg1, (igNode *)arg0);
    igAttrStackManager_PopOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_005625a0[0]);
    igAttrStackManager_PopOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_005625c8[0]);
    igAttrStackManager_PopOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_005625d8[0]);
    igAttrStackManager_PopOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_005625e8[0]);
    igAttrStackManager_PopOverrideAttr((igAttrStackManager *)temp_s0, (igAttr *)DAT_005625e0[0]);
    FUN_001dc610((igSorter *)arg1->f68);
}

void FUN_001b3ff0(void *arg0, int arg1) {
    void **temp_a0;
    void **temp_a0_2;

    if (FUN_001b4130((struct O4130 *)arg0) == 0) {
        igTraversal_TraverseChildren((igTraversal *)arg1, (igNode *)arg0);
        return;
    }
    FUN_001b4220((struct A4220 *)arg0, (struct B4220 *)arg1);
    FUN_001b42c0((TravFlattenView *)arg0, arg1);
    temp_a0 = (void **)(*(int *)((char *)(arg0) + 176));
    ((DW4VC_132_1 *)(temp_a0))->vX((int)(*(int *)((char *)(arg0) + 48)));
    temp_a0_2 = (void **)(*(int *)((char *)(arg0) + 180));
    ((DW4VC_132_1 *)(temp_a0_2))->vX((int)(*(int *)((char *)(arg0) + 52)));
    FUN_001b3c90((A0 *)arg0, (A1 *)arg1);
}

void FUN_001b4090(T_1b2fa0 *arg0, int arg1, int arg2) {
    if (arg1 < 8) {
        if (arg2 != 0) {
            arg0->flags |= (1 << arg1);
        } else {
            arg0->flags &= ~(1 << arg1);
        }
    }
}

int FUN_001b40f0(void *arg0, int arg1) {
    if (arg1 >= 8) {
        return 0;
    }
    return *(unsigned char *)((char *)(arg0) + 64) & (1 << arg1) & 0xFF;
}

int FUN_001b4120(int *p)
{
    return *(unsigned char *)((char *)p + 64);
}

int FUN_001b4130(struct O4130 *arg0) {
    struct Rc_1b2fa0 *temp_a0;
    struct Rc_1b2fa0 *temp_v0;

    if ((arg0->f32 == 0) || (FUN_001b4120((int *)arg0) == 0) || (arg0->f56->f8 == 0)) {
        return 0;
    }
    if (arg0->f160 == 0) {
        temp_v0 = ((struct Rc_1b2fa0 *)igTextureAttr_GetImage((igTextureAttr *)arg0->f32->f12, 0));
        if (temp_v0 != 0) {
            temp_v0->rc = temp_v0->rc + 1;
        }
        temp_a0 = arg0->f160;
        if (temp_a0 != 0) {
            temp_a0->rc = temp_a0->rc - 1;
            if ((temp_a0->rc & 0x7FFFFF) == 0) {
                igObject_Destroy((igObject *)temp_a0);
            }
        }
        arg0->f160 = temp_v0;
        if (arg0->f160 == 0) {
            return 0;
        }
    }
    if (arg0->f160->f16 != 1) {
        return 0;
    }
    return 1;
}

void FUN_001b4220(struct A4220 *arg0, struct B4220 *arg1) {
    int temp_s2;
    int n;
    int i;
    struct Q_1b2fa0 *q;

    q = arg0->f144;
    temp_s2 = arg1->f52;
    n = 0;
    if (q != 0) {
        n = q->count;
    }
    if (n > 8) {
        n = 8;
    }
    for (i = 0; i < n; i++) {
        FUN_001b4090((T_1b2fa0 *)arg0, i, igAttrStackManager_IsLightEnabled((igAttrStackManager *)temp_s2, (igLightAttr *)arg0->f144->data[i]));
    }
}

void FUN_001b42c0(TravFlattenView *self, int root) {
    int saved[32];
    igTDataList<igTraversalFunctionPtr> *table = g_igCommonTraversal_travProcs;
    int meta = (int)g_igGeometry_metaObject;
    int n = igMetaObject_CountTree((igMetaObject *)meta);
    int i;
    for (i = 0; i < n; i++) {
        TravObject *m = ((TravObject *)igMetaObject_GetTreeNode((igMetaObject *)meta, i));
        saved[i] = (int)table->_data[m->_id];
        igTraversal_RegisterFunction((igTraversalFunctionList *)table, (igMetaObject *)m, (void *)((void *)FUN_001b3ad0));
    }
    DAT_005625f0 = self;
    clearRetained(self->_a);
    clearRetained(self->_b);
    igTraversal_TraverseChildren((igTraversal *)root, (igNode *)self);
    for (i = 0; i < n; i++) {
        igTraversal_RegisterFunction((igTraversalFunctionList *)table, (igMetaObject *)(((TravObject *)igMetaObject_GetTreeNode((igMetaObject *)meta, i))), (void *)((void *)saved[i]));
    }
}

void FUN_001b4500(struct O4500 *o, struct S4500 *s, int b) {
    s = o->s;
    if (s != 0) {
        if (s->k == 1) { o->x = s->firstX; o->y = s->firstY; o->z = s->firstZ; o->w = 0x3F800000; return; }
        o->x = s->secondX; o->y = s->secondY; o->z = s->secondZ; o->w = 0;
    }
}

int FUN_001b4bb0(igCommonTraversal *traversal, int node) {
    igAttrStackManager *manager;
    igAttrStack *l;
    int v;

    manager = (igAttrStackManager *)traversal->_attrStack;
    l = ((igAttrStack **)((igAttrStackList *)manager->_attrStacks)->_data)[((int *)manager->_attrStackIndexTable)[g_igModelViewMatrixAttr_metaObject->_id]];
    if (l->_count == 0) {
        v = 0;
    } else {
        v = *(int *)(l->_data + ((l->_count - 1) * 4));
    }
    DAT_00562638[0]->vX(node, v);
    return 0;
}

/* The attribute objects igCommonTraversal_DrawCartoonShader drives through their virtual slots. */
class ShaderAttrView_1b4c40 : public igVirtualObject {
public:
    virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5();
    virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10();
    virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();
    virtual int query(int what);
    virtual void d22();
    virtual void setEnabled(int enabled);
    virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28();
    virtual void d29();
    virtual void set30(int value);
    virtual void set31(int value);
    virtual void set32(int value);
    virtual void set33(int value);
    short _cachedAttrIndex;
    short _cachedUnitID;
    ShaderAttrView_1b4c40 *_texture;
};
struct igCartoonShader {
    char _pad0[32];
    ShaderAttrView_1b4c40 *_oTex;
    ShaderAttrView_1b4c40 *_sTex;
    int _mats;
    int _geoms;
    int _oTexCoordIndex;
    int _sTexCoordIndex;
    char _pad56[92];
    ShaderAttrView_1b4c40 *_tcs0;
    ShaderAttrView_1b4c40 *_tcs1;
};
struct ImageView_1b4c40 { char _pad0[16]; int _format; char _pad20[24]; int _levels; };
extern "C" ShaderAttrView_1b4c40 *DAT_005625f8;
extern "C" ShaderAttrView_1b4c40 *DAT_00562600;
extern "C" ShaderAttrView_1b4c40 *DAT_00562608;
extern "C" ShaderAttrView_1b4c40 *DAT_00562610;
extern "C" ShaderAttrView_1b4c40 *DAT_00562618;
extern "C" ShaderAttrView_1b4c40 *DAT_00562620;
extern "C" ShaderAttrView_1b4c40 *DAT_00562628;
extern "C" ShaderAttrView_1b4c40 *DAT_00562630;
static inline void pushAttr_1b4c40(igAttrStackManager *manager, ShaderAttrView_1b4c40 *attr) {
    /* matching construct: declaration order n, stack, slot, pushed (slot s2, count s5) */
    int n;
    AttrObjectStack *stack;
    int slot;
    igObject *pushed;
    slot = attr->_cachedUnitID + ((int *)manager->_attrStackIndexTable)[attr->_cachedAttrIndex];
    stack = ((AttrObjectStackList *)manager->_attrStacks)->_data[slot];
    if (stack->_cachedOverride < 0) {
        stack->_cachedOverride = stack->_count;
    }
    pushed = (igObject *)attr;
    n = stack->getCount();
    if (n < stack->_capacity) {
        stack->_count = stack->_count + 1;
    } else {
        ((Gap::Core::igDataList *)stack)->resizeAndSetCount(n + 1, 4);
    }
    stack->set(n, &pushed);
    igAttrStackManager_MarkStackChanged(manager, (igAttrStack *)stack, slot);
}
static inline void popAttr_1b4c40(igAttrStackManager *manager, ShaderAttrView_1b4c40 *attr_) {
    /* matching construct: the attribute held as an igObject copy takes a3, the pop proc a2 */
    igObject *attr = (igObject *)attr_;
    int slot = attr_->_cachedUnitID + ((int *)manager->_attrStackIndexTable)[attr_->_cachedAttrIndex];
    AttrObjectStack *stack = ((AttrObjectStackList *)manager->_attrStacks)->_data[slot];
    igObject *top = stack->get(stack->_count - 1);
    void (*pop)(igObject *, int) = stack->_popProc;
    if (pop != 0 && top == attr) {
        pop(top, manager->_popProcData);
    }
    stack->_count = stack->_count - 1;
    if (stack->_count == stack->_cachedOverride) {
        stack->_cachedOverride = -1;
    }
    igAttrStackManager_MarkStackChanged(manager, (igAttrStack *)stack, slot);
}

void igCommonTraversal_DrawCartoonShader(igCartoonShader *self, igCommonTraversal *traversal) {
    int saved[32];
    /* matching construct: declaration order (count s6, procs s5, meta s4, manager s3), from a 120-order search */
    int i;
    int count;
    igTDataList<igTraversalFunctionPtr> *procs;
    igMetaObject *meta;
    igAttrStackManager *manager;
    ImageView_1b4c40 *image;
    if (self->_oTex == 0 || self->_sTex == 0) {
        return;
    }
    self->_oTex->setEnabled(0);
    if (((ImageView_1b4c40 *)igTextureAttr_GetImage((igTextureAttr *)self->_oTex->_texture, 0))->_format != 1) {
        return;
    }
    image = (ImageView_1b4c40 *)igTextureAttr_GetImage((igTextureAttr *)self->_oTex->_texture, 0);
    if (image->_levels != 1) {
        FUN_00157200((igImage *)image, 1, (igImage *)image);
    }
    self->_oTex->_texture->set32(0);
    self->_oTex->_texture->set33(0);
    self->_sTex->_texture->set32(0);
    self->_sTex->_texture->set33(0);
    self->_sTex->_texture->set30(0);
    self->_oTex->_texture->set31(0);
    self->_tcs0->set31(self->_sTexCoordIndex);
    self->_tcs1->set31(self->_oTexCoordIndex);
    manager = (igAttrStackManager *)traversal->_attrStack;
    procs = g_igCommonTraversal_travProcs;
    meta = g_igGeometry_metaObject;
    count = igMetaObject_CountTree(meta);
    for (i = 0; i < count; i++) {
        igMetaObject *node = (igMetaObject *)igMetaObject_GetTreeNode(meta, i);
        saved[i] = (int)procs->_data[node->_id];
        igTraversal_RegisterFunction((igTraversalFunctionList *)procs, node, (void *)FUN_001b4bb0);
    }
    DAT_00562638[0] = (VC_1b2fa0 *)self;
    ((Gap::Core::igObjectList *)((igTDataList<igObject *> *)self->_mats))->setCount(0);
    ((Gap::Core::igObjectList *)((igTDataList<igObject *> *)self->_geoms))->setCount(0);
    igTraversal_TraverseChildren((igTraversal *)traversal, (igNode *)self);
    for (i = 0; i < count; i++) {
        igTraversal_RegisterFunction((igTraversalFunctionList *)procs, (igMetaObject *)igMetaObject_GetTreeNode(meta, i), (void *)saved[i]);
    }
    FUN_001dc500((A_1dc500 *)traversal->_sorter, 0, 0);
    FUN_001b4570((LightingTexGenView *)self, traversal);
    if (((ShaderAttrView_1b4c40 *)traversal->_capabilityManager)->query(8) >= 2) {
        if (DAT_00562620 == 0) {
            DAT_00562620 = (ShaderAttrView_1b4c40 *)igTextureStateAttr_CreateInstance((int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleSystem));
            DAT_00562620->set30(1);
            DAT_00562620->setEnabled(1);
        }
        self->_oTex->setEnabled(1);
        self->_tcs1->setEnabled(1);
        pushAttr_1b4c40(manager, DAT_00562630);
        pushAttr_1b4c40(manager, DAT_00562628);
        pushAttr_1b4c40(manager, DAT_00562600);
        pushAttr_1b4c40(manager, self->_sTex);
        pushAttr_1b4c40(manager, DAT_00562610);
        pushAttr_1b4c40(manager, self->_tcs0);
        pushAttr_1b4c40(manager, DAT_00562620);
        pushAttr_1b4c40(manager, self->_oTex);
        pushAttr_1b4c40(manager, DAT_00562618);
        pushAttr_1b4c40(manager, self->_tcs1);
        igTraversal_TraverseChildren((igTraversal *)traversal, (igNode *)self);
        popAttr_1b4c40(manager, self->_tcs1);
        popAttr_1b4c40(manager, DAT_00562618);
        popAttr_1b4c40(manager, self->_oTex);
        popAttr_1b4c40(manager, DAT_00562620);
        popAttr_1b4c40(manager, self->_tcs0);
        popAttr_1b4c40(manager, DAT_00562610);
        popAttr_1b4c40(manager, self->_sTex);
        popAttr_1b4c40(manager, DAT_00562600);
        popAttr_1b4c40(manager, DAT_00562628);
        popAttr_1b4c40(manager, DAT_00562630);
    } else {
        pushAttr_1b4c40(manager, DAT_00562630);
        pushAttr_1b4c40(manager, DAT_00562628);
        pushAttr_1b4c40(manager, DAT_00562600);
        pushAttr_1b4c40(manager, DAT_00562610);
        pushAttr_1b4c40(manager, self->_sTex);
        pushAttr_1b4c40(manager, self->_tcs0);
        igTraversal_TraverseChildren((igTraversal *)traversal, (igNode *)self);
        popAttr_1b4c40(manager, self->_tcs0);
        popAttr_1b4c40(manager, self->_sTex);
        pushAttr_1b4c40(manager, self->_oTex);
        pushAttr_1b4c40(manager, self->_tcs1);
        pushAttr_1b4c40(manager, DAT_00562608);
        pushAttr_1b4c40(manager, DAT_005625f8);
        igTraversal_TraverseChildren((igTraversal *)traversal, (igNode *)self);
        popAttr_1b4c40(manager, DAT_005625f8);
        popAttr_1b4c40(manager, DAT_00562608);
        popAttr_1b4c40(manager, self->_tcs1);
        popAttr_1b4c40(manager, self->_oTex);
        popAttr_1b4c40(manager, DAT_00562610);
        popAttr_1b4c40(manager, DAT_00562600);
        popAttr_1b4c40(manager, DAT_00562628);
        popAttr_1b4c40(manager, DAT_00562630);
    }
    FUN_001dc610((igSorter *)traversal->_sorter);
}

void igCommonTraversal_RegisterClass(int arg0) {
    igCommonTraversal_RegisterClassFunction(g_igCommonTraversal_travProcs, (void *)arg0);
}

void igCommonTraversal_RegisterClassFunction(void *self, void *meta) {
    igTraversal_RegisterClassFunction((int)(self), (int)(meta));
    if (igMetaObject_IsOfType((igMetaObject *)meta, (igMetaObject *)(((int)igNode_GetMetaObject()))) != 0) {
        NodeProcTable t = DAT_0048d8f0;
        int i;
        t.e[0].meta = (int)g_igActor_metaObject;
        t.e[1].meta = (int)g_igProjectiveShadowShader_metaObject;
        t.e[2].meta = g_igSelfShadowShader_metaObject;
        t.e[3].meta = g_igDOFShader_metaObject[0];
        t.e[4].meta = (int)g_igSegment_metaObject;
        t.e[5].meta = (int)g_igEnvironmentMapShader2_metaObject;
        t.e[6].meta = g_igInverseKinematicsHandle_metaObject;
        t.e[7].meta = g_igInverseKinematicsSolver_metaObject;
        t.e[8].meta = g_igInverseKinematicsJoint_metaObject;
        t.e[9].meta = g_igMultiTextureShader_metaObject[0];
        t.e[10].meta = g_igMultiResolutionMeshInstance_metaObject;
        t.e[11].meta = g_igCartoonShader_metaObject[0];
        t.e[12].meta = g_igBumpMapShader_metaObject[0];
        t.e[13].meta = (int)g_unlinkedTransformClass_metaObject;
        t.e[14].meta = g_igMorphInstance_metaObject;
        t.e[15].meta = g_igMorphInstance2_metaObject;
        t.e[16].meta = (int)g_igLod_metaObject;
        t.e[17].meta = (int)g_igLightStateSet_metaObject;
        t.e[18].meta = (int)g_igLightSet_metaObject;
        t.e[19].meta = (int)g_igGeometry_metaObject;
        t.e[20].meta = (int)g_igPlanarShadowShader_metaObject;
        t.e[21].meta = g_igShader_metaObject[0];
        t.e[22].meta = g_igShader2_metaObject;
        t.e[23].meta = (int)g_igBlendMatrixSelect_metaObject;
        t.e[24].meta = (int)g_igOverrideAttrSet_metaObject;
        t.e[25].meta = (int)g_igAttrSet_metaObject;
        t.e[26].meta = (int)g_igTransform_metaObject;
        t.e[27].meta = (int)g_igBillboard_metaObject;
        t.e[28].meta = (int)g_igSwitch_metaObject;
        t.e[29].meta = (int)g_igTransformRecorder_metaObject;
        t.e[30].meta = g_igTimeTransform_metaObject[0];
        t.e[31].meta = g_igCompiledGraph_metaObject[0];
        t.e[32].meta = (int)g_igModelViewMatrixBoneSelect_metaObject;
        t.e[33].meta = g_igTimeSwitch_metaObject;
        for (i = 0; i < 34; i++) {
            NodeProcEntry *e = &t.e[i];
            if (e->meta != 0 && igMetaObject_IsOfType((igMetaObject *)meta, (igMetaObject *)e->meta) != 0) {
                igTraversal_RegisterFunction((igTraversalFunctionList *)self, (igMetaObject *)meta, (void *)e->proc);
                return;
            }
        }
    }
}

void igCommonTraversal_userConstruct(igCommonTraversal *self, int arg1) {
    igObject *s0;
    igObject *a0;

    igTraversal_userConstruct((A_1e0380 *)self, arg1);
    if (arg1 == 0) {
        s0 = g_igCommonTraversal_travProcs;
        if (s0 != 0) {
            s0->_refCount = s0->_refCount + 1;
        }
        a0 = (igObject *)self->_travProcs;
        if (a0 != 0) {
            --a0->_refCount;
            if (((unsigned long long)(long long)a0->_refCount & 0x7fffffULL) == 0) {
                igObject_Destroy((igObject *)a0);
            }
        }
        self->_travProcs = (int)s0;
        ((C_1b2fa0 *)self->_matrixOptimization)->vX(0);
        *(char *)(self->_normalizeNormalsEnable + 12) = 1;
    }
}

void igCommonTraversal_UserRegister(void) {
    g_igCommonTraversal_travProcs = (igTDataList<igTraversalFunctionPtr> *)igTraversalFunctionList_CreateInstance((int)Memory_GetAllocatorBySelector(*(int *)0x587038));
    Gap::Attrs::igAttr::arkRegister();
    igTextureBindAttr_EnsureRegistered();
    igModelViewMatrixAttr_EnsureRegistered();
    igVertexBlendMatrixAttr_EnsureRegistered();
    igTextureMatrixAttr_EnsureRegistered();
    Gap::Attrs::igVertexBlendStateAttr::arkRegister();
    igVertexBlendMatrixListAttr_EnsureRegistered();
}

void igCommonTraversal_UserUnregister(void) {
    igTDataList<igTraversalFunctionPtr> *procs = g_igCommonTraversal_travProcs;
    IG_OBJECT_RELEASE(procs);
}

