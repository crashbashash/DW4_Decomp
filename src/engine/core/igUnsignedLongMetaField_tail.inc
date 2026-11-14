int Gap__Core__igUnsignedLongMetaField__vfunc_56(int arg0, int arg1, int arg2) {
    int sp1C;

    sp1C = 0;
    sscanf(arg2, &text_ld_n[0], arg1, &sp1C);
    return sp1C;
}

void Gap__Core__igUnsignedLongMetaField__vfunc_57(int *arg0, int arg1, long long *arg2) {
    struct { int w; int pad[255]; } sp20;
    int var_v0;
    int var_v1;

    sprintf((int *)&sp20, &DAT_004f9bc0[0], *arg2);
    if ((int *)&sp20 == 0) {
        var_v1 = 0;
    } else {
        if (g_stringPool[0] == 0) {
            var_v0 = ((int)StringPool_Allocate(0x10));
            if (var_v0 != 0) {
                var_v0 = ((int)StringPool_Construct((StringPool *)var_v0));
            }
            g_stringPool[0] = var_v0;
        }
        var_v1 = StringPool_Intern((StringPool *)g_stringPool[0], (const char *)((int *)&sp20));
    }
    *arg0 = var_v1;
}

int FUN_0030eb30(void) {
    return 8;
}

int **FUN_0030eb40(int **arg0, int extra1) {
    igMetaField_Construct((igMetaField *)arg0);
    *arg0 = &DAT_00533530[0];
    if (arg0 != 0) {
        FUN_0030eb80(arg0);
    }
    return arg0;
}

int **FUN_0030eb80(int **arg0) {
    igMetaField_Init((igMetaField *)arg0);
    *arg0 = &DAT_00533530[0];
    return arg0;
}

int **FUN_0030ebc0(int **arg0, int extra1) {
    igMetaField_CopyConstruct((igMetaField *)arg0, (igMetaField *)extra1);
    *arg0 = &DAT_00533530[0];
    return arg0;
}

void Gap__Core__igUnsignedLongMetaField__vfunc_02(int extra0) {
    igMetaField_Destruct((igMetaField *)extra0);
}

void FUN_0030ec10(void **arg0, long long arg1) {
    long long sp18;

    sp18 = arg1;
    ((igMetaFieldView *)(arg0))->SetDefault(&sp18);
}

/* igUnsignedLongArrayMetaField vtable slot 27 (+0x6c): constant leaf returning 8, the byte size of
 * one unsigned long element (a 64-bit value on this target). The same igMetaField slot is the
 * base's `return -1` and igStructMetaField's `_alignment` accessor. */
int Gap__Core__igUnsignedLongMetaField__vfunc_27(igUnsignedLongArrayMetaField *self) {
    return 8;
}

