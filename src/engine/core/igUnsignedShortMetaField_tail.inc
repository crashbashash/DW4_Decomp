int Gap__Core__igUnsignedShortMetaField__vfunc_56(int arg0, int arg1, int arg2) {
    int sp1C;

    sp1C = 0;
    sscanf(arg2, &text_hd_n[0], arg1, &sp1C);
    return sp1C;
}

void Gap__Core__igUnsignedShortMetaField__vfunc_57(int *arg0, int arg1, unsigned short *arg2) {
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
                var_v0 = ((int)StringPool_Construct((S_2eadf0 *)var_v0));
            }
            g_stringPool[0] = var_v0;
        }
        var_v1 = StringPool_Intern((StringPool *)g_stringPool[0], (const char *)sp20);
    }
    *arg0 = var_v1;
}

int FUN_0030ed90(void) {
    return 2;
}

void FUN_0030eda0(void **arg0, short arg1) {
    short sp1E;

    sp1E = arg1;
    ((DW4VC_140_1 *)(arg0))->vX((int)(&sp1E));
}

int **FUN_0030edd0(int **arg0, int extra1) {
    igMetaField_Construct((igMetaField *)arg0);
    *arg0 = &DAT_00533630[0];
    if (arg0 != 0) {
        FUN_0030ee10(arg0);
    }
    return arg0;
}

int **FUN_0030ee10(int **arg0) {
    igMetaField_Init((igMetaField *)arg0);
    *arg0 = &DAT_00533630[0];
    return arg0;
}

int **FUN_0030ee50(int **arg0, int extra1) {
    igMetaField_CopyConstruct((igMetaField *)arg0, (igMetaField *)extra1);
    *arg0 = &DAT_00533630[0];
    return arg0;
}

void Gap__Core__igUnsignedShortMetaField__vfunc_02(int extra0) {
    igMetaField_Destruct((igMetaField *)extra0);
}

/* igUnsignedShortArrayMetaField vtable slot 27 (+0x6c): constant leaf returning 2, the byte size
 * of one unsigned short element. The same igMetaField slot is the base's `return -1` and
 * igStructMetaField's `_alignment` accessor. */
int Gap__Core__igUnsignedShortMetaField__vfunc_27(igUnsignedShortArrayMetaField *self) {
    return 2;
}

