void FUN_0018ec40(void) {
    DAT_00561130 = FUN_00189420(Memory_GetAllocatorBySelector(DAT_00587038[0]));
    DAT_00561138 = FUN_001892c0(Memory_GetAllocatorBySelector(DAT_00587038[0]));
    DAT_00561140 = FUN_00189160(Memory_GetAllocatorBySelector(DAT_00587038[0]));
    DAT_00561148 = FUN_00189000(Memory_GetAllocatorBySelector(DAT_00587038[0]));
    DAT_00561150 = FUN_00188ea0(Memory_GetAllocatorBySelector(DAT_00587038[0]));
    DAT_00561160 = FUN_00188be0(Memory_GetAllocatorBySelector(DAT_00587038[0]));
    DAT_00561168 = FUN_00188a80(Memory_GetAllocatorBySelector(DAT_00587038[0]));
    DAT_00561158 = FUN_00188d40(Memory_GetAllocatorBySelector(DAT_00587038[0]));
    DAT_00561170 = FUN_00188920(Memory_GetAllocatorBySelector(DAT_00587038[0]));
    DAT_00561118 = FUN_00189840(Memory_GetAllocatorBySelector(DAT_00587038[0]));
    DAT_00561120 = FUN_001896e0(Memory_GetAllocatorBySelector(DAT_00587038[0]));
    DAT_00561128 = FUN_00189580(Memory_GetAllocatorBySelector(DAT_00587038[0]));
}

void FUN_0018edb0(int meta) {
    int root = (int)g_igVolume_metaObject[0];
    unsigned n;
    unsigned i;
    unsigned j;
    if (FUN_002fe290(meta, root) == 0) {
        return;
    }
    if (root == meta) {
        return;
    }
    n = FUN_002fe2c0(root);
    i = DAT_00561160->count;
    if (i >= n) {
        return;
    }
    ((IndexedWordPairKey *)FUN_002fe2e0(root, i))->idx = i;
    setCount(DAT_00561130, n); setSlot(DAT_00561130, i, (int)FUN_0018f490);
    setCount(DAT_00561138, n); setSlot(DAT_00561138, i, (int)FUN_0018f480);
    setCount(DAT_00561140, n); setSlot(DAT_00561140, i, (int)FUN_0018f470);
    setCount(DAT_00561148, n); setSlot(DAT_00561148, i, (int)FUN_0018f460);
    setCount(DAT_00561150, n); setSlot(DAT_00561150, i, (int)FUN_0018f450);
    setCount(DAT_00561158, n); setSlot(DAT_00561158, i, (int)FUN_0018f440);
    setCount(DAT_00561160, n); setSlot(DAT_00561160, i, (int)FUN_0018f430);
    setCount(DAT_00561168, n); setSlot(DAT_00561168, i, (int)FUN_0018f420);
    setCount(DAT_00561170, n); setSlot(DAT_00561170, i, (int)FUN_0018f410);
    n = n * n;
    i = i * i;
    setCount(DAT_00561118, n);
    for (j = i; j < n; j++) setSlot(DAT_00561118, j, (int)FUN_0018f400);
    setCount(DAT_00561120, n);
    for (j = i; j < n; j++) setSlot(DAT_00561120, j, (int)FUN_0018f3f0);
    setCount(DAT_00561128, n);
    for (j = i; j < n; j++) setSlot(DAT_00561128, j, (int)FUN_0018f3e0);
}

int FUN_0018f3e0(void) { return 0; }

void FUN_0018f3f0(void) { }

int FUN_0018f400(void) { return 0; }

void FUN_0018f410(void) { }

int FUN_0018f420(void) { return 1; }

void FUN_0018f430(void) { }

void FUN_0018f440(void) { }

int FUN_0018f450(void) { return 0; }

void FUN_0018f460(void) { }

int FUN_0018f470(void) { return 0; }

void FUN_0018f480(void) { }

int FUN_0018f490(void) { return 0; }

void FUN_0018f4a0(void){
  REL(DAT_00561118)
  REL(DAT_00561120)
  REL(DAT_00561128)
  REL(DAT_00561130)
  REL(DAT_00561138)
  REL(DAT_00561140)
  REL(DAT_00561148)
  REL(DAT_00561150)
  REL(DAT_00561158)
  REL(DAT_00561160)
  REL(DAT_00561168)
  REL(DAT_00561170)
}

InstanceListRef FUN_0018f760(int allocator) {
    int meta = (int)g_igVolume_metaObject[0];
    unsigned count = FUN_002fe2c0(meta);
    unsigned i;
    InstanceListRef list((NodeList *)FUN_00186c00(allocator));
    FUN_00301ee0(list.p, count);
    for (i = 0; i < count; i++) {
        igSmartPointer<InstanceNode> element(FUN_002fd6e0(FUN_002fe2e0(meta, i), allocator).get(), kRetainReference);
        setElement(list, i, element);
    }
    return list;
}

void **FUN_0018f980(void **arg0, int arg1) {
    int *o;

    if (arg0 != 0) {
        o = (int *)(*arg0);
        if (o != 0) {
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if ((short)arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

void **FUN_0018fa00(void **arg0, short arg1) {
    int *o;

    if (arg0 != 0) {
        o = (int *)*arg0;
        if (o != 0) {
            o[1] = o[1] - 1;
            if ((o[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(o);
            }
        }
        if (arg1 > 0) {
            __dl__FPv(arg0);
        }
    }
    return arg0;
}

BinaryOp FUN_0018fa80(void *arg0, void *arg1) {
    int var_v0;
    unsigned int temp_a0;
    unsigned int temp_v1;

    temp_a0 = *(int *)((char *)(arg0) + 8);
    temp_v1 = *(int *)((char *)(arg1) + 8);
    if (temp_a0 < temp_v1) {
        var_v0 = (temp_v1 * (temp_v1 + 2)) - temp_a0;
    } else {
        var_v0 = temp_v1 + (temp_a0 * temp_a0);
    }
    return (BinaryOp)*(int *)(*(int *)((char *)(DAT_00561118) + 16) + (var_v0 * 4));
}

BinaryOp FUN_0018fad0(void *arg0, void *arg1) {
    int var_v0;
    unsigned int temp_a0;
    unsigned int temp_v1;

    temp_a0 = *(int *)((char *)(arg0) + 8);
    temp_v1 = *(int *)((char *)(arg1) + 8);
    if (temp_a0 < temp_v1) {
        var_v0 = (temp_v1 * (temp_v1 + 2)) - temp_a0;
    } else {
        var_v0 = temp_v1 + (temp_a0 * temp_a0);
    }
    return (BinaryOp)*(int *)(*(int *)((char *)(DAT_00561120) + 16) + (var_v0 * 4));
}

UnaryOp FUN_0018fb20(void *arg0) {
    return (UnaryOp)*(int *)(*(int *)((char *)((*(void **)0x561130)) + 16) + (*(int *)((char *)arg0 + 8) * 4));
}

UnaryOp FUN_0018fb40(void *arg0) {
    return (UnaryOp)*(int *)(*(int *)((char *)((*(void **)0x561150)) + 16) + (*(int *)((char *)arg0 + 8) * 4));
}

UnaryOp FUN_0018fb60(void *arg0) {
    return (UnaryOp)*(int *)(*(int *)((char *)((*(void **)0x561148)) + 16) + (*(int *)((char *)arg0 + 8) * 4));
}

UnaryOp FUN_0018fb80(void *arg0) {
    return (UnaryOp)*(int *)(*(int *)((char *)((*(void **)0x561158)) + 16) + (*(int *)((char *)arg0 + 8) * 4));
}

UnaryOp FUN_0018fba0(void *arg0) {
    return (UnaryOp)*(int *)(*(int *)((char *)((*(void **)0x561170)) + 16) + (*(int *)((char *)arg0 + 8) * 4));
}

void FUN_0018fbc0(void *arg0, void *arg1, int arg2) {
    void *temp_a1;
    unsigned int temp_a3;
    unsigned int temp_a0;
    int var_a0;
    int temp_v1;

    temp_a3 = *(int *)((char *)arg0 + 8);
    temp_a0 = *(int *)((char *)arg1 + 8);
    if (temp_a3 < temp_a0) {
        var_a0 = (temp_a0 * (temp_a0 + 2)) - temp_a3;
    } else {
        var_a0 = temp_a0 + (temp_a3 * temp_a3);
    }
    temp_a1 = *(void **)0x561118;
    temp_v1 = *(int *)((char *)temp_a1 + 8);
    if ((temp_v1 != 0) && (var_a0 >= 0) && (var_a0 < temp_v1)) {
        *(int *)(*(int *)((char *)temp_a1 + 16) + (var_a0 * 4)) = arg2;
    }
}

void FUN_0018fc30(struct IndexedWordPairKey *arg0, struct IndexedWordPairKey *arg1, int arg2) {
    unsigned int a = arg0->idx;
    unsigned int b = arg1->idx;
    int i;
    if (a < b) {
        i = b * (b + 2) - a;
    } else {
        i = b + a * a;
    }
    setEntry(DAT_00561120, i, arg2);
}

void FUN_0018fca0(PairKeyedItem *a, PairKeyedItem *b, int v) {
    unsigned int x = a->key;
    unsigned int y = b->key;
    int i;
    if (x < y) {
        i = y * (y + 2) - x;
    } else {
        i = x * x + y;
    }
    setAt(DAT_00561128, i, v);
}

void FUN_0018fd10(int *arg0, int arg1) {
    OpTable *list = DAT_00561130;
    int i = arg0[2];
    if (list->count != 0 && i >= 0 && i < list->count) {
        list->data[i] = arg1;
    }
}

void FUN_0018fd50(struct IndexedSlotKey *arg0, int arg1) {
    int i;
    OpTable *g;
    i = arg0->idx;
    g = DAT_00561138;
    if ((g->count != 0) && (i >= 0) && (i < g->count)) {
        g->data[i] = arg1;
    }
}

void FUN_0018fd90(struct IndexedWordKey *arg0, int arg1) {
    setEntry(DAT_00561140, arg0->idx, arg1);
}

void FUN_0018fdd0(igMetaObject *meta, int arg1) {
    setAt(DAT_00561148, meta->_id, arg1);
}

void FUN_0018fe10(int *arg0, int arg1) {
    OpTable *list = DAT_00561150;
    int i = arg0[2];
    if (list->count != 0 && i >= 0 && i < list->count) {
        list->data[i] = arg1;
    }
}

void FUN_0018fe50(struct IndexedSlotKey *arg0, int arg1) {
    int i;
    OpTable *g;
    i = arg0->idx;
    g = DAT_00561158;
    if ((g->count != 0) && (i >= 0) && (i < g->count)) {
        g->data[i] = arg1;
    }
}

void FUN_0018fe90(struct IndexedWordKey *arg0, int arg1) {
    setEntry(DAT_00561160, arg0->idx, arg1);
}

void FUN_0018fed0(igMetaObject *meta, int arg1) {
    setAt(DAT_00561168, meta->_id, arg1);
}

void FUN_0018ff10(int *arg0, int arg1) {
    OpTable *list = DAT_00561170;
    int i = arg0[2];
    if (list->count != 0 && i >= 0 && i < list->count) {
        list->data[i] = arg1;
    }
}

void FUN_0018ff50(void **arg0, int arg1) {
    FUN_0018fb40(((DW4VC_88_0 *)(arg0))->vX())(arg0, arg1);
}

int FUN_0018ffa0(void **arg0, void **arg1) {
    void *temp_s0;

    temp_s0 = ((DW4VC_88_0 *)(arg0))->vX();
    return FUN_0018fa80(temp_s0, ((DW4VC_88_0 *)(arg1))->vX())(arg0, arg1);
}

void FUN_00190010(void **arg0, int arg1) {
    FUN_0018fb20(((DW4VC_88_0 *)(arg0))->vX())(arg0, arg1);
}

void igVolume_ExtendBy(void **arg0, void **arg1) {
    void *temp_s0;

    temp_s0 = ((DW4VC_88_0 *)(arg0))->vX();
    FUN_0018fad0(temp_s0, ((DW4VC_88_0 *)(arg1))->vX())(arg0, arg1);
}

void FUN_001900d0(void **arg0, int arg1) {
    FUN_0018fb60(((DW4VC_88_0 *)(arg0))->vX())(arg0, arg1);
}

void FUN_00190120(void **arg0, int arg1, int arg2) {
    int (*fn)(void **, int);
    int i;
    fn = (int (*)(void **, int))(FUN_0018fb60(((DW4VC_88_0 *)(arg0))->vX()));
    for (i = 0; i < arg2; i++) {
        fn(arg0, arg1 + i * 0xC);
    }
}

void FUN_001901b0(void **arg0, int arg1) {
    FUN_0018fb80(((DW4VC_88_0 *)(arg0))->vX())(arg0, arg1);
}

void FUN_00190200(void **arg0, int arg1) {
    FUN_0018fba0(((DW4VC_88_0 *)(arg0))->vX())(arg0, arg1);
}

