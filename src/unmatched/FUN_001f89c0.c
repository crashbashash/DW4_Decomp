extern int DAT_00491270[4];
extern int DAT_00491478[4];
extern long long DAT_0056af08[4];
extern long long DAT_0056b478[4];
extern char GPR_00554bc0;

void FUN_001f89c0(void) {
    if (GPR_00554bc0 != 0) {
        GPR_00554bc0 = 0;
        DAT_0056af08[0] += 1;
        DAT_0056b478[0] &= (int)0xFFFF1E7F;
        DAT_00491270[0] = 1;
        DAT_00491478[0] |= 0x97;
    }
}
