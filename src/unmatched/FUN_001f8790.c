int FUN_001e7500();
int FUN_001f89c0();
extern int DAT_00491270[4];
extern int DAT_00491478[4];
extern int DAT_0056af40[8];
extern int DAT_0056af60[4];
extern int DAT_0056af64[4];
extern int DAT_0056af68[4];
extern int DAT_0056af70[4];
extern int DAT_0056b488[4];
extern char GPR_00554bc4;

void FUN_001f8790(void) {
    int *temp_v0;
    int var_a0;

    var_a0 = 0;
    do {
        temp_v0 = &DAT_0056af40[var_a0];
        var_a0 += 1;
        *temp_v0 = 0;
    } while (var_a0 < 8);
    DAT_0056af60[0] = 0;
    DAT_0056af64[0] = 0;
    DAT_00491478[0] |= 4;
    FUN_001e7500(0xC);
    DAT_00491270[0] = 1;
    GPR_00554bc4 = 0;
    DAT_0056b488[0] = 0;
    DAT_0056af68[0] = 0;
    DAT_0056af70[0] = 0;
    FUN_001f89c0();
}
