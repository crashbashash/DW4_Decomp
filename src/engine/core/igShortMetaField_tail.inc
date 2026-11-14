int igShortMetaField_ValueFromString(int arg0, int arg1, int arg2) {
    int sp1C;

    sp1C = 0;
    sscanf(arg2, &text_hd_n[0], arg1, &sp1C);
    return sp1C;
}

void igShortMetaField_ValueToString(int *arg0, int arg1, short *arg2) {
    char sp20[1024];
    int var_v0;
    int var_v1;

    sprintf(sp20, &DAT_004fb428[0], *arg2);
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

int **igShortMetaField_Construct(int **arg0, int extra1) {
    igMetaField_Construct((igMetaField *)arg0);
    *arg0 = &DAT_00533080[0];
    if (arg0 != 0) {
        igShortMetaField_Init(arg0);
    }
    return arg0;
}

int **igShortMetaField_Init(int **arg0) {
    igMetaField_Init((igMetaField *)arg0);
    *arg0 = &DAT_00533080[0];
    return arg0;
}

int **igShortMetaField_CopyConstruct(int **arg0, int extra1) {
    igMetaField_CopyConstruct((igMetaField *)arg0, (igMetaField *)extra1);
    *arg0 = &DAT_00533080[0];
    return arg0;
}

void igShortMetaField_Destruct(int extra0) {
    igMetaField_Destruct((igMetaField *)extra0);
}

/* igRegistryValueList vtable slot 53 (+0xd4): constant leaf returning 2. */
int igShortMetaField_GetSize(igRegistryValueList *self) {
    return 2;
}

void igShortMetaField_SetDefault(void **arg0, short arg1) {
    short sp1E;

    sp1E = arg1;
    ((igMetaFieldView *)(arg0))->SetDefault(&sp1E);
}

int igShortMetaField_GetAlignment(void) {
    return 2;
}

