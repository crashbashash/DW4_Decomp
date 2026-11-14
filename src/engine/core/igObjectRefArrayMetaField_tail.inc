void Gap__Core__igObjectRefArrayMetaField__vfunc_52(igObjectRefArrayMetaField *self, int passThrough, int perElement) {
    void **elementDescriptor;

    elementDescriptor = (void **)(((void **)igObjectRefMetaField_GetDefaultDescriptor()));
    ((igMetaFieldView *)(elementDescriptor))->SwapBytes((void *)(passThrough), (int)(perElement * self->_num));
}

void FUN_00302780(igObjectRefArrayMetaField *arg0, int arg1, int arg2, igObject *arg3) {
    int temp_s0;
    igObject *temp_a0;

    temp_s0 = arg2 * 4;
    temp_a0 = ((igObject **)(arg1 + arg0->_offset))[arg2];
    if (arg0->_refCounted != 0) {
        if (arg3 != 0) {
            arg3->_refCount = arg3->_refCount + 1;
        }
        if (temp_a0 != 0) {
            temp_a0->_refCount = temp_a0->_refCount - 1;
            if ((temp_a0->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
    }
    ((igObject **)(arg1 + arg0->_offset))[arg2] = arg3;
}

int Gap__Core__igObjectRefArrayMetaField__vfunc_51(void *arg0, int arg1, char *arg2, int arg3, int arg4) {
    int *p;
    int cur;
    int start;
    int i;
    p = (int *)arg1;
    cur = (int)arg2;
    start = cur;
    for (i = 0; i < *(int *)((char *)arg0 + 68); i++) {
        cur += Gap__Core__igObjectRefMetaField__vfunc_51((igObjectRefMetaField *)arg0, (igObject **)p, cur, arg3, arg4);
        p++;
    }
    return cur - start;
}

void Gap__Core__igObjectRefArrayMetaField__vfunc_31(igObjectRefArrayMetaField *arg0, int arg1) {
    igObject *temp_v0;
    int var_s1;
    int var_s0;
    char *temp_a0;

    if (arg0->_construct != 0) {
        temp_a0 = (char *)arg0->_poolName;
        if ((temp_a0 != 0) && (*temp_a0 != 0)) {
            var_s1 = ((int)Memory_GetAllocatorByName((int)temp_a0));
            if (var_s1 == 0) {
                var_s1 = ((int)igObject_GetAllocator(arg1));
            }
        } else {
            var_s1 = ((int)igObject_GetAllocator(arg1));
        }
        for (var_s0 = 0; var_s0 < arg0->_num; var_s0++) {
            temp_v0 = ((igObject *)igMetaObject_CreateInstance((CreateMeta *)arg0->_metaObject, (MemoryPool *)var_s1));
            FUN_00302780((igObjectRefArrayMetaField *)arg0, arg1, var_s0, (igObject *)temp_v0);
            if (arg0->_refCounted != 0) {
                temp_v0->_refCount = temp_v0->_refCount - 1;
                if (((unsigned long long) ((long long)(int)temp_v0->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(temp_v0);
                }
            }
        }
    }
}

void Gap__Core__igObjectRefArrayMetaField__vfunc_32(igObjectRefArrayMetaField *arg0, int arg1) {
    int i;
    igObject *temp_a0;

    if (arg0->_destruct != 0) {
        for (i = 0; i < arg0->_num; i++) {
            temp_a0 = *(igObject **)(arg1 + arg0->_offset + (i * 4));
            if (temp_a0 != 0) {
                temp_a0->_refCount = (int)((int) (temp_a0->_refCount - 1));
                if (((unsigned long long) ((long long)(int)temp_a0->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(temp_a0);
                }
            }
        }
    }
}

void Gap__Core__igObjectRefArrayMetaField__vfunc_34(igObjectRefArrayMetaField *arg0, int arg1) {
    int var_s0;
    igObject *temp_a0;

    if (arg0->_persistent != 0) {
        if (arg0->_refCounted != 0) {
            for (var_s0 = 0; var_s0 < arg0->_num; var_s0++) {
                temp_a0 = *(igObject **)(arg1 + arg0->_offset + (var_s0 * 4));
                if (temp_a0 != 0) {
                    temp_a0->_refCount = temp_a0->_refCount - 1;
                    if (((unsigned long long)((long long)(int)temp_a0->_refCount << 0x29) >> 0x29) == 0) {
                        igObject_Destroy(temp_a0);
                    }
                }
            }
        }
        igRefMetaField_ClearValue((igMetaField *)arg0, (void *)arg1);
    }
}

void Gap__Core__igObjectRefArrayMetaField__vfunc_28(void *arg0, int arg1) {
    int temp_a0;
    int var_s0;

    for (var_s0 = 0; var_s0 < *(int *)((char *)(arg0) + 68); var_s0++) {
        temp_a0 = *(int *)(arg1 + *(int *)((char *)(arg0) + 8) + (var_s0 * 4));
        if (temp_a0 != 0) {
            igObject_ResetFields((igObjectDispatchView *)temp_a0);
        }
    }
}

void Gap__Core__igObjectRefArrayMetaField__vfunc_30(igObjectRefArrayMetaField *arg0, int arg1) {
    int i;

    for (i = 0; i < arg0->_num; i++) {
        FUN_00302780((igObjectRefArrayMetaField *)arg0, arg1, i, (igObject *)((int *)arg0->_default)[i]);
    }
}

void Gap__Core__igObjectRefArrayMetaField__vfunc_37(void *arg0, int arg1, int arg2) {
    int var_s0;

    for (var_s0 = 0; var_s0 < *(int *)((char *)(arg0) + 68); var_s0++) {
        FUN_00302780((igObjectRefArrayMetaField *)arg0, arg1, var_s0, (igObject *)(*(int *)(arg2 + *(int *)((char *)(arg0) + 8) + (var_s0 * 4))));
    }
}

void Gap__Core__igObjectRefArrayMetaField__vfunc_36(igObjectRefArrayMetaField *s, char *a1, char *a2) {
    int i = 0;
    while (i < s->_num) {
        int base = s->_offset;
        int off = i * 4;
        igObject *x = *(igObject **)(a1 + base + off);
        igObjectDispatchView *y = *(igObjectDispatchView **)(a2 + base + off);
        if (x == 0 && y == 0) break;
        if (x != 0 && y != 0) {
            FUN_003006a0((ShallowObject *)x, (ShallowObject *)y);
        } else if (x == 0) {
            FUN_00302780((igObjectRefArrayMetaField *)s, (int)a1, i, (igObject *)(y->cloneViaMetadata(1)));
        } else if (y == 0) {
            x->_refCount = x->_refCount - 1;
            if (((unsigned long long)((long long)(int)x->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(x);
            }
            FUN_00302780((igObjectRefArrayMetaField *)s, (int)a1, i, (igObject *)0);
        }
        i++;
    }
}

void Gap__Core__igObjectRefArrayMetaField__vfunc_38(int *arg0, int arg1, int arg2) {
    int var_s0;
    int v1;
    int p1;
    int p2;
    int off;
    igObject *a0;
    igObjectDispatchView *a1;

    var_s0 = 0;
    while (var_s0 < arg0[17]) {
        v1 = arg0[2];
        off = var_s0 * 4;
        p1 = arg1 + v1;
        p2 = arg2 + v1;
        a0 = *(igObject **)(p1 + off);
        a1 = *(igObjectDispatchView **)(p2 + off);
        if (a0 != 0 || a1 != 0) {
            if (a0 != 0 && a1 != 0) {
                FUN_00300770((ShallowObject *)a0, (int)a1);
            } else if (a0 == 0) {
                FUN_00302780((igObjectRefArrayMetaField *)arg0, arg1, var_s0, (igObject *)(a1->cloneViaMetadata(1)));
            } else if (a1 == 0) {
                a0->_refCount = a0->_refCount - 1;
                if ((a0->_refCount & 0x7FFFFF) == 0) {
                    igObject_Destroy(a0);
                }
                FUN_00302780((igObjectRefArrayMetaField *)arg0, arg1, var_s0, (igObject *)0);
            }
            var_s0 += 1;
        } else {
            break;
        }
    }
}

void Gap__Core__igObjectRefArrayMetaField__vfunc_39(igObjectRefArrayMetaField *arg0, int arg1) {
    int i;
    for (i = 0; i < arg0->_num; i++) {
        int *p = (int *)(arg1 + arg0->_offset + (i * 4));
        if (*p != 0) {
            igObject_ResetFields((igObjectDispatchView *)(*p));
        }
    }
}

int Gap__Core__igObjectRefArrayMetaField__vfunc_50(igObjectRefArrayMetaField *self, int src, void *dst, int a3, int a4) {
    int s;
    int d;
    int start;
    int i;

    s = src;
    d = (int)dst;
    start = d;
    for (i = 0; i < self->_num; i++) {
        d += igMemoryRefMetaField_WriteRawFieldMem(self, s, d, a3, a4);
        s += 4;
    }
    return ((d - start) + 3) & ~3;
}

int Gap__Core__igObjectRefArrayMetaField__vfunc_25(void *arg0) {
    return (*(int *)((char *)(arg0) + 68) * 4) & 0xFFFF;
}

void Gap__Core__igObjectRefArrayMetaField__vfunc_42(igObjectRefArrayMetaField *arg0, int arg1, int arg2, int arg3) {
    int temp_a0;
    int var_s0;

    for (var_s0 = 0; var_s0 < arg0->_num; var_s0++) {
        temp_a0 = *(int *)(arg1 + arg0->_offset + (var_s0 * 4));
        if (temp_a0 != 0) {
            igObject_VisitFields((VisitorObjectView *)temp_a0, (int (*)(void *, void *, void *))arg2, (void *)arg3);
        }
    }
}

int Gap__Core__igObjectRefArrayMetaField__vfunc_45(igObjectRefArrayMetaField *arg0, int arg1, int arg2) {
    int i;
    int off;
    int a;
    int b;
    for (i = 0; i < arg0->_num; i++) {
        off = arg0->_offset;
        a = *(int *)(arg1 + off + i * 4);
        b = *(int *)(arg2 + off + i * 4);
        if (a != b) {
            if (a == 0 || b == 0) {
                return 0;
            }
            if (!(igObject_IsAlikeExactly((void *)a, (void *)b) & 0xFF)) {
                return 0;
            }
        }
    }
    return 1;
}

int Gap__Core__igObjectRefArrayMetaField__vfunc_46(igObjectRefArrayMetaField *arg0, int arg1, int arg2) {
    int i;
    for (i = 0; i < arg0->_num; i++) {
        int a = *(int *)(arg1 + arg0->_offset + i * 4);
        int b = *(int *)(arg2 + arg0->_offset + i * 4);
        if (a != b) {
            if (a == 0 || b == 0) {
                return 0;
            }
            if (!(igObject_IsAlikeDeep((DeepObject *)a, (DeepObject *)b) & 0xFF)) {
                return 0;
            }
        }
    }
    return 1;
}

int Gap__Core__igObjectRefArrayMetaField__vfunc_47(igObjectRefArrayMetaField *arg0, int arg1, int arg2) {
    int i;
    int a;
    int b;

    for (i = 0; i < arg0->_num; i++) {
        a = *(int *)(arg1 + arg0->_offset + i * 4);
        b = *(int *)(arg2 + arg0->_offset + i * 4);
        if (a != b) {
            if ((a == 0) || (b == 0)) {
                return 0;
            }
            if (!(igObject_IsAlikeShallow((igObjectDispatchView *)a, (igObjectDispatchView *)b) & 0xFF)) {
                return 0;
            }
        }
    }
    return 1;
}

