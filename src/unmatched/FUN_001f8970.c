extern char DAT_00554bc0;
extern int DAT_00491270[4];
extern int DAT_00491478[4];
extern long long DAT_0056af08[4];
void FUN_001f8970(void) {
    if (DAT_00554bc0 != 1) {
        DAT_00554bc0 = 1;
        DAT_00491270[0] = 1;
        DAT_0056af08[0] += 1;
        DAT_00491478[0] |= 0x97;
    }
}
