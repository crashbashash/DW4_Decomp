int png_get_valid();
int png_get_IHDR();
int png_set_strip_16();
int png_set_gray_1_2_4_to_8();
int png_set_tRNS_to_alpha();
int png_set_read_user_transform_fn();
int png_set_packing();
void FUN_001673a0(void);
int FUN_001681c0(int arg0, int arg1, int arg2) {
    int sp44;
    int sp48;
    int sp4C;
    int sp50;
    int sp54;
    int sp58;
    int sp5C;

    png_get_IHDR(arg1, arg2, &sp5C, &sp58, &sp54, &sp50, &sp4C, &sp48, &sp44);
    png_set_strip_16(arg1);
    if ((sp54 < 8) && (sp50 == 3)) {
        png_set_packing(arg1);
    }
    if (sp54 < 8) {
        if (sp50 == 0) {
            png_set_gray_1_2_4_to_8(arg1);
        }
    }
    if ((png_get_valid(arg1, arg2, 0x10) != 0) && !(sp50 & 4) && !(sp50 & 1)) {
        png_set_tRNS_to_alpha(arg1);
    }
    png_set_read_user_transform_fn(arg1, FUN_001673a0);
    return 1;
}
