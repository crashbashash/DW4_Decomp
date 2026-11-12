/* matching construct: the receiver class is not established (the +12 vertex array and +32 index base are accessed through FUN_001b23b0 / f32 below), so it keeps a local layout; _objList data, _data and the vertex array reference are 4-byte handles, so the handle and the array stay ONE variable */
void FUN_001b21d0(A_1b21d0 *arg0, V3_1b21d0 *arg1, V3_1b21d0 *arg2) {
    igVertexArray2 *sp7C;
    igVec3fList *s3;
    unsigned s4, s5;
    V3_1b21d0 *v;
    arg1->x = arg1->y = arg1->z = 1.00000002e+20f;
    arg2->x = arg2->y = arg2->z = -1.00000002e+20f;
    FUN_001b23b0((int *)&sp7C, (int *)arg0);
    s3 = (igVec3fList *)igVertexArray2__FindVertexData(sp7C, 1, 0);
    if (sp7C != 0) {
        sp7C->_refCount = sp7C->_refCount - 1;
        if (((unsigned long long)(long long)(int)sp7C->_refCount & 0x7fffffULL) == 0) igObject_Destroy((void *)sp7C);
    }
    if (s3 != 0) {
        s3 = (igVec3fList *)((igVertexData *)s3)->_data;
        if (s3 != 0 && igObject_IsKindOf(s3, DAT_005610b8[0]) != 0) {
            s3 = (igVec3fList *)s3;
        } else {
            s3 = 0;
        }
        s4 = arg0->f32;
        while (s5 = arg0->f32, s4 < s5 + arg0->v34()) {
            v = (V3_1b21d0 *)((char *)s3->_data + s4 * 12);
            if (!(arg1->x <= v->x)) arg1->x = v->x;
            if (!(arg1->y <= v->y)) arg1->y = v->y;
            if (!(arg1->z <= v->z)) arg1->z = v->z;
            v = (V3_1b21d0 *)((char *)s3->_data + s4 * 12);
            if (arg2->x < v->x) arg2->x = v->x;
            if (arg2->y < v->y) arg2->y = v->y;
            if (arg2->z < v->z) arg2->z = v->z;
            s4++;
        }
    }
}

void FUN_001b23b0(int *arg0, int *arg1) {
    int *p;
    *arg0 = arg1[3];
    p = (int *)*arg0;
    if (p != 0) {
        p[1] = p[1] + 1;
    }
}

int FUN_001b23e0(int arg0, Y *arg1) {
    V3_1b23e0 sp40;
    V3_1b23e0 sp30;
    igSmartPointer<X_1b23e0> created(((X_1b23e0 *)FUN_0018a660(igObject_GetAllocator())));
    FUN_001b1fa0(arg1, &sp40, &sp30);
    created.get()->a = sp40;
    created.get()->b = sp30;
    FUN_00190060(arg0, created.get());
    return (((int)((unsigned int) (*arg1->f12->vX() & 0xF0) >> 4)) & 0xFF) <= 0;
}

int FUN_001b24d0(int arg0, int arg1) {
    igSmartPointer<BoundsObject> bounds(((BoundsObject *)FUN_0018a660(igObject_GetAllocator())));
    BoundsObject *array;
    V3_1b24d0 min;
    V3_1b24d0 max;
    FUN_001b21d0((A_1b21d0 *)arg1, (V3_1b21d0 *)&min, (V3_1b21d0 *)&max);
    bounds.get()->min = min;
    bounds.get()->max = max;
    FUN_00190060(arg0, bounds.get());
    FUN_001b23b0((int *)&array, (int *)arg1);
    int missing = igVertexArray2__FindVertexData(array, 5, 0);
    if (array != 0) {
        array->_refCount = array->_refCount - 1;
        if ((array->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(array);
        }
    }
    return !missing;
}

bool FUN_001b2600(int arg0, void *arg1) {
    List_1b2600 *l;
    int n;
    bool ok;
    int i;
    Elem *e;
    ok = true;
    l = ((Owner *)arg1)->list;
    n = l->count;
    for (i = 0; i < n; i++) {
        e = l->data[i];
        if (igObject_IsKindOf(e, DAT_0055f170[0]) != 0) {
            if (FUN_001b23e0(arg0, (Y *)e) == 0) {
                ok = false;
            }
        } else if (DAT_0055f158[0] == e->vX()) {
            if (FUN_001b24d0(arg0, (int)(e)) == 0) {
                ok = false;
            }
        } else {
            ok = false;
        }
    }
    return ok;
}

int FUN_001b26f0(int arg0, void *arg1, int arg2) {
    if (*(int *)((char *)(arg1) + 96) == 0) {
        ((DW4VC_156_1 *)(((char *)(arg1) + 0)))->vX((int)(arg2));
        FUN_0018ac80(arg0, (char *)arg1 + 0x20);
    }
    return 1;
}

void Gap__Core__igObject__vfunc_37(void *self, int arg1) {
    char *base = (char *)self;
    V_1b2750 *c = *(V_1b2750 **)(base + 104);
    if (c != 0) c->vX(base + 0x20, arg1);
}

