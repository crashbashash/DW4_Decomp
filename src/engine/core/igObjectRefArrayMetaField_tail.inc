void igObjectRefArrayMetaField_SwapBytes(igObjectRefArrayMetaField *self, int passThrough, int perElement) {
    void **elementDescriptor;

    elementDescriptor = (void **)(((void **)igObjectRefMetaField_GetDefaultDescriptor()));
    ((igMetaFieldView *)(elementDescriptor))->SwapBytes((void *)(passThrough), (int)(perElement * self->_num));
}

void igObjectRefArrayMetaField_SetElement(igObjectRefArrayMetaField *arg0, int arg1, int arg2, igObject *arg3) {
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

int igObjectRefArrayMetaField_ReadRawFieldMem(void *arg0, int arg1, char *arg2, int arg3, int arg4) {
    int *p;
    int cur;
    int start;
    int i;
    p = (int *)arg1;
    cur = (int)arg2;
    start = cur;
    for (i = 0; i < *(int *)((char *)arg0 + 68); i++) {
        cur += igObjectRefMetaField_ReadRawFieldMem((igObjectRefMetaField *)arg0, (igObject **)p, cur, arg3, arg4);
        p++;
    }
    return cur - start;
}

void igObjectRefArrayMetaField_ConstructValue(igObjectRefArrayMetaField *arg0, int arg1) {
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
            temp_v0 = ((igObject *)igMetaObject_CreateInstance((igMetaObject *)arg0->_metaObject, (igMemoryPoolView *)var_s1));
            igObjectRefArrayMetaField_SetElement((igObjectRefArrayMetaField *)arg0, arg1, var_s0, (igObject *)temp_v0);
            if (arg0->_refCounted != 0) {
                temp_v0->_refCount = temp_v0->_refCount - 1;
                if (((unsigned long long) ((long long)(int)temp_v0->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(temp_v0);
                }
            }
        }
    }
}

void igObjectRefArrayMetaField_DestructValue(igObjectRefArrayMetaField *arg0, int arg1) {
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

void igObjectRefArrayMetaField_ClearValue(igObjectRefArrayMetaField *arg0, int arg1) {
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

void igObjectRefArrayMetaField_SetToDefault(void *arg0, int arg1) {
    int temp_a0;
    int var_s0;

    for (var_s0 = 0; var_s0 < *(int *)((char *)(arg0) + 68); var_s0++) {
        temp_a0 = *(int *)(arg1 + *(int *)((char *)(arg0) + 8) + (var_s0 * 4));
        if (temp_a0 != 0) {
            igObject_ResetFields((igObjectDispatchView *)temp_a0);
        }
    }
}

void igObjectRefArrayMetaField_CopyDefaultToValue(igObjectRefArrayMetaField *arg0, int arg1) {
    int i;

    for (i = 0; i < arg0->_num; i++) {
        igObjectRefArrayMetaField_SetElement((igObjectRefArrayMetaField *)arg0, arg1, i, (igObject *)((int *)arg0->_default)[i]);
    }
}

void igObjectRefArrayMetaField_CopyReference(void *arg0, int arg1, int arg2) {
    int var_s0;

    for (var_s0 = 0; var_s0 < *(int *)((char *)(arg0) + 68); var_s0++) {
        igObjectRefArrayMetaField_SetElement((igObjectRefArrayMetaField *)arg0, arg1, var_s0, (igObject *)(*(int *)(arg2 + *(int *)((char *)(arg0) + 8) + (var_s0 * 4))));
    }
}

void igObjectRefArrayMetaField_DeepCopy(igObjectRefArrayMetaField *s, char *a1, char *a2) {
    int i = 0;
    while (i < s->_num) {
        int base = s->_offset;
        int off = i * 4;
        igObject *x = *(igObject **)(a1 + base + off);
        igObjectDispatchView *y = *(igObjectDispatchView **)(a2 + base + off);
        if (x == 0 && y == 0) break;
        if (x != 0 && y != 0) {
            igObject_DeepCopy((igObjectDispatchView *)x, (igObjectDispatchView *)y);
        } else if (x == 0) {
            igObjectRefArrayMetaField_SetElement((igObjectRefArrayMetaField *)s, (int)a1, i, (igObject *)(y->cloneViaMetadata(1)));
        } else if (y == 0) {
            x->_refCount = x->_refCount - 1;
            if (((unsigned long long)((long long)(int)x->_refCount << 0x29) >> 0x29) == 0) {
                igObject_Destroy(x);
            }
            igObjectRefArrayMetaField_SetElement((igObjectRefArrayMetaField *)s, (int)a1, i, (igObject *)0);
        }
        i++;
    }
}

void igObjectRefArrayMetaField_ShallowCopy(int *arg0, int arg1, int arg2) {
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
                igObject_ShallowCopy((igObjectDispatchView *)a0, (int)a1);
            } else if (a0 == 0) {
                igObjectRefArrayMetaField_SetElement((igObjectRefArrayMetaField *)arg0, arg1, var_s0, (igObject *)(a1->cloneViaMetadata(1)));
            } else if (a1 == 0) {
                a0->_refCount = a0->_refCount - 1;
                if ((a0->_refCount & 0x7FFFFF) == 0) {
                    igObject_Destroy(a0);
                }
                igObjectRefArrayMetaField_SetElement((igObjectRefArrayMetaField *)arg0, arg1, var_s0, (igObject *)0);
            }
            var_s0 += 1;
        } else {
            break;
        }
    }
}

void igObjectRefArrayMetaField_ResetValue(igObjectRefArrayMetaField *arg0, int arg1) {
    int i;
    for (i = 0; i < arg0->_num; i++) {
        int *p = (int *)(arg1 + arg0->_offset + (i * 4));
        if (*p != 0) {
            igObject_ResetFields((igObjectDispatchView *)(*p));
        }
    }
}

int igObjectRefArrayMetaField_WriteRawFieldMem(igObjectRefArrayMetaField *self, int src, void *dst, int a3, int a4) {
    int s;
    int d;
    int start;
    int i;

    s = src;
    d = (int)dst;
    start = d;
    for (i = 0; i < self->_num; i++) {
        d += igMemoryRefMetaField_WriteRawFieldMem((igMetaFieldView *)self, (int *)s, (void *)d, a3, a4);
        s += 4;
    }
    return ((d - start) + 3) & ~3;
}

int igObjectRefArrayMetaField_GetSize(void *arg0) {
    return (*(int *)((char *)(arg0) + 68) * 4) & 0xFFFF;
}

void igObjectRefArrayMetaField_ReleaseElements(igObjectRefArrayMetaField *arg0, int arg1, int arg2, int arg3) {
    int temp_a0;
    int var_s0;

    for (var_s0 = 0; var_s0 < arg0->_num; var_s0++) {
        temp_a0 = *(int *)(arg1 + arg0->_offset + (var_s0 * 4));
        if (temp_a0 != 0) {
            igObject_VisitFields((igObjectDispatchView *)temp_a0, (int (*)(void *, void *, void *))arg2, (void *)arg3);
        }
    }
}

int igObjectRefArrayMetaField_IsAlikeExactly(igObjectRefArrayMetaField *arg0, int arg1, int arg2) {
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

int igObjectRefArrayMetaField_IsAlikeDeep(igObjectRefArrayMetaField *arg0, int arg1, int arg2) {
    int i;
    for (i = 0; i < arg0->_num; i++) {
        int a = *(int *)(arg1 + arg0->_offset + i * 4);
        int b = *(int *)(arg2 + arg0->_offset + i * 4);
        if (a != b) {
            if (a == 0 || b == 0) {
                return 0;
            }
            if (!(igObject_IsAlikeDeep((igObjectDispatchView *)a, (igObjectDispatchView *)b) & 0xFF)) {
                return 0;
            }
        }
    }
    return 1;
}

int igObjectRefArrayMetaField_IsAlikeShallow(igObjectRefArrayMetaField *arg0, int arg1, int arg2) {
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

