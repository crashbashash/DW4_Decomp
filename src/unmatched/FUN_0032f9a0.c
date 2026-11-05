int FUN_0020d360(int);
long long FUN_0022f1e0(int, int);
extern int DAT_004fb410[4];
extern int DAT_004fb418[4];
extern unsigned char GPR_00554ddc;
void FUN_0032f9a0(int *arg0, int arg1, int arg2) {
    if (GPR_00554ddc != 0) {
        FUN_0020d360((int)FUN_0022f1e0(arg2, 0xF4240));
        *arg0 = DAT_004fb410[0];
    } else {
        *arg0 = DAT_004fb418[0];
    }
}
