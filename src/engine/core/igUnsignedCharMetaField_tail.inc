int Gap__Core__igUnsignedCharMetaField__vfunc_56(void *arg0, char *arg1, int arg2) {
    int sp2C;
    int sp28;

    sp2C = 0;
    sp28 = 0;
    sscanf(arg2, &DAT_004fb440[0], &sp28, &sp2C);
    *arg1 = (char) sp28;
    return sp2C;
}

void Gap__Core__igUnsignedCharMetaField__vfunc_57(int *arg0, int arg1, unsigned char *arg2) {
    int sp20[256];
    int var_v0;
    int var_v1;
    sprintf(sp20, &DAT_004f9948[0], *arg2);
    if (sp20 == 0) {
        var_v1 = 0;
    } else {
        if (DAT_00586f20[0] == 0) {
            var_v0 = ((int)FUN_002eb010(0x10));
            if (var_v0 != 0) {
                var_v0 = ((int)StringPool_Construct((S_2eadf0 *)var_v0));
            }
            DAT_00586f20[0] = var_v0;
        }
        var_v1 = StringPool_Intern((StringPool *)DAT_00586f20[0], (const char *)sp20);
    }
    *arg0 = var_v1;
}

/* igMetaField slot +0x64 (GetSize): the byte size of one field value. An unsigned char is a single
 * byte. The field constructor stores this result as the field's `_size` (+0x14). */
int igUnsignedCharMetaField_GetSize(void) {
    return 1;
}

void FUN_0030e750(void **arg0, char arg1) {
    char sp1F;

    sp1F = arg1;
    ((DW4VC_140_1 *)(arg0))->vX((int)(&sp1F));
}

int Gap__Core__igUnsignedCharMetaField__vfunc_27(void) {
    return 1;
}

