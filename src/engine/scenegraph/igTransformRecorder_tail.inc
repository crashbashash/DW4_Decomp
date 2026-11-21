void Gap__Sg__igTransformRecorder__vfunc_38(igTransformRecorder *self, const float *matrix) {
    igMatrix44f_Copy(self->_mvm, matrix);
}

void Gap__Sg__igTransformRecorder__vfunc_37(igTransformRecorder *self, const float *matrix) {
    igMatrix44f_Copy(self->_m, matrix);
}

int FUN_001baa10(RecorderTraversalView *o, TransformRecorderVisitor *v) {
    int state;
    int r;
    RecorderFramePool *pool;
    int i;
    long long t;
    RecorderFrame *frame;
    pool = o->_frames;
    state = o->_state;
    if (!(pool->_used < pool->_capacity)) {
        igObjectPool_Grow((igObjectPool *)pool, (igObject *(*)(int))Gap::Attrs::igTimeAttr::_instantiateFromPool);
    }
    i = pool->_used;
    pool->_used = i + 1;
    frame = pool->_data[i];
    t = v->sample(o->channel());
    o->begin(t);
    frame->_time = t;
    FUN_001b1030((igAttrStackManager *)state, (igAttr *)frame);
    r = igTraversal_TraverseChildren((igTraversal *)(o), (igNode *)v);
    FUN_001b1100((struct A_1b1100 *)state, (struct B_1b1100 *)frame);
    o->end();
    if (r == 2) {
        return 2;
    }
    return 0;
}

int FUN_001bab30(int a0, void **arg1) {
    void *arg0 = (void *)a0;
    int temp_s0;
    int temp_s1;
    int temp_s0_2;

    if ((((DW4VC_148_0 *)(arg1))->vX() != 0) && (((DW4VC_152_1 *)(arg1))->vX((int)(*(int *)((char *)(arg0) + 32))) == 0)) {
        return igTraversal_TraverseChildren((igTraversal *)arg0, (igNode *)arg1);
    }
    ((DW4VC_156_1 *)(arg1))->vX((int)(arg0));
    temp_s1 = ((DW4VC_172_0 *)(arg1))->vX() & 0xFF;
    if (temp_s1 != 0) {
        temp_s0_2 = *(int *)((char *)(arg0) + 68);
        FUN_001dc500((A_1dc500 *)temp_s0_2, ((DW4VC_164_0 *)(arg1))->vX(), 0);
    }
    temp_s0 = ((DW4VC_160_1 *)(arg1))->vX((int)(arg0));
    if (temp_s1 != 0) {
        FUN_001dc610(*(igSorter **)((char *)(arg0) + 68));
    }
    return temp_s0;
}

int igCommonTraversal_TraverseEnvironmentMapShader2(int arg0, void **arg1) {
    ((DW4VC_184_1 *)(arg1))->vX((int)(0));
    ((DW4VC_176_1 *)(arg1))->vX((int)(arg0));
    return 0;
}

int FUN_001bac90(int arg0, void **arg1) {
    ((DW4VC_184_1 *)(arg1))->vX((int)(1));
    ((DW4VC_176_1 *)(arg1))->vX((int)(arg0));
    return 0;
}

int igCommonTraversal_TraverseModelViewMatrixBoneSelect(DrawItemSource *arg0, DrawItemIndex *arg1) {
    char buf[64];
    DrawItemPool *pool = arg0->f72;
    int x = arg0->f52;
    int r;
    int idx;
    int cnt;
    PooledDrawItem *obj;
    int base;
    int off;
    BaseTable *a;
    if (pool->idx >= pool->cap) {
        igObjectPool_Grow((igObjectPool *)pool, (igObject *(*)(int))igModelViewMatrixAttr_CreateInstance);
    }
    idx = pool->idx;
    pool->idx = idx + 1;
    a = arg0->f248;
    obj = pool->data[idx];
    cnt = a->count;
    off = arg1->f32;
    if (cnt > 0) {
        int last = cnt - 1; base = a->data[last];
    } else {
        base = 0;
    }
    if (base == 0) {
        return 0;
    }
    if (off < 0) {
        return 0;
    }
    igMatrix44f_Multiply((float *)buf, (const float *)(base + (off << 6)), (const float *)base);
    obj->v(buf);
    FUN_001b1030((igAttrStackManager *)x, (igAttr *)obj);
    r = igTraversal_TraverseChildren((igTraversal *)arg0, (igNode *)arg1);
    FUN_001b11b0((struct A_1b11b0 *)x, (struct B_1b11b0 *)((int)g_igModelViewMatrixAttr_metaObject));
    if (r == 2) {
        return 2;
    }
    return 0;
}

int igCommonTraversal_TraverseBlendMatrixSelect(CompileTraversalHead *o, BlendNodeView *node) {
    char *out;
    char *palette;
    int slot;
    MatrixArrayList *l;
    int i;
    int state;
    MatrixFrame *frame;
    unsigned int n;
    int r;
    MatrixFramePool *pool;
    pool = o->_frames;
    state = o->_state;
    if (!(pool->_used < pool->_capacity)) {
        igObjectPool_Grow((igObjectPool *)pool, (igObject *(*)(int))igBlendMatricesAttr_Create);
    }
    slot = pool->_used;
    pool->_used = slot + 1;
    frame = pool->_data[slot];
    l = o->_palettes;
    palette = 0;
    if (l->_count > 0) {
        palette = paletteAt(l, l->_count - 1);
    }
    n = node->_boneIndices->_count;
    if (frame->_capacity < n) {
        if (frame->_matrices != 0) {
            ((Gap::Core::igObject *)frame)->free(frame->_matrices);
        }
        frame->_matrices = (char *)((Gap::Core::igObject *)frame)->mallocAligned(n << 6, 16);
        frame->_capacity = n;
    }
    frame->_count = n;
    out = frame->_matrices;
    for (i = 0; i < node->_boneIndices->_count; i++, out += 64) {
        igMatrix44f_Copy((float *)out, (const float *)(palette + (node->_boneIndices->_data[i] << 6)));
    }
    FUN_001b1030((igAttrStackManager *)state, (igAttr *)frame);
    r = igCommonTraversal_TraverseAttrSet((igCommonTraversal *)o, (igAttrSet *)node);
    FUN_001b1100((struct A_1b1100 *)state, (struct B_1b1100 *)frame);
    if (r == 2) {
        return 2;
    }
    return 0;
}

int igCommonTraversal_TraverseSegment(int arg0, struct S_1bafb0 *arg1) {
    int *var_a1;
    int *var_a1_2;
    int *var_a1_3;
    int temp_v0;
    int var_s0;

    var_a1 = arg1->f8;
    var_a1 = var_a1 ? var_a1 : (int *)emptyString;
    temp_v0 = FUN_001b7af0((void *)arg0, (int)var_a1);
    if (temp_v0 != 0) {
        var_a1_2 = arg1->f8;
        var_a1_2 = var_a1_2 ? var_a1_2 : (int *)emptyString;
        FUN_001b7770((igCommonTraversal *)arg0, (int)var_a1_2, 0);
        var_s0 = igTraversal_TraverseNode((igTraversal *)arg0, (igNode *)temp_v0);
        var_a1_3 = arg1->f8;
        var_a1_3 = var_a1_3 ? var_a1_3 : (int *)emptyString;
        FUN_001b7920((igCommonTraversal *)arg0, (int)var_a1_3);
    } else {
        var_s0 = igTraversal_TraverseChildren((igTraversal *)arg0, (igNode *)arg1);
    }
    return var_s0;
}

int FUN_001bb090(S_1e04c0 *self, KeyTrackView *track) {
    long long time;
    double fraction;

    time = ((DW4VC_104_3 *)self)->vX();
    fraction = (double)(time % 1000000000) / 1000000000;
    igSmartPointer<KeyTrackValue> found((KeyTrackValue *)FUN_001dcc80(track, (double)(time / 1000000000) + fraction), kRetainReference);
    if (found.p == 0) {
        return 0;
    }
    return igTraversal_TraverseNode((igTraversal *)self, (igNode *)found.p);
}

