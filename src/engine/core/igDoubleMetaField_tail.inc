int Gap__Core__igDoubleMetaField__vfunc_56(int arg0, int arg1, int arg2) {
    int sp1C;

    sp1C = 0;
    sscanf(arg2, &text_lg_n[0], arg1, &sp1C);
    return sp1C;
}

void Gap__Core__igDoubleMetaField__vfunc_57(int *arg0, int arg1, long long *arg2) {
    int sp20[256];
    int var_v0;
    int var_v1;

    sprintf(sp20, &DAT_004f9610[0], *arg2);
    if (sp20 == 0) {
        var_v1 = 0;
    } else {
        if (g_stringPool[0] == 0) {
            var_v0 = ((int)StringPool_Allocate(0x10));
            if (var_v0 != 0) {
                var_v0 = ((int)StringPool_Construct((StringPool *)var_v0));
            }
            g_stringPool[0] = var_v0;
        }
        var_v1 = StringPool_Intern((StringPool *)g_stringPool[0], (const char *)sp20);
    }
    *arg0 = var_v1;
}

int Gap__Core__igDoubleMetaField__vfunc_25(void) {
    return 8;
}

void FUN_002d9500(void **arg0, long long arg1) {
    long long sp18;

    sp18 = arg1;
    ((igMetaFieldView *)(arg0))->SetDefault(&sp18);
}

int Gap__Core__igDoubleMetaField__vfunc_27(void) {
    return 8;
}

