int Gap__Gfx__igVertexArray2Helper__vfunc_23(igVertexArray2Helper *arg0, unsigned int *arg1, int arg2) {
    RP array;
    RP record;
    if (arg0->_vertexArray != 0) { return 0; }
    array.p = (RC *)FUN_0014a780(igObject_GetAllocator(arg0));
    {
        RC *a_ = array.p;
        if (a_ != 0) a_->rc = a_->rc + 1;
        REL_15ff10((RC *)arg0->_vertexArray)
        arg0->_vertexArray = (int)a_;
    }
    record.p = 0;
    if (*arg1 & 1) {
        RP list;
        int alloc;
        list.p = (RC *)FUN_0018a060(igObject_GetAllocator(arg0));
        SIZE_LIST((DataList *)list.p, arg2, 12)
        alloc = igObject_GetAllocator(arg0);
        REL_15ff10(record.p)
        record.p = (RC *)FUN_0014b390(alloc);
        ATTACH((StreamRec *)record.p, list.p)
        ((StreamRec *)record.p)->kind = 1;
        ObjectList_AppendRetained(((int *)array.p)[4], record.p);
        REL_15ff10(list.p)
    }
    if (*arg1 & 2) {
        RP list;
        int alloc;
        list.p = (RC *)FUN_0018a060(igObject_GetAllocator(arg0));
        SIZE_LIST((DataList *)list.p, arg2, 12)
        alloc = igObject_GetAllocator(arg0);
        REL_15ff10(record.p)
        record.p = (RC *)FUN_0014b390(alloc);
        ATTACH((StreamRec *)record.p, list.p)
        ((StreamRec *)record.p)->kind = 3;
        ObjectList_AppendRetained(((int *)array.p)[4], record.p);
        REL_15ff10(list.p)
    }
    if (*arg1 & 4) {
        RP list;
        int alloc;
        list.p = (RC *)FUN_00189e40(igObject_GetAllocator(arg0));
        SIZE_LIST((DataList *)list.p, arg2, 4)
        alloc = igObject_GetAllocator(arg0);
        REL_15ff10(record.p)
        record.p = (RC *)FUN_0014b390(alloc);
        ATTACH((StreamRec *)record.p, list.p)
        ((StreamRec *)record.p)->kind = 2;
        ObjectList_AppendRetained(((int *)array.p)[4], record.p);
        REL_15ff10(list.p)
    }
    if ((*arg1 & 0xF0000) >> 16 & 0xFF) {
        unsigned int index;
        for (index = 0; index < ((*arg1 & 0xF0000) >> 16 & 0xFF); index++) {
            RP list;
            int alloc;
            list.p = (RC *)FUN_0018a2d0(igObject_GetAllocator(arg0));
            SIZE_LIST((DataList *)list.p, arg2, 8)
            alloc = igObject_GetAllocator(arg0);
            REL_15ff10(record.p)
            record.p = (RC *)FUN_0014b390(alloc);
            ATTACH((StreamRec *)record.p, list.p)
            ((StreamRec *)record.p)->kind = 4;
            ((StreamRec *)record.p)->index = index;
            ObjectList_AppendRetained(((int *)array.p)[4], record.p);
            REL_15ff10(list.p)
        }
    }
    if ((*arg1 & 0xF0) >> 4 & 0xFF) {
        RP list;
        int alloc;
        int total;
        list.p = (RC *)FUN_002c9740(igObject_GetAllocator(arg0));
        total = arg2 * ((*arg1 & 0xF0) >> 4 & 0xFF);
        SIZE_LIST((DataList *)list.p, total, 4)
        alloc = igObject_GetAllocator(arg0);
        REL_15ff10(record.p)
        record.p = (RC *)FUN_0014b390(alloc);
        ATTACH((StreamRec *)record.p, list.p)
        ((StreamRec *)record.p)->kind = 5;
        ((StreamRec *)record.p)->count = (*arg1 & 0xF0) >> 4 & 0xFF;
        ObjectList_AppendRetained(((int *)array.p)[4], record.p);
        REL_15ff10(list.p)
    }
    if ((*arg1 & 0xF00) >> 8 & 0xFF) {
        RP list;
        int alloc;
        int total;
        list.p = (RC *)FUN_002c99b0(igObject_GetAllocator(arg0));
        total = arg2 * ((*arg1 & 0xF00) >> 8 & 0xFF);
        SIZE_LIST((DataList *)list.p, total, 1)
        alloc = igObject_GetAllocator(arg0);
        REL_15ff10(record.p)
        record.p = (RC *)FUN_0014b390(alloc);
        ATTACH((StreamRec *)record.p, list.p)
        ((StreamRec *)record.p)->kind = 6;
        ((StreamRec *)record.p)->count = (*arg1 & 0xF00) >> 8 & 0xFF;
        ObjectList_AppendRetained(((int *)array.p)[4], record.p);
        REL_15ff10(list.p)
    }
    {
        unsigned int mode = (*arg1 & 0x300000) >> 0x14;
        unsigned char field = mode;
        if (field != 0) {
            int modeInt = field & 0xFF;
            int alloc = igObject_GetAllocator(arg0);
            REL_15ff10(record.p)
            record.p = (RC *)FUN_0014b390(alloc);
            ((StreamRec *)record.p)->kind = 9;
            if (modeInt == 1) {
                RP list;
                list.p = (RC *)FUN_002c9740(igObject_GetAllocator(arg0));
                SIZE_LIST((DataList *)list.p, arg2, 4)
                ATTACH((StreamRec *)record.p, list.p)
                REL_15ff10(list.p)
            } else if (modeInt == 2) {
                RP list;
                list.p = (RC *)FUN_0018a2d0(igObject_GetAllocator(arg0));
                SIZE_LIST((DataList *)list.p, arg2, 8)
                ATTACH((StreamRec *)record.p, list.p)
                REL_15ff10(list.p)
            }
            ObjectList_AppendRetained(((int *)array.p)[4], record.p);
        }
    }
    if (*arg1 & 0x400000) {
        RP list;
        int alloc;
        list.p = (RC *)FUN_0018a060(igObject_GetAllocator(arg0));
        SIZE_LIST((DataList *)list.p, arg2, 12)
        alloc = igObject_GetAllocator(arg0);
        REL_15ff10(record.p)
        record.p = (RC *)FUN_0014b390(alloc);
        ATTACH((StreamRec *)record.p, list.p)
        ((StreamRec *)record.p)->kind = 7;
        ObjectList_AppendRetained(((int *)array.p)[4], record.p);
        REL_15ff10(list.p)
    }
    if (*arg1 & 0x800000) {
        RP list;
        int alloc;
        list.p = (RC *)FUN_0018a060(igObject_GetAllocator(arg0));
        SIZE_LIST((DataList *)list.p, arg2, 12)
        alloc = igObject_GetAllocator(arg0);
        REL_15ff10(record.p)
        record.p = (RC *)FUN_0014b390(alloc);
        ATTACH((StreamRec *)record.p, list.p)
        ((StreamRec *)record.p)->kind = 8;
        ObjectList_AppendRetained(((int *)array.p)[4], record.p);
        REL_15ff10(list.p)
    }
    REL_15ff10(record.p)
    REL_15ff10(array.p)
    return arg2;
}

void Gap__Gfx__igVertexArray2Helper__vfunc_26(igVertexArray2Helper *helper, unsigned int flags) {
    int mode = 0;
    VertexFormatOwner *array;

    if (flags & 1) {
        mode = 2;
    }
    array = (VertexFormatOwner *)helper->_vertexArray;
    if (array == 0) {
        return;
    }
    if (array->format != 0) {
        array->format->primitiveMode = mode;
        return;
    }
    {
        igSmartPointer<VertexArrayFormat> format((VertexArrayFormat *)FUN_0014adc0(igObject_GetAllocator(helper)));
        if (format != 0) {
            format->primitiveMode = mode;
            array = (VertexFormatOwner *)helper->_vertexArray;
            array->setFormat(format);
        }
    }
}

/* Predicate on the bound vertex array: true when its igVertexStream exists and that stream's
 * _accessMode is 2. The enum behind _accessMode is not named in the reflection data, so the value
 * stays a literal. */
int Gap__Gfx__igVertexArray2Helper__vfunc_27(igVertexArray2Helper *self) {
    int result;
    igVertexArray2 *vertexArray;
    igVertexStream *stream;

    vertexArray = (igVertexArray2 *)(self->_vertexArray);
    result = 0;
    if (vertexArray != 0) {
        stream = (igVertexStream *)(vertexArray->_vertexStream);
        if ((stream != 0) && (stream->_accessMode == 2)) {
            result = 1;
        }
    }
    return result;
}

void Gap__Gfx__igVertexArray2Helper__vfunc_28(H *arg0, int arg1, V_15ff10 *arg2) {
    A28 *a = A28::Cast((A28 *)igVertexArray2__FindVertexData((A_15f430 *)arg0->f12, 1, 0)->_data);
    int n = a->f8;
    if (n != 0 && arg1 >= 0 && arg1 < n) {
        V_15ff10 *p = &a->f16[arg1];
        p->x = arg2->x;
        p->y = arg2->y;
        p->z = arg2->z;
    }
}

void Gap__Gfx__igVertexArray2Helper__vfunc_29(igVertexArray2Helper *arg0, int arg1, float *arg2) {
    igVec3fList *var_s0;
    float *temp_v1;

    var_s0 = (igVec3fList *)dw4_cast_or_null((char *)(((igVertexData *)igVertexArray2__FindVertexData((A_15f430 *)arg0->_vertexArray, 1, 0))->_data), g_igVec3fList_metaObject);
    temp_v1 = (float *)(var_s0->_data + (arg1 * 0xC));
    arg2[0] = temp_v1[0];
    arg2[1] = temp_v1[1];
    arg2[2] = temp_v1[2];
}

int Gap__Gfx__igVertexArray2Helper__vfunc_30(struct A30 *arg0, int arg1) {
    struct B_15ff10 *p = (struct B_15ff10 *)igVertexArray2__FindVertexData((A_15f430 *)arg0->d, 1, 0)->_data;
    if (p != 0 && igObject_IsKindOf(p, g_igVec3fList_metaObject[0]) != 0) {
        p = (struct B_15ff10 *)p;
    } else {
        p = 0;
    }
    return p->e + arg1 * 12;
}

void Gap__Gfx__igVertexArray2Helper__vfunc_31(struct H31 *arg0, int arg1, float *arg2) {
    struct M *m = (struct M *)igVertexArray2__FindVertexData((A_15f430 *)arg0->a, 3, 0)->_data;
    int n;
    float *p;
    if (m != 0 && igObject_IsKindOf(m, g_igVec3fList_metaObject[0]) != 0) { m = (struct M*)m; } else { m = 0; }
    n = m->cnt;
    if (n != 0 && arg1 >= 0 && arg1 < n) {
        p = (float *)(m->data + arg1 * 12);
        p[0] = arg2[0];
        p[1] = arg2[1];
        p[2] = arg2[2];
    }
}

void Gap__Gfx__igVertexArray2Helper__vfunc_32(A_15ff10 *arg0, int arg1, V_15ff10 *arg2) {
    V_15ff10 *temp_v1;
    Q_15ff10 *var_s0;
    Q_15ff10 *t;

    t = (Q_15ff10 *)((O_15ff10 *)igVertexArray2__FindVertexData((A_15f430 *)arg0->f12, 3, 0))->f12;
    if ((t != 0) && (igObject_IsKindOf(t, g_igVec3fList_metaObject[0]) != 0)) {
        var_s0 = t;
    } else {
        var_s0 = 0;
    }
    temp_v1 = var_s0->f16 + arg1;
    arg2->x = temp_v1->x;
    arg2->y = temp_v1->y;
    arg2->z = temp_v1->z;
}

int Gap__Gfx__igVertexArray2Helper__vfunc_33(igVertexArray2Helper *arg0, int arg1) {
    void *var_s0;
    void *r;
    var_s0 = (void *)(*(int *)((char *)(igVertexArray2__FindVertexData((A_15f430 *)arg0->_vertexArray, 3, 0)) + 12));
    if ((var_s0 != 0) && (igObject_IsKindOf(var_s0, g_igVec3fList_metaObject[0]) != 0)) {
        r = var_s0;
    } else {
        r = (void *)(0);
    }
    return *(int *)((char *)(r) + 16) + (arg1 * 0xC);
}

void Gap__Gfx__igVertexArray2Helper__vfunc_34(A_15ff10 *arg0, int arg1, V_15ff10 *arg2) {
    Q34 *var_s1;
    Q34 *t;
    int n;
    V_15ff10 *p;

    t = (Q34 *)((O_15ff10 *)igVertexArray2__FindVertexData((A_15f430 *)arg0->f12, 7, 0))->f12;
    if ((t != 0) && (igObject_IsKindOf(t, g_igVec3fList_metaObject[0]) != 0)) {
        var_s1 = t;
    } else {
        var_s1 = 0;
    }
    n = var_s1->f8;
    if ((n != 0) && (arg1 >= 0) && (arg1 < n)) {
        p = var_s1->f16 + arg1;
        p->x = arg2->x;
        p->y = arg2->y;
        p->z = arg2->z;
    }
}

void Gap__Gfx__igVertexArray2Helper__vfunc_35(igVertexArray2Helper *arg0, int arg1, float *arg2) {
    void *temp_v1;
    igVec3fList *var_s0;

    var_s0 = (igVec3fList *)(igVertexArray2__FindVertexData((A_15f430 *)arg0->_vertexArray, 7, 0)->_data);
    if ((var_s0 != 0) && (igObject_IsKindOf(var_s0, g_igVec3fList_metaObject[0]) != 0)) {
        var_s0 = (igVec3fList *)var_s0;

    } else {
        var_s0 = (igVec3fList *)(0);
    }
    temp_v1 = (void *)(var_s0->_data + (arg1 * 0xC));
    arg2[0] = ((float *)temp_v1)[0];
    arg2[1] = ((float *)temp_v1)[1];
    arg2[2] = ((float *)temp_v1)[2];
}

V_15ff10 *Gap__Gfx__igVertexArray2Helper__vfunc_36(A_15ff10 *arg0, int arg1) {
    Q_15ff10 *var_s0;
    Q_15ff10 *t;

    t = (Q_15ff10 *)((O_15ff10 *)igVertexArray2__FindVertexData((A_15f430 *)arg0->f12, 7, 0))->f12;
    if ((t != 0) && (igObject_IsKindOf(t, g_igVec3fList_metaObject[0]) != 0)) {
        var_s0 = t;
    } else {
        var_s0 = 0;
    }
    return var_s0->f16 + arg1;
}

void Gap__Gfx__igVertexArray2Helper__vfunc_37(igVertexArray2Helper *arg0, int arg1, void *arg2) {
    int temp_v1;
    void *temp_v1_2;
    igVec3fList *var_s1;

    var_s1 = (igVec3fList *)dw4_cast_or_null((char *)(((igVertexData *)igVertexArray2__FindVertexData((A_15f430 *)arg0->_vertexArray, 8, 0))->_data), g_igVec3fList_metaObject);
    temp_v1 = var_s1->_count;
    if ((temp_v1 != 0) && (arg1 >= 0) && (arg1 < temp_v1)) {
        temp_v1_2 = (void *)(var_s1->_data + (arg1 * 0xC));
        *(float *)((char *)(temp_v1_2) + 0) = (float) *(float *)((char *)(arg2) + 0);
        *(float *)((char *)(temp_v1_2) + 4) = (float) *(float *)((char *)(arg2) + 4);
        *(float *)((char *)(temp_v1_2) + 8) = (float) *(float *)((char *)(arg2) + 8);
    }
}

/* The cast-or-null result is kept in a separate variable (t = s0 / t = 0): the then arm survives
 * as a jump and the join load is copied into its delay slot. */
void Gap__Gfx__igVertexArray2Helper__vfunc_38(igVertexArray2Helper *arg0, int arg1, void *arg2) {
    void *temp_v1;
    void *var_s0;
    igVec3fList *t;

    var_s0 = (void *)(*(int *)((char *)(igVertexArray2__FindVertexData((A_15f430 *)arg0->_vertexArray, 8, 0)) + 12));
    if ((var_s0 != 0) && (igObject_IsKindOf(var_s0, g_igVec3fList_metaObject[0]) != 0)) {
        t = (igVec3fList *)var_s0;
    } else {
        t = (igVec3fList *)(0);
    }
    temp_v1 = (void *)(t->_data + (arg1 * 0xC));
    *(float *)((char *)(arg2) + 0) = (float) *(float *)((char *)(temp_v1) + 0);
    *(float *)((char *)(arg2) + 4) = (float) *(float *)((char *)(temp_v1) + 4);
    *(float *)((char *)(arg2) + 8) = (float) *(float *)((char *)(temp_v1) + 8);
}

V_15ff10 *Gap__Gfx__igVertexArray2Helper__vfunc_39(A_15ff10 *arg0, int arg1) {
    Q_15ff10 *var_s0;
    Q_15ff10 *t;

    t = (Q_15ff10 *)((O_15ff10 *)igVertexArray2__FindVertexData((A_15f430 *)arg0->f12, 8, 0))->f12;
    if ((t != 0) && (igObject_IsKindOf(t, g_igVec3fList_metaObject[0]) != 0)) {
        var_s0 = t;
    } else {
        var_s0 = 0;
    }
    return var_s0->f16 + arg1;
}

void Gap__Gfx__igVertexArray2Helper__vfunc_40(igVertexArray2Helper *arg0, int arg1, U_15ff10 arg2) {
    int temp_s1;
    S_15ff10 *temp_v0;
    int temp_s1_2;
    temp_v0 = (S_15ff10 *)(igVertexArray2__FindVertexData((A_15f430 *)arg0->_vertexArray, 2, 0));
    temp_s1 = g_igUnsignedIntList_metaObject[0];
    if (temp_s1 == temp_v0->f12->vX()) {
        T_15ff10 *a = temp_v0->f12;
        int v1 = a->f8;
        if (v1 != 0 && arg1 >= 0 && arg1 < v1) {
            a->f16[arg1] = arg2.i;
        }
    } else {
        temp_s1_2 = g_igVec4ucList_metaObject[0];
        if (temp_s1_2 == temp_v0->f12->vX()) {
            T_15ff10 *a = temp_v0->f12;
            int v1 = a->f8;
            if (v1 != 0 && arg1 >= 0 && arg1 < v1) {
                unsigned char *d = (unsigned char *)(a->f16 + arg1);
                d[0] = arg2.b.b[0];
                d[1] = arg2.b.b[1];
                d[2] = arg2.b.b[2];
                d[3] = arg2.b.b[3];
            }
        }
    }
}

void Gap__Gfx__igVertexArray2Helper__vfunc_41(igVertexArray2Helper *arg0, int arg1, int arg2) {
    int temp_s1;
    S_15ff10 *temp_v0;
    int temp_s1_2;
    U_15ff10 sp5C;
    temp_v0 = (S_15ff10 *)(igVertexArray2__FindVertexData((A_15f430 *)arg0->_vertexArray, 2, 0));
    temp_s1 = g_igUnsignedIntList_metaObject[0];
    if (temp_s1 == temp_v0->f12->vX()) {
        T_15ff10 *a = temp_v0->f12;
        int r = FUN_001931b0((float *)arg2, 1);
        int v1 = a->f8;
        if (v1 != 0 && arg1 >= 0 && arg1 < v1) {
            a->f16[arg1] = r;
        }
    } else {
        temp_s1_2 = g_igVec4ucList_metaObject[0];
        if (temp_s1_2 == temp_v0->f12->vX()) {
            T_15ff10 *a = temp_v0->f12;
            sp5C.i = FUN_001931b0((float *)arg2, 1);
            int v1 = a->f8;
            if (v1 != 0 && arg1 >= 0 && arg1 < v1) {
                unsigned char *d = (unsigned char *)(a->f16 + arg1);
                d[0] = sp5C.b.b[0];
                d[1] = sp5C.b.b[1];
                d[2] = sp5C.b.b[2];
                d[3] = sp5C.b.b[3];
            }
        }
    }
}

int Gap__Gfx__igVertexArray2Helper__vfunc_42(A_15ff10 *arg0, int arg1) {
    int temp_s0;
    Y_15ff10 *temp_a0;
    Y_15ff10 *temp_a0_2;
    X_15ff10 *temp_v0;
    int temp_s0_2;

    temp_v0 = (X_15ff10 *)igVertexArray2__FindVertexData((A_15f430 *)arg0->f12, 2, 0);
    temp_a0 = temp_v0->f12;
    temp_s0 = g_igUnsignedIntList_metaObject[0];
    if (temp_s0 == temp_a0->vX()) {
        return temp_v0->f12->f16[arg1];
    }
    temp_a0_2 = temp_v0->f12;
    temp_s0_2 = g_igVec4ucList_metaObject[0];
    if (temp_s0_2 == temp_a0_2->vX()) {
        return temp_v0->f12->f16[arg1];
    }
    return 0;
}

void Gap__Gfx__igVertexArray2Helper__vfunc_43(igVertexArray2Helper *arg0, int arg1, int arg2) {
    int temp_s1;
    S43 *temp_v0;
    int temp_s1_2;

    temp_v0 = (S43 *)(igVertexArray2__FindVertexData((A_15f430 *)arg0->_vertexArray, 2, 0));
    temp_s1 = g_igUnsignedIntList_metaObject[0];
    if (temp_s1 == ((DW4VC_88_0 *)(temp_v0->f12))->vX()) {
        Color4f_Unpack(arg2, 1, temp_v0->f12->f16[arg1]);
        return;
    }
    temp_s1_2 = g_igVec4ucList_metaObject[0];
    if (temp_s1_2 == ((DW4VC_88_0 *)(temp_v0->f12))->vX()) {
        Color4f_Unpack(arg2, 1, temp_v0->f12->f16[arg1]);
    }
}

void Gap__Gfx__igVertexArray2Helper__vfunc_44(igVertexArray2Helper *arg0, int arg1, int arg2, float arg3) {
    S44 *v;
    int s3;
    T44 *c;
    v = (S44 *)(igVertexArray2__FindVertexData((A_15f430 *)arg0->_vertexArray, 5, 0));
    s3 = g_igFloatList_metaObject[0];
    if (s3 == v->f12->vX()) {
        int idx;
        c = v->f12;
        idx = arg1 + arg2 * v->f24;
        if (c->f8 != 0 && idx >= 0 && idx < c->f8) {
            c->f16[idx] = arg3;
        }
    } else {
    s3 = g_igVec2fList_metaObject[0];
    if (s3 == v->f12->vX()) {
        c = v->f12;
        V2_15ff10 *q = (V2_15ff10 *)c->f16 + arg2;
        V2_15ff10 t(*q);
        t[arg1] = arg3;
        if (c->f8 != 0 && arg2 >= 0 && arg2 < c->f8) {
            *q = t;
        }
    } else {
    s3 = g_igVec3fList_metaObject[0];
    if (s3 == v->f12->vX()) {
        c = v->f12;
        V3 *q = (V3 *)c->f16 + arg2;
        V3 t(*q);
        t[arg1] = arg3;
        if (c->f8 != 0 && arg2 >= 0 && arg2 < c->f8) {
            *q = t;
        }
    } else {
    s3 = DAT_005610a8[0];
    if (s3 == v->f12->vX()) {
        c = v->f12;
        V4 *q = (V4 *)c->f16 + arg2;
        V4 t(*q);
        t[arg1] = arg3;
        if (c->f8 != 0 && arg2 >= 0 && arg2 < c->f8) {
            *q = t;
        }
    }
    }
    }
    }
}

float Gap__Gfx__igVertexArray2Helper__vfunc_45(igVertexArray2Helper *arg0, int arg1, int arg2) {
    S44 *v;
    int s3;
    float sp2[2];
    float sp3[3];
    float sp4[4];
    float *p;
    int idx;
    v = (S44 *)(igVertexArray2__FindVertexData((A_15f430 *)arg0->_vertexArray, 5, 0));
    s3 = g_igFloatList_metaObject[0];
    if (s3 == v->f12->vX()) {
        idx = arg1 + arg2 * v->f24;
        return *(float *)((char *)v->f12->f16 + idx * 4);
    }
    s3 = g_igVec2fList_metaObject[0];
    if (s3 == v->f12->vX()) {
        p = v->f12->f16 + arg2 * 2;
        sp2[0] = p[0];
        sp2[1] = p[1];
        return sp2[arg1];
    }
    s3 = g_igVec3fList_metaObject[0];
    if (s3 == v->f12->vX()) {
        p = v->f12->f16 + arg2 * 3;
        sp3[0] = p[0];
        sp3[1] = p[1];
        sp3[2] = p[2];
        return sp3[arg1];
    }
    s3 = DAT_005610a8[0];
    if (s3 == v->f12->vX()) {
        p = v->f12->f16 + arg2 * 4;
        sp4[0] = p[0];
        sp4[1] = p[1];
        sp4[2] = p[2];
        sp4[3] = p[3];
        return sp4[arg1];
    }
    return 0.0f;
}

/* matching construct: a small sweep of spellings */
void Gap__Gfx__igVertexArray2Helper__vfunc_46(igVertexArray2Helper *helper, int component, int index, unsigned char value) {
    VertexData *v;
    int meta;
    ByteList *l;
    v = (VertexData *)igVertexArray2__FindVertexData((A_15f430 *)helper->_vertexArray, 6, 0);
    meta = g_igUnsignedCharList_metaObject[0];
    if (meta == v->list->getMeta()) {
        int i;
        l = v->list;
        i = component + index * v->stride;
        if (l->_count != 0 && i >= 0 && i < l->_count) {
            ((unsigned char *)l->_data)[i] = value;
        }
    } else {
        meta = DAT_005610b0[0];
        if (meta == v->list->getMeta()) {
            l = v->list;
            Byte3 *q = (Byte3 *)l->_data + index;
            Byte3 t(*q);
            t[component] = value;
            if (l->_count != 0 && index >= 0 && index < l->_count) {
                *q = t;
            }
        } else {
            meta = g_igVec4ucList_metaObject[0];
            if (meta == v->list->getMeta()) {
                l = v->list;
                Byte4 *q = (Byte4 *)l->_data + index;
                Byte4 t(*q);
                t[component] = value;
                if (l->_count != 0 && index >= 0 && index < l->_count) {
                    *q = t;
                }
            }
        }
    }
}

unsigned char Gap__Gfx__igVertexArray2Helper__vfunc_47(igVertexArray2Helper *arg0, int arg1, int arg2) {
    S47 *v;
    int s3;
    unsigned char sp3[3];
    unsigned char sp4[4];
    unsigned char *p;
    int idx;
    T47 *t;
    v = (S47 *)(igVertexArray2__FindVertexData((A_15f430 *)arg0->_vertexArray, 6, 0));
    s3 = g_igUnsignedCharList_metaObject[0];
    if (s3 == v->f12->vX()) {
        idx = arg1 + arg2 * v->f24;
        return v->f12->f16[idx];
    }
    s3 = DAT_005610b0[0];
    if (s3 == v->f12->vX()) {
        p = v->f12->f16 + arg2 * 3;
        sp3[0] = p[0];
        sp3[1] = p[1];
        sp3[2] = p[2];
        return sp3[arg1];
    }
    s3 = g_igVec4ucList_metaObject[0];
    if (s3 == v->f12->vX()) {
        p = v->f12->f16 + arg2 * 4;
        sp4[0] = p[0];
        sp4[1] = p[1];
        sp4[2] = p[2];
        sp4[3] = p[3];
        return sp4[arg1];
    }
    return 0;
}

void Gap__Gfx__igVertexArray2Helper__vfunc_48(igVertexArray2Helper *arg0, int arg1, int arg2, void *arg3) {
    int temp_v1;
    void *temp_v1_2;
    void *var_s0;
    igVec2fList *p;

    var_s0 = (void *)(*(int *)((char *)(igVertexArray2__FindVertexData((A_15f430 *)arg0->_vertexArray, 4, arg1)) + 12));
    if ((var_s0 != 0) && (igObject_IsKindOf(var_s0, g_igVec2fList_metaObject[0]) != 0)) {
        p = (igVec2fList *)var_s0;
    } else {
        p = (igVec2fList *)(0);
    }
    temp_v1 = p->_count;
    if ((temp_v1 != 0) && (arg2 >= 0) && (arg2 < temp_v1)) {
        temp_v1_2 = (void *)(p->_data + (arg2 * 8));
        *(float *)((char *)(temp_v1_2) + 0) = (float) *(float *)((char *)(arg3) + 0);
        *(float *)((char *)(temp_v1_2) + 4) = (float) *(float *)((char *)(arg3) + 4);
    }
}

void Gap__Gfx__igVertexArray2Helper__vfunc_49(igVertexArray2Helper *arg0, int arg1, int arg2, float *arg3) {
    float *temp_v1;
    igVec2fList *var_s0;
    igVec2fList *r;

    var_s0 = (igVec2fList *)(igVertexArray2__FindVertexData((A_15f430 *)arg0->_vertexArray, 4, arg1)->_data);
    if ((var_s0 != 0) && (igObject_IsKindOf(var_s0, g_igVec2fList_metaObject[0]) != 0)) {

        r = var_s0;
    } else {
        r = (igVec2fList *)(0);
    }
    temp_v1 = (float *)(r->_data + (arg2 * 8));
    arg3[0] = temp_v1[0];
    arg3[1] = temp_v1[1];
}

int Gap__Gfx__igVertexArray2Helper__vfunc_50(igVertexArray2Helper *arg0, int arg1, int arg2) {
    char *var_s0; char *p;
    var_s0 = (char *)(*(int *)((char *)(igVertexArray2__FindVertexData((A_15f430 *)arg0->_vertexArray, 4, arg1)) + 12));
    if ((var_s0 != 0) && (igObject_IsKindOf(var_s0, g_igVec2fList_metaObject[0]) != 0)) {
        p = var_s0;
    } else {
        p = 0;
    }
    return *(int *)(p + 16) + (arg2 * 8);
}

void Gap__Gfx__igVertexArray2Helper__vfunc_51(A_15ff10 *arg0, int arg1, float fparg0) {
    Q51 *var_s0;
    Q51 *t;

    t = (Q51 *)((O_15ff10 *)igVertexArray2__FindVertexData((A_15f430 *)arg0->f12, 9, 0))->f12;
    if ((t != 0) && (igObject_IsKindOf(t, g_igFloatList_metaObject[0]) != 0)) {
        var_s0 = t;
    } else {
        var_s0 = 0;
    }
    { int n = *(int *)((char *)var_s0 + 8); if (n != 0 && arg1 >= 0 && arg1 < n) { var_s0->f16[arg1] = fparg0; } }
}

float Gap__Gfx__igVertexArray2Helper__vfunc_52(A_15ff10 *arg0, int arg1) {
    Q51 *var_s0;
    Q51 *t;

    t = (Q51 *)((O_15ff10 *)igVertexArray2__FindVertexData((A_15f430 *)arg0->f12, 9, 0))->f12;
    if ((t != 0) && (igObject_IsKindOf(t, g_igFloatList_metaObject[0]) != 0)) {
        var_s0 = t;
    } else {
        var_s0 = 0;
    }
    return var_s0->f16[arg1];
}

void Gap__Gfx__igVertexArray2Helper__vfunc_53(H *arg0, int arg1, V53 *arg2) {
    A53 *a = A53::Cast((A53 *)igVertexArray2__FindVertexData((A_15f430 *)arg0->f12, 9, 0)->_data);
    int n = a->f8;
    if (n != 0 && arg1 >= 0 && arg1 < n) {
        V53 *p = &a->f16[arg1];
        p->x = arg2->x;
        p->y = arg2->y;
    }
}

void Gap__Gfx__igVertexArray2Helper__vfunc_54(igVertexArray2Helper *arg0, int arg1, void *arg2) {
    igVec2fList *var_s0;
    char *temp_v1;

    var_s0 = (igVec2fList *)dw4_cast_or_null((char *)(((igVertexData *)igVertexArray2__FindVertexData((A_15f430 *)arg0->_vertexArray, 9, 0))->_data), g_igVec2fList_metaObject);
    temp_v1 = (char *)(var_s0->_data + (arg1 * 8));
    *(float *)((char *)(arg2) + 0) = *(float *)(temp_v1 + 0);
    *(float *)((char *)(arg2) + 4) = *(float *)(temp_v1 + 4);
}

/* Looks up the bound vertex array's stream with component type 5, index 0
 * (igVertexArray2__FindVertexData) and passes it to FUN_00162b50, which switches on the class of
 * the stream's data list and leaves its component count in v0. The declared return type is void. */

void Gap__Gfx__igVertexArray2Helper__vfunc_24(igVertexArray2Helper *self) {
    FUN_00162b50((A162b50 *)igVertexArray2__FindVertexData((A_15f430 *)self->_vertexArray, 5, 0));
}

/* Same as slot 24 for the stream with component type 6, index 0: looks it up with
 * igVertexArray2__FindVertexData and passes it to FUN_00162ca0 (same shape as FUN_00162b50 with
 * fewer data-list classes), whose component count is left in v0. The declared return type is void. */

void Gap__Gfx__igVertexArray2Helper__vfunc_25(igVertexArray2Helper *self) {
    FUN_00162ca0(igVertexArray2__FindVertexData((A_15f430 *)self->_vertexArray, 6, 0));
}

void Gap__Gfx__igVertexArray2Helper__vfunc_56(void **arg0, int arg1, void **arg2, int arg3, int *arg4) {
    int sp88[2];
    unsigned int c1;
    unsigned int c2;
    unsigned int c3;
    unsigned int c4;
    unsigned int i;

    if (*arg4 & 1) {
        ((D112 *)arg0)->vY(arg1, ((S124 *)arg2)->vX(arg3));
    }
    if (*arg4 & 2) {
        ((D124 *)arg0)->vY(arg1, ((S136 *)arg2)->vX(arg3));
    }
    if (*arg4 & 0x400000) {
        ((D136 *)arg0)->vY(arg1, ((S148 *)arg2)->vX(arg3));
    }
    if (*arg4 & 0x800000) {
        ((D148 *)arg0)->vY(arg1, ((S160 *)arg2)->vX(arg3));
    }
    if (*arg4 & 4) {
        ((D160 *)arg0)->vY(arg1, ((S172 *)arg2)->vX(arg3));
    }
    c1 = ((unsigned int)(*arg4 & 0xF0) >> 4) & 0xFF;
    if (c1 != 0) {
        for (i = 0; i < (c1 & 0xFF); i++) {
            ((D176 *)arg0)->vY(i, arg1, ((S184 *)arg2)->vX(i, arg3));
        }
    }
    c2 = ((unsigned int)(*arg4 & 0xF00) >> 8) & 0xFF;
    if (c2 != 0) {
        for (i = 0; i < (c2 & 0xFF); i++) {
            ((D184 *)arg0)->vY(i, arg1, (((S196 *)arg2)->vX(i, arg3) & 0xFF));
        }
    }
    c3 = ((unsigned int)(*arg4 & 0x300000) >> 0x14) & 0xFF;
    if (c3 != 0) {
        if ((c3 & 0xFF) == 1) {
            ((D204 *)arg0)->vY(arg1, ((S216 *)arg2)->vX(arg3));
        } else if ((c3 & 0xFF) == 2) {
            ((S224 *)arg2)->vX(arg3, sp88);
            ((D212 *)arg0)->vY(arg1, sp88);
        }
    }
    c4 = ((unsigned int)(*arg4 & 0xF0000) >> 0x10) & 0xFF;
    if (c4 != 0) {
        for (i = 0; i < (c4 & 0xFF); i++) {
            ((D192 *)arg0)->vY(i, arg1, ((S208 *)arg2)->vX(i, arg3));
        }
    }
}

int Gap__Gfx__igVertexArray2Helper__vfunc_57(void) {
    return 0;
}

void Gap__Gfx__igVertexArray2Helper__vfunc_58(H58 *arg0, unsigned int *arg1) {
    igVertexData *s3, *s2, *s1, *s6, *s7, *s8, *spAC, *s0;
    void *x;
    void *y;
    unsigned int v;
    int n;
    unsigned char sel;
    s3 = (igVertexData *)igVertexArray2__FindVertexData((A_15f430 *)arg0->f12, 1, 0);
    s2 = (igVertexData *)igVertexArray2__FindVertexData((A_15f430 *)arg0->f12, 3, 0);
    s1 = (igVertexData *)igVertexArray2__FindVertexData((A_15f430 *)arg0->f12, 2, 0);
    s6 = (igVertexData *)igVertexArray2__FindVertexData((A_15f430 *)arg0->f12, 5, 0);
    s7 = (igVertexData *)igVertexArray2__FindVertexData((A_15f430 *)arg0->f12, 6, 0);
    s8 = (igVertexData *)igVertexArray2__FindVertexData((A_15f430 *)arg0->f12, 8, 0);
    spAC = (igVertexData *)igVertexArray2__FindVertexData((A_15f430 *)arg0->f12, 7, 0);
    s0 = (igVertexData *)igVertexArray2__FindVertexData((A_15f430 *)arg0->f12, 9, 0);
    if (s3 != 0) {
        *arg1 |= 1;
    }
    if (s2 != 0) {
        *arg1 |= 2;
    }
    if (s1 != 0) {
        *arg1 |= 4;
    }
    if (s6 != 0) {
        v = arg0->v96() & 0xFF;
        *arg1 &= ~0xF0;
        *arg1 |= v << 4;
    }
    if (s7 != 0) {
        v = arg0->v100() & 0xFF;
        *arg1 &= ~0xF00;
        *arg1 |= v << 8;
    }
    if (s8 != 0) {
        *arg1 |= 0x800000;
    }
    if (spAC != 0) {
        *arg1 |= 0x400000;
    }
    if (s0 != 0) {
        x = (void *)s0->_data;
        if (x != 0 && igObject_IsKindOf(x, g_igFloatList_metaObject[0]) != 0) {
            y = x;
        } else {
            y = 0;
        }
        if (((y != 0) ? 1 : 2) & 0xFF) {
            *arg1 &= 0xFFCFFFFF;
            *arg1 = *arg1 | ((((y != 0) ? 1 : 2) & 0xFF) << 0x14);
        } else {
            *arg1 = *arg1 & 0xFFCFFFFF;
        }
    }
    n = 0;
    while (igVertexArray2__FindVertexData((A_15f430 *)arg0->f12, 4, n) != 0) {
        n += 1;
    }
    *arg1 &= 0xFFF0FFFF;
    *arg1 |= (n & 0xFF) << 0x10;
}

int FUN_00162b50(A162b50 *arg0) {
    if (g_igFloatList_metaObject[0] == arg0->f12->v88() || g_igCharList_metaObject[0] == arg0->f12->v88() || g_igUnsignedCharList_metaObject[0] == arg0->f12->v88() || g_igShortList_metaObject[0] == arg0->f12->v88() || g_igUnsignedShortList_metaObject[0] == arg0->f12->v88()) {
        return arg0->f24;
    }
    if (g_igVec2fList_metaObject[0] == arg0->f12->v88()) {
        return 2;
    }
    if (g_igVec3fList_metaObject[0] == arg0->f12->v88()) {
        return 3;
    }
    if (DAT_005610a8[0] == arg0->f12->v88()) {
        return 4;
    }
    return 0;
}

int FUN_00162ca0(void *a0) {
    O162ca0 *arg0 = (O162ca0 *)a0;
    if (g_igUnsignedCharList_metaObject[0] == arg0->obj->vX()) {
        return arg0->f18;
    }
    if (DAT_005610b0[0] == arg0->obj->vX()) {
        return 3;
    }
    if (g_igVec4ucList_metaObject[0] == arg0->obj->vX()) {
        return 4;
    }
    return 0;
}

void Gap__Gfx__igVertexArray2Helper__vfunc_59(igVertexArray2Helper *self, int type, float *out, int index) {
    VData *vd;
    FloatList *list;
    FloatList *scalars;
    FloatList *pairs;
    FloatList *triples;
    FloatList *quads;
    int i;
    int n;
    /* matching construct: hand sweep — function-scope x, y, z here and block-local accumulators in
     * the pair (case 4) and quad blocks set the float register order */
    float x, y, z;

    vd = (VData *)igVertexArray2__FindVertexData((A_15f430 *)self->_vertexArray, type, index);
    *out = 1e23f;
    list = vd->list;
    if ((list != 0) && (igObject_IsKindOf(list, g_igFloatList_metaObject[0]) != 0)) { scalars = list; } else { scalars = 0; }
    list = vd->list;
    if ((list != 0) && (igObject_IsKindOf(list, g_igVec2fList_metaObject[0]) != 0)) { pairs = list; } else { pairs = 0; }
    list = vd->list;
    if ((list != 0) && (igObject_IsKindOf(list, g_igVec3fList_metaObject[0]) != 0)) { triples = list; } else { triples = 0; }
    list = vd->list;
    if ((list != 0) && (igObject_IsKindOf(list, DAT_005610a8[0]) != 0)) { quads = list; } else { quads = 0; }
    switch (type) {
    case 1:
    case 3:
    case 7:
    case 8:
        if (triples != 0) {
            x = 1e23f; y = 1e23f; z = 1e23f;
            n = vd->list->count;
            for (i = 0; i < n; i++) {
                float *p = triples->data + i * 3;
                if (x > p[0]) x = p[0];
                if (y > p[1]) y = p[1];
                if (z > p[2]) z = p[2];
            }
            *out = (x < y) ? x : y;
            *out = (*out < z) ? *out : z;
        }
        break;
    case 4:
        if (pairs != 0) {
            float x = 1e23f, y = 1e23f;
            n = vd->list->count;
            for (i = 0; i < n; i++) {
                float *p = pairs->data + i * 2;
                if (x > p[0]) x = p[0];
                if (y > p[1]) y = p[1];
            }
            *out = (x < y) ? x : y;
        }
        break;
    case 5:
    case 9:
        if (scalars != 0) {
            float m = 1e23f;
            n = vd->list->count;
            for (i = 0; i < n; i++) {
                m = (m < scalars->data[i]) ? m : scalars->data[i];
            }
            *out = m;
        } else if (pairs != 0) {
            x = 1e23f; y = 1e23f;
            n = vd->list->count;
            for (i = 0; i < n; i++) {
                float *p = pairs->data + i * 2;
                if (x > p[0]) x = p[0];
                if (y > p[1]) y = p[1];
            }
            *out = (x < y) ? x : y;
        } else if (triples != 0) {
            x = 1e23f; y = 1e23f; z = 1e23f;
            n = vd->list->count;
            for (i = 0; i < n; i++) {
                float *p = triples->data + i * 3;
                if (x > p[0]) x = p[0];
                if (y > p[1]) y = p[1];
                if (z > p[2]) z = p[2];
            }
            *out = (x < y) ? x : y;
            *out = (*out < z) ? *out : z;
        } else if (quads != 0) {
            float x = 1e23f, y = 1e23f, z = 1e23f, w = 1e23f;
            n = vd->list->count;
            for (i = 0; i < n; i++) {
                float *p = quads->data + i * 4;
                if (x > p[0]) x = p[0];
                if (y > p[1]) y = p[1];
                if (z > p[2]) z = p[2];
                if (w > p[3]) w = p[3];
            }
            *out = (x < y) ? x : y;
            *out = (*out < z) ? *out : z;
            *out = (*out < w) ? *out : w;
        }
        break;
    }
}

void Gap__Gfx__igVertexArray2Helper__vfunc_60(igVertexArray2Helper *self, int type, float *out, int index) {
    VData *vd;
    FloatList *list;
    FloatList *scalars;
    FloatList *pairs;
    FloatList *triples;
    FloatList *quads;
    int i;
    int n;
    /* matching construct: hand sweep — function-scope x, y, z here and block-local accumulators in
     * the pair (case 4) and quad blocks set the float register order */
    float x, y, z;

    vd = (VData *)igVertexArray2__FindVertexData((A_15f430 *)self->_vertexArray, type, index);
    *out = -1e23f;
    list = vd->list;
    if ((list != 0) && (igObject_IsKindOf(list, g_igFloatList_metaObject[0]) != 0)) { scalars = list; } else { scalars = 0; }
    list = vd->list;
    if ((list != 0) && (igObject_IsKindOf(list, g_igVec2fList_metaObject[0]) != 0)) { pairs = list; } else { pairs = 0; }
    list = vd->list;
    if ((list != 0) && (igObject_IsKindOf(list, g_igVec3fList_metaObject[0]) != 0)) { triples = list; } else { triples = 0; }
    list = vd->list;
    if ((list != 0) && (igObject_IsKindOf(list, DAT_005610a8[0]) != 0)) { quads = list; } else { quads = 0; }
    switch (type) {
    case 1:
    case 3:
    case 7:
    case 8:
        if (triples != 0) {
            x = -1e23f; y = -1e23f; z = -1e23f;
            n = vd->list->count;
            for (i = 0; i < n; i++) {
                float *p = triples->data + i * 3;
                if (x < p[0]) x = p[0];
                if (y < p[1]) y = p[1];
                if (z < p[2]) z = p[2];
            }
            *out = (x > y) ? x : y;
            *out = (*out > z) ? *out : z;
        }
        break;
    case 4:
        if (pairs != 0) {
            float x = -1e23f, y = -1e23f;
            n = vd->list->count;
            for (i = 0; i < n; i++) {
                float *p = pairs->data + i * 2;
                if (x < p[0]) x = p[0];
                if (y < p[1]) y = p[1];
            }
            *out = (x > y) ? x : y;
        }
        break;
    case 5:
    case 9:
        if (scalars != 0) {
            float m = -1e23f;
            n = vd->list->count;
            for (i = 0; i < n; i++) {
                m = (m > scalars->data[i]) ? m : scalars->data[i];
            }
            *out = m;
        } else if (pairs != 0) {
            x = -1e23f; y = -1e23f;
            n = vd->list->count;
            for (i = 0; i < n; i++) {
                float *p = pairs->data + i * 2;
                if (x < p[0]) x = p[0];
                if (y < p[1]) y = p[1];
            }
            *out = (x > y) ? x : y;
        } else if (triples != 0) {
            x = -1e23f; y = -1e23f; z = -1e23f;
            n = vd->list->count;
            for (i = 0; i < n; i++) {
                float *p = triples->data + i * 3;
                if (x < p[0]) x = p[0];
                if (y < p[1]) y = p[1];
                if (z < p[2]) z = p[2];
            }
            *out = (x > y) ? x : y;
            *out = (*out > z) ? *out : z;
        } else if (quads != 0) {
            float x = -1e23f, y = -1e23f, z = -1e23f, w = -1e23f;
            n = vd->list->count;
            for (i = 0; i < n; i++) {
                float *p = quads->data + i * 4;
                if (x < p[0]) x = p[0];
                if (y < p[1]) y = p[1];
                if (z < p[2]) z = p[2];
                if (w < p[3]) w = p[3];
            }
            *out = (x > y) ? x : y;
            *out = (*out > z) ? *out : z;
            *out = (*out > w) ? *out : w;
        }
        break;
    }
}

/* Union read-back through the stack; the exponent bias is subtracted after the join, not inside
 * the condition. */
int FUN_00163770(unsigned int arg0, float fparg0) {
    union { float f; unsigned u; struct { unsigned frac:23; } b; } x;
    int e, v;
    unsigned int s, t, r, m;
    int iv;
    x.f = fparg0;
    e = (x.u >> 23) & 0xFF;
    m = x.b.frac;
    if (m != 0 || e != 0) {
        m |= 0x800000;
    }
    v = e - 0x7F;
    s = 0x17;
    if (v != 0) {
        s -= v;
    } else {
        s += v;
    }
    t = m & ((1 << s) - 1);
    iv = (int)x.f;
    if (arg0 < s) {
        r = t >> (s - arg0);
    } else {
        r = t << (arg0 - s);
    }
    return r | (iv << arg0);
}

float FUN_00163800(int arg0, int arg1) {
    return (float) (arg0 >> arg1);
}

ObjectRefWord *FUN_00164870(ObjectRefWord *self,int delete_storage) {
    if(self) {
        ObjectRefTarget *object=self->value;
        if(object) {
            --object->references;
            if(((unsigned long long)(long long)object->references & 0x7fffffULL)==0)
                igObject_Destroy(object);
        }
        if((short)delete_storage>0) FUN_00100610(self);
    }
    return self;
}

struct R **FUN_001648f0(struct R **arg0, short arg1) {
    struct R *temp_a0;

    if (arg0 != 0) {
        temp_a0 = *arg0;
        if (temp_a0 != 0) {
            temp_a0->rc = temp_a0->rc - 1;
            if ((temp_a0->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
        if (arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

void **FUN_00164970(void **arg0, long long arg1) {
    char *o;

    if (arg0 != 0) {
        o = (char *)*arg0;
        if (o != 0) {
            *(int *)(o + 4) = *(int *)(o + 4) - 1;
            if ((*(int *)(o + 4) & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if ((short)arg1 > 0) {
            FUN_00100610(arg0);
        }
    }
    return arg0;
}

int *FUN_001649f0(void) {
    if (DAT_00554b20 == 0) {
        DAT_00554b20 = 1;
        DAT_00560670[0] = g_igVec3fList_metaObject[0];
        DAT_00560674[0] = g_igCharList_metaObject[0];
        DAT_00560678[0] = g_igUnsignedCharList_metaObject[0];
        DAT_0056067c[0] = g_igShortList_metaObject[0];
        DAT_00560680[0] = g_igUnsignedShortList_metaObject[0];
    }
    return &DAT_00560670[0];
}

int *FUN_00164a60(void) {
    if (DAT_00554b24 == 0) {
        DAT_00554b24 = 1;
        DAT_00560688[0] = g_igUnsignedIntList_metaObject[0];
        DAT_0056068c[0] = g_igVec4ucList_metaObject[0];
    }
    return &DAT_00560688[0];
}

int *FUN_00164aa0(void) {
    if (DAT_00554b28 == 0) {
        DAT_00554b28 = 1;
        DAT_005606a0[0] = g_igVec3fList_metaObject[0];
        DAT_005606a4[0] = g_igCharList_metaObject[0];
        DAT_005606a8[0] = g_igUnsignedCharList_metaObject[0];
        DAT_005606ac[0] = g_igShortList_metaObject[0];
        DAT_005606b0[0] = g_igUnsignedShortList_metaObject[0];
    }
    return &DAT_005606a0[0];
}

int *FUN_00164b10(void) {
    if (DAT_00554b2c == 0) {
        DAT_00554b2c = 1;
        DAT_005606c0[0] = g_igVec2fList_metaObject[0];
        DAT_005606c4[0] = g_igCharList_metaObject[0];
        DAT_005606c8[0] = g_igUnsignedCharList_metaObject[0];
        DAT_005606cc[0] = g_igShortList_metaObject[0];
        DAT_005606d0[0] = g_igUnsignedShortList_metaObject[0];
    }
    return &DAT_005606c0[0];
}

int *FUN_00164b80(void) {
    if (GPR_00554b30 == 0) {
        DAT_005606e0[0] = g_igFloatList_metaObject[0];
        GPR_00554b30 = 1;
        DAT_005606e4[0] = g_igVec2fList_metaObject[0];
        DAT_005606e8[0] = g_igVec3fList_metaObject[0];
        DAT_005606ec[0] = DAT_005610a8[0];
        DAT_005606f0[0] = g_igCharList_metaObject[0];
        DAT_005606f4[0] = g_igUnsignedCharList_metaObject[0];
        DAT_005606f8[0] = g_igShortList_metaObject[0];
        DAT_005606fc[0] = g_igUnsignedShortList_metaObject[0];
    }
    return &DAT_005606e0[0];
}

int *FUN_00164c20(void) {
    if (DAT_00554b34 == 0) {
        DAT_00554b34 = 1;
        DAT_00560710[0] = g_igUnsignedCharList_metaObject[0];
        DAT_00560714[0] = DAT_005610b0[0];
        DAT_00560718[0] = g_igVec4ucList_metaObject[0];
    }
    return &DAT_00560710[0];
}

int *FUN_00164c70(void) {
    if (GPR_00554b38 == 0) {
        DAT_00560720[0] = g_igVec3fList_metaObject[0];
        GPR_00554b38 = 1;
    }
    return &DAT_00560720[0];
}

int *FUN_00164ca0(void) {
    if (GPR_00554b3c == 0) {
        DAT_00560728[0] = g_igVec3fList_metaObject[0];
        GPR_00554b3c = 1;
    }
    return &DAT_00560728[0];
}

int *FUN_00164cd0(void) {
    if (GPR_00554b40 == 0) {
        DAT_00560730[0] = g_igFloatList_metaObject[0];
        GPR_00554b40 = 1;
        DAT_00560734[0] = g_igVec2fList_metaObject[0];
        DAT_00560738[0] = g_igCharList_metaObject[0];
        DAT_0056073c[0] = g_igUnsignedCharList_metaObject[0];
        DAT_00560740[0] = g_igShortList_metaObject[0];
        DAT_00560744[0] = g_igUnsignedShortList_metaObject[0];
    }
    return &DAT_00560730[0];
}

int *FUN_00164d50(void) {
    return &DAT_00560750[0];
}

int FUN_00164d60(int arg0, A_164d60 *arg1) {
    int *p; int v;
    p = 0;
    switch (arg1->f16) {
    case 1: p = (int *)FUN_001649f0(); break;
    case 2: p = (int *)FUN_00164a60(); break;
    case 3: p = (int *)FUN_00164aa0(); break;
    case 4: p = (int *)FUN_00164b10(); break;
    case 5: p = (int *)FUN_00164b80(); break;
    case 6: p = (int *)FUN_00164c20(); break;
    case 7: p = (int *)FUN_00164c70(); break;
    case 8: p = (int *)FUN_00164ca0(); break;
    case 9: p = (int *)FUN_00164cd0(); break;
    case 10: p = (int *)FUN_00164d50(); break;
    }
    goto test;
body:
    if (v == arg1->f12->v88()) { return 1; }
    p = p + 1;
test:
    v = *p;
    if (v != 0) goto body;
    return 0;
}

