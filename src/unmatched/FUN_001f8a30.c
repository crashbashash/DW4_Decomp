extern int DAT_00491270[4];
extern int DAT_00491478[4];
extern long long DAT_0056af20[4];
extern int DAT_0056af40[4];
void FUN_001f8a30(int arg0, int *arg1) {
    if (arg1[27] & 8) {
        DAT_00491270[0] = 1;
        arg1[27] = arg1[27] & ~8;
    }
    DAT_0056af20[0] += 1;
    DAT_0056af40[arg0] = (int)arg1;
    DAT_00491478[0] |= 4;
}
