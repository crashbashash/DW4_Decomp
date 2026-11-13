void Gap__Gfx__igTgaLoader__vfunc_12(void) {
    Gap__Core__igObject__vfunc_10();
}

int FUN_001682e0(S_1682e0 *arg0, int arg1) {
    O_1682e0 *temp_a0;
    O_1682e0 *temp_a0_2;

    temp_a0 = arg0->f8;
    if (temp_a0 != 0) {
        temp_a0->vX();
        temp_a0_2 = arg0->f8;
        if (temp_a0_2 != 0) {
            temp_a0_2->rc = temp_a0_2->rc - 1;
            if ((temp_a0_2->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0_2);
            }
        }
        arg0->f8 = 0;
    }
    FUN_00300f50(arg0, arg0->f12);
    arg0->f12 = 0;
    FUN_00300f50(arg0, arg0->f16);
    arg0->f16 = 0;
    FUN_00300f50(arg0, arg0->f20);
    arg0->f20 = 0;
    arg0->f24 = 0;
    arg0->f28 = 0;
    return arg1;
}

int FUN_001683a0(void *arg0) {
    int temp_v0;
    void **temp_a0;

    temp_a0 = (void **)(*(int *)((char *)(arg0) + 8));
    temp_v0 = ((DW4VC_108_3 *)(temp_a0))->vX((int)(*(int *)((char *)(arg0) + 20)), (int)(1), (int)(0x400));
    if (temp_v0 == 0) {
        return 0;
    }
    *(int *)((char *)(arg0) + 40) = temp_v0;
    *(int *)((char *)(arg0) + 36) = 0;
    return 1;
}

int FUN_00168400(void *arg0) {
    return *(int *)((char *)arg0 + 36) >= *(int *)((char *)arg0 + 40);
}

unsigned char FUN_00168420(void *arg0) {
    int temp_v1;

    if ((FUN_00168400(arg0) != 0) && (FUN_001683a0(arg0) == 0)) {
        return 0xFFU;
    }
    temp_v1 = *(int *)((char *)(arg0) + 36);
    *(int *)((char *)(arg0) + 36) = (int)((int) (temp_v1 + 1));
    return *(int *)(*(int *)((char *)(arg0) + 20) + temp_v1);
}

void FUN_00168480(struct D *arg0, char *arg1) {
    int i; int a; int v;
    v = arg0->f24 - 1;
    arg0->f24 = v;
    if (v <= 0) {
        arg0->f24 = (signed char)FUN_00168420(arg0);
        a = arg0->f24;
        if (a & 0x80) {
            arg0->f24 = (a & 0x7F) + 1;
            arg0->f28 = 1;
            for (i = 0; i < arg0->f32; i++) { arg1[i] = FUN_00168420(arg0); }
        } else {
            arg0->f24 = a + 1;
            arg0->f28 = 0;
        }
    }
    if (arg0->f28 == 0) {
        for (i = 0; i < arg0->f32; i++) { arg1[i] = FUN_00168420(arg0); }
    }
}

int FUN_00168570(int arg0, unsigned int arg1, int arg2, int *arg3, int *arg4, int *arg5, char *arg6) {
    *arg4 = arg2;
    *arg6 = 0;
    *arg5 = 0x64;
    switch (arg1) {
    case 1:
        *arg3 = 0x10000;
        break;
    case 6:
        *arg3 = 0;
        break;
    case 2:
        *arg3 = 0x10000;
        *arg4 *= 2;
        break;
    case 3:
        *arg3 = 8;
        *arg4 *= 2;
        break;
    case 4:
        *arg3 = 5;
        *arg4 *= 3;
        break;
    case 5:
        *arg3 = 7;
        *arg4 *= 4;
        break;
    case 7:
        *arg3 = 0x10000;
        *arg6 = 1;
        *arg4 = 0x400;
        break;
    case 8:
        *arg3 = 0x10000;
        *arg6 = 1;
        *arg4 = 0x400;
        break;
    case 12:
        *arg3 = 0;
        *arg6 = 1;
        *arg4 = 0x400;
        break;
    case 9:
        *arg3 = 8;
        *arg6 = 1;
        *arg4 = 0x400;
        break;
    case 10:
        *arg3 = 5;
        *arg6 = 1;
        *arg4 = 0x400;
        break;
    case 11:
        *arg3 = 7;
        *arg6 = 1;
        *arg4 = 0x400;
        break;
    default:
        *arg3 = -1;
        *arg4 = -1;
        *arg5 = -1;
        break;
    }
    return *arg3;
}

void FUN_001690d0(Arg0d0 *arg0) {
    int sp5C;
    int i;
    P_1690d0 *p;
    int n;
    int v;
    int *old;
    int *s3;
    Buf860 *b;
    sp5C = 4;
    thunk_FUN_003065f0(*(int *)((char *)(g_objectSystem[0]) + 56), 4, &IG_GFX_VC_RD_ARRAY_SIZE[0], &sp5C, 4, 0);
    p = (P_1690d0 *)Memory_AllocateBufferDirect(20, FUN_00165d10((int *)arg0));
    if (p != 0) {
        n = sp5C;
        p->f8 = 0;
        if (g_stringPool[0] == 0) {
            v = StringPool_Allocate(16);
            if (v != 0) {
                v = StringPool_Construct(v);
            }
            g_stringPool[0] = v;
        }
        s3 = (int *)StringPool_Intern(g_stringPool[0], &IG_GFX_VC_RD_ARRAY_SIZE[0]);
        old = p->f8;
        if (old != 0) {
            int *a1 = old - 2;
            int v0 = old[-1] - 1;
            old[-1] = v0;
            if (v0 == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
        p->f8 = s3;
        if (n == 0) {
            n = 1;
        }
        b = (Buf860 *)Memory_FindBufferOwner(p);
        p->f16 = b->vA(n, 48, 16);
        p->f12 = b->vB(n, 2);
        i = 0;
        p->f2 = n;
        p->f0 = n;
        p->f4 = n;
        while (i < n) {
            p->f12[i] = i;
            i = i + 1;
        }
    }
    arg0->f868 = p;
    arg0->f872 = -1;
}

