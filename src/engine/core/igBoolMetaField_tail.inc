int Gap__Core__igBoolMetaField__vfunc_56(void *arg0, char *arg1, int arg2) {
    int sp3C;
    int sp38;

    sp3C = 0;
    sp38 = 0;
    sscanf(arg2, &DAT_004f9588[0], &sp38, &sp3C);
    if (sp3C > 0) {
        *arg1 = sp38 != 0;
        return sp3C;
    }
    if (strncasecmp(&text_true_2[0], arg2, 4) == 0) {
        *arg1 = 1;
        return 4;
    }
    if (strncasecmp(&text_false_2[0], arg2, 5) == 0) {
        *arg1 = 0;
        return 5;
    }
    return 0;
}

void Gap__Core__igBoolMetaField__vfunc_57(int *arg0, void *arg1, unsigned char *arg2) {
    int sp20[256];
    int *var_a2;
    int var_v0;
    int var_v1;

    if (*arg2 != 0) {
        var_a2 = (int *)(&text_true_2[0]);
    } else {
        var_a2 = (int *)(&text_false_2[0]);
    }
    sprintf(sp20, &DAT_004f95a0[0], var_a2);
    if (sp20 == 0) {
        var_v1 = 0;
    } else {
        if (g_stringPool[0] == 0) {
            var_v0 = ((int)StringPool_Allocate(0x10));
            if (var_v0 != 0) {
                var_v0 = ((int)StringPool_Construct((S_2eadf0 *)var_v0));
            }
            g_stringPool[0] = var_v0;
        }
        var_v1 = StringPool_Intern((StringPool *)g_stringPool[0], (const char *)sp20);
    }
    *arg0 = var_v1;
}

int **FUN_002d37b0(int **arg0, int extra1) {
    igMetaField_Construct((igMetaField *)arg0);
    *arg0 = &DAT_00531540[0];
    if (arg0 != 0) {
        FUN_002d37f0(arg0);
    }
    return arg0;
}

int **FUN_002d37f0(int **arg0) {
    igMetaField_Init((igMetaField *)arg0);
    *arg0 = &DAT_00531540[0];
    return arg0;
}

int **FUN_002d3830(int **arg0, int extra1) {
    igMetaField_CopyConstruct((igMetaField *)arg0, (igMetaField *)extra1);
    *arg0 = &DAT_00531540[0];
    return arg0;
}

void Gap__Core__igBoolMetaField__vfunc_02(int extra0) {
    igMetaField_Destruct((igMetaField *)extra0);
}

int FUN_002d3880(void) {
    return 1;
}

void FUN_002d3890(void **arg0, char arg1) {
    char sp1F;

    sp1F = arg1;
    ((DW4VC_140_1 *)(arg0))->vX((int)(&sp1F));
}

int Gap__Core__igBoolMetaField__vfunc_27(void) {
    return 1;
}

void FUN_002d38d0(int a0, int a1)
{
    *(int *)((char *)a0 + 8) = a1;
}

