int FUN_001e8990();
extern float DAT_0048dc88[4];
extern float DAT_0048dc8c[4];
extern int DAT_00491478[4];
extern int DAT_00562cb8[4];
void FUN_001e8a90(int arg0, float fparg0, float fparg1, float fparg2) {
    float temp_f2;

    if (DAT_00562cb8[0] != arg0) {
        DAT_00562cb8[0] = arg0;
        DAT_00491478[0] |= 1;
    }
    switch (arg0) {
    case 0:
        temp_f2 = -255.0f / (fparg1 - fparg0);
        DAT_0048dc88[0] = temp_f2;
        DAT_0048dc8c[0] = 255.0f - (temp_f2 * fparg0);
        break;
    case 1:
    case 2:
        DAT_0048dc88[0] = fparg2;
        DAT_0048dc8c[0] = fparg2;
        break;
    case 3:
        break;
    }
    FUN_001e8990();
}
