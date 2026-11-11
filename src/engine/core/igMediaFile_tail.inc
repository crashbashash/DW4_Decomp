void Gap__Core__igMediaFile__vfunc_24(S_2ec250 *arg0) {
    R_2ec250 *t;

    if (arg0->f45 != 0) {
        ((VC_128_0 *)arg0)->vX();
        ((VC_104_1 *)arg0->f64)->vX(arg0->f24);
        ((VC_96_1 *)arg0->f64)->vX(arg0->f24);
        t = arg0->f64;
        if (t != 0) {
            t->f4 = t->f4 - 1;
            if (((unsigned long long) ((long long) t->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(t);
            }
        }
        arg0->f64 = 0;
        arg0->f24 = -1;
        FUN_00300f50((int)arg0, arg0->f60);
        arg0->f60 = 0;
        arg0->f48 = 0;
        arg0->f56 = 0;
        arg0->f45 = 0;
    }
}

void **Gap__Core__igMediaFile__vfunc_25(void **arg0, int arg1, int arg2) {
    DW4SR4 sp4C;
    DW4SR4 sp48;
    DW4SR4 sp44;
    DW4SR4 sp40;
    DW4SR4 sp3C;
    DW4SR4 sp38;
    DW4SR4 sp34;
    DW4SR4 sp30;
    int var_v1;

    FUN_002e30b0((int *)arg0, arg1);
    if (strcmp(arg2, &DAT_004f96a8[0]) == 0) {
        sp4C = ((DW4VCSR_92_1 *)(arg0))->vX((int)(0));
        var_v1 = sp4C.w0;
        goto block_21;
    }
    if (strcmp(arg2, (int *)DAT_004f9c48) == 0) {
        sp48 = ((DW4VCSR_92_1 *)(arg0))->vX((int)(4));
        var_v1 = sp48.w0;
        goto block_21;
    }
    if (strcmp(arg2, (int *)((char *)DAT_004f92f0)) == 0) {
        sp44 = ((DW4VCSR_92_1 *)(arg0))->vX((int)(1));
        var_v1 = sp44.w0;
        goto block_21;
    }
    if (strcmp(arg2, (int *)((char *)DAT_004f9c50)) == 0) {
        sp40 = ((DW4VCSR_92_1 *)(arg0))->vX((int)(5));
        var_v1 = sp40.w0;
        goto block_21;
    }
    if ((strcmp(arg2, (int *)DAT_004f9c58) == 0) || (strcmp(arg2, &DAT_004f9c60[0]) == 0)) {
        sp3C = ((DW4VCSR_92_1 *)(arg0))->vX((int)(3));
        var_v1 = sp3C.w0;
        goto block_21;
    }
    if ((strcmp(arg2, (int *)DAT_004f9c68) == 0) || (strcmp(arg2, &DAT_004f9c70[0]) == 0)) {
        sp38 = ((DW4VCSR_92_1 *)(arg0))->vX((int)(7));
        var_v1 = sp38.w0;
        goto block_21;
    }
    if ((strcmp(arg2, (int *)DAT_004f9c78) == 0) || (strcmp(arg2, &DAT_004f9c80[0]) == 0)) {
        sp34 = ((DW4VCSR_92_1 *)(arg0))->vX((int)(2));
        var_v1 = sp34.w0;
        goto block_21;
    }
    if ((strcmp(arg2, (int *)DAT_004f9c88) == 0) || (strcmp(arg2, &DAT_004f9c90[0]) == 0)) {
        sp30 = ((DW4VCSR_92_1 *)(arg0))->vX((int)(6));
        var_v1 = sp30.w0;
        goto block_21;
    }
    return 0;
block_21:
    return var_v1 == DAT_004fb418.v ? 0 : arg0;
}

void Gap__Core__igMediaFile__vfunc_26(igMediaFileView *self)
{
    self->vfunc_22();
}

void FUN_002ec570(struct O_2ec570 *arg0, int arg1) {
    int temp_a1;
    int var_s0;
    int var_v0;
    if (arg0->f48 < arg1) {
        var_s0 = arg1 * 2;
        if (arg1 > 0x100000) {
            var_s0 = arg1 + 0x100000;
        }
        temp_a1 = arg0->f60;
        if (temp_a1 != 0) {
            var_v0 = FUN_00300e50((int)arg0, temp_a1, var_s0);
        } else {
            var_v0 = igObject_AllocateStorage((int)arg0, var_s0);
        }
        arg0->f60 = var_v0;
        arg0->f48 = var_s0;
    }
    arg0->f52 = arg1;
}

int Gap__Core__igMediaFile__vfunc_27(A_2ec600 *arg0, int arg1, int arg2, int arg3) {
    int bytes;
    int got;
    int n;
    int cnt;
    int back;
    if (arg0->f2d == 0) {
        return -1;
    }
    bytes = arg2 * arg3;
    if (arg0->f2c == 1) {
        got = ((VC_112a *)arg0->f40)->vX(arg0->f18, arg1, (unsigned)arg3 * arg2);
        n = got / arg2;
        back = n * arg2;
        if (got != back) {
            ((VC_120b *)arg0->f40)->vX(arg0->f18, back - got, 1);
        }
        return n;
    }
    cnt = arg3;
    if (arg0->f34 < arg0->f38 + bytes) {
        cnt = (arg0->f34 - arg0->f38) / arg2;
        bytes = cnt * arg2;
    }
    memcpy(arg1, arg0->f3c + arg0->f38, bytes, arg0->f38);
    arg0->f38 = arg0->f38 + bytes;
    return cnt;
}

void Gap__Core__igMediaFile__vfunc_28(void *arg0, int arg1, int arg2, int (*arg3)(int, int), int arg4) {
    void **temp_a0;

    if (*(unsigned char *)((char *)(arg0) + 45) == 0) {
        arg3(arg4, -1);
    }
    if (*(unsigned char *)((char *)(arg0) + 44) == 1) {
        temp_a0 = (void **)(*(int *)((char *)(arg0) + 64));
        ((DW4VC_116_5 *)(temp_a0))->vX((int)(*(int *)((char *)(arg0) + 24)), (int)(arg1), (int)(arg2), (int)(arg3), (int)(arg4));
    }
    arg3(arg4, ((DW4VC_108_3 *)(((char *)(arg0) + 0)))->vX((int)(arg1), (int)(1), (int)(arg2)));
}

int Gap__Core__igMediaFile__vfunc_29(S_2ec7d0 *arg0, int arg1, int arg2, int arg3) {
    int s0;
    if (arg0->f45 == 0) {
        return -1;
    }
    if (arg2 == 0) {
        return 0;
    }
    if (arg0->f44 == 1) {
        if (arg0->f20 == 6) {
            arg0->f64->v120(arg0->f24, 0, 2);
        }
        return arg0->f64->v108(arg0->f24, arg1, arg3 * arg2) / arg2;
    }
    s0 = arg2 * arg3;
    if (arg0->f20 == 2) {
        arg0->f56 = arg0->f52;
    }
    FUN_002ec570((struct O_2ec570 *)arg0, arg0->f56 + s0);
    memcpy(arg0->f60 + arg0->f56, arg1, s0);
    arg0->f56 = arg0->f56 + s0;
    return s0 / arg2;
}

int Gap__Core__igMediaFile__vfunc_32(S_2ec900 *arg0) {
    if (arg0->f44 != 0) {
        return 0;
    }
    if (arg0->f46 != 0) {
        arg0->f64->vB(arg0->f24, 0, 0);
        arg0->f64->vA(arg0->f24, arg0->f60, arg0->f52);
    }
    return 0;
}

int Gap__Core__igMediaFile__vfunc_31(struct F_2ecc50 *self, int fmt, ...) {
    char buf[16384];
    int n;
    int off;
    int len;
    int pos;
    if (self->f44 != 0) {
        return -1;
    }
    n = __builtin_args_info(2);
    if (n >= 8) {
        off = 0;
    } else {
        off = (8 - n) * 8;
    }
    len = vsprintf(buf, fmt, (char *)__builtin_next_arg(fmt) - off);
    pos = self->f56 + len;
    if (pos >= self->f52) {
        FUN_002ec570((O_2ec570 *)self, pos);
    }
    memcpy(self->f60 + self->f56, buf, len);
    self->f56 = self->f56 + len;
    return len;
}

int Gap__Core__igMediaFile__vfunc_33(S_2ecd30 *arg0) {
    int sp1C;
    int t;
    if (arg0->f44 != 0) {
        int a = arg0->f24;
        V_2ecd30 *v = arg0->f64;
        if (v->v112(a, &sp1C, 1) != 0) {
            return sp1C;
        }
        return -1;
    }
    t = arg0->f56;
    if (t >= arg0->f52) {
        return -1;
    }
    arg0->f56 = t + 1;
    return arg0->f60[arg0->f56 - 1];
}

int Gap__Core__igMediaFile__vfunc_34(char *a, int c) {
    int n;
    if (*(unsigned char *)(a + 44) != 0) return -1;
    n = *(int *)(a + 56);
    if (n == 0) return -1;
    *(int *)(a + 56) = n - 1;
    if ((c & 0xff) != *(unsigned char *)(*(int *)(a + 60) + *(int *)(a + 56))) c = -1;
    return c;
}

int Gap__Core__igMediaFile__vfunc_35(S_2ece20 *arg0, unsigned char arg1) {
    int temp_a1;

    if (arg0->f2c != 0) {
        return -1;
    }
    temp_a1 = arg0->f38 + 1;
    if (temp_a1 >= arg0->f34) {
        FUN_002ec570((O_2ec570 *)arg0, temp_a1);
    }
    arg0->f3c[arg0->f38] = arg1;
    arg0->f38 = arg0->f38 + 1;
    return arg1;
}

char *Gap__Core__igMediaFile__vfunc_36(struct F_2ecea0 *arg0, char *arg1, int arg2) {
    /* matching construct: variant search — decl order [3, 2, 1, 0]; the unit compiler (combat build -O3 -Iinclude) assigns stack slots and registers in declaration order, the reverse of the 2001 default */
    unsigned char c;
    int pos;
    int len;
    int i;
    if (arg1 == 0) return 0;
    if (arg0->f44 != 0) return 0;
    len = arg0->len;
    pos = arg0->pos;
    if (pos >= len) return 0;
    i = 0;
    arg2 = arg2 - 1;
    if (arg2 + pos >= len) arg2 = len - pos;
    while (i < arg2) {
        c = arg0->data[arg0->pos];
        arg1[i] = c;
        i++;
        arg0->pos = arg0->pos + 1;
        if (c == 10) break;
    }
    arg1[i] = 0;
    return arg1;
}

int Gap__Core__igMediaFile__vfunc_37(struct S_2ecf50 *arg0, int arg1) {
    int temp_a1;
    int temp_v0;

    if (arg1 == 0) {
        return -1;
    }
    if (arg0->f44 != 0) {
        return -1;
    }
    temp_v0 = strlen(arg1);
    temp_a1 = arg0->f56 + temp_v0;
    if (temp_a1 >= arg0->f52) {
        FUN_002ec570((O_2ec570 *)arg0, temp_a1);
    }
    memcpy(arg0->f60 + arg0->f56, arg1, temp_v0);
    arg0->f56 = arg0->f56 + temp_v0;
    return temp_v0;
}

int Gap__Core__igMediaFile__vfunc_38(A_2ed000 *arg0, int arg1, int arg2) {
    int base;
    int cur;
    if (arg0->f44 != 0) {
        base = ((VC_156 *)arg0)->vX();
        if (((VC_120 *)arg0->f64)->vX(arg0->f24, arg1, arg2) != 0) {
            return 0;
        }
        cur = ((VC_156 *)arg0)->vX();
        switch (arg2) {
        case 0:
            return -(cur != arg1);
        case 1:
            return -(arg1 != cur - base);
        case 2:
            return 0;
        default:
            return -1;
        }
    } else {
        switch (arg2) {
        case 0:
            arg0->f56 = arg1;
            break;
        case 1:
            arg0->f56 = arg0->f56 + arg1;
            break;
        case 2:
            arg0->f56 = arg0->f52 + arg1;
            break;
        default:
            return -1;
        }
        if (arg0->f56 > arg0->f52) {
            arg0->f56 = arg0->f52;
        } else if (arg0->f56 < 0) {
            arg0->f56 = 0;
        }
        return 0;
    }
}

int Gap__Core__igMediaFile__vfunc_39(F_2ed170 *p) { if (p->f44) { int a = p->f24; C31 *o = p->f64; return o->vX(a); } return p->f56; }

