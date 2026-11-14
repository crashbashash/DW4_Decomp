int igDoubleMetaField_ValueFromString(int arg0, int arg1, int arg2) {
    int sp1C;

    sp1C = 0;
    sscanf(arg2, &text_lg_n[0], arg1, &sp1C);
    return sp1C;
}

void igDoubleMetaField_ValueToString(int *arg0, int arg1, long long *arg2) {
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

int igDoubleMetaField_GetSize(void) {
    return 8;
}

void igDoubleMetaField_SetDefaultDouble(void **arg0, long long arg1) {
    long long sp18;

    sp18 = arg1;
    ((igMetaFieldView *)(arg0))->SetDefault(&sp18);
}

int igDoubleMetaField_GetAlignment(void) {
    return 8;
}

