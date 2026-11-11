void Gap__Core__igObjectRefArrayMetaField__vfunc_52(igObjectRefArrayMetaField *self, int passThrough, int perElement) {
    void **elementDescriptor;

    elementDescriptor = (void **)(((void **)igObjectRefMetaField_GetDefaultDescriptor()));
    ((DW4VC_208_2 *)(elementDescriptor))->vX((int)(passThrough), (int)(perElement * self->_num));
}

void FUN_00302780(struct A_302780 *arg0, int arg1, int arg2, struct R_302780 *arg3) {
    int temp_s0;
    struct R_302780 *temp_a0;

    temp_s0 = arg2 * 4;
    temp_a0 = ((struct R_302780 **)(arg1 + arg0->f8))[arg2];
    if (arg0->f60 != 0) {
        if (arg3 != 0) {
            arg3->rc = arg3->rc + 1;
        }
        if (temp_a0 != 0) {
            temp_a0->rc = temp_a0->rc - 1;
            if ((temp_a0->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
    }
    ((struct R_302780 **)(arg1 + arg0->f8))[arg2] = arg3;
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

void Gap__Core__igObjectRefArrayMetaField__vfunc_31(struct A_3028d0 *arg0, int arg1) {
    struct T_3028d0 *temp_v0;
    int var_s1;
    int var_s0;
    char *temp_a0;

    if (arg0->f34 != 0) {
        temp_a0 = arg0->f40;
        if ((temp_a0 != 0) && (*temp_a0 != 0)) {
            var_s1 = ((int)Memory_GetAllocatorByName((int)temp_a0));
            if (var_s1 == 0) {
                var_s1 = ((int)igObject_GetAllocator(arg1));
            }
        } else {
            var_s1 = ((int)igObject_GetAllocator(arg1));
        }
        for (var_s0 = 0; var_s0 < arg0->f44; var_s0++) {
            temp_v0 = ((struct T_3028d0 *)igMetaObject_CreateInstance((CreateMeta *)arg0->f38, (MemoryPool *)var_s1));
            FUN_00302780((A_302780 *)arg0, arg1, var_s0, (R_302780 *)temp_v0);
            if (arg0->f3c != 0) {
                temp_v0->refs = temp_v0->refs - 1;
                if (((unsigned long long) ((long long) temp_v0->refs << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(temp_v0);
                }
            }
        }
    }
}

void Gap__Core__igObjectRefArrayMetaField__vfunc_32(A_3029e0 *arg0, int arg1) {
    int i;
    S1_3029e0 *temp_a0;

    if (arg0->f35 != 0) {
        for (i = 0; i < arg0->f44; i++) {
            temp_a0 = *(S1_3029e0 **)(arg1 + arg0->f8 + (i * 4));
            if (temp_a0 != 0) {
                temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
                if (((unsigned long long) ((long long) temp_a0->f4 << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(temp_a0);
                }
            }
        }
    }
}

void Gap__Core__igObjectRefArrayMetaField__vfunc_34(S_302a80 *arg0, int arg1) {
    int var_s0;
    R_302a80 *temp_a0;

    if (arg0->f38 != 0) {
        if (arg0->f60 != 0) {
            for (var_s0 = 0; var_s0 < arg0->f68; var_s0++) {
                temp_a0 = *(R_302a80 **)(arg1 + arg0->f8 + (var_s0 * 4));
                if (temp_a0 != 0) {
                    temp_a0->refs = temp_a0->refs - 1;
                    if (((unsigned long long)((long long)temp_a0->refs << 0x29) >> 0x29) == 0) {
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
            igObject_ResetFields((void **)temp_a0);
        }
    }
}

void Gap__Core__igObjectRefArrayMetaField__vfunc_30(struct L_302bc0 *arg0, int arg1) {
    int i;

    for (i = 0; i < arg0->count; i++) {
        FUN_00302780((A_302780 *)arg0, arg1, i, (R_302780 *)arg0->data[i]);
    }
}

void Gap__Core__igObjectRefArrayMetaField__vfunc_37(void *arg0, int arg1, int arg2) {
    int var_s0;

    for (var_s0 = 0; var_s0 < *(int *)((char *)(arg0) + 68); var_s0++) {
        FUN_00302780((A_302780 *)arg0, arg1, var_s0, (R_302780 *)(*(int *)(arg2 + *(int *)((char *)(arg0) + 8) + (var_s0 * 4))));
    }
}

void Gap__Core__igObjectRefArrayMetaField__vfunc_36(S_302cb0 *s, char *a1, char *a2) {
    int i = 0;
    while (i < s->f68) {
        int base = s->f8;
        int off = i * 4;
        R_302cb0 *x = *(R_302cb0 **)(a1 + base + off);
        V_302cb0 *y = *(V_302cb0 **)(a2 + base + off);
        if (x == 0 && y == 0) break;
        if (x != 0 && y != 0) {
            FUN_003006a0((void **)x, (void **)y);
        } else if (x == 0) {
            FUN_00302780((struct A_302780 *)s, (int)a1, i, (struct R_302780 *)(y->v19(1)));
        } else if (y == 0) {
            x->f4 = x->f4 - 1;
            if (((unsigned long long)((long long)x->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(x);
            }
            FUN_00302780((struct A_302780 *)s, (int)a1, i, (struct R_302780 *)0);
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
    R_302de0 *a0;
    C_302de0 *a1;

    var_s0 = 0;
    while (var_s0 < arg0[17]) {
        v1 = arg0[2];
        off = var_s0 * 4;
        p1 = arg1 + v1;
        p2 = arg2 + v1;
        a0 = *(R_302de0 **)(p1 + off);
        a1 = *(C_302de0 **)(p2 + off);
        if (a0 != 0 || a1 != 0) {
            if (a0 != 0 && a1 != 0) {
                FUN_00300770((ShallowObject *)a0, (int)a1);
            } else if (a0 == 0) {
                FUN_00302780((A_302780 *)arg0, arg1, var_s0, (R_302780 *)(a1->clone(1)));
            } else if (a1 == 0) {
                a0->refs = a0->refs - 1;
                if ((a0->refs & 0x7FFFFF) == 0) {
                    igObject_Destroy(a0);
                }
                FUN_00302780((A_302780 *)arg0, arg1, var_s0, (R_302780 *)0);
            }
            var_s0 += 1;
        } else {
            break;
        }
    }
}

void Gap__Core__igObjectRefArrayMetaField__vfunc_39(S_302f10 *arg0, int arg1) {
    int i;
    for (i = 0; i < arg0->n; i++) {
        int *p = (int *)(arg1 + arg0->base + (i * 4));
        if (*p != 0) {
            igObject_ResetFields((void **)(*p));
        }
    }
}

int Gap__Core__igObjectRefArrayMetaField__vfunc_50(F_302f90 *self, int src, void *dst, int a3, int a4) {
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

int Gap__Core__igObjectRefArrayMetaField__vfunc_45(struct M_3030e0 *arg0, int arg1, int arg2) {
    int i;
    int off;
    int a;
    int b;
    for (i = 0; i < arg0->f68; i++) {
        off = arg0->f8;
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

int Gap__Core__igObjectRefArrayMetaField__vfunc_46(struct S_3031a0 *arg0, int arg1, int arg2) {
    int i;
    for (i = 0; i < arg0->n; i++) {
        int a = *(int *)(arg1 + arg0->off + i * 4);
        int b = *(int *)(arg2 + arg0->off + i * 4);
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

int Gap__Core__igObjectRefArrayMetaField__vfunc_47(struct O_303260 *arg0, int arg1, int arg2) {
    int i;
    int a;
    int b;

    for (i = 0; i < arg0->f68; i++) {
        a = *(int *)(arg1 + arg0->f8 + i * 4);
        b = *(int *)(arg2 + arg0->f8 + i * 4);
        if (a != b) {
            if ((a == 0) || (b == 0)) {
                return 0;
            }
            if (!(igObject_IsAlikeShallow((V_2fef20 *)a, (V_2fef20 *)b) & 0xFF)) {
                return 0;
            }
        }
    }
    return 1;
}

