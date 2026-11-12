void Gap__Sg__igTransformRecorder__vfunc_38(int a0) {
    Matrix44_Copy((char *)a0 + 96);
}

void Gap__Sg__igTransformRecorder__vfunc_37(void *arg0) {
    Matrix44_Copy((int)((char *)arg0 + 32));
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
        igObjectPool_Grow((List_1dca40 *)pool, (Obj_1dca40 * (*)(int))igTimeAttr_CreateInstance);
    }
    i = pool->_used;
    pool->_used = i + 1;
    frame = pool->_data[i];
    t = v->sample(o->channel());
    o->begin(t);
    frame->_time = t;
    FUN_001b1030((igAttrStackManager *)state, (igAttr *)frame);
    r = igTraversal_TraverseChildren((int)(o), (S_1e07a0 *)v);
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
        return igTraversal_TraverseChildren((int)arg0, (S_1e07a0 *)arg1);
    }
    ((DW4VC_156_1 *)(arg1))->vX((int)(arg0));
    temp_s1 = ((DW4VC_172_0 *)(arg1))->vX() & 0xFF;
    if (temp_s1 != 0) {
        temp_s0_2 = *(int *)((char *)(arg0) + 68);
        FUN_001dc500((A_1dc500 *)temp_s0_2, ((DW4VC_164_0 *)(arg1))->vX(), 0);
    }
    temp_s0 = ((DW4VC_160_1 *)(arg1))->vX((int)(arg0));
    if (temp_s1 != 0) {
        FUN_001dc610(*(int *)((char *)(arg0) + 68));
    }
    return temp_s0;
}

int FUN_001bac30(int arg0, void **arg1) {
    ((DW4VC_184_1 *)(arg1))->vX((int)(0));
    ((DW4VC_176_1 *)(arg1))->vX((int)(arg0));
    return 0;
}

int FUN_001bac90(int arg0, void **arg1) {
    ((DW4VC_184_1 *)(arg1))->vX((int)(1));
    ((DW4VC_176_1 *)(arg1))->vX((int)(arg0));
    return 0;
}

int FUN_001bacf0(DrawItemSource *arg0, DrawItemIndex *arg1) {
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
        igObjectPool_Grow((List_1dca40 *)pool, (Obj_1dca40 * (*)(int))FUN_001356b0);
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
    FUN_001904f0(buf, base + (off << 6), base);
    obj->v(buf);
    FUN_001b1030((igAttrStackManager *)x, (igAttr *)obj);
    r = igTraversal_TraverseChildren((int)arg0, (S_1e07a0 *)arg1);
    FUN_001b11b0((struct A_1b11b0 *)x, (struct B_1b11b0 *)((int *)g_igModelViewMatrixAttr_metaObject)[0]);
    if (r == 2) {
        return 2;
    }
    return 0;
}

int FUN_001bae20(CompileTraversalHead *o, BlendNodeView *node) {
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
        igObjectPool_Grow((List_1dca40 *)pool, (Obj_1dca40 * (*)(int))FUN_00139c10);
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
            FUN_00300f50(frame, frame->_matrices);
        }
        frame->_matrices = FUN_00300db0(frame, n << 6, 16);
        frame->_capacity = n;
    }
    frame->_count = n;
    out = frame->_matrices;
    for (i = 0; i < node->_boneIndices->_count; i++, out += 64) {
        Matrix44_Copy(out, palette + (node->_boneIndices->_data[i] << 6));
    }
    FUN_001b1030((igAttrStackManager *)state, (igAttr *)frame);
    r = FUN_001b9320(o, node);
    FUN_001b1100((struct A_1b1100 *)state, (struct B_1b1100 *)frame);
    if (r == 2) {
        return 2;
    }
    return 0;
}

int FUN_001bafb0(int arg0, struct S_1bafb0 *arg1) {
    int *var_a1;
    int *var_a1_2;
    int *var_a1_3;
    int temp_v0;
    int var_s0;

    var_a1 = arg1->f8;
    var_a1 = var_a1 ? var_a1 : &emptyString[0];
    temp_v0 = FUN_001b7af0((void *)arg0, (int)var_a1);
    if (temp_v0 != 0) {
        var_a1_2 = arg1->f8;
        var_a1_2 = var_a1_2 ? var_a1_2 : &emptyString[0];
        FUN_001b7770((igCommonTraversal *)arg0, (int)var_a1_2, 0);
        var_s0 = FUN_001e04c0((S_1e04c0 *)arg0, (V_1e04c0 *)temp_v0);
        var_a1_3 = arg1->f8;
        var_a1_3 = var_a1_3 ? var_a1_3 : &emptyString[0];
        FUN_001b7920((igCommonTraversal *)arg0, (int)var_a1_3);
    } else {
        var_s0 = igTraversal_TraverseChildren(arg0, (S_1e07a0 *)arg1);
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
    return FUN_001e04c0(self, (V_1e04c0 *)found.p);
}

